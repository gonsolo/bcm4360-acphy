// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Broadcom B43 wireless driver
 * IEEE 802.11ac AC-PHY support
 *
 * Copyright (c) 2015 Rafał Miłecki <zajec5@gmail.com>
 */

#include "b43.h"
#include "phy_ac.h"
#include "radio_2069.h"
#include "tables_phy_ac.h"
#include "dma.h"
#include "main.h"

/**************************************************
 * Basic PHY ops
 **************************************************/

static int b43_phy_ac_op_allocate(struct b43_wldev *dev)
{
	struct b43_phy_ac *phy_ac;

	phy_ac = kzalloc(sizeof(*phy_ac), GFP_KERNEL);
	if (!phy_ac)
		return -ENOMEM;
	dev->phy.ac = phy_ac;

	return 0;
}

static void b43_phy_ac_op_free(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_ac *phy_ac = phy->ac;

	kfree(phy_ac);
	phy->ac = NULL;
}

static void b43_phy_ac_op_maskset(struct b43_wldev *dev, u16 reg, u16 mask,
				  u16 set)
{
	b43_write16f(dev, B43_MMIO_PHY_CONTROL, reg);
	b43_write16(dev, B43_MMIO_PHY_DATA,
		    (b43_read16(dev, B43_MMIO_PHY_DATA) & mask) | set);
}

/*
 * Decompiled from the vendor driver's phy_reg_write(): unlike the generic
 * b43_phy_write() fallback (two separate 16-bit writes to CONTROL then
 * DATA), the vendor driver does a single combined 32-bit write encoding
 * (value << 16) | reg to the CONTROL address. Whether the split-write
 * fallback is actually equivalent on real ACPHY hardware is untested;
 * implement the vendor's exact sequence here to remove that variable.
 */
static void b43_phy_ac_op_write(struct b43_wldev *dev, u16 reg, u16 value)
{
	b43_write32(dev, B43_MMIO_PHY_CONTROL, ((u32)value << 16) | reg);
}

/*
 * Decompiled from the vendor driver's write_radio_reg()/read_radio_reg():
 * which CONTROL/DATA register pair to use depends on core revision (and,
 * on core_rev 0x16 specifically, on the active radio-core index - that
 * extra check is on a codepath we don't expect to hit on this chip's core
 * revision and is not reproduced here). For core_rev == 0x1b or < 0x18,
 * use the legacy RADIO_CONTROL/RADIO_DATA_LOW pair; otherwise (which is
 * the expected case for this chip - see notes/02-register-primitives.md)
 * use RADIO24_CONTROL/RADIO24_DATA, matching the previous hardcoded
 * behaviour of this stub.
 */
static bool b43_phy_ac_use_radio24(struct b43_wldev *dev)
{
	u8 rev = dev->dev->core_rev;

	return !(rev == 0x1b || rev < 0x18);
}

static u16 b43_phy_ac_op_radio_read(struct b43_wldev *dev, u16 reg)
{
	if (b43_phy_ac_use_radio24(dev)) {
		b43_write16f(dev, B43_MMIO_RADIO24_CONTROL, reg);
		return b43_read16(dev, B43_MMIO_RADIO24_DATA);
	}

	b43_write16f(dev, B43_MMIO_RADIO_CONTROL, reg);
	return b43_read16(dev, B43_MMIO_RADIO_DATA_LOW);
}

static void b43_phy_ac_op_radio_write(struct b43_wldev *dev, u16 reg,
				      u16 value)
{
	if (b43_phy_ac_use_radio24(dev)) {
		b43_write16f(dev, B43_MMIO_RADIO24_CONTROL, reg);
		b43_write16(dev, B43_MMIO_RADIO24_DATA, value);
		return;
	}

	b43_write16f(dev, B43_MMIO_RADIO_CONTROL, reg);
	b43_write16(dev, B43_MMIO_RADIO_DATA_LOW, value);
}

static u8 b43_phy_ac_num_cores(struct b43_wldev *dev)
{
	u8 cores = b43_phy_read(dev, 0x00b) & 0x7;

	if (dev->dev->chip_id == 0x4360 &&
	    (dev->dev->board_type == 0x137 || dev->dev->board_type == 0x117))
		cores = 2;
	return cores;
}

