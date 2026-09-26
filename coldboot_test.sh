#!/usr/bin/env bash
# One-shot cold-boot test: is b43 the very first driver to ever touch this
# chip's hardware this power-on (unlike every earlier test today, where wl
# always initialized the chip first). wl and stock b43 are kernel-blacklisted
# in this boot's NixOS generation; only our custom out-of-tree b43.ko can
# bind, via normal bus auto-probe (no unbind/rebind tricks needed here).
#
# SAFETY: the very first action, before anything touches the WiFi hardware,
# is switching the bootloader default back to the known-good generation, so
# any outcome - success, a crash caught by the panic-on-oops net below, or
# even a true hang needing a manual power-cycle - lands on a working wl
# config on the next boot. No manual steps required.

PROJ=/home/gonsolo/bcm4360-acphy
GOOD_GEN=/nix/store/9rhwm6526aq8nlilicalmjgsbvvvgv81-nixos-system-zitrone-26.05.10529.c508844df6c2
DEV=0000:03:00.0
mkdir -p "$PROJ/test-logs"
LOG="$PROJ/test-logs/coldboot-$(date +%Y%m%d-%H%M%S).log"
exec >"$LOG" 2>&1
set -x

date -u

# ==== SAFETY FIRST: revert the boot default before touching hardware. ====
"$GOOD_GEN/bin/switch-to-configuration" boot
sync

sleep 10

sysctl -w kernel.panic_on_oops=1 kernel.panic=10 \
	kernel.hung_task_panic=1 kernel.hung_task_timeout_secs=30 \
	kernel.softlockup_panic=1
sync

echo "$PROJ/firmware" > /sys/module/firmware_class/parameters/path
modprobe mac80211
modprobe ssb
modprobe cordic
modprobe bcma
sync

echo "===== interrupts before ====="
grep -iE "bcma|b43|wl|03:00" /proc/interrupts
echo "===== driver bound to device before insmod ====="
readlink -f /sys/bus/pci/devices/$DEV/driver 2>&1

echo "coldboot: === INSMOD ===" > /dev/kmsg
insmod "$PROJ/b43-src/b43.ko" verbose=3
sync

sleep 90

echo "===== ip link ====="
ip link
echo "===== interrupts after ====="
grep -iE "bcma|b43|wl|03:00" /proc/interrupts
echo "===== nmcli device ====="
nmcli -t -f DEVICE,TYPE,STATE,CONNECTION device
echo "===== netdev counters ====="
for ifc in $(ls /sys/class/net); do
	if readlink "/sys/class/net/$ifc/device/driver" 2>/dev/null | grep -q b43; then
		echo "$ifc rx_packets=$(cat /sys/class/net/$ifc/statistics/rx_packets)" \
			"tx_packets=$(cat /sys/class/net/$ifc/statistics/tx_packets)"
		echo "===== scan results ($ifc) ====="
		nmcli -f SSID,BSSID,CHAN,SIGNAL dev wifi list ifname "$ifc" --rescan yes 2>&1
	fi
done
echo "===== dmesg since INSMOD ====="
dmesg | sed -n '/coldboot: === INSMOD ===/,$p'
journalctl --sync
sync

echo "coldboot: === DONE, rebooting to reverted default ===" > /dev/kmsg
journalctl --sync
sync
systemctl reboot
