#!/usr/bin/env bash
# Per-second ucode RX counter rates via /sys/kernel/debug/b43ac/shm.
# usage: sudo tools/rxrate.sh [seconds]
S=${1:-5}
D=/sys/kernel/debug/b43ac/shm
rd() { echo "$1" > $D; printf "%d" 0x$(cut -d' ' -f2 < $D); }
snap() { for o in 10a 10c 10e 110 132 13e 11e; do rd $o; echo -n " "; done; }
a=($(snap)); sleep "$S"; b=($(snap))
n=(badfcs badplcp crsglitch rxstrt beaconobss? dfrmmcast? ucast?)
out=""
for i in 0 1 2 3; do out+="${n[$i]}=$(( ((b[i] - a[i]) & 0xffff) / S ))/s "; done
echo "$out"
