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

**Read `notes/97-status-2026-09-29-fourth-bisect-boot-login-succeeds-shell-exits-instantly-debug-shell-staged.md`
first** — it's the current entry point: four bisect boot attempts at
the same commit (`60b8d4d49281`) now, each hitting a different boot-
environment problem, each diagnosed straight from the journal and
fixed with no lasting harm (notes/94: `/boot`, `vfat`, no `nofail` in
fstab, took down the whole boot; notes/95: no keyboard/mouse, the Apple
SPI input chain was all modules - fixed, and switched to a text console
to drop the GDM/mouse dependency entirely; notes/96: the text console
then reached a fully healthy running system with SSH/network up but no
login prompt anywhere, because this NixOS config disables `getty@tty1`
by default since GDM normally owns it - fixed with a kernel-cmdline
`systemd.wants=`; notes/97: login itself now succeeds but the shell
exits within about a second with no journal-visible error - not yet
root-caused, worked around by staging `systemd.debug-shell=1`, an
unauthenticated root shell on tty9 independent of PAM/login entirely).
notes/93 has the fuller compile-server/bisect setup context. notes/92
concluded the timing-
instrumentation thread: on 7.2.7, `psctl=0ms` and `wait=79-86ms` in
16/16 samples from an ordinary daily-use boot autoload; on 6.18.53
(notes/90/91, same instrumented binary), `psctl=0ms` and `wait=0-3ms`.
**The entire regression is isolated to one single-register poll**
(waiting for the ucode to set `B43_IRQ_MAC_SUSPENDED` after a `MACCTL`
write) - every other phase of the same function is equally fast on both
kernels, and there's no more driver-side code left to split. A `git
bisect` is now underway to find *why*: a remote compile server
(pampelmuse, 24 cores, same LAN) is wired up, the first candidate
commit (`60b8d4d49281`, ~15 steps predicted out of 66,387 commits
between v6.18 and v7.2) is built and staged as a one-shot boot entry
(default entry, normal 7.2.7 daily use, untouched), waiting on a
reboot to test. It links back to everything that built up to this
(start with `notes/77` for the fuller kernel-regression writeup,
`notes/78`-`81` for the channel-6 replay/A-B/C-state threads, `notes/82`-
`83` for the ftrace finding on steady-state scanning, `notes/84` for the
phase-timing instrumentation that first pinned connect-time slowness on
`b43_mac_suspend`, `notes/85`-`86` for the still-parked steady-state-
scanning mystery, `notes/87`-`88` for the auto-recovery watchdog,
`notes/89` for the lock-vs-suspend split, `notes/90` for the 6.18.53
reference capture, `notes/91` for the refuted IRQ-race hypothesis and
the psctl/wait split, `notes/92` for the conclusive 7.2.7 confirmation).
The numbered files in `notes/` are a chronological log of the whole
investigation; earlier "session summary"
checkpoints (`notes/17`, `notes/76`) are also good wide-angle reads, but
`notes/92` is the most current.

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

**Current blocker, now precisely bounded (root cause itself still not
found): `b43_mac_suspend()`'s suspend-ack poll** — the specific loop
that does nothing but repeatedly read one register waiting for the
ucode to set an acknowledgment bit, after an immediately-preceding,
flush-verified register write — **completes in 0-3ms on kernel 6.18.53
and takes a consistent ~80ms on kernel 7.2.7, for the identical driver
binary, identical hardware, identical operation** (notes/90-92: a
direct, controlled reference capture with the same instrumented build
on both kernels, split down to this one specific wait — every other
phase of the same function and its caller, including a separate power-
save wake-wait inside the same call, is proven equally fast on both
kernels). This is what makes fresh connects/reconnects on 7.2.7 fail
~30-40% of the time (notes/76, notes/84, reconfirmed by an ordinary
daily-use boot autoload in notes/92) — not a firmware/RF/hardware
issue, and not (per notes/89) simply "2x a retry" (that ~80ms figure is
`msleep(1)` rounding, present on both kernels equally; what differs is
whether the wait ever *succeeds* within it). **Staying on 6.18.53 as the
daily-use kernel is explicitly not an option** — 7.2.x has to be made
reliable; 6.18.53 stays reference-only. Ruled out as the cause: bcma/
mac80211/PCI-ASPM/irq/workqueue/hrtimer commits (notes/77), CPU
C-states/wakeup latency (notes/81), and a real interrupt-handler race on
the same status register (notes/91 — the bit isn't even in the hardware
interrupt mask). **Driver-side instrumentation has reached its limit**
(notes/92) — there is no more source code between the write and the
poll to split further; the remaining question (does the write itself
arrive late, or does the ucode take longer to act on it) needs either
bus-level tracing this project doesn't currently have, or a `git
bisect` in `~/src/linux`, now well-scoped to a fast, unambiguous
pass/fail test instead of a vague reliability judgment call. A
*separate*, real but currently un-reproducible-on-demand phenomenon
also exists during steady-state scanning (notes/82/83/85/86, parked).
notes/78 found a real, heavy (~1300-register) vendor-state replay on
every touch of channel 6 (a fixed staging channel every module bring-up
passes through, unrelated to the AP's real channel — which is 11,
notes/81) that the `ac_state_once` runtime knob suppresses, but whether
that reduces the failure rate is still untested under the right
conditions (notes/79/80). A newer, not-yet-understood RX-blackout
symptom found live at the end of an earlier session (notes/77, Part 6)
also still needs a clean re-check. **Auto-recovery is built and working
regardless** (`tools/b43_autorecover.sh`, notes/87/88) — a stuck
connection self-heals within ~60-90s, so the driver is usable today
even before the root cause above is fully nailed down.

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
