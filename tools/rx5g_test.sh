#!/usr/bin/env bash
# 5 GHz receive check: load b43 with the given extra params, monitor mode, count rx frames per channel.
# usage: sudo tools/rx5g_test.sh [freq ...] -- [module params]   (default freqs: 2462 5580)
# Restores the normal setup (wrapper service) afterwards.
IW=/home/gonsolo/bcm4360-acphy/tools/iw/sbin/iw; IF=wlp3s0b1
F=(); while [ $# -gt 0 ] && [ "$1" != -- ]; do F+=("$1"); shift; done; shift
[ ${#F[@]} = 0 ] && F=(2462 5580)
nmcli device set $IF managed no 2>/dev/null
rmmod b43 2>/dev/null
/home/gonsolo/bcm4360-acphy/tools/b43_boot.sh ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 "$@" >/dev/null 2>&1
for _ in $(seq 40); do [ -e /sys/class/net/$IF ] && break; sleep 1; done
sleep 3; nmcli device set $IF managed no 2>/dev/null; ip link set $IF down; $IW dev $IF set type monitor; ip link set $IF up
for f in "${F[@]}"; do
	$IW dev $IF set freq $f 2>&1 | head -1; sleep 1
	a=$(cat /sys/class/net/$IF/statistics/rx_packets); sleep 8; b=$(cat /sys/class/net/$IF/statistics/rx_packets)
	echo "freq $f: rx frames in 8 s = $((b-a))"
done
dmesg | grep -i "replayed wl\|phy_ac: .*error\|BUG\|Oops" | tail -3
ip link set $IF down; $IW dev $IF set type managed; nmcli device set $IF managed yes
systemctl restart b43-ac-load.service
