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

#ifdef CONFIG_B43_PHY_AC_DEBUG
#include <linux/debugfs.h>
#include <linux/seq_file.h>

/**************************************************
 * Debug: live PHY/radio register access.
 * /sys/kernel/debug/b43ac/{phy,radio}: write "addr" to select, "addr val"
 * to write; read returns "addr val" for the selected register.
 **************************************************/

static struct dentry *b43_ac_dbg_dir;
static struct b43_wldev *b43_ac_dbg_dev;
static u16 b43_ac_dbg_addr[6];

static ssize_t b43_ac_dbg_read(struct file *f, char __user *ubuf, size_t len,
			       loff_t *ppos)
{
	long which = (long)f->private_data;
	struct b43_wldev *dev = b43_ac_dbg_dev;
	u16 addr = b43_ac_dbg_addr[which], val;
	char buf[16];
	int n;

	if (*ppos)
		return 0;
	if (!dev)
		return -ENODEV;
	mutex_lock(&dev->wl->mutex);
	if (b43_status(dev) < B43_STAT_INITIALIZED) {
		mutex_unlock(&dev->wl->mutex);
		return -ENODEV;
	}
	if (which == 5)
		val = b43_shm_read16(dev, B43_SHM_SCRATCH, addr);
	else if (which == 4)
		val = b43_shm_read16(dev, B43_SHM_HW, addr);
	else if (which == 3)
		val = b43_read16(dev, addr);
	else if (which == 2)
		val = b43_shm_read16(dev, B43_SHM_SHARED, addr);
	else {
		bool susp = which == 0;

		if (susp)
			b43_mac_suspend(dev);
		val = which ? b43_radio_read(dev, addr) : b43_phy_read(dev, addr);
		if (susp)
			b43_mac_enable(dev);
	}
	mutex_unlock(&dev->wl->mutex);
	n = scnprintf(buf, sizeof(buf), "%04x %04x\n", addr, val);
	return simple_read_from_buffer(ubuf, len, ppos, buf, n);
}

static ssize_t b43_ac_dbg_write(struct file *f, const char __user *ubuf,
				size_t len, loff_t *ppos)
{
	long which = (long)f->private_data;
	struct b43_wldev *dev = b43_ac_dbg_dev;
	char buf[32];
	unsigned int addr, val;
	int n;

	if (!dev)
		return -ENODEV;
	if (len >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, len))
		return -EFAULT;
	buf[len] = 0;
	n = sscanf(buf, "%x %x", &addr, &val);
	if (n < 1 || addr > 0xffff || (n == 2 && val > 0xffff))
		return -EINVAL;
	b43_ac_dbg_addr[which] = addr;
	if (n == 2) {
		mutex_lock(&dev->wl->mutex);
		if (b43_status(dev) < B43_STAT_INITIALIZED) {
			mutex_unlock(&dev->wl->mutex);
			return -ENODEV;
		}
		if (which == 5)
			b43_shm_write16(dev, B43_SHM_SCRATCH, addr, val);
		else if (which == 4)
			b43_shm_write16(dev, B43_SHM_HW, addr, val);
		else if (which == 3)
			b43_write16(dev, addr, val);
		else if (which == 2)
			b43_shm_write16(dev, B43_SHM_SHARED, addr, val);
		else if (which)
			b43_radio_write(dev, addr, val);
		else {
			b43_mac_suspend(dev);
			b43_phy_write(dev, addr, val);
			b43_mac_enable(dev);
		}
		mutex_unlock(&dev->wl->mutex);
	}
	return len;
}

static int b43_ac_dbg_cc_show(struct seq_file *s, void *unused)
{
	static const struct { u16 off; const char *name; } regs[] = {
		{ 0x000, "chipid" }, { 0x028, "chipcontrol" }, { 0x02c, "chipstatus" },
		{ 0x064, "gpioout" }, { 0x068, "gpioouten" }, { 0x06c, "gpiocontrol" },
		{ 0x600, "pmucontrol" }, { 0x604, "pmucap" }, { 0x608, "pmustatus" },
		{ 0x60c, "res_state" }, { 0x618, "min_res_mask" }, { 0x61c, "max_res_mask" },
	};
	static const struct { u16 addr, data; const char *name; } ind[] = {
		{ BCMA_CC_PMU_CHIPCTL_ADDR, BCMA_CC_PMU_CHIPCTL_DATA, "chipctl" },
		{ BCMA_CC_PMU_REGCTL_ADDR, BCMA_CC_PMU_REGCTL_DATA, "regctl" },
		{ BCMA_CC_PMU_PLLCTL_ADDR, BCMA_CC_PMU_PLLCTL_DATA, "pllctl" },
	};
	struct b43_wldev *dev = b43_ac_dbg_dev;
	struct bcma_drv_cc *cc;
	int i, j;

	if (!dev || dev->dev->bus_type != B43_BUS_BCMA)
		return -ENODEV;
	cc = &dev->dev->bdev->bus->drv_cc;
	mutex_lock(&dev->wl->mutex);
	for (i = 0; i < ARRAY_SIZE(regs); i++)
		seq_printf(s, "%03x %-14s %08x\n", regs[i].off, regs[i].name,
			   bcma_cc_read32(cc, regs[i].off));
	for (i = 0; i < ARRAY_SIZE(ind); i++)
		for (j = 0; j < 16; j++) {
			bcma_cc_write32(cc, ind[i].addr, j);
			bcma_cc_read32(cc, ind[i].addr);
			seq_printf(s, "%s[%d] %08x\n", ind[i].name, j,
				   bcma_cc_read32(cc, ind[i].data));
		}
	/* PMU resource tables: dependency mask and up/down timer per resource */
	for (j = 0; j < 16; j++) {
		bcma_cc_write32(cc, 0x620, j);
		seq_printf(s, "res[%d] dep %08x updn %08x\n", j,
			   bcma_cc_read32(cc, 0x624), bcma_cc_read32(cc, 0x628));
	}
	/* raw chipcommon, without JTAG (0x30-0x3c) and the UART/flash blocks */
	for (j = 0x000; j < 0x700; j += 4) {
		if ((j >= 0x030 && j < 0x040) || (j >= 0x200 && j < 0x600))
			continue;
		seq_printf(s, "raw %03x %08x\n", j, bcma_cc_read32(cc, j));
	}
	for (j = 0; j < 5; j++) {
		static const u16 w[] = { 0x160, 0x164, 0x408, 0x500, 0x800 };

		seq_printf(s, "wrap %03x %08x\n", w[j],
			   bcma_aread32(dev->dev->bdev, w[j]));
	}
	mutex_unlock(&dev->wl->mutex);
	{
		struct ssb_sprom *sp = dev->dev->bus_sprom;

		seq_printf(s, "sprom rev %u boardflags lo %04x hi %04x flags2 lo %04x hi %04x board_rev %04x board_type %04x\n",
			   sp->revision, sp->boardflags_lo, sp->boardflags_hi,
			   sp->boardflags2_lo, sp->boardflags2_hi, sp->board_rev,
			   sp->board_type);
		seq_printf(s, "sprom ant_avail a %x bg %x txchain %x rxchain %x antswitch %x\n",
			   sp->ant_available_a, sp->ant_available_bg,
			   sp->txchain, sp->rxchain, sp->antswitch);
		seq_printf(s, "sprom fem2g tssipos %u extpa_gain %u pdet_range %u tr_iso %u antswlut %u\n",
			   sp->fem.ghz2.tssipos, sp->fem.ghz2.extpa_gain,
			   sp->fem.ghz2.pdet_range, sp->fem.ghz2.tr_iso,
			   sp->fem.ghz2.antswlut);
		seq_printf(s, "sprom fem5g tssipos %u extpa_gain %u pdet_range %u tr_iso %u antswlut %u\n",
			   sp->fem.ghz5.tssipos, sp->fem.ghz5.extpa_gain,
			   sp->fem.ghz5.pdet_range, sp->fem.ghz5.tr_iso,
			   sp->fem.ghz5.antswlut);
		/* Stock bcma has no SROM rev 11 extractor, so the lines above
		 * are rev 8 offsets applied to a rev 11 image. Decode the rev 11
		 * words here (offsets: Alessio Ferri's patch 0001, notes/112).
		 */
		if (sp->revision == 11) {
#define SP11(o) (bcma_read16(cc->core, BCMA_CC_SPROM + (o)) & 0xffff)
			u16 txrx = SP11(0xa8), f1 = SP11(0xaa), f2 = SP11(0xac);

			seq_printf(s, "sprom11 ant_avail a %x bg %x txchain %x rxchain %x antswitch %x\n",
				   SP11(0xa0) >> 8, SP11(0xa0) & 0xff,
				   txrx & 0xf, (txrx >> 4) & 0xf, txrx >> 8);
			seq_printf(s, "sprom11 femctrl %u | 2g tssipos %u epagain %u pdgain %u tworange %u papdcap %u | 5g tssipos %u epagain %u pdgain %u tworange %u papdcap %u gainctrlsph %u\n",
				   f1 >> 11, f1 & 1, (f1 >> 1) & 7, (f1 >> 4) & 0x1f,
				   (f1 >> 9) & 1, (f1 >> 10) & 1,
				   f2 & 1, (f2 >> 1) & 7, (f2 >> 4) & 0x1f,
				   (f2 >> 9) & 1, (f2 >> 10) & 1, f2 >> 11);
#undef SP11
		}
	}
	return 0;
}
static int b43_ac_dbg_cc_open(struct inode *inode, struct file *file)
{
	return single_open(file, b43_ac_dbg_cc_show, NULL);
}

