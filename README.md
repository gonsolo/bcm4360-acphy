# bcm4360-acphy

Reverse-engineering effort to bring the Broadcom BCM4360 (802.11ac
AC-PHY, PCI ID `14e4:43a0`) to the in-kernel, open-source `b43` Wi-Fi
driver, by observing and decompiling Broadcom's proprietary `wl`
driver (`broadcom-sta`) on real hardware (a MacBookAir6,1: core
revision 42, radio Broadcom 2069 revision 4).

`CONFIG_B43_PHY_AC` has been present but marked **BROKEN** in mainline
Linux since kernel 4.5 (~2016) — nobody had gotten it working. This
project is not there either, but it's the furthest getting I'm aware
of anyone getting: real hardware, real reception, real association.

## Status (2026-09-29)

**Read `notes/90-status-2026-09-29-6-18-53-reference-capture-suspend-is-genuinely-near-instant-regression-confirmed-kernel-side.md`
first** — it's the current entry point: a direct, controlled 6.18.53
reference capture, using the exact same instrumented driver binary as
every 7.2.7 capture, found `b43_mac_suspend()` completing in 0-2ms
across 38+ samples with zero failures, versus a consistent ~80ms/many
failures on 7.2.7 for the identical operation - **conclusively
confirming this is a real, kernel-side regression**, not measurement
noise or driver drift. It links back to everything that built up to
this (start with `notes/77` for the fuller kernel-regression writeup,
`notes/78`-`81` for the channel-6 replay/A-B/C-state threads, `notes/82`-
`83` for the ftrace finding on steady-state scanning, `notes/84` for the
phase-timing instrumentation that first pinned connect-time slowness on
`b43_mac_suspend`, `notes/85`-`86` for the still-parked steady-state-
scanning mystery, `notes/87`-`88` for the auto-recovery watchdog,
`notes/89` for the lock-vs-suspend split and the pre-staged 6.18.53
build this capture used). The numbered files in `notes/` are a
chronological log of the whole investigation; earlier "session summary"
checkpoints (`notes/17`, `notes/76`) are also good wide-angle reads, but
`notes/90` is the most current.

**The original ACK/firmware-TX blocker (2026-09-26/27, see notes/06-21) is
long since resolved** — it turned out to be several distinct SHM/POR-replay
bugs (see notes/33, "Bug 1-4"), not a hardware fault. Since then:

Working, on real hardware, on kernel 6.18.53 (the original/historical
kernel this project developed against):
- Attach, firmware upload, DMA, radio power-up, channel tuning (2.4 GHz
  and 5 GHz, including the Farrow-resampler per-channel fix, notes/51/53).
- Full WPA2 4-way handshake, DHCP (IPv4 and IPv6), and real IP traffic
  (ping, ARP) over the actual BCM4360 hardware (notes/33) — the project's
  original milestone.
- Reliable reconnection: 4-5/5 clean first-try connections, zero MAC-
  suspend failures, in the project's most recent clean A/B test
  (notes/76).

