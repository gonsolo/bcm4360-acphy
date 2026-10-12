# notes/159: hardware crypto on the AC ucode, decoded from a capture; not pursued (2026-10-12)

Decision: not implemented. A 5 GHz download at 43-65 Mbit/s costs about 37 % of one core in total (iperf3, TCP stack, DMA copies and
mac80211's software CCMP together; idle 28 %, 2 cores / 4 threads, AES-NI). The AES part is far below 1 % of a core at 8 MB/s,
so the gain would be nothing measurable, and a wrong key slot or header field drops the link. Alessio's driver also keeps `hwcrypto_enabled`
off on `B43_FW_HDR_AC`. If it is ever wanted, this is what is known.

## What Alessio's archer-t5e mmiotrace shows (6.30.223 wl, ucode 832 = ours, WPA2 CCMP on ch157/80)
Decoded with `reverse-tools/mmio2ops.py`; the key installation is at +2.3 s, two keys:

| step | writes |
|---|---|
| pairwise key | SHM `0x05e8 = 0x0045`; SHM `0x1134..0x1142` = the 16 key bytes (8 words); AMT row 0 (selector 0x40000, words 0/1) = peer MAC + flags `0x8004`; SHM `0x0668 \|= 0x1000` |
| group key | SHM `0x05e2 = 0x0015`; SHM `0x1104..0x1112` = the 16 key bytes |

- Slot s: index word at SHM `0x05e0 + 2 s`, key material at `0x10f4 + 0x10 s` (16 bytes per slot, 60 slots = the 480 words the stock driver clears).
  Pairwise key in slot 4 + AMT row (row 0 -> slot 4), group key idx 1 -> slot 1: b43's own numbering (4 group slots, pairwise after them).
- Index word: low nibble 5 = the AC ucode's cipher number for a 16 byte key (CCMP; not b43's AES = 3); `0x40` for a pairwise slot, `0x10` for a group slot.
- The stock TX cache info starts `50 04` (notes/137): cipher 5 in the high nibble of byte 0, key slot in byte 1. We send 0 0 and encrypt in software.
- Unknown: the RX header fields that report decryption, TX header fields for non-aggregated frames, what SHM `0x0668` bit 12 does, TKIP and WEP numbers.
  Our code never touches key memory on AC (`b43_security_init` returns early, `b43_op_set_key` returns -EOPNOTSUPP, notes/33).