static ssize_t b43_ac_dbg_cc_write(struct file *f, const char __user *ubuf,
				   size_t len, loff_t *ppos)
{
	struct b43_wldev *dev = b43_ac_dbg_dev;
	unsigned int off, val;
	char buf[32];

	if (!dev || dev->dev->bus_type != B43_BUS_BCMA)
		return -ENODEV;
	if (len >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, len))
		return -EFAULT;
	buf[len] = 0;
	if (sscanf(buf, "%x %x", &off, &val) != 2 || off > 0xffc || (off & 3))
		return -EINVAL;
	mutex_lock(&dev->wl->mutex);
	bcma_cc_write32(&dev->dev->bdev->bus->drv_cc, off, val);
	mutex_unlock(&dev->wl->mutex);
	return len;
}

static const struct file_operations b43_ac_dbg_cc_fops = {
	.owner		= THIS_MODULE,
	.open		= b43_ac_dbg_cc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
	.write		= b43_ac_dbg_cc_write,
};

/* Raw SPROM words, straight from the ChipCommon SPROM shadow (0x800..0xbff).
 * Read-only; for sharing with other AC-PHY reverse engineers (notes/105).
 */
static int b43_ac_dbg_sprom_show(struct seq_file *s, void *unused)
{
	struct b43_wldev *dev = b43_ac_dbg_dev;
	struct bcma_drv_cc *cc;
	unsigned int i;

	if (!dev || dev->dev->bus_type != B43_BUS_BCMA)
		return -ENODEV;
	cc = &dev->dev->bdev->bus->drv_cc;
	mutex_lock(&dev->wl->mutex);
	for (i = 0; i < 0x200; i++) {
		if ((i % 8) == 0)
			seq_printf(s, "%sword[%03x]:", i ? "\n" : "", i);
		seq_printf(s, " %04x",
			   bcma_read16(cc->core, BCMA_CC_SPROM + 2 * i) & 0xffff);
	}
	seq_putc(s, '\n');
	mutex_unlock(&dev->wl->mutex);
	return 0;
}

static int b43_ac_dbg_sprom_open(struct inode *inode, struct file *file)
{
	return single_open(file, b43_ac_dbg_sprom_show, NULL);
}

static const struct file_operations b43_ac_dbg_sprom_fops = {
	.owner		= THIS_MODULE,
	.open		= b43_ac_dbg_sprom_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static u16 b43_ac_dump_lo, b43_ac_dump_hi = 0x1fff;

static int b43_ac_dbg_phydump_show(struct seq_file *s, void *unused)
{
	struct b43_wldev *dev = b43_ac_dbg_dev;
	unsigned int r;

	if (!dev)
		return -ENODEV;
	mutex_lock(&dev->wl->mutex);
	if (b43_status(dev) < B43_STAT_INITIALIZED) {
		mutex_unlock(&dev->wl->mutex);
		return -ENODEV;
	}
	b43_mac_suspend(dev);
	for (r = b43_ac_dump_lo; r <= b43_ac_dump_hi; r++) {
		if (r >= 0x00f && r <= 0x011)
			continue;	/* table data ports auto-increment */
		seq_printf(s, "%04x %04x\n", r, b43_phy_read(dev, r));
	}
	b43_mac_enable(dev);
	mutex_unlock(&dev->wl->mutex);
	return 0;
}

static int b43_ac_dbg_phydump_open(struct inode *inode, struct file *file)
{
	return single_open_size(file, b43_ac_dbg_phydump_show, NULL, 128 * 1024);
}

static ssize_t b43_ac_dbg_phydump_write(struct file *f, const char __user *ubuf,
					size_t len, loff_t *ppos)
{
	char buf[32];
	unsigned int lo, hi;

	if (len >= sizeof(buf))
		return -EINVAL;
	if (copy_from_user(buf, ubuf, len))
		return -EFAULT;
	buf[len] = 0;
	if (sscanf(buf, "%x %x", &lo, &hi) != 2 || lo > hi || hi > 0x3fff)
		return -EINVAL;
	b43_ac_dump_lo = lo;
	b43_ac_dump_hi = hi;
	return len;
}

static const struct file_operations b43_ac_dbg_phydump_fops = {
	.owner		= THIS_MODULE,
	.open		= b43_ac_dbg_phydump_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
	.write		= b43_ac_dbg_phydump_write,
};

/* PHY tables wl writes during init: id, entries, 32-bit wide. notes/121 */
static const struct { u16 id, n; bool w32; } b43_ac_dump_tbls[] = {
	{0x01, 128, 0}, {0x02, 38, 0}, {0x03, 256, 1}, {0x04, 256, 0}, {0x05, 22, 1},
	{0x07, 1092, 0}, {0x0a, 96, 0}, {0x0b, 23, 0}, {0x0c, 120, 0}, {0x0e, 160, 1},
	{0x10, 1463, 1}, {0x21, 24, 1},
	{0x40, 128, 0}, {0x41, 128, 1}, {0x42, 128, 0}, {0x44, 42, 0}, {0x45, 42, 0}, {0x47, 64, 1}, {0x48, 64, 1},
	{0x60, 128, 0}, {0x61, 128, 1}, {0x62, 128, 0}, {0x64, 42, 0}, {0x65, 42, 0}, {0x67, 64, 1}, {0x68, 64, 1},
	{0x80, 128, 0}, {0x81, 128, 1}, {0x82, 128, 0}, {0x87, 64, 1}, {0x88, 64, 1},
};

static int b43_ac_dbg_tbldump_show(struct seq_file *s, void *unused)
{
	struct b43_wldev *dev = b43_ac_dbg_dev;
	unsigned int t, o;

	if (!dev)
		return -ENODEV;
	mutex_lock(&dev->wl->mutex);
	if (b43_status(dev) < B43_STAT_INITIALIZED) {
		mutex_unlock(&dev->wl->mutex);
		return -ENODEV;
	}
	b43_mac_suspend(dev);
	seq_printf(s, "wrap ioctl %08x reset_ctl %08x iostatus %08x\n",
		   bcma_aread32(dev->dev->bdev, BCMA_IOCTL),
		   bcma_aread32(dev->dev->bdev, BCMA_RESET_CTL),
		   bcma_aread32(dev->dev->bdev, BCMA_IOST));
	for (t = 0; t < ARRAY_SIZE(b43_ac_dump_tbls); t++) {
		for (o = 0; o < b43_ac_dump_tbls[t].n; o++) {
			u16 lo, hi = 0;

			b43_phy_write(dev, B43_PHY_AC_TABLE_ID, b43_ac_dump_tbls[t].id);
			b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, o);
			lo = b43_phy_read(dev, B43_PHY_AC_TABLE_DATA1);
			if (b43_ac_dump_tbls[t].w32)
				hi = b43_phy_read(dev, B43_PHY_AC_TABLE_DATA2);
			seq_printf(s, "%02x %04x %04x%04x\n", b43_ac_dump_tbls[t].id, o, hi, lo);
		}
	}
	b43_mac_enable(dev);
	mutex_unlock(&dev->wl->mutex);
	return 0;
}

