#!/usr/bin/env bash
# Snapshot the live b43 AC state into OUTDIR for diffing two runs:
# phy (all), radio (regs wl writes), mac (IHR), shm (shared, 0..0x2000),
# tables (entries wl writes). usage: sudo tools/state_snapshot.sh OUTDIR
P=/home/gonsolo/bcm4360-acphy
D=/sys/kernel/debug/b43ac
O=${1:?outdir}; mkdir -p "$O"
cat $D/phydump > "$O/phy.txt"
$P/tools/radiodump.sh > "$O/radio.txt"
cat $D/macdump > "$O/mac.txt"
for ((o = 0; o < 0x2000; o += 2)); do
	printf "%x\n" $o > $D/shm; cat $D/shm
done > "$O/shm.txt"
cat $P/traces/decoded-firstload*/tables.txt | awk '{print $1, $2, $3}' | sort -u -n -k1,1 -k2,2 |
while read -r id off w; do
	echo "00d $(printf %x $id)" > $D/phy
	echo "00e $(printf %x $off)" > $D/phy
	echo 00f > $D/phy; lo=$(cut -d' ' -f2 < $D/phy)
	hi=""
	[ "$w" = 32 ] && { echo 010 > $D/phy; hi=$(cut -d' ' -f2 < $D/phy); }
	echo "$id $off $hi$lo"
done > "$O/tables.txt"
wc -l "$O"/*.txt
