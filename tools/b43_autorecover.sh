#!/usr/bin/env bash
# Auto-recovery watchdog for daily use (notes/86 Phase 2a): if wlp3s0b1
# stays disconnected while its AP's SSID is still visible, reload b43
# via the normal daily-use path (tools/b43_boot.sh) instead of leaving
# the user to notice and do it by hand. Rate-limited (chip-degradation
# caution, notes/59/77) - at most MAX_PER_HOUR reloads.
# Run detached: sudo systemd-run --unit=b43-autorecover --collect \
#   --setenv=PATH="$PATH:/home/gonsolo/bcm4360-acphy/tools/iw/bin" \
#   bash tools/b43_autorecover.sh
set -u
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1
SSID="${B43_AUTORECOVER_SSID:-Vodafone-2A84}"
LOG=$P/test-logs/b43_autorecover.log
# notes/88 live test: a single real connect attempt can legitimately
# take up to ~70s (connect_test.sh's own ceiling, matching mac80211's
# auth-retry timeout) before succeeding or failing on its own - a 60s
# trigger can pre-empt a still-in-flight attempt. 90s gives real
# attempts room to finish while still recovering promptly from a
# genuinely stuck/flapping interface.
POLL_SECS=15
DISCONNECTED_POLLS_TRIGGER=6  # ~90s
MAX_PER_HOUR=6
ATTEMPTS_FILE=/run/b43_autorecover_attempts

echo "$(date) b43-autorecover start (ssid=$SSID)" >> "$LOG"
: > "$ATTEMPTS_FILE" 2>/dev/null || true
disconnected_polls=0

recent_attempts() {
	now=$(date +%s)
	[ -f "$ATTEMPTS_FILE" ] || { echo 0; return; }
	awk -v now="$now" '{if (now - $1 < 3600) print}' "$ATTEMPTS_FILE" > "${ATTEMPTS_FILE}.tmp"
	mv "${ATTEMPTS_FILE}.tmp" "$ATTEMPTS_FILE"
	wc -l < "$ATTEMPTS_FILE"
}

while true; do
	if [ ! -e "/sys/class/net/$IF" ]; then
		iface_present=0
		state="absent"
	else
		iface_present=1
		state=$(nmcli -t -f DEVICE,STATE device 2>/dev/null | awk -F: -v d="$IF" '$1==d{print $2}')
	fi

	if [ "$state" = "connected" ]; then
		disconnected_polls=0
	else
		disconnected_polls=$((disconnected_polls + 1))
		echo "$(date) $IF state=$state ($disconnected_polls)" >> "$LOG"
	fi

	if [ "$disconnected_polls" -ge "$DISCONNECTED_POLLS_TRIGGER" ]; then
		# If the interface is gone entirely (b43 unloaded, e.g. by
		# netwatch, or crashed out), there's nothing to scan with -
		# that alone is grounds to reload. Otherwise, only reload if
		# the AP's SSID is actually visible (a real AP outage or being
		# out of range won't be fixed by reloading, and shouldn't burn
		# a reload attempt).
		should_recover=0
		if [ "$iface_present" -eq 0 ]; then
			should_recover=1
			why="interface absent"
		elif nmcli -t -f SSID dev wifi list ifname "$IF" 2>/dev/null | grep -qF "$SSID"; then
			should_recover=1
			why="SSID visible"
		fi

		if [ "$should_recover" -eq 1 ]; then
			n=$(recent_attempts)
			if [ "$n" -lt "$MAX_PER_HOUR" ]; then
				echo "$(date) $IF disconnected ~$((disconnected_polls * POLL_SECS))s ($why), reloading (attempt $((n + 1))/$MAX_PER_HOUR this hour)" >> "$LOG"
				echo "b43-autorecover: reloading b43" > /dev/kmsg
				date +%s >> "$ATTEMPTS_FILE"
				rmmod b43 2>> "$LOG"
				sleep 2
				bash "$P/tools/b43_boot.sh" ac_replay=0 dma32=1 ac_por=7 nohwcrypt=1 >> "$LOG" 2>&1
			else
				echo "$(date) $IF disconnected but $MAX_PER_HOUR/hour cap reached, not reloading" >> "$LOG"
			fi
		else
			echo "$(date) $IF disconnected but SSID '$SSID' not visible, leaving alone" >> "$LOG"
		fi
		disconnected_polls=0
		sleep 20
	fi

	sleep "$POLL_SECS"
done
