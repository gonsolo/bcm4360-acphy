# Status 2026-09-28 (cont'd): the post-association degradation was b43_rx() dropping frames the AC ucode flags DECERR; plus two measurement errors corrected

Picks up from notes/49. Goal: the "connects, then degrades" problem
(notes/34/38/39/40/46).

## Two measurement errors found first

### 1. `txackfrm` counts ACKs we *send*, not ACKs we receive

`b43.h` described `B43_SHM_SH_TXACKFRM` as "Frames transmitted, ACK
received". In Broadcom's macstat layout it is the number of ACK frames the
MAC *transmitted*. Proof from two live dumps while associated:

| time | rxdfrmucastmbss + rxmfrmucastmbss | txackfrm |
|---|---|---|
| 12:11:38 | 114 + 32 = 146 | 146 |
| 12:12:55 | 132 + 36 = 168 | 168 |

Every unicast frame we received got exactly one ACK from us. ACKs received
for our own frames are `rxackucast` (byte 0x11C, now `B43_SHM_SH_RXACKUCAST`).

Consequences:
- The ACK-ratio watchdog (notes/37/42) computed (unicast frames received) /
  (all frames sent). That says nothing about TX health, yet it fired full
  controller restarts, and its restart path is the leading suspect for the
  hard freeze (notes/48). **Now off by default** (`ac_ackwatchdog=0`).
- Every "ACK ratio N/M" figure in notes/37/40/42/46/49 measured that same
  quantity, not TX success.

### 2. "100% ping loss over b43" was mostly the NixOS reverse-path filter

NixOS installs `nixos-fw-rpfilter` (iptables raw PREROUTING, strict
`rpfilter --validmark`), with an explicit exception for DHCP (udp 67->68).
With the USB stick holding the 192.168.0.0/24 route, replies to
`ping -I wlp3s0b1 192.168.0.1` arriving on b43 fail the reverse-path check
and are dropped, whatever the radio does. That is also why DHCP could
succeed while ping "failed". At 12:11:38, during a "100% loss" ping run, the
ucode counters showed 114 unicast data frames, 301 ACKs and ~10 beacons/s
received from the AP.

Use `arping -I wlp3s0b1 192.168.0.1` (ARP is not filtered) or IPv6 ping to
the router's link-local `fe80::10:18ff:fe9e:2a84%wlp3s0b1` instead.

## The real bug: DECERR drops

tcpdump on b43 (before netfilter) during a stuck DHCP showed the router's
DHCP reply arriving within ~35 ms, and later attempts showed none at all.
Tracing frames from the AP into `b43_rx()` and out to `ieee80211_rx_list()`:

```
IN  fc=8802 seq=0000 len=137 ms=0002  -> UP      EAPOL 4-way msg 1
IN  fc=8802 seq=0010 len=193 ms=0012  -> dropped EAPOL 4-way msg 3
IN  fc=8802 seq=0020 len=193 ms=0012  -> dropped msg 3, retransmitted
```

`ms` is RxStatus1 (rxhdr+0x10). Bit 0x10 is what b43 calls
`B43_RX_MAC_DECERR`, and `b43_rx()` dropped every such frame. But
`fc=8802` is **unprotected**, so "decrypt error" is meaningless there. This
port programs no hardware keys on AC, and the DEC-attempted bit (0x08) was
never set. The same bit appeared on the router's DHCP replies and (from the
A/B below) on ARP replies. Depending on which frames got flagged in a given
attempt, the connection stalled in the handshake (NM state 50), at DHCP
(state 70), or came up and then lost unicast RX. That matches every variant
of "degradation" seen tonight. wl's `wlc_recv()` drops on RxStatus1 bit 0
(FCS) and PHY-status errors, but has no visible drop on bit 4.

**Fix** (`xmit.c`): on AC, pass DECERR-flagged frames up to mac80211
instead of dropping them (`ac_decerr_pass`, default on). mac80211 decrypts
in software and still rejects anything genuinely corrupt via the CCMP MIC.

### A/B, fresh load per arm, 5 connect/disconnect cycles each, same load

| | IPv4 up | ARP right after | still up +20s |
|---|---|---|---|
| `ac_decerr_pass=1` | **5/5** (0-3 s) | **10/10** each | **5/5** (ARP 7-10/10) |
| `ac_decerr_pass=0` | 2/5 | 0/10 | **0/5** |

## Also tested, inconclusive

`ac_state_once` (new param, default off): apply the wl snapshot only on the
first switch to channel 6 per core init, instead of on every return to
channel 6 (73 re-applications in one 20-minute load). With DECERR drops
still active, both arms failed similarly (once: 5/5 stuck at DHCP; every:
1 stuck in handshake, 3 at DHCP, 1 up briefly). Kept as an option, not a
fix.

## Soak

Fresh load with defaults (`ac_decerr_pass=1`, `ac_ackwatchdog=0`), one
connection, probed every ~13 s for ~7 minutes (31 probes; the first run
stopped at 113 s on a single missed backup-link ping, so the harness was
changed to require 3 consecutive failures and continued on the same
connection):

- NM state 100 (connected) at every probe; no deauth, no disassoc, no
  controller restart, no kernel WARN in the whole load.
- ARP to the gateway: 141/155 (91%). IPv6 ping to the router's link-local:
  145/155 (94%). Losses are scattered single probes (worst: 2/5), not
  outages.

Before the fix, the same connection went dead within ~20 s every time.
The remaining ~6-9% probe loss is a separate, smaller problem.

## Still open

- What RxStatus1 bit 4 means in this ucode. One lead: the POR SHM snapshot
  was captured from wl while associated and may carry wl's key-table / RCMTA
  state, so the ucode "attempts" decryption for the AP's address with stale
  keys. Unverified.
- One DHCP reply seen earlier reached the IP layer one byte short
  (IP total length 329, 328 present). Not reproduced since the fix; watch
  for it.
- Channel 1 RX (notes/45 section 5) is still broken, independent of this.
- The hard-freeze cause (notes/48) is unconfirmed; the watchdog restart path
  is now off by default.
