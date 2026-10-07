# notes/132: PHY and radio first-load writes (2026-10-07)

Base: `ac_replay=0 ac_por=7` (notes/130), tables already cut to 703 (notes/131). Params `ac_por_pfrom/pto`, `ac_por_rfrom/rto` skip index ranges.
Chunk scan (one load each): PHY chunks of 29 and radio chunks of 28. Needed (loss/slow): PHY 203-232 (60 % loss, 2 kB/s), PHY 232-261
(939 kB/s), radio 112-140 (25 % loss, 517 kB/s), radio 140-168 (5 % loss). All other single chunks looked harmless.
But harmless chunks are not independent: skipping PHY [0,203) as a whole gave 370 kB/s; prefix scan [0,N) with radio [0,112) skipped:
N=29..174 about 1.3-1.6 MB/s (116: 786 kB/s, 25 % loss, noise?), so 0-174 looked ok. Paired A/B check (6 alternating loads each, 3 downloads averaged):
A = full PHY+radio: mean ~1340 kB/s, loss 0 %; B = PHY[0,174) + radio[0,112) removed: mean ~937 kB/s, worse in all 6 pairs, 3 loads with 5-35 % loss.
=> The cumulative PHY cut costs ~30 %: single-load chunk tests understate effects of many small contributions. PHY cut reverted.
Radio only (paired, 5 alternating loads): A 1092, B (radio [0,112) skipped) 1028 kB/s, B wins 2 of 5: within noise. Applied: radio list 163 -> 51 entries,
4/4 loads connect. Lesson: use paired alternating A/B with >=5 pairs and averaged downloads; single-sample quality is +-30 %.
State after this: replayed data = PHY 290 + radio 51 + tables 703 (was 290 + 163 + 3022, plus 969 ch6 replay, SHM 795, cc 18, PMU 1).
