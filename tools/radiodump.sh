#!/usr/bin/env bash
# Read the radio registers wl writes (union of the decoded first-load traces)
# through debugfs. usage: sudo tools/radiodump.sh > out.txt
P=/home/gonsolo/bcm4360-acphy
D=/sys/kernel/debug/b43ac/radio
for a in $(cut -d' ' -f1 $P/traces/decoded-firstload*/radio.txt | sort -u); do
	echo "$a" > $D && cat $D
done
