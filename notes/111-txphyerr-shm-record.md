# 111 - ucode txphyerr SHM record, good vs bad init

Tool: tools/txphyerr_shm_test.sh (reload until an init does not connect, dump shared SHM, restore a connection).
Data: test-logs/txphyerr-shm-1.log (byte range 0xBE0-0xC20: all zero, wrong range - SHM word addresses are x2),
test-logs/txphyerr-shm-2.log (0x17C0-0x1840).

Result (shared SHM byte offsets, = ucode word 0xBFA-0xC07 x2):
| offset | good init | bad init |
| 17f4 | 0000 | 0001 |
| 17f6 | 0000 | 0020 |
| 17f8 | 0000 | 0044 |
| 1802 | 0000 | 040a |
| 1804 | 0000 | 0110 |
| 180e | 0000 | 002c |
Other differences (17de, 17e0, 17e2, 1816, 183a) look like association/traffic state.
The error record is filled only after a PHY TX error, so it confirms the failure but does not yet say why.
Next: decode which IHR registers these words are (ucode txphyerr handler) and compare with PHY regs at that moment.

## Decode (layout from notes/13)
flag=1 | ext-IHR read=0x0020 | TXE_PHYCTL=0x0044 | PHYCTL1/2=0 | L-SIG=0/0 | HT-SIG0=0x040a HT-SIG1=0x0110 HT-SIG2=0 | VHT-SIG-B=0/0 | SCR12=0x002c.
- Same record type, same forensic picture as the 2026-09-27 samples (0x0045 / 0x01C0 / 0x2000 / 0x31): TXE_PHYCTL = 0x40 template | small selector,
  HT-SIG fields hold leftovers, nothing else set. Values differ per frame, so this is the generic txphyerr record, not a distinct failure signature.
- TXE_PHYCTL bits[1:0] = 0 here (0x45 had bit 0 set), so the ucode's address computation (0x0C64-66) takes the other branch: the ext-IHR read is a
  different register than "mode 3, offset 7" in notes/13 - which explains 0x0020 vs 0x2000 without a different error.
- Conclusion: the record says "PHY reported a TX error" (already known, TXE_STATUS bit 10). It carries no information on the cause. Branch closed.
- near router (signal 100/77 vs 60/39): 2/10 fresh inits connected, same as the ~21% baseline -> signal strength ruled out (test-logs/ab_reload_near_router_*.log)

## 5 GHz association attempt (tools/test_5ghz_connect.sh, test-logs/5ghz-connect-1.log)
ac_5ghz=1, connect to the 5 GHz BSSID (ch116 DFS), then 2.4 GHz on the same init to tell a bad init from a 5 GHz problem.
6/6 inits failed on both bands = bad inits, so 5 GHz itself is untested (P ~ 24% at the usual 79% failure rate). The wrapper then failed
12/12 on its first restart and connected on the second (18 bad in a row, ~1.4%): possible that ac_5ghz scans leave the chip worse; not established.
Stopped: a clean 5 GHz test needs a good init plus a 5 GHz TX chain setup that the replay does not load (see Alessio's code).
