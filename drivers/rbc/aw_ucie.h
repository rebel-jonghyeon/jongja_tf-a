/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#define UCIE_INTR_LOG_SIZE			(50)
#define UCIE_INTR_LOG_LEN			(100)
#define UCIE_SRAM_SIZE				(0x20000)

#define PCIE_EXT_CAP_ID				(0x0023)
#define DVSEC_VENDOR_ID_FOR_UCIE	(0xD2DE)

#define NUM_OF_REG_LOC				(4)
#define BLK_RBC_V00_UCIE_INTR_ID	(303)
#define BLK_RBC_V01_UCIE_INTR_ID	(308)
#define BLK_RBC_V10_UCIE_INTR_ID	(313)
#define BLK_RBC_V11_UCIE_INTR_ID	(318)
#define BLK_RBC_H00_UCIE_INTR_ID	(323)
#define BLK_RBC_H01_UCIE_INTR_ID	(328)

struct ucie_sb_reg_req {
	union {
		struct {
			uint32_t opcode:5;/* [4:0] */
			uint32_t ep:1;/* [5:5] */
			uint32_t rsvd_0:8;/* [13:6] */
			uint32_t be:8;/* [21:14] */
			uint32_t tag:5;/* [26:22] */
			uint32_t rsvd_1:2;/* [28:27] */
			uint32_t srcid:3;/* [31:29] */
		};
		uint32_t val;
	} phase0;
	union {
		struct {
			uint32_t addr:24;/* [23:0] */
			uint32_t dstid:3;/* [26:24] */
			uint32_t rsvd_0:2;/* [28:27] */
			uint32_t cr:1;/* [29:29] */
			uint32_t cp:1;/* [30:30] */
			uint32_t dp:1;/* [31:31] */
		};
		uint32_t val;
	} phase1;
	union {
		struct {
			uint32_t data_low;
		};
		uint32_t val;
	} phase2;
	union {
		struct {
			uint32_t data_high;
		};
		uint32_t val;
	} phase3;
};

struct ucie_sb_reg_comp {
	struct {
		uint32_t opcode:5;/* [4:0] */
		uint32_t ep:1;/* [5:5] */
		uint32_t rsvd_0:8;/* [13:6] */
		uint32_t be:8;/* [21:14] */
		uint32_t tag:5;/* [26:22] */
		uint32_t rsvd_1:2;/* [28:27] */
		uint32_t srcid:3;/* [31:29] */
	} phase0;
	struct {
		uint32_t status:3;/* [2:0] */
		uint32_t rsvd_0:2;/* [23:3] */
		uint32_t dstid:3;/* [26:24] */
		uint32_t rsvd_1:2;/* [28:27] */
		uint32_t cr:1;/* [29:29] */
		uint32_t cp:1;/* [30:30] */
		uint32_t dp:1;/* [31:31] */
	} phase1;
	struct {
		uint32_t data_low;
	} phase2;
	struct {
		uint32_t data_high;
	} phase3;
};

struct ucie_sb_msg_wo_data {
	struct {
		uint32_t opcode:5;/* [4:0] */
		uint32_t rsvd_0:9;/* [13:5] */
		uint32_t msgcode:8;/* [21:14] */
		uint32_t rsvd_1:7;/* [28:22] */
		uint32_t srcid:3;/* [31:29] */
	} phase0;
	struct {
		uint32_t msgsubcode:8;/* [7:0] */
		uint32_t msginfo:16;/* [23:8] */
		uint32_t dstid:3;/* [26:24] */
		uint32_t rsvd_0:3;/* [29:27] */
		uint32_t cp:1;/* [30:30] */
		uint32_t dp:1;/* [31:31] */
	} phase1;
};

