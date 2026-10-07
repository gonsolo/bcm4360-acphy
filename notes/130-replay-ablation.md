# notes/130: what the replayed vendor state is actually needed for (2026-10-07)

With the init now deterministic (notes/122) the old ablations can be redone. Judge = tools/b43_load_until_connected.sh with
B43_TRIES=1 (tools/b43_ablate_connect.sh), and for link quality 20 pings + 10 MB download after a 25 s settle
(tools/b43_ablate_quality.sh). NM "connected" and an immediate ping are NOT usable judges (baseline failed that check).
Classes of `ac_por` (first-load state): 1 radio (163 writes), 2 PHY regs (290), 4 tables (3022), 8 SHM (795),
16 chipcommon (18), 32 PMU (1); `ac_replay` = the 969-entry ch6 replay.

Connect test (replay off, one class removed from 63): without radio / SHM / cc / PMU still connects 3/3; without PHY regs the
AP is never seen; without tables bad init. Replay on or off with ac_por=63: 4/4 either way.
Quality test (loss / download):
| config | loss | speed |
| base 63 + replay (twice) | 0 % | 1.73 / 1.65 MB/s |
| replay off, 63 | 0 % | 1.60 |
| replay off, 62 (no radio) | 20 % | 0.54 |
| replay on, 6 (phy+tbl) | 20 % | 0.77 |
| replay off, 55 (no SHM) | 0 % | 1.29 / 1.67 |
| replay off, 47 (no cc) | 0 % | 1.67 |
| replay off, 31 (no PMU) | 0 % | 1.64 |
| **replay off, 7 (radio+phy+tables)** (twice) | 0 % | 1.56 / 1.59 |
| replay off, 15 (+SHM) (twice) | 0 % | 1.56 / 1.62 |
Conclusion: radio + PHY regs + tables (3475 writes) are the real content; the ch6 replay (969 entries, also executed on
every scan return to ch6), SHM (795), chipcommon (18) and PMU (1) first-load writes are not needed on this setup (2.4 GHz,
ch11 AP). Next: make `ac_replay=0 ac_por=7` the tested default (soak, suspend/resume, scan), then shrink the 3475 writes the
same way (per table id, per radio register range) and replace survivors by real init code.
Caveat: single 20-ping/10 MB samples; the 20 % vs 0 % gap is large, differences of ~10 % in speed are noise.
