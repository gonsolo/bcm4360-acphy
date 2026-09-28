# Status 2026-09-28 (cont'd): channel 1 fixed - the per-channel Farrow resampler was never programmed

Follow-up to notes/45 section 5 (channel 1: every CCK frame one bit off,
no OFDM at all) and notes/50.

## Finding it

Our channel-1 radio tuning values already matched wl's channel-1 writes
exactly. The 19 channel-dependent radio registers are absent from the POR
tables because wl's first-load trace scans through all channels, so its
"final" values aren't channel 1's.

The trace has one block per channel switch (ch1 at line 18030, ch2 at
23983, ...; wl returns to ch1 at 133857 and associates there). Diffing
last-written values per block, and keeping only registers whose value is
identical in both channel-1 visits and appears in none of channels 2-11,
left the known tuning/bandwidth registers plus two PHY groups we never
write on a channel switch:

| ch | 1 | 2 | 3 | 4 | 5 | 6 | ... | 11 |
|---|---|---|---|---|---|---|---|---|
| 0x19b:0x19a | 69:cccd | 6a:8ccd | 6b:4ccd | 6c:0ccd | 6c:cccd | 6d:8ccd | ... | 71:4ccd |
| 0x1603 | 91c3 | 61cc | 3208 | 0276 | d316 | a3e9 | ... | bae3 |

(The first-switch-after-init block also showed radio 0x2c/0x22c/0x645
differences; wl's second visit to channel 1 writes the same values as
other channels, so those were init artifacts.)

`find_imm.java` (scan all disassembled instructions for scalar operands)
located the writers in an unnamed static function; `find_prologue.java`
found its entry at 0x1a581c (`55 48 89 e5` after a `ret`). Decompiled, it
is wl's **Farrow resampler** setup: look the channel up in `rx_farrow_tbl`
and `tx_farrow_dac1_tbl` (3 bandwidths x 123 entries x 12 bytes, byte 0 =
channel, then four u16) and write

- RX: PHY 0x19a/0x19b/0x19c/0x199 (core 0), 0x1a1/0x1a2/0x1a3/0x1a0 (core 1)
- TX (BCM4360): PHY 0x1603/0x1602/0x1607/0x1606
- then PHY 0x1601 = PHY 0x601

The ADC/DAC clock comes from the synthesizer, so the fractional resampler
to the baseband rate depends on the channel. This port never programmed
it: every channel ran with channel 6's values from the wl snapshot. On
channel 1 that is 105.80 vs 109.55 (19b:19a as 8.16 fixed point), a 3.5%
sample-rate error - enough to slip CCK by a bit and kill OFDM. Nearer
channels had smaller errors, which is why they mostly worked.

`dump_farrow.java` dumped the tables; `rx_farrow_tbl` + `tx_farrow_dac1_tbl`
match wl's trace exactly for channels 1-11 (dac2 does not).

## Fix

`phy_ac_farrow.h` (20 MHz section, 124 channels) and
`b43_phy_ac_set_farrow()`, called on every 2.4 GHz channel switch after
the wl snapshot (`ac_farrow`, default on). 5 GHz still runs on wl's 80 MHz
state, so it is not applied there yet.

## Results

Registers read back per channel exactly as wl writes them. Channel 6
unchanged (3/3 connect cycles).

User moved the router to channel 1. Monitor mode on channel 1, 6 s windows,
alternating:

| ac_farrow | frames | AP frames decoded correctly |
|---|---|---|
| 1 | 336 / 311 / 264 | 234 / 216 / 209 |
| 0 | 39 / 50 / 32 | 0 / 0 / 0 |

Managed, 5 connect cycles on channel 1: 5/5 WPA2 + IPv4 in 1-10 s, ARP
10/10 immediately and 10/10 after 20 s in every cycle.

Soak on channel 1, fresh load with defaults, one connection, 5 minutes:
**ARP 115/115, IPv6 link-local ping 115/115**, NM state 100 throughout,
no restarts or kernel warnings.

That is better than channel 6's soak (notes/50: 91% / 94%). Lead for the
difference: on channel 6 every return from an off-channel scan step
re-applies the entire wl snapshot mid-connection (73 times in 20 minutes,
notes/50); on channel 1 nothing is re-applied. Test `ac_state_once=1` in
a channel-6 soak next time the AP is there.

## Open

- Farrow for 5 GHz (and 40/80 MHz sections) once 5 GHz leaves wl's 80 MHz
  snapshot state.
- wl's function also clears 0x410 and per-core 0x73a/0x725 override bits
  when not in its 5 GHz 80 MHz special cases; not ported (current values
  unaffected).