struct ucie_sb_msg_w_data {
	struct {
		uint32_t opcode:5;/* [4:0] */
		uint32_t rsvd_0:9;/* [13:5] */
		uint32_t msgcode:8;/* [21:14] */
		uint32_t rsvd_1:7;/* [28:22] */
		uint32_t srcid:3;/* [31:29] */
	} phase0;
	struct {
		uint32_t msgsubcode:8;/* [7:0] */
		uint32_t msginfo:16;/* [23:8] */
		uint32_t dstid:3;/* [26:24] */
		uint32_t rsvd_0:3;/* [29:27] */
		uint32_t cp:1;/* [30:30] */
		uint32_t dp:1;/* [31:31] */
	} phase1;
	struct {
		uint32_t data_low;
	} phase2;
	struct {
		uint32_t data_high;
	} phase3;
};

union ucie_sb_mbox_reg_addr {
	struct {
		uint32_t offset:12;
		uint32_t rsvd_0:8;
		uint32_t rl:4;
		uint32_t rsvd_1:8;
	};
	uint32_t val;
};

union ucie_sb_mbox_mem_addr {
	struct {
		uint32_t offset:20;
		uint32_t rl:4;
		uint32_t rsvd_0:8;
	};
	uint32_t val;
};

enum {
	UCIE_REG_BLK_ID_D2D_PHY = 0x0,
	UCIE_REG_BLK_ID_TEST_COMP,
	UCIE_REG_BLK_ID_D2D_IMP,
	UCIE_REG_BLK_ID_PHY_IMP,
};

enum {
	UCIE_SB_32B_MEM_RD = 0x00,
	UCIE_SB_32B_MEM_WR = 0x01,
	UCIE_SB_32B_CONFIG_RD = 0x04,
	UCIE_SB_32B_CONFIG_WR = 0x05,
	UCIE_SB_64B_MEM_RD = 0x08,
	UCIE_SB_64B_MEM_WR = 0x09,
	UCIE_SB_64B_CONFIG_RD = 0x0C,
	UCIE_SB_64B_CONFIG_WR = 0x0D,
	UCIE_SB_COMP_WO_DATA = 0x10,
	UCIE_SB_COMP_W_32B_DATA = 0x11,
	UCIE_SB_MSG_WO_DATA = 0x12,
	UCIE_SB_COMP_W_64B_DATA = 0x19,
	UCIE_SB_MSG_W_64B_DATA = 0x1B,
};

enum {
	UCIE_SB_MBOX_STAT_CA = 0x0,/* Completer Abort */
	UCIE_SB_MBOX_STAT_UR = 0x1,/* Unsupported Request */
	UCIE_SB_MBOX_STAT_SUCCESS = 0x3,
};

enum {
	UCIE_SB_CONFIG_REG_LOCATOR_0 = 0x0,
	UCIE_SB_MEM_REG_LOCATOR_0 = 0x0,
	UCIE_SB_MEM_REG_LOCATOR_1 = 0x1,
	UCIE_SB_MEM_REG_LOCATOR_2 = 0x2,
	UCIE_SB_MEM_REG_LOCATOR_3 = 0x3,
	UCIE_SB_MEM_REG_LOCATOR_SPECIFIC = 0xF,
};

enum {
	UCIE_SS_H00_ID = 0,
	UCIE_SS_H01_ID,
	UCIE_SS_V00_ID,
	UCIE_SS_V01_ID,
	UCIE_SS_V10_ID,
	UCIE_SS_V11_ID,
	NUM_OF_UCIE_SS_ID
};

enum {
	TARGET_LINK_SPEED_4GT = 0,
	TARGET_LINK_SPEED_8GT,
	TARGET_LINK_SPEED_12GT,
	TARGET_LINK_SPEED_16GT,
	TARGET_LINK_SPEED_24GT,
	TARGET_LINK_SPEED_32GT,
};

enum {
	TARGET_LINK_WIDTH_X8 = 1,
	TARGET_LINK_WIDTH_X16,
	TARGET_LINK_WIDTH_X32,
	TARGET_LINK_WIDTH_X64,
	TARGET_LINK_WIDTH_X128,
	TARGET_LINK_WIDTH_X256,
};

