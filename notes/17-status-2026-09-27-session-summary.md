# Session summary, 2026-09-27: where this project actually stands

This ties together a very long day's work (notes/07-16) into one place.
Read this first if picking the project back up; dive into the
individual dated notes only for the detailed evidence behind a specific
claim below.

## What works right now

- Attach, firmware load, DMA, radio (Broadcom 2069 rev 4) power-up and
  channel tuning, PHY table init.
- RX in monitor mode: 2.4 GHz (`ac_replay=1 dma32=1 ac_por=63`) and
  5 GHz including 80 MHz bandwidth (`ac_5ghz=1 ac_5g_80=1`).
- Host-queued TX: works cleanly. 802.11 authentication and association
  succeed (AID assigned).

## The one hard blocker

**Firmware-autonomous TX (ACKs, beacons) fails ~90-95% of the time.**
This is fatal for any real use: ACKs are mandatory in 802.11, so
without them the WPA2 handshake fails (longer EAPOL frames never get
acknowledged) and the link is fundamentally unreliable even before
encryption is involved. Host-queued TX is unaffected - only TX the
*firmware* originates itself is broken.

This is the only thing standing between this driver and daily
usability. Everything else works.

## What's been ruled out (notes/07-11, exhaustive register/table
comparison against wl's captured state)

Every PHY register, every PHY table (969 of them), radio registers,
chipcommon/PMU state, RF sequencer force/settle logic, per-core gain
override, FIFO/threshold math, and all 795 SHM words wl is seen writing
have been checked against a live wl capture and found to match, or
found to have zero effect when forced to wl's value. None of it
explains the failure. **Do not re-check any of this in a future
session** - it is genuinely exhausted.

## Ucode-level tracing (notes/12-14)

Independently confirmed, at the D11 core microcode level (not just the
host driver), that the failure is a real hardware-asserted PHY
condition bit, not a software logic bug in either wl or this port.
Traced the exact ucode addresses involved and decoded a diagnostic
record showing the failed TX was in valid HT (802.11n) PLCP format -
not a malformed-frame issue.

## Independent over-the-air evidence (notes/15)

Using a technique discovered this session - a USB WiFi stick can run an
independent monitor-mode capture *concurrently* with its own connected
managed interface, with zero disruption (`iw phy <phy> interface add
<name> type monitor`) - captured traffic independently while the
internal chip attempted to ACK real AP probe responses. Result: **zero
of the AP's probe responses were ever ACKed on the air**, despite the
firmware's own counters showing it believed it sent ~120 ACKs. This was
the first methodologically sound OTA evidence in the whole project, and
points specifically at "the TX chain doesn't produce usable RF for fast
autonomous transmissions," not just "the AP fails to decode it."

## Today's major thread: TX calibration (notes/16, very long, this is the condensed version)

**Finding:** `wlc_phy_cals_acphy`, AC-PHY's periodic TX IQ/LO-feedthrough
calibration state machine, is never invoked anywhere in this port. It's
a genuine per-chip, per-antenna, *measured* correction (not a fixed
constant) - which would explain why every earlier register-comparison
check came back clean: the values replayed from wl's one-time capture
may have been correct at the moment wl captured them, but nothing
re-establishes or refreshes that calibration in our port.

**What was built and safely tested on real hardware today** (each
piece staged and tested standalone before combining, per this
project's established practice - zero instability across all of it,
0% packet loss on the backup link throughout):
- Full save/restore of the RF-loopback calibration mode switch.
- The gain-table override and settle-pulse pieces of the algorithm.
- **A real, live TX test tone, generated and sustained on this
  hardware for the first time in this project** (CORDIC waveform
  synthesis, verified bit-exact against Python's `math.sin`/`cos`
  before trusting it).
- The full ~110-register per-core measurement setup block, resolved
  with zero remaining guesswork (fully hand-verified against the
  decompiled arithmetic, bit-exact).
- The actual closed-loop candidate-search measurement itself (write a
  correction candidate, trigger a hardware comparison, read back the
  result) - the first closed-loop, hardware-reactive test in this
  project.
- Two real bugs caught and fixed along the way: an earlier test
  session's "sustained tone" wasn't actually sustained (restored the
  tone-control registers immediately, undoing it within microseconds);
  and two register writes initially dismissed as inert bookkeeping
  turned out to be real, necessary table clears.

