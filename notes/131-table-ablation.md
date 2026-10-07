# notes/131: which first-load table entries are needed (2026-10-07)

Offline (scratchpad tblcmp.py): of the 3022 unique first-load table writes, 1974 are identical to what tables_phy_ac.c
(real init tables, "wrote 23 PHY tables") already writes, 262 differ (ids 0x40/0x60 and 6 of id 0x04, probably the
duplicate id-64 arrays in our table list, last write wins), 786 are not covered (ids 0x07 0x0a 0x0b 0x0c 0x0e 0x10 0x21 0x44 0x45 0x64 0x65).
Ablation with `ac_replay=0 ac_por=7` and the new param `ac_por_tskip` (groups, one load each, loss/speed after settling):
| skipped | result |
| ids written identically by tables_phy_ac.c (0x80) | 0 %, 0 % again, ok |
| id 0x07 (211) | 100 % loss: needed |
| ids 0x0a/b/c/e (152) | 67 kB/s: needed |
| id 0x10 (243) | ok: not needed |
| id 0x21 (24) | 40 % loss: needed |
| ids 0x44/0x45/0x64/0x65 (96) | ok: not needed |
| ids 0x40/0x60 (256) | 15 % loss, 0.5 MB/s: needed |
| id 0x04 (6 differing) | ok |
Combined skip of everything "not needed" (mask 212) vs baseline, interleaved: baseline loss 0/0/35/30 %, skipped 0/5/0 %; speeds
1.5-1.8 vs 1.3-1.7 MB/s. The ping-loss scatter of this measurement is about +-30 %, so only large effects are detectable.
Result: phy_ac_por.h table list cut from 3022 to 703 entries (ids 0x07 0x0a-0x0c 0x0e 0x21 0x40 0x60); verified 4/4 loads, 0 % loss
in 3/4, 1.2-1.5 MB/s. The 703 are what real init code must still produce: next, find their meaning (0x07 = ?, 0x40/0x60 = per-core
tables, 0x0a-0x0e small constants) and the same for the 290 PHY and 163 radio writes. Param `ac_por_tskip` kept for ablation.
