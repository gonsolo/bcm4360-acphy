# notes/124: HT20 advertised + RX decode + MCS TX (stage 2): works, no throughput gain yet

`ac_ht=1` (default off): 2.4 GHz band gets HT20 caps (2 streams, no SGI, no aggregation); xmit.c uses
IEEE80211_TX_RC_MCS rates for the HT TX header (notes/123) and decodes HT-SIG on RX (frame type 2, MCS in byte 0).
Negotiates: tx MCS15 130 Mbit/s, rx MCS12 78 Mbit/s, 20/20 pings, 0 failed.

LAN TCP (pampelmuse ncat sink/source, 10 s runs, Mbit/s), same link, -65..-67 dBm:
- legacy (ac_ht=0): up 16 18 18, down 17 13 17
- HT (ac_ht=1):    up 22 13 15 21 20 21, down 12 12 14 12 13 12
About 10 % of TX frames are retried in both modes (9446 of 90941 HT; 10672 legacy), the AP's downlink rate sits at MCS4-12.
So the radio link quality (TX EVM/cal, RX sensitivity), not the rate set, limits throughput without aggregation.
Next candidates: TX calibration/power, retry analysis, A-MPDU.
