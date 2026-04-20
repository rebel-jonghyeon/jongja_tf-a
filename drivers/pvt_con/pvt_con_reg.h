/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
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

#include "pvt_con_reg_voltage.h"
#include "pvt_con_reg_temperature.h"
#include "pvt_con_reg_process.h"

/* Structure of PVT registers */
/**
 * TRIMINFO_CONFIG	(Reset Value = 0x0000_0000)
 * [31:30] : VERSION			/ [29:28] : CALIB_SEL
 * [27:24] : RSVD				/ [23:22] : BGR_TC_CON_TS[1:0]
 * [21:20] : BGR_I_CON_TS[1:0]	/ [19:16] : OFSET_CON_TS[3:0]
 * [15: 9] : SLOPE_CON_TS[6:0]	/ [ 8: 2] : SLOPE_CON_VS[6:0]
 * [ 1: 0] : AVG_MODE[1:0]
 */
union pvt_triminfo_config_reg {
	struct {
		RO uint32_t avg_mode:2;
		RO uint32_t slope_con_vs:7;
		RO uint32_t slope_con_ts:7;
		RO uint32_t offset_con_ts:4;
		RO uint32_t bgr_i_con_ts:2;
		RO uint32_t bgr_tc_con_ts:2;
		RO uint32_t reserved:4;
		RO uint32_t calib_sel:2;
		RO uint32_t version:2;

		/* bits[ 1: 0] | R  | OTP information for AVG_MODE_TS			| Default Value = 2'b00 */
		/* bits[ 8: 2] | R  | Slope control for voltage output code		| Default Value = 0x00 */
		/* bits[15: 9] | R  | Slope control for temperature output code	| Default Value = 0x00 */
		/* bits[19:16] | R  | Offset for temperature output code		| Default Value = 0x0 */
		/* bits[21:20] | R  | BJT current								| Default Value = 2'b00 */
		/* bits[23:22] | R  | Reference voltage temperature coefficient	| Default Value = 2'b00 */
		/* bits[27:24] | R  | Reserved									| Default Value = 0x0 */
		/* bits[29:28] | R  | Indicated calibration for temperature		| Default Value = 2'b00 */
		/* bits[31:30] | R  | OTP information for Version				| Default Value = 2'b00 */
	};
	RO uint32_t val;
};

/**
 * TRIM_CONTROL		(Reset Value = 0x3000_0000)
 * [   31] : TRIM_BYPASS		/ [   30] : RSVD
 * [29:28] : AVG_MODE_TS[1:0]	/ [27:24] : RSVD
 * [23:22] : BGR_TC_CON_TS[1:0]	/ [21:20] : BGR_I_CON_TS[1:0]
 * [19:16] : OFSET_CON_TS[3:0]	/ [15: 9] : SLOPE_CON_TS[6:0]
 * [ 8: 2] : SLOPE_CON_VS[6:0]	/ [ 1: 0] : RSVD
 */
union pvt_triminfo_control_reg {
	struct {
		RO uint32_t reserved0:2;

		RW uint32_t slope_con_vs:7;
		RW uint32_t slope_con_ts:7;
		RW uint32_t offset_con_ts:4;
		RW uint32_t bgr_i_con_ts:2;
		RW uint32_t bgr_tc_con_ts:2;
		RO uint32_t reserved1:4;

		RW uint32_t avg_mode_ts:2;
		RO uint32_t reserved2:1;

		RW uint32_t trim_bypass:1;

		/* bits[ 1: 0] | -  | Reserved									| Reset Value = 2'b00 */
		/* bits[ 8: 2] | RW | Slope control for voltage output code		| Reset Value = 0x00 */
		/* bits[15: 9] | RW | Slope control for temperature output code	| Reset Value = 0x00 */
		/* bits[19:16] | RW | Offset for temperature output code		| Reset Value = 4'b0000 */
		/* bits[21:20] | RW | BJT current								| Reset Value = 2'b00 */
		/* bits[23:22] | RW | Reference voltage temperature coefficient	| Reset Value = 2'b00 */
		/* bits[27:24] | -  | Reserved									| Reset Value = 4'b0000 */
		/* bits[29:28] | RW | Temperature code averaging mode			| Reset Value = 2'b11 */
		/* bits[   30] | -  | Reserved									| Reset Value = 1'b0 */
		/* bits[   31] | RW | TRIMINFO registering bypass enable		| Reset Value = 1'b0 */
	};
	RW uint32_t val;
};

