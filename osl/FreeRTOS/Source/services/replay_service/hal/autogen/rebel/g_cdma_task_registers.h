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

#ifndef _G_CDMA_TASK_REGISTERS_COMMON_H_
#define _G_CDMA_TASK_REGISTERS_COMMON_H_

#define ADDR_OFFSET_RBDMA_TD_PTID_INIT				   0x0
#define ADDR_OFFSET_RBDMA_TD_SRCADDRESS_OR_CONST	   0x4
#define ADDR_OFFSET_RBDMA_TD_DESTADDRESS			   0x8
#define ADDR_OFFSET_RBDMA_TD_SIZEOF128BLOCK			   0xC
#define ADDR_OFFSET_RBDMA_TD_TSYNC_CONF_MASK		   0x10
#define ADDR_OFFSET_RBDMA_TD_SYNC_CONF_GIDX			   0x14
#define ADDR_OFFSET_RBDMA_TD_RUN_CONF0				   0x18
#define ADDR_OFFSET_RBDMA_TD_RUN_CONF1				   0x1C
#define ADDR_OFFSET_RBDMA_TDE_CHK_BASE_ADDR_MSB		   0x20
#define ADDR_OFFSET_RBDMA_TDE_CHK1_BASE_ADDR_OR_STRIDE 0x24
#define ADDR_OFFSET_RBDMA_TDE_CHK1_SIZE				   0x28
#define ADDR_OFFSET_RBDMA_TDE_CHK2_BASE_ADDR		   0x2C
#define ADDR_OFFSET_RBDMA_TDE_CHK2_SIZE				   0x30
#define ADDR_OFFSET_RBDMA_TDE_CHK3_BASE_ADDR		   0x34
#define ADDR_OFFSET_RBDMA_TDE_CHK3_SIZE				   0x38
#define ADDR_OFFSET_RBDMA_TDE_CHK4_BASE_ADDR		   0x3C
#define ADDR_OFFSET_RBDMA_TDE_CHK4_SIZE				   0x40
#define ADDR_OFFSET_RBDMA_TDE_CHK5_BASE_ADDR		   0x44
#define ADDR_OFFSET_RBDMA_TDE_CHK5_SIZE				   0x48
#define ADDR_OFFSET_RBDMA_TDE_CHK6_BASE_ADDR		   0x4C
#define ADDR_OFFSET_RBDMA_TDE_CHK6_SIZE				   0x50
#define ADDR_OFFSET_RBDMA_TDE_CHK7_BASE_ADDR		   0x54
#define ADDR_OFFSET_RBDMA_TDE_CHK7_SIZE				   0x58
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK1		   0x5C
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK2		   0x60
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK3		   0x64
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK4_RSV	   0x68
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK5_RSV	   0x6C
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK6_RSV	   0x70
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK7_RSV	   0x74
#define ADDR_OFFSET_RBDMA_TDE_RLSYNC_CONF_MASK		   0x78
#define ADDR_OFFSET_RBDMA_TDE_DONERPT_MST			   0x7C
#define ADDR_OFFSET_RBDMA_TD_RUN_CONF_EXT			   0x80

union rbdma_td_ptid_init {
	struct __attribute__((packed)) {
		uint32_t func_id : 4;
		uint32_t ctx_id : 8;
		uint32_t thread_id : 4;
		uint32_t cmd_id : 16;
	};
	uint32_t bits;
};