/* prefregs_2069_rev4 from the vendor driver. */
static const u16 b43_radio_2069r4_prefregs[][2] = {
	{ 0x063a, 0x0000 }, { 0x063d, 0x000f }, { 0x0645, 0x3000 },
	{ 0x0646, 0x0303 }, { 0x0647, 0x36e2 }, { 0x0649, 0x6000 },
	{ 0x064a, 0x0003 }, { 0x065e, 0x0ff4 }, { 0x0666, 0x0b2d },
	{ 0x0667, 0x03ff }, { 0x0115, 0x3337 }, { 0x0117, 0x1337 },
	{ 0x0718, 0x7777 }, { 0x071c, 0x1000 }, { 0x0726, 0x0100 },
	{ 0x0727, 0x0002 }, { 0x0761, 0x0100 }, { 0x0407, 0x8382 },
	{ 0x055e, 0x0020 }, { 0x0885, 0x0700 }, { 0x08e9, 0x01ce },
	{ 0x08ea, 0x00ff }, { 0x08ec, 0x06ff }, { 0x0972, 0x0600 },
};

/*
 * Radio 2069 rev 4 init (vendor FUN_001a08b2). Skipped: a board-flag
 * dependent "radio 0x8ea |= 0x100" whose flag source we haven't identified.
 */
static void b43_radio_2069_init(struct b43_wldev *dev)
{
	u16 s728, s408;
	unsigned int i;
	u8 core, cores;

	s728 = b43_phy_read(dev, 0x728);
	s408 = b43_phy_read(dev, B43_PHY_AC_RFCTL_CMD) & 0xfc38;
	b43_phy_write(dev, 0x415, 0);
	b43_phy_write(dev, 0x40e, 0);
	b43_phy_write(dev, 0x40c, 0x2000);
	b43_phy_write(dev, B43_PHY_AC_RFCTL_CMD, s408);
	b43_phy_write(dev, 0x417, 0);
	b43_phy_write(dev, 0x416, 0xd);
	b43_phy_write(dev, 0x728, s728 & 0x7e7f);
	b43_phy_set(dev, 0x720, 0x180);
	b43_phy_write(dev, B43_PHY_AC_RFCTL_CMD, s408);
	b43_phy_write(dev, B43_PHY_AC_RFCTL_CMD, s408 | 1);
	udelay(1);
	b43_phy_write(dev, B43_PHY_AC_RFCTL_CMD, s408);

	for (i = 0; i < ARRAY_SIZE(b43_radio_2069r4_prefregs); i++)
		b43_radio_write(dev, b43_radio_2069r4_prefregs[i][0],
				b43_radio_2069r4_prefregs[i][1]);

	b43_radio_set(dev, 0x96b, 0x0800);
	b43_radio_set(dev, 0x96b, 0x4000);
	b43_radio_set(dev, 0x96c, 0x0800);
	b43_radio_set(dev, 0x96b, 0x8000);
	b43_radio_set(dev, 0x96b, 0x1000);
	b43_radio_set(dev, 0x96b, 0x0004);
	b43_radio_set(dev, 0x407, 0x0002);
	b43_radio_set(dev, 0x55e, 0x0010);

	cores = b43_phy_ac_num_cores(dev);
	for (core = 0; core < cores; core++) {
		u16 c = core << 9;

		b43_radio_maskset(dev, 0x126 | c, ~0x300, 0x100);
		b43_radio_maskset(dev, 0x127 | c, ~0x003, 0x002);
		b43_radio_mask(dev, 0x06f | c, ~0x004);
		b43_radio_mask(dev, 0x06f | c, ~0x001);
		b43_radio_mask(dev, 0x06f | c, ~0x002);
		b43_radio_mask(dev, 0x065 | c, ~0x001);
	}

	b43_radio_mask(dev, 0x40c, ~0x10);
	b43_phy_write(dev, B43_PHY_AC_RFCTL_CMD, s408 | 6);
	udelay(100);
	b43_radio_set(dev, 0x40c, 0x10);
	b43_phy_write(dev, 0x417, 0xd);
	b43_phy_write(dev, B43_PHY_AC_RFCTL_CMD, s408 | 2);
	b43_phy_write(dev, 0x728, s728 | 0x180);
	udelay(100);
	b43_phy_write(dev, 0x417, 4);
	b43_phy_write(dev, 0x728, s728 & 0xfeff);

	b43info(dev->wl, "phy_ac: radio 2069 init done (%u cores)\n", cores);
}

/*
 * Resistor calibration: the vendor's default path when SPROM boardflags3
 * bits 3 and 13 are clear. bcma does not parse boardflags3, so we assume 0.
 */
