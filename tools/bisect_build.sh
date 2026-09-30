#!/usr/bin/env bash
# Build+package one git-bisect candidate kernel on the remote builder
# (pampelmuse) and stage it as a one-shot local boot entry. Run from the
# laptop. See notes/100 for the full story of how this pipeline evolved
# (notes/93-99 chronicle six failed boot attempts caused by hand-picking
# which drivers must be builtin, one at a time, by trial and error -
# storage/vfat, HID/input, GPU (i915) were each discovered as a boot
# failure before being fixed).
#
# Current design (notes/100), much more robust than the earlier one:
#  - ~/src/linux/.config is NixOS's own actual .config for the real,
#    working 7.2.7 kernel (from the linux-7.2.7-dev package in the Nix
#    store), NOT a hand-built minimal config - guaranteed to already
#    support everything this hardware needs, since it's what's really
#    running day to day. `make localmodconfig` (LSMOD=current lsmod)
#    trims it down to roughly what's actually relevant on this specific
#    machine, per the user's "strip what's obviously not needed"
#    request - safe because it's a standard, well-tested kbuild tool,
#    not hand-guessing individual Kconfig symbols.
#  - Module compression is disabled (CONFIG_MODULE_COMPRESS unset) so
#    plain .ko files, no compression-library dependency in the initrd.
#  - A real, generic initrd (built by this script, see below) loads
#    *every* module the kernel produced via `modprobe -a`, using a
#    depmod-generated dependency database - this is what actually
#    eliminates the whole "which driver needs to be builtin" class of
#    bug going forward, not another round of manual Kconfig guessing.
#    Everything in the kernel's own modules_install tree (storage, HID,
#    GPU, sound, whatever) loads automatically and generically. Only
#    b43.ko (out-of-tree, not part of the kernel's own module tree)
#    still needs a manual insmod, via bisect-boot/load.sh after login.
#  - Boots to the real default target (graphical.target/GDM, no
#    systemd.unit= override) with systemd.wants=getty@tty1.service and
#    systemd.debug-shell=1 as fallbacks, and hid_apple.fnmode=2 (this
#    hardware's F-keys default to media functions, not literal Fn -
#    notes/98) - though note Ctrl+Alt+F9 VT-switching was not observed
#    to work on this hardware even with fnmode fixed (notes/98),
#    unexplained, treat tty9 access as unreliable.
#
# Assumes:
#  - ~/src/linux has the commit already checked out (git bisect does this)
#  - ~/src/linux/.config exists locally, built as described above
#  - the SSH key + pampelmuse ~/src/linux clone from notes/93 already exist
#  - ~/busybox-static exists on pampelmuse (a statically-linked
#    pkgsStatic.busybox build, copied once - `nix-shell -p
#    pkgsStatic.busybox --run 'echo $(readlink -f $(which busybox))'`
#    locally, then scp to pampelmuse - includes modprobe/switch_root/
#    mdev applets, no shared-library bundling needed since it's static)
#  - a generic init script for the initrd - kept as
#    tools/bisect_initrd_init (deploy alongside this script)
#  - IMPORTANT: only call this via a backgrounded Bash tool invocation
#    (run_in_background / &), never via a detached remote nohup/screen -
#    pampelmuse's logind kills those the moment the SSH session closes
#    (notes/93).
# The laptop reaches pampelmuse over Wi-Fi that can drop or roam mid-build:
# retry connection failures (exit 255) instead of aborting the whole pipeline.
ssh() { local i rc; for i in 1 2 3 4 5 6 7 8; do command ssh -o ConnectTimeout=10 "$@" && return 0; rc=$?; [ $rc -ne 255 ] && return $rc; sleep 8; done; return 255; }
scp() { local i rc; for i in 1 2 3 4 5 6 7 8; do command scp -o ConnectTimeout=10 "$@" && return 0; rc=$?; [ $rc -ne 255 ] && return $rc; sleep 8; done; return 255; }
set -eu
KEY=~/.ssh/id_ed25519_builder
REMOTE=gonsolo@192.168.0.236
LOCAL_LINUX=~/src/linux
STAGE=~/bcm4360-acphy/bisect-boot
B43SRC=~/bcm4360-acphy/b43-src
INITSCRIPT=~/bcm4360-acphy/tools/bisect_initrd_init

COMMIT=$(cd "$LOCAL_LINUX" && git rev-parse --short=12 HEAD)
echo "=== bisect_build: $COMMIT ==="

echo "--- syncing checkout + config to pampelmuse ---"
ssh -i "$KEY" "$REMOTE" "cd ~/src/linux && git checkout -f $COMMIT" >/dev/null
scp -i "$KEY" "$LOCAL_LINUX/.config" "$REMOTE:~/src/linux/.config" >/dev/null
# Optional config overrides for experiments (notes/103), e.g. EXTRA_CONFIG="CONFIG_KVM=n"
if [ -n "${EXTRA_CONFIG:-}" ]; then
	for opt in $EXTRA_CONFIG; do ssh -i "$KEY" "$REMOTE" "echo $opt >> ~/src/linux/.config"; done
	echo "extra config: $EXTRA_CONFIG"
fi
ssh -i "$KEY" "$REMOTE" "cd ~/src/linux && yes '' | make olddefconfig" >/dev/null 2>&1

echo "--- building bzImage + modules (-j18) ---"
ssh -i "$KEY" "$REMOTE" "cd ~/src/linux && make -j18 bzImage modules > /tmp/build.log 2>&1"
ssh -i "$KEY" "$REMOTE" "tail -3 /tmp/build.log; test -f ~/src/linux/arch/x86/boot/bzImage"

