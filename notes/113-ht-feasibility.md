# 113: HT (802.11n) feasibility, read-only look

Result: HT is not a capability flag, it is missing end to end in b43-src.

- main.c: no `ieee80211_sta_ht_cap` on any band; only legacy rate tables (b43_g/a ratetable). No
  AMPDU/HT hw flags set (only RX_INCLUDES_FCS, SIGNAL_DBM, MFP_CAPABLE).
- xmit.c TX: `b43_generate_plcp_hdr` has `if (0) { /* FIXME: MIMO */ }`; only legacy PLCP words are built.
  HT TX needs the MIMO PHY control words in the TX header (format per ucode rev) plus
  rate-control feedback (TX status -> MCS) for minstrel.
- xmit.c RX: rate index comes only from legacy PLCP (`b43_plcp_get_bitrate_idx_ofdm/cck`); no
  MCS/NSS/BW parsing, no `RX_ENC_HT`, `for_ampdu` unused.
- Aggregation (A-MPDU) is not implemented at all.
- Unverified: whether our replayed 2.4 GHz PHY state enables the 11n TX path.

So HT is a multi-part feature (TX header + RX decode + capabilities + rate control feedback), and TX
reliability (only ~21 % of inits transmit) comes first. Parked until the init failure is understood.