static bool b43_radio_2069_rcal(struct b43_wldev *dev)
{
	u16 v = 0;
	int i;

	b43_radio_set(dev, 0x8ea, 0x40);
	b43_radio_set(dev, 0x8ea, 0x80);
	b43_radio_mask(dev, 0x8ed, ~0x600);
	b43_radio_mask(dev, 0x8ed, ~0x1800);
	b43_radio_set(dev, 0x548, 0x1);
	b43_radio_write(dev, 0x549, 0);
	b43_radio_write(dev, 0x54a, 0);
	b43_radio_write(dev, 0x54b, 0);
	b43_radio_write(dev, 0x54c, 0);
	b43_radio_mask(dev, 0x40b, ~0x1);
	udelay(1);
	b43_radio_set(dev, 0x40b, 0x1);
	for (i = 0; i < 100; i++) {
		udelay(10);
		v = b43_radio_read(dev, 0x40b);
		if (v & 0x8)
			break;
	}
	b43_radio_read(dev, 0x40b);
	b43_radio_mask(dev, 0x548, ~0x1);
	b43_radio_mask(dev, 0x8ea, ~0x40);
	b43_radio_mask(dev, 0x8ea, ~0x80);
	b43_radio_mask(dev, 0x40b, ~0x1);

	b43info(dev->wl, "phy_ac: RCAL %s after %d polls (0x40b=%04x)\n",
		(v & 0x8) ? "done" : "TIMEOUT", i, v);
	return v & 0x8;
}

/* RC calibration (vendor FUN_0019665e), radio type 0 values. */
static void b43_radio_2069_rccal(struct b43_wldev *dev)
{
	static const u8 cal_a[3] = { 1, 0, 0 };
	static const u8 cal_b[3] = { 0, 2, 1 };
	static const u8 cal_c[3] = { 0x1c, 0x70, 0x40 };
	static const u16 cal_d[3] = { 0x14a, 0x101, 0x11a };
	u8 core, cores = b43_phy_ac_num_cores(dev);
	u16 v, r1, r2;
	int step, i;
	bool done;

	b43_radio_set(dev, 0x8ea, 0x80);
	b43_radio_maskset(dev, 0x8ed, ~0x600, 0x400);

	for (step = 0; step < 3; step++) {
		b43_radio_maskset(dev, 0x410, ~0x1000, cal_a[step] << 12);
		b43_radio_maskset(dev, 0x410, ~0x0018, cal_b[step] << 3);
		b43_radio_maskset(dev, 0x411, 0x00ff, cal_c[step] << 8);
		b43_radio_write(dev, 0x412, cal_d[step]);
		if (step == 2) {
			for (core = 0; core < cores; core++) {
				b43_radio_mask(dev, 0x11d | (core << 9), ~0x4);
				b43_radio_set(dev, 0x171 | (core << 9), 0x2000);
			}
		}
		b43_radio_mask(dev, 0x410, ~0x1);
		udelay(1);
		b43_radio_set(dev, 0x410, 0x1);
		udelay(35);
		b43_radio_set(dev, 0x411, 0x1);

		done = false;
		for (i = 0; i < 100; i++) {
			udelay(100);
			if (b43_radio_read(dev, 0x413) & 0x10) {
				done = true;
				break;
			}
		}
		b43_radio_mask(dev, 0x411, ~0x1);

		if (done) {
			if (step == 0) {
				r1 = b43_radio_read(dev, 0x414);
				r2 = b43_radio_read(dev, 0x415);
				b43info(dev->wl, "phy_ac: RCCAL step 0: %04x %04x -> %02x\n",
					r1, r2, (((u32)(r2 - r1)) * 0xc1 >> 8) & 0xff);
			} else if (step == 1) {
				v = b43_radio_read(dev, 0x416);
				for (core = 0; core < cores; core++) {
					b43_radio_maskset(dev, 0x126 | (core << 9),
							  ~0x1f, v & 0x1f);
					b43_radio_maskset(dev, 0x043 | (core << 9),
							  ~0x1f, v & 0x1f);
				}
				b43info(dev->wl, "phy_ac: RCCAL step 1: %04x\n", v);
			} else {
				v = b43_radio_read(dev, 0x416);
				for (core = 0; core < cores; core++)
					b43_radio_mask(dev, 0x171 | (core << 9),
						       ~0x2000);
				b43info(dev->wl, "phy_ac: RCCAL step 2: %04x\n", v);
			}
		} else {
			b43info(dev->wl, "phy_ac: RCCAL step %d TIMEOUT\n", step);
		}
		b43_radio_mask(dev, 0x410, ~0x1);
	}
	b43_radio_mask(dev, 0x8ea, ~0x80);
}

/* Radio power-up (vendor wlc_phy_switch_radio_acphy, on, radio type 0). */
static void b43_radio_2069_power_up(struct b43_wldev *dev)
{
	b43_radio_2069_init(dev);
	b43_phy_mask(dev, 0x16b, ~0x400);
	udelay(3);
	b43_phy_write(dev, 0x175, 0);
	udelay(3);
	b43_radio_2069_rcal(dev);
	b43_radio_2069_rccal(dev);
}

