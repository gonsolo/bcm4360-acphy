# 169: series B, C and D sent as RFC; Linux 7.3.3 in daily use

## Series B, C, D (2026-11-12)
- Johannes Berg is too busy to take b43 patches (via Alessio), series A sits on needs-ack. So B, C and D went out as
  RFC so that people with BCM4352/BCM4360 chips can build a working driver.
- Before sending: Co-developed-by + Signed-off-by from Alessio Ferri on C 2/4 and D 1/4-3/4 (he agreed by mail), copyright
  lines in phy_ac.c, tables_phy_ac.c, radio_2069.c, phy_ac_farrow.h, a provenance paragraph in the covers (values traced
  from wl with bpftrace on its MMIO accessors, parts from Alessio's tree, some formats after brcmsmac), the 40 MHz
  claim removed (never tested), Alessio's known issues listed in D (core count forced to 2, SROM rev 11 read at fixed
  word offsets).
- Style pass on the target tree (final2) for checkpatch --strict --max-line-length=80, as the netdev bot runs it:
  ~630 remarks -> 0 errors, 3 warnings (2x MAINTAINERS for new files, 1 user-visible string), 14 checks (udelay,
  CamelCase names after b43's existing ones, 2 open-ended lines). Tables rewrapped by a script, long code lines by
  clang-format with the kernel's .clang-format (only the lines over 80), a few manual rewrites (SPROM base offset in
  phy_ac.c, VHT->HT fallback in xmit.c with a local, braces on two else arms). The restyled build compiles patch by
  patch but was NOT run on the hardware (user's decision).
- B, C, D apply on series A as sent, on wireless-next 5dbf2415ca98. Sent with tools/upstream/send_series.sh
  (CONFIRM=never for unattended sends). Cover letters: B 20261112175624.40547-1, C 20261112175640.40603-1,
  D 20261112175656.40686-1 (@gmail.com).
- Michael Büsch asked to stop being Cc'd: removed from the send scripts.
- Tested-by sent for Alessio's bcma patches 1-4; he will repost with patch 4 rewritten after siutils.c.

## Linux 7.3.3
- nixos-26.05 dropped linux 7.2 (EOL); boot.kernelPackages is now linux_7_3 (backup configuration.nix.bak-before-7_3).
  Both out-of-tree modules (nix/b43-ac.nix, nix/bcma-ac.nix) build unchanged.
- First boot: patched bcma and b43 from extra/, connected on try 1, 2.4 GHz ch 11 at -49 dBm, MCS 15 both ways,
  30 MB download 45 Mbit/s, no b43 errors. MCS 15 is not new (notes/123-125); whether 7.3 is faster is unknown
  (stronger signal than in earlier runs, one sample). Not yet tested on 7.3: 5 GHz, long suspend.
- Remote builds: pampelmuse had garbage-collected the 7.2.10 -dev tree (nix-store -r restores it); its sshd drops
  connections when the cut opens many in a row, so the cut runs with an ssh ControlMaster wrapper.