static int b43_ac_dbg_tbldump_open(struct inode *inode, struct file *file)
{
	return single_open_size(file, b43_ac_dbg_tbldump_show, NULL, 1024 * 1024);
}

static const struct file_operations b43_ac_dbg_tbldump_fops = {
	.owner		= THIS_MODULE,
	.open		= b43_ac_dbg_tbldump_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int b43_ac_dbg_macdump_show(struct seq_file *s, void *unused)
{
	struct b43_wldev *dev = b43_ac_dbg_dev;
	unsigned int o;

	if (!dev)
		return -ENODEV;
	mutex_lock(&dev->wl->mutex);
	if (b43_status(dev) < B43_STAT_INITIALIZED) {
		mutex_unlock(&dev->wl->mutex);
		return -ENODEV;
	}
	/* Same ranges as tools/macdump (userspace, for wl). */
	for (o = 0; o < 0x1000; o += 2) {
		if ((o >= 0x160 && o < 0x180) || (o >= 0x200 && o < 0x400))
			continue;
		seq_printf(s, "%03x %04x\n", o, b43_read16(dev, o));
	}
	mutex_unlock(&dev->wl->mutex);
	return 0;
}
DEFINE_SHOW_ATTRIBUTE(b43_ac_dbg_macdump);

static const struct file_operations b43_ac_dbg_fops = {
	.owner	= THIS_MODULE,
	.open	= simple_open,
	.read	= b43_ac_dbg_read,
	.write	= b43_ac_dbg_write,
};
#endif /* CONFIG_B43_PHY_AC_DEBUG */

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

#ifdef CONFIG_B43_PHY_AC_DEBUG
	if (!b43_ac_dbg_dir) {
		b43_ac_dbg_dev = dev;
		b43_ac_dbg_dir = debugfs_create_dir("b43ac", NULL);
		debugfs_create_file("phy", 0600, b43_ac_dbg_dir, (void *)0L,
				    &b43_ac_dbg_fops);
		debugfs_create_file("radio", 0600, b43_ac_dbg_dir, (void *)1L,
				    &b43_ac_dbg_fops);
		debugfs_create_file("shm", 0600, b43_ac_dbg_dir, (void *)2L,
				    &b43_ac_dbg_fops);
		debugfs_create_file("phydump", 0600, b43_ac_dbg_dir, NULL,
				    &b43_ac_dbg_phydump_fops);
		debugfs_create_file("tbldump", 0400, b43_ac_dbg_dir, NULL,
				    &b43_ac_dbg_tbldump_fops);
		debugfs_create_file("macdump", 0400, b43_ac_dbg_dir, NULL,
				    &b43_ac_dbg_macdump_fops);
		debugfs_create_file("mmio16", 0600, b43_ac_dbg_dir, (void *)3L,
				    &b43_ac_dbg_fops);
		debugfs_create_file("ihr", 0600, b43_ac_dbg_dir, (void *)4L,
				    &b43_ac_dbg_fops);
		debugfs_create_file("scr", 0600, b43_ac_dbg_dir, (void *)5L,
				    &b43_ac_dbg_fops);
		debugfs_create_file("cc", 0600, b43_ac_dbg_dir, NULL,
				    &b43_ac_dbg_cc_fops);
		debugfs_create_file("sprom", 0400, b43_ac_dbg_dir, NULL,
				    &b43_ac_dbg_sprom_fops);
	}
#endif
	return 0;
}

static void b43_phy_ac_op_free(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_ac *phy_ac = phy->ac;

#ifdef CONFIG_B43_PHY_AC_DEBUG
	if (b43_ac_dbg_dev == dev) {
		debugfs_remove_recursive(b43_ac_dbg_dir);
		b43_ac_dbg_dir = NULL;
		b43_ac_dbg_dev = NULL;
	}
#endif
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
MODULE_PARM_DESC(ac_replay, "ignored, kept so old command lines still load");

/* See notes/62: wl's real hostflags (HOSTF2/HOSTF3), which this port
 * never writes at all. Test flag, default off - unconfirmed live.
 */

/* See notes/64: HOSTF1 (SHM 0x5E), also never written. Test flag,
 * default off - a reasoned guess (EDCF|ACIW), not a captured wl value.
 */

/* Accepted and ignored: the boot service still passes them (notes/130-135). */
static uint b43_ac_por = 7;

/* Centre channel of the 80 MHz block a 5 GHz primary belongs to, 0 if none */
static unsigned int b43_phy_ac_80mhz_centre(unsigned int channel)
{
	static const u8 centre[] = { 42, 58, 106, 122, 138, 155 };
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(centre); i++)
		if (channel >= centre[i] - 6u && channel <= centre[i] + 6u &&
		    (channel - (centre[i] - 6u)) % 4 == 0)
			return centre[i];
	return 0;
}

/*
 * 80 MHz mode: wl's captured 80 MHz state (taken on the block 100-112, centre
 * 106), retuned to the centre of the primary's block. Only 100-112 is tested.
 */
static bool b43_phy_ac_is_80mhz(struct b43_wldev *dev, unsigned int channel)
{
	return b43_current_band(dev->wl) == NL80211_BAND_5GHZ &&
	       b43_phy_ac_80mhz_centre(channel);
}

/*
 * The 11ac chanspec of a primary channel as the microcode and the TX header
 * take it: channel, 0x1000 for 20 MHz, 0xc000 on 5 GHz. In 80 MHz mode the
 * centre channel, 0x2000 for the width and the primary's position in the
 * block in bits 10:8 (wl on channel 112: 0xe36a).
 */
u16 b43_phy_ac_chanspec(struct b43_wldev *dev, unsigned int channel)
{
	if (b43_phy_ac_is_80mhz(dev, channel)) {
		unsigned int centre = b43_phy_ac_80mhz_centre(channel);

		return 0xe000 | (((channel - (centre - 6)) / 4) << 8) | centre;
	}
	return channel | 0x1000 |
	       (b43_current_band(dev->wl) == NL80211_BAND_5GHZ ? 0xc000 : 0);
}
static void b43_radio_2069_vcocal(struct b43_wldev *dev);


/* 2.4 GHz TX gain table index applied on a channel switch; 0 = highest gain, the reset value 64 is too weak beyond a few metres. The stock power loop ran at 20-38 here (notes/138) */
#define B43_AC_TXIDX_2G	20
static void b43_phy_ac_txpwr_by_index(struct b43_wldev *dev, unsigned int idx);

module_param_named(ac_por, b43_ac_por, uint, 0444);
MODULE_PARM_DESC(ac_por, "ignored, kept so old command lines still load");

