# Status 2026-09-29 (part 20): third bisect boot reached a fully
healthy multi-user system with no login prompt anywhere - `getty@tty1`
is disabled by this NixOS config (GDM normally owns it); fixed with a
kernel-cmdline `systemd.wants=`, no rebuild needed

Direct continuation of notes/95, same day. The input-driver fix
worked - this boot's own journal shows
`systemd-logind[367]: Watching system buttons on /dev/input/event0
(Apple Inc. Apple Internal Keyboard / Trackpad)`, confirming the
keyboard/trackpad chain is now correctly detected. But the user still
saw no login prompt and had to reboot again.

## Diagnosis: not a hang, not a driver problem - a genuinely absent login mechanism

The full journal for that boot (`journalctl -b -1`) shows a completely
healthy, fast boot: NetworkManager started, SSH daemon started and
listening, `Reached target Multi-User System`, `Startup finished in
871ms (kernel) + 3.205s (userspace) = 4.077s.` - nothing hung, nothing
failed in a way that blocked the target. But **no `getty`/`agetty`
unit is mentioned anywhere in the entire boot log** - not started, not
failed, not even attempted.

Checked directly on the normal (7.2.7) boot, since this is static
system configuration that doesn't depend on which kernel is running:

```
$ systemctl status getty@tty1.service
○ getty@tty1.service - Getty on tty1
     Loaded: loaded (...); disabled; preset: ignored
```

**`getty@tty1.service` is disabled by this system's own NixOS
configuration** - normal and correct for a system whose default target
is `graphical.target` with GDM providing the login screen on tty1
instead (a standard systemd/display-manager pattern, avoids a text
getty racing the graphical login on the same VT). notes/95's
`systemd.unit=multi-user.target` override was the right call to avoid
depending on a working mouse/GDM, but it has this side effect: with
`graphical.target` (and GDM) never reached, and `getty@tty1` statically
disabled, **nothing at all provides a login prompt** - the system
reaches a fully healthy running state with network and SSH up, and
just sits there silently. Easy to read as "the boot hung," but the
timestamps and the clean `Startup finished` line show it didn't.

## Fix: no rebuild needed

`systemd.wants=<unit>` is a documented systemd kernel command-line
parameter that adds a synthetic start job for a unit, independent of
whether it's normally enabled - exactly what's needed here. Added
`systemd.wants=getty@tty1.service` to the boot entry's `options` line
directly (`/boot/loader/entries/nixos-bisect.conf`, no kernel/module
rebuild required - this is pure boot configuration, unlike notes/94/95's
fixes which needed new `.config`/`bzImage` builds). Re-armed the
existing one-shot. `tools/bisect_build.sh`'s boot-entry template
updated with the same flag and a comment explaining why, so every
future bisect step gets it automatically.

## Current state at session end

Boot entry updated in place (same `bzImage` as notes/95, commit
`60b8d4d49281`, only the kernel command line changed), one-shot
re-armed. This is the fourth attempt at the same commit; the actual
bisect test still hasn't run once. Three real, independent boot-
environment problems found and fixed in a row (storage/vfat, notes/94;
input/HID, notes/95; now getty/login, this note) - each one only
became visible once the *previous* one was fixed and the boot got
further before stalling, which is itself a reasonable (if slow) way
these things converge.

## Next steps

Unchanged in substance: reboot into the one-shot entry, this time
expecting an actual `login:` prompt on tty1, log in, run
`bash ~/bcm4360-acphy/bisect-boot/load.sh`, confirm `wlp3s0b1` comes up,
run the `connect_test.sh`/`suspendtiming` pass/fail check, record `git
bisect good`/`bad`, then `tools/bisect_build.sh` for the next candidate.
