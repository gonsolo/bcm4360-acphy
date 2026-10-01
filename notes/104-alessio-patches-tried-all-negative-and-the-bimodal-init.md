# 104 - Alessio's b43-ac-wip patches tried on the failure: all negative

Continuation of notes/103. Alessio Ferri's repo (`~/src/b43-ac-wip`, a patch
series 0001-0021 against the kernel's b43/bcma) was read for anything that
explains the `PHY transmission error` -> `MAC suspend failed` chain. Every
test below is the usual fresh-reload + connect A/B (`ab_reload_test.sh`, logs in
`test-logs/ab_reload_*.log`). Baseline on 7.2.7: ~30-40 % connect, 4-16 suspend
failures per attempt.

| idea (source) | result |
|---|---|
| TX FIFO geometry (patch 0019) | already present and identical in `b43_ac_fifo_init()` (default on) |
| read back the object memory address after every write (0020) | 3/8 connected, 4-15 failures: no change |
| MAC setup before PHY init + TSF fraction 0x6614b, power-up delay 1500 us (0019) | 1/8, 7-15 failures: no change |
| passive-only scanning (no probe requests) | 2/8, still 7-12 failures; auth frames alone give PHY TX errors |
| force the CRS min-power threshold low byte to 68 / 120 (docs/crs-min-power.md) | 1/6 and 0/3; `phydebug` stays 0x5/0x45: that threshold does not govern the stuck CRS |
| suspend retry: re-enable MAC, wait, suspend again (x2) | 1/8, recovered=0 (notes/103) |
| PMU PLL / resources (patch 0007) | PMU state is byte-identical at every init (`pll2=0x0c31 pll3=0x100e` already the stock values, `maxres=0x1ff`, `minres=0x13b`); forcing `maxres=0x7ff`: 3/6, no clear change |

Only the read-only PMU dump (`b43_ac_pmu_dump()`) and the test switch
`ac_pmu_maxres` stayed in `main.c`; the other experiments were removed.

## What the evidence says now
- notes/58: in the failing state `phydebug=0x5` (CRS|TXF): the ucode is
  mid-TX, the PHY holds carrier sense, the ucode never answers suspend.
- notes/57: a fresh init is either *good* (zero failures for a long time,
  association works) or *bad* (failures until the next re-init). That is a
  per-init coin flip, so the notes/103 bisect (one init per boot) mostly
  measured that coin flip, which is why a no-op change seemed to flip it.
- PMU, DMA placement, CPU count, ASPM, IOMMU, mitigations, config: all
  identical or ruled out. The random element is inside the PHY/radio
  initialisation (analog state set up by the vendor-state replay), not the host.

## Next
- Real cold start (notes/58 idea, never done): power off 30+ min, boot, load,
  compare the good/bad rate.
- Send Alessio the wl trace + the facts above (his PHY decode is 99.7 % on the
  cold bring-up; ours replays captured state).
- PSM PC of the halted ucode vs the d11emu disassembly (notes/12, 66).

## Later the same day (2026-10-01): cold boot, snapshots, more negatives
- Real cold boot (powered off overnight): first autoload bad (12 suspend failures in the
  first minute), 2/8 fresh reloads connected: same rate as warm. Chip state left over from
  earlier boots is not the factor (notes/60 already recorded a 24 h cold boot failing too).
- `PSM_PHY_HDR` (0x492) paired with the PHY force clock as the stock driver does
  (b43-ac-wip bd6d687, `ac_psm_hdr`): 1/8, no change (reverted).
- `tools/init_snapshot_test.sh`: 50 fresh inits, snapshot after load (PHY/radio/MAC/SHM) and
  after the connect attempt, label by outcome. Outcomes: 9 good (connected, <=2 failures,
  18 %), 8 connected with 3-7 failures, the rest never connected. No static PHY/radio
  register separates good from bad right after load (only timers/counters, unique per run).
  The post-connect radio snapshots separate them, but that only shows which channel/state
  the PHY is in (connected vs scanning): circular, not a cause.
- Correction: `b43info()` is rate-limited (`net_ratelimit()`), so "replayed vendor ch6
  state" lines go missing under heavy debug logging. Do not count them; the replay does run
  on every switch to channel 6. NetworkManager/wpa_supplicant also cycle the interface
  (Adding/Removing Interface, software_rfkill, switch_channel(1) re-inits) several times
  right after load.
- d11-emu treats NAP as a no-op (no wake semantics), so it cannot say what wakes the PSM.
- Standing picture: the failure is a runtime event (ucode in NAP at PC 0x000F, TX posted,
  no timely wake - notes/60), not a difference in init state.
