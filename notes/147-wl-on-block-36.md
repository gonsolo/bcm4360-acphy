# 147: wl's state on the 80 MHz block 36-48 (router on channel 36)

Capture: `traces/wl-firstload-5g-20261011-092013.trace.xz`, decoded to `traces/decoded-firstload-5g-ch36/`
(wl connected to 8c:6a:8d:9e:2a:90 on 5180 MHz, centre 5210). Not a cold boot: b43 had been loaded in
this boot, so state may include earlier b43 writes.

First b43 result on that block (monitor mode, ac_5g_80=1, generic retune for centre 42):
330 beacons decoded, but 0 frames of the stick's VHT80 download (65 Mbit/s), rxbadfcs 17469.
Beacons decode, fast frames do not: same symptom as the 20 MHz 5 GHz path (notes/141).

Diff of wl's final PHY/radio state, block 100-112 (cold capture) against block 36-48:
- Farrow words 0x019a/9b/a1/a2, 0x1602/03/06/07: equal to `b43_phy_ac_farrow_80()` for 5210 MHz (ratio 0x1cf1c72, dphase 0x8d8332). Formula confirmed again.
- PHY 0x371-0x376: 0828 0824 0820 01f6 01f7 01f8 (channel table).
- Not written by our retune and different: PHY 0x030f (c040 vs 0040), 0x0910-0x0913 (0404 vs fefe; written
  once near the end of wl's init after a block of 0x3633 writes to 0x321..0x336), 0x0644-46, 0x06a0/a1, 0x0844/46, 0x08a0/a1 (per-core), radio 0x002, 0x024/25, 0x11a/11b, 0x203, 0x630, 0x65c, 0x662, 0x66d, 0x894-0x89c, 0x8c4/8c5, 0x8d6, 0x8dc, 0x8e6/8e7 (second-core PLL/VCO values, probably what `b43_phy_ac_tune` covers).
Next: boot clean, load b43 on this block, poke the PHY diffs live through debugfs and count decoded stick frames.