enum {
	FLIT_FORMAT_1_RAW = 1,
	FLIT_FORMAT_2_68B,
	FLIT_FORMAT_3_STD_256_END,
	FLIT_FORMAT_4_STD_256_STT,
	FLIT_FORMAT_5_LAT_256_WO,
	FLIT_FORMAT_6_LAT_256_W,
	NUM_OF_FLIT_FORMAT
};

enum {
	PHY_COMP_OP_TYPE_NO_OP = 0,
	PHY_COMP_OP_TYPE_TX_D2C_POINT,
	PHY_COMP_OP_TYPE_TX_D2C_SWEEP,
	PHY_COMP_OP_TYPE_RX_D2C_POINT,
	PHY_COMP_OP_TYPE_RX_D2C_SWEEP,
};

enum {
	RX_VREF_OFFSET_EN_NONE = 0,
	RX_VREF_OFFSET_EN_ADD,
	RX_VREF_OFFSET_EN_SUB,
};

enum {
	DATA_PAT_PER_LANE_LFSR = 0,
	DATA_PAT_PER_LANE_ID,
	DATA_PAT_PER_LANE_AA,
	DATA_PAT_PER_LANE_ALL_0,
	DATA_PAT_PER_LANE_ALL_1,
	DATA_PAT_PER_LANE_IVT_CLK,
};

enum {
	VAL_PAT_FUNC_VALID = 0,
};

enum {
	CLK_PHASE_CON_CENTER = 0,
	CLK_PHASE_CON_LEFT,
	CLK_PHASE_CON_RIGHT
};

enum {
	TRAIN_MODE_CONT = 0,
	TRAIN_MODE_BURST,
};

enum {
	CLOCK_MODE_STROBE = 0,
	CLOCK_MODE_FREERUN,
};

enum {
	CLOCK_PHASE_DIFF = 0,
	CLOCK_PHASE_QUAD,
};

enum {
	LTSM_RESET = 0,
	LTSM_SBINIT,
	LTSM_MBINIT_PARAM,
	LTSM_MBINIT_CAL,
	LTSM_MBINIT_REPAIRCLK,
	LTSM_MBINIT_REPAIRVAL,
	LTSM_MBINIT_REVERSALMB,
	LTSM_MBINIT_REPAIRMB,
	LTSM_MBTRAIN_VALVREF,
	LTSM_MBTRAIN_DATAVREF,
	LTSM_MBTRAIN_SPEEDIDLE,
	LTSM_MBTRAIN_TXSELFCAL,
	LTSM_MBTRAIN_RXSELFCAL,
	LTSM_MBTRAIN_VALTRAINCENTER,
	LTSM_MBTRAIN_VALTRAINVREF,
	LTSM_MBTRAIN_DATATRAINCENTER1,
	LTSM_MBTRAIN_DATATRAINVREF,
	LTSM_MBTRAIN_RXDESKEW,
	LTSM_MBTRAIN_DATATRAINCENTER2,
	LTSM_MBTRAIN_LINKSPEED,
	LTSM_MBTRAIN_REPAIR,
	LTSM_PHYRETRAIN,
	LTSM_LINKINIT,
	LTSM_ACTIVE,
	LTSM_TRAINERROR,
	LTSM_L1_L2,
};

enum {
	ADAP_COMPLIANCE_MODE_NORMAL = 0,
	ADAP_COMPLIANCE_MODE_PHY_ONLY,
	ADAP_COMPLIANCE_MODE_ADAPTER,
};

enum {
	FLIT_INJECT_FLIT_TYPE_NOP = 0,
	FLIT_INJECT_FLIT_TYPE_TEST,
	FLIT_INJECT_FLIT_TYPE_ALT,
};

