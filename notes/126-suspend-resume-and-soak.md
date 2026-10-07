# notes/126: suspend/resume works; soak started

Suspend to RAM (S3, `rtcwake -m mem -s N`), module = hand build with ac_phyreset (b43 + stick both up):
6/6 cycles (sleeps 45, 20, 60, 20, 90, 25 s): the driver's own PM path re-inits the core (prepare_structs ... first-init),
NetworkManager reconnects wlp3s0b1 on its own, stick stays connected, 0 PHY TX errors / MAC suspend failures.
Pings pass ~6-9 s after wake (3 s: 0/3, 9 s: 3/3). No b43-resume hook (tools/install_b43_resume_hook.sh) is needed.

Soak: tools/b43_soak.sh <seconds> [log]: ping the gateway through wlp3s0b1 every 10 s, log outages, NM state
transitions, kernel error counters and station retries every 5 min. 2 h run on the production Nix module
(test-logs/soak_main.log). Gotcha: restarting b43-ac-load.service by hand with b43 already loaded logs
"try 1: load failed (File exists)" and reloads; at boot the module is not loaded so this does not happen.

## Soak result (production Nix module, 03:10-05:05, killed at ~1 h 55 min of the planned 2 h)
690 pings, 11 lost, never more than 2 in a row, 0 kernel errors (PHY TX error / MAC suspend failed / bad init).
Two NM state transitions at 03:37 (connected -> connecting (configuring) -> connected in 10 s, during my own
test activity); no unrecovered drop. Last 55 min: 0 lost. Verdict: pass. b43_soak.sh now uses tools/iw
(txpk/retries filled) and prints the end line on INT/TERM.
