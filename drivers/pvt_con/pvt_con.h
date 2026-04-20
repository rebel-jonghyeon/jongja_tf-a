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

#include <stdint.h>
#include "pvt_con_config.h"

struct pvt_regs;

/**
 * PVT macros
 */

/* TRIMINFO_CONFIG */
#define PVT_GET_CALIB_SEL(_pvt_regs)					\
			((volatile struct pvt_regs *)(_pvt_regs))->triminfo_config.calib_sel

/* TRIMINFO_CONTROL */
	/* Select trim registering/bypass mode. */
#define PVT_SELECT_TRIM_REGISTERING(_pvt_regs)			\
			((volatile struct pvt_regs *)(_pvt_regs))->triminfo_control.trim_bypass	= PVT_REGISTERING
#define PVT_SELECT_TRIM_BYPASS(_pvt_regs)				\
			((volatile struct pvt_regs *)(_pvt_regs))->triminfo_control.trim_bypass	= PVT_BYPASS

/* ADC_CONTROL */
#define PVT_SET_ANALOG_VOLTAGE_MUX(_pvt_regs, _mux)		\
			((volatile struct pvt_regs *)(_pvt_regs))->adc_control.amux_addr_ts	= (_mux)
#define PVT_SET_DIGITAL_VOLTAGE_MUX(_pvt_regs, _mux)	\
			((volatile struct pvt_regs *)(_pvt_regs))->adc_control.dmux_addr_ts	= (_mux)
#define PVT_ENABLE_VOLTAGE_MONITORING(_pvt_regs)		\
			((volatile struct pvt_regs *)(_pvt_regs))->adc_control.test_mode_ts	= PVT_ENABLE
#define PVT_DISABLE_VOLTAGE_MONITORING(_pvt_regs)		\
			((volatile struct pvt_regs *)(_pvt_regs))->adc_control.test_mode_ts	= PVT_DISABLE

/* PVT_CONTROL */
	/* Select output average */
#define PVT_SELECT_PROC_AVERAGE(_pvt_regs, _count)		\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.avg_sel_ps	= PVT_##_count##_AVERAGE
#define PVT_SELECT_VOLT_AVERAGE(_pvt_regs, _count)		\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.avg_sel_ts_vs	= PVT_##_count##_AVERAGE
#define PVT_SELECT_TEMP_AVERAGE(_pvt_regs, _count)		\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.avg_sel_ts_vs	= PVT_##_count##_AVERAGE

	/* Control DFS mode.*/
#define PVT_SET_DFS_PAST_THRESHOLD(_pvt_regs, _count)	\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.therm_dfs_mode	= PVT_EXCEED_##_count##_PAST
#define PVT_ENABLE_DFS_MODE(_pvt_regs)					\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.therm_dfs_en		= PVT_ENABLE
#define PVT_DISABLE_DFS_MODE(_pvt_regs)					\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.therm_dfs_en		= PVT_DISABLE
#define PVT_IS_DFS_MODE(_pvt_regs)						\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.therm_dfs_en == PVT_ENABLE)

	/* Control TRIP mode. */
#define PVT_SET_TRIP_PAST_THRESHOLD(_pvt_regs, _count)	\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.therm_trip_mode	= PVT_EXCEED_##_count##_PAST
#define PVT_ENABLE_TRIP_MODE(_pvt_regs)					\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.therm_trip_en		= PVT_ENABLE
#define PVT_DISABLE_TRIP_MODE(_pvt_regs)				\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.therm_trip_en		= PVT_DISABLE
#define PVT_IS_TRIP_MODE(_pvt_regs)						\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.therm_trip_en == PVT_ENABLE)

	/* Enable the controller. */
#define PVT_ENABLE_PROC_CONTROLLER(_pvt_regs)										\
			PVT_DISABLE_PROC_CONTROLLER(_pvt_regs);									\
			while (!PVT_IS_PROC_CON_IDLE(_pvt_regs))								\
				;																	\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.ps_en		= PVT_ENABLE
