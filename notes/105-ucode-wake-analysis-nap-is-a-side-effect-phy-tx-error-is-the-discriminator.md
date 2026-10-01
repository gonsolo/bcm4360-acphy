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
