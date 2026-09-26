#!/usr/bin/env bash
# 5 GHz variant of ack_setup.sh: wl's 5 GHz state in 80 MHz mode on the
# router's primary channel 112, managed wlp3s0b1 plus monitor vif b43mon.
P=/home/gonsolo/bcm4360-acphy
IF=wlp3s0b1; IW=$P/tools/iw/bin/iw
[ -e /run/udev/rules.d/99-zz-no-wpa-restart.rules ] || { echo "udev override missing - aborting"; exit 1; }
ip link set b43mon down 2>/dev/null; $IW dev b43mon del 2>/dev/null
rmmod b43 2>/dev/null
CH=112 $P/b43_live.sh load ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 ac_5ghz=2 ac_5g_80=1 "$@" > /dev/null || exit 1
ip link set $IF down
$IW dev $IF set type managed
ip link set $IF up
PHY=$(basename $(readlink -f /sys/class/net/$IF/phy80211))
$IW phy $PHY interface add b43mon type monitor flags control otherbss
ip link set b43mon up
$IW dev $IF scan freq 5560 > /dev/null 2>&1
sleep 2
ping -c2 -W2 192.168.0.1 > /dev/null && echo "setup ok, network ok" || echo "setup done, NETWORK FAILING"