enum {
	FLIT_INJECT_MODE_CONT = 0,
	FLIT_INJECT_MODE_NUM_WO_INTL,
	FLIT_INJECT_MODE_NUM_W_INTL,
};

enum {
	FLIT_INJECT_PAYLOAD_FIXED_ALL,
	FLIT_INJECT_PAYLOAD_RANDOM_ALL,
	FLIT_INJECT_PAYLOAD_FIXED_OFFSET_ONCE,
	FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_ONCE,
	FLIT_INJECT_PAYLOAD_FIXED_OFFSET_REP,
	FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_REP,
};

enum {
	FLIT_INJECT_STAT_NO_FLIT = 0,
	FLIT_INJECT_STAT_ONGOING,
	FLIT_INJECT_STAT_DONE,
	FLIT_INJECT_STAT_HALTED
};

enum {
	RETRY_INJECT_STAT_NO_ERROR = 0,
	RETRY_INJECT_STAT_ONGOING,
	RETRY_INJECT_STAT_DONE,
};

enum {
	FLIT_RX_STAT_NO_FLIT = 0,
	FLIT_RX_STAT_ONGOING,
};

enum {
	LINK_STATE_INJ_TYPE_REQ = 0,
	LINK_STATE_INJ_TYPE_RESP = 1,
};

enum {
	RDI_FDI_STATE_NOP = 0x0,
	RDI_FDI_STATE_ACTIVE = 0x1,
	RDI_FDI_STATE_L1 = 0x4,
	RDI_FDI_STATE_L2 = 0x8,
	RDI_FDI_STATE_LINKRESET = 0x9,
	RDI_FDI_STATE_RETRAIN = 0xb,
	RDI_FDI_STATE_DISABLED = 0xc
};

enum {
	ERROR_INJ_TYPE_NO_ERROR = 0x0,
	ERROR_INJ_TYPE_1BIT = 0x1,
	ERROR_INJ_TYPE_2BIT = 0x2,
	ERROR_INJ_TYPE_3BIT = 0x3,
};

enum {
	ERROR_INJ_FLIT_ANY = 0x0,
	ERROR_INJ_FLIT_NOP = 0x1,
	ERROR_INJ_FLIT_PAYLOAD = 0x2,
	ERROR_INJ_FLIT_TEST = 0x3,
	ERROR_INJ_FLIT_PAYLOAD_SAME_SEQ = 0x4,
};

enum {
	NUM_OF_INSERTED_ONE_64BYTES = 0x0,
	NUM_OF_INSERTED_TWO_64BYTES = 0x1,
	NUM_OF_INSERTED_FOUR_64BYTES = 0x2,
};

enum {
	CRC_ERR_INJ_DISABLE = 0x0,
	CRC_ERR_INJ_1BIT_INVERTED = 0x1,
	CRC_ERR_INJ_2BIT_INVERTED = 0x2,
	CRC_ERR_INJ_3BIT_INVERTED = 0x3,
};

enum {
	CRC_ERR_INJ_COUNT_PER_1_FLIT = 0x0,
	CRC_ERR_INJ_COUNT_PER_8_FLIT = 0x1,
	CRC_ERR_INJ_COUNT_PER_16_FLIT = 0x2,
	CRC_ERR_INJ_COUNT_PER_64_FLIT = 0x3,
};

enum {
	ADAP_LSM_RESP_TYPE_ACTIVE = 1,
	ADAP_LSM_RESP_TYPE_L1,
	ADAP_LSM_RESP_TYPE_L2,
	ADAP_LSM_RESP_TYPE_LINKRESET,
	ADAP_LSM_RESP_TYPE_DISABLE
};

enum {
	ADAP_TIMEOUT_PARAM_EXCHANGE = 1,
	ADAP_TIMEOUT_NOT_RCV_RESP,
	ADAP_TIMEOUT_TRANS_ACTIVE,
	ADAP_TIMEOUT_RETRY,
	ADAP_TIMEOUT_LOCAL_SB,
	ADAP_TIMEOUT_RETIMER_CREDIT,
	ADAP_TIMEOUT_REMOTE_REG_ACCESS
};

