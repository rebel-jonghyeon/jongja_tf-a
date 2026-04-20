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

#include "pvt_con.h"

#define DEV_CFG(dev)	((const struct pvt_samsung_device_config * const)(dev)->config)
#define DEV_DATA(dev)	((struct pvt_samsung_device_data *)(dev)->data)

struct pvt_samsung_device_config {
	uint64_t base;
};

struct pvt_samsung_device_data {
	uint64_t base;
};

uint64_t pvt_instances[PVT_N_INSTANCE] = {
	0x1FF0260000ULL,	/* PVT_ROT, */
	0x1FF2120000ULL,	/* PVT0CTRL_DCL0, */
	0x1FF2130000ULL,	/* PVT1CTRL_DCL0, */
	0x1FF2920000ULL,	/* PVT0CTRL_DCL1, */
	0x1FF2930000ULL,	/* PVT1CTRL_DCL1, */
};

uint32_t pvt_instance_n_sensors[PVT_N_INSTANCE * PVT_INSTANCE_OFFSET] = {
	/* Voltage | Temperature | Process */
	6, 7, 1,	/* PVT_ROT */
	3, 15, 1,	/* PVT0_DCL0 */
	0,  8, 1,	/* PVT1_DCL0 */
	1, 13, 1,	/* PVT0_DCL1 */
	3, 10, 1,	/* PVT1_DCL1 */
};

static uint32_t pvt_temp_default_threshold_rise[PVT_TEMPERATURE_N_RISE] = {
	2680U,	/* Rise0 =  87.5'C */
	2720U,	/* Rise1 =  90.0'C */
	2760U,	/* Rise2 =  92.5'C */
	2800U,	/* Rise3 =  95.0'C */
	2840U,	/* Rise4 =  97.5'C */
	2880U,	/* Rise5 = 100.0'C */
	2920U,	/* Rise6 = 102.5'C */
	3000U,	/* Rise7 = 107.5'C */
};

static uint32_t pvt_temp_default_threshold_fall[PVT_TEMPERATURE_N_FALL] = {
	2672U,	/* Fall0 =  87.0'C */
	2712U,	/* Fall1 =  89.5'C */
	2752U,	/* Fall2 =  92.0'C */
	2792U,	/* Fall3 =  94.5'C */
	2832U,	/* Fall4 =  97.0'C */
	2872U,	/* Fall5 =  99.5'C */
	2912U,	/* Fall6 = 102.0'C */
	2992U,	/* Fall7 = 107.0'C */
};

/**
 * PVT common functions
 */

/* TODO: Need to change index to Macro? */
static inline uint32_t pvt_get_instance_index(uint64_t pvt_addr)
{
	for (uint32_t instance_index = 0; instance_index < PVT_N_INSTANCE; ++instance_index) {
		if (pvt_instances[instance_index] == pvt_addr) {
			return instance_index;
		}
	}
	return -1;
}

/* calib_sel = 2-points */
static inline void pvt_set_trim_control(uint64_t pvt_addr)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;

	pvt_regs->triminfo_control.trim_bypass		= PVT_REGISTERING;
	pvt_regs->triminfo_control.avg_mode_ts		= pvt_regs->triminfo_config.avg_mode;
	pvt_regs->triminfo_control.bgr_tc_con_ts	= pvt_regs->triminfo_config.bgr_tc_con_ts;
	pvt_regs->triminfo_control.bgr_i_con_ts		= pvt_regs->triminfo_config.bgr_i_con_ts;
	pvt_regs->triminfo_control.offset_con_ts	= pvt_regs->triminfo_config.offset_con_ts;
	pvt_regs->triminfo_control.slope_con_ts		= pvt_regs->triminfo_config.slope_con_ts;
	pvt_regs->triminfo_control.slope_con_vs		= pvt_regs->triminfo_config.slope_con_vs;
}

/**
 * PVT Voltage
 */

static inline uint32_t pvt_vol_get_current_voltage(uint64_t pvt_addr,
												   uint32_t sensor_id)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_voltage_regs *volt_regs = &pvt_regs->voltage_regs[sensor_id];

	while (!volt_regs->vs_status.vs_valid)
		;

	return volt_regs->current_vol.currvoltage;
}

