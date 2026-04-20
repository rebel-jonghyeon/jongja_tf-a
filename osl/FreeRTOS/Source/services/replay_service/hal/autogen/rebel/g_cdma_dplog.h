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

#ifndef _G_CDMA_DPLOG_COMMON_H_
#define _G_CDMA_DPLOG_COMMON_H_

#define ADDR_OFFSET_RBDMA_CLOG_CLEAR			   0x000
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC0 0x004
#define ADDR_OFFSET_RBDMA_CLOG_NUM_URG_TDONE_TSTC0 0x008
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC1 0x00C
#define ADDR_OFFSET_RBDMA_CLOG_NUM_URG_TDONE_TSTC1 0x010
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC2 0x014
#define ADDR_OFFSET_RBDMA_CLOG_NUM_URG_TDONE_TSTC2 0x018
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC3 0x01C
#define ADDR_OFFSET_RBDMA_CLOG_NUM_URG_TDONE_TSTC3 0x020
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC4 0x024
#define ADDR_OFFSET_RBDMA_CLOG_NUM_URG_TDONE_TSTC4 0x028
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC5 0x02C
#define ADDR_OFFSET_RBDMA_CLOG_NUM_URG_TDONE_TSTC5 0x030
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC6 0x034
#define ADDR_OFFSET_RBDMA_CLOG_NUM_URG_TDONE_TSTC6 0x038
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC7 0x03C
#define ADDR_OFFSET_RBDMA_CLOG_NUM_URG_TDONE_TSTC7 0x040
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED6		   0x044
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED7		   0x048
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED0		   0x04C
#define ADDR_OFFSET_RBDMA_CLOG_STATUS_QUEUES	   0x050
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NT_QUEUEIN	   0x054
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NT_QUEUEOUT	   0x058
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NTE_QUEUEIN	   0x05C
#define ADDR_OFFSET_RBDMA_CLOG_NUM_NTE_QUEUEOUT	   0x060
#define ADDR_OFFSET_RBDMA_CLOG_NUM_PT_QUEUEIN	   0x064
#define ADDR_OFFSET_RBDMA_CLOG_NUM_PT_QUEUEOUT	   0x068
#define ADDR_OFFSET_RBDMA_CLOG_NUM_UT_QUEUEIN	   0x06C
#define ADDR_OFFSET_RBDMA_CLOG_NUM_UT_QUEUEOUT	   0x070
#define ADDR_OFFSET_RBDMA_CLOG_NUM_UTE_QUEUEIN	   0x074
#define ADDR_OFFSET_RBDMA_CLOG_NUM_UTE_QUEUEOUT	   0x078
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED1		   0x07C
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED2		   0x080
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED3		   0x084
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED4		   0x088
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED5		   0x08C
#define ADDR_OFFSET_RBDMA_CLOG_NUM_TSYNC_GET	   0x090
#define ADDR_OFFSET_RBDMA_CLOG_NUM_TSYNC_PUT	   0x094
#define ADDR_OFFSET_RBDMA_CLOG_NUM_TSYNC_TASK	   0x098
#define ADDR_OFFSET_RBDMA_CLOG_NUM_TSYNC_REL	   0x09C
#define ADDR_OFFSET_RBDMA_CLOG_NUM_LSYNC_PUT	   0x0A0
#define ADDR_OFFSET_RBDMA_CLOG_NUM_LSYNC_REL	   0x0A4
#define ADDR_OFFSET_RBDMA_CLOG_NUM_LSYNC_TASK	   0x0A8
#define ADDR_OFFSET_RBDMA_CLOG_NUM_RLSYNC_PUT	   0x0AC
#define ADDR_OFFSET_RBDMA_CLOG_NUM_RLSYNC_REL	   0x0B0
#define ADDR_OFFSET_RBDMA_CLOG_NUM_RLSYNC_TASK	   0x0B4
#define ADDR_OFFSET_RBDMA_CLOG_NUM_RLSYNC_GET	   0x0B8
#define ADDR_OFFSET_RBDMA_CLOG_NUM_MP_LSYNC_PUT	   0x0BC
#define ADDR_OFFSET_RBDMA_CLOG_NUM_MP_LSYNC_REL	   0x0C0
#define ADDR_OFFSET_RBDMA_CLOG_NUM_MP_LSYNC_TASK   0x0C4
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED13		   0x0C8
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED14		   0x0CC
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED15		   0x0D0
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED16		   0x0D4
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED17		   0x0D8
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED18		   0x0DC
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED19		   0x0E0
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED20		   0x0E4
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED21		   0x0E8
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED22		   0x0EC
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED23		   0x0F0
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED24		   0x0F4
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED25		   0x0F8
#define ADDR_OFFSET_RBDMA_CLOG_RESERVED26		   0x0FC
#define ADDR_OFFSET_RBDMA_VERSION				   0x100
#define ADDR_OFFSET_RBDMA_RELEASE				   0x104
#define ADDR_OFFSET_RBDMA_RESERVED0				   0x108
#define ADDR_OFFSET_RBDMA_RESERVED1				   0x10C
#define ADDR_OFFSET_RBDMA_CONTROL				   0x110
#define ADDR_OFFSET_RBDMA_CONFIG				   0x114
#define ADDR_OFFSET_RBDMA_EVENT_MASK			   0x118
#define ADDR_OFFSET_RBDMA_DUMP_DEST0			   0x11C
#define ADDR_OFFSET_RBDMA_DUMP_DEST1			   0x120
#define ADDR_OFFSET_RBDMA_DUMP_SIZE				   0x124
#define ADDR_OFFSET_RBDMA_RESERVED2				   0x128
#define ADDR_OFFSET_RBDMA_RESERVED3				   0x12C
#define ADDR_OFFSET_RBDMA_STATUS0				   0x130
#define ADDR_OFFSET_RBDMA_STATUS1				   0x134
#define ADDR_OFFSET_RBDMA_DUMP_STATUS			   0x138
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED2		   0x13C
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED3		   0x140
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED4		   0x144
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED5		   0x148
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED6		   0x14C
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED7		   0x150
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED8		   0x154
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED9		   0x158
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED10	   0x15C
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED11	   0x160
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED12	   0x164
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED13	   0x168
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED14	   0x16C
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED15	   0x170
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED16	   0x174
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED17	   0x178
#define ADDR_OFFSET_RBDMA_CLOG_LM_RESERVED18	   0x17C

