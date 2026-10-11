# 146: periodic loss of data frames over b43 = software scans (found while the owner was away)

## Housekeeping first
- A-MPDU requeue counter moved from `skb->mark` to `b43_private_tx_info.requeues`
  (reset in `b43_dma_tx`, not in `dma_tx_fragment`, so a requeue keeps it). 6-minute
  2.4 GHz soak afterwards: 70/63 Mbit/s, 291 failed of 1.56 M frames, no errors.
- checkpatch errors in phy_ac.c fixed (0 left); other files only have upstream legacy errors in main.c.
- Draft reply to Alessio: notes/145 (not sent).
- Power save: `iw set power_save on` returns -95; the driver does not advertise PS. Not needed on the desk, relevant for battery.

## The finding
TCP (iperf) hides loss. A 100 pps ping over b43 (host route to 192.168.0.236, src .119, stick
untouched) loses 20-50 % of the frames in bursts of a few seconds, 0 % otherwise.

What I ruled out, in the order I (wrongly) believed it:
- not the air or the router: tcpdump on the Ethernet side saw only the requests that b43 had answered, 157 of 200.
- not the driver: `b43_op_tx`, `b43_dma_tx` and the TX status handler have equal counts, and a per-frame
  trace of `b43_dma_tx` shows that in a lossy burst only ~110 of the 200 frames ever arrive there.
  (My first reading, "equal counts, so nothing is lost before the driver", was wrong: I had not compared the
  counts with the 200 pings sent.)
- not A-MPDU (same with `ac_ampdu=0`), not TX power control (same with `ac_txpwrctl=0`), not uptime
  (fresh reloads are clean, then loss comes back in the same pattern).
- The IP layer hands all 200 frames to the netdev (`IpOutReq` and the netdev TX counter both +201).

Where they go: `tracepoint:skb:kfree_skb` during a lossy burst shows 86 frames freed in
`invoke_tx_handlers_early` (mac80211), 1-45 per second over three seconds. That function drops data frames in
`ieee80211_tx_h_check_assoc` while a software scan has the interface off-channel (SCAN_SW_SCANNING + OFFCHANNEL).

Confirmation: `iw event -t` shows wlp3s0b1 scans every ~305 s lasting ~4.8 s (13 channels of 2.4 GHz,
SSID "Vodafone-2A84", started by NetworkManager/wpa_supplicant although the signal is -29 dBm). Every lossy burst
(01:18:18, 01:48:49, 01:53:51, 02:24:23) sits on that 304 s grid. One burst a minute of 2 s hits a 5 s scan about
once in 40 bursts, which is the rate seen.

So this is the known scan loss of notes/136 (NM background scans), not a new TX defect. Frames from the stack
during the off-channel dwell are dropped by mac80211 (b43 has no PS, so the AP is not told either).

## What is still open
- The stick (same router, 21 s scans, same period) did not lose frames in a 4000-ping run across one of its scans,
  but at a much lower packet rate (the run took 380 s, not 40 s), so the comparison is weak.
- A scan costs b43 about 370 ms per channel; a channel switch itself is cheap now (`b43_op_config` 8-16 ms,
  `b43_mac_suspend` 32-64 us; the 80 ms suspend wait of notes/92 is gone on this build). Most of the time is mac80211 dwell.
- Options: (a) user side: keep NetworkManager from scanning every 5 minutes while connected at a strong signal
  (needs a change in /etc/nixos, not done by me); (b) driver side: advertise power save so mac80211 sends the
  null-function frame before leaving the channel and the AP buffers frames (needs PS support in the ucode,
  not examined); (c) shorter scans, e.g. limit to channels the router uses.
