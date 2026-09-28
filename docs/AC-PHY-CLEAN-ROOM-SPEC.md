# BCM4360 AC-PHY: functional specification for a clean-room b43 implementation

## 0. Provenance, scope, and a legal caveat

**How this document was produced.** The facts in this spec were determined
by reverse-engineering Broadcom's proprietary `wl` driver (`wl.ko`): static
decompilation (Ghidra) of its logic, and live capture of the exact
register/SHM writes it performs on real BCM4360 hardware (a MacBookAir6,1).
A working, GPL-licensed driver (`b43-src/` in this repository) was then
written using that knowledge. That driver is **not** a clean-room
implementation and is not fit to submit upstream as-is: its author had the
proprietary driver's decompiled logic in view while writing it, which is a
real copyright/provenance problem for a from-scratch kernel driver, not
merely a style concern.

**What this document is for.** It describes the hardware's *required
behavior* - register values, sequences, data formats - as technical facts
about how the silicon must be operated, in this author's own words and
organization, without reproducing `wl.ko`'s source structure, comments, or
expression. The intent is that someone who has **never seen `wl.ko` or
`b43-src/`** could read only this document and an 802.11 spec, and
implement a working driver. That second, independent implementation is
the "clean room" half of the classic two-team methodology; this document
is the "spec team" half.

