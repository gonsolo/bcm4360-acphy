# Status 2026-09-27 (late evening, continued yet further still): couldn't resolve the vtable calls by name, but found direct evidence of what they do - a real per-core loopback measurement sweep, every ~1.024s

Direct follow-up to notes/29, same evening, per explicit user instruction
("keep going, resolve the vtable calls next"). The originally-planned
method didn't work; a different, still read-only method found something
more directly useful than a function name would have been.

## `wlc_bmac_watchdog`'s own code is not kprobe-able

Tried the obvious approach: a `kprobe` on `wlc_bmac_watchdog` itself,
reading `wlc_hw` (the first argument, via `arg0`) and following the exact
same pointer chain the decompiled code follows
(`*(lVar1+0x20)` -> dereference -> `+0xd8` -> dereference -> call target)
to resolve both indirect calls empirically, live, on the real running
driver. `bpftrace` refused immediately: `wlc_bmac_watchdog is not
traceable (either non-existing, inlined, or marked as "notrace")` - this
project already knew (from much earlier tracing work) that only `wl.ko`'s
`osl_*` OSL-shim functions are kprobe-able; the rest of the compiled blob
isn't. No harm done - the probe simply failed to attach, nothing was
touched.

## A better method: decode the already-captured trace directly

Realized the answer didn't need a function *name* at all: whatever the
two indirect calls do, if it touches hardware, it goes through the same
`osl_writel`/`osl_readw`/`osl_readl` functions this project has been
tracing all along - already fully captured in
`traces/wl-init-20260927-212541.trace` (notes/27). Extracted a precise
±3-5 ms window around one of the already-identified ~1.024 s watchdog
markers (a `DMA1_REASON` read) and decoded every event through the PHY/
radio indirect-register ports (`0x3fc`/`0x3fe`, `0x3d8`/`0x3da`) into
logical `(register, value)` pairs, in exact temporal order.

## What one watchdog cycle actually contains

The decoded sequence, confirmed identically in two completely independent
cycles (different points in the trace):

1. DMA-reason register reads (`wlc_bmac_fifoerrors`, notes/27/28) and a
   block of SHM-counter reads via the `0x160`/`0x164`/`0x166` port
   (iterating over a range of statistics-counter offsets) and `MACCMD`
   writes.
2. **PHY register `0x19e` cleared in three steps**: `0x3d0 -> 0x390 ->
   0x310 -> 0x210` - the exact same register this project's own
   TX-loft-calibration port (`b43_phy_ac_op_switch_channel`,
   `b43_phy_ac_txcal_measure_setup_enter`) manipulates when entering its
   loopback/measurement mode, and the same register flagged as an
   *unexplained* clear-then-restore in notes/21.
3. **A full per-core PHY register setup block**, core 0 then core 1,
   touching exactly the register set this project already knows and has
   already ported: `0x73e, 0x727, 0x73c, 0x721, 0x729, 0x720, 0x728,
   0x724, 0x736, 0x725, 0x739, 0x73a, 0x722, 0x734` for core 0, and the
   identical set at `+0x200` (`0x93e, 0x927, ...`) for core 1 - this is
   `measure_setup_enter`'s own register list, already ported in
   `b43_phy_ac_txcal_measure_setup_enter()` (notes/16-21).
4. **A per-core radio mode-switch sequence**: reads then writes to
   `0x016e, 0x000e, 0x0161, 0x0017, 0x015f, 0x0024, 0x0025` for core 0,
   and the same set at `+0x200` for core 1 - a save-then-change pattern,
   consistent with entering a loopback/calibration radio mode.
5. **A repeated comparator/ADC-style sampling loop**: many rapid,
   fast-changing reads of PHY register `0x0013`, in bursts of ~8,
   interleaved with radio register `0x016e`/`0x000e` (core 0) or
   `0x036e`/`0x020e` (core 1) being stepped through a small sequence of
   values (0 -> 1/2 -> 3 -> ...) between bursts - structurally identical
   in shape to this project's own already-ported "candidate measurement"
   sweep (`b43_phy_ac_txcal_measure_candidates`/`_sweep`), just with a
   different comparator register (`0x0013` here vs `radio 0x144` in the
   TX-loft-cal work) and a different, smaller state space.
