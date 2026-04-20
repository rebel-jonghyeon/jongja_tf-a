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

#include "pvt_con_config.h"
#include "pvt_con_reg.h"
#include "pvt_con_reg_process.h"
#include "pvt_con_reg_temperature.h"
#include "pvt_con.h"
#include <interrupt.h>
#include <driver.h>
#include <assert.h>

#if defined(__TARGET_CP)
uint64_t pvt_base_address[PVT_N_INSTANCE] = {
	PVT_ROT,
	PVT0CTRL_DCL0,
	PVT1CTRL_DCL0,
	PVT0CTRL_DCL1,
	PVT1CTRL_DCL1,
};
#else
uint64_t pvt_base_address[PVT_N_INSTANCE] = {
	0xC0260000,		// IP_BLK_SYS_REG_BAT_BASE_CHIPET0 + PVT_ROT,
	0xC2120000,		// IP_BLK_SYS_REG_BAT_BASE_CHIPET0 + PVT0CTRL_DCL0,
	0xC2130000,		// IP_BLK_SYS_REG_BAT_BASE_CHIPET0 + PVT1CTRL_DCL0,
	0xC2920000,		// IP_BLK_SYS_REG_BAT_BASE_CHIPET0 + PVT0CTRL_DCL1,
	0xC2930000,		// IP_BLK_SYS_REG_BAT_BASE_CHIPET0 + PVT1CTRL_DCL1,
};
#endif

uint32_t pvt_n_sensors[PVT_N_INSTANCE * PVT_INSTANCE_OFFSET] = {
	/* Process | Voltage | Temperature*/
	32, 7, 7,	/* PVT_ROT */
	32, 3, 16,	/* PVT0_DCL0 */
	32, 0,  9,	/* PVT1_DCL0 */
	32, 1, 14,	/* PVT0_DCL1 */
	32, 3, 11,	/* PVT1_DCL1 */
};

/* All irqs are 'Level' sensitive interrupts. */
// static void pvt_callbacks[PVT_N_INSTANCE * PVT_TEMPERATURE_N_SENSOR];
struct pvt_irq pvt_irqs[PVT_N_INSTANCE] = {
	{	/* BLK_ROT */
		 73,	/* THERM_INTREQ */
		 74,	/* THERM_TRIP_INT */
		{		/* THERM_TRIP_P_INT */
			 75,  76,  77,  78,  79,  80,  81,  82,
			 83,  84,  85,  86,  87,  88,  89,  90,
		},
		 91,	/* THERM_DFS_INT */
		{		/* THERM_DFS_P_INT */
			 92,  93,  94,  95,  96,  97,  98,  99,
			100, 101, 102, 103, 104, 105, 106, 107,
		},
	},
	{	/* BLK_DCL0_PVT0 */
		396,	/* THERM_INTREQ */
		398,	/* THERM_TRIP_INT */
		{		/* THERM_TRIP_P_INT */
			348, 349, 350, 351, 352, 353, 354, 355,
			356, 357, 358, 359, 360, 361, 362, 363,
		},
		397,	/* THERM_DFS_INT */
		{		/* THERM_DFS_P_INT */
			332, 333, 334, 335, 336, 337, 338, 339,
			340, 341, 342, 343, 344, 345, 346, 347,
		},
	},
	{	/* BLK_DCL0_PVT1 */
		399,	/* THERM_INTREQ */
		401,	/* THERM_TRIP_INT */
		{		/* THERM_TRIP_P_INT */
			380, 381, 382, 383, 384, 385, 386, 387,
			388, 389, 390, 391, 392, 393, 394, 395,
		},
		400,	/* THERM_DFS_INT */
		{		/* THERM_DFS_P_INT */
			364, 365, 366, 367, 368, 369, 370, 371,
			372, 373, 374, 375, 376, 377, 378, 379,
		},
	},
	{	/* BLK_DCL1_PVT0 */
		556,	/* THERM_INTREQ*/
		558,	/* THERM_TRIP_INT */
		{		/* THERM_TRIP_P_INT */
			508, 509, 510, 511, 512, 513, 514, 515,
			516, 517, 518, 519, 520, 521, 522, 523,
		},
		557,	/* THERM_DFS_INT */
		{		/* THERM_DFS_P_INT */
			492, 493, 494, 495, 496, 497, 498, 499,
			500, 501, 502, 503, 504, 505, 506, 507,
		},
	},
	{	/* BLK_DCL1_PVT1 */
		559,	/* THERM_INTREQ */
		561,	/* THERM_TRIP_INT */
		{		/* THERM_TRIP_P_INT */
			540, 541, 542, 543, 544, 545, 546, 547,
			548, 549, 550, 551, 552, 553, 554, 555,
		},
		560,	/* THERM_DFS_INT */
		{		/* THERM_DFS_P_INT */
			524, 525, 526, 527, 528, 529, 530, 531,
			532, 533, 534, 535, 536, 537, 538, 539,
		},
	},
};

/*
 * FIXME: Temporary threshold value
 * This value is an arbitrary default and should be adjusted to
 * an appropriate level as desired by the user.
 */
uint32_t pvt_fall_threshold[PVT_N_INSTANCE][PVT_TEMPERATURE_N_FALL] = {
	{	/* BLK_ROT */
		55, 65, 75, 85,
		95, 105, 115, 125,	/* unused threshold */
	},
	{	/* BLK_DCL0_PVT0 */
		55, 65, 75, 85,
		95, 105, 115, 125,	/* unused threshold */
	},
	{	/* BLK_DCL0_PVT1 */
		55, 65, 75, 85,
		95, 105, 115, 125,	/* unused threshold */
	},
	{	/* BLK_DCL1_PVT0 */
		55, 65, 75, 85,
		95, 105, 115, 125,	/* unused threshold */
	},
	{	/* BLK_DCL1_PVT1 */
		55, 65, 75, 85,
		95, 105, 115, 125,	/* unused threshold */
	},
};