**This is not legal advice.** Whether register-value tables and sequences
extracted this way are copyrightable-free facts (as opposed to protected
expression) is a real legal question this author is not qualified to
settle. Get a lawyer's review, ideally one experienced with SFLC/SFC or
similar FOSS-driver clean-room precedent (e.g. the original Phoenix BIOS
clone, or `nouveau`'s register-level documentation efforts), before
posting any of this to LKML or asserting it's safe to build on.

**Scope of what's covered.** This spec describes only the 2.4 GHz,
20 MHz-wide, single-spatial-stream path: chip bring-up, channel tuning,
basic data TX/RX, and software (not hardware) encryption. It was verified
end-to-end on real hardware: WPA2 association, DHCP, and sustained traffic
with a stable connection. It does **not** cover: 5 GHz operation beyond a
single untested experimental mode, 40/80 MHz channel widths, VHT/AC rates,
MIMO beyond 2 spatial streams, hardware crypto acceleration, or full RF
calibration (LO leakage cancellation, PAPD, temperature-compensated TX
power control). Section 9 lists open items explicitly.

**Target hardware.** Broadcom BCM4360 802.11ac combo chip, radio
synthesizer part 0x2069 revision 4, PHY core revision 42 (referred to
throughout as "AC-PHY" to distinguish it from b43's existing legacy
B/G/N/HT PHY support). The same PHY/radio combination, under the chip IDs
0x4352, 0xa9c4, 0xaa06, and 0x4350, is believed to share this
specification, though only 0x4360 (board type 0x0117) was tested.

---

## 1. Chip identification and core discovery

The AC-PHY core is reached the same way b43 already reaches every other
PHY generation: via the bcma bus, core class "802.11", matching on chip
ID/board type through the existing SPROM-derived `dev->dev->chip_id` /
`board_type` fields. Two cores are present on the tested board
(chip ID 0x4360, board type 0x0117 or 0x0137); core count is otherwise
read from PHY register 0x00B, low 3 bits.

Radio identification: radio version 0x2069, revision 4. A different radio
addressing scheme applies depending on a capability bit - see §2.1.

---

## 2. Chip bring-up (once per core attach)

Performed once when the PHY is first allocated, before any channel is
tunable.

### 2.1 Radio register addressing

Two different MMIO windows exist for radio register access, and the
correct one must be selected based on a PHY capability bit
(bit 0 of a PHY status/capability register the existing b43 driver already
reads for other PHY generations - "radio24" capability). When set: radio
reads/writes go through MMIO offsets belonging to "RADIO24_CONTROL" /
"RADIO24_DATA"; the target register number is written to CONTROL, then
DATA is read or written. When clear: the legacy RADIO_CONTROL/RADIO_DATA_LOW
pair is used identically. On the tested hardware the radio24 path is used.

### 2.2 PHY table upload

23 PHY calibration/lookup tables are written via the b43 core's existing
generic table-write mechanism (already used by earlier PHY generations:
select table+offset via PHY control registers, burst-write data words).
The tables cover RX Farrow/gain-control coefficients, TX gain ramp tables,
AGC thresholds, and similar per-generation constant data. Table IDs and
contents are chip-generation-specific binary data, not narrow enough to
usefully describe as "logic" here - an implementer needs to capture these
from a live `wl` session's table-write trace (same technique used to
produce this project's data) or from firmware disassembly, since they are
not otherwise documented. This spec does not reproduce the table contents
themselves.

### 2.3 First-init register writes

A fixed sequence of PHY and radio register writes follows table upload,
gated on chip generation. This sequence:
- Clears/reconfigures a PHY RF-control command register (offset within the
  PHY register file; existing b43 code names this "RFCTL_CMD") through a
  short dance: read current value, mask to a fixed set of bits, write,
  toggle a "commit" bit, write again.
- Writes a fixed table of ~23 radio register/value pairs (`prefregs`) -
  gain, bias, and calibration-enable bits for the synthesizer and RC
  network. These values are again chip-generation constants; capture from
  a live trace.
- Sets several radio bits gating the RC-calibration state machine
  (registers in the 0x96b/0x96c range) and enables a resistor-calibration
  clock (0x407 bit 1, 0x55e bit 4).
- Per RF core present: sets two bits in a per-core "TX gain" register pair
  (registers offset by `core_index << 9` from a base - this
  `<< 9`-per-core addressing convention recurs throughout radio register
  access on this chip) and clears three bits in a per-core register near
  offset 0x06F, plus one bit in a register near 0x065. These are RF-path
  enable/reset bits; exact function names weren't recovered, only their
  effect (required for calibration to succeed).
- A final short handshake toggles a "commit" bit in the RFCTL_CMD register
  and a PHY register near offset 0x728 to actually apply the just-written
  radio state to the analog RF path, with a >=100us settle delay.

### 2.4 Resistor calibration ("RCAL")

A one-shot calibration of an on-chip reference resistor, required once per
power-up (not per channel switch). Procedure:
1. Set two enable bits in a radio calibration-control register (offset
   0x8EA), then clear two bits in a related register (0x8ED) to select the
   default calibration path (this project did not parse SPROM
   `boardflags3`, which on some boards selects an alternate path - assumed
   0/default throughout).
2. Zero four consecutive "calibration target" registers (0x549-0x54C) and
   set an "start calibration source" bit (0x548).
3. Toggle a start bit (bit 0 of register 0x40B): clear, wait 1us, set.
4. Poll register 0x40B, up to 100 times with a 10us delay between polls,
   for bit 3 ("done") to be set.
5. Tear down: clear the start-source bit, clear the two 0x8EA enable bits,
   clear the start bit.

Failure (timeout) does not abort chip bring-up in the reference
implementation - it's logged and calibration continues on to the RC
calibration step regardless, i.e. RCAL failure alone was never observed to
prevent a working chip in testing, though its downstream effect on RX
sensitivity if it genuinely fails was not characterized.

### 2.5 RC calibration ("RCCAL")

A three-step calibration sequence, run once per power-up immediately after
RCAL, each step calibrating a different RC-network parameter. All three
steps share one mechanism: write four small constant register groups,
strobe a start bit, poll a status register for a done bit, then (per step)
apply the read-back result somewhere else in the radio register file.

Per-step constant table (indexed 0/1/2 by step number):
- Register 0x410, bits handled as two sub-fields: bit 12 <- {1,0,0}, bits
  4:3 <- {0,2,1}.
- Register 0x411, bits 15:8 <- {0x1C,0x70,0x40}.
- Register 0x412 (full 16-bit value) <- {0x14A,0x101,0x11A}.

Step 2 additionally (before the strobe) clears bit 2 of a per-core register
at offset 0x11D and sets bit 13 of a per-core register at offset 0x171,
for every RF core present (again using the `<< 9`-per-core offset
convention).

Per-step procedure after the constant writes:
1. Clear bit 0 of register 0x410, wait 1us, set it, wait 35us.
2. Set bit 0 of register 0x411 (strobe).
3. Poll register 0x413 bit 4, up to 100 times with 100us between polls.
4. Clear register 0x411 bit 0.
5. If the poll succeeded, per step:
   - **Step 0**: read registers 0x414 and 0x415 (two raw calibration
     counter values); the driver only logs a derived byte
     `((r415 - r414) * 0xC1) >> 8`, it is not fed back into another
     register on this hardware.
   - **Step 1**: read register 0x416 (result, low 5 bits significant);
     write those same 5 bits into bits 4:0 of two per-core registers,
     0x126 and 0x043, for every core.
   - **Step 2**: read register 0x416 again (result unused numerically on
     this path); for every core, clear bit 13 of the per-core register at
     0x171 that step 2's setup had set (undoing the setup, not applying a
     new value).
