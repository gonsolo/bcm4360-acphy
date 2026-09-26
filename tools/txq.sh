#!/usr/bin/env bash
# TX quality: inject from b43 (monitor), count unique intact frames at the USB stick's mon0.
# usage: sudo tools/txq.sh [count] [tag]
P=/home/gonsolo/bcm4360-acphy
N=${1:-50}
TAG=${2:-1}
IF=$(for i in /sys/class/net/*; do readlink $i/device/driver 2>/dev/null | grep -q b43 && basename $i; done | head -1)
TD=$P/tools/tcpdump/bin/tcpdump
f=$(mktemp)
$TD -i mon0 -n -w "$f" "wlan addr1 02:00:00:00:00:01" 2>/dev/null &
cap=$!
sleep 1.5
for r in 2 22 12 48 108; do
	for l in 40 150 500 1400; do
		perl $P/tools/inject.pl "$IF" $r $l $N $TAG
		sleep 0.5
	done
done
sleep 1
kill $cap; wait $cap 2>/dev/null
declare -A got
while read -r t r l n; do got["$r $l"]=$n; done < <($TD -r "$f" -n -xx 2>/dev/null | perl $P/tools/txq_count.pl | awk -v t=$TAG '$1 == t')
printf "%-8s" "rate\\len"; for l in 40 150 500 1400; do printf "%8s" $l; done; echo
for r in 2 22 12 48 108; do
	printf "%-8s" "$((r / 2))M"
	for l in 40 150 500 1400; do printf "%8s" "${got["$r $l"]:-0}/$N"; done
	echo
done
rm -f "$f"
