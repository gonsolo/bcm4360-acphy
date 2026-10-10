#!/usr/bin/env bash
# rx80.sh LABEL [module params] : b43 in monitor mode on 5560 MHz; while the stick downloads over 5 GHz, count what b43 decodes
P=/home/gonsolo/bcm4360-acphy; S=$(dirname "$0"); IF=wlp3s0b1; IW="$P/tools/iw/bin/iw"; L=$1; shift
sysctl -q net.core.message_cost=0; sync; nmcli dev set $IF managed no 2>/dev/null; rmmod b43 2>/dev/null
bash $S/b43_boot_dev.sh ac_replay=0 dma32=1 ac_por=7 nohwcrypt=1 ac_selfheal=0 ac_5ghz=1 ac_diag=1 "$@" >/dev/null 2>&1
timeout 30 bash -c "until [ -e /sys/class/net/$IF ]; do sleep 1; done"
nmcli dev set $IF managed no 2>/dev/null; sleep 1; ip link set $IF down; sleep 1; $IW dev $IF set type monitor; ip link set $IF up; $IW dev $IF set freq 5560; sleep 2; sync
dmesg -C; timeout 36 tcpdump -i $IF -nn -e -c 200000 2>/dev/null > $S/rx80.cap &
sleep 1; d=$(iperf3 -c 192.168.0.236 -t 33 -R -f m 2>/dev/null | awk '/receiver/{print $7}'); wait
tot=$(wc -l < $S/rx80.cap); bc=$(grep -c Beacon $S/rx80.cap); st=$(grep -c -i "00:c0:ca:b0:22:a0" $S/rx80.cap)
echo "$L: stick download $d Mbit/s; b43 decoded $tot frames, $bc beacons, $st to/from the stick"
grep -i "00:c0:ca:b0:22:a0" $S/rx80.cap | grep -o -E "[0-9.]+ Mb/s|MCS [0-9]+|[0-9]+ MHz [a-z0-9/]+" | sort | uniq -c | sort -rn | head -6 | tr '\n' ';'; echo
dmesg | grep macstat > $S/rx80.ms; perl $P/tools/macstat_decode.pl $S/rx80.ms 2>/dev/null | awk 'NR>2 && $NF!=0 && /^rx/{printf "%s=%s ", $1, $NF} END{print ""}'