extern int32_t (*aw_ucie_init)(const int32_t ucie_ss_id, void * const base_address);
int32_t aw_ucie_set_target_ss(const uint32_t ucie_ss_id);
int32_t aw_ucie_get_target_ss(void);

int32_t aw_ucie_get_pcie_cap_hdr(uint32_t * const val);
int32_t aw_ucie_get_dvs_hdr1(uint32_t * const val);
int32_t aw_ucie_get_dvs_hdr2_cap_desc(uint32_t * const val);
int32_t aw_ucie_set_corr_err_noti(const uint32_t prot_based_en, const uint32_t link_err_intr_en);
int32_t aw_ucie_set_non_fatal_uncorr_err_noti(const uint32_t prot_based_en, const uint32_t link_err_intr_en);
int32_t aw_ucie_set_fatal_uncorr_err_noti(const uint32_t prot_based_en, const uint32_t link_err_intr_en);
int32_t aw_ucie_set_link_cap_APMW(void);
int32_t aw_ucie_clear_link_cap_APMW(void);
int32_t aw_ucie_get_link_capability(uint32_t * const val);
int32_t aw_ucie_get_link_control(uint32_t * const val);
int32_t aw_ucie_set_link_control(const uint32_t val);
int32_t aw_ucie_get_link_status(uint32_t * const val);
int32_t aw_ucie_set_link_event_noti(const uint32_t link_stat_chg, const uint32_t hw_auto_bw_chg);

int32_t aw_ucie_set_phy_init_debug(const uint32_t val);
int32_t aw_ucie_set_phy_control(const uint32_t val);
int32_t aw_ucie_get_phy_control(uint32_t * const val);
int32_t aw_ucie_get_phy_status(uint32_t * const val);
int32_t aw_ucie_get_phy_train_setup_1(const uint32_t mod_id, uint32_t * const val);
int32_t aw_ucie_set_phy_train_setup_1(const uint32_t mod_id, const uint32_t val);
int32_t aw_ucie_get_phy_err_log0(const uint32_t mod_id, uint32_t * const val);
int32_t aw_ucie_get_aw_ucie_ltsm_state(const uint32_t mod_id, uint32_t * const state);
int32_t aw_ucie_get_phy_err_log1(const uint32_t mod_id, uint32_t * const val);

int32_t aw_ucie_set_d2d_uncorr_err_status(const uint32_t val);
int32_t aw_ucie_get_d2d_uncorr_err_status(uint32_t * const val);
int32_t aw_ucie_set_d2d_uncorr_err_mask(const uint32_t val);
int32_t aw_ucie_get_d2d_uncorr_err_mask(uint32_t * const val);
int32_t aw_ucie_set_uncorr_err_mask(const uint32_t adap_to, const uint32_t rcv_of,
									const uint32_t internal, const uint32_t sb_fatal,
									const uint32_t sb_nfatal, const uint32_t inv_param);
int32_t aw_ucie_get_intr_summary_mask(uint32_t * const val);
int32_t aw_ucie_set_intr_summary_mask(const uint32_t val);
int32_t aw_ucie_get_d2d_uncorr_err_severity(uint32_t * const val);
int32_t aw_ucie_set_d2d_uncorr_err_severity(const uint32_t val);
int32_t aw_ucie_set_uncorr_err_severity(const uint32_t adap_to, const uint32_t rcv_of,
										const uint32_t internal, const uint32_t sb_fatal,
										const uint32_t sb_nfatal, const uint32_t inv_param);
int32_t aw_ucie_set_d2d_corr_err_status(const uint32_t val);
int32_t aw_ucie_get_d2d_corr_err_status(uint32_t * const val);
int32_t aw_ucie_set_corr_err_mask(const bool crc_err, const bool adap_retrain, const bool internal,
								  const bool dev_corr_err_msg_rcv, const bool runtime_link_test);
