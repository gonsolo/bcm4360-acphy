# notes/129: TX power / calibration, what we can and cannot tell (2026-10-07)

Same AP (ch11), same spot, both interfaces associated at once (iw link / station dump):
- b43: signal -73 dBm (avg -70, beacons -68), tx 48 Mbit/s (legacy), 1633 tx packets, 201 retries (12 %), 22 failed (1.3 %).
- stick (mt76x2u): -60 dBm, MCS15 tx, 1603 tx packets, 203 retries, 1 failed.
A 13 dB gap in reported RX level. Not conclusive: different antennas, and b43 reports the raw per-antenna power byte
(rxhdr +0x09/+0x0a, xmit.c) as dBm with no calibration offset (wl applies per-core RSSI corrections from SROM). The
13 dB may be antenna/report offset, a real RX gain/AGC shortfall, or both.
TX: retries match the stick (201 vs 203 per ~1600), so TX power into the AP looks adequate at this distance; the 1.3 %
failures are the legacy-rate frames at -73 dBm.
Decision: no blind port of the ~11k-line calibration code (TXIQ/LO, RXIQ, idle TSSI, tempsense). The replayed state was
captured on this very chip; the first thing to establish is whether range is a problem in practice.
Cheap discriminating tests (need the user): (1) walk-away test, b43 vs stick throughput/loss at increasing distance
(or behind a wall); (2) repeat the signal comparison with b43 and stick swapped to an AP at a known distance;
(3) if b43 loses badly, port the SROM RSSI offsets first (small), calibration second.

Update (user): the stick has two large external antennas, the MacBook's are small internal ones. That alone plausibly
explains most of the 10-13 dB RX level gap; the signal comparison is dropped as a test. TX retries (201 vs 203) are
antenna-independent and match. The uncorrected raw RSSI byte only affects the displayed signal and decisions that use it.
