#!/usr/bin/env bash
# Build+package one git-bisect candidate kernel on the remote builder
# (pampelmuse) and stage it as a one-shot local boot entry. Run from the
# laptop. Assumes:
#  - ~/src/linux has the commit already checked out (git bisect does this)
#  - ~/src/linux/.config exists locally with the project's minimal,
#    boot-without-initrd config. Required builtin (=y, not =m) since
#    there's no initrd/depmod to load modules for any of this before
#    it's needed - each was hit for real as a boot failure before being
#    added (notes/93, notes/94, notes/95):
#      storage/root-fs:  SCSI, BLK_DEV_SD, ATA, SATA_AHCI, EXT4_FS
#      boot-fs (/boot is the EFI System Partition, vfat, no `nofail`
#        in fstab, so a failed mount here takes down local-fs.target
#        and drops to the emergency shell):
#                         FAT_FS, VFAT_FS, NLS_CODEPAGE_437, NLS_ISO8859_1
#      input (no keyboard/trackpad without these - notes/95):
#                         LEDS_CLASS, SPI_PXA2XX, SPI_PXA2XX_PCI,
#                         KEYBOARD_APPLESPI, HID, HID_APPLE, HID_GENERIC,
#                         USB_HID, USB_XHCI_HCD, USB_XHCI_PCI,
#                         INPUT_MOUSEDEV, INPUT_LEDS, INPUT_EVDEV
#    Kconfig dependency note: `make olddefconfig` does NOT auto-upgrade
#    an existing =m to =y just because a blocking dependency later
#    becomes satisfied - if two of these depend on each other (e.g.
#    KEYBOARD_APPLESPI/HID_APPLE/INPUT_LEDS all depend on LEDS_CLASS),
#    fix the dependency first, rerun olddefconfig, then re-apply =y to
#    whichever ones got silently held back at =m, and rerun once more.
#    If regenerating .config from scratch, flip all of the above from
#    =m to =y, rerunning olddefconfig between passes until every one of
#    them sticks at =y (`grep` them back out and check - don't trust
#    the first pass).
#    Boots to the *real* default target (graphical.target/GDM, same as
#    normal - no systemd.unit= override) now that notes/95's input fix
#    is confirmed working (keyboard+trackpad correctly detected in the
#    journal) - that was the only known reason GDM wasn't viable.
#    Passes systemd.wants=getty@tty1.service as a fallback text login
#    (this NixOS config disables getty@tty1 by default since GDM
#    normally owns tty1, notes/96) and systemd.debug-shell=1 as a
#    last-resort unauthenticated root shell on tty9 (Ctrl+Alt+F9) -
#    on this hardware also needs hid_apple.fnmode=2 (also passed) since
#    the default fnmode=1 sends bare F-keys as media functions, not
#    literal Fn, though Ctrl+Alt+F9 VT-switching was not observed to
#    work even with fnmode fixed and Fn held (notes/98) - not yet
#    understood, tty9 access is unconfirmed, treat it as unreliable.
#    Separately: the getty@tty1 *text* login was observed to
#    authenticate successfully and then have its shell exit cleanly
#    (no crash/signal/oops - just exits) within about a second, cause
#    not yet found (notes/97/98) - if graphical.target/GDM also hits
#    this, that's a strong clue it's not console-specific.
#  - the SSH key + pampelmuse ~/src/linux clone from notes/93 already exist
#  - IMPORTANT: only call this via a backgrounded Bash tool invocation
#    (run_in_background / &), never via a detached remote nohup/screen -
#    pampelmuse's logind kills those the moment the SSH session closes
#    (notes/93).
set -eu
KEY=~/.ssh/id_ed25519_builder
REMOTE=gonsolo@192.168.0.236
LOCAL_LINUX=~/src/linux
STAGE=~/bcm4360-acphy/bisect-boot
B43SRC=~/bcm4360-acphy/b43-src

COMMIT=$(cd "$LOCAL_LINUX" && git rev-parse --short=12 HEAD)
echo "=== bisect_build: $COMMIT ==="

echo "--- syncing checkout + config to pampelmuse ---"
ssh -i "$KEY" "$REMOTE" "cd ~/src/linux && git checkout -f $COMMIT" >/dev/null
scp -i "$KEY" "$LOCAL_LINUX/.config" "$REMOTE:~/src/linux/.config" >/dev/null
ssh -i "$KEY" "$REMOTE" "cd ~/src/linux && yes '' | make olddefconfig" >/dev/null 2>&1