int32_t aw_ucie_get_crc_err_detected(bool * const crc_err_detected);
int32_t aw_ucie_get_d2d_hdr_log1_1(uint32_t * const val);
int32_t aw_ucie_get_d2d_hdr_log1_2(uint32_t * const val);
int32_t aw_ucie_get_d2d_hdr_log2(uint32_t * const val);
int32_t aw_ucie_set_d2d_runtime_link_test_cntrl(const uint32_t val);
int32_t aw_ucie_get_d2d_runtime_link_test_cntrl(uint32_t * const val);
int32_t aw_ucie_get_d2d_runtime_link_parity_log(const uint32_t module_id, const bool low, uint32_t * const val);
int32_t aw_ucie_set_d2d_adv_adp_log1(const uint32_t val);
int32_t aw_ucie_get_d2d_adv_adp_log1(uint32_t * const val);
int32_t aw_ucie_get_d2d_fin_adp_log1(uint32_t * const val);
int32_t aw_ucie_get_phy_cap(uint32_t * const val);
int32_t aw_ucie_get_phy_extnd_cap_hdr(uint32_t * const val);
int32_t aw_ucie_get_uhm_dvsec_hdr1(uint32_t * const val);
int32_t aw_ucie_get_uhm_dvsec_hdr2(uint32_t * const val);

int32_t aw_ucie_set_adap_test_comp_ctrl(const uint32_t val);
int32_t aw_ucie_get_adap_test_comp_ctrl(uint32_t * const val);
int32_t aw_ucie_get_adap_test_comp_stat(uint32_t * const val);
int32_t aw_ucie_set_adap_test_comp_phy_only_mode(void);
int32_t aw_ucie_set_adap_test_comp_normal_mode(void);
int32_t aw_ucie_set_adap_test_comp_adap_mode(void);
int32_t aw_ucie_adap_test_comp_force_reset(void);
int32_t aw_ucie_get_adap_test_comp_ctrl(uint32_t * const val);
int32_t aw_ucie_set_adap_test_comp_flit_injt_ctrl(const uint32_t val);

int32_t aw_ucie_get_cmn_mcu_scratch_reg1(uint32_t * const val);

extern int32_t (*aw_ucie_link_training)(void);
extern int32_t (*aw_ucie_link_retraining)(void);

int32_t aw_ucie_sb_mbox_manual(const uint32_t opcode, const uint32_t be,
							   const uint32_t addr_18_0, const uint32_t addr_23_19,
							   uint32_t * const out_buf, uint32_t * const in_buf);
extern int32_t (*aw_ucie_sb_mem_rd32)(const uint32_t rl, const uint32_t offset, uint32_t * const buf);
extern int32_t (*aw_ucie_sb_mem_wr32)(const uint32_t rl, const uint32_t offset, uint32_t * const buf);
int32_t aw_ucie_sb_mem_rd64(const uint32_t rl, const uint32_t offset, uint32_t * const buf);
int32_t aw_ucie_sb_mem_wr64(const uint32_t rl, const uint32_t offset, uint32_t * const buf);
int32_t aw_ucie_sb_config_rd32(const uint32_t rl, const uint32_t offset, uint32_t * const buf);
int32_t aw_ucie_sb_config_wr32(const uint32_t rl, const uint32_t offset, uint32_t * const buf);
int32_t aw_ucie_sb_config_rd64(const uint32_t rl, const uint32_t offset, uint32_t * const buf);
int32_t aw_ucie_sb_config_wr64(const uint32_t rl, const uint32_t offset, uint32_t * const buf);
int32_t aw_ucie_get_sb_mbox_status(uint8_t * const val);