6. Clear register 0x410 bit 0 again before the next step.

A per-step timeout is logged but does not abort bring-up, matching RCAL's
behavior.

### 2.6 VCO calibration kick

A short sequence run once at bring-up and again after every channel
tune (§3): clear bit 14 of radio register 0x8E5, bit 0 of 0x8D0, bit 6 of
0x8E8, and bit 13 of 0x8DC; wait 11us; then set those same four bits back
in the order 0x8D0, 0x8E8 (with an extra 1us wait between), then 0x8DC.
This forces the synthesizer's VCO calibration state machine to re-run
against the just-programmed tuning values.

---

## 3. Channel tuning (2.4 GHz, 20 MHz)

Retuning to a new channel (both at bring-up and on every channel switch
thereafter) is:

1. Write 50 specific radio registers from a **per-channel table** (below)
   - one value per register, per channel. This table is empirical/
   measured data: what values the synthesizer needs for each channel's
   carrier frequency and channel-6-specific N-ratio, not something derivable
   from the 802.11 channel-to-frequency formula alone. It must be captured
   per-channel from a live trace or from calibration first principles for
   this exact radio part; this spec does not reproduce the 2652 individual
   values (50 registers x 14 channels x 5 GHz channels too), only the
   *shape* of the table and the register list, which is itself required
   knowledge to know what to capture:

   Register list (50 entries, applied in this fixed order for every
   channel): `0x8e0, 0x8e1, 0x8dd, 0x8dc, 0x8e6, 0x8e7, 0x8c4, 0x8c5, 0x8e5,
   0x8eb, 0x8d6, 0x113, 0x8db, 0x8da, 0x8d7, 0x885, 0x886, 0x887, 0x8d9,
   0x8d8, 0x8c9, 0x8ca, 0x8cc, 0x8c7, 0x8c8, 0x892, 0x894, 0x895, 0x896,
   0x897, 0x899, 0x89a, 0x89b, 0x89c, 0x112, 0x629, 0x65b, 0x65e, 0x668,
   0x11a, 0x11b, 0x719, 0x630, 0x65c, 0x662, 0x66d, 0x893, 0x145, 0x146,
   0x723`.

2. Special case: on channel 4 specifically, two additional radio writes
   follow the table (register 0x8D6 <- 0x0CE4, and register 0x8EC: clear
   bits 6:4, set bits 6:4 to 0b101). No other channel needs post-table
   fixups in the 2.4 GHz table this project captured.

3. Set bit 12 of radio register 0x645 (unconditionally, every tune).

4. Write radio register 0x723 <- 0x83E0 (unconditionally, every tune).

5. Run the VCO calibration kick (§2.6).

### 3.1 The Farrow (fractional sample-rate) resampler - REQUIRED, easy to
miss

