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

Connect/hold check (5 loads each, 200 pings at 20 ms after the 25 s hold): all 10 loads connect and hold clean.
Ping loss: ac_por=3 (no PHY replay) 22.5/22.5/0/23/0 %; ac_por=7 (full replay) 0/23/0/0/0 %. The loss is bimodal
(0 or ~22 %) per load. 3/5 bad loads without the replay vs 1/5 with it: small sample, but the PHY replay is NOT
deleted. The bimodal 22 % load state is the remaining 2.4 GHz problem (throughput is ~equal in both modes).

## The bimodal ~22% ping loss is background scanning, not init state (2026-10-09)
10 loads (3 bad, 7 good) dumped (phy, radio, mac, tables): no static register differs between good and bad. Radio and
tables are identical; the "separating" PHY/MAC registers are AGC/noise counters.
A bad load loses pings in bursts of 3-4 every ~7.7 pings (~385 ms), only for the first ~5 s of the ping run; a second
run on the same load and a run after 30 s idle are 0 %. Triggering `iw dev wlp3s0b1 scan freq 2412 2437 2462 2467 2472`
during a clean ping run reproduces exactly that pattern (8.5 % loss, bursts of 3-4). So "bad load" = a background scan
(NetworkManager/wpa_supplicant) happened to fall in the 10 s ping window. Each off-channel hop drops the pings that
arrive meanwhile: the AP is apparently not buffering for us (PS nullfunc not sent/acked or not honoured).
Next: monitor-capture a scan hop (is the PM=1 nullfunc sent and acked?).

Monitor capture of a scan hop (mon43 as a second vif on b43's phy, concurrent with the managed one works): before each
off-channel hop b43 sends a QoS-Null with PM=1 (FC c8 11), the AP ACKs it, and on return a QoS-Null with PM=0 (c8 01).
So the power-save signalling is correct. Each hop leaves a ~130-190 ms gap, ~3-4 pings at 50 ms spacing. Scan of 2
channels 5 % loss, of 4 channels 27 %. Not a b43 TX-status bug; looks like generic mac80211 software-scan behaviour
(a stick comparison failed: ping via wlp0s20u1 gets 100 % loss for an unrelated routing reason). Parked.

## CORRECTION (2026-10-09): the two "no PHY replay" tests above used ac_por=3, which still contains B43_AC_POR_PHY (0x02)
The no-PHY setting is ac_por=5 (RADIO|TBL). The sections "PHY replay no longer needed for throughput" and the hold/ping
check (3 vs 5 bad loads) compared two settings that both replay the PHY writes; their conclusions are void.
Redo with ac_por=5 (3 pairs, up/down Mbit/s): with replay 5.1/7.1 (bad load), 21.0/15.7, 19.9/11.0;
no PHY replay 7.8/14.1, 5.3/15.2, 9.0/10.1. Upload collapses to 5-9 without the PHY writes, download is unaffected.
So some of the 290 PHY writes are needed for TX. Next: bisect on the upload figure.

## PHY replay bisect on upload (2026-10-09), result: partial
While the AP was on ch11 (single-file bisect, keep/skip ranges of the 290 writes, upload Mbit/s):
- ac_por=5 (no PHY table, 0x70 only): 5-9. Skipping table entries 224/225 (PHY 0x0072=0x400d, 0x0071=0x04c8) alone: 0.4-0.8.
  Writing 0x70/0x71/0x72 explicitly: 10.7 with no table, ~21 with the table (3 pairs, stable).
- Any single quarter or half skipped: ~20 (the table is redundant); keeping only entries [0,72): 20.5 twice,
  [72,145) mixed, [145,290) 1-3. Neither [0,36) nor [36,72) alone works (worse than nothing): a coherent set.
  Candidate groups in [0,72): 0x04xx, 0x172x, 0x02ef-0x02f7 (0x2055), 0x01b0-0x01b6, 0x0180-0x0194 table, 0x06ed-0x08ef.
The router was then switched to auto and moved to channel 1; every later run (group removal, even the control with the
identical config: 20.5, 20.5, then 2.3, 3.5, then 0 x4) is not comparable, and the full replay itself gave 11.0/18.4.
Bisect inconclusive. 0x70/0x71/0x72 are now written explicitly (TX power control); the rest stays replayed until the
init is rewritten (decision: rewrite from Alessio's op_init, even if it hangs).

## The 290-write PHY replay is gone (2026-10-09): b43_phy_ac_phyinit()
Bisect of the replay on upload: only entries 0-71 matter and only as a whole (halves of them are worse than none).
They map to the reset-time blocks of Alessio's code: mode_init (0x17xx AFE page), set_reg_on_reset (0x01f2, 0x0025/26,
clip mask 0x02eb-0x02f7, 0x01b0/b1/b6, 0x0690/0x0890, 0x01e6), set_pdet_on_reset (0x0358), coeff_bank_init (0x0076,
LUT 0x0180-0x0194, 0x01b5, 0x0312/13, 0x06ed/0x06ef per core), init_regs (0x1645) and channel_setup (0x0197/98); plus a few
words wl writes that his code does not (0x04xx, 0x03c4, 0x01ed, 0x016b, 0x0175, 0x0414, 0x040a).
b43_phy_ac_phyinit() writes those 72 values as grouped, commented code (ac_phyinit=1, default). A/B vs the full table
(3 pairs, up/down Mbit/s): table 20.5/17.6, 19.3/17.4, 20.1/18.0; phyinit 20.7/16.8, 20.9/17.7, 20.7/17.9.
phy_ac_por.h and the ablation params are removed from phy_ac.c. 5 GHz still uses its own table (phy_ac_por5g.h).
Ping loss after connect (22 % in every load of both builds today) is the scan-hop effect described above.
Next: derive the values instead of writing them (his masksets, bandwidth/band dependent), starting with coeff_bank_init and
set_reg_on_reset.

b43_phy_ac_phyinit() now uses Alessio's read-modify-write forms (mode_init, set_reg_on_reset, coeff_bank_init as named
functions, per-core loops): a full phydump after load matches the literal version on all 72 registers (so the reset
defaults + masksets give the replayed values). Still constants for 2.4 GHz / 20 MHz; the band/width dependent parts of
coeff_bank_init (0x0076 index, LUT per width, 0x0250/0x0261-0x0263, 0x0140/0x0164) are not used yet.

