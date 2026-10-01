#!/usr/bin/env bash
# Try to associate to the AP's 5 GHz BSSID with ac_5ghz=1. Per init: 5 GHz connect; if that fails,
# 2.4 GHz connect on the same init tells a bad init (both fail) from a 5 GHz problem (only 5 GHz fails).
# Run with sudo. Restores the profile (no pinned BSSID) and the normal wrapper at the end.
P=Vodafone-2A84; IF=wlp3s0b1; B5=8C:6A:8D:9E:2A:90; B24=8C:6A:8D:9E:2A:88
OUT=${1:-/home/gonsolo/bcm4360-acphy/test-logs/5ghz-connect-$(date +%H%M%S).log}
KM=/dev/kmsg
conn() { nmcli connection modify "$P" 802-11-wireless.bssid "$1"; nmcli --wait 0 connection up "$P" ifname $IF >/dev/null 2>&1
	for _ in $(seq 30); do sleep 1; [ "$(nmcli -t -f DEVICE,STATE device | grep ^$IF:)" = "$IF:connected" ] && return 0; done; return 1; }
: > "$OUT"
for t in 1 2 3 4 5 6; do
	rmmod b43 2>/dev/null
	/home/gonsolo/bcm4360-acphy/tools/b43_boot.sh ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 ac_5ghz=1 >/dev/null 2>&1
	for _ in $(seq 40); do nmcli -t device | grep -q "^$IF" && break; sleep 1; done
	echo "b43 5ghz test try $t" > $KM
	if conn $B5; then echo "try $t: 5GHz CONNECTED" >> "$OUT"; ping -I $IF -c 3 -W 2 192.168.0.1 >> "$OUT" 2>&1; iw dev $IF link >> "$OUT" 2>&1; break; fi
	echo "try $t: 5GHz failed" >> "$OUT"
	if conn $B24; then echo "try $t: 2.4GHz connects on this init -> good init, 5 GHz itself fails" >> "$OUT"; break; fi
	echo "try $t: 2.4GHz also failed -> bad init" >> "$OUT"
done
dmesg | sed -n '/b43 5ghz test try/,$p' | grep -i "b43\|phy" | tail -40 >> "$OUT"
nmcli connection modify "$P" 802-11-wireless.bssid ""
echo done >> "$OUT"
