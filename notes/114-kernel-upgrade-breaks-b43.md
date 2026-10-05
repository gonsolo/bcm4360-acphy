# 114: `nixos-rebuild switch --upgrade` moved the kernel 7.2.7 -> 7.2.9 and broke b43

Symptom (2026-10-05): the newest boot entry (generation 21, kernel 7.2.9) had no b43 wifi.
Cause: `b43.ko` is out of tree and built for one kernel (vermagic), and both b43 services had
`ConditionKernelVersion = "7.2.7"` in /etc/nixos/configuration.nix, so on 7.2.9 they were skipped
(stock b43/bcma are blacklisted, so the card had no driver at all).

Fix (plan item 1c, cheap version):
- `tools/b43_boot.sh` loads `b43-src-builds/b43-$(uname -r).ko` if it exists, else `b43-src/b43.ko`.
- `tools/build_b43_for_kernel.sh <linux-X.Y.Z-dev store path>` builds a per-kernel module from a clean
  `git archive` + the working-tree sources. The 7.2.9 dev output was missing locally; it is in
  cache.nixos.org (`nix copy --from https://cache.nixos.org <path>`; it pulls rustc, ~minutes).
  Its path: `nix-store -q --outputs /nix/store/<hash>-linux-7.2.9.drv`.
- `sudo tools/unpin_b43_kernel.sh` removes the `ConditionKernelVersion` pins (backup + `nixos-rebuild boot`).

Not done: a real Nix kernel-module derivation built per `boot.kernelPackages` (auto rebuild on upgrade),
and a guard so an upgrade without a matching module fails loudly instead of leaving the card driverless.
Do not run `nixos-rebuild switch --upgrade` without building the module for the new kernel first.
