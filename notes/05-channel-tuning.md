# Radio 2069 rev 4: power-up and channel tuning

All register numbers are resolved for `acphychipid == 0x4360`. Radio
type field `pi+0x16e` is 0 for 2069 revs 3..8 (ours: rev 4); PHY rev is 1.
Sources are in `decompiled/chan/` and `decompiled/`.

## chanspec (vendor format)
- bits 0-7: channel number
- bits 11-13: bandwidth, 0x1000/0x1800/0x2000 = 20/40/80 MHz
- bits 14-15: band, 0x0000 = 2.4 GHz, 0xc000 = 5 GHz

## Channel lookup — `FUN_0018f6f1`
Radio type 0: `PTR_chan_tuning_2069rev3[rev - 3]`, so rev 4 uses
`chan_tuning_2069rev4` (77 entries x 58 u16). Entry layout:
- [0] channel, [1] freq MHz
- [2..51] 50 radio registers (list in `phy_ac.c`)
- [52..57] PHY BW1a..BW6 = 0x371..0x376 (written by `FUN_001a581c`)

The table also shows that channels 184-216 are 4920-5080 MHz (JP 4.9 GHz), so
b43's old A-PHY table had them at the wrong frequency.
Generated into `b43-src/radio_2069.c` by `tools/gen_radio_2069.py`.

## Channel set — `FUN_001a7dc9` (our radio's path)
1. save 0x19e; 0x19e |= 3
2. if bandwidth changed: `wlapi_bmac_bw_set` (MAC side) — not ported yet
3. PHY 0x003 bit 0x100 = 5 GHz (b43's phy_ac.h says bit 0x0001 — mismatch)
4. carrier-search suppression on (`wlc_phy_stay_in_carriersearch_acphy`) — not ported
5. if band/bw changed: pulse PHY 0x728 bit 0x100
6. 50 radio writes from the entry
7. channel 4 only: radio 0x8d6 = 0xce4; 0x8ec bits 0x70 -> 0x50
8. radio 0x645 |= 0x7000
9. 5 GHz only: `wlc_2069_rfpll_150khz` — not ported
10. radio rev > 3: radio 0x723 = 0x83e0 (overrides the entry value)
11. VCO cal (`FUN_00193e5b`): clear 0x8e5.0x4000, 0x8d0.0x1, 0x8e8.0x40,
    0x8dc.0x2000; 11 us; set 0x8d0.0x1, 0x8e8.0x40; 1 us; set 0x8dc.0x2000
12. restore 0x19e bits 0-1
13. BW regs 0x371..0x376 from the entry, then many PHY/TX-power
    follow-ups (`FUN_001a581c` rest, `FUN_0019f0b8` tx gain tables,
    `FUN_0019f839`, ...) — not ported
14. CCA reset (PHY rev 1): force clock; PHY 0x001 |= 0x4000; 1 us; clear;
    release clock; 2 us

## Radio init — `FUN_001a08b2`
- s728 = PHY 0x728; s408 = PHY 0x408 & 0xfc38
- PHY: 0x415=0, 0x40e=0, 0x40c=0x2000, 0x408=s408, 0x417=0, 0x416=0xd,
  0x728=s728&0x7e7f, 0x720|=0x180, 0x408=s408, 0x408=s408|1, 1 us, 0x408=s408
- 24 preferred radio writes from `prefregs_2069_rev4` ({reg,val} pairs,
  0xffff-terminated; values in `phy_ac.c`)
- boardflag (`sh+100` & 2): radio 0x8ea |= 0x100 — source unknown, skipped
- radio 0x96b |= 0x800, 0x4000; 0x96c |= 0x800; 0x96b |= 0x8000, 0x1000, 0x4
- radio 0x407 |= 0x2; radio 0x55e |= 0x10
- per core c (reg | c<<9): 0x126 bits 0x300 -> 0x100; 0x127 bits 3 -> 2;
  0x6f clear 0x4, 0x1, 0x2; 0x65 clear 0x1
- radio 0x40c clear 0x10; PHY 0x408 = s408|6; 100 us; radio 0x40c |= 0x10
- PHY 0x417=0xd, 0x408=s408|2, 0x728=s728|0x180; 100 us;
  PHY 0x417=4, 0x728=s728&0xfeff

Core count: PHY 0x00b & 7, forced to 2 for chip 0x4360 with board type
0x137 or 0x117 (`wlc_phy_attach_acphy`).

## Power-up — `wlc_phy_switch_radio_acphy` (on) for radio type 0
1. radio init (above)
2. PHY 0x16b clear 0x400; 3 us; PHY 0x175 = 0; 3 us
3. path chosen by SPROM `boardflags3` bit 13 (`pi+0x34e`) / bit 3
   (`pi+0x345`). bcma does not parse boardflags3, so b43 sees 0 and we take
   the default path (RCAL):
   radio 0x8ea |= 0x40, 0x80; 0x8ed clear 0x600, 0x1800;
   radio 0x548 |= 1; 0x549..0x54c = 0;
   radio 0x40b clear 1; 1 us; set 1; poll 0x40b bit 3 (100 x 10 us);
   radio 0x548 clear 1; 0x8ea clear 0x40, 0x80; 0x40b clear 1
4. `FUN_0019665e` (RC calibration, not yet fully read)
5. if `pi->+0x32d`: `FUN_001a1202`, then full channel set

## First hardware results (2026-09-26, test-logs/run-20260926-123832.log)
- radio init done, 2 cores (board type 0x117 -> vendor's 2-core override)
- RCAL done after 1 poll, 0x40b = 0x0169
- RCCAL: step 0 0a80/0b55 -> 0xa0, step 1 0x000b, step 2 0x01eb
  (repeatable across two inits in the same run)
- channel switch 1..6 runs without errors; no DMA errors, no mac80211 warnings
- still NO-CARRIER: PHY init (tables, AGC) not implemented