/* One 48-bit PHY table entry: three words through the third data port. */
static void b43_phy_ac_table_write48(struct b43_wldev *dev, u16 id, u16 offset,
				     const u16 *w)
{
	b43_phy_write(dev, B43_PHY_AC_TABLE_ID, id);
	b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, offset);
	b43_phy_write(dev, 0x011, w[0]);
	b43_phy_write(dev, 0x011, w[1]);
	b43_phy_write(dev, 0x011, w[2]);
}

/*
 * The 48-bit tables wl loads on 2.4 GHz and the trace decoder missed
 * (notes/139): the TX gain table 0x20, which hardware TX power control
 * indexes; the RF sequencer extension entry 0x33; and table 0x11, twelve
 * fixed cells, then 448 cells of the SROM's rpcal coefficient (here the
 * value wl computed for this board on 2.4 GHz), then four zero cells.
 */
static void b43_phy_ac_wide_tables_2g(struct b43_wldev *dev)
{
	static const u16 ext33[3] = { 0xe800, 0x0084, 0xd351 };
	static const u16 head11[12][3] = {
		{ 0x005b, 0, 0 }, { 0x8250, 0, 0 }, { 0xc338, 0, 0 },
		{ 0x4527, 1, 0 }, { 0xa6a1, 1, 0 }, { 0x081b, 2, 0 },
		{ 0x8a18, 2, 0 }, { 0x2c96, 3, 0 }, { 0x8e17, 3, 0 },
		{ 0x101b, 4, 0 }, { 0x0020, 0, 0 }, { 0x0020, 0, 0 },
	};
	static const u16 fill11[3] = { 0xd602, 0x007e, 0x4002 };
	static const u16 zero[3] = { 0, 0, 0 };
	unsigned int i;

	for (i = 0; i < 128; i++)
		b43_phy_ac_table_write48(dev, 0x20, i, b43_phy_ac_txgain_2g[i]);
	b43_phy_ac_table_write48(dev, 0x14, 0x33, ext33);
	for (i = 0; i < 12; i++)
		b43_phy_ac_table_write48(dev, 0x11, i, head11[i]);
	for (i = 12; i < 460; i++)
		b43_phy_ac_table_write48(dev, 0x11, i, fill11);
	for (i = 460; i < 464; i++)
		b43_phy_ac_table_write48(dev, 0x11, i, zero);
}

/*
 * RF sequencer extension (PHY table 0x14), entries 0x30-0x33, as wl writes
 * them on 5 GHz. The entries are 48 bits wide and go through the third data
 * port, 0x011, low word first; the trace decoder knew only 0x00f/0x010, so
 * they were never in the replayed state. Without 0x30-0x32 the receiver is
 * completely deaf on 5 GHz; 2.4 GHz does not need them. PHY tables survive
 * a driver reload and a PCI bus reset, which is why 5 GHz received after wl
 * had run once in the same boot (notes/139).
 */
/* The second sequencer's command lists (table 7 @ 0x30/0x40/0x50, cores 0-2)
 * on 5 GHz: no leading 0x2a, and 0xb0/0xb1/0xb2 where 2.4 GHz has 0x2b
 * (notes/154). With wl's PHY words off the link needs these. Opcodes after
 * Alessio Ferri's tree where known.
 */
static const u16 b43_rfseq2_c0_5g[] = { 0x07, 0x0a, 0x00, 0x08, 0xb0, 0xb1, 0x1f, 0x1f };
static const u16 b43_rfseq2_c1_5g[] = { 0x07, 0x08, 0x0c, 0x0e, 0xb0, 0xb2, 0x1f, 0x1f };
static const u16 b43_rfseq2_c2_5g[] = { 0x07, 0x08, 0x0e, 0xb0, 0xb1, 0x1f, 0x1f, 0x1f };
static const struct b43_phy_ac_tbl b43_rfseq2_5g_tbls[] = {
	{ b43_rfseq2_c0_5g, 8, 7, 0x30, 16 },
	{ b43_rfseq2_c1_5g, 8, 7, 0x40, 16 },
	{ b43_rfseq2_c2_5g, 8, 7, 0x50, 16 },
};

static void b43_phy_ac_write_table(struct b43_wldev *dev,
				   const struct b43_phy_ac_tbl *t);

static void b43_phy_ac_table_write16(struct b43_wldev *dev, u16 id, u16 offset,
				     u16 value);

static void b43_phy_ac_rfseq_ext_5g(struct b43_wldev *dev)
{
	static const u16 ext[4][3] = {
		{ 0x0fd2, 0x0096, 0x0000 },
		{ 0x0fc2, 0x0086, 0x0000 },
		{ 0x0fd2, 0x0086, 0x0000 },
		{ 0x0800, 0x0086, 0x0000 },
	};
	unsigned int i;

	static const u16 fill11[3] = { 0xbf25, 0x0071, 0x4002 };

	for (i = 0; i < ARRAY_SIZE(ext); i++)
		b43_phy_ac_table_write48(dev, 0x14, 0x30 + i, ext[i]);
	for (i = 0; i < ARRAY_SIZE(b43_rfseq2_5g_tbls); i++)
		b43_phy_ac_write_table(dev, &b43_rfseq2_5g_tbls[i]);
	/* rfseq2 timing cells of the TX chains (core 0 at 973, core 1 at 989) that
	 * differ from the 2.4 GHz defaults: without the core 1 value no two-stream
	 * frame is ever acknowledged (notes/156).
	 */
	b43_phy_ac_table_write16(dev, 7, 973, 0x03a2);
	b43_phy_ac_table_write16(dev, 7, 989, 0x05d0);
	b43_phy_ac_table_write16(dev, 7, 398, 0x0049);
	/* The 5 GHz TX gain table, and the rpcal fill wl used on channel 112
	 * (the twelve head cells and the zero tail are band independent).
	 */
	for (i = 0; i < 128; i++)
		b43_phy_ac_table_write48(dev, 0x20, i, b43_phy_ac_txgain_5g[i]);
	for (i = 12; i < 460; i++)
		b43_phy_ac_table_write48(dev, 0x11, i, fill11);
}

static void b43_phy_ac_write_table(struct b43_wldev *dev,
				   const struct b43_phy_ac_tbl *t);

/* 5 GHz AGC tables as written by the vendor driver on this board (notes/154):
 * the same four table ids as 2.4 GHz (0x44/0x45 core 0, 0x64/0x65 core 1) but
 * with the 5 GHz LNA gains. Offset 0: eLNA, 8: LNA1, 16: LNA2, 32: gain limits.
 */
static const u8 b43_ac_agc5_elna[] = { 0x0c, 0x0c };
static const u8 b43_ac_agc5_lna1_gain[] = { 0xfe, 0xfe, 0x04, 0x0a, 0x10, 0x17 };
static const u8 b43_ac_agc5_lna1_code[] = { 1, 1, 2, 3, 4, 5 };
static const u8 b43_ac_agc5_lna2_gain[] = { 0xf8, 0xf8, 0xfb, 0xfe, 0x02, 0x05, 0x09 };
static const u8 b43_ac_agc5_lna2_code[] = { 1, 1, 2, 3, 4, 5, 6 };
static const u8 b43_ac_agc5_lim7[] = { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 };
static const u8 b43_ac_agc5_lim2[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };

