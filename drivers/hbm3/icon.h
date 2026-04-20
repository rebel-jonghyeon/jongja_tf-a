/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include <stdint.h>
#include <stdbool.h>
#include <ieee1500_icon.h>

#define B_DIE_UPPER 0x6400
#define B_DIE_MIDDLE 0x6800
#define B_DIE_LOWER 0x7000

#define C_DIE_SID0_UPPER 0x46400
#define C_DIE_SID0_MIDDLE 0x46800
#define C_DIE_SID0_LOWER 0x47000

#define C_DIE_SID1_UPPER 0xc6400
#define C_DIE_SID1_MIDDLE 0xc6800
#define C_DIE_SID1_LOWER 0xc7000

#define C_DIE_SID2_UPPER 0x146400
#define C_DIE_SID2_MIDDLE 0x146800
#define C_DIE_SID2_LOWER 0x147000

#define SOFT_LANE_REPAIR 0x0
#define HARD_LANE_REPAIR 0x1

#define ICON_MBIST_WDR_IDX 71

#define ICON_SET_WIR(CH_SELECT, WIR) (((CH_SELECT) << 8) | ((WIR) & 0xFF))
#define ICON_HBM3_TEMP(raw_temp) (-40 + (raw_temp))

struct lane_mapping {
	uint16_t bit_pos;
	char lane[8];
	uint16_t repair_pos;
	uint8_t dword_group;
};

typedef struct lane_mapping lane_map;

enum repair_group {
	DWORD0_BYTE0 = 0,
	DWORD0_BYTE1 = 1,
	DWORD0_BYTE2 = 2,
	DWORD0_BYTE3 = 3,
	AWORD_CA = 4,
	AWORD_RA = 5,
	DWORD1_BYTE0 = 6,
	DWORD1_BYTE1 = 7,
	DWORD1_BYTE2 = 8,
	DWORD1_BYTE3 = 9,
	REDUNDANT = 10,
	UNREPAIRABLE = 11,
	NA = 12,
};

enum extest_mode {
	TX0_EXTEST = 0,
	TX1_EXTEST = 1,
	RX0_EXTEST = 2,
	RX1_EXTEST = 3,
};

enum ICON_WIR {
	ICON_WIR_BYPASS = 0x0,
	ICON_WIR_EXTEST_RX = 0x1,
	ICON_WIR_EXTEST_TX = 0x2,
	ICON_WIR_RFU0 = 0x3,
	ICON_WIR_RFU1 = 0x4,
	ICON_WIR_HBM_RESET = 0x5,
	ICON_WIR_MBIST = 0x6,
	ICON_WIR_SOFT_REPAIR = 0x7,
	ICON_WIR_HARD_REPAIR = 0x8,
	ICON_WIR_DWORD_MISR = 0x9,
	ICON_WIR_AWORD_MISR = 0xa,
	ICON_WIR_CHANNEL_ID = 0xb,
	ICON_WIR_RFU2 = 0xc,
	ICON_WIR_AWORD_MISR_CONFIG = 0xd,
	ICON_WIR_DEVICE_ID = 0xe,
	ICON_WIR_TEMPERATURE = 0xf,
	ICON_WIR_MODE_REGISTER_DUMP_SET = 0x10,
	ICON_WIR_READ_LFSR_COMPARE_STICKY = 0x11,
	ICON_WIR_SOFT_LANE_REPAIR = 0x12,
	ICON_WIR_HARD_LANE_REPAIR = 0x13,
	ICON_WIR_CHANNEL_DISABLE = 0x14,
	ICON_WIR_CHANNEL_TEMPERATURE = 0x15,
	ICON_WIR_WOSC_RUN = 0x16,
	ICON_WIR_WOSC_COUNT = 0x17,
	ICON_WIR_ECS_ERROR_LOG = 0x18,
	ICON_WIR_HS_REP_CAP = 0x19,
	ICON_WIR_SELF_REP = 0x1a,
	ICON_WIR_SELF_REP_RESULT = 0x1b,
	/* 0x1c - 0x3f: RFU */
	ICON_WIR_CDC = 0xd0,
	/* 0x40 - 0xff: vendor specific */
};

enum ICON_WIR_CH_SELECT {
	ICON_WIR_CH_A = 0x0,
	ICON_WIR_CH_B = 0x1,
	ICON_WIR_CH_C = 0x2,
	ICON_WIR_CH_D = 0x3,
	ICON_WIR_CH_E = 0x4,
	ICON_WIR_CH_F = 0x5,
	ICON_WIR_CH_G = 0x6,
	ICON_WIR_CH_H = 0x7,
	ICON_WIR_CH_I = 0x8,
	ICON_WIR_CH_J = 0x9,
	ICON_WIR_CH_K = 0xa,
	ICON_WIR_CH_L = 0xb,
	ICON_WIR_CH_M = 0xc,
	ICON_WIR_CH_N = 0xd,
	ICON_WIR_CH_O = 0xe,
	ICON_WIR_CH_P = 0xf,
	ICON_WIR_CH_UPPER = 0x1c, /* CH A, B, C, D, M, N, O, P */
	ICON_WIR_CH_LOWER = 0x1d, /* CH E, F, G, H, I, J, K, L */
	ICON_WIR_CH_ALL = 0x1f,
	/* Xh: ignored - All channels selected */
	/* All others: reserved */
};

