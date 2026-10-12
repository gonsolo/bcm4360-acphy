#!/usr/bin/env python3
"""polish.py DIR: rewrite development-notebook comments of the series tree (phy_ac.c, main.c, dma.c, xmit.c, b43.h) into plain
descriptions. Every replacement must match exactly once, so a changed source shows up as an error instead of a silent skip."""
import re, sys
d = sys.argv[1]
def sub(path, pairs, regex=False):
    s = open(f"{d}/{path}").read()
    for old, new in pairs:
        if regex:
            s, n = re.subn(old, lambda m: new, s, count=1, flags=re.S)
        else:
            n = s.count(old)
            if n == 1:
                s = s.replace(old, new)
        if n != 1:
            sys.exit(f"polish: {path}: expected one match, got {n}: {old[:70]!r}")
    open(f"{d}/{path}", "w").write(s)

P = []
P.append((r"/\*\n \* Decompiled from the vendor driver's phy_reg_write\(\).*?\*/\nstatic void b43_phy_ac_op_write",
 "/*\n * Unlike the generic b43_phy_write() fallback (two 16-bit writes to CONTROL\n * and DATA), the vendor driver writes one 32-bit word, (value << 16) | reg,\n * to the CONTROL address. Do the same.\n */\nstatic void b43_phy_ac_op_write"))
P.append((r"/\*\n \* Decompiled from the vendor driver's write_radio_reg\(\)/read_radio_reg\(\):.*?\*/\nstatic bool b43_phy_ac_use_radio24",
 "/*\n * Which CONTROL/DATA register pair addresses the radio depends on the core\n * revision: cores 0x1b and below 0x18 use the legacy RADIO_CONTROL and\n * RADIO_DATA_LOW pair, newer ones (including the BCM4360's) the RADIO24 pair.\n */\nstatic bool b43_phy_ac_use_radio24"))
P.append((r"/\*\n \* Decompiled from wlc_phy_switch_radio_acphy\(\).*?\*/\nstatic void b43_radio_2069_power_down",
 "/* Radio power-down; the power-up is b43_radio_2069_power_up(). */\nstatic void b43_radio_2069_power_down"))
P.append((r"/\* The vendor's radio on/off lives in software_rfkill; nothing extra here yet\. \*/",
 "/* The radio is powered up by software_rfkill(); only switching off is done here. */"))
P.append((r"\n\n/\* wl's real hostflags.*?\*/\n\n/\* HOSTF1.*?\*/\n\n", "\n\n"))
P.append((r"/\*\n \* 80 MHz mode: wl's captured 80 MHz state.*?\*/\n\nstatic bool b43_phy_ac_is_80mhz",
 "/*\n * 80 MHz mode: on 5 GHz the PHY runs on the 80 MHz block that contains the\n * primary channel, tuned to the centre of the block.\n */\nstatic bool b43_phy_ac_is_80mhz"))
P.append((r"block in bits 10:8 \(wl on channel 112: 0xe36a\)\.", "block in bits 10:8 (primary channel 112: 0xe36a)."))
P.append((r"static void b43_radio_2069_vcocal\(struct b43_wldev \*dev\);\n\n\n/\* 2\.4 GHz TX gain table index[^\n]*\n",
 "static void b43_radio_2069_vcocal(struct b43_wldev *dev);\n\n/*\n * 2.4 GHz TX gain table index set on a channel switch (0 is the highest gain).\n * The reset value, 64, is too weak beyond a few metres.\n */\n"))
P.append((r"/\*\n \* The 48-bit tables wl loads on 2\.4 GHz and the trace decoder missed\n \*: the TX gain table 0x20.*?\*/\nstatic void b43_phy_ac_wide_tables_2g",
 "/*\n * The 48-bit wide tables of the 2.4 GHz setup: the TX gain table 0x20, which\n * hardware TX power control indexes; the RF sequencer extension entry 0x33;\n * and table 0x11: twelve fixed cells, 448 cells of the SROM's rpcal\n * coefficient (the value for this board on 2.4 GHz), then four zero cells.\n */\nstatic void b43_phy_ac_wide_tables_2g"))
