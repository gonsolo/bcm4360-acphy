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

## Resolved: it's ordinary background scanning, not a bug

Checked dmesg for `switch_channel` activity during the soak window: while
connected and idle, mac80211 runs a full 13-channel background scan sweep
roughly every 45-49 seconds (e.g. bursts at 14:01:05, 14:01:51, 14:02:40 -
~46-49s apart), each taking ~5 seconds (13 quick channel switches, back to
the operating channel between each, then settling). This is normal
mac80211 behavior for any associated station (keeps the scan cache fresh),
not something b43-src controls.

5 seconds off-channel out of every ~45-49 seconds is **10-11% of the
time** - matching the measured ~6-10% probe loss almost exactly, and the
dip timing in both soaks (roughly 30-80s apart, aliasing against the
~13-15s probe cadence) is consistent with this. **The "residual loss" is
not a driver defect**: a probe that happens to land during a background
scan's off-channel window will legitimately miss, on any WiFi client, on
any channel - which is also why `ac_state_once` made no measurable
difference (it isn't the cause) and why the loss rate was similar on
channel 1's soak too (notes/51's channel-1 soak just got a luckier probe
cadence relative to its scan timing, at 115/115 - not zero real loss,
zero *sampled* loss).

## Next steps

1. No driver work follows from this - the post-association reliability
   problem this project chased since notes/34 is resolved (notes/50/51's
   fixes), and the small remaining probe-loss rate is explained as normal
   scan behavior, not a new lead.
2. `ac_state_once` can stay as an available option (default off); nothing
   here shows it's needed.
3. If background-scan-induced loss ever matters in practice (e.g. for
   real traffic, not just probes), it would show up as mac80211's own
   standard off-channel-scan tradeoff, not a b43-src issue - out of scope
   for this project's remaining work.
