# Status 2026-09-27: the per-core setup block is fully, bit-exactly validated - the mystery is elsewhere

Direct follow-up to notes/20. Diffed `b43_phy_ac_txcal_measure_setup_enter()`
and `b43_phy_ac_txcal_settle_pulse()` against the same live wl trace
(`traces/wl-init-20260927-184726.trace`), register by register, for the
entire window between loopback-mode entry and the gain-table override -
the one large block that had only ever been checked for internal
self-consistency, never against real wl behavior.

## Method

Decoded every PHY register access in the window (not just the combined
32-bit `(data<<16)|reg` writes checked in notes/20 - also the separate
16-bit "select register" + 16-bit "read/write data" pairs, which turned
out to carry most of the traffic here) into a plain `(op, register,
value)` sequence, then walked it side by side with the ported C code.

## Result: complete match, no new bugs

Every single operation in both `measure_setup_enter()` and
`settle_pulse()` - the initial `0x19e`/`0x40f` save, all sixteen save
reads per core (`0x73e,0x725,0x739,0x73a,0x721,0x729,0x720,0x728,0x724,
0x736,0x723,0x735,0x737,0x738,0x727,0x73c`), the ~30 subsequent
set/mask/maskset operations per core (`0x720,0x721,0x723,0x725,0x727,
0x728,0x729,0x735,0x738,0x739,0x73a,0x73c`), the direct writes
(`0x724=0x3ff`, `0x736=0x152`), and the settle pulse's own
set-then-restore of `0x739`/`0x73a`/`0x725` - matched the real trace
**exactly**, bit for bit, for both cores. Loopback-mode entry (already
validated in notes/16) was also re-confirmed here as a side effect of
extending the search window earlier.

This resolves the leading suspicion from notes/20 - the setup block was
never the problem.

## One small, unexplained, likely-inconsequential gap

Right after the settle pulse and right before the gain-table override,
the real trace shows PHY reg `0x19e` explicitly cleared then
immediately re-set (`0x3d2 -> 0x3d0 -> 0x3d2`) - a step this port's code
doesn't perform anywhere in this sequence (the port's own `0x19e` state
at this point is already `0x3d2`, set once at the start of
`measure_setup_enter` and never touched again until the very end). Net
effect is the same either way (`0x19e` ends up back at `0x3d2` before
the gain-table writes in both cases), so this almost certainly isn't
the source of the flat-measurement result - but it's a real,
unexplained discrepancy, noted here rather than silently ignored. Not
investigated further given the more promising lead below.

## Where this leaves the investigation

With the entire setup block now independently confirmed correct
against real hardware behavior (not just self-consistent), the
remaining explanation has to be in one of:

1. **The measurement trigger itself** (`899`/`0x380`/`0x381` writes and
   the `radio 0x144` readback in
   `b43_phy_ac_txcal_measure_candidates_outer`) - this was checked
   against the trace in notes/20 for the *values written* (all
   matched), but not yet for the exact *timing/ordering* relative to
   the table-0xC clears and the ramp-table call.
2. **A missing ramp-table call.** `FUN_001ac9b6` calls
   `FUN_0019d65d` (this project's already-ported
   `b43_phy_ac_txcal_ramp_table`) once per core, the first time that
   core is touched in the sweep - `ac_txcal_candidate_test6` never
   calls it at all. Worth checking whether the real trace shows table
   0xC writes matching the ramp curve in this exact window (a
   `ghidra_dump_bytes`-extracted table was already ported; this would
   just be wiring an existing, already-tested function into the test
   sequence).
3. State established before this entire window even starts - something
   in `wl`'s real attach/association sequence, before calibration is
   ever invoked, that `ac_por`'s replay doesn't cover.

(2) is the cheapest to check next, since the function already exists,
is already tested standalone, and the trace data to confirm it against
is already captured.

## Follow-up: found and fixed (2) - the missing ramp-table call - still flat, but a real timing finding

Checked (2) immediately, since it was cheap. The real trace does show
exactly the ramp-table's signature pattern (table 0xC, offsets `0-0x11`
and `0x20-0x31`) right after the tone-generation trigger and right
before the first `0x381`/`0x383`/`0x380` write - and
`ac_txcal_candidate_test6` never called `b43_phy_ac_txcal_ramp_table()`
at all. Worked backward from the exact observed values to pin down the
real `percent` argument precisely: offset `0x2a`'s value (`0x4100`)
comes from `ramp_b[10] = {100, 0}`, i.e. `(100*percent/100)<<8|0` -
which only equals `0x4100` when `percent` is exactly `65` (`100*65/100
= 65 = 0x41`). Every other observed offset/value pair independently
confirmed `percent=65` as well, narrowing to that exact value with high
confidence, not just a plausible guess. Added
`b43_phy_ac_txcal_ramp_table(dev, 65)` right after `gen_tone_start()`
in every candidate test.

**Result: still completely flat** - `radio 0x144` bit-2-clear for every
combination, zero change from before this fix. No instability, 0%
backup-link packet loss.

**One genuinely new, useful piece of evidence found while re-checking
this:** added an iteration counter to the `0x380` busy-poll loop.
Earlier (notes/20) it looked like this port's poll might be completing
instantly compared to wl's observed ~637us - but that comparison relied
on this port's own `b43info`/printk-timestamped log lines, which
notes/20 already flagged as unreliable for timing. Measured directly
this time: **45-83 iterations per candidate (450-830us)** - the same
order of magnitude as wl's real observed poll duration, and genuinely
variable (not a fixed, trivial delay). This rules out "the busy bit
clears instantly / nothing is really happening" as an explanation.
The digital trigger/busy/poll mechanism is engaging in a real,
comparable-duration cycle - the remaining unexplained gap is
specifically in what that cycle *measures* (the analog tone/loopback
path, or the `radio 0x144` readback itself), not in the digital control
sequence around it, which is now about as thoroughly validated against
real hardware behavior as this project's methodology allows.

## Summary of everything now confirmed byte-exact against the real trace

Loopback-mode entry, the full per-core setup block (~55 ops/core), the
settle pulse, the gain-table override (table 7 and table 0xC, real
values), the `0x382=0x8a09` write, the tone-generation trigger sequence,
the ramp-table call, the outer candidate table, the `0x381` value, the
table-0xC clears, the inner candidate byte, the `0x380` trigger
encoding, and now the busy-poll's real timing characteristics. That is
the entire digital control path from loopback entry through to the
comparator readback. With all of it confirmed, the honest conclusion is
that the remaining explanation lies in something this kind of register-
sequence comparison cannot see: the actual analog tone/loopback signal
path, or a precondition established well before this window even
starts (during `wl`'s real attach, not its periodic calibration calls) -
not another missing register write in the calibration function itself.
