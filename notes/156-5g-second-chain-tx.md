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

## Cell 398 (same day)
The other 66 differing table 7 cells, applied live in six groups (160-195, 249-263, 321-346, 398, 864-890, 1088-1091) and
measured at fixed NSS 1 MCS 7 and NSS 2 MCS 7 (two streams at MCS 7 was dead): only offset 398 (wl 0x0049, ours 0) matters. With it
NSS 2 MCS 7 carries 22-24 Mbit/s (54 % retries, 27 failed, was 0 and dead); the other groups add nothing on top. Written
next to 973/989. With all three, minstrel settles on VHT-MCS 6 NSS 2 (tx 526 Mbit/s), up 68-84, down 63-65 (path ceiling),
0-3 failed per 55k frames. 5 -> 2.4 GHz switch puts 398/973/989 back (0 / 0x2d3 / 0x352), 2.4 GHz connects at MCS 14-15.

## HT20 on 5 GHz again with the fix (ac_5ghz=1 only)
Upload 61-74 Mbit/s at HT MCS 15 two streams (was 35 at MCS 7), TX retries 1 % (was 27 %). Download still 21-24 Mbit/s: the one
problem left from notes/142 (20 MHz RX on 5 GHz; the 80 MHz mode receives fine, 63-65). 114 PHY words differ between our 20 MHz and
80 MHz state (Farrow 0x180-0x1c6, per-core 0x6xx/0x7xx, 0x531-0x539, ...), no wl reference for 20 MHz on 5 GHz to decide which
belong to the bandwidth and which to a missing 20 MHz setup. Open.

## 5 GHz on by default (same day)
Module defaults now `ac_5ghz=1 ac_5g_80=1 ac_vht=1 ac_por=7`; the boot service's `ac_replay=0 dma32=1 ac_por=7 nohwcrypt=1` is still accepted
unchanged (the NixOS config is not touched). Loaded with exactly those arguments, no 5 GHz flag: NetworkManager autoconnects
Vodafone-2A84 to the 5 GHz BSS (rx VHT-MCS 7 NSS 2, tx MCS 9), no manual profile. Soak 3 min up + 3 min down with a scan in the middle
of each: up 72-82 Mbit/s (39 in the scan window), down 59-64 (49 in the scan window); 399 failed of 1.1 M frames (0.04 %); NM roamed
5 GHz -> 2.4 GHz -> 5 GHz during the run (17 s apart) with traffic carrying on.
