# 162: Alessio's tree on 2.4 GHz: the PHY TX fault is one register, RX is still dead

Tree 63b6e32 (his patches 0001-0003 on v7.2), MacBookAir6,1, kernel 7.2.9. Questions from his reply: which field is wrong on 2.4 GHz, and are there
errors on 5 GHz download.

## The PHY TX fault: found
The ucode saved the first fault on every 2.4 GHz scan probe: `phyctl 00c4 00b8 0000, plcp ... 040a 05f0` (CCK 1 Mbit/s, 190 bytes).
- TX descriptor ruled out: CCK on one core only (`0044`) and power offset 0 (`00c4 0000`, same as ours) both still fault.
- Register dump on the first fault at channel 6 (371 PHY/radio registers, 969 table cells of `traces/wl-final-*-2g-ch6.txt`): `tools/ale_dump.h`,
  `ALE_DUMP=1`. 113 registers and 111 cells differ; most are calibration results.
- **PHY 0x0003 (BANDCTL) bit 8**: his `b43_phy_ac_channel_switch_prep()` sets it on every channel switch
  (`b43_phy_maskset(dev, 0x0003, ~0x0100, 0x0100)`) and nothing clears it; wl's final 2.4 GHz state has 0x0000. Writing 0 at the end of the channel
  switch on 2.4 GHz: 0 faults in 21 scanned channels (`ALE_FIX1=a`). The other register groups tested alone (0x0402, 0x0910-3, 0x073b/093b/173b) change nothing.
  What bit 8 does is not known; on 5 GHz it is left set and 5 GHz works.

## 2.4 GHz receive: still dead in his tree
- Monitor mode on channel 6: 0 frames in 8 s; same card, same session, 5500 MHz: 48-49 frames. `iw scan` finds no 2.4 GHz BSS (the stick sees ours at 85).
- Tried together and individually, none brings RX back: PHY 0x0003/0x0402/0x0910-3/0x73b group, wl's values of 38 static PHY registers (per-core gain and
  clip thresholds 0x06dc-06e5/0x08dc-08e5, timing 0x0250/0x0261-3, ...), radio 0x0e/0x17/0x20e/0x217/0x24/0x224/0x225/0x113, GPIO front-end pins as our
  driver drives them (0xa7, GPIO1+2 high), table 7 cells 16-31 and 128-143.
- Table 7 finding, real but not sufficient: his TX->RX sequencer list (table 7 @ 0x10) lacks the leading 0xb3 opcode that wl and our `tables_phy_ac.c`
  have on core rev 42, so cells 16-29 are shifted by one; the delay list @ 0x80 lacks its leading 1 (cells 128-140). Also tables 0x44/0x45/0x64/0x65
  (offsets 8, 16, 32-41) carry 5 GHz values (his own warning: "first cell of each run is the 5 GHz value").
- Not yet looked at: radio 0x45/0x645, 0x2c/0x22c, 0x33/0x233, 0x122/0x322, 0x4e/0x24e, 0x145/0x146; table 12 (gain) differences; tables after calibration.

## Tools
`tools/build_alessio_driver.sh` options: `ALE_CCK1`, `ALE_CCKPO0`, `ALE_DUMP`, `ALE_FIX1=<letters a-h>` (a 0x0003, b 0x0402, c 0x0910-3, d 0x73b,
e/f radio groups, g table 7 lists, h 38 PHY registers), `ALE_GPIO`. The script's "init failed, unload" check in `try_alessio_driver.sh` greps
"ERROR" and fires on unrelated lines (an i915 message); load by hand with insmod when testing.
