# Goal

Get the BCM4360 (PCI id 14e4:43a0, MacBookAir6,1 internal WiFi) working with
the in-kernel open-source `b43` driver instead of the proprietary `wl`
(broadcom-sta) blob, by reverse-engineering the AC-PHY init/calibration
sequence out of `wl.ko` and porting it into `b43`'s existing (currently
empty) AC-PHY skeleton.

# Why this is plausible but hard

- `CONFIG_B43_PHY_AC` has been marked `BROKEN` in mainline since ~2015.
- `drivers/net/wireless/broadcom/b43/phy_ac.c` (see `reference/b43/`) is a
  ~90-line stub by Rafał Miłecki: it wires up indirect PHY/radio register
  read/write plumbing (same convention as older b43 PHYs) but has **no**
  init or calibration logic at all. `recalc_txpower`/`adjust_txpower` are
  no-ops.
- A 2015 b43-dev mailing list thread confirms the maintainers had real
  BCM4360 hardware and tried, but stalled ("today we're still far away
  from getting it running") and nothing has moved since.
- The proprietary `wl.ko` (still shipped/buildable via nixpkgs
  `broadcom-sta`, currently what this laptop uses) contains ~137 functions
  and data tables with `_acphy` in the name (see
  `extracted/wl_acphy_symbols.txt`) — e.g. `wlc_phy_attach_acphy`,
  `wlc_phy_cals_acphy`, `wlc_phy_table_write_acphy`,
  `wlc_phy_txpwrctrl_set_target_acphy` — plus large calibration/gain
  tables (`acphy_txgain_ipa_5g_*`, `acphy_papd_cal_scalars_tbl_*`, etc).
  This is ordinary compiled x86-64 code in a normal ELF `.ko` (confirmed
  via `objdump -d`), not encrypted/opaque firmware. `wlc_phy_attach_acphy`
  alone is ~6KB of machine code, mostly struct-field initialization.
- Separately, `d11ac0/1/2/3/6initvals*` etc. are genuinely opaque firmware
  blobs uploaded to the chip's embedded D11 MAC-timing core — but that
  layer is *not* the blocker; b43 already knows how to upload/use blobs
  of this kind for older chips via the standard `fwcutter` mechanism.

# What's blocking

Not obfuscation, not crypto — pure **volume and lack of documentation**.
~100+ substantial functions to decompile, correlate against unknown
hardware register semantics, and reimplement cleanly enough to be
legally shippable as GPL code (should not be literal copied/translated
disassembly of proprietary code — needs to be an independent
reimplementation once we understand *what* it does, mirroring how earlier
b43 PHY generations were done).

This is the same order of effort as the multi-year work that got N-PHY/
LCN-PHY into b43 originally — realistically many sessions, not one.

# An MMIO trace was tried first (see notes/01-mmiotrace.md)

Traced `wl.ko`'s `osl_writel`/`osl_readl` etc. via bpftrace kprobes while
toggling WiFi off/on. Result: mostly DMA-ring/interrupt housekeeping
traffic (one register hit 75k times in 20s), because the higher-level
register-access wrapper functions (`phy_reg_write`, `si_corereg`, ...)
aren't ftrace-instrumented and can't be kprobed directly. A **full**
`rmmod`/`modprobe` reload trace (not yet done) would likely show more of
the real cold-init path and is worth doing before/alongside decompiling.

# Plan / next steps

1. Ghidra headless decompile of the ~137 `_acphy` functions +
   `wlc_phy_attach*`/`wlc_phy_init*` call graph → `decompiled/`.
2. Re-run the bpftrace MMIO capture across a full `rmmod wl; modprobe wl`
   cycle to get the genuine cold-init register write sequence, cross-
   reference against decompiled logic.
3. Build a register-offset/struct-field glossary as we go
   (`notes/registers.md`) rather than trying to understand everything at
   once.
4. Start with the smallest useful milestone: get `b43` to at least attach
   and bring the radio up on a legacy (non-VHT) rate, before attempting
   full 802.11ac support.

# Environment notes

- This laptop currently has TEMPORARY passwordless sudo enabled for
  `gonsolo` (added to `/etc/nixos/configuration.nix` as
  `security.sudo.extraRules`) specifically to support this project's
  bpftrace/kprobe work. Revert this when the project is paused/done.
- `bpftrace` was added to `environment.systemPackages` for the same
  reason.
