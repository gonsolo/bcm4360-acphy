# Draft reply to Alessio (not sent; for Andreas to edit and send)

Hi Alessio,

Quick update, three things that mattered since my last mail:

1. **Second TX chain**: chipcommon `chipcontrol` bit 3 (0x00000008) has to be set,
   otherwise chain 2 never radiates. With it, two-stream HT TX works.

2. **Wide PHY tables**: tables 0x11, 0x14 and 0x20 have 48-bit entries (three
   words through PHY reg 0x011, low word first). Table 0x20 is the TX gain table
   (hardware power control works with it), table 0x14 entries 0x30..0x33 are the
   rfseq extension that 5 GHz RX needs.

3. **50 Mbit/s cap**: it was DMA, not RF. TX control |= 0x03780040 and RX control
   |= 0x036c0000 (burst/prefetch) removed it. With A-MPDU (ucode aggregates,
   driver requeues unacked MPDUs) 2.4 GHz now gives 50-70 Mbit/s both ways,
   15-minute soaks without errors.

5 GHz works too: channel 112 connects, 80 MHz mode with VHT80 reaches
~70 up / ~55 down on a gigabit-limited test path. The Farrow values for 80 MHz
match your formula (ratio = f*2^18/45), verified against wl's 5530 MHz words.
Open: coming back to our block after tuning to another one loses RX; I will test
other blocks once I can switch the router channel.

Repo: <link>

Thanks,
Andreas
