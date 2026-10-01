# 108 - Alessio's reply; first attempt at porting his RX AFE calibration (did not work)

## Alessio's reply (2026-10-01)
- "WL programs the awake bit during every MAC suspension to prevent the ucode from entering sleep. B43
  doesn't do it by default, you have to patch it." We already do: b43_mac_suspend() calls
  b43_power_saving_ctl_bits(PS_AWAKE) (forced awake=true) and the failure dumps show MACCTL c4120402 with
  AWAKE (0x04000000) set; releasing it between windows like wl (`ac_awake_release`, notes/105) changed
  nothing. So no new lead from this answer.
- The MacBookAir6,1 trace in his README is one of OUR early traces (he picked it up when we wrote to
  b43); the new one to look at is the T5E trace (same 6.30 driver, other hardware).
- 2.4 GHz: planned; with our complete 2.4 GHz trace he can now look at it: "most logic should be already
  there, but some fixes may be needed". => wait for his 2.4 GHz update, then adopt his code as a whole.

## Hypothesis behind the port
His post-channel calibration block is almost all RX-side (RX IQ cal, RX AFE cal ~1500 ops, gain LUT
finalise); the AFE results feed the TX LO-feedthrough tables 0x42/0x62/0x82. We replay wl's captured
results from another session instead of calibrating this init: per-init random analog offsets could leave
the PHY seeing carrier sense whenever TX starts (notes/58).

## What I ported (patch saved: notes/108-afe-cal-port-attempt.patch, reverted from the tree)
rxcal_afe_iter / rxcal_afe_calibrate (the PHY calibration engine: command word to PHY 0x0380, wait for the
busy bit 0x8000, copy table 0x0c words), the gain-ladder B write, and, instead of his 5 GHz-only LOFT base
values, a shift of the replayed LOFT tables by (new - replayed) result per byte. Gated by `ac_afe_cal`,
saving and restoring every PHY register it touched.

## Result
- Without opening his window (force PHY clock + 0x0382 = 0x8a09) the engine never finished (busy timeout
  on every iteration); with it only core 0's first iterations timed out at 1 ms, none at 20 ms.
- But the results are all zero (new LO 0000/0000/0000 vs replayed ff02/0101/0000): without the radio
  loopback / DDS tone setup that his RX IQ calibration chain does immediately before, the engine measures
  nothing. Applying zero results would corrupt the LOFT tables. Connect rate with it: 1/6 (no gain).
- A faithful port needs the whole chain: rxiqcal (rxiqcal_phy_ac.c 532 lines + ~1000 lines in phy_ac.c:
  radio_iqcal_config, dds seed, meas iterations, apply stages), his state tracking, and 2.4 GHz validation
  (his ladders and LOFT bases are board/5 GHz specific). Not worth doing blind; wait for his 2.4 GHz code.