enum ICON_INSTRUCTION_REQ_BIT {
	ICON_INSTRUCTION_REQ_BYPASS = 0,
	ICON_INSTRUCTION_REQ_EXTEST_RX = 1,
	ICON_INSTRUCTION_REQ_EXTEST_TX = 2,
	ICON_INSTRUCTION_REQ_HBM_RESET = 3,
	ICON_INSTRUCTION_REQ_MBIST = 4,
	ICON_INSTRUCTION_REQ_SOFT_REPAIR = 5,
	ICON_INSTRUCTION_REQ_HARD_REPAIR = 6,
	ICON_INSTRUCTION_REQ_DWORD_MISR_MODE = 7,
	ICON_INSTRUCTION_REQ_DWORD_MISR_READ = 8,
	ICON_INSTRUCTION_REQ_DWORD_MISR_WRITE = 9,
	ICON_INSTRUCTION_REQ_AWORD_MISR_MODE = 10,
	ICON_INSTRUCTION_REQ_AWORD_MISR_READ = 11,
	ICON_INSTRUCTION_REQ_CHANNEL_ID = 12,
	ICON_INSTRUCTION_REQ_AWORD_MISR_CONFIG = 13,
	ICON_INSTRUCTION_REQ_DEVICE_ID = 14,
	ICON_INSTRUCTION_REQ_TEMPERATURE = 15,
	ICON_INSTRUCTION_REQ_MR_DUMP_SET_READ = 16,
	ICON_INSTRUCTION_REQ_MR_DUMP_SET_WRITE = 17,
	ICON_INSTRUCTION_REQ_READ_LFSR_CMP_STICKY = 18,
	ICON_INSTRUCTION_REQ_SOFT_LANE_REPAIR_READ = 19,
	ICON_INSTRUCTION_REQ_SOFT_LANE_REPAIR_WRITE = 20,
	ICON_INSTRUCTION_REQ_HARD_LANE_REPAIR_READ = 21,
	ICON_INSTRUCTION_REQ_HARD_LANE_REPAIR_WRITE = 22,
	ICON_INSTRUCTION_REQ_CHANNEL_DISABLE = 23,
	ICON_INSTRUCTION_REQ_CHANNEL_TEMP = 24,
	ICON_INSTRUCTION_REQ_WOSC_RUN = 25,
	ICON_INSTRUCTION_REQ_WOSC_COUNT = 26,
	ICON_INSTRUCTION_REQ_ECS_ERROR_LOG = 27,
	ICON_INSTRUCTION_REQ_HS_REQ_CAP = 28,
	ICON_INSTRUCTION_REQ_SELF_REP_READ = 29,
	ICON_INSTRUCTION_REQ_SELF_REP_WRITE = 30,
	ICON_INSTRUCTION_REQ_SELF_REP_RESULTS = 31,
};

/* specific ICON WDR */
union icon_device_id_t {
	union {
		uint32_t val[5];
		struct __attribute__((packed)) {
			uint32_t model_part_number : 8;
			uint32_t channel_available : 16;
			uint32_t density : 4;
			uint32_t manufacture_id : 4;
			uint32_t serial_no_lower : 32;
			uint32_t serial_no_upper : 32;
			uint32_t manufacturing_week : 8;
			uint32_t manufacturing_year : 8;
			uint32_t rfm : 1;
			uint32_t arfm : 1;
			uint32_t raaimt : 3;
			uint32_t raammt : 2;
			uint32_t raadec : 1;
			uint32_t raaimt_a : 3;
			uint32_t raammt_a : 2;
			uint32_t raadec_a : 1;
			uint32_t raaimt_b : 3;
			uint32_t raammt_b : 2;
			uint32_t raadec_b : 1;
			uint32_t raaimt_c : 3;
			uint32_t raammt_c : 2;
			uint32_t raadec_c : 1;
			uint32_t ppr_ra : 15;
			uint32_t ppr_rsvd : 1;
			uint32_t shared_rep_res : 1;
			uint32_t opt_feature : 5;
		};
	};
};

union icon_dram_temp_t {
	uint32_t val[1];
	struct __attribute__((packed)) {
		uint32_t valid : 1;
		uint32_t temp : 8;
	};
};

