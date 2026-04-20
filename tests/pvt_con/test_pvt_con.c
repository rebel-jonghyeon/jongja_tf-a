/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 * PROPRIETARY/CONFIDENTIAL
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it
 * only in accordance with the terms of the license agreement you entered
 * into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NON-INFRINGEMENT.
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT
 * OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include <test_common.h>
#include "test_pvt_con.h"
#include <pvt_con.h>
#include <pvt_con_reg.h>
#include <interrupt.h>

#include <printf.h>
#include <system_api.h>

extern uint64_t pvt_base_address[];
extern uint32_t pvt_n_sensors[];
extern struct pvt_irq pvt_irqs[];

static inline void test_pvt_delay(uint32_t delay_time)
{
	mdelay(delay_time);
}

static void test_pvt_process(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = PVT_GET_INSTANCE(pvt_regs);
	uint32_t delay_time	= 3U;
	uint32_t next_time = 1U;
	uint32_t current_value;

	PVT_ENABLE_EMULATION_MODE(pvt_regs);
	PVT_ENABLE_CONTROLLER(PROC, pvt_regs);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_N_SENSOR(PROC, pvt_instance); ++sensor_id) {
		printf("[Process] #%u-%u\n", pvt_instance, sensor_id);

		for (uint32_t next_data = 0; next_data < 0xFFFU; next_data += 0x1FFU) {
			PVT_SET_NEXT_DATA(pvt_regs, next_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(PROC, pvt_regs, sensor_id);
			printf("next_data = %08x, current_value = %08x\n", next_data, current_value);
			if (next_data != current_value) {
				printf("[pvt] Process Error\n");
			}
		}
		for (uint32_t next_data = 0xFFFU; next_data > 0U; next_data -= 0x1FFU) {
			PVT_SET_NEXT_DATA(pvt_regs, next_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(PROC, pvt_regs, sensor_id);
			printf("next_data = %08x, current_value = %08x\n", next_data, current_value);
			if (next_data != current_value) {
				printf("[pvt] Process Error\n");
			}
		}
	}

	PVT_DISABLE_EMULATION_MODE(pvt_regs);
}

static void test_pvt_voltage(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = PVT_GET_INSTANCE(pvt_regs);
	uint32_t delay_time	= 3U;
	uint32_t next_time = 1U;
	uint32_t current_value;
	uint32_t calib_data;

	PVT_ENABLE_EMULATION_MODE(pvt_regs);
	PVT_ENABLE_CONTROLLER(VOLT, pvt_regs);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_N_SENSOR(VOLT, pvt_instance); ++sensor_id) {
		printf("[Voltage] #%u-%u\n", pvt_instance, sensor_id);

		for (uint32_t next_data = 450; next_data < 900; next_data += 20) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_VOLT(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(VOLT, pvt_regs, sensor_id);
			printf("next_data = %08x, current_value = %08x\n", next_data, current_value);
			if (next_data != current_value) {
				printf("[pvt] Voltage Error\n");
			}
		}
		for (uint32_t next_data = 900; next_data > 450; next_data -= 20) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_VOLT(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(VOLT, pvt_regs, sensor_id);
			printf("next_data = %08x, current_value = %08x\n", next_data, current_value);
			if (next_data != current_value) {
				printf("[pvt] Voltage Error\n");
			}
		}
	}

	PVT_DISABLE_EMULATION_MODE(pvt_regs);
}

static inline void test_pvt_disable_all_interrupts(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = PVT_GET_INSTANCE(pvt_regs);

	PVT_DISABLE_TRIP_MODE(pvt_regs);
	PVT_DISABLE_DFS_MODE(pvt_regs);

	/* Disable all interrupts */
	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_N_SENSOR(TEMP, pvt_instance); ++sensor_id) {
		PVT_CONTROL_ALL_INTERRUPT(pvt_regs, sensor_id, PVT_DISABLE);
	}

}