**Result:** with essentially everything this project can find and
safely port now in place, and tested against the *entire* real
candidate table wl itself would use (36 combinations, not a cherry-picked
sample), **the measurement never shows any signal-dependent behavior at
all.** It reports the same result regardless of the correction
candidate tried.

**Honest caveats, checked deliberately before trusting the above:**
- The one remaining unported piece is wl's real cleanup path
  (`wlc_phy_resetcca_acphy` → `wlapi_bmac_phyclk_fgc`), which writes to
  **BCMA_IOCTL** on the live D11 core - the same register category
  behind this project's one hard machine freeze (notes/07,
  2026-09-26). This was deliberately *not* implemented or tested solo;
  it needs the user physically present, full stop.
- The measurement register (`0x144` on the radio) was found to have a
  *different* role in another, unrelated calibration routine elsewhere
  in wl (different bits, different meaning) - real evidence it's a
  live, mode-dependent status latch, not proof its meaning in the
  TX-loft-cal context is fully understood. This tempers the finding
  above without overturning it.

**Net assessment:** the TX-calibration hypothesis - this project's
leading theory going into today - is *less* favored coming out of today
than it was going in, precisely because implementing it as completely
as currently possible failed to produce the kind of signal-dependent
behavior a working measurement should show. The more parsimonious
reading of all accumulated evidence (today's flat measurement + the
independent OTA finding above) is a genuine hardware problem somewhere
in the TX RF front-end - something calibration code, however complete,
cannot fix. **This is a strong working hypothesis, not a proven
conclusion.**

## Concrete next steps, roughly in order

1. **Needs the user present:** port and test wl's real cleanup path
   (`wlc_phy_resetcca_acphy`/`wlapi_bmac_phyclk_fgc`, the BCMA_IOCTL
   write) in case it's actually a precondition rather than just
   cleanup, and/or attempt the actual tone-generation + measurement
   sweep at higher signal amplitude to rule out "the test tone itself
   is too weak to be measured."
2. **Needs the user present, higher risk still:** if the above doesn't
   change anything, the honest conclusion is that root-causing this
   further needs either real chip documentation (none exists publicly)
   or actual RF test equipment (spectrum analyzer) this project doesn't
   have - at that point, register/code archaeology has reached its
   practical limit.
3. **Unresolved, not started:** whether wl itself sees any `txphyerr`
   on this exact hardware during normal association - would settle
   whether the failure rate is a b43-port bug or a baseline this
   specific chip/board tolerates and wl simply works around. Needs wl
   bound again (reboot) and a kprobe on wl's stats path, not direct
   SHM polling while wl owns the device (see notes/09's macdump
   caveat).
4. **Not urgent:** the user asked for this driver to eventually be
   "upstreamable." The codebase is decompiled-derived, not clean-room -
   not mainline-submittable as-is regardless of whether the ACK bug is
   fixed. This tension was flagged to the user earlier and is still
   unresolved; a real submission would need a from-scratch clean-room
   rewrite, a separate, much larger effort. Don't assume "keep making
   it work" implies solving this - it needs the user's explicit
   decision when they're free to discuss it.

## Standing safety rules (all still in force)

- Never commit `extracted/`, `ghidra_proj/`, or `firmware/` (proprietary
  Broadcom binaries) - gitignored, already purged from history.
- Only one Claude/Codex session touches this hardware at a time -
  `ps aux | grep -iE "claude|codex"` before every hardware-touching
  step.
- USB stick (`wlp0s20u1`) is the backup network link - verify 0% packet
  loss before and after every load/unload, not just once per session.
- `sudo tools/postboot.sh` after every reboot, before any b43 swap.
- Set `kernel.panic_on_oops=1 kernel.panic=10 kernel.hung_task_panic=1
  kernel.hung_task_timeout_secs=30 kernel.softlockup_panic=1` before any
  live hardware test.
- Never rebind `wl` after `b43` has touched the chip in the same boot
  session.
- **BCMA_IOCTL writes on the live D11 core are the one specific,
  documented hard-freeze category in this project's history** (5 GHz
  80 MHz bandwidth bit, 2026-09-26). Treat any new BCMA_IOCTL-touching
  code as needing the user physically present, regardless of which
  specific bit is involved.
