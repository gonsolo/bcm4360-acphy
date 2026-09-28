#!/usr/bin/env bash
# One-shot post-reboot test for the kernel 7.2.7 port (see notes/54).
# Run this AFTER rebooting into the "b43dev (Linux 7.2.7)" boot entry.
set -eu
echo "=== kernel check ==="
uname -r
if [ "$(uname -r)" != "7.2.7" ]; then
	echo "Not running 7.2.7 (currently $(uname -r)) - wrong boot entry?" >&2
	exit 1
fi

echo "=== backup link check ==="
ping -c1 -W2 -I wlp0s20u1 192.168.0.1 >/dev/null && echo "backup OK" || {
	echo "USB backup stick not connected/working - fix this before continuing" >&2
	exit 1
}

echo "=== panic sysctls ==="
sysctl -qw kernel.panic_on_oops=1 kernel.panic=10 \
	kernel.hung_task_panic=1 kernel.hung_task_timeout_secs=30 \
	kernel.softlockup_panic=1

echo "=== postboot ==="
bash /home/gonsolo/bcm4360-acphy/tools/postboot.sh

echo "=== swap (wl -> bcma) ==="
/home/gonsolo/bcm4360-acphy/b43_live.sh swap

echo "=== load b43 (staged 7.2.7 build) ==="
/home/gonsolo/bcm4360-acphy/b43_live.sh load ac_replay=1 dma32=1 ac_por=63 nohwcrypt=1

sleep 2
echo "=== module + dmesg check ==="
lsmod | grep "^b43 " || { echo "b43 not loaded" >&2; exit 1; }
dmesg | tail -20

echo "=== done - bring up managed mode and try a connection manually ==="
echo "nmcli device set wlp3s0b1 managed yes"
echo "nmcli device wifi rescan ifname wlp3s0b1 && sleep 5"
echo "nmcli connection up b43-test"
