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

## Retest with his head ce2127a (2026-10-09), user-approved
Built with tools/build_alessio_driver.sh (ACFN/mdelay forensics), loaded with try_alessio_driver.sh. The init got
much further than on 2026-10-06: past the rfseq kicks, radio init, rccal and the rxcal AFE iterations (the last non-table
function in the journal is b43_phy_ac_rxcal_afe_finalize_gain_luts -> b43_phy_ac_cca_pulse), then ~80000 log lines of
b43_actab_write_bulk_scoped (table writes), and the log ends there. WiFi on both interfaces was dead afterwards (the stick
too, so not only b43: the PCI/bus side or the whole machine); reboot needed. The journal survived (emerg + fsync).
Open: whether that is a real hang in the table path (a gate/lock pair he added 2026-10-07: "table gate as nested
lock/unlock") or just the 30 ms mdelay per ACFN line making an 80000-call init take 40 min while the stack timed out.
Next time: drop the mdelay from the table functions, keep it elsewhere.

## Second retest, no delay in the table functions (2026-10-09): NO HANG
The earlier "hang" was my logging: ACFN + mdelay(30) on ~80000 b43_actab_* calls (~40 min). tools/build_alessio_driver.sh now
skips the log/delay for b43_actab*. With that his driver (head ce2127a, ALLOW_24) runs the whole init in ~5 s, the machine and
the stick stay up, wlp3s0b1 appears and the ACFN trace shows the complete op_init -> switch_channel -> calibrate path.
But the radio does not work: after the first channel "radio 2069: power-on timeout (0x040b=0x0001)" repeats every channel
switch (the first pwron read 0x0169 after 2 polls), probe requests go out with acked 0 / supp 0-4, no scan result
(`ip link up` / scan: -EBUSY at the time). 0x040b is also the register our TX power loop needs (we write 0x168).
Restored with try_alessio_driver.sh restore (the stick needed `nmcli device connect`).
Next: find out why 0x040b stays 0x0001 after the first channel, and compare with our sequence there.
