# 168: Alessio's bcma patches tested and installed permanently

Alessio sent his bcma series in mainline form (8 patches, base v7.3-rc5). Built as out-of-tree `bcma.ko` for 7.2.10
(`b43-src-builds/ale8-bcma-7.2.10.ko`, `tools/try_bcma_patches.sh`):

- Loads, cores found, our b43 init clean, connected, 2.4 GHz MCS 7, 30 MB download about 32 Mbit/s.
- Resume after a 3 h 42 min lid-closed suspend (16:54-20:36): b43 came back, no HT/PLL/ucode errors. One run; stock
  bcma failed after 11 h (notes/167), so an overnight repeat is still due.
- Patches 5-7 (SPROM rev 11, NVRAM) not exercised by our b43; patch 8 (PCI ID 0x43b3, BCM4352) not testable.
- Reply sent to Alessio (`upstream/reply-to-alessio-bcma.txt`).

## Permanent install
- `nix/bcma-ac.nix`: kernel source of the running kernel + `nix/bcma-patches/` (his patches 1-4 and 8), builds
  `extra/bcma.ko`; `boot.extraModulePackages` in /etc/nixos/configuration.nix (backup `.bak-before-bcma-ac`).
  `nixos-rebuild boot` done (takes effect at the next reboot; not switched, to keep the stick up).
- Only patches 1-4 and 8: 5-7 change `struct ssb_sprom` (a `gpio_ext[12]` member mid-struct, bigger
  `ssb_sprom_core_pwr_info`), and our b43 is compiled against the stock header and would read sprom fields at wrong
  offsets. Add 5-7 once b43 is built against the same headers.
- depmod does not index `extra/`, so `tools/b43_boot.sh` insmods the extra bcma by path (like b43) when bcma is not
  loaded yet, else `modprobe bcma`.
- The Nix-built module was loaded by hand and our b43 connected on the first try.
- The in-use test at the next reboot: `journalctl -b | grep "loading .*extra/bcma.ko"`.
