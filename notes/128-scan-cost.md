# notes/128: what a scan costs the link (2026-10-07)

ping -D every 0.1 s to the gateway via b43 while `iw dev wlp3s0b1 scan trigger` runs once: for ~4.4 s (seq 24-67)
the pattern is 2 lost pings in every 4 (period 0.4 s), 21/150 lost in total, no gap longer than 0.5 s. That is
mac80211's normal off-channel hopping (return to the operating channel between scan channels); the ch6 replay does not
show up as a long stall (no "optiming" outliers; the replay costs ~1 channel hop). Three scans in 20 s: 24 % loss.
Conclusion: not a driver defect, expected cost of a software scan on an associated station; background scans from
NetworkManager happen rarely. Nothing to fix; reducing it would mean fewer scan channels/dwell (mac80211/NM policy).
