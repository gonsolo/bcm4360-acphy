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

## Second round: our DMA settings on his tree, and where his download is lost
`ALE_DMA=1 tools/build_alessio_driver.sh` adds our DMA findings (TX control |= 0x03780040, RX control |= 0x036c0000, intrcvlazy0 = 1 << 24) to his
tree (his DMA already has the "index registers hold bus addresses" part); `ALE_VARIANT=dma tools/try_alessio_driver.sh` loads that build.
- No change: download 2.27-3.15 Mbit/s, upload 33-47 (rate MCS 8-9, no failed frames), same PHY TX error lines while scanning 2.4 GHz.
- Ping flood through his interface: 0 % loss (300 packets at 20 ms, 100 packets of 1400 bytes). UDP download from the LAN host:
  20 Mbit/s offered -> 11.3 received (43 % lost); 60 Mbit/s offered -> 12.2 received (76 % lost). So the receive path loses frames above about
  1000 packets per second; TCP collapses to 2-3 Mbit/s on top of that. No "underrun" or other RX message in the log (netconsole capture).
- His tree does not take the "DMA bits" fix, so his slow download is something else; candidates for him: RX interrupt/ring handling under load,
  the AC RX header handling (drops counted in `rx drop misc`), A-MPDU RX reordering (the session is accepted, the ucode deaggregates).

## chipcontrol bit 3 in his tree (checked, 2026-10-12)
`b43_phy_ac_fem2_sub1_setup()` in his phy_ac.c already does `bcma_cc_set32(..., BCMA_CC_CHIPCTL, 0x00000008)` (from the MacBookAir6,1 capture), and sets
bit 24 (0x01000000) for boardflags with BFL_BTCOEXIST (that is where our dump's `0x01000008` comes from). Test with chipcontrol cleared to 0 before loading
his driver: his driver sets what it needs; forced NSS 1 / NSS 2 upload: 1:5 41.8, 2:0 24.8, 2:5 46.5 Mbit/s, 2-3 % retries, 0-2 failed. Facts on this
bit that his tree may not state: it persists across module reloads (only a cold boot clears it), and without it two-stream frames are never acknowledged
(one-stream is fine), so a test made after another driver ran in the same boot can hide a missing bit.
