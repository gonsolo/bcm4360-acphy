# 103 - git bisect: the regression is an interaction, not a single commit

Goal (notes/92): find what makes the MAC suspend-ack take ~80 ms (vs 0-3 ms)
on 7.2.x. Test per candidate: boot it, `bisect-boot/load.sh`, let NetworkManager
scan, then `dmesg | grep suspendtiming`. Bad = `wait=79-85ms` + `MAC suspend
failed`; good = no `suspendtiming` line (it logs only above 15 ms) with well
over zero `switch_channel` lines (scans really ran).

## Pipeline fixes this session (all in tools/)
- initrd `/init`: mount of `/dev/sda3` retried (+ drop to a shell instead of
  the silent "Attempted to kill init" panic); firmware path read with a plain
  `readlink` (the old `chroot /newroot busybox` never worked: no busybox in the
  NixOS root); stock in-tree `b43*` modules skipped (they bind the BCM4360 and
  fail with "UNSUPPORTED PHY", blocking our own `insmod`); every step is also
  appended + sync'd to `/var/log/bisect-initrd.log` on the real root.
- boot entry: `init=` now taken from `readlink -f /run/current-system` (the stale
  default entry gave an old generation, hence the old claude version);
  `loglevel=7 panic=0`; old `bisect-*` files removed before staging (/boot is
  511M); `nixos-rebuild` deletes unknown files in /boot/EFI/nixos, so never run
  one between staging and the test.
- `bisect_build.sh`: SSH/SCP retry on connection failure (the laptop's Wi-Fi
  roams); `EXTRA_CONFIG="CONFIG_X=n ..."` override for experiments.
- `bisect_merge_test.sh`: build "good mainline + prefix of a pulled branch".
- Netconsole was rejected: not in the config, and there is no NIC up that early.

## Results
Pass 1 (plain `git bisect`) was misleading: it walked into side branches based
on v6.18-rc1/rc3 (they do not contain v6.18, all bad) and was heading for an
arm64 dts commit. Results of pass 1:

| commit | kernel | result |
|---|---|---|
| 60b8d4d49281 | 7.0.0-01891 | bad |
| 417d029dc412 | 6.19.0-00914 | bad |
| b1dd1e2f3e4e | 6.18.0-08235 | good |
| feb06d2690bb | 6.18.0-12415 | bad |
| 0cac5ce06e52 | 6.18.0-10462 | bad |
| 399ead3a6d76 | 6.18.0-09318 | good |
| c02dce25bc66, e828dff381a4, ab07edaab69e (soc/dt merges, base v6.18-rc3) | 6.18.0-rc3-* | bad |
| 4651760fb2c4, ad58d1078a17, 7b76c923f582, 8895b0e60050 (renesas dts, base v6.18-rc1) | 6.18.0-rc1-* | bad |

`bisect_build.sh` does `rm -rf bisect-boot` on every run, so nothing saved there survives.

Pass 2 (`git bisect --first-parent`, Linus's mainline only) ends on
**51d90a15fedf "Merge tag 'for-linus' of .../kvm/kvm" (2025-12-05)**; first
parent 399ead3a6d76 good, second parent e0c26d47def7 (kvm branch tip, based on
v6.18-rc7) **also good when booted alone**.

| tree | result |
|---|---|
| b1dd1e2f3e4e, 399ead3a6d76 (mainline before the pull) | good |
| e0c26d47def7 (kvm tip alone), with and without `mitigations=off` | good |
| 51d90a15fedf (the merge) | bad |
| 51d90a15fedf, `CONFIG_KVM=n` | bad |
| + x86 core files bugs.c/nospec-branch.h/cpufeatures.h/scattered.c from 399ead | bad |
| + mm/filemap.c, mm/mempolicy.c, mm/readahead.c, include/linux/pagemap.h, fs/{btrfs,erofs,f2fs} callers from 399ead (819e185d09c9) | **good** |

Ruled out: CPU-bug mitigations (boot messages identical, tip good with them on),
kernel config (olddefconfig output identical for 399ead vs the merge), the
cpuidle driver (Monitor-Mwait lines do not correlate).

## What is left
The only remaining difference is the "NUMA mempolicy for filemap" series: an
extra `struct mempolicy *policy` argument to `filemap_alloc_folio()` /
`__filemap_get_folio()`; every non-KVM caller passes NULL. That is a no-op for
this machine, so the effect must be indirect (page allocation / physical memory
layout / code layout), not a logic change. Note the bisect's `load.sh` loads
b43 without `dma32=1` (64-bit DMA mask, 8 GB RAM) while the daily boot uses
`dma32=1` and is still ~40% flaky on 7.2.7, so DMA placement alone is not
proven.

## Follow-up experiments on the running 7.2.7 (all negative)
Baseline everywhere: fresh reload + connect (`ab_reload_test.sh`, logs in
`test-logs/`), ~2/5 connect, 4-15 `MAC suspend failed` per attempt.

| experiment | result |
|---|---|
| boot 7.2.7 with `mem=2G` (all RAM below 2 GB) | still bad (12-14 failures): DMA placement above 2 GB is not the trigger |
| boot 7.2.7 with `maxcpus=1` | 0 failures, connected after one auth timeout - but a single boot |
| same, CPUs 1-3 offlined at runtime | module reload failed 4/5 times (invalid); the one valid attempt had 12 failures. A CPU race is not the cause; the clean `maxcpus=1` boot was probably luck |
| driver: on suspend timeout re-enable MAC, wait 5 ms, suspend again (x2) | 1/8 connected, `recovered=0` in 8 attempts: the halted ucode is not restarted by this (reverted) |
| `pcie_aspm` policy `performance` (card link confirmed `ASPM Disabled`) | 1/6 connected, 13-16 failures: not ASPM |
| IOMMU | none on this machine (0 iommu groups): not relevant |

Ruled out overall: CPU-bug mitigations, kernel config, cpuidle driver, DMA
placement, CPU count, ASPM, IOMMU, suspend retry. Still standing: the 79-85 ms
failures start with a `PHY transmission error` on the scan probe right before
them (see `bla`-style dmesg); the ucode is then halted at a fixed PSM address
(notes/77), which only a real fix of the TX/PHY state can avoid. The bisect
proved the trigger is sensitive to tiny, functionally irrelevant kernel changes
(a NULL `policy` argument in mm/filemap), i.e. timing/layout, not a logic
change - so there is no single culprit commit to revert.

Scripts added/changed this session: `tools/bisect_initrd_init`,
`tools/bisect_build.sh`, `tools/bisect_merge_test.sh`.
