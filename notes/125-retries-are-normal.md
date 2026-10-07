# notes/125: the ~10 % TX retries are not a radio fault

minstrel_ht rc_stats (/sys/kernel/debug/ieee80211/phy*/netdev:wlp3s0b1/stations/*/rc_stats), HT20 forced on (ac_ht=1):
per-attempt success MCS15 102574/111825 = 92 %, MCS14 85 %, MCS13 84 %; best rate MCS15, expected throughput 45-49 Mbit/s
at 1 frame per A-MPDU. RX side: 'rx drop misc' (duplicates after lost ACKs) 1688 of 81684 = 2 %. Signal -63..-67 dBm.
So uplink link quality is fine at the top rate; 8 % retries is ordinary for 2.4 GHz at this signal.
Measured LAN TCP (pampelmuse): up 16-22, down 12-14 Mbit/s; UDP at forced MCS15 ~29-35 Mbit/s vs ~42 theoretical
for unaggregated 1400 B frames (about 75-80 %). CPU 87 % idle, ~1100 rx pps on download.
Downlink: the AP sends to us at MCS4-12 (rx bitrate 39-78), the stick sees the same asymmetry (rx MCS4-11, tx MCS14-15).
Internet download via curl: b43 legacy ~13.8 Mbit/s vs stick ~22 Mbit/s: the stick's A-MPDU is the difference.
Conclusion: no radio bug to fix; the remaining gap to the stick is aggregation (and 5 GHz/40 MHz, not attempted).
