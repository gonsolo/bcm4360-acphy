#!/usr/bin/env bash
# Reset the BCM4360 over PCI between two b43 load tries (notes/164): after a long suspend the chip
# can come back with its clocks dead (bcma "HT force timeout" / "PLL enable timeout", b43 "Microcode
# not responding"), and reloading the module alone does not revive it. b43 must be unloaded first.
#   1. unbind bcma-pci-bridge, 2. PCI bus reset through the root port (the "reset" attribute),
#   3. if that fails: remove the device and rescan the bus. b43_boot.sh rebinds the device afterwards.
# usage: tools/b43_pci_reset.sh            (run as root; B43_PCI_DEV overrides the device)
set -u
DEV=${B43_PCI_DEV:-0000:03:00.0}
SYS=${B43_SYSFS:-/sys/bus/pci}
D=$SYS/devices/$DEV

if [ ! -e "$D" ]; then
	echo "b43_pci_reset: $DEV is gone, rescanning"
	echo 1 > "$SYS/rescan"; sleep 1
	[ -e "$D" ] && exit 0 || exit 1
fi
[ -e "$D/driver" ] && echo "$DEV" > "$D/driver/unbind"
if echo 1 > "$D/reset" 2>/dev/null; then
	echo "b43_pci_reset: $DEV reset"
else
	echo "b43_pci_reset: reset failed, remove and rescan"
	echo 1 > "$D/remove"; sleep 1
	echo 1 > "$SYS/rescan"; sleep 1
	[ -e "$D" ] || { echo "b43_pci_reset: $DEV did not come back"; exit 1; }
fi
sleep 1