/*
 * Decompiled from wlc_phy_switch_radio_acphy(), resolved specifically for
 * acphychipid == 0x4360 (this chip - see notes/session log). The power-down
 * sequence is fully resolved and reproduced faithfully below. The power-up
 * sequence in the vendor driver branches further on a radio-type field we
 * have not yet fully mapped to a b43-visible quantity, so it is NOT
 * reproduced here - .switch_analog(dev, true) is currently a stub. This
 * means we expect probe/attach to get further than before but TX/RX will
 * not work until switch-on and PHY .init are implemented.
 */
static void b43_radio_2069_power_down(struct b43_wldev *dev)
{
	b43_phy_write(dev, 0x173e, 0x1c00);
	b43_phy_write(dev, 0x1739, 0);
	b43_phy_write(dev, 0x173a, 0);
	b43_phy_write(dev, 0x1725, 0x1fff);
	b43_phy_write(dev, 0x1729, 0);
	b43_phy_write(dev, 0x1721, 0xffff);
	b43_phy_write(dev, 0x1728, 0);
	b43_phy_write(dev, 0x1720, 0x3ff);
	b43_phy_maskset(dev, B43_PHY_AC_RFCTL_CMD, ~2, 0);
	b43_phy_write(dev, 0x417, 0);
	b43_phy_write(dev, 0x416, 1);
	dev->phy.ac->radio_on = false;
	b43info(dev->wl, "phy_ac: radio powered down\n");
}

/* The vendor's radio on/off lives in software_rfkill; nothing extra here yet. */
static void b43_phy_ac_op_switch_analog(struct b43_wldev *dev, bool on)
{
	if (!on)
		b43_radio_2069_power_down(dev);
}

static void b43_phy_ac_op_software_rfkill(struct b43_wldev *dev, bool blocked)
{
	struct b43_phy_ac *phy_ac = dev->phy.ac;

	b43info(dev->wl, "phy_ac: software_rfkill(blocked=%d)\n", blocked);
	if (blocked) {
		b43_radio_2069_power_down(dev);
		return;
	}
	if (phy_ac->radio_on)
		return;
	if (dev->phy.radio_ver != 0x2069 || dev->phy.radio_rev != 4) {
		b43err(dev->wl, "phy_ac: no power-up sequence for radio %04x rev %u\n",
		       dev->phy.radio_ver, dev->phy.radio_rev);
		return;
	}
	b43_radio_2069_power_up(dev);
	phy_ac->radio_on = true;
}

static void b43_phy_ac_op_prepare_structs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_ac *phy_ac = phy->ac;

	b43info(dev->wl, "phy_ac: prepare_structs\n");
	memset(phy_ac, 0, sizeof(*phy_ac));
}

static bool b43_ac_replay;
module_param_named(ac_replay, b43_ac_replay, bool, 0444);
MODULE_PARM_DESC(ac_replay, "AC-PHY diagnostic: apply the vendor driver's channel 6 PHY/radio state");

static void b43_phy_ac_replay_ch6(struct b43_wldev *dev);

/*
 * Radio registers written from entries [2..51] of the 2069 tuning table, in
 * table order. Resolved for acphychipid 0x4360 from the vendor driver's
 * channel-set code (see notes/05-channel-tuning.md).
 */
static const u16 b43_radio_2069_tune_regs[B43_RADIO_2069_TUNE_REGS] = {
	0x8e0, 0x8e1, 0x8dd, 0x8dc, 0x8e6, 0x8e7, 0x8c4, 0x8c5, 0x8e5, 0x8eb,
	0x8d6, 0x113, 0x8db, 0x8da, 0x8d7, 0x885, 0x886, 0x887, 0x8d9, 0x8d8,
	0x8c9, 0x8ca, 0x8cc, 0x8c7, 0x8c8, 0x892, 0x894, 0x895, 0x896, 0x897,
	0x899, 0x89a, 0x89b, 0x89c, 0x112, 0x629, 0x65b, 0x65e, 0x668, 0x11a,
	0x11b, 0x719, 0x630, 0x65c, 0x662, 0x66d, 0x893, 0x145, 0x146, 0x723,
};

static const struct b43_radio_2069_chan *
b43_radio_2069_find_chan(struct b43_wldev *dev, unsigned int channel)
{
	unsigned int i;

	if (dev->phy.radio_ver != 0x2069 || dev->phy.radio_rev != 4)
		return NULL;
	for (i = 0; i < b43_radio_2069r4_chans_n; i++)
		if (b43_radio_2069r4_chans[i].channel == channel)
			return &b43_radio_2069r4_chans[i];
	return NULL;
}

