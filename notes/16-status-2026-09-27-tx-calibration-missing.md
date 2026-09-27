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
