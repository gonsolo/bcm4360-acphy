#!/usr/bin/env bash
# Compare live b43 PHY/radio registers with wl's final ch6 values.
# usage: sudo tools/ac_diff.sh phy|radio
set -u
W=${1:-phy}
F=/home/gonsolo/bcm4360-acphy/traces/wl-final-$W-2g-ch6.txt
D=/sys/kernel/debug/b43ac/$W
n=0; d=0
while read -r a v; do
	[[ $a =~ ^[0-9a-fA-F]+$ ]] || continue
	echo "$a" > "$D" || exit 1
	cur=$(cut -d" " -f2 < "$D")
	n=$((n + 1))
	if [ "$((16#$cur))" -ne "$((16#$v))" ]; then
		d=$((d + 1))
		printf "%s %s wl=%04x b43=%s\n" "$W" "$a" "$((16#$v))" "$cur"
	fi
done < "$F"
echo "$W: $d of $n differ"
