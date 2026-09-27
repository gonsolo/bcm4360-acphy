# Status 2026-09-27: applied real-trace corrections to the TX-cal measurement - three real bugs found and fixed, still flat

Follow-up to notes/19. With `wl`'s hardware capability now proven (a
sustained ping test), the natural next step was comparing what `wl`
actually does during a real calibration pass against what this port's
port of `FUN_001ac9b6` guessed. Captured `wl`'s full register-access
sequence live during a real association
(`traces/wl-init-20260927-184726.trace`, via the already-proven
`trace_wl.sh` - kept wl loaded and bound throughout, only bounced the
netdev up/down, never touched the PCI binding) and diffed it
line-by-line against this port's `b43_phy_ac_txcal_*` code.

## Three real, concrete bugs found and fixed

1. **Wrong outer-sample candidate table.** wl's first `0x380` trigger
   write was `0x8434` (outer sample `0x434`), not `0x8423`. That's
   `local_d8` (`FUN_001ac9b6`'s `param_2=='\0'` branch), not `local_e8`
   (`param_2!='\0'`) as this project had guessed two rounds ago - i.e.
   wl's real call here has `local_51` (`param_2`) `== 0`, not `1`. Fixed
   `b43_phy_ac_txcal_measure_candidates`/`_sweep` to use the correct
   table: `{0x434, 0x334, 0x84, 0x267, 0x56, 0x234}`.
2. **Missing register write.** wl writes PHY reg `0x382 = 0x8a09` once,
   between the gain-table override and the tone-generation start
   (`FUN_001ac9b6` line 609 - present in the decompiled source all
   along, just never carried into the port). Added it right after
   `b43_phy_ac_txcal_save_gaintbl()` in every test that calls it.
3. **`save_gaintbl` never actually overrode table 0xC.** This was a
   real gap, not the "no-op self-value" simplification it was thought
   to be: it saved table 0xC's old value for later restore, but the
   function that's supposed to write a *new* calibration value there
   (`FUN_0019d224`, called from `FUN_0019d3ac`) was never implemented.
   The real trace gave the exact values for our 2-core board: table 7
   per core `{0xff00, 0x47ff, 0xa7}` (core 0) / `{0xff00, 0x27ff, 0xa7}`
   (core 1), table 0xC per core `0x41` (core 0) / `0x40` (core 1),
   written to *both* of table 0xC's paired offsets (confirmed identical
   in the trace, matching `FUN_0019d224.c` writing the same source
   value to both `_off` and `_off2`). Extended `new_gain` to carry a
   4th value per core and added the missing table-0xC write.

Everything else this project had already derived - the `0x381=0x7976`
value, the table-0xC clear-writes at offsets `0x43`/`0x44`, the
candidate byte `0x3d`, the `0x461`/`0x462`/`0x463` tone-trigger values,
the `0x144`/bit-2 register and bit semantics - matched the real trace
exactly, byte for byte. That's a real, independent validation of the
bulk of this project's decompiled-source-derived work, not just of the
three fixes above.

## Result with all three fixes applied

Rebuilt, swapped to `b43` (fresh swap this boot, `wl` had been running
normally beforehand per notes/19), ran `ac_txcal_candidate_test6` (the
full flow: loopback, per-core setup, classifier switch, settle pulse,
corrected gain override, the `0x382` write, sustained tone, full
36-combination candidate sweep, real resetcca cleanup). No instability,
0% packet loss on the backup link throughout, clean load/unload.

**`radio 0x144` is still bit-2-clear for every combination, exactly as
before every one of these fixes.** Not a single reading differed from
the pre-fix state.

## What this means

This is real, verified progress - three concrete, trace-confirmed bugs
fixed, not guesses - but it means there is **at least one more gap**
beyond these three. Candidates, roughly in order of suspicion:

1. **The large per-core PHY register setup block
   (`b43_phy_ac_txcal_measure_setup_enter`) may still have an error.**
   It was hand-verified against the decompiled arithmetic (bit-exact
   round-trip, matching hand-computed values for 0x735/0x73a/0x720),
   but that only checked its own internal consistency, not against a
   real trace the way the fixes above were. This is the next thing to
   diff against `wl-init-20260927-184726.trace` line by line.
2. Some other precondition state established earlier in `wl`'s real
   attach/association sequence (before the calibration pass even
   starts) that this port's `ac_por` replay doesn't cover, and that
   this specific measurement quietly depends on.
3. A remaining misunderstanding of `radio 0x144`'s exact semantics -
   less likely now, given the bit-2 interpretation held up exactly
   against the real trace (bit 2 clear on the very first candidate,
   matching wl's own break condition), but not entirely ruled out.

## Note on timing

Initially thought the real trace's ~637us busy-poll (before the bit
cleared) versus this port's apparently-instant completion was a smoking
gun for "no real measurement is happening" - but re-checking this
port's own dmesg timestamps shows ~950us between consecutive candidate
log lines, comparable to or longer than wl's observed poll duration.
`b43info`/printk overhead likely dominates this port's own timing
signal, so it cannot presently be used to distinguish "real hardware
settling time" from "logging overhead." Not a reliable signal either
way - the actual comparator *value* (flat `0x0000` vs wl's observed
`0x0003`) remains the only solid piece of evidence.

## Next step

Diff the per-core setup block's real register sequence
(`0x720`-`0x73e`/`0x920`-`0x93e`, `0x400`/`0x401`, and anything else `wl`
touches between entering loopback mode and starting the tone) against
`wl-init-20260927-184726.trace` line by line, the same way this round's
three fixes were found - narrower and more promising than further
guessing, since the trace data already exists and covers exactly this
window.