P.append((r"/\*\n \* RF sequencer extension \(PHY table 0x14\), entries 0x30-0x33, as wl writes\n.*?\*/\n/\* The second sequencer's command lists.*?\*/\n",
 "/*\n * The second sequencer's command lists (table 7 at 0x30/0x40/0x50, cores 0-2)\n * on 5 GHz: no leading 0x2a, and 0xb0/0xb1/0xb2 where 2.4 GHz has 0x2b.\n */\n"))
P.append((r"static void b43_phy_ac_rfseq_ext_5g\(struct b43_wldev \*dev\)\n\{",
 "/*\n * 5 GHz additions to the sequencer and the wide tables:\n * - table 0x14 entries 0x30-0x33, the RF sequencer extension (48 bits wide,\n *   written through the third data port 0x011, low word first). Without\n *   0x30-0x32 the receiver is deaf on 5 GHz; 2.4 GHz does not need them.\n *   PHY tables survive a driver reload and a PCI bus reset.\n * - the command lists above and three table 7 cells, see below,\n * - the 5 GHz TX gain table and the table 0x11 fill.\n */\nstatic void b43_phy_ac_rfseq_ext_5g(struct b43_wldev *dev)\n{"))
P.append((r"\t/\* rfseq2 timing cells of the TX chains \(core 0 at 973, core 1 at 989\) that\n\t \* differ from the 2\.4 GHz defaults: without the core 1 value no two-stream\n\t \* frame is ever acknowledged\.\n\t \*/",
 "\t/* Table 7 cells of the TX chains (core 0 at 973, core 1 at 989) and the cell\n\t * 398 that differ from the 2.4 GHz defaults: without the core 1 value no\n\t * two-stream frame is ever acknowledged, and 398 makes two-stream MCS 7\n\t * usable.\n\t */"))
P.append((r"\t/\* The 5 GHz TX gain table, and the rpcal fill wl used on channel 112\n\t \* \(the twelve head cells and the zero tail are band independent\)\.\n\t \*/",
 "\t/* The 5 GHz TX gain table and the table 0x11 fill (the twelve head cells\n\t * and the zero tail are band independent).\n\t */"))
P.append((r"/\* 5 GHz setup on entering 80 MHz mode:.*?\n \*/\nstatic void b43_phy_ac_setup_5g",
 "/*\n * 5 GHz setup, run on every 5 GHz channel switch: the sequencer extension,\n * VCO calibration, RX gain control and the AGC tables.\n */\nstatic void b43_phy_ac_setup_5g"))
P.append((r"\t/\* RX gain control, all cores: wl and Alessio use 0x2c on 5 GHz, our 2\.4 GHz\n\t \* init leaves 0x18; about 8 dB more RX level\.\n\t \*/",
 "\t/* RX gain control, all cores: 0x2c on 5 GHz (the 2.4 GHz setup leaves\n\t * 0x18); about 8 dB more RX level.\n\t */"))
P.append((r"/\*\n \* PHY register init, 2\.4 GHz / 20 MHz, replacing the first 72 entries of the\n.*?\*/\n#define B43_AC_NCORES",
 "/*\n * PHY register init for 2.4 GHz and 20 MHz, in the blocks of the reset-time\n * code of Alessio Ferri's b43-ac-wip (mode_init, set_reg_on_reset,\n * set_pdet_on_reset, coeff_bank_init), plus the few registers the vendor\n * driver writes in the same window. Read-modify-write is kept where his\n * code uses it.\n */\n#define B43_AC_NCORES"))