static inline void test_pvt_enable_all_interrupts(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = PVT_GET_INSTANCE(pvt_regs);

	/* Restore interrupts */
	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_N_SENSOR(TEMP, pvt_instance); ++sensor_id) {
		PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 0, PVT_ENABLE);
		PVT_CLEAR_ALL_INTERRUPT(pvt_regs, sensor_id);
	}

	PVT_ENABLE_TRIP_MODE(pvt_regs);
	PVT_ENABLE_DFS_MODE(pvt_regs);
}

static void test_pvt_temperature(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = PVT_GET_INSTANCE(pvt_regs);
	uint32_t delay_time	= 3U;
	uint32_t next_time = 1U;
	uint32_t current_value;
	uint32_t calib_data;

	PVT_ENABLE_EMULATION_MODE(pvt_regs);
	PVT_ENABLE_CONTROLLER(TEMP, pvt_regs);
	test_pvt_disable_all_interrupts(pvt_regs);
	test_pvt_delay(delay_time);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_N_SENSOR(TEMP, pvt_instance); ++sensor_id) {
		printf("[Temperature] #%u-%u\n", pvt_instance, sensor_id);

		for (uint32_t next_data = 25; next_data < 85; next_data += 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("next_data = %08x, current_value = %08x\n", next_data, current_value);
			if ((next_data >> 4) != (current_value >> 4)) {
				printf("[pvt] Temperature Error\n");
			}
		}
		for (uint32_t next_data = 85; next_data > 25; next_data -= 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("next_data = %08x, current_value = %08x\n", next_data, current_value);
			if ((next_data >> 4) != (current_value >> 4)) {
				printf("[pvt] Temperature Error\n");
			}
		}
	}

	PVT_DISABLE_EMULATION_MODE(pvt_regs);
	test_pvt_enable_all_interrupts(pvt_regs);
}

static inline void test_pvt_temp_window(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = PVT_GET_INSTANCE(pvt_regs);
	uint32_t delay_time	= 3U;
	uint32_t next_time = 1U;
	uint32_t current_value;
	uint32_t calib_data;

	PVT_ENABLE_EMULATION_MODE(pvt_regs);
	PVT_ENABLE_CONTROLLER(TEMP, pvt_regs);
	test_pvt_disable_all_interrupts(pvt_regs);
	test_pvt_delay(delay_time);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_N_SENSOR(TEMP, pvt_instance); ++sensor_id) {
		PVT_CONTROL_ALL_INTERRUPT(pvt_regs, sensor_id, PVT_DISABLE);
		PVT_CLEAR_ALL_INTERRUPT(pvt_regs, sensor_id);
		printf("[Window Test] #%u-%u\n", pvt_instance, sensor_id);

		PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 0, PVT_ENABLE);
		test_pvt_delay(delay_time);
		for (uint32_t next_data = 25; next_data < 85; next_data += 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}
		for (uint32_t next_data = 85; next_data >= 25; next_data -= 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}

		test_pvt_delay(delay_time);
		PVT_CONTROL_ALL_INTERRUPT(pvt_regs, sensor_id, PVT_DISABLE);
		PVT_CLEAR_ALL_INTERRUPT(pvt_regs, sensor_id);
		test_pvt_delay(delay_time);
	}

	PVT_DISABLE_EMULATION_MODE(pvt_regs);
}

static inline void test_pvt_temp_dfs(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = PVT_GET_INSTANCE(pvt_regs);
	uint32_t delay_time	= 5U;
	uint32_t next_time = 1U;
	uint32_t current_value;
	uint32_t calib_data;

	PVT_ENABLE_EMULATION_MODE(pvt_regs);
	PVT_ENABLE_CONTROLLER(TEMP, pvt_regs);
	test_pvt_disable_all_interrupts(pvt_regs);
	test_pvt_delay(delay_time);

	PVT_SET_DFS_PAST_THRESHOLD(pvt_regs, 1);
	PVT_ENABLE_DFS_MODE(pvt_regs);
	test_pvt_delay(delay_time);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_N_SENSOR(TEMP, pvt_instance); ++sensor_id) {
		printf("[DFS Test] #%u-%u\n", pvt_instance, sensor_id);

		PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 8, PVT_ENABLE);
		test_pvt_delay(delay_time);
		for (uint32_t next_data = 70; next_data < 85; next_data += 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}
		for (uint32_t next_data = 85; next_data >= 70; next_data -= 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}
		for (uint32_t next_data = 70; next_data < 85; next_data += 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}
		for (uint32_t next_data = 85; next_data >= 70; next_data -= 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}

		portENTER_CRITICAL();
		PVT_CONTROL_ALL_INTERRUPT(pvt_regs, sensor_id, PVT_DISABLE);
		PVT_CLEAR_ALL_INTERRUPT(pvt_regs, sensor_id);
		portEXIT_CRITICAL();
	}

	PVT_DISABLE_EMULATION_MODE(pvt_regs);
}

