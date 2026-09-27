# Status 2026-09-27 (late evening, continued yet further still): decompiled `wlc_phy_watchdog`/`wlc_fatal_error`; found a MAC-suspend cycle inside the AC-PHY ACI engine

Direct follow-up to notes/27, same evening, per explicit user instruction
("decompile wlc_phy_watchdog and wlc_fatal_error next"). Read-only Ghidra
work only - no hardware touched, no source changes.

## Setup note: the Ghidra project's `.gpr` marker file was missing

`analyzeHeadless ghidra_proj AcphyProj ...` (the invocation documented in
notes/04) failed with "Opening existing project" but then couldn't find
`decompile_named.java", tracing back to a missing `AcphyProj.gpr` file -
only `AcphyProj.rep/` (the actual analyzed-program data) was present;
`ghidra_proj/AcphyAnalyzed.gpr` also existed but was 0 bytes. Confirmed
`AcphyProj.rep/project.prp` and the sibling `AcphyAnalyzed.rep/project.prp`
share an identical, minimal format (just an `OWNER` property), so
reconstructed `AcphyProj.gpr` with that same content. This is a top-level
project marker file, not part of the analyzed program data in `.rep/` -
low risk, and it worked: the project opened normally and the existing
analysis (labels, prior decompilations, etc.) was intact. Not otherwise
investigated *why* the file went missing.

## `wlc_phy_watchdog`: a big multi-PHY-type dispatcher; AC-PHY's actual work is narrow

Decompiled (`decompiled-si/wlc_phy_watchdog.c`, ~600 lines). Most of the
function is other PHY types' calibration logic (GPHY/NPHY/LPPHY/HTPHY/
LCNPHY ACI and calibration routines) that AC-PHY's branch (`phy type ==
0xb`) explicitly skips past. Tracing AC-PHY's actual path through the
dispatch, the calls that *do* apply to this chip are:

- `wlc_phy_desense_aci_engine_acphy()` - gated on a flag bit at the PHY's
  hardware-info struct (`+0x80`, bit 0)
- `wlc_phy_hwaci_engine_acphy()` - gated on bits 1-2 of the same field
- `wlc_phy_hirssi_elnabypass_engine()` - gated on `phytype==0xb` and a
  separate byte flag
- `wlc_phy_stop_bt_toggle_acphy()` - gated on `phytype==0xb`, inside a
  block also gated on Bluetooth-coexistence-related flags
- a generic, all-PHY-types periodic BT-chanspec update
  (`wlapi_update_bt_chanspec`), gated on a tick-count modulus

All four AC-PHY-specific functions were also decompiled this session for
completeness (`decompiled-si/wlc_phy_{desense_aci_engine_acphy,
hwaci_engine_acphy,hirssi_elnabypass_engine,stop_bt_toggle_acphy}.c`).

## The key finding: `wlc_phy_hwaci_engine_acphy` suspends the MAC to do real PHY work

`wlc_phy_stop_bt_toggle_acphy` (26 lines) and
`wlc_phy_hirssi_elnabypass_engine` (64 lines) are both narrow, mostly
self-contained state-machine/countdown logic - the eLNA-bypass one *does*
reconfigure RX front-end gain when its own internal countdown expires
(calling `wlc_phy_hirssi_elnabypass_set_ucode_params_acphy`/`_apply_acphy`),
but only once every N watchdog ticks (N held in state, not visible in
this function alone), not necessarily every cycle.

`wlc_phy_desense_aci_engine_acphy` (278 lines) is almost entirely
self-contained arithmetic/history-tracking (one incidental
`osl_memcmp`) - it looks like it *decides* whether desense is needed
without directly touching hardware itself.

**`wlc_phy_hwaci_engine_acphy` (223 lines) is different and directly
relevant**: partway through, it calls `wlapi_suspend_mac_and_wait()`,
then does a substantial block of real ACI-mitigation PHY work
(culminating in `wlc_phy_aci_updsts_acphy()`), and only then calls
`wlapi_enable_mac()` to resume. `wlapi_suspend_mac_and_wait` is the same
category of call this project already knows disables RX -
`b43_mac_suspend()` in `main.c` does exactly this (confirmed back in
notes/24's timing investigation: MAC-suspended means no RX processing).

This is now the single most concrete, structurally-matching candidate
mechanism found so far for the periodic RX blackout (notes/25/26): a
real, named, AC-PHY-specific routine that suspends the MAC, does
meaningful PHY register work, and resumes it - called from the same
watchdog that fires on the same ~1.024 s cycle already measured in both
`b43` and real `wl` traces.

**Honest caveat: this has not been shown to actually cause a user-visible
RX gap in wl's real operation.** Nothing tonight directly measured
whether wl's own reception has a corresponding gap during this specific
routine's execution (as opposed to just showing the MMIO *access*
periodicity, which notes/27 already established). It's entirely possible
this suspend/resume cycle is fast enough in wl's correct, complete
implementation to be imperceptible, and that b43's observed blackout
comes from a related-but-different cause (e.g. firmware/ucode-level
behavior this routine is specifically designed to accompany, which fires
regardless of host-driver code and produces a worse outcome when nothing
host-side ever runs alongside it). Both readings remain open.

## `wlc_fatal_error`: confirmed as a full driver reinit

Decompiled (`decompiled-si/wlc_fatal_error.c`, 24 lines). It's short and
unambiguous: on any DMA/FIFO error escalation from
`wlc_bmac_fifoerrors()` (notes/27), it saves/restores a hi-res timer and
power-save-control byte around a call to **`wl_init()`** - i.e. wl's real
response to a detected DMA error is a full chip reinitialization, not a
targeted per-ring reset. This confirms notes/27's reading: `b43-src` has
no equivalent of this anywhere, so if this hardware ever hits one of the
DMA/FIFO error conditions `wlc_bmac_fifoerrors` checks for, there is
currently nothing in this port that would ever notice or recover from it
- it would simply persist until the module is reloaded (which is exactly
what every test session in this project has always done between rounds,
incidentally "fixing" any such lingering state without anyone knowing it
was there).

## Where this leaves things

Nothing was ported or tested on real hardware tonight - this was
deliberately kept to static analysis, consistent with notes/27's stated
plan and this project's standing caution around DMA/reset-path code.
Two independent, concrete candidate mechanisms are now identified and
named precisely enough to decompile further or reason about directly,
rather than being a vague "some periodic calibration" placeholder:

1. `wlc_phy_hwaci_engine_acphy`'s MAC-suspend/PHY-work/MAC-resume cycle -
   candidate for the RX blackout.
2. `wlc_bmac_fifoerrors` -> `wlc_fatal_error` -> `wl_init()` - candidate
   for silently-persisting DMA/FIFO error states that could plausibly
   degrade TX reliability over time with nothing ever detecting or
   fixing it.

## Next steps for a future session

1. Decompile `wlc_phy_aci_updsts_acphy` (the substantive work inside
   `wlc_phy_hwaci_engine_acphy`) to see exactly what PHY state it
   changes while the MAC is suspended, and roughly how long that would
   plausibly take.
2. Try to directly measure whether *wl's own* reception shows a
   corresponding brief gap during one of these ~1.024 s cycles (a
   `trace_wl.sh`-style capture combined with an independent RX-timing
   check, similar to notes/25's b43 gap analysis, but for `wl`) - this
   would settle the open caveat above one way or the other.
3. Resolve `wlc_bmac_watchdog`'s two indirect/vtable calls (still
   unresolved - noted in notes/27) - may reveal additional periodic work
   this port is also missing.
4. Any actual porting of watchdog-derived code stays a materially
   different risk category (DMA/reset/PHY-recalibration paths) - needs
   the user present, per this project's standing practice, and should
   wait until the above is better understood.
5. Loft-comp calibration question (notes/22) remains fully open and
   untouched.

## Session close

No hardware touched this round - static Ghidra analysis only, run
against the existing extracted `wl.ko` binary. No `b43-src` or other
source changes. The only local, low-risk change was reconstructing the
missing `ghidra_proj/AcphyProj.gpr` marker file so the existing analysis
project could be reopened.
