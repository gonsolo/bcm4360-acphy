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
