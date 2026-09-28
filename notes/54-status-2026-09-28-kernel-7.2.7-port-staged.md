# Status 2026-09-28 (cont'd): b43-src ported to kernel 7.2.7, staged for a reboot test

User asked to switch to the latest kernel in this nixpkgs channel (7.2.7,
not the 7.2.8 they initially named - that version isn't in this channel).
Explicit instruction: skip `wl` entirely, just port `b43-src`.

## b43-src compiles clean against 7.2.7, no code changes

Fetched `linuxKernel.packages.linux_7_2.kernel.dev` (cached, no kernel
build needed) and built with `KDIR` pointed at its headers instead of the
running 6.18.53 kernel's. Zero errors, zero warnings from our code, across
a 6.18 -> 7.2 jump. Vermagic on the result: `7.2.7 SMP preempt mod_unload`.
This only proves it compiles - runtime behavior on 7.2.7 is unverified
until it's actually loaded there.

Saved as `b43-src/b43-7.2.7.ko` (gitignored, like all `.ko` builds) so it
survives a future `make` for 6.18.53 overwriting the default `b43.ko`.
Staged as the active `b43.ko` right before this note, ready to load once
booted into 7.2.7 (loading it now, on 6.18.53, would fail on vermagic).

## wl does NOT compile on 7.2.7 - and, per instruction, isn't needed

First `nixos-rebuild boot` attempt left the existing
`boot.kernelModules = [ "wl" ]` / `boot.extraModulePackages` declarations
in place, thinking a working fallback was a free bonus. It wasn't free:
`wl`'s source fails on this kernel/toolchain combination -
`src/shared/linux_osl.c` calls `strncpy()` without including `<string.h>`,
which a newer GCC now treats as a hard error
(`implicit declaration of function 'strncpy'`), not a mainline API
change. Since `boot.extraModulePackages` is a hard dependency of the
system closure, this failure blocked the *entire* generation, including
the (already-working) kernel + b43-src pieces. Removed both lines and the
matching `permittedInsecurePackages` entry per the user's explicit
correction; the rebuild then succeeded immediately (cached, no rebuild
of anything else needed).

**Consequence**: generation 11 (kernel 7.2.7) has no driver at all for the
internal WiFi chip at boot - `b43` stays blacklisted from auto-load (as
always) and `wl` isn't present. The chip sits idle until `b43_live.sh
swap` + `load` claims it manually, same workflow as every other test
this project has ever done.

## Current state

- Boot menu: generation 11 (`b43dev`, Linux 7.2.7) is the new default.
  6-10 (Linux 6.18.53) remain, selectable from the menu.
- Currently running: still generation 9 (6.18.53), completely untouched -
  no reboot has happened yet.
- `b43-src/b43.ko` is now the 7.2.7 build; `b43-src/b43-7.2.7.ko` is a
  copy of the same, kept for reference across future `make` runs.
- `tools/test_7.2.7.sh` - one-shot post-reboot script: verifies the
  kernel actually is 7.2.7, checks the USB backup link, sets panic
  sysctls, runs `postboot.sh`, then `swap` + `load` with the standard
  params, and prints the next manual steps (bring the interface to
  managed mode, connect).

## Why this wasn't tested live tonight

Rebooting ends the current Claude Code session (it runs as a process on
this machine) - there's a hard boundary between "kernel switch prepared"
and "kernel switch tested" that requires either the user to run the
reboot + `tools/test_7.2.7.sh` themselves, or a fresh session to pick this
up afterward. Everything above is staged so that either path is just:
reboot, pick the 7.2.7 entry (it's default, so no menu interaction is
even needed), run `tools/test_7.2.7.sh`.

## Next steps

1. Reboot into generation 11, run `tools/test_7.2.7.sh`, then the
   standard managed-mode + `nmcli connection up b43-test` sequence.
2. If it works: this is a much bigger milestone than tonight's channel
   fixes - a live confirmation that b43-src's mac80211/DMA assumptions
   hold across a major kernel version jump.
3. If it doesn't: the boot menu still has 6-10 (6.18.53, known-working)
   as an immediate, tested fallback - just reboot again and pick one.
4. `wl` on 7.2.7 is a separate, real (if minor-looking) upstream/nixpkgs
   packaging bug - not pursued further per the user's instruction, but
   worth knowing it exists if `wl` is ever needed on this kernel again.