static const struct b43_phy_ac_tbl b43_ac_agc_tbls_5g[] = {
	{ b43_ac_agc5_elna, 2, 0x44, 0x00, 8 },
	{ b43_ac_agc5_lna1_gain, 6, 0x44, 0x08, 8 },
	{ b43_ac_agc5_lna2_gain, 7, 0x44, 0x10, 8 },
	{ b43_ac_agc5_lim7, 10, 0x44, 0x20, 8 },
	{ b43_ac_agc5_lna1_code, 6, 0x45, 0x08, 8 },
	{ b43_ac_agc5_lna2_code, 7, 0x45, 0x10, 8 },
	{ b43_ac_agc5_lim2, 10, 0x45, 0x20, 8 },
	{ b43_ac_agc5_elna, 2, 0x64, 0x00, 8 },
	{ b43_ac_agc5_lna1_gain, 6, 0x64, 0x08, 8 },
	{ b43_ac_agc5_lna2_gain, 7, 0x64, 0x10, 8 },
	{ b43_ac_agc5_lim7, 10, 0x64, 0x20, 8 },
	{ b43_ac_agc5_lna1_code, 6, 0x65, 0x08, 8 },
	{ b43_ac_agc5_lna2_code, 7, 0x65, 0x10, 8 },
	{ b43_ac_agc5_lim2, 10, 0x65, 0x20, 8 },
};

/* 5 GHz setup on entering 80 MHz mode: the RF sequencer extension entries,
 * 5 GHz TX gain table and rpcal fill, the second sequencer's command lists
 * and the AGC tables, all from this file; none of wl's first-load state
 * (radio, PHY registers, tables, SHM, chipcommon, PMU) is replayed any more
 * (notes/153-155).
 */
static void b43_phy_ac_setup_5g(struct b43_wldev *dev)
{
	unsigned int i;

	b43_phy_ac_rfseq_ext_5g(dev);
	b43_radio_2069_vcocal(dev);
	/* RX gain control, all cores: wl and Alessio use 0x2c on 5 GHz, our 2.4 GHz
	 * init leaves 0x18; about 8 dB more RX level (notes/155).
	 */
	b43_phy_write(dev, 0x173b, 0x002c);
	for (i = 0; i < ARRAY_SIZE(b43_ac_agc_tbls_5g); i++)
		b43_phy_ac_write_table(dev, &b43_ac_agc_tbls_5g[i]);
}

/*
 * PHY register init, 2.4 GHz / 20 MHz, replacing the first 72 entries of the
 * wl first-load replay. The blocks follow the reset-time code of Alessio
 * Ferri's b43-ac-wip (mode_init, set_reg_on_reset, set_pdet_on_reset,
 * coeff_bank_init); the words marked "wl" are written by wl in this window
 * but not by his code. Read-modify-write is kept where he uses it: the
 * result must equal the replayed value (checked register by register).
 */
#define B43_AC_NCORES	2	/* coremask 0x3 on this chip */

/* 0x17xx analog front end page, AFE on */
static void b43_phy_ac_mode_init(struct b43_wldev *dev)
{
	b43_phy_write(dev, 0x173e, 0x0000);
	b43_phy_write(dev, 0x1725, 0x0000);
	b43_phy_write(dev, 0x1722, 0x0000);
	b43_phy_write(dev, 0x1723, 0x0000);
	b43_phy_write(dev, 0x1724, 0x0000);
	b43_phy_write(dev, 0x1727, 0x0000);
	b43_phy_write(dev, 0x1750, 0x0000);
	b43_phy_write(dev, 0x1728, 0x0080);
	b43_phy_write(dev, 0x1720, 0x0180);
	b43_phy_write(dev, 0x1729, 0x0000);
	b43_phy_write(dev, 0x1721, 0x5000);
	b43_phy_write(dev, 0x173a, b43_phy_read(dev, 0x073a) | 0x0100);
	b43_phy_write(dev, 0x1725, b43_phy_read(dev, 0x1725) | 0x0400);
}

static void b43_phy_ac_set_reg_on_reset(struct b43_wldev *dev)
{
	unsigned int c;

	b43_phy_write(dev, 0x01f2, 0x00c8);
	b43_phy_write(dev, 0x0026, 0x0092);
	b43_phy_write(dev, 0x01ed, 0x0050);	/* wl */
	b43_phy_write(dev, 0x0025, 0x0030);

	/* clip mask: low byte 0x55 */
	b43_phy_maskset(dev, 0x02ef, (u16)~0x00ff, 0x0055);
	b43_phy_maskset(dev, 0x02eb, (u16)~0x00ff, 0x0055);
	b43_phy_maskset(dev, 0x02f7, (u16)~0x00ff, 0x0055);
	b43_phy_maskset(dev, 0x02f3, (u16)~0x00ff, 0x0055);

	b43_phy_maskset(dev, 0x01ca, (u16)~0x1000, 0);
	b43_phy_maskset(dev, 0x01b0, (u16)~0x0020, 0);
	b43_phy_maskset(dev, 0x01b1, (u16)~0x1000, 0x1000);
	b43_phy_maskset(dev, 0x01b6, (u16)~0x8000, 0);
	for (c = 0; c < B43_AC_NCORES; c++) {
		b43_phy_maskset(dev, 0x0690 + c * 0x200, (u16)~0x0200, 0x0200);
		b43_phy_maskset(dev, 0x0690 + c * 0x200, (u16)~0x0400, 0x0400);
	}
	b43_phy_write(dev, 0x01e6, 0x0030);
}

/* Operating width in MHz; the coefficient bank scales with it. */
static unsigned int b43_phy_ac_bw_mhz(struct b43_wldev *dev)
{
	switch (dev->wl->hw->conf.chandef.width) {
	case NL80211_CHAN_WIDTH_80:
		return 80;
	case NL80211_CHAN_WIDTH_40:
		return 40;
	default:
		return 20;
	}
}

/*
 * RX gain / threshold LUT and per-core words. The 20 MHz values are checked
 * against wl on 2.4 GHz; the 40 and 80 MHz ones are his (5 GHz captures) and
 * not exercised here yet.
 */
static void b43_phy_ac_coeff_bank_init(struct b43_wldev *dev)
{
	static const u16 lut[3][21] = {
		{ 0x0015, 0x0146, 0x0088, 0x0146, 0x076e, 0x01a8, 0x00a3, 0x00f4,
		  0x00a3, 0x0684, 0x00ad, 0x00e5, 0x0068, 0x00e5, 0x06be, 0x019e,
		  0x0073, 0x00b2, 0x0073, 0x05fe, 0x00cc },
		{ 0x000b, 0x0181, 0x005a, 0x0181, 0x0793, 0x01b7, 0x00c1, 0x0102,
		  0x00c1, 0x06c0, 0x00a9, 0x0162, 0x0042, 0x0162, 0x075c, 0x01b3,
		  0x00b1, 0x00ed, 0x00b1, 0x0692, 0x00af },
		{ 0x0005, 0x017a, 0x009e, 0x017a, 0x07ca, 0x01b2, 0x00bd, 0x0114,
		  0x00bd, 0x06d6, 0x00a2, 0x016c, 0x006f, 0x016c, 0x0793, 0x01b2,
		  0x00b6, 0x00ff, 0x00b6, 0x06b4, 0x00a8 },
	};
	const unsigned int bw = b43_phy_ac_bw_mhz(dev);
	const unsigned int w = bw / 40;		/* 0, 1, 2 */
	unsigned int i, c;

	b43_phy_maskset(dev, 0x0076, (u16)~0x0007, w + 1);	/* width index */
	b43_phy_maskset(dev, 0x0180, (u16)~0x001f, lut[w][0]);
	for (i = 1; i < 21; i++)
		b43_phy_maskset(dev, 0x0180 + i, (u16)~0x07ff, lut[w][i]);
	b43_phy_maskset(dev, 0x01b5, (u16)~0x00ff, bw == 40 ? 0x008b : 0x0097);
	b43_phy_maskset(dev, 0x0312, (u16)~0x00ff, bw == 80 ? 0x0009 : 0x0013);
	b43_phy_maskset(dev, 0x0313, (u16)~0xff00, bw == 80 ? 0x0900 : 0x1300);
	for (c = 0; c < B43_AC_NCORES; c++) {
		u16 st = c * 0x200;

		b43_phy_maskset(dev, 0x06ed + st, (u16)~0x00ff,
				bw == 20 ? 0x000a : 0x0014);
		b43_phy_maskset(dev, 0x06ef + st, (u16)~0x00ff,
				bw == 20 ? 0x0017 : (bw == 40 ? 0x002a : 0x0054));
		b43_phy_maskset(dev, 0x06ef + st, (u16)~0xff00,
				bw == 20 ? 0x0e00 : (bw == 40 ? 0x1600 : 0x2c00));
		b43_phy_maskset(dev, 0x06ef + st, (u16)~0x00ff, 15 * (bw / 20));
	}
}

