# Status 2026-09-28 (cont'd): fixed a real design flaw in the ACK-ratio watchdog's counter logic

Direct follow-up to notes/37/40/41. Watching the watchdog live against the
currently degraded connection (severe, ~5-30% ACK ratios per window,
per notes/41), it kept resetting from 1/3 or 2/3 consecutive bad windows
back to 0 without ever reaching the 3-window trigger, despite the
connection clearly being in bad shape throughout.

## The bug

`b43_phy_ac_check_ack_watchdog()`'s "not enough frames this window to
mean anything" branch (`d_all < B43_AC_ACKWD_MIN_FRAMES`) was resetting
`ack_ratio_bad_windows` to 0 - treating "inconclusive, too little data" the
same as "genuinely fine". With sparse or bursty traffic (ordinary
application usage, or - notably - the effect of notes/41's own
early-suppression bug, which reduces the number of real TX attempts per
failed frame and so can itself lower the per-window frame count below the
20-frame minimum), a quiet window falling between two genuinely bad ones
would erase the streak, making the watchdog far less likely to ever
accumulate 3 truly consecutive bad windows - exactly the situation
observed live tonight.

## The fix

Changed the idle-window case to leave `ack_ratio_bad_windows` unchanged
(just skip the window) instead of resetting it to 0. A window is only
still reset by genuine evidence of health - a window with enough traffic
that *does* show a good ACK ratio (the existing `else` branch, unchanged).

Rebuilt, reloaded, and tested live: generated 90s of sustained IPv6 ping
traffic. No crash, no misbehavior; the streak now correctly persists
across quieter ticks (observed real windows at 1/3, 2/3, back to 1/3 -
that reset was into a *good* window this time, not an idle one, which is
correct behaviour). Did not observe an actual 3/3 trigger in this specific
test window - tonight's connection quality fluctuates (one 5-ping burst
got 1/5 through just now, versus 0/8 a few minutes earlier), so this
wasn't a clean pass/fail test of the fix's practical effect, but the
counter logic itself is now demonstrably correct where it was previously
wrong.

## Current state

Chip loaded and associated (`b43-test`, IPv6 only, IPv4 DHCP still not
obtained this session - consistent with notes/40's asymmetry finding).
USB backup link functional throughout. No hardware risk taken beyond what
was already covered by notes/37's original safety analysis (this is a
pure software counter-logic change, no new register access).

## Still open

- The actual root cause(s) - the early-suppression mechanism (notes/41)
  and the missing RX-ring periodic refill (notes/38, mitigated in notes/39)
  - remain the deeper work. Tonight's fixes are all mitigations/
  instrumentation-quality improvements around the edges of a problem
  that's still not fully understood.
- Whether the corrected counter logic meaningfully improves real-world
  recovery frequency needs a longer observation window than was available
  tonight.
