#!/usr/bin/env bash
# Self-contained b43 live test. Run as root via systemd-run so it survives
# loss of network / the Claude session. Swaps wl -> b43, captures logs,
# then reboots (wl comes back on the next boot).
#
# Launch with:
#   sudo systemd-run --unit=b43test --collect --no-block \
#     --setenv=PATH="$PATH" /run/current-system/sw/bin/bash run_test.sh
#
# Safety net (runtime only, reset on reboot): any oops or hung task panics
# the kernel, which saves the log to EFI pstore / journal and auto-reboots
# after 10s instead of freezing.

PROJ=/home/gonsolo/bcm4360-acphy
DEV=0000:03:00.0
mkdir -p "$PROJ/test-logs"
LOG="$PROJ/test-logs/run-$(date +%Y%m%d-%H%M%S).log"
exec >"$LOG" 2>&1
set -x

# Give the Claude session time to send its reply before WiFi drops.
sleep 5

sysctl -w kernel.panic_on_oops=1 kernel.panic=10 \
	kernel.hung_task_panic=1 kernel.hung_task_timeout_secs=30 \
	kernel.softlockup_panic=1

echo "$PROJ/firmware" > /sys/module/firmware_class/parameters/path
modprobe mac80211
modprobe ssb
modprobe cordic
modprobe bcma
sync

echo "===== interrupts before ====="
grep -iE "bcma|b43|wl|03:00" /proc/interrupts

echo "b43test: === TEST START ===" > /dev/kmsg
echo bcma-pci-bridge > /sys/bus/pci/devices/$DEV/driver_override
echo "$DEV" > /sys/bus/pci/drivers/wl/unbind
insmod "$PROJ/b43-src/b43.ko" verbose=3 ac_replay=1
echo "$DEV" > /sys/bus/pci/drivers_probe
sync

sleep 20

echo "===== ip link ====="
ip link
echo "===== interrupts after ====="
grep -iE "bcma|b43|wl|03:00" /proc/interrupts
echo "===== netdev counters ====="
for ifc in $(ls /sys/class/net); do
	if readlink "/sys/class/net/$ifc/device/driver" | grep -q b43; then
		echo "$ifc rx_packets=$(cat /sys/class/net/$ifc/statistics/rx_packets)" \
			"tx_packets=$(cat /sys/class/net/$ifc/statistics/tx_packets)"
		echo "===== scan results ($ifc) ====="
		nmcli -f SSID,BSSID,CHAN,SIGNAL dev wifi list ifname "$ifc" --rescan yes 2>&1
	fi
done
echo "===== dmesg since test start ====="
dmesg | sed -n '/b43test: === TEST START ===/,$p'
journalctl --sync
sync

# Recovery is a clean reboot. Once b43 has initialized the chip, wl's probe
# fails (garbage error code) and a second probe attempt corrupts kernel
# memory (list_del corruption inside wl.ko) - so never rebind wl here.
echo "b43test: === DONE, rebooting ===" > /dev/kmsg
echo "===== DONE, rebooting ====="
journalctl --sync
sync
systemctl reboot