/**
 * ADC_CONTROL	(Reset Value = 0x0000_0000)
 * [31: 5] : RSVD				/ [ 4: 3] : AMUX_ADDR_TS[1:0]
 * [ 2: 1] : DMUX_ADDR_TS[1:0]	/ [    0] : TEST_MODE_TS
 */
union pvt_adc_control_reg {
	struct {
		RW uint32_t test_mode_ts:1;
		RW uint32_t dmux_addr_ts:2;
		RW uint32_t amux_addr_ts:2;
		RO uint32_t reserved:27;

		/* bits[    0] | RW | Test mode control input				| Reset Value = 1'b0 */
		/* bits[ 2: 1] | RW | MUX address control for digital value	| Reset Value = 2'b00 */
		/* bits[ 4: 3] | RW | MUX address control for analog value	| Reset Value = 2'b00 */
		/* bits[31: 5] | -  | Reserved								| Reset Value = 0x0000_000 */
	};
	RW uint32_t val;
};

/**
 * PVT_CONTROL	(Reset Value = 0x0000_8000)
 * [31:24] : RSVD				/ [23:22] : AVG_SEL_PS[1:0]
 * [21:20] : AVG_SEL_TS_VS[1:0]	/ [19:17] : THERM_DFS_MODE[2:0]
 * [   16] : THERM_DFS_EN		/ [15:13] : THERM_TRIP_MODE[2:0]
 * [   12] : THERM_TRIP_EN		/ [11: 9] : RSVD
 * [    8] : PS_EN				/ [ 7: 2] : RSVD
 * [    1] : TS_VS_SEL			/ [    0] : TS_VS_EN
 */
union pvt_pvt_control_reg {
	struct {
		RW uint32_t ts_vs_en:1;
		RW uint32_t ts_vs_sel:1;
		RO uint32_t reserved0:6;
		RW uint32_t ps_en:1;
		RO uint32_t reserved1:3;
		RW uint32_t therm_trip_en:1;
		RW uint32_t therm_trip_mode:3;
		RW uint32_t therm_dfs_en:1;
		RW uint32_t therm_dfs_mode:3;
		RW uint32_t avg_sel_ts_vs:2;
		RW uint32_t avg_sel_ps:2;
		RO uint32_t reserved2:8;

		/* bits[    0] | RW | Temperature/Voltage Sensor FSM enable/disable	| Reset Value = 0x0 */
		/* bits[    1] | RW | Selection between Temperature and Voltage Mode| Reset Value = 0x0 */
		/* bits[ 7: 2] | -  | Reserved										| Reset Value = 0x0 */
		/* bits[    8] | RW | Process Sensor FSM enable/disable				| Reset Value = 0x0 */
		/* bits[11: 9] | -  | Reserved										| Reset Value = 0x0 */
		/* bits[   12] | RW | Enables thermal tripping						| Reset Value = 0x0 */
		/* bits[15:13] | RW | Selects thermal tripping mode					| Reset Value = 0x0 */
		/* bits[   16] | RW | Enables thermal frequency scaling interrupt	| Reset Value = 0x0 */
		/* bits[19:17] | RW | Selects thermal frequency scaling mode		| Reset Value = 0x0 */
		/* bits[21:20] | RW | Sense Output Code Average Selection for TS/VS	| Reset Value = 0x0 */
		/* bits[23:22] | RW | Sense Output Code Average Selection for PS	| Reset Value = 0x0 */
		/* bits[31:24] | -  | Reserved										| Reset Value = 0x0 */
	};
	RW uint32_t val;
};

