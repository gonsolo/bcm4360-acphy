#!/usr/bin/env bash
# notes/105: per-init TX test on a FIXED channel, no scanning, no association: reload b43, park on the
# AP's channel, inject directed probe requests (tools/inject_probe.pl) and read the ucode counters
# (txallfrm/txackfrm/txphyerr) and the AP's responses. PHY/radio/MAC/SHM snapshots are taken while
# the PHY sits on that channel, so snapshots of good and bad inits are directly comparable.
# usage: sudo tools/init_txtest.sh <N> [outdir]    (env: CH=11 BSSID=8c:6a:8d:9e:2a:88 RATE=12 PROBES=20)
set -u
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1; IW=$P/tools/iw/bin/iw; TD=$P/tools/tcpdump/bin/tcpdump
DBG=/sys/kernel/debug/b43ac
BSSID=${BSSID:-8c:6a:8d:9e:2a:88}; CH=${CH:-11}; RATE=${RATE:-12}; NP=${PROBES:-20}
N=${1:?count}; OUT=${2:-$P/test-logs/init-txtest-$(date +%H%M%S)}
mkdir -p "$OUT"
S=$DBG/shm
rd() { echo $1 > $S; printf "%d" 0x$(cut -d" " -f2 $S); }
FREQ=$(( CH < 15 ? 2407 + 5 * CH : 5000 + 5 * CH ))
for i in $(seq 1 "$N"); do
	R="$OUT/run$i"; mkdir -p "$R"
	dmesg -c > /dev/null
	nmcli dev set $IF managed no 2>/dev/null
	rmmod b43 2>/dev/null
	CH=6 $P/b43_live.sh load ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 > /dev/null 2>&1
	sleep 1
	MAC=$(cat /sys/class/net/$IF/address)
	ip link set $IF down
	PHY=$(basename $(readlink -f /sys/class/net/$IF/phy80211))
	$IW dev b43mon info > /dev/null 2>&1 || $IW phy $PHY interface add b43mon type monitor flags control otherbss
	$IW dev $IF set type managed
	ip link set b43mon up
	ip link set $IF up
	sleep 1
	$IW dev $IF scan freq 2437 > /dev/null 2>&1
	$IW dev $IF offchannel $FREQ $(( NP * 100 + 6000 )) > /dev/null 2>&1 &
	sleep 1.5
	f=$(mktemp)
	$TD -i b43mon -e -n -w "$f" 2>/dev/null & cap=$!
	sleep 1
	a=$(rd e6); e=$(rd fe); t=$(rd e0)
	perl $P/tools/inject_probe.pl b43mon "$MAC" "$BSSID" Vodafone-2A84 "$RATE" "$NP"
	sleep 0.3
	cat $DBG/phydump > "$R/phy.txt" 2>/dev/null
	$P/tools/radiodump.sh > "$R/radio.txt" 2>/dev/null
	cat $DBG/macdump > "$R/mac.txt" 2>/dev/null
	$P/tools/full_snapshot > "$R/shm_ihr.txt" 2>/dev/null
	sleep 1; kill $cap; wait $cap 2>/dev/null
	resp=$($P/tools/python3/bin/python3 $P/tools/fc_retry.py "$f" resp | head -1 | sed -E 's/[^0-9]*([0-9]+) frames, ([0-9]+) retries.*/\1 \2/')
	echo "counters before: a=$a e=$e t=$t after: $(rd e6) $(rd fe) $(rd e0)" >> "$R/debug.txt"
	ack=$(( ($(rd e6) - a) & 0xffff )); perr=$(( ($(rd fe) - e) & 0xffff )); all=$(( ($(rd e0) - t) & 0xffff ))
	rm -f "$f"
	dm_perr=$(dmesg | grep -c "PHY transmission error"); dm_sf=$(dmesg | grep -c "MAC suspend failed")
	label=bad; { [ "$dm_perr" -eq 0 ] && [ "${resp%% *}" -ge 10 ]; } 2>/dev/null && label=good
	echo "resp=[$resp] txackfrm=$ack txphyerr=$perr txallfrm=$all dmesg_phytxerr=$dm_perr dmesg_suspendfail=$dm_sf $label" > "$R/outcome.txt"
	echo "run $i: resp=[$resp] ack=$ack phyerr=$perr all=$all dmesg_phytxerr=$dm_perr suspend_fail=$dm_sf -> $label"
	ip link set $IF down 2>/dev/null; sleep 1
done
echo "OUT=$OUT"
