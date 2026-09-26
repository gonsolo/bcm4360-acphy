#!/usr/bin/env bash
# ACK test without NetworkManager or the USB stick: open-system auth to the
# router with iw; count the router's auth replies as received by b43's own
# monitor vif (b43mon). ~1 reply per request means the router got our ACK.
# usage: sudo tools/acktest.sh [tries]
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1; IW=$P/tools/iw/bin/iw; TD=$P/tools/tcpdump/bin/tcpdump
BSSID=${BSSID:-8c:6a:8d:9e:2a:88}; FREQ=${FREQ:-2412}; N=${1:-3}
S=/sys/kernel/debug/b43ac/shm
rd() { echo $1 > $S; printf "%d" 0x$(cut -d" " -f2 $S); }
a0=$(rd e6)
echo "acktest: start" > /dev/kmsg
f=$(mktemp)
$TD -i b43mon -e -n -w "$f" 2>/dev/null & cap=$!
sleep 1
for i in $(seq 1 $N); do
	# 2437 (channel 6) applies the replayed wl state on 2.4 GHz only.
	# Passive (DFS) channels may need several scans to catch a beacon.
	for s in 1 2 3 4 5 6; do
		$IW dev $IF scan freq $([ $FREQ -lt 5000 ] && echo 2437) $FREQ 2>/dev/null | grep -qi "$BSSID" && break
	done
	$IW dev $IF auth Vodafone-2A84 $BSSID open $FREQ >/dev/null 2>&1
	sleep 1.5
	$IW dev $IF disconnect >/dev/null 2>&1
	sleep 0.5
done
sleep 0.5; kill $cap; wait $cap 2>/dev/null
req=$(dmesg | tac | sed "/acktest: start/q" | grep -c "$IF: send auth")
ok=$(dmesg | tac | sed "/acktest: start/q" | grep -c "$IF: authenticated")
rsp=$($TD -r "$f" -e -n 2>/dev/null | grep -c "SA:$BSSID Authentication (Open System)-2")
echo "auth requests $req, authenticated $ok, router auth replies seen $rsp (ideal $ok), ucode txackfrm +$(( ($(rd e6) - a0) & 0xffff ))"
rm -f "$f"