static inline uint32_t pvt_vol_get_past_voltage(uint64_t pvt_addr,
												uint32_t sensor_id,
												uint32_t past_index)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_voltage_regs *volt_regs = &pvt_regs->voltage_regs[sensor_id];

	if (!PVT_VOLTAGE_IS_VALID_PAST_INDEX(past_index))
		return -1;

	if (past_index & 0x1U)
		return volt_regs->past_vol[past_index / 2].pastvol1;
	else
		return volt_regs->past_vol[past_index / 2].pastvol0;
}

static inline void pvt_vol_init(uint64_t pvt_addr,
								uint32_t voltage_range,
								uint32_t sampling_interval,
								uint32_t average_selection_ts_vs)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_voltage_regs *volt_regs;

	/* Disable temperature/voltage sensors */
	pvt_regs->pvt_control.ts_vs_en = PVT_DISABLE;

	/* TODO: MUX address control for analog/digital */

	/* Re-initialize each voltage sensors */
	for (uint32_t sensor_id = 0; sensor_id < PVT_VOLTAGE_N_SENSOR; ++sensor_id) {
		if (!PVT_VOLTAGE_IS_VALID_SENSOR_ID(sensor_id))
			break;
		volt_regs = &pvt_regs->voltage_regs[sensor_id];

		/* Disable voltage sensor */
		volt_regs->probe_en_vs.probe_en_vs	= PVT_DISABLE;

		/* Select voltage sensor input range */
		volt_regs->probe_en_vs.vol_range_ts	= voltage_range;
		/* Enable voltage sensor */
		volt_regs->probe_en_vs.probe_en_vs	= PVT_ENABLE;
	}

	/* Select sampling interval */
	pvt_regs->sampling_interval.samp_intval = sampling_interval;

	/* Select average selection mode */
	pvt_regs->pvt_control.avg_sel_ts_vs	= average_selection_ts_vs;

	/* Check temperaeture/voltage sensing operation is idle */
	while (!pvt_regs->pvt_con_status.ts_con_idle)
		;

	/* Select voltage mode in pvt_control reg */
	pvt_regs->pvt_control.ts_vs_sel = PVT_VOLTAGE_MODE;

	/* Enable temperature/voltage sensors */
	pvt_regs->pvt_control.ts_vs_en = PVT_ENABLE;
}

/**
 * PVT Temperature APIs
 */

static inline uint32_t pvt_temp_get_rise_fall_index(uint32_t value)
{
	/* Rise threshold */
	for (uint32_t n = 0; n < PVT_TEMPERATURE_N_RISE; ++n) {
		if (value & (1 << n)) {
			return n;
		}
	}

	/* Fall threshold */
	for (uint32_t n = 16; n < 16 + PVT_TEMPERATURE_N_FALL; ++n) {
		if (value & (1 << n)) {
			return n - 8;
		}
	}

	return -1;
}

static inline uint32_t pvt_temp_calibration(uint64_t pvt_addr,
											uint32_t sensor_id,
											uint32_t calib_sel,
											uint32_t target_temp)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_temperature_regs *temp_regs = &pvt_regs->temperature_regs[sensor_id];

	uint32_t t25			= temp_regs->triminfo1.triminfo_25;
	uint32_t t125			= temp_regs->triminfo1.triminfo_125;
	uint32_t calibration;

	switch (calib_sel) {
	case 0U:	/* 1-point calibration */
		calibration = (target_temp - t25) / 16;
		break;
	case 1U:	/* 2-point calibration */
		calibration = ((target_temp - t25) * 100) / (t125 - t25);
		break;
	case 2U:	/* 3-point calibration (Not implemented) */
	default:
		return -1;
	}
	calibration += 25;

	return calibration;
}

static inline uint32_t pvt_temp_reverse_calibration(uint64_t pvt_addr,
													uint32_t sensor_id,
													uint32_t calib_sel,
													uint32_t target_temp)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_temperature_regs *temp_regs = &pvt_regs->temperature_regs[sensor_id];

	uint32_t t25			= temp_regs->triminfo1.triminfo_25;
	uint32_t t125			= temp_regs->triminfo1.triminfo_125;
	uint32_t reverse_calibration;

	switch (calib_sel) {
	case 0U:	/* 1-point calibration */
		reverse_calibration = (target_temp - 25) * 16;
		break;
	case 1U:	/* 2-point calibration */
		reverse_calibration = ((target_temp - 25) * (t125 - t25)) * 100;
		break;
	case 2U:	/* 3-point calibration (Not implemented) */
	default:
		return -1;
	}
	reverse_calibration += t25;

	return reverse_calibration;
}

