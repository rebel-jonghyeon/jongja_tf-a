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

#ifndef _G_CDMA_TSYNC_REGISTERS_COMMON_H_
#define _G_CDMA_TSYNC_REGISTERS_COMMON_H_

#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_LVL_DNC			0x000
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_BASEADDR		0x004
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_L1STEP			0x008
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_L2STEP			0x00C
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_L3STEP			0x010
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_RESERVED0		0x014
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_RESERVED1		0x018
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_RESERVED2		0x01C
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_TSYNC_OFFSET	0x020
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_GET_INFO			0x024
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_RESERVED3		0x028
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_RESERVED4		0x02C
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_RESERVED5		0x030
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_RESERVED6		0x034
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_RESERVED7		0x038
#define ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_RESERVED8		0x03C
#define ADDR_OFFSET_RBDMA_TSYNC_STATUS_DPDC_GRP_0_31	0x040
#define ADDR_OFFSET_RBDMA_TSYNC_STATUS_DPDC_GRP_32_63	0x044
#define ADDR_OFFSET_RBDMA_TSYNC_STATUS_DPDC_GRP_64_95	0x048
#define ADDR_OFFSET_RBDMA_TSYNC_STATUS_DPDC_GRP_96_127	0x04C
#define ADDR_OFFSET_RBDMA_TSYNC_STATUS_DPDC_GRP_128_159 0x050
#define ADDR_OFFSET_RBDMA_TSYNC_STATUS_DPDC_GRP_160_191 0x054
#define ADDR_OFFSET_RBDMA_TSYNC_STATUS_DPDC_GRP_192_223 0x058
#define ADDR_OFFSET_RBDMA_TSYNC_STATUS_DPDC_GRP_224_255 0x05C

union rbdma_tsync_dnc_cfg_lvl_dnc {
	struct __attribute__((packed)) {
		uint32_t l1_dnc_num : 8;
		uint32_t l2_dnc_num : 8;
		uint32_t l3_dnc_num : 8;
		uint32_t reserved : 8;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_baseaddr {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_l1step {
	struct __attribute__((packed)) {
		uint32_t dnc : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_l2step {
	struct __attribute__((packed)) {
		uint32_t dnc4 : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_l3step {
	struct __attribute__((packed)) {
		uint32_t dcluster : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_reserved0 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_reserved1 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_reserved2 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_tsync_offset {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_get_info {
	struct __attribute__((packed)) {
		uint32_t dncid : 7;
		uint32_t reserved0 : 1;
		uint32_t gidx : 5;
		uint32_t reserved1 : 3;
		uint32_t p_taskid : 16;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_reserved3 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_reserved4 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_reserved5 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_reserved6 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_reserved7 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_dnc_cfg_reserved8 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_status_dpdc_grp_0_31 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_status_dpdc_grp_32_63 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_status_dpdc_grp_64_95 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_status_dpdc_grp_96_127 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_status_dpdc_grp_128_159 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_status_dpdc_grp_160_191 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_status_dpdc_grp_192_223 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tsync_status_dpdc_grp_224_255 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

#endif /* _G_CDMA_TSYNC_REGISTERS_COMMON_H_*/
