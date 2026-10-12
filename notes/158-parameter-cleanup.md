# notes/158: test parameters and diagnostics removed (2026-10-12)

Preparation for upstreaming. Behaviour is unchanged; each former parameter is now the constant its default was.

- `phy_ac.c` 3943 -> 1877 lines: the TX calibration drafts and their ten test flags (`ac_txcal_*`), wl op replays (`ac_replay` code,
  `phy_ac_replay.h`, `ac_win116`, `phy_ac_win116.h`, `ac_fr_*`), `ac_rfkick`, `ac_rfseq`, `ac_hostflags`, `ac_hostf1`, `ac_ackwatchdog`, the
  macstat/DMA/GPIO log (`ac_diag`), `ac_5g_ctr`, `ac_state_once`, `ac_init_state`, `ac_5g_coeff`, `ac_phyinit`, `ac_farrow`.
- Constants now: `ac_5ghz`, `ac_5g_80`, `ac_ht`, `ac_vht`, `ac_ampdu`, `ac_ampdu_rx`, `ac_phyreset`, `ac_fifo`, `ac_dmaburst` = on; `ac_nopllctl`,
  `ac_txs_sum`, `ac_irq_extra`, `ac_pmu_maxres`, `ac_httx`, `ac_txlifetime` = off (code removed); `ac_txcore` = core 0 (1 stream) / cores 0+1 (2 streams);
  `ac_ampdu_mpdus` = 4 (in the cache info), `ac_ampdu_requeue` = 4, `ac_selfheal` = 3, `ac_txpwrctl` = on (PHY 0x70 = 0xe500),
  `ac_txidx` = 20 (2.4 GHz gain index at a channel switch; with the hardware loop on it is the starting point, notes/138/140).
- `b43_mac_suspend()` is the stock function again (the 80 ms diagnostic variants, `suspend_ms`, `optiming_thresh_ms` and the timing code in
  `b43_op_config()` are gone; notes/82-92 stay as the record of that hunt).
- Still accepted so the boot service's command line loads, and ignored: `ac_replay`, `ac_por`; `dma32` and `nohwcrypt` are real.
- Debugfs `b43ac` (phy/radio/shm/table/mac/cc/sprom access) is compiled only with `CONFIG_B43_PHY_AC_DEBUG`:
  `AC_DEBUG=1 tools/build_b43_for_kernel.sh <kernel-dev>` builds `b43-src-builds/b43-<ver>-debug.ko`; the default build has none.
- Checked after the cleanup with the service's arguments only: 5 GHz VHT80 two streams up 64 / down 61-65 Mbit/s, switch to 2.4 GHz
  (HT MCS 15, up 23 / down 46-50), NM roaming back and forth.
- Left for the upstream split: `ieee80211_hw_set(AMPDU_AGGREGATION)` is unconditional (non-AC chips never take the A-MPDU actions, but it should be
  set only for AC), the `AC txhdr` hex dumps in xmit.c, `b43info` chatter in phy_ac.c, the `ac_` function-name prefixes, README claims.
