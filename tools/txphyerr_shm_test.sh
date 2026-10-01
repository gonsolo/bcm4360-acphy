#!/usr/bin/env bash
# Read the ucode's txphyerr SHM record (shared SHM 0xBE0..0xC20) on a good and on a bad init.
# Reloads b43 until an init does NOT connect (max 8 tries), dumps, then restores a connection
# via the wrapper service. Run with sudo, one thing at a time.
D=/sys/kernel/debug/b43ac/shm
OUT=${1:-test-logs/txphyerr-shm-$(date +%H%M%S).log}
dump() { echo "== $1" >> "$OUT"; for a in $(seq $((${LO:-0xBE0})) 2 $((${HI:-0xC20}))); do printf '%x\n' $a > $D; printf '%s ' "$(cat $D)"; done | tr ' ' '\n' | paste -sd' ' | fold -w 100 >> "$OUT"; }
connected() { [ "$(nmcli -t -f DEVICE,STATE device | grep wlp3s0b1)" = "wlp3s0b1:connected" ]; }
: > "$OUT"
connected && dump "current init (connected, good)"
for t in 1 2 3 4 5 6 7 8; do
	rmmod b43 2>/dev/null
	/home/gonsolo/bcm4360-acphy/tools/b43_boot.sh ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 >/dev/null 2>&1
	for _ in $(seq 40); do nmcli -t device | grep -q '^wlp3s0b1' && break; sleep 1; done
	nmcli --wait 0 device connect wlp3s0b1 >/dev/null 2>&1
	sleep 30
	if connected; then echo "try $t: connected" >> "$OUT"; else echo "try $t: NOT connected" >> "$OUT"; dump "bad init after try $t"; break; fi
done
connected || systemctl restart b43-ac-load.service
echo done >> "$OUT"
