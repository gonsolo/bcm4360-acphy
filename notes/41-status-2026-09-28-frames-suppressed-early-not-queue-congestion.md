# Status 2026-09-28 (cont'd): found a new, robust symptom - many unicast data frames give up after 0-2 real attempts, well short of the configured retry limit

User returned, explicitly authorized riskier live work ("you can also do
riskier things, I can reboot"). Used that to trace the current zombie
connection (valid IP, ~10% ACK ratio, confirmed via the ACK-ratio watchdog
from notes/37 oscillating near its trigger threshold without quite firing)
with the same `b43_op_tx`/`b43_handle_txstatus` bpftrace technique from
notes/34/35.

## What was found

Traced live while pinging the gateway. The overwhelming majority of
outgoing encrypted QoS data frames (`fc=0x4188`) show:

```
TXHDR fc=4188 len=134
TXSTATUS cookie=203c fcnt=1 supp=5 acked=0
```

`supp=5` is `B43_TXST_SUPP_LIFE` in b43's existing (legacy-derived) enum -
"suppressed, frame lifetime expired." Critically, `fcnt` (frame transmit
count) is consistently **0-2**, far short of the confirmed-correct retry
limit (read live via the `scr` debugfs file: `SRLIMIT=7, LRLIMIT=4`,
exactly `B43_DEFAULT_SHORT_RETRY_LIMIT`/`LONG_RETRY_LIMIT`). Whatever is
happening, it is **not** the frame running out of its allowed retry count.

**Ruled out queue congestion as the cause**: repeated the trace with pings
spaced 2 full seconds apart (deliberately far below anything that could
back up the TX queue) - the same `supp=5`/low-`fcnt` pattern still
appeared on isolated, well-spaced individual frames. This is a genuine
per-frame issue, not a side effect of sending faster than the link drains.

Also observed, on other frame types captured in the same window:
- QoS Null keepalive/PM frames (`fc=0x11c8`/`0x01c8`, mac80211's own
  connection-monitor traffic): frequently `fcnt=7 supp=0 acked=0` - a
  **different** failure mode, genuine full-retry exhaustion with no ACK
  ever received (matching notes/34's original diagnosis), sometimes
  succeeding after 2 attempts.
- A directed probe request (`fc=0x0040`): `fcnt=1 supp=0 acked=0`.
- One frame with `supp=4` (`B43_TXST_SUPP_CHAN`, channel mismatch) -
  a single occurrence, plausibly a transient race with background
  scanning/channel-switch activity.

The presence of *varied*, semantically-plausible small values (4 and 5,
not just a single constant or noise) is mild evidence the `supp_reason`
bitfield decode (`(v0 & 0x00f0) >> 4` in `handle_irq_transmit_status()`)
is meaningful, though this has never been independently verified against
real AC-PHY hardware/ucode semantics (it was carried over from the legacy
b43 enum) - stated as an open caveat, not a settled fact.

## What this means

Regardless of the exact name/enum value, the robust, mechanism-independent
finding is: **a large fraction of outgoing unicast data frames are being
given up on by the firmware after only 0-2 real transmission attempts,
well short of the correctly-configured 7-attempt retry limit** - a
distinct failure mode from "genuinely retried the full limit and never
got ACKed" (which is what notes/34's original bpftrace diagnosis found for
mac80211's keepalive probes, and is still also happening, per the QoS-Null
frames above). Tonight's zombie-connection symptom is very plausibly the
combination of *both* mechanisms happening at once.

## Investigation attempted, not completed

Looked for a misconfigured "frame lifetime"/timeout value that could
explain premature suppression:

- `wlc_set_txh_info.c`/`wlc_get_txh_info.c` (already-decompiled AC TX
  header read/write helpers) - read fully; neither shows an obvious
  lifetime/expiry field being set. The AC-branch fields being
  read/written (VHT header pointer, PLCP-adjacent short values) look like
  rate/PLCP construction, not timing.
- This port's own `b43_generate_txhdr_ac()` (`xmit.c`) only populates a
  small subset of the 124-byte AC TX header body (prefix, mac_lo flags,
  chanspec, length, cookie, one rate entry) - the header is `memset()` to
  zero first and most of it is never explicitly written. If wl's real
  header format has a lifetime/duration field somewhere in the
  currently-untouched region, leaving it zeroed could plausibly mean
  "already expired" rather than "no limit" (by analogy with
  `B43_SHM_SH_PRMAXTIME`, where 0 means infinite but other timeout-style
  fields in this codebase don't all follow that same convention) - not
  confirmed.
- A quick, bounded search of the ucode disassembly for TSF-based frame
  aging logic didn't converge before deciding the effort was
  disproportionate to continue as an ad-hoc grep exercise.
- Realized `supp_reason` is read directly from a hardware TX-status
  register at completion (`handle_irq_transmit_status()`'s `v0`), not a
  ucode-maintained SHM counter like `txackfrm`/`txphyerr` - there may be no
  ucode *instruction* to trace at all; the actual decision could be made
  autonomously by the D11 core's own TX-engine hardware state machine.
  Checked the one directly-named, plausible candidate register,
  `IHR_TXE_TIME_OUT` (offset `0x083`, per `d11emu`'s own IHR table) live:
  reads `0x0a00` - nonzero, and not written anywhere in `b43-src`, so this
  is whatever the firmware/ucode itself configures at boot, not something
  this port is misconfiguring. **Ruled out as the cause** (absent knowing
  its exact unit scale, a plausible-looking nonzero value is at least not
  the obvious "left at zero" bug that was hoped for).

**Deliberately stopped here rather than guess-and-check a fix** for a
mechanism that isn't understood yet - matching this project's standing
practice.

## Current state

No code changes this round (read-only tracing and decompiled-source
review only). Chip currently loaded, associated (`b43-test`, valid IP,
degraded throughput) - left in this state for now since the user is
actively present and may want to continue from here directly rather than
having it reset.

## Next steps

1. **Properly trace where `supp_reason` (specifically value 5) gets set
   in the ucode**, the way notes/12 precisely traced `txackfrm++`/
   `txphyerr++` - this is the concrete way to either confirm or refute
   the "frame lifetime" interpretation and find what governs the
   threshold.
2. Cross-check `wlc_set_txh_info`'s AC-branch fields against the *full*
   124-byte AC TX header layout this port implements, to see if any
   currently-zeroed byte range corresponds to fields wl's real header
   populates - would need decompiling whatever function actually builds
   the AC TX header end-to-end on wl's side (not just the get/set-info
   helpers read so far), which hasn't been identified yet.
3. This is now a second, concrete, congestion-independent failure mode
   (early suppression) *in addition to* the original full-retry-exhaustion
   one (notes/34) and the RX-ring-refill gap (notes/38/39) - all three may
   be contributing to tonight's overall poor connection quality
   simultaneously. Worth keeping them conceptually separate when
   evaluating any future fix's effect.
