# notes/136: PHY replay bisect -> TX power control (2026-10-08)

## Bisect of the 290 PHY replay writes (throughput, paired A/B, 2 pairs per range)
- No PHY replay (`ac_por=5`): 124-239 kB/s vs 751-1074 with it (6 pairs). The writes ARE needed;
  the earlier dump analysis saying otherwise was wrong.
- Halves, quarters, ... down to one write: skipping only PHY 0x0070 = 0xe500 gives 16/22 kB/s.
  Skipping 0x0400, 0x0072+0x0071, 0x0846+0x0646 individually: no effect. Control (six 0xffff
  no-op entries): no effect.
- With 0x0070 written explicitly and no other replay: 340-409 kB/s vs 439-696 full replay (4 pairs),
  so ~40 % is still spread over other writes. Skipping 72-216 (with 0x70 explicit) cost ~40 % in one
  run and nothing in an earlier one; ranges 0-35, 36-71, 253-289 no effect. Not resolved.
- Ping loss was unreliable in these runs (100 % loss next to 700 kB/s downloads); throughput is the judge.

## What 0x70 is (decompiled wl, decompiled/ and decompiled-tx/)
- `wlc_phy_txpwrctrl_enable_acphy`: PHY 0x70 bits 15:13 = hardware TX power control enable.
  On disable wl first saves the per-core index, on enable it restores it.
- 0x640 + core*0x200: status, bits 14:8 = current TX gain index, bit 15 valid, low byte est. power.
- 0x642 + core*0x200: bit 8 valid, low byte est. power.
- 0x644 + core*0x200: bits 6:0 = init index. wl wrote 0x26/0x19 (ch6) and 0x16/0x14 (ch1 boot).
- 0x645 + core*0x200: idle TSSI (wl: 0x250/0x261 ch6, 0x24d/0x25f ch1; a measured value).
- 0x646 + core*0x200: low byte = target power (0x2e on both cores).
- 0x71 bits 10:8: averaging window (0x400 normal, 0x100 short).
- table 7 offsets 0x100/0x103/0x106 (+core): the three TX gain words for a fixed index
  (`wlc_phy_txpwr_by_index_acphy`); these are the vendor cells b43_vendor_7_256/259/262.

## Live readback on b43 (2.4 GHz, ch1, under ping load)
`70=e500 71=04c8 72=400d 640=8013 642=0113 644=0020 646=002e 840=8022 842=0122 844=0020 846=002e`
- Current index reads 0 on both cores, always. wl's own indices were 20-38.
- Est. power is constant (0x13 / 0x22) and below the target 0x2e.
- Changing the target (0x2e, 0x22, 0x16, 0x0c) or the init index (0x10..0x60) changes nothing in the
  status registers, and loss stays 14-46 %.