static inline void test_pvt_temp_trip(struct pvt_regs *pvt_regs)
{
	uint32_t pvt_instance = PVT_GET_INSTANCE(pvt_regs);
	uint32_t delay_time	= 5U;
	uint32_t next_time = 1U;
	uint32_t current_value;
	uint32_t calib_data;

	PVT_ENABLE_EMULATION_MODE(pvt_regs);
	PVT_ENABLE_CONTROLLER(TEMP, pvt_regs);
	test_pvt_disable_all_interrupts(pvt_regs);
	test_pvt_delay(delay_time);

	PVT_SET_TRIP_PAST_THRESHOLD(pvt_regs, 1);
	PVT_ENABLE_TRIP_MODE(pvt_regs);
	test_pvt_delay(delay_time);

	for (uint32_t sensor_id = 0; sensor_id < PVT_GET_N_SENSOR(TEMP, pvt_instance); ++sensor_id) {
		printf("[TRIP Test] #%u-%u\n", pvt_instance, sensor_id);

		PVT_CONTROL_INTERRUPT(RISE, pvt_regs, sensor_id, 7, PVT_ENABLE);
		test_pvt_delay(delay_time);
		for (uint32_t next_data = 70; next_data < 85; next_data += 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}
		for (uint32_t next_data = 85; next_data >= 70; next_data -= 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}
		for (uint32_t next_data = 70; next_data < 85; next_data += 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}
		for (uint32_t next_data = 85; next_data >= 70; next_data -= 5) {
			calib_data = PVT_CONVERT_TO_CALIBRATED_TEMP(pvt_regs,
														sensor_id,
														next_data);
			PVT_SET_NEXT_DATA(pvt_regs, calib_data);
			PVT_SET_NEXT_TIME(pvt_regs, next_time);
			test_pvt_delay(delay_time);

			current_value = PVT_GET_CURRENT_VALUE(TEMP, pvt_regs, sensor_id);
			printf("Current Temperature = %u\n", current_value);
		}

		portENTER_CRITICAL();
		PVT_CONTROL_ALL_INTERRUPT(pvt_regs, sensor_id, PVT_DISABLE);
		PVT_CLEAR_ALL_INTERRUPT(pvt_regs, sensor_id);
		portEXIT_CRITICAL();
	}

	PVT_DISABLE_EMULATION_MODE(pvt_regs);
}

uint8_t test_pvt(int argc, char **argv)
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

		PVT_SET_SAMPLING_INTERVAL(pvt_regs, 0x186A0U);
		test_pvt_delay(3);

		test_pvt_process(pvt_regs);
		test_pvt_voltage(pvt_regs);
		test_pvt_temperature(pvt_regs);

		test_pvt_temp_window(pvt_regs);
		// test_pvt_temp_dfs(pvt_regs);
		// test_pvt_temp_trip(pvt_regs);

		PVT_SET_SAMPLING_INTERVAL(pvt_regs, 0xF4240U);
		test_pvt_enable_all_interrupts(pvt_regs);
	}

	return 1;
}

static const char help_test_pvt[] =
	"[test_pvt]\n"
	" * Test for PVT controller driver\n"
	"\n";

CLI_REGISTER(test_pvt, NULL, test_pvt, help_test_pvt);