union icon_channel_temp_t {
	uint32_t val[2];
	struct __attribute__((packed)) {
		uint32_t sid0_valid : 1;
		uint32_t sid0_temp : 8;
		uint32_t sid1_valid : 1;
		uint32_t sid1_temp : 8;
		uint32_t sid2_valid : 1;
		uint32_t sid2_temp : 8;
		uint32_t sid3_valid : 1;
		uint32_t sid3_temp : 8;
	};
};

union icon_ecs_error_log_t {
	uint32_t val[7];
	struct __attribute__((packed)) {
		uint32_t sid0_pc0_ecs_valid : 1;
		uint32_t sid0_pc0_ecs_error_type : 2;
		uint32_t sid0_pc0_ecs_column_address : 5;
		uint32_t sid0_pc0_ecs_row_address : 15;
		uint32_t sid0_pc0_ecs_bank_address : 4;
		uint32_t sid0_pc1_ecs_valid : 1;
		uint32_t sid0_pc1_ecs_error_type : 2;
		uint32_t sid0_pc1_ecs_column_address : 5;
		uint32_t sid0_pc1_ecs_row_address : 15;
		uint32_t sid0_pc1_ecs_bank_address : 4;

		uint32_t sid1_pc0_ecs_valid : 1;
		uint32_t sid1_pc0_ecs_error_type : 2;
		uint32_t sid1_pc0_ecs_column_address : 5;
		uint32_t sid1_pc0_ecs_row_address : 15;
		uint32_t sid1_pc0_ecs_bank_address : 4;
		uint32_t sid1_pc1_ecs_valid : 1;
		uint32_t sid1_pc1_ecs_error_type : 2;
		uint32_t sid1_pc1_ecs_column_address : 5;
		uint32_t sid1_pc1_ecs_row_address : 15;
		uint32_t sid1_pc1_ecs_bank_address : 4;

		uint32_t sid2_pc0_ecs_valid : 1;
		uint32_t sid2_pc0_ecs_error_type : 2;
		uint32_t sid2_pc0_ecs_column_address : 5;
		uint32_t sid2_pc0_ecs_row_address : 15;
		uint32_t sid2_pc0_ecs_bank_address : 4;
		uint32_t sid2_pc1_ecs_valid : 1;
		uint32_t sid2_pc1_ecs_error_type : 2;
		uint32_t sid2_pc1_ecs_column_address : 5;
		uint32_t sid2_pc1_ecs_row_address : 15;
		uint32_t sid2_pc1_ecs_bank_address : 4;

		uint32_t sid3_pc0_ecs_valid : 1;
		uint32_t sid3_pc0_ecs_error_type : 2;
		uint32_t sid3_pc0_ecs_column_address : 5;
		uint32_t sid3_pc0_ecs_row_address : 15;
		uint32_t sid3_pc0_ecs_bank_address : 4;
		uint32_t sid3_pc1_ecs_valid : 1;
		uint32_t sid3_pc1_ecs_error_type : 2;
		uint32_t sid3_pc1_ecs_column_address : 5;
		uint32_t sid3_pc1_ecs_row_address : 15;
		uint32_t sid3_pc1_ecs_bank_address : 4;
	};
};