/* Synthesizer VCO calibration kick. */
static void b43_radio_2069_vcocal(struct b43_wldev *dev)
{
	b43_radio_mask(dev, 0x8e5, ~0x4000);
	b43_radio_mask(dev, 0x8d0, ~0x0001);
	b43_radio_mask(dev, 0x8e8, ~0x0040);
	b43_radio_mask(dev, 0x8dc, ~0x2000);
	udelay(11);
	b43_radio_set(dev, 0x8d0, 0x0001);
	b43_radio_set(dev, 0x8e8, 0x0040);
	udelay(1);
	b43_radio_set(dev, 0x8dc, 0x2000);
}

/* Reset clear-channel assessment (PHY rev 1 variant). */
static void b43_phy_ac_resetcca(struct b43_wldev *dev)
{
	u16 bbcfg;

	b43_phy_force_clock(dev, true);
	bbcfg = b43_phy_read(dev, B43_PHY_AC_BBCFG);
	b43_phy_write(dev, B43_PHY_AC_BBCFG, bbcfg | B43_PHY_AC_BBCFG_RSTCCA);
	udelay(1);
	b43_phy_write(dev, B43_PHY_AC_BBCFG, bbcfg & ~B43_PHY_AC_BBCFG_RSTCCA);
	b43_phy_force_clock(dev, false);
	udelay(2);
}

/*
 * Follows the vendor driver's channel-set sequence for radio 2069 rev 4 at
 * 20 MHz. Not yet ported: carrier-search suppression during the switch,
 * the 5 GHz PLL setup, TX gain tables, and the per-channel PHY tweaks that
 * follow the BW registers.
 */
static int b43_phy_ac_op_switch_channel(struct b43_wldev *dev,
					unsigned int new_channel)
{
	struct b43_phy_ac *phy_ac = dev->phy.ac;
	const struct b43_radio_2069_chan *e;
	bool is_5ghz = b43_current_band(dev->wl) == NL80211_BAND_5GHZ;
	u16 save;
	int i;

	e = b43_radio_2069_find_chan(dev, new_channel);
	if (!e) {
		b43err(dev->wl, "phy_ac: no tuning data for channel %u (radio %04x rev %u)\n",
		       new_channel, dev->phy.radio_ver, dev->phy.radio_rev);
		return -ESRCH;
	}
	if (is_5ghz) {
		b43dbg(dev->wl, "phy_ac: 5 GHz tuning not implemented (channel %u)\n",
			new_channel);
		return -EOPNOTSUPP;
	}
	b43dbg(dev->wl, "phy_ac: switch_channel(%u) -> %u MHz\n",
		new_channel, e->freq);

	save = b43_phy_read(dev, 0x19e);
	b43_phy_set(dev, 0x19e, 0x3);

	b43_phy_maskset(dev, B43_PHY_AC_BANDCTL, ~0x0100, is_5ghz ? 0x0100 : 0);

	if (!phy_ac->chan_set || phy_ac->last_5ghz != is_5ghz) {
		b43_phy_set(dev, 0x728, 0x0100);
		udelay(1);
		b43_phy_mask(dev, 0x728, ~0x0100);
	}
	phy_ac->chan_set = true;
	phy_ac->last_5ghz = is_5ghz;

	for (i = 0; i < B43_RADIO_2069_TUNE_REGS; i++)
		b43_radio_write(dev, b43_radio_2069_tune_regs[i], e->radio[i]);
	if (new_channel == 4) {
		b43_radio_write(dev, 0x8d6, 0x0ce4);
		b43_radio_maskset(dev, 0x8ec, ~0x0070, 0x0050);
	}
	b43_radio_set(dev, 0x645, 0x7000);
	b43_radio_write(dev, 0x723, 0x83e0);
	b43_radio_2069_vcocal(dev);

	b43_phy_maskset(dev, 0x19e, ~0x3, save & 0x3);

	for (i = 0; i < 6; i++)
		b43_phy_write(dev, B43_PHY_AC_BW1A + i, e->bw[i]);

	if (b43_ac_replay && new_channel == 6)
		b43_phy_ac_replay_ch6(dev);

	b43_phy_ac_resetcca(dev);
	return 0;
}

/*
 * Not a real PHY init yet - no calibration, no channel setup. This exists
 * purely so .init is non-NULL (b43 requires it) and to let us observe how
 * far probe/attach gets on real hardware with just power-up wired in.
 */
