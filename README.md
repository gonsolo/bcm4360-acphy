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

**Read `notes/87-status-2026-09-29-phase-2a-auto-recovery-watchdog-built-and-live-tested.md`
first** — it's the current entry point and links back to everything else
that still matters (start with `notes/77` for the fuller kernel-
regression writeup, `notes/78`-`81` for the channel-6 replay/A-B/
C-state threads, `notes/82`-`83` for the ftrace finding that steady-
state scanning has slow `drv_config` outliers unrelated to
`b43_mac_suspend`, `notes/84` for the phase-timing instrumentation that
pins the *connect-time* slowness on `b43_mac_suspend` genuinely failing,
`notes/85`-`86` for two failed attempts to reproduce the steady-state
outliers, now parked — `notes/87` builds and live-tests an automatic
detect-and-reload watchdog, `tools/b43_autorecover.sh`, so a stuck
connection now self-heals within ~60-75s instead of needing manual
intervention). The numbered files in `notes/` are a chronological log of
the whole investigation; earlier "session summary" checkpoints
(`notes/17`, `notes/76`) are also good wide-angle reads, but `notes/87`
is the most current.

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

**Current blocker: the exact same driver/binary is reliably reliable on
kernel 6.18.53 and reliably unreliable (~30-40%) on kernel 7.2.7** — a
confirmed, repeatable, clean-A/B-tested kernel-version regression
(notes/76), not a firmware/RF/hardware issue. **Staying on 6.18.53 as
the daily-use kernel is explicitly not an option** — 7.2.x has to be
made reliable; 6.18.53 stays reference-only for A/B testing. Ruled out:
bcma/mac80211/PCI-ASPM/irq/workqueue/hrtimer commits (notes/77) and CPU
C-states/wakeup latency (notes/81). **Root cause, precisely localized
for the connect-time case** (notes/84, direct phase-timing
instrumentation, `optiming_thresh_ms` param in `main.c`):
`b43_mac_suspend()` genuinely fails on a large fraction of scan-
triggered channel switches during a fresh connect, eating ~80-90% of a
slow `b43_op_config` call's total time — confirmed with 7/7 clean
samples, each lining up exactly with a real `MAC suspend failed (40ms)`
line. **This alone plausibly explains most day-to-day unreliability**,
since every fresh connect/reconnect goes through this path. A
*separate* phenomenon also exists during steady-state scanning on an
already-associated link, where `drv_config` can take up to ~1.5s
**without** any suspend failure (notes/82/83), but two follow-up
attempts to reproduce it on demand (a freshly-reloaded module, then a
deliberately "aged" one with 28 accumulated scans) both came back
completely clean, 174/174 samples (notes/85/86) — parked pending a real
reproduction rather than actively chased further, since it doesn't
explain the bulk of daily-use pain the way the connect-time failure
does. notes/78 separately found a real, heavy (~1300-register)
vendor-state replay on every touch of channel 6 (a fixed staging channel
every module bring-up passes through, unrelated to the AP's real
channel — which is 11, correcting a wrong assumption in notes/78, see
notes/81) that the `ac_state_once` runtime knob suppresses, but whether
that reduces the failure rate is still untested under the right
conditions (notes/79/80). A newer, not-yet-understood RX-blackout
symptom found live at the end of an earlier session (notes/77, Part 6)
also still needs a clean re-check. **Recommended next step**: build the
daily-use plan's Phase 2a (automatic detect-and-reload on a stuck/failed
connection) — it compensates for the connect-time failure rate directly
and doesn't require resolving either open mechanism first.

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
