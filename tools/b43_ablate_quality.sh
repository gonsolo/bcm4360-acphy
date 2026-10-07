#!/usr/bin/env bash
# quality ablation: load via loader (1 try), settle 25 s, 20 pings + 10 MB download via b43
P=/home/gonsolo/bcm4360-acphy; S=$(dirname "$0")
sysctl -q net.ipv4.conf.wlp3s0b1.rp_filter=0
for v in "$@"; do
	set -- $v; l=$1; shift
	rmmod b43 2>/dev/null
	B43_TRIES=1 B43_LOAD="bash $S/b43_boot_dev.sh" timeout 200 bash $P/tools/b43_load_until_connected.sh ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 "$@" >$S/a4.tmp 2>&1
	v1=$(tail -1 $S/a4.tmp | sed 's/.*: //' | cut -c1-40)
	sleep 25
	loss=$(ping -I wlp3s0b1 -c 20 -W 2 -i 0.3 192.168.0.1 2>/dev/null | grep -o "[0-9.]*% packet loss")
	sp=$(curl -s --interface wlp3s0b1 -o /dev/null -w "%{speed_download}" -m 20 http://speedtest.tele2.net/10MB.zip)
	echo "$l: [$v1] loss=${loss:-?} speed=$((${sp%.*}/1000)) kB/s"
done
