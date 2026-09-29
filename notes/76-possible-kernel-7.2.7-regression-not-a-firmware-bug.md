# Possible major redirect: kernel 7.2.7 regression, not necessarily a firmware/ucode bug

Direct follow-up to notes/75's process correction, same session. Having
just learned the lesson "check what's already been tried," did exactly
that more thoroughly - listed the full `notes/` directory - and found
something that could redirect this entire night's investigation.

## notes/45-49 (2026-09-28, before the 7.2.7 port): fully reliable

With the SHM 0x7C POR fix (`{1, 0x007c, 0x0320}`, still present
unchanged in `phy_ac_por.h` right now), this exact driver code achieved
**4/4, then 5/5, clean first-try connections** (notes/47, notes/49),
loaded via the proven manual sequence (`b43_live.sh swap` + `load`) on
the *original* kernel (6.18.53) - before the 7.2.7 port (notes/54,
later the same day) existed at all.

## Direct test tonight: the same proven sequence, on 7.2.7, fails

Reloaded b43 via the exact proven sequence (not `tools/b43_boot.sh`,
the new auto-load script written tonight - the original `b43_live.sh`)
on the current kernel (7.2.7, generation 16). Result: **0/5** connect
attempts succeeded, with 29 `MAC suspend failed` events across the 5
tries - the identical failure signature as every other test tonight.

This rules out `b43_boot.sh`'s bring-up sequence as the regression
cause (same proven script, still fails) and points at something that
changed between kernel 6.18.53 and 7.2.7 - or at the generation itself
(possible userspace package version differences bundled with the
generation bump, not isolated from the kernel change - an honest
confound not yet ruled out).

## What this would mean if confirmed

Everything from notes/56 through notes/75 tonight - the NAP mechanism,
HOSTF2/HOSTF3, the d11emu ground-truth harness, the live hardware
timing tools, the watchdog/desense-engine chain - is real, verified
work, but if the *actual* difference between "4/4 reliable" and "30-40%
unreliable" is a kernel-version regression, none of it may be the
proximate cause of tonight's specific reliability drop. It could still
be that b43's real reliability has *two* problems (a genuine port gap,
AND a kernel-7.2.7-specific regression on top), but the clean 4/4→0/5
swing with identical code strongly suggests the kernel change is doing
real, first-order damage on its own.

## Verification in progress

Staged generation 10 (6.18.53, the last pre-7.2.7-port generation) as a
one-time next boot (`bootctl set-oneshot`) to directly re-test whether
the SAME driver code, SAME proven load sequence, is *still* reliable on
the original kernel *right now* - ruling out that something in the
physical RF environment (not the kernel) drifted since notes/47/49 were
written and is the real explanation instead.

**Not yet completed - needs the reboot, which the user carries out.**
If gen 10 is still reliable: strong confirmation this is a genuine
7.2.7-kernel regression, and the real next step is bisecting what
changed in the kernel (or its config) between the two versions that
would affect USB/PCIe/interrupt timing or mac80211/cfg80211 internals -
a completely different, more tractable investigation than firmware
internals. If gen 10 has *also* degraded: points back toward something
environmental (RF conditions, or a real hardware-condition change), and
tonight's firmware-level work remains the most relevant thread.