static void b43_phy_ac_phyinit(struct b43_wldev *dev)
{
	/* His b43_radio_2069_init() prologue (0x0415/040e/040c/0408/0417/0416)
	 * and the end state of the power-on (0x0408 = 0x0c02, 0x0417 = 4)
	 */
	b43_phy_write(dev, 0x1739, 0x0000);
	b43_phy_write(dev, 0x0415, 0x0000);
	b43_phy_write(dev, 0x040e, 0x0000);
	b43_phy_write(dev, 0x040c, 0x2000);
	b43_phy_write(dev, 0x0416, 0x000d);
	b43_phy_write(dev, 0x0408, 0x0c02);
	b43_phy_write(dev, 0x0417, 0x0004);
	b43_phy_write(dev, 0x016b, 0x0000);
	b43_phy_write(dev, 0x0175, 0x0000);

	b43_phy_ac_mode_init(dev);
	b43_phy_write(dev, 0x1645, 0x025c);	/* init_regs */
	b43_phy_write(dev, 0x03c4, 0x0668);	/* wl */
	b43_phy_ac_set_reg_on_reset(dev);
	b43_phy_write(dev, 0x0358, 0xc07f);	/* set_pdet_on_reset */
	/* FEM table 2 / sub 1 setup (his b43_phy_ac_fem2_sub1_setup) */
	b43_phy_set(dev, 0x040a, 0x0100);
	b43_phy_write(dev, 0x0414, 0x0555);
	/* Second TX chain: without this bit core 1 does not radiate and
	 * two-stream rates fail completely (notes/136).
	 */
	if (dev->dev->bus_type == B43_BUS_BCMA)
		bcma_cc_set32(&dev->dev->bdev->bus->drv_cc, BCMA_CC_CHIPCTL, 0x00000008);
	b43_phy_ac_coeff_bank_init(dev);
	/* RX gain control, all cores (his rxgainctrl setup). Without it the
	 * receive level is 26 dB down: -66 instead of -40 dBm (notes/136).
	 */
	b43_phy_write(dev, 0x1726, 0x000c);
	b43_phy_write(dev, 0x0197, 0x0014);	/* channel_setup */
	b43_phy_write(dev, 0x0198, 0x0010);
	b43_phy_ac_wide_tables_2g(dev);
}

static void b43_phy_ac_apply_por(struct b43_wldev *dev)
{

	/* Radio state the hardware TX power loop needs (TSSI / power detector
	 * path, per-core 0x01a-0x01f / 0x21a-0x21f, notes/136). Without it PHY 0x640/0x840 freeze at index 0 and
	 * the loop never reaches its target.
	 */
	b43_radio_write(dev, 0x0548, 0x0001);
	b43_radio_write(dev, 0x0549, 0x0000);
	b43_radio_write(dev, 0x054a, 0x0000);
	b43_radio_write(dev, 0x054c, 0x0000);
	b43_radio_write(dev, 0x040b, 0x0168);
	b43_radio_write(dev, 0x054b, 0x0101);
	b43_radio_write(dev, 0x004e, 0x8400);
	b43_radio_write(dev, 0x0166, 0x0000);
	b43_radio_write(dev, 0x024e, 0x8600);
	b43_radio_write(dev, 0x0366, 0x0000);
	b43_radio_write(dev, 0x001a, 0x0014);
	b43_radio_write(dev, 0x001b, 0x0280);
	b43_radio_write(dev, 0x001c, 0x0044);
	b43_radio_write(dev, 0x001e, 0x0010);
	b43_radio_write(dev, 0x001f, 0x0000);
	b43_radio_write(dev, 0x021a, 0x0014);
	b43_radio_write(dev, 0x021b, 0x0280);
	b43_radio_write(dev, 0x021c, 0x0044);
	b43_radio_write(dev, 0x021e, 0x0010);
	b43_radio_write(dev, 0x021f, 0x0000);
	b43_radio_write(dev, 0x0170, 0x0100);

	/* Everything else wl's first-load state contained (radio, tables, SHM,
	 * chipcommon, PMU) is now real init code or proven unnecessary
	 * (notes/130-135). Only the PHY register writes are left.
	 */
	b43_phy_ac_phyinit(dev);
	/* Hardware TX power control: 0x70 bits 15:13 enable it, 0x71 holds the
	 * averaging window, 0x72 the rest of its configuration. On since
	 * notes/140 (with the wide tables it no longer fails frames next to the
	 * AP; 0x0100 would switch it off).
	 */
	b43_phy_write(dev, 0x0070, 0xe500);
	b43_phy_write(dev, 0x0071, 0x04c8);
	b43_phy_write(dev, 0x0072, 0x400d);
}

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
/* Final per-core RF control state of wl (first-load trace) that our init
 * doesn't reach; diagnostic until the owning init step is ported.
 */
static void b43_phy_ac_rfctrl_wl(struct b43_wldev *dev)
{
	static const u16 regs[][2] = {
		{ 0x645, 0x024d }, { 0x845, 0x025f },
		{ 0x725, 0x0600 }, { 0x925, 0x0600 },
		{ 0x727, 0x0004 }, { 0x927, 0x0004 },
		{ 0x728, 0x0880 }, { 0x928, 0x0880 },
		{ 0x729, 0x1000 }, { 0x929, 0x1000 },
		{ 0x73a, 0x0180 }, { 0x93a, 0x0180 },
	};
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(regs); i++)
		b43_phy_write(dev, regs[i][0], regs[i][1]);
}

#include "phy_ac_farrow.h"

/*
 * The ADC/DAC run from a clock derived from the synthesizer, so the
 * fractional resampler to the baseband rate depends on the channel. wl
 * (static function at 0x1a581c) writes these on every channel switch;
 * without them every channel kept channel 6's ratio, 3.5% off on
 * channel 1 (notes/51).
 */
static void b43_phy_ac_set_farrow(struct b43_wldev *dev, unsigned int channel)
{
	const struct b43_phy_ac_farrow *f = NULL;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(b43_phy_ac_farrow_20); i++)
		if (b43_phy_ac_farrow_20[i].channel == channel)
			f = &b43_phy_ac_farrow_20[i];
	if (!f)
		return;

	b43_phy_write(dev, 0x19a, f->rx[0]);
	b43_phy_write(dev, 0x19b, f->rx[1]);
	b43_phy_write(dev, 0x19c, f->rx[2]);
	b43_phy_write(dev, 0x199, f->rx[3]);
	b43_phy_write(dev, 0x1a1, f->rx[0]);
	b43_phy_write(dev, 0x1a2, f->rx[1]);
	b43_phy_write(dev, 0x1a3, f->rx[2]);
	b43_phy_write(dev, 0x1a0, f->rx[3]);
	b43_phy_write(dev, 0x1603, f->tx[0]);
	b43_phy_write(dev, 0x1602, f->tx[1]);
	b43_phy_write(dev, 0x1607, f->tx[2]);
	b43_phy_write(dev, 0x1606, f->tx[3]);
	b43_phy_write(dev, 0x1601, b43_phy_read(dev, 0x601));
}

/*
 * Farrow resampler for an 80 MHz channel centred on @freq (MHz), Alessio
 * Ferri's formula: ratio = round(f * 2^18 / 45), deltaphase =
 * round(0xb40000000 / f). For 5530 MHz it gives exactly wl's captured words.
 */
