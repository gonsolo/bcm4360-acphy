#!/usr/bin/env bash
# Router beacon reception over N seconds on the b43 monitor interface.
# Router sends 10 beacons/s; prints good/bad beacon counts and all-frame totals.
S=${1:-10}
T=/home/gonsolo/bcm4360-acphy/tools/tcpdump/bin/tcpdump
IF=$(for i in /sys/class/net/*; do readlink $i/device/driver 2>/dev/null | grep -q b43 && basename $i; done | head -1)
out=$(timeout "$S" $T -i "$IF" -e -n 2>/dev/null)
bg=$(grep 'Beacon (Vodafone-2A84)' <<<"$out" | grep -vc bad-fcs)
bb=$(grep 'Beacon (Vodafone-2A84)' <<<"$out" | grep -c bad-fcs)
all=$(grep -c . <<<"$out"); bad=$(grep -c bad-fcs <<<"$out")
echo "router beacons good=$bg bad=$bb (of $((S * 10)))  frames=$all bad-fcs=$bad"
