/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2025 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#ifndef _G_DNC_STATUS_COMMON_H_
#define _G_DNC_STATUS_COMMON_H_

#define ADDR_OFFSET_DNC_STATUS_DO					0x000
#define ADDR_OFFSET_DNC_STATUS_TRIG					0x004
#define ADDR_OFFSET_DNC_STATUS_FETCH_STATUS_COMP0	0x010
#define ADDR_OFFSET_DNC_STATUS_FETCH_STATUS_COMP1	0x014
#define ADDR_OFFSET_DNC_STATUS_FETCH_STATUS_LDUDMA0 0x018
#define ADDR_OFFSET_DNC_STATUS_FETCH_STATUS_LDUDMA1 0x01C
#define ADDR_OFFSET_DNC_STATUS_FETCH_STATUS_LPUDMA0 0x020
#define ADDR_OFFSET_DNC_STATUS_FETCH_STATUS_LPUDMA1 0x024
#define ADDR_OFFSET_DNC_STATUS_FETCH_STATUS_STUDMA0 0x028
#define ADDR_OFFSET_DNC_STATUS_FETCH_STATUS_STUDMA1 0x02C
#define ADDR_OFFSET_DNC_STATUS_DM_STATUS00			0x030
#define ADDR_OFFSET_DNC_STATUS_FETCH_COMP0			0x040
#define ADDR_OFFSET_DNC_STATUS_FETCH_COMP1			0x044
#define ADDR_OFFSET_DNC_STATUS_FETCH_COMP2			0x048
#define ADDR_OFFSET_DNC_STATUS_FETCH_COMP3			0x04C
#define ADDR_OFFSET_DNC_STATUS_FETCH_COMP4			0x050
#define ADDR_OFFSET_DNC_STATUS_FETCH_COMP5			0x054
#define ADDR_OFFSET_DNC_STATUS_FETCH_COMP6			0x058
#define ADDR_OFFSET_DNC_STATUS_FETCH_COMP7			0x05C
#define ADDR_OFFSET_DNC_STATUS_FETCH_LDUDMA0		0x060
#define ADDR_OFFSET_DNC_STATUS_FETCH_LDUDMA1		0x064
#define ADDR_OFFSET_DNC_STATUS_FETCH_LDUDMA2		0x068
#define ADDR_OFFSET_DNC_STATUS_FETCH_LDUDMA3		0x06C
#define ADDR_OFFSET_DNC_STATUS_FETCH_LDUDMA4		0x070
#define ADDR_OFFSET_DNC_STATUS_FETCH_LDUDMA5		0x074
#define ADDR_OFFSET_DNC_STATUS_FETCH_LDUDMA6		0x078
#define ADDR_OFFSET_DNC_STATUS_FETCH_LDUDMA7		0x07C
#define ADDR_OFFSET_DNC_STATUS_FETCH_LPUDMA0		0x080
#define ADDR_OFFSET_DNC_STATUS_FETCH_LPUDMA1		0x084
#define ADDR_OFFSET_DNC_STATUS_FETCH_LPUDMA2		0x088
#define ADDR_OFFSET_DNC_STATUS_FETCH_LPUDMA3		0x08C
#define ADDR_OFFSET_DNC_STATUS_FETCH_LPUDMA4		0x090
#define ADDR_OFFSET_DNC_STATUS_FETCH_LPUDMA5		0x094
#define ADDR_OFFSET_DNC_STATUS_FETCH_LPUDMA6		0x098
#define ADDR_OFFSET_DNC_STATUS_FETCH_LPUDMA7		0x09C
#define ADDR_OFFSET_DNC_STATUS_FETCH_STUDMA0		0x0A0
#define ADDR_OFFSET_DNC_STATUS_FETCH_STUDMA1		0x0A4
#define ADDR_OFFSET_DNC_STATUS_FETCH_STUDMA2		0x0A8
#define ADDR_OFFSET_DNC_STATUS_FETCH_STUDMA3		0x0AC
#define ADDR_OFFSET_DNC_STATUS_FETCH_STUDMA4		0x0B0
#define ADDR_OFFSET_DNC_STATUS_FETCH_STUDMA5		0x0B4
#define ADDR_OFFSET_DNC_STATUS_FETCH_STUDMA6		0x0B8
#define ADDR_OFFSET_DNC_STATUS_FETCH_STUDMA7		0x0BC
#define ADDR_OFFSET_DNC_STATUS_COMP_ACC0			0x0C0
#define ADDR_OFFSET_DNC_STATUS_COMP_ACC1			0x0C4
#define ADDR_OFFSET_DNC_STATUS_COMP_ACC2			0x0C8
#define ADDR_OFFSET_DNC_STATUS_COMP_ACC3			0x0CC
#define ADDR_OFFSET_DNC_STATUS_COMP_ACC4			0x0D0
#define ADDR_OFFSET_DNC_STATUS_COMP_ACC5			0x0D4
#define ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC0			0x0E0
#define ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC1			0x0E4
#define ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC2			0x0E8
#define ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC3			0x0EC
#define ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC4			0x0F0
#define ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC5			0x0F4
#define ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC0			0x100
#define ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC1			0x104
#define ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC2			0x108
#define ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC3			0x10C
#define ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC4			0x110
#define ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC5			0x114
#define ADDR_OFFSET_DNC_STATUS_STUDMA_ACC0			0x120
#define ADDR_OFFSET_DNC_STATUS_STUDMA_ACC1			0x124
#define ADDR_OFFSET_DNC_STATUS_STUDMA_ACC2			0x128
#define ADDR_OFFSET_DNC_STATUS_STUDMA_ACC3			0x12C
#define ADDR_OFFSET_DNC_STATUS_STUDMA_ACC4			0x130
#define ADDR_OFFSET_DNC_STATUS_STUDMA_ACC5			0x134
#define ADDR_OFFSET_DNC_STATUS_CMST_ACC0			0x140
#define ADDR_OFFSET_DNC_STATUS_CMST_ACC1			0x144
#define ADDR_OFFSET_DNC_STATUS_CMST_ACC2			0x148
#define ADDR_OFFSET_DNC_STATUS_CMST_ACC3			0x14C
#define ADDR_OFFSET_DNC_STATUS_CMST_ACC4			0x150
#define ADDR_OFFSET_DNC_STATUS_CSLV_ACC0			0x160
#define ADDR_OFFSET_DNC_STATUS_CSLV_ACC1			0x164
#define ADDR_OFFSET_DNC_STATUS_CSLV_ACC2			0x168
#define ADDR_OFFSET_DNC_STATUS_CSLV_ACC3			0x16C
#define ADDR_OFFSET_DNC_STATUS_CSLV_ACC4			0x170
#define ADDR_OFFSET_DNC_STATUS_Q_STATUS_COMP		0x180
#define ADDR_OFFSET_DNC_STATUS_Q_STATUS_LDUDMA		0x184
#define ADDR_OFFSET_DNC_STATUS_Q_STATUS_LPUDMA		0x188
#define ADDR_OFFSET_DNC_STATUS_Q_STATUS_STUDMA		0x18C
#define ADDR_OFFSET_DNC_STATUS_Q_IDLE_TIME_COMP_L32 0x190
#define ADDR_OFFSET_DNC_STATUS_Q_IDLE_TIME_COMP_H32 0x194
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC0		0x1C0
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC1		0x1C4
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC2		0x1C8
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC3		0x1CC
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC4		0x1D0
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC5		0x1D4
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC6		0x1D8
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC7		0x1DC
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC8		0x1E0
#define ADDR_OFFSET_DNC_STATUS_TLB_MISS_ACC9		0x1E4
#define ADDR_OFFSET_DNC_STATUS_SP_TRAN00			0x1F0
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS00			0x200
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS01			0x204
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS02			0x208
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS03			0x20C
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS04			0x210
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS05			0x214
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS06			0x218
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS07			0x21C
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS08			0x220
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS09			0x224
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS10			0x228
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS11			0x22C
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS12			0x230
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS13			0x234
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS14			0x238
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS15			0x23C
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS16			0x240
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS17			0x244
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS18			0x248
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS19			0x24C
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS20			0x250
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS21			0x254
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS22			0x258
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS23			0x25C
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS24			0x260
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS25			0x264
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS26			0x268
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS27			0x26C
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS28			0x270
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS29			0x274
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS30			0x278
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS31			0x27C
#define ADDR_OFFSET_DNC_STATUS_SP_STATUS32			0x280
#define ADDR_OFFSET_DNC_STATUS_DBUS_TOUCH			0x2A0
#define ADDR_OFFSET_DNC_STATUS_DMST0_OTF_CNT		0x2A4
#define ADDR_OFFSET_DNC_STATUS_DMST1_OTF_CNT		0x2A8
#define ADDR_OFFSET_DNC_STATUS_DSLV_OTF_CNT			0x2AC
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP00		0x2C0
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP01		0x2C4
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP02		0x2C8
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP03		0x2CC
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP04		0x2D0
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP05		0x2D4
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP06		0x2D8
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP07		0x2DC
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP08		0x2E0
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP09		0x2E4
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP10		0x2E8
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP11		0x2EC
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP12		0x2F0
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP13		0x2F4
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP14		0x2F8
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP15		0x2FC
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP16		0x300
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP17		0x304
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP18		0x308
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP19		0x30C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP20		0x310
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP21		0x314
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP22		0x318
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP23		0x31C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP24		0x320
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP25		0x324
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP26		0x328
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP27		0x32C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP28		0x330
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP29		0x334
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP30		0x338
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP31		0x33C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP32		0x340
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP33		0x344
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP34		0x348
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP35		0x34C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP36		0x350
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP37		0x354
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP38		0x358
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP39		0x35C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP40		0x360
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP41		0x364
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP42		0x368
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP43		0x36C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP44		0x370
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP45		0x374
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP46		0x378
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP47		0x37C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP48		0x380
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP49		0x384
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP50		0x388
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP51		0x38C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP52		0x390
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP53		0x394
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP54		0x398
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP55		0x39C
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP56		0x3A0
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP57		0x3A4
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP58		0x3A8
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP59		0x3AC
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP60		0x3B0
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP61		0x3B4
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP62		0x3B8
#define ADDR_OFFSET_DNC_STATUS_TSYNC_GROUP63		0x3BC
#define ADDR_OFFSET_DNC_STATUS_TEST0				0x3F0
#define ADDR_OFFSET_DNC_STATUS_TEST1				0x3F4
#define ADDR_OFFSET_DNC_STATUS_TEST2				0x3F8
#define ADDR_OFFSET_DNC_STATUS_TEST3				0x3FC

