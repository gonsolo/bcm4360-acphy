# 115: b43 as a Nix kernel module (follow-up to notes/114)

`nix/b43-ac.nix` builds `b43.ko` for any `boot.kernelPackages` and installs it to
`lib/modules/<ver>/extra/b43.ko` (depmod prefers extra/ over the in-tree module). Sources come from
`b43-src/*.[ch]` + Makefile only (no objects). Tested on pampelmuse (ssh, not by copying closures from the laptop):
nixpkgs pinned to rev 825e2028c29b (the laptop's channel), `linuxKernel.packages.linux_7_2` -> 7.2.9,
vermagic and depends identical to the hand build.

Gotcha: passing `kernel.makeFlags` to make fails with `make: *** empty variable name` (the `O=$(buildRoot)` /
`--eval=` flags); the derivation calls `make -C <kernel dev>/.../build M=$PWD modules` directly.
`preferLocalBuild = true` keeps the tiny compile off the remote builder (which would need the kernel closure copied).

Wiring (needs the user, /etc/nixos): `sudo tools/install_b43_module.sh` adds
`boot.extraModulePackages = [ (config.boot.kernelPackages.callPackage <repo>/nix/b43-ac.nix { }) ];`
after the `boot.kernelPackages` line (backup, `--remove`, `nixos-rebuild boot`).
`tools/b43_boot.sh` then loads `modinfo -n b43` when it is under extra/, else the hand-built per-kernel module.
After this, `nixos-rebuild switch --upgrade` rebuilds the module for the new kernel automatically; no
more `ConditionKernelVersion` pin needed (see notes/114, already dropped).
Remaining caveat: the module is built from the working tree, so uncommitted edits to b43-src are included
only after a rebuild; a build failure on a new kernel (API change) fails the whole rebuild loudly, which is intended.