P.append((r"\tb43_phy_write\(dev, 0x01ed, 0x0050\);\t/\* wl \*/", "\tb43_phy_write(dev, 0x01ed, 0x0050);"))
P.append((r"\tb43_phy_write\(dev, 0x03c4, 0x0668\);\t/\* wl \*/", "\tb43_phy_write(dev, 0x03c4, 0x0668);"))
P.append((r"/\*\n \* RX gain / threshold LUT and per-core words\. The 20 MHz values are checked\n \* against wl on 2\.4 GHz; the 40 and 80 MHz ones are his \(5 GHz captures\) and\n \* not exercised here yet\.\n \*/",
 "/*\n * RX gain / threshold LUT and per-core words. The 20 MHz values are checked\n * on 2.4 GHz; the 40 and 80 MHz ones are from Alessio Ferri's tree (5 GHz).\n */"))
P.append((r"\t/\* His b43_radio_2069_init\(\) prologue \(0x0415/040e/040c/0408/0417/0416\)\n\t \* and the end state of the power-on \(0x0408 = 0x0c02, 0x0417 = 4\)\n\t \*/",
 "\t/* The prologue of b43_radio_2069_init() (0x0415/040e/040c/0408/0417/0416)\n\t * and the end state of the power-on (0x0408 = 0x0c02, 0x0417 = 4)\n\t */"))
P.append((r"/\* FEM table 2 / sub 1 setup \(his b43_phy_ac_fem2_sub1_setup\) \*/", "/* FEM table 2 / sub 1 setup */"))
P.append((r"/\* RX gain control, all cores \(his rxgainctrl setup\)\. Without it the", "/* RX gain control, all cores. Without it the"))
P.append((r"\n\t/\* Everything else wl's first-load state contained.*?Only the PHY register writes are left\.\n\t \*/\n", "\n"))
P.append((r"On since\n\t \* \(with the wide tables it no longer fails frames next to the\n\t \* AP; 0x0100 would switch it off\)\.",
 "Enabled: with\n\t * the wide tables it no longer fails frames next to the AP (0x0100 would\n\t * switch it off)."))
P.append((r"/\*\n \* Follows the vendor driver's channel-set sequence for radio 2069 rev 4 at\n \* 20 MHz\. Not yet ported:.*?\*/\n/\* Final per-core RF control state of wl \(first-load trace\) that our init\n \* doesn't reach; diagnostic until the owning init step is ported\.\n \*/\nstatic void b43_phy_ac_rfctrl_wl",
 "/* Per-core RF control state of the 2.4 GHz setup that the init does not reach. */\nstatic void b43_phy_ac_rfctrl_2g"))
P.append((r"fractional resampler to the baseband rate depends on the channel\. wl\n \* \(static function at 0x1a581c\) writes these on every channel switch;\n \* without them every channel kept channel 6's ratio, 3\.5% off on\n \* channel 1\.",
 "fractional resampler to the baseband rate depends on the channel. The vendor\n * driver writes these on every channel switch; without them every channel\n * kept channel 6's ratio, 3.5% off on channel 1."))
P.append((r"Farrow resampler for an 80 MHz channel centred on @freq \(MHz\), Alessio\n \* Ferri's formula: ratio = round\(f \* 2\^18 / 45\), deltaphase =\n \* round\(0xb40000000 / f\)\. For 5530 MHz it gives exactly wl's captured words\.",
 "Farrow resampler for an 80 MHz channel centred on @freq (MHz). The formula is\n * from Alessio Ferri's tree: ratio = round(f * 2^18 / 45), deltaphase =\n * round(0xb40000000 / f); for 5530 MHz it gives the vendor driver's values."))
P.append((r"static void b43_phy_ac_tune\(struct b43_wldev \*dev,",
 "/* Program the synthesizer and the per-channel radio words of one channel. */\nstatic void b43_phy_ac_tune(struct b43_wldev *dev,"))
P.append((r"\t\t/\* Test: keep wl's 80 MHz setup \(synthesizer on its 80 MHz centre,\n\t\t \* PHY in 80 MHz mode\) and set the core's PHY bandwidth to 80 MHz,\n\t\t \* toggling force-gated-clock around the change like wl\.\n\t\t \*/\n\t\tunsigned int ctr",
 "\t\t/* Tune the synthesizer to the centre of the block, put the core's PHY\n\t\t * in 80 MHz mode and toggle force-gated-clock around the change.\n\t\t */\n\t\tunsigned int ctr"))