/*
 * FIXME: Temporary threshold value
 * This value is an arbitrary default and should be adjusted to
 * an appropriate level as desired by the user.
 */
uint32_t pvt_rise_threshold[PVT_N_INSTANCE][PVT_TEMPERATURE_N_RISE] = {
	{	/* BLK_ROT */
		60, 70, 80, 90,
		100, 110, 120, 130,	/* unused threshold */
	},
	{	/* BLK_DCL0_PVT0 */
		60, 70, 80, 90,
		100, 110, 120, 130,	/* unused threshold */
	},
	{	/* BLK_DCL0_PVT1 */
		60, 70, 80, 90,
		100, 110, 120, 130,	/* unused threshold */
	},
	{	/* BLK_DCL1_PVT0 */
		60, 70, 80, 90,
		100, 110, 120, 130,	/* unused threshold */
	},
	{	/* BLK_DCL1_PVT1 */
		60, 70, 80, 90,
		100, 110, 120, 130,	/* unused threshold */
	},
};

/**
 * PVT internal functions
 */

#if defined(__TARGET_CP)
static inline uint32_t pvt_get_instance_index(const struct pvt_regs *pvt_regs)
{
	for (uint32_t instance_index = 0; instance_index < PVT_N_INSTANCE; ++instance_index) {
		if (pvt_base_address[instance_index] == (uint64_t)pvt_regs) {
			return instance_index;
		}
	}
	return -1;
}
#else
static inline uint32_t pvt_get_instance_index(const struct pvt_regs *pvt_regs)
{
	for (uint32_t instance_index = 0; instance_index < PVT_N_INSTANCE; ++instance_index) {
		if (pvt_base_address[instance_index] == (uint32_t)pvt_regs) {
			return instance_index;
		}
	}
	return 0;
}
#endif

/**
 * PVT configuration functions
 */

/* calib_sel = 2-points */
static inline void pvt_set_trim_control(struct pvt_regs *pvt_regs)
{
	PVT_SELECT_TRIM_REGISTERING(pvt_regs);
	pvt_regs->triminfo_control.avg_mode_ts		= pvt_regs->triminfo_config.avg_mode;
	pvt_regs->triminfo_control.bgr_tc_con_ts	= pvt_regs->triminfo_config.bgr_tc_con_ts;
	pvt_regs->triminfo_control.bgr_i_con_ts		= pvt_regs->triminfo_config.bgr_i_con_ts;
	pvt_regs->triminfo_control.offset_con_ts	= pvt_regs->triminfo_config.offset_con_ts;
	pvt_regs->triminfo_control.slope_con_ts		= pvt_regs->triminfo_config.slope_con_ts;
	pvt_regs->triminfo_control.slope_con_vs		= pvt_regs->triminfo_config.slope_con_vs;
}

/**
 * PVT interface functions
 */

/**
 * Equation for reading process sensor
 *
 * Measured Frequency = (Frequency of CLK_TS / 200MHz) * Output_Code * Resolution (kHz)
 */
static inline uint32_t pvt_convert_to_process(struct pvt_regs *pvt_regs,
											  uint32_t sensor_id,
											  int32_t calib_data)
{
	uint32_t hfdiv_ps = pvt_regs->process_regs[sensor_id].probe_en_ps.hfdiv_ps;
	/* uint32_t clk_ts; */
	int32_t resolution;
	int32_t frequency;

	switch (hfdiv_ps) {
	case 0U:
		/* clk_ts		= 200;	(fixed) */
		resolution	= 16;	/* kHz */
		break;
	case 1U:
		/* clk_ts		= 200;	(fixed) */
		resolution	= 32;	/* kHz */
		break;
	default:
		break;
	}
	/* frequency = (clk_ts / 200) * calib_data * resolution; */
	frequency = 1 * calib_data * resolution;

	return frequency;
}

/**
 * Equation for reading voltage sensor
 *
 * Measured Voltage = (Slope * Output_Code * Resolution) + Offset
 * Measured Voltage = ((Slope * Output_Code * (Resolution * 10)) + (Offset * 10)) / 10
 *
 * e.g.
 * [Original Formula]
 *    VOL_RANGE_TS = 1b'1 ----> offset = 52.5
 *        450 (mV) = (1 * 0x31B * 0.5) + 52.5 (mV) {0x31B = 795}
 *                 = 397.5 + 52.5 = 450
 *    VOL_RANGE_TS = 1b'0 ----> offset = 42.5
 *        450 (mV) = (1 * 0x32F * 0.5) + 42.5 (mV) {0x32F = 815}
 *                 = 407.5 + 42.5 = 450
 *
 * [Changed Formula] -> (to avoid 'float' instructions)
 *    VOL_RANGE_TS = 1b'1 ---> offset = 52.5
 *        450      = ((1 * 0x31B * 5) + 525) / 10  {0x31B = 795}
 *                 = (3975 + 525) / 10 = 4500 / 10 = 450
 *    VOL_RANGE_TS = 1b'0 ---> offset = 42.5
 *        450      = ((1 * 0x32F * 5) + 425) / 10  {0x32F = 815}
 *                 = (4075 + 425) / 10 = 4500 / 10 = 450
 */
static inline uint32_t pvt_convert_to_voltage(struct pvt_regs *pvt_regs,
											  uint32_t sensor_id,
											  int32_t calib_data)
{
	uint32_t vol_range_ts = pvt_regs->voltage_regs[sensor_id].probe_en_vs.vol_range_ts;
	int32_t slope;
	int32_t resolution;
	int32_t offset;
	int32_t voltage;

	switch (vol_range_ts) {
	case 0U:
		slope		= 1;
		resolution	= 5;
		offset		= 425;
		break;
	case 1U:
		slope		= 1;
		resolution	= 5;
		offset		= 525;
		break;
	default:
		break;
	}
	voltage = ((slope * calib_data * resolution) + offset) / 10;

	return voltage;
}

