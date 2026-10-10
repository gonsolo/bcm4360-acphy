/* SPDX-License-Identifier: GPL-2.0 */
#ifndef B43_TABLES_PHY_AC_H_
#define B43_TABLES_PHY_AC_H_

#include <linux/types.h>

struct b43_phy_ac_tbl {
	const void *data;
	u16 count;
	u16 id;
	u16 offset;
	u8 width;	/* bits per entry: 8, 16 or 32 */
};

extern const struct b43_phy_ac_tbl b43_phy_ac_tbls_rev0[];
extern const unsigned int b43_phy_ac_tbls_rev0_n;
extern const struct b43_phy_ac_tbl b43_phy_ac_rfseq_tbls[];
extern const unsigned int b43_phy_ac_rfseq_tbls_n;
extern const struct b43_phy_ac_tbl b43_phy_ac_femctrl2_tbls[];
extern const unsigned int b43_phy_ac_femctrl2_tbls_n;
extern const struct b43_phy_ac_tbl b43_phy_ac_misc_tbls[];
extern const unsigned int b43_phy_ac_misc_tbls_n;
extern const struct b43_phy_ac_tbl b43_phy_ac_ladder_tbls[];
extern const unsigned int b43_phy_ac_ladder_tbls_n;
extern const struct b43_phy_ac_tbl b43_phy_ac_vendor_tbls[];
extern const unsigned int b43_phy_ac_vendor_tbls_n;

extern const u16 b43_phy_ac_txgain_2g[128][3];
extern const u16 b43_phy_ac_txgain_5g[128][3];

#endif /* B43_TABLES_PHY_AC_H_ */
