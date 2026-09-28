# Status 2026-09-28 (cont'd): the AP silently moved to channel 11 mid-session - a likely confound for tonight's "instability" data, plus real channel-6-adjacent stability numbers

## The discovery

While chasing the post-association disconnect issue further (running scripted
connect/hold/ping trials to get real numbers), noticed `iw dev wlp3s0b1 info`
reporting **channel 11 (2462 MHz)**, not channel 6. `journalctl` confirms
every single association attempt in the last 40 minutes of testing used
`freq=2462 MHz` (33/33 occurrences) - the AP's own auto-channel-select moved
it from channel 6 to channel 11 at some point during tonight's testing,
entirely independent of anything this session did. This is a real-world
router behaviour, not a driver bug, but it has significant implications for
how to read tonight's later results.

## Why this matters: channel-6-specific tuning doesn't apply to channel 11

`b43_phy_ac_op_switch_channel()` (`phy_ac.c:1069`) gates the entire
`b43_ac_por`/`b43_ac_replay` reapplication to `new_channel == 6` specifically
(lines 1114/1116):

```c
if (b43_ac_replay && new_channel == 6)
	b43_phy_ac_replay_ch6(dev);
if (b43_ac_por && new_channel == 6)
	b43_phy_ac_apply_por(dev);
```

`b43_phy_ac_apply_por()` **does** also run once, unconditionally, during
`b43_phy_ac_op_init()` (module/core init, before any channel is selected) -
so tonight's SHM/rate-block/CTS-to-self fixes (all living inside that
function) are applied at least once regardless of which channel gets
selected afterward. But the **channel-switch-time reapplication** - the
mechanism that exists specifically because a wl-captured "channel 1
first-boot" snapshot conflicts with the register requirements of switching
to a *specific* other channel (the entire subject of notes/22 through
notes/32: 19+4 radio-register skips, the `SHM_SH_CHAN` fix, the 40
conflicting OFDM PHY entries - all discovered and fixed **for channel 6
specifically**) - **only fires when the target channel is 6**. Any other
channel gets the regular per-channel radio/PHY tune
(`b43_phy_ac_tune()`) but none of the extra channel-6-specific
conflict-resolution work this project spent many sessions on.

**This means channel 11 is, right now, in the same under-tuned state
channel 6 was in before notes/22-32's fixes** - there is no reason to expect
it's been silently fine; nobody has done the equivalent reverse-engineering
work for it. If a similar "channel 1 boot state clobbers channel N's
requirements" issue exists for channel 11 (plausible, given how much work
channel 6 needed), it would manifest as exactly the kind of degraded/dead
throughput observed in tonight's later ping tests, **independent of the
watchdog/RX-reliability question from the earlier part of tonight**.

## What this means for tonight's numbers

- The 10-trial stability batch (8/10 "connected" per `nmcli`, 2/10
  disconnected with the beacon-loss pattern) was run **entirely on channel
  11**, not channel 6 - confirmed via journalctl, every attempt shows
  `freq=2462 MHz`. This is a real number, but it's a number for channel 11,
  not a re-confirmation of channel 6 behaviour.
- A follow-up check showed something *more informative than the pass/fail
  count alone*: one of the "connected" (state=100) sessions that held for
  3+ minutes without disconnecting **still had 100% ping loss to the
  gateway the entire time**, with `rx_packets` still incrementing (so the
  link wasn't fully dead - beacons/broadcast were still arriving) and
  roughly half of outgoing unicast frames failing to get ACKed
  (`AC txstatus` alternating acked/unacked in dmesg). So "connected" per
  `nmcli`/`wpa_supplicant` does **not** guarantee working data throughput -
  a connection can sit in a stable-looking zombie state. This was captured
  on channel 11 and needs re-checking on channel 6 before concluding it's
  the same root cause as the earlier bpftrace-diagnosed disconnect issue
  (which *was* captured on channel 6, per the b43mon capture in that
  session showing "channel 6 (2437 MHz)" explicitly).
- Independently confirmed with a concurrent USB-stick monitor capture that
  our own ping requests genuinely reach the air (visible SA:<our-MAC> frames
  at real signal strength, -22 to -30 dBm) but no reply frame from the AP
  was captured in that same window either - consistent with either a
  channel-11 mistuning issue on the TX or RX side, or (less likely given the
  strong local signal) a coincidental AP-side non-response.

## Practical implications / corrected next steps

1. **Don't treat the "8/10 connected" statistic, or the sustained-zombie-connection
   observation, as settled facts about channel 6 or about the
   previously-diagnosed watchdog/RX-reliability issue** - they're
   channel-11 data points, a materially different and unvetted condition.
2. **The single highest-value next step is now checking whether channel 11
   needs its own version of notes/22-32's work** (or, more robustly,
   generalizing the existing channel-6-specific fixes into something that
   applies the right conflict-resolution logic for *any* target channel,
   not just 6) - this could plausibly explain a large fraction of tonight's
   apparent instability with much more mundane, already-understood causes
   than an unresolved proprietary-driver vtable call.
3. If/when the AP returns to channel 6 (routers often revisit
   auto-channel-select periodically, or this can be forced from the router's
   own admin UI if the user is willing), re-run the same stability-trial
   script (`stability_trial.sh`, in this session's scratchpad, not yet
   committed - trivial to recreate: connect, hold 20s, check state/IP) to
   get a clean channel-6 baseline uncontaminated by this confound.
4. The watchdog-vtable-resolution work from earlier tonight (notes/34) is
   still worth finishing eventually, but should no longer be treated as the
   only or primary suspect for "instability" until the channel-11 confound
   is ruled out or fixed - it may turn out to explain a smaller fraction of
   the symptoms than it looked like an hour ago.

No hardware changes this round - this was diagnostic (journalctl review,
code re-reading, one more concurrent-capture check). Chip returned to safe
idle monitor-mode state on channel 6 (its default resting channel), USB
backup link reconfirmed working (0% loss, real RTTs via wlp0s20u1), netwatch
active.