#define PVT_ENABLE_VOLT_CONTROLLER(_pvt_regs)										\
			PVT_DISABLE_VOLT_CONTROLLER(_pvt_regs);									\
			PVT_SELECT_VOLT_CONTROLLER(_pvt_regs);									\
			while (!PVT_IS_VOLT_CON_IDLE(_pvt_regs))								\
				;																	\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.ts_vs_en	= PVT_ENABLE
#define PVT_ENABLE_TEMP_CONTROLLER(_pvt_regs)										\
			PVT_DISABLE_TEMP_CONTROLLER(_pvt_regs);									\
			PVT_SELECT_TEMP_CONTROLLER(_pvt_regs);									\
			while (!PVT_IS_TEMP_CON_IDLE(_pvt_regs))								\
				;																	\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.ts_vs_en	= PVT_ENABLE

	/* Disable the controller. */
#define PVT_DISABLE_PROC_CONTROLLER(_pvt_regs)			\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.ps_en		= PVT_DISABLE
#define PVT_DISABLE_VOLT_CONTROLLER(_pvt_regs)			\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.ts_vs_en	= PVT_DISABLE
#define PVT_DISABLE_TEMP_CONTROLLER(_pvt_regs)			\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.ts_vs_en	= PVT_DISABLE

	/* Select temperature/voltage sensor. */
#define PVT_SELECT_VOLT_CONTROLLER(_pvt_regs)			\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.ts_vs_sel	= PVT_VOLTAGE_MODE
#define PVT_SELECT_TEMP_CONTROLLER(_pvt_regs)			\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_control.ts_vs_sel	= PVT_TEMPERATURE_MODE

/* SAMPLING_INTERVAL */
/**
 * SAMP_INTVAL = Sampling interval for sensing temperature/voltage sensor.
 *
 * Clock frequency = 200 MHz
 * Default value   = 5 (ms) = 1/200 (sec) = 1,000,000 / 200,000,000 (sec)
 *                 = 1,000,000 = 0xF_4240
 */
#define PVT_SET_SAMPLING_INTERVAL(_pvt_regs, _interval)	\
			((volatile struct pvt_regs *)(_pvt_regs))->sampling_interval.samp_intval	= (_interval)

/* SETUP_TIME_CNT */
/**
 * SETUP_TIME = Time interval between 'EN_TS' and 'SOC_TS'.
 *     EN_TS       = Enable signal for temperature/voltage sensor
 *     SOC_TS      = Start signal of Conversion for temperature/voltage sensor
 *
 * Clock frequency = 200 MHz
 * Default value   = 40 (us) = 1/25,000 (sec) = 8,000 / 200,000,000 (sec)
 *                 = 8,000 = 0x1F40
 */
#define PVT_SET_SETUP_TIME(_pvt_regs, _setup_time)		\
			((volatile struct pvt_regs *)(_pvt_regs))->setup_time_cnt.setup_time_cnt	= (_setup_time)

/**
 * TIME_CNT = Time interval between 'BJT_SEL_TS' and 'SOC_TS'.
 *     BJT_SEL_TS  = Selection signal for temperature/voltage sensor
 *     SOC_TS      = Start signal of Conversion for temperature/voltage sensor
 *
 * Clock frequency = 200 MHz
 * Default value   = 10 (clocks) = 10 / 200,000,000 (sec) = 50 (ns)
 *                 = 10 = 0xA
 */
#define PVT_SET_TIME_CNT(_pvt_regs, _time_cnt)			\
			((volatile struct pvt_regs *)(_pvt_regs))->setup_time_cnt.setup_prb_cnt	= (_time_cnt)

/* HANDSHAKE_ON_EXP_CNT */
/**
 * (The controller uses sensors with a 'round robin' policy)
 * SOC_ON_EXP_CNT = Expiration (timeout) counter from 'SOC = 1' to 'EOC = 1'.
 *     SOC         = The start of conversion
 *     EOC         = The end of conversion
 *
 * Clock frequency = 200 MHz
 * Default value   = 2 (ms) = 1/500 (sec) = 400,000 / 200,000,000 (sec)
 *                 = 400,000 = 0x61A80
 */
