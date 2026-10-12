#!/usr/bin/env bash
# build_upstream_tree.sh <repo> <kernel-dev>: compile the b43 directory of the upstream series repo against a kernel's -dev headers
# (out of tree; the CONFIG_ symbols a defconfig would set are passed on the command line). Prints warnings/errors only.
set -eu
R=${1:?usage: $0 <repo> <kernel-dev>}; DEV=${2:?}
VER=$(ls "$DEV/lib/modules")
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
cp -r "$R/drivers/net/wireless/broadcom/b43" "$T/b43"
nix-shell -p gnumake gcc --run "make -C $DEV/lib/modules/$VER/build M=$T/b43 CONFIG_B43=m CONFIG_B43_BCMA=y CONFIG_B43_PHY_G=y CONFIG_B43_PHY_N=y CONFIG_B43_PHY_LP=y CONFIG_B43_PHY_HT=y CONFIG_B43_PHY_LCN=y CONFIG_B43_PHY_AC=y CONFIG_B43_LEDS=y modules W=1 2>&1" | grep -E "error|warning|Error" | grep -v pahole || true
[ -e "$T/b43/b43.ko" ] && echo "built OK: $(modinfo -F vermagic $T/b43/b43.ko)" || { echo "BUILD FAILED"; exit 1; }