P.append((r"\t\t/\* The one PHY word of wl's 5 GHz state that 80 MHz RX/TX needs\n\t\t \* \(bisect of 318 words\); reg 0x18b is 0 after reset\.\n\t\t \*/",
 "\t\t/* PHY word 0x18b is 0 after reset; 80 MHz RX and TX need 0x016c. */"))
P.append((r"\t\t/\* Synthesizer, the per-channel PHY words \(wl leaves 0x371 at 0 in\n\t\t \* 80 MHz mode\) and the resampler for the block centre; same result\n\t\t \* as wl's own tuning on centre 106\. Calibration results\n\t\t \* and the rpcal fill stay those of channel 106\.\n\t\t \*/",
 "\t\t/* The synthesizer, the per-channel PHY words and the resampler for the\n\t\t * block centre. The calibration results and the rpcal fill are those\n\t\t * of channel 106; they are not recalibrated per block.\n\t\t */"))
P.append((r'"phy_ac: 5 GHz 80 MHz test, ioctrl', '"phy_ac: 5 GHz 80 MHz mode, ioctrl'))
P.append((r"\t\t/\* wl's state is its 80 MHz one: filters for our width \*/\n", "\t\t/* The filter bank for our width. */\n"))
P.append((r"\t\t/\* wl's state tunes to its 80 MHz centre; tune our channel\. \*/\n", ""))
P.append((r"\t/\* After the wl snapshot\. wl's own trace uses this same per-channel\n\t \* 20 MHz table on 5 GHz channels too.*?this table was never shown to apply to\.\n\t \*/",
 "\t/* The per-channel 20 MHz resampler table; in 80 MHz mode the resampler was\n\t * set for the block centre above.\n\t */"))
P.append((r"/\*\n \* Not a real PHY init yet - no calibration, no channel setup\..*?\*/\nstatic void b43_phy_ac_write_table",
 "/* Write a table of 8, 16 or 32 bit entries through the PHY table ports. */\nstatic void b43_phy_ac_write_table"))
P.append((r"/\*\n \* PHY init for PHY rev 0/1 \(as the vendor driver does it\): RF-control override\n \* defaults, then the acphytbl_info_rev0 table set\.\n \*/\n/\*\n \* 2\.4 GHz power-estimation LUT",
 "/*\n * 2.4 GHz power-estimation LUT"))
P.append((r"as b43_nphy_tx_power_ctl_setup\(\); checks it 128/128 against wl's table on this card\)\.",
 "as b43_nphy_tx_power_ctl_setup(); it matches the vendor driver's table entry for\n * entry on this board)."))
P.append((r"static void b43_phy_ac_tables_init\(struct b43_wldev \*dev\)\n\{\n\tstatic const u16 clear_regs",
 "/*\n * PHY init for PHY rev 0/1: the AFE page, then the table set of the\n * acphytbl_info_rev0 plus the FEM tables of this board's control pattern.\n */\nstatic void b43_phy_ac_tables_init(struct b43_wldev *dev)\n{\n\tstatic const u16 clear_regs"))
P.append((r"/\*\n \* First-init PHY register setup \(as the vendor driver does it\), resolved for PHY rev\n \* 0/1\. Not ported yet: wlc_phy_hwaci_setup_acphy \(interference mitigation\)\.\n \*/",
 "/*\n * First-init PHY register setup for PHY rev 0/1. Not ported: the hardware\n * interference mitigation setup.\n */"))
P.append((r"\t\t/\* wl's captured state, once; the channel switch that follows\n\t\t \* init tunes the radio for the requested channel\.\n\t\t \*/",
 "\t\t/* The channel switch that follows init tunes the radio. */"))
P.append((r"Self-healing for the per-init coin flip: only ~30 % of\n \* fresh inits can transmit;",
 "Self-healing for a bad init: only about 30 % of fresh inits can transmit;"))
