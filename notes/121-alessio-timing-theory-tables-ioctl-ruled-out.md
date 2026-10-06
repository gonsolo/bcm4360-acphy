# notes/121: Alessio's timing theories, PHY tables and wrapper IOCTL: all negative

Alessio's two hints (rfseq needs delay+poll; replayed wl delays are only as long as in the trace).

- rfseq: our `force_rfseq` polled 0x403 right after the 0x402 write; wl waits 10 us first
  (seq.txt ~137510). Fixed (udelay(10)). The default init never calls it; `ac_rfseq=1` with the fix: 2/10 (baseline).
- Delay padding of the radio init/cal replay (`ac_fr_pad`, `ac_fr_dscale`): pad 10 us: 1/10 (baseline 3/10).
  The pad1/pad100 runs and the first rfseq run were invalid (stale b43-src/b43.ko, module stuck in "Unloading"):
  the harness loads b43-src/b43.ko, copy the build there.
- New debugfs `b43ac/tbldump`: all PHY tables wl writes (5382 entries) plus wrapper IOCTL/RESET_CTL/IOSTATUS.
  30 inits with outcome (tools/connect_test.sh honours SNAP=<file>): 0 of 5382 entries discriminate good from bad.
  Table 4 (gate, 0/8,6,4) and table 7 toggle between two global patterns, uncorrelated with the outcome.
- Wrapper IOCTL = 0x2155, RESET_CTL 0, IOSTATUS 0x100c in all 30 inits (good 11, bad 19), same as wl.

Good rate over 30 inits: 11/30 (and 8/30, 3/24 earlier) ~ 25-35 %. The per-init random element is not in
PHY registers, tables, radio registers, PMU or wrapper control state. Remaining idea: an analog/clock-phase
coin (MAC clock vs PHY clock) re-rolled by every core reset, visible only as TX-side PHY errors.
