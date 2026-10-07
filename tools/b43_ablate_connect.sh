#!/usr/bin/env bash
# usage: ablate3.sh N "label params..." ...   judge = tools/b43_load_until_connected.sh with B43_TRIES=1
P=/home/gonsolo/bcm4360-acphy; S=$(dirname "$0"); N=$1; shift
for v in "$@"; do
	set -- $v; l=$1; shift; ok=0
	for i in $(seq 1 $N); do
		rmmod b43 2>/dev/null
		B43_TRIES=1 B43_LOAD="bash $S/b43_boot_dev.sh" timeout 200 bash $P/tools/b43_load_until_connected.sh ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 "$@" >$S/a3.tmp 2>&1; rc=$?
		echo "$l #$i rc=$rc $(tail -1 $S/a3.tmp | cut -c1-110)"
		[ $rc = 0 ] && ok=$((ok+1))
	done
	echo "== $l: $ok/$N"
done
