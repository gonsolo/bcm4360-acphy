# Status 2026-09-29 (part 23): sixth bisect boot - graphical login
worked. No cursor and nothing new ever rendered (search results,
windows) because the real Intel GPU driver was never loaded - the
kernel fell back to the generic `simpledrm` driver, which has no
hardware cursor plane and no acceleration. Fixed (`DRM_I915` builtin).

Direct continuation of notes/98, same day. Pivoting back to
`graphical.target` (per the user's explicit request) worked in the
important sense: **GDM login succeeded**, GNOME Shell started, and the
Activities overview/search UI was interactive enough to type into. Two
remaining symptoms: no mouse cursor visible, and typing into the app
search produced no results at all (not "the terminal failed to launch"
- literally nothing appeared in the chooser, a clarification the user
gave that turned out to matter).

## Root cause, found directly in the journal

```
gdm[515]: Gdm: It appears that your system does not have a primary GPU! Proceeding with any GPU
gnome-shell[579]: Added device '/dev/dri/card0' (simpledrm) using atomic mode setting.
gnome-shell[579]: Failed to initialize accelerated iGPU/dGPU framebuffer sharing: Not hardware accelerated
gnome-shell[579]: Created gbm renderer for '/dev/dri/card0'
gnome-shell[761]: Xwayland glamor: GBM Wayland interfaces not available
gnome-shell[761]: Failed to initialize glamor, falling back to sw
```

**`simpledrm`** is the kernel's generic, EFI-framebuffer-backed DRM
fallback driver - used only when no real GPU driver claims the device.
It provides a single static framebuffer with no hardware cursor plane
and no acceleration. Checked `.config`:
`CONFIG_DRM_I915=m` - the real Intel GPU driver was present in the
build but, same as every previous fix this thread (notes/94/95),
**a module with nothing to load it**, since this kernel has no initrd
and `load.sh` only ever handled the WiFi driver chain.

This precisely explains both symptoms, and the user's clarification
that *nothing* appeared in the search results (not a launch failure)
sharpens it further: `simpledrm` can display the one static surface
GNOME Shell composites at startup (hence login and the initial desktop
being visible and even accepting keyboard input), but genuinely cannot
composite anything added *afterward* - a hardware cursor sprite,
dynamically-appearing search result icons, or a new application
window. It's not that any specific thing failed to launch; it's that
the rendering pipeline can only show what was already there.

## Fix

`sed`'d `CONFIG_DRM_I915=m` to `=y` in the local template `.config`,
`olddefconfig` (stuck at `=y` on the first pass this time, no repeat of
notes/95's dependency-ordering gotcha), rebuilt on pampelmuse - `i915`
is a large driver, this build took noticeably longer than the previous
incremental fixes but still completed cleanly (`bzImage` #5, 2 "error"
grep hits, both benign filenames: `i915_gpu_error.o`,
`arch/x86/boot/compressed/error.o`). `b43-src` rebuilt against it
(binary-identical again). Repackaged and re-staged.

## Unrelated hiccup: one transfer attempt hung on the USB-stick interface

Pulling the (larger, ~30M) package with `-o BindAddress=192.168.0.98`
(the usual "avoid the buggy b43 link" precaution from notes/93) hung
indefinitely after the TCP handshake - `ping` to pampelmuse over the
same path was fine (if a bit jittery), so this looks like a transient,
specific glitch on the stick's connection rather than anything
structural. Retried without the bind constraint (default route, which
happens to be the b43 link) and it completed normally and quickly for
this size. Not investigated further - noted in case it recurs, but a
single anomalous hang isn't enough to draw a conclusion from.

## Current state at session end

Corrected `bzImage` (#5) staged, one-shot re-armed, same commit
(`60b8d4d49281`), same graphical-default-plus-fallbacks kernel command
line as notes/98 (unchanged - this was a `.config`/rebuild fix, not a
boot-parameter one). `tools/bisect_build.sh`'s required-builtin list
extended with `DRM_I915`. Sixth attempt at the same commit about to
begin; still zero actual bisect test runs so far, but every boot
environment problem hit has been a real, fixable gap in the minimal
config or boot parameters, not a dead end - each attempt has gotten
further than the last (emergency shell -> no input -> no login prompt
-> login works but shell dies -> full graphical login with a rendering
gap). This is very plausibly the last such gap: storage, boot
partition, input, login mechanism, and now graphics have each been
addressed in turn, and a normal desktop session shouldn't need much
else.

## Next steps

Reboot into the corrected entry. If GDM/GNOME Shell now renders
normally (cursor visible, search results appear, a terminal opens):
proceed directly with the actual bisect test from a real terminal -
`bash ~/bcm4360-acphy/bisect-boot/load.sh`, confirm `wlp3s0b1`, run
`connect_test.sh`/check `dmesg` for `suspendtiming`/`MAC suspend
failed`, record `git bisect good`/`bad`, then `tools/bisect_build.sh`
for the next candidate - finally moving the actual investigation
forward after a long but genuinely productive boot-environment
debugging detour. The still-unresolved `Ctrl+Alt+F9`/tty1-shell-exit
mysteries from notes/97/98 become moot if graphical login now works
fully; they remain open curiosities, not blockers, if so.