int32_t aw_ucie_mb_runtime_link_test_enable(const uint32_t num_of_parity_bytes);
int32_t aw_ucie_mb_runtime_link_test_disable(void);
extern int32_t (*aw_ucie_mb_crc_err_inject)(const uint32_t inverted_bits, const uint32_t injection_cnt);

int32_t aw_ucie_mb_inject_flit_disable(void);
extern int32_t (*aw_ucie_mb_inject_nop_flit)(const uint32_t inj_mode, const uint32_t flit_num);
extern int32_t (*aw_ucie_mb_inject_test_flit)(const uint32_t inj_mode, const uint32_t flit_num,
											  const uint32_t payload_type, const uint32_t pattern,
											  const uint32_t offset, const uint32_t repetition);
int32_t aw_ucie_mb_inject_alt_flit(const uint32_t inj_mode, const uint32_t flit_num,
								   const uint32_t payload_type, const uint32_t pattern,
								   const uint32_t offset, const uint32_t repetition);

int32_t aw_ucie_link_state_req_inject_stack0(const uint32_t state);
int32_t aw_ucie_link_state_resp_inject_stack0(const uint32_t state);
int32_t aw_ucie_mb_inject_error(const uint32_t error_type, const uint32_t byte_offset,
								const uint32_t num_btwn_err, const uint32_t num_err_flits,
								const uint32_t flit_type, const uint32_t retry_threshold);

int32_t do_runtime_link_test(const uint32_t m0_repair, const uint32_t m1_repair, const uint32_t m0_lane_id,
							 const uint32_t m1_lane_id, const uint32_t stuck_at_fault);

/* int32_t aw_ucie_inject_stuck_at_fault_in_runtime_link_test(const uint32_t val); */

int32_t aw_ucie_get_m0_lane_repair_stat(uint32_t * const trd_val, uint32_t * const rrd_val);
int32_t aw_ucie_get_m1_lane_repair_stat(uint32_t * const trd_val, uint32_t * const rrd_val);

int32_t aw_ucie_clear_intr_log(void);
int32_t aw_ucie_get_intr_log_count(uint32_t * const log_cnt);
int32_t aw_ucie_get_intr_log_arr(char log_buf[][UCIE_INTR_LOG_LEN], uint32_t log_cnt);
int32_t aw_ucie_get_log_data(uint32_t hdr_log[][3], uint32_t err_log[][4][2], uint32_t log_cnt);
int32_t aw_ucie_show_intr_counter(void);
int32_t aw_ucie_set_phy_compliance_enable(const uint32_t module_sel, const uint32_t compl_en);
int32_t aw_ucie_get_phy_compliance_mode(const uint32_t module_sel, uint32_t * const mode);
int32_t aw_ucie_set_scrambling_disable(const uint32_t module_sel, const uint32_t scram_disabled);
int32_t aw_ucie_get_scrambling_disable(const uint32_t module_sel, uint32_t * const scram_disabled);
int32_t aw_ucie_do_phy_compliance_operation(const uint32_t module_sel, const uint32_t operation_trigger,
											const uint32_t operation_type);
int32_t aw_ucie_get_phy_compliance_operation_status(const uint32_t module_sel, uint32_t * const operation_status);

