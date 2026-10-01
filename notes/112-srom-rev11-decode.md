# 112: SROM rev 11 decode of our card (offsets from Alessio's patch 0001)

Stock bcma has no rev 11 extractor, so `struct ssb_sprom` holds rev 8 offsets applied to a rev 11 image
(txchain 6, rxchain 0, ant_avail ff, fem2g/fem5g garbage). `cc` debugfs now also prints `sprom11` lines
decoded from the raw ChipCommon SPROM shadow (b43-src/phy_ac.c), using Alessio's rev 11 offsets
(0xa0 antavail, 0xa8 txrxc, 0xaa/0xac FEM cfg1/2).

Our MacBookAir6,1 BCM4360 (raw words in `/sys/kernel/debug/b43ac/sprom`):

    sprom11 ant_avail a 3 bg 3 txchain 3 rxchain 3 antswitch 0
    sprom11 femctrl 2 | 2g tssipos 1 epagain 0 pdgain 16 tworange 0 papdcap 0 | 5g tssipos 1 epagain 0 pdgain 16 tworange 0 papdcap 0 gainctrlsph 0

- 2x2 chip, as expected (not 6/0).
- femctrl = 2 confirmed (Alessio's boards all have 6, so his FEM control table scaffolding does not
  apply to us; our FEM control currently comes from wl's replay).
- External PA gain index 0, same in both bands; no PAPD cap.

Nothing in the driver consumes these yet; next is deciding where femctrl matters (per-band FEM control).
