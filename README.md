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

## Status (2026-09-27)

**Not ready for daily use.** Read `notes/10-status-2026-09-27-gain-override.md`
for the full, current picture; the numbered files in `notes/` are a
chronological log of the whole investigation.

Working, on real hardware:
- Attach, firmware upload, DMA, radio power-up and channel tuning.
- **Receive** on both 2.4 GHz and 5 GHz: decodes the majority of a
  nearby AP's beacons, scan, open-system authentication, association.

Not working:
- **The firmware's own automatically-generated transmissions (ACKs,
  beacons) fail ~90-95% of the time** with a genuine hardware PHY
  transmission-error interrupt, while host-generated transmissions
  (data frames built and queued by the driver) are 100% clean at every
  rate tested. This is why WPA2 can't complete — the access point never
  reliably receives our ACKs. The root cause is unresolved; see
  `notes/07` through `notes/10` for everything ruled out (chip-control
  registers, MAC timing, the TX FIFO threshold setup, every shared-
  memory word the vendor driver is known to write, gain-calibration
  freshness) and what's suspected to remain (something in the PHY's
  analog/calibration state, or a difference below the register
  abstraction — needs instrumentation this project doesn't have, e.g.
  an RF capture during a failure).
- 5 GHz transmit and a from-scratch (non-replay) channel-set/init path
  are unfinished; see `notes/`.

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
first — `tools/postboot.sh` and `tools/netwatch.sh` exist specifically
because of lessons learned the hard way.

## License

`b43` itself is GPL-2.0; changes here follow that. Decompiled-code
excerpts and analysis notes (`decompiled*/`, `refs_out/`, `notes/`)
document research into a proprietary binary's behavior and are not
themselves copies of it. No proprietary binaries or extracted firmware
are included, per above.