#define PVT_SET_ON_EXP_CNT(_pvt_regs, _on_exp_cnt)		\
			((volatile struct pvt_regs *)(_pvt_regs))->handshake_on_exp_cnt.soc_on_exp_cnt	= (_on_exp_cnt)

/* HANDSHAKE_OFF_EXP_CNT */
/**
 * (The controller uses sensors with a 'round robin' policy)
 * SOC_OFF_EXP_CNT = Expiration (timeout) counter from 'SOC = 0' to 'EOC = 1'.
 *     SOC         = The start of conversion
 *     EOC         = The end of conversion
 *
 * Clock frequency = 200 MHz
 * Default value   = 1 (ms) = 1/1000 (sec) = 200,000 / 200,000,000 (sec)
 *                 = 200,000 = 0x30D40
 */
#define PVT_SET_OFF_EXP_CNT(_pvt_regs, _off_exp_cnt)	\
			((volatile struct pvt_regs *)(_pvt_regs))->handshake_off_exp_cnt.soc_off_exp_cnt	= (_off_exp_cnt)

/* SOC_WAIT_INTERVAL */
/**
 * (The controller uses sensors with a 'round robin' policy)
 * SOC_WAIT_INTERVAL = Wait interval between 'EOC = 1' and 'SOC = 0'.
 *     SOC         = The start of conversion
 *     EOC         = The end of conversion
 *
 * Clock frequency = 200 MHz
 * Default value   = 1 (clocks) = 1 / 200,000,000 (sec) = 5 (ns)
 *                 = 1 = 0x1
 */
#define PVT_SET_WAIT_INTERVAL(_pvt_regs, _interval)		\
			((volatile struct pvt_regs *)(_pvt_regs))->soc_wait_interval.soc_wait_interval	= (_interval)

/* PVT_CON_STATUS */
	/* Check if timeout occurred. */
#define PVT_IS_PROC_TIMEOUT_OCCURRED(_pvt_regs)			\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.timeout_ps == PVT_ENABLE)
#define PVT_IS_VOLT_TIMEOUT_OCCURRED(_pvt_regs)			\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.timeout_ts == PVT_ENABLE)
#define PVT_IS_TEMP_TIMEOUT_OCCURRED(_pvt_regs)			\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.timeout_ts == PVT_ENABLE)

	/* Check if DFS/TRIP occurred. */
#define PVT_IS_TEMP_DFS_OCCURRED(_pvt_regs)				\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.therm_dfs == PVT_ENABLE)
#define PVT_IS_TEMP_TRIP_OCCURRED(_pvt_regs)			\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.therm_trip == PVT_ENABLE)

	/* Get sensor id of currently detected sensor. */