static void b43_phy_ac_write_table(struct b43_wldev *dev,
				   const struct b43_phy_ac_tbl *t)
{
	unsigned int i;
	u32 v;

	b43_phy_write(dev, B43_PHY_AC_TABLE_ID, t->id);
	b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, t->offset);
	for (i = 0; i < t->count; i++) {
		switch (t->width) {
		case 8:
			b43_phy_write(dev, B43_PHY_AC_TABLE_DATA1,
				      ((const u8 *)t->data)[i]);
			break;
		case 16:
			b43_phy_write(dev, B43_PHY_AC_TABLE_DATA1,
				      ((const u16 *)t->data)[i]);
			break;
		case 32:
			v = ((const u32 *)t->data)[i];
			b43_phy_write(dev, B43_PHY_AC_TABLE_DATA2, v >> 16);
			b43_phy_write(dev, B43_PHY_AC_TABLE_DATA1, v & 0xffff);
			break;
		}
	}
}

/*
 * PHY init for PHY rev 0/1 (vendor FUN_001a1202): RF-control override
 * defaults, then the acphytbl_info_rev0 table set.
 */
static void b43_phy_ac_tables_init(struct b43_wldev *dev)
{
	static const u16 clear_regs[] = {
		0x173e, 0x1725, 0x1722, 0x1723, 0x1724, 0x1725, 0x1726, 0x1727,
		0x1750,
	};
	unsigned int i;
	u16 save;

	b43_phy_write(dev, 0x410, 0x77);
	for (i = 0; i < ARRAY_SIZE(clear_regs); i++)
		b43_phy_write(dev, clear_regs[i], 0);
	b43_phy_write(dev, 0x1728, 0x80);
	b43_phy_write(dev, 0x1720, 0x180);
	b43_phy_write(dev, 0x1729, 0);
	b43_phy_write(dev, 0x1721, 0x5000);
	b43_phy_write(dev, 0x173a, b43_phy_read(dev, 0x73a) | 0x100);
	b43_phy_write(dev, 0x1725, b43_phy_read(dev, 0x725) | 0x400);

	save = b43_phy_read(dev, 0x19e);
	b43_phy_set(dev, 0x19e, 0x2);
	for (i = 0; i < b43_phy_ac_tbls_rev0_n; i++)
		b43_phy_ac_write_table(dev, &b43_phy_ac_tbls_rev0[i]);
	b43_phy_maskset(dev, 0x19e, ~0x2, save & 0x2);

	b43_phy_write(dev, 0x1645, 0x25c);
	b43info(dev->wl, "phy_ac: wrote %u PHY tables\n", b43_phy_ac_tbls_rev0_n);
}

/*
 * First-init PHY register setup (vendor FUN_001a1924), resolved for PHY rev
 * 0/1. Not ported yet: wlc_phy_hwaci_setup_acphy (interference mitigation).
 */
static void b43_phy_ac_first_init(struct b43_wldev *dev)
{
	bool is_2ghz = b43_current_band(dev->wl) == NL80211_BAND_2GHZ;
	u8 core, cores = b43_phy_ac_num_cores(dev);
	static const u16 core_reg[3] = { 0x690, 0x890, 0xa90 };

	b43_phy_set(dev, 0x19e, 0x1c0);
	if (is_2ghz)
		b43_phy_write(dev, 0x3c4, 0x668);
	b43_phy_set(dev, 0x19e, 0x200);
	b43_phy_maskset(dev, 0x19e, ~0x3c, 0x10);
	b43_phy_write(dev, 0x1f2, 0xc8);
	b43_phy_write(dev, 0x026, 0x92);
	b43_phy_write(dev, 0x1ed, 0x50);
	b43_phy_write(dev, 0x025, 0x30);

	if (dev->dev->bus_type == B43_BUS_BCMA)
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL,
			      bcma_aread32(dev->dev->bdev, BCMA_IOCTL) |
			      B43_BCMA_IOCTL_MACPHYCLKEN);

	b43_phy_mask(dev, 0x40f, ~0x200);
	b43_phy_mask(dev, 0x2f1, ~0x20);
	b43_phy_mask(dev, 0x2ed, ~0x20);
	b43_phy_mask(dev, 0x2f9, ~0x20);
	b43_phy_mask(dev, 0x2f5, ~0x20);
	b43_phy_maskset(dev, 0x2ef, ~0xff, 0x55);
	b43_phy_maskset(dev, 0x2eb, ~0xff, 0x55);
	b43_phy_maskset(dev, 0x2f7, ~0xff, 0x55);
	b43_phy_maskset(dev, 0x2f3, ~0xff, 0x55);

	b43_phy_write(dev, 0x400, 0);
	b43_phy_mask(dev, 0x1ca, ~0x1000);
	b43_phy_ac_resetcca(dev);
	b43_phy_set(dev, 0x072, 0x4);
	b43_phy_mask(dev, 0x1b0, ~0x20);
	b43_phy_set(dev, 0x1b1, 0x1000);
	b43_phy_mask(dev, 0x1b6, 0x7fff);
	for (core = 0; core < cores && core < 3; core++) {
		b43_phy_set(dev, core_reg[core], 0x200);
		b43_phy_set(dev, core_reg[core], 0x400);
	}
	b43_phy_write(dev, 0x1e6, 0x30);
	b43_phy_write(dev, 0x358, 0xc07f);

	b43info(dev->wl, "phy_ac: first-init registers done\n");
}

