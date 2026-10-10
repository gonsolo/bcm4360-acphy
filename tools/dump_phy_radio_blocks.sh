#!/usr/bin/env bash
# d5.sh OUTDIR : with b43 already in monitor mode on 5560 MHz, dump PHY and radio in small blocks.
# Progress is synced to OUTDIR/progress before each block, so a hang names its block.
O=$1; D=/sys/kernel/debug/b43ac; mkdir -p $O; : > $O/phy.txt; : > $O/radio.txt
for ((b=0; b<0xc00; b+=0x80)); do
	printf 'phy %03x\n' $b >> $O/progress; sync
	printf '%x %x\n' $b $((b+0x7f)) > $D/phydump; cat $D/phydump >> $O/phy.txt; sync
done
printf '0 1fff\n' > $D/phydump
for ((b=0; b<0xa00; b+=0x40)); do
	printf 'radio %03x\n' $b >> $O/progress; sync
	for ((a=b; a<b+0x40; a++)); do printf '%x\n' $a > $D/radio; cat $D/radio >> $O/radio.txt; done; sync
done
echo done >> $O/progress; sync
