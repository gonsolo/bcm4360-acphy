# 135: radio replay (51 writes) is unnecessary

Paired alternating A/B (5 pairs, 20 pings + 3 downloads each, `ac_replay=0 ac_por=7` vs `ac_por=6`):

| pair | radio replay | no radio replay |
|---|---|---|
| 1 | 1355 kB/s | 1549 |
| 2 | 1283 | 1375 |
| 3 | 1309 | 1543 |
| 4 | 1361 | 1384 |
| 5 | 1544 | 1521 |

Loss 0% everywhere, every load connected and held 25 s. Averages ~1370 vs ~1470 kB/s (not worse).
The 51 captured radio writes were deleted from `phy_ac_por.h`; tbldump still identical.
Replay left: the 290 PHY register writes only (`ac_por` bit 2).
