# 165: Alessio's main c452fdd on this MacBookAir6,1: 2.4 GHz works, 5 GHz download fixed

Tree: aleferri/b43-ac-wip origin/main c452fdd (18 commits past 63b6e32), patches 0001-0003 on v7.2, plain build for 7.2.10
(`tools/build_alessio_driver.sh /nix/store/294g2688syzh1m82nizdrvgkmaiczr2k-linux-7.2.10-dev`), loaded with `tools/try_alessio_driver.sh` behind
netconsole + panic sysctls (restored afterwards); the stick stayed the default route. Router Vodafone-2A84: 2.4 GHz ch11 (:88), 5 GHz ch64 (:90).

## Results
- Loads, no hang. Card MAC 84:38:35:4d:18:6e (DHCP 192.168.0.115).
- **2.4 GHz**: associates and holds (-47..-52 dBm), 0 PHY transmission errors, RX works (10.4k frames, 3.6k beacons in 6 min; before: 0 frames), DHCP,
  ping 20/20 and 5 x 1400 B, 0 % loss. Throughput on a host route through the interface (iperf3): upload 3.0-3.4, download 5.1 Mbit/s;
  rates stay legacy (tx 54, rx 24 Mbit/s, no HT), tx retries about 5-25 %. Slow but alive.
- **5 GHz** (profile pinned to :90, reverted afterwards): VHT 80 MHz, 2 streams, MCS 4-9. upload 58.5, 58.6; **download 70.2, 70.5 Mbit/s**
  (63b6e32: 2.45). Counters afterwards: 235 failed of 128k TX (retries 6.8k), signal -73..-79 dBm.
- Observation, not reproduced on purpose: after the background scan of the first load (15 x "Switching to 2.4 GHz band: core restart", his new "a band
  change is a full init") arping to the router got no answer for minutes on 2.4 GHz while the station stayed associated; after a fresh load arping and
  ping worked at once. Candidate for him: state lost or not restored by the full init on a band change.

## Test pitfalls (iperf3)
- Daemonized `iperf3 -s -D` on pampelmuse: every test dies with "unable to create a new stream: Bad file descriptor". Run `nohup iperf3 -s &` in the foreground.
- iperf3 is only available through `nix-shell -p iperf3` on both machines. Host route: `ip route add 192.168.0.236/32 dev wlp3s0b1 src <b43 ip> metric 1`
  and `iperf3 -B <b43 ip>`; wait a few seconds between runs (a run right after another gets a reset).
- Grepping `wlp0s20u1:disconnected` also matches `p2p-dev-wlp0s20u1:disconnected`; it is not the stick.
