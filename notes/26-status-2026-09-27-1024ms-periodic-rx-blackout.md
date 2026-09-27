# Status 2026-09-27 (late evening, continued further still): a precise, recurring ~1.024s RX blackout - likely 1000 802.11 Time Units

Direct follow-up to notes/25, same evening, pushing further per explicit
user instruction. Set out to characterize whether the intermittent
steady-state RX gaps found in notes/25 are periodic or random. Found
something much more specific than expected.

## Method

Captured steady-state reception (radio parked on channel 6, no switching,
no scanning) for 90 seconds in one session and 60 seconds in a second,
independent, freshly-reloaded session. Extracted every gap between
consecutive received frames from the AP and flagged anything over 150 ms
as abnormal (matching notes/25's threshold).

## Finding: a precise, repeating ~1.02-1.03 second blackout, far too consistent to be random

The first (90 s) capture showed 191/1195 gaps (16%) over 150 ms, with a
strikingly regular alternating ~0.77 s / ~0.26 s pattern for roughly 15
seconds in the middle of the capture (t=60-75 s), repeating almost
exactly every ~1.03 s.

The second (60 s), completely independent, freshly-reloaded capture
showed 102/531 gaps (19%) over 150 ms, and specifically **twelve
individual gaps clustered extremely tightly around 1.02-1.03 seconds**:
1.002, 1.026, 1.020, 1.023, 1.024, 1.030, 1.021, 1.023, 1.032, 1.014,
1.012, 1.024 (all seconds). A 30 ms spread across twelve independent
occurrences, in a second, unrelated capture session, is not something
random jitter produces - this is a real, deterministic, repeatable
period.

**1.02-1.03 seconds is essentially exactly 1000 802.11 Time Units** (1 TU
= 1024 µs by the 802.11 spec, so 1000 TU = 1.024 s). This is a
suspiciously round number in 802.11's own native timing unit, not an
arbitrary duration - strongly suggesting a real TU-based timer or
interval configured to (or defaulting to) 1000 somewhere in the
firmware/ucode or this port's SHM/PHY setup, rather than coincidence.

The *onset timing* of individual blackout events is less regular than
their *duration* - sometimes back-to-back (e.g. two ~1.02 s blackouts
essentially adjacent), sometimes several seconds apart - consistent with
a fixed-duration recalibration/housekeeping routine that gets *triggered*
somewhat irregularly (possibly retried, or triggered by a
condition-based check) but always runs for the same ~1.024 s once
started, rather than firing on a strict, unconditional 1.024 s clock.

## What was ruled out as an explanation

- **Not the port's own periodic debug dump** (`macstat`/`gpio`/`MACCTL`
  logging seen throughout this evening's dmesg): that fires roughly every
  15-16 seconds, a completely different cadence.
- **A blind SHM-register poll** at one arbitrarily-chosen address showed
  a constant, non-counting value - uninformative, and not pursued further
  since guessing addresses without a documented map isn't a sound method.
- **`b43_set_beacon_listen_interval()`/power-save TU-based intervals**
  were considered (this is exactly the kind of code that would use a
  raw TU count) but the driver is in monitor mode, never associated, for
  all of tonight's testing - standard listen-interval/power-save
  scheduling shouldn't apply here, though this hasn't been definitively
  ruled out at the firmware level.

## Why this matters

This is now a specific, well-evidenced, *mechanistically concrete*
candidate for why scanning fails (notes/24) and why steady-state
reception is intermittently unreliable (notes/25): a recurring ~1-second
RX blackout, precise enough to strongly suggest a genuine periodic
firmware/hardware process (very plausibly the never-ported AC-PHY
periodic calibration state machine flagged since notes/16,
`wlc_phy_cals_acphy`, or some other TU-scheduled housekeeping routine),
rather than generic flakiness. A scan's short per-channel dwell window
landing inside this ~1 s blackout would reliably fail; over several
visited channels, near-certain failure follows.

Whether the *same* routine also disrupts transmission (the project's
original, long-standing core question) is still unknown - not tested
tonight, and not something the current `probeack.sh`/ucode-counter
tooling is well suited to catching for a transient, sub-2-second event.

## Deliberately not pursued further tonight

Finding the *exact* firmware/ucode source of this timer would need
dedicated ucode-level tracing or disassembly (this project has done this
kind of work before, notes/12-14), not further ad-hoc register guessing.
Given this project's own established caution around deep register/ucode
probing (the one hard-freeze precedent, documented in `[[wifi-live-testing-safety]]`
memory and referenced throughout the notes), this is deliberately being
left as a well-defined, well-evidenced next step for a dedicated session
rather than continued blind probing tonight.

## Next steps for a future session

1. **Correlate the blackout with ucode/SHM state directly**, using the
   already-proven-safe `trace_wl.sh`/`wl_full_trace.bt` bpftrace
   technique (reads `wl`'s own real behavior without touching PCI
   binding) to see whether the real vendor driver shows the same
   ~1.024 s-periodic pattern, and if so, what SHM/PHY/radio register it
   touches on that cadence - this would very plausibly reveal the timer
   directly, safely, without register guessing on the live b43 port.
2. **Check for a corresponding TX effect** during a deliberately-timed,
   short TX burst test aligned to when a blackout is expected/observed,
   to see whether transmissions attempted during one of these windows
   fail characteristically differently from ones outside it - this would
   be the first direct test connecting this finding to the project's
   central open question.
3. Search the decompiled `wlc_phy_cals_acphy` material (referenced but
   never fully decompiled/ported, per notes/16) specifically for a
   1000-TU or similarly-valued periodic trigger, now that there's a
   concrete duration to search for instead of a vague "periodic
   calibration" description.
4. The scan-finds-nothing (notes/24) and general intermittent-RX
   (notes/25) findings are best understood as downstream symptoms of
   *this* more specific finding, not separate mysteries.
5. Loft-comp calibration question (notes/22) remains fully open and
   untouched.

## Session close

No crashes, no dmesg BUG/Oops/panic lines. USB backup link 0% packet
loss throughout and at close, verified after every reload tonight. No
source changes from tonight's continued investigation (notes/24, 25, and
this note) - only `b43_live.sh`/`iw`/`tcpdump` invocations and read-only
analysis. `b43` unloaded cleanly; chip left on `bcma-pci-bridge`. `wl`
remains restored and working normally from earlier this evening.
