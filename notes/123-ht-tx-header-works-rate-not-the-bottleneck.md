# notes/123: HT20 TX header found; PHY rate is not the throughput bottleneck

Experiment (xmit.c `ac_httx` = MCS+1, `ac_httx_var`, both runtime-writable under /sys/module/b43/parameters):
unicast data frames sent as HT20 instead of legacy. HT rate entry in the AC TX header:
phy0 = FT 2 (HT) | 0x4 | txcore mask (3 for MCS8-15), PLCP = brcmsmac HT layout (mcs, len lo, len hi, 0x07, 0, 0),
rate field (ri+0x0e) = HT rate in 500 kbit/s units, **rate index (ri+0x04) = MCS** (var bit 0; with 0 only MCS0 works).
Rate field 0x80|mcs (var bit 1) breaks it.
Measured with `iw station dump` tx retries/failed deltas over 20-30 pings: MCS0-15 all 20/20 acked, 0-3 retries, 0 failed.

But throughput does not move: LAN upload to pampelmuse (ncat sink) 19-20 Mbit/s legacy 54, 17-19 at MCS7,
22-24 at MCS15; UDP blast 23/23/29 Mbit/s. CPU 89 % idle, ~1700 IRQ/s (about one per frame):
the TX path is limited per frame (~450 us), not by airtime. verbose=1 changes little.
Next: find the per-frame limit (TX completion/ring/queue depth), then A-MPDU.
Harness gotchas: tools/connect_test.sh-loaded links don't pass data reliably; use
tools/b43_load_until_connected.sh with B43_LOAD pointing at a b43_boot.sh copy that insmods b43-src/b43.ko.
Two interfaces on one subnet: use `ping -I`/`curl --interface`, rp_filter 0 on wlp3s0b1.