static inline uint32_t pvt_temp_get_current_temperature(uint64_t pvt_addr,
														uint32_t sensor_id)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_temperature_regs *temp_regs;

	uint32_t calib_sel = pvt_regs->triminfo_config.calib_sel;

	temp_regs = &pvt_regs->temperature_regs[sensor_id];

	while (!temp_regs->ts_status.ts_valid)
		;

	return pvt_temp_reverse_calibration(pvt_addr,
										sensor_id,
										calib_sel,
										temp_regs->current_temp.currenttemp);
}

static inline uint32_t pvt_temp_get_past_temperature(uint64_t pvt_addr,
													 uint32_t sensor_id,
													 uint32_t index)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_temperature_regs *temp_regs;

	uint32_t calib_sel = pvt_regs->triminfo_config.calib_sel;

	temp_regs = &pvt_regs->temperature_regs[sensor_id];

	if (index & 0x1U)
		return pvt_temp_reverse_calibration(pvt_addr,
											sensor_id,
											calib_sel,
											temp_regs->past_temp[index / 2].pasttemp1);
	else
		return pvt_temp_reverse_calibration(pvt_addr,
											sensor_id,
											calib_sel,
											temp_regs->past_temp[index / 2].pasttemp0);
}

static inline void pvt_temp_set_fall_threshold(uint64_t pvt_addr,
											   uint32_t sensor_id,
											   uint32_t calib_sel,
											   uint32_t index,
											   uint32_t threshold)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_temperature_regs *temp_regs;

	threshold = pvt_temp_calibration(pvt_addr, sensor_id, calib_sel, threshold);

	temp_regs = &pvt_regs->temperature_regs[sensor_id];

	if (index & 0x1U)
		temp_regs->threshold_temp_fall[(7 - index) / 2].thresholdlevel_fall1 = threshold;
	else
		temp_regs->threshold_temp_fall[(7 - index) / 2].thresholdlevel_fall0 = threshold;
}

static inline void pvt_temp_set_rise_threshold(uint64_t pvt_addr,
											   uint32_t sensor_id,
											   int32_t calib_sel,
											   uint32_t index,
											   uint32_t threshold)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_temperature_regs *temp_regs;

	threshold = pvt_temp_calibration(pvt_addr, sensor_id, calib_sel, threshold);

	temp_regs = &pvt_regs->temperature_regs[sensor_id];

	if (index & 0x1U)
		temp_regs->threshold_temp_rise[(7 - index) / 2].thresholdlevel_rise1 = threshold;
	else
		temp_regs->threshold_temp_rise[(7 - index) / 2].thresholdlevel_rise0 = threshold;
}

