#!/usr/bin/env bash
# Build b43-ac as a Nix kernel module for the running boot.kernelPackages (run with sudo), so kernel upgrades
# rebuild it automatically (notes/115). Adds boot.extraModulePackages to /etc/nixos/configuration.nix, then
# `nixos-rebuild boot` (takes effect on the next boot; does not restart b43 now).
#   sudo tools/install_b43_module.sh            install
#   sudo tools/install_b43_module.sh --remove   restore the backup
# Test without touching the system:  CONF=/path/copy.nix REBUILD=true tools/install_b43_module.sh
set -eu
CONF=${CONF:-/etc/nixos/configuration.nix}
BAK=$CONF.bak-before-b43-module
REBUILD=${REBUILD:-nixos-rebuild boot}
ANCHOR='  boot.kernelPackages = '
IFS= read -r -d '' BLOCK <<'NIX' || true
  # notes/115: out-of-tree b43 (AC-PHY port), rebuilt for every kernel in boot.kernelPackages.
  # (tools/install_b43_module.sh --remove undoes this; backup: configuration.nix.bak-before-b43-module)
  boot.extraModulePackages = [
    (config.boot.kernelPackages.callPackage /home/gonsolo/bcm4360-acphy/nix/b43-ac.nix { })
  ];
NIX
if [ "${1:-}" = --remove ]; then
	[ -f "$BAK" ] || { echo "no backup $BAK"; exit 1; }
	cp "$BAK" "$CONF"; echo "restored $CONF from backup"
else
	grep -q 'b43-ac.nix' "$CONF" && { echo "already installed in $CONF"; exit 0; }
	grep -qF "$ANCHOR" "$CONF" || { echo "anchor '$ANCHOR' not found in $CONF; add the block by hand"; exit 1; }
	[ -f "$BAK" ] || cp "$CONF" "$BAK"
	awk -v blk="$BLOCK" -v anc="$ANCHOR" '{ print } index($0, anc) == 1 && !done { print blk; done = 1 }' "$CONF" > "$CONF.new"
	mv "$CONF.new" "$CONF"; echo "added boot.extraModulePackages to $CONF (backup: $BAK)"
fi
$REBUILD