/**
 * Equation for writing voltage sensor (for test)
 *
 * Input Code = (((10 * Voltage - 10 * Offset) / Slope) / Resolution) / 10
 */
static inline uint32_t pvt_convert_to_calibrated_voltage(struct pvt_regs *pvt_regs,
														 uint32_t sensor_id,
														 int32_t voltage)
{
	uint32_t vol_range_ts = pvt_regs->voltage_regs[sensor_id].probe_en_vs.vol_range_ts;
	int32_t slope;
	int32_t resolution;
	int32_t offset;
	int32_t input_code;

	switch (vol_range_ts) {
	case 0U:
		slope		= 1;
		resolution	= 5;
		offset		= 425;
		break;
	case 1U:
		slope		= 1;
		resolution	= 5;
		offset		= 525;
		break;
	default:
		break;
	}
	input_code = (((10 * voltage) -  offset) / slope) / resolution;

	return input_code;
}

/**
 * Equation for reading temperature sensor
 *
 * Calibration Equation for 1-Point Trimming
 *     Measured Temperature = ((Output_Code - t25) / resolution) + 25
 *
 * Calibration Equation for 2-Point Trimming
 *     Measured Temperature = ((Output_Code - t25) * (85 - 25) / (t85 - t25)) + 25
 *
 * Calibration Equation for 3-Point Trimming
 * if (Output_Code >= t25)
 *     Measured Temperature = ((Output_Code - t25) * (85 - 25) / (t85 - t25)) + 25
 * if (Output_Code < t25)
 *     Measured Temperature = ((Output_Code - t25) * (-40 - 25) / (tm40 - t25)) + 25
 */
static inline uint32_t pvt_convert_to_temperature(struct pvt_regs *pvt_regs,
												  uint32_t sensor_id,
												  int32_t calib_data)
{
	int32_t calib_sel	= PVT_GET_CALIB_SEL(pvt_regs);
	int32_t t25		= PVT_GET_TEMP_TRIMINFO_25(pvt_regs, sensor_id);
	int32_t t85		= PVT_GET_TEMP_TRIMINFO_85(pvt_regs, sensor_id);
	int32_t temperature;

	switch (calib_sel) {
	case 0U:	/* 1-point calibration */
		temperature = ((int32_t)calib_data - t25) / 16;	/* resolution = 16 */
		break;
	case 1U:	/* 2-point calibration */
		temperature = (((int32_t)calib_data - t25) * (85 - 25)) / (t85 - t25);
		break;
	case 2U:	/* 3-point calibration (Not implemented) */
		return -1;
	default:
		return -1;
	}
	temperature += 25;

	return temperature;
}

/**
 * Equation for writing temperature sensor
 *
 * Calibration Equation for 1-Point Trimming
 *     Input_Code = ((temperature - 25) * resolution) + t25
 *
 * Calibration Equation for 2-Point Trimming
 *     Input_Code = ((temperature - 25) * (t85 - t25) / (85 - 25)) + t25
 *
 * Calibration Equation for 3-Point Trimming
 * if (temperature >= 25)
 *     Input_Code = ((temperature - 25) * (t85 - t25) / (85 - 25)) + t25
 * if (temperature < 25)
 *     Input_Code = ((temperature - 25) * (tm40 - t25) / (-40 - 25)) + t25
 */
static inline uint32_t pvt_convert_to_calibrated_temperature(struct pvt_regs *pvt_regs,
															 uint32_t sensor_id,
															 int32_t temperature)
{
	int32_t calib_sel	= PVT_GET_CALIB_SEL(pvt_regs);
	int32_t t25		= PVT_GET_TEMP_TRIMINFO_25(pvt_regs, sensor_id);
	int32_t t85		= PVT_GET_TEMP_TRIMINFO_85(pvt_regs, sensor_id);
	int32_t calib_data;

	switch (calib_sel) {
	case 0U:
		calib_data = ((int32_t)temperature - 25) * 16;	/* resolution = 16 */
		break;
	case 1U:
		calib_data = (((int32_t)temperature - 25) * (t85 - t25)) / (85 - 25);
		break;
	case 2U:	/* 3-point calibration (Not implemented) */
		return -1;
	default:
		return -1;
	}
	calib_data += t25;

	return calib_data;
}

static inline uint32_t pvt_get_current_process(struct pvt_regs *pvt_regs,
											   uint32_t sensor_id)
{
	PVT_WAIT_UNTIL_VALID(PROC, pvt_regs, sensor_id);

	return pvt_convert_to_process(pvt_regs,
								  sensor_id,
								  pvt_regs->process_regs[sensor_id].current_proc.currprocess);
}

static inline uint32_t pvt_get_current_voltage(struct pvt_regs *pvt_regs,
											   uint32_t sensor_id)
{
	PVT_WAIT_UNTIL_VALID(VOLT, pvt_regs, sensor_id);

	return pvt_convert_to_voltage(pvt_regs,
								  sensor_id,
								  pvt_regs->voltage_regs[sensor_id].current_vol.currvoltage);
}

static inline uint32_t pvt_get_current_temperature(struct pvt_regs *pvt_regs,
												   uint32_t sensor_id)
{
	PVT_WAIT_UNTIL_VALID(TEMP, pvt_regs, sensor_id);

	return pvt_convert_to_temperature(pvt_regs,
									  sensor_id,
									  pvt_regs->temperature_regs[sensor_id].current_temp.currenttemp);
}

static inline void pvt_get_past_process(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t past_values[PVT_PROCESS_N_PAST])
{
	struct pvt_process_regs *proc_regs = &pvt_regs->process_regs[sensor_id];

	PVT_WAIT_UNTIL_VALID(PROC, pvt_regs, sensor_id);

	for (uint32_t past_index = 0; past_index < PVT_PROCESS_N_PAST; past_index += 2)
		past_values[past_index] = pvt_convert_to_process(pvt_regs,
														 sensor_id,
														 proc_regs->past_proc[past_index / 2].pastproc0);
	for (uint32_t past_index = 1; past_index < PVT_PROCESS_N_PAST; past_index += 2)
		past_values[past_index] = pvt_convert_to_process(pvt_regs,
														 sensor_id,
														 proc_regs->past_proc[past_index / 2].pastproc1);
}

