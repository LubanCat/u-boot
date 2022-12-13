/*
 * Copyright (C) Guangzhou FriendlyARM Computer Tech. Co., Ltd.
 * (http://www.friendlyarm.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can access it online at
 * http://www.gnu.org/licenses/gpl-2.0.html.
 */

#include <config.h>
#include <common.h>
#include <adc.h>
#include <asm/io.h>
#include <asm/gpio.h>

/*
 * ID info:
 *  ID : Volts : ADC value :   Bucket
 *  ==   =====   =========   ===========
 *   0 : 0.300V:       170 :    0 -  229
 *   1 : 0.507V:       288 :  230 -  344
 *   2 : 0.720V:       409 :  345 -  460
 *   3 : 0.900V:       512 :  461 -  595
 *   4 : 1.192V:       678 :  596 -  732
 *   5 : 1.384V:       787 :  733 -  858
 *   6 : 1.636V:       930 :  859 -  975
 *   7 : 1.800V:      1024 :  977 - 1023
 */
static const int id_readings[] = {
	 229, 344, 460, 595, 732, 858, 975, 1023
};

static uint32_t get_adc_index(int chn)
{
	int i;
	u32 adc_reading = 0;

	adc_channel_single_shot("saradc", chn, &adc_reading);
	for (i = 0; i < ARRAY_SIZE(id_readings); i++) {
		if (adc_reading <= id_readings[i]) {
			printf("ADC Channel:%d reading_value: %d, CH_ID: 0x%02x\n", chn, adc_reading, i);
			return i;
		}
	}

	/* should die for impossible value */
	return 0;
}

/*
 * Board revision by ((ADC_IN3 << 8) + ADC_IN4)
 *  0x0000 - LubanCat1
 *  0x0100 - LubanCat1N
 *  0x0200 - LubanCat Zero N
 *  0x0300 - LubanCat Zreo W
 *  0x0400 - LubanCat2
 *  0x0500/0x0600 - LubanCat2N
 *  0x0700 - LubanCat2IO
 */
static int pcb_rev = -1;
static int pcb_rev_ch2 = -1;
static int pcb_rev_ch3 = -1;

void bd_hwrev_init(void)
{
	if (pcb_rev >= 0)
		return;

	pcb_rev_ch2 = get_adc_index(2);
	pcb_rev_ch3 = get_adc_index(3);
	pcb_rev = ((pcb_rev_ch2 << 8) + pcb_rev_ch3);
}

/* To override __weak symbols */
u32 get_board_rev(void)
{
	return pcb_rev;
}

const char *get_board_name(void)
{
	bd_hwrev_init();

	printf("Board Version: Board_ID 0x%04x\n", pcb_rev);

	switch (pcb_rev) {
		case 0x0000:
			env_set("board_env", "LubanCat1");
			return "LubanCat1";
		case 0x0100:
			env_set("board_env", "LubanCat1N");
			return "LubanCat1N";
		case 0x0200:
			env_set("board_env", "LubanCatZN");
			return "LubanCat Zero N";			
		case 0x0300:
			env_set("board_env", "LubanCatZW");
			return "LubanCat Zero W";
		case 0x0400:
			env_set("board_env", "LubanCat2");
			return "LubanCat2";
		case 0x0500:
			env_set("board_env", "LubanCat2N");
			return "LubanCat2N";
		case 0x0600:
			env_set("board_env", "LubanCat2N");
			return "LubanCat2N";
		case 0x0700:
			env_set("board_env", "LubanCat2IO");
			return "LubanCat2IO";
		default:
			env_set("board_env", "");
			return "LubanCat RK356x board";
	}
	
}