**This is the single most important correctness requirement in this
whole spec.** The baseband ADC/DAC sample clock is derived from the
synthesizer, so it is channel-dependent; a digital fractional resampler
("Farrow" structure) converts it to the fixed rate the rest of the PHY
pipeline expects. This resampler's coefficients are *also* channel-
dependent and must be reprogrammed on every channel switch, separately
from the radio tuning table in §3 step 1. **Failing to do this is not a
subtle degradation - it silently corrupts every received frame on any
channel whose sample-rate error versus the resampler's currently-loaded
channel is large enough** (observed: ~3.5% error was enough to shift CCK
symbol timing by a full bit and make OFDM demodulation fail completely;
smaller errors on nearby channels degraded more gracefully, which is why
this defect can look like "channel 6 works, channel 1 doesn't" rather
than an obvious total failure).

Eight registers, four for RX (per RF core, so 4 registers x however many
cores, though testing only used core-0/core-1 mirrored pairs) and four for
TX, keyed by channel:

- RX: PHY registers `0x19A, 0x19B, 0x19C, 0x199` (core 0), mirrored to
  `0x1A1, 0x1A2, 0x1A3, 0x1A0` (core 1) with identical values.
- TX: PHY registers `0x1603, 0x1602, 0x1607, 0x1606`.
- Then: PHY register `0x1601` <- (current value of PHY register `0x601`,
  read back and copied - not a fixed constant).

Like the radio tuning table, the actual per-channel numeric values are
empirical data requiring capture (this project captured all 2.4 GHz and
5 GHz 20 MHz-mode channels; values climb smoothly and monotonically with
channel number within a band, which is a useful sanity check when
capturing/verifying your own trace - a value badly out of that monotonic
trend for its channel number indicates a capture error).

**Implementation note for whoever builds this clean-room**: because the
resampler correction is smooth and monotonic in channel number, and its
required precision is empirically known from testing (get all 14 known-
good 2.4 GHz values from a live trace, observe they fall on a near-linear
curve versus channel center frequency), it may be possible to interpolate
untested channels or even derive the coefficients analytically from the
known ADC/DAC clock topology, rather than requiring a full-table capture
for every supported channel/bandwidth combination. This project did not
attempt that derivation - it captured all needed values directly.

---

## 4. TX path

### 4.1 TX descriptor header format

Each transmitted frame is preceded by a 128-byte header (4-byte prefix +
124-byte body) written into the DMA TX descriptor ahead of the 802.11
frame payload:

```
offset  size  field
0x00    1     0x02 (fixed "passthrough" prefix byte 0)
0x01    1     0x00
0x02    1     0x02 (fixed "passthrough" prefix byte 2)
0x03    1     0x00
--- 124-byte body starts here (offsets below relative to body start) ---
0x02    2     MAC control flags, LE16 (bit 0x0080: expect immediate ACK,
              set unless destination is multicast or the frame is marked
              no-ack; bit 0x4000: this is the start of an MSDU, set
              unless the 802.11 sequence-control fragment-number field is
              nonzero; bit 0x0200: set for beacons, to have the MAC ignore
              its own power-save queue state for this frame)
0x04    2     0x0002 (fixed - selects "use explicit rate table entry 0"
              TX rate mode)
0x06    2     chanspec, LE16: channel number in the low byte, 0x1000 set
              (20 MHz width marker) for all tested configurations, with
              0xC000 additionally set when transmitting on the 5 GHz band
0x08    1     802.11 header length in bytes (ieee80211 hdrlen of the
              frame's frame-control field)
0x0a    2     total frame length including a 4-byte FCS, LE16
0x0c    2     opaque cookie, LE16, echoed back unchanged in the
              corresponding TX-status completion (§4.3) - used to match
              completions to pending frames, any allocation scheme works
              as long as it round-trips
0x14    20    rate table entry 0 (format below); a second identical-
              shaped 20-byte slot at 0x28 exists for a fallback rate but
              was not populated by this implementation (single-rate only)
```