## The periodic ping loss is NetworkManager's roaming scan below -70 dBm (2026-10-10)

The "bimodal" 11-35 % ping loss is one 5 s background scan every ~20 s. NetworkManager configures
wpa_supplicant with `bgscan simple:30:-70:86400`: below -70 dBm it scans every 30 s, above it once a day.
Our signal sits at -65..-76 dBm, so a load lands on either side. Measured (200 pings, 0.1 s): 11 % with
1-2 scans per 20 s; after `nmcli connection modify Vodafone-2A84 802-11-wireless.bssid <AP>` (NM then sets
no bgscan): 0 scans, 0 % loss, twice, on both the dev build and the Nix-packaged module.
The profile is generated by NixOS (ensureProfiles, /run), so the permanent fix is `wifi.bssid` in
configuration.nix. With b43 (metric 600) as default route, its loss also hits traffic meant for the stick.

## Correction: RX level was 26-35 dB low; the state must be applied at init; TX power control off (2026-10-10)

The roaming scans above have a cause in the driver: b43 reported -66..-76 dBm next to the router, where the
stick measures the same 2.4 GHz BSS at -35 dBm. Three findings, each reproduced by switching it on and off:

1. **The first-load state was only applied when a channel switch passed channel 6** (`ac_init_state=0`), i.e.
   when a scan happened to hop there, and was lost again on every re-init (reconnect). That is the "per-init
   coin flip": state present (RX -45, TX power control on) or absent (RX -71). `ac_init_state` now defaults to 1.
2. **The tail of wl's PHY table (entries 72-289) carries 26-35 dB of RX level.** The reduction to 72 writes was
   checked by throughput only, which does not move (21/17 Mbit/s either way, the unaggregated ceiling). With the
   72 writes alone: -67..-71 dBm; with the tail (`ac_por_tail=1`, default, phy_ac_por.h restored): -35..-44 dBm,
   three re-inits. Which of the 218 writes matter is open; signal avg is now a fast, deterministic metric.
3. **The hardware TX power control (0x70 = 0xe500) breaks TX next to the AP**: 388 retries and 58 failures per
   206 frames, upload 0.7-2.3 Mbit/s; with 0x70 = 0x0100: 19 retries, 0 failures, 21 Mbit/s (toggled at runtime,
   twice each). `ac_txpwrctl` (default 0). The earlier bisect result (control needed) was taken in the low-RX
   state and does not hold here; behaviour at range is untested.

Result, no BSSID lock: signal avg -39 dBm, 0 scans in 75 s, 0 TX failures, 18-21 up / 15-18 down.
A-MPDU work parked on branch wip-ampdu (session header 0x45c0 / cache info breaks the link).

## The RX level is one write: PHY 0x1726 = 0x000c (2026-10-10)

Bisect of the table tail (entries 72-289) on beacon signal avg after a re-init (controls: tail -39, no tail -66 dBm,
twice). No single 18-entry chunk matters, and either half alone gives -39: the register is written twice,
entry 144 (0x1726, the all-cores alias) and entry 188 (0x0726, core 0), both 0x000c; each alone gives -40.
It is the write that closes the RX gain control setup in Alessio's driver (0x173b = 0x2c, 0x1726 = 0x0c).
Now in b43_phy_ac_phyinit(); the tail and phy_ac_por.h are removed again. Without the tail: -39..-41 dBm on
three re-inits, 18/18 Mbit/s, 0 scans in 40 s. TX retries are the same with and without the tail in alternating
runs (96-142 per 300 pings either way); an earlier lower count (0-9) was a different moment, not the tail.
2.4 GHz PHY replay left: none. Constants of unknown meaning: 0x1739, 0x016b, 0x0175, 0x03c4, 0x0197/98.

