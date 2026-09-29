# Status 2026-09-29 (part 24): seventh bisect boot infrastructure
rework - stopped hand-guessing which drivers must be builtin, switched
to NixOS's own actual `.config` plus a real, generic
`modprobe`-everything initrd

Direct continuation of notes/99, same day. The `i915` fix got further
- GDM login worked, GNOME Shell ran, `i915` attached correctly (`Found
haswell/ult... integrated display`) - but "no mouse, no apps" persisted.
Investigation found the actual trackpad/mouse HID device (`hid-generic
... Mouse [HID 05ac:820b]`, `input3`) registers correctly at the kernel
level, and EGL/glamor acceleration succeeded this time (no more
`simpledrm` fallback) - so this was **not** the same class of bug as
before. Also found, and confirmed as a red herring, that
`pxa2xx_spi_pci`'s probe failure (`error -22`) happens identically on
the *normal, working* 7.2.7 system too - not specific to our build.

## The user's steer, twice, that actually fixed the underlying process problem

Two suggestions landed back to back and together solved the *real*
issue - not this specific "no mouse" symptom, but the whole *pattern*
of six boot attempts each hitting one more missing driver:

1. **"Can't you have a look how the NixOS kernels are built? They
   work!!"** - obviously correct in hindsight: the actual, currently-
   running 7.2.7 kernel's `.config` (from the `linux-7.2.7-dev` package
   already in the Nix store, `/nix/store/.../lib/modules/7.2.7/build/
   .config`) is *guaranteed* to support everything this hardware needs,
   since it's what's running daily. Hand-trimming a config via
   `localmodconfig` from scratch and then playing whack-a-mole with
   individually-discovered missing drivers (storage, `vfat`, HID/input,
   `i915` - notes/94/95/99) was strictly worse than starting from a
   config already proven complete.
2. **"But initrd is probably a good idea."** - the deeper fix. Every
   missing-driver bug so far existed *specifically* because the earlier
   pipeline had no initrd at all, forcing each needed driver to be
   manually identified and flipped to `=y` (builtin) one at a time. A
   real initrd that loads modules generically eliminates this whole bug
   class permanently, rather than requiring the *next* missing driver
   to also be discovered by trial and error.
3. **"You can strip things from the config that are obviously not
   needed on our MacBook."** - `make localmodconfig` (a standard,
   well-tested kbuild tool, not hand-guessing symbols) is the right,
   safe way to do this trimming, as long as it's applied for build-time
   reasons only, not as a substitute for a real initrd's runtime module
   loading.

## New pipeline (see `tools/bisect_build.sh`'s header comment for the full detail)

- **Base `.config`**: NixOS's actual `linux-7.2.7-dev` config, copied
  directly - not hand-built.
- **`make localmodconfig`** (against current `lsmod`) on top, to keep
  the build reasonably sized - safe because the base is already known-
  complete; trimming can only remove genuinely-irrelevant hardware, not
  introduce a new "forgot this driver" bug.
- **Module compression disabled** (`CONFIG_MODULE_COMPRESS` unset) -
  plain `.ko` files, no compression-library dependency needed in the
  initrd's `busybox`.
- **A real, generic initrd**, built by `bisect_build.sh` itself:
  - `~/busybox-static` on pampelmuse - a statically-linked
    `pkgsStatic.busybox` build (has `modprobe`/`insmod`/`mdev`/
    `switch_root`/`mount` applets, confirmed via `ldd` → "not a dynamic
    executable", no shared-library bundling needed).
  - `make modules_install INSTALL_MOD_PATH=... INSTALL_MOD_STRIP=1`
    (this also auto-runs `depmod`, generating the dependency database
    `modprobe` needs) - 185 stripped modules, ~55M.
  - `tools/bisect_initrd_init`: mounts `/proc`/`/sys`/`/dev`, does a
    single `modprobe -a <every module in the tree>` (dependency
    ordering handled automatically by `depmod`'s database - modules
    already builtin or irrelevant to this hardware just no-op), `mdev
    -s` to populate device nodes once drivers have loaded, mounts the
    real root, reads the real `init=` path from `/proc/cmdline` (so it
    always matches whatever the boot entry itself specifies - one
    source of truth, not duplicated), `switch_root`s into it.
  - Packaged as a standard `cpio -H newc | gzip` archive, ~13M
    compressed.
- **`bisect-boot/load.sh` is now much simpler**: only handles the
  `bcma-pci-bridge` PCI binding dance (same as `tools/b43_boot.sh` -
  not automatic, still needed) and `insmod b43.ko` itself (out-of-tree,
  never part of the kernel's own module tree, so the generic initrd
  can't load it). Everything else - storage, HID/input, GPU,
  `bcma`/`mac80211`/`cfg80211`/`ssb` for WiFi - now loads automatically
  at boot, before `load.sh` is even needed.

Rebuilt clean with this pipeline (`bzImage` #6, 1 benign "error" grep
hit again - `arch/x86/boot/compressed/error.o`), `b43-src` rebuilt
against it, packaged (`bzImage` + `initrd.img` + `b43.ko` only now -
the other driver `.ko` files don't need separate packaging since the
initrd already carries and loads the full module tree itself), staged
as the same one-shot entry with a new `initrd=` line.

## Current state at session end

Seventh attempt at the same commit (`60b8d4d49281`) about to begin.
This is a genuinely different, more robust approach than every attempt
before it - rather than another single fix for the specific "no mouse"
symptom, it removes the entire mechanism that made six consecutive
boot attempts each surface a new missing driver one at a time.

## Next steps

Reboot into the new entry. If this boots to a fully working desktop
(cursor, app launching, everything): finally run the actual bisect
test - `bash ~/bcm4360-acphy/bisect-boot/load.sh`, confirm `wlp3s0b1`,
`connect_test.sh`/check `dmesg` for `suspendtiming`/`MAC suspend
failed`, `git bisect good`/`bad`, then `tools/bisect_build.sh` for the
next candidate - which should now be dramatically more reliable since
the generic initrd approach isn't specific to this one commit's driver
needs. If something *still* doesn't work: the failure mode itself
becomes much more informative, since the "did I forget a driver"
explanation is now much less likely to be the cause.