6. A `PHY_VER` (`0x3e0`) sanity read.
7. **Full restoration**: all the per-core radio registers from step 4
   written back to their original saved values, for both cores, then PHY
   `0x19e` restored (`0x3d0 -> 0x3d2 -> 0x3d0`) - closely matching, and
   very likely fully explaining, notes/21's previously "unexplained gap"
   (a `0x19e` clear-then-restore observed in the real trace at a
   different point, with no equivalent in this port's ported code at the
   time).
8. More SHM-counter reads, continuing into whatever comes after in the
   watchdog's own sequence.

**Total measured duration, start of the `0x19e` clear to full
restoration: ~1.1-1.3 ms**, consistent across both independently-checked
cycles.

## What this means

This is now the most concrete, most directly-comparable finding of the
entire investigation: **the real vendor driver runs an actual,
structurally-recognizable loopback-mode measurement sweep - closely
resembling this project's own already-ported TX-loft-calibration
candidate search - as a routine part of its periodic (~1.024 s) watchdog
cycle**, not (as this project's TX-calibration work assumed since
notes/16) a one-time thing done only around attach/association. This
was never previously known: the earlier TX-calibration investigation
(notes/16-21) only ever looked at wl's *attach-time* trace, not its
ongoing, steady-state periodic behavior.

Practically, this likely explains notes/21's previously-unresolved
`0x19e` clear/restore mystery directly, and gives this project's stalled
TX-calibration work (last left at "everything ported, measurement still
flat," notes/20/21) a genuinely new avenue: comparing this specific
*periodic, steady-state* sweep against the ported
`b43_phy_ac_txcal_candidate_test*` code, rather than only comparing
against the one-time attach-time trace used previously - there may be
real, undiscovered differences between what happens at attach and what
happens on this recurring cycle.

**On the original question (does this explain the RX blackout):** at
~1.1-1.3 ms, this specific measured sweep is *still* far too short to
explain the RX blackout's longer instances (457 ms, or the >2.5 s
no-reception trials from notes/26) - consistent with, and a bit more
precise than, notes/29's ~85-90ms upper bound for the MAC-suspend
mechanism. The vtable calls' *names* remain unresolved, but their
*effect*, at least in these two sampled cycles, is now directly known and
measured, and it is not by itself long enough to be the sole cause of the
longer blackouts.

## Next steps for a future session

1. Compare this periodic sweep's register values in detail against the
   already-ported `b43_phy_ac_txcal_measure_setup_enter`/
   `_measure_candidates_sweep` code - are the values genuinely identical,
   or does the periodic sweep differ in some way (different candidate
   table, different comparator register `0x0013` vs `radio 0x144`) that
   would explain the earlier flat-measurement result (notes/20)?
2. Sample several more watchdog cycles across a longer trace window to
   see whether the ~1.1-1.3 ms duration is always this short, or whether
   it occasionally runs longer (e.g. if the ACI engine's own history/
   hysteresis logic, decompiled in notes/28-29, sometimes takes a
   different, slower branch) - this trace only sampled two cycles.
3. The longer blackout tail (hundreds of ms to multiple seconds) is
   still unexplained by anything decompiled or measured so far - next
   candidates: `wlc_phy_desense_aci_engine_acphy` (278 lines, still only
   grep-scanned, never fully read - notes/28's open item), or something
   entirely outside the watchdog path.
4. Loft-comp calibration question (notes/22) remains fully open and
   untouched - but this note's finding is directly relevant context for
   it, since it shows real, ongoing loopback-based measurement activity
   this project didn't know was happening at all until now.

## Session close

No hardware touched - this was decoding of the already-captured trace
file only (`traces/wl-init-20260927-212541.trace`, unchanged from
notes/27), plus one failed, harmless `bpftrace` attach attempt. No
`b43-src` changes.
