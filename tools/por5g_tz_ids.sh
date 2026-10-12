#!/usr/bin/env bash
# por5g_tz_ids.sh : zero one table id (contiguous range of wl's 5 GHz table replay) at a time and
# report whether the 80 MHz link still works (notes/153). Run as root, router on 5 GHz 80 MHz.
P=/home/gonsolo/bcm4360-acphy
ranges="1:0:128 2:128:166 3:166:422 4:422:678 5:678:700 7:700:911 10:911:1007 11:1007:1020 12:1020:1083 14:1083:1243 16:1243:1486 33:1486:1510 64:1510:1638 65:1638:1766 66:1766:1894 68:1894:1919 69:1919:1942 71:1942:2006 72:2006:2070 96:2070:2198 97:2198:2326 98:2326:2454 100:2454:2479 101:2479:2502 103:2502:2566 104:2566:2630 128:2630:2758 129:2758:2886 130:2886:3014 135:3014:3078 136:3078:3142"
for r in 0:0:0 $ranges; do
	IFS=: read id a b <<< "$r"
	out=$(RESET=1 bash $P/tools/por5g_chain.sh "163,0,3142,0,$a,$b" 2>&1 | grep "^step" | tail -1)
	down=$(sed -n 's/.*down \([0-9]*\)\..*/\1/p' <<< "$out")
	if grep -q Connected <<< "$out" && [ "${down:-0}" -ge 40 ]; then v=works; else v=BREAKS; fi
	echo "table id $id [$a,$b): $v  ${out:0:160}"
done
echo "done"
