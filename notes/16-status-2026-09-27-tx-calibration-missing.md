# Status 2026-09-27 (continued again), likely found the real root cause: TX calibration is never run

Following "fix all bugs and make the driver usable" - kept digging past the
ucode work (notes/12-15) into the host-driver side one more time, this
time specifically looking for calibration *procedures* our port never
invokes at all, rather than more register *values* to compare (that
avenue was already exhausted in notes/09-11).

## The finding

`wlc_phy_cals_acphy` (decompiled earlier, `decompiled/wlc_phy_cals_acphy.c`)
is AC-PHY's full periodic calibration state machine - a ~19-phase
sequence, driven by repeated calls with an advancing phase counter, that
keeps the PHY's analog calibration state current over the driver's
lifetime (temperature drift, aging, etc.). **`b43-src` never calls this
function, or anything like it, anywhere.** The only calibration-adjacent
code that exists in the tree at all is in `phy_n.c` - mainline b43's
existing code for N-PHY, a different, older chip family.

Decompiled one of its key sub-functions, `FUN_001ac9b6` (called from
several of the 19 phases), and confirmed what it actually is: **the TX
LO-feedthrough / IQ-imbalance calibration routine.** It:
1. Generates a real, live TX test tone (`wlc_phy_tx_tone_acphy` - the
   exact "TX test tone" function decompiled earlier this session for an
   unrelated reason).
2. Sweeps gain/phase correction settings per core, polling hardware
   status registers (PHY 0x380/0x381) with bounded timeouts between steps.
3. Feeds the *measured* results into `wlc_phy_populate_tx_loft_comp_tbl_acphy`
   (found earlier - the LO-feedthrough compensation table writer) at the
   end, via `param_1+0xf58`'s per-core measurement buffer.

This is a genuine, per-chip, per-antenna, *measured* calibration - not a
fixed constant that could ever be discovered by comparing our replayed
register/table snapshot against wl's. It only exists as something that
*runs*, repeatedly, over the life of the connection.

## Why this fits the evidence better than anything tried before

- **TX-specific, not RX-specific** - matches the whole failure pattern
  exactly (RX has always worked; every TX-side hypothesis has been the
  productive line all along).
- **A measured, drifting correction, not a static value** - explains why
  every register/table comparison against wl's captured state came back
  clean (notes/09-11): the *values* we replay may have been correct *at
  the moment wl captured them*, but nothing keeps them current, and
  nothing ever established them from a real measurement on our own
  hardware/antenna/board variation in the first place.
- **Would plausibly affect fast, tight-timing autonomous TX (ACK/beacon)
  much more than host-queued TX** - host TX has driver-scheduling latency
  that autonomous TX doesn't; if imperfect IQ/LO calibration pushes a
  fast, immediate transmission attempt just outside some hardware
  tolerance window (gain settling, spectral mask, whatever the real
  silicon-level margin is), that would produce exactly the "ACK/beacon
  fail, host TX fine" split this whole project has chased, and the
  "zero signal ever reaches the air" result from notes/15's independent
  capture (a sufficiently bad LO/IQ problem, not just a quality
  degradation, could plausibly explain a PA/mixer never actually
  producing usable output for a very short, tightly-timed burst).

This is not proven - it's the most coherent, evidence-consistent
hypothesis this project has had, not a confirmed fix.

## Why nothing was implemented or tested on hardware this session

`FUN_001ac9b6` generates live RF test tones and sweeps gain/frequency
settings across cores while polling hardware, in a loop, for real. This is
the same *category* of operation (continuous live TX combined with
register/frequency sweeps) that caused this project's one hard machine
freeze (`notes/07`, 2026-09-26: 5 GHz bandwidth change + live TX). It also
calls several more sub-functions not yet decompiled or verified
(`FUN_0019454f`, `FUN_00193d3a`, `FUN_0019d3ac`, `FUN_0019ccd9`,
`FUN_0019d65d`, `FUN_0019d550`, `FUN_001982a2`, `FUN_00195603` -
`FUN_0019ccd9` in particular is called ~20+ times per calibration pass and
is clearly a core table-write helper worth understanding fully before
relying on it). Porting this well enough to trust running it - repeatedly,
automatically, sweeping real transmit power/frequency - on real hardware,
while the user was away and unavailable to help recover from anything
going wrong, was judged not worth the risk. Documenting it thoroughly here
instead of rushing a half-verified implementation onto hardware solo.

