# 141: first 5 GHz connection with b43 (HT20, channel 112)

After notes/139 (RX) three more things stood between a scan result and a link:

1. **No HT on the 5 GHz band.** Auth worked at once (auth and assoc response within 8 ms: 5 GHz TX works), but the AP answered the association with status 18 (basic rates not supported). `b43_band_5GHz_acphy` had no HT capabilities; with `ac_ht` it now gets the same `ht_cap` as the 2.4 GHz band. Then: status 0, associated.
2. **wl's SHM in the 5 GHz replay.** Associated, but the 4-way handshake failed ("pre-shared key may be incorrect"): 4 frames sent, none failed, the AP kept repeating message 1. `apply_por5g` wrote wl's whole shared memory on every 5 GHz switch, key and session state included, so the microcode mangled our EAPOL frames. The SHM, chipcommon and PMU classes of the 5 GHz state are now applied only with their `ac_por` bits (8/16/32); the default `ac_por=7` leaves them out. Reception does not need them.
3. **The 5 GHz wide tables**: TX gain table 0x20 with wl's 5 GHz values (`b43_phy_ac_txgain_5g`, from the trace) and the table 0x11 fill `bf25 0071 4002`, next to the RF sequencer extension. The replayed PHY state has hardware TX power control on (0x70 = 0xe500), which needs table 0x20.

Result, notebook next to the router, `ac_5ghz=1`, temporary NM profile pinned to the 5 GHz BSSID 8c:6a:8d:9e:2a:90:

- Connected on 5560 MHz, -51..-53 dBm, DHCP address, ping fine.
- Upload 48.2, 39.7, 30.9, 43.1 Mbit/s (TX MCS 10–15, 2–6 % retries).
- Download 14.8, 17.8 Mbit/s; the AP sends at MCS 0 (rx bitrate 6.5).
- No driver error, no warning, no freeze. 20 MHz path only; `ac_5g_80` untouched.

Open:
- Download: the AP falls to MCS 0 towards us, so reception of HT frames on 5 GHz is poor although beacons arrive at -51 dBm. The PHY/radio state is wl's 80 MHz snapshot retuned to one 20 MHz channel; RX filters, the bandwidth-dependent registers and the 0x14 entries for 20 MHz are candidates.
- Confirm from a cold boot.
- 40/80 MHz and VHT; other channels than 112 (rpcal fill, VCO block); `ac_5ghz` stays off by default.