#include "phy_ac_replay.h"

/* 2.4 GHz AGC tables as written by the vendor driver on this board. */
static const u8 b43_ac_agc_lna1_gain[] = { 0xff, 0xff, 0x06, 0x0c, 0x12, 0x19 };
static const u8 b43_ac_agc_lna1_code[] = { 1, 1, 2, 3, 4, 5 };
static const u8 b43_ac_agc_lna1_max[] = { 0x0b, 0x0c, 0x0e, 0x20, 0x24, 0x28 };
static const u8 b43_ac_agc_lna2_gain[] = { 0xf8, 0xf8, 0xfc, 0xff, 0x02, 0x02, 0x02 };
static const u8 b43_ac_agc_lna2_code[] = { 1, 1, 2, 3, 4, 4, 4 };
static const u8 b43_ac_agc_lna2_max[] = { 0, 0, 0, 3, 3, 3, 3 };
static const u8 b43_ac_agc_elna_c0[] = { 0x0e, 0x0e };
static const u8 b43_ac_agc_elna_c1[] = { 0x0c, 0x0c };

static const struct b43_phy_ac_tbl b43_ac_agc_tbls_2g[] = {
	{ b43_ac_agc_lna1_gain, 6, 0x44, 0x08, 8 },
	{ b43_ac_agc_lna1_code, 6, 0x45, 0x08, 8 },
	{ b43_ac_agc_lna1_gain, 6, 0x64, 0x08, 8 },
	{ b43_ac_agc_lna1_code, 6, 0x65, 0x08, 8 },
	{ b43_ac_agc_lna1_max, 6, 0x0b, 0x08, 8 },
	{ b43_ac_agc_lna2_gain, 7, 0x44, 0x10, 8 },
	{ b43_ac_agc_lna2_code, 7, 0x45, 0x10, 8 },
	{ b43_ac_agc_lna2_gain, 7, 0x64, 0x10, 8 },
	{ b43_ac_agc_lna2_code, 7, 0x65, 0x10, 8 },
	{ b43_ac_agc_lna2_max, 7, 0x0b, 0x10, 8 },
	{ b43_ac_agc_elna_c0, 2, 0x44, 0x00, 8 },
	{ b43_ac_agc_elna_c1, 2, 0x64, 0x00, 8 },
};

static void b43_phy_ac_replay_ch6(struct b43_wldev *dev)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(b43_ac_replay_radio); i++)
		b43_radio_write(dev, b43_ac_replay_radio[i][0],
				b43_ac_replay_radio[i][1]);
	b43_radio_2069_vcocal(dev);
	for (i = 0; i < ARRAY_SIZE(b43_ac_replay_phy); i++)
		b43_phy_write(dev, b43_ac_replay_phy[i][0],
			      b43_ac_replay_phy[i][1]);
	for (i = 0; i < ARRAY_SIZE(b43_ac_replay_tbl); i++) {
		b43_phy_write(dev, B43_PHY_AC_TABLE_ID, b43_ac_replay_tbl[i].id);
		b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, b43_ac_replay_tbl[i].off);
		if (b43_ac_replay_tbl[i].width == 32)
			b43_phy_write(dev, B43_PHY_AC_TABLE_DATA2,
				      b43_ac_replay_tbl[i].val >> 16);
		b43_phy_write(dev, B43_PHY_AC_TABLE_DATA1,
			      b43_ac_replay_tbl[i].val & 0xffff);
	}
	for (i = 0; i < ARRAY_SIZE(b43_ac_agc_tbls_2g); i++)
		b43_phy_ac_write_table(dev, &b43_ac_agc_tbls_2g[i]);
	for (i = 0; i < ARRAY_SIZE(b43_ac_replay_shm); i++) {
		if (b43_ac_replay_shm[i].bits == 32)
			b43_shm_write32(dev, b43_ac_replay_shm[i].routing,
					b43_ac_replay_shm[i].off,
					b43_ac_replay_shm[i].val);
		else
			b43_shm_write16(dev, b43_ac_replay_shm[i].routing,
					b43_ac_replay_shm[i].off,
					b43_ac_replay_shm[i].val);
	}
	b43info(dev->wl, "phy_ac: replayed vendor ch6 state (%zu radio, %zu PHY regs, %zu table entries)\n",
		ARRAY_SIZE(b43_ac_replay_radio), ARRAY_SIZE(b43_ac_replay_phy),
		ARRAY_SIZE(b43_ac_replay_tbl));
}

