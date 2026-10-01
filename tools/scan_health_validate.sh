#!/usr/bin/env bash
# notes/105: does a short active scan right after load predict the connect outcome?
# For each fresh init: scan phase (2 x nmcli rescan, 5 s apart) -> count PHY TX errors and MAC suspend
# failures in that window; then the normal connect attempt -> outcome and counts. One CSV line per init.
# usage: sudo tools/scan_health_validate.sh <N>
set -u
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1; IW=$P/tools/iw/bin/iw
N=${1:?count}
OUT=$P/test-logs/scan-health-$(date +%H%M%S).csv
echo "run,scan_phytxerr,scan_suspendfail,conn_state,total_phytxerr,total_suspendfail" > "$OUT"
for i in $(seq 1 "$N"); do
	dmesg -c > /dev/null
	nmcli dev set $IF managed no 2>/dev/null
	rmmod b43 2>/dev/null
	CH=6 $P/b43_live.sh load ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 > /dev/null 2>&1
	sleep 1
	$IW dev $IF set channel 1; ip link set $IF down; $IW dev $IF set type managed
	nmcli dev set $IF managed yes
	sleep 2
	d0=$(dmesg | wc -l)
	for k in 1 2; do nmcli dev wifi rescan ifname $IF 2>/dev/null; sleep 5; done
	sp=$(dmesg | grep -c "PHY transmission error"); ss=$(dmesg | grep -c "MAC suspend failed")
	timeout 70 nmcli --wait 60 con up b43-test ifname $IF > /dev/null 2>&1
	tp=$(dmesg | grep -c "PHY transmission error"); ts=$(dmesg | grep -c "MAC suspend failed")
	st=$(nmcli -t -f DEVICE,STATE device | grep "^$IF:" | cut -d: -f2)
	echo "$i,$sp,$ss,${st:-none},$tp,$ts" | tee -a "$OUT"
	sleep 3
done
echo "OUT=$OUT"