union hbm3_mr_t {
	uint32_t mrs[4];
	struct {
		union hbm3_mr0_t {
			uint8_t val;
			struct {
				uint8_t read_dbi : 1;
				uint8_t write_dbi : 1;
				uint8_t tcsr : 1;
				uint8_t rsvd0 : 1;
				uint8_t read_parity : 1;
				uint8_t write_parity : 1;
				uint8_t ca_parity : 1;
				uint8_t test_mdoe : 1;
			};
		} mr0;
		union hbm3_mr1_t {
			uint8_t val;
			struct {
				uint8_t write_latency : 5;
				uint8_t parity_latency : 3;
			};
		} mr1;
		union hbm3_mr2_t {
			uint8_t val;
			struct {
				uint8_t read_latency : 8;
			};
		} mr2;
		union hbm3_mr3_t {
			uint8_t val;
			struct {
				uint8_t write_recovery_for_auto_precharge : 8;
			};
		} mr3;
		union hbm3_mr4_t {
			uint8_t val;
			struct {
				uint8_t activate_to_precharge : 8;
			};
		} mr4;
		union hbm3_mr5_t {
			uint8_t val;
			struct {
				uint8_t read_to_auto_precharge : 4;
				uint8_t rsvd0 : 4;
			};
		} mr5;
		union hbm3_mr6_t {
			uint8_t val;
			struct {
				uint8_t pull_down_driver_strength : 3;
				uint8_t pull_up_driver_strength : 3;
				uint8_t rsvd0 : 2;
			};
		} mr6;
		union hbm3_mr7_t {
			uint8_t val;
			struct {
				uint8_t dword_loopback : 1;
				uint8_t dword_read_mux_control : 1;
				uint8_t rsvd0 : 1;
				uint8_t dword_misr_control : 3;
				uint8_t rsvd1 : 1;
				uint8_t cattrip : 1;
			};
		} mr7;
		union hbm3_mr8_t {
			uint8_t val;
			struct {
				uint8_t da_port_lockout : 1;
				uint8_t duty_cycle_monitor : 1;
				uint8_t ecs_error_log_auto_reset : 1;
				uint8_t wdqs_to_ck_training : 1;
				uint8_t rfm_levels: 2;
				uint8_t rsvd0 : 2;
			};
		} mr8;
		union hbm3_mr9_t {
			uint8_t val;
			struct {
				uint8_t meta_data : 1;
				uint8_t severity_reporting : 1;
				uint8_t error_vector_input_mode : 1;
				uint8_t error_vector_pattern : 1;
				uint8_t auto_ecs_via_refab : 1;
				uint8_t auto_ecs_during_self_refresh : 1;
				uint8_t ecs_multi_bit_error_correction : 1;
				uint8_t ecs_error_type_address_reset : 1;
			};
		} mr9;
		union hbm3_mr10_t {
			uint8_t val;
			struct {
				uint8_t rsvd0 : 8;
			};
		} mr10;
		union hbm3_mr11_t {
			uint8_t val;
			struct {
				uint8_t dca_code_wdqs0 : 4;
				uint8_t dca_code_wdqs1 : 4;
			};
		} mr11;
		union hbm3_mr12_t {
			uint8_t val;
			struct {
				uint8_t rsvd0 : 8;
			};
		} mr12;
		union hbm3_mr13_t {
			uint8_t val;
			struct {
				uint8_t rsvd0 : 8;
			};
		} mr13;
		union hbm3_mr14_t {
			uint8_t val;
			struct {
				uint8_t rsvd0 : 1;
				uint8_t ref_volt_aword : 6;
				uint8_t rsvd1 : 1;
			};
		} mr14;
		union hbm3_mr15_t {
			uint8_t val;
			struct {
				uint8_t rsvd0 : 1;
				uint8_t ref_volt_dword : 6;
				uint8_t rsvd1 : 1;
			};
		} mr15;
	};
};

/* ICON */
void wait_for_test_instruction_req_done(struct hbm3_config *cfg);
void wait_for_test_instruction_req_done_clear(struct hbm3_config *cfg);
uint32_t icon_test_instruction_req(struct hbm3_config *cfg, uint8_t ch,
								   enum ICON_INSTRUCTION_REQ_BIT req_bit);
uint32_t icon_sw_instruction_req(struct hbm3_config *cfg);
union icon_device_id_t icon_get_device_id(struct hbm3_config *cfg);
union icon_dram_temp_t icon_get_dram_temperature(struct hbm3_config *cfg);
union icon_channel_temp_t icon_get_channel_temperature(struct hbm3_config *cfg);
union icon_ecs_error_log_t icon_get_ecs_error_log(struct hbm3_config *cfg, uint8_t ch);
void icon_print_device_id(union icon_device_id_t device_id);
void icon_print_dram_temperature(union icon_dram_temp_t dram_temp);
void icon_print_channel_temperature(union icon_channel_temp_t channel_temp);
void icon_print_ecs_error_log(union icon_ecs_error_log_t ecs_error_log);
uint32_t icon_mrs_ch(struct hbm3_config *cfg, uint8_t ch, uint32_t *mr_data);
uint32_t icon_mrr(struct hbm3_config *cfg, uint8_t ch);
uint32_t icon_mbist_wdr(struct hbm3_config *cfg, uint32_t *mbist_wdr);
uint32_t icon_mbist_wir(struct hbm3_config *cfg);
uint32_t icon_mbist_result(struct hbm3_config *cfg);
uint32_t icon_cdc_wir(struct hbm3_config *cfg);
uint32_t icon_cdc_wdr(struct hbm3_config *cfg, uint32_t cdc_wdr);
uint32_t icon_cdc_result(struct hbm3_config *cfg);
uint32_t icon_hbm_chipping_detection(struct hbm3_config *cfg);
uint32_t icon_mrw_idx(struct hbm3_config *cfg, uint8_t ch, enum wdr_mr_pos wdr_idx, uint32_t mr_data);
uint32_t icon_rd_feedback(struct hbm3_config *cfg, uint8_t ch,
						  uint32_t *rd_data0, uint32_t *rd_data1);
int32_t icon_extest(struct hbm3_config *cfg, uint8_t ch, uint8_t ch_rep_lane[REDUNDANT]);
int32_t hbm3_lane_repair(struct hbm3_config *cfg, uint8_t ch, uint8_t ch_rep_lane[REDUNDANT]);
