# 152: kernel oops in rmmod b43 during the unattended ablation chain (12:59, needs a reboot)

What happened: `RESET=1 por5g_chain.sh 0,132,0,0 0,137,0,133 ...` (run with the owner's permission while away). Step 1 ran normally (not connected, as expected). During the next step the dev module was loaded, NetworkManager brought wlp3s0b1 up (the second `software_rfkill(blocked=0)` / radio init in the log) and about 2 s later `rmmod b43` (ld.sh of the following step) ran while that init was still in progress.

Result: `general protection fault` in `kfree` from `bcma_device_remove+0x23` <- `device_release_driver_internal` <- `driver_detach` <- `bus_remove_driver` <- `delete_module` (rmmod, pid 10340, 12:59:34). b43 is stuck in `initstate=going` with refcount -1, bcma0:1 has no driver, `wlp3s0b1` does not exist, insmod fails with "Device or resource busy". The stick is unaffected (default route, 0 % loss). b43-autorecover keeps trying (rate limited) and cannot succeed; **only a reboot brings b43 back.**

Not yet understood: which kfree (the freed object looks overwritten by ASCII text, a use-after-free or DMA into freed memory). The remove path races with an interface bring-up that is still initialising the core (b43_op_start -> b43_wireless_core_init).

Lessons: (1) never `rmmod b43` within ~30 s of loading; wait until the interface has an address and stays associated (the boot loader waits 25 s for a reason). (2) the chain script now sleeps 30 s after each step. (3) unattended 5 GHz experiments stay a bad idea even when allowed, because the failure mode is a machine that needs a reboot.
