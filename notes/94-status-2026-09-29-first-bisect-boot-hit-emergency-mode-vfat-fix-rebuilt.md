# Status 2026-09-29 (part 18): first bisect boot attempt hit emergency
mode (missing VFAT support for /boot), diagnosed and fixed, rebuilt

Direct continuation of notes/93, same day. User rebooted into the
staged first bisect candidate (`60b8d4d49281`) and hit systemd's
emergency shell - had to reboot again. **No damage**: the one-shot
mechanism correctly consumed itself and the second reboot returned to
the normal default entry (7.2.7 daily use) automatically, exactly as
designed - this is precisely the safety property the one-shot approach
(persistent default untouched) was built for.

## Root cause: found directly in the persisted journal, no guessing needed

`journalctl -b -1` (the failed boot is still in the persistent journal,
even after rebooting again) showed exactly one problem, cleanly:

```
mount: /boot: unknown filesystem type 'vfat'.
Failed to mount /boot.
Dependency failed for Local File Systems.
local-fs.target: Job local-fs.target/start failed with result 'dependency'.
...
Started Emergency Shell.
```

Everything else in that boot succeeded first - swap activated, root
(`ext4`, already builtin per notes/93's earlier fix) mounted fine,
`fsck.fat` even ran cleanly against `/boot` (a *userspace* tool,
independent of kernel driver support) right before the kernel-side
mount itself failed. `/boot` here is the EFI System Partition -
required to be FAT-formatted by the UEFI spec - and `/etc/fstab` has no
`nofail` on it, so systemd treats mounting it as mandatory for
`local-fs.target`. The bisect kernel's `.config` had `CONFIG_VFAT_FS=m`
(a loadable module) with, as with the earlier `EXT4_FS`/`SATA_AHCI`
fix, no initrd or module database to load it with before systemd needs
it - so the mount failed outright and took the whole boot down with it.

Exactly the same class of bug as notes/93's storage-driver fix, just
one filesystem missed that time (root/`ext4` and the underlying
`ATA`/`SATA_AHCI`/`SCSI`/`BLK_DEV_SD` chain were caught then; `/boot`'s
`vfat`/`FAT_FS`/`NLS_CODEPAGE_437`/`NLS_ISO8859_1` chain was not).

## Fix and rebuild

Flipped `FAT_FS`, `VFAT_FS`, `NLS_CODEPAGE_437`, `NLS_ISO8859_1` from
`=m` to `=y` in the local template `.config`, `olddefconfig`'d clean,
pushed to pampelmuse, rebuilt (`bzImage` #3, `-j18`, clean, no errors),
rebuilt `b43-src` against the same commit (binary-identical to the
first build - VFAT doesn't touch anything b43-relevant, `make`'s own
dependency tracking correctly skipped recompiling it), repackaged with
`tar`+`xz` (27.8M compressed vs. the earlier ~110M uncompressed - the
user's suggestion from notes/93 paid off immediately on a real
transfer, not just the small first one), pulled over the USB-stick
interface, re-staged as the same one-shot `nixos-bisect.conf` entry
(same commit, corrected kernel).

`tools/bisect_build.sh` updated with a comment documenting exactly
which symbols must be builtin and why, so regenerating `.config` from
scratch in a future session doesn't reintroduce this.

## Current state at session end

Corrected `bzImage` (#3) staged at
`/boot/EFI/nixos/bisect-60b8d4d4-bzImage.efi`, one-shot re-armed
(`bootctl set-oneshot nixos-bisect.conf`). Persistent default entry
still untouched (normal 7.2.7 daily use). Local `~/src/linux/.config`
now carries both fixes (storage/root-fs *and* boot-fs builtin) and will
be reused as-is (via `scp` + `olddefconfig`) for every subsequent
bisect step through `tools/bisect_build.sh`, so this specific class of
bug shouldn't recur. Ready for the user to retry the reboot.

## Next steps

Unchanged from notes/93: reboot into the (now-corrected) one-shot
entry, run `bash ~/bcm4360-acphy/bisect-boot/load.sh`, confirm
`wlp3s0b1` + NetworkManager work, then run the `connect_test.sh`/
`suspendtiming` pass/fail check and record `git bisect good`/`bad`.