static void b43_phy_ac_farrow_80(struct b43_wldev *dev, unsigned int freq)
{
	u32 ratio = DIV_ROUND_CLOSEST_ULL((u64)freq << 18, 45);
	u32 dphase = DIV_ROUND_CLOSEST_ULL(0xb40000000ull, freq);
	u16 mu = 0x0004 | (((ratio >> 24) & 0x3) << 7);

	b43_phy_write(dev, 0x019a, ratio & 0xffff);
	b43_phy_write(dev, 0x019b, (ratio >> 16) & 0xff);
	b43_phy_write(dev, 0x019c, 0x0b40);
	b43_phy_write(dev, 0x0199, mu);
	b43_phy_write(dev, 0x01a1, ratio & 0xffff);
	b43_phy_write(dev, 0x01a2, (ratio >> 16) & 0xff);
	b43_phy_write(dev, 0x01a3, 0x0b40);
	b43_phy_write(dev, 0x01a0, mu);
	b43_phy_write(dev, 0x1603, dphase & 0xffff);
	b43_phy_write(dev, 0x1602, dphase >> 16);
	b43_phy_write(dev, 0x1607, dphase & 0xffff);
	b43_phy_write(dev, 0x1606, dphase >> 16);
}

static void b43_phy_ac_tune(struct b43_wldev *dev,
			    const struct b43_radio_2069_chan *e,
			    unsigned int channel)
{
	int i;

	for (i = 0; i < B43_RADIO_2069_TUNE_REGS; i++)
		b43_radio_write(dev, b43_radio_2069_tune_regs[i], e->radio[i]);
	if (channel == 4) {
		b43_radio_write(dev, 0x8d6, 0x0ce4);
		b43_radio_maskset(dev, 0x8ec, ~0x0070, 0x0050);
	}
	b43_radio_set(dev, 0x645, 0x7000);
	b43_radio_write(dev, 0x723, 0x83e0);
	b43_radio_2069_vcocal(dev);
}

static void b43_phy_ac_tables_init(struct b43_wldev *dev);

/* Back on 2.4 GHz after 5 GHz in the same boot: the 5 GHz setup overwrote
 * the AGC, RF sequencer and TX gain tables and left the core in 80 MHz mode
 * (without this 2.4 GHz associates and receives, but nothing is sent).
 */
static void b43_phy_ac_restore_2g(struct b43_wldev *dev)
{
	u32 ioctl;

	b43_phy_ac_tables_init(dev);
	b43_phy_ac_wide_tables_2g(dev);
	b43_phy_write(dev, 0x173b, 0x0018);
	b43_phy_write(dev, 0x18b, 0);
	ioctl = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
	if ((ioctl & B43_BCMA_IOCTL_PHY_BW) == B43_BCMA_IOCTL_PHY_BW_80MHZ) {
		ioctl = (ioctl & ~B43_BCMA_IOCTL_PHY_BW) | B43_BCMA_IOCTL_PHY_BW_20MHZ;
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl | 0x2);
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl);
	}
}

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
	b43dbg(dev->wl, "phy_ac: switch_channel(%u) -> %u MHz\n",
		new_channel, e->freq);

	save = b43_phy_read(dev, 0x19e);
	b43_phy_set(dev, 0x19e, 0x3);

	b43_phy_maskset(dev, B43_PHY_AC_BANDCTL, ~0x0100, is_5ghz ? 0x0100 : 0);

	if (phy_ac->chan_set && phy_ac->last_5ghz && !is_5ghz)
		b43_phy_ac_restore_2g(dev);

	if (!phy_ac->chan_set || phy_ac->last_5ghz != is_5ghz) {
		b43_phy_set(dev, 0x728, 0x0100);
		udelay(1);
		b43_phy_mask(dev, 0x728, ~0x0100);
	}
	phy_ac->chan_set = true;
	phy_ac->last_5ghz = is_5ghz;

	b43_phy_ac_tune(dev, e, new_channel);
	b43_phy_maskset(dev, 0x19e, ~0x3, save & 0x3);

	for (i = 0; i < 6; i++)
		b43_phy_write(dev, B43_PHY_AC_BW1A + i, e->bw[i]);

	if (b43_phy_ac_is_80mhz(dev, new_channel)) {
		u32 ioctl;

		/* Test: keep wl's 80 MHz setup (synthesizer on its 80 MHz centre,
		 * PHY in 80 MHz mode) and set the core's PHY bandwidth to 80 MHz,
		 * toggling force-gated-clock around the change like wl.
		 */
		unsigned int ctr = b43_phy_ac_80mhz_centre(new_channel);

		b43_phy_ac_setup_5g(dev);
		/* The one PHY word of wl's 5 GHz state that 80 MHz RX/TX needs
		 * (bisect of 318 words, notes/153); reg 0x18b is 0 after reset.
		 */
		b43_phy_write(dev, 0x18b, 0x016c);
		/* Synthesizer, the per-channel PHY words (wl leaves 0x371 at 0 in
		 * 80 MHz mode) and the resampler for the block centre; same result
		 * as wl's own tuning on centre 106 (notes/144). Calibration results
		 * and the rpcal fill stay those of channel 106.
		 */
		{
			const struct b43_radio_2069_chan *c = b43_radio_2069_find_chan(dev, ctr);

			if (c) {
				save = b43_phy_read(dev, 0x19e);
				b43_phy_set(dev, 0x19e, 0x3);
				b43_phy_ac_tune(dev, c, ctr);
				b43_phy_maskset(dev, 0x19e, ~0x3, save & 0x3);
				for (i = 1; i < 6; i++)
					b43_phy_write(dev, B43_PHY_AC_BW1A + i, c->bw[i]);
				b43_phy_ac_farrow_80(dev, 5000 + 5 * ctr);
			}
		}
		ioctl = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl | 0x2);
		ioctl = (ioctl & ~B43_BCMA_IOCTL_PHY_BW) | B43_BCMA_IOCTL_PHY_BW_80MHZ;
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl | 0x2);
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl);
		b43info(dev->wl, "phy_ac: 5 GHz 80 MHz test, ioctrl %08x\n",
			bcma_aread32(dev->dev->bdev, BCMA_IOCTL));
	} else if (is_5ghz) {
		b43_phy_ac_setup_5g(dev);
		/* wl's state is its 80 MHz one: filters for our width */
		b43_phy_ac_coeff_bank_init(dev);
		/* wl's state tunes to its 80 MHz centre; tune our channel. */
		save = b43_phy_read(dev, 0x19e);
		b43_phy_set(dev, 0x19e, 0x3);
		b43_phy_ac_tune(dev, e, new_channel);
		b43_phy_maskset(dev, 0x19e, ~0x3, save & 0x3);
		for (i = 0; i < 6; i++)
			b43_phy_write(dev, B43_PHY_AC_BW1A + i, e->bw[i]);
	} else
		b43_phy_ac_rfctrl_wl(dev);

	/* After the wl snapshot. wl's own trace uses this same per-channel
	 * 20 MHz table on 5 GHz channels too (confirmed against its 5 GHz
	 * scan sweep, notes/53) - but not when ac_5g_80 keeps wl's captured
	 * 80 MHz state instead of retuning per-channel, a different PHY mode
	 * this table was never shown to apply to.
	 */
	if (!b43_phy_ac_is_80mhz(dev, new_channel))
		b43_phy_ac_set_farrow(dev, new_channel);

	b43_phy_ac_resetcca(dev);

	if (!is_5ghz)
		b43_phy_ac_txpwr_by_index(dev, B43_AC_TXIDX_2G);

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
/*
 * 2.4 GHz power-estimation LUT of one core (tables 0x40 / 0x60), 128 entries, from the SROM
 * power-detector triple (a1, b0, b1) = pa2ga words. At step j: num = 512*b0 + 32*b1*j,
 * den = 0x8000 + a1*j, v = (den/2 + num)/den clamped to [-8, 0x7f] (the same transfer function
 * as b43_nphy_tx_power_ctl_setup(); notes/134 checks it 128/128 against wl's table on this card).
 * SROM word offsets (rev 11): core 0 pa2ga at 0x6d, core 1 at 0x81.
 */
