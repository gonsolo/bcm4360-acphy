# Status 2026-09-29 (part 2): the per-scan-step channel-6 state replay
lines up with notes/77's failure pattern; `ac_state_once` live-tested,
not yet proven as a fix

Direct continuation of notes/77 (same day, later session), picking up
next-step #1 (measure channel-switch settle time vs. scan dwell) on a
fresh boot (kernel 7.2.7, generation 16, uptime ~12 min at session
start). Ran `tools/postboot.sh` first (netwatch watchdog + no-wpa-
restart udev rule were not yet active this boot - now are). No source
changes, no module reload; b43 was already loaded and associated
(`wlp3s0b1`, autoloaded by `b43-ac-load.service`) for the whole session.
USB stick backup path (`wlp0s20u1`) was up throughout, per project
convention.

## What was found

Triggering an `nmcli dev wifi rescan` on the already-associated
interface reproduced `b43-phy1: phy_ac: replayed vendor ch6 state
(121 radio, 250 PHY regs, 969 table entries)` +
`applied first-load state` in `dmesg`, ~2s after the rescan call.
Reading `phy_ac.c` (`b43_phy_ac_switch_channel`, around line 1165-1176)
shows this is fully expected, already-documented behavior: the
`b43_ac_replay`-captured vendor state (radio + PHY + ~1000 PHY table
entries + AGC tables + SHM) is re-applied **every time the radio
returns to channel 6**, unless `ac_state_once` is set - and the comment
already there says exactly why: "e.g. after each off-channel scan step
while associated."

**This matters because our AP's channel is 6.** Every off-channel scan
probe that returns to the home channel re-triggers this full, ~1300+-
register synchronous MMIO write burst - not a cheap retune like every
other channel gets. This lines up precisely with notes/77 Part 5's
observation that channel 6 (and 7, adjacent) were disproportionately
represented among the channels that failed `b43_mac_suspend()` during a
scan sweep - channel 6 uniquely carries this extra cost on every scan
revisit, on top of whatever the kernel-version-dependent regression
itself is doing. It's a plausible contributing factor to *why* channel 6
specifically shows up as failing, even if it's not the root kernel-side
cause notes/77 is still hunting.

Also confirmed live: the actual first association attempt this boot
(`16:27:49`-`16:28:00`, autoload time, before any of this session's
testing) already hit several `b43-phy1 ERROR: MAC suspend failed (40ms)`
- so the regression is still present and firing on this kernel/boot, as
expected, unrelated to anything done this session.

## `ac_state_once` live-tested (runtime sysfs, no reload) - inconclusive on failure rate

`ac_state_once` (`/sys/module/b43/parameters/ac_state_once`, `0644`,
default off) exists specifically to suppress this: "apply wl's captured
state only on the first switch to channel 6 per core init." Set it to
`1` live (no `rmmod`/`insmod`) and re-triggered a rescan: confirmed the
`replayed vendor ch6 state` line no longer appears on subsequent
returns to channel 6, with the connection staying up and RX packets
continuing to climb normally (no immediate ill effect).

**However**: no `b43_mac_suspend()` failures occurred in either the
"before" or "after" window this session (only the one cold-attach
failure at boot, well before any of this testing) - sample size here is
effectively zero for suspend failures either way, so this is **not** a
statistically meaningful A/B on failure rate, just a confirmation that
the knob works as documented and is safe to flip live. Reverted to `0`
(the documented default) at session end, matching project convention
of leaving runtime state as found unless a fix is actually confirmed.

## Where this leaves things

**Not proven**: whether `ac_state_once=1` actually reduces the 7.2.7
scan-triggered suspend-failure rate. It removes a real, heavy,
channel-6-specific MMIO burst that's a plausible aggravating factor,
but "plausible and removed" isn't "measured and confirmed" - needs a
real multi-attempt A/B test (same methodology as notes/76: several
connect attempts / scan sweeps, `ac_state_once=1` vs `=0`, counting
suspend failures each way) before calling it a mitigation.

**Also unresolved**: whether `ac_state_once=1` is safe from a
correctness standpoint long-term, not just "didn't visibly break in a
few minutes" - the vendor capture is a channel-6-specific snapshot; if
any of what it reapplies is expected to drift and need periodic
refreshing (e.g. calibration-adjacent state), skipping the reapply could
trade a scan-time hang for a slower, quieter correctness regression.
Nothing in this session's testing suggested that, but nothing rules it
out either - worth specifically watching AGC/RX-quality behavior over a
longer `ac_state_once=1` session, not just connection success/failure.

Part 6 of notes/77 (the RX-completely-empty-during-scan symptom) was
**not** re-checked this session - ran out of session time chasing this
thread instead. Still open.

## Next steps for a future session, in order

1. **The concrete, testable claim from this session**: run notes/76's
   A/B methodology (several connect/scan-sweep attempts, counting
   `b43_mac_suspend()` failures via `journalctl`/`dmesg`) comparing
   `ac_state_once=0` (current default) vs. `ac_state_once=1`, enough
   attempts to get a real failure-rate signal, not just 1-2 clean runs.
   `ac_state_once` is already `0644`/runtime-settable, so this needs no
   reload between arms, only sysfs writes.
2. If `ac_state_once=1` measurably helps: figure out whether it's safe
   to default on (check for drift/correctness issues per above,
   probably via a longer soak with the diagnostic hex-dump / rate
   counters, not just connect success), then flip its default in
   `phy_ac.c` and document why in this repo's notes, not just the sysfs
   description.
3. If it doesn't measurably help: notes/77's settle-time-vs-dwell
   theory (comparing actual channel-switch completion time against
   mac80211's per-channel scan budget, via `tools/hw_timing`/
   `tools/psmpc_fast`) is still the next-most-concrete lead, followed by
   a real `git bisect` in `~/src/linux` (confirmed to need local builds
   at every step, notes/77 Part 3).
4. Re-check notes/77 Part 6 (RX-completely-empty during an isolated
   scan) on a still-clean boot - still not re-verified.

## Current state at session end

No source changes. `ac_state_once` exercised live via its existing
runtime-settable (`0644`) sysfs parameter, reverted to its default (`0`)
before ending. `netwatch` watchdog and the no-wpa-restart udev override
(`tools/postboot.sh`) are now active for the rest of this boot (were not
before this session started). b43 remained loaded and associated
throughout - no `rmmod`/`insmod` cycling this session, per the standing
chip-degradation caution (notes/77's safety note, echoing notes/59). A
large (66 MB) raw `hw_timing` capture from this session's first test was
inspected and deleted (`test-logs/`, not committed) - nothing in the raw
register-tick samples themselves was informative; the useful signal was
in `dmesg`/`journalctl` timestamps instead.
