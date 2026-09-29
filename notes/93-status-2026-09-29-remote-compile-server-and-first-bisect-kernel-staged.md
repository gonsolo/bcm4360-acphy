# Status 2026-09-29 (part 17): remote compile server set up, first
`git bisect` kernel built and staged as a one-shot boot

Direct continuation of notes/92. notes/92 concluded that further
localization of the connect-time `b43_mac_suspend` regression needs
either bus-level tracing (not available) or a `git bisect` in
`~/src/linux` - now well-scoped (fast pass/fail test: `suspendtiming`/
`MAC suspend failed` presence) but expensive (66,387 commits between
`v6.18` and `v7.2`, ~16-17 build+boot+test cycles). User asked to set up
a compile server first, using their own workstation on the same LAN.

## Remote builder: pampelmuse (192.168.0.236)

Found it by ARP-sweeping the local `/24` (`ip neigh`, then `avahi-resolve`/
`getent hosts`/an SSH-banner probe to disambiguate real hosts from
phones/tablets) and confirming with the user. Specs: Arch Linux, kernel
7.2.7-arch1-1, 24 cores, 62G RAM, x86_64-linux, Nix 2.35.2 already
installed as a proper multi-user daemon (`nix-daemon` active,
`nix-users` group).

Setup:
- Generated a dedicated SSH keypair (`~/.ssh/id_ed25519_builder`), not
  reusing any existing key. Installed via `ssh-copy-id` (interactive
  password auth) to `gonsolo@pampelmuse`.
- Wired into NixOS as a Nix remote builder:
  `nix.distributedBuilds = true` + `nix.buildMachines` in
  `/etc/nixos/configuration.nix` (16 max jobs, `x86_64-linux`,
  `speedFactor = 2`). Applied with `nixos-rebuild switch` (no reboot -
  a new generation, 17, was created; the boot-loader default follows
  it automatically, matching normal NixOS behavior). Previous config
  backed up at `/etc/nixos/configuration.nix.pre-builder-backup`.
- Host key trust: had to add pampelmuse's key to **root's**
  `known_hosts` specifically (`nix-daemon` runs as root and does its
  own SSH connections, separate from the user's own `~/.ssh/known_hosts`
  used when testing manually) - the first distributed-build attempt
  failed with "Host key verification failed" until this was fixed.
- **Verified working**: a real, guaranteed-uncached test derivation
  (`--max-jobs 0`, forcing no local build) built successfully on
  pampelmuse and copied back automatically.

**For the actual bisect loop**, ended up **not** routing individual
kernel builds through Nix's distributed-build machinery - wrapping an
arbitrary, frequently-changing git-bisect checkout as a reproducible Nix
derivation fights Nix's content-addressed model more than it helps for
this specific, inherently-iterative workflow. Instead: plain `rsync`/
`ssh` to a raw `~/src/linux` clone the user made directly on
pampelmuse (sidestepping an accidentally very slow initial transfer
attempt - see below), building with pampelmuse's native toolchain
(`gcc`/`make`/`bc`/`flex`/`bison`/`elfutils`/`pahole`, all already
present). The Nix remote-builder config itself remains in place as
general system infrastructure, just unused by this specific pipeline.

## Two real problems hit and fixed while wiring this up

1. **Initial `rsync` of the kernel tree was extremely slow** (tens of
   minutes for tens of MB) - turned out to be routing over `wlp3s0b1`
   (the very b43 link under investigation, lower routing metric than
   the USB backup stick) *and*, separately, an early attempt
   accidentally included the 3.7G `.git` directory. Fixed by having the
   user clone directly on pampelmuse instead (no transfer needed for
   the big one-time clone at all), and by explicitly binding later
   transfers to the USB stick interface (`-o BindAddress=192.168.0.98`)
   for anything that does need to cross the link. User also flagged
   that tarring+`xz`-compressing packages before transfer is worth
   doing even over the fast path - adopted in `tools/bisect_build.sh`.
2. **Backgrounded remote builds kept dying the moment the SSH session
   closed** - tried `nohup ... & disown`, `setsid`, and `screen -dmS`,
   all killed anyway. Root cause: pampelmuse has `systemd-logind`'s
   `KillUserProcesses` active and `Linger=no`, and this project has no
   root access there to fix it properly (`loginctl enable-linger`).
   **Fix**: don't detach on the remote side at all - run the SSH build
   command directly via this session's own background-job mechanism
   (`run_in_background: true`), which keeps the actual TCP/SSH session
   open for the build's full duration instead of trying to survive its
   closure. Reliable across both builds attempted this session.

## First bisect step: built, packaged, and staged