int32_t aw_ucie_set_data_pattern_of_train_setup1(const uint32_t module_sel, const uint32_t data_pattern);
int32_t aw_ucie_get_data_pattern_of_train_setup1(const uint32_t module_sel, uint32_t * const data_pattern);
int32_t aw_ucie_set_valid_pattern_of_train_setup1(const uint32_t module_sel, const uint32_t valid_pattern);
int32_t aw_ucie_get_valid_pattern_of_train_setup1(const uint32_t module_sel, uint32_t * const valid_pattern);
int32_t aw_ucie_set_clk_phase_cntrl_of_train_setup1(const uint32_t module_sel, const uint32_t clk_phase_cntrl);
int32_t aw_ucie_get_clk_phase_cntrl_of_train_setup1(const uint32_t module_sel, uint32_t * const clk_phase_cntrl);
int32_t aw_ucie_set_train_mode_of_train_setup1(const uint32_t module_sel, const uint32_t train_mode);
int32_t aw_ucie_get_train_mode_of_train_setup1(const uint32_t module_sel, uint32_t * const train_mode);
int32_t aw_ucie_set_burst_cnt_of_train_setup1(const uint32_t module_sel, const uint32_t burst_cnt);
int32_t aw_ucie_get_burst_cnt_of_train_setup1(const uint32_t module_sel, uint32_t * const burst_cnt);
int32_t aw_ucie_set_idle_cnt_of_train_setup2(const uint32_t module_sel, const uint32_t idle_cnt);
int32_t aw_ucie_get_idle_cnt_of_train_setup2(const uint32_t module_sel, uint32_t * const idle_cnt);
int32_t aw_ucie_set_iterations_of_train_setup2(const uint32_t module_sel, const uint32_t iterations);
int32_t aw_ucie_get_iterations_of_train_setup2(const uint32_t module_sel, uint32_t * const iterations);
int32_t aw_ucie_set_lane_mask_of_train_setup3(const uint32_t module_sel, const uint64_t reg_lane_mask);
int32_t aw_ucie_get_lane_mask_of_train_setup3(const uint32_t module_sel, uint64_t * const reg_lane_mask);

int32_t aw_ucie_set_repair_lane_mask_of_train_setup4(const uint32_t module_sel, const uint32_t repair_lane_mask);
int32_t aw_ucie_get_repair_lane_mask_of_train_setup4(const uint32_t  module_sel, uint32_t * const repair_lane_mask);
int32_t aw_ucie_set_max_err_th_per_lane_of_train_setup4(const uint32_t module_sel, const uint32_t max_err_th_per_lane);
int32_t aw_ucie_get_max_err_th_per_lane_of_train_setup4(const uint32_t module_sel,
														uint32_t * const max_err_th_per_lane);
int32_t aw_ucie_set_max_err_th_aggregate_of_train_setup4(const uint32_t module_sel,
														 const uint32_t max_err_th_aggregate);
int32_t aw_ucie_get_max_err_th_aggregate_of_train_setup4(const uint32_t  module_sel,
														 uint32_t * const max_err_th_aggregate);

extern int32_t (*aw_ucie_set_rx_vref_offset_enable)(const uint32_t module_sel, const uint32_t rx_vref_offset_enable);
extern int32_t (*aw_ucie_set_rx_vref_offset)(const uint32_t module_sel, const uint32_t rx_vref_offset);
int32_t aw_ucie_get_rx_vref_offset_operation_status(const uint32_t module_sel,
													uint32_t * const rx_vref_offset_operation_status);
int32_t aw_ucie_set_even_ui_compare_mask(const uint32_t module_sel, const uint32_t even_ui_compare_mask);
int32_t aw_ucie_get_even_ui_compare_mask(const uint32_t module_sel, uint32_t * const even_ui_compare_mask);
int32_t aw_ucie_set_odd_ui_compare_mask(const uint32_t module_sel, const uint32_t odd_ui_compare_mask);
int32_t aw_ucie_get_odd_ui_compare_mask(const uint32_t module_sel, uint32_t * const odd_ui_compare_mask);
int32_t aw_ucie_set_track_enable(const uint32_t module_sel, const uint32_t track_enable);
int32_t aw_ucie_get_track_enable(const uint32_t module_sel, uint32_t * const track_enable);
int32_t aw_ucie_set_compare_setup(const uint32_t module_sel, const uint32_t compare_setup);
int32_t aw_ucie_get_compare_setup(const uint32_t module_sel, uint32_t * const compare_setup);
extern int32_t (*aw_ucie_retrain_and_get_new_eml_emr)(const uint32_t module_sel, uint32_t * const eml,
													  uint32_t * const emr, const uint32_t lane_id);
