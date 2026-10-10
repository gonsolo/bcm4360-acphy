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

## Status (2026-10-10)

**Current entry points:** `notes/136-phy-replay-bisect-tx-power-control.md`
(init, RX level, second TX chain), `notes/137-ampdu-tx-works.md` (A-MPDU)
and `notes/117-alessio-driver-live-test-hangs.md` (the other AC-PHY
driver, retested).

- **2.4 GHz works** on kernel 7.2.9, next to the router: -39 dBm, 0% ping
  loss, about 20 Mbit/s up and 17 down at legacy rates (the default).
- **HT20 with A-MPDU TX works** behind `ac_ht=1 ac_ampdu=1` (off by
  default): MCS 0-15 on both chains, about 30 Mbit/s up over a 15-minute
  soak, 36-43 in short runs. The microcode builds the aggregates; the
  driver requeues MPDUs it gives up on. Aggregates are limited to 4 MPDUs:
  longer ones lose their later MPDUs, which points at the transmit signal.
- **Init is real code, not a replay.** The 290-write PHY replay table is
  replaced by `b43_phy_ac_phyinit()` (named blocks, following Alessio's
  driver), the radio table is cut to 21 named writes. Three single writes
  mattered most: PHY `0x1726 = 0x000c` (26 dB of RX level), chipcommon
  `chipcontrol` bit 3 (without it the second TX chain does not radiate),
  and hardware TX power control off (it fails about 28% of frames at 1 m).
- **Not done:** TX calibration (only about 12 dB of TX margin at 1 m) and
  a real TX power setting; RX aggregation; 40 MHz is coded but untested;
  5 GHz init is still a table (`phy_ac_por5g.h`) and 5 GHz TX does not
  work; hardware encryption is off (`nohwcrypt=1`); five PHY words
  (0x1739, 0x016b, 0x0175, 0x03c4, 0x0197/98 values) are constants of
  unknown meaning; the test parameters and debugfs have to go before any
  upstreaming.
- Older bisect/boot history (kernel regression hunt, notes/76-102) is kept
  in the notes.

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
