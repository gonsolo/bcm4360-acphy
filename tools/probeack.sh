#!/usr/bin/env bash
# Firmware ACK test without association: b43mon (monitor) alone sets the
# channel, then wlp3s0b1 comes up idle in managed mode so our MAC is in the
# address match table; directed probe requests from that MAC make the AP send
# unicast probe responses. Count responses and how many were retries.
# usage: sudo tools/probeack.sh [count]   (env: BSSID, CH, RATE in 500 kb/s)
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1; IW=$P/tools/iw/bin/iw; TD=$P/tools/tcpdump/bin/tcpdump
BSSID=${BSSID:-8c:6a:8d:9e:2a:90}; CH=${CH:-112}; RATE=${RATE:-12}; N=${1:-20}
MAC=$(cat /sys/class/net/$IF/address)
S=/sys/kernel/debug/b43ac/shm
rd() { echo $1 > $S; printf "%d" 0x$(cut -d" " -f2 $S); }
ip link set $IF down
PHY=$(basename $(readlink -f /sys/class/net/$IF/phy80211))
$IW dev b43mon info > /dev/null 2>&1 || $IW phy $PHY interface add b43mon type monitor flags control otherbss
$IW dev $IF set type managed
ip link set b43mon up
ip link set $IF up
sleep 1
# Channel 6 applies the replayed wl 2.4 GHz state (still needed first).
$IW dev $IF scan freq 2437 > /dev/null 2>&1
# An idle station sits on the default channel; hold ours with remain-on-channel.
FREQ=$(( CH < 15 ? 2407 + 5 * CH : 5000 + 5 * CH ))
$IW dev $IF offchannel $FREQ $(( N * 100 + 3000 )) > /dev/null 2>&1 &
sleep 1.5
f=$(mktemp)
$TD -i b43mon -e -n -w "$f" 2>/dev/null & cap=$!
sleep 1
a=$(rd e6); e=$(rd fe); t=$(rd e0)
perl $P/tools/inject_probe.pl b43mon "$MAC" "$BSSID" Vodafone-2A84 "$RATE" "$N"
sleep 1; kill $cap; wait $cap 2>/dev/null
# tcpdump's summary line never prints "Retry" for management frames; read the
# real frame-control retry bit (0x0800) instead.
$P/tools/python3/bin/python3 $P/tools/fc_retry.py "$f" resp | sed 's/^/probe /'
echo "ucode txackfrm +$(( ($(rd e6) - a) & 0xffff )) txphyerr +$(( ($(rd fe) - e) & 0xffff )) txallfrm +$(( ($(rd e0) - t) & 0xffff ))"
rm -f "$f"
