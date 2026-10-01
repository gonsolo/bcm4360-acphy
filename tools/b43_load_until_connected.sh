#!/usr/bin/env bash
# Load b43 and keep reloading it until an init is clean (notes/57, 103-105): only ~25-35 % of fresh
# inits can transmit; in the others every TX ends in a "PHY transmission error" and the connect
# never completes. A scan does NOT reveal a bad init (notes/105), the first connect attempt does.
#
# Per try: load (tools/b43_boot.sh), start a connect, then watch up to B43_WAIT (45) seconds:
#   - wlp3s0b1 reports "connected"                         -> done, clean init
#   - >= B43_MAX_ERRS new "PHY transmission error" / "authentication ... timed out" lines
#                                                           -> bad init, unload and try again
#   - neither (no connect attempt happened / out of range)  -> nothing to judge, keep this init
# After B43_TRIES bad tries it leaves the last one loaded and exits 1.
#
# Every unload/load restarts wpa_supplicant on NixOS (other wlan links blink); run at boot, not mid-work.
# usage: tools/b43_load_until_connected.sh [b43 module params...]   (the b43-ac-load.service params)
# Tests: bash tools/test_b43_load_until_connected.sh   (all commands are overridable via B43_* env)
set -u
P=${B43_PROJ:-/home/gonsolo/bcm4360-acphy}
IF=${B43_IF:-wlp3s0b1}
LOAD=${B43_LOAD:-$P/tools/b43_boot.sh}
RMMOD=${B43_RMMOD:-rmmod}
NMCLI=${B43_NMCLI:-nmcli}
DMESG=${B43_DMESG:-dmesg}
SLEEP=${B43_SLEEP:-sleep}
TRIES=${B43_TRIES:-6}
WAIT=${B43_WAIT:-45}
POLL=${B43_POLL:-2}
MAX_ERRS=${B43_MAX_ERRS:-3}
MAX_AUTH=${B43_MAX_AUTH:-2}
MAX_SUSP=${B43_MAX_SUSP:-8}

# Evidence of a bad init (deltas since this try's load): PHY TX errors (only logged with verbose=3, so
# usually 0 in production), MAC suspend failures and mac80211 auth timeouts (one per ~17 s).
# Early verdict "bad": phy >= MAX_ERRS, or auth >= MAX_AUTH, or susp >= MAX_SUSP. A few suspend failures
# alone are normal for an init that goes on to connect. At the end of the window, an init that tried and
# failed (any evidence) but did not connect is bad too; one with no evidence at all is kept.
cnt() { $DMESG 2>/dev/null | grep -cE "$1"; }
log() { echo "b43_load_until_connected: $*"; }

for try in $(seq 1 "$TRIES"); do
	bphy=$(cnt "PHY transmission error"); bsusp=$(cnt "MAC suspend failed"); bauth=$(cnt "authentication with .* timed out")
	if ! $LOAD "$@"; then
		log "try $try/$TRIES: load failed"
		verdict=bad
	else
		verdict=quiet
		phy=0; susp=0; auth=0
		waited=0
		tried=0
		while [ "$waited" -lt "$WAIT" ]; do
			# NM autoconnect does not reliably pick up the b43 interface (a profile can be active on one
			# device only), so start the attempt ourselves once the renamed interface exists.
			if [ "$tried" = 0 ] && $NMCLI -t -f DEVICE device 2>/dev/null | grep -q "^$IF"; then
				$NMCLI --wait 0 device connect "$IF" >/dev/null 2>&1
				tried=1
			fi
			state=$($NMCLI -t -f DEVICE,STATE device 2>/dev/null | grep "^$IF:" | cut -d: -f2)
			if [ "$state" = connected ]; then
				log "try $try/$TRIES: connected, clean init"
				exit 0
			fi
			phy=$(( $(cnt "PHY transmission error") - bphy )); susp=$(( $(cnt "MAC suspend failed") - bsusp ))
			auth=$(( $(cnt "authentication with .* timed out") - bauth ))
			if [ "$phy" -ge "$MAX_ERRS" ] || [ "$auth" -ge "$MAX_AUTH" ] || [ "$susp" -ge "$MAX_SUSP" ]; then
				verdict=bad
				break
			fi
			$SLEEP "$POLL"
			waited=$(( waited + POLL ))
		done
		[ "$verdict" = quiet ] && [ $(( phy + susp + auth )) -ge 1 ] && verdict=bad
	fi
	if [ "$verdict" = quiet ]; then
		log "try $try/$TRIES: no connect attempt and no TX errors; keeping this init"
		exit 0
	fi
	if [ "$try" -lt "$TRIES" ]; then
		log "try $try/$TRIES: bad init, reloading (evidence since load: phy=$(( $(cnt "PHY transmission error") - bphy )) susp=$(( $(cnt "MAC suspend failed") - bsusp )) auth=$(( $(cnt "authentication with .* timed out") - bauth )))"
		$RMMOD b43
		$SLEEP 2
	fi
done
log "gave up after $TRIES bad inits; leaving the last one loaded"
exit 1