union dnc_status_do {
	struct __attribute__((packed)) {
		uint32_t acc_en : 1;
		uint32_t rsvd1 : 31;
	};
	uint32_t bits;
};

union dnc_status_trig {
	struct __attribute__((packed)) {
		uint32_t clear_status : 1;
		uint32_t clear_fetch : 1;
		uint32_t clear_acc : 1;
		uint32_t clear_fetch_cnt_comp : 1;
		uint32_t clear_fetch_cnt_ldudma : 1;
		uint32_t clear_fetch_cnt_lpudma : 1;
		uint32_t clear_fetch_cnt_studma : 1;
		uint32_t stop_qitm_comp : 1;
		uint32_t start_qitm_comp : 1;
		uint32_t rsvd9 : 23;
	};
	uint32_t bits;
};

union dnc_status_fetch_status_comp0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_status_comp1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t cnt_wait : 8;
		uint32_t cnt_fetch : 16;
	};
	uint32_t bits;
};

union dnc_status_fetch_status_ldudma0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_status_ldudma1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t cnt_wait : 8;
		uint32_t cnt_fetch : 16;
	};
	uint32_t bits;
};

union dnc_status_fetch_status_lpudma0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_status_lpudma1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t cnt_wait : 8;
		uint32_t cnt_fetch : 16;
	};
	uint32_t bits;
};

