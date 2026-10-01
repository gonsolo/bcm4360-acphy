# 110 - TX status attempt-count bug: every frame looked like a retry (upload 1 -> 18 Mbit/s)

Symptom (after the wrapper made b43 the main link): `iw station dump` showed tx bitrate 1-6 Mbit/s, rx 36,
"expected throughput 0.64 Mbps", tens of thousands of tx retries; a 12 MB upload did not finish in 90 s
(~1 Mbit/s). Retries stayed at ~1.2 per frame at every forced rate, with every TX power (`bbmult` 0x3f..0x78
made no difference) - so it was accounting, not air-time loss.

Cause: `handle_irq_transmit_status()` (main.c) for AC took the attempt count as the sum of four byte
fields of status words 2/3: `(v2&0xff)+((v2>>16)&0xff)+(v3&0xff)+((v3>>16)&0xff)`. Raw words of acknowledged
frames are `xxxx8103 00000000 00010001 00000000`: the low byte (1) is the attempt count; bits 16-23 hold a
constant 1 on every acknowledged frame (0 on suppressed ones), not a second counter. Summing them reported
2 attempts for a frame sent once and acked (40 of 42 sampled frames), so mac80211/minstrel saw ~50 %
failures at every rate and parked TX at the bottom.

Fix: `frame_count = v2 & 0xff` (module param `ac_txs_sum=1` restores the old sum for comparison).
Measured after reloading b43 with the fix (same AP, -70 dBm, ch6): tx bitrate 54 Mbit/s, retries +24 per
100 pings (was ~125), expected throughput 17.3 Mbps, **upload 24 MB in 11 s = 18.2 Mbit/s** (was ~1),
download 10.5 Mbit/s. Download is limited on the AP side: our firmware-generated ACKs still fail
(PHY TX error on SIFS-timed responses, notes/07/12), so the AP retransmits towards us - a root-cause
symptom, not fixed here.

Method note: the `verbose` module parameter is writable at runtime (echo 3 > /sys/module/b43/parameters/
verbose) and makes the driver log the raw `AC txstatus` words; tabulating them is how the bug showed up.
