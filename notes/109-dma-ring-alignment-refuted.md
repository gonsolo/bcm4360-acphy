# 109 - DMA descriptor ring 64 KB alignment (b43-ac-wip core patch): refuted

Hypothesis: Alessio's core patch says the AC-PHY DMA64 engine needs each descriptor ring 64 KB-aligned and
not crossing a 64 KB boundary (stock b43 allocates 8 KB per ring, so alignment would be luck at every core
init = a per-init coin flip with ~1/8 odds, similar to our ~20-30 % clean rate).

Test: logged every ring's physical base and 64 KB alignment at allocation (stock 8 KB rings, no code change
in behaviour) over 12 connect attempts, recording the rings in effect next to the outcome.
- connected attempt 3: no ring 64 KB-aligned; connected attempt 8: only the RX ring aligned;
- attempts 5, 6, 7, 9, 10 each had an aligned TX ring and all five failed to connect.
No correlation, so alignment does not decide whether an init works; `ac_ring64` (64 KB rings) was
therefore not worth an A/B run. Reverted (dma.c is stock again).

Remaining differences to his code (notes/108): run-time calibration chain (RX IQ, RX AFE, LOFT, idle TSSI,
TX power control, tempsense, CRS min-power watchdog), a different build method (trace-driven, unit-tested),
5 GHz only so far. Alessio is looking at our 2.4 GHz trace.
