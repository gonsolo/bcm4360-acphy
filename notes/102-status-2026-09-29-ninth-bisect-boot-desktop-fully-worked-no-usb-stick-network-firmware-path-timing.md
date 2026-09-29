# Status 2026-09-29 (part 26): ninth bisect boot - the desktop fully
worked (apps launch, a terminal opened, the user even ran `claude`
inside it), but the USB WiFi stick never got network - the initrd
loaded it before the firmware search path was set, a pure ordering bug.
Fixed, no kernel rebuild.

Direct continuation of notes/101, same day - and the first genuinely
*good* boot report of this whole saga: `/run/current-system` fix
worked, apps launched from the grid and from `Alt+F2`, a terminal
opened, and the user actually started a `claude` session running
*inside* the bisect-booted kernel. The one remaining problem: no
network at all, not even the USB backup stick (`mt76x2u`), which also
never appeared in GNOME's network settings.

## Diagnosis

Checked (from the normal boot) what firmware the stick's driver
(`mt76x2u`) needs and where it normally comes from: NixOS's
`hardware.firmware` list gets built into **one consolidated store path**
(`/nix/store/<hash>-firmware/lib/firmware`), containing *both* the
stick's firmware (`mt7662.bin.zst` etc.) *and* this project's own `b43`
firmware - the same single directory serves everything, not separate
per-device paths. Every NixOS system closure has a stable
`$SYSTEM/firmware` symlink pointing at it (verified identical across
both the old and new generation on this machine).

The real bug: **ordering**. `bisect-boot/load.sh` (which sets the
firmware search path) only runs *after* login - but the initrd's own
`modprobe -a` (notes/100) loads every module, including `mt76x2u`,
*during early boot*, long before login. `mt76x2u` requests its firmware
immediately on module load/device probe, at a point when the firmware
search path was still whatever default the initrd's own bare root
provides (nothing) - so the request failed silently, once, and (unlike
`b43`, which is loaded manually and much later via `load.sh`, by which
point the path was already fixable) there was no later retry to fix.

## Fix

Moved the firmware-path setup into `tools/bisect_initrd_init` itself,
*before* the `modprobe -a` call: mount the real root first (need it to
read the firmware files), resolve `$SYSTEM/firmware` via a `chroot
/newroot readlink -f` (correct symlink resolution across the not-yet-
switched-root boundary), then write that path to
`/sys/module/firmware_class/parameters/path` before any module loads.
Simplified `bisect-boot/load.sh` to match - it no longer needs its own
firmware-path override at all, since the initrd now sets it globally
and correctly for the whole boot, before `b43.ko` is loaded too.

Like notes/101's fix, this needed **no kernel rebuild** - initrd-only,
repackaged and re-staged in well under a minute.

## Current state at session end

Ninth attempt at the same commit (`60b8d4d49281`) about to begin, same
`bzImage`, new `initrd.img`. If this works, the point of a working
network *inside* the bisect boot is to let a `claude` session running
there work directly and continuously through the remaining bisect
steps, rather than relaying every result back through the user across
reboots - a meaningful speed-up for the ~13 remaining steps.

## Next steps

Reboot into the corrected entry. If the USB stick gets a real IP this
time: the environment is finally complete enough to actually run the
bisect test - `bash ~/bcm4360-acphy/bisect-boot/load.sh` for `b43`
itself, `connect_test.sh`/check `dmesg` for `suspendtiming`/`MAC
suspend failed`, `git bisect good`/`bad`, then `tools/bisect_build.sh`
for the next candidate.
