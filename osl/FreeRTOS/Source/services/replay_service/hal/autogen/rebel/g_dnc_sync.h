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

#ifndef _G_DNC_SYNC_COMMON_H_
#define _G_DNC_SYNC_COMMON_H_

#ifndef EVT_VER
#error "EVT_VER must be defined (replay_service: CMake -DEVT_VER=0 or 1)"
#endif

#define ADDR_OFFSET_DNC_SYNC_TSYNC_RECEIVE		0x000
#define ADDR_OFFSET_DNC_SYNC_PSYNC_RECEIVE		0x004
#define ADDR_OFFSET_DNC_SYNC_TSYNC_FORCE		0x010
#define ADDR_OFFSET_DNC_SYNC_DO					0x020

#define ADDR_OFFSET_DNC_SYNC_TRIG				0x024

#define ADDR_OFFSET_DNC_SYNC_STATUS				0x028
#define ADDR_OFFSET_DNC_SYNC_SET_MY_ID			0x030
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP00		0x040
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP01		0x044
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP02		0x048
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP03		0x04C
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP04		0x050
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP05		0x054
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP06		0x058
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP07		0x05C
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP08		0x060
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP09		0x064
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP10		0x068
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP11		0x06C
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP12		0x070
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP13		0x074
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP14		0x078
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP15		0x07C
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP16		0x080
#define ADDR_OFFSET_DNC_SYNC_TSYNC_MAP17		0x084
#define ADDR_OFFSET_DNC_SYNC_TSYNC_ADDR			0x088
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP00		0x0A0
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP01		0x0A4
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP02		0x0A8
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP03		0x0AC
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP04		0x0B0
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP05		0x0B4
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP06		0x0B8
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP07		0x0BC
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP08		0x0C0
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP09		0x0C4
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP10		0x0C8
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP11		0x0CC
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP12		0x0D0
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP13		0x0D4
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP14		0x0D8
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP15		0x0DC
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP16		0x0E0
#define ADDR_OFFSET_DNC_SYNC_ISYNC_MAP17		0x0E4
#define ADDR_OFFSET_DNC_SYNC_ISYNC_ADDR			0x0E8
#define ADDR_OFFSET_DNC_SYNC_ISYNC_DATA			0x0EC
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MAP00		0x100
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MAP01		0x104
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MAP02		0x108
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MAP03		0x10C
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MAP04		0x110
#define ADDR_OFFSET_DNC_SYNC_WSYNC_ADDR			0x114
#define ADDR_OFFSET_DNC_SYNC_WSYNC_DATA			0x118
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK0		0x11C
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK1		0x120
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK2		0x124
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK3		0x128
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK4		0x12C
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK5		0x130
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK6		0x134
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK7		0x138
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK4_OUT	0x13C
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK5_OUT	0x140
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK6_OUT	0x144
#define ADDR_OFFSET_DNC_SYNC_WSYNC_MASK7_OUT	0x148
#define ADDR_OFFSET_DNC_SYNC_TSYNC_LOG0			0x150
#define ADDR_OFFSET_DNC_SYNC_TSYNC_LOG1			0x154
#define ADDR_OFFSET_DNC_SYNC_TSYNC_LOG2			0x158
#define ADDR_OFFSET_DNC_SYNC_TSYNC_LOG3			0x15C
#define ADDR_OFFSET_DNC_SYNC_TSYNC_LOG4			0x160
#define ADDR_OFFSET_DNC_SYNC_TSYNC_LOG5			0x164
#define ADDR_OFFSET_DNC_SYNC_TSYNC_LOG6			0x168
#define ADDR_OFFSET_DNC_SYNC_TSYNC_LOG7			0x16C
#define ADDR_OFFSET_DNC_SYNC_PSYNC_LOG0			0x170
#define ADDR_OFFSET_DNC_SYNC_PSYNC_LOG1			0x174
#define ADDR_OFFSET_DNC_SYNC_PSYNC_LOG2			0x178
#define ADDR_OFFSET_DNC_SYNC_PSYNC_LOG3			0x17C
#define ADDR_OFFSET_DNC_SYNC_PSYNC_LOG4			0x180
#define ADDR_OFFSET_DNC_SYNC_PSYNC_LOG5			0x184
#define ADDR_OFFSET_DNC_SYNC_PSYNC_LOG6			0x188
#define ADDR_OFFSET_DNC_SYNC_PSYNC_LOG7			0x18C
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG_MODE0		0x19C
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG_MODE1		0x1A0
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG1_D0		0x1A4
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG2_D0		0x1A8
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG2_D1		0x1AC
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG4_D0		0x1B0
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG4_D1		0x1B4
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG4_D2		0x1B8
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG4_D3		0x1BC
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG8_D0		0x1C0
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG8_D1		0x1C4
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG8_D2		0x1C8
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG8_D3		0x1CC
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG8_D4		0x1D0
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG8_D5		0x1D4
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG8_D6		0x1D8
#define ADDR_OFFSET_DNC_SYNC_SEND_CFG8_D7		0x1DC
#define ADDR_OFFSET_DNC_SYNC_ACC_TSYNC_PASSAGE0 0x1F0
#define ADDR_OFFSET_DNC_SYNC_ACC_TSYNC_PASSAGE1 0x1F4
#define ADDR_OFFSET_DNC_SYNC_ACC_PSYNC_PASSAGE0 0x1F8
#define ADDR_OFFSET_DNC_SYNC_ACC_PSYNC_PASSAGE1 0x1FC

