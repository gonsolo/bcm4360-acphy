#!/usr/bin/env bash
# notes/105: like init_snapshot_test.sh, but the PHY/radio/MAC/SHM snapshot is taken ~15 s INTO
# the connect attempt (while the PHY is in whatever TX state it is in, the interface still up),
# not after it. Each run records the interface state, channel and the suspend/TX-error counts.
# usage: sudo tools/init_snapshot_test2.sh <N> [outdir]
set -u
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1
IW=$P/tools/iw/bin/iw
DBG=/sys/kernel/debug/b43ac
N=${1:?count}; OUT=${2:-$P/test-logs/init-snap2-$(date +%H%M%S)}
mkdir -p "$OUT"
for i in $(seq 1 "$N"); do
	R="$OUT/run$i"; mkdir -p "$R"
	dmesg -c > /dev/null
	nmcli dev set $IF managed no 2>/dev/null
	rmmod b43 2>/dev/null
	CH=6 $P/b43_live.sh load ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 > /dev/null
	sleep 1
	$IW dev $IF set channel 1
	ip link set $IF down
	$IW dev $IF set type managed
	nmcli dev set $IF managed yes
	sleep 2
	for k in 1 2; do nmcli dev wifi rescan ifname $IF 2>/dev/null; sleep 5; done
	e0=$(dmesg | grep -c "PHY transmission error")
	(timeout 70 nmcli --wait 60 con up b43-test ifname $IF > "$R/connect.txt" 2>&1) &
	CP=$!
	sleep 15
	{ echo "state=$(nmcli -t -f DEVICE,STATE device | grep "^$IF:" | cut -d: -f2)"; $IW dev $IF info 2>/dev/null | grep -E "channel|type"; echo "txerr_so_far=$(( $(dmesg | grep -c 'PHY transmission error') - e0 ))"; echo "suspend_fail_so_far=$(dmesg | grep -c 'MAC suspend failed')"; } > "$R/at_snapshot.txt"
	cat $DBG/phydump > "$R/phy.txt" 2>/dev/null
	$P/tools/radiodump.sh > "$R/radio.txt" 2>/dev/null
	cat $DBG/macdump > "$R/mac.txt" 2>/dev/null
	$P/tools/full_snapshot > "$R/shm_ihr.txt" 2>/dev/null
	wait $CP
	e1=$(dmesg | grep -c "PHY transmission error")
	fails=$(dmesg | grep -c "MAC suspend failed")
	state=$(nmcli -t -f DEVICE,STATE device | grep "^$IF:" | cut -d: -f2)
	label=bad; [ "$state" = connected ] && label=conn
	echo "$state $fails $((e1 - e0)) $label" > "$R/outcome.txt"
	echo "run $i: state=$state suspend_failures=$fails phytxerr_during_connect=$((e1 - e0)) -> $label"
	sleep 3
done
echo "OUT=$OUT"
