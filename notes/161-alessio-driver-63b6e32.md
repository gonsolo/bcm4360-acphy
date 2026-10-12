# notes/161: Alessio's b43-ac-wip at 63b6e32 on this MacBookAir6,1 (2026-10-12)

He asked for tests of the tree up to 63b6e32 ("docs: VHT and hardware CCMP on the DSL-3580L"); later commits (AQM, A-MPDU TX) are untested by him.
Built with `tools/build_alessio_driver.sh` (patches 0001-0003 of that commit on v7.2, plain build, no forensics; `FORENSICS=1` keeps the old
per-register logging), loaded with `tools/try_alessio_driver.sh` after `tools/ale_logging_setup.sh` (netconsole to pampelmuse, panic sysctls;
restored afterwards), our b43-autorecover stopped meanwhile. Kernel 7.2.9, router on automatic channel, AP 5 GHz channel 100, 80 MHz.

- Loads without a hang: "Broadcom 4360 WLAN found (core revision 42)", PHY AC rev 1, radio 2069 rev 4, firmware 832.127, bcma with the PMU PLL pre-write
  messages (his bcma patch). The interface uses the card's own MAC 84:38:35:4d:18:6e (ours: 00:01:00:00:84:38), so DHCP gives another address.
- 5 GHz: NM autoconnects to channel 100, signal -54 dBm, VHT 80 MHz 2 streams, rx MCS 8-9, tx MCS 8 (short GI).
- Throughput, host route over the interface, 6 s runs: upload 37.4, 44.4, 42.6 Mbit/s (retries ~5 %, 0 failed); download 2.45, 2.45, 2.62 Mbit/s.
  Same minutes, our driver and the USB stick: 40-65 down. No underrun message, `rx drop misc` 270 of 16.9k packets.
- 2.4 GHz: not usable. The ucode logs "PHY transmission error; first TX fault saved by the ucode: ... phyctl 00c4 00b8" and NM's association on the
  2.4 GHz BSS times out ("association took too long"); the stack falls back to 5 GHz.
- Not tested here: hardware CCMP (he runs it on his MIPS router), A-MPDU (later commits).
- Pitfall: tests that bind a source address must use the interface's current address; with his MAC the old 192.168.0.119 route failed and the first
  "results" went over the USB stick instead.
