# Commit messages of the four-series split (notes/166), in order. (subject, body). No Signed-off-by: the sender adds their own.
# Series A: 1-3 (generic), B: 4-6 (core revisions 40 and 42), C: 7-10 (microcode formats), D: 11-14 (PHY).
M = [
# ---- A: generic fixes ----
("wifi: b43: reprogram the MAC filter after an interface restart",
"""b43_op_start() clears wl->filter_flags, but mac80211 computes @changed
for b43_op_configure_filter() against the flags it cached from the
previous run. After a down/up it can therefore report no change, so
b43_adjust_opmode() is not called and MACCTL keeps the cleared filter.

Seen on a BCM4360: after an interface restart nothing was received until
some other change touched the filter. Compare the requested flags with
what the hardware was actually programmed with and add the difference to
@changed.

Not checked on other chips."""),

("wifi: b43: handle 64-bit DMA engines whose index registers hold bus addresses",
"""Newer 64-bit DMA engines (found on the core revisions of the BCM4352 and
BCM4360) accept ring addresses with low bits set and then use bus
addresses, not offsets into the ring, in the index and status registers.
They are detected with the probe the vendor driver and brcmsmac use:
write 0xff0 to TXRINGLO and see whether it sticks.

On such an engine keep the ring address in the new ring->ptr_base, add it
when writing TXINDEX and RXINDEX and subtract it when reading RXSTATUS.
The ring address registers have to be written before the control word
enables the engine, and the hardware defaults of burst length,
outstanding reads and prefetch control (the *CTL_KEEP masks) have to be
preserved.

Engines that keep offsets behave as before."""),

("wifi: b43: retry RX buffer refills that failed under memory pressure",
"""dma_rx() refills a slot with GFP_ATOMIC. When that fails it reposts the
old buffer, and nothing tries again: an idle slot and a slot stuck after
a failed refill both hold a poisoned buffer, so they cannot be told apart
by the poison alone.

Add a flag to the slot meta data that is set when a refill failed, and a
function that walks the RX ring and retries those slots. It runs from the
15 second periodic work, under wl->mutex like b43_dma_rx() itself, and
does nothing unless a refill has failed."""),

# ---- B: core revisions 40 and 42 ----
("wifi: b43: set the DMA burst and prefetch bits of core revisions 40 and 42",
"""The DMA engines of the core revisions 40 and 42 (BCM4352, BCM4360) need
the burst length and prefetch bits of the TX and RX control words that the
vendor driver sets (0x03780040 and 0x036c0000). Without them the engine
moves about 6 MB/s and every link tops out near 50 Mbit/s.

Add b43_is_ac_core() for these core revisions."""),

("wifi: b43: MAC core setup for core revisions 40 and 42",
"""The core revisions 40 and 42 of the BCM4352 and BCM4360 need these
differences from the older cores:

 - PHY reset: the reset is asserted with the clock forced and released
   with the clock free, in the order the vendor driver uses.
 - GPIOs: the pins are host driven with GPIO1 and GPIO2 high. This is the
   pattern of the MacBookAir6,1 (front end control); other boards may
   need other values.
 - The template and TX FIFOs are carved out of the MAC memory and the TX
   queue table is set up, because the microcode does not size them.
 - MACCTL is written without SHM_ENABLED, which the vendor driver never
   sets on this core.
 - The RX interrupt lazy timeout (register 0x100) is set so that an
   interrupt is raised after every frame.

The microcode (revision 784 and above, b43_ucode_is_ac()) has no key
table pointer at the legacy KTP word, it reads 0, so b43_security_init()
must not clear the "key table": that zeroed SHM 0x000-0x3a0 (rate maps,
ACK/CTS PHY control, microcode state) on every core init.
b43_op_set_key() returns -EOPNOTSUPP, mac80211 does the crypto in
software."""),

("wifi: b43: address match table, templates and beacons for the AC microcode",
"""The microcode of revisions 784 and above lays out several things
differently:

 - the address match table is in the RCMTA object memory, 8 bytes per
   entry (MAC[0..3], then MAC[4..5] and the attributes); the vendor driver
   uses entry 63 for its own address and 62 for the BSSID,
 - the templates in template RAM: 0x30 holds BSSID, MAC, BSSID, 0x48 the
   MAC, plus the default null frame at 0x2c and a header at 0,
 - the ACK/CTS PHY control word and the antenna selection use the AC
   PhyTxControlWord_0 format,
 - the two beacon template slots are at 0x200 and 0x480, and the beacon's
   PHY TX control words are at SHM 0xcc, 0xce and 0xd0 instead of the
   legacy BEACPHYCTL word."""),

# ---- C: microcode formats ----
("wifi: b43: 11ac chanspec for the AC microcode",
"""The AC microcode keeps an 11ac chanspec of the current channel in SHM
(where older microcode keeps the channel cookie) and takes one in every
TX descriptor and puts one in every RX header: the channel, 0x1000 for
20 MHz and 0xc000 on 5 GHz.

Add b43_ac_chanspec() and use it for the channel cookie in
b43_switch_channel(). The TX and RX header patches that follow use it too."""),

("wifi: b43: TX descriptor and TX status for the AC microcode",
"""The AC microcode takes a 4 byte passthrough prefix and a 124 byte
descriptor with four 20 byte rate entries. Add the descriptor builder:
legacy CCK and OFDM rates, HT rates with the PLCP laid out as brcmsmac
does, VHT rate blocks (frame type 3, with the width and the subband of the
primary channel in the first two words and the VHT-SIG-A fields), and the
cache info that session frames carry (the microcode builds the A-MPDU
from them). The cache info must not carry a cipher: mac80211 has encrypted
the frame already.

The TX status comes as two 4 word records. The attempt count is the low
byte of word 2, not the sum of its bytes, and a record with more than one
MPDU carries a block ack bitmap for the consecutive cookies; the cookies
are advanced with the new b43_dma_cookie_advance().

Only microcode revision 832 has been tested."""),

("wifi: b43: RX header handling for the AC microcode",
"""The RX header of the AC microcode keeps the MAC status at 0x10, the TSF at
0x14, an 11ac chanspec at 0x16 and the power of the two antennas at 0x09
and 0x0a. Decode the channel (including the 80 MHz block with the position
of the primary channel), the signal, and the HT-SIG and VHT-SIG-A bytes
that precede the frame for the rate, bandwidth, guard interval, coding
and stream count.

The microcode sets the decryption error bit on frames it never decrypted,
because no hardware key is programmed (the 4-way handshake message 3 and
DHCP replies carry it). Pass such frames up; mac80211's own decryption
still rejects anything corrupt.

Only microcode revision 832 has been tested."""),

("wifi: b43: A-MPDU for the AC microcode",
"""The microcode builds the aggregates and sends the block acks. Accept block
ack sessions on both sides (ampdu_action) and set
IEEE80211_HW_AMPDU_AGGREGATION on the AC cores.

Frames of a session that the microcode gave up on are put back on the
ring, up to four times, with the retry bit set; the block ack window lets
them follow later frames. The cache info limits an aggregate to four MPDUs,
longer ones lose their later MPDUs."""),

# ---- D: the PHY ----
("wifi: b43: radio 2069 and AC-PHY tables",
"""Add the data the AC PHY needs:

 - radio_2069.c: the channel tuning table of radio 2069 rev 4 (2.4 GHz
   and 5 GHz rows) and the register list it programs,
 - tables_phy_ac.c: the PHY tables of the PHY init (rev 0 set, RF
   sequencer, gain limits, gain ladder, the FEM control pattern of
   femctrl == 2 boards, the 2.4 GHz and 5 GHz TX gain tables), and the
   values of the remaining table cells this board holds after the vendor
   driver's init.

The tables are values as seen in operation on a BCM4360 board (MacBookAir6,1)
with the vendor driver; the names of several tables follow Alessio Ferri's
b43-ac-wip. They have been checked on this board only. The
data is used by the patches that follow."""),

("wifi: b43: AC-PHY init and 2.4 GHz channel switching",
"""Replace the placeholder AC-PHY code with an initialization that brings
the BCM4360 (PHY AC rev 1, radio 2069 rev 4) up on 2.4 GHz at 20 MHz:

 - radio 2069 power-up (init, resistor and RC calibration) and power-down
   from software_rfkill,
 - PHY init: the table set, the first-init registers, the reset-time
   register blocks, hardware TX power control with the wide tables, and
   the second TX chain, which stays dark unless chipcontrol bit 3 is set,
 - channel switching: tune the synthesizer from the radio table, the
   per-channel Farrow resampler words and BW registers, reset CCA,
   with PHY 0x0003 bit 8 (the band) cleared on 2.4 GHz,
 - a fixed 2.4 GHz TX gain table index as the starting point of the power
   loop,
 - the 15 second work restarts the core when the microcode counts PHY TX
   errors in several fresh inits (only about a third of fresh inits can
   transmit, the rest fail every frame), at most three times,
 - HT capabilities for the 2.4 GHz band.

5 GHz channels are refused for now."""),

("wifi: b43: 5 GHz, 80 MHz and VHT for the AC PHY",
"""Add 5 GHz channel switching: the RF sequencer extension, the second
sequencer's command lists and three table 7 cells (which keep the second
TX chain working), the 5 GHz TX gain table and AGC tables, VCO calibration
and the RX gain control word. Switching back to 2.4 GHz rewrites the 2.4 GHz
tables and the 20 MHz PHY bandwidth.

On 5 GHz the PHY runs in its 80 MHz mode on the 80 MHz block that contains
the primary channel, tuned to the centre of the block, with the
Farrow resampler words computed for it. The chanspec of such a channel
names the centre channel, the width and the position of the primary. A
20 MHz or 40 MHz AP works as well, the primary channel's frames are
received in the block.

Register the 5 GHz band with HT and VHT capabilities (two streams, MCS 0-9,
80 MHz); mac80211 wants 40 MHz capability before it uses 80 MHz."""),

("wifi: b43: enable the AC-PHY support",
"""The AC-PHY now brings up a BCM4352/BCM4360 on 2.4 GHz and 5 GHz and
transmits and receives with HT and VHT at 20, 40 and 80 MHz. Remove the
dependency on BROKEN and say what is missing: no TX calibration, no TX
power control beyond the hardware loop, no hardware crypto and no power
save.""")
]