static inline void pvt_get_past_voltage(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t past_values[PVT_VOLTAGE_N_PAST])
{
	struct pvt_voltage_regs *volt_regs = &pvt_regs->voltage_regs[sensor_id];

	PVT_WAIT_UNTIL_VALID(VOLT, pvt_regs, sensor_id);

	for (uint32_t past_index = 0; past_index < PVT_VOLTAGE_N_PAST; past_index += 2)
		past_values[past_index] = pvt_convert_to_voltage(pvt_regs,
														 sensor_id,
														 volt_regs->past_vol[past_index / 2].pastvol0);
	for (uint32_t past_index = 1; past_index < PVT_VOLTAGE_N_PAST; past_index += 2)
		past_values[past_index] = pvt_convert_to_voltage(pvt_regs,
														 sensor_id,
														 volt_regs->past_vol[past_index / 2].pastvol1);
}

static inline void pvt_get_past_temperature(struct pvt_regs *pvt_regs,
											uint32_t sensor_id,
											uint32_t past_values[PVT_TEMPERATURE_N_PAST])
{
	struct pvt_temperature_regs *temp_regs = &pvt_regs->temperature_regs[sensor_id];

	PVT_WAIT_UNTIL_VALID(TEMP, pvt_regs, sensor_id);

	for (uint32_t past_index = 0; past_index < PVT_TEMPERATURE_N_PAST; past_index += 2)
		past_values[past_index] = pvt_convert_to_temperature(pvt_regs,
															 sensor_id,
															 temp_regs->past_temp[past_index / 2].pasttemp0);
	for (uint32_t past_index = 1; past_index < PVT_TEMPERATURE_N_PAST; past_index += 2)
		past_values[past_index] = pvt_convert_to_temperature(pvt_regs,
															 sensor_id,
															 temp_regs->past_temp[past_index / 2].pasttemp1);
}

static inline void pvt_set_fall_threshold(struct pvt_regs *pvt_regs,
										  uint32_t sensor_id,
										  uint32_t fall_threshold[PVT_TEMPERATURE_N_FALL])
{
	struct pvt_temperature_regs *temp_regs = &pvt_regs->temperature_regs[sensor_id];

	for (uint32_t index = 0; index < PVT_TEMPERATURE_N_RISE; index += 2)
		temp_regs->threshold_temp_fall[(7 - index) / 2].thresholdlevel_fall0 =
														pvt_convert_to_calibrated_temperature(pvt_regs,
																							  sensor_id,
																							  fall_threshold[index]);
	for (uint32_t index = 1; index < PVT_TEMPERATURE_N_RISE; index += 2)
		temp_regs->threshold_temp_fall[(7 - index) / 2].thresholdlevel_fall1 =
														pvt_convert_to_calibrated_temperature(pvt_regs,
																							  sensor_id,
																							  fall_threshold[index]);
}

static inline void pvt_get_fall_threshold(struct pvt_regs *pvt_regs,
										  uint32_t sensor_id,
										  uint32_t fall_threshold[PVT_TEMPERATURE_N_FALL])
{
	struct pvt_temperature_regs *temp_regs = &pvt_regs->temperature_regs[sensor_id];

	for (uint32_t index = 0; index < PVT_TEMPERATURE_N_RISE; index += 2)
		fall_threshold[index] =
			pvt_convert_to_temperature(pvt_regs,
									   sensor_id,
									   temp_regs->threshold_temp_fall[(7 - index) / 2].thresholdlevel_fall0);
	for (uint32_t index = 1; index < PVT_TEMPERATURE_N_RISE; index += 2)
		fall_threshold[index] =
			pvt_convert_to_temperature(pvt_regs,
									   sensor_id,
									   temp_regs->threshold_temp_fall[(7 - index) / 2].thresholdlevel_fall1);
}

static inline void pvt_set_rise_threshold(struct pvt_regs *pvt_regs,
										  uint32_t sensor_id,
										  uint32_t rise_threshold[PVT_TEMPERATURE_N_RISE])
{
	struct pvt_temperature_regs *temp_regs = &pvt_regs->temperature_regs[sensor_id];

	for (uint32_t index = 0; index < PVT_TEMPERATURE_N_RISE; index += 2)
		temp_regs->threshold_temp_rise[(7 - index) / 2].thresholdlevel_rise0 =
														pvt_convert_to_calibrated_temperature(pvt_regs,
																							  sensor_id,
																							  rise_threshold[index]);
	for (uint32_t index = 1; index < PVT_TEMPERATURE_N_RISE; index += 2)
		temp_regs->threshold_temp_rise[(7 - index) / 2].thresholdlevel_rise1 =
														pvt_convert_to_calibrated_temperature(pvt_regs,
																							  sensor_id,
																							  rise_threshold[index]);
}

static inline void pvt_get_rise_threshold(struct pvt_regs *pvt_regs,
										  uint32_t sensor_id,
										  uint32_t rise_threshold[PVT_TEMPERATURE_N_RISE])
{
	struct pvt_temperature_regs *temp_regs = &pvt_regs->temperature_regs[sensor_id];

	for (uint32_t index = 0; index < PVT_TEMPERATURE_N_RISE; index += 2)
		rise_threshold[index] =
			pvt_convert_to_temperature(pvt_regs,
									   sensor_id,
									   temp_regs->threshold_temp_rise[(7 - index) / 2].thresholdlevel_rise0);
	for (uint32_t index = 1; index < PVT_TEMPERATURE_N_RISE; index += 2)
		rise_threshold[index] =
			pvt_convert_to_temperature(pvt_regs,
									   sensor_id,
									   temp_regs->threshold_temp_rise[(7 - index) / 2].thresholdlevel_rise1);
}

