# Status 2026-09-29 (part 5): deep C-states ruled out as the 7.2.7 cause;
correction - the AP is on channel 11, not 6, notes/78's framing was wrong

Direct continuation of notes/80, same day, same boot. Starting a
deliberate "daily-use" plan (see the session's plan file) rather than
open-ended archaeology: Phase 1 is reliable connects on the *current*
kernel (7.2.7) - staying on 6.18.53 as a daily-use fallback was
explicitly ruled out by the user, so 6.18.53 remains reference-only for
A/B, never a destination.

## C-state / wakeup-latency theory: tested, ruled out

Diffed the 6.18.53 vs 7.2.7 kernel `.config`s from the Nix store
(`*-dev/lib/modules/*/build/.config`, read-only, no rebuild needed):
548 lines differ, almost entirely unrelated driver/subsystem config
(IOMMU page-table backends, PCIe host-controller drivers for other
silicon, debug options). `HZ`, `PREEMPT*`, `NO_HZ*`, `IOMMU`,
`PCIEASPM`, `IRQ_FORCED_THREADING` are all **identical** between the two
configs. `cpuidle` driver is `intel_idle`/`menu` with states C1 through
C10 (exit latencies 2us-2.6ms) - a real, plausible source of PCIe/DMA
wakeup-latency variance if the ucode's suspend-wait window collides with
a deep-C-state exit.

Live-tested (no reboot): disabled cpuidle states 3-8 (C3 through C10) on
all 4 CPUs via `/sys/devices/system/cpu/cpu*/cpuidle/state*/disable`,
then ran the same 5-attempt fresh-reload-and-reconnect test as notes/80
(`ab_reload_test.sh`, default module params). **Result: 1/5 connected,
suspend-failure counts 12/15/12/18/10 per attempt - same range as the
baseline (8-14), arguably slightly worse.** No improvement. C-states/
CPU wakeup latency is **ruled out** as the regression's cause. Reverted
all `disable` files to `0` (default) immediately after.

Combined today's reload testing: baseline 3/5 + `ac_state_once=1` 1/5
(notes/80) + C-states-blocked 1/5 (this note) = **5/15 (33%)** across 15
total fresh-connect attempts - consistent with notes/76's original 0/5
to ~40% range throughout, no drift, no improvement from either lever
tried today.

## Correction: the AP is on channel 11, not channel 6

Checked live (`iw dev wlp3s0b1 info` on a natural, non-`connect_test.sh`
association): **`channel 11 (2462 MHz)`, no HT** - the actual AP
(Vodafone-2A84, `8c:6a:8d:9e:2a:88`) operates on channel 11. notes/78's
central claim ("our AP's channel is 6, so channel-6 revisits are
special") **was wrong** - I never actually checked the AP's real
channel, I inferred it from seeing the ch6-replay log line fire
constantly and assumed causation the wrong way around.

**What's actually true, corrected:** `CH=6` in `b43_live.sh`/
`connect_test.sh` is a **fixed staging channel** the driver is
temporarily parked on (monitor mode) during every single module
bring-up, completely independent of the AP's real channel - that's why
the replay fired on *every* fresh-load test today (15/15 today, not
just some), not because of anything scan- or AP-channel-specific. The
mechanism itself (returning to channel 6 re-triggers the full vendor-
state replay, per `phy_ac.c` ~line 1169, confirmed real in notes/78) is
still correct and still real, and it's *more* central to every fresh
connect than notes/78-80 gave it credit for - it's not an occasional
scan-collision, it's a guaranteed part of *every single bring-up's*
channel history (stage on 6, then move to whatever the AP's real
channel is, here 11). But the "channel 6 specifically fails more during
scans because that's our AP's channel" reasoning in notes/78 does not
hold - notes/77 Part 5's channel 6/7 scan-failure observation needs to
be re-read as "channels near the *staging* channel," not "channels near
the AP," if that distinction matters at all going forward.

This doesn't change notes/80's core finding (`ac_state_once` can't
differ on a single fresh connect, confirmed by code, independent of
which channel is involved) - it only corrects the causal story
around *why* channel 6 showed up as special.

## Also noted: no HT on the live link

`iw dev wlp3s0b1 info` shows `width: 20 MHz (no HT)` on the current
natural connection - legacy 802.11g-equivalent rates only (18 Mbit/s RX,
6 Mbit/s TX in `iw link` at the time), not 802.11n. Out of scope for the
reliability work but flagged for the plan's Phase 3 (throughput) - band/
HT-capability registration in `main.c`/`phy_ac.c` needs a look.

## Where this leaves Phase 1 (reliable connects on 7.2.7)

Both cheap, non-invasive levers tried today (`ac_state_once`, deep
C-states) are now ruled out or unproven-and-costly to test properly.
Per the plan, next is Phase 1b: capture mac80211 `drv_*` tracepoints and
`b43_mac_suspend` timing during a real connect on 7.2.7 and (ideally) a
reference capture on 6.18.53, to see whether mac80211 is actually
driving b43 differently - a more targeted question than another blind
reload-count A/B. Not started this session - needs either a live ftrace
capture setup or the one-off 6.18.53 reference boot flagged in the plan
(user's call, since it's a reboot).

## Current state at session end

No source changes. All live sysfs overrides from today (`ac_state_once`,
cpuidle `disable` flags) reverted to defaults. `kernel.panic_on_oops=1`
and related panic sysctls still enabled (standing test-session state).
netwatch still active. Connection currently up (`b43-test` profile, from
Arm C's attempt 5). 15 total `rmmod`/`insmod` cycles today across
notes/80-81 combined - noted per the standing chip-degradation caution;
no crashes, no `wl` regression signal, machine stable throughout.
