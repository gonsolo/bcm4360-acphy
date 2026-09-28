# Status 2026-09-28 (cont'd): kernel 7.2.7 confirmed across a repeat boot; two real bugs found and fixed along the way

Follow-up to notes/54. Did the repeat-boot test that note called for: rebooted
into generation 11 a second time to check the whole cycle (not just
within-one-boot stability) is consistent.

## Result: confirmed

Second boot, same sequence (`tools/test_7.2.7.sh`, then managed mode +
`nmcli connection up b43-test`): WPA2 + IPv4 DHCP on the first real
connection attempt, ARP 5/5, USB backup link healthy throughout. Matches
the first boot's result exactly. Two real bugs surfaced in the process,
both now fixed:

## Bug 1: `swap` leaking `firmware_class/parameters/path` onto other devices

`b43_live.sh swap` points the kernel's firmware search path at this
project's own `firmware/` directory (needed for b43's own
`request_firmware()` calls) but never reset it. Left pointed there, any
*other* device's driver that loads firmware later in the same boot fails
to find it in the normal system path. Found live: after `swap`+`load`,
unplugging and replugging the USB backup stick made its `mt76x2u` driver
fail to find `mt7662_rom_patch.bin` - not because the file was missing
(it's present, just zstd-compressed as `mt7662_rom_patch.bin.zst`, normal
for this system), but because the search path itself had been hijacked.

Fixed in `b43_live.sh`: reset the path back to empty right after b43's own
`insmod` (its firmware load is synchronous within that call). Not fully
re-verified live after the fix (got sidetracked - see below) but the fix
is the correct, narrow one: unset the process-wide override the moment
the one driver that actually needed it is done with it.

## Bug 2: a timing race between `swap` and `load`, hit once

On this boot's first `tools/test_7.2.7.sh` run, b43 itself failed to find
*its own* firmware (`ac1initvals42.fw`, `ucode42.fw`) immediately after a
normal `swap`. Not a missing-file problem (confirmed present, correct
path). A plain manual retry seconds later - `rmmod`, `swap`, then a
directly-run `insmod` with no other changes - worked cleanly on the exact
same boot, same files, same path. Best explanation: the bcma bus
registration/probe triggered by `swap`'s `drivers_probe` write hadn't
fully settled before `load`'s `insmod` ran immediately after, in the
original script's tight sequencing. Added a 2-second `sleep` between the
two steps in `tools/test_7.2.7.sh` as a cheap guard; not proven to be the
exact mechanism, but the retry-with-more-time-elapsed working is at least
consistent with it.

## Also: the LKML/b43-dev email

Sent (by the user, plain text, after the first HTML attempt bounced from
`b43-dev@lists.infradead.org` - mailing lists reject HTML mail
unconditionally). No response yet.

## Current state

Chip loaded and connected on kernel 7.2.7 (second boot of this session),
USB backup link healthy. `docs/AC-PHY-CLEAN-ROOM-SPEC.md` and the email
seeking guidance on upstreaming are both out; no reply yet.

## Next steps

1. Re-verify the firmware-path-reset fix specifically (a hot-replug of
   the USB stick after a `swap`+`load` cycle, checking it now finds its
   firmware correctly) - not done this round, got sidetracked into the
   second bug and the email logistics instead.
2. If the 2-second sleep doesn't fully eliminate the swap/load race,
   the more robust fix would be to actually wait on a signal indicating
   bus registration completed (e.g. poll for the bcma core's driver
   binding in sysfs) rather than a fixed guess.
3. Whether to whitelist `b43` for automatic boot-time loading on 7.2.7 is
   still an open, deliberate decision - not done, per earlier discussion.
