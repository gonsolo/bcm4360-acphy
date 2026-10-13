# 164: resume after a 2 h 39 min suspend: chip dead, reload did not help

User report: after suspend there was no b43 module and no network.

## What the journal of that boot (7.2.10, lid close 16:25:35, lid open 19:04:56) shows
- Resume failed before b43 ran: bcma `HT force timeout`, `PLL enable timeout`, then b43 `Microcode not responding`, mac80211
  `Hardware became unavailable upon resume` (wiphy_resume -19, WARNING at ieee80211_reconfig).
- `b43-resume.service` -> `b43-ac-load.service`: try 1 `insmod: File exists` (module still loaded) -> reload; every later init died with
  `Microcode not responding`, wpa_supplicant `No such device`, until the user rebooted.
- The chip is alive on the bus (chip id, PHY type read fine), but HT clock / PLL never start. No PCIe/AER/ASPM errors.
- `b43_load_until_connected.sh` ended with "no connect attempt and no TX errors; keeping this init": it only counted PHY TX errors, MAC suspend
  failures and auth timeouts, so a dead chip looked "quiet".
- Same day, 7.2.9, lid-close sleeps of 1 h 43 and 1 h 25 min resumed cleanly (0 HT force timeouts), also with the hook reloading b43.
  notes/126 and 157 ("no hook needed", 6 + 3 cycles) only slept 20-90 s.
- Differences: kernel 7.2.10 vs 7.2.9, sleep 2 h 39 vs <= 1 h 43. Hypothesis (unproven): after a long S3 the card loses power and comes
  back without the firmware init the Apple EFI does at boot; module reloads cannot redo that. Kernel change is the other candidate.

## Could not reproduce here
- PCI remove / rescan with b43 unloaded: root port 1c.2 goes to D3hot only (no ACPI power resources, no D3cold), card keeps power; b43 loads fine after.
- `rtcwake -m mem` with the lid open: wakes after ~8 s whatever the alarm (90 s, 9600 s), with XHC1 and all root ports' PME wake disabled; GPE 0x70
  (no AML handler in the DSDT) fires once per suspend. Lid-close suspends held (the failing and the two good ones were lid suspends).
  A real long-sleep test needs the lid closed.

## Fix in the recovery path (tested with mocks and on the healthy card)
- `tools/b43_load_until_connected.sh`: `Microcode not responding` / `HT force timeout` / `PLL enable timeout` since the try's marker count as
  evidence `dead=`: the try is bad at once, and before the next try the chip is reset with `tools/b43_pci_reset.sh` (unbind, PCI bus reset through the
  root port via the `reset` attribute, fallback remove + rescan). Tests: `bash tools/test_b43_load_until_connected.sh` (12 pass, two new).
- Live on the healthy card: `rmmod b43; b43_pci_reset.sh` ("reset", device present, no driver) then b43-ac-load.service: connected, clean, first try.
- Whether a bus reset revives a really dead chip is not known until the failure is reproduced.

## Test pitfall
`ping -I wlp3s0b1` fails with both interfaces up on 192.168.0.0/24: tcpdump shows the echo reply arriving on b43, but the NixOS firewall
(`iptables -t mangle` chain `nixos-fw-rpfilter`, strict rpfilter) drops it because the better route to 192.168.0.1 is the stick. Use `arping -I` or tcpdump.
