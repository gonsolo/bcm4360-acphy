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
