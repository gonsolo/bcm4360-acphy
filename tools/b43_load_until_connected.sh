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

# Evidence of a bad init: PHY TX errors and MAC suspend failures (both rate-limited in dmesg) and mac80211
# auth timeouts (not, but only one per ~17 s).
errs() { $DMESG 2>/dev/null | grep -cE "PHY transmission error|MAC suspend failed|authentication with .* timed out"; }
log() { echo "b43_load_until_connected: $*"; }

for try in $(seq 1 "$TRIES"); do
	base=$(errs)
	if ! $LOAD "$@"; then
		log "try $try/$TRIES: load failed"
		verdict=bad
	else
		verdict=quiet
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
			if [ $(( $(errs) - base )) -ge "$MAX_ERRS" ]; then
				verdict=bad
				break
			fi
			$SLEEP "$POLL"
			waited=$(( waited + POLL ))
		done
	fi
	if [ "$verdict" = quiet ]; then
		log "try $try/$TRIES: no connect attempt and no TX errors; keeping this init"
		exit 0
	fi
	if [ "$try" -lt "$TRIES" ]; then
		log "try $try/$TRIES: bad init (TX errors), reloading"
		$RMMOD b43
		$SLEEP 2
	fi
done
log "gave up after $TRIES bad inits; leaving the last one loaded"
exit 1
