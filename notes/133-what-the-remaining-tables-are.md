# notes/133: what the 703 remaining first-load table entries are (2026-10-07)

Method: state dumps (debugfs b43ac/tbldump) are bit-identical across loads (0 differing lines), so replacing a replayed table with
real code can be verified exactly by diffing dumps. Alessio's tree (~/src/b43-ac-wip, phy_ac.c/ppr_ac.c) has real code for several.
| id | entries | what | real source |
| 0x07 | 211 | RF sequencer: rx2tx/tx2rx/reset2rx cmd+delay (offsets 0-0x3f, 0x90), updl lpf/tia hpc, per-core second rfseq setup (72 ops), plus gain/spexp cells | his b43_acphy_rfseq_* arrays + b43_phy_ac_rfseq_tbl_init(); delay/hpc blocks match ours exactly (24/24 compared); cmd arrays use symbolic opcodes (not yet parsed) |
| 0x0a | 96 | FEM control pattern, 3 x 32 | his fem6_tbl differs from ours in 9-21 of 32 entries (router vs MacBook board): board-specific, derive from SROM/boardflags (femctrl) |
| 0x0b, 0x0c, 0x0e | 13, 63, 40 | small constant tables (0x0b: 8 distinct, 0x0e: 20 distinct) | unknown, check wl tables acphy_* ids 0xb/0xc/0xe |
| 0x21 | 24 | final value all zero | trivial: 24 zero writes (his b43_actab_write_bulk(0x21,0,32,24,ppr) with ppr = 0 at this point) |
| 0x40, 0x60 | 128 each | est_pwr_lut core0/core1, ours has 0/128 matches with the rev0 default arrays (tbl_05/tbl_06) so they are the programmed power-estimation LUT | TX power control setup (txpwrctrl program from SROM pa params); part of the TX power / calibration port |
So real-code replacement order by effort: 0x21 (zeros, trivial) < 0x07 (symbolic arrays exist, verify with dump diff) < 0x0a (needs board FEM derivation)
< 0x0b/0xc/0xe (unknown) < 0x40/0x60 (TX power control). The 290 PHY writes (all contribute, notes/132) are the larger open item.
