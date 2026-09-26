// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Broadcom B43 wireless driver
 * IEEE 802.11ac AC-PHY support
 *
 * Copyright (c) 2015 Rafał Miłecki <zajec5@gmail.com>
 */

#include "b43.h"
#include "phy_ac.h"

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
static void b43_phy_ac_op_switch_analog(struct b43_wldev *dev, bool on)
{
	b43info(dev->wl, "phy_ac: switch_analog(%s)\n", on ? "on" : "off");

	if (on) {
		/* TODO: vendor radio power-up sequence not yet resolved. */
		return;
	}

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
	b43info(dev->wl, "phy_ac: switch_analog(off) done\n");
}

static void b43_phy_ac_op_software_rfkill(struct b43_wldev *dev, bool blocked)
{
	b43info(dev->wl, "phy_ac: software_rfkill(blocked=%d)\n", blocked);
	b43_phy_ac_op_switch_analog(dev, !blocked);
}

static void b43_phy_ac_op_prepare_structs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_ac *phy_ac = phy->ac;

	b43info(dev->wl, "phy_ac: prepare_structs\n");
	memset(phy_ac, 0, sizeof(*phy_ac));
}

/*
 * Channel switching is not implemented yet. b43_switch_channel() calls this
 * op unconditionally, so it must exist. Touches no hardware.
 */
static int b43_phy_ac_op_switch_channel(struct b43_wldev *dev,
					unsigned int new_channel)
{
	b43info(dev->wl, "phy_ac: switch_channel(%u) - not implemented, no-op\n",
		new_channel);
	return 0;
}

/*
 * Not a real PHY init yet - no calibration, no channel setup. This exists
 * purely so .init is non-NULL (b43 requires it) and to let us observe how
 * far probe/attach gets on real hardware with just power-up wired in.
 */
static int b43_phy_ac_op_init(struct b43_wldev *dev)
{
	b43info(dev->wl, "phy_ac: init (core_rev %u, radio24=%d)\n",
		dev->dev->core_rev, b43_phy_ac_use_radio24(dev));
	b43_phy_ac_op_switch_analog(dev, true);
	b43info(dev->wl, "phy_ac: init done\n");

	return 0;
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
};
