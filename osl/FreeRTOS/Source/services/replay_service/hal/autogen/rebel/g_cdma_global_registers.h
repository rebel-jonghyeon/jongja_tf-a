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

#ifndef _G_CDMA_GLOBAL_REGISTERS_COMMON_H_
#define _G_CDMA_GLOBAL_REGISTERS_COMMON_H_

#define ADDR_OFFSET_RBDMA_IP_INFO0						  0x000
#define ADDR_OFFSET_RBDMA_IP_INFO1						  0x004
#define ADDR_OFFSET_RBDMA_IP_INFO2						  0x008
#define ADDR_OFFSET_RBDMA_IP_INFO3						  0x00C
#define ADDR_OFFSET_RBDMA_IP_INFO4						  0x010
#define ADDR_OFFSET_RBDMA_IP_INFO5						  0x014
#define ADDR_OFFSET_RBDMA_IP_INFO_RESERVED1				  0x018
#define ADDR_OFFSET_RBDMA_IP_INFO_RESERVED2				  0x01C
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_CFG_ROLE			  0x020
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_CFG_BASE_ADDR	  0x024
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_CFG_DIE_STEP		  0x028
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_CFG_DRAM_BASE	  0x02C
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_CFG_CMGR_BASE	  0x030
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_CFG_CMGR_TX_OFFSET 0x034
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_RESERVED1		  0x038
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_RESERVED2		  0x03C
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_TD_COMP0_SLV		  0x040
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_TD_COMP1_SLV		  0x044
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_TD_COMP2_SLV		  0x048
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_TD_COMP3_SLV		  0x04C
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_RESERVED3		  0x050
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_TD_SYNC_SLV		  0x054
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_RESERVED4		  0x058
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_RESERVED5		  0x05C
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_TD_ERR0_SLV		  0x060
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_TD_ERR1_SLV		  0x064
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_TD_ERR2_SLV		  0x068
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_TD_ERR3_SLV		  0x06C
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_RESERVED6		  0x070
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_RESERVED7		  0x074
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_RESERVED8		  0x078
#define ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_RESERVED9		  0x07C
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_PKG_MODE		  0x080
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0	  0x084
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE1	  0x088
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0	  0x08C
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_DPLOG_SET	  0x090
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_RESERVED1		  0x094
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_RESERVED8		  0x098
#define ADDR_OFFSET_RBDMA_GLOBAL_DONERPT_MST_BASE		  0x09C
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CLEAR_CTRL		  0x0A0
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CLEAR_CTRL_STATUS 0x0A4
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_RESERVED2		  0x0A8
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_RESERVED3		  0x0AC
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_RESERVED4		  0x0B0
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_RESERVED5		  0x0B4
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_RESERVED6		  0x0B8
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_RESERVED7		  0x0BC
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC0_RUN	  0x0C0
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC1_RUN	  0x0C4
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC2_RUN	  0x0C8
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC3_RUN	  0x0CC
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC4_RUN	  0x0D0
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC5_RUN	  0x0D4
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC6_RUN	  0x0D8
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC7_RUN	  0x0DC
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC0_CMPL	  0x0E0
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC1_CMPL	  0x0E4
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC2_CMPL	  0x0E8
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC3_CMPL	  0x0EC
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC4_CMPL	  0x0F0
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC5_CMPL	  0x0F4
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC6_CMPL	  0x0F8
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_TSTC7_CMPL	  0x0FC
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_INT		  0x100
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_CBUSM_STATUS 0x104
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_RESERVED1	  0x108
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_RESERVED2	  0x10C
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_RESERVED3	  0x110
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_RESERVED4	  0x114
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_RESERVED5	  0x118
#define ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_RESERVED6	  0x11C
#define ADDR_OFFSET_RBDMA_GLOBAL_INTR_FIFO_READABLE_NUM	  0x120
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_ERR_EXPLICITY_RD	  0x124
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_INTR_FIFO			  0x128
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_INTR_FIFO_APP0	  0x12C
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_INTR_FIFO_APP1	  0x130
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_INTR_FIFO_APP2	  0x134
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_RESERVED0			  0x138
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_RESERVED1			  0x13C
#define ADDR_OFFSET_RBDMA_GLOBAL_ERR_INTR_FIFO			  0x140
#define ADDR_OFFSET_RBDMA_GLOBAL_ERR_INTR_INFO_APP0		  0x144
#define ADDR_OFFSET_RBDMA_GLOBAL_ERR_INTR_INFO_APP1		  0x148
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_RESERVED2			  0x14C
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_MST_DONE_NUM0		  0x150
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_MST_DONE_NUM1		  0x154
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_MST_DONE_NUM2		  0x158
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_MST_DONE_NUM3		  0x15C
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_MST_DONE_NUM4		  0x160
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_MST_DONE_NUM5		  0x164
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_MST_DONE_NUM6		  0x168
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_MST_DONE_NUM7		  0x16C
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_RESERVED3			  0x170
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_RESERVED4			  0x174
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_RESERVED5			  0x178
#define ADDR_OFFSET_RBDMA_GLOBAL_FNSH_RESERVED6			  0x17C
#define ADDR_OFFSET_RBDMA_GLOBAL_NORMALTQUEUE_STATUS	  0x180
#define ADDR_OFFSET_RBDMA_GLOBAL_NORMALTQUEUE_EXT_STATUS  0x184
#define ADDR_OFFSET_RBDMA_GLOBAL_URGENTTQUEUE_STATUS	  0x188
#define ADDR_OFFSET_RBDMA_GLOBAL_URGENTTQUEUE_EXT_STATUS  0x18C
#define ADDR_OFFSET_RBDMA_GLOBAL_PTQUEUE_STATUS			  0x190
#define ADDR_OFFSET_RBDMA_GLOBAL_UTLB_AVAIL_NUM			  0x194
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED0				  0x198
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED1				  0x19C
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED2				  0x1A0
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED3				  0x1A4
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED4				  0x1A8
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED5				  0x1AC
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED6				  0x1B0
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED7				  0x1B4
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED8				  0x1B8
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED9				  0x1BC
#define ADDR_OFFSET_RBDMA_GLOBAL_CDMA_STOP_RESUME_KILL	  0x1C0
#define ADDR_OFFSET_RBDMA_GLOBAL_CDMA_TASK_KILL_ID		  0x1C4
#define ADDR_OFFSET_RBDMA_GLOBAL_CDMA_TASK_KILL_STATUS	  0x1C8
#define ADDR_OFFSET_RBDMA_GLOBAL_RESERVED10				  0x1CC

