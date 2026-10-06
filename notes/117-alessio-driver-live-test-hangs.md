# 117: Alessio's b43-ac-wip on our BCM4360 (MacBookAir6,1): live tests hang the machine

Built his bcma+b43 (patches 0001-0003 on v7.2 sources) as out-of-tree modules for 7.2.9 with
tools/build_alessio_driver.sh, loaded with tools/try_alessio_driver.sh (b43 swapped, stick untouched).

- Run 1/2: 2.4 GHz default channel rejected ("not supported on this board"), init fails, retries; machine hung
  after a few minutes of retries. Fix: -DALLOW_24=true.
- With ALLOW_24: init runs the whole attach, tables, rccal (cap 0xa0-0xa2 like ours), then HARD HANGS (whole machine,
  no oops, no panic, nothing in pstore/journal after) three times at the same place:
  b43_phy_ac_op_init -> post_rfseq_misc_setup -> b43_phy_ac_rxcore_setstate -> b43_phy_ac_run_rfseq_cmd
  (second call, cmd bit 0x0002), i.e. during the RF-sequencer kick/poll of PHY 0x400/0x402/0x403.
- Logging that worked: pr_emerg ACFN lines (journald fsyncs emerg) with mdelay(30). netconsole over the wifi stick
  does NOT deliver (netpoll over mac80211). Per-port logging (b43_read16/b43_write16 hook) only caught PHY
  data-port reads; writes/other reads go another way, so the last register access is still unknown.
- Observation: wl 6.30's first-load trace (traces/decoded-firstload-5g/seq.txt ~22290-22320) has the same
  rfseq kicks (phy 400/402/19e) but NOT his preceding 0x16d8=0xffff + 5.85 ms delay in rxcore_setstate: his code
  is the 7.14 sequence, our chip's captures are wl 6.30. Version mismatch is a lead, not proven.
- Each live test costs a reboot (and has corrupted .git twice: unsynced writes). Stop live runs of his driver.
  Safe path: run his offline unit harness (test/unit, cmp_skip.py) against OUR MacBook trace and diff op by op.