## Full algorithm now understood (all sub-functions decompiled)

Decompiled and read all remaining sub-functions (`decompiled-cal/`). The
complete picture, in call order from `wlc_phy_cals_acphy`:

1. **`FUN_0019454f`** - per-core: save ~7 radio registers (chip-ID-dependent
   addresses: 0x1a/0x1b/0x1c/0x1e/0x1f/0x24 for our BCM4360, into
   `phy+0x138` struct offsets 0x48-0x80), then switch the RF front-end into
   an **on-chip TX-calibration loopback mode** via `mod_radio_reg` (routes
   the PA/mixer output back through an internal sense path to the receiver
   ADC - the standard way chips self-calibrate TX IQ/LO without external
   test gear). Band-dependent (2.4 vs 5 GHz) and radio-generation-dependent
   (`phy+0x16e`) bit patterns.
2. **`FUN_00193d3a`** - brief (~1us) forced state on PHY 0x739/0x73a/0x725
   per core, then restored - looks like a quiesce/settle pulse before
   calibration starts.
3. **`FUN_0019d3ac`** - save the current TX gain-table (table 7, offsets
   0x100/0x103/0x106 - the same gain table `wlc_phy_txpwr_by_index_acphy`
   uses for real traffic) per core, then overwrite it with calibration-tone
   gain settings.
4. **`FUN_0019d65d`** - once per core, loads a gain-ramp curve (extracted:
   `3,4,6,9,13,18,25,35,50,71,100` and a per-core variant maxing out
   differently per the 8 possible cores - roughly logarithmic ramp from 3%
   to 100%) into PHY table 0xC, scaled by a percentage - the smooth
   power-up curve for the calibration tone itself, avoiding a hard-edge
   transient that would corrupt the measurement.
5. **`FUN_001ac9b6`** - the actual measurement: generates a live test tone
   (`wlc_phy_tx_tone_acphy`), then for a sweep of calibration-parameter
   indices writes/reads via `FUN_0019ccd9` (dispatches to real PHY table 0xC
   - extracted the index table: 12 (count,base,stride) triples mapping
   index 0-11 to table-0xC row/offset/per-core-stride - or to in-memory
   scratch buffers for indices >=0xC), reading back the loopback result via
   `read_radio_reg` after each write, polling PHY 0x380 for completion with
   a bounded timeout, to find the best I/Q phase/amplitude and LO-offset
   correction per core.
6. Feeds the measured results into **`wlc_phy_populate_tx_loft_comp_tbl_acphy`**
   (found earlier) to commit the final correction into the real,
   always-active loft-compensation table.
7. **`FUN_0019d550`**, **`FUN_001982a2`**, **`FUN_00195603`** - restore, in
   reverse order, everything saved in steps 3, 2 (PHY regs), and 1 (radio
   regs + RF front-end back to normal TX mode).

This is a complete, well-structured, self-contained save/calibrate/restore
procedure - not fundamentally exotic or badly designed, but genuinely
substantial (9 functions, ~500 decompiled lines total, several
chip-ID/band-dependent branches, 3 extracted static data tables plus the
already-known loft-comp correction tables). All raw data tables needed for
a faithful port are now extracted (see `tools/ghidra_dump_bytes.java`, a
new small reusable Ghidra script for pulling raw bytes at a given address -
useful for any future need to extract unnamed static data during
decompilation).

**Deliberately not attempting a blind full port from here.** Getting ~500
lines of multi-branch, register-mapping-heavy code right by hand, from
decompilation alone, with no way to validate any of it against real
hardware until it's finished, is exactly the situation most likely to
produce a subtle, hard-to-spot bug (wrong offset, swapped save/restore
order, mismatched per-core indexing) - and this code will be driving a live
RF measurement loop on real hardware. The safe way to port this is
incrementally, testing each piece (state save/restore first, verified
inert; then the loopback mode switch, verified it doesn't disrupt normal
RX; then the tone generation; then the actual sweep) against real hardware
as it's built - which requires the user's presence throughout, not just at
a final "does it work" test.

## Follow-up (same day, user confirmed still away): wrote the lowest-risk slice