enum rbdma_global_rbdma_cfg_role_c_s {
	RBDMA_GLOBAL_RBDMA_CFG_ROLE_C_S_CENT,
	RBDMA_GLOBAL_RBDMA_CFG_ROLE_C_S_SATE,
};

enum rbdma_global_rbdma_cfg_role_phy_assign_en {
	RBDMA_GLOBAL_RBDMA_CFG_ROLE_PHY_ASSIGN_EN_PAS_DS,
	RBDMA_GLOBAL_RBDMA_CFG_ROLE_PHY_ASSIGN_EN_PAS_EN,
};

enum rbdma_global_rbdma_cfg_role_phy_assign_base {
	RBDMA_GLOBAL_RBDMA_CFG_ROLE_PHY_ASSIGN_BASE_SRCB,
	RBDMA_GLOBAL_RBDMA_CFG_ROLE_PHY_ASSIGN_BASE_DSTB,
};

enum rbdma_global_config_pkg_mode_td_expand {
	RBDMA_GLOBAL_CONFIG_PKG_MODE_TD_EXPAND_BASIC_TD,
	RBDMA_GLOBAL_CONFIG_PKG_MODE_TD_EXPAND_EXPAND_TD,
};

enum rbdma_global_config_cdma_opmode0_lvl_op {
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_LVL_OP_PTG,
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_LVL_OP_FNG,
};

enum rbdma_global_config_cdma_opmode0_sp_parallel {
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_SP_PARALLEL_SPS,
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_SP_PARALLEL_SPM,
};

enum rbdma_global_config_cdma_opmode0_force_mst_mode {
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_FORCE_MST_MODE_DR_SWTCHMODE,
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_FORCE_MST_MODE_DR_FIXMODE,
};

enum rbdma_global_config_cdma_opmode0_en_auto_fetch {
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_EN_AUTO_FETCH_QUM,
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_EN_AUTO_FETCH_AFM,
};

enum rbdma_global_config_cdma_opmode0_max_perf {
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_MAX_PERF_NRM,
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_MAX_PERF_MXP,
};

enum rbdma_global_config_cdma_opmode0_mp_mode {
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_MP_MODE_ONEP,
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0_MP_MODE_MULP,
};

enum rbdma_global_config_cdma_opmode1_dnrpt_loss_remedy {
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE1_DNRPT_LOSS_REMEDY_LSY,
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE1_DNRPT_LOSS_REMEDY_LSL,
};

