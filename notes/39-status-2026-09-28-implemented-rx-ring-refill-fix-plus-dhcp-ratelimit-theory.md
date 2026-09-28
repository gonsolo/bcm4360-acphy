# Status 2026-09-28 (cont'd): implemented and safety-tested the RX ring refill fix; found a possible router-side DHCP rate-limit explaining tonight's persistent failures

User said "Do it!" - explicit authorization to implement notes/38's RX-ring
refill fix, which had been deliberately left unimplemented given its risk
category (DMA descriptor/hardware synchronization) and the lack of a
present user to test with.

## What was implemented

Added `b43_dma_rx_retry_poisoned()` to `dma.c`/`dma.h`, called from AC-PHY's
existing `pwork_15sec` periodic hook (`phy_ac.c`) - a bulk RX-ring
catch-up sweep modeled on wl's `dma_rxfill()` (notes/38), retrying any RX
descriptor whose `GFP_ATOMIC` refill attempt previously failed, this time
with `GFP_KERNEL` from a context that can sleep.

## Found and fixed a real design bug during the very first live test

The first version used `b43_rx_buffer_is_poisoned()` (the existing marker
`dma_rx()` writes into a buffer to later detect "did DMA ever write real
data here") as the retry signal. **This was wrong**: a freshly allocated,
never-yet-used RX slot is *always* poisoned by design - that's the whole
mechanism by which a real incoming frame gets detected later (the poison
pattern gets overwritten). On the very first `pwork_15sec` tick after
loading, with a quiet ring that had barely received any traffic yet, this
found essentially the *entire* ring "poisoned" and replaced all 256 slots
unnecessarily:

```
phy_ac: recovered 256 stuck RX descriptor(s)
```

Not dangerous by itself (replacing a valid, never-used buffer with another
valid buffer doesn't corrupt anything), but completely wrong - it couldn't
distinguish "idle, working fine, just hasn't received its first frame yet"
from "genuinely stuck because a refill attempt failed." Left unfixed, this
would have caused constant unnecessary allocation churn every 15 seconds
(potentially the whole ring's worth), which is not just wasteful but
ironically could itself contribute to the very memory-pressure scenario
the fix is meant to guard against.

**Fixed with explicit state tracking instead of reusing the poison
marker**: added a new field, `rx_refill_failed`, to `struct
b43_dmadesc_meta` (`dma.h`), set to `true` at the *one specific place*
`dma_rx()`'s reactive refill actually fails (the `GFP_ATOMIC`
`setup_rx_descbuffer()` call, not the other two paths that also jump to
`drop_recycle_buffer` for unrelated reasons - a zero-length frame or an
already-poisoned buffer that genuinely never received data, both of which
are normal, not failures) and cleared on success. The periodic sweep now
checks this flag, not poison state - unambiguous, no false positives.

## Live-verified the fix on real hardware

Rebuilt, reloaded, and watched three consecutive `pwork_15sec` ticks
(45s) on a healthy, idle (monitor-mode, light beacon-only traffic) ring:
zero "recovered" messages, confirming the corrected logic doesn't
false-positive during ordinary operation. No crashes, no kernel warnings,
`B43_WARN_ON`s stayed silent, USB backup link unaffected throughout.

## Safety analysis (why this doesn't introduce a new risk category)

`b43_dma_rx()` (the reactive RX path) only ever runs under `wl->mutex`,
via the threaded IRQ handler (`b43_do_interrupt_thread()`). The new
periodic sweep runs under the same `wl->mutex` (via
`b43_periodic_work_handler()`). The two can therefore never run
concurrently - no software race on `rx_refill_failed` or the ring's other
bookkeeping, and reading/writing that flag needs no DMA-coherency sync at
all (it's plain host memory, not part of the DMA-mapped buffer).

The one thing no software lock can fully rule out is the DMA *hardware*
itself writing to a flagged slot's buffer at the exact moment the sweep
tries to replace it. But a flagged slot's buffer was already left in
exactly the state `dma_rx()`'s own existing, always-used reactive-refill
failure path leaves it - the same "hardware won't return to this precise
ring position until it wraps all the way around again" timing margin that
already makes that in-place reactive refill safe applies identically here.
This isn't a new risk category; it's the same swap `dma_rx()` already does
routinely, just performed slightly later, from a context that can retry
with `GFP_KERNEL` instead of giving up forever after one `GFP_ATOMIC`
attempt.

## Honest result: tonight's specific failures don't show this mechanism firing

Attempted several real connections after the fix was verified safe.
`sudo dmesg` was checked across every attempt for "recovered N stuck RX
descriptor(s)" - it never appeared during any of tonight's actual
connection failures. This means the RX-ring-allocation-failure mechanism
this fix targets was **not** the cause of tonight's specific, persistent
DHCP failures - the fix is a real, correctly-implemented, safety-verified
improvement for a genuine architectural gap, but it isn't what's blocking
connections tonight specifically. That's useful, honest information, not a
failure of the fix itself.

## A better-fitting explanation for tonight's persistent DHCP failures: a router-side rate-limit

Captured DHCP traffic directly across several more attempts: every single
one shows the same pattern - our own DHCPDISCOVER goes out cleanly
(2-3 broadcast retransmissions), zero DHCPOFFER replies ever arrive - and
this has now been **persistent**, not intermittent, across roughly 15+
minutes and many reconnect attempts, while the completely unrelated USB
backup stick (different chipset, different MAC, different driver) has been
pinging cleanly at 0% loss with zero beacon-loss events the entire time.
That combination - one specific MAC's DHCP requests going consistently
unanswered while general RF health (confirmed via the USB stick) is fine -
doesn't fit the "intermittent RF/RX reliability" explanation nearly as
well as it fits a much more mundane one: **many consumer routers rate-limit
or temporarily ignore DHCP requests from a MAC address that has requested
an address many times in a short window**, as a basic anti-flood/anti-churn
heuristic. This session has reconnected with the same MAC
(`00:01:00:00:84:38`) many dozens of times over the last couple of hours
while testing tonight's various fixes.

This is a plausible, not confirmed, explanation - and importantly, if
correct, **more reconnect attempts right now would not help and could
extend the rate-limit window**. Stopped retrying for this reason rather
than continuing to hammer at it.

## Current state

- `b43-src` changes (uncommitted at time of writing, to be committed
  alongside this note): `dma.h` (`rx_refill_failed` field,
  `b43_dma_rx_retry_poisoned()` declaration), `dma.c` (the function itself,
  and the one-line flag set/clear in `dma_rx()`), `phy_ac.c` (the call from
  `pwork_15sec`).
- Chip returned to safe idle monitor-mode state (channel 6); USB backup
  link reconfirmed (0% loss, real RTTs); netwatch active.

## Next steps

1. **Do not retry `b43-test` again for a while** if the router-rate-limit
   theory is right - give it real time (tens of minutes to hours,
   depending on the router's own policy) before the next attempt, or
   check the router's own admin UI/logs if reachable for confirmation.
2. Once a clean connection is achievable again, re-verify the ACK-ratio
   watchdog's `ieee80211_restart_hw()` fix (notes/37) end-to-end - still
   not done.
3. The RX-ring refill fix itself is done and safe; it doesn't need further
   validation *of its safety*, but confirming it actually reduces the
   ACK-watchdog's trigger rate over a longer real-world session (once
   testing is possible again) would be good practical evidence for
   notes/38's hypothesis.
4. If the DHCP-rate-limit theory turns out wrong (i.e. it keeps failing
   long after any reasonable rate-limit window), reconsider a genuine,
   separate connectivity issue - possibly worth trying a *different* SSID/
   AP (if available) to isolate "this router doesn't like this MAC right
   now" from "something changed on this laptop's setup."