Rate table entry format (20 bytes, offsets relative to the entry start):
```
0x00  2  PHY control word: bit 0 = 1 for OFDM / 0 for CCK; bit 2 always
         set; bits 9:6 = TX RF core mask (which cores transmit this
         frame - 0xF for "all cores" on 4 cores, use the mask matching
         your `b43_phy_ac_num_cores()`-equivalent count); bit 4 set only
         for CCK rates other than 1 Mbit/s when the driver wants a short
         preamble
0x02  2  0x0000 (unused/reserved in this implementation)
0x04  2  rate-table index: position of the chosen bitrate within a fixed
         8-entry OFDM table {6,9,12,18,24,36,48,54 Mbit/s} or 4-entry CCK
         table {1,2,5.5,11 Mbit/s}, whichever applies to the chosen rate;
         0 if the rate isn't found in the applicable table
0x06  8  PLCP header for the chosen rate/length, in the same format b43
         already generates for legacy CCK/OFDM PHYs (existing
         `b43_generate_plcp_hdr()` logic - not AC-specific)
0x0e  2  the chosen rate itself, in 500 kbit/s units (i.e. raw 802.11
         rate byte value), LE16
0x10  2  0x0020 (marks this as the last populated rate-table entry)
```

Everything in the 124-byte body not listed above is zeroed and unused by
this implementation - in particular, no VHT/AC-rate fields, no aggregation
control, and no hardware-crypto key-index fields are populated (hardware
crypto was out of scope; software crypto via mac80211 was used
throughout, meaning the 802.11 frame handed to the TX path is already
fully encrypted by the time this header is built).

### 4.2 Rate limits

Short and long retry limits are configured via the existing generic
SHM-based mechanism common to all b43 PHY generations (SHM shared-routing
words at the addresses b43 already names `SRLIMIT`/`LRLIMIT`) - no
AC-specific override needed; defaults (7 short / 4 long) were verified
correct by direct SHM readback during testing.

### 4.3 TX status completion / lifetime

