# Status 2026-09-28 (cont'd): channel 11 soak confirms ~7-10% residual loss is not explained by ac_state_once

Follow-up to notes/50/51. Router set to automatic channel selection
(picked channel 11) once channel 1 was confirmed fixed.

## Channel 11, default params (`ac_state_once=0`)

Fresh load, one connection, 5-minute soak: **ARP 103/110 (94%), IPv6
ping 102/110 (93%)**. No restarts, no kernel warnings, NM state 100
throughout. Matches channel 6's earlier figure (notes/50: 91%/94%)
closely - the residual loss is not channel-6-specific.

## Channel 11, `ac_state_once=1`

Same test: **ARP 103/115 (90%), IPv6 ping 106/115 (92%)**. Statistically
indistinguishable from the default-params run above.

## Interpretation

notes/50 proposed the wl-snapshot reapplication on every return to channel
6 during background scans (`b43_phy_ac_apply_por`/`replay_ch6`, gated on
`new_channel == 6`) as the leading suspect for residual loss, and
`ac_state_once` was written to test it. But that gate only fires when the
*scan* touches channel 6 - on a connection actually running on channel 11,
it fires at most briefly during off-channel scan dwells on 6, not on the
operating channel. This test shows the same ~7-10% loss rate on channel 11
regardless of `ac_state_once`, so **that mechanism is not the (or not the
main) explanation** for the residual loss. The hypothesis from notes/50 is
weakened, not confirmed - same pattern as notes/43's SHM-0x3E correction
earlier tonight.

## Current state

Chip loaded and connected on channel 11 (whatever the router currently
picks), `ac_state_once=1` still set from this test. USB backup link
confirmed working throughout both soaks.

## Next steps

1. A cleaner test of the reapplication hypothesis would need the
   connection actually running on channel 6 (not just present in the scan
   list), which needs the router pinned there again - not requested this
   round.
2. More likely explanations for the general ~7-10% loss, not yet checked:
   ordinary background-scan interruptions during otherwise-idle probe
   windows (a scan step just happened to overlap the ARP/ping attempt),
   or genuine RF-level loss at normal WiFi operating margins. Correlating
   probe misses against `switch_channel` timestamps in dmesg would
   distinguish these - not done yet (blocked mid-investigation by a
   transient tool failure).
3. `ac_state_once` can stay as an available option; it just isn't shown to
   help here. Not reverting the default (already off) without more
   evidence either way.
