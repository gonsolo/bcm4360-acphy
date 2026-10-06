#!/usr/bin/env bash
# notes/104: each fresh b43 init is randomly good or bad (notes/57). Snapshot the
# PHY/radio/MAC/SHM state right after load, then run the usual connect attempt and
# label the init by its suspend failures, so good and bad snapshots can be diffed.
# usage: sudo tools/init_snapshot_test.sh <N> [outdir]
set -u
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1
IW=$P/tools/iw/bin/iw
DBG=/sys/kernel/debug/b43ac
N=${1:?count}; OUT=${2:-$P/test-logs/init-snap-$(date +%H%M%S)}
mkdir -p "$OUT"
for i in $(seq 1 "$N"); do
	R="$OUT/run$i"; mkdir -p "$R"
	dmesg -c > /dev/null
	nmcli dev set $IF managed no 2>/dev/null
	rmmod b43 2>/dev/null
	CH=6 $P/b43_live.sh load ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 > /dev/null
	sleep 1
	cat $DBG/phydump > "$R/phy.txt" 2>/dev/null
	$P/tools/radiodump.sh > "$R/radio.txt" 2>/dev/null
	cat $DBG/macdump > "$R/mac.txt" 2>/dev/null
	cat $DBG/tbldump > "$R/tbl.txt" 2>/dev/null
	$P/tools/full_snapshot > "$R/shm_ihr.txt" 2>/dev/null
	dmesg | grep -E "AC PMU|AC FIFO|replayed|first-load" > "$R/dmesg_init.txt"
	$IW dev $IF set channel 1
	ip link set $IF down
	$IW dev $IF set type managed
	nmcli dev set $IF managed yes
	sleep 2
	for k in 1 2; do nmcli dev wifi rescan ifname $IF 2>/dev/null; sleep 5; done
	timeout 70 nmcli --wait 60 con up b43-test ifname $IF > "$R/connect.txt" 2>&1
	cat $DBG/phydump > "$R/phy_after.txt" 2>/dev/null
	$P/tools/radiodump.sh > "$R/radio_after.txt" 2>/dev/null
	cat $DBG/macdump > "$R/mac_after.txt" 2>/dev/null
	cat $DBG/tbldump > "$R/tbl_after.txt" 2>/dev/null
	fails=$(dmesg | grep -c "MAC suspend failed")
	state=$(nmcli -t -f DEVICE,STATE device | grep "^$IF:" | cut -d: -f2)
	label=bad; { [ "$state" = connected ] && [ "$fails" -le 2 ]; } && label=good
	echo "$state $fails $label" > "$R/outcome.txt"
	echo "run $i: state=$state suspend_failures=$fails -> $label"
	sleep 3
done
echo "OUT=$OUT"
