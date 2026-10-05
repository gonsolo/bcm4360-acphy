#!/usr/bin/env bash
# Drop the ConditionKernelVersion = "7.2.7" pins from the b43 services in /etc/nixos/configuration.nix (run with sudo).
# tools/b43_boot.sh now loads b43-src-builds/b43-$(uname -r).ko, so the services no longer need a fixed kernel.
# Build the module for a new kernel before booting it (notes/114). Uses "nixos-rebuild boot": takes effect on the
# next boot, does not restart b43 now.
#   sudo tools/unpin_b43_kernel.sh            edit + nixos-rebuild boot
#   sudo tools/unpin_b43_kernel.sh --remove   restore the backup + nixos-rebuild boot
# Test without touching the system:  CONF=/path/copy.nix REBUILD=true tools/unpin_b43_kernel.sh
set -eu
CONF=${CONF:-/etc/nixos/configuration.nix}
BAK=$CONF.bak-before-unpin
REBUILD=${REBUILD:-nixos-rebuild boot}
if [ "${1:-}" = --remove ]; then
	[ -f "$BAK" ] || { echo "no backup $BAK"; exit 1; }
	cp "$BAK" "$CONF"; echo "restored $CONF from backup"
else
	grep -q 'ConditionKernelVersion' "$CONF" || { echo "no ConditionKernelVersion in $CONF, nothing to do"; exit 0; }
	[ -f "$BAK" ] || cp "$CONF" "$BAK"
	sed -i '/ConditionKernelVersion *= *"[0-9.]*";/d' "$CONF"
	echo "removed ConditionKernelVersion lines from $CONF (backup: $BAK)"
fi
$REBUILD
