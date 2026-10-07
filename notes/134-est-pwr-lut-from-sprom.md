# notes/134: tables 0x40/0x60 are computed from the SROM (2026-10-08)

The 128-entry est_pwr LUTs match the nphy-style transfer function exactly (128/128 for both cores) when fed with the SROM power-detector
triples (a1, b0, b1): core 0 = SROM words 0x6d..0x6f (ff39 1776 fd13 = -199, 6006, -749), core 1 = words 0x81..0x83 (ff32 17c1 fd0d).
These are the pa2ga coefficients (found by trying every consecutive word triple of the SROM against the captured table).
step j: num = 512*b0 + 32*b1*j, den = 0x8000 + a1*j, v = (den/2 + num)/den clamped to [-8, 0x7f]. Formula as in Alessio's
b43_phy_ac_est_pwr_lut() (he uses pa5ga for the 5 GHz sub-bands; 2.4 GHz uses pa2ga, which he does not have).
Implemented as b43_phy_ac_write_est_pwr() in b43_phy_ac_tables_init (reads the SROM words through the chipcommon SPROM window);
the 256 replayed entries are gone. Check: tbldump (31 tables, 5383 cells) bit-identical to the baseline, fresh load + connect.
Lesson (PHY registers): a register dump is NOT a stable acceptance test: 115 registers differ between two identical loads and more once
the radio environment changes, so a 2-load volatile set is too small (the first delta-debug run was invalid for this reason). Table dumps are stable.
Replay left: tables 0x07 (75), 0x0a (96), 0x0b (13), 0x0c (63), 0x0e (40) = 287 entries (from 3022).
