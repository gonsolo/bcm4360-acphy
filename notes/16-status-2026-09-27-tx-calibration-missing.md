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

## Follow-up: read-only radio register check for the loopback-mode switch

"Continue" was interpreted as moving to the next piece - the RF-loopback-
mode switch (`FUN_0019454f`/`FUN_00195603`). Transcribing it precisely
revealed it has *two* compounding unknowns, not one: the already-flagged
`phy+0x16e` field, plus a second wl-internal condition
(`phy+0x17e & 0xc000`) that selects which register values to *write*.
Stacking two unconfirmed guesses on code that reconfigures live RF
front-end bias/routing registers is a meaningfully bigger risk than
anything tested solo so far - so this was split: implemented and tested
only the **read** half (the seven per-core radio register saves, chip-ID
branches resolved to fixed BCM4360 values), logged the values, and
deliberately did not implement or run any of the actual mode-switch
writes.

**Result: plausible, stable, real values** - identical between core 0 and
core 1, unchanged across repeated channel-set calls (not noise), and
`0x1f`'s value (`0`) is consistent with the driver currently being in
normal, non-calibration mode, matching what the "else" branch of the
write-side code would set it to. This gives real confidence the register-
address resolution (`0x1a/0x1b/0x1c/0x1e/0x1f/0x24`, `core<<9` addressing)
is correct, without taking on the risk of the actual mode-switch writes.
No instability; connectivity never dropped.

**Still not resolved, still needed before the write half can be ported
safely**: which branch `phy+0x16e` takes for our board (affects whether
the 8th saved/restored register is at `0x170|core9` or `core9|0x184`), and
what `phy+0x17e & 0xc000` represents in terms of parameters this port
already knows (band? bandwidth? something else) - needed to pick the
right branch of the actual loopback-mode-entry writes. Both are wl-
internal software state, not hardware registers, so they can't be read
directly; they need either more decompiled source or careful inference
from behavior once the write side is attempted.

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

## Follow-up: full loopback-mode enter/exit write test (user authorized continuing solo)

Resolved the `phy+0x17e & 0xc000` unknown by cross-referencing ~10 other
decompiled functions (`FUN_0019a2eb`, `FUN_0019a398`, `FUN_0019b279`,
`FUN_0019bc45`) that test the same mask: it's the standard Broadcom
chanspec bandwidth sub-field (bits 14-15), and for our 20 MHz test
scenario it's `0`, not `0xc000` - so the "else" branch of
`FUN_0019454f`/`FUN_00195603` is the right one. This is corroborated by
the earlier read-only finding (notes above): `0x1f` already reads back
with bit 2 clear, exactly what the else-branch write would set.

`phy+0x16e` (register `0x170` vs `0x184` for the 8th saved/restored
register) remains an unconfirmed guess - assumed `0` (register `0x170`),
documented as the first thing to revisit if results look wrong.

Wrote `b43_phy_ac_txcal_enter_loopback()` / `_exit_loopback()` into
`phy_ac.c` (full port of `FUN_0019454f`/`FUN_00195603`'s else-branch
logic), gated behind a new, separate `ac_txcal_loopback_test` module
parameter (kept distinct from `ac_txcal_test` since this one writes to
live RF front-end bias/routing registers, not just digital table/gain
state). Test block: enter loopback mode, log core-0 registers, exit
immediately, log again - no tone, no live TX.

**Result: exact match on every documented expectation.**

```
before core0:      1a=0004 1f=0000 1e=0010 170=0000
after-enter core0: 1a=0084 1f=0000 1e=0014 170=4000
  (want: 1a low nibble of top byte=8 -> yes (0x84);
         1f bit2=0 -> yes; 1e bit2=1 -> yes (0x14 has bit2 set);
         170 bit8=0 -> yes; 170 bit14=1 -> yes (0x4000))
after-exit core0:  1a=0004 1f=0000 1e=0010 170=0000  (matches 'before' exactly)
```

Identical result across all 5 channel-set invocations logged. No
warnings/oops/BUG/call-trace in dmesg around load or unload. USB backup
link held 0% packet loss throughout (before, during, after). Clean
unload; chip returned to `bcma-pci-bridge`.

This is a real, positive result for the *port*: the loopback-mode-switch
register logic, including the `phy+0x16e==0` guess, produced internally
consistent, fully-predicted values and a bit-perfect restore - good
evidence the enter/exit logic and the `phy+0x16e` guess are both correct,
or at least self-consistent, for this board. **It still does not test
the calibration hypothesis itself** - no tone was generated, no
measurement sweep ran, nothing about actual TX behavior was exercised.
The next genuinely diagnostic step is still `FUN_001ac9b6` (tone
generation + measurement sweep), which remains the highest-risk,
least-tested part of the algorithm and - per the plan above - should be
tested with the user physically present, not solo.

## Follow-up: first live TX test tone, generated and played back on real hardware (user explicitly authorized: "You can also do the risky stuff")

