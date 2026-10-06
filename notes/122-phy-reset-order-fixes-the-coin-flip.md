# notes/122: the per-init coin flip is the PHY reset order (FOUND)

Alessio's repo (commit "reset the core as wl do") forces the clock while the PHY is in reset (IOCTL 0x14f).
wl's AC sequence (seq.txt 2421-2432): 0x105, 0x101, 0x105, [MAC regs, 64 us], 0x14f, 2 us, 0x14f,
0x141 (reset off, FGC off, PHYCLKEN off), 1 us, 0x145.
Generic b43 does: reset on without FGC, then reset off WITH FGC forced and PHYCLKEN off, then FGC off.
The PHY clock divider phase after reset is then random: good rate ~25-30 % (= TX handoff MAC/PHY domain).

Fix: `ac_phyreset` (main.c b43_bcma_phy_reset), default on, for core rev 40/42: wl's order.
Results (ac_selfheal=0, raw first init): 20/20 connected with 0 PHY TX errors, then 8/8 and 20/20 with defaults.
Before: 8/30, 11/30, 3/24.
Ruled out along the way (notes/121): rfseq delay, replay padding, PHY tables, IOCTL value after init.
Not yet ported from Alessio: pcie2 HAVEHTREQ (CLKCTLST), skipping bcma_core_pll_ctl on AC.
