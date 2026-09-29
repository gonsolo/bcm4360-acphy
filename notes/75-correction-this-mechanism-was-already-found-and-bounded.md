# Correction: notes/28-29 (2026-09-27) already found and timing-bounded this mechanism

Direct, urgent correction to notes/72-74, same continued session
(2026-09-29). Went to decompile the remaining desense/hwaci helper
functions per notes/74's own plan, and in checking which were already
decompiled, found `notes/28` and `notes/29` - from a **previous session,
2026-09-27**, two days before tonight's work - already covering this
exact area in more depth on one specific, critical point.

## What notes/28-29 already established

Per explicit user instruction on 2026-09-27, a prior session decompiled
`wlc_phy_watchdog`, `wlc_phy_desense_aci_engine_acphy`,
`wlc_phy_hwaci_engine_acphy`, `wlc_fatal_error`, and the full MAC-
suspend/enable call chain (`wlc_bmac_suspend_mac_and_wait`,
`wlc_bmac_enable_mac`, `wlc_bmac_mctrl`) - all already sitting in
`decompiled-si/` and `decompiled/`, which is exactly why they were
"already decompiled" when notes/73-74 checked tonight (I read that as
generically available, not as a signal that this exact investigation
had already happened).

Critically, notes/29 **timed the MAC-suspend window precisely**: traced
`wlc_bmac_suspend_mac_and_wait`'s actual poll loop (countdown from
`0x14441`, `osl_delay(10)` per iteration) to a hard **~83ms worst-case
bound**, and the rest of `wlc_phy_hwaci_engine_acphy`'s work inside the
suspend window to "a few dozen microsecond-scale register accesses,"
concluding the whole cycle is bounded at roughly 85-90ms.

Their own stated conclusion, directly: *"this can plausibly account for
some of the shorter observed blackout instances... but it cannot, on
its own, explain the longer instances (457 ms, and the several trials
that showed no reception at all within a 2.5s window)."*

## What this means for tonight's notes/72-74

notes/72 claimed wl's 1.024s watchdog tick was "never before located" -
**wrong**, corrected here. notes/74 presented the missing desense
engine as a strong candidate for tonight's auth-failure symptom without
this crucial prior bound in view.

The two investigations aren't necessarily about the identical symptom -
notes/28-29 were chasing an earlier-characterized "RX blackout duration"
(notes/25-26), tonight's notes/58-74 chase intermittent auth success/
failure (notes/58 onward) - related, both AC-PHY periodic-mechanism
questions, but not confirmed to be the same observable. Still, the
timing bound is a real, hard constraint either way: *if* this exact
mechanism (hwaci engine's suspend cycle specifically) is meant to
explain a gap, that gap should be under ~90ms. Tonight's auth timeouts
run to hundreds of ms to full failure (notes/58's original 3-second
gaps, this session's repeated multi-second stretches) - on the high end
of what even notes/29's own most generous reading allows, and beyond it
for the worst cases.

## What's still real and additive from tonight

notes/73's specific finding - that `macstat[60]`'s delta, computed each
watchdog tick, is a real *input* to `wlc_phy_desense_aci_engine_acphy`'s
decision arithmetic (traced via matching offsets between `wlc_phy_
watchdog`'s history-array writes and the desense engine's reads) -
doesn't appear to be in notes/28-29, which scanned the desense engine
for structure but (per notes/29's own admission) hadn't read it fully
line-by-line yet, and didn't trace its specific counter inputs. That
connection is new. So is confirming this port implements none of it at
all (a `grep`, not previously stated explicitly either).

But given notes/29's timing bound, `wlc_phy_hwaci_engine_acphy`'s own
suspend/resume cycle specifically should not be read as a strong
candidate for large gaps - it wasn't when it was found two days ago,
and rediscovering it tonight doesn't change that math. Porting the
desense/ACI logic remains worth doing for correctness (it's real,
missing functionality), but the *causal story* for tonight's specific
failure pattern needs to be held more loosely than notes/74 presented
it - closer to "a real gap in the port, plausible contributor, not
shown sufficient" than "the answer."

## Process lesson

Before presenting a "genuinely new" finding, check the notes directory
for prior sessions on the same specific mechanism - not just search for
whether a *function* is already decompiled (which only tells you
whether the read-only extraction step was done), but whether the
*investigation* was already run and concluded. A decompiled `.c` file
sitting in the repo is not neutral information: if it exists, something
already looked at it and probably wrote up what it found.