Decoded `wlc_phy_cals_acphy` (the top-level periodic calibration state
machine, `decompiled/wlc_phy_cals_acphy.c`) to get `FUN_001ac9b6`'s real
calling convention and, critically, the exact real-world arguments wl
uses for our band: `wlc_phy_tx_tone_acphy(pi, 1000, 0xfa, 1, 0, 0)` for
2.4 GHz (frequency-parameter 1000, amplitude 0xfa=250, `param_4=1`
skips carrier-search toggling, `param_5=0` takes the real hardware
trigger path, `param_6=0`).

Traced `FUN_001ac9b6`'s ~500-line setup block far enough to find it
depends on a *third*, previously unnoticed unresolved field
(`phy+0x164`, compared against 0/1/2/3/5/6 throughout, gating both a
large per-core PHY-register save block and the final loft-comp-table
commit) with no assignment site found anywhere in what's decompiled so
far (checked `wlc_phy_attach_acphy.c` and everywhere else `+0x164` is
referenced - only reads, no writes). Rather than guess a third unknown
on top of the other two, or spend more time chasing it, split the work
again: **`wlc_phy_tx_tone_acphy` itself turns out to be fully
self-contained and independent of `phy+0x164`, the per-core save block,
and `phy+0x116a`** - none of those are touched by the tone-generation
function for our exact call pattern. So it's possible to test "can this
port actually drive a live TX tone through the chip" without first
solving the calibration state machine's remaining unknowns at all.

Decompiled two more small dependencies: `wlc_phy_cordic` (a textbook
18-iteration fixed-point CORDIC rotator, angle in 1/65536-degree units,
touches zero hardware - pure integer math) and confirmed
`wlc_phy_stopplayback_acphy`/`wlc_phy_resetcca_acphy` (wl's own
cleanup path) unfortunately *does* depend on the new `phy+0x164`
unknown. Verified the CORDIC port against Python's `math.sin`/`cos` at
10 different angles (0/30/45/90/135/180/270/-45/360/738 degrees) before
writing a line of test C - matched exactly at every angle, and the
actual 40-sample, amplitude-250 tone waveform computed cleanly with no
overflow (`|x|,|y| <= 250` throughout, as expected for that amplitude).
This is the first time in this project a piece of decompiled math was
checked against a reference implementation before trusting it, rather
than only against re-read hardware state - worth doing again for any
future numeric (non-register) porting.

**Deliberately did not replicate wl's real cleanup.** Since
`wlc_phy_resetcca_acphy` depends on the unresolved `phy+0x164`, and this
is a live-TX code path, chose a strictly safer alternative that sidesteps
the unknown entirely: `b43_phy_ac_txcal_gen_tone()` saves all 7 PHY
registers it touches (`0x460/0x461/0x462/0x463/0x471/0x382/0x400`)
before doing anything, and writes them back verbatim afterward,
regardless of what wl's own semantics would do. This means the chip may
not end up in exactly wl's normal post-tone-test operating state, only
back in whatever state it was in immediately before the function ran -
documented clearly in the function's comment as a deliberate
simplification, not an oversight.

Wired this into a new, separate `ac_txcal_tone_test` module parameter
(explicitly labeled in its `MODULE_PARM_DESC` as "highest-risk flag in
this project so far... only ever run with the user physically present"
- even though this run itself was solo, per the user's explicit,
informed override: *"You can also do the risky stuff"*, given directly
in response to being told this was exactly the point flagged as needing
their presence).

**Result: no instability, across two separate load/test/unload cycles
(5 invocations each).** Every one of the 7 saved registers round-tripped
exactly; the tone-generation register sequence (waveform table 0xE
write, then the 0x460-0x463/0x382/0x400/0x471 trigger sequence, then a
bounded ~1ms poll on 0x403 bit 0) completed without hanging - the poll
condition was already satisfied on the very first check every time
(`403=0000` both before and after), i.e. playback reported itself
complete essentially instantly, which is unsurprising for a very short,
low-amplitude test tone. No warnings/oops/BUG/call-trace in dmesg across
either cycle. USB backup link held 0% packet loss throughout both loads.
Clean unloads; chip returned to `bcma-pci-bridge` each time.

Added one more read-only observation on the second cycle: logged radio
register `0x144|core<<9` (the exact loopback-measurement register
`FUN_001ac9b6` polls during its real sweep, for our confirmed
`acphychipid==0x4360` branch) before and after the tone. It read `0000`
unchanged in both cases, for both cores. **This is inconclusive, not
negative evidence** - the real algorithm only gets a meaningful reading
there *after* writing to PHY register `0x380` (the actual per-candidate
measurement trigger, part of the still-unported sweep loop), which this
test never did. Reading `0x144` without first triggering a measurement
is expected to show nothing regardless of whether the tone radiated
correctly or not - noted here so a future session doesn't mistake this
non-result for evidence either way.