static inline void pvt_temp_init(uint64_t pvt_addr,
								 uint32_t fast_conversion,
								 uint32_t dfs_mode,
								 uint32_t dfs_enable,
								 uint32_t trip_mode,
								 uint32_t trip_enable,
								 uint32_t sampling_interval,
								 uint32_t average_selection_ts_vs)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_temperature_regs *temp_regs;

	uint32_t calib_sel = pvt_regs->triminfo_config.calib_sel;

	/* Disable temperature/voltage sensors */
	pvt_regs->pvt_control.ts_vs_en = PVT_DISABLE;

	/* TODO: Get first interrupt number for each types */

	/* Enable interrupts */
	for (uint32_t sensor_id = 0; sensor_id < PVT_TEMPERATURE_N_SENSOR; ++sensor_id) {
		if (!PVT_TEMPERATURE_IS_VALID_SENSOR_ID(sensor_id))
			break;
		temp_regs = &pvt_regs->temperature_regs[sensor_id];

		/* Disable temperature sensor */
		temp_regs->probe_en_ts.probe_en_ts = PVT_DISABLE;

		pvt_temp_set_fall_threshold(pvt_addr, sensor_id, calib_sel, 0, pvt_temp_default_threshold_fall[0]);
		pvt_temp_set_fall_threshold(pvt_addr, sensor_id, calib_sel, 1, pvt_temp_default_threshold_fall[1]);
		pvt_temp_set_fall_threshold(pvt_addr, sensor_id, calib_sel, 2, pvt_temp_default_threshold_fall[2]);
		pvt_temp_set_fall_threshold(pvt_addr, sensor_id, calib_sel, 3, pvt_temp_default_threshold_fall[3]);
		pvt_temp_set_fall_threshold(pvt_addr, sensor_id, calib_sel, 4, pvt_temp_default_threshold_fall[4]);
		pvt_temp_set_fall_threshold(pvt_addr, sensor_id, calib_sel, 5, pvt_temp_default_threshold_fall[5]);
		pvt_temp_set_fall_threshold(pvt_addr, sensor_id, calib_sel, 6, pvt_temp_default_threshold_fall[6]);
		pvt_temp_set_fall_threshold(pvt_addr, sensor_id, calib_sel, 7, pvt_temp_default_threshold_fall[7]);

		pvt_temp_set_rise_threshold(pvt_addr, sensor_id, calib_sel, 0, pvt_temp_default_threshold_rise[0]);
		pvt_temp_set_rise_threshold(pvt_addr, sensor_id, calib_sel, 1, pvt_temp_default_threshold_rise[1]);
		pvt_temp_set_rise_threshold(pvt_addr, sensor_id, calib_sel, 2, pvt_temp_default_threshold_rise[2]);
		pvt_temp_set_rise_threshold(pvt_addr, sensor_id, calib_sel, 3, pvt_temp_default_threshold_rise[3]);
		pvt_temp_set_rise_threshold(pvt_addr, sensor_id, calib_sel, 4, pvt_temp_default_threshold_rise[4]);
		pvt_temp_set_rise_threshold(pvt_addr, sensor_id, calib_sel, 5, pvt_temp_default_threshold_rise[5]);
		pvt_temp_set_rise_threshold(pvt_addr, sensor_id, calib_sel, 6, pvt_temp_default_threshold_rise[6]);
		pvt_temp_set_rise_threshold(pvt_addr, sensor_id, calib_sel, 7, pvt_temp_default_threshold_rise[7]);

		/* Enable fast conversion mode */
		temp_regs->probe_en_ts.en_cycle = fast_conversion;
		/* Enable temperature sensor */
		temp_regs->probe_en_ts.probe_en_ts = PVT_ENABLE;
	}

	/* Enable DFS mode */
	pvt_regs->pvt_control.therm_dfs_mode	= dfs_mode;
	pvt_regs->pvt_control.therm_dfs_en		= dfs_enable;

	/* Enable Trip mode */
	pvt_regs->pvt_control.therm_trip_mode	= trip_mode;
	pvt_regs->pvt_control.therm_trip_en		= trip_enable;

	/* Select sampling interval (5ms = 0x000F_4240U = Default) */
	pvt_regs->sampling_interval.samp_intval = sampling_interval;

	/* Select average selection mode */
	pvt_regs->pvt_control.avg_sel_ts_vs		= average_selection_ts_vs;

	/* Check temperaeture/voltage sensing operation is idle */
	while (!pvt_regs->pvt_con_status.ts_con_idle)
		;

	/* Select temperature mode in pvt_control reg */
	pvt_regs->pvt_control.ts_vs_sel = PVT_TEMPERATURE_MODE;
	/* Enable temperature/voltage sensors */
	pvt_regs->pvt_control.ts_vs_en = PVT_ENABLE;
}

/**
 * PVT Process
 */

static inline uint32_t pvt_proc_get_current_process(uint64_t pvt_addr,
													uint32_t sensor_id)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_process_regs *proc_regs = &pvt_regs->process_regs[sensor_id];

	while (!proc_regs->ps_status.ps_valid)
		;

	return proc_regs->current_proc.currprocess;
}

static inline uint32_t pvt_proc_get_past_process(uint64_t pvt_addr,
												 uint32_t sensor_id,
												 uint32_t past_index)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_process_regs *proc_regs = &pvt_regs->process_regs[sensor_id];

	if (!PVT_PROCESS_IS_VALID_INDEX(past_index)) {
		return -1;
	}

	if (past_index & 0x1U)
		return proc_regs->past_proc[past_index / 2].pastproc1;
	else
		return proc_regs->past_proc[past_index / 2].pastproc0;
}

