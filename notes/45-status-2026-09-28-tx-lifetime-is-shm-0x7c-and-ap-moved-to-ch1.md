# Status 2026-09-28 (cont'd): the early-suppression bug is the TX lifetime at SHM 0x7C, zeroed by a flawed bisect; separately, the AP moved to channel 1 and channel-1 RX is broken

Supersedes the SHM-0x3E parts of notes/43 and notes/44.

## 1. notes/43 read the wrong address

The ucode's `ShmDir` operands are **word** addresses; `b43_shm_read16()`
takes **byte** offsets (notes/12: `txackfrm` is byte 0xE6, ucode word
0x73). Ucode word 0x3E is therefore driver byte **0x7C**. notes/43 read byte
0x3E (word 0x1F, mainline's `NRRXTRANS`), so both its "confirmed zero" and
the NRRXTRANS aliasing were about the wrong location.

## 2. What word 0x3E (byte 0x7C) does

Only one instruction in the whole ucode touches it. Routine 0x01BF-0x01D0,
entered from the main loop whenever `IHR_TXE_CTL` bit 0 is set (a frame is
pending in the TX engine):

```
01C2 JZX  SHM[0x3C].bit5 -> skip         ; byte 0x78 = 0x0060 from POR: bit 5 set, enabled
01C3 r33 = IHR_TSF_TMR_TSF_L
01C4 r35 = (TSF_ML:TSF_L) >> 8           ; now, in 256us units
01C5 JNZX r63.bit6 -> 01C8               ; deadline already armed
01C6 SHM[0x867] = SHM[0x3E] + r35        ; deadline = now + lifetime
01C7 r63.bit6 = 1                        ; armed (cleared on TX completion: 0x403/0xAD0/0xD4E)
01C8 JDPZ r35, SHM[0x867] -> 01CD        ; now - deadline >= 0 -> expired
...
01CE ORX 5 -> txstatus.supp_reason       ; B43_TXST_SUPP_LIFE
```

With the lifetime at 0, the deadline equals "now" on the arming pass, so
any frame that has to wait in the main loop (deferral, backoff, re-queue
for a retry) is completed as `supp=5` right away. That is exactly notes/41's
"fcnt 0-2, then supp=5" symptom, and it gets worse on a busy channel. wl's
first-boot value is **0x0320 = 800 x 256us, about 205 ms**.

## 3. Why it was zero: the bisect that disabled it measured the wrong thing

`phy_ac_por.h` had `{ 1, 0x007c, 0x0320 }` until `37455b6`, which turned it
into a `0xffff` skip ("With 0x0320 here the ucode never accepts the ACKs...
found by bisecting"). The bisect script (`shm_bisect.sh`) injected 10 CCK
probes in monitor mode and used `txallfrm` (total TX attempts) as its
metric, threshold 40: 70 with the entry, 22 without. Even the "good" state
was 2.2 attempts per probe, not ~1, so ACKs weren't recognised in either
state. The lifetime just cut each unACKed frame off after ~2 tries instead
of letting it retry to the limit of 7. That is a metric artifact, not an
ACK fix; the real ACK fix in that commit was the rate-block PLCP exclusion.

## 4. Causal A/B on suppression

Added `ac_txlifetime` (module param, default -1 = leave unset, writes SHM
0x7C at PHY init). Eight alternating trials, same load:

| lifetime | supp=5 per trial (of 158 TX statuses) |
|---|---|
| 0      | 66, 65, 64, 64 |
| 0x0320 | 0, 0, 0, 0 |

No retry-to-limit pathology appeared with 0x0320 (`fcnt=7 acked=0`: 0 in
all trials). **Not yet shown**: the effect on real connections (auth, 4-way
handshake, DHCP, ping). Every trial's connection attempt failed for the
reason in section 5, so the connection-level half of the A/B is still owed
before changing the default or re-enabling the POR entry.

## 5. Separate blocker: the AP is now on channel 1, and channel 1 RX is broken

The Vodafone AP auto-moved again (6 -> 11 earlier, now 11 -> 1; the USB
stick confirms ch1 at 58-72%). NetworkManager's "network could not be
found" / "association took too long" were the scan never seeing it.

Monitor-mode findings (after a channel-6 visit has applied the POR; without
it this port receives nothing on any channel):

- On ch1 every received frame is a 1 Mbps CCK frame from the AP, and every
  one is shifted by exactly one bit: broadcast `ff..ff` arrives as
  `ff ff ff ff ff 7f`, BSSID `8e:6a:8d:9e` as `47:b5:46:4f`. All fail FCS. No
  OFDM frames decode at all, despite heavy traffic on that BSS.
- On ch3 and ch6, the USB stick's (very strong, adjacent) ch1 frames decode
  **correctly**; on ch11, CCK beacons from another AP decode correctly.
- Varies per init: one fresh load briefly showed plausible ch1 counts, most
  showed zero or garbage. Not yet understood.

Ruled out: wl's spur-avoid PLL mode. `wlc_phy_set_spurmode()` maps channel
to mode and calls `si_pmu_spuravoid()`, but its chip-specific PLL routine
has no BCM4360 case and falls through to a no-op, so wl doesn't change the
PLL here either. Our ch1 tuning row is consistent with its neighbours (no
table-parse off-by-one).

## Current state

- `ac_txlifetime` param committed, default -1 (no behaviour change).
- NetworkManager's `b43-test` profile now has
  `802-11-wireless.cloned-mac-address permanent` (avoids a core restart on
  each activation; revert with `nmcli connection modify b43-test
  802-11-wireless.cloned-mac-address ""` if unwanted).
- Chip loaded with the standard params, idle. USB backup link fine throughout.

## Next steps

1. Connection-level A/B of `ac_txlifetime=0` vs `800`. Needs the AP on a
   channel where RX works (6 or 11), e.g. by pinning the router's 2.4 GHz
   channel. If it holds up, re-enable the POR entry (or write 0x0320 by
   default) and update its comment.
2. Channel-1 CCK one-bit slip / no-OFDM: compare PHY/radio state on ch1 vs
   ch3 after the same POR application, and against wl's own ch1 state in
   `traces/wl-firstload-*.trace` (wl associated on ch1 in that trace).
