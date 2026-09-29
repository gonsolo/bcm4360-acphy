# Status 2026-09-29 (part 25): eighth bisect boot - desktop mostly
worked (cursor, interaction) but no application could be launched at
all, not even by typing a bare command name - `/run/current-system`
was never created, because NixOS's *own* real initrd normally sets it
up before handing off to systemd, and our generic replacement initrd
never knew to. Fixed - and for the first time, the fix needed no kernel
rebuild at all, just a new initrd.

Direct continuation of notes/100, same day. The new NixOS-config +
generic-initrd pipeline worked well: mouse cursor appeared (a "strange
square cursor" - cosmetic, a separate/minor theme issue, not
investigated), Activities overview opened and accepted keyboard input,
`Alt+F2`'s "Run a Command" dialog opened correctly (confirming
`hid_apple.fnmode=2` genuinely works for at least this key). But **no
application could be launched at all** - not from the app grid/search
(empty, no icons, not even Firefox or the terminal), and not by typing
a bare command name like `kgx` into the `Alt+F2` dialog either.

## Diagnosis

`journalctl -b -1` found the exact failure, repeated for several
different processes:

```
gnome-session[1035]: Failed to re-execute with login shell (/run/current-system/sw/bin/bash): No such file or directory
gnome-shell[699]: AT-SPI: Error retrieving accessibility bus address: ... Failed to spawn child process "/run/current-system/sw/bin/dbus-daemon" (No such file or directory)
.gnome-shell-wr[699]: Failed to launch ibus-daemon: ... "ibus-daemon" (No such file or directory)
```

**Every failure is the same shape**: something under
`/run/current-system/sw/bin/` doesn't exist. Checked whether the
underlying Nix store path itself was gone (e.g. garbage collected) -
no, `/nix/store/4g50ax5.../sw/bin/bash` resolves fine right now, on the
normal boot. The real problem: **`/run/current-system` was never
created as a symlink at all** during our custom boot. On a real NixOS
boot, this symlink (and `/run/booted-system`) is set up by NixOS's own
stage-1 (real initrd) before it switches to stage-2/systemd - our
generic, NixOS-agnostic initrd (notes/100) correctly loads every kernel
module generically, but has no idea this NixOS-specific step exists,
so it never happens.

Confirmed indirectly: the currently-running normal system's
`/run/current-system` actually points at a *different*, newer
generation (`9p3rg4ya...`) than the one our boot entry's `init=`
still names (`4g50ax...`, captured back in notes/93 before a later
`nixos-rebuild switch` moved the default forward) - this is expected
and harmless (each NixOS generation is a fully self-contained closure;
booting an older one and having it establish `/run/current-system` as
*itself* is completely normal, that's exactly what a real NixOS boot
of an older generation does) - it just highlighted that the symlink
needs to be created fresh, pointing at whatever `init=` on *this*
boot's command line actually says, not copied from the live system.

## Fix, and a nice property of this new pipeline: no kernel rebuild needed

Updated `tools/bisect_initrd_init`: after mounting the real root but
before `switch_root`, mount a fresh `tmpfs` at `/newroot/run` and
create `current-system`/`booted-system` symlinks pointing at
`dirname "$REALINIT"` (the same system closure `init=` already names -
one source of truth, matches the existing pattern for reading
`$REALINIT` itself from `/proc/cmdline`). This relies on systemd
detecting an already-suitable `/run` mount and not remounting it fresh
once `switch_root` hands off - standard, expected systemd behavior
(`mount-setup.c` checks before mounting), and apparently exactly what
NixOS's own real initrd already relies on too.

**Because only the init script changed, not the kernel or its modules,
this was the first fix in the whole bisect-boot saga that needed no
kernel rebuild at all** - just re-running the (fast) initrd packaging
step against the already-built module tree from notes/100, re-staging,
done in well under a minute. This is exactly the kind of iteration-
speed win the generic-initrd rework was for.

## Current state at session end

Eighth attempt at the same commit (`60b8d4d49281`) about to begin, same
`bzImage`, new `initrd.img`. `tools/bisect_initrd_init` updated in the
repo. The "strange square cursor" from this session is still
unexplained and unfixed - noted but not blocking, will revisit only if
it turns out to matter once an actual terminal is reachable.

## Next steps

Reboot into the corrected entry. If application launching now works:
finally, actually run the bisect test - open a terminal, `bash
~/bcm4360-acphy/bisect-boot/load.sh`, confirm `wlp3s0b1`, `connect_test.sh`/
check `dmesg` for `suspendtiming`/`MAC suspend failed`, `git bisect
good`/`bad`, then `tools/bisect_build.sh` for the next candidate.
