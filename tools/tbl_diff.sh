#!/usr/bin/env bash
# Read back PHY table entries and compare with wl's final ch6 values.
# usage: sudo tools/tbl_diff.sh   (needs /sys/kernel/debug/b43ac/phy)
P=/sys/kernel/debug/b43ac/phy
F=/home/gonsolo/bcm4360-acphy/traces/wl-final-tables-2g-ch6.txt
n=0; d=0
while read -r id off w val; do
	echo "00d $(printf %x $id)" > $P
	echo "00e $(printf %x $off)" > $P
	echo 00f > $P
	lo=$(cut -d' ' -f2 < $P)
	cur=$((16#$lo))
	if [ "$w" = 32 ]; then
		echo 010 > $P
		hi=$(cut -d' ' -f2 < $P)
		cur=$(( (16#$hi << 16) | 16#$lo ))
	fi
	n=$((n + 1))
	if [ "$cur" -ne "$((16#$val))" ]; then
		d=$((d + 1))
		printf "tbl %d off %d w%s wl=%x b43=%x\n" "$id" "$off" "$w" "$((16#$val))" "$cur"
	fi
done < "$F"
echo "tables: $d of $n differ"
