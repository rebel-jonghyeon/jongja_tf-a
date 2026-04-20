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

#ifndef _G_EDMA_BUSPROFILE_COMMON_H_
#define _G_EDMA_BUSPROFILE_COMMON_H_

#define ADDR_OFFSET_RBDMA_BP_IP_INFO0		  0x00
#define ADDR_OFFSET_RBDMA_BP_IP_INFO1		  0x04
#define ADDR_OFFSET_RBDMA_BP_IP_INFO2		  0x08
#define ADDR_OFFSET_RBDMA_BP_IP_INFO3		  0x0C
#define ADDR_OFFSET_RBDMA_BP_IP_INFO4		  0x10
#define ADDR_OFFSET_RBDMA_BP_IP_INFO5		  0x14
#define ADDR_OFFSET_RBDMA_BP_IP_INFO6		  0x18
#define ADDR_OFFSET_RBDMA_BP_IP_INFO7		  0x1C
#define ADDR_OFFSET_RBDMA_BP_CONFIGURE_EN	  0x20
#define ADDR_OFFSET_RBDMA_BP_CLEAR_SET		  0x24
#define ADDR_OFFSET_RBDMA_BP_CONFIGURE_PERIOD 0x28
#define ADDR_OFFSET_RBDMA_BP_CONFIGURE_FLUSH  0x2C
#define ADDR_OFFSET_RBDMA_BP_CONFIGURE_TRGT01 0x30
#define ADDR_OFFSET_RBDMA_BP_CONFIGURE_TRGT23 0x34
#define ADDR_OFFSET_RBDMA_BP_RESERVED_15	  0x38
#define ADDR_OFFSET_RBDMA_BP_MON_STATUS		  0x3C
#define ADDR_OFFSET_RBDMA_PROFILE_PKG0		  0x40
#define ADDR_OFFSET_RBDMA_PROFILE_PKG1		  0x44
#define ADDR_OFFSET_RBDMA_PROFILE_PKG2		  0x48
#define ADDR_OFFSET_RBDMA_PROFILE_PKG3		  0x4C
#define ADDR_OFFSET_RBDMA_PROFILE_PKG4		  0x50
#define ADDR_OFFSET_RBDMA_PROFILE_PKG5		  0x54
#define ADDR_OFFSET_RBDMA_PROFILE_PKG6		  0x58
#define ADDR_OFFSET_RBDMA_PROFILE_PKG7		  0x5C
#define ADDR_OFFSET_RBDMA_PROFILE_PKG8		  0x60
#define ADDR_OFFSET_RBDMA_PROFILE_PKG9		  0x64
#define ADDR_OFFSET_RBDMA_PROFILE_PKG10		  0x68
#define ADDR_OFFSET_RBDMA_PROFILE_PKG11		  0x6C
#define ADDR_OFFSET_RBDMA_PROFILE_PKG12		  0x70
#define ADDR_OFFSET_RBDMA_PROFILE_PKG13		  0x74
#define ADDR_OFFSET_RBDMA_PROFILE_PKG14		  0x78
#define ADDR_OFFSET_RBDMA_PROFILE_PKG15		  0x7C

union rbdma_bp_ip_info0 {
	struct __attribute__((packed)) {
		uint32_t rel_date : 32;
	};
	uint32_t bits;
};

union rbdma_bp_ip_info1 {
	struct __attribute__((packed)) {
		uint32_t min_ver : 8;
		uint32_t maj_ver : 8;
		uint32_t busprofiler_ver : 8;
		uint32_t reserved : 8;
	};
	uint32_t bits;
};

union rbdma_bp_ip_info2 {
	struct __attribute__((packed)) {
		uint32_t target_num : 32;
	};
	uint32_t bits;
};

union rbdma_bp_ip_info3 {
	struct __attribute__((packed)) {
		uint32_t min_conf_time : 32;
	};
	uint32_t bits;
};

union rbdma_bp_ip_info4 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_bp_ip_info5 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_bp_ip_info6 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_bp_ip_info7 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_bp_configure_en {
	struct __attribute__((packed)) {
		uint32_t read_mon_en : 1;
		uint32_t write_mon_en : 1;
		uint32_t target0_en : 1;
		uint32_t target1_en : 1;
		uint32_t target2_en : 1;
		uint32_t target3_en : 1;
		uint32_t reserved : 26;
	};
	uint32_t bits;
};

union rbdma_bp_clear_set {
	struct __attribute__((packed)) {
		uint32_t requeue : 1;
		uint32_t profile_reg : 1;
		uint32_t profile_fifo : 1;
		uint32_t status : 1;
		uint32_t sequence_idx : 1;
		uint32_t reserved : 27;
	};
	uint32_t bits;
};

union rbdma_bp_configure_period {
	struct __attribute__((packed)) {
		uint32_t sampling_period : 32;
	};
	uint32_t bits;
};

union rbdma_bp_configure_flush {
	struct __attribute__((packed)) {
		uint32_t start : 1;
		uint32_t reserved : 31;
	};
	uint32_t bits;
};

union rbdma_bp_configure_trgt01 {
	struct __attribute__((packed)) {
		uint32_t trgt0_offset_exp : 4;
		uint32_t trgt0_intv_exp : 4;
		uint32_t trgt0_cntup_exp : 3;
		uint32_t reserved11 : 5;
		uint32_t trgt1_offset_exp : 4;
		uint32_t trgt1_intv_exp : 4;
		uint32_t trgt1_cntup_exp : 3;
		uint32_t reserved27 : 5;
	};
	uint32_t bits;
};

union rbdma_bp_configure_trgt23 {
	struct __attribute__((packed)) {
		uint32_t trgt2_offset_exp : 4;
		uint32_t trgt2_intv_exp : 4;
		uint32_t trgt2_cntup_exp : 3;
		uint32_t reserved11 : 5;
		uint32_t trgt3_offset_exp : 4;
		uint32_t trgt3_intv_exp : 4;
		uint32_t trgt3_cntup_exp : 3;
		uint32_t reserved27 : 5;
	};
	uint32_t bits;
};

union rbdma_bp_reserved_15 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_bp_mon_status {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg0 {
	struct __attribute__((packed)) {
		uint32_t header_0 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg1 {
	struct __attribute__((packed)) {
		uint32_t header_1 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg2 {
	struct __attribute__((packed)) {
		uint32_t data_0 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg3 {
	struct __attribute__((packed)) {
		uint32_t data_1 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg4 {
	struct __attribute__((packed)) {
		uint32_t data_2 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg5 {
	struct __attribute__((packed)) {
		uint32_t data_3 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg6 {
	struct __attribute__((packed)) {
		uint32_t data_4 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg7 {
	struct __attribute__((packed)) {
		uint32_t data_5 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg8 {
	struct __attribute__((packed)) {
		uint32_t data_6 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg9 {
	struct __attribute__((packed)) {
		uint32_t data_7 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg10 {
	struct __attribute__((packed)) {
		uint32_t data_8 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg11 {
	struct __attribute__((packed)) {
		uint32_t data_9 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg12 {
	struct __attribute__((packed)) {
		uint32_t data_10 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg13 {
	struct __attribute__((packed)) {
		uint32_t data_11 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg14 {
	struct __attribute__((packed)) {
		uint32_t data_12 : 32;
	};
	uint32_t bits;
};

union rbdma_profile_pkg15 {
	struct __attribute__((packed)) {
		uint32_t data_13 : 32;
	};
	uint32_t bits;
};

#endif /* _G_EDMA_BUSPROFILE_COMMON_H_*/