static inline void pvt_proc_init(uint64_t pvt_addr,
								 uint32_t process_range,
								 uint32_t sampling_interval,
								 uint32_t average_selection_ps)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;
	volatile struct pvt_process_regs *proc_regs;

	/* Disable process sensors */
	pvt_regs->pvt_control.ps_en = PVT_DISABLE;

	for (uint32_t sensor_id = 0; sensor_id < PVT_PROCESS_N_SENSOR; ++sensor_id) {
		if (!PVT_PROCESS_IS_VALID_SENSOR_ID(sensor_id))
			break;
		proc_regs = &pvt_regs->process_regs[sensor_id];

		/* Disable process sensor */
		proc_regs->probe_en_ps.probe_en_ps = PVT_DISABLE;

		/* Select process output range */
		proc_regs->probe_en_ps.hfdiv_ps = process_range;
		/* Enable process sensor */
		proc_regs->probe_en_ps.probe_en_ps = PVT_ENABLE;
	}

	/* Select sampling interval (5ms = 0x000F_4240U = Default) */
	pvt_regs->sampling_interval.samp_intval = sampling_interval;

	/* Check process sensing operation is idle */
	while (!pvt_regs->pvt_con_status.ps_con_idle)
		;

	/* Select average selection mode */
	pvt_regs->pvt_control.avg_sel_ps = average_selection_ps;

	/* Enable process sensors */
	pvt_regs->pvt_control.ps_en = PVT_ENABLE;
}

/**
 * PVT APIs
 */

static int pvt_init(const struct device *dev)
{
	const struct pvt_samsung_device_config *config = DEV_CFG(dev);
	uint64_t pvt_addr = config->base;

	/* Read OTP & Write to trim_control */
	pvt_set_trim_control(pvt_addr);

	/* By default, use Temperature sensors & Process sensors */
	/*
	 * pvt_vol_init(pvt_addr,
	 *				PVT_VOLTAGE_RANGE_045V_090V,
	 *				0x000F4240U,
	 *				PVT_NONE_AVERAGE);
	 */
	pvt_temp_init(pvt_addr,
				  PVT_ENABLE,
				  PVT_EXCEED_ONLY_CURRENT,
				  PVT_ENABLE,
				  PVT_EXCEED_ONLY_CURRENT,
				  PVT_ENABLE,
				  0x000F4240U,
				  PVT_NONE_AVERAGE);
	pvt_proc_init(pvt_addr,
				  PVT_PROCESS_NORMAL_OUTPUT,
				  0x000F4240U,
				  PVT_NONE_AVERAGE);

	return 0;
}

/* Enable sensor */
void pvt_vol_enable_sensor(uint64_t pvt_addr,
						   uint32_t voltage_range,
						   uint32_t sampling_interval,
						   uint32_t average_selection_ts_vs)
{
	pvt_vol_init(pvt_addr,
				 voltage_range,
				 sampling_interval,
				 average_selection_ts_vs);
}

void pvt_temp_enable_sensor(uint64_t pvt_addr,
							uint32_t fast_conversion,
							uint32_t dfs_mode,
							uint32_t dfs_enable,
							uint32_t trip_mode,
							uint32_t trip_enable,
							uint32_t sampling_interval,
							uint32_t average_selection_ts_vs)
{
	pvt_temp_init(pvt_addr,
				  fast_conversion,
				  dfs_mode,
				  dfs_enable,
				  trip_mode,
				  trip_enable,
				  sampling_interval,
				  average_selection_ts_vs);
}

void pvt_proc_enable_sensor(uint64_t pvt_addr,
							uint32_t process_range,
							uint32_t sampling_interval,
							uint32_t average_selection_ps)
{
	pvt_proc_init(pvt_addr,
				  process_range,
				  sampling_interval,
				  average_selection_ps);
}

/* Get current value */
uint32_t pvt_vol_get_current_value(uint64_t pvt_addr,
								   uint32_t sensor_id)
{
	return pvt_vol_get_current_voltage(pvt_addr, sensor_id);
}

uint32_t pvt_temp_get_current_value(uint64_t pvt_addr,
									uint32_t sensor_id)
{
	return pvt_temp_get_current_temperature(pvt_addr, sensor_id);
}

uint32_t pvt_proc_get_current_value(uint64_t pvt_addr,
									uint32_t sensor_id)
{
	return pvt_proc_get_current_process(pvt_addr, sensor_id);
}

/* Get past value */
uint32_t pvt_vol_get_past_value(uint64_t pvt_addr,
								uint32_t sensor_id,
								uint32_t past_index)
{
	return pvt_vol_get_past_voltage(pvt_addr, sensor_id, past_index);
}

