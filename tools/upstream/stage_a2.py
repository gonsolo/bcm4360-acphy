#!/usr/bin/env python3
"""stage_a2.py FINAL_DIR OUT_DIR: derive the 2.4 GHz-only stage of phy_ac.c / phy_ac.h from the final tree (5 GHz, 80 MHz mode and the
band-switch restore removed). Every removal must match exactly once."""
import re, sys
src, dst = sys.argv[1:3]
s = open(f"{src}/phy_ac.c").read()
def cut(pattern, repl):
    global s
    s, n = re.subn(pattern, lambda m: repl, s, count=1, flags=re.S)
    if n != 1:
        sys.exit(f"stage_a2: no match for {pattern[:60]!r}")
# 80 MHz helper and the vcocal prototype (5 GHz only)
cut(r"/\*\n \* 80 MHz mode: on 5 GHz the PHY runs on the 80 MHz block.*?\nstatic void b43_radio_2069_vcocal\(struct b43_wldev \*dev\);\n\n", "")
# the 5 GHz block: rfseq2 lists, sequencer extension, AGC tables, setup_5g
cut(r"/\*\n \* The second sequencer's command lists.*?(?=/\*\n \* PHY register init for 2\.4 GHz)", "")
# Farrow for 80 MHz
cut(r"/\*\n \* Farrow resampler for an 80 MHz channel.*?(?=/\* Program the synthesizer)", "")
# back-to-2.4 restore
cut(r"static void b43_phy_ac_tables_init\(struct b43_wldev \*dev\);\n\n/\* Back on 2\.4 GHz after 5 GHz.*?\n}\n\n(?=/\*\n \* Channel switch for radio 2069)", "")
# the channel switch
cut(r"static int b43_phy_ac_op_switch_channel\(.*?\n\treturn 0;\n}\n",
"""static int b43_phy_ac_op_switch_channel(struct b43_wldev *dev,
					unsigned int new_channel)
{
	struct b43_phy_ac *phy_ac = dev->phy.ac;
	const struct b43_radio_2069_chan *e;
	u16 save;
	int i;

	if (b43_current_band(dev->wl) != NL80211_BAND_2GHZ)
		return -EOPNOTSUPP;

	e = b43_radio_2069_find_chan(dev, new_channel);
	if (!e) {
		b43err(dev->wl, "phy_ac: no tuning data for channel %u (radio %04x rev %u)\\n",
		       new_channel, dev->phy.radio_ver, dev->phy.radio_rev);
		return -ESRCH;
	}
	b43dbg(dev->wl, "phy_ac: switch_channel(%u) -> %u MHz\\n",
		new_channel, e->freq);

	save = b43_phy_read(dev, 0x19e);
	b43_phy_set(dev, 0x19e, 0x3);

	b43_phy_mask(dev, B43_PHY_AC_BANDCTL, ~0x0100);

	if (!phy_ac->chan_set) {
		b43_phy_set(dev, 0x728, 0x0100);
		udelay(1);
		b43_phy_mask(dev, 0x728, ~0x0100);
		phy_ac->chan_set = true;
	}

	b43_phy_ac_tune(dev, e, new_channel);
	b43_phy_maskset(dev, 0x19e, ~0x3, save & 0x3);

	for (i = 0; i < 6; i++)
		b43_phy_write(dev, B43_PHY_AC_BW1A + i, e->bw[i]);

	b43_phy_ac_rfctrl_2g(dev);
	b43_phy_ac_set_farrow(dev, new_channel);
	b43_phy_ac_resetcca(dev);
	b43_phy_ac_txpwr_by_index(dev, B43_AC_TXIDX_2G);

	return 0;
}
""")
open(f"{dst}/phy_ac.c", "w").write(s)
h = open(f"{src}/phy_ac.h").read()
h2, n = re.subn(r"\tbool last_5ghz;\n", "", h, count=1)
if n != 1:
    sys.exit("stage_a2: phy_ac.h last_5ghz not found")
open(f"{dst}/phy_ac.h", "w").write(h2)
print("stage_a ok")