echo "--- building bzImage + modules (-j18) ---"
ssh -i "$KEY" "$REMOTE" "cd ~/src/linux && make -j18 bzImage modules > /tmp/build.log 2>&1"
ssh -i "$KEY" "$REMOTE" "tail -3 /tmp/build.log; test -f ~/src/linux/arch/x86/boot/bzImage"

echo "--- syncing b43-src, building against this kernel ---"
rsync -a --exclude='*.ko' --exclude='*.o' --exclude='*.mod' --exclude='*.mod.c' \
	--exclude='.*.cmd' --exclude='Module.symvers' --exclude='modules.order' \
	-e "ssh -i $KEY" "$B43SRC/" "$REMOTE:~/b43-src-bisect/"
ssh -i "$KEY" "$REMOTE" "cd ~/b43-src-bisect && make -j18 KDIR=/home/gonsolo/src/linux > /tmp/b43build.log 2>&1"
ssh -i "$KEY" "$REMOTE" "tail -3 /tmp/b43build.log; test -f ~/b43-src-bisect/b43.ko"

echo "--- packaging (tar+xz on the remote, small transfer either way) ---"
ssh -i "$KEY" "$REMOTE" "cd ~/src/linux && tar -cJf /tmp/bisect-pkg.tar.xz -C arch/x86/boot bzImage \
	-C /home/gonsolo/src/linux/drivers/bcma bcma.ko \
	-C /home/gonsolo/src/linux/drivers/ssb ssb.ko \
	-C /home/gonsolo/src/linux/drivers/leds led-class.ko \
	-C /home/gonsolo/src/linux/net/wireless cfg80211.ko \
	-C /home/gonsolo/src/linux/net/mac80211 mac80211.ko \
	-C /home/gonsolo/src/linux/lib/math cordic.ko \
	-C /home/gonsolo/src/linux/net/rfkill rfkill.ko \
	-C /home/gonsolo/src/linux/lib/crypto libarc4.ko \
	-C /home/gonsolo/b43-src-bisect b43.ko"

echo "--- pulling package (via USB stick interface, not the buggy b43 link) ---"
rm -rf "$STAGE"
mkdir -p "$STAGE"
scp -i "$KEY" -o BindAddress=192.168.0.98 "$REMOTE:/tmp/bisect-pkg.tar.xz" "$STAGE/pkg.tar.xz"
tar -xJf "$STAGE/pkg.tar.xz" -C "$STAGE"
rm "$STAGE/pkg.tar.xz"
ls -la "$STAGE"

echo "--- staging boot entry (default entry untouched, one-shot only) ---"
EFI_NAME="bisect-$COMMIT-bzImage.efi"
sudo cp "$STAGE/bzImage" "/boot/EFI/nixos/$EFI_NAME"
DEFAULT_ENTRY=$(sudo awk '/^default /{print $2}' /boot/loader/loader.conf)
INIT=$(sudo grep -oP 'init=\S+' "/boot/loader/entries/$DEFAULT_ENTRY")
cat <<EOF | sudo tee /boot/loader/entries/nixos-bisect.conf >/dev/null
title NixOS (bisect)
sort-key nixos-bisect
version bisect $COMMIT (mainline, no NixOS initrd, custom minimal config, graphical default + fallbacks)
linux /EFI/nixos/$EFI_NAME
options $INIT root=/dev/sda3 rootfstype=ext4 loglevel=4 lsm=landlock,yama,bpf systemd.wants=getty@tty1.service systemd.debug-shell=1 hid_apple.fnmode=2
machine-id 1e7ffcf2ac3d46e0855327b0012ddbee
EOF
sudo bootctl set-oneshot nixos-bisect.conf

cat > "$STAGE/load.sh" <<'EOF'
#!/usr/bin/env bash
set -eu
cd "$(dirname "$0")"
echo /home/gonsolo/bcm4360-acphy/firmware | sudo tee /sys/module/firmware_class/parameters/path
sudo insmod cordic.ko
sudo insmod rfkill.ko
sudo insmod libarc4.ko
sudo insmod cfg80211.ko
sudo insmod mac80211.ko
sudo insmod bcma.ko
sudo insmod ssb.ko
sudo insmod led-class.ko
sudo insmod b43.ko verbose=3
echo "b43 interface: $(ls /sys/class/net | grep -E '^wl')"
EOF
chmod +x "$STAGE/load.sh"

echo "=== ready: commit $COMMIT staged as one-shot boot, reboot when ready ==="
