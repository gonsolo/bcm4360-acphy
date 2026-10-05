#!/usr/bin/env bash
# Daily-use boot-time load of b43-src on the BCM4360 (run by the NixOS
# b43-ac-load.service). Unlike b43_live.sh this leaves the interface to
# NetworkManager: no monitor mode, no "managed no", no debug panic sysctls.
#
# Firmware must already be in the system firmware search path (NixOS
# hardware.firmware) - b43 requests it asynchronously after insmod returns,
# so any temporary firmware_class path override here would race it.
set -u
PROJ=/home/gonsolo/bcm4360-acphy
DEV=0000:03:00.0

modprobe -a mac80211 ssb cordic bcma || exit 1

if [ "$(basename "$(readlink -f /sys/bus/pci/devices/$DEV/driver)")" != bcma-pci-bridge ]; then
	echo bcma-pci-bridge > /sys/bus/pci/devices/$DEV/driver_override
	[ -e /sys/bus/pci/devices/$DEV/driver ] && \
		echo "$DEV" > /sys/bus/pci/devices/$DEV/driver/unbind
	echo "$DEV" > /sys/bus/pci/drivers_probe
fi

# Wait for the bcma bus to expose the 802.11 core before loading b43.
for _ in $(seq 50); do
	[ -e /sys/bus/bcma/devices/bcma0:1 ] && break
	sleep 0.1
done
[ -e /sys/bus/bcma/devices/bcma0:1 ] || { echo "bcma0:1 never appeared"; exit 1; }

# One module per kernel (vermagic). Prefer the Nix-built one (boot.extraModulePackages installs it
# under extra/, notes/115), else the hand build b43-src-builds/b43-<uname -r>.ko, else the in-tree
# build output (built for the kernel it was last made against).
KO=/run/booted-system/kernel-modules/lib/modules/$(uname -r)/extra/b43.ko   # modinfo -n would pick the in-tree module
if [ ! -e "$KO" ]; then
	KO="$PROJ/b43-src-builds/b43-$(uname -r).ko"
	[ -e "$KO" ] || KO="$PROJ/b43-src/b43.ko"
fi
echo "b43_boot: loading $KO"
insmod "$KO" "$@" || exit 1

# Firmware loads asynchronously; the netdev only registers once it has.
for _ in $(seq 100); do
	for i in /sys/class/net/*; do
		if readlink "$i/device/driver" 2>/dev/null | grep -q b43; then
			echo "b43 interface: $(basename "$i")"
			exit 0
		fi
	done
	sleep 0.1
done
echo "b43 loaded but no interface after 10s (firmware?)"
exit 1
