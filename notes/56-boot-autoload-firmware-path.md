# Boot-time auto-load: three failed attempts, and notes/55 corrected

Goal: b43-src loads by itself at boot on kernel 7.2.7, NetworkManager
connects with it, USB stick unplugged.

## Failures

1. Gen 13, `boot.kernelModules = [ "b43" ]`: loaded the stock in-tree b43
   (same module name), which fails probe on AC-PHY. Now b43/bcma stay
   blacklisted and a systemd oneshot (`b43-ac-load.service`) insmods ours.
2. Gen 14: service's hand-built PATH lacked bash (`env: 'bash': No such
   file`). Now PATH is `/run/current-system/sw`.
3. Gen 15: the service ran `b43_live.sh swap` + `load`, the test harness.
   Two separate problems:
   - `load` sets the netdev `managed no` and parks it in monitor mode, so
     GNOME wouldn't have shown it even if it had come up.
   - It never came up: b43 found no firmware, and neither did the USB
     stick (`mt7662_rom_patch.bin` -2).

## Root cause of gen 15 (and both "bugs" in notes/55)

NixOS has no /lib/firmware. `firmware_class/parameters/path` is the
**only** firmware search path, set at boot to
`/nix/store/...-firmware/lib/firmware`. So:

- `swap` overwrote it with `$PROJ/firmware`, and every other driver lost
  its firmware until it was restored. The notes/55 "reset" wrote an empty
  string, which wiped it for good. That's why the stick failed on
  hot-replug before and at boot in gen 15.
- b43 requests firmware **asynchronously** (`INIT_WORK(&wl->firmware_load)`
  + `schedule_work` in probe, main.c:5937). notes/55 assumed it was
  synchronous within insmod. The reset right after insmod raced the work
  item, so b43 missed its own firmware, and the netdev (registered only
  after firmware loads) never appeared. That's the notes/55 "swap/load
  timing race" too; the 2 s sleep there did nothing useful.

## Fix

- `hardware.firmware` installs `firmware/b43/*.fw` into the NixOS firmware
  bundle (as .fw.zst). No path override needed. Rebuild after changing
  firmware files.
- `tools/b43_boot.sh`: daily-use load for the service. It does modprobe
  deps, bcma-pci-bridge override, waits for bcma0:1, insmods, then waits
  for the netdev. No path games, no monitor mode, no panic sysctls. NM
  auto-connects the Vodafone profile.
- `b43_live.sh`: `swap` overrides the path only when b43 firmware isn't
  already there, saving the original to /run/b43live_fwpath_orig. `load`
  restores it after the netdev appears, not straight after insmod.