**What this does and doesn't tell us:** This is the first time in the
whole project that live TX-tone-generation code has run on this
hardware, and the register-level mechanics (waveform table write,
trigger, bounded poll, restore) all behaved exactly as the decompiled
source predicts - genuine, positive validation of this slice of the
port. It does **not** yet confirm or refute the calibration hypothesis:
there is still no working measurement (no `0x380` trigger, no read-back
interpretation, no loft-comp write), so whether the tone actually
produced usable RF - even just internally, via the loopback path - is
still unknown. The next informative step would be adding the actual
`0x380`-triggered measurement read (bounded, read-mostly, one register
write per sample) to see whether the loopback receive path shows *any*
signal at all correlated with the tone, before attempting the full
correction-search sweep or the loft-comp table commit (both of which
still need `phy+0x164` resolved, or another deliberate simplification
worked out first).

## Follow-up: `phy+0x164` fully resolved - it's a real hardware register, not opaque state

Tried to plan the next step (a single-candidate measurement test using
the real `0x380`/899 trigger sequence) and found it directly requires
knowing `phy+0x164` after all: `FUN_001ac9b6`'s candidate-table dispatch
(lines 630-654) branches on `phy+0x164 != 1` to pick between two
completely different correction-candidate tables (`local_c8` vs
`local_e8`) before a single register gets written - guessing wrong here
wouldn't crash anything, but would mean testing with the wrong candidate
values, which defeats the point.

Went looking for where `phy+0x164` actually gets assigned, since nothing
in `decompiled/wlc_phy_attach_acphy.c` writes it (only reads it) -
decompiled the generic, chip-independent `wlc_phy_attach()` (the
dispatcher that calls `wlc_phy_attach_acphy()` for our chip) and found
it at `wlc_phy_attach.c:71-75`:

```
uVar4 = osl_readw(*(long *)(lVar10 + 0x148) + 0x3e0);
*(uint *)(lVar10 + 0x160) = (uVar4 & 0xf00) >> 8;   /* phy type */
*(uint *)(lVar10 + 0x164) = uVar4 & 0xf;            /* phy rev (low nibble) */
*(uint *)(lVar10 + 0x174) = uVar4 >> 0xc;           /* analog type */
```

Offset `0x3e0` is `B43_MMIO_PHY_VER` - the exact same PHY-versioning
register mainline b43 already reads at attach for every chip it
supports (`b43_phy_versioning()` in `phy_common.c`, bits 12-15=analog
type, bits 8-11=phy type, bits 0-7=phy rev). **`phy+0x164` is not
opaque software state at all - it's `B43_MMIO_PHY_VER & 0xf`, a real,
directly-readable hardware register.** There is one override just below
it (`if (chipid in {0xa8e2,0xa8e3,0xa8e4,0xa8e6} && radio-rev check)
phy+0x164 = 9`), but that's keyed on `acphychipid`, which is `0x4360`
for every single test in this entire project - it can never fire for
us, unconditionally.

Read the register directly on real hardware (`mmio16` debugfs file,
zero risk, a plain 16-bit MMIO read already used throughout this
project): **`0x3e0` = `0xcb01`.** Decoded: analog type = `0xc`, phy type
= `0xb`, **phy rev (`phy+0x164`) = `0x1`.** This exactly matches
`notes/05-channel-tuning.md`'s independent, much-earlier finding ("PHY
rev is 1") - a real, satisfying cross-check between two unrelated
investigations landing on the same hardware-derived fact. `phy+0x164 ==
1` is now a confirmed, hardware-verified value for this board, not a
guess.

**What this unblocks:** `phy+0x164==1` means, for our exact chip:
- The candidate-table dispatch resolves definitively to `local_e8`
  (`{0x423, 0x334, 0x73, 0x267, 0x45, 0x234}`) for the real
  `param_2=1,param_3=1,param_4=0` call wl itself uses.
- `wlc_phy_populate_tx_loft_comp_tbl_acphy`'s call in `FUN_001ac9b6` at
  line 827 (`if (phy+0x164==1) ...`) is reachable for us - the loft-comp
  commit isn't dead code on this board, unlike a chip where it wouldn't
  be 1.
- `phy+0x164==3` branches (elsewhere: `wlapi_bmac_phyclk_fgc` calls,
  `wlc_phy_populate_recipcoeffs_acphy`'s alternate path, `FUN_001a1202`'s
  rev-3 table set) are all confirmed *not* to apply to us.
- `wlc_phy_resetcca_acphy`'s branch (`if (phy+0x164 in {2,5,6})`) also
  does not apply - we'd take its simpler "else" path, so a *real* port
  of wl's own cleanup (rather than this session's save-everything
  workaround) is now possible without guessing, if a future session
  wants to replace `b43_phy_ac_txcal_gen_tone`'s simplified cleanup with
  wl's actual one.

Not yet done: implementing the actual candidate-search loop using this
now-resolved table (still a genuinely large, closed-loop, hardware-
reactive piece - the loop writes a candidate to register 899, triggers
via `0x380`, polls, reads back radio `0x144`, and *branches on that
reading* to decide whether to keep searching or stop - a materially
different risk profile than every open-loop register sequence tested
so far, deserving its own careful, isolated first test rather than
being bolted onto this same session's already-substantial hardware
testing).