Reading: the loop is enabled but not regulating; it sits at index 0 (if index 0 is maximum gain, as in
other Broadcom PHYs, the PA is overdriven, which would hit OFDM 48/54 Mbit/s first and leave CCK alone,
matching the observed loss pattern). NOT proven. Likely missing piece: the TSSI path enable and the
idle-TSSI measurement (never ported; Alessio's driver has idle_tssi_meas / txpwrctrl_setup / _enable).

## Next
- Confirm under wl: read 0x640/0x840 while wl transmits (index should sit at 20-38, est near target).
- Port TSSI path enable + idle TSSI + txpwrctrl setup; acceptance: index moves off 0, est tracks target,
  then loss/throughput A/B.

## Update: the power loop needs radio state, not PHY writes (same day)
- Old module (full replay) status 0x640=942e/0x840=2000 (index ~20, est = target 0x2e): the loop regulates.
  Our current build: frozen at 8013/8022. Bisect of the 51 radio writes removed in e214612:
  writes 3-8 (radio 0x0548, 0x0549, 0x054a, 0x054c, 0x040b, 0x054b) are what the loop needs.
  Restoring the radio table (always applied; ac_por_rfrom/rto skip a range): index 19, est 0x2e on both cores in 3 of 3 loads.
- The e214612 A/B only measured throughput/loss, so it missed this.
- 4-pair A/B, loop frozen vs working: 500 vs 483 kB/s, loss unchanged. The loop is NOT the cause of the loss.
- TODO: cut the radio table to the six writes as named init code.

## 5 GHz RX baselines on 2026-10-09 (all listen-only, monitor mode, 2.4 GHz sanity 110-126 frames each time)
- iPhone hotspot on ch44 at -17 dBm: existing 20 MHz path (minimal args and full replay): 0 frames on 5220/5180/5240.
  Plus the 28 PHY + 2 radio regs that wl sets differently per band in its channel steps (extracted from
  traces/decoded-firstload-5g/seq.txt, 221 5 GHz and 81 2.4 GHz steps): still 0.
- Router ch116 at -44 dBm: 20 MHz path 0, 80 MHz state retuned to centre 122: 0.
- Router moved to ch112 at -42 dBm, wl's untouched 80 MHz state (ac_5ghz=1 ac_5g_80=1), the mode of notes/07 that
  decoded 88/100 beacons: current tree 0, Oct 7 module 0, the 09-26 commit 6b399f0 ("5 GHz: receives") rebuilt for 7.2.9: 0.
=> the former 5 GHz RX success does not reproduce on kernel 7.2.9 with this setup. Not a code regression of the last
   days; either the environment (kernel/reset order/router DFS) or the notes/07 measurement conditions differ.
Alessio's 5 GHz channel switch runs ~17 phases (switch_prep ... afe_gain); ours is tune + BW regs + Farrow + CCA reset.

## 5 GHz: Alessio's channel sequence on our chip (2026-10-09)

- Throwaway copy of his switch_channel (b43-src/phy_ac_alx.c, `ac_alx=1|2`, not committed): 0 frames on ch112 (router, -42 dBm)
  and ch44, with and without reset_cca/afecal/adc_reset/txpwrctrl_enable. 2.4 GHz sanity 126-135 frames.
- His full bring-up (op_init, software_rfkill, cold preamble) hard-hangs this machine (notes/117); not run.
- Offline diff (his test/unit harness, ch36/20 MHz, vs our wl 6.30 first-load hop, segment 12): radio writes 79/79 covered
  (4 value diffs), PHY writes covered except 0x02e4/0x06d4/0x08d4 (17 value diffs: IQ coefficients, CRS regs, 0x0d-0f, 0x1601).
  The wl-only MMIO in the hop (0x0200/0240/0280/02c0/02c4, 0x0128/012c) is TX DMA of scan probe requests and IRQ mask, not RX.
- Conclusion: the channel-switch register set is not what is missing; the cause is state before it (bring-up) or a value detail.

## Radio table cut to 21 named writes (2026-10-09)
Bisect of the table with ac_por_rfrom/rto: the power loop needs 0x548-0x54c, 0x40b, 0x4e, 0x166, 0x24e, 0x366 and the
per-core 0x1a-0x1f / 0x21a-0x21f plus 0x170. The six TSSI writes alone are not enough (loop frozen). The other ~50 writes
(0x203-0x205, 0x370, 0x20-0x3d, 0x220-0x23d, 0x16e..) are not needed. Table deleted, 21 writes in apply_por(); the
ac_por_rfrom/rto params are gone. Loop regulates (0x640=922e, 0x840=9b2d) in 3 of 3 loads.
A/B (3 pairs, up/down Mbit/s): old table 20.0/19.6, 19.1/18.9, 18.8/18.1; 21 writes 20.2/19.3, 16.2/11.1, 20.3/19.2.

## PHY replay no longer needed for throughput (2026-10-09, after the radio fix)
3 pairs, same build, ac_por=7 vs ac_por=3 (no PHY register replay), up/down Mbit/s:
full 19.5/15.0, 21.8/15.3, 19.5/11.3; no PHY replay 19.2/12.6, 19.0/10.2, 20.1/12.3.
Averages 20.3/13.9 vs 19.4/11.7: within the load-to-load spread (10-19 down). The 124-239 vs 751-1074 kB/s gap
measured earlier was the frozen power loop (0x70 and the radio state), not the 290 PHY writes.
Next: connect/hold check without the replay, then delete the PHY table.
