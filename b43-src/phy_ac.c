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
	else
		{
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
		 * words here (offsets: Alessio Ferri's patch 0001, notes/112). */
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
 * Read-only; for sharing with other AC-PHY reverse engineers (notes/105). */
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
	{0x01,128,0},{0x02,38,0},{0x03,256,1},{0x04,256,0},{0x05,22,1},
	{0x07,1092,0},{0x0a,96,0},{0x0b,23,0},{0x0c,120,0},{0x0e,160,1},
	{0x10,1463,1},{0x21,24,1},
	{0x40,128,0},{0x41,128,1},{0x42,128,0},{0x44,42,0},{0x45,42,0},{0x47,64,1},{0x48,64,1},
	{0x60,128,0},{0x61,128,1},{0x62,128,0},{0x64,42,0},{0x65,42,0},{0x67,64,1},{0x68,64,1},
	{0x80,128,0},{0x81,128,1},{0x82,128,0},{0x87,64,1},{0x88,64,1},
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

	return 0;
}

static void b43_phy_ac_op_free(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_ac *phy_ac = phy->ac;

	if (b43_ac_dbg_dev == dev) {
		debugfs_remove_recursive(b43_ac_dbg_dir);
		b43_ac_dbg_dir = NULL;
		b43_ac_dbg_dev = NULL;
	}
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

static bool b43_ac_diag;
module_param_named(ac_diag, b43_ac_diag, bool, 0644);
MODULE_PARM_DESC(ac_diag, "log MAC/DMA/GPIO/macstat state every 15 s (default off)");
static bool b43_ac_replay;
module_param_named(ac_replay, b43_ac_replay, bool, 0444);
MODULE_PARM_DESC(ac_replay, "AC-PHY diagnostic: apply the vendor driver's channel 6 PHY/radio state");

/* See notes/62: wl's real hostflags (HOSTF2/HOSTF3), which this port
 * never writes at all. Test flag, default off - unconfirmed live. */
static bool b43_ac_hostflags;
module_param_named(ac_hostflags, b43_ac_hostflags, bool, 0644);
MODULE_PARM_DESC(ac_hostflags, "AC-PHY test: write wl's real HOSTF2/HOSTF3 value (notes/62)");

/* See notes/64: HOSTF1 (SHM 0x5E), also never written. Test flag,
 * default off - a reasoned guess (EDCF|ACIW), not a captured wl value. */
static bool b43_ac_hostf1;
module_param_named(ac_hostf1, b43_ac_hostf1, bool, 0644);
MODULE_PARM_DESC(ac_hostf1, "AC-PHY test: write HOSTF1 EDCF|ACIW (notes/64, guess not captured)");

static void b43_phy_ac_replay_ch6(struct b43_wldev *dev);

bool b43_ac_5ghz;
module_param_named(ac_5ghz, b43_ac_5ghz, bool, 0444);
MODULE_PARM_DESC(ac_5ghz, "AC-PHY: advertise and tune 5 GHz channels (experimental)");

static bool b43_ac_5g_80;
module_param_named(ac_5g_80, b43_ac_5g_80, bool, 0644);
MODULE_PARM_DESC(ac_5g_80, "AC-PHY test: on 5 GHz keep wl's 80 MHz setup instead of re-tuning to 20 MHz");
static uint b43_ac_5g_ctr;
module_param_named(ac_5g_ctr, b43_ac_5g_ctr, uint, 0644);
MODULE_PARM_DESC(ac_5g_ctr, "AC-PHY test: with ac_5g_80, retune the 80 MHz setup to this block-centre channel (106, 122, ...)");

static bool b43_ac_init_state = true;
module_param_named(ac_init_state, b43_ac_init_state, bool, 0444);
MODULE_PARM_DESC(ac_init_state, "AC-PHY: apply wl's captured state at PHY init (else on the first switch to channel 6)");
static bool b43_ac_state_once;
module_param_named(ac_state_once, b43_ac_state_once, bool, 0644);
MODULE_PARM_DESC(ac_state_once, "AC-PHY: apply wl's captured state only on the first switch to channel 6 per core init");
static void b43_radio_2069_vcocal(struct b43_wldev *dev);

static bool b43_ac_rfseq;
module_param_named(ac_rfseq, b43_ac_rfseq, bool, 0444);
MODULE_PARM_DESC(ac_rfseq, "AC-PHY test: force the RF sequencer through its RX-core-state settling steps on channel set (vendor wlc_phy_rxcore_setstate_acphy, unported)");
static void b43_phy_ac_rxcore_setstate(struct b43_wldev *dev, u8 mask);
static void b43_phy_ac_force_rfseq(struct b43_wldev *dev, u8 which);

static bool b43_ac_txcal_test;
module_param_named(ac_txcal_test, b43_ac_txcal_test, bool, 0444);
MODULE_PARM_DESC(ac_txcal_test, "AC-PHY test: exercise the untested TX-cal gain-table save/restore, settle pulse, and ramp-table draft code and log before/after register values (no live TX/tone, see notes/16)");

static bool b43_ac_txcal_loopback_test;
module_param_named(ac_txcal_loopback_test, b43_ac_txcal_loopback_test, bool, 0444);
MODULE_PARM_DESC(ac_txcal_loopback_test, "AC-PHY test: additionally enter and immediately exit the untested RF-loopback calibration mode, logging register values before/during/after (documented best-guess for 2 unresolved wl-internal conditions, no tone/live TX, see notes/16 - separate flag from ac_txcal_test since this one writes to live RF front-end registers)");

static bool b43_ac_txcal_tone_test;
module_param_named(ac_txcal_tone_test, b43_ac_txcal_tone_test, bool, 0444);
MODULE_PARM_DESC(ac_txcal_tone_test, "AC-PHY test: additionally generate one real, brief TX test tone while in RF-loopback mode (vendor wlc_phy_tx_tone_acphy for our exact 2.4GHz call pattern), logging status before/after. Deliberately does NOT replicate wl's own cleanup (wlc_phy_stopplayback_acphy/wlc_phy_resetcca_acphy - both gated on an unresolved wl-internal field) and instead saves/restores all 7 PHY registers this touches verbatim, byte for byte, regardless of what wl's own semantics would do - see notes/16. Highest-risk flag in this project so far: this is a real, brief RF transmission, only ever run with the user physically present.");

static bool b43_ac_txcal_tone_sustain_test;
module_param_named(ac_txcal_tone_sustain_test, b43_ac_txcal_tone_sustain_test, bool, 0444);
MODULE_PARM_DESC(ac_txcal_tone_sustain_test, "AC-PHY test: like ac_txcal_tone_test, but does NOT restore the 4 playback-control registers (0x460/0x461/0x462/0x463) right after triggering - wl's own algorithm leaves the tone running and only tears it down after its whole measurement sweep, so ac_txcal_tone_test's immediate restore likely stopped the tone almost instantly. This version leaves it running for a short, bounded, fixed duration while repeatedly sampling the loopback-measurement register (radio 0x144), then explicitly stops it - still no candidate-search writes to 899/0x380, purely observational. See notes/16.");

static bool b43_ac_txcal_candidate_test;
module_param_named(ac_txcal_candidate_test, b43_ac_txcal_candidate_test, bool, 0444);
MODULE_PARM_DESC(ac_txcal_candidate_test, "AC-PHY test: the first closed-loop, hardware-reactive piece in this project - while a sustained test tone plays in RF-loopback mode, writes each of wl's real 6 candidate values to PHY reg 899, triggers a comparison via reg 0x380 (using the now phy+0x164-resolved candidate 0x423, core 0 - vendor FUN_001ac9b6's inner sweep, single outer sample only, not wl's full generation-counter-driven loop), and reads back radio reg 0x144's bit 2. Deliberately does NOT stop at the first candidate that clears bit 2 like wl does - sweeps and logs all 6 for full diagnostic visibility, since the point here is observing the measurement mechanism itself, not finding/applying a real correction (nothing gets written to the loft-comp table). See notes/16.");

static bool b43_ac_txcal_candidate_test2;
module_param_named(ac_txcal_candidate_test2, b43_ac_txcal_candidate_test2, bool, 0444);
MODULE_PARM_DESC(ac_txcal_candidate_test2, "AC-PHY test: like ac_txcal_candidate_test, but adds the two pieces of setup wl's real algorithm does immediately before the candidate sweep and that the first version skipped: the settle pulse and the TX gain-table override (both already individually validated by ac_txcal_test). The override reads each core's current table-7 gain and writes those exact same values back - a deliberate no-op on the actual gain, safe, but exercising the real write sequence (including the 0x19e table-access-enable toggle) in case that, not the gain value itself, is what the previous test's uniform bit-2-clear result was missing. Order matches vendor FUN_001ac9b6 exactly: enter loopback, settle pulse, gain override, start tone, candidate sweep, stop tone, restore gain, exit loopback. See notes/16.");

static bool b43_ac_txcal_candidate_test3;
module_param_named(ac_txcal_candidate_test3, b43_ac_txcal_candidate_test3, bool, 0444);
MODULE_PARM_DESC(ac_txcal_candidate_test3, "AC-PHY test: adds the large per-core measurement setup block (b43_phy_ac_txcal_measure_setup_enter/_exit - now fully resolved for our hardware, no guessing) that ac_txcal_candidate_test/test2 both skipped. Deliberately uses a straight save/write-back cleanup instead of vendor's real one, to avoid a BCMA_IOCTL write that function makes (wlc_phy_resetcca_acphy -> wlapi_bmac_phyclk_fgc) - the same register category behind this project's one hard machine freeze (notes/07). Full order: save PHY reg 0x140, enter loopback, measurement setup, settle pulse, gain override, start tone, candidate sweep, stop tone, restore gain, undo measurement setup, exit loopback, restore 0x140. See notes/16.");

static bool b43_ac_txcal_setup_test;
module_param_named(ac_txcal_setup_test, b43_ac_txcal_setup_test, bool, 0444);
MODULE_PARM_DESC(ac_txcal_setup_test, "AC-PHY test: exercises ONLY b43_phy_ac_txcal_measure_setup_enter()/_exit() in isolation (~110 register writes across both cores, the largest single register-write surface added in this project so far), immediately back to back, logging a few representative registers before/after - a round-trip-safety check run before combining this block with the tone/candidate-sweep test in ac_txcal_candidate_test3, matching this project's established practice of testing each new risky piece standalone first. No tone, no candidate sweep, no loft-comp writes. See notes/16.");

static bool b43_ac_txcal_resetcca_test;
module_param_named(ac_txcal_resetcca_test, b43_ac_txcal_resetcca_test, bool, 0444);
MODULE_PARM_DESC(ac_txcal_resetcca_test, "AC-PHY test: exercises ONLY b43_phy_ac_txcal_resetcca() in isolation - wl's real cleanup for the measurement setup block (wlc_phy_resetcca_acphy/wlapi_bmac_phyclk_fgc), previously avoided because it writes BCMA_IOCTL_FGC (0x0002, 'Force Gate Clock' - a generic, standard bcma bus core-control bit, not an exotic hazard; see notes/18 for why this is a different risk category from the 2026-09-26 BCMA_IOCTL PHY-bandwidth incident). Logs BCMA_IOCTL and PHY reg 1 before/after in isolation, no loopback, no tone, no candidate sweep - staged the same way as every other new risky piece in this project. Only run with explicit, informed user authorization given directly for this specific step.");

static bool b43_ac_txcal_candidate_test4;
module_param_named(ac_txcal_candidate_test4, b43_ac_txcal_candidate_test4, bool, 0444);
MODULE_PARM_DESC(ac_txcal_candidate_test4, "AC-PHY test: like ac_txcal_candidate_test3, but adds the one remaining piece of FUN_001ac9b6's setup context that wasn't yet ported: wlc_phy_classifier_acphy(pi,7,4), a trivial 3-bit mask-and-set on PHY reg 0x140 (already saved/restored by test3, now actually exercised) that vendor code runs immediately before entering RF-loopback mode - likely disables normal RX signal classification during calibration. PHY-register only, not BCMA_IOCTL. If the candidate sweep still reads uniformly after this, every known piece of setup this project can decompile is in place. See notes/16.");

static bool b43_ac_txcal_candidate_test5;
module_param_named(ac_txcal_candidate_test5, b43_ac_txcal_candidate_test5, bool, 0444);
MODULE_PARM_DESC(ac_txcal_candidate_test5, "AC-PHY test: identical setup to ac_txcal_candidate_test4, but sweeps all 6 entries of the real local_e8 outer-sample table (b43_phy_ac_txcal_measure_candidates_sweep) instead of just entry 0 (36 total 899/0x380/radio144 readings instead of 6) - checks whether the flat result seen on every version of this test so far is specific to outer sample 0 or holds across wl's whole real candidate table. See notes/16.");

static bool b43_ac_txcal_candidate_test6;
module_param_named(ac_txcal_candidate_test6, b43_ac_txcal_candidate_test6, bool, 0444);
MODULE_PARM_DESC(ac_txcal_candidate_test6, "AC-PHY test: identical to ac_txcal_candidate_test5, but replaces the save/write-back cleanup with wl's real one (b43_phy_ac_txcal_resetcca - BCMA_IOCTL_FGC, individually verified safe in ac_txcal_resetcca_test first) - this closes the one remaining gap between this port's measurement path and vendor's real sequence. Full order: classifier switch, loopback, full per-core setup, settle pulse, gain override, sustained tone, full 36-combination candidate sweep, restore gain, real resetcca cleanup, exit loopback. See notes/16 and notes/18.");

/* wl supports up to 4 cores in this code path (decompiled-cal/FUN_00199491.c,
 * FUN_0019d224.c index a 4-entry table); our board only ever uses 2.
 */
#define B43_PHY_AC_TXCAL_MAX_CORES 4

struct b43_phy_ac_txcal_gainsave {
	u16 tbl7[B43_PHY_AC_TXCAL_MAX_CORES][3];
	u16 tbl0xc[B43_PHY_AC_TXCAL_MAX_CORES];
};

static int b43_ac_txidx = 20;
module_param_named(ac_txidx, b43_ac_txidx, int, 0644);
MODULE_PARM_DESC(ac_txidx, "AC-PHY: fixed 2.4 GHz TX gain table index, 0 = highest gain, applied on a channel switch; -1 leaves the reset value, index 64, which is too weak beyond a few metres. The stock power loop ran at 20-38 here (notes/138)");
static void b43_phy_ac_txpwr_by_index(struct b43_wldev *dev, unsigned int idx);

static void b43_phy_ac_txcal_save_gaintbl(struct b43_wldev *dev,
					   struct b43_phy_ac_txcal_gainsave *save,
					   const u16 new_gain[][4]);
static void b43_phy_ac_txcal_restore_gaintbl(struct b43_wldev *dev,
					const struct b43_phy_ac_txcal_gainsave *save);
static void b43_phy_ac_txcal_settle_pulse(struct b43_wldev *dev);
static void b43_phy_ac_txcal_ramp_table(struct b43_wldev *dev, u16 percent);
static u16 b43_phy_ac_table_read16(struct b43_wldev *dev, u16 id, u16 offset);

struct b43_phy_ac_txcal_radiosave {
	u16 r1a[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 r1b[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 r1c[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 r1e[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 r1f[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 r24[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 r170_or_184[B43_PHY_AC_TXCAL_MAX_CORES];
};
static void b43_phy_ac_txcal_read_radiosave(struct b43_wldev *dev,
					struct b43_phy_ac_txcal_radiosave *save);
static void b43_phy_ac_txcal_enter_loopback(struct b43_wldev *dev,
					struct b43_phy_ac_txcal_radiosave *save);
static void b43_phy_ac_txcal_exit_loopback(struct b43_wldev *dev,
				const struct b43_phy_ac_txcal_radiosave *save);
struct b43_phy_ac_txcal_tonesave {
	u16 r460, r461, r462, r463, r471, r382, r400;
};
static void b43_phy_ac_txcal_gen_tone_start(struct b43_wldev *dev,
					struct b43_phy_ac_txcal_tonesave *save);
static void b43_phy_ac_txcal_gen_tone_stop(struct b43_wldev *dev,
				const struct b43_phy_ac_txcal_tonesave *save);
static void b43_phy_ac_txcal_gen_tone(struct b43_wldev *dev);
static void b43_phy_ac_txcal_measure_candidates(struct b43_wldev *dev);
static void b43_phy_ac_txcal_measure_candidates_sweep(struct b43_wldev *dev);

struct b43_phy_ac_txcal_setupsave {
	u16 t73e[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t721[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t729[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t720[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t728[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t724[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t736[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t723[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t735[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t737[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t738[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t727[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t73c[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t725[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t739[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 t73a[B43_PHY_AC_TXCAL_MAX_CORES];
	u16 r19e, r40f;
};
static void b43_phy_ac_txcal_measure_setup_enter(struct b43_wldev *dev,
				struct b43_phy_ac_txcal_setupsave *save);
static void b43_phy_ac_txcal_measure_setup_exit(struct b43_wldev *dev,
			const struct b43_phy_ac_txcal_setupsave *save);
static void b43_phy_ac_txcal_resetcca(struct b43_wldev *dev);

static uint b43_ac_por;
module_param_named(ac_por, b43_ac_por, uint, 0644);
/* ac_por bits beyond the first-load classes: 0x40 skip vcocal after the
 * radio class, 0x80 wl MAC timing regs, 0x100 wl final radio regs. */
MODULE_PARM_DESC(ac_por, "AC-PHY diagnostic: after the ch6 replay also apply wl's first-load state (bitmask: 1 radio, 2 phy, 4 tables, 8 shm, 16 chipcommon, 32 pmu)");

#include "phy_ac_por5g.h"

/*
 * RF sequencer extension (PHY table 0x14), entries 0x30-0x33, as wl writes
 * them on 5 GHz. The entries are 48 bits wide and go through the third data
 * port, 0x011, low word first; the trace decoder knew only 0x00f/0x010, so
 * they were never in the replayed state. Without 0x30-0x32 the receiver is
 * completely deaf on 5 GHz; 2.4 GHz does not need them. PHY tables survive
 * a driver reload and a PCI bus reset, which is why 5 GHz received after wl
 * had run once in the same boot (notes/139).
 */
static void b43_phy_ac_rfseq_ext_5g(struct b43_wldev *dev)
{
	static const u16 ext[4][3] = {
		{ 0x0fd2, 0x0096, 0x0000 },
		{ 0x0fc2, 0x0086, 0x0000 },
		{ 0x0fd2, 0x0086, 0x0000 },
		{ 0x0800, 0x0086, 0xd182 },
	};
	unsigned int i, j;

	for (i = 0; i < ARRAY_SIZE(ext); i++) {
		b43_phy_write(dev, B43_PHY_AC_TABLE_ID, 0x14);
		b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, 0x30 + i);
		for (j = 0; j < 3; j++)
			b43_phy_write(dev, 0x011, ext[i][j]);
	}
}

/* wl's 5 GHz first-load state (80 MHz, channel 112 primary): radio, PHY,
 * tables, SHM. Chipcommon/PMU are band independent (2.4 GHz state). */
static void b43_phy_ac_apply_por5g(struct b43_wldev *dev)
{
	unsigned int i;

	b43_phy_ac_rfseq_ext_5g(dev);

	for (i = 0; i < ARRAY_SIZE(b43_ac_por5g_radio); i++)
		if (b43_ac_por5g_radio[i][0] != 0xffff)
			b43_radio_write(dev, b43_ac_por5g_radio[i][0],
					b43_ac_por5g_radio[i][1]);
	b43_radio_2069_vcocal(dev);
	for (i = 0; i < ARRAY_SIZE(b43_ac_por5g_phy); i++)
		if (b43_ac_por5g_phy[i][0] != 0xffff)
			b43_phy_write(dev, b43_ac_por5g_phy[i][0],
				      b43_ac_por5g_phy[i][1]);
	for (i = 0; i < ARRAY_SIZE(b43_ac_por5g_tbl); i++) {
		if (b43_ac_por5g_tbl[i].id == 0xffff)
			continue;
		b43_phy_write(dev, B43_PHY_AC_TABLE_ID, b43_ac_por5g_tbl[i].id);
		b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, b43_ac_por5g_tbl[i].off);
		if (b43_ac_por5g_tbl[i].width == 32)
			b43_phy_write(dev, B43_PHY_AC_TABLE_DATA2,
				      b43_ac_por5g_tbl[i].val >> 16);
		b43_phy_write(dev, B43_PHY_AC_TABLE_DATA1,
			      b43_ac_por5g_tbl[i].val & 0xffff);
	}
	for (i = 0; i < ARRAY_SIZE(b43_ac_por5g_shm); i++)
		/* not the chanspec (wl's 80 MHz one): it comes back in every RX
		 * header and mac80211 drops beacons tagged with the wrong channel */
		if (b43_ac_por5g_shm[i].routing != 0xffff &&
		    !(b43_ac_por5g_shm[i].routing == B43_SHM_SHARED &&
		      b43_ac_por5g_shm[i].off == B43_SHM_SH_CHAN))
			b43_shm_write16(dev, b43_ac_por5g_shm[i].routing,
					b43_ac_por5g_shm[i].off,
					b43_ac_por5g_shm[i].val);
	if (dev->dev->bus_type == B43_BUS_BCMA) {
		struct bcma_drv_cc *cc = &dev->dev->bdev->bus->drv_cc;

		for (i = 0; i < ARRAY_SIZE(b43_ac_por5g_cc); i++)
			if (b43_ac_por5g_cc[i][0] != 0xffff)
				bcma_cc_write32(cc, b43_ac_por5g_cc[i][0],
						b43_ac_por5g_cc[i][1]);
		for (i = 0; i < ARRAY_SIZE(b43_ac_por5g_pmu); i++) {
			if (b43_ac_por5g_pmu[i].kind == 0)
				bcma_chipco_chipctl_maskset(cc, b43_ac_por5g_pmu[i].idx,
							    0, b43_ac_por5g_pmu[i].val);
			else if (b43_ac_por5g_pmu[i].kind == 1)
				bcma_chipco_regctl_maskset(cc, b43_ac_por5g_pmu[i].idx,
							   0, b43_ac_por5g_pmu[i].val);
		}
	}
	b43info(dev->wl, "phy_ac: applied 5 GHz first-load state\n");
}

static uint b43_ac_rfkick;
module_param_named(ac_rfkick, b43_ac_rfkick, uint, 0644);
MODULE_PARM_DESC(ac_rfkick, "AC-PHY diagnostic (notes/118): after the first-load replay run wl's RF-sequencer kicks verbatim, in wl's order (bit 0: the 5 cmd1+cmd2 pairs of rxcore_setstate, bit 1: the 4 cmd 0x20 kicks)");

/* Wait for the RF sequencer (PHY 0x403 bit 0 busy), at most ~2 ms like wl's poll. */
static void b43_ac_rfkick_wait(struct b43_wldev *dev)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (!(b43_phy_read(dev, 0x403) & 1))
			return;
		udelay(200);
	}
	b43warn(dev->wl, "phy_ac: rfseq busy after 2 ms\n");
}

/* wl's rxcore_setstate pair (traces/decoded-firstload-5g/seq.txt line 137500..137530, coremask 3). */
static void b43_ac_rfkick_pair(struct b43_wldev *dev)
{
	udelay(10);
	b43_phy_write(dev, 0x160, 0x7b);
	b43_phy_write(dev, 0x401, 0x7733);
	b43_phy_write(dev, 0x401, 0x7733);
	b43_phy_write(dev, 0x401, 0x7730);
	b43_phy_write(dev, 0x400, 1);
	b43_phy_write(dev, 0x19e, 0x3d2);
	b43_phy_write(dev, 0x19e, 0x3d3);
	b43_phy_write(dev, 0x400, 3);
	b43_phy_write(dev, 0x402, 1);
	udelay(20);
	b43_ac_rfkick_wait(dev);
	b43_phy_write(dev, 0x400, 1);
	b43_phy_write(dev, 0x19e, 0x3d0);
	b43_phy_write(dev, 0x19e, 0x3d2);
	b43_phy_write(dev, 0x19e, 0x3d3);
	b43_phy_write(dev, 0x400, 3);
	b43_phy_write(dev, 0x402, 2);
	udelay(10);
	b43_ac_rfkick_wait(dev);
	b43_phy_write(dev, 0x400, 1);
	b43_phy_write(dev, 0x19e, 0x3d0);
	b43_phy_write(dev, 0x401, 0x7733);
	b43_phy_write(dev, 0x401, 0x7733);
	b43_phy_write(dev, 0x400, 0);
}

/* wl's cmd 0x20 kick (seq.txt line 141632). */
static void b43_ac_rfkick_k20(struct b43_wldev *dev)
{
	b43_phy_write(dev, 0x19e, 0x3d2);
	b43_phy_write(dev, 0x19e, 0x3d3);
	b43_phy_write(dev, 0x400, 3);
	b43_phy_write(dev, 0x402, 0x20);
	udelay(10);
	b43_ac_rfkick_wait(dev);
	b43_phy_write(dev, 0x400, 0);
	b43_phy_write(dev, 0x19e, 0x3d0);
}

/* wl's order in its first load: pair, pair, k20, k20, pair, pair, k20, k20, pair. */
static void b43_ac_rfkick_run(struct b43_wldev *dev)
{
	static const char order[] = "PPKKPPKKP";
	int i;

	for (i = 0; i < sizeof(order) - 1; i++) {
		bool pair = order[i] == 'P';

		if (!(b43_ac_rfkick & (pair ? 1 : 2)))
			continue;
		pr_emerg("b43 ac_rfseq: %d %s\n", i, pair ? "pair" : "k20");
		mdelay(30);
		if (pair)
			b43_ac_rfkick_pair(dev);
		else
			b43_ac_rfkick_k20(dev);
	}
	b43info(dev->wl, "phy_ac: rfseq kicks done (mask %u)\n", b43_ac_rfkick);
}


/*
 * Diagnostic (notes/119): replay wl's recorded PHY/radio/table/delay op
 * stream (tools/gen_wl_ops.py) verbatim after the first-load replay, to see
 * whether wl's exact sequence/timing makes every init good.
 */
static char *b43_ac_fr_path;
static uint b43_ac_fr_start, b43_ac_fr_end;
static uint b43_ac_fr_mask = 0x1f;
static uint b43_ac_fr_dscale = 1, b43_ac_fr_pad;
module_param_named(ac_fr_dscale, b43_ac_fr_dscale, uint, 0644);
MODULE_PARM_DESC(ac_fr_dscale, "AC-PHY diagnostic: multiply every replayed delay by this");
module_param_named(ac_fr_pad, b43_ac_fr_pad, uint, 0644);
MODULE_PARM_DESC(ac_fr_pad, "AC-PHY diagnostic: extra us of delay after every replayed op");
module_param_named(ac_fr_path, b43_ac_fr_path, charp, 0644);
module_param_named(ac_fr_start, b43_ac_fr_start, uint, 0644);
module_param_named(ac_fr_end, b43_ac_fr_end, uint, 0644);
module_param_named(ac_fr_mask, b43_ac_fr_mask, uint, 0644);
MODULE_PARM_DESC(ac_fr_path, "AC-PHY diagnostic: wl op file; replay trace lines [ac_fr_start, ac_fr_end) of types in ac_fr_mask (bit t-1: 1 phy 2 radio 3 tbl 4 delay 5 shm)");

struct b43_ac_fr_op {
	u32 line;
	u8 type, width;
	u16 a;
	u32 b, c;
} __packed;

static void b43_ac_fr_run(struct b43_wldev *dev)
{
	struct b43_ac_fr_op *buf;
	struct file *f;
	loff_t pos = 0;
	unsigned long n = 0, applied = 0;
	ssize_t got;

	f = filp_open(b43_ac_fr_path, O_RDONLY, 0);
	if (IS_ERR(f)) {
		b43warn(dev->wl, "ac_fr: cannot open %s\n", b43_ac_fr_path);
		return;
	}
	buf = kmalloc(16 * 4096, GFP_KERNEL);
	if (!buf) {
		filp_close(f, NULL);
		return;
	}
	pr_emerg("b43 ac_fr: start lines [%u,%u) mask %x\n", b43_ac_fr_start,
		 b43_ac_fr_end, b43_ac_fr_mask);
	mdelay(30);
	while ((got = kernel_read(f, buf, 16 * 4096, &pos)) >= (ssize_t)sizeof(*buf)) {
		unsigned int i, cnt = got / sizeof(*buf);

		pos -= got - cnt * sizeof(*buf);
		for (i = 0; i < cnt; i++, n++) {
			const struct b43_ac_fr_op *op = &buf[i];

			if (op->line >= b43_ac_fr_end)
				goto done;
			if (op->line < b43_ac_fr_start ||
			    !(b43_ac_fr_mask & (1u << (op->type - 1))))
				continue;
			applied++;
			switch (op->type) {
			case 1:
				b43_phy_write(dev, op->a, op->b);
				break;
			case 2:
				b43_radio_write(dev, op->a, op->b);
				break;
			case 3:
				b43_phy_write(dev, B43_PHY_AC_TABLE_ID, op->a);
				b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, op->b);
				if (op->width == 32)
					b43_phy_write(dev, B43_PHY_AC_TABLE_DATA2, op->c >> 16);
				b43_phy_write(dev, B43_PHY_AC_TABLE_DATA1, op->c & 0xffff);
				break;
			case 4: {
				u32 us = op->c * b43_ac_fr_dscale;

				if (us >= 1000)
					mdelay(us / 1000);
				else
					udelay(us);
				break;
			}
			case 5:
				if (op->width == 32)
					b43_shm_write32(dev, op->a, op->b, op->c);
				else
					b43_shm_write16(dev, op->a, op->b, op->c);
				break;
			}
			if (b43_ac_fr_pad)
				udelay(b43_ac_fr_pad);
		}
	}
done:
	kfree(buf);
	filp_close(f, NULL);
	pr_emerg("b43 ac_fr: done, %lu ops applied\n", applied);
	mdelay(30);
}

static uint b43_ac_phyinit = 1;
module_param_named(ac_phyinit, b43_ac_phyinit, uint, 0644);

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
	 * and the end state of the power-on (0x0408 = 0x0c02, 0x0417 = 4) */
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
	 * two-stream rates fail completely (notes/136). */
	if (dev->dev->bus_type == B43_BUS_BCMA)
		bcma_cc_set32(&dev->dev->bdev->bus->drv_cc, BCMA_CC_CHIPCTL, 0x00000008);
	b43_phy_ac_coeff_bank_init(dev);
	/* RX gain control, all cores (his rxgainctrl setup). Without it the
	 * receive level is 26 dB down: -66 instead of -40 dBm (notes/136). */
	b43_phy_write(dev, 0x1726, 0x000c);
	b43_phy_write(dev, 0x0197, 0x0014);	/* channel_setup */
	b43_phy_write(dev, 0x0198, 0x0010);
}

static bool b43_ac_txpwrctl;
module_param_named(ac_txpwrctl, b43_ac_txpwrctl, bool, 0644);
MODULE_PARM_DESC(ac_txpwrctl, "AC-PHY: enable the hardware TX power control loop (PHY 0x70 = 0xe500)");

static void b43_phy_ac_apply_por(struct b43_wldev *dev)
{

	/* Radio state the hardware TX power loop needs (TSSI / power detector
	 * path, per-core 0x01a-0x01f / 0x21a-0x21f, notes/136). Without it PHY 0x640/0x840 freeze at index 0 and
	 * the loop never reaches its target. */
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
	 * (notes/130-135). Only the PHY register writes are left. */
	if (b43_ac_phyinit)
		b43_phy_ac_phyinit(dev);
	/* Hardware TX power control: 0x70 bits 15:13 enable it, 0x71 holds the
	 * averaging window, 0x72 the rest of its configuration. Off by
	 * default: next to the AP the loop's power makes 28 % of the frames
	 * fail (upload 1-2 Mbit/s against 21 with 0x70 = 0x0100, notes/136). */
	b43_phy_write(dev, 0x0070, b43_ac_txpwrctl ? 0xe500 : 0x0100);
	b43_phy_write(dev, 0x0071, 0x04c8);
	b43_phy_write(dev, 0x0072, 0x400d);
	b43dbg(dev->wl, "phy_ac: applied first-load state 0x%x\n",
		b43_ac_por);
	if (b43_ac_rfkick)
		b43_ac_rfkick_run(dev);
	if (b43_ac_fr_path)
		b43_ac_fr_run(dev);
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
 * doesn't reach; diagnostic until the owning init step is ported. */
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

	if (b43_ac_por & 0x100) {
		static const u16 radio[][2] = {
			{ 0x049, 0x0030 }, { 0x249, 0x0030 },
			{ 0x04e, 0x8400 }, { 0x24e, 0x8600 },
			{ 0x122, 0x5830 }, { 0x322, 0x5830 },
			{ 0x126, 0x010b }, { 0x326, 0x010b },
			{ 0x02c, 0x61c1 }, { 0x22c, 0x61a1 },
			{ 0x245, 0x73ff }, { 0x145, 0x0185 }, { 0x146, 0x00ac },
			{ 0x407, 0x8302 }, { 0x65b, 0x037f },
		};

		for (i = 0; i < ARRAY_SIZE(radio); i++)
			b43_radio_write(dev, radio[i][0], radio[i][1]);
	}
	if (b43_ac_por & 0x80) {
		static const u16 mac[][2] = {
			{ 0x490, 0x0000 }, { 0x4ae, 0xffff }, { 0x4b8, 0x0000 },
			{ 0x4bc, 0x0000 }, { 0x500, 0x4000 }, { 0x612, 0x0400 },
			{ 0x684, 0x0207 }, { 0x69c, 0x0001 }, { 0x6a8, 0x05dc },
			{ 0x6b8, 0x0000 }, { 0x6c6, 0x0f0f }, { 0x6f0, 0x0001 },
			{ 0x816, 0x103f }, { 0x8c0, 0x0001 },
		};

		for (i = 0; i < ARRAY_SIZE(mac); i++)
			b43_write16(dev, mac[i][0], mac[i][1]);
		b43_write32(dev, 0x3dc, 0x00989680);
	}
}

#include "phy_ac_farrow.h"

static bool b43_ac_farrow = true;
module_param_named(ac_farrow, b43_ac_farrow, bool, 0644);
MODULE_PARM_DESC(ac_farrow, "AC-PHY: program the per-channel RX/TX Farrow resampler on channel switch");

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

/* Test (notes/111): replay one wl 20 MHz channel-116 switch, op for op. */
static bool b43_ac_win116;
module_param_named(ac_win116, b43_ac_win116, bool, 0644);
MODULE_PARM_DESC(ac_win116, "AC-PHY test: on 5 GHz channel 116 replay wl's whole channel-switch write sequence");
#include "phy_ac_win116.h"

static void b43_phy_ac_replay_win116(struct b43_wldev *dev)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(b43_ac_win116_ops); i++) {
		switch (b43_ac_win116_ops[i].t) {
		case 0:
			b43_phy_write(dev, b43_ac_win116_ops[i].a, b43_ac_win116_ops[i].v);
			break;
		case 1:
			b43_radio_write(dev, b43_ac_win116_ops[i].a, b43_ac_win116_ops[i].v);
			break;
		case 2:
			b43_phy_write(dev, B43_PHY_AC_TABLE_ID, b43_ac_win116_ops[i].a);
			b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, b43_ac_win116_ops[i].b);
			if (b43_ac_win116_ops[i].w == 32)
				b43_phy_write(dev, B43_PHY_AC_TABLE_DATA2,
					      b43_ac_win116_ops[i].v >> 16);
			b43_phy_write(dev, B43_PHY_AC_TABLE_DATA1,
				      b43_ac_win116_ops[i].v & 0xffff);
			break;
		case 3:
			udelay(min_t(u32, b43_ac_win116_ops[i].v, 2000));
			break;
		}
	}
	b43info(dev->wl, "phy_ac: replayed wl's channel-116 switch (%zu ops)\n",
		ARRAY_SIZE(b43_ac_win116_ops));
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
	if (is_5ghz && !b43_ac_5ghz) {
		b43dbg(dev->wl, "phy_ac: 5 GHz disabled (channel %u, ac_5ghz=0)\n",
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

	b43_phy_ac_tune(dev, e, new_channel);
	b43_phy_maskset(dev, 0x19e, ~0x3, save & 0x3);

	for (i = 0; i < 6; i++)
		b43_phy_write(dev, B43_PHY_AC_BW1A + i, e->bw[i]);

	/* wl's captured state is applied on channel 6; our own tuning then
	 * works for the other 2.4 GHz channels. Without ac_state_once this
	 * re-runs on every return to channel 6, e.g. after each off-channel
	 * scan step while associated. */
	if (!b43_ac_init_state && new_channel == 6 &&
	    !(b43_ac_state_once && phy_ac->wl_state_applied)) {
		if (b43_ac_replay)
			b43_phy_ac_replay_ch6(dev);
		if (b43_ac_por)
			b43_phy_ac_apply_por(dev);
		phy_ac->wl_state_applied = true;
	}
	if (is_5ghz && b43_ac_por && b43_ac_5g_80) {
		u32 ioctl;

		/* Test: keep wl's 80 MHz setup (synthesizer on its 80 MHz centre,
		 * PHY in 80 MHz mode) and set the core's PHY bandwidth to 80 MHz,
		 * toggling force-gated-clock around the change like wl. */
		b43_phy_ac_apply_por5g(dev);
		if (b43_ac_5g_ctr) {
			const struct b43_radio_2069_chan *c = b43_radio_2069_find_chan(dev, b43_ac_5g_ctr);

			if (c) {
				save = b43_phy_read(dev, 0x19e);
				b43_phy_set(dev, 0x19e, 0x3);
				b43_phy_ac_tune(dev, c, b43_ac_5g_ctr);
				b43_phy_maskset(dev, 0x19e, ~0x3, save & 0x3);
				for (i = 0; i < 6; i++)
					b43_phy_write(dev, B43_PHY_AC_BW1A + i, c->bw[i]);
				b43_phy_ac_set_farrow(dev, b43_ac_5g_ctr);
			}
		}
		ioctl = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl | 0x2);
		ioctl = (ioctl & ~B43_BCMA_IOCTL_PHY_BW) | B43_BCMA_IOCTL_PHY_BW_80MHZ;
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl | 0x2);
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl);
		b43info(dev->wl, "phy_ac: 5 GHz 80 MHz test, ioctrl %08x\n",
			bcma_aread32(dev->dev->bdev, BCMA_IOCTL));
	} else if (is_5ghz && b43_ac_por) {
		b43_phy_ac_apply_por5g(dev);
		/* wl's state tunes to its 80 MHz centre; tune our channel. */
		save = b43_phy_read(dev, 0x19e);
		b43_phy_set(dev, 0x19e, 0x3);
		b43_phy_ac_tune(dev, e, new_channel);
		b43_phy_maskset(dev, 0x19e, ~0x3, save & 0x3);
		for (i = 0; i < 6; i++)
			b43_phy_write(dev, B43_PHY_AC_BW1A + i, e->bw[i]);
	} else if (b43_ac_por)
		b43_phy_ac_rfctrl_wl(dev);

	/* After the wl snapshot. wl's own trace uses this same per-channel
	 * 20 MHz table on 5 GHz channels too (confirmed against its 5 GHz
	 * scan sweep, notes/53) - but not when ac_5g_80 keeps wl's captured
	 * 80 MHz state instead of retuning per-channel, a different PHY mode
	 * this table was never shown to apply to. */
	if (b43_ac_farrow && !(is_5ghz && b43_ac_5g_80))
		b43_phy_ac_set_farrow(dev, new_channel);

	if (is_5ghz && new_channel == 116 && b43_ac_win116)
		b43_phy_ac_replay_win116(dev);

	b43_phy_ac_resetcca(dev);

	if (b43_ac_rfseq) {
		u8 cores = b43_phy_ac_num_cores(dev);

		/* vendor FUN_001aeb3a (real channel/PLL tuning) fires this,
		 * unconditionally, before anything else in the tune - untested
		 * standalone. See notes/11. */
		b43_phy_ac_force_rfseq(dev, 2);
		b43_phy_ac_rxcore_setstate(dev, (1 << cores) - 1);
	}

	if (b43_ac_txcal_test) {
		/* Exercises only the already-drafted, non-RF pieces of the TX
		 * calibration code (notes/16): table save/restore, the settle
		 * pulse, and the ramp-table writer. Deliberately does NOT
		 * touch the RF-loopback-mode switch or generate any tone -
		 * those aren't ported yet. Logs before/after values so a live
		 * dmesg read is enough to see whether the code round-trips
		 * correctly; does not change device behavior once done since
		 * everything it touches gets restored.
		 */
		struct b43_phy_ac_txcal_gainsave save;
		struct b43_phy_ac_txcal_radiosave radiosave;
		static const u16 test_gain[4][4] = {
			{ 0x1234, 0x1234, 0x1234, 0x1234 }, { 0x1234, 0x1234, 0x1234, 0x1234 },
			{ 0x1234, 0x1234, 0x1234, 0x1234 }, { 0x1234, 0x1234, 0x1234, 0x1234 },
		};

		/* Read-only: verifies the resolved register addresses for the
		 * (still unwritten) loopback-mode switch look plausible on
		 * real hardware. See b43_phy_ac_txcal_read_radiosave's
		 * comment for why only the read half is tested.
		 */
		b43_phy_ac_txcal_read_radiosave(dev, &radiosave);
		b43info(dev->wl, "phy_ac: txcal test: radio core0 1a=%04x 1b=%04x 1c=%04x 1e=%04x 1f=%04x 24=%04x 170=%04x\n",
			radiosave.r1a[0], radiosave.r1b[0], radiosave.r1c[0],
			radiosave.r1e[0], radiosave.r1f[0], radiosave.r24[0],
			radiosave.r170_or_184[0]);
		if (b43_phy_ac_num_cores(dev) > 1)
			b43info(dev->wl, "phy_ac: txcal test: radio core1 1a=%04x 1b=%04x 1c=%04x 1e=%04x 1f=%04x 24=%04x 170=%04x\n",
				radiosave.r1a[1], radiosave.r1b[1], radiosave.r1c[1],
				radiosave.r1e[1], radiosave.r1f[1], radiosave.r24[1],
				radiosave.r170_or_184[1]);

		b43info(dev->wl, "phy_ac: txcal test: before, tbl7[0]=%04x %04x %04x\n",
			b43_phy_ac_table_read16(dev, 7, 0x100),
			b43_phy_ac_table_read16(dev, 7, 0x103),
			b43_phy_ac_table_read16(dev, 7, 0x106));

		b43_phy_ac_txcal_save_gaintbl(dev, &save, test_gain);
		b43info(dev->wl, "phy_ac: txcal test: after override, tbl7[0]=%04x %04x %04x (want 1234 1234 1234)\n",
			b43_phy_ac_table_read16(dev, 7, 0x100),
			b43_phy_ac_table_read16(dev, 7, 0x103),
			b43_phy_ac_table_read16(dev, 7, 0x106));

		b43_phy_ac_txcal_settle_pulse(dev);
		b43info(dev->wl, "phy_ac: txcal test: settle pulse done\n");

		b43_phy_ac_txcal_ramp_table(dev, 50);
		b43info(dev->wl, "phy_ac: txcal test: ramp table at 50%%, tbl0xc[0]=%04x tbl0xc[0x20]=%04x\n",
			b43_phy_ac_table_read16(dev, 0xc, 0),
			b43_phy_ac_table_read16(dev, 0xc, 0x20));

		b43_phy_ac_txcal_restore_gaintbl(dev, &save);
		b43info(dev->wl, "phy_ac: txcal test: after restore, tbl7[0]=%04x %04x %04x (want match 'before')\n",
			b43_phy_ac_table_read16(dev, 7, 0x100),
			b43_phy_ac_table_read16(dev, 7, 0x103),
			b43_phy_ac_table_read16(dev, 7, 0x106));
	}

	if (b43_ac_txcal_loopback_test) {
		/* Separate, higher-risk flag: writes to live RF front-end
		 * registers using a documented best-guess for 2 unresolved
		 * wl-internal conditions (see b43_phy_ac_txcal_enter_loopback's
		 * comment). Enters loopback mode, logs the result, then
		 * immediately exits/restores - no tone, no live TX.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;

		b43info(dev->wl, "phy_ac: txcal loopback test: entering\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);
		b43info(dev->wl, "phy_ac: txcal loopback test: before core0 1a=%04x 1f=%04x 1e=%04x 170=%04x\n",
			radiosave.r1a[0], radiosave.r1f[0], radiosave.r1e[0],
			radiosave.r170_or_184[0]);
		b43info(dev->wl, "phy_ac: txcal loopback test: after-enter core0 1a=%04x 1f=%04x 1e=%04x 170=%04x (want 1a low nibble of top byte=8, 1f bit2=0, 1e bit2=1, 170 bit8=0 bit14=1)\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));

		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43info(dev->wl, "phy_ac: txcal loopback test: after-exit core0 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match 'before')\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}

	if (b43_ac_txcal_tone_test) {
		/* Highest-risk flag in this project so far: a real, brief TX
		 * test tone, generated only while inside the RF-loopback mode
		 * already validated above. See b43_phy_ac_txcal_gen_tone's
		 * comment for what is and isn't faithfully replicated.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;

		b43info(dev->wl, "phy_ac: txcal tone test: entering loopback\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);

		b43info(dev->wl, "phy_ac: txcal tone test: before 460=%04x 403=%04x 400=%04x loopbackrd(core0)=%04x core1=%04x\n",
			b43_phy_read(dev, 0x460), b43_phy_read(dev, 0x403),
			b43_phy_read(dev, 0x400),
			b43_radio_read(dev, 0x144),
			b43_radio_read(dev, 0x144 | 0x200));

		b43info(dev->wl, "phy_ac: txcal tone test: generating tone\n");
		b43_phy_ac_txcal_gen_tone(dev);

		/* Read-only, purely observational: 0x144|core<<9 is the exact
		 * loopback-measurement register decompiled-cal/FUN_001ac9b6.c
		 * polls after each write during the real calibration sweep
		 * (acphychipid==0x4360 branch). We aren't running that sweep,
		 * just seeing whether anything here visibly reacted to the
		 * tone at all - not a measurement, just a first look.
		 */
		b43info(dev->wl, "phy_ac: txcal tone test: after 460=%04x 403=%04x 400=%04x loopbackrd(core0)=%04x core1=%04x (want 460/403/400 match 'before')\n",
			b43_phy_read(dev, 0x460), b43_phy_read(dev, 0x403),
			b43_phy_read(dev, 0x400),
			b43_radio_read(dev, 0x144),
			b43_radio_read(dev, 0x144 | 0x200));

		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43info(dev->wl, "phy_ac: txcal tone test: after-exit-loopback 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match loopback test's 'before')\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}

	if (b43_ac_txcal_tone_sustain_test) {
		/* See b43_phy_ac_txcal_gen_tone_start's comment: unlike
		 * ac_txcal_tone_test, this leaves the tone actually playing
		 * for a short, bounded window (10 samples * 200us = 2ms)
		 * while repeatedly reading the loopback-measurement register,
		 * before explicitly stopping it. Still purely observational -
		 * no writes to 899/0x380 (the actual candidate-search
		 * registers), so this cannot yet find/apply a real
		 * correction, only observe whether anything detectable
		 * changes while a live tone is actually sustained.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;
		struct b43_phy_ac_txcal_tonesave tonesave;
		int i;

		b43info(dev->wl, "phy_ac: txcal tone sustain test: entering loopback\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);

		b43info(dev->wl, "phy_ac: txcal tone sustain test: idle loopbackrd(core0)=%04x core1=%04x\n",
			b43_radio_read(dev, 0x144),
			b43_radio_read(dev, 0x144 | 0x200));

		b43_phy_ac_txcal_gen_tone_start(dev, &tonesave);

		for (i = 0; i < 10; i++) {
			udelay(200);
			b43info(dev->wl, "phy_ac: txcal tone sustain test: playing[%d] 460=%04x 403=%04x loopbackrd(core0)=%04x core1=%04x\n",
				i, b43_phy_read(dev, 0x460),
				b43_phy_read(dev, 0x403),
				b43_radio_read(dev, 0x144),
				b43_radio_read(dev, 0x144 | 0x200));
		}

		b43_phy_ac_txcal_gen_tone_stop(dev, &tonesave);
		b43info(dev->wl, "phy_ac: txcal tone sustain test: after-stop 460=%04x loopbackrd(core0)=%04x core1=%04x\n",
			b43_phy_read(dev, 0x460),
			b43_radio_read(dev, 0x144),
			b43_radio_read(dev, 0x144 | 0x200));

		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43info(dev->wl, "phy_ac: txcal tone sustain test: after-exit-loopback 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match 'idle' state)\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}

	if (b43_ac_txcal_candidate_test) {
		/* First closed-loop, hardware-reactive test in this project -
		 * see b43_phy_ac_txcal_measure_candidates's comment for the
		 * full derivation. Combines everything validated so far:
		 * loopback mode, a sustained tone, then the real
		 * measurement-trigger sequence while the tone plays.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;
		struct b43_phy_ac_txcal_tonesave tonesave;

		b43info(dev->wl, "phy_ac: txcal candidate test: entering loopback\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);

		b43info(dev->wl, "phy_ac: txcal candidate test: starting tone\n");
		b43_phy_ac_txcal_gen_tone_start(dev, &tonesave);
		/* FUN_0019d65d, called once per core the first time it's
		 * touched in the real sweep - confirmed against a real wl
		 * trace (notes/21): percent=65 exactly reproduces the
		 * observed table-0xC ramp values. Not core-parameterized in
		 * this port (table 0xC's ramp region isn't per-core
		 * addressed), matching the single occurrence seen in the
		 * trace for our single-core (core 0) test.
		 */
		b43_phy_ac_txcal_ramp_table(dev, 65);

		b43_phy_ac_txcal_measure_candidates(dev);

		b43_phy_ac_txcal_gen_tone_stop(dev, &tonesave);
		b43info(dev->wl, "phy_ac: txcal candidate test: tone stopped\n");

		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43info(dev->wl, "phy_ac: txcal candidate test: after-exit-loopback 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match loopback test's 'before')\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}

	if (b43_ac_txcal_candidate_test2) {
		/* Same measurement as ac_txcal_candidate_test, but in wl's
		 * real order and with the settle pulse + gain-table override
		 * (as a same-value no-op) added beforehand - see this flag's
		 * MODULE_PARM_DESC for why.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;
		struct b43_phy_ac_txcal_tonesave tonesave;
		struct b43_phy_ac_txcal_gainsave gainsave;
		/* Real calibration-tone gain values, confirmed against a real
		 * wl trace for our exact 2-core board (see notes/20) -
		 * replaces the earlier "read current value back" no-op.
		 */
		static const u16 new_gain[B43_PHY_AC_TXCAL_MAX_CORES][4] = {
			{ 0xff00, 0x47ff, 0xa7, 0x41 },
			{ 0xff00, 0x27ff, 0xa7, 0x40 },
		};

		b43info(dev->wl, "phy_ac: txcal candidate test2: entering loopback\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);

		b43_phy_ac_txcal_settle_pulse(dev);
		b43_phy_ac_txcal_save_gaintbl(dev, &gainsave, new_gain);
		/* FUN_001ac9b6 line 609, confirmed in a real wl trace (notes/20):
		 * a single PHY reg 0x382 write, between the gain-table
		 * override and the per-core table-0xC clears / tone start.
		 */
		b43_phy_write(dev, 0x382, 0x8a09);
		b43info(dev->wl, "phy_ac: txcal candidate test2: after settle+gain-override (no-op values), starting tone\n");

		b43_phy_ac_txcal_gen_tone_start(dev, &tonesave);
		b43_phy_ac_txcal_ramp_table(dev, 65);
		b43_phy_ac_txcal_measure_candidates(dev);
		b43_phy_ac_txcal_gen_tone_stop(dev, &tonesave);
		b43info(dev->wl, "phy_ac: txcal candidate test2: tone stopped\n");

		b43_phy_ac_txcal_restore_gaintbl(dev, &gainsave);
		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43info(dev->wl, "phy_ac: txcal candidate test2: after-exit-loopback 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match loopback test's 'before')\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}

	if (b43_ac_txcal_setup_test) {
		/* Isolated round-trip check of the new measurement setup
		 * block, before combining it with anything else - see this
		 * flag's MODULE_PARM_DESC.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;
		struct b43_phy_ac_txcal_setupsave setupsave;

		b43info(dev->wl, "phy_ac: txcal setup test: entering loopback\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);

		b43info(dev->wl, "phy_ac: txcal setup test: before core0 735=%04x 73a=%04x 720=%04x core1 735=%04x 73a=%04x 720=%04x\n",
			b43_phy_read(dev, 0x735), b43_phy_read(dev, 0x73a),
			b43_phy_read(dev, 0x720),
			b43_phy_read(dev, 0x735 + 0x200),
			b43_phy_read(dev, 0x73a + 0x200),
			b43_phy_read(dev, 0x720 + 0x200));

		b43_phy_ac_txcal_measure_setup_enter(dev, &setupsave);
		b43info(dev->wl, "phy_ac: txcal setup test: after-enter core0 735=%04x 73a=%04x 720=%04x core1 735=%04x 73a=%04x 720=%04x\n",
			b43_phy_read(dev, 0x735), b43_phy_read(dev, 0x73a),
			b43_phy_read(dev, 0x720),
			b43_phy_read(dev, 0x735 + 0x200),
			b43_phy_read(dev, 0x73a + 0x200),
			b43_phy_read(dev, 0x720 + 0x200));

		b43_phy_ac_txcal_measure_setup_exit(dev, &setupsave);
		b43info(dev->wl, "phy_ac: txcal setup test: after-exit core0 735=%04x 73a=%04x 720=%04x core1 735=%04x 73a=%04x 720=%04x (want match 'before')\n",
			b43_phy_read(dev, 0x735), b43_phy_read(dev, 0x73a),
			b43_phy_read(dev, 0x720),
			b43_phy_read(dev, 0x735 + 0x200),
			b43_phy_read(dev, 0x73a + 0x200),
			b43_phy_read(dev, 0x720 + 0x200));

		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43info(dev->wl, "phy_ac: txcal setup test: after-exit-loopback 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match loopback test's 'before')\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}

	if (b43_ac_txcal_resetcca_test) {
		/* Isolated test of the new BCMA_IOCTL_FGC-based cleanup,
		 * before combining it with anything else - see this flag's
		 * MODULE_PARM_DESC and b43_phy_ac_txcal_resetcca's comment.
		 * No loopback, no tone, no candidate sweep.
		 */
		u32 ioctl_before = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
		u16 phy1_before = b43_phy_read(dev, 1);

		b43info(dev->wl, "phy_ac: txcal resetcca test: before ioctl=%08x phy1=%04x\n",
			ioctl_before, phy1_before);

		b43_phy_ac_txcal_resetcca(dev);

		b43info(dev->wl, "phy_ac: txcal resetcca test: after ioctl=%08x phy1=%04x (want match 'before')\n",
			bcma_aread32(dev->dev->bdev, BCMA_IOCTL),
			b43_phy_read(dev, 1));
	}

	if (b43_ac_txcal_candidate_test3) {
		/* Adds the per-core measurement setup block, the one piece of
		 * FUN_001ac9b6's context still missing from candidate_test2.
		 * See b43_phy_ac_txcal_measure_setup_enter's comment for the
		 * BCMA_IOCTL-avoidance rationale for its exit counterpart.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;
		struct b43_phy_ac_txcal_tonesave tonesave;
		struct b43_phy_ac_txcal_gainsave gainsave;
		struct b43_phy_ac_txcal_setupsave setupsave;
		/* Real calibration-tone gain values, confirmed against a real
		 * wl trace for our exact 2-core board (see notes/20) -
		 * replaces the earlier "read current value back" no-op.
		 */
		static const u16 new_gain[B43_PHY_AC_TXCAL_MAX_CORES][4] = {
			{ 0xff00, 0x47ff, 0xa7, 0x41 },
			{ 0xff00, 0x27ff, 0xa7, 0x40 },
		};
		u16 saved140 = b43_phy_read(dev, 0x140);

		b43info(dev->wl, "phy_ac: txcal candidate test3: entering loopback\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);

		b43_phy_ac_txcal_measure_setup_enter(dev, &setupsave);
		b43_phy_ac_txcal_settle_pulse(dev);
		b43_phy_ac_txcal_save_gaintbl(dev, &gainsave, new_gain);
		/* FUN_001ac9b6 line 609, confirmed in a real wl trace (notes/20):
		 * a single PHY reg 0x382 write, between the gain-table
		 * override and the per-core table-0xC clears / tone start.
		 */
		b43_phy_write(dev, 0x382, 0x8a09);
		b43info(dev->wl, "phy_ac: txcal candidate test3: setup done, starting tone\n");

		b43_phy_ac_txcal_gen_tone_start(dev, &tonesave);
		b43_phy_ac_txcal_ramp_table(dev, 65);
		b43_phy_ac_txcal_measure_candidates(dev);
		b43_phy_ac_txcal_gen_tone_stop(dev, &tonesave);
		b43info(dev->wl, "phy_ac: txcal candidate test3: tone stopped\n");

		b43_phy_ac_txcal_restore_gaintbl(dev, &gainsave);
		b43_phy_ac_txcal_measure_setup_exit(dev, &setupsave);
		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43_phy_write(dev, 0x140, saved140);
		b43info(dev->wl, "phy_ac: txcal candidate test3: after-exit-loopback 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match loopback test's 'before')\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}

	if (b43_ac_txcal_candidate_test4) {
		/* Same as candidate_test3, plus wlc_phy_classifier_acphy(pi,7,4)
		 * (decompiled-cal/wlc_phy_classifier_acphy.c: PHY reg 0x140,
		 * mask=7 set=4) right before entering loopback, matching
		 * vendor's real call order exactly.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;
		struct b43_phy_ac_txcal_tonesave tonesave;
		struct b43_phy_ac_txcal_gainsave gainsave;
		struct b43_phy_ac_txcal_setupsave setupsave;
		/* Real calibration-tone gain values, confirmed against a real
		 * wl trace for our exact 2-core board (see notes/20) -
		 * replaces the earlier "read current value back" no-op.
		 */
		static const u16 new_gain[B43_PHY_AC_TXCAL_MAX_CORES][4] = {
			{ 0xff00, 0x47ff, 0xa7, 0x41 },
			{ 0xff00, 0x27ff, 0xa7, 0x40 },
		};
		u16 saved140 = b43_phy_read(dev, 0x140);

		b43_phy_maskset(dev, 0x140, ~7, 4);
		b43info(dev->wl, "phy_ac: txcal candidate test4: classifier set, entering loopback\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);

		b43_phy_ac_txcal_measure_setup_enter(dev, &setupsave);
		b43_phy_ac_txcal_settle_pulse(dev);
		b43_phy_ac_txcal_save_gaintbl(dev, &gainsave, new_gain);
		/* FUN_001ac9b6 line 609, confirmed in a real wl trace (notes/20):
		 * a single PHY reg 0x382 write, between the gain-table
		 * override and the per-core table-0xC clears / tone start.
		 */
		b43_phy_write(dev, 0x382, 0x8a09);
		b43info(dev->wl, "phy_ac: txcal candidate test4: setup done, starting tone\n");

		b43_phy_ac_txcal_gen_tone_start(dev, &tonesave);
		b43_phy_ac_txcal_ramp_table(dev, 65);
		b43_phy_ac_txcal_measure_candidates(dev);
		b43_phy_ac_txcal_gen_tone_stop(dev, &tonesave);
		b43info(dev->wl, "phy_ac: txcal candidate test4: tone stopped\n");

		b43_phy_ac_txcal_restore_gaintbl(dev, &gainsave);
		b43_phy_ac_txcal_measure_setup_exit(dev, &setupsave);
		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43_phy_write(dev, 0x140, saved140);
		b43info(dev->wl, "phy_ac: txcal candidate test4: after-exit-loopback 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match loopback test's 'before')\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}

	if (b43_ac_txcal_candidate_test5) {
		/* Identical to candidate_test4, but sweeps all 6 outer-sample
		 * candidates instead of just entry 0 - see this flag's
		 * MODULE_PARM_DESC.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;
		struct b43_phy_ac_txcal_tonesave tonesave;
		struct b43_phy_ac_txcal_gainsave gainsave;
		struct b43_phy_ac_txcal_setupsave setupsave;
		/* Real calibration-tone gain values, confirmed against a real
		 * wl trace for our exact 2-core board (see notes/20) -
		 * replaces the earlier "read current value back" no-op.
		 */
		static const u16 new_gain[B43_PHY_AC_TXCAL_MAX_CORES][4] = {
			{ 0xff00, 0x47ff, 0xa7, 0x41 },
			{ 0xff00, 0x27ff, 0xa7, 0x40 },
		};
		u16 saved140 = b43_phy_read(dev, 0x140);

		b43_phy_maskset(dev, 0x140, ~7, 4);
		b43info(dev->wl, "phy_ac: txcal candidate test5: classifier set, entering loopback\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);

		b43_phy_ac_txcal_measure_setup_enter(dev, &setupsave);
		b43_phy_ac_txcal_settle_pulse(dev);
		b43_phy_ac_txcal_save_gaintbl(dev, &gainsave, new_gain);
		/* FUN_001ac9b6 line 609, confirmed in a real wl trace (notes/20):
		 * a single PHY reg 0x382 write, between the gain-table
		 * override and the per-core table-0xC clears / tone start.
		 */
		b43_phy_write(dev, 0x382, 0x8a09);
		b43info(dev->wl, "phy_ac: txcal candidate test5: setup done, starting tone\n");

		b43_phy_ac_txcal_gen_tone_start(dev, &tonesave);
		b43_phy_ac_txcal_ramp_table(dev, 65);
		b43_phy_ac_txcal_measure_candidates_sweep(dev);
		b43_phy_ac_txcal_gen_tone_stop(dev, &tonesave);
		b43info(dev->wl, "phy_ac: txcal candidate test5: tone stopped\n");

		b43_phy_ac_txcal_restore_gaintbl(dev, &gainsave);
		b43_phy_ac_txcal_measure_setup_exit(dev, &setupsave);
		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43_phy_write(dev, 0x140, saved140);
		b43info(dev->wl, "phy_ac: txcal candidate test5: after-exit-loopback 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match loopback test's 'before')\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}

	if (b43_ac_txcal_candidate_test6) {
		/* Identical to candidate_test5, but with wl's real
		 * resetcca-based cleanup instead of the save/write-back
		 * workaround - see this flag's MODULE_PARM_DESC.
		 */
		struct b43_phy_ac_txcal_radiosave radiosave;
		struct b43_phy_ac_txcal_tonesave tonesave;
		struct b43_phy_ac_txcal_gainsave gainsave;
		struct b43_phy_ac_txcal_setupsave setupsave;
		/* Real calibration-tone gain values, confirmed against a real
		 * wl trace for our exact 2-core board (see notes/20) -
		 * replaces the earlier "read current value back" no-op.
		 */
		static const u16 new_gain[B43_PHY_AC_TXCAL_MAX_CORES][4] = {
			{ 0xff00, 0x47ff, 0xa7, 0x41 },
			{ 0xff00, 0x27ff, 0xa7, 0x40 },
		};
		u16 saved140 = b43_phy_read(dev, 0x140);

		b43_phy_maskset(dev, 0x140, ~7, 4);
		b43info(dev->wl, "phy_ac: txcal candidate test6: classifier set, entering loopback\n");
		b43_phy_ac_txcal_enter_loopback(dev, &radiosave);

		b43_phy_ac_txcal_measure_setup_enter(dev, &setupsave);
		b43_phy_ac_txcal_settle_pulse(dev);
		b43_phy_ac_txcal_save_gaintbl(dev, &gainsave, new_gain);
		/* FUN_001ac9b6 line 609, confirmed in a real wl trace (notes/20):
		 * a single PHY reg 0x382 write, between the gain-table
		 * override and the per-core table-0xC clears / tone start.
		 */
		b43_phy_write(dev, 0x382, 0x8a09);
		b43info(dev->wl, "phy_ac: txcal candidate test6: setup done, starting tone\n");

		b43_phy_ac_txcal_gen_tone_start(dev, &tonesave);
		b43_phy_ac_txcal_ramp_table(dev, 65);
		b43_phy_ac_txcal_measure_candidates_sweep(dev);
		b43_phy_ac_txcal_gen_tone_stop(dev, &tonesave);
		b43info(dev->wl, "phy_ac: txcal candidate test6: tone stopped, running real resetcca cleanup\n");

		b43_phy_ac_txcal_restore_gaintbl(dev, &gainsave);
		b43_phy_ac_txcal_measure_setup_exit(dev, &setupsave);
		b43_phy_ac_txcal_resetcca(dev);
		b43_phy_ac_txcal_exit_loopback(dev, &radiosave);
		b43_phy_write(dev, 0x140, saved140);
		b43info(dev->wl, "phy_ac: txcal candidate test6: after-exit-loopback 1a=%04x 1f=%04x 1e=%04x 170=%04x (want match loopback test's 'before')\n",
			b43_radio_read(dev, 0x1a), b43_radio_read(dev, 0x1f),
			b43_radio_read(dev, 0x1e), b43_radio_read(dev, 0x170));
	}


	if (!is_5ghz && b43_ac_txidx >= 0)
		b43_phy_ac_txpwr_by_index(dev, b43_ac_txidx);

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

/*
 * Force one RF-sequencer settling step and wait for hardware to signal
 * completion (vendor wlc_phy_force_rfseq_acphy). `which` selects one of 6
 * vendor-defined steps, each a single bit in PHY 0x402/0x403; case values
 * and their bits come straight from the decompiled switch. Only called from
 * b43_phy_ac_rxcore_setstate() with which=0 and which=1, matching the
 * vendor's own only call site.
 */
static void b43_phy_ac_force_rfseq(struct b43_wldev *dev, u8 which)
{
	static const u16 seq_bit[6] = { 1, 2, 0x20, 4, 8, 0x10 };
	u16 save400, save19e, bit;
	int i;

	if (which >= ARRAY_SIZE(seq_bit))
		return;
	bit = seq_bit[which];

	save400 = b43_phy_read(dev, 0x400);
	save19e = b43_phy_read(dev, 0x19e);
	b43_phy_set(dev, 0x19e, 0x2);
	b43_phy_set(dev, 0x19e, 0x1);
	b43_phy_set(dev, 0x400, 0x3);
	b43_phy_set(dev, 0x402, bit);
	/* wl waits 10 us before polling (seq.txt 137510); the busy bit is not up immediately */
	udelay(10);
	for (i = 200009; i != 9; i -= 10) {
		if (!(b43_phy_read(dev, 0x403) & bit))
			break;
		udelay(10);
	}
	b43_phy_write(dev, 0x400, save400);
	b43_phy_write(dev, 0x19e, save19e);
}

/*
 * Configure the PHY's active RX-core state and run the RF sequencer's
 * settling steps for it (vendor wlc_phy_rxcore_setstate_acphy). Never
 * called by wl until the channel-set tail decides the active core count
 * changed; we always run it once per channel switch, which is a superset
 * of what's needed and harmless (MAC is suspended throughout).
 *
 * Untested hypothesis (ac_rfseq): this step is entirely missing from our
 * port, and its absence may leave the analog front-end's per-core gain/LNA
 * state unsettled in a way that's invisible to host-generated TX (which has
 * extra software latency to settle in) but causes the firmware's own fast,
 * autonomous transmissions (ACK, beacon) to fail probabilistically. See
 * notes/10 and notes/11.
 */
static void b43_phy_ac_rxcore_setstate(struct b43_wldev *dev, u8 mask)
{
	u16 save400, save401;

	b43_mac_suspend(dev);

	save400 = b43_phy_read(dev, 0x400);
	save401 = b43_phy_read(dev, 0x401);

	b43_phy_maskset(dev, 0x160, ~0x7, mask);
	b43_phy_maskset(dev, 0x401, ~0x70, (u16)mask << 4);
	b43_phy_set(dev, 0x401, 0x7000);
	b43_phy_mask(dev, 0x401, ~0x7);
	b43_phy_set(dev, 0x400, 0x1);

	b43_phy_ac_force_rfseq(dev, 0);
	b43_phy_ac_force_rfseq(dev, 1);

	b43_phy_maskset(dev, 0x401, ~0x7, mask);
	b43_phy_maskset(dev, 0x401, ~0x7000, save401 & 0x7000);
	b43_phy_write(dev, 0x400, save400);

	b43_mac_enable(dev);
}

/*
 * ---------------------------------------------------------------------
 * UNTESTED DRAFT - TX IQ/LO calibration (wlc_phy_cals_acphy and friends).
 *
 * Not wired into anything, not tested on hardware. Decompiled from wl's TX
 * IQ-imbalance/LO-feedthrough calibration routine, which our port has
 * never invoked at all (see notes/16-status-2026-09-27-tx-calibration-missing.md
 * for the full algorithm map and the reasoning for treating this as the
 * most likely cause of the firmware-autonomous-TX failure this project has
 * chased since notes/07). That routine generates a live test tone and
 * sweeps gain/frequency settings on real hardware in a loop - the same
 * category of operation that caused this project's one hard machine
 * freeze (notes/07). Do not call any of this, or build on it, without the
 * user physically present: test each piece incrementally against real
 * hardware as it's added, the way every other live-TX experiment in this
 * project has been done.
 *
 * What follows so far is only the lowest-risk slice: reading and writing a
 * single AC-PHY table entry (mirrors wl's wlc_phy_table_read_acphy /
 * wlc_phy_table_write_acphy, and mainline b43's own N-PHY table access
 * pattern in tables_nphy.c - write the address, then read/write the data
 * port), and the per-core save/restore of the TX gain table (table 7 - the
 * same table wlc_phy_txpwr_by_index_acphy uses for real traffic) and its
 * paired table-0xC entries around a calibration tone
 * (decompiled-cal/FUN_0019d3ac.c, FUN_0019d550.c, FUN_00199491.c,
 * FUN_0019d224.c). This alone does nothing observable - it's just the
 * save/restore bookkeeping half, with no caller yet. The remaining,
 * harder pieces (switching the RF front-end into its on-chip calibration
 * loopback mode, generating the tone, and the actual correction-sweep
 * measurement) are documented in notes/16 but not implemented, since they
 * involve real chip-ID/band-dependent branching and live RF that should
 * be written and tested incrementally with the user present, not typed in
 * one block from decompiled source and trusted blind.
 * ---------------------------------------------------------------------
 */

static u16 b43_phy_ac_table_read16(struct b43_wldev *dev, u16 id, u16 offset)
{
	b43_phy_write(dev, B43_PHY_AC_TABLE_ID, id);
	b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, offset);
	return b43_phy_read(dev, B43_PHY_AC_TABLE_DATA1);
}

static void b43_phy_ac_table_write16(struct b43_wldev *dev, u16 id, u16 offset,
				      u16 value)
{
	b43_phy_write(dev, B43_PHY_AC_TABLE_ID, id);
	b43_phy_write(dev, B43_PHY_AC_TABLE_OFFSET, offset);
	b43_phy_write(dev, B43_PHY_AC_TABLE_DATA1, value);
}

/* Set the TX gain of both cores from the 2.4 GHz gain table, as the stock
 * driver's txpwr_by_index does with hardware power control off. */
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

/* decompiled-cal/FUN_00199491.c: per-core table-0xC offset for the single
 * saved entry (the "0x63" set; FUN_0019d224.c writes both the "0x63" and
 * "0x73" sets on restore, but only the former is ever read back to save).
 */
static const u16 b43_phy_ac_txcal_tbl0xc_off[B43_PHY_AC_TXCAL_MAX_CORES] = {
	0x63, 0x67, 0x6b, 0x6f,
};
static const u16 b43_phy_ac_txcal_tbl0xc_off2[B43_PHY_AC_TXCAL_MAX_CORES] = {
	0x73, 0x77, 0x7b, 0x7f,
};

/* decompiled-cal/FUN_0019d3ac.c: save each core's current TX gain-table
 * (table 7) entry and its paired table-0xC entry, then overwrite table 7
 * AND table 0xC with the calibration-tone gain settings from "new_gain".
 *
 * CORRECTED against a real wl trace (traces/wl-init-20260927-184726.trace,
 * see notes/20): this function originally only overrode table 7 and left
 * table 0xC completely untouched (only ever saving the old value for
 * later restore) - a real gap, not a simplification. wl's actual
 * FUN_0019d3ac also calls FUN_0019d224 to write a 4th value into BOTH of
 * table 0xC's paired offsets (b43_phy_ac_txcal_tbl0xc_off[core] and
 * _off2[core] - confirmed identical in the trace, matching
 * FUN_0019d224.c writing the same source value to both). new_gain now
 * carries that 4th value per core.
 */
static void b43_phy_ac_txcal_save_gaintbl(struct b43_wldev *dev,
					   struct b43_phy_ac_txcal_gainsave *save,
					   const u16 new_gain[][4])
{
	u8 core, cores = b43_phy_ac_num_cores(dev);
	u16 saved19e = b43_phy_read(dev, 0x19e);

	b43_phy_set(dev, 0x19e, 0x2);

	for (core = 0; core < cores && core < B43_PHY_AC_TXCAL_MAX_CORES; core++) {
		save->tbl7[core][0] = b43_phy_ac_table_read16(dev, 7, core + 0x100);
		save->tbl7[core][1] = b43_phy_ac_table_read16(dev, 7, core + 0x103);
		save->tbl7[core][2] = b43_phy_ac_table_read16(dev, 7, core + 0x106);
		save->tbl0xc[core] = b43_phy_ac_table_read16(dev,
					0xc, b43_phy_ac_txcal_tbl0xc_off[core]);

		b43_phy_ac_table_write16(dev, 7, core + 0x100, new_gain[core][0]);
		b43_phy_ac_table_write16(dev, 7, core + 0x103, new_gain[core][1]);
		b43_phy_ac_table_write16(dev, 7, core + 0x106, new_gain[core][2]);
		b43_phy_ac_table_write16(dev, 0xc,
					  b43_phy_ac_txcal_tbl0xc_off[core],
					  new_gain[core][3]);
		b43_phy_ac_table_write16(dev, 0xc,
					  b43_phy_ac_txcal_tbl0xc_off2[core],
					  new_gain[core][3]);
	}

	b43_phy_maskset(dev, 0x19e, ~0x2, saved19e & 0x2);
}

/* decompiled-cal/FUN_0019d550.c + FUN_0019d224.c: restore what
 * b43_phy_ac_txcal_save_gaintbl saved.
 */
static void b43_phy_ac_txcal_restore_gaintbl(struct b43_wldev *dev,
					const struct b43_phy_ac_txcal_gainsave *save)
{
	u8 core, cores = b43_phy_ac_num_cores(dev);
	u16 saved19e = b43_phy_read(dev, 0x19e);

	b43_phy_set(dev, 0x19e, 0x2);

	for (core = 0; core < cores && core < B43_PHY_AC_TXCAL_MAX_CORES; core++) {
		b43_phy_ac_table_write16(dev, 7, core + 0x100, save->tbl7[core][0]);
		b43_phy_ac_table_write16(dev, 7, core + 0x103, save->tbl7[core][1]);
		b43_phy_ac_table_write16(dev, 7, core + 0x106, save->tbl7[core][2]);
		b43_phy_ac_table_write16(dev, 0xc,
					  b43_phy_ac_txcal_tbl0xc_off[core],
					  save->tbl0xc[core]);
		b43_phy_ac_table_write16(dev, 0xc,
					  b43_phy_ac_txcal_tbl0xc_off2[core],
					  save->tbl0xc[core]);
	}

	b43_phy_maskset(dev, 0x19e, ~0x2, saved19e & 0x2);
}

/*
 * decompiled-cal/FUN_00193d3a.c: a brief (~1us) forced analog settle pulse
 * on three per-core PHY registers, used right before the calibration
 * sequence starts. No chip-ID or radio-generation branching at all (unlike
 * the RF-loopback-mode switch this file's block comment mentions still
 * needing - decompiled-cal/FUN_0019454f.c / FUN_00195603.c - those depend
 * on a wl-internal struct field, phy+0x16e, whose assignment site hasn't
 * been found in anything decompiled so far, so their exact register
 * mapping for our chip isn't confidently resolved yet; this one has no
 * such dependency).
 */
static void b43_phy_ac_txcal_settle_pulse(struct b43_wldev *dev)
{
	u8 core, cores = b43_phy_ac_num_cores(dev);
	u16 saved[B43_PHY_AC_TXCAL_MAX_CORES][3];
	static const u16 base[3] = { 0x739, 0x73a, 0x725 };
	static const u16 orbits[3] = { 0x80, 0x80, 0x204 };
	int i;

	for (core = 0; core < cores && core < B43_PHY_AC_TXCAL_MAX_CORES; core++) {
		for (i = 0; i < 3; i++) {
			u16 reg = base[i] + core * 0x200;

			saved[core][i] = b43_phy_read(dev, reg);
			b43_phy_set(dev, reg, orbits[i]);
		}
	}

	udelay(1);

	if (cores > B43_PHY_AC_TXCAL_MAX_CORES)
		cores = B43_PHY_AC_TXCAL_MAX_CORES;
	for (core = cores; core-- > 0;) {
		for (i = 3; i-- > 0;) {
			u16 reg = base[i] + core * 0x200;

			b43_phy_write(dev, reg, saved[core][i]);
		}
	}

	udelay(1);
}

/*
 * decompiled-cal/FUN_0019d65d.c: load a gain-ramp curve into PHY table 0xC,
 * scaled by "percent" (0-100) - the smooth power-up curve for the
 * calibration tone itself, run once per core before its first measurement
 * pass. Static data extracted from wl.ko's own two internal ramp-curve
 * tables via tools/ghidra_dump_bytes.java (see notes/16); each pair is
 * (percent-of-full-scale, index-byte). No chip-ID or radio-generation
 * branching - like the settle pulse above, safe to write from
 * decompilation alone.
 */
struct b43_phy_ac_txcal_ramp_step {
	u8 percent;
	u8 index;
};

static const struct b43_phy_ac_txcal_ramp_step b43_phy_ac_txcal_ramp_a[18] = {
	{ 3, 0 }, { 4, 0 }, { 6, 0 }, { 9, 0 }, { 13, 0 }, { 18, 0 },
	{ 25, 0 }, { 25, 1 }, { 25, 2 }, { 25, 3 }, { 25, 4 }, { 25, 5 },
	{ 25, 6 }, { 25, 7 }, { 35, 7 }, { 50, 7 }, { 71, 7 }, { 100, 7 },
};

static const struct b43_phy_ac_txcal_ramp_step b43_phy_ac_txcal_ramp_b[18] = {
	{ 3, 0 }, { 4, 0 }, { 6, 0 }, { 9, 0 }, { 13, 0 }, { 18, 0 },
	{ 25, 0 }, { 35, 0 }, { 50, 0 }, { 71, 0 }, { 100, 0 }, { 100, 1 },
	{ 100, 2 }, { 100, 3 }, { 100, 4 }, { 100, 5 }, { 100, 6 }, { 100, 7 },
};

static void b43_phy_ac_txcal_ramp_table(struct b43_wldev *dev, u16 percent)
{
	u16 saved19e = b43_phy_read(dev, 0x19e);
	unsigned int i;

	b43_phy_set(dev, 0x19e, 0x2);

	for (i = 0; i < 18; i++) {
		u16 val_a = ((u16)b43_phy_ac_txcal_ramp_a[i].percent * percent / 100) << 8
			    | b43_phy_ac_txcal_ramp_a[i].index;
		u16 val_b = ((u16)b43_phy_ac_txcal_ramp_b[i].percent * percent / 100) << 8
			    | b43_phy_ac_txcal_ramp_b[i].index;

		b43_phy_ac_table_write16(dev, 0xc, i, val_a);
		b43_phy_ac_table_write16(dev, 0xc, i + 0x20, val_b);
	}

	b43_phy_maskset(dev, 0x19e, ~0x2, saved19e & 0x2);
}

/*
 * decompiled-cal/FUN_0019454f.c (enter) / FUN_00195603.c (exit) - switches
 * the RF front-end into its on-chip TX-calibration loopback mode. Chip-ID
 * branches resolved to their fixed BCM4360 values (this file is hardcoded
 * for our exact chip everywhere else).
 *
 * Two wl-internal conditions needed resolving, since they're software
 * state (not hardware registers) and can't just be read:
 *
 *  - phy+0x17e & 0xc000: cross-checked against ~10 other decompiled
 *    functions that test the same mask (FUN_0019a2eb.c, FUN_0019a398.c,
 *    FUN_0019b279.c, FUN_0019bc45.c, ...), all treating it as a
 *    multi-valued field with 0 and 0xc000 as the two ends - consistent
 *    with the standard Broadcom chanspec bandwidth sub-field (bits 14-15:
 *    20/40/80/some-widest-class). Our test config is always 2.4 GHz/20 MHz,
 *    so this should be 0, not 0xc000 - taking the "else" branch below.
 *    This is also the branch consistent with what was already measured
 *    live: baseline radio 0x1f reads back with bit 2 clear, matching
 *    exactly what this branch's "mod_radio_reg(0x1f,4,0)" targets.
 *  - phy+0x16e: still not resolved from any decompiled source (see
 *    notes/16). Assumed 0 (the branch reached by default/first in every
 *    if-else that tests this field throughout the whole decompiled
 *    corpus) - a genuine, documented guess, not a confirmed fact. If the
 *    read-back values captured by the test path below don't look sane,
 *    this is the first thing to reconsider.
 */
static void b43_phy_ac_txcal_read_radiosave(struct b43_wldev *dev,
					struct b43_phy_ac_txcal_radiosave *save)
{
	u8 core, cores = b43_phy_ac_num_cores(dev);

	for (core = 0; core < cores && core < B43_PHY_AC_TXCAL_MAX_CORES; core++) {
		u16 c9 = (u16)core << 9;

		save->r1a[core] = b43_radio_read(dev, 0x1a | c9);
		save->r1b[core] = b43_radio_read(dev, 0x1b | c9);
		save->r1c[core] = b43_radio_read(dev, 0x1c | c9);
		save->r1e[core] = b43_radio_read(dev, 0x1e | c9);
		save->r1f[core] = b43_radio_read(dev, 0x1f | c9);
		save->r24[core] = b43_radio_read(dev, 0x24 | c9);
		/* Assuming phy+0x16e == 0 (see block comment above): the
		 * saved/restored register here is (0x170|c9), not (c9|0x184). */
		save->r170_or_184[core] = b43_radio_read(dev, 0x170 | c9);
	}
}

static void b43_phy_ac_txcal_enter_loopback(struct b43_wldev *dev,
					struct b43_phy_ac_txcal_radiosave *save)
{
	u8 core, cores = b43_phy_ac_num_cores(dev);

	b43_phy_ac_txcal_read_radiosave(dev, save);

	for (core = 0; core < cores && core < B43_PHY_AC_TXCAL_MAX_CORES; core++) {
		u16 c9 = (u16)core << 9;

		/* "else" (non-0xc000-bandwidth) branch of FUN_0019454f.c. */
		b43_radio_maskset(dev, 0x1a | c9, ~0xf0, 0x80);
		b43_radio_maskset(dev, 0x1f | c9, ~4, 0);
		b43_radio_maskset(dev, 0x170 | c9, ~0x100, 0);
		b43_radio_maskset(dev, 0x170 | c9, ~0x4000, 0x4000);
		b43_radio_maskset(dev, 0x1e | c9, ~4, 4);
		b43_radio_maskset(dev, 0x1a | c9, ~0x300, 0);
		/* phy+0x16e == '\x01' branch skipped: assumed 0, not 1. */
	}
}

static void b43_phy_ac_txcal_exit_loopback(struct b43_wldev *dev,
				const struct b43_phy_ac_txcal_radiosave *save)
{
	u8 core, cores = b43_phy_ac_num_cores(dev);

	for (core = 0; core < cores && core < B43_PHY_AC_TXCAL_MAX_CORES; core++) {
		u16 c9 = (u16)core << 9;

		b43_radio_write(dev, 0x1a | c9, save->r1a[core]);
		b43_radio_write(dev, 0x1b | c9, save->r1b[core]);
		b43_radio_write(dev, 0x1c | c9, save->r1c[core]);
		b43_radio_write(dev, 0x1e | c9, save->r1e[core]);
		b43_radio_write(dev, 0x1f | c9, save->r1f[core]);
		b43_radio_write(dev, 0x24 | c9, save->r24[core]);
		b43_radio_write(dev, 0x170 | c9, save->r170_or_184[core]);
	}
}

/*
 * decompiled-cal/wlc_phy_cordic.c: an 18-iteration fixed-point CORDIC
 * rotation, verified bit-exact by hand: full circle is 0x1680000 units
 * (so 65536 units = 1 degree exactly), the 0x9b75 constant is the
 * standard CORDIC gain, and the >90-degree quadrant-extension check
 * (0x5b = 91 degrees) plus its final +-1 scale are textbook. Pure
 * integer math, touches no hardware - zero risk regardless of what
 * calls it. angle is in 1/65536-degree units; out[0]/out[1] come back
 * proportional to sin/cos scaled by the 0x9b75 CORDIC gain.
 */
static void b43_phy_ac_txcal_cordic(s32 angle, s32 out[2])
{
	static const s32 arctan_tbl[18] = {
		2949120, 1741991, 919879, 466945, 234891, 117304, 58666, 29335,
		14668, 7334, 3667, 1833, 917, 458, 229, 115, 57, 29,
	};
	s32 sign = (angle < 0) ? -1 : 1;
	s32 target = (sign * 0xb40000 + angle) % 0x1680000 - sign * 0xb40000;
	s32 rounded, final_scale;
	s32 x = 0, y = 0x9b75;
	s32 acc = 0;
	int i;

	rounded = (target < 0) ? -((((-target) >> 15) + 1) >> 1)
				: (((target) >> 15) + 1) >> 1;

	if (rounded < 0x5b) {
		if (target >= 0 ||
		    -0x5b < -((((-target) >> 15) + 1) >> 1)) {
			final_scale = 1;
			goto rotate;
		}
		target += 0xb40000;
	} else {
		target -= 0xb40000;
	}
	final_scale = -1;

rotate:
	for (i = 0; i < 18; i++) {
		s32 old_x = x, old_y = y, step;

		if (acc < target) {
			step = arctan_tbl[i];
			x = (old_y >> i) + old_x;
			y = old_y - (old_x >> i);
		} else {
			step = -arctan_tbl[i];
			x = old_x - (old_y >> i);
			y = (old_x >> i) + old_y;
		}
		acc += step;
	}

	out[0] = final_scale * x;
	out[1] = final_scale * y;
}

static s32 b43_phy_ac_txcal_round15(s32 v)
{
	return (v < 0) ? -((((-v) >> 15) + 1) >> 1) : (((v) >> 15) + 1) >> 1;
}

/*
 * decompiled/wlc_phy_tx_tone_acphy.c, specialised for the exact call
 * wl itself makes for our band from decompiled-cal/FUN_001ac9b6.c line
 * 682 (2.4 GHz: freq=1000, amplitude=0xfa, param_4=1, param_5=0,
 * param_6=0) - not a general port of all 6 parameters, just this one
 * call pattern, matching this project's "port exactly what's needed"
 * convention. Builds a 40-sample tone waveform via CORDIC, writes it
 * into PHY table 0xe (32-bit wide), then drives the real playback
 * trigger sequence (registers 0x460-0x463/0x382/0x400/0x471), polling
 * 0x403 bit0 with the same ~1ms bound wl itself uses.
 *
 * DELIBERATELY simplified vs. wl: the real algorithm's cleanup here is
 * wlc_phy_stopplayback_acphy() -> wlc_phy_resetcca_acphy(), and the
 * latter branches on the still-unresolved phy+0x164 field (see
 * notes/16). Rather than guess that field on a live-TX code path, this
 * saves all 7 PHY registers it touches (0x460/0x461/0x462/0x463/0x471/
 * 0x382/0x400) before doing anything and writes them back verbatim
 * afterward - a strictly safer, if less "authentic", cleanup that does
 * not depend on that unknown at all. This means the chip may not end
 * up in exactly wl's normal post-tone operating state, only back in
 * whatever state it was in immediately before this function ran.
 *
 * Split into _start()/_stop(): wl's own algorithm leaves the tone
 * *running* after this trigger sequence and only tears it down, much
 * later, after its whole measurement sweep (wlc_phy_stopplayback_acphy).
 * The original combined b43_phy_ac_txcal_gen_tone() (kept below,
 * unchanged, for ac_txcal_tone_test) restores all 7 registers
 * immediately, which likely stops the tone again almost instantly -
 * fine for testing that the register sequence itself is safe, but not
 * representative of a sustained, measurable tone. _start()/_stop() let
 * a caller do something in between while the tone is actually playing.
 */
static void b43_phy_ac_txcal_gen_tone_start(struct b43_wldev *dev,
					struct b43_phy_ac_txcal_tonesave *save)
{
	static const int nsamples = 40;	/* 2.4 GHz: iVar16=0x14, *2 */
	static const int freq = 1000;		/* wl's 2.4 GHz tone param */
	static const int amplitude = 0xfa;
	u32 wave[40];
	s32 phase_step;
	s32 phase = 0;
	int i;
	unsigned int timeout;
	struct b43_phy_ac_tbl tbl = {
		.data = wave, .count = nsamples, .id = 0xe, .offset = 0,
		.width = 32,
	};

	/* (freq * 0x24) / nsamples << 0x10) / 100, exactly as decompiled. */
	phase_step = ((freq * 0x24) / nsamples << 0x10) / 100;

	for (i = 0; i < nsamples; i++) {
		s32 xy[2];

		b43_phy_ac_txcal_cordic(phase, xy);
		xy[0] = b43_phy_ac_txcal_round15(amplitude * xy[0]);
		xy[1] = b43_phy_ac_txcal_round15(amplitude * xy[1]);
		wave[i] = ((u32)(xy[1] & 0x3ff) << 10) | ((u32)xy[0] & 0x3ff);
		phase += phase_step;
	}

	save->r460 = b43_phy_read(dev, 0x460);
	save->r461 = b43_phy_read(dev, 0x461);
	save->r462 = b43_phy_read(dev, 0x462);
	save->r463 = b43_phy_read(dev, 0x463);
	save->r471 = b43_phy_read(dev, 0x471);
	save->r382 = b43_phy_read(dev, 0x382);
	save->r400 = b43_phy_read(dev, 0x400);

	b43_phy_ac_write_table(dev, &tbl);

	b43_phy_mask(dev, 0x471, ~1);
	b43_phy_write(dev, 0x463, nsamples - 1);
	b43_phy_write(dev, 0x461, 0xffff);
	b43_phy_write(dev, 0x462, 0x3c);
	b43_phy_set(dev, 0x400, 1);
	b43_phy_mask(dev, 0x460, ~4);
	b43_phy_mask(dev, 0x460, ~1);
	b43_phy_mask(dev, 0x382, 0x3fff);
	b43_phy_set(dev, 0x382, 0x8000);

	for (timeout = 0x3f1; timeout != 9; timeout -= 10) {
		if (!(b43_phy_read(dev, 0x403) & 1))
			break;
		udelay(10);
	}

	b43_phy_write(dev, 0x400, save->r400);
}

static void b43_phy_ac_txcal_gen_tone_stop(struct b43_wldev *dev,
				const struct b43_phy_ac_txcal_tonesave *save)
{
	b43_phy_write(dev, 0x460, save->r460);
	b43_phy_write(dev, 0x461, save->r461);
	b43_phy_write(dev, 0x462, save->r462);
	b43_phy_write(dev, 0x463, save->r463);
	b43_phy_write(dev, 0x471, save->r471);
	b43_phy_write(dev, 0x382, save->r382);
}

static void b43_phy_ac_txcal_gen_tone(struct b43_wldev *dev)
{
	struct b43_phy_ac_txcal_tonesave save;

	b43_phy_ac_txcal_gen_tone_start(dev, &save);
	b43_phy_ac_txcal_gen_tone_stop(dev, &save);
}

/*
 * decompiled-cal/FUN_001ac9b6.c's inner per-candidate measurement loop
 * (lines ~701-746), specialised to a single outer sample rather than
 * wl's full loop (whose bounds depend on a persistent, never-ported
 * "generation counter" in the calibration state struct - see notes/16).
 *
 * Derivation for our exact board (2.4 GHz, phy+0x16e==0, phy+0x164==1,
 * confirmed hardware values, not guesses - see notes/16):
 *   - local_168 = 0 (band 0x17e&0x3800 is neither 0x2000 nor 0x1800)
 *     -> register 0x381 = CONCAT11(local_58[0]=0x79, local_48[0]=0x76)
 *        = 0x7976 (our else-branch constants from lines 156-169).
 *   - phy+0x164==1 with param_4==0 (our call pattern, matching wl's
 *     real phases 2-12) resolves local_150 to local_e8 =
 *     {0x423,0x334,0x73,0x267,0x45,0x234} - using only the first entry
 *     (0x423) here, i.e. outer sample 0, core 0 (uVar28=0).
 *   - The inner 899-candidate sweep, phy+0x16e==0 branch: the 6 bytes
 *     {local_a8,local_a7,...,local_a3} = {0x3d,0x1e,0xf,7,3,1}.
 *
 * Deliberately does NOT stop at the first candidate where radio 0x144
 * bit 2 clears (what wl itself does - that's its "found a correction"
 * exit). Sweeps and logs all 6 unconditionally: the point of this test
 * is to see how the measurement register responds at all, not to find
 * or apply a real correction - nothing here writes to the loft-comp
 * table. Skips most of the FUN_0019ccd9 bookkeeping calls wl makes in
 * this loop (they only matter for collecting/committing a result) -
 * EXCEPT two that turn out to be real, not bookkeeping: for our exact
 * case (bVar23 = (trigger>>8)&0xf = 4), wl's per-sample setup runs
 * `FUN_0019ccd9(pi,1,&zero,1,core)` and `FUN_0019ccd9(pi,1,&zero,2,
 * core)` right before the candidate sweep - decoded via
 * decompiled-cal/FUN_0019ccd9.c's dispatch table (extracted from
 * DAT_00558d60, see notes/16): index 1 -> table 0xc offset
 * `core*8+0x43`, index 2 -> `core*8+0x44`, both writing 0. Initially
 * mis-classified as pure bookkeeping and skipped - they're real table
 * writes that could plausibly be exactly the missing precondition for
 * a differentiated reading (a stale, never-cleared value there could
 * make the comparator return "pass" unconditionally, matching the
 * uniform result seen so far).
 */
static void b43_phy_ac_txcal_measure_candidates_outer(struct b43_wldev *dev,
						       u16 outer)
{
	static const u8 inner[6] = { 0x3d, 0x1e, 0x0f, 0x07, 0x03, 0x01 };
	u16 trigger = outer | 0x8000;
	int i;

	b43_phy_ac_table_write16(dev, 0xc, 0x43, 0);
	b43_phy_ac_table_write16(dev, 0xc, 0x44, 0);
	b43_phy_write(dev, 0x381, 0x7976);

	for (i = 0; i < 6; i++) {
		unsigned int timeout;
		u16 v144;

		b43_phy_write(dev, 899, inner[i]);
		b43_phy_write(dev, 0x380, trigger);

		{
		int iters = 0;
		for (timeout = 0x4e29; timeout != 9; timeout -= 10) {
			iters++;
			if (!(b43_phy_read(dev, 0x380) & 0xc000))
				break;
			udelay(10);
		}

		v144 = b43_radio_read(dev, 0x144);
		b43info(dev->wl, "phy_ac: txcal candidate test: outer=%04x 899=%02x -> 380=%04x radio144=%04x bit2=%d iters=%d\n",
			outer, inner[i], b43_phy_read(dev, 0x380), v144,
			(v144 & 4) != 0, iters);
		}

		b43_phy_set(dev, 0x73a, 0x100);
		b43_phy_mask(dev, 0x73a, ~0x100);
	}
}

/*
 * CORRECTED against a real wl trace (traces/wl-init-20260927-184726.trace,
 * captured live during a real association - see notes/20): wl's actual
 * first outer-sample write to reg 0x380 was 0x8434 (outer=0x434), not
 * 0x423. That's `local_d8` (param_2=='\0' branch, phy+0x164==1), not
 * `local_e8` (param_2!='\0') as this project originally guessed - i.e.
 * wl's real call here has `local_51` (param_2) == 0, not 1. Every other
 * observed value (0x381=0x7976, the 0x43/0x44 table-0xC clears, the
 * candidate byte 0x3d, the 0x461/0x462/0x463 tone-trigger values)
 * matched this project's port exactly, byte for byte - only this one
 * table selection was wrong.
 */
static void b43_phy_ac_txcal_measure_candidates(struct b43_wldev *dev)
{
	b43_phy_ac_txcal_measure_candidates_outer(dev, 0x434);
}

/*
 * Sweeps ALL 6 entries of local_d8 (see the corrected derivation in
 * b43_phy_ac_txcal_measure_candidates's comment just above), not just
 * entry 0, to check whether the flat bit-2-clear result seen so far is
 * specific to outer sample 0's parameters or holds across the whole
 * real table. If even one entry shows bit 2 ever set, the measurement
 * mechanism is working and outer sample 0 was simply always a "pass";
 * if all 6 are flat too, that is much stronger evidence something is
 * genuinely wrong rather than this test just probing the wrong range.
 */
static void b43_phy_ac_txcal_measure_candidates_sweep(struct b43_wldev *dev)
{
	static const u16 local_d8[6] = { 0x434, 0x334, 0x84, 0x267, 0x56, 0x234 };
	int i;

	for (i = 0; i < 6; i++)
		b43_phy_ac_txcal_measure_candidates_outer(dev, local_d8[i]);
}

/*
 * decompiled-cal/FUN_001ac9b6.c lines ~179-599: the per-core measurement
 * setup block, run once before the tone/candidate-search loop. Fully
 * resolved for our exact hardware (2 cores, phy+0x164==1, 2.4GHz band -
 * all confirmed hardware facts, not guesses, see notes/16): the
 * apparent 3-way "0x73e/0xb3e/0x93e"-style register-family selection
 * used throughout the vendor source turns out to be exactly `base +
 * core*0x200` addressing (verified against multiple register bases) -
 * no lookup table needed for a 2-core board. Every phy+0x164 branch is
 * resolved (1, matching none of {2,3,5,6}) and the band-dependent
 * constant (uVar28=0xd5eb for 2.4GHz) is fixed. Skips the not-yet-
 * decompiled wlc_phy_classifier_acphy(pi,7,4) call - PHY-register
 * based, not BCMA_IOCTL, a deliberate simplification in the same spirit
 * as skipping FUN_0019ccd9's bookkeeping elsewhere in this file.
 *
 * DELIBERATELY does not use vendor's real cleanup:
 * b43_phy_ac_txcal_measure_setup_exit() is a straight write-back of
 * every register this saves (same registers, same order as vendor's
 * own FUN_001982a2), but skips its trailing wlc_phy_resetcca_acphy()
 * call - that function unconditionally calls wlapi_bmac_phyclk_fgc()
 * -> si_core_cflags(), a BCMA_IOCTL control-flags write on the live D11
 * core. That is the same register category behind this project's one
 * hard machine freeze (notes/07, 2026-09-26). Not touched here, solo,
 * on purpose.
 */
static void b43_phy_ac_txcal_measure_setup_enter(struct b43_wldev *dev,
				struct b43_phy_ac_txcal_setupsave *save)
{
	static const u16 band_const = 0xd5eb; /* 2.4 GHz (uVar28) */
	u8 core, cores = b43_phy_ac_num_cores(dev);

	save->r19e = b43_phy_read(dev, 0x19e);
	save->r40f = b43_phy_read(dev, 0x40f);
	b43_phy_set(dev, 0x19e, 0x2);
	b43_phy_mask(dev, 0x40f, ~0x200);

	for (core = 0; core < cores && core < B43_PHY_AC_TXCAL_MAX_CORES; core++) {
		u16 c = core * 0x200;

		save->t73e[core] = b43_phy_read(dev, 0x73e + c);
		b43_phy_write(dev, 0x73e + c, 0);
		b43_phy_mask(dev, 0x73e + c, ~0x10);
		b43_phy_mask(dev, 0x73e + c, ~0x20);
		b43_phy_mask(dev, 0x73e + c, ~0x40);
		b43_phy_mask(dev, 0x73e + c, ~0x80);
		b43_phy_set(dev, 0x73e + c, 0x1000);
		b43_phy_set(dev, 0x73e + c, 0x400);

		save->t725[core] = b43_phy_read(dev, 0x725 + c);
		save->t739[core] = b43_phy_read(dev, 0x739 + c);
		save->t73a[core] = b43_phy_read(dev, 0x73a + c);
		save->t721[core] = b43_phy_read(dev, 0x721 + c);
		save->t729[core] = b43_phy_read(dev, 0x729 + c);
		save->t720[core] = b43_phy_read(dev, 0x720 + c);
		save->t728[core] = b43_phy_read(dev, 0x728 + c);
		save->t724[core] = b43_phy_read(dev, 0x724 + c);
		save->t736[core] = b43_phy_read(dev, 0x736 + c);
		save->t723[core] = b43_phy_read(dev, 0x723 + c);
		save->t735[core] = b43_phy_read(dev, 0x735 + c);
		save->t737[core] = b43_phy_read(dev, 0x737 + c);
		save->t738[core] = b43_phy_read(dev, 0x738 + c);
		save->t727[core] = b43_phy_read(dev, 0x727 + c);
		save->t73c[core] = b43_phy_read(dev, 0x73c + c);

		b43_phy_set(dev, 0x720 + c, 2);
		b43_phy_mask(dev, 0x728 + c, ~2);
		b43_phy_set(dev, 0x721 + c, 0x40);
		b43_phy_mask(dev, 0x729 + c, ~0x40);
		b43_phy_set(dev, 0x721 + c, 0x80);
		b43_phy_mask(dev, 0x729 + c, ~0x80);
		b43_phy_set(dev, 0x721 + c, 0x20);
		b43_phy_mask(dev, 0x729 + c, ~0x20);
		b43_phy_set(dev, 0x721 + c, 0x2000);
		b43_phy_mask(dev, 0x729 + c, (u16)~0xe000);
		b43_phy_set(dev, 0x721 + c, 0x800);
		b43_phy_mask(dev, 0x729 + c, ~0x800);
		b43_phy_set(dev, 0x721 + c, 0x400);
		b43_phy_mask(dev, 0x729 + c, ~0x400);
		b43_phy_set(dev, 0x721 + c, 0x4000);
		b43_phy_mask(dev, 0x728 + c, ~0x3800);
		b43_phy_set(dev, 0x721 + c, 0x1000);
		b43_phy_mask(dev, 0x729 + c, ~0x1000);
		b43_phy_set(dev, 0x720 + c, 0x20);
		b43_phy_set(dev, 0x728 + c, 0x20);
		b43_phy_set(dev, 0x720 + c, 0x40);
		b43_phy_set(dev, 0x728 + c, 0x40);
		b43_phy_set(dev, 0x720 + c, 0x10);
		b43_phy_set(dev, 0x728 + c, 0x10);
		b43_phy_set(dev, 0x721 + c, 0x100);
		b43_phy_set(dev, 0x729 + c, 0x100);
		b43_phy_set(dev, 0x727 + c, 4);
		b43_phy_set(dev, 0x73c + c, 0x10);

		b43_phy_write(dev, 0x724 + c, 0x3ff);
		b43_phy_write(dev, 0x736 + c, 0x152); /* param_4==0 for our call */

		b43_phy_maskset(dev, 0x73a + c, ~7, band_const & 7);
		b43_phy_set(dev, 0x725 + c, 0x20);
		b43_phy_maskset(dev, 0x739 + c, ~0x7e, (band_const >> 2) & 0x7e);
		b43_phy_set(dev, 0x725 + c, 2);
		b43_phy_maskset(dev, 0x73a + c, ~8, (band_const >> 6) & 8);
		b43_phy_set(dev, 0x725 + c, 0x40);
		b43_phy_maskset(dev, 0x73a + c, ~0x10, (band_const >> 6) & 0x10);
		b43_phy_set(dev, 0x725 + c, 0x80);
		b43_phy_maskset(dev, 0x73a + c, ~0x60, (band_const >> 6) & 0x60);
		b43_phy_set(dev, 0x725 + c, 0x100);

		b43_phy_set(dev, 0x723 + c, 8);
		b43_phy_set(dev, 0x723 + c, 0x10);
		b43_phy_set(dev, 0x723 + c, 0x800);

		/* iVar12 = band-index(0) + 3 = 3; phy+0x164==1 -> else branch */
		b43_phy_maskset(dev, 0x735 + c, ~0x700, 3 * 0x100);
		b43_phy_maskset(dev, 0x735 + c, ~0x3800, 3 * 0x800);
		b43_phy_maskset(dev, 0x738 + c, ~7, 3);

		b43_phy_set(dev, 0x723 + c, 1);
		b43_phy_mask(dev, 0x735 + c, ~1);
		b43_phy_set(dev, 0x723 + c, 0x20);
		b43_phy_mask(dev, 0x735 + c, ~0x4000);
		b43_phy_set(dev, 0x723 + c, 2);
		b43_phy_maskset(dev, 0x735 + c, ~0x1e, 8);

		/* phy+0x164 != 3 (true for us) */
		b43_phy_set(dev, 0x727 + c, 2);
		b43_phy_maskset(dev, 0x73c + c, ~0xe, 4);
		b43_phy_set(dev, 0x727 + c, 1);
		b43_phy_set(dev, 0x73c + c, 1);
	}
}

static void b43_phy_ac_txcal_measure_setup_exit(struct b43_wldev *dev,
			const struct b43_phy_ac_txcal_setupsave *save)
{
	u8 core, cores = b43_phy_ac_num_cores(dev);

	for (core = 0; core < cores && core < B43_PHY_AC_TXCAL_MAX_CORES; core++) {
		u16 c = core * 0x200;

		b43_phy_write(dev, 0x73e + c, save->t73e[core]);
		b43_phy_write(dev, 0x721 + c, save->t721[core]);
		b43_phy_write(dev, 0x729 + c, save->t729[core]);
		b43_phy_write(dev, 0x720 + c, save->t720[core]);
		b43_phy_write(dev, 0x728 + c, save->t728[core]);
		b43_phy_write(dev, 0x724 + c, save->t724[core]);
		b43_phy_write(dev, 0x736 + c, save->t736[core]);
		b43_phy_write(dev, 0x723 + c, save->t723[core]);
		b43_phy_write(dev, 0x735 + c, save->t735[core]);
		b43_phy_write(dev, 0x737 + c, save->t737[core]);
		b43_phy_write(dev, 0x738 + c, save->t738[core]);
		b43_phy_write(dev, 0x727 + c, save->t727[core]);
		b43_phy_write(dev, 0x73c + c, save->t73c[core]);
		b43_phy_write(dev, 0x725 + c, save->t725[core]);
		b43_phy_write(dev, 0x739 + c, save->t739[core]);
		b43_phy_write(dev, 0x73a + c, save->t73a[core]);
	}

	b43_phy_write(dev, 0x19e, save->r19e);
	b43_phy_write(dev, 0x40f, save->r40f);
	/* wl's real cleanup here is wlc_phy_resetcca_acphy() - see
	 * b43_phy_ac_txcal_resetcca() below, kept as a separate function
	 * (not called from here) so it can be tested in isolation first,
	 * per this project's established practice for every new risky
	 * piece. Not called automatically by this function.
	 */
}

/*
 * decompiled-cal/wlc_phy_resetcca_acphy.c + decompiled-si/wlc_bmac_phyclk_fgc.c:
 * wl's real cleanup after the measurement setup block, previously
 * avoided (see this file's git history / notes/16) because it writes
 * BCMA_IOCTL - the same *register* behind this project's one hard
 * machine freeze (notes/07, 2026-09-26: BCMA_IOCTL PHY-bandwidth bits
 * changed on an associated, actively-transmitting core).
 *
 * Investigated further at the user's explicit direction ("Fix the gap.
 * Even if I'm not here.") rather than either blindly implementing it or
 * refusing outright. Found this is a materially different operation,
 * not just the same register:
 * - wlapi_bmac_phyclk_fgc's si_core_cflags(sih,2,val) is BCMA_IOCTL_FGC
 *   (0x0002, "Force Gate Clock") - a GENERIC bcma-bus core-control bit
 *   defined in the mainline Linux kernel's own
 *   include/linux/bcma/bcma_regs.h, used across the whole bcma
 *   subsystem for many chips. Not a PHY-specific or exotic bit.
 * - It's a narrow, paired set-then-clear around a ~1us PHY-register
 *   toggle (force clock on, flip PHY reg 1 bit 0x4000, flip it back,
 *   force clock off) - structurally nothing like a persistent
 *   bandwidth-mode change on a running, transmitting core.
 * - We are never associated and never mid-TX when this runs (monitor
 *   mode only, called from the calibration test path).
 *
 * phy+0x164==1 for our board (confirmed, see notes/16) takes
 * wlc_phy_resetcca_acphy's simpler branch (no extra PHY 0x19e mods) -
 * implemented directly, no guessing. wlc_bmac_phyclk_fgc's own D11-
 * core-type guard is skipped: we only ever call this from PHY-specific
 * code operating on our own core, so it always applies here.
 */
static void b43_phy_ac_txcal_resetcca(struct b43_wldev *dev)
{
	u32 ioctl;
	u16 saved1;

	if (dev->dev->bus_type != B43_BUS_BCMA)
		return;

	ioctl = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
	bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl | BCMA_IOCTL_FGC);

	saved1 = b43_phy_read(dev, 1);
	b43_phy_write(dev, 1, saved1 | 0x4000);
	udelay(1);
	b43_phy_write(dev, 1, saved1 & 0xbfff);

	bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, ioctl);
	udelay(2);
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
		/* Only shared memory; routing 4 is wl's address match table. */
		if (b43_ac_replay_shm[i].routing != B43_SHM_SHARED)
			continue;
		if (b43_ac_replay_shm[i].bits == 32)
			b43_shm_write32(dev, b43_ac_replay_shm[i].routing,
					b43_ac_replay_shm[i].off,
					b43_ac_replay_shm[i].val);
		else
			b43_shm_write16(dev, b43_ac_replay_shm[i].routing,
					b43_ac_replay_shm[i].off,
					b43_ac_replay_shm[i].val);
	}
	b43dbg(dev->wl, "phy_ac: replayed vendor ch6 state (%zu radio, %zu PHY regs, %zu table entries)\n",
		ARRAY_SIZE(b43_ac_replay_radio), ARRAY_SIZE(b43_ac_replay_phy),
		ARRAY_SIZE(b43_ac_replay_tbl));
}

/* SHM 0x7C (ucode word 0x3E): TX lifetime in 256us units. While a frame
 * waits in the main loop (deferral/backoff/retry) the ucode arms a deadline
 * of now + this value and completes the frame with supp_reason=5 (LIFE)
 * once it passes; 0 expires it on the arming pass. wl writes 0x0320. */
static int b43_ac_txlifetime = -1;
module_param_named(ac_txlifetime, b43_ac_txlifetime, int, 0644);
MODULE_PARM_DESC(ac_txlifetime, "AC-PHY: TX lifetime written to SHM 0x7C in 256us units (-1: leave unset)");

static int b43_phy_ac_op_init(struct b43_wldev *dev)
{
	if (b43_ac_txlifetime >= 0 && b43_ac_txlifetime <= 0xffff) {
		b43_shm_write16(dev, B43_SHM_SHARED, 0x7c, b43_ac_txlifetime);
		b43info(dev->wl, "phy_ac: TX lifetime (SHM 0x7C) = 0x%04x\n",
			b43_ac_txlifetime);
	}
	if (dev->phy.rev <= 1) {
		b43_phy_ac_tables_init(dev);
		b43_phy_ac_first_init(dev);
		/* wl's captured state, once; the channel switch that follows
		 * init tunes the radio for the requested channel. */
		if (b43_ac_init_state && b43_ac_replay)
			b43_phy_ac_replay_ch6(dev);
		if (b43_ac_init_state && b43_ac_por)
			b43_phy_ac_apply_por(dev);
	}
	else
		b43err(dev->wl, "phy_ac: no table set for PHY rev %u\n",
		       dev->phy.rev);

	b43info(dev->wl, "phy_ac: init (core_rev %u, radio24=%d, chip %04x, board %04x, radio_on %d)\n",
		dev->dev->core_rev, b43_phy_ac_use_radio24(dev),
		dev->dev->chip_id, dev->dev->board_type, dev->phy.ac->radio_on);

	/* See notes/62: this port never writes HOSTF2/HOSTF3 (SHM 0x60/0x62)
	 * at all. The ucode's own idle-loop predicate (ucode42.fw 0x000C/
	 * 0x000D) reads those two words directly and skips NAP if EITHER is
	 * nonzero - wl's real trace sets both to a nonzero, specific value
	 * right around association; this port leaves them zero, so nothing
	 * stops the ucode from freely NAPping whenever its other (SCR-based)
	 * flags happen to be momentarily clear. Value below is wl's real
	 * captured HOSTF2/HOSTF3 (traces/wl-init-20260927-184726.trace,
	 * bits 16-47: SKCFPUP|N40W|ANTSELEN|MLADVW|PR45960W plus several
	 * bits b43.h has no name for - written as a raw OR, not decoded
	 * bit-by-bit). Test flag, default off. */
	if (b43_ac_hostflags)
		b43_hf_write(dev, b43_hf_read(dev) | 0xb0518c050000ULL);

	/* See notes/64: HOSTF1 (SHM 0x5E, word 0x2F) gates something deeper
	 * still. ucode42.fw 0x0407, right before the code that (eventually)
	 * sets SCR 0x2C - one of the two ucode-internal flags the idle loop
	 * also checks alongside HOSTF2/3 - does `JZX ShmDir(0x2F), 0x414`:
	 * if HOSTF1 == 0, the entire per-FIFO TX-status dispatch block is
	 * skipped outright. This port never writes HOSTF1 either, so it's
	 * always 0. Unlike HOSTF2/3, no live wl value was safely capturable
	 * (it's set once at attach, before any ifdown/ifup trace window, and
	 * capturing that moment needs a reload-while-tracing test that has
	 * crashed this machine before - not repeated solo). Value below is
	 * not wl's real bytes; it's a reasoned pick from b43.h's own named
	 * HOSTF1 bits that plausibly apply here: B43_HF_EDCF ("on if WME and
	 * MAC suspended" - literally this port's whole story) and
	 * B43_HF_ACIW ("shift bits by 2 on PHY CRS" - notes/58's CRS|TXF
	 * finding). Separate flag from ac_hostflags since it's a guess, not
	 * a captured value; default off. */
	if (b43_ac_hostf1)
		b43_hf_write(dev, b43_hf_read(dev) | B43_HF_EDCF | B43_HF_ACIW);

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
/* wl runs a real periodic watchdog (wlc_bmac_watchdog/wlc_phy_watchdog)
 * that this port has never had an equivalent for (see notes/27-31/34): a
 * ~1.024s cycle doing DMA-error recovery and PHY/ACI recalibration. Its
 * absence is the leading suspect for this port's intermittent RX/ACK
 * reliability (notes/25/26's abnormal-gap baseline, notes/34's bpftrace
 * evidence of a live connection's keepalive probes going repeatedly
 * unacked). Fully porting it is blocked on resolving two still-unidentified
 * indirect (vtable) function-pointer calls in the proprietary driver
 * (notes/34's addendum) - real, open-ended reverse-engineering, not
 * something to guess at on a live radio.
 *
 * This is a pragmatic stand-in, not a fix for the underlying cause: watch
 * the ucode's own TX-vs-ACKed frame counters (the same SHM_SH_TXALLFRM/
 * TXACKFRM this project's diagnostics have used all along) once actually
 * associated to a BSS, and if the ACK ratio stays bad for several
 * consecutive 15s windows, recover the same way b43 already recovers from
 * a firmware watchdog timeout or a fatal DMA error: b43_controller_restart().
 * That's an existing, already-proven-safe mechanism (full core re-init,
 * used elsewhere in this file for exactly this class of "something is
 * wrong, recover" situation) - this only adds a new, read-only-until-the-
 * threshold-trips trigger for it, not a new recovery mechanism.
 *
 * Off by default: TXACKFRM counts ACKs we *send* (it equals the unicast
 * frames we received), not ACKs received for our frames, so this ratio says
 * nothing about TX health; and its restart path is the leading suspect for
 * a hard freeze (notes/48, notes/50). Needs a real metric before reuse.
 */
static uint b43_ac_ackwatchdog;
module_param_named(ac_ackwatchdog, b43_ac_ackwatchdog, uint, 0644);
MODULE_PARM_DESC(ac_ackwatchdog,
		 "AC-PHY: recover via a core restart if the ACK ratio stays "
		 "degraded for several consecutive 15s windows (0 to disable)");

/* Minimum frames sent in a window before its ACK ratio means anything -
 * an idle or lightly-loaded link shouldn't trip this on a small sample. */
#define B43_AC_ACKWD_MIN_FRAMES	20
/* Trigger when fewer than 1/this fraction of frames got ACKed. */
#define B43_AC_ACKWD_BAD_RATIO	2
/* Consecutive bad windows required before actually restarting (~45s). */
#define B43_AC_ACKWD_BAD_WINDOWS	3

/* Returns true if it restarted the controller, in which case the caller
 * must not touch any more registers (same discipline as the existing
 * firmware-watchdog and fatal-DMA-error restart call sites in main.c,
 * which both return immediately after calling b43_controller_restart()). */
static bool b43_phy_ac_check_ack_watchdog(struct b43_wldev *dev)
{
	struct b43_phy_ac *ac = dev->phy.ac;
	u16 txallfrm, txackfrm, d_all, d_ack;

	if (!b43_ac_ackwatchdog)
		return false;
	/* Only meaningful once actually associated: scanning/monitor mode
	 * naturally has a low ACK ratio (broadcast probes aren't ACKed). */
	if (is_zero_ether_addr(dev->wl->bssid))
		return false;

	txallfrm = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_TXALLFRM);
	txackfrm = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_TXACKFRM);

	if (!ac->ack_ratio_valid) {
		ac->last_txallfrm = txallfrm;
		ac->last_txackfrm = txackfrm;
		ac->ack_ratio_valid = true;
		ac->ack_ratio_bad_windows = 0;
		return false;
	}

	/* u16 wraparound is fine here: unsigned subtraction still gives the
	 * right delta as long as at most one wrap happened since last read,
	 * which a 16-bit ucode counter over a 15s window will not exceed. */
	d_all = txallfrm - ac->last_txallfrm;
	d_ack = txackfrm - ac->last_txackfrm;
	ac->last_txallfrm = txallfrm;
	ac->last_txackfrm = txackfrm;

	if (d_all < B43_AC_ACKWD_MIN_FRAMES) {
		/* Not enough traffic this window to say anything - inconclusive,
		 * not "fine". Leave ack_ratio_bad_windows as-is: sparse/bursty
		 * traffic (real application traffic, or the effect of notes/41's
		 * early-suppression bug itself reducing per-frame attempt counts)
		 * would otherwise reset the streak every time a quiet window
		 * happened to fall between two genuinely bad ones, making this
		 * watchdog far less likely to ever trigger during exactly the
		 * kind of bursty-traffic degradation it exists to catch. */
		return false;
	}

	if (d_ack * B43_AC_ACKWD_BAD_RATIO < d_all) {
		ac->ack_ratio_bad_windows++;
		b43warn(dev->wl,
			"phy_ac: ACK ratio degraded (%u/%u acked this window, "
			"%u/%u consecutive bad)\n",
			d_ack, d_all, ac->ack_ratio_bad_windows,
			B43_AC_ACKWD_BAD_WINDOWS);
		if (ac->ack_ratio_bad_windows >= B43_AC_ACKWD_BAD_WINDOWS) {
			b43err(dev->wl,
			       "phy_ac: ACK ratio degraded for %u consecutive "
			       "windows, restarting the controller\n",
			       ac->ack_ratio_bad_windows);
			/* Re-baseline once the restart brings the core back
			 * up, rather than judging the first post-restart
			 * window against pre-restart counters. */
			ac->ack_ratio_valid = false;
			/* Not b43_controller_restart(): that quietly reinits
			 * the hardware without telling mac80211, which leaves
			 * this recurring trigger's connections stuck
			 * association-stale (observed live: no re-DHCP, no
			 * re-handshake, just a silently reset radio). This
			 * needs the full ieee80211_restart_hw()-driven path. */
			b43_controller_restart_full(dev, "AC-PHY ACK ratio degraded");
			return true;
		}
	} else {
		ac->ack_ratio_bad_windows = 0;
	}
	return false;
}

/*
 * Self-healing for the per-init coin flip (notes/105, 119): only ~30 % of
 * fresh inits can transmit; in the others every TX ends in a PHY TX error.
 * With ac_selfheal=N the 15 s work polls the ucode's txphyerr counter (SHM
 * 0xFE) and restarts the core through mac80211 (fresh init, fresh coin flip)
 * after >= 3 errors in a window, at most N times; the budget refills after
 * 10 quiet minutes. Polled, not IRQ-driven: unmasking B43_IRQ_PHY_TXERR hung
 * the machine twice (notes/119).
 */
static uint b43_ac_selfheal = 3;
module_param_named(ac_selfheal, b43_ac_selfheal, uint, 0644);
MODULE_PARM_DESC(ac_selfheal, "AC-PHY: max automatic core restarts when the txphyerr counter shows a bad init, 0 = off, default 3");

#define B43_AC_SH_TXPHYERR	0x00FE

static bool b43_phy_ac_check_badinit(struct b43_wldev *dev)
{
	static unsigned int restarts;
	static unsigned long last_restart;
	static u16 last;
	u16 now, d;

	if (!b43_ac_selfheal)
		return false;
	if (restarts && time_after(jiffies, last_restart + 600 * HZ))
		restarts = 0;
	now = b43_shm_read16(dev, B43_SHM_SHARED, B43_AC_SH_TXPHYERR);
	d = now - last;
	last = now;
	if (d < 3 || restarts >= b43_ac_selfheal)
		return false;
	restarts++;
	last_restart = jiffies;
	last = 0;	/* the ucode is reloaded, its counters restart at 0 */
	pr_emerg("b43 ac_selfheal: bad init (%u PHY TX errors), restart %u/%u\n",
		 d, restarts, b43_ac_selfheal);
	mdelay(30);
	b43_controller_restart(dev, "AC bad init");
	return true;
}

static void b43_phy_ac_op_pwork_15sec(struct b43_wldev *dev)
{
	struct b43_dmaring *rx = dev->dma.rx_ring;
	struct b43_dmaring *tx = dev->dma.tx_ring_AC_BE;

	if (b43_phy_ac_check_badinit(dev))
		return;
	if (b43_phy_ac_check_ack_watchdog(dev))
		return;

	/* See notes/38: wl's real watchdog runs a periodic bulk RX-ring
	 * refill sweep this port never had; do the equivalent here. */
	b43_dma_rx_retry_poisoned(dev);

	if (!b43_ac_diag)
		return;
	b43info(dev->wl, "phy_ac: MACCTL=%08x IRQ reason=%08x mask=%08x pio=%d\n",
		b43_read32(dev, B43_MMIO_MACCTL),
		b43_read32(dev, B43_MMIO_GEN_IRQ_REASON),
		b43_read32(dev, B43_MMIO_GEN_IRQ_MASK),
		dev->__using_pio_transfers);
	if (!dev->__using_pio_transfers && rx && tx)
		b43info(dev->wl, "phy_ac: DMA rx status=%08x/%08x index=%08x tx(BE) status=%08x\n",
			b43_read32(dev, rx->mmio_base + B43_DMA64_RXSTATUS),
			b43_read32(dev, rx->mmio_base + B43_DMA64_RXSTATUS + 4),
			b43_read32(dev, rx->mmio_base + B43_DMA64_RXINDEX),
			b43_read32(dev, tx->mmio_base + B43_DMA64_TXSTATUS));
	b43info(dev->wl, "phy_ac: dma0 reason=%08x mask=%08x intrcvlazy0=%08x\n",
		b43_read32(dev, B43_MMIO_DMA0_REASON),
		b43_read32(dev, B43_MMIO_DMA0_IRQ_MASK),
		b43_read32(dev, 0x100));
	b43_phy_ac_log_macstat(dev);
	if (dev->dev->bus_type == B43_BUS_BCMA) {
		struct bcma_drv_cc *cc = &dev->dev->bdev->bus->drv_cc;

		b43info(dev->wl, "phy_ac: gpio in=%08x out=%08x outen=%08x control=%08x ioctrl=%08x\n",
			bcma_cc_read32(cc, BCMA_CC_GPIOIN),
			bcma_cc_read32(cc, BCMA_CC_GPIOOUT),
			bcma_cc_read32(cc, BCMA_CC_GPIOOUTEN),
			bcma_cc_read32(cc, BCMA_CC_GPIOCTL),
			bcma_aread32(dev->dev->bdev, BCMA_IOCTL));
	}
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
