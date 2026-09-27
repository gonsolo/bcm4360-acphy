# Status 2026-09-27 (late evening, continued further): the RX outage is not a channel-switch bug - it's general, intermittent PHY/RF flakiness

Direct follow-up to notes/24, same evening, pushing further per explicit
user instruction ("keep going"). Set out to find exactly where, in the
software stack, the post-channel-switch RX outage happens. Ended up
reframing the finding entirely: it isn't really about channel switching.

## Precise, kernel-side outage measurement (not tcpdump-latency-limited)

Added temporary `ktime_get()` instrumentation (reverted before
committing - no net source change, see below) that timestamps the exact
moment a channel switch is issued and logs the elapsed time to the first
hardware interrupt of any kind afterward, read directly in the top-half
IRQ handler (`b43_do_interrupt()`, `main.c`). This avoids all the
userspace/tcpdump subprocess-launch latency that made earlier estimates
(notes/23, "~100-350 ms") rough.

Repeated real switches (channel 1 -> sleep -> channel 6) and measured the
delay to the first interrupt (always `reason=00008000`
[`B43_IRQ_DMA`], `dma0=00010000` [`B43_DMAIRQ_RX_DONE`] - genuinely an
RX-completion interrupt, not some unrelated event):

34.6 ms, 40.4 ms, 60.8 ms, 150.8 ms, 165.1 ms, 180.6 ms, 457.3 ms, and
two trials that didn't fire at all within a 2.5 s window.

**This spread (34 ms to 2.5+ s) is far too wide and non-deterministic to
be a fixed hardware settling/calibration time.** A real VCO-lock or
AGC-settling delay would be consistent trial to trial; this isn't.

## Cross-check: the IRQ timing is a real proxy for reception, not a coalescing artifact

Worried the measurement might just reflect RX-interrupt coalescing
(`intrcvlazy0`, visible in this port's periodic debug dumps) rather than
real reception - i.e. frames arriving normally but the interrupt itself
being delayed/batched. Ran a real packet capture (`tcpdump`) concurrently
with the same instrumented build: kernel-measured first IRQ at 60.8 ms,
first actually-captured frame at 90 ms. Same order of magnitude, capture
slightly later (consistent with tcpdump's own process-launch overhead,
not an inverted "frames arrived earlier than the interrupt" pattern).
This is evidence the IRQ timing genuinely tracks when reception starts
working again, not just when a lazy interrupt timer happens to fire.

## The real finding: this happens in steady state too, with no channel switch at all

Captured 30 s of frames from the AP with the interface parked
continuously on channel 6, no switching at all, and measured the gaps
between consecutive received frames (453 frames total):

| gap size | count |
|---|---|
| < 150 ms (normal) | 402 |
| 150-500 ms | 27 |
| 500 ms - 1 s | 20 |
| 1-2 s | 3 |
| > 2 s (seen in an earlier 15 s sample) | 1 (3.65 s) |

**About 11% of all inter-frame gaps are abnormally long** (150 ms to
several seconds), even with nothing about the channel or tuning changing
at all. This is a genuine, general, intermittent PHY/RF reception
reliability problem - not something specific to the moment right after a
channel switch.

## Reconciling both observations

Every one of the 9 direct post-switch timing trials showed *some*
nontrivial gap (none were near-instant) - a much higher hit rate than the
~11% steady-state background alone would predict for random chance. The
most likely reading: **switching to channel 6 (the retune itself, or the
state replay/reset that goes with it) appears to reliably trigger or
coincide with one of these same intermittent RX dropouts, on top of the
~11% baseline rate that exists anyway during ordinary, untouched
operation.** This would fully explain why scanning (which needs a clean,
short dwell window on every visited channel) fails so consistently: it's
not fighting a fixed multi-hundred-ms settling delay, it's repeatedly
running into the same kind of dropout that happens anyway roughly one
time in nine even without touching the channel, at each of several
channels visited per scan, compounding into near-certain failure.

## Why this might matter for the project's central, long-standing question

This has **not** been shown to be the same mechanism as the long-standing
TX/firmware-autonomous-ACK problem - they are still, formally, two
separate observations. But an intermittent, general PHY/RF reliability
issue that affects *reception* is at least plausible as evidence of a
shared, flaky front-end/AGC/calibration stage that could *also* affect
*transmission* reliability, which is exactly the project's central open
question. This is a real, new, well-evidenced candidate worth keeping in
mind - not a confirmed unification, but a genuinely promising lead that
didn't exist before tonight.

## Diagnostic code

All instrumentation (`ktime_get()` calls and `b43info()` diagnostic
prints in `main.c`, plus the switch_channel-internal timing in `phy_ac.c`
from notes/24) has been reverted before every commit tonight - none of it
belongs in the tree; it was scaffolding to answer specific questions and
is fully described here and in notes/24 instead. `git diff --stat
b43-src/` was confirmed clean before each commit.

## Next steps for a future session

1. **Characterize the steady-state dropout more precisely**: is it
   periodic (a recurring calibration/re-lock cycle on some interval,
   which would show up as fixed-interval gaps) or genuinely random? A
   longer capture (several minutes) with gap-time autocorrelation would
   answer this cheaply.
2. **Check whether TX shows the same pattern.** If host-queued TX
   (already documented as working) *also* shows an ~11% rate of failed/
   delayed transmissions on close inspection, that would be a strong,
   concrete link to the ACK/firmware-autonomous-TX problem. This wasn't
   tested tonight - the existing `probeack.sh`/ucode-counter tooling
   isn't well-suited to catching brief, intermittent TX failures the way
   this evening's frame-gap analysis caught RX ones.
3. Revisit whether AC-PHY's periodic calibration state machine
   (`wlc_phy_cals_acphy`, flagged as never-ported since notes/16) is
   specifically responsible for periodic RX (and possibly TX) glitches -
   this reframing makes that old, previously-deprioritized hypothesis
   worth another look, now with a concrete, measurable symptom (frame
   gaps) to test it against instead of a flat/inconclusive measurement.
4. The scan-finds-nothing symptom (notes/24) is very likely explained by
   this finding rather than needing a separate root cause - not fully
   proven, but no longer treated as a mystery requiring its own fix.
5. Loft-comp calibration question (notes/22) remains fully open and
   untouched by tonight's work.

## Session close

No crashes, no dmesg BUG/Oops/panic lines throughout tonight's continued
testing. USB backup link 0% packet loss throughout and at close. All
diagnostic instrumentation reverted before every commit - no net b43-src
changes from tonight's post-notes/23 investigation, notes and memory
only. `b43` unloaded cleanly; chip left on `bcma-pci-bridge`. `wl`
remains restored and working normally from earlier this evening.
