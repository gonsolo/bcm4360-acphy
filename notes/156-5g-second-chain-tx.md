# notes/156: 5 GHz two-stream TX needs two table 7 cells (2026-10-12)

Finding: with wl's replay removed (notes/155) every two-stream frame on 5 GHz failed (HT MCS 8-15 at 20 MHz, VHT NSS 2 at 80 MHz,
all MCS, even MCS 0), one-stream worked. minstrel probes the two-stream rates, so the ~11 % TX retries (27 % at HT20) were that.
Next to the router, forced rates, 6 s uploads:

| build | NSS 1 MCS 5 | NSS 2 MCS 0 | NSS 2 MCS 5 |
|---|---|---|---|
| no replay (1fb7d47) | 1-5 % retries | all failed | all failed |
| d6c121c, replay of tables only (nt=3142) | 0 % | 1 % | 1 % |

Bisect on d6c121c with `ac_por5g_nt/ts0/ts1` (table entries applied / skipped), nss2.sh: not the radio words (nr=163 alone no),
not the PHY words; table ids 1-11 yes, 12 no, 14-136 no individually; ids 5/7/10/11 yes, id 7 alone yes; its entry range
872-910, then 894-902, then 897-899 = table 7 offsets 982, 983, 989 (core 1 timing cells). 982/983 are already 0x20; only
989 differs: 0x0352 (2.4 GHz default from tables_init) against 0x05d0 on 5 GHz. The core 0 twin, 973, is 0x02d3 against 0x03a2.
Writing 989 live alone did not help (retune put it back; our tune rewrites it); written in `b43_phy_ac_rfseq_ext_5g()` together
with 973 it works: NSS 2 MCS 0/5 at 2-6 % retries, 0 failed; minstrel up 76-84 Mbit/s at MCS 5 NSS 2 (was 59-78 at MCS 7 NSS 1).
`b43_phy_ac_restore_2g()` runs `tables_init`, which puts both cells back for 2.4 GHz.

Other table 7 cells still differ from wl's 5 GHz values (69 cells: 160-195, 249-263, 321-346, 398, 864-890, 1088-1091); not needed for
connecting or two streams, may matter for the remaining retries.
