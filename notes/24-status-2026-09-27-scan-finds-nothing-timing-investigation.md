# Status 2026-09-27 (late evening, continued): scanning finds zero networks despite proven-good RX; the synchronous channel-switch path is cleared as the cause

Direct follow-up to notes/23, same evening, continuing after the TX-not-
reaching-air reconfirmation. Pushed further on the "why does `iw scan`
find nothing" question raised in notes/23's open items.

## The scan-finds-nothing bug is not channel-6-specific, and not about TX

With the channel-6 tuning correct (`ac_por=0`/`ac_replay=1`, notes/22)
and reception independently proven strong (notes/23), tested scanning
directly:

- A **purely passive** single-channel scan (`iw scan freq 2437 passive` -
  confirmed via dmesg to send no probe at all) on the exact channel and
  frequency where plain monitor-mode listening moments earlier received
  the AP's beacons at -56 dBm: **zero results, five times in a row.**
  `rx_packets` on the interface didn't increment by even one during the
  scan window - not "reception was poor," but "the hardware/driver
  received literally nothing" during that specific window.
- A **full active scan across all 13 channels** also found zero networks
  - including channels where neighboring APs are known to be present and
    receivable via plain monitoring. This rules out anything specific to
  channel 6 or to `phy_ac_replay_ch6()`/`phy_ac_por.h` (which only fire
  for channel 6): the failure is general to scanning, on any channel.
- This means the ~100-350 ms of apparent "dead air" right after a channel
  switch (loosely estimated in earlier testing this evening) is real and
  large enough to plausibly consume an entire scan dwell window, on any
  channel, not just 6.

## The synchronous channel-switch code is cleared as the cause

Instrumented (temporarily, with `ktime_get()`/`b43info` calls, reverted
before committing - see below) every layer between mac80211's `config()`
callback and the actual PHY channel-switch code, to find where time
actually goes on a real channel switch:

- `b43_phy_ac_op_switch_channel()` (this port's own code, including the
  channel-6 `replay_ch6()`/`apply_por()` calls): **~0.1-2.3 ms total**,
  matching earlier direct measurement.
- `b43_switch_band()` (mainline b43, generic): confirmed via an added
  "taking SLOW path" log line that it always takes the fast no-op path
  (the band never actually changes in this 2.4 GHz-only testing) - not
  the source of any delay.
- `b43_op_config()` (mainline b43's `mac80211` config callback,
  `main.c`): total wall-clock time per channel-switching call was
  consistently **~8.5-11 ms**.
- Traced the ~8.5 ms specifically to `b43_switch_channel()`
  (`phy_common.c:444`): `msleep(8); /* Wait for the radio to tune to the
  channel and stabilize. */` - a **deliberate, standard, mainline b43
  sleep present for every channel switch on every chip this driver
  supports**, not a bug and not specific to this port.

**Conclusion: the entire synchronous channel-switch path, from
`mac80211`'s config() call down through this port's own code, completes
in under ~11 ms - it cannot be the source of a 100-350+ ms RX outage.**
Whatever is actually suppressing reception for that much longer must be
happening asynchronously, after `b43_op_config()` already returned to
`mac80211` - a DMA/interrupt re-arm delay, a firmware-side state machine,
or something in how `mac80211`'s own scan dwell-timing interacts with
this driver, none of which this evening's instrumentation reached.

The diagnostic timing code (in `phy_ac.c` and `main.c`) was reverted
before committing - it was debug-only scaffolding, not a real fix, and
didn't belong in the tree once its question was answered.

## What this means, and what doesn't change

This does **not** overturn or add to the core TX-not-reaching-the-air
finding from notes/23 - passive RX and active scanning are different
mechanisms with, evidently, different bugs. It does mean there may be
**two separate, independent problems** blocking normal use: (1) the
long-standing TX/ACK issue, and (2) this newly-isolated scan/dwell-timing
issue that would block ordinary `NetworkManager`/`wpa_supplicant`
connections even if (1) were fixed, since normal connection setup
depends on a successful scan first (`notes/23`'s failed `nmcli
connection up b43-test` attempt is consistent with this, once the
`wpa_supplicant`-restart confound is set aside).

## Next steps for a future session

1. **Find where post-`config()` RX actually resumes.** Candidates worth
   instrumenting next: the DMA RX ring re-arm path, the IRQ mask
   registers immediately after `b43_mac_enable()`, and whether
   `ieee80211_scan_rx()`/`cfg80211_inform_bss_frame()` are ever reached
   at all during a scan (vs. reached but discarding results).
2. **Directly measure real outage duration precisely** with an actual
   timestamped RX test (this evening's tcpdump-based measurements were
   rough, subprocess-launch-latency-limited estimates in the 100-350+ ms
   range, not a clean, direct measurement) - e.g. a small kernel-side
   probe logging `ktime_get()` at the first RX interrupt after a channel
   switch, compared against the switch-issued timestamp.
3. Re-attempt the original documented "auth/assoc succeeds, AID
   assigned" test (still open from notes/23) now with the extra context
   that scanning itself is suspect - if that older test bypassed
   scanning (fixed BSSID/frequency), it may still work today and would
   further confirm scanning specifically, not general RX-after-switch,
   is the point of failure.
4. Loft-comp calibration question (notes/22) still fully open, unrelated
   to and untouched by tonight's continued work.

## Session close

No crashes, no dmesg BUG/Oops/panic/WARNING lines throughout tonight's
continued testing. USB backup link 0% packet loss throughout and at
close. Diagnostic instrumentation reverted before committing - no net
source change from this note's investigation (notes and memory only).
`b43` unloaded cleanly; chip left on `bcma-pci-bridge`. `wl` remains
restored and working normally from earlier this evening.