enum rbdma_global_config_cdma_opmode1_af_err_pause_off {
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE1_AF_ERR_PAUSE_OFF_AF_ERR_PAUSE_ON,
	RBDMA_GLOBAL_CONFIG_CDMA_OPMODE1_AF_ERR_PAUSE_OFF_AF_ERR_PAUSE_OFF,
};

enum rbdma_global_config_cdma_intr_set0_reserved0 {
	RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0_RESERVED0_RPT_SLV,
	RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0_RESERVED0_RPT_MST,
};

enum rbdma_global_config_cdma_intr_set0_fnsh_rptpolicy_m1_ext {
	RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0_FNSH_RPTPOLICY_M1_EXT_DEFAULT,
	RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0_FNSH_RPTPOLICY_M1_EXT_EXTEND,
};

enum rbdma_global_config_cdma_intr_set0_fnsh_explicity_clear {
	RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0_FNSH_EXPLICITY_CLEAR_IMP_CLR,
	RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0_FNSH_EXPLICITY_CLEAR_EXP_CLR,
};

enum rbdma_global_config_cdma_intr_set0_err_explicity_clear {
	RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0_ERR_EXPLICITY_CLEAR_IMP_CLR,
	RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0_ERR_EXPLICITY_CLEAR_EXP_CLR,
};

union rbdma_ip_info0 {
	struct __attribute__((packed)) {
		uint32_t rel_date : 32;
	};
	uint32_t bits;
};

union rbdma_ip_info1 {
	struct __attribute__((packed)) {
		uint32_t min_ver : 8;
		uint32_t maj_ver : 8;
		uint32_t rbdma_ver : 8;
		uint32_t ip_id : 8;
	};
	uint32_t bits;
};

union rbdma_ip_info2 {
	struct __attribute__((packed)) {
		uint32_t chiplet_id : 8;
		uint32_t reserved : 24;
	};
	uint32_t bits;
};

union rbdma_ip_info3 {
	struct __attribute__((packed)) {
		uint32_t num_of_totalutlb : 8;
		uint32_t num_of_executer : 8;
		uint32_t num_of_max_sgr : 12;
		uint32_t num_of_max_sgi : 4;
	};
	uint32_t bits;
};

union rbdma_ip_info4 {
	struct __attribute__((packed)) {
		uint32_t num_of_tqueue : 8;
		uint32_t num_of_utqueue : 8;
		uint32_t num_of_ptq : 8;
		uint32_t reserved : 8;
	};
	uint32_t bits;
};

union rbdma_ip_info5 {
	struct __attribute__((packed)) {
		uint32_t num_of_tequeue : 8;
		uint32_t num_of_uetqueue : 8;
		uint32_t num_of_fnsh_fifo : 8;
		uint32_t num_of_err_fifo : 8;
	};
	uint32_t bits;
};