**Current blocker, now conclusively confirmed and precisely localized:
`b43_mac_suspend()` — a function that does nothing but write one
register and poll another — completes in 0-2ms on kernel 6.18.53 and
takes a consistent ~80ms (or fails outright) on kernel 7.2.7, for the
identical driver binary, identical hardware, identical operation**
(notes/90: a direct, controlled reference capture using the same
instrumented build on both kernels, not just success/failure-rate
inference). This is what makes fresh connects/reconnects on 7.2.7 fail
~30-40% of the time (notes/76, notes/84) — not a firmware/RF/hardware
issue, and not (per notes/89) simply "2x a retry" (that ~80ms figure is
`msleep(1)` rounding, present on both kernels equally; what differs is
whether the wait ever *succeeds* within it). **Staying on 6.18.53 as the
daily-use kernel is explicitly not an option** — 7.2.x has to be made
reliable; 6.18.53 stays reference-only. Ruled out as the cause: bcma/
mac80211/PCI-ASPM/irq/workqueue/hrtimer commits (notes/77) and CPU
C-states/wakeup latency (notes/81). **Narrowed but not yet found**: since
the rest of the same function's MMIO-heavy work (channel retune, TX
power, antenna, `mac_enable`) is equally fast on both kernels, whatever
changed looks targeted at this one wait — either the ucode's own
response latency to a suspend request, or something specific to the
`B43_MMIO_GEN_IRQ_REASON`/`B43_MMIO_MACCTL` register pair (notes/90
suggests checking whether the real IRQ handler, `b43_interrupt_handler`,
races this same register with the polling loop). A *separate*, real but
currently un-reproducible-on-demand phenomenon also exists during
steady-state scanning (notes/82/83/85/86, parked). notes/78 found a
real, heavy (~1300-register) vendor-state replay on every touch of
channel 6 (a fixed staging channel every module bring-up passes
through, unrelated to the AP's real channel — which is 11, notes/81)
that the `ac_state_once` runtime knob suppresses, but whether that
reduces the failure rate is still untested under the right conditions
(notes/79/80). A newer, not-yet-understood RX-blackout symptom found
live at the end of an earlier session (notes/77, Part 6) also still
needs a clean re-check. **Auto-recovery is built and working regardless**
(`tools/b43_autorecover.sh`, notes/87/88) — a stuck connection self-heals
within ~60-90s, so the driver is usable today even before the root
cause above is fully nailed down.

Not working / not attempted:
- 5 GHz transmit (receive works, notes/53) and a from-scratch
  (non-replay) channel-set/init path.
- The kernel-7.2.7 regression above.

## How this is built

A large part of the *receive* path currently works by **replaying a
literal snapshot** of `wl`'s register/table state, captured by tracing
it on real hardware (`traces/`, `tools/decode_trace.py`,
`tools/gen_replay.py` → `b43-src/phy_ac_por*.h`). That's diagnostic
scaffolding, not real driver code — the actual goal (and the harder,
unfinished part) is porting the *logic* wl.ko's decompiled functions
implement into clean, minimal, understood init code in `b43-src/`,
the way `phy_ac.c`'s existing (pre-2026) upstream skeleton and the rest
of `b43` are written. Some of that porting is done (radio/channel
tuning, PHY table init, the AC TX descriptor and RX header formats, the
address-match table, FIFO setup, beacon templates); a lot of it
(especially AGC/calibration) is not.

**Provenance note:** this codebase was developed by decompiling and
directly studying Broadcom's proprietary `wl.ko`, not via clean-room
reverse engineering. That makes it unsuitable for submission to
mainline Linux as-is (see e.g. the OpenBRCM project's explicit
clean-room approach to the same PHY family) — a from-scratch,
clean-room implementation informed by (but not derived from) what's
documented here would be needed for that. This repo exists to share
the research and progress, not as a ready-to-merge kernel patch.

## Firmware

**No firmware or extracted binary material is included in this repo**
(see `.gitignore`) — Broadcom's firmware is not redistributable, the
same reason the `b43`/`b43legacy` community has always relied on
`b43-fwcutter` (a tool users run themselves against a driver package
they've legally obtained) rather than shipping extracted blobs.

To rebuild the `extracted/`, `ghidra_proj/` and `firmware/` directories
this project relies on locally, you need your own copy of
`broadcom-sta`/`wl.ko` for this chip (e.g. via your Linux
distribution's package, built against a matching kernel) and to run
the extraction tools in `tools/` against it. This hasn't been packaged
into a single script yet.

## Building and testing

See `b43-src/Makefile` for an out-of-tree build against a running
kernel, `b43_live.sh` for swapping the chip between `wl` and `bcma`
live (for testing without a full reboot — has real risks, see below),
and `notes/00-overview.md` onward for the reverse-engineering process.

**Hardware safety:** this project involved a hard machine freeze during
testing (see `notes/07`) from combining an experimental 5 GHz bandwidth
change with live TX. If you're experimenting on hardware where Wi-Fi is
your only network path, read the test-harness notes in `notes/`
first — `tools/postboot.sh`, `tools/netwatch.sh`, and (since notes/87)
`tools/b43_autorecover.sh` exist specifically because of lessons learned
the hard way; run `sudo tools/postboot.sh` after every reboot to arm all
of them (netwatch unloads b43 if the network goes fully dark,
b43-autorecover reloads it automatically if the connection gets stuck).

## License

`b43` itself is GPL-2.0; changes here follow that. Decompiled-code
excerpts and analysis notes (`decompiled*/`, `refs_out/`, `notes/`)
document research into a proprietary binary's behavior and are not
themselves copies of it. No proprietary binaries or extracted firmware
are included, per above.
