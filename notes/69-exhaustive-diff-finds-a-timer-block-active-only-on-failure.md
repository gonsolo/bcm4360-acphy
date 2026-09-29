# Exhaustive live diff: a real timer-computation block, active only on failure

Direct follow-up to notes/68, same session. Built the exhaustive-diff
method notes/68 proposed as the next step (closer to what found the real
HOSTF2/HOSTF3 bug, notes/62, than targeted register guessing).

## Tooling: full_snapshot.c, and a real bug in it caught before trusting results

`tools/full_snapshot.c`: dumps all of SHM (4096 words) + IHR (0-0x39F)
in ~46ms (vs. the shell loop's ~45s - fast enough to bracket a real
event, not just steady state). First version had a real addressing bug:
passed a raw incrementing integer as the SHM debugfs address, but
`b43_shm_read16`'s SHARED-routing path internally divides non-word-
aligned addresses by 4 (its own 32-bit-access optimization) - so 3 out
of every 4 "SHM" entries silently aliased onto the same underlying
register under different fake labels. Caught by noticing suspicious
identical-triplet patterns in an early diff (`SHM 00FD/00FE/00FF` all
showing the same transition) before drawing any conclusion from it -
fixed to pass byte offsets (word*2), matching the already-validated
convention from notes/62's real wl trace cross-check. The IHR side was
never affected (`B43_SHM_HW` routing has no such scaling).

## Method

Burst-capture full snapshots (~140-220 per attempt) through real
connect attempts, index by converting each snapshot's epoch timestamp to
boot-monotonic (`/proc/uptime` offset) so they align with `journalctl
-o short-monotonic`'s real auth-event timestamps. Pick the snapshot
immediately before and immediately after the real event (auth timeout,
or "associated"), diff word-by-word, then compare the failure-diff set
against the success-diff set.

## Result: a real, correctly-addressed, novel signal

Bulk of both diffs (215 words changed across a success, 75 across a
failure) is downstream cascade - expected, since the success window
necessarily captures the chip going from idle to actively processing a
real association (AID assignment, rate tables, etc.), not a narrow
cause. But one specific block stands out in the "changed during failure,
NOT during success" list: `IHR[0x150]` through `IHR[0x159]` (minus
0x154, which is the PC register already used all night for something
else) - a genuinely tight, contiguous, real cluster.

Traced it in the disassembly (`0x0EC0-0x0F30`): a real routine doing
actual multi-word arithmetic (`MUL`/`ADDC`/`SUBC`/`SUBS`, not just flag
ORs) against a 32-bit free-running hardware timer (`IHR[0x119]`/
`IHR[0x11A]` - consistent with every capture tonight showing IHR[0x119]
at a different, large value each time). Computes an elapsed-time-based
value, loops, and reaches **a second NAP instruction at `0x0F2E`**
(distinct from the one at `0x000F` this whole investigation has centered
on) - with a real "sleep, wake, check `IHR[0x150]`, loop back and sleep
again if not done" structure (`0x0F2F`-`0x0F30`) matching the *shape* of
notes/60's original observation almost exactly.

## Important: this is NOT the already-characterized NAP - checked, not assumed

Before drawing any conclusion, checked whether `0x0F2E` ever appears in
any of tonight's many PC samples (`pc_onetry.txt`, `pc_hf.txt`,
`pc_irqextra.txt`, `pc_hf1.txt`, the fast sampler's output) - **zero
hits, everywhere.** The long naps observed and fixed-for tonight
(notes/60-62) are confirmed, repeatedly, to happen at `0x000F`, never
`0x0F2E`. So this is a real, separate, previously-unexamined mechanism -
its live SHM/IHR footprint changes specifically when attempts fail, but
it is not (at least not directly, not yet shown) the site of the
sleep behavior already fixed.

## What this plausibly is

The real, wl-documented periodic watchdog/recalibration timer this
project's own `phy_ac.c` comment (near `pwork_15sec`) has flagged as
missing since notes/27-31/34: "wl runs a real periodic watchdog
(wlc_bmac_watchdog/wlc_phy_watchdog) that this port has never had an
equivalent for... ~1.024s cycle doing DMA-error recovery and PHY/ACI
recalibration." A ucode-side timer computation block that only shows
real activity during failures is consistent with a recalibration/
recovery routine correctly detecting something is wrong and trying to
respond - or with a genuine bug in that response.

## Honest status, not yet resolved

Real, novel, correctly-addressed, live-verified finding - not yet
understood. Open questions for whoever continues: what gates entry to
`0xEC0` (the checks on `IHR[0x47]`/`SCR[0x14]` at `0xEC0`-`0xEC1`); what
the computed value actually represents (a recalibration interval? a
retry backoff?); and whether its behavior differing between success and
failure is cause, effect, or coincidence - the same causal-direction
question that turned the earlier `ihr97`/`0x0d74` lead (notes/68) out to
be a pure effect. Needs the same tight timing-correlation treatment
before trusting it as more than "real and worth investigating."