/**
 * SAMPLING_INTERVAL	(Reset Value = 0x0000F_4240)
 * [31: 0] : SAMP_INTVAL
 */
union pvt_sampling_interval_reg {
	struct {
		RW uint32_t samp_intval;

		/* bits[31: 0] | RW | Sampling interval for temperature	| Reset Value = 0x000F_4240 */
	};
	RW uint32_t val;
};

/**
 * SETUP_TIME_CNT	(Reset Value = 0x000A_1F40)
 * [31:28] : RSVD	/ [27:16] : SETUP_PRB_CNT[11:0]
 * [15: 0] : SETUP_TIME_CNT[15:0]
 */
union pvt_setup_time_cnt_reg {
	struct {
		RW uint32_t setup_time_cnt:16;
		RW uint32_t setup_prb_cnt:12;
		RO uint32_t reserved:4;

		/* bits[15: 0] | RW | Setup time counter		| Reset Value = 0x1F40 */
		/* bits[27:16] | RW | Probe Setup time counter	| Reset Value = 0xA */
		/* bits[31:28] | -  | Reserved					| Reset Value = 0x0 */
	};
	RW uint32_t val;
};

/**
 * HANDSHAKE_ON_EXP_CNT		(Reset Value = 0x0006_1A80)
 * [31: 0] : SOC_ON_EXP_CNT[31:0]
 */
union pvt_handshake_on_exp_cnt_reg {
	struct {
		RW uint32_t soc_on_exp_cnt;

		/* bits[31: 0] | RW | Timeout counter value	| Reset Value = 0x6_1A80 */
	};
	RW uint32_t val;
};

/**
 * PVT_CON_STATUS	(Reset Value = 0x0000_0003)
 * [31:28] : RSVD				/ [   27] : TIMEOUT_PS
 * [   26] : TIMEOUT_TS			/ [   25] : THERM_DFS
 * [   24] : THERM_TRIP			/ [23:19] : CUR_SENSING_PROBE_PS[4:0]
 * [   18] : RSVD				/ [17:12] : CUR_SENSING_PROBE_TS[5:0]
 * [11: 8] : PS_CON_STATE[3:0]	/ [ 7: 4] : TS_CON_STATE[3:0]
 * [ 3: 2] : RSVD				/ [    1] : RS_CON_IDLE
 * [    0] : TS_CON_IDLE
 */
union pvt_pvt_con_status_reg {
	struct {
		RO uint32_t ts_con_idle:1;
		RO uint32_t ps_con_idle:1;
		RO uint32_t reserved0:2;
		RO uint32_t ts_con_state:4;
		RO uint32_t ps_con_state:4;
		RO uint32_t cur_sensing_probe_ts:6;
		RO uint32_t reserved1:1;
		RO uint32_t cur_sensing_probe_ps:5;
		RO uint32_t therm_trip:1;
		RO uint32_t therm_dfs:1;
		RO uint32_t timeout_ts:1;
		RO uint32_t timeout_ps:1;
		RO uint32_t reserved2:4;

		/* bits[    0] | R  | Indicates that Temp/Vol sensing is idle	| Reset Value = 0x1 */
		/* bits[    1] | R  | Indicates that Process sensing is idle	| Reset Value = 0x1 */
		/* bits[ 3: 2] | -  | Reserved									| Reset Value = 0x0 */
		/* bits[ 7: 4] | R  | For debugging purpose to TS/VS FSM		| Reset Value = 0x0 */
		/* bits[11: 8] | R  | For debugging purpose to PS FSM			| Reset Value = 0x0 */
		/* bits[17:12] | R  | Probe that is currently sensing temp/vol	| Reset Value = 0x0 */
		/* bits[   18] | -  | Reserved									| Reset Value = 0x0 */
		/* bits[23:19] | R  | Probe that is currently sensing process	| Reset Value = 0x0 */
		/* bits[   24] | R  | Thermal trip status						| Reset Value = 0x0 */
		/* bits[   25] | R  | Thermal dynamic frequency scaling status	| Reset Value = 0x0 */
		/* bits[   26] | R  | TS/VS Handshake timeout					| Reset Value = 0x0 */
		/* bits[   27] | R  | PS Handshake timeout						| Reset Value = 0x0 */
		/* bits[31:28] | -  | Reserved									| Reset Value = 0x0 */
	};
	RO uint32_t val;
};

