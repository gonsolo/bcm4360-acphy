# Status 2026-09-29 (part 21): fourth bisect boot - login itself
succeeds, but the shell exits within about a second with no
journal-visible error; staged `systemd.debug-shell` as a PAM/login-
independent fallback rather than keep guessing blind

Direct continuation of notes/96, same day. The `getty@tty1` fix
worked - a real login prompt appeared. The user reported entering
username and password produced a brief on-screen error (too fast to
read) and returned to the login prompt.

## What the journal actually shows: authentication succeeds, the shell doesn't survive

`journalctl -b -1` (`journalctl --since`/`--until` narrowed to the
exact login window) shows, for the *first* login attempt:

```
login[490]: pam_unix(login:session): session opened for user gonsolo(uid=1000) by LOGIN(uid=0)
systemd-logind[363]: New session '1' of user 'gonsolo' ...
(systemd)[509]: pam_unix(systemd-user:session): session opened ...
... [484ms of completely normal systemd --user startup: D-Bus, GCR
     ssh-agent, NixOS user activation, "Reached target Main User
     Target", "Startup finished in 484ms"] ...
login[490]: gkr-pam: gnome-keyring-daemon started properly and unlocked keyring
login[490]: pam_unix(login:session): session closed for user gonsolo
systemd[1]: getty@tty1.service: ... Scheduled restart job ...
```

**Authentication genuinely succeeded** - this isn't a wrong-password
problem (a *second* identical attempt shows the exact same
open-then-close pattern; only a *third*, later attempt shows a real
`pam_unix(login:auth): authentication failure`, almost certainly the
user retyping out of confusion after the first two silently failed).
The user-level `systemd --user` instance starts completely cleanly.
Then the **login session closes within about a second**, with nothing
in the systemd journal explaining why - `login`'s own child process
(the shell) must be exiting almost immediately, and its output would
have gone straight to the physical console, not the journal - matching
the user's "brief on-screen error, too fast to read."

## Investigated, didn't find a smoking gun

Checked `/etc/bashrc`/`/etc/profile` for anything that might crash on a
kernel this reduced (virtualization/`/dev/kvm` checks, hardware feature
probes) - nothing obviously suspect, this is standard generated NixOS
output, same as the working 7.2.7 system. `gnome-keyring-daemon
started properly and unlocked keyring` suggests that part completed
fine too. Without direct access to the console's actual output (it
flashed and vanished), further static guessing didn't seem productive.

## Staged instead: `systemd.debug-shell=1`

A standard, well-documented systemd kernel parameter: spawns an
**unauthenticated root shell on tty9** (`Ctrl+Alt+F9`), independent of
PAM, `login`, `getty`, and the normal user shell/profile chain
entirely - `systemd-debug-generator` sets it up directly under PID 1.
Added to the boot entry (pure kernel-cmdline change, no rebuild)
alongside the existing `systemd.wants=getty@tty1.service`. If tty1's
login misbehaves again, tty9 should still give a working shell to
actually diagnose (and unblock) this from inside the running system,
rather than continuing to guess from outside it. `tools/bisect_build.sh`
updated with the same flag for every future step.

## Current state at session end

Boot entry updated in place again (same `bzImage`, commit
`60b8d4d49281`, only the kernel command line changed), one-shot
re-armed. Fifth attempt at the same commit pending; the bisect test
itself still hasn't run once. Four independent boot-environment
problems found and fixed in sequence now (storage/vfat notes/94,
input/HID notes/95, getty/login-prompt notes/96, and now this
shell-exits-instantly one - not yet actually root-caused, only worked
around with a fallback path).

## Next steps

If `Ctrl+Alt+F9` gives a working root shell: use it to actually
diagnose the tty1 shell-exit (run the login shell manually, e.g. `su -
gonsolo` or inspect `/var/log`/dmesg from there) *and* to just proceed
with the bisect test directly as root, sidestepping the tty1 problem
entirely rather than insisting on fixing it first - `load.sh`/
`connect_test.sh` don't need a specific user, only working commands.
If tty9 *also* doesn't work, that would be a much bigger, different
signal (something wrong with debug-shell/tty allocation itself) worth
its own investigation. Otherwise, proceed as before: run
`bash ~/bcm4360-acphy/bisect-boot/load.sh`, confirm `wlp3s0b1`, run the
`connect_test.sh`/`suspendtiming` pass/fail check, `git bisect good`/
`bad`, next candidate via `tools/bisect_build.sh`.