static int b43_phy_ac_op_init(struct b43_wldev *dev)
{
	if (dev->phy.rev <= 1) {
		b43_phy_ac_tables_init(dev);
		b43_phy_ac_first_init(dev);
	}
	else
		b43err(dev->wl, "phy_ac: no table set for PHY rev %u\n",
		       dev->phy.rev);

	b43info(dev->wl, "phy_ac: init (core_rev %u, radio24=%d, chip %04x, board %04x, radio_on %d)\n",
		dev->dev->core_rev, b43_phy_ac_use_radio24(dev),
		dev->dev->chip_id, dev->dev->board_type, dev->phy.ac->radio_on);

	return 0;
}

/* Ucode MAC statistics block (wl's M_UCODE_MACSTAT), decoded by tools/macstat_decode.pl. */
static void b43_phy_ac_log_macstat(struct b43_wldev *dev)
{
	char line[64 * 5 + 1];
	int i;

	for (i = 0; i < 64; i++)
		snprintf(line + i * 5, 6, " %04x",
			 b43_shm_read16(dev, B43_SHM_SHARED, 0xe0 + i * 2));
	b43info(dev->wl, "phy_ac: macstat:%s\n", line);
}

/* Diagnostic: MAC, interrupt and DMA state, every 15 seconds. */
static void b43_phy_ac_op_pwork_15sec(struct b43_wldev *dev)
{
	struct b43_dmaring *rx = dev->dma.rx_ring;
	struct b43_dmaring *tx = dev->dma.tx_ring_AC_BE;

	b43info(dev->wl, "phy_ac: MACCTL=%08x IRQ reason=%08x mask=%08x pio=%d\n",
		b43_read32(dev, B43_MMIO_MACCTL),
		b43_read32(dev, B43_MMIO_GEN_IRQ_REASON),
		b43_read32(dev, B43_MMIO_GEN_IRQ_MASK),
		dev->__using_pio_transfers);
	if (!dev->__using_pio_transfers && rx && tx)
		b43info(dev->wl, "phy_ac: DMA rx status=%08x tx(BE) status=%08x\n",
			b43_read32(dev, rx->mmio_base + B43_DMA64_RXSTATUS),
			b43_read32(dev, tx->mmio_base + B43_DMA64_TXSTATUS));
	b43_phy_ac_log_macstat(dev);
}

static unsigned int b43_phy_ac_op_get_default_chan(struct b43_wldev *dev)
{
	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		return 11;
	return 36;
}

static enum b43_txpwr_result
b43_phy_ac_op_recalc_txpower(struct b43_wldev *dev, bool ignore_tssi)
{
	return B43_TXPWR_RES_DONE;
}

static void b43_phy_ac_op_adjust_txpower(struct b43_wldev *dev)
{
}

/**************************************************
 * PHY ops struct
 **************************************************/

const struct b43_phy_operations b43_phyops_ac = {
	.allocate		= b43_phy_ac_op_allocate,
	.free			= b43_phy_ac_op_free,
	.prepare_structs	= b43_phy_ac_op_prepare_structs,
	.init			= b43_phy_ac_op_init,
	.phy_write		= b43_phy_ac_op_write,
	.phy_maskset		= b43_phy_ac_op_maskset,
	.radio_read		= b43_phy_ac_op_radio_read,
	.radio_write		= b43_phy_ac_op_radio_write,
	.software_rfkill	= b43_phy_ac_op_software_rfkill,
	.switch_analog		= b43_phy_ac_op_switch_analog,
	.switch_channel		= b43_phy_ac_op_switch_channel,
	.get_default_chan	= b43_phy_ac_op_get_default_chan,
	.recalc_txpower		= b43_phy_ac_op_recalc_txpower,
	.adjust_txpower		= b43_phy_ac_op_adjust_txpower,
	.pwork_15sec		= b43_phy_ac_op_pwork_15sec,
};