Each completed (or given-up) TX produces a completion record read back
through the existing generic b43 TX-status IRQ mechanism, decoding a
32-bit-per-frame legacy-format status word that already exists in b43 for
other PHY generations: cookie (matches §4.1's field), a frame/attempt
count, a 4-bit "suppress reason" code, and an ACKed flag. One
suppress-reason value is critical to get right:

**Frame lifetime (suppress reason = "LIFE").** The firmware maintains,
per queued frame, a deadline computed as (current TSF time) + (a
configurable duration). If a frame is still waiting to be sent when that
deadline passes - because of contention, backoff, or queueing - the
firmware gives up on it immediately and reports it as suppressed with
this reason, *regardless of how many retry attempts remain available*.
**The duration must be configured to a non-trivial value.** Left at zero
(which is where it defaults to if never explicitly set), the deadline
equals "now" the instant a frame is queued, so almost any frame that
doesn't transmit on its very first opportunity is discarded before it
ever gets a real retry - this presents as authentication/association/DHCP
frequently timing out, and as an established connection's throughput
silently collapsing under any real contention, while looking to a
casual read of retry-count statistics like the frames are "succeeding
quickly" (low attempt counts) rather than being starved. **The verified
correct value is 0x0320, in units of 256 microseconds (~205ms total),**
written to shared-routing SHM word offset 0x7C (equivalently, ucode-side
word address 0x3E, if your ucode-interface code addresses SHM by 16-bit
word rather than byte offset - confirm which convention your host-side
SHM accessor uses before setting this, getting the addressing wrong here
reproduces exactly the same symptom as never setting it at all).

---

## 5. RX path

### 5.1 RX descriptor header format

Each received frame arrives with a hardware-prepended header before the
802.11 frame bytes. This project's host-side RX header struct already
has fields for several PHY generations at fixed offsets (RX status
words, MAC status, TSF, channel); for AC-PHY specifically, the following
raw byte offsets into that same header are used instead of the
legacy-PHY-named fields:

```
offset  size  field
0x09    1     per-antenna power/RSSI, core 0 (signed, dBm-ish units;
              -128 is a sentinel meaning "not valid for this antenna")
0x0a    1     per-antenna power/RSSI, core 1 (same sentinel convention)
0x10    2     RX status word, LE16 (see below - NOT the legacy 32-bit MAC
              status field; AC-PHY packs its equivalent into 16 bits at
              this offset)
0x14    2     TSF time, low 16 bits, LE16
0x16    2     chanspec, LE16 - low byte is the channel number when
              operating in the mode this spec covers; bits 15:14 both set
              (0xC000) indicates 5 GHz
```

Combining the two per-antenna power bytes into a single RSSI value: if
core-0's value is the -128 sentinel, use core 1's; else if core-1's is
the sentinel, use core 0's; else use whichever of the two is larger.

### 5.2 RX status word (offset 0x10, 16-bit)

Bit layout (only bits actually observed/used are listed; treat others as
reserved/unknown):
```
bit 0   FCS error
bit 2   padding present: 2 extra bytes were inserted before the 802.11
        header for alignment - skip them (after skipping a fixed 6-byte
        PLCP header that always precedes the frame) before the 802.11
        header begins
bit 3   "decryption attempted" - hardware tried to decrypt this frame
        against a configured key
bit 4   "decrypt error" - see below, READ CAREFULLY before using this bit
```

**Bit 4 ("decrypt error") pitfall.** This bit is set by firmware on some
received frames well beyond genuine decryption failures - it was observed
set on entirely unprotected (not encrypted at all) frames, including
critical ones: WPA 4-way-handshake message 3, DHCP server replies, and
ARP replies. **Do not drop frames on this bit alone if you are not
programming hardware crypto keys** (this spec's scope doesn't cover
hardware crypto at all - see §0). Discarding on this bit unconditionally
reproduces, depending on which specific frames happen to get hit by it in
a given connection attempt, any of: the WPA handshake stalling, DHCP
never completing, or an association that completes but then can't
exchange any further unicast data. Passing every frame up to the 802.11
stack regardless of this bit, and letting software decryption (which
re-validates the actual cryptographic MIC/ICV independently) be the real
correctness check, was sufficient and correct throughout testing. If you
do implement hardware crypto key offload later, you'll need to determine
this bit's true, narrower meaning in that configuration - it was not
characterized here, precisely because avoiding hardware crypto sidesteps
needing to understand it.

### 5.3 RX statistics (for diagnostics, not required for basic operation)

A block of 16-bit ucode-maintained counters exists at shared-routing SHM
byte offset 0xE0 for total TX attempts, and further counters follow
before the 0x120s range covering various sent/received frame-type tallies
by category (management/data/control x unicast/multicast/broadcast x
serving-BSS/other-BSS, plus PHY/FCS error tallies and a raw
carrier-detect-glitch counter). Two easily confused - **the offset
commonly assumed to mean "ACKs received for our own transmitted frames"
(0xE6) actually counts ACK frames *this device transmitted* in response
to received unicast frames** (i.e. it's an RX-side "how many unicast
frames did we ACK" counter, numerically equal to inbound unicast frame
count, not a TX-success metric at all). The genuine "ACKs we received for
frames we sent" counter is at a different offset, 0x11C. Any health/
reliability heuristic built on these counters should be built on the
*correct* one - a monitor built on the wrong one will appear to track
"TX success rate" plausibly (it's a real, sensibly-bounded ratio) while
actually measuring something unrelated, and can trigger false-positive
"link is unhealthy" recovery actions when the link is fine, or vice
versa.

---

## 6. DMA ring considerations

Nothing AC-PHY-specific was required in the DMA ring machinery itself -
descriptor format, ring sizing, and the RX buffer-refill path used by
this project's implementation are shared with existing b43 PHY
generations' 64-bit DMA support, unmodified.

One general-purpose robustness gap, not AC-PHY-specific but worth
carrying into any implementation: a synchronous RX-buffer allocation
failure (atomic/non-blocking allocation, called from interrupt context)
that occurs while recycling a descriptor has no automatic retry in a
naive reactive-refill-only design - that one descriptor slot is
permanently stuck reusing its old (already-processed) buffer, silently
degrading RX capacity by one slot per such failure, indefinitely, unless
something separately re-attempts the allocation later from a context that
can block. A periodic (this project used ~15 second interval, arbitrary)
sweep that retries any flagged-failed slots with a blocking allocation is
a straightforward mitigation, not required for correctness under normal
memory pressure but cheap enough to include.

---

## 7. Filter/security-related SHM state

On every core (re-)initialization, the standard b43 key-table
clear/reinit path (shared across PHY generations) must be **skipped
entirely for AC-PHY** if you are not implementing hardware crypto -
AC-PHY firmware's key table lives at a different SHM location than the
legacy PHYs' `KTP` pointer references, and running the generic clear path
against a firmware revision that doesn't have a key table at that
location corrupts unrelated SHM state (observed effect: RX stopped
working entirely after any interface restart, and network scans found no
APs). Guard the existing generic key-table-clear call on PHY type, or
require `nohwcrypt`-equivalent behavior unconditionally for AC-PHY until
hardware crypto is separately implemented and its correct SHM key-table
address for this firmware is determined.

Separately, mac80211's own "changed flags" filter-reconfiguration
optimization (skip reprogramming hardware filter flags if mac80211's
cached idea of them didn't change) does not account for hardware state
having been reset out from under it by a core restart - explicitly force
a full filter-flags reprogram after any core restart rather than trusting
the cached-unchanged fast path, or RX silently stays disabled after a
restart even though every other symptom suggests it should be working
again.

---

## 8. First-boot / snapshot-replay pitfalls (methodology note)

If your own reverse-engineering approach involves capturing `wl`'s
register/SHM writes during its own first boot and replaying that captured
state at driver-init time (a reasonable, tractable strategy for chip
bring-up given how much of §2's sequence is otherwise opaque binary
data) - be aware this approach has a specific, recurring failure mode
worth designing your capture/replay tooling around: **some state `wl`'s
capture appears to set at "boot" is actually runtime-computed by `wl` at
a later point (e.g. once actually associated to a BSS, or computed
per-channel at tune time), not a true boot-time constant.** Naively
replaying the captured value for such a field either leaves it at
whatever incidental value the capture's specific channel/association
state happened to have, or (worse) overwrites a value your own driver
correctly computed afterward, silently reintroducing the bug. Every
individual pitfall in §§3-7 above that's phrased as "X must be set to Y,
don't leave it at the replayed/default value" was found this way -
treat every single captured value as a hypothesis to verify against
independently-reasoned expected behavior, not a fact to trust blindly,
especially for anything that looks like a counter, a deadline, a per-
association key/filter state, or a per-channel tuning parameter captured
while the reference capture happened to be on one specific channel.

---

## 9. Open items (not covered by this spec)

- **5 GHz beyond one untested mode.** An alternate bring-up path exists
  for 5 GHz that keeps `wl`'s own captured 80 MHz-wide PHY/synthesizer
  state instead of retuning per-channel; it was implemented experimentally
  but never verified live (it toggles a core-level PHY-bandwidth ioctl
  bit pattern believed, from project history, to be crash-prone on this
  hardware - approach with real caution and only with hardware recovery
  readily available). The ordinary per-channel 20 MHz retune path (§3)
  was verified to also apply correctly to 5 GHz channels' register writes
  when read back, but a live 5 GHz *association* was never completed in
  testing - only register-level verification.
- **Full RF calibration.** LO leakage cancellation, PAPD (power amplifier
  predistortion), and temperature/voltage-compensated TX power control
  were not implemented. TX power output correctness/legality across
  temperature and supply voltage is therefore unverified.
- **Hardware crypto.** Entirely out of scope; §5.2 and §7 flag the two
  places this most directly affects (the RX decrypt-error bit's true
  meaning, and the key-table SHM location for AC-PHY firmware).
- **Rate control refinement / VHT rates.** Only fixed-selection legacy
  CCK/OFDM rates (802.11a/b/g rate set) were exercised; no VHT/AC rate
  table support, no aggregation (A-MPDU/A-MSDU) TX or RX handling.
- **The exact hardware-timing cause of a small (~5-10%) residual packet
  loss** observed in extended link testing was identified as ordinary
  mac80211 background-scan off-channel dwell time (a normal, expected
  cost of any associated 802.11 station doing periodic background scans,
  not a driver defect) - included here only so an implementer doesn't
  waste time chasing it as a bug.
