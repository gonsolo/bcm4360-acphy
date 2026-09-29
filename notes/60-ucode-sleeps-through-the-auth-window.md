# The ucode is asleep (NAP), not stuck, during failed auth attempts

Direct follow-up to notes/58, same day (2026-09-29). Read the PSM's actual
program counter live via `/sys/kernel/debug/b43ac/mmio16` (MMIO 0x154,
`{status byte, PC}` packed - low 13 bits match address ranges in the real
ucode42.fw disassembly, produced locally with d11emu, see notes/12).
Sampled every ~10ms through single connect attempts.

## Finding

Address 0x000F is `NAP` (CPU sleep) - the very last instruction of the
ucode's main scheduler loop (0x0000-0x0014): check a handful of pending-
work flags, and if none are set, sleep until the next hardware interrupt.
Completely normal firmware idle behavior in general.

During a failed connect attempt (auth sent at t=0, three retries, timeout
at t~0.2s per mac80211's own budget, but wpa_supplicant/NM waited and
retried around t=11.9s):

```
t=0.06  PC=000F (NAP)          <- enters sleep right after auth goes out
t=3.35  briefly 11c0, then 000F again
t=4.58  briefly 10e2, then 000F again
t=5.66  briefly 0045, then 000F again
t=7.60  briefly 11c2, then 000F again
t=8.11  briefly 00de, then 000F again
t=10.37 briefly 0105, then 000F again
t=11.88 finally a sustained multi-second burst of real activity
```

The PSM spends essentially the entire window asleep, waking only for one
~10ms tick every 1-2.5 seconds before going straight back to NAP. Each
wake is far too short and far too rare to carry an 802.11 auth exchange,
whose own retry timers are sub-second. This is the same window
notes/58's phydebug=CRS|TXF sample came from: a TX frame is sitting
posted (TXF) but the CPU that would service it is asleep, not spinning.

By contrast, sampling PC continuously while genuinely idle (no connection
attempt in progress) shows normal, varied activity, not a stuck NAP -
notes/58's `pwork_15sec` register dumps keep appearing on schedule, so
the periodic host-driven work isn't what's blocked; specifically the
post-TX-post wake is.

Right before NAP, the loop does `IHR[0x40] |= 0xFFFF` (0x000E) - looks
like arming the wake-source mask to "everything", which argues against
the ucode itself refusing to listen for wake events. The likely gap is
on the delivery side: something this AC port's bring-up doesn't do that
wl's real init does, so an interrupt that should immediately follow a
TX-descriptor post (`B43_DMA64_TXINDEX` write, dma.c:215 - shared,
generic b43 code, used by every other PHY type for years) doesn't reach
the PSM, or reaches it but doesn't satisfy the predicate it's waiting on.

## Open question / next step

Diff wl's real IRQ-mask and DMA/PSM wake-source setup during association
(same method as notes/19-22's TX-cal trace diffing) against this port's
own `b43_op_config`/`switch_channel`/DMA-ring init, looking specifically
for an interrupt-enable or wake-source bit that's set in one but not the
other. Candidates worth checking first: `B43_MMIO_GEN_IRQ_MASK`,
`B43_MMIO_DMA0_IRQ_MASK`, and the AC-specific PSM control bits touched
around `phy_ac.c`'s init (IHR 0x40 is written 0xFFFF once at the top of
the ucode's own loop - check whether the host is expected to also poke a
matching enable somewhere, the way wl's `wlc_bmac_init_ucode_dispatch`-
equivalent might).

Ruled out by this finding: stick interference, suspend-timeout duration,
verbose logging overhead (notes/57), temperature/cumulative-uptime drift
(notes/59 conversation - a 24h cold boot failed just as fast as a warm
one). The mechanism is now real and specific: NAP re-entry after too-
short wakes, not a busy-wait, not thermal, not RX deafness.