#if defined(__TARGET_CP)
/**
 * PVT IRQ related functions
 */

#define PVT_COMMON_IRQ_PRIO		(5)
#define PVT_ADDRESS_MASK		(0xFFFFFFFFFFFF0000ULL)
#define PVT_SENSOR_ID_MASK		(0x00000000000000FFULL)

/**
 * rise_threshold[7] = TRIP = DFS
 * intpend[7] = TRIP
 * intpend[8] = DFS
 */

uint32_t pvt_trip_flag[PVT_N_INSTANCE];
uint32_t pvt_dfs_flag[PVT_N_INSTANCE];

void pvt_trip_handler(void *cb_ref)
{
	struct pvt_regs *pvt_regs	= (struct pvt_regs *)((uint64_t)cb_ref & PVT_ADDRESS_MASK);
	uint32_t sensor_id			= (uint64_t)cb_ref & PVT_SENSOR_ID_MASK;
	uint32_t pvt_instance		= PVT_GET_INSTANCE(pvt_regs);

	assert(pvt_instance != -1);

	uint32_t flag				= 0x1 << sensor_id;
	uint32_t ulPreviousMask;

	ulPreviousMask = portENTER_CRITICAL_FROM_ISR();
	if (pvt_trip_flag[pvt_instance] & (0x1 << sensor_id)) {
		// printf("[Fall] pvt_trip_handler, pvt_instance = %u, sensor_id = %u\n", pvt_instance, sensor_id);
		PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 8, PVT_ENABLE);
		/* TBD: add pmu related works */
	} else {
		// printf("[Rise] pvt_trip_handler, pvt_instance = %u, sensor_id = %u\n", pvt_instance, sensor_id);
		PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 8, PVT_DISABLE);
	}
	pvt_trip_flag[pvt_instance] ^= flag;
	portEXIT_CRITICAL_FROM_ISR(ulPreviousMask);
}

void pvt_dfs_handler(void *cb_ref)
{
	struct pvt_regs *pvt_regs	= (struct pvt_regs *)((uint64_t)cb_ref & PVT_ADDRESS_MASK);
	uint32_t sensor_id			= (uint64_t)cb_ref & PVT_SENSOR_ID_MASK;
	uint32_t pvt_instance		= PVT_GET_INSTANCE(pvt_regs);

	assert(pvt_instance != -1);

	uint32_t flag				= 0x1 << sensor_id;
	uint32_t irq_num			= pvt_irqs[pvt_instance].intreq;
	uint32_t ulPreviousMask;

	ulPreviousMask = portENTER_CRITICAL_FROM_ISR();
	if (pvt_dfs_flag[pvt_instance] & flag) {
		// printf("[Fall] pvt_dfs_handler, pvt_instance = %u, sensor_id = %u\n", pvt_instance, sensor_id);
		gic_irq_enable(irq_num);

		/* TBD: change rise threshold after DFS occurred */
		pvt_rise_threshold[pvt_instance][7] = 85;
		pvt_set_rise_threshold(pvt_regs, sensor_id, pvt_rise_threshold[pvt_instance]);
	} else {
		// printf("[Rise] pvt_dfs_handler, pvt_instance = %u, sensor_id = %u\n", pvt_instance, sensor_id);
		gic_irq_disable(irq_num);

		/* TBD: change rise threshold after DFS occurred */
		pvt_rise_threshold[pvt_instance][7] = 75;
		pvt_set_rise_threshold(pvt_regs, sensor_id, pvt_rise_threshold[pvt_instance]);
	}
	pvt_dfs_flag[pvt_instance] ^= flag;
	portEXIT_CRITICAL_FROM_ISR(ulPreviousMask);
}

