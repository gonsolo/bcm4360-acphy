# Status 2026-09-29 (part 19): second bisect boot reached graphical
login but had no keyboard/mouse - fixed the input driver chain and
switched to a text console for extra margin

Direct continuation of notes/94, same day. The VFAT fix worked - the
second bisect attempt reached GDM (graphical login), a real step
forward - but the user reported no mouse and Enter not registering at
the login prompt, so they had to reboot again. No lasting harm, same
as before (one-shot mechanism, persistent default untouched).

## Diagnosis: same class of bug again, one layer up the stack

`journalctl -b -1` for that boot showed no explicit errors for input -
because nothing ever *tried* to load the drivers (they're all `=m`,
and this kernel has no initrd or module-loading mechanism beyond
`load.sh`'s hand-written, WiFi-only `insmod` list). Checked the
*working* 7.2.7 system's actual `lsmod` for what the real input chain
is on this hardware (MacBookAir6,1's keyboard+trackpad are a combined
Apple SPI device, not USB or PS/2 - the earlier "Failed to find module
'atkbd'" line in the journal, seen on both failed boots, is a red
herring, that's the generic PS/2 keyboard driver, irrelevant on this
hardware):

```
spi_pxa2xx_core/pci/platform -> applespi -> hid, hid_apple, hid_generic
                                          -> led_class (LEDs the driver exports)
usbhid, xhci_hcd/xhci_pci     -> hid, hid_generic (any USB-attached HID device)
mousedev, input_leds           (input-core sysfs/LED glue)
```

## Fix, with a real Kconfig-dependency gotcha along the way

Flipped the whole chain to builtin
(`SPI_PXA2XX`/`SPI_PXA2XX_PCI`/`KEYBOARD_APPLESPI`/`LEDS_CLASS`/`HID`/
`HID_APPLE`/`HID_GENERIC`/`USB_HID`/`USB_XHCI_HCD`/`USB_XHCI_PCI`/
`INPUT_MOUSEDEV`/`INPUT_LEDS`/`INPUT_EVDEV`). **First pass didn't
stick**: `KEYBOARD_APPLESPI`, `INPUT_LEDS`, and (added mid-fix)
`HID_APPLE` all silently reverted to `=m` after `make olddefconfig` -
all three `depends on LEDS_CLASS`, which was itself still `=m` at that
point. `olddefconfig` doesn't auto-upgrade an existing `=m` to `=y`
just because a dependency *later* becomes satisfiable in the same run
- it only accepts an explicit `=y` if the dependency is *already*
satisfied when it processes that line. Fixed by flipping `LEDS_CLASS`
first, rerunning `olddefconfig`, *then* re-applying `=y` to the three
that got held back, and rerunning once more - this time all three
stuck (`grep`-verified, not just trusted). Rebuilt clean (`bzImage`
#4, no errors), `b43-src` rebuilt against it (binary-identical again -
none of this touches b43-relevant code), repackaged and re-staged the
same way as notes/94.

## Extra margin added: boot to a text console, not graphical

Rather than fully trust that the HID/input fix covers *everything*
GDM/GNOME might need (framebuffer/DRM drivers, audio, etc. - all things
this minimal config was never meant to carry), added
`systemd.unit=multi-user.target` to the boot entry's kernel command
line. This skips `graphical.target` (and therefore GDM) entirely and
lands on a plain text console instead - removes any dependency on a
working mouse at all, and narrows what "working" needs to mean down to
just "keyboard input at a TTY," which is both simpler to verify and
sufficient for what this bisect actually needs (running `load.sh`,
`connect_test.sh`, reading `dmesg`).

`tools/bisect_build.sh` updated: the full required-builtin list
(storage/root-fs, boot-fs, input - three separate incidents now,
notes/93/94/95), a note about the Kconfig auto-upgrade gotcha for
future `.config` regeneration, and the boot entry template itself now
includes `systemd.unit=multi-user.target` by default for every future
bisect step.

## Current state at session end

Corrected `bzImage` (#4) staged, one-shot re-armed. Local
`~/src/linux/.config` now carries all three fix categories and will
be reused as-is for every remaining bisect step. Ready for the user to
retry the reboot - this is the third attempt at the *same* commit
(`60b8d4d49281`); the actual bisect test itself (the point of all this)
still hasn't run once yet.

## Next steps

Unchanged in substance from notes/93/94: reboot into the (now further-
corrected) one-shot entry, this time landing on a text console with
(expected) working keyboard input, log in, run
`bash ~/bcm4360-acphy/bisect-boot/load.sh`, confirm `wlp3s0b1` comes up,
run the `connect_test.sh`/`suspendtiming` pass/fail check, record `git
bisect good`/`bad`, then `tools/bisect_build.sh` for the next candidate.