Asked the user directly whether they were physically present before going
further - they weren't. Continued with safe, non-hardware work only:
decompiled the last two small sub-functions (`FUN_00199491`, `FUN_0019d224`
- table-0xC single-entry save/restore, straightforward), completing the
full algorithm map (11 functions total now).

Wrote `b43_phy_ac_txcal_save_gaintbl()` / `_restore_gaintbl()` into
`phy_ac.c` - the TX gain-table (table 7) and paired table-0xC save/restore
around a calibration tone. This is deliberately the *only* piece written:
no chip-ID branching, no live RF, a direct, symmetric save-then-restore
that's easy to verify by inspection against the decompiled source. **Not
wired into anything** - no caller exists yet, on purpose. Builds clean
(only the expected "defined but not used" warnings). Everything else
(the RF-loopback mode switch, tone generation, the actual sweep) is
understood well enough now to write, but is being deliberately left for a
session with the user present, per the reasoning above - writing more of
it blind wouldn't reduce risk, it would just accumulate more untested code
before the first real validation point.

## Follow-up: first live hardware test of the draft code (user explicitly authorized testing solo)

The user explicitly said to try hardware feedback even while away, having
already been told the risk reasoning above. Kept the scope narrow: wired a
new `ac_txcal_test` module parameter that exercises *only* the three
already-drafted, non-RF pieces (gain-table save/restore, settle pulse,
ramp-table writer) with before/after values logged via `b43info`/dmesg -
deliberately still not touching the RF-loopback-mode switch, tone
generation, or the measurement sweep, all of which remain unwritten and
are the genuinely higher-risk parts.

**Result: no instability whatsoever** (no crash, no hang, no dropped
connectivity, panic-on-hang sysctls set beforehand as an extra safety net
per this project's established practice). Real, useful feedback:

- **Save/restore round-trips exactly**: `before = after-restore = 0000
  0000 0000` on every one of 5 channel-set invocations logged.
- **Ramp-table writer produces exactly the hand-computed value** (`0x0100`
  for a 50%-scaled `{3,0}` ramp step - matches `(3*50/100)<<8|0` exactly).
- **One genuine hardware discovery**: writing a test value of `0x1234` to
  the third table-7 field (`core+0x106`) reads back as `0x0034` - only the
  low 8 bits took effect, even though both wl's own decompiled code and
  this port pass the generic 16-bit width parameter for it. This isn't a
  bug in the save/restore logic (the restore step still returned to the
  exact original value regardless), but it's a real, concrete fact about
  that specific field's actual width that wasn't visible from
  decompilation alone - worth remembering if that field's value ever
  needs to be reasoned about precisely (e.g. when eventually computing
  real calibration-tone gain values for it).

This is genuine confirmation that this slice of the port is correct and
safe on real hardware. It does not yet tell us anything about the ACK bug
itself - none of what's tested here touches RF, tone generation, or the
loopback-mode switch, so no conclusion about the calibration hypothesis
should be drawn from this test succeeding. It's groundwork validation,
not a result.

## What a responsible next session should do

1. Decompile the remaining sub-functions listed above, especially
   `FUN_0019ccd9` (the table-write helper used throughout the sweep) and
   `wlc_phy_populate_tx_loft_comp_tbl_acphy`'s gating condition
   (`param_1+0x16a != 0x30b` - need to determine what this field is and
   whether it's `0x30b` for our exact board, i.e. whether the loft-comp
   table write is even reachable for us at all).
2. Port `FUN_001ac9b6` (and enough of `wlc_phy_cals_acphy` to invoke it
   with sensible phase/mode arguments) into `phy_ac.c`, gated behind a new
   `ac_*` module parameter exactly like every other experimental change
   this project has made, so it's opt-in and easy to disable.
3. Test it **with the user physically present**, same standard as every
   other live-TX-adjacent experiment in this project: single Claude
   session, USB backup link verified first, `postboot.sh`, and this one
   specifically should NOT be run unattended given its live-TX-sweep
   nature - closer in risk profile to the 5 GHz bandwidth work than to
   anything tested solo this session.
4. If it changes the ACK/beacon failure rate at all (even partially), that
   would be strong confirmation this is the real mechanism, worth
   investing further porting effort in; if it changes nothing, it would be
   the first real evidence *against* this theory rather than just another
   untested guess.