void pvt_intreq_handler(void *cb_ref)
{
	struct pvt_regs *pvt_regs	= (struct pvt_regs *)((uint64_t)cb_ref & PVT_ADDRESS_MASK);
	uint32_t pvt_instance		= PVT_GET_INSTANCE(pvt_regs);
	assert(pvt_instance != -1);
	uint32_t ulPreviousMask;

	// printf("pvt_intreq_handler, pvt_instance = %u\n", pvt_instance);

	ulPreviousMask = portENTER_CRITICAL_FROM_ISR();
	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_N_SENSOR(TEMP, pvt_instance); ++sensor_id) {
		/* Search the existstance of pending IRQ. */
		if (PVT_GET_INTREQ_PENDING(pvt_regs, sensor_id)) {
			/* Check the start of TRIP interrupt */
			// if (PVT_GET_INTERRUPT_PENDING(RISE, pvt_regs, sensor_id, 7)) {
				// PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 7, PVT_DISABLE);
				// pvt_trip_handler((void *)((uint64_t)pvt_regs + sensor_id));
			// }

			/* Check the start of DFS interrupt */
			// if (PVT_GET_INTERRUPT_PENDING(RISE, pvt_regs, sensor_id, 8)) {
				// PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 8, PVT_DISABLE);
				// pvt_dfs_handler((void *)((uint64_t)pvt_regs + sensor_id));
			// }

			/* Find the highest rise threshold */
			for (int32_t index = PVT_TEMPERATURE_N_RISE - 2; index > -1; --index) {
				/* If rise IRQ is occurred, */
				if (PVT_GET_INTERRUPT_PENDING(RISE, pvt_regs, sensor_id, index)) {
					// printf("rise threshold sensor_id = %u, index = %u\n", sensor_id, index);
					/* Clear pending bits */
					for (int32_t clear_index = 0; clear_index <= index; ++clear_index) {
						PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, clear_index, PVT_DISABLE);
						PVT_CONTROL_INTERRUPT(FALL, pvt_regs, sensor_id, clear_index, PVT_ENABLE);
						PVT_CLEAR_INTERRUPT(RISE, pvt_regs, sensor_id, index);
						PVT_CLEAR_INTERRUPT(FALL, pvt_regs, sensor_id, index);
					}
					for (int32_t clear_index = index + 1; clear_index < PVT_TEMPERATURE_N_RISE - 1; ++clear_index) {
						PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, clear_index, PVT_ENABLE);
						PVT_CONTROL_INTERRUPT(FALL, pvt_regs, sensor_id, clear_index, PVT_DISABLE);
						PVT_CLEAR_INTERRUPT(RISE, pvt_regs, sensor_id, index);
						PVT_CLEAR_INTERRUPT(FALL, pvt_regs, sensor_id, index);
					}
					break;
				}
			}

			/* Check the end of TRIP/DFS interrupt */
			if (PVT_GET_INTERRUPT_PENDING(FALL, pvt_regs, sensor_id, 7)) {
				// PVT_CLEAR_INTERRUPT(RISE, pvt_regs, sensor_id, 7);
				// PVT_CLEAR_INTERRUPT(RISE, pvt_regs, sensor_id, 8);
				PVT_CLEAR_INTERRUPT(FALL, pvt_regs, sensor_id, 7);
				// PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 7, PVT_DISABLE);
				// PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 8, PVT_DISABLE);
			}

			/* Find the lowest fall threshold */
			for (int32_t index = 0; index < PVT_TEMPERATURE_N_FALL; ++index) {
				/* If fall IRQ is occurred, */
				if (PVT_GET_INTERRUPT_PENDING(FALL, pvt_regs, sensor_id, index)) {
					// printf("fall threshold sensor_id = %u, index = %u\n", sensor_id, index);
					/* Clear pending bits */
					for (int32_t clear_index = 0; clear_index < index; ++clear_index) {
						PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, clear_index, PVT_DISABLE);
						PVT_CONTROL_INTERRUPT(FALL, pvt_regs, sensor_id, clear_index, PVT_ENABLE);
						PVT_CLEAR_INTERRUPT(RISE, pvt_regs, sensor_id, index);
						PVT_CLEAR_INTERRUPT(FALL, pvt_regs, sensor_id, index);
					}
					for (int32_t clear_index = index; clear_index < PVT_TEMPERATURE_N_FALL; ++clear_index) {
						PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, clear_index, PVT_ENABLE);
						PVT_CONTROL_INTERRUPT(FALL, pvt_regs, sensor_id, clear_index, PVT_DISABLE);
						PVT_CLEAR_INTERRUPT(RISE, pvt_regs, sensor_id, index);
						PVT_CLEAR_INTERRUPT(FALL, pvt_regs, sensor_id, index);
					}
					break;
				}
			}
		}
	}
	portEXIT_CRITICAL_FROM_ISR(ulPreviousMask);
}

void pvt_init_intreq(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance	= pvt_get_instance_index(pvt_regs);
	assert(pvt_instance != -1);
	uint32_t irq_num		= pvt_irqs[pvt_instance].intreq;

	connect_interrupt_with_handler(irq_num, PVT_COMMON_IRQ_PRIO, IRQ_TYPE_LEVEL,
								   pvt_intreq_handler, (void *)pvt_regs);

	/* Enable all thresholds */
	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(pvt_instance); ++sensor_id) {
		for (uint32_t threshold_idx = 0; threshold_idx < PVT_TEMPERATURE_N_RISE - 1; ++threshold_idx) {
			PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, threshold_idx, PVT_ENABLE);
		}
		for (uint32_t threshold_idx = 0; threshold_idx < PVT_TEMPERATURE_N_FALL; ++threshold_idx) {
			PVT_CONTROL_INTERRUPT(FALL, pvt_regs, sensor_id, threshold_idx, PVT_ENABLE);
		}
	}
}

static inline void pvt_init_trip_irq(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance	= pvt_get_instance_index(pvt_regs);
	assert(pvt_instance != -1);
	uint32_t irq_num		= pvt_irqs[pvt_instance].trip_int;

	/* TRIP_P_INT =	pending bit of TRIP_P_INT[0]
	 *				|| pending bit of TRIP_P_INT[1]
	 *				|| ...
	 *				|| pending bit of TRIP_P_INT[15]
	 */
	//connect_interrupt_with_handler(irq_num, PVT_COMMON_IRQ_PRIO, IRQ_TYPE_LEVEL,
	//							   pvt_trip_handler, NULL);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(pvt_instance); ++sensor_id) {
		irq_num = pvt_irqs[pvt_instance].trip_ints[sensor_id];
		connect_interrupt_with_handler(irq_num, PVT_COMMON_IRQ_PRIO, IRQ_TYPE_EDGE,
									   pvt_trip_handler, (void *)((uint64_t)pvt_regs + sensor_id));
	}

	PVT_SET_TRIP_PAST_THRESHOLD(pvt_regs, 1);
	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(pvt_instance); ++sensor_id) {
		PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 7, PVT_ENABLE);
	}
	PVT_ENABLE_TRIP_MODE(pvt_regs);
}

static inline void pvt_init_dfs_irq(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance	= pvt_get_instance_index(pvt_regs);
	assert(pvt_instance != -1);
	uint32_t irq_num		= pvt_irqs[pvt_instance].dfs_int;

	/* DFS_P_INT = pending bit of DFS_P_INT[0]
	 *			   || pending bit of DFS_P_INT[1]
	 *			   || ...
	 *			   || pending bit of DFS_P_INT[15]
	 */
	//connect_interrupt_with_handler(irq_num, PVT_COMMON_IRQ_PRIO, IRQ_TYPE_LEVEL,
	//							   pvt_dfs_handler, NULL);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(pvt_instance); ++sensor_id) {
		irq_num = pvt_irqs[pvt_instance].dfs_ints[sensor_id];
		connect_interrupt_with_handler(irq_num, PVT_COMMON_IRQ_PRIO, IRQ_TYPE_EDGE,
									   pvt_dfs_handler, (void *)((uint64_t)pvt_regs + sensor_id));
	}

	PVT_SET_DFS_PAST_THRESHOLD(pvt_regs, 1);
	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(pvt_instance); ++sensor_id) {
		PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 8, PVT_ENABLE);
	}
	PVT_ENABLE_DFS_MODE(pvt_regs);
}
#endif

