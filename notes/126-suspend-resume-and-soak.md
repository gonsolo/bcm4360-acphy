# notes/126: suspend/resume works; soak started

Suspend to RAM (S3, `rtcwake -m mem -s N`), module = hand build with ac_phyreset (b43 + stick both up):
6/6 cycles (sleeps 45, 20, 60, 20, 90, 25 s): the driver's own PM path re-inits the core (prepare_structs ... first-init),
NetworkManager reconnects wlp3s0b1 on its own, stick stays connected, 0 PHY TX errors / MAC suspend failures.
Pings pass ~6-9 s after wake (3 s: 0/3, 9 s: 3/3). No b43-resume hook (tools/install_b43_resume_hook.sh) is needed.

Soak: tools/b43_soak.sh <seconds> [log]: ping the gateway through wlp3s0b1 every 10 s, log outages, NM state
transitions, kernel error counters and station retries every 5 min. 2 h run on the production Nix module
(test-logs/soak_main.log). Gotcha: restarting b43-ac-load.service by hand with b43 already loaded logs
"try 1: load failed (File exists)" and reloads; at boot the module is not loaded so this does not happen.