static void b43_phy_ac_write_est_pwr(struct b43_wldev *dev)
{
	static const struct { u16 id; u16 word; } core_tbl[] = { { 0x40, 0x6d }, { 0x60, 0x81 } };
	struct bcma_drv_cc *cc;
	unsigned int c, j;

	if (dev->dev->bus_type != B43_BUS_BCMA)
		return;
	cc = &dev->dev->bdev->bus->drv_cc;
	for (c = 0; c < ARRAY_SIZE(core_tbl) && c < b43_phy_ac_num_cores(dev); c++) {
		u16 w0 = bcma_read16(cc->core, BCMA_CC_SPROM + 2 * core_tbl[c].word);
		u16 w1 = bcma_read16(cc->core, BCMA_CC_SPROM + 2 * (core_tbl[c].word + 1));
		u16 w2 = bcma_read16(cc->core, BCMA_CC_SPROM + 2 * (core_tbl[c].word + 2));
		s32 a1 = (s16)w0, b0 = (s16)w1, b1 = (s16)w2, num, den;
		u16 lut[128];
		struct b43_phy_ac_tbl tbl = { lut, 128, core_tbl[c].id, 0, 16 };

		if (w0 == 0xffff && w1 == 0xffff && w2 == 0xffff)
			continue;	/* unprogrammed SROM: keep the default table */
		num = b0 << 9;
		den = 0x8000;
		for (j = 0; j < 128; j++) {
			s32 d = den ? den : 1;
			s32 v = (d / 2 + num) / d;

			num += b1 * 0x20;
			den += a1;
			lut[j] = (u16)(clamp(v, -8, 0x7f) & 0xff);
		}
		b43_phy_ac_write_table(dev, &tbl);
	}
}

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
	for (i = 0; i < b43_phy_ac_rfseq_tbls_n; i++)
		b43_phy_ac_write_table(dev, &b43_phy_ac_rfseq_tbls[i]);
	b43_phy_ac_write_est_pwr(dev);
	for (i = 0; i < b43_phy_ac_misc_tbls_n; i++)
		b43_phy_ac_write_table(dev, &b43_phy_ac_misc_tbls[i]);
	for (i = 0; i < b43_phy_ac_ladder_tbls_n; i++)
		b43_phy_ac_write_table(dev, &b43_phy_ac_ladder_tbls[i]);
	for (i = 0; i < b43_phy_ac_vendor_tbls_n; i++)
		b43_phy_ac_write_table(dev, &b43_phy_ac_vendor_tbls[i]);
	/* FEM control pattern: only the femctrl == 2 variant (this card) is known. SROM rev 11 word 0x55 bits 15:11. */
	if (dev->dev->bus_type == B43_BUS_BCMA &&
	    (bcma_read16(dev->dev->bdev->bus->drv_cc.core, BCMA_CC_SPROM + 0xaa) >> 11) == 2)
		for (i = 0; i < b43_phy_ac_femctrl2_tbls_n; i++)
			b43_phy_ac_write_table(dev, &b43_phy_ac_femctrl2_tbls[i]);
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

static void b43_phy_ac_table_write16(struct b43_wldev *dev, u16 id, u16 offset,
				      u16 value)
{
	b43_phy_write(dev, B43_PHY_AC_TABLE_ID, id);
	b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, offset);
	b43_phy_write(dev, B43_PHY_AC_TABLE_DATA1, value);
}

/* Set the TX gain of both cores from the 2.4 GHz gain table, as the stock
 * driver's txpwr_by_index does with hardware power control off.
 */
static void b43_phy_ac_txpwr_by_index(struct b43_wldev *dev, unsigned int idx)
{
	const u16 *e = b43_phy_ac_txgain_2g[min(idx, 127u)];
	u16 bbmult = e[0] & 0x00ff;
	u16 g0 = (e[0] >> 8) | ((e[1] & 0x00ff) << 8);
	u16 g1 = (e[1] >> 8) | ((e[2] & 0x00ff) << 8);
	u16 g2 = e[2] >> 8;
	u8 core, cores = b43_phy_ac_num_cores(dev);

	for (core = 0; core < cores && core < 3; core++) {
		b43_phy_ac_table_write16(dev, 7, core + 0x100, g0);
		b43_phy_ac_table_write16(dev, 7, core + 0x103, g1);
		b43_phy_ac_table_write16(dev, 7, core + 0x106, g2);
		b43_phy_ac_table_write16(dev, 0xc, 0x63 + 4 * core, bbmult);
		b43_phy_ac_table_write16(dev, 0xc, 0x73 + 4 * core, bbmult);
	}
}

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


static int b43_phy_ac_op_init(struct b43_wldev *dev)
{
	if (dev->phy.rev <= 1) {
		b43_phy_ac_tables_init(dev);
		b43_phy_ac_first_init(dev);
		/* wl's captured state, once; the channel switch that follows
		 * init tunes the radio for the requested channel.
		 */
		b43_phy_ac_apply_por(dev);
	} else
		b43err(dev->wl, "phy_ac: no table set for PHY rev %u\n",
		       dev->phy.rev);

	b43info(dev->wl, "phy_ac: init (core_rev %u, radio24=%d, chip %04x, board %04x, radio_on %d)\n",
		dev->dev->core_rev, b43_phy_ac_use_radio24(dev),
		dev->dev->chip_id, dev->dev->board_type, dev->phy.ac->radio_on);

	return 0;
}

/*
 * Self-healing for the per-init coin flip (notes/105, 119): only ~30 % of
 * fresh inits can transmit; in the others every TX ends in a PHY TX error.
 * The 15 s work polls the ucode's txphyerr counter (SHM
 * 0xFE) and restarts the core through mac80211 (fresh init, fresh coin flip)
 * after >= 3 errors in a window, at most 3 times (B43_AC_SELFHEAL_MAX); the budget refills after
 * 10 quiet minutes. Polled, not IRQ-driven: unmasking B43_IRQ_PHY_TXERR hung
 * the machine twice (notes/119).
 */
#define B43_AC_SELFHEAL_MAX	3
#define B43_AC_SH_TXPHYERR	0x00FE

static bool b43_phy_ac_check_badinit(struct b43_wldev *dev)
{
	static unsigned int restarts;
	static unsigned long last_restart;
	static u16 last;
	u16 now, d;

	if (restarts && time_after(jiffies, last_restart + 600 * HZ))
		restarts = 0;
	now = b43_shm_read16(dev, B43_SHM_SHARED, B43_AC_SH_TXPHYERR);
	d = now - last;
	last = now;
	if (d < 3 || restarts >= B43_AC_SELFHEAL_MAX)
		return false;
	restarts++;
	last_restart = jiffies;
	last = 0;	/* the ucode is reloaded, its counters restart at 0 */
	pr_emerg("b43 ac_selfheal: bad init (%u PHY TX errors), restart %u/%u\n",
		 d, restarts, B43_AC_SELFHEAL_MAX);
	mdelay(30);
	b43_controller_restart(dev, "AC bad init");
	return true;
}

static void b43_phy_ac_op_pwork_15sec(struct b43_wldev *dev)
{
	if (b43_phy_ac_check_badinit(dev))
		return;

	/* See notes/38: wl's real watchdog runs a periodic bulk RX-ring
	 * refill sweep this port never had; do the equivalent here.
	 */
	b43_dma_rx_retry_poisoned(dev);
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