/**
 * PVT init functions
 */

static inline void pvt_init_common(struct pvt_regs *pvt_regs)
{
	pvt_set_trim_control(pvt_regs);

	PVT_SET_SAMPLING_INTERVAL(pvt_regs, 0xF4240U);
	PVT_SET_SETUP_TIME(pvt_regs, 0x1F40U);
	PVT_SET_TIME_CNT(pvt_regs, 0xAU);
	PVT_SET_ON_EXP_CNT(pvt_regs, 0x61A80U);
	PVT_SET_OFF_EXP_CNT(pvt_regs, 0x30D40U);
	PVT_SET_WAIT_INTERVAL(pvt_regs, 0x1U);
}

static inline void pvt_init_proc(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = pvt_get_instance_index(pvt_regs);
	assert(pvt_instance != -1);

	PVT_SELECT_AVERAGE(PROC, pvt_regs, SINGLE);
	PVT_ENABLE_CONTROLLER(PROC, pvt_regs);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_PROC_N_SENSOR(pvt_instance); ++sensor_id) {
		PVT_SELECT_PROC_NORMAL_OUTPUT(pvt_regs, sensor_id);
		PVT_ENABLE_SENSOR(PROC, pvt_regs, sensor_id);
	}
}

static inline void pvt_init_volt(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = pvt_get_instance_index(pvt_regs);
	assert(pvt_instance != -1);

	PVT_SET_ANALOG_VOLTAGE_MUX(pvt_regs, 0U);
	PVT_SET_DIGITAL_VOLTAGE_MUX(pvt_regs, 0U);
	PVT_DISABLE_VOLTAGE_MONITORING(pvt_regs);

	PVT_SELECT_AVERAGE(VOLT, pvt_regs, SINGLE);
	PVT_ENABLE_CONTROLLER(VOLT, pvt_regs);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_VOLT_N_SENSOR(pvt_instance); ++sensor_id) {
		PVT_SELECT_045V(pvt_regs, sensor_id);
		PVT_ENABLE_SENSOR(VOLT, pvt_regs, sensor_id);
	}
}

static inline void pvt_init_temp(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = pvt_get_instance_index(pvt_regs);
	assert(pvt_instance != -1);

	PVT_DISABLE_CONTROLLER(TEMP, pvt_regs);
	PVT_SELECT_AVERAGE(TEMP, pvt_regs, SINGLE);
#if defined(__TARGET_CP)
	pvt_init_intreq(pvt_regs);
	pvt_init_trip_irq(pvt_regs);
	pvt_init_dfs_irq(pvt_regs);
#endif
	PVT_ENABLE_CONTROLLER(TEMP, pvt_regs);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_TEMP_N_SENSOR(pvt_instance); ++sensor_id) {
		PVT_DISABLE_SENSOR(TEMP, pvt_regs, sensor_id);
		pvt_set_fall_threshold(pvt_regs, sensor_id, pvt_fall_threshold[pvt_instance]);
		pvt_set_rise_threshold(pvt_regs, sensor_id, pvt_rise_threshold[pvt_instance]);
		PVT_ENABLE_SENSOR(TEMP, pvt_regs, sensor_id);
	}
}

/**
 * API
 */

uint32_t PVT_GET_INSTANCE(struct pvt_regs *pvt_regs)
{
	return pvt_get_instance_index(pvt_regs);
}

void PVT_CONTROL_RISE_INTERRUPT(struct pvt_regs *pvt_regs,
								uint32_t sensor_id,
								uint32_t index,
								uint32_t value)
{
	switch (index) {
	case 0U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_rise0 = value;
		break;
	case 1U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_rise1 = value;
		break;
	case 2U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_rise2 = value;
		break;
	case 3U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_rise3 = value;
		break;
	case 4U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_rise4 = value;
		break;
	case 5U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_rise5 = value;
		break;
	case 6U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_rise6 = value;
		break;
	case 7U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_rise7 = value;
		break;
	case 8U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_rise8 = value;
		break;
	default:
		break;
	}
}

void PVT_CONTROL_FALL_INTERRUPT(struct pvt_regs *pvt_regs,
								uint32_t sensor_id,
								uint32_t index,
								uint32_t value)
{
	switch (index) {
	case 0U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_fall0 = value;
		break;
	case 1U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_fall1 = value;
		break;
	case 2U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_fall2 = value;
		break;
	case 3U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_fall3 = value;
		break;
	case 4U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_fall4 = value;
		break;
	case 5U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_fall5 = value;
		break;
	case 6U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_fall6 = value;
		break;
	case 7U:
		pvt_regs->temperature_regs[sensor_id].inten.inten_fall7 = value;
		break;
	default:
		break;
	}
}

uint32_t PVT_GET_RISE_INTERRUPT_PENDING(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t index)
{
	return pvt_regs->temperature_regs[(sensor_id)].intpend.val & (0x1 << index);
}

uint32_t PVT_GET_FALL_INTERRUPT_PENDING(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t index)
{
	return pvt_regs->temperature_regs[(sensor_id)].intpend.val & (0x1 << (index + 16));
}

void PVT_CLEAR_RISE_INTERRUPT(struct pvt_regs *pvt_regs,
							  uint32_t sensor_id,
							  uint32_t index)
{
	pvt_regs->temperature_regs[sensor_id].intpend.val = (0x1 << index);
}

void PVT_CLEAR_FALL_INTERRUPT(struct pvt_regs *pvt_regs,
							  uint32_t sensor_id,
							  uint32_t index)
{
	pvt_regs->temperature_regs[sensor_id].intpend.val = (0x1 << (index + 16));
}