`git bisect start` / `bad v7.2` / `good v6.18` in `~/src/linux`
(66,387 commits, ~15 steps predicted). First midpoint:
`60b8d4d492815eed6d52646998167bc60dd94e5a` ("Merge tag
'x86_sev_for_v7.1_rc1'..."), 2026-04-14.

**Minimal config, per the user's suggestion**: `zcat /proc/config.gz`
(the running system's actual config) as a base, `make olddefconfig`
against the target commit's Kconfig, then `make LSMOD=<current lsmod>
localmodconfig` to trim to only what's actually loaded on this hardware
- 9899 enabled options down to 2161. Spot-checked the result for every
subsystem this project's testing actually needs (bcma, mac80211,
cfg80211, PCI, AHCI, HID, the Apple keyboard driver, EFI stub) - all
present. **One deliberate deviation from pure `localmodconfig`
output**: flipped `SCSI`/`BLK_DEV_SD`/`ATA`/`SATA_AHCI`/`EXT4_FS` from
`=m` to `=y` (builtin) specifically so the bisect kernel can mount root
**without needing a matching initrd** - reusing NixOS's own generated
initrd wasn't viable (it bundles kernel-version-specific module paths
that wouldn't match a raw mainline build's own version string).

**Boot mechanism**: no NixOS generation involved at all for the bisect
kernel itself - just a raw `bzImage` copied to
`/boot/EFI/nixos/bisect-<sha>-bzImage.efi`, a hand-written
`/boot/loader/entries/nixos-bisect.conf` reusing the **current default
NixOS generation's own `init=` path** (userspace/systemd doesn't care
which kernel started it) plus an explicit `root=/dev/sda3
rootfstype=ext4` (replacing NixOS's `root=fstab` initrd-only
mechanism), and `bootctl set-oneshot nixos-bisect.conf` - **the
persistent default boot entry is never touched**, so any boot after
this one (successful or not) returns to normal daily-use 7.2.7
automatically, matching the project's standing "no destructive boot
changes" caution.

b43-src (this project's instrumented driver, unchanged from notes/91)
built against the bisect kernel on pampelmuse too (`KDIR=~/src/linux`
pointed at the prepared tree). Stock dependency modules
(`bcma`/`mac80211`/`cfg80211`/`ssb`/`cordic`/`led-class`/`rfkill`/
`libarc4`) collected from the same build and staged at
`~/bcm4360-acphy/bisect-boot/` alongside a `load.sh` that insmods them
in dependency order (no `depmod`/module-version database exists for
this out-of-tree kernel, so ordered manual `insmod` instead of
`modprobe`) and re-points `firmware_class`'s search path at this
project's own `firmware/` dir (same override `b43_live.sh swap` uses,
needed since this kernel isn't part of any NixOS generation's
`hardware.firmware`).

`tools/bisect_build.sh` captures the whole per-step pipeline (sync
checkout + config, build, build b43-src, package with `tar`+`xz`,
pull over the USB-stick interface, stage the boot entry) as a single
reusable script for the remaining ~15 steps, incorporating every fix
from this session.

## Next steps for a future session, in order

1. **User reboots** into the staged `nixos-bisect` one-shot entry
   (not done yet as of this note), runs
   `bash ~/bcm4360-acphy/bisect-boot/load.sh`, confirms `wlp3s0b1`
   appears and NetworkManager can see/use the existing "Vodafone-2A84"
   profile.
2. Run the pass/fail test (`connect_test.sh` + check for
   `MAC suspend failed`/`suspendtiming: wait=` in `dmesg`) - the
   `optiming` instrumentation is already compiled into this b43.ko
   build (from notes/91), so it's available immediately without
   further changes.
3. `cd ~/src/linux && git bisect good` or `git bisect bad`, then
   `tools/bisect_build.sh` again for the next candidate. Repeat.
4. Once the bisect converges on a single first-bad commit: read it,
   understand what it actually changed, and only then decide whether a
   real fix belongs in the kernel (upstream-reportable) or a
   driver-side workaround in `b43-src`.

## Current state at session end

New files: `tools/bisect_build.sh` (the reusable per-step pipeline),
`bisect-boot/` (gitignored, current candidate's staged kernel+modules).
`.gitignore` updated. `/etc/nixos/configuration.nix` gained the
`nix.distributedBuilds`/`nix.buildMachines` block (backup at
`configuration.nix.pre-builder-backup`). `~/.ssh/id_ed25519_builder`
generated (private, not committed anywhere). One-shot boot staged
(`nixos-bisect.conf`, commit `60b8d4d49281`); persistent default
untouched. Current boot still 7.2.7, daily-use connection healthy,
`netwatch`/`b43-autorecover` active - the reboot to actually test the
first bisect candidate is pending, user-initiated as always.
