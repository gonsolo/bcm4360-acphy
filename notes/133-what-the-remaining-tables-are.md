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

## Done (same day)
- id 0x21: now a real zero table in tables_phy_ac.c (24 entries removed from the replay).
- id 0x07: 136 of 211 entries are now named RF-sequencer arrays in tables_phy_ac.c (opcode enum after Alessio's tree; rx2tx/tx2rx/
  reset2rx commands, rfseq2 commands per core, delay blocks, update-delay cells), written by b43_phy_ac_tables_init and removed from
  the replay. Note the tx2rx list starts with an extra opcode 0xb3 on this core rev; his array has no such opcode.
- Verified exactly: tbldump (all 31 tables, 5383 cells) bit-identical to the pre-change dump (0 lines differ), including after a fresh
  load + connect. Replay now: id7 75 entries, 0x0a 96, 0x0b 13, 0x0c 63, 0x0e 40, 0x40 128, 0x60 128 = 543 table entries (from 3022).
- Remaining id 7 offsets: 0x6a-0x6f, 0xf9, 0x100-0x106 (gain coefficients), 0x140-0x15a, 0x18e, 0x360-0x37a, 0x3c6-0x3e7, 0x3fa-0x3ff, 0x440.

## Why the rest is not a cheap win (checked)
- id 7 @ 0x100/0x103/0x106 (gain codes ff00, 07cf, 00a7, both cores): Alessio's b43_phy_ac_txgain_program() derives them from an entry of the
  TX gain LUT; no entry of his 5 GHz LUT (txgain_epa_5g_2069rev4) gives these values, so they come from the 2.4 GHz LUT, which his tree lacks.
- id 0x0c: three groups: gain-index ramps (0x00-0x11, 0x20-0x31: 0x100,0x200,0x300,0x500,0x800,0xb00,0x1000,..), setup cells 0x40-0x4d, and
  bbmult/limit cells 0x5f-0x77 (0x3f at 0x63/0x73/0x67/0x77 ...). The bbmult cells are the ones his TX-power code writes; the ramps are not in his tree.
- id 0x40/0x60: programmed power-estimation LUT (does not match rev0 defaults at all). id 0x0a: board FEM pattern (differs from his router table). id 0x0b: gain limits
  (his code writes 0x0b @ 8 (6 cells) and @ 0x10 (7 cells) from glim_a/glim_b), 0x0e: tone tables.
So the remaining 543 entries are a coherent block: the TX gain / power-control setup for the 2.4 GHz band on this board. Replacing it needs the 2.4 GHz TX gain
LUT (wl's acphy_txgain_*2g* tables, in the wl object in the repo's disassembly) plus Alessio's txpwrctrl programming; this is the TX power/calibration item.