uint32_t PVT_GET_RISE_INTERRUPT_STATE(struct pvt_regs *pvt_regs,
									  uint32_t sensor_id,
									  uint32_t index)
{
	switch (index) {
	case 0U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_rise0 == PVT_ENABLE);
	case 1U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_rise1 == PVT_ENABLE);
	case 2U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_rise2 == PVT_ENABLE);
	case 3U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_rise3 == PVT_ENABLE);
	case 4U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_rise4 == PVT_ENABLE);
	case 5U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_rise5 == PVT_ENABLE);
	case 6U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_rise6 == PVT_ENABLE);
	case 7U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_rise7 == PVT_ENABLE);
	case 8U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_rise8 == PVT_ENABLE);
	default: return 0;
	}
}

uint32_t PVT_GET_FALL_INTERRUPT_STATE(struct pvt_regs *pvt_regs,
									  uint32_t sensor_id,
									  uint32_t index)
{
	switch (index) {
	case 0U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_fall0 == PVT_ENABLE);
	case 1U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_fall1 == PVT_ENABLE);
	case 2U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_fall2 == PVT_ENABLE);
	case 3U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_fall3 == PVT_ENABLE);
	case 4U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_fall4 == PVT_ENABLE);
	case 5U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_fall5 == PVT_ENABLE);
	case 6U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_fall6 == PVT_ENABLE);
	case 7U: return (((struct pvt_regs *)pvt_regs)->temperature_regs[(sensor_id)].intstat.intstate_fall7 == PVT_ENABLE);
	default: return 0;
	}
}

uint32_t PVT_CONVERT_TO_PROC(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t calib_data)
{
	return pvt_convert_to_process(pvt_regs, sensor_id, calib_data);
}

uint32_t PVT_CONVERT_TO_VOLT(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t calib_data)
{
	return pvt_convert_to_voltage(pvt_regs, sensor_id, calib_data);
}

uint32_t PVT_CONVERT_TO_CALIBRATED_VOLT(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t voltage)
{
	return pvt_convert_to_calibrated_voltage(pvt_regs, sensor_id, voltage);
}

uint32_t PVT_CONVERT_TO_TEMP(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t calib_data)
{
	return pvt_convert_to_temperature(pvt_regs, sensor_id, calib_data);
}

uint32_t PVT_CONVERT_TO_CALIBRATED_TEMP(struct pvt_regs *pvt_regs,
										uint32_t sensor_id,
										uint32_t temperature)
{
	return pvt_convert_to_calibrated_temperature(pvt_regs, sensor_id, temperature);
}

uint32_t PVT_GET_CURRENT_PROC_VALUE(struct pvt_regs *pvt_regs,
									uint32_t sensor_id)
{
	return pvt_get_current_process(pvt_regs, sensor_id);
}

uint32_t PVT_GET_CURRENT_VOLT_VALUE(struct pvt_regs *pvt_regs,
									uint32_t sensor_id)
{
	return pvt_get_current_voltage(pvt_regs, sensor_id);
}

uint32_t PVT_GET_CURRENT_TEMP_VALUE(struct pvt_regs *pvt_regs,
									uint32_t sensor_id)
{
	return pvt_get_current_temperature(pvt_regs, sensor_id);
}

void PVT_GET_PAST_PROC_VALUE(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t past_values[PVT_PROCESS_N_PAST])
{
	pvt_get_past_process(pvt_regs, sensor_id, past_values);
}

void PVT_GET_PAST_VOLT_VALUE(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t past_values[PVT_VOLTAGE_N_PAST])
{
	pvt_get_past_voltage(pvt_regs, sensor_id, past_values);
}

void PVT_GET_PAST_TEMP_VALUE(struct pvt_regs *pvt_regs,
							 uint32_t sensor_id,
							 uint32_t past_values[PVT_TEMPERATURE_N_PAST])
{
	pvt_get_past_temperature(pvt_regs, sensor_id, past_values);
}

void PVT_SET_FALL_THRESHOLD(struct pvt_regs *pvt_regs,
							uint32_t sensor_id,
							uint32_t fall_threshold[PVT_TEMPERATURE_N_FALL])
{
	pvt_set_fall_threshold(pvt_regs, sensor_id, fall_threshold);
}

void PVT_GET_FALL_THRESHOLD(struct pvt_regs *pvt_regs,
							uint32_t sensor_id,
							uint32_t fall_threshold[PVT_TEMPERATURE_N_FALL])
{
	pvt_get_fall_threshold(pvt_regs, sensor_id, fall_threshold);
}

void PVT_SET_RISE_THRESHOLD(struct pvt_regs *pvt_regs,
							uint32_t sensor_id,
							uint32_t rise_threshold[PVT_TEMPERATURE_N_RISE])
{
	pvt_set_rise_threshold(pvt_regs, sensor_id, rise_threshold);
}

void PVT_GET_RISE_THRESHOLD(struct pvt_regs *pvt_regs,
							uint32_t sensor_id,
							uint32_t rise_threshold[PVT_TEMPERATURE_N_RISE])
{
	pvt_get_rise_threshold(pvt_regs, sensor_id, rise_threshold);
}

int pvt_init(void)
{
	struct pvt_regs *pvt_regs;

#if defined(ZEBU)
	for (uint32_t index = 0; index < 1; ++index) {
#else
	for (uint32_t index = 0; index < PVT_N_INSTANCE; ++index) {
#endif
#if defined(__TARGET_CP)
		pvt_regs = (struct pvt_regs *)pvt_base_address[index];
#else
		pvt_regs = (struct pvt_regs *)(uintptr_t)pvt_base_address[index];
#endif

		pvt_init_common(pvt_regs);

		pvt_init_proc(pvt_regs);
		pvt_init_volt(pvt_regs);
		pvt_init_temp(pvt_regs);
	}

	return 0;
}

#ifndef ZEBU_POC
#if defined(__TARGET_CP)
DRIVER_INIT_ENTRY_DEFINE(5, pvt_init);
#endif
#endif /* ZEBU_POC */