union rbdma_ip_info_reserved1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_ip_info_reserved2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_cfg_role {
	struct __attribute__((packed)) {
		uint32_t c_s : 1;
		uint32_t phy_assign_en : 1;
		uint32_t phy_assign_base : 1;
		uint32_t reserved0 : 1;
		uint32_t s_pos_mask : 4;
		uint32_t reserved1 : 4;
		uint32_t c_pos_mask : 4;
		uint32_t reserve2 : 16;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_cfg_base_addr {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_cfg_die_step {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_cfg_dram_base {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_cfg_cmgr_base {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_cfg_cmgr_tx_offset {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_reserved1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_reserved2 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_td_comp0_slv {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_td_comp1_slv {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_td_comp2_slv {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_td_comp3_slv {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_reserved3 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_td_sync_slv {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_reserved4 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_reserved5 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_td_err0_slv {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_td_err1_slv {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_td_err2_slv {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_td_err3_slv {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_reserved6 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_reserved7 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_reserved8 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_rbdma_reserved9 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_pkg_mode {
	struct __attribute__((packed)) {
		uint32_t td_expand : 1;
		uint32_t reserved : 31;
	};
	uint32_t bits;
};

union rbdma_global_config_cdma_opmode0 {
	struct __attribute__((packed)) {
		uint32_t en_cmgr_evt0 : 1;
		uint32_t en_cmgr_evt1 : 1;
		uint32_t en_cmgr_evt2 : 1;
		uint32_t lvl_op : 1;
		uint32_t sp_parallel : 1;
		uint32_t force_mst_mode : 1;
		uint32_t en_auto_fetch : 1;
		uint32_t max_perf : 1;
		uint32_t split_granule : 6;
		uint32_t read_bl : 2;
		uint32_t write_bl : 2;
		uint32_t overwrite : 1;
		uint32_t mp_mode : 1;
		uint32_t mp_hash_pos0 : 4;
		uint32_t mp_hash_pos1 : 4;
		uint32_t mp_hash_pos2 : 4;
	};
	uint32_t bits;
};

union rbdma_global_config_cdma_opmode1 {
	struct __attribute__((packed)) {
		uint32_t low_read_qos_val : 4;
		uint32_t low_write_qos_val : 4;
		uint32_t high_read_qos_val : 4;
		uint32_t high_write_qos_val : 4;
		uint32_t dnrpt_loss_remedy : 1;
		uint32_t dnrpt_loss_watermark : 7;
		uint32_t af_tdq_watermark : 6;
		uint32_t af_err_pause_off : 1;
		uint32_t reserved : 1;
	};
	uint32_t bits;
};

union rbdma_global_config_cdma_intr_set0 {
	struct __attribute__((packed)) {
		uint32_t reserved0 : 1;
		uint32_t fnsh_rptpolicy_m1_ext : 1;
		uint32_t fnsh_explicity_clear : 1;
		uint32_t err_explicity_clear : 1;
		uint32_t reserved1 : 3;
		uint32_t en_finish_intr : 1;
		uint32_t en_error_intr : 1;
		uint32_t reserved2 : 1;
		uint32_t reserved3 : 1;
		uint32_t finish_intr_app_en : 1;
		uint32_t error_intr_app_en : 1;
		uint32_t reserved4 : 4;
		uint32_t en_mask_dpdc : 1;
		uint32_t reserved : 1;
		uint32_t en_mask_parity : 1;
		uint32_t reserved6 : 1;
		uint32_t en_mask_wrongcmd : 1;
		uint32_t en_mask_pterror : 1;
		uint32_t en_mask_overflow_pt : 1;
		uint32_t reserved5 : 1;
		uint32_t en_mask_overflow_tq : 1;
		uint32_t en_mask_bus_read_err : 1;
		uint32_t en_mask_bus_write_err : 1;
		uint32_t en_mask_fintr_fullwr : 1;
		uint32_t en_mask_ctrlbus_proc_err : 1;
		uint32_t en_mask_cbus_read_err : 1;
		uint32_t en_mask_cbus_write_err : 1;
	};
	uint32_t bits;
};

union rbdma_global_config_cdma_dplog_set {
	struct __attribute__((packed)) {
		uint32_t reserved0 : 1;
		uint32_t en_log_event : 1;
		uint32_t en_debug_cdma : 1;
		uint32_t reserved : 29;
	};
	uint32_t bits;
};

union rbdma_global_config_reserved1 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_reserved8 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_donerpt_mst_base {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_clear_ctrl {
	struct __attribute__((packed)) {
		uint32_t clear : 1;
		uint32_t pause : 1;
		uint32_t reserved : 30;
	};
	uint32_t bits;
};

union rbdma_global_config_clear_ctrl_status {
	struct __attribute__((packed)) {
		uint32_t pause_done : 1;
		uint32_t ue_pause_done : 1;
		uint32_t reserved : 30;
	};
	uint32_t bits;
};

union rbdma_global_config_reserved2 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_reserved3 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_reserved4 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_reserved5 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_reserved6 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_config_reserved7 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc0_run {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc1_run {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc2_run {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc3_run {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc4_run {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc5_run {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc6_run {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc7_run {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc0_cmpl {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc1_cmpl {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc2_cmpl {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc3_cmpl {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc4_cmpl {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc5_cmpl {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc6_cmpl {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_tstc7_cmpl {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_int {
	struct __attribute__((packed)) {
		uint32_t idle : 8;
		uint32_t reserved : 8;
		uint32_t tstc_status : 16;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_cbusm_status {
	struct __attribute__((packed)) {
		uint32_t master_w : 8;
		uint32_t master_r : 8;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_reserved1 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_reserved2 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_reserved3 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_reserved4 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_reserved5 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_status_cdma_reserved6 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_intr_fifo_readable_num {
	struct __attribute__((packed)) {
		uint32_t fnsh : 8;
		uint32_t err : 8;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_err_explicity_rd {
	struct __attribute__((packed)) {
		uint32_t fnsh_base : 1;
		uint32_t fnsh_app0 : 1;
		uint32_t fnsh_app1 : 1;
		uint32_t fnsh_app2 : 1;
		uint32_t reserved0 : 3;
		uint32_t fnsh_mst_clr : 1;
		uint32_t err_base : 1;
		uint32_t err_app0 : 1;
		uint32_t err_app1 : 1;
		uint32_t reserved1 : 21;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_intr_fifo {
	struct __attribute__((packed)) {
		uint32_t func_id : 4;
		uint32_t ctx_id : 8;
		uint32_t thread_id : 4;
		uint32_t cmd_id : 16;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_intr_fifo_app0 {
	struct __attribute__((packed)) {
		uint32_t num_te0_assigned : 10;
		uint32_t num_te1_assigned : 10;
		uint32_t num_te2_assigned : 10;
		uint32_t reserved : 2;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_intr_fifo_app1 {
	struct __attribute__((packed)) {
		uint32_t num_te3_assigned : 10;
		uint32_t num_te4_assigned : 10;
		uint32_t num_te5_assigned : 10;
		uint32_t reserved : 2;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_intr_fifo_app2 {
	struct __attribute__((packed)) {
		uint32_t num_te6_assigned : 10;
		uint32_t num_te7_assigned : 10;
		uint32_t urgent_task : 1;
		uint32_t assigned_tstc : 3;
		uint32_t execute_rbdma_id : 2;
		uint32_t reserved1 : 6;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_reserved0 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_reserved1 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_err_intr_fifo {
	struct __attribute__((packed)) {
		uint32_t te_par : 1;
		uint32_t reserved0 : 9;
		uint32_t dpdc : 1;
		uint32_t reserved1 : 5;
		uint32_t wrongcmd : 1;
		uint32_t pterror : 1;
		uint32_t overflow_pt : 1;
		uint32_t reserved2 : 1;
		uint32_t overflow_tq : 1;
		uint32_t bus_read_err : 1;
		uint32_t bus_write_err : 1;
		uint32_t fnsh_fifo_fullwr : 1;
		uint32_t ctrlbus_proc_err : 1;
		uint32_t cbus_af_err : 1;
		uint32_t cbus_mst_err : 1;
		uint32_t reserved3 : 5;
	};
	uint32_t bits;
};

union rbdma_global_err_intr_info_app0 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_err_intr_info_app1 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_reserved2 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_mst_done_num0 {
	struct __attribute__((packed)) {
		uint32_t ppid0 : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_mst_done_num1 {
	struct __attribute__((packed)) {
		uint32_t ppid1 : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_mst_done_num2 {
	struct __attribute__((packed)) {
		uint32_t ppid2 : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_mst_done_num3 {
	struct __attribute__((packed)) {
		uint32_t ppid3 : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_mst_done_num4 {
	struct __attribute__((packed)) {
		uint32_t ppid4 : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_mst_done_num5 {
	struct __attribute__((packed)) {
		uint32_t ppid5 : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_mst_done_num6 {
	struct __attribute__((packed)) {
		uint32_t ppid6 : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_mst_done_num7 {
	struct __attribute__((packed)) {
		uint32_t ppid7 : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_reserved3 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_reserved4 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_reserved5 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_fnsh_reserved6 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_normaltqueue_status {
	struct __attribute__((packed)) {
		uint32_t num : 32;
	};
	uint32_t bits;
};

union rbdma_global_normaltqueue_ext_status {
	struct __attribute__((packed)) {
		uint32_t num : 32;
	};
	uint32_t bits;
};

union rbdma_global_urgenttqueue_status {
	struct __attribute__((packed)) {
		uint32_t num : 32;
	};
	uint32_t bits;
};

union rbdma_global_urgenttqueue_ext_status {
	struct __attribute__((packed)) {
		uint32_t num : 32;
	};
	uint32_t bits;
};

union rbdma_global_ptqueue_status {
	struct __attribute__((packed)) {
		uint32_t num : 32;
	};
	uint32_t bits;
};

union rbdma_global_utlb_avail_num {
	struct __attribute__((packed)) {
		uint32_t avail_num_of_utlb : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved0 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved1 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved2 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved3 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved4 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved5 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved6 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved7 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved8 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved9 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union rbdma_global_cdma_stop_resume_kill {
	struct __attribute__((packed)) {
		uint32_t stop : 1;
		uint32_t resume : 1;
		uint32_t kill : 1;
		uint32_t kill_level : 1;
		uint32_t reserved : 28;
	};
	uint32_t bits;
};

union rbdma_global_cdma_task_kill_id {
	struct __attribute__((packed)) {
		uint32_t taskid : 32;
	};
	uint32_t bits;
};

union rbdma_global_cdma_task_kill_status {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_global_reserved10 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

#endif /* _G_CDMA_GLOBAL_REGISTERS_COMMON_H_*/
