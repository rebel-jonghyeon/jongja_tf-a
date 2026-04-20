/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2024 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _G_CDMA_PT_REGISTERS_COMMON_H_
#define _G_CDMA_PT_REGISTERS_COMMON_H_

#define ADDR_OFFSET_RBDMA_PT_V2P_0		0x000
#define ADDR_OFFSET_RBDMA_PT_V2P_1		0x004
#define ADDR_OFFSET_RBDMA_PT_V2P_2		0x008
#define ADDR_OFFSET_RBDMA_PT_V2P_3		0x00C
#define ADDR_OFFSET_RBDMA_PT_V2P_4		0x010
#define ADDR_OFFSET_RBDMA_PT_V2P_5		0x014
#define ADDR_OFFSET_RBDMA_PT_V2P_6		0x018
#define ADDR_OFFSET_RBDMA_PT_V2P_7		0x01C
#define ADDR_OFFSET_RBDMA_PT_V2P_8		0x020
#define ADDR_OFFSET_RBDMA_PT_V2P_9		0x024
#define ADDR_OFFSET_RBDMA_PT_V2P_10		0x028
#define ADDR_OFFSET_RBDMA_PT_V2P_11		0x02C
#define ADDR_OFFSET_RBDMA_PT_V2P_12		0x030
#define ADDR_OFFSET_RBDMA_PT_V2P_13		0x034
#define ADDR_OFFSET_RBDMA_PT_V2P_14		0x038
#define ADDR_OFFSET_RBDMA_PT_V2P_15		0x03C
#define ADDR_OFFSET_RBDMA_PT_MSB_0_3	0x040
#define ADDR_OFFSET_RBDMA_PT_MSB_4_7	0x044
#define ADDR_OFFSET_RBDMA_PT_MSB_8_11	0x048
#define ADDR_OFFSET_RBDMA_PT_MSB_12_15	0x04C
#define ADDR_OFFSET_RBDMA_PT_INFO		0x050
#define ADDR_OFFSET_RBDMA_PT_NUM		0x054
#define ADDR_OFFSET_RBDMA_PT_RESERVED1	0x058
#define ADDR_OFFSET_RBDMA_PT_RESERVED2	0x05C
#define ADDR_OFFSET_RBDMA_PT_RESERVED3	0x060
#define ADDR_OFFSET_RBDMA_PT_RESERVED4	0x064
#define ADDR_OFFSET_RBDMA_PT_RESERVED5	0x068
#define ADDR_OFFSET_RBDMA_PT_RESERVED6	0x06C
#define ADDR_OFFSET_RBDMA_PT_RESERVED7	0x070
#define ADDR_OFFSET_RBDMA_PT_RESERVED8	0x074
#define ADDR_OFFSET_RBDMA_PT_RESERVED9	0x078
#define ADDR_OFFSET_RBDMA_PT_RESERVED10 0x07C

union rbdma_pt_v2p_0 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_3 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_4 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_5 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_6 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_7 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_8 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_9 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_10 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_11 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_12 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_13 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_14 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_v2p_15 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_msb_0_3 {
	struct __attribute__((packed)) {
		uint32_t pt0_pa_msb4b : 4;
		uint32_t pt0_va_msb4b : 4;
		uint32_t pt1_pa_msb4b : 4;
		uint32_t pt1_va_msb4b : 4;
		uint32_t pt2_pa_msb4b : 4;
		uint32_t pt2_va_msb4b : 4;
		uint32_t pt3_pa_msb4b : 4;
		uint32_t pt3_va_msb4b : 4;
	};
	uint32_t bits;
};

union rbdma_pt_msb_4_7 {
	struct __attribute__((packed)) {
		uint32_t pt4_pa_msb4b : 4;
		uint32_t pt4_va_msb4b : 4;
		uint32_t pt5_pa_msb4b : 4;
		uint32_t pt5_va_msb4b : 4;
		uint32_t pt6_pa_msb4b : 4;
		uint32_t pt6_va_msb4b : 4;
		uint32_t pt7_pa_msb4b : 4;
		uint32_t pt7_va_msb4b : 4;
	};
	uint32_t bits;
};

union rbdma_pt_msb_8_11 {
	struct __attribute__((packed)) {
		uint32_t pt8_pa_msb4b : 4;
		uint32_t pt8_va_msb4b : 4;
		uint32_t pt9_pa_msb4b : 4;
		uint32_t pt9_va_msb4b : 4;
		uint32_t pt10_pa_msb4b : 4;
		uint32_t pt10_va_msb4b : 4;
		uint32_t pt11_pa_msb4b : 4;
		uint32_t pt11_va_msb4b : 4;
	};
	uint32_t bits;
};

union rbdma_pt_msb_12_15 {
	struct __attribute__((packed)) {
		uint32_t pt12_pa_msb4b : 4;
		uint32_t pt12_va_msb4b : 4;
		uint32_t pt13_pa_msb4b : 4;
		uint32_t pt13_va_msb4b : 4;
		uint32_t pt14_pa_msb4b : 4;
		uint32_t pt14_va_msb4b : 4;
		uint32_t pt15_pa_msb4b : 4;
		uint32_t pt15_va_msb4b : 4;
	};
	uint32_t bits;
};

union rbdma_pt_info {
	struct __attribute__((packed)) {
		uint32_t func_id : 4;
		uint32_t ctx_id : 8;
		uint32_t thread_id : 4;
		uint32_t cmd_id : 16;
	};
	uint32_t bits;
};

union rbdma_pt_num {
	struct __attribute__((packed)) {
		uint32_t num_of_pt : 5;
		uint32_t reserved0 : 3;
		uint32_t vaddr_granule : 4;
		uint32_t reserved1 : 19;
		uint32_t queue_type : 1;
	};
	uint32_t bits;
};

union rbdma_pt_reserved1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_reserved2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_reserved3 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_reserved4 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_reserved5 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_reserved6 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_reserved7 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_reserved8 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_reserved9 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_pt_reserved10 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

#endif /* _G_CDMA_PT_REGISTERS_COMMON_H_*/
