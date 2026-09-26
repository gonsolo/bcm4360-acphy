/* SPDX-License-Identifier: GPL-2.0 */
#ifndef B43_RADIO_2069_H_
#define B43_RADIO_2069_H_

#include <linux/types.h>

#define B43_RADIO_2069_TUNE_REGS	50

struct b43_radio_2069_chan {
	u16 channel;
	u16 freq;
	u16 radio[B43_RADIO_2069_TUNE_REGS];
	u16 bw[6];
};

extern const struct b43_radio_2069_chan b43_radio_2069r4_chans[];
extern const unsigned int b43_radio_2069r4_chans_n;

#endif /* B43_RADIO_2069_H_ */
