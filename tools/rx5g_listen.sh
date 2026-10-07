#!/usr/bin/env bash
# usage: rx5.sh "<freqs>" [module params]  -- listen-only 5 GHz RX test, monitor mode
P=/home/gonsolo/bcm4360-acphy; S=$(dirname "$0"); IF=wlp3s0b1; IW="$P/tools/iw/bin/iw"
FR=$1; shift
sysctl -q net.core.message_cost=0; sync
nmcli dev set $IF managed no 2>/dev/null; rmmod b43 2>/dev/null; dmesg -c >/dev/null
bash $S/b43_boot_dev.sh ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1 "$@" 2>&1 | tail -1
timeout 30 bash -c "until [ -e /sys/class/net/$IF ]; do sleep 1; done"
nmcli dev set $IF managed no 2>/dev/null; sleep 1; ip link set $IF down; sleep 1; $IW dev $IF set type monitor; ip link set $IF up; $IW dev $IF set channel 6; sleep 2
cap(){ nix-shell -p tcpdump --run "timeout ${1:-6} tcpdump -i $IF -nn -c 300 2>&1" | grep -o "[0-9]* packets captured"; }
$IW dev $IF set freq 2462; sleep 1; echo "2462: $(cap 5)"
for f in $FR; do dmesg -c >/dev/null; $IW dev $IF set freq $f; sleep 2; echo "$f: $(cap 8)"; dmesg | grep -E "80 MHz|ERROR|BUG|Oops" | cut -c1-120 | head -3; done
