#!/usr/bin/env bash
# One active scan on ch6; report TX errors, TX status records, tx_packets delta.
IF=$(for i in /sys/class/net/*; do readlink $i/device/driver 2>/dev/null | grep -q b43 && basename $i; done | head -1)
IW=/home/gonsolo/bcm4360-acphy/tools/iw/bin/iw
echo "b43txtest: mark" > /dev/kmsg
t0=$(cat /sys/class/net/$IF/statistics/tx_packets)
$IW dev "$IF" scan freq 2437 > /dev/null 2>&1
sleep 1
t1=$(cat /sys/class/net/$IF/statistics/tx_packets)
log=$(dmesg | sed -n '/b43txtest: mark/,$p')
echo "txerr=$(grep -c 'transmission error' <<<"$log") txstatus=$(grep -c 'AC txstatus' <<<"$log") tx_packets+=$((t1 - t0))"
grep 'AC txstatus' <<<"$log" | tail -2
