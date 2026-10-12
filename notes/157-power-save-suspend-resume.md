# notes/157: power save and suspend/resume (2026-10-12)

Build 6ae8c0d defaults (5 GHz, VHT80, two streams), boot-service arguments, no extra flags.

## Power save
`iw dev wlp3s0b1 set power_save on` -> `command failed: Operation not supported (-95)`: the driver does not advertise
power save support (mac80211 never sets PS for it), the radio stays on. Fine for now (battery cost only). Left as is.
Pings during the three runs lost 11 % and 46 % in two windows; both coincide with wpa_supplicant's roam to the 2.4 GHz BSS and back
(17 s apart, seen in dmesg), the known NM/bgscan behaviour, not the driver.

## Suspend/resume (`rtcwake -m mem`, 45 s then two cycles of 30 s, b43 + USB stick both associated)
- Suspend: b43 deauthenticates, powers the radio down; dmesg shows a full radio init/rfkill dance, no errors.
- Resume: firmware reloaded (832.127), chip and radio re-initialised, PHY tables rewritten, DMA rings recreated; b43 reassociated within
  seconds in all three cycles (2.4 GHz BSS in two of them, 5 GHz VHT80 in the others, as NM chose), the stick too (some seconds later).
- After cycle 1: up 76, down 55-64 Mbit/s on 5 GHz VHT80 (MCS 5, 2 streams), no MAC suspend failures, no errors.
No systemd-sleep hook needed.