echo "--- modules_install + depmod ---"
ssh -i "$KEY" "$REMOTE" "cd ~/src/linux && rm -rf ~/modinstall && make -j18 modules_install INSTALL_MOD_PATH=~/modinstall INSTALL_MOD_STRIP=1 > /tmp/modinstall.log 2>&1; tail -3 /tmp/modinstall.log"

echo "--- building generic modprobe-everything initrd ---"
scp -i "$KEY" "$INITSCRIPT" "$REMOTE:~/initrd-init" >/dev/null
ssh -i "$KEY" "$REMOTE" "
set -e
rm -rf ~/initramfs-root
mkdir -p ~/initramfs-root/bin ~/initramfs-root/proc ~/initramfs-root/sys ~/initramfs-root/dev ~/initramfs-root/newroot ~/initramfs-root/lib
cp ~/busybox-static ~/initramfs-root/bin/busybox
chmod +x ~/initramfs-root/bin/busybox
cp ~/initrd-init ~/initramfs-root/init
chmod +x ~/initramfs-root/init
cp -a ~/modinstall/lib/modules ~/initramfs-root/lib/modules
cd ~/initramfs-root
find . | cpio -o -H newc 2>/dev/null | gzip -9 > ~/initrd.img
"
ssh -i "$KEY" "$REMOTE" "ls -la ~/initrd.img"

echo "--- syncing b43-src, building against this kernel ---"
rsync -a --exclude='*.ko' --exclude='*.o' --exclude='*.mod' --exclude='*.mod.c' \
	--exclude='.*.cmd' --exclude='Module.symvers' --exclude='modules.order' \
	-e "ssh -i $KEY" "$B43SRC/" "$REMOTE:~/b43-src-bisect/"
ssh -i "$KEY" "$REMOTE" "cd ~/b43-src-bisect && make -j18 KDIR=/home/gonsolo/src/linux > /tmp/b43build.log 2>&1"
ssh -i "$KEY" "$REMOTE" "tail -3 /tmp/b43build.log; test -f ~/b43-src-bisect/b43.ko"

echo "--- packaging (tar+xz on the remote) ---"
ssh -i "$KEY" "$REMOTE" "cd ~/src/linux && tar -cJf /tmp/bisect-pkg.tar.xz -C arch/x86/boot bzImage \
	-C /home/gonsolo initrd.img \
	-C /home/gonsolo/b43-src-bisect b43.ko"

echo "--- pulling package ---"
rm -rf "$STAGE"
mkdir -p "$STAGE"
scp -i "$KEY" "$REMOTE:/tmp/bisect-pkg.tar.xz" "$STAGE/pkg.tar.xz"
tar -xJf "$STAGE/pkg.tar.xz" -C "$STAGE"
rm "$STAGE/pkg.tar.xz"
ls -la "$STAGE"

echo "--- staging boot entry (default entry untouched, one-shot only) ---"
# /boot is small (511M) and every candidate is ~25M: drop the earlier, already-tested ones
sudo rm -f /boot/EFI/nixos/bisect-*
EFI_KERNEL="bisect-$COMMIT-bzImage.efi"
EFI_INITRD="bisect-$COMMIT-initrd.img"
sudo cp "$STAGE/bzImage" "/boot/EFI/nixos/$EFI_KERNEL"
sudo cp "$STAGE/initrd.img" "/boot/EFI/nixos/$EFI_INITRD"
DEFAULT_ENTRY=$(sudo awk '/^default /{print $2}' /boot/loader/loader.conf)
INIT="init=$(readlink -f /run/current-system)/init"  # the running generation, not a stale default entry (notes/103)
cat <<EOF | sudo tee /boot/loader/entries/nixos-bisect.conf >/dev/null
title NixOS (bisect)
sort-key nixos-bisect
version bisect $COMMIT (mainline, generic modprobe-everything initrd, graphical default)
linux /EFI/nixos/$EFI_KERNEL
initrd /EFI/nixos/$EFI_INITRD
options $INIT root=/dev/sda3 rootfstype=ext4 loglevel=7 panic=0 lsm=landlock,yama,bpf systemd.wants=getty@tty1.service systemd.debug-shell=1 hid_apple.fnmode=2
machine-id 1e7ffcf2ac3d46e0855327b0012ddbee
EOF
sudo bootctl set-oneshot nixos-bisect.conf

cat > "$STAGE/load.sh" <<'EOF'
#!/usr/bin/env bash
set -eu
cd "$(dirname "$0")"
DEV=0000:03:00.0
if [ "$(basename "$(readlink -f /sys/bus/pci/devices/$DEV/driver 2>/dev/null)" 2>/dev/null)" != bcma-pci-bridge ]; then
	echo bcma-pci-bridge | sudo tee /sys/bus/pci/devices/$DEV/driver_override
	[ -e /sys/bus/pci/devices/$DEV/driver ] && \
		echo "$DEV" | sudo tee /sys/bus/pci/devices/$DEV/driver/unbind
	echo "$DEV" | sudo tee /sys/bus/pci/drivers_probe
fi
sudo rmmod b43 2>/dev/null || true
sudo insmod b43.ko verbose=3
sleep 1
echo "b43 interface: $(ls /sys/class/net | grep -E '^wl')"
EOF
chmod +x "$STAGE/load.sh"

echo "=== ready: commit $COMMIT staged as one-shot boot, reboot when ready ==="
