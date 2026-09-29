# Correction: the 0xEC0 timer block is unconditional periodic housekeeping, not failure-specific

Direct follow-up to notes/69, same session - retracts that note's framing
in one specific way while keeping the underlying discovery.

## What changed the picture

Added the timer block's registers (`IHR[0x150]`, `0x151`, `0x155`,
`0x156`, `0x159`) and its gate (`IHR[0x47]`) to `tools/hw_timing.c` and
watched them live, with real timestamps, across several real connect
attempts including the gaps between them.

`IHR[0x150]` toggles `0x0002`/`0x0000` on a steady **~0.94 second**
rhythm - and critically, **it keeps ticking straight through a 12-second
idle gap between two failed attempts**, when no auth frame was in
flight at all. A separate 6-second capture with the interface fully
*down* (no attempt in progress, not just between retries) showed zero
ticks.

## The correction

notes/69's "changed during failure, not during success" framing was a
window-length artifact, not a real difference. A successful attempt
completes in ~50ms - faster than even one tick of a ~0.94s-period
routine can occur - so of course a before/after snapshot pair 50ms apart
never caught it firing. A failed attempt spans several seconds of
retries, long enough to contain multiple ticks. The diff wasn't
comparing "cause of failure" against "absence of it" - it was comparing
a window too short to contain even one sample of ordinary background
activity against one long enough to contain several. Exactly the kind
of artifact the causal-direction check (established in notes/68 for the
`ihr97`/`0x0d74` lead) exists to catch - applied it here too, on my own
newer finding, before letting it stand uncorrected.

## What's real and kept

The routine itself, its ~0.94s period, and its independence from
auth success/failure are all real, timestamped, directly-measured
findings - not corrected away, just reframed. This is very plausibly the
real periodic watchdog/recalibration timer `phy_ac.c`'s own comment
(notes/27-31/34) has flagged as missing from this port for days: "wl
runs a real periodic watchdog... ~1.024s cycle doing DMA-error recovery
and PHY/ACI recalibration." 0.94s measured here is in the right range
given normal timer/measurement slack. Locating and timing it is real,
useful progress toward that older open question, independent of
whether it turns out relevant to tonight's auth-reliability thread.

## Honest status

The `0xEC0-0xF30` block is not (on current evidence) part of why auth
attempts fail. It's unconditional background housekeeping present
whenever the radio is up, in both successful and failing scenarios
alike. Whether *what it does* (real elapsed-time arithmetic reaching a
second NAP at `0xF2E`, notes/69) matters for reliability is now a
separate, calmer question than "does it only run on failure" - and would
need actually decoding what the computed value drives (a recalibration
trigger? a timeout/backoff value?), not just when it fires.

This closes out the live-timing thread for tonight on an honest note:
real tooling built and left in the repo (`hw_timing.c`,
`full_snapshot.c`), a real background mechanism found and timed, and an
honest self-correction of an overclaim before it could mislead a future
session.