uint32_t pvt_temp_get_past_value(uint64_t pvt_addr,
								 uint32_t sensor_id,
								 uint32_t past_index)
{
	return pvt_vol_get_past_voltage(pvt_addr, sensor_id, past_index);
}

uint32_t pvt_proc_get_past_value(uint64_t pvt_addr,
								 uint32_t sensor_id,
								 uint32_t past_index)
{
	return pvt_proc_get_past_process(pvt_addr, sensor_id, past_index);
}

/* Emulation mode */
void pvt_emul_set_next_time(uint64_t pvt_addr,
							uint32_t next_time)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;

	pvt_regs->emul_con.emul_next_time = next_time;
}

void pvt_emul_set_next_data(uint64_t pvt_addr,
							uint32_t next_data)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;

	pvt_regs->emul_con.emul_next_data = next_data;
}

void pvt_emul_enable_emulation(uint64_t pvt_addr)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;

	pvt_regs->emul_con.emul_en = PVT_ENABLE;
}

void pvt_emul_disable_emulation(uint64_t pvt_addr)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;

	pvt_regs->emul_con.emul_en = PVT_DISABLE;
}

uint32_t pvt_temp_apply_calibration(uint64_t pvt_addr,
									uint32_t sensor_id,
									uint32_t temperature)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;

	return pvt_temp_calibration(pvt_addr,
								sensor_id,
								pvt_regs->triminfo_config.calib_sel,
								temperature);
}

uint32_t pvt_temp_apply_reverse_calibration(uint64_t pvt_addr,
											uint32_t sensor_id,
											uint32_t calibrated_temperature)
{
	cmrt_sac_set_base(NULL, pvt_addr);

	volatile struct pvt_regs *pvt_regs = SAC_ADDRESS;

	return pvt_temp_reverse_calibration(pvt_addr,
										sensor_id,
										pvt_regs->triminfo_config.calib_sel,
										calibrated_temperature);
}

static const struct pvt_samsung_api __attribute__((used)) pvt_samsung_driver_api = {
	.init					= (uint32_t)&pvt_init,
	.vol_enable_sensor		= (uint32_t)&pvt_vol_enable_sensor,
	.temp_enable_sensor		= (uint32_t)&pvt_temp_enable_sensor,
	.proc_enable_sensor		= (uint32_t)&pvt_proc_enable_sensor,
	.vol_get_current_value	= (uint32_t)&pvt_vol_get_current_value,
	.temp_get_current_value	= (uint32_t)&pvt_temp_get_current_value,
	.proc_get_current_value	= (uint32_t)&pvt_proc_get_current_value,
	.vol_get_past_value		= (uint32_t)&pvt_vol_get_past_value,
	.temp_get_past_value	= (uint32_t)&pvt_temp_get_past_value,
	.proc_get_past_value	= (uint32_t)&pvt_proc_get_past_value,
	/* Emulation */
	.emul_set_next_time		= (uint32_t)&pvt_emul_set_next_time,
	.emul_set_next_data		= (uint32_t)&pvt_emul_set_next_data,
	.emul_enable_emulation	= (uint32_t)&pvt_emul_enable_emulation,
	.emul_disable_emulation	= (uint32_t)&pvt_emul_disable_emulation,
	/* Calibration */
	.temp_apply_calibration			= (uint32_t)&pvt_temp_apply_calibration,
	.temp_apply_reverse_calibration	= (uint32_t)&pvt_temp_apply_reverse_calibration,
};

#define SAMSUNG_PVT_DEVICE_INIT(inst_nums)											\
	static const struct pvt_samsung_device_config pvt_samsung_cfg_##inst_num = {	\
		.base = DT_INST_REG_ADDR(inst_num),											\
	};																				\
																					\
	static struct pvt_samsung_device_data pvt_samsung_data_##inst_num = {			\
		.base = DT_INST_REG_ADDR(inst_num),											\
	};																				\
																					\
	DEVICE_DT_INST_DEFINE(															\
		inst_num,																	\
		&pvt_init,																	\
		NULL,																		\
		&pvt_samsung_data_##inst_num,												\
		&pvt_samsung_cfg_##inst_num,												\
		POST_KERNEL,																\
		CONFIG_KERNEL_INIT_PRIORITY_DEVICE,											\
		&pvt_samsung_driver_api)

DT_INST_FOREACH_STATUS_OKAY(SAMSUNG_PVT_DEVICE_INIT);