## HT retest at the right RX level: two-stream TX fails completely (2026-10-10)

Legacy vs ac_ht=1, three alternating loads: legacy 17-18 up / 17.5-18 down; HT 0.5-0.6 up, AP sends us MCS 12-15.
Forced rates (ac_httx, 150 pings): MCS 0, 3, 7 as legacy (32-44 retries, 0 failed); MCS 8 and 15: all 150 failed.
Each TX core alone and both together work at legacy rates (ac_txcore 1/2/3). Not the replay cuts and not today's
changes: commits a39b8f3 (full replay) and 0ba45ae (where notes/123 measured MCS 0-15 all acked) fail MCS 8 the
same way today, with and without ac_init_state, with and without TX power control and the table tail.
What differs from 2026-10-07 is the place: the notebook is next to the router now (stick -35..-46 dBm, then -60).
Open: overload of the AP's receiver at this range, or a two-stream TX fault that only shows here. Test: move away.

## Two-stream TX is not overload: lowering the amplitude makes it worse

The baseband multiplier (table 0x0c, 0x63/0x67 and 0x73/0x77, both cores) can be written live through debugfs `b43ac/phy` (0x00d, 0x00e, 0x00f); no write gate needed. Current TX gain: table 7 `ff00/07cf/00a7`, bbmult 0x3f. Failed frames of ~150 pings, next to the router:

| bbmult | legacy | MCS 7 | MCS 8 | MCS 15 |
|---|---|---|---|---|
| 0x3f (0 dB) | 0 | 1 | all | all |
| 0x2d (-3) | 1 | 0 | all | all |
| 0x20 (-6) | 0 | 1 | all | all |
| 0x16 (-9) | 0 | 2 | all | all |
| 0x10 (-12) | 2 | all | all | all |
| 0x0b (-15) | 55 | all | all | all |
| 0x08 (-18) | 57 | all | all | all |
| 0x04 (-24) | 114, then deauth | | | |

Two-stream fails at every level, so the AP is not overloaded. And the link has little margin: 12 dB less kills 64-QAM, 15 dB less hurts legacy, at 1 m from the AP. The transmitted signal is weak or dirty (no TX IQ/LO calibration, or the PA/gain setup). Two-stream is a separate fault in how the frame is built or sent.

## The second TX chain does not transmit

Per-core test, muting one core's bbmult cells (0x63/0x73 = core 0, 0x67/0x77 = core 1) and sending 40 legacy pings with each `ac_txcore` mask:

| ac_txcore | core 0 muted | core 1 muted |
|---|---|---|
| 1 | 45 failed | 0 |
| 2 | 40 failed | 0 |
| 3 | 42 failed | 0 |

Whatever the mask says, everything the AP hears comes from core 0; core 1 adds nothing. HT with mask 2 fails at every MCS (0–5 tested), HT with mask 3 works through core 0. So two-stream fails because the second stream is never radiated. The earlier "each TX core works alone" was wrong: legacy frames with mask 2 still leave through core 0. RX on both chains works (the AP's MCS 12–15 arrive).

The ucode TX core table (shm 0x05d4–0x05dc, here `0001 0207 0207 0307 0007`; Alessio writes plain masks) makes no difference. Next: the core 1 TX path in the radio and RF sequencer (PA, pad, mixer power-up, FEM control lines).

## Fix: chipcommon chipcontrol bit 3

Radio registers (0x000–0x17f vs 0x200–0x37f) and per-core PHY registers are symmetric, tables are identical to the 2026-10-07 dump, and writing back the PHY registers that differ from that day changed nothing. What differs is chipcommon `chipcontrol` (0x28): 0 here. Alessio's `fem2_sub1_setup` ends with `bcma_cc_set32(CHIPCTL, 0x8)`; I had ported its two PHY writes but not this one. Setting the bit live (`echo '28 8' > b43ac/cc`): core 1 alone sends MCS 0, MCS 8 and 15 are acked, 0 failed. On 2026-10-07 the bit was presumably still set from an earlier wl load in that boot; it survives a module reload, a cold boot clears it.

Now in `b43_phy_ac_phyinit()`. Clean load (bit cleared before rmmod), next to the router, iperf3 8 s, two runs each:

| | up | down | TX rate |
|---|---|---|---|
| `ac_ht=1` | 22.0 / 22.3 | 15.7 / 15.5 | MCS 13–15 |
| legacy | 19.8 / 19.9 | 17.3 | 54 |

HT works again but gains little without aggregation, and download is 10 % lower. `ac_ht` stays off by default until A-MPDU.