/**
 * EMUL_CON		(Reset Value = 0x0001_0000)
 * [31:16] : EMUL_NEXT_TIME[15:0]	/ [15: 4] : EMUL_NEXT_DATA[N-1:0]
 * [ 3: 1] : RSVD					/ [    0] : EMUL_EN
 */
union pvt_emul_con_reg {
	struct {
		RW uint32_t emul_en:1;
		RO uint32_t reserved:3;
		RW uint32_t emul_next_data:12;
		RW uint32_t emul_next_time:16;

		/* bits[    0] | RW | Enables emulation mode		| Reset Value = 0x0 */
		/* bits[ 3: 1] | -  | Reserved						| Reset Value = 0x0 */
		/* bits[15: 4] | RW | Next emulation data value		| Reset Value = 0x0 */
		/* bits[31:16] | RW | Emulation data after Tnext	| Reset Value = 0x1 */
	};
	RW uint32_t val;
};

/**
 * HANDSHAKE_OFF_EXP_CNT	(Reset Value = 0x0003_0D40)
 * [31: 0] : SOC_OFF_EXP_CNT[31:0]
 */
union pvt_handshake_off_exp_cnt {
	struct {
		RW uint32_t soc_off_exp_cnt;

		/* bits[31: 0] | RW | Timeout counter value		| Reset Value = 0x0003_0D40 */
	};
	RW uint32_t val;
};

/**
 * SOC_WAIT_INTERVAL	(Reset Value = 0x0000_0001)
 * [31:16] : RSVD	/ [15: 0] : SOC_WAIT_INTERVAL[15:0]
 */
union pvt_soc_wait_interval {
	struct {
		RW uint32_t soc_wait_interval:16;
		RO uint32_t reserved:16;

		/* bits[15: 0] | RW | SOC Wait Interval	| Reset Value = 0x01 */
		/* bits[31:16] | -  | Reserved			| Reset Value = 0x00 */
	};
	RW uint32_t val;
};

/* Structure of all PVT registers */
struct pvt_regs {
	union pvt_triminfo_config_reg		triminfo_config;
	union pvt_triminfo_control_reg		triminfo_control;
	union pvt_adc_control_reg			adc_control;
	union pvt_pvt_control_reg			pvt_control;
	union pvt_sampling_interval_reg		sampling_interval;
	union pvt_setup_time_cnt_reg		setup_time_cnt;
	union pvt_handshake_on_exp_cnt_reg	handshake_on_exp_cnt;
	union pvt_pvt_con_status_reg		pvt_con_status;
	union pvt_emul_con_reg				emul_con;
	union pvt_handshake_off_exp_cnt		handshake_off_exp_cnt;
	union pvt_soc_wait_interval			soc_wait_interval;
	uint8_t								reserved0[980];
	struct pvt_voltage_regs				voltage_regs[PVT_VOLTAGE_N_SENSOR];
	struct pvt_temperature_regs			temperature_regs[PVT_TEMPERATURE_N_SENSOR];
	uint8_t								reserved1[6144];
	struct pvt_process_regs				process_regs[PVT_PROCESS_N_SENSOR];

	/* Offset = 0x000 */
	/* Offset = 0x004 */
	/* Offset = 0x008 */
	/* Offset = 0x00C */
	/* Offset = 0x010 */
	/* Offset = 0x014 */
	/* Offset = 0x018 */
	/* Offset = 0x01C */
	/* Offset = 0x020 */
	/* Offset = 0x024 */
	/* Offset = 0x028 */
	/* Offset = 0x02C-0x3FC */
	/* Offset = 0x400-0x7FC */
	/* Offset = 0x800-0xFFC */
	/* Offset = 0x1000-0x27FC */
	/* Offset = 0x2800-0x3000 */
};