union rbdma_td_srcaddress_or_const {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_td_destaddress {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_td_sizeof128block {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_td_tsync_conf_mask {
	struct __attribute__((packed)) {
		uint32_t get_dnc_mask : 16;
		uint32_t put_dnc_mask : 16;
	};
	uint32_t bits;
};

union rbdma_td_sync_conf_gidx {
	struct __attribute__((packed)) {
		uint32_t get_tsync_gidx : 7;
		uint32_t get_tsync_en : 1;
		uint32_t put_tsync_gidx : 7;
		uint32_t put_tsync_en : 1;
		uint32_t get_lsync_gidx : 6;
		uint32_t get_lsync_en : 1;
		uint32_t get_rlsync_en : 1;
		uint32_t put_lsync_gidx : 6;
		uint32_t put_lsync_en : 1;
		uint32_t put_rlsync_en : 1;
	};
	uint32_t bits;
};

union rbdma_td_run_conf0 {
	struct __attribute__((packed)) {
		uint32_t task_type : 4;
		uint32_t split_granule_l2 : 4;
		uint32_t ext_num_of_chunk : 12;
		uint32_t src_addr_msb : 2;
		uint32_t dst_addr_msb : 2;
		uint32_t tsync_dnc_code : 4;
		uint32_t ext_dnc_mask : 3;
		uint32_t fid_max : 1;
	};
	uint32_t bits;
};

union rbdma_td_run_conf1 {
	struct __attribute__((packed)) {
		uint32_t intr_disable : 1;
		uint32_t en_donerpt_mst : 1;
		uint32_t en_invalid_pt : 1;
		uint32_t no_tlb : 1;
		uint32_t map_lvl : 2;
		uint32_t iv_lvl : 2;
		uint32_t ptnum_or_v2pnum : 8;
		uint32_t read_bl : 2;
		uint32_t write_bl : 2;
		uint32_t te_mask : 8;
		uint32_t read_qos : 1;
		uint32_t write_qos : 1;
		uint32_t td_mst : 1;
		uint32_t queue_type : 1;
	};
	uint32_t bits;
};

union rbdma_tde_chk_base_addr_msb {
	struct __attribute__((packed)) {
		uint32_t chk1_stride_msb : 2;
		uint32_t chk2_msb : 2;
		uint32_t chk3_msb : 2;
		uint32_t chk4_msb : 2;
		uint32_t chk5_msb : 2;
		uint32_t chk6_msb : 2;
		uint32_t chk7_msb : 2;
		uint32_t reserved : 18;
	};
	uint32_t bits;
};

union rbdma_tde_chk1_base_addr_or_stride {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk1_size {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk2_base_addr {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk2_size {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk3_base_addr {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk3_size {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk4_base_addr {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk4_size {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk5_base_addr {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk5_size {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk6_base_addr {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk6_size {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk7_base_addr {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_chk7_size {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_tde_tsync_conf_mask1 {
	struct __attribute__((packed)) {
		uint32_t get_dnc_mask : 16;
		uint32_t put_dnc_mask : 16;
	};
	uint32_t bits;
};

union rbdma_tde_tsync_conf_mask2 {
	struct __attribute__((packed)) {
		uint32_t get_dnc_mask : 16;
		uint32_t put_dnc_mask : 16;
	};
	uint32_t bits;
};

union rbdma_tde_tsync_conf_mask3 {
	struct __attribute__((packed)) {
		uint32_t get_dnc_mask : 16;
		uint32_t put_dnc_mask : 16;
	};
	uint32_t bits;
};

union rbdma_tde_tsync_conf_mask4_rsv {
	struct __attribute__((packed)) {
		uint32_t get_dnc_mask : 16;
		uint32_t put_dnc_mask : 16;
	};
	uint32_t bits;
};

union rbdma_tde_tsync_conf_mask5_rsv {
	struct __attribute__((packed)) {
		uint32_t get_dnc_mask : 16;
		uint32_t put_dnc_mask : 16;
	};
	uint32_t bits;
};

union rbdma_tde_tsync_conf_mask6_rsv {
	struct __attribute__((packed)) {
		uint32_t get_dnc_mask : 16;
		uint32_t put_dnc_mask : 16;
	};
	uint32_t bits;
};

union rbdma_tde_tsync_conf_mask7_rsv {
	struct __attribute__((packed)) {
		uint32_t get_dnc_mask : 16;
		uint32_t put_dnc_mask : 16;
	};
	uint32_t bits;
};

union rbdma_tde_rlsync_conf_mask {
	struct __attribute__((packed)) {
		uint32_t get_rbdma_mask : 4;
		uint32_t reserved0 : 4;
		uint32_t put_rbdma_mask : 4;
		uint32_t reserved1 : 20;
	};
	uint32_t bits;
};

union rbdma_tde_donerpt_mst {
	struct __attribute__((packed)) {
		uint32_t offset : 16;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union rbdma_td_run_conf_ext {
	struct __attribute__((packed)) {
		uint32_t tstc_idx : 2;
		uint32_t reserved0 : 6;
		uint32_t get_lsync_mp : 1;
		uint32_t get_lsync_mp_cnt : 3;
		uint32_t get_lsync_mp_idx : 8;
		uint32_t put_lsync_mp : 1;
		uint32_t put_lsync_rsv : 3;
		uint32_t put_lsync_mp_idx : 8;
	};
	uint32_t bits;
};

#endif /* _G_CDMA_TASK_REGISTERS_COMMON_H_*/