union dnc_sync_tsync_receive {
	struct __attribute__((packed)) {
		uint32_t dest_queue : 4;
		uint32_t rsvd4 : 4;
		uint32_t dest_group : 6;
		uint32_t rsvd14 : 2;
		uint32_t generator : 8;
		uint32_t src_dnc : 6;
		uint32_t src_queue : 2;
	} tsync_receive;
	uint32_t bits;
};

union dnc_sync_psync_receive {
	struct __attribute__((packed)) {
		uint32_t src_idx : 8;
		uint32_t src_unit : 2;
		uint32_t dest_idx : 8;
		uint32_t dest_unit : 2;
		uint32_t rsvd20 : 4;
		uint32_t sync_type : 8;
	} psync_receive;
	uint32_t bits;
};

union dnc_sync_tsync_force {
	struct __attribute__((packed)) {
		uint32_t code : 16;
		uint32_t cmd : 2;
		uint32_t group : 6;
		uint32_t rsvd24 : 6;
		uint32_t qbq_en : 1;
		uint32_t tkn_en : 1;
	};
	uint32_t bits;
};

union dnc_sync_do {
	struct __attribute__((packed)) {
		uint32_t en_tsync_qbq : 1;
		uint32_t en_tsync_tkn : 1;
		uint32_t en_psync_isync : 1;
		uint32_t en_psync_wsync : 1;
		uint32_t en_tsync_qbq_status : 1;
		uint32_t en_tsync_tkn_status : 1;
		uint32_t en_passage_log : 1;
		uint32_t en_passage_acc : 1;
		uint32_t rsvd26 : 24;
	};
	uint32_t bits;
};

#if EVT_VER == 1
#include "evt1/g_dnc_sync.h"
#else
#include "evt0/g_dnc_sync.h"
#endif

#if EVT_VER == 0
/* EVT0 version of dnc_sync_trig */
union dnc_sync_trig {
	struct __attribute__((packed)) {
		uint32_t clr_tsync : 1;
		uint32_t clr_psync : 1;
		uint32_t clr_passage_log : 1;
		uint32_t clr_passage_acc : 1;
		uint32_t rsvd4 : 28;
	};
	uint32_t bits;
};
#endif
/* EVT1 version is defined in evt1/g_dnc_sync.h */


union dnc_sync_status {
	struct __attribute__((packed)) {
		uint32_t rsvd : 32;
	};
	uint32_t bits;
};