#define PVT_GET_CURRENT_PROC_SENSOR_ID(_pvt_regs)		\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.cur_sensing_probe_ps
#define PVT_GET_CURRENT_VOLT_SENSOR_ID(_pvt_regs)		\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.cur_sensing_probe_ts
#define PVT_GET_CURRENT_TEMP_SENSOR_ID(_pvt_regs)		\
			((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.cur_sensing_probe_ts

	/* Get the controller state. */
#define PVT_GET_PROC_CON_STATE(_pvt_regs)				\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.ps_con_state == PVT_ENABLE)
#define PVT_GET_VOLT_CON_STATE(_pvt_regs)				\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.ts_con_state == PVT_ENABLE)
#define PVT_GET_TEMP_CON_STATE(_pvt_regs)				\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.ts_con_state == PVT_ENABLE)

	/* Check if the controller is idle. */
#define PVT_IS_PROC_CON_IDLE(_pvt_regs)					\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.ps_con_idle == PVT_ENABLE)
#define PVT_IS_VOLT_CON_IDLE(_pvt_regs)					\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.ts_con_idle == PVT_ENABLE)
#define PVT_IS_TEMP_CON_IDLE(_pvt_regs)					\
			(((volatile struct pvt_regs *)(_pvt_regs))->pvt_con_status.ts_con_idle == PVT_ENABLE)

/* EMUL_CON */
#define PVT_ENABLE_EMULATION_MODE(_pvt_regs)			\
			((volatile struct pvt_regs *)(_pvt_regs))->emul_con.emul_en	= PVT_ENABLE
#define PVT_DISABLE_EMULATION_MODE(_pvt_regs)			\
			((volatile struct pvt_regs *)(_pvt_regs))->emul_con.emul_en	= PVT_DISABLE
#define PVT_SET_NEXT_DATA(_pvt_regs, _next_data)		\
			((volatile struct pvt_regs *)(_pvt_regs))->emul_con.emul_next_data	= (_next_data)
#define PVT_SET_NEXT_TIME(_pvt_regs, _next_time)		\
			((volatile struct pvt_regs *)(pvt_regs))->emul_con.emul_next_time	= (_next_time)

/**
 * Process sensor related macros
 */

/**
 * | Control Value	| Hex	| Sensor Type		|
 * |----------------|-------|-------------------|
 * | 6b'00_0000		| 0x00	| INV_D0P7_LVT		|
 * | 6b'00_0001		| 0x01	| INV_D1_LVT		|
 * | 6b'00_0010		| 0x02	| INV_D2_LVT		|
 * | 6b'00_0011		| 0x03	| INV_D4_LVT		|
 * | 6b'00_0100		| 0x04	| INV_D8_LVT		|
 * | 6b'00_0101		| 0x05	| INV_D16_LVT		|
 * | 6b'00_0110		| 0x06	| INV_D0P7_RVT		|
 * | 6b'00_0111		| 0x07	| INV_D1_RVT		|
 * | 6b'00_1000		| 0x08	| INV_D2_RVT		|
 * | 6b'00_1001		| 0x09	| INV_D4_RVT		|
 * | 6b'00_1010		| 0x0A	| INV_D0P7_SLVT		|
 * | 6b'00_1011		| 0x0B	| INV_D1_SLVT		|
 * | 6b'00_1100		| 0x0C	| INV_D2_SLVT		|
 * | 6b'00_1101		| 0x0D	| INV_D4_SLVT		|
 * | 6b'00_1110		| 0x0E	| INV_D1_LVT_L06	|
 * | 6b'00_1111		| 0x0F	| INV_D4_LVT_L06	|
 * | 6b'01_0000		| 0x10	| INV_D1_RVT_L06	|
 * | 6b'01_0001		| 0x11	| INV_D4_RVT_L06	|
 * | 6b'01_0010		| 0x12	| INV_D1_SLVT_L06	|
 * | 6b'01_0011		| 0x13	| INV_D4_SLVT_L06	|
 * | 6b'01 0100		| 0x14	| DLY_D1_RVT_L06	|
 * | 6b'01 0101		| 0x15	| DLY_D4_RVT_L06	|
 * | 6b'01 0110		| 0x16	| NAND_D2_LVT		|
 * | 6b'01 0111		| 0x17	| NOR2_D2_LVT		|
 * | 6b'01 1000		| 0x18	| INV_D0P7_ULVT		|
 * | 6b'01 1001		| 0x19	| INV_D1_ULVT		|
 * | 6b'01 1010		| 0x1A	| INV_D2_ULVT		|
 * | 6b'01 1011		| 0x1B	| INV_D4_ULVT		|
 * | 6b'01 1100		| 0x1C	| INV_D1_ULVT_L06	|
 * | 6b'01 1101		| 0x1D	| INV_D2_ULVT_L06	|
 * | 6b'01 1110		| 0x1E	| NPG_LVT			|
 * | 6b'01 1111		| 0x1F	| PPG_LVT			|
 * | 6b'10 0000		| 0x20	| NPG_RVT			|
 * | 6b'10 0001		| 0x21	| PPG_RVT			|
 * | 6b'10 0010		| 0x22	| NPG_SLVT			|
 * | 6b'10 0011		| 0x23	| PPG_SLVT			|
 * | 6b'10 0100		| 0x24	| NPG_LVT_L06		|
 * | 6b'10 0101		| 0x25	| PPG_LVT_L06		|
 * | 6b'10 0110		| 0x26	| NPG_ULVT			|
 * | 6b'10 0111		| 0x27	| PPG_ULVT			|
 */

/* Pr_TRIMINFO */
#define PVT_GET_PROC_TRIMINFO(_pvt_regs, _sensor_id)			\
			((volatile struct pvt_regs *)(_pvt_regs))->process_regs[(_sensor_id)].triminfo.triminfo_ps

/* Pr_PROBE_EN_PS */
	/* Enable/disable the process sensor. */
#define PVT_ENABLE_PROC_SENSOR(_pvt_regs, _sensor_id)			\
			((volatile struct pvt_regs *)(_pvt_regs))->process_regs[(_sensor_id)].probe_en_ps.probe_en_ps = PVT_ENABLE
#define PVT_DISABLE_PROC_SENSOR(_pvt_regs, _sensor_id)			\
			((volatile struct pvt_regs *)(_pvt_regs))->process_regs[(_sensor_id)].probe_en_ps.probe_en_ps = PVT_DISABLE

	/* Select sensor output range. */
#define PVT_SELECT_PROC_NORMAL_OUTPUT(_pvt_regs, _sensor_id)	\
			((volatile struct pvt_regs *)(_pvt_regs))->process_regs[(_sensor_id)].probe_en_ps.hfdiv_ps	=	\
			PVT_PROCESS_NORMAL_OUTPUT
#define PVT_SELECT_PROC_HALF_OUTPUT(_pvt_regs, _sensor_id)		\
			((volatile struct pvt_regs *)(_pvt_regs))->process_regs[(_sensor_id)].probe_en_ps.hfdiv_ps	=	\
			PVT_PROCESS_HALF_OUTPUT

/* Pr_CURRENT_PROC */
/* static inline uint32_t pvt_get_current_process(struct pvt_regs *pvt_regs,
 *												  uint32_t sensor_id);
 */
uint32_t PVT_GET_CURRENT_PROC_VALUE(struct pvt_regs *pvt_regs,
									uint32_t sensor_id);

/* Pr_PS_STATUS */
#define PVT_IS_PROC_VALID(_pvt_regs, _sensor_id)				\
			(((volatile struct pvt_regs *)(_pvt_regs))->process_regs[(_sensor_id)].ps_status.ps_valid == PVT_ENABLE)

/* Pr_PAST_PROC */
/* static inline uint32_t *pvt_get_past_process(struct pvt_regs *pvt_regs,
 *												uint32_t sensor_id);
 */
void PVT_GET_PAST_PROC_VALUE(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t past_values[PVT_PROCESS_N_PAST]);

/**
 * Voltage sensor related macros
 */

/* Vr_TRIMINFO */
#define PVT_GET_VOLT_TRIMINFO(_pvt_regs, _sensor_id)		\
			((volatile struct pvt_regs *)(_pvt_regs))->voltage_regs[(_sensor_id)].triminfo.triminfo_vs

/* Vr_PROBE_EN_VS */
	/* Select input range of voltage sensor. */
#define PVT_SELECT_045V(_pvt_regs, _sensor_id)				\
			((volatile struct pvt_regs *)(_pvt_regs))->voltage_regs[(_sensor_id)].probe_en_vs.vol_range_ts	=	\
			PVT_VOLTAGE_RANGE_045V
#define PVT_SELECT_025V(_pvt_regs, _sensor_id)				\
			((volatile struct pvt_regs *)(_pvt_regs))->voltage_regs[(_sensor_id)].probe_en_vs.vol_range_ts	=	\
			PVT_VOLTAGE_RANGE_025V
	/* Enable/disable the voltage sensor. */
#define PVT_ENABLE_VOLT_SENSOR(_pvt_regs, _sensor_id)		\
			((volatile struct pvt_regs *)(_pvt_regs))->voltage_regs[(_sensor_id)].probe_en_vs.probe_en_vs = PVT_ENABLE
#define PVT_DISABLE_VOLT_SENSOR(_pvt_regs, _sensor_id)		\
			((volatile struct pvt_regs *)(_pvt_regs))->voltage_regs[(_sensor_id)].probe_en_vs.probe_en_vs = PVT_DISABLE

/* Vr_CURRENT_VOL */
/* static inline uint32_t pvt_get_current_voltage(struct pvt_regs *pvt_regs,
 *												  uint32_t sensor_id);
 */
uint32_t PVT_GET_CURRENT_VOLT_VALUE(struct pvt_regs *pvt_regs,
									uint32_t sensor_id);

/* Vr_VS_STATUS */
#define PVT_IS_VOLT_VALID(_pvt_regs, _sensor_id)			\
			(((volatile struct pvt_regs *)(_pvt_regs))->voltage_regs[(_sensor_id)].vs_status.vs_valid == PVT_ENABLE)

/* Vr_PAST_VOL */
/* static inline uint32_t *pvt_get_past_voltage(struct pvt_regs *pvt_regs,
 *												uint32_t sensor_id);
 */
void PVT_GET_PAST_VOLT_VALUE(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t past_values[PVT_VOLTAGE_N_PAST]);

/**
 * Temperature related macros
 */

/* Tr_TRIMINFO1 */
#define PVT_GET_TEMP_TRIMINFO_85(_pvt_regs, _sensor_id)		\
			((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].triminfo1.triminfo_85
#define PVT_GET_TEMP_TRIMINFO_25(_pvt_regs, _sensor_id)		\
			((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].triminfo1.triminfo_25
#define PVT_GET_TEMP_TRIMINFO_M40(_pvt_regs, _sensor_id)	\
			((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].triminfo2.triminfo_m40

/* Tr_PROBE_EN_TS */
	/* Control fast conversion mode. */
#define PVT_ENABLE_FAST_CONVERSION(_pvt_regs, _sensor_id)	\
			((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].probe_en_ts.en_cycle = PVT_ENABLE
#define PVT_DISABLE_FAST_CONVERSION(_pvt_regs, _sensor_id)	\
			((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].probe_en_ts.en_cycle = PVT_DISABLE
	/* Enable/disable the temperature sensor. */
#define PVT_ENABLE_TEMP_SENSOR(_pvt_regs, _sensor_id)		\
			((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].probe_en_ts.probe_en_ts = \
			PVT_ENABLE
#define PVT_DISABLE_TEMP_SENSOR(_pvt_regs, _sensor_id)		\
			((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].probe_en_ts.probe_en_ts = \
			PVT_DISABLE

/* Tr_INTEN */
	/* Control rise/fall interrupt. */
void PVT_CONTROL_RISE_INTERRUPT(struct pvt_regs *pvt_regs,
								uint32_t sensor_id,
								uint32_t index,
								uint32_t value);
void PVT_CONTROL_FALL_INTERRUPT(struct pvt_regs *pvt_regs,
								uint32_t sensor_id,
								uint32_t index,
								uint32_t value);
#define PVT_CONTROL_INTERRUPT(_rise_fall, _pvt_regs, _sensor_id, _index, _value)	\
			PVT_CONTROL_##_rise_fall##_INTERRUPT(_pvt_regs, _sensor_id, _index, _value)
#define PVT_CONTROL_ALL_INTERRUPT(_pvt_regs, _sensor_id, _value)	\
			((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].inten.val = (_value)

/* Tr_INTPEND */
	/* Check if rise/fall interrupt is pending. */
#define PVT_GET_INTREQ_PENDING(_pvt_regs, _sensor_id)	\
			(((struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].intpend.val)
uint32_t PVT_GET_RISE_INTERRUPT_PENDING(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t index);
uint32_t PVT_GET_FALL_INTERRUPT_PENDING(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t index);
#define PVT_GET_INTERRUPT_PENDING(_rise_fall, _pvt_regs, _sensor_id, _index)	\
			PVT_GET_##_rise_fall##_INTERRUPT_PENDING(_pvt_regs, _sensor_id, _index)
	/* Clear pending bit of rise/fall interrupt. */
void PVT_CLEAR_RISE_INTERRUPT(struct pvt_regs *pvt_regs,
							  uint32_t sensor_id,
							  uint32_t index);
void PVT_CLEAR_FALL_INTERRUPT(struct pvt_regs *pvt_regs,
							  uint32_t sensor_id,
							  uint32_t index);
#define PVT_CLEAR_INTERRUPT(_rise_fall, _pvt_regs, _sensor_id, _index)	\
			PVT_CLEAR_##_rise_fall##_INTERRUPT(_pvt_regs, _sensor_id, _index)
#define PVT_CLEAR_ALL_INTERRUPT(_pvt_regs, _sensor_id)	\
			((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].intpend.val = 0xFFFFFFFFU

/* Tr_INTSTAT */
	/* Check status of rise/fall interrupt. */
uint32_t PVT_GET_RISE_INTERRUPT_STATE(struct pvt_regs *pvt_regs,
									  uint32_t sensor_id,
									  uint32_t index);
uint32_t PVT_GET_FALL_INTERRUPT_STATE(struct pvt_regs *pvt_regs,
									  uint32_t sensor_id,
									  uint32_t index);

/* Tr_THRESHOLD_TEMP */
	/* Control rise/fall threshold of interrupt. */
/* static inline void pvt_set_fall_threshold(struct pvt_regs *pvt_regs,
 *											 uint32_t sensor_id,
 *											 uint32_t fall_threshold[PVT_TEMPERATURE_N_FALL]);
 */
void PVT_SET_FALL_THRESHOLD(struct pvt_regs *pvt_regs,
							uint32_t sensor_id,
							uint32_t fall_threshold[PVT_TEMPERATURE_N_FALL]);

/* static inline void pvt_get_fall_threshold(struct pvt_regs *pvt_regs,
 *											 uint32_t sensor_id,
 *											 uint32_t fall_threshold[PVT_TEMPERATURE_N_FALL]);
 */
void PVT_GET_FALL_THRESHOLD(struct pvt_regs *pvt_regs,
							uint32_t sensor_id,
							uint32_t fall_threshold[PVT_TEMPERATURE_N_FALL]);

/* static inline void pvt_set_rise_threshold(struct pvt_regs *pvt_regs,
 *											 uint32_t sensor_id,
 *											 uint32_t rise_threshold[PVT_TEMPERATURE_N_RISE]);
 */
void PVT_SET_RISE_THRESHOLD(struct pvt_regs *pvt_regs,
							uint32_t sensor_id,
							uint32_t rise_threshold[PVT_TEMPERATURE_N_RISE]);

/* static inline void pvt_get_rise_threshold(struct pvt_regs *pvt_regs,
 *											 uint32_t sensor_id,
 *											 uint32_t rise_threshold[PVT_TEMPERATURE_N_RISE]);
 */
void PVT_GET_RISE_THRESHOLD(struct pvt_regs *pvt_regs,
							uint32_t sensor_id,
							uint32_t rise_threshold[PVT_TEMPERATURE_N_RISE]);

/* Tr_CURRENT_TEMP */
/* static inline uint32_t pvt_get_current_temperature(struct pvt_regs *pvt_regs,
 *													  uint32_t sensor_id);
 */
uint32_t PVT_GET_CURRENT_TEMP_VALUE(struct pvt_regs *pvt_regs,
									uint32_t sensor_id);

/* Tr_TS_STATUS */
	/* Check if DFS/TRIP is occurred. */
#define PVT_IS_DFS_OCCURRED(_pvt_regs, _sensor_id)			\
			(((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].ts_status.therm_dfs_status == \
			PVT_ENABLE)
#define PVT_IS_TRIP_OCCURRED(_pvt_regs, _sensor_id)			\
			(((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].ts_status.therm_trip_status == \
			PVT_ENABLE)
	/* Check if temperature sensor is valid/ */
#define PVT_IS_TEMP_VALID(_pvt_regs, _sensor_id)			\
			(((volatile struct pvt_regs *)(_pvt_regs))->temperature_regs[(_sensor_id)].ts_status.ts_valid == \
			PVT_ENABLE)

/* Tr_PAST_TEMP */
/* static inline uint32_t *pvt_get_past_temperature(struct pvt_regs *pvt_regs,
 *													uint32_t sensor_id);
 */
void PVT_GET_PAST_TEMP_VALUE(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t past_values[PVT_TEMPERATURE_N_PAST]);

/**
 * Interrupt related macros
 */

struct pvt_irq {
	uint32_t intreq;
	uint32_t trip_int;
	uint32_t trip_ints[PVT_TEMPERATURE_N_SENSOR];
	uint32_t dfs_int;
	uint32_t dfs_ints[PVT_TEMPERATURE_N_SENSOR];
};

/**
 * PVT API
 */

/* TODO: gather all user macros */
/**
 * type			: { PROC, VOLT, TEMP, }
 * pvt_regs		: struct pvt_regs *
 * sensor_id	: uint32_t
 * past_values	: uint32_t [16]
 * count		: { SINGLE, TWO, FOUR, EIGHT, }
 * index		: { 0-7, }
 */

#define PVT_INSTANCE_OFFSET		(3)
#define PVT_PROC_OFFSET			(0)
#define PVT_VOLT_OFFSET			(1)
#define PVT_TEMP_OFFSET			(2)

#define PVT_GET_PROC_N_SENSOR(_pvt_instance)		\
			(pvt_n_sensors[((_pvt_instance) * PVT_INSTANCE_OFFSET) + PVT_PROC_OFFSET])
#define PVT_GET_VOLT_N_SENSOR(_pvt_instance)		\
			(pvt_n_sensors[((_pvt_instance) * PVT_INSTANCE_OFFSET) + PVT_VOLT_OFFSET])
#define PVT_GET_TEMP_N_SENSOR(_pvt_instance)		\
			(pvt_n_sensors[((_pvt_instance) * PVT_INSTANCE_OFFSET) + PVT_TEMP_OFFSET])
#define PVT_GET_N_SENSOR(_type, _pvt_instance)	PVT_GET_##_type##_N_SENSOR(_pvt_instance)

uint32_t PVT_CONVERT_TO_PROC(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t calib_data);
uint32_t PVT_CONVERT_TO_VOLT(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t calib_data);
uint32_t PVT_CONVERT_TO_CALIBRATED_VOLT(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t voltage);
uint32_t PVT_CONVERT_TO_TEMP(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t calib_data);
uint32_t PVT_CONVERT_TO_CALIBRATED_TEMP(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t temperature);

#define PVT_ENABLE_CONTROLLER(_type, _pvt_regs)					PVT_ENABLE_##_type##_CONTROLLER(_pvt_regs)
#define PVT_DISABLE_CONTROLLER(_type, _pvt_regs)				PVT_DISABLE_##_type##_CONTROLLER(_pvt_regs)

#define PVT_ENABLE_SENSOR(_type, _pvt_regs, _sensor_id)			PVT_ENABLE_##_type##_SENSOR(_pvt_regs, _sensor_id)
#define PVT_DISABLE_SENSOR(_type, _pvt_regs, _sensor_id)		PVT_DISABLE_##_type##_SENSOR(_pvt_regs, _sensor_id)

#define PVT_IS_VALID(_type, _pvt_regs, _sensor_id)				PVT_IS_##_type##_VALID(_pvt_regs, _sensor_id)
#define PVT_WAIT_UNTIL_VALID(_type, _pvt_regs, _sensor_id)						\
	do {																		\
		int retries = 100;														\
		while (!PVT_IS_VALID(_type, _pvt_regs, _sensor_id) && retries > 0) {	\
			retries--;															\
		}																		\
	} while (0)

#define PVT_GET_CURRENT_VALUE(_type, _pvt_regs, _sensor_id)		PVT_GET_CURRENT_##_type##_VALUE(_pvt_regs, _sensor_id)
#define PVT_GET_PAST_VALUE(_type, _pvt_regs, _sensor_id, _past_values)	\
													PVT_GET_PAST_##_type##_VALUE(_pvt_regs, _sensor_id, _past_values)
#define PVT_SELECT_AVERAGE(_type, _pvt_regs, _count)			PVT_SELECT_##_type##_AVERAGE(_pvt_regs, _count)

uint32_t PVT_GET_INSTANCE(struct pvt_regs *pvt_regs);

int pvt_init(void);
