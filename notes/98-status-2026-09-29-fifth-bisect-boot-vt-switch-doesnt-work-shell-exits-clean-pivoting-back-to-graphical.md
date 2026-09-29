# Status 2026-09-29 (part 22): fifth bisect boot - `Ctrl+Alt+F9` VT
switching doesn't work even with the Apple-keyboard `fnmode` quirk
fixed; the tty1 shell-exit is a clean exit, not a crash; pivoting back
to `graphical.target` since the input fix (notes/95) removed the only
known reason it wasn't viable

Direct continuation of notes/97, same day. The `systemd.debug-shell`
service itself did start successfully (`Started Early root shell on
/dev/tty9 FOR DEBUGGING ONLY.`, confirmed in the journal, and never
shown as deactivated for the rest of that boot) - but the user couldn't
actually reach it. Neither `Ctrl+Alt+F9` nor `Fn+Ctrl+Alt+F9` switched
the console.

## Investigated the Apple-keyboard angle first

Checked `hid-apple.c`: default `fnmode=3` (auto) resolves to
`real_fnmode=1` for a genuine Apple internal keyboard - meaning bare
F-row presses are translated to their *media* function by default, and
the physical Fn key must be held to get a literal F-key. This is a
real, well-known MacBook-on-Linux quirk and a completely reasonable
explanation to try first. Added `hid_apple.fnmode=2` (bare F-keys
always literal, Fn only needed for the media function instead) to the
boot entry - a pure kernel-cmdline change, no rebuild. **The user had
already tried holding Fn too, before this landed, and it didn't help
either** - so whatever's blocking the VT switch isn't (solely) about
which virtual keycode the F9 press produces. Left the `fnmode=2` change
in place regardless (harmless, plausibly still useful), but it isn't
the fix by itself. Not further investigated this session - genuinely
unresolved.

## Ruled out: the tty1 shell exit is not a crash

Went back and grepped the original shell-exit boot's *entire* journal
for kernel-level crash signatures - `segfault`, `coredump`, `signal`,
`killed`, `oops`, `BUG`, `general protection` - **nothing**. The shell
exits cleanly (a voluntary `exit()`, not a signal/crash), just within
about a second. Read `/etc/profile` and the NixOS-generated
`set-environment` file in full for anything that does a conditional
`exit`/`return` based on a check this custom boot might fail
differently from the normal system (hardware probes, `/proc`/`/sys`
checks, kernel-version gates) - found nothing suspicious; this is
completely standard generated NixOS shell-environment code, unchanged
from what works fine on the normal 7.2.7 boot. The actual cause remains
unidentified.

## User's steer: stop stacking bypasses, get the real thing working

The user explicitly asked for normal login or the graphical desktop to
work, not another workaround layered on top of `multi-user.target`.
Correct call: notes/95's `systemd.unit=multi-user.target` override was
originally chosen as "extra margin" specifically *because* GDM's
prerequisite (working keyboard/mouse input) wasn't confirmed working
yet at that point (notes/95's own boot never got far enough to test
GDM directly, it never had a chance - no input at all). **That
blocker is now resolved** - notes/95's journal already showed
`systemd-logind: Watching system buttons on /dev/input/event0 (Apple
Inc. Apple Internal Keyboard / Trackpad)`, i.e. the fix that mattered
for GDM was already confirmed working, just never actually tested
under `graphical.target` itself.

**Pivoted back to the real default target** - removed
`systemd.unit=multi-user.target` entirely, letting the kernel boot
normally into `graphical.target`/GDM, same as any ordinary boot.
Kept the fallbacks (`systemd.wants=getty@tty1.service`,
`systemd.debug-shell=1`, the `fnmode=2` fix) in case GDM itself doesn't
come up cleanly, but the primary path is now the one the user actually
wants tested.

## Current state at session end

Boot entry updated in place again (same `bzImage`, commit
`60b8d4d49281`, kernel command line changed to drop the `multi-user`
override), one-shot re-armed. `tools/bisect_build.sh`'s template and
header comment updated to match - default to graphical, keep the same
fallback flags. Sixth attempt at the same commit pending. Two genuinely
open mysteries remain, neither blocking the next attempt: why
`Ctrl+Alt+F9` doesn't switch VTs on this hardware even with `fnmode`
addressed, and why the tty1 text-login shell exits cleanly and quickly
- both worth real investigation later if `graphical.target` also
doesn't pan out, but not chased further this session in favor of
trying the more direct path the user asked for.

## Next steps

Reboot into the (now graphical-default) one-shot entry. If GDM comes up
and login works normally: proceed with the bisect test from there
(a terminal inside the graphical session is enough - `load.sh`,
`connect_test.sh`, `dmesg`). If GDM *also* fails in some way: that's
new information worth its own diagnosis, distinct from the earlier
text-console-specific findings. If the tty1 fallback shows the same
clean-shell-exit symptom under GDM's absence: that would suggest the
cause is more fundamental than either display path specifically.