union dnc_sync_set_my_id {
	struct __attribute__((packed)) {
		uint32_t tsync : 8;
		uint32_t isync : 8;
		uint32_t wsync : 8;
		uint32_t rsvd24 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map00 {
	struct __attribute__((packed)) {
		uint32_t dnc_00 : 8;
		uint32_t dnc_01 : 8;
		uint32_t dnc_02 : 8;
		uint32_t dnc_03 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map01 {
	struct __attribute__((packed)) {
		uint32_t dnc_04 : 8;
		uint32_t dnc_05 : 8;
		uint32_t dnc_06 : 8;
		uint32_t dnc_07 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map02 {
	struct __attribute__((packed)) {
		uint32_t dnc_08 : 8;
		uint32_t dnc_09 : 8;
		uint32_t dnc_10 : 8;
		uint32_t dnc_11 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map03 {
	struct __attribute__((packed)) {
		uint32_t dnc_12 : 8;
		uint32_t dnc_13 : 8;
		uint32_t dnc_14 : 8;
		uint32_t dnc_15 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map04 {
	struct __attribute__((packed)) {
		uint32_t dnc_16 : 8;
		uint32_t dnc_17 : 8;
		uint32_t dnc_18 : 8;
		uint32_t dnc_19 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map05 {
	struct __attribute__((packed)) {
		uint32_t dnc_20 : 8;
		uint32_t dnc_21 : 8;
		uint32_t dnc_22 : 8;
		uint32_t dnc_23 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map06 {
	struct __attribute__((packed)) {
		uint32_t dnc_24 : 8;
		uint32_t dnc_25 : 8;
		uint32_t dnc_26 : 8;
		uint32_t dnc_27 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map07 {
	struct __attribute__((packed)) {
		uint32_t dnc_28 : 8;
		uint32_t dnc_29 : 8;
		uint32_t dnc_30 : 8;
		uint32_t dnc_31 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map08 {
	struct __attribute__((packed)) {
		uint32_t dnc_32 : 8;
		uint32_t dnc_33 : 8;
		uint32_t dnc_34 : 8;
		uint32_t dnc_35 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map09 {
	struct __attribute__((packed)) {
		uint32_t dnc_36 : 8;
		uint32_t dnc_37 : 8;
		uint32_t dnc_38 : 8;
		uint32_t dnc_39 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map10 {
	struct __attribute__((packed)) {
		uint32_t dnc_40 : 8;
		uint32_t dnc_41 : 8;
		uint32_t dnc_42 : 8;
		uint32_t dnc_43 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map11 {
	struct __attribute__((packed)) {
		uint32_t dnc_44 : 8;
		uint32_t dnc_45 : 8;
		uint32_t dnc_46 : 8;
		uint32_t dnc_47 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map12 {
	struct __attribute__((packed)) {
		uint32_t dnc_48 : 8;
		uint32_t dnc_49 : 8;
		uint32_t dnc_50 : 8;
		uint32_t dnc_51 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map13 {
	struct __attribute__((packed)) {
		uint32_t dnc_52 : 8;
		uint32_t dnc_53 : 8;
		uint32_t dnc_54 : 8;
		uint32_t dnc_55 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map14 {
	struct __attribute__((packed)) {
		uint32_t dnc_56 : 8;
		uint32_t dnc_57 : 8;
		uint32_t dnc_58 : 8;
		uint32_t dnc_59 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map15 {
	struct __attribute__((packed)) {
		uint32_t dnc_60 : 8;
		uint32_t dnc_61 : 8;
		uint32_t dnc_62 : 8;
		uint32_t dnc_63 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map16 {
	struct __attribute__((packed)) {
		uint32_t dma_00 : 8;
		uint32_t dma_01 : 8;
		uint32_t dma_02 : 8;
		uint32_t dma_03 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_map17 {
	struct __attribute__((packed)) {
		uint32_t dma_04 : 8;
		uint32_t dma_05 : 8;
		uint32_t dma_06 : 8;
		uint32_t dma_07 : 8;
	};
	uint32_t bits;
};

union dnc_sync_tsync_addr {
	struct __attribute__((packed)) {
		uint32_t dnc : 16;
		uint32_t dma : 16;
	};
	uint32_t bits;
};

union dnc_sync_isync_map00 {
	struct __attribute__((packed)) {
		uint32_t idx_00 : 8;
		uint32_t idx_01 : 8;
		uint32_t idx_02 : 8;
		uint32_t idx_03 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map01 {
	struct __attribute__((packed)) {
		uint32_t idx_04 : 8;
		uint32_t idx_05 : 8;
		uint32_t idx_06 : 8;
		uint32_t idx_07 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map02 {
	struct __attribute__((packed)) {
		uint32_t idx_08 : 8;
		uint32_t idx_09 : 8;
		uint32_t idx_10 : 8;
		uint32_t idx_11 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map03 {
	struct __attribute__((packed)) {
		uint32_t idx_12 : 8;
		uint32_t idx_13 : 8;
		uint32_t idx_14 : 8;
		uint32_t idx_15 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map04 {
	struct __attribute__((packed)) {
		uint32_t idx_16 : 8;
		uint32_t idx_17 : 8;
		uint32_t idx_18 : 8;
		uint32_t idx_19 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map05 {
	struct __attribute__((packed)) {
		uint32_t idx_20 : 8;
		uint32_t idx_21 : 8;
		uint32_t idx_22 : 8;
		uint32_t idx_23 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map06 {
	struct __attribute__((packed)) {
		uint32_t idx_24 : 8;
		uint32_t idx_25 : 8;
		uint32_t idx_26 : 8;
		uint32_t idx_27 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map07 {
	struct __attribute__((packed)) {
		uint32_t idx_28 : 8;
		uint32_t idx_29 : 8;
		uint32_t idx_30 : 8;
		uint32_t idx_31 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map08 {
	struct __attribute__((packed)) {
		uint32_t idx_32 : 8;
		uint32_t idx_33 : 8;
		uint32_t idx_34 : 8;
		uint32_t idx_35 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map09 {
	struct __attribute__((packed)) {
		uint32_t idx_36 : 8;
		uint32_t idx_37 : 8;
		uint32_t idx_38 : 8;
		uint32_t idx_39 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map10 {
	struct __attribute__((packed)) {
		uint32_t idx_40 : 8;
		uint32_t idx_41 : 8;
		uint32_t idx_42 : 8;
		uint32_t idx_43 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map11 {
	struct __attribute__((packed)) {
		uint32_t idx_44 : 8;
		uint32_t idx_45 : 8;
		uint32_t idx_46 : 8;
		uint32_t idx_47 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map12 {
	struct __attribute__((packed)) {
		uint32_t idx_48 : 8;
		uint32_t idx_49 : 8;
		uint32_t idx_50 : 8;
		uint32_t idx_51 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map13 {
	struct __attribute__((packed)) {
		uint32_t idx_52 : 8;
		uint32_t idx_53 : 8;
		uint32_t idx_54 : 8;
		uint32_t idx_55 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map14 {
	struct __attribute__((packed)) {
		uint32_t idx_56 : 8;
		uint32_t idx_57 : 8;
		uint32_t idx_58 : 8;
		uint32_t idx_59 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map15 {
	struct __attribute__((packed)) {
		uint32_t idx_60 : 8;
		uint32_t idx_61 : 8;
		uint32_t idx_62 : 8;
		uint32_t idx_63 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map16 {
	struct __attribute__((packed)) {
		uint32_t idx_64 : 8;
		uint32_t idx_65 : 8;
		uint32_t idx_66 : 8;
		uint32_t idx_67 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_map17 {
	struct __attribute__((packed)) {
		uint32_t idx_68 : 8;
		uint32_t idx_69 : 8;
		uint32_t idx_70 : 8;
		uint32_t idx_71 : 8;
	};
	uint32_t bits;
};

union dnc_sync_isync_addr {
	struct __attribute__((packed)) {
		uint32_t dnc : 16;
		uint32_t dma : 16;
	};
	uint32_t bits;
};

union dnc_sync_isync_data {
	struct __attribute__((packed)) {
		uint32_t dma : 32;
	};
	uint32_t bits;
};

union dnc_sync_wsync_map00 {
	struct __attribute__((packed)) {
		uint32_t sig_00 : 8;
		uint32_t sig_01 : 8;
		uint32_t sig_02 : 8;
		uint32_t sig_03 : 8;
	};
	uint32_t bits;
};

union dnc_sync_wsync_map01 {
	struct __attribute__((packed)) {
		uint32_t sig_04 : 8;
		uint32_t sig_05 : 8;
		uint32_t sig_06 : 8;
		uint32_t sig_07 : 8;
	};
	uint32_t bits;
};

union dnc_sync_wsync_map02 {
	struct __attribute__((packed)) {
		uint32_t sig_08 : 8;
		uint32_t sig_09 : 8;
		uint32_t sig_10 : 8;
		uint32_t sig_11 : 8;
	};
	uint32_t bits;
};

union dnc_sync_wsync_map03 {
	struct __attribute__((packed)) {
		uint32_t sig_12 : 8;
		uint32_t sig_13 : 8;
		uint32_t sig_14 : 8;
		uint32_t sig_15 : 8;
	};
	uint32_t bits;
};

union dnc_sync_wsync_map04 {
	struct __attribute__((packed)) {
		uint32_t sig_16 : 8;
		uint32_t sig_17 : 8;
		uint32_t sig_18 : 8;
		uint32_t sig_19 : 8;
	};
	uint32_t bits;
};

union dnc_sync_wsync_addr {
	struct __attribute__((packed)) {
		uint32_t dnc : 16;
		uint32_t dma : 16;
	};
	uint32_t bits;
};

union dnc_sync_wsync_data {
	struct __attribute__((packed)) {
		uint32_t dma : 32;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask0 {
	struct __attribute__((packed)) {
		uint32_t nclu_put_sync_to_nclu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask1 {
	struct __attribute__((packed)) {
		uint32_t nclu_put_sync_to_ncsu : 20;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask2 {
	struct __attribute__((packed)) {
		uint32_t ncsu_put_sync_to_nclu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask3 {
	struct __attribute__((packed)) {
		uint32_t ncsu_put_sync_to_ncsu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask4 {
	struct __attribute__((packed)) {
		uint32_t nclu_get_sync_fr_nclu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask5 {
	struct __attribute__((packed)) {
		uint32_t nclu_get_sync_fr_ncsu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask6 {
	struct __attribute__((packed)) {
		uint32_t ncsu_get_sync_fr_nclu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask7 {
	struct __attribute__((packed)) {
		uint32_t ncsu_get_sync_fr_ncsu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask4_out {
	struct __attribute__((packed)) {
		uint32_t nclu_get_sync_fr_nclu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask5_out {
	struct __attribute__((packed)) {
		uint32_t nclu_get_sync_fr_ncsu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask6_out {
	struct __attribute__((packed)) {
		uint32_t ncsu_get_sync_fr_nclu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_wsync_mask7_out {
	struct __attribute__((packed)) {
		uint32_t ncsu_get_sync_fr_ncsu : 20;
		uint32_t rsvd20 : 12;
	};
	uint32_t bits;
};

union dnc_sync_tsync_log0 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_tsync_log1 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_tsync_log2 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_tsync_log3 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_tsync_log4 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_tsync_log5 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_tsync_log6 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_tsync_log7 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_psync_log0 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_psync_log1 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_psync_log2 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_psync_log3 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_psync_log4 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_psync_log5 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_psync_log6 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_psync_log7 {
	struct __attribute__((packed)) {
		uint32_t passage : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg_mode0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg_mode1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t rsvd8 : 8;
		uint32_t burst_len : 2;
		uint32_t rsvd18 : 14;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg1_d0 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg2_d0 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg2_d1 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg4_d0 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg4_d1 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg4_d2 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg4_d3 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg8_d0 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg8_d1 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg8_d2 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg8_d3 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg8_d4 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg8_d5 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg8_d6 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_send_cfg8_d7 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_sync_acc_tsync_passage0 {
	struct __attribute__((packed)) {
		uint32_t qbq : 32;
	};
	uint32_t bits;
};

union dnc_sync_acc_tsync_passage1 {
	struct __attribute__((packed)) {
		uint32_t token : 32;
	};
	uint32_t bits;
};

union dnc_sync_acc_psync_passage0 {
	struct __attribute__((packed)) {
		uint32_t wsync : 32;
	};
	uint32_t bits;
};

union dnc_sync_acc_psync_passage1 {
	struct __attribute__((packed)) {
		uint32_t isync : 32;
	};
	uint32_t bits;
};

enum dnc_sync_tsync_force_cmd {
	DNC_SYNC_TSYNC_FORCE_CMD_GCLR,
	DNC_SYNC_TSYNC_FORCE_CMD_CFRC,
};

enum dnc_sync_send_cfg_mode1_burst_len {
	DNC_SYNC_SEND_CFG_MODE1_BURST_LEN_BL1,
	DNC_SYNC_SEND_CFG_MODE1_BURST_LEN_BL2,
	DNC_SYNC_SEND_CFG_MODE1_BURST_LEN_BL4,
	DNC_SYNC_SEND_CFG_MODE1_BURST_LEN_BL8,
};

#endif /* _G_DNC_SYNC_COMMON_H_*/
