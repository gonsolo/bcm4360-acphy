#!/usr/bin/env bash
# Build b43-src for a kernel and store it as b43-src-builds/b43-<version>.ko (loaded by tools/b43_boot.sh).
# usage: tools/build_b43_for_kernel.sh /nix/store/...-linux-X.Y.Z-dev
# If the -dev output is missing locally (e.g. after nix-collect-garbage), fetch it from the cache first:
#   nix --extra-experimental-features nix-command copy --from https://cache.nixos.org <dev path>
# (the dev path of a generation's kernel: nix-store -q --outputs <linux-X.Y.Z.drv>, see notes/114)
set -eu
DEV=${1:?usage: $0 /nix/store/...-linux-X.Y.Z-dev}
P=$(cd "$(dirname "$0")/.." && pwd)
VER=$(ls "$DEV/lib/modules")
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
(cd "$P" && git archive HEAD b43-src) | tar -x -C "$T"
cp "$P"/b43-src/*.[ch] "$T/b43-src/"          # include uncommitted edits, no stale objects
nix-shell -p gnumake gcc --run "make -C $DEV/lib/modules/$VER/build M=$T/b43-src modules" >/dev/null
mkdir -p "$P/b43-src-builds"
cp "$T/b43-src/b43.ko" "$P/b43-src-builds/b43-$VER.ko"
modinfo -F vermagic "$P/b43-src-builds/b43-$VER.ko"
