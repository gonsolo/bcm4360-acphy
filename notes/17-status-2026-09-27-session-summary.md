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

**Update (same day, user explicit direction: "Fix the gap. Even if I'm
not here."):** the `wlc_phy_resetcca_acphy`/`wlapi_bmac_phyclk_fgc`
cleanup gap below has since been closed - see notes/18. Investigation
found `si_core_cflags(sih,2,val)` is `BCMA_IOCTL_FGC`, a generic,
mainline-kernel-defined bcma bus bit (not exotic), used in a narrow,
paired set-then-clear while never associated and never mid-TX -
materially different from the incident's mechanism (a persistent
bandwidth-mode change on a running, transmitting core). Implemented,
staged (isolated test first, bit-exact round-trip, then the full flow),
and tested clean: 0% packet loss, `BCMA_IOCTL` stable across sustained
operation. The measurement result itself is unchanged (expected - the
cleanup runs after the measurement) but the port's measurement path no
longer has any documented deliberate deviation from vendor's real
sequence.

**Honest caveats, checked deliberately before trusting the above:**
- ~~The one remaining unported piece is wl's real cleanup path...~~
  **Resolved same day, see the update just above and notes/18.**
- The measurement register (`0x144` on the radio) was found to have a
  *different* role in another, unrelated calibration routine elsewhere
  in wl (different bits, different meaning) - real evidence it's a
  live, mode-dependent status latch, not proof its meaning in the
  TX-loft-cal context is fully understood. This tempers the finding
  above without overturning it.

**Net assessment (superseded below, kept for the historical record):**
the TX-calibration hypothesis - this project's leading theory going into
today - is *less* favored coming out of today than it was going in,
precisely because implementing it as completely as currently possible
failed to produce the kind of signal-dependent behavior a working
measurement should show. The more parsimonious reading of all
accumulated evidence (today's flat measurement + the independent OTA
finding above) is a genuine hardware problem somewhere in the TX RF
front-end - something calibration code, however complete, cannot fix.

**Update (same day, user back at the machine): this is now weakened.**
See notes/19 - a direct, sustained ping test over the internal chip
under `wl` (60 packets, 1400-byte payload, 0% loss, surviving a live AP
roam) proves the hardware *can* reliably do firmware-autonomous ACK
generation on this exact chip. **The hardware is not broken.** The flat
TX-calibration measurement more likely reflects a remaining bug or
missing precondition in this port's *measurement itself* (or something
else entirely wl does differently) than a genuine RF fault. The
hardware-fault reading is no longer the better-supported explanation -
"our port is still missing something" is, again.

## Concrete next steps, roughly in order

1. ~~Whether wl itself sees any `txphyerr` on this exact hardware~~
   **Done, same day - see notes/19. Answered more directly than
   planned: a sustained ping test proved `wl` achieves reliable
   firmware-autonomous ACK generation on this exact chip. The hardware
   works; this is a port-side gap.** This is the most important update
   from today - it demotes the hardware-fault hypothesis and reopens
   "our port is still missing something."
2. **Most promising next angle (see notes/19):** capture wl's full
   register-access sequence during and immediately after association
   (`wl_full_trace.bt`/`trace_wl.sh`, already proven safe to attach to
   the running, bound driver without touching PCI binding) and diff it
   against what this port's `ac_por` replay already covers, looking for
   anything wl touches near association time that this port doesn't
   replicate. Narrower and more tractable than either free-form counter
   hunting (tried today, proved slow and inconclusive) or a full init
   trace (already partially done in earlier sessions).
3. Attempt the actual tone-generation + measurement sweep at higher
   signal amplitude, to rule out "the test tone itself is too weak to
   be measured" - a parameter change to already-tested, already-safe
   code (just a larger `amplitude` constant in
   `b43_phy_ac_txcal_gen_tone_start`), still worth doing given the
   calibration hypothesis is live again.
4. **Needs the user present, higher risk still:** if the above don't
   turn up anything, root-causing this further needs either real chip
   documentation (none exists publicly) or actual RF test equipment
   (spectrum analyzer) this project doesn't have.
5. **Not urgent:** the user asked for this driver to eventually be
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
- **The 2026-09-26 hard freeze was `BCMA_IOCTL`'s PHY-bandwidth bits
  changed on an associated, actively-transmitting core** - not
  `BCMA_IOCTL` as a register in general (mainline b43 itself already
  writes several other `BCMA_IOCTL` bits during ordinary attach/up/down,
  and this port's `MACPHYCLKEN`/`FGC` writes have since been tested
  clean - see notes/18). Before touching a *new* `BCMA_IOCTL` bit,
  investigate the actual mechanism (which bit, persistent or
  momentary, does it require being associated/transmitting) rather than
  generalizing "BCMA_IOCTL = needs the user present" as a blanket rule -
  but a bit whose effect is genuinely unclear, or that persists across
  an active TX path, still warrants the user's presence by default.
