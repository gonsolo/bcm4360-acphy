# 105 - ucode wake analysis: NAP is a side effect; PHY TX errors decide the outcome

Continuation of notes/104 (2026-10-01). Question asked: what wakes the PSM out of NAP
(PC 0x000F) after a TX post, and why not in the bad state?

## Results
- `ac_hostflags=1` (notes/62: writes wl's real HOSTF2/HOSTF3, which the idle loop at
  0x000C/0x000D tests before napping): 3/8 connected, 8-15 suspend failures in the failing
  attempts. The failure-time PSM samples are no longer frozen at 0x800f; they are varied
  (8020, 8107, 91c2, 80c4, 8047, 802e, 8106, 918b) with phydebug 0x45 (CRS|TXF...):
  the ucode is awake and busy mid-TX, waiting on a PHY that never completes the frame.
  So the NAP at 0x000F (notes/60) is a side effect of the missing host flags, not the
  cause of the suspend failures.
- Over all 118 fresh-reload connect attempts in `test-logs/ab_reload_*.log` that logged
  "PHY TX errors during connect":
  | outcome | n | PHY TX errors during connect |
  |---|---|---|
  | not connected | 90 | median 11, max 21 (only 7 with 0) |
  | connected, <=2 suspend failures | 8 | 0 in all |
  | connected, >2 suspend failures | 20 | 0 in 18, max 1 |
  Connecting happens exactly when the PHY completes its TX frames without
  `PHY transmission error`. The MAC suspend failures follow: the ucode is stuck in a TX the
  PHY never finishes. (Earlier notes 07/12: the ucode's txphyerr counter equals its auto-ACK
  count ~1:1 and the error is a hardware condition line the PHY asserts.)
- wl's raw trace (traces/wl-tx-*.trace): a TX post is a single MMIO write (core offset
  0x244 DMA ptr); MACCTL toggles 0x44020403 / 0x40020403 (releasing AWAKE between suspend
  windows). Releasing AWAKE like wl (`ac_awake_release`, reverted): no change.
- MAC bandwidth register PHY0 (0x3e6): wl writes it 5 times (0 / 0xf4), ours reads 0: not a lead.
- d11-emu models NAP as a no-op, so it cannot say what wakes the PSM.

## Standing picture
The proximate cause is PHY TX errors in the bad state; every host-side init/clock/PMU/MAC/
power-bit difference tried so far (notes/103-105) leaves the ~20-30 % good-init rate
unchanged. What differs between a PHY that can transmit and one that cannot is not in any
static register we snapshot after load, nor in the MAC-side items Alessio's patches cover.
Open: the TX power/gain path (TX IQ/LO calibration never worked in this port, notes/16-22),
tempsense, per-channel TX tables; and Alessio's answer (email sent 2026-10-01).

## Same day, later: TX power control off, mid-connect snapshots, fixed-channel TX test
- `ac_txpctl_off` (clear PHY 0x70[15:13] after each channel switch; our driver has no TX power
  control of its own, recalc/adjust_txpower are stubs): 2/8, 8-16 PHY TX errors in the failing
  attempts, 0 in the two connected: no change (reverted). PHY 0x70 reads 0xe500 after connect in
  every connected run and in the non-connected runs that left a readable snapshot, so the loop
  being enabled does not separate them either.
- `tools/init_snapshot_test2.sh` (snapshot 15 s INTO the connect attempt, 40 inits): 8 connected /
  32 not, and "PHY TX errors during connect" separates them exactly (0 vs 5-15). The ~48 PHY
  registers that separate the groups (0x019b/0x01a2 Farrow ratio, 0x0371-0x0376, 0x0602-0x0607
  family, 0x0840, 0x0990, 0x0029/0x002a) mostly encode the CHANNEL: connected runs sit on the
  AP's channel, failing ones are hopping through scan channels at the snapshot time. Confounded.
- `tools/init_txtest.sh` (fixed-channel, no scan, no association: reload, park on ch11, inject 20
  directed probe requests with tools/inject_probe.pl at 6 Mbit/s, count AP responses and dmesg
  PHY TX errors): over 40 inits only 2 had a PHY TX error and none had a MAC suspend failure;
  AP responses ranged from 0 to 13 of 20. So TX from a monitor-mode injection at a fixed OFDM
  rate does not reproduce the connect-flow failure (5-15 PHY TX errors per attempt). Manual 1 vs
  6 Mbit/s runs also gave only 1-2 errors each: not a simple CCK-vs-OFDM split.
- The ucode macstat counters (SHM 0xE0/0xE6/0xFE) do not update right after a fresh load
  (synced periodically), so they cannot label a fresh init.
- Open: what differs between the mac80211-driven TX of the connect flow (managed interface, ACK
  requested, TX status, scan suppression) and the injected frames. The failure needs the managed
  flow, not just any TX.

## Same day, last: scan-health validation, TX header, TX core mask
- `tools/scan_health_validate.sh` (24 valid inits; the run was interrupted): PHY TX errors during
  the 2 x rescan phase right after load were 0 in 23 of 24 inits, including every init that then
  failed to connect with 8-16 errors during the connect attempt. A scan does NOT predict the outcome;
  failures start with the unicast auth frames of the connect attempt. A reload-until-clean loop
  must therefore judge an init by a real connect attempt, not by a scan.
- Our AC TX header (xmit.c b43_generate_txhdr_ac, format copied from wl) differs from Alessio's
  approach (stock generic txhdr with phy_ctl1 filled for AC). Ours demonstrably gets frames to the
  AP, so no change there.
- TX core mask `ac_txcore`: default 1 (core 0), SROM says txchain 6. `ac_txcore=6`: 1/8; `ac_txcore=7`:
  2/8, failing attempts unchanged: not the cause.
- Process note: running tests in the background while doing other work makes the laptop lose its
  connection (every b43 reload restarts wpa_supplicant on NixOS and drops the USB stick too). Run
  one thing at a time.