P.append((r"Polled, not IRQ-driven: unmasking B43_IRQ_PHY_TXERR hung\n \* the machine twice\.", "Polled, not IRQ-driven: unmasking B43_IRQ_PHY_TXERR hung\n * the machine."))
P.append((r"\t/\* wl's real watchdog runs a periodic bulk RX-ring\n\t \* refill sweep this port never had; do the equivalent here\.\n\t \*/",
 "\t/* Retry the RX buffer refills that failed under memory pressure. */"))
sub("phy_ac.c", P, regex=True)
s = open(f"{d}/phy_ac.c").read()
s = s.replace("b43_phy_ac_apply_por", "b43_phy_ac_setup_regs").replace("b43_phy_ac_rfctrl_wl", "b43_phy_ac_rfctrl_2g")
open(f"{d}/phy_ac.c", "w").write(s)
print("polish: phy_ac.c ok")

# "wl" in the comments of lines we added (not in stock lines): the vendor driver
import subprocess, os
root = subprocess.check_output(["git", "-C", d, "rev-parse", "--show-toplevel"], text=True).strip()
first = subprocess.check_output(["git", "-C", root, "rev-list", "--max-parents=0", "HEAD"], text=True).split()[0]
for fn in ("phy_ac.c", "main.c", "dma.c", "xmit.c", "b43.h", "tables_phy_ac.c", "radio_2069.c", "phy_ac_farrow.h", "phy_common.c"):
    try:
        stock = set(subprocess.check_output(["git", "-C", root, "show", f"{first}:drivers/net/wireless/broadcom/b43/{fn}"],
                                            text=True, stderr=subprocess.DEVNULL).splitlines())
    except subprocess.CalledProcessError:
        stock = set()
    out = []
    for line in open(f"{d}/{fn}").read().split("\n"):
        if line not in stock and re.match(r"\s*(/\*|\*)", line.lstrip() if False else line):
            line = re.sub(r"\bwl's\b", "the vendor driver's", line)
            line = re.sub(r"\bwl\b(?!->|\)|_)", "the vendor driver", line)
        out.append(line)
    open(f"{d}/{fn}", "w").write("\n".join(out))
print("polish: wl -> vendor driver in added comments ok")

# xmit.c: the RX debug counter does not belong in the TX code; put the stock comment back on its function
X = []
X.append((r"/\* Generate a TX data header\. \*/\nstatic unsigned int b43_ac_decerr_logged;\n\n?", ""))
X.append((r"\nint b43_generate_txhdr\(", "\n/* Generate a TX data header. */\nint b43_generate_txhdr("))
X.append((r"\t\tif \(dev->phy.type == B43_PHYTYPE_AC\) \{\n\t\t\tif \(b43_ac_decerr_logged < 8\) \{\n\t\t\t\tb43_ac_decerr_logged\+\+;\n\t\t\t\tb43dbg\(dev->wl, \"RX: DECERR passed up \(len %u, macstat %04x\)\\n\",\n\t\t\t\t\tskb->len, macstat\);\n\t\t\t\}\n\t\t\} else \{",
          "\t\tif (dev->phy.type == B43_PHYTYPE_AC) {\n\t\t\tb43dbg(dev->wl, \"RX: DECERR passed up (len %u, macstat %04x)\\n\",\n\t\t\t\tskb->len, macstat);\n\t\t} else {"))
sub("xmit.c", X, regex=True)
print("polish: xmit.c ok")

# phy_ac.c: describe the channel switch
sub("phy_ac.c", [(r"\nstatic int b43_phy_ac_op_switch_channel\(",
 "\n/*\n * Channel switch for radio 2069 rev 4, following the vendor driver's channel-set\n * sequence. Not ported: carrier-search suppression during the switch, the 5 GHz\n * PLL setup and the per-channel PHY tweaks that follow the BW registers.\n */\nstatic int b43_phy_ac_op_switch_channel(")], regex=True)
print("polish: switch_channel comment ok")
