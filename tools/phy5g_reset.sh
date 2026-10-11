#!/usr/bin/env bash
# phy5g_reset.sh : write the 318 PHY words of wl's 5 GHz state back to their cold-boot values
# (tools/phy5g_cold.txt, captured on this machine after a cold boot with only the 2.4 GHz init run,
# before any 5 GHz use). Gives the replay ablation (por5g_chain.sh) a cold start without a reboot,
# as far as PHY words matter: radio words and tables were shown not to matter (notes/149).
# Run as root with b43 loaded and up on 2.4 GHz.
D=/sys/kernel/debug/b43ac
while read a v; do echo "$a $v" > $D/phy; done < "$(dirname "$0")/phy5g_cold.txt"