NOTE_TESTED = """Each patch compiles on its own (kernel 7.2.10 headers). The four series
together were run on a MacBookAir6,1 (14e4:43a0, BCM4360, core revision 42,
microcode 832.127, 2 of 3 chains wired) on top of v7.3-rc5's b43. The AC PHY
only comes with series 4, so the earlier series cannot be exercised on this
hardware alone."""

COVERS = {
"A": ("wifi: b43: DMA and filter fixes for the BCM4360 (series 1/4)",
"""Three fixes found while bringing up the BCM4360. None depends on the
AC PHY; they only change behaviour where stated:

 1. MAC filter after an interface restart,
 2. 64-bit DMA engines whose index and status registers hold bus
    addresses (detected by probe, offset engines are untouched),
 3. retry of RX buffer refills that failed under memory pressure.

This is the first of four series; the rest (core revision 40/42 MAC
setup, AC microcode formats, the AC PHY and removal of BROKEN) follow
once this is merged, as agreed with Alessio Ferri who has a series for the
same hardware.

""" + NOTE_TESTED + """ Not tested on other chips.
"""),
"B": ("wifi: b43: core revision 40 and 42 MAC setup (series 2/4)",
"""MAC core support for the BCM4352/BCM4360 core revisions 40 and 42. Things
that depend on the core revision are gated on it (b43_is_ac_core()),
things that depend on the microcode layout are gated on the microcode
revision (b43_ucode_is_ac(), revision 784 and above, set once the
microcode is loaded). The TX and RX formats and the PHY are not in this
series. Based on series 1/4.

""" + NOTE_TESTED + """
"""),
"C": ("wifi: b43: AC microcode TX and RX formats (series 3/4)",
"""The TX descriptor, TX status, RX header and A-MPDU handling of the AC
microcode, gated on the microcode revision. Only revision 832 has been
tested; the layouts of 784 and 928 are expected to match but are not
verified. Based on series 2/4.

""" + NOTE_TESTED + """
"""),
"D": ("wifi: b43: AC-PHY support (series 4/4)",
"""Radio 2069 and the AC PHY: tables, 2.4 GHz and 5 GHz channel switching
(5 GHz in 80 MHz mode), HT and VHT capabilities, and the removal of
"depends on BROKEN". Based on series 3/4.

With the four series b43 brings up a BCM4360 on 2.4 GHz and 5 GHz, with HT
and VHT at 20, 40 and 80 MHz, two streams and A-MPDU.

""" + NOTE_TESTED + """ Association and traffic with WPA2 (software
crypto) on 2.4 GHz (HT, about 54-63 Mbit/s) and on 5 GHz (VHT, 80 MHz block,
two streams, 40-70 Mbit/s at -78 dBm), no errors in the log. Not tested:
suspend/resume with this exact series, other boards. Not done: TX
calibration, hardware crypto, power save.

[Provenance of the register sequences and tables: to be written, agreed
with Alessio Ferri, before this is sent.]
""")
}
