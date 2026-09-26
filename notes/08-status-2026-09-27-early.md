# Status 2026-09-27 (early morning, AP-beacon test)

## AP-beacon test: done

Ported wl's rev-40+ (core_rev > 0x27) beacon-template handling, decompiled
from `wlc_bmac_write_hw_bcntemplates` / `FUN_00163582` / `FUN_001635f7` /
`wlc_beacon_phytxctl`:

- Template RAM base: slot0 = **0x200** (not legacy 0x68), slot1 = **0x480**
  (not legacy 0x468). Length registers (SHM 0x18/0x1a) and the valid-bit
  register (MMIO MACCMD 0x124, bits 0/1) are unchanged from legacy b43 —
  only the RAM base moves. (This confirms an offset I'd stated earlier in
  the session from code analysis, not a captured trace — wl was never
  traced operating as an AP, so there's no trace-based cross-check for it,
  only this decompiled-code derivation, now applied and tested live.)
- PHY control: for core_rev > 0x27, the beacon slot's PhyTxControlWord_0/1/2
  live at **SHM 0xcc/0xce/0xd0**, computed the same way as a normal AC TX
  descriptor rate entry (CCK/OFDM bit, core mask, PLCP rate-table index) —
  not the legacy `BEACPHYCTL` word at SHM 0x54 b43 was writing before.

Patched `b43_upload_beacon0/1` and `b43_write_beacon_template` in main.c
accordingly (AC-PHY branch only; legacy chips unaffected).

## Result: rules out SIFS timing as the explanation

With hostapd running an open test AP (`b43-beacon-test`, channel 6,
`tools/beacontest.conf`) for ~8 s: ucode counted **86 beacon-frame attempts,
80 PHY transmission errors** (93%) — essentially the same failure rate as
the firmware's ACKs (~94%, from the probe-response test the previous
session). An independent scan from the USB stick found no trace of the
test SSID (consistent, though the scan ran after hostapd's bounding
`timeout` had already fired, so a handful of clean beacons in the 6-beacon
gap could have been missed).

**This is the important negative result**: a beacon has no SIFS deadline —
it's scheduled by a TBTT timer with ample lead time, nothing like an ACK's
10 us turnaround. Yet it fails at nearly the identical rate. So the
failure is not specifically about *urgency* (the RX->TX turnaround
hypothesis from notes/07). It's about *any* firmware/ucode-scheduled
autonomous transmission — the mechanism the D11 core/ucode uses to send a
frame from template RAM + a fixed SHM PhyTxControlWord, as opposed to a
frame arriving via the normal host TX-DMA descriptor path (which is 100%
clean, established extensively via the TX quality matrix and the sub-band
sweep). Something in how that autonomous path hands the frame to the PHY
is broken or misconfigured, independent of timing pressure.

## Next ideas (neither attempted)

- wl definitely sends ACKs in plain STA mode too (mandatory 802.11
  behavior), and we *do* have STA-mode wl traces. If there's a register or
  table write specific to enabling the autonomous-TX path that we haven't
  found, it should be in there — worth another structured diff pass
  specifically looking for anything gating "ucode may originate its own
  TX" rather than anything about content/timing (which have both been
  checked repeatedly already).
- A byte-level trace of exactly what the D11 core's own internal TX state
  machine registers show in the instant a PHY transmission error fires
  (vs. a clean host TX) might localize this to a specific stage. We have
  `phydump`/`macdump`/`state_snapshot.sh` for live snapshots but haven't
  tried snapshotting *immediately after* triggering one specific failure
  (single beacon, single-shot, rather than free-running).

## Housekeeping

- `tools/hostapd`, `tools/python3`: nix-rooted, gitignored (like `iw`,
  `tcpdump`).
- `tools/beacontest.conf`: the minimal open-AP config used above.
- `test-logs/hostapd-beacontest-20260927.log`: the run's hostapd -dd log.
