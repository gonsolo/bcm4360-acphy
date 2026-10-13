#!/usr/bin/env bash
# build_upstream_tree.sh <repo> <kernel-dev>: compile the b43 directory of the upstream series repo against a kernel's -dev headers
# KEEP=<file> also copies the built module there.
# REMOTE=<host> compiles on that host (rsync + ssh, make -j${JOBS:-18}); the -dev path must exist there
#   (ssh <host> nix-store -r <kernel-dev> fetches it from the binary cache). Use it: the laptop is slow.
# (out of tree; the CONFIG_ symbols a defconfig would set are passed on the command line). Prints warnings/errors only.
set -eu
R=${1:?usage: $0 <repo> <kernel-dev>}; DEV=${2:?}
VER=$(ls "$DEV/lib/modules")
MAKEARGS="CONFIG_B43=m CONFIG_B43_BCMA=y CONFIG_B43_PHY_G=y CONFIG_B43_PHY_N=y CONFIG_B43_PHY_LP=y CONFIG_B43_PHY_HT=y CONFIG_B43_PHY_LCN=y CONFIG_B43_PHY_AC=y CONFIG_B43_LEDS=y KCFLAGS=-DCONFIG_B43_PHY_AC=1 modules W=1"
if [ -n "${REMOTE:-}" ]; then
	RT=/tmp/b43build-$$
	trap 'ssh "$REMOTE" "rm -rf $RT" >/dev/null 2>&1 || true' EXIT
	ssh "$REMOTE" "mkdir -p $RT"
	rsync -a --delete "$R/drivers/net/wireless/broadcom/b43/" "$REMOTE:$RT/b43/"
	ssh "$REMOTE" "nix-shell -p gnumake gcc --run 'make -j${JOBS:-18} -C $DEV/lib/modules/$VER/build M=$RT/b43 $MAKEARGS 2>&1'" \
		| grep -E "error|warning|Error" | grep -v pahole || true
	if ssh "$REMOTE" "test -e $RT/b43/b43.ko"; then
		T=$(mktemp -d); trap 'rm -rf "$T"; ssh "$REMOTE" "rm -rf $RT" >/dev/null 2>&1 || true' EXIT
		scp -q "$REMOTE:$RT/b43/b43.ko" "$T/b43.ko"
		[ -n "${KEEP:-}" ] && cp "$T/b43.ko" "$KEEP"
		echo "built OK: $(modinfo -F vermagic $T/b43.ko)"
	else
		echo "BUILD FAILED"; exit 1
	fi
	exit 0
fi
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
cp -r "$R/drivers/net/wireless/broadcom/b43" "$T/b43"
nix-shell -p gnumake gcc --run "make -C $DEV/lib/modules/$VER/build M=$T/b43 $MAKEARGS 2>&1" | grep -E "error|warning|Error" | grep -v pahole || true
[ -n "${KEEP:-}" ] && [ -e "$T/b43/b43.ko" ] && cp "$T/b43/b43.ko" "$KEEP"
[ -e "$T/b43/b43.ko" ] && echo "built OK: $(modinfo -F vermagic $T/b43/b43.ko)" || { echo "BUILD FAILED"; exit 1; }
