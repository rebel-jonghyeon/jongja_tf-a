#include <stdio.h>
#include <pvt_con.h>
#include "test_pvt_con.h"
#include <kernel.h>

#include <logging/log.h>
#include <rebel_h.h>
LOG_MODULE_DECLARE(main, CONFIG_CMRT_LOG_LEVEL);

extern uint64_t pvt_instances[];
extern uint32_t pvt_instance_n_sensors[];

/* 0x000F4240U = 1,000,000 = 5ms */
/* 0x00009C40U = 100,000 = 0.5ms */
static inline void test_pvt_con_delay(uint32_t next_time)
{
	k_msleep(next_time);
}

static void test_pvt_voltage(void)
{
	uint64_t pvt_addr;
	uint32_t next_time = 1U;
	uint32_t current_value;

	/* TODO: ZEBU cannot access to BLK_DCL0/1 'PVT_N_INSTANCE' */
	for (uint32_t pvt_instance = 0; pvt_instance < 1; ++pvt_instance) {
		pvt_addr = pvt_instances[pvt_instance];

		/* Init PVT voltage */
		pvt_vol_enable_sensor(pvt_addr,
							  PVT_VOLTAGE_RANGE_045V_090V,
							  0x00009000U,
							  PVT_NONE_AVERAGE);

		pvt_emul_enable_emulation(pvt_addr);
		for (uint32_t sensor_id = 0;
			 sensor_id < pvt_instance_n_sensors[PVT_INSTANCE_VOLTAGE(pvt_instance)];
			 ++sensor_id) {
			LOG_INF("[Voltage] #%u-%u", pvt_instance, sensor_id);

			for (uint32_t next_data = 0; next_data < 0xFFFU; next_data += 0x1FFU) {
				pvt_emul_set_next_data(pvt_addr, next_data);
				pvt_emul_set_next_time(pvt_addr, next_time);
				test_pvt_con_delay(next_time);

				current_value = pvt_vol_get_current_value(pvt_addr, sensor_id);
				LOG_INF("next_data = %08x, current_value = %08x", next_data, current_value);
				if (next_data != current_value) {
					LOG_INF("[pvt_con] Voltage Error");
				}
			}
		}
		pvt_emul_disable_emulation(pvt_addr);
	}
}

/* TODO: Add static */
void test_pvt_temperature(void)
{
	uint64_t pvt_addr;
	uint32_t next_time = 1U;
	uint32_t current_value;

	/* TODO: ZEBU cannot access to BLK_DCL0/1 'PVT_N_INSTANCE' */
	for (uint32_t pvt_instance = 0; pvt_instance < 1; ++pvt_instance) {
		pvt_addr = pvt_instances[pvt_instance];

		/* Init PVT temperature */
		pvt_temp_enable_sensor(pvt_addr,
							   PVT_ENABLE,
							   PVT_EXCEED_ONLY_CURRENT,
							   PVT_ENABLE,
							   PVT_EXCEED_ONLY_CURRENT,
							   PVT_ENABLE,
							   0x00009000U,
							   PVT_NONE_AVERAGE);

		pvt_emul_enable_emulation(pvt_addr);
		for (uint32_t sensor_id = 0;
			 sensor_id < pvt_instance_n_sensors[PVT_INSTANCE_TEMPERATURE(pvt_instance)];
			 ++sensor_id) {
			LOG_INF("[Temperature] #%u-%u", pvt_instance, sensor_id);
			/* TODO: Test each settings */
			for (uint32_t next_data = 0; next_data < 0xFFFU; next_data += 0x1FFU) {
				pvt_emul_set_next_data(pvt_addr,
									   pvt_temp_apply_calibration(pvt_addr,
																  sensor_id,
																  next_data));
				pvt_emul_set_next_time(pvt_addr, next_time);
				test_pvt_con_delay(next_time);
				current_value = pvt_temp_get_current_value(pvt_addr, sensor_id);

				LOG_INF("next_data = %08x, current_value = %08x", next_data, current_value);
				if ((next_data >> 4) != (current_value >> 4)) {
					LOG_INF("[pvt_con] Temperature Error");
				}
			}
		}
		pvt_emul_disable_emulation(pvt_addr);
	}
}

/* TODO: Add static */
void test_pvt_process(void)
{
	/* TODO: Emulation for process sensor is not working in ZEBU */
	return;

	uint64_t pvt_addr;
	uint32_t next_time = 1U;
	uint32_t current_value;

	/* TODO: ZEBU cannot access to BLK_DCL0/1 'PVT_N_INSTANCE' */
	for (uint32_t pvt_instance = 0; pvt_instance < 1; ++pvt_instance) {
		pvt_addr = pvt_instances[pvt_instance];

		/* Init PVT process */
		pvt_proc_enable_sensor(pvt_addr,
							   PVT_PROCESS_NORMAL_OUTPUT,
							   0x00009000U,
							   PVT_NONE_AVERAGE);

		pvt_emul_enable_emulation(pvt_addr);
		for (uint32_t sensor_id = 0;
			 sensor_id < pvt_instance_n_sensors[PVT_INSTANCE_PROCESS(pvt_instance)];
			 ++sensor_id) {
			LOG_INF("[Process] #%u-%u", pvt_instance, sensor_id);
			/* TODO: Test each settings */
			for (uint32_t next_data = 0; next_data < 0xFFFU; next_data += 0x1FFU) {
				pvt_emul_set_next_data(pvt_addr, next_data);
				pvt_emul_set_next_time(pvt_addr, next_time);
				test_pvt_con_delay(next_time);
				current_value = pvt_proc_get_current_value(pvt_addr, sensor_id);

				LOG_INF("next_data = %08x, current_value = %08x", next_data, current_value);
				if (next_data != current_value) {
					LOG_INF("[pvt_con] Process Error");
				}
			}
		}
		pvt_emul_disable_emulation(pvt_addr);
	}
}

int test_pvt_con(void)
{
	test_pvt_voltage();
	test_pvt_temperature();
	test_pvt_process();

	return 0;
}