union dnc_status_fetch_status_studma0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_status_studma1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t cnt_wait : 8;
		uint32_t cnt_fetch : 16;
	};
	uint32_t bits;
};

union dnc_status_dm_status00 {
	struct __attribute__((packed)) {
		uint32_t init_done : 1;
		uint32_t rsvd1 : 3;
		uint32_t init_cnt : 12;
		uint32_t rsvd16 : 16;
	};
	uint32_t bits;
};

union dnc_status_fetch_comp0 {
	struct __attribute__((packed)) {
		uint32_t desc_id : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_comp1 {
	struct __attribute__((packed)) {
		uint32_t desc_mode : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_comp2 {
	struct __attribute__((packed)) {
		uint32_t desc_prog0 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_comp3 {
	struct __attribute__((packed)) {
		uint32_t desc_prog1 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_comp4 {
	struct __attribute__((packed)) {
		uint32_t desc_prog2 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_comp5 {
	struct __attribute__((packed)) {
		uint32_t desc_tsync : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_comp6 {
	struct __attribute__((packed)) {
		uint32_t desc_cfg0 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_comp7 {
	struct __attribute__((packed)) {
		uint32_t desc_cfg1 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_ldudma0 {
	struct __attribute__((packed)) {
		uint32_t desc_id : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_ldudma1 {
	struct __attribute__((packed)) {
		uint32_t desc_mode : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_ldudma2 {
	struct __attribute__((packed)) {
		uint32_t desc_prog0 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_ldudma3 {
	struct __attribute__((packed)) {
		uint32_t desc_prog1 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_ldudma4 {
	struct __attribute__((packed)) {
		uint32_t desc_prog2 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_ldudma5 {
	struct __attribute__((packed)) {
		uint32_t desc_tsync : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_ldudma6 {
	struct __attribute__((packed)) {
		uint32_t desc_cfg0 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_ldudma7 {
	struct __attribute__((packed)) {
		uint32_t desc_cfg1 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_lpudma0 {
	struct __attribute__((packed)) {
		uint32_t desc_id : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_lpudma1 {
	struct __attribute__((packed)) {
		uint32_t desc_mode : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_lpudma2 {
	struct __attribute__((packed)) {
		uint32_t desc_prog0 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_lpudma3 {
	struct __attribute__((packed)) {
		uint32_t desc_prog1 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_lpudma4 {
	struct __attribute__((packed)) {
		uint32_t desc_prog2 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_lpudma5 {
	struct __attribute__((packed)) {
		uint32_t desc_tsync : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_lpudma6 {
	struct __attribute__((packed)) {
		uint32_t desc_cfg0 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_lpudma7 {
	struct __attribute__((packed)) {
		uint32_t desc_cfg1 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_studma0 {
	struct __attribute__((packed)) {
		uint32_t desc_id : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_studma1 {
	struct __attribute__((packed)) {
		uint32_t desc_mode : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_studma2 {
	struct __attribute__((packed)) {
		uint32_t desc_prog0 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_studma3 {
	struct __attribute__((packed)) {
		uint32_t desc_prog1 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_studma4 {
	struct __attribute__((packed)) {
		uint32_t desc_prog2 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_studma5 {
	struct __attribute__((packed)) {
		uint32_t desc_tsync : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_studma6 {
	struct __attribute__((packed)) {
		uint32_t desc_cfg0 : 32;
	};
	uint32_t bits;
};

union dnc_status_fetch_studma7 {
	struct __attribute__((packed)) {
		uint32_t desc_cfg1 : 32;
	};
	uint32_t bits;
};

union dnc_status_comp_acc0 {
	struct __attribute__((packed)) {
		uint32_t enq : 32;
	};
	uint32_t bits;
};

union dnc_status_comp_acc1 {
	struct __attribute__((packed)) {
		uint32_t deq : 32;
	};
	uint32_t bits;
};

union dnc_status_comp_acc2 {
	struct __attribute__((packed)) {
		uint32_t done : 32;
	};
	uint32_t bits;
};

union dnc_status_comp_acc3 {
	struct __attribute__((packed)) {
		uint32_t enq_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_comp_acc4 {
	struct __attribute__((packed)) {
		uint32_t deq_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_comp_acc5 {
	struct __attribute__((packed)) {
		uint32_t done_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_ldudma_acc0 {
	struct __attribute__((packed)) {
		uint32_t enq : 32;
	};
	uint32_t bits;
};

union dnc_status_ldudma_acc1 {
	struct __attribute__((packed)) {
		uint32_t deq : 32;
	};
	uint32_t bits;
};

union dnc_status_ldudma_acc2 {
	struct __attribute__((packed)) {
		uint32_t done : 32;
	};
	uint32_t bits;
};

union dnc_status_ldudma_acc3 {
	struct __attribute__((packed)) {
		uint32_t enq_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_ldudma_acc4 {
	struct __attribute__((packed)) {
		uint32_t deq_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_ldudma_acc5 {
	struct __attribute__((packed)) {
		uint32_t done_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_lpudma_acc0 {
	struct __attribute__((packed)) {
		uint32_t enq : 32;
	};
	uint32_t bits;
};

union dnc_status_lpudma_acc1 {
	struct __attribute__((packed)) {
		uint32_t deq : 32;
	};
	uint32_t bits;
};

union dnc_status_lpudma_acc2 {
	struct __attribute__((packed)) {
		uint32_t done : 32;
	};
	uint32_t bits;
};

union dnc_status_lpudma_acc3 {
	struct __attribute__((packed)) {
		uint32_t enq_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_lpudma_acc4 {
	struct __attribute__((packed)) {
		uint32_t deq_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_lpudma_acc5 {
	struct __attribute__((packed)) {
		uint32_t done_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_studma_acc0 {
	struct __attribute__((packed)) {
		uint32_t enq : 32;
	};
	uint32_t bits;
};

union dnc_status_studma_acc1 {
	struct __attribute__((packed)) {
		uint32_t deq : 32;
	};
	uint32_t bits;
};

union dnc_status_studma_acc2 {
	struct __attribute__((packed)) {
		uint32_t done : 32;
	};
	uint32_t bits;
};

union dnc_status_studma_acc3 {
	struct __attribute__((packed)) {
		uint32_t enq_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_studma_acc4 {
	struct __attribute__((packed)) {
		uint32_t deq_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_studma_acc5 {
	struct __attribute__((packed)) {
		uint32_t done_sole : 32;
	};
	uint32_t bits;
};

union dnc_status_cmst_acc0 {
	struct __attribute__((packed)) {
		uint32_t aw : 32;
	};
	uint32_t bits;
};

union dnc_status_cmst_acc1 {
	struct __attribute__((packed)) {
		uint32_t w : 32;
	};
	uint32_t bits;
};

union dnc_status_cmst_acc2 {
	struct __attribute__((packed)) {
		uint32_t b : 32;
	};
	uint32_t bits;
};

union dnc_status_cmst_acc3 {
	struct __attribute__((packed)) {
		uint32_t ar : 32;
	};
	uint32_t bits;
};

union dnc_status_cmst_acc4 {
	struct __attribute__((packed)) {
		uint32_t r : 32;
	};
	uint32_t bits;
};

union dnc_status_cslv_acc0 {
	struct __attribute__((packed)) {
		uint32_t aw : 32;
	};
	uint32_t bits;
};

union dnc_status_cslv_acc1 {
	struct __attribute__((packed)) {
		uint32_t w : 32;
	};
	uint32_t bits;
};

union dnc_status_cslv_acc2 {
	struct __attribute__((packed)) {
		uint32_t b : 32;
	};
	uint32_t bits;
};

union dnc_status_cslv_acc3 {
	struct __attribute__((packed)) {
		uint32_t ar : 32;
	};
	uint32_t bits;
};

union dnc_status_cslv_acc4 {
	struct __attribute__((packed)) {
		uint32_t r : 32;
	};
	uint32_t bits;
};

union dnc_status_q_status_comp {
	struct __attribute__((packed)) {
		uint32_t sequence : 16;
		uint32_t back_pressure : 16;
	};
	uint32_t bits;
};

union dnc_status_q_status_ldudma {
	struct __attribute__((packed)) {
		uint32_t sequence : 16;
		uint32_t back_pressure : 16;
	};
	uint32_t bits;
};

union dnc_status_q_status_lpudma {
	struct __attribute__((packed)) {
		uint32_t sequence : 16;
		uint32_t back_pressure : 16;
	};
	uint32_t bits;
};

union dnc_status_q_status_studma {
	struct __attribute__((packed)) {
		uint32_t sequence : 16;
		uint32_t back_pressure : 16;
	};
	uint32_t bits;
};

union dnc_status_q_idle_time_comp_l32 {
	struct __attribute__((packed)) {
		uint32_t cycles : 32;
	};
	uint32_t bits;
};

union dnc_status_q_idle_time_comp_h32 {
	struct __attribute__((packed)) {
		uint32_t cycles : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc0 {
	struct __attribute__((packed)) {
		uint32_t p0_comprd : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc1 {
	struct __attribute__((packed)) {
		uint32_t p0_compwr : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc2 {
	struct __attribute__((packed)) {
		uint32_t p0_ldudma : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc3 {
	struct __attribute__((packed)) {
		uint32_t p0_lpudma : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc4 {
	struct __attribute__((packed)) {
		uint32_t p0_studma : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc5 {
	struct __attribute__((packed)) {
		uint32_t p1_comprd : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc6 {
	struct __attribute__((packed)) {
		uint32_t p1_compwr : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc7 {
	struct __attribute__((packed)) {
		uint32_t p1_ldudma : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc8 {
	struct __attribute__((packed)) {
		uint32_t p1_lpudma : 32;
	};
	uint32_t bits;
};

union dnc_status_tlb_miss_acc9 {
	struct __attribute__((packed)) {
		uint32_t p1_studma : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_tran00 {
	struct __attribute__((packed)) {
		uint32_t nclu0_rv_status : 4;
		uint32_t ncsu0_rv_status : 4;
		uint32_t nclu1_rv_status : 4;
		uint32_t ncsu1_rv_status : 4;
		uint32_t wrslv_rv_status : 4;
		uint32_t rdslv_rv_status : 4;
		uint32_t rsvd24 : 8;
	};
	uint32_t bits;
};

union dnc_status_sp_status00 {
	struct __attribute__((packed)) {
		uint32_t init_done : 2;
		uint32_t init_error : 2;
		uint32_t init_explicit : 1;
		uint32_t rsvd5 : 3;
		uint32_t run_unit : 24;
	};
	uint32_t bits;
};

union dnc_status_sp_status01 {
	struct __attribute__((packed)) {
		uint32_t test_done : 1;
		uint32_t rsvd1 : 15;
		uint32_t test_cnt_mismatch : 16;
	};
	uint32_t bits;
};

union dnc_status_sp_status02 {
	struct __attribute__((packed)) {
		uint32_t test_cnt_wr : 16;
		uint32_t test_cnt_rd : 16;
	};
	uint32_t bits;
};

union dnc_status_sp_status03 {
	struct __attribute__((packed)) {
		uint32_t test_cnt_ce : 16;
		uint32_t test_cnt_ue : 16;
	};
	uint32_t bits;
};

union dnc_status_sp_status04 {
	struct __attribute__((packed)) {
		uint32_t addr : 16;
		uint32_t ce   : 1;
		uint32_t ue   : 1;
		uint32_t ptm  : 1;
		uint32_t valid : 1;
		uint32_t rsvd20 : 12;
	} sp_test_log;
	uint32_t bits;
};

union dnc_status_sp_status05 {
//	struct __attribute__((packed)) {
//		uint32_t test_log1 : 32;
//	};
	struct __attribute__((packed)) {
		uint32_t addr : 16;
		uint32_t ce   : 1;
		uint32_t ue   : 1;
		uint32_t ptm  : 1;
		uint32_t valid : 1;
		uint32_t rsvd20 : 12;
	} sp_test_log;
	uint32_t bits;
};

union dnc_status_sp_status06 {
//	struct __attribute__((packed)) {
//		uint32_t test_log2 : 32;
//	};
	struct __attribute__((packed)) {
		uint32_t addr : 16;
		uint32_t ce   : 1;
		uint32_t ue   : 1;
		uint32_t ptm  : 1;
		uint32_t valid : 1;
		uint32_t rsvd20 : 12;
	} sp_test_log;
	uint32_t bits;
};

union dnc_status_sp_status07 {
//	struct __attribute__((packed)) {
//		uint32_t test_log3 : 32;
//	};
	struct __attribute__((packed)) {
		uint32_t addr : 16;
		uint32_t ce   : 1;
		uint32_t ue   : 1;
		uint32_t ptm  : 1;
		uint32_t valid : 1;
		uint32_t rsvd20 : 12;
	} sp_test_log;
	uint32_t bits;
};

union dnc_status_sp_status08 {
	struct __attribute__((packed)) {
		uint32_t rsvd0 : 16;
		uint32_t tot_ce : 8;
		uint32_t tot_ue : 8;
	};
	uint32_t bits;
};

union dnc_status_sp_status09 {
	struct __attribute__((packed)) {
		uint32_t acc00l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status10 {
	struct __attribute__((packed)) {
		uint32_t acc00h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status11 {
	struct __attribute__((packed)) {
		uint32_t acc01l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status12 {
	struct __attribute__((packed)) {
		uint32_t acc01h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status13 {
	struct __attribute__((packed)) {
		uint32_t acc02l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status14 {
	struct __attribute__((packed)) {
		uint32_t acc02h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status15 {
	struct __attribute__((packed)) {
		uint32_t acc03l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status16 {
	struct __attribute__((packed)) {
		uint32_t acc03h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status17 {
	struct __attribute__((packed)) {
		uint32_t acc04l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status18 {
	struct __attribute__((packed)) {
		uint32_t acc04h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status19 {
	struct __attribute__((packed)) {
		uint32_t acc05l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status20 {
	struct __attribute__((packed)) {
		uint32_t acc05h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status21 {
	struct __attribute__((packed)) {
		uint32_t acc06l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status22 {
	struct __attribute__((packed)) {
		uint32_t acc06h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status23 {
	struct __attribute__((packed)) {
		uint32_t acc07l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status24 {
	struct __attribute__((packed)) {
		uint32_t acc07h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status25 {
	struct __attribute__((packed)) {
		uint32_t acc08l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status26 {
	struct __attribute__((packed)) {
		uint32_t acc08h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status27 {
	struct __attribute__((packed)) {
		uint32_t acc09l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status28 {
	struct __attribute__((packed)) {
		uint32_t acc09h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status29 {
	struct __attribute__((packed)) {
		uint32_t acc10l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status30 {
	struct __attribute__((packed)) {
		uint32_t acc10h : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status31 {
	struct __attribute__((packed)) {
		uint32_t acc11l : 32;
	};
	uint32_t bits;
};

union dnc_status_sp_status32 {
	struct __attribute__((packed)) {
		uint32_t acc11h : 32;
	};
	uint32_t bits;
};

union dnc_status_dbus_touch {
	struct __attribute__((packed)) {
		uint32_t dmst0_aw : 1;
		uint32_t dmst0_w : 1;
		uint32_t dmst0_b : 1;
		uint32_t dmst0_ar : 1;
		uint32_t dmst0_r : 1;
		uint32_t dmst1_aw : 1;
		uint32_t dmst1_w : 1;
		uint32_t dmst1_b : 1;
		uint32_t dmst1_ar : 1;
		uint32_t dmst1_r : 1;
		uint32_t dslv_aw : 1;
		uint32_t dslv_w : 1;
		uint32_t dslv_b : 1;
		uint32_t dslv_ar : 1;
		uint32_t dslv_r : 1;
		uint32_t rsvd15 : 17;
	};
	uint32_t bits;
};

union dnc_status_dmst0_otf_cnt {
	struct __attribute__((packed)) {
		uint32_t rd : 16;
		uint32_t wr : 16;
	};
	uint32_t bits;
};

union dnc_status_dmst1_otf_cnt {
	struct __attribute__((packed)) {
		uint32_t rd : 16;
		uint32_t wr : 16;
	};
	uint32_t bits;
};

union dnc_status_dslv_otf_cnt {
	struct __attribute__((packed)) {
		uint32_t rd : 16;
		uint32_t wr : 16;
	};
	uint32_t bits;
};

union dnc_status_tsync_group00 {
	struct __attribute__((packed)) {
		uint32_t qbq_comp : 4;
		uint32_t qbq_ldudma : 4;
		uint32_t qbq_lpudma : 4;
		uint32_t qbq_studma : 4;
		uint32_t tkn_comp : 4;
		uint32_t tkn_ldudma : 4;
		uint32_t tkn_lpudma : 4;
		uint32_t tkn_studma : 4;
	} tsync_status;
	uint32_t bits;
};

union dnc_status_tsync_group01 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group02 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group03 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group04 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group05 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group06 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group07 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group08 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group09 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group10 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group11 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group12 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group13 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group14 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group15 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group16 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group17 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group18 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group19 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group20 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group21 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group22 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group23 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group24 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group25 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group26 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group27 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group28 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group29 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group30 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group31 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group32 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group33 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group34 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group35 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group36 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group37 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group38 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group39 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group40 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group41 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group42 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group43 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group44 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group45 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group46 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group47 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group48 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group49 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group50 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group51 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group52 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group53 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group54 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group55 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group56 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group57 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group58 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group59 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group60 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group61 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group62 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_tsync_group63 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_status_test0 {
	struct __attribute__((packed)) {
		uint32_t space : 32;
	};
	uint32_t bits;
};

union dnc_status_test1 {
	struct __attribute__((packed)) {
		uint32_t space : 32;
	};
	uint32_t bits;
};

union dnc_status_test2 {
	struct __attribute__((packed)) {
		uint32_t space : 32;
	};
	uint32_t bits;
};

union dnc_status_test3 {
	struct __attribute__((packed)) {
		uint32_t space : 32;
	};
	uint32_t bits;
};

#endif /* _G_DNC_STATUS_COMMON_H_*/