enum rbdma_config_full_policy {
	RBDMA_CONFIG_FULL_POLICY_DISC,
	RBDMA_CONFIG_FULL_POLICY_OVWR,
};

union rbdma_clog_clear {
	struct __attribute__((packed)) {
		uint32_t clear : 1;
		uint32_t reserved : 31;
	};
	uint32_t bits;
};

union rbdma_clog_num_nrm_tdone_tstc0 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_urg_tdone_tstc0 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nrm_tdone_tstc1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_urg_tdone_tstc1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nrm_tdone_tstc2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_urg_tdone_tstc2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nrm_tdone_tstc3 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_urg_tdone_tstc3 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nrm_tdone_tstc4 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_urg_tdone_tstc4 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nrm_tdone_tstc5 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_urg_tdone_tstc5 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nrm_tdone_tstc6 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_urg_tdone_tstc6 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nrm_tdone_tstc7 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_urg_tdone_tstc7 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved6 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved7 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved0 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_status_queues {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nt_queuein {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nt_queueout {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nte_queuein {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_nte_queueout {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_pt_queuein {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_pt_queueout {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_ut_queuein {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_ut_queueout {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_ute_queuein {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_ute_queueout {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved3 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved4 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved5 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_tsync_get {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_tsync_put {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_tsync_task {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_tsync_rel {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_lsync_put {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_lsync_rel {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_lsync_task {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_rlsync_put {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_rlsync_rel {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_rlsync_task {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_rlsync_get {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_mp_lsync_put {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_mp_lsync_rel {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_num_mp_lsync_task {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved13 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved14 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved15 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved16 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved17 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved18 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved19 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved20 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved21 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved22 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved23 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved24 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved25 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_reserved26 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_version {
	struct __attribute__((packed)) {
		uint32_t id : 16;
		uint32_t major : 8;
		uint32_t minor : 8;
	};
	uint32_t bits;
};

union rbdma_release {
	struct __attribute__((packed)) {
		uint32_t date : 32;
	};
	uint32_t bits;
};

union rbdma_reserved0 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_reserved1 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_control {
	struct __attribute__((packed)) {
		uint32_t enable : 1;
		uint32_t reset_timer : 1;
		uint32_t clear_buffer : 1;
		uint32_t reset_dump : 1;
		uint32_t reserved : 28;
	};
	uint32_t bits;
};

union rbdma_config {
	struct __attribute__((packed)) {
		uint32_t full_policy : 1;
		uint32_t reserved : 15;
		uint32_t rsln : 16;
	};
	uint32_t bits;
};

union rbdma_event_mask {
	struct __attribute__((packed)) {
		uint32_t enbl_evt00 : 1;
		uint32_t enbl_evt01 : 1;
		uint32_t enbl_evt02 : 1;
		uint32_t enbl_evt03 : 1;
		uint32_t enbl_evt04 : 1;
		uint32_t enbl_evt05 : 1;
		uint32_t enbl_evt06 : 1;
		uint32_t enbl_evt07 : 1;
		uint32_t enbl_evt08 : 1;
		uint32_t enbl_evt09 : 1;
		uint32_t enbl_evt10 : 1;
		uint32_t enbl_evt11 : 1;
		uint32_t enbl_evt12 : 1;
		uint32_t enbl_evt13 : 1;
		uint32_t enbl_evt14 : 1;
		uint32_t enbl_evt15 : 1;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union rbdma_dump_dest0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union rbdma_dump_dest1 {
	struct __attribute__((packed)) {
		uint32_t addr : 8;
		uint32_t reserved : 24;
	};
	uint32_t bits;
};

union rbdma_dump_size {
	struct __attribute__((packed)) {
		uint32_t size : 16;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union rbdma_reserved2 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_reserved3 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_status0 {
	struct __attribute__((packed)) {
		uint32_t exception : 2;
		uint32_t num_valid : 6;
		uint32_t reserved : 24;
	};
	uint32_t bits;
};

union rbdma_status1 {
	struct __attribute__((packed)) {
		uint32_t num_log : 16;
		uint32_t num_full : 16;
	};
	uint32_t bits;
};

union rbdma_dump_status {
	struct __attribute__((packed)) {
		uint32_t dump_count : 16;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved3 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved4 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved5 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved6 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved7 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved8 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved9 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved10 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved11 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved12 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved13 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved14 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved15 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved16 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved17 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_lm_reserved18 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

#endif /* _G_CDMA_DPLOG_COMMON_H_*/
