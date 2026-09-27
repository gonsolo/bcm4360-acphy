# Status 2026-09-27 (continued again), independent capture confirms firmware ACKs never radiate

Per the user's explicit go-ahead ("Do it. But make it so that if something
goes wrong a simple reboot will help"): got a real, independent, over-the-
air answer to whether our firmware's ACK transmissions actually leave the
antenna at all, using the USB stick (`wlp0s20u1`, mt76x2u) as an
independent monitor while the internal chip (b43) ran the usual
`probeack.sh` test.

## Safer than expected: no connectivity risk at all

Worried this would need tearing down the USB stick's managed connection
(this session's only network path while the user is away), with a
self-healing detached script as the fallback plan. Turned out unnecessary:
`iw phy phy1 interface add usbmon type monitor` succeeds *concurrently*
with the stick's existing connected managed interface - confirmed with
0% ping loss throughout. The stick's own AP association was already on
channel 1, exactly matching the test channel, so no channel switch was
needed either. This session's own network connectivity was never at risk.
(Cleanly removed `usbmon` afterward; `b43` unloaded; internal chip back on
`bcma-pci-bridge`, idle.)

## Result

Ran `probeack.sh` (N=30, channel 1, home AP) while `usbmon` independently
captured everything nearby with `otherbss` (announced from a
physically-adjacent but electrically separate radio - strong signal for
both the AP and our own internal chip, ~-18 to -29 dBm for our own
transmissions specifically, confirming no antenna-desense/proximity issue
that could suppress reception).

- **29 of our own outgoing Probe Requests captured cleanly** (`SA` = our
  b43 MAC, `00:01:00:00:84:38`) - confirms, independently, that host-
  generated TX from this chip really does radiate a valid signal reliably,
  as this whole project has assumed.
- **38 total Acknowledgment frames captured.** ACK frames have no source
  address field (just FC/Duration/RA/FCS), so "who sent it" has to be
  inferred from *who it's addressed to* (RA): 28 have `RA` = our own MAC
  (the AP acking our probe requests - expected, matches the ~29-30 probes
  sent), 10 have `RA` of two unrelated neighboring devices (ordinary
  nearby traffic, one a Raspberry Pi OUI). **Zero have `RA` = the AP's MAC
  (`8c:6a:8d:9e:2a:88`)** - i.e. zero captured evidence, anywhere, of our
  own firmware successfully acknowledging any of the 107 Probe Responses
  we received in this same window, despite `txackfrm` incrementing by
  ~120 (ucode believes it sent that many acks).

## What this means

This is the first *methodologically sound* over-the-air evidence in this
project (the earlier same-radio monitor attempt in notes/14 was
uninformative by construction - half-duplex). Given host TX from the same
chip demonstrably radiates fine and gets captured cleanly under identical
conditions, the clean absence of any AP-directed ACK from us - not even a
partial, garbled, or malformed one that a very-close, sensitive monitor
would still register as *some* transmission - is real, direct support for
the hypothesis this whole investigation has converged on from a different
direction (notes/09-14's hardware/ucode analysis): **the firmware's
autonomous ACK transmission attempt does not produce a valid RF signal at
all**, not merely "a signal the AP fails to decode." This is more specific
than "PHY reports an error" - it suggests the failure is at or before the
point where a real signal would leave the antenna (consistent with an
analog TX-path/calibration problem, not a digital framing/encoding bug,
since a digital-only bug would more plausibly still radiate *something*
detectable nearby even if the AP itself can't decode it).

## Caveats

- One test run, N=30, one set of conditions (channel 1, rate 12/6 Mbps,
  home AP). Didn't repeat to check consistency the way notes/13 did for
  the SHM diagnostic record - worth another run before treating "zero
  ever" as fully certain rather than "zero in this one capture."
- Can't rule out a very-low-power or very-short transmission that a
  monitor a few dozen centimeters away still fails to catch, though this
  is a materially higher bar than "the AP fails to decode it" and the
  detection sensitivity here (partial neighbor traffic from further away
  was captured fine) argues against a simple sensitivity gap.
