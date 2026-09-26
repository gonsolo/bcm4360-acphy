#!/usr/bin/env bash
# Reload b43 (wl state replayed on ch6), switch to managed, connect via NM.
# usage: sudo tools/connect_test.sh [extra module params]
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1
IW=$P/tools/iw/bin/iw
nmcli dev set $IF managed no 2>/dev/null
rmmod b43 2>/dev/null
CH=6 $P/b43_live.sh load ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 "$@" > /dev/null
$IW dev $IF set channel 1
ip link set $IF down
$IW dev $IF set type managed
nmcli dev set $IF managed yes
sleep 2
for i in 1 2; do nmcli dev wifi rescan ifname $IF 2>/dev/null; sleep 5; done
e0=$(dmesg | grep -c "PHY transmission error")
timeout 70 nmcli --wait 60 con up b43-test ifname $IF 2>&1 | tail -1
e1=$(dmesg | grep -c "PHY transmission error")
echo "PHY TX errors during connect: $((e1 - e0))"
nmcli -t -f DEVICE,STATE,CONNECTION device | grep $IF
ip -4 addr show $IF | grep inet
dmesg | grep "$IF:" | tail -3
