# 148: 5 GHz VHT80 on block 36-48 works with the generic retune

Router on channel 36 (80 MHz, centre 5210). b43 loaded with `ac_5ghz=1 ac_5g_80=1 ac_vht=1`, temporary NM profile on band a, BSSID 8C:6A:8D:9E:2A:90.

- Connects at once: rx VHT-MCS 9 2SS 80 MHz (780 Mbit/s), tx MCS 7-8, signal -57 dBm.
- iperf (host route, path capped by router/gigabit host): up 76-90, down 62-66 Mbit/s.
- Three to four full 5 GHz scans while connected (they visit the other blocks): link and throughput unchanged. The round-trip problem of notes/144 does not appear here; it was specific to coming back to centre 106 after wl's captured state had been replayed for it.
- 10-minute soak with scans every 140 s: 2.76 M frames, 3333 failed (0.12 %), no b43 errors, stick 1142/1142 pings, up ~80-90 / down ~62.
- Monitor mode on this block decodes beacons but not the stick's VHT-MCS9 2SS frames; that is a limit of monitor-mode reception at that rate, not of the association (the connection itself runs MCS 9). Pokes of wl's PHY/table differences (notes/147) made no difference to it and were not needed for the link.

Not done: other blocks (only 36 and 112 tested), 20/40 MHz, DFS blocks beyond 112 untested, 5 GHz not enabled by default (`ac_5ghz=0`).

## Block 52-64 (centre 5290, router on channel 52, DFS)
Same procedure. Connects at rx MCS 8 / tx MCS 9 (2SS, 80 MHz), -56 dBm; iperf up 84-90, down 57-62. 5-minute soak with two scans: 1.25 M frames, 652 failed (0.05 %), no errors, stick 590/590. So three blocks work: 36-48 (centre 42), 52-64 (centre 58), 100-112 (centre 106, wl replay). Untested: 116-128, 132-144, 149-161; 20/40 MHz.
