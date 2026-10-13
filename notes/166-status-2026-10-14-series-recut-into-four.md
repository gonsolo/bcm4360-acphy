# 166: the 13-patch series re-cut into Alessio's four series (14 patches)

Alessio (reply to the RFC, 2026-10-13): split into several series or it gets struck down as "too much"; gate MAC things on the ucode revision and PHY
things on the PHY revision, not mixed. Order: (1) BCMA integration for rev 11 (his patch 0001) and the generic DMA64 fixes, without comments, (2) core
support gated on rev 42 without TX/RX formats and PHY, (3) TX/RX formats per ucode version, (4) the whole PHY and the removal of "depends on BROKEN".

## Result: `upstream/split/{A,B,C,D}/` (git format-patch, cover letters, one mbox each), branch `series2` in ~/b43-upstream, target tree `final2`
| series | patches |
|---|---|
| A generic (`[PATCH wireless-next]`) | 1 MAC filter after interface restart; 2 64-bit DMA engines with bus-address index registers (probe, no comments, no debug prints); 3 RX refill retry (now called from the generic 15 s work) |
| B core 40/42 (RFC) | 4 DMA burst/prefetch bits (`b43_is_ac_core()`); 5 MAC core setup (+ `b43_ucode_is_ac()` for key table/set_key); 6 AMT, templates, beacons |
| C formats (RFC) | 7 11ac chanspec (`b43_ac_chanspec()` in phy_common.c, 20 MHz only); 8 TX descriptor + status; 9 RX header; 10 A-MPDU (`AMPDU_AGGREGATION` set only on core 40/42) |
| D PHY (RFC) | 11 radio 2069 + tables; 12 PHY init + 2.4 GHz (+ 2.4 GHz HT caps); 13 5 GHz, 80 MHz, VHT (80 MHz chanspec, 5 GHz band caps); 14 drop BROKEN |
The use-after-free fix (sent 2026-10-13) is the base (commit 2bd8d42), not part of the series.

## Gating (the change that matters)
- `b43_is_ac_core(dev)`: core revision 40 or 42. Used for what is decided at attach or by the core: DMA control bits, GPIO, FIFO carve-out, MACCTL, intrcvlazy, PHY reset, `AMPDU_AGGREGATION`.
- `b43_ucode_is_ac(dev)`: `fw.rev >= 784`, valid once the ucode runs. Used for ucode layout: AMT, templates, beacon slots, ACK/CTS ctl word, TX descriptor, TX status,
  RX header, key table skip, set_key, ampdu_action, SHM chanspec. Only 832 is tested.
- `phy.type == B43_PHYTYPE_AC` remains only for PHY things: band tables with HT/VHT caps, and stock code.
- Moved out of phy_ac.c: the 80 MHz centre and the chanspec (phy_common.c), so formats do not depend on the PHY file; DMA RX retry no longer called from the AC PHY.

## Checks
- All 14 commits compile alone (`REMOTE=pampelmuse tools/build_upstream_tree.sh`, 11 s instead of minutes; the first local attempt was too slow; user pointed at pampelmuse).
  `tools/upstream/cut2.py` (regions of final2 vs base assigned to patches, small text overrides for the burst bits and the 80 MHz chanspec, `stage_a2.py` for the 2.4 GHz-only phy_ac.c),
  `format2.py` (format-patch + cover letters from `messages2.py`). The end state `series2` equals `final2`.
- checkpatch: only "Missing Signed-off-by" errors; warnings: 12 trailing `*/` of block comments, a few long lines (PHY code), patch D1 data lines.
- **Live test of the end state** (`b43-src-builds/upstream-final2-7.2.10.ko`, no module parameters, stock bcma, stick as link, netconsole): first init connected at once;
  2.4 GHz ch11 -51 dBm HT MCS 14/15: upload 63.3, download 54.1 Mbit/s; 5 GHz ch64 -78 dBm VHT 80 MHz: upload 53.1/40.2, download 69.5/58.5 Mbit/s; 0 lines of
  error/warning/restart in the log. Not tested with this build: suspend/resume, 2.4 GHz and 5 GHz roaming, A-MPDU sessions separately, other boards.
- Not tested with the generic parts on other chips: the DMA probe (write 0xff0 to TXRINGLO of every 64-bit engine), the RX refill retry, the MAC filter fix.

## Open
- Provenance statement with Alessio; comments that credit his tree are still in the code (PROVENANCE-REVIEW.txt was for the 13-patch version).
- Alessio's BCMA patch (his 0001) is series 1 for him; ours has no BCMA part. His bcma patch pre-writes PMU PLL values; worth testing against the dead chip after long suspend (notes/164).
- Patch 4/5 split of gating is untested on ucode 784 and 928.
- Sending: series A needs Signed-off-by (`git format-patch -s` or amend), list and Cc as for the use-after-free patch (notes/163), tree prefix `wireless-next`.
