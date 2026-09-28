#!/usr/bin/env bash
# Live b43 iteration while the USB stick (wlp0s20u1) carries the network.
#   sudo ./b43_live.sh swap            one-time: wl -> bcma (wl can't come back without reboot)
#   sudo ./b43_live.sh load [params]   insmod b43.ko, park in monitor mode on ch6
#   sudo ./b43_live.sh unload          rmmod b43
#   sudo ./b43_live.sh stats [secs]    counters + macstat delta over secs (default 20)
set -u
PROJ=/home/gonsolo/bcm4360-acphy
DEV=0000:03:00.0
IW=$PROJ/tools/iw/bin/iw
CH=${CH:-6}

b43_if() {
	for i in /sys/class/net/*; do
		readlink "$i/device/driver" 2>/dev/null | grep -q b43 && basename "$i"
	done | head -1
}

case "${1:-}" in
swap)
	sysctl -qw kernel.panic_on_oops=1 kernel.panic=10 \
		kernel.hung_task_panic=1 kernel.hung_task_timeout_secs=30 \
		kernel.softlockup_panic=1
	echo "$PROJ/firmware" > /sys/module/firmware_class/parameters/path
	modprobe -a mac80211 ssb cordic bcma
	nmcli dev set wlp3s0 managed no 2>/dev/null
	echo bcma-pci-bridge > /sys/bus/pci/devices/$DEV/driver_override
	echo "$DEV" > /sys/bus/pci/drivers/wl/unbind
	echo "$DEV" > /sys/bus/pci/drivers_probe
	readlink -f /sys/bus/pci/devices/$DEV/driver
	;;
load)
	shift
	echo "b43live: === LOAD $* ===" > /dev/kmsg
	insmod "$PROJ/b43-src/b43.ko" verbose=3 "$@" || exit 1
	# firmware_class/parameters/path (set in `swap`) only needs to be
	# pointed at $PROJ/firmware for b43's own request_firmware() calls
	# during the insmod above (synchronous). Reset it now - left pointed
	# there, any other device's driver that loads firmware later (e.g.
	# the USB backup stick on hot-replug) fails to find its firmware in
	# the normal system path and silently fails to probe.
	echo "" > /sys/module/firmware_class/parameters/path
	sleep 3
	IF=$(b43_if)
	echo "interface: $IF"
	nmcli dev set "$IF" managed no
	ip link set "$IF" down
	$IW dev "$IF" set type monitor
	$IW dev "$IF" set monitor otherbss control fcsfail 2>/dev/null || $IW dev "$IF" set monitor otherbss control
	ip link set "$IF" up
	$IW dev "$IF" set channel "$CH"
	$IW dev "$IF" info | grep -E "type|channel"
	;;
unload)
	echo "b43live: === UNLOAD ===" > /dev/kmsg
	rmmod b43
	;;
stats)
	IF=$(b43_if)
	S=${2:-20}
	r0=$(cat /sys/class/net/$IF/statistics/rx_packets)
	i0=$(awk '/b43/ {s=0; for (i=2;i<=5;i++) s+=$i; print s}' /proc/interrupts)
	echo "b43live: === STATS START ===" > /dev/kmsg
	sleep "$S"
	echo "b43live: === STATS END ===" > /dev/kmsg
	r1=$(cat /sys/class/net/$IF/statistics/rx_packets)
	i1=$(awk '/b43/ {s=0; for (i=2;i<=5;i++) s+=$i; print s}' /proc/interrupts)
	echo "$IF over ${S}s: rx_packets +$((r1 - r0)), irqs +$((i1 - i0))"
	;;
*)
	sed -n 2,7p "$0"
	exit 1
	;;
esac
