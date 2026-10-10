# 137: A-MPDU TX works (branch wip-ampdu), not yet stable

Load with `ac_ht=1 ac_ampdu=1`; `ac_ampdu_hdr` (runtime, default 7) selects the session header parts: bit 0 MAC control 0x45c0 and no fixed-rate flag, bit 1 cache info, bit 2 sequence number.

What was missing, found by comparing with a raw stock header (router-data/vd625-agcombo/rxtx-1s-ht20-40-80.zip, `c0 45 ...`):

1. **Sequence number at header +0x0e** (the frame's seq_ctrl). Without it the link dies.
2. **Cache info bytes 0–1 must be 0 for us.** The stock `50 04` are cipher and key index: the ucode then encrypts the already software-encrypted frame. The AP acks it (FCS is fine) and drops it: "acked but no traffic". Ours: `00 00 20 20 26 15 3f 14`.
3. **Cache info is required** with 0x45c0: without it (hdr 5) the AP deauths us.
4. **minstrel_ht ignores session frames without IEEE80211_TX_STAT_AMPDU**, so rates stayed at MCS 0–3. Now every MPDU is reported with ampdu_len 1.
5. **The attempt count of a status covers the whole aggregate** (word 2: attempts in 7:0, acked in 15:8). Reporting it per MPDU made 7 attempts per frame. Now attempts / MPDUs.

TX status with aggregates, e.g. `20668703 00000fb2 00000707 0 / 1 0000007f 0 ...`: 7 MPDUs from seq 0xfb2, 7 attempts, 7 acked, bitmap 0x7f. Cookies advance by 2 per MPDU (two ring slots).

Result next to the router, iperf3 8 s upload: 8.4, 18.6, 30.1, 11.1, 9.3, 38.0, 9.2, 10.7 Mbit/s; with sessions but no ucode aggregation (hdr 0) 18.5–20; download 17.7. Bimodal: 30–38 when it runs, ~10 with 50–70 failed frames per run. A failed MPDU is given up after 4–6 attempts at the one rate we pass.

Next: fill the fallback rate blocks (stock passes up to four), RTS/CTS word 0x0905 and FBW 0x0300 as stock, and see what the failed MPDUs have in common.

Also: every b43 reload restarts wpa_supplicant on NixOS (udev rule in /etc/udev/rules.d/99-local.rules) and drops the USB stick for ~19 s. tools/postboot.sh installs a runtime override; it was not active in this boot.

## Later the same day: stable with a driver-side requeue

Ruled out as the cause of the 50–90 failed frames per 8 s run: aggregate size (`ac_ampdu_mpdus` 1–32), a fallback rate block (hdr bit 3), four rate blocks (bit 4), the chain mask, the TX ring depth (`ac_txslots` 64/96/256), legacy probe frames (session header now only on HT-rate frames).

The cause: the microcode tries an MPDU only a few times (2+2 with two rate blocks) and then reports it unacknowledged; the stock driver puts such an MPDU back on the ring, we dropped it, and TCP collapsed. With single-MPDU aggregates 1.4 % of frames ended that way, often two or three consecutive sequence numbers.

`ac_ampdu_requeue` (default 4): an unacknowledged session frame goes back on the ring with the Retry bit set, up to 4 times; the count sits in `skb->mark` (0xb430nnnn), which needs a proper place before upstreaming. Failed frames: 0–14 per run.

Upload next to the router, iperf3 8 s, requeue on:

| MPDUs per aggregate | Mbit/s | retries / packets |
|---|---|---|
| 4 | 39.3, 36.0 | 15–21 % |
| 8 | 30.7, 38.1 | 19–37 % |
| 16 | 19.4, 34.9 | 26–44 % |
| 32 (stock) | 22.8, 29.6 | 43–46 % |

Retries grow with the aggregate length: the later MPDUs of a long frame are lost. That points at the transmit signal (drift over the frame; no TX calibration yet, see the 12 dB margin in notes/136), not at the aggregation logic. Default `ac_ampdu_mpdus=4` until that is fixed. Download with sessions: 19.1–19.7 (legacy 17.3).

Reference: legacy 20, HT without aggregation 22 Mbit/s up.
