#!/usr/bin/env bash
# Does the AP hear our TX? Inject unicast frames to the AP on the b43
# interface and count ucode transmissions per frame (1 = AP ACKed and we
# received the ACK, 7 = retry limit) for each PhyTxControlWord_1 sub-band.
# usage: sudo tools/txsb_sweep.sh [count] [sub-bands...]   (env: BSSID, RATE)
P=/home/gonsolo/bcm4360-acphy
IF=$(for i in /sys/class/net/*; do readlink $i/device/driver 2>/dev/null | grep -q b43 && basename $i; done | head -1)
BSSID=${BSSID:-8c:6a:8d:9e:2a:90}; RATE=${RATE:-12}; N=${1:-20}; shift
S=/sys/kernel/debug/b43ac/shm
rd() { echo $1 > $S; printf "%d" 0x$(cut -d" " -f2 $S); }
for sb in ${@:--1}; do
	echo $sb > /sys/module/b43/parameters/ac_txsb
	t=$(rd e0); e=$(rd fe)
	perl $P/tools/inject_to.pl "$IF" "$BSSID" "$RATE" "$N"
	sleep 0.5
	dt=$(( ($(rd e0) - t) & 0xffff ))
	printf "sb %2s: txallfrm %4d for %d frames (%s/frame) txphyerr +%d\n" "$sb" "$dt" "$N" \
		"$(awk "BEGIN{printf \"%.1f\", $dt/$N}")" $(( ($(rd fe) - e) & 0xffff ))
done
echo -1 > /sys/module/b43/parameters/ac_txsb
