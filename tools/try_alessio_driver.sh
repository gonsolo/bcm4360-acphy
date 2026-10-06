#!/usr/bin/env bash
# Run as root. Swap our b43 for Alessio's bcma+b43 (build with tools/build_alessio_driver.sh),
# observe the init, leave it loaded. Does NOT touch the stick (wlp0s20u1).
#   sudo tools/try_alessio_driver.sh         load his bcma + b43, log to /tmp/ale-load.log
#   sudo tools/try_alessio_driver.sh restore back to our b43 via the normal service
set -u
PROJ=/home/gonsolo/bcm4360-acphy
DEV=0000:03:00.0
V=$(uname -r)
unload() {
	rmmod b43 2>/dev/null
	[ -e /sys/bus/pci/devices/$DEV/driver ] && echo $DEV > /sys/bus/pci/devices/$DEV/driver/unbind
	rmmod bcma 2>/dev/null
}
if [ "${1:-}" = restore ]; then
	unload
	modprobe bcma
	systemctl restart b43-ac-load.service
	exit
fi
modprobe -a mac80211 ssb cordic || exit 1
unload
insmod $PROJ/b43-src-builds/ale-bcma-$V.ko || exit 1
echo bcma-pci-bridge > /sys/bus/pci/devices/$DEV/driver_override
echo $DEV > /sys/bus/pci/drivers_probe
for _ in $(seq 50); do [ -e /sys/bus/bcma/devices/bcma0:1 ] && break; sleep 0.1; done
[ -e /sys/bus/bcma/devices/bcma0:1 ] || { echo "bcma0:1 never appeared"; exit 1; }
sync
T0=$(date +%s)
insmod $PROJ/b43-src-builds/ale-b43-$V.ko || exit 1
timeout 20 bash -c 'until ls /sys/class/net | grep -q . && readlink /sys/class/net/*/device/driver 2>/dev/null | grep -q b43; do sleep 0.5; done'
sleep 3
journalctl -k --since "@$T0" --no-pager > /tmp/ale-load.log; sync
echo "log: /tmp/ale-load.log ($(wc -l < /tmp/ale-load.log) lines)"
grep -aiE "b43|phy_ac|AC-PHY" /tmp/ale-load.log | head -40
# a failed init gets retried by the stack and the machine hung once (2026-10-06): unload on failure
if ! grep -aq "Hardware init done\|Wireless interface started\|Broadcom 43xx.*started" /tmp/ale-load.log && grep -aq "ERROR" /tmp/ale-load.log; then
	echo "init failed, unloading b43"; rmmod b43
fi
