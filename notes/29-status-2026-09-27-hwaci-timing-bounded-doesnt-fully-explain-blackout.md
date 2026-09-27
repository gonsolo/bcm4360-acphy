# Status 2026-09-27 (late evening, continued yet further): traced the hwaci-engine MAC-suspend cycle's actual timing - it's bounded and too fast to fully explain the blackout

Direct follow-up to notes/28, same evening, continuing the decompilation
thread. Read-only Ghidra work only - no hardware touched, no source
changes. Set out to find out exactly how long `wlc_phy_hwaci_engine_acphy`'s
MAC-suspend window (notes/28's leading candidate for the RX blackout)
could plausibly take, by decompiling everything in its call chain.

## Setup note: decompiling call targets with no existing Function boundary

Two calls inside `wlc_phy_hwaci_engine_acphy` (`func_0x0019a60c(param_1,1)`/
`func_0x0019a60c(param_1,2)` and `func_0x0019173d(param_1)`) had no
Ghidra Function object at their address - `decompile_named.java`'s
address lookup (`getFunctionAt`) returned null for both, since with
`-noanalysis` Ghidra doesn't automatically create function boundaries at
addresses only ever seen as call targets. Wrote a small new script,
`decompile_at_addr.java` (same pattern as `decompile_named.java`, but
calls `createFunction()` first if no function exists yet at the given
address) - a standard, safe, additive Ghidra analysis action, not a
destructive one. Worked immediately; both resolved to real functions
(`FUN_0019a60c`, `FUN_0019173d`).

## What `wlc_phy_hwaci_engine_acphy` actually does inside the suspended window

Read the full 223-line function (only partially scanned in notes/28).
Structure, in order, between `wlapi_suspend_mac_and_wait()` and
`wlapi_enable_mac()`:

1. Up to ~12-16 `phy_reg_read()` calls (per-core noise/ACI measurement
   registers, three iterations of up to 4 reads each) - only when a
   specific averaging flag is set.
2. Occasionally 4 more `phy_reg_read()`s plus a small lookup-table
   comparison, to decide whether the desense level needs to change.
3. Bookkeeping/hysteresis arithmetic - pure memory, no register access.
4. If the desense level actually changed: 2 `phy_reg_write()` calls.
5. If a larger state transition occurred: read PHY reg `0x19e`, set 2
   bits, call `FUN_0019173d()` (decompiled - pure in-memory arithmetic,
   nine byte comparisons, no register access at all), call
   `FUN_0019a60c(param_1,1)` then `FUN_0019a60c(param_1,2)` (each
   decompiled - builds a small local table and makes exactly one
   `wlc_phy_table_write_acphy()` call, ~7-8 entries, 8-bit width),
   restore reg `0x19e`, then the small `wlc_phy_aci_updsts_acphy()`
   status notifier (also already decompiled, one boolean check plus one
   notification call).

**None of this involves a delay, a poll loop, or a large data transfer.**
Even in the worst case (every conditional branch taken), this is on the
order of two or three dozen individual MMIO reads/writes - each a
microsecond-scale PCI-attached register access, not milliseconds. This
whole block should complete in well under a millisecond on real
hardware, not hundreds of milliseconds.

## The MAC-suspend/enable wrapper chain, fully traced - bounded at ~83 ms worst case

Decompiled the full chain: `wlapi_suspend_mac_and_wait` ->
`wlc_bmac_suspend_mac_and_wait`, and `wlapi_enable_mac` (already known
from notes/28) -> `wlc_bmac_enable_mac`, plus the shared helper
`wlc_bmac_mctrl` they both call.

- `wlc_bmac_mctrl`: a plain masked register write, no delay.
- `wlc_bmac_enable_mac`: a handful of register reads/writes and one GPIO
  control call, no delay/poll loop at all - fast and unconditional.
- `wlc_bmac_suspend_mac_and_wait`: **has exactly one bounded poll loop**,
  waiting for the MAC to acknowledge suspension: starts a countdown at
  `0x14441` (83,009), decrementing by 10 and calling `osl_delay(10)`
  (presumably microseconds) each iteration until either the
  acknowledgment bit is seen or the countdown reaches 9. Worst case,
  that's roughly 8,300 iterations x 10 us = **~83 ms maximum**, not
  unbounded - and only reached if the MAC is unusually slow to
  acknowledge suspend, which should be rare in normal operation.

## Conclusion: this mechanism can only partly, and only occasionally, explain the blackout

Putting both halves together: **the entire `wlc_phy_hwaci_engine_acphy`
suspend-work-resume cycle is bounded at roughly 85-90 ms in the
worst case**, and should typically complete far faster than that. This
can plausibly account for some of the *shorter* observed blackout
instances from notes/26 (34.6 ms, 40.4 ms, 60.8 ms all fit comfortably;
even 150-180 ms is in a plausible range allowing for some scheduling/
measurement slop), **but it cannot, on its own, explain the longer
instances** (457 ms, and the several trials that showed no reception at
all within a 2.5 s window). Revising notes/28's framing: this remains a
real, concretely-identified, structurally-relevant mechanism (a genuine
MAC-suspend cycle, running on the right ~1.024 s cadence, for the right
chip type), but it is very unlikely to be the *complete* explanation for
the RX blackout's full observed range. Something else - possibly firmware/
ucode-side, possibly `wlc_bmac_watchdog`'s still-unresolved indirect
calls (flagged in notes/27/28), possibly unrelated entirely - must
account for the longer tail.

## Next steps for a future session

1. Resolve `wlc_bmac_watchdog`'s two remaining indirect/vtable calls
   (`(**(code**)(**(long**)(lVar1+0x20)+0xd8))()` and a conditional
   second one) - these were never decompiled because they're
   function-pointer calls, not resolvable by static analysis alone;
   may need to inspect the actual vtable contents at a known offset, or
   trace live call targets via `wl`'s own execution (e.g. `uprobe`s on
   candidate addresses during a `trace_wl.sh`-style capture).
2. Directly and precisely measure real reception during one of `wl`'s
   own ~1.024 s cycles (still not done - notes/27/28's open item), now
   with a sharper prediction to test against: if the *real* cause is
   `wlc_phy_hwaci_engine_acphy`, wl's own blackout (if any) should be
   short (tens of ms), not hundreds-to-thousands; if wl shows a longer
   gap too, that points away from this mechanism and toward something
   else still unidentified.
3. `wlc_phy_desense_aci_engine_acphy` (278 lines, previously only
   grep-scanned in notes/28, not read in full) hasn't been fully read
   line by line yet - worth a full read given it's the *other*
   AC-PHY-specific watchdog call, in case it has a slower path not
   caught by the earlier grep-for-calls scan.
4. Any actual porting decision should wait until the real cause (or at
   least a stronger, better-bounded candidate) is identified - still a
   materially different risk category needing the user present.
5. Loft-comp calibration question (notes/22) remains fully open and
   untouched.

## Session close

No hardware touched - static Ghidra analysis only, using the existing
extracted `wl.ko` binary and the already-reopened `AcphyProj` project
(notes/28). One new, small, reusable script added
(`decompile_at_addr.java`) alongside the existing `decompile_*.java`
scripts. No `b43-src` changes.
