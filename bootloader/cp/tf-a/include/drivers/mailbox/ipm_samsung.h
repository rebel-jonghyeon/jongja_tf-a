/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#pragma once
#include "stdint.h"

union ipm_samsung_mcuctrl {
	struct {
		uint32_t mswrst:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union ipm_samsung_intgr0 {
	struct {
		uint32_t intgc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_intcr0 {
	struct {
		uint32_t intcc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_intmr0 {
	struct {
		uint32_t intmc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_intsr0 {
	struct {
		uint32_t intsc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_intmsr0 {
	struct {
		uint32_t intmsc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_intgr1 {
	struct {
		uint32_t intgc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_intcr1 {
	struct {
		uint32_t intcc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_intmr1 {
	struct {
		uint32_t intmc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_intsr1 {
	struct {
		uint32_t intsc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_intmsr1 {
	struct {
		uint32_t intmsc31_0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_mif_init {
	struct {
		uint32_t rsvd1:2; /* [1:0] */
		uint32_t mif_init:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union ipm_samsung_is_version {
	struct {
		uint32_t is_version; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr0 {
	struct {
		uint32_t issr0; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr1 {
	struct {
		uint32_t issr1; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr2 {
	struct {
		uint32_t issr2; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr3 {
	struct {
		uint32_t issr3; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr4 {
	struct {
		uint32_t issr4; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr5 {
	struct {
		uint32_t issr5; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr6 {
	struct {
		uint32_t issr6; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr7 {
	struct {
		uint32_t issr7; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr8 {
	struct {
		uint32_t issr8; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr9 {
	struct {
		uint32_t issr9; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr10 {
	struct {
		uint32_t issr10; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr11 {
	struct {
		uint32_t issr11; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr12 {
	struct {
		uint32_t issr12; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr13 {
	struct {
		uint32_t issr13; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr14 {
	struct {
		uint32_t issr14; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr15 {
	struct {
		uint32_t issr15; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr16 {
	struct {
		uint32_t issr16; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr17 {
	struct {
		uint32_t issr17; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr18 {
	struct {
		uint32_t issr18; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr19 {
	struct {
		uint32_t issr19; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr20 {
	struct {
		uint32_t issr20; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr21 {
	struct {
		uint32_t issr21; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr22 {
	struct {
		uint32_t issr22; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr23 {
	struct {
		uint32_t issr23; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr24 {
	struct {
		uint32_t issr24; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr25 {
	struct {
		uint32_t issr25; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr26 {
	struct {
		uint32_t issr26; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr27 {
	struct {
		uint32_t issr27; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr28 {
	struct {
		uint32_t issr28; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr29 {
	struct {
		uint32_t issr29; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr30 {
	struct {
		uint32_t issr30; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr31 {
	struct {
		uint32_t issr31; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr32 {
	struct {
		uint32_t issr32; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr33 {
	struct {
		uint32_t issr33; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr34 {
	struct {
		uint32_t issr34; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr35 {
	struct {
		uint32_t issr35; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr36 {
	struct {
		uint32_t issr36; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr37 {
	struct {
		uint32_t issr37; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr38 {
	struct {
		uint32_t issr38; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr39 {
	struct {
		uint32_t issr39; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr40 {
	struct {
		uint32_t issr40; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr41 {
	struct {
		uint32_t issr41; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr42 {
	struct {
		uint32_t issr42; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr43 {
	struct {
		uint32_t issr43; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr44 {
	struct {
		uint32_t issr44; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr45 {
	struct {
		uint32_t issr45; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr46 {
	struct {
		uint32_t issr46; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr47 {
	struct {
		uint32_t issr47; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr48 {
	struct {
		uint32_t issr48; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr49 {
	struct {
		uint32_t issr49; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr50 {
	struct {
		uint32_t issr50; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr51 {
	struct {
		uint32_t issr51; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr52 {
	struct {
		uint32_t issr52; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr53 {
	struct {
		uint32_t issr53; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr54 {
	struct {
		uint32_t issr54; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr55 {
	struct {
		uint32_t issr55; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr56 {
	struct {
		uint32_t issr56; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr57 {
	struct {
		uint32_t issr57; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr58 {
	struct {
		uint32_t issr58; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr59 {
	struct {
		uint32_t issr59; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr60 {
	struct {
		uint32_t issr60; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr61 {
	struct {
		uint32_t issr61; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr62 {
	struct {
		uint32_t issr62; /* [31:0] */
	};
	uint32_t val;
};

union ipm_samsung_issr63 {
	struct {
		uint32_t issr63; /* [31:0] */
	};
	uint32_t val;
};

struct ipm_samsung {
	union ipm_samsung_mcuctrl mcuctrl; /* offset : 0x0 */
	uint32_t reserved_1;
	union ipm_samsung_intgr0 intgr0; /* offset : 0x8 */
	union ipm_samsung_intcr0 intcr0; /* offset : 0xc */
	union ipm_samsung_intmr0 intmr0; /* offset : 0x10 */
	union ipm_samsung_intsr0 intsr0; /* offset : 0x14 */
	union ipm_samsung_intmsr0 intmsr0; /* offset : 0x18 */
	union ipm_samsung_intgr1 intgr1; /* offset : 0x1c */
	union ipm_samsung_intcr1 intcr1; /* offset : 0x20 */
	union ipm_samsung_intmr1 intmr1; /* offset : 0x24 */
	union ipm_samsung_intsr1 intsr1; /* offset : 0x28 */
	union ipm_samsung_intmsr1 intmsr1; /* offset : 0x2c */
	uint32_t reserved_2[15];
	union ipm_samsung_mif_init mif_init; /* offset : 0x6c */
	union ipm_samsung_is_version is_version; /* offset : 0x70 */
	uint32_t reserved_3[3];
	union ipm_samsung_issr0 issr0; /* offset : 0x80 */
	union ipm_samsung_issr1 issr1; /* offset : 0x84 */
	union ipm_samsung_issr2 issr2; /* offset : 0x88 */
	union ipm_samsung_issr3 issr3; /* offset : 0x8c */
	union ipm_samsung_issr4 issr4; /* offset : 0x90 */
	union ipm_samsung_issr5 issr5; /* offset : 0x94 */
	union ipm_samsung_issr6 issr6; /* offset : 0x98 */
	union ipm_samsung_issr7 issr7; /* offset : 0x9c */
	union ipm_samsung_issr8 issr8; /* offset : 0xa0 */
	union ipm_samsung_issr9 issr9; /* offset : 0xa4 */
	union ipm_samsung_issr10 issr10; /* offset : 0xa8 */
	union ipm_samsung_issr11 issr11; /* offset : 0xac */
	union ipm_samsung_issr12 issr12; /* offset : 0xb0 */
	union ipm_samsung_issr13 issr13; /* offset : 0xb4 */
	union ipm_samsung_issr14 issr14; /* offset : 0xb8 */
	union ipm_samsung_issr15 issr15; /* offset : 0xbc */
	union ipm_samsung_issr16 issr16; /* offset : 0xc0 */
	union ipm_samsung_issr17 issr17; /* offset : 0xc4 */
	union ipm_samsung_issr18 issr18; /* offset : 0xc8 */
	union ipm_samsung_issr19 issr19; /* offset : 0xcc */
	union ipm_samsung_issr20 issr20; /* offset : 0xd0 */
	union ipm_samsung_issr21 issr21; /* offset : 0xd4 */
	union ipm_samsung_issr22 issr22; /* offset : 0xd8 */
	union ipm_samsung_issr23 issr23; /* offset : 0xdc */
	union ipm_samsung_issr24 issr24; /* offset : 0xe0 */
	union ipm_samsung_issr25 issr25; /* offset : 0xe4 */
	union ipm_samsung_issr26 issr26; /* offset : 0xe8 */
	union ipm_samsung_issr27 issr27; /* offset : 0xec */
	union ipm_samsung_issr28 issr28; /* offset : 0xf0 */
	union ipm_samsung_issr29 issr29; /* offset : 0xf4 */
	union ipm_samsung_issr30 issr30; /* offset : 0xf8 */
	union ipm_samsung_issr31 issr31; /* offset : 0xfc */
	union ipm_samsung_issr32 issr32; /* offset : 0x100 */
	union ipm_samsung_issr33 issr33; /* offset : 0x104 */
	union ipm_samsung_issr34 issr34; /* offset : 0x108 */
	union ipm_samsung_issr35 issr35; /* offset : 0x10c */
	union ipm_samsung_issr36 issr36; /* offset : 0x110 */
	union ipm_samsung_issr37 issr37; /* offset : 0x114 */
	union ipm_samsung_issr38 issr38; /* offset : 0x118 */
	union ipm_samsung_issr39 issr39; /* offset : 0x11c */
	union ipm_samsung_issr40 issr40; /* offset : 0x120 */
	union ipm_samsung_issr41 issr41; /* offset : 0x124 */
	union ipm_samsung_issr42 issr42; /* offset : 0x128 */
	union ipm_samsung_issr43 issr43; /* offset : 0x12c */
	union ipm_samsung_issr44 issr44; /* offset : 0x130 */
	union ipm_samsung_issr45 issr45; /* offset : 0x134 */
	union ipm_samsung_issr46 issr46; /* offset : 0x138 */
	union ipm_samsung_issr47 issr47; /* offset : 0x13c */
	union ipm_samsung_issr48 issr48; /* offset : 0x140 */
	union ipm_samsung_issr49 issr49; /* offset : 0x144 */
	union ipm_samsung_issr50 issr50; /* offset : 0x148 */
	union ipm_samsung_issr51 issr51; /* offset : 0x14c */
	union ipm_samsung_issr52 issr52; /* offset : 0x150 */
	union ipm_samsung_issr53 issr53; /* offset : 0x154 */
	union ipm_samsung_issr54 issr54; /* offset : 0x158 */
	union ipm_samsung_issr55 issr55; /* offset : 0x15c */
	union ipm_samsung_issr56 issr56; /* offset : 0x160 */
	union ipm_samsung_issr57 issr57; /* offset : 0x164 */
	union ipm_samsung_issr58 issr58; /* offset : 0x168 */
	union ipm_samsung_issr59 issr59; /* offset : 0x16c */
	union ipm_samsung_issr60 issr60; /* offset : 0x170 */
	union ipm_samsung_issr61 issr61; /* offset : 0x174 */
	union ipm_samsung_issr62 issr62; /* offset : 0x178 */
	union ipm_samsung_issr63 issr63; /* offset : 0x17c */
};
