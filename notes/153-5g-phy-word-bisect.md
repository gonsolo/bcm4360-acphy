# 153: which PHY word of wl's 5 GHz replay is essential (bisect with phy5g_reset.sh)

Setup: router on channel 52, 80 MHz, signal about -40 dBm at the desk. Each step: reload b43 with the
boot parameters plus `ac_5ghz=1 ac_5g_80=1 ac_vht=1 ac_por5g_*`, run `tools/phy5g_reset.sh` (restores the 318 PHY
words to the cold values of tools/phy5g_cold.txt), connect, iperf. Radio (163 words) and tables (3142) always applied
in full. Tool: `RESET=1 tools/por5g_chain.sh r,np,nt,p0`.

Control: all words (p0=0, np=318): VHT-MCS 9, 83 up / 63 down. So the reset script works (validated).

| PHY words applied | result |
|---|---|
| none, 0-132, 130-136, 133-136, 136 | not connected |
| 137-317, 0-249, 0-159, 60-317 | connected, 65-88 up / 62-67 down |
| 137-159 / 137-147 / 148-159 | yes / no / yes |
| 148-153 / 154-159 | no / yes |
| 154-156 / 157-159 | no / yes |
| 157 / 158-159 | no / yes |
| 158 / 159 | no / yes (79 up, 71 down) |

Result: word 159 = PHY register 0x018b = 0x016c is the one essential PHY write; the earlier "essential among 133-136"
(notes/149) was an artifact of leftover state in a nested chain.

Open: radio and table parts of the replay are still applied in full here; the radio state cannot be reset by a script,
so ablating them needs a cold boot or real init code for them.

## Tables (done without a reboot: zeroing instead of skipping)
Skipping words only works from a cold state; zeroing a range of wl's table words (`ac_por5g_tz0/tz1`, state then independent of
earlier runs; PHY replay off, the one 0x18b write, all radio words) works from any state. `tools/por5g_tz_ids.sh` zeroes one table
id at a time (about 2 min per id, unattended). Zeroing a *half* of all tables breaks the link everywhere, so id granularity it is.

Zeroing breaks the 80 MHz link (not connected): table ids **5** (22 words), **7** (211), **10** (96), **68** (25), **69** (23),
**100** (25), **101** (23). Zeroing any of ids 1-4, 11, 12, 14, 16, 33, 64-66, 71, 72, 96-98, 103, 104, 128-130, 135, 136
leaves it working (71-88 up / 60-67 down). That is 7 of 31 ids, 425 of 3142 words, instead of all of them.
Log: test-logs/tz_ids.log. Next: check which of these our own init already writes, and replace the rest with real data.
