# Status 2026-09-27 (late evening, continued yet further still): correction - the periodic sweep is NOT the same code as the ported TX-cal candidate search

Direct follow-up to notes/30, same evening, per explicit user instruction
("keep going, compare the sweep against the ported code"). Doing that
comparison rigorously - register by register, against the actual C code,
not from memory - overturns notes/30's central claim. This note exists to
correct the record honestly rather than let an overstated claim stand.

## What notes/30 claimed, and why it doesn't hold up

Notes/30 said the periodic sweep's per-core PHY setup block touches
"exactly the register set this project already knows and has already
ported" (`b43_phy_ac_txcal_measure_setup_enter`), and that its repeated
comparator loop is "structurally identical... to this project's own
already-ported candidate measurement sweep." Both claims were made from
a quick visual pattern-match (same rough shape: per-core, read-then-
write, repeated sampling) without actually diffing the register lists or
checking the comparator/trigger registers against the real ported code.
Doing that properly now:

## PHY setup block: substantial overlap, but not a match

Precisely extracted the full set of PHY registers touched in the trace's
per-core setup window and compared against `b43_phy_ac_txcal_measure_setup_enter`'s
actual register list in `phy_ac.c`:

- **In both**: `0x720, 0x721, 0x724, 0x725, 0x727, 0x728, 0x729, 0x736,
  0x739, 0x73a, 0x73c, 0x73e` (12 registers)
- **In the ported code, not touched in this trace window**: `0x723,
  0x735, 0x737, 0x738`
- **Touched in the trace, not in the ported code's list at all**:
  `0x722, 0x734`

More importantly than the register *set*: `measure_setup_enter` performs
over 50 individual mask/set/write operations per core (multiple separate
`b43_phy_set`/`b43_phy_mask`/`b43_phy_maskset` calls against many of
these registers). The trace's actual per-core window shows roughly 14
distinct registers touched with about 28 total read/write events per
core - a much shorter, simpler sequence. This is not the same function
executing; at best it's a different, lighter-weight routine that happens
to operate on an overlapping subset of the same PHY register cluster
(plausibly a general "per-core gain/control" register block used by more
than one calibration-adjacent routine on this chip, not exclusively by
TX-loft calibration).

## Radio "loopback-like" entry: essentially no overlap

Precisely extracted the RADIO registers touched in the trace's per-core
radio-mode window and compared against `b43_phy_ac_txcal_enter_loopback`/
`read_radiosave`'s actual register list:

- Ported code touches: `0x1a, 0x1b, 0x1c, 0x1e, 0x1f, 0x24, 0x170`
- Trace touches (core 0): `0xe, 0x17, 0x24, 0x25, 0x15f, 0x161, 0x16e`
- **Overlap: only `0x24`**, out of 7 ported / 7 trace registers.

This is not the same radio-mode-entry code. The trace's real activity
here is a genuinely different register set.

## Comparator and trigger: also different

`b43_phy_ac_txcal_measure_candidates_outer` (the ported candidate-search
core) writes PHY table `0xC` (offsets `0x43`/`0x44`), PHY reg `0x381 =
0x7976`, PHY reg `899` (candidate byte), triggers via PHY reg `0x380`,
and reads back the result from **radio register `0x144`**. None of
`0x380`, `0x381`, `899`, or radio `0x144` appear anywhere in the trace's
repeated-sampling window. The trace instead repeatedly reads **PHY
register `0x0013`**, with no visible trigger-write beforehand - a
different comparator, and seemingly a different (or absent) triggering
mechanism, not a variant of the same measurement.

## Conclusion

**The periodic watchdog sweep found in notes/30 is not the ported
TX-loft-calibration candidate-search code, and is not simply a
"steady-state version" of it.** It's a separate, still-unidentified
routine (most likely one of `wlc_bmac_watchdog`'s two unresolved
indirect/vtable calls, per notes/27-29) that happens to share a rough
structural shape (per-core setup, per-core radio-state change, repeated
sampling, full restore) and a partially-overlapping PHY register range
with the TX-cal work, but uses different radio registers, a different
comparator, and a different (or no) trigger mechanism. Checked whether it
might be hiding inside `wlc_phy_desense_aci_engine_acphy` (the other
AC-PHY watchdog call, previously only grep-scanned for `wlc_phy_`/
`wlapi_`/`osl_`-prefixed calls in notes/28) in case that grep missed
lowercase `phy_reg_read`/`_write`/`_mod` calls - it doesn't: zero matches
for those calls or for any of the `0x720`-`0x73e` register range in that
function's decompiled source.

**This means notes/30's practical suggestion - that this sweep gives a
new angle for comparing against the stalled TX-calibration work - does
not hold.** They are different code paths. The sweep remains a real,
novel, precisely-measured (~1.1-1.3 ms) finding in its own right (still
too short to explain the RX blackout's longer instances, per notes/29),
but it is not evidence about, and should not be used to reason about,
the TX-loft-calibration candidate-search port specifically.

## Next steps for a future session

1. The sweep's actual identity is still open. Given it's neither
   `wlc_phy_hwaci_engine_acphy`'s decompiled body (notes/28/29, confirmed
   too simple/fast to match) nor `wlc_phy_desense_aci_engine_acphy`
   (confirmed above, no matching register access at all), it is most
   likely one of `wlc_bmac_watchdog`'s two unresolved indirect/vtable
   calls - still not identified by name. Static resolution isn't
   possible (function-pointer calls); live kprobe tracing of
   `wlc_bmac_watchdog` itself isn't possible either (confirmed
   not-traceable, notes/30). The remaining option is inspecting the
   vtable's actual data contents (if statically located) or accepting
   this as characterized-by-behavior-only.
2. If precise identification matters less than behavior, the more
   productive path may be: sample several more of these cycles from the
   trace to build a complete, exact register+value sequence (this note
   only characterized register *sets*, not the full value-level detail
   for the radio/comparator portions), which could still be useful
   reference data even without a function name attached.
3. Loft-comp calibration question (notes/22) remains fully open and
   untouched.

## Session close

No hardware touched - this was register-set analysis of the
already-captured trace against the existing `phy_ac.c` source, both
already on disk. No `b43-src` changes.
