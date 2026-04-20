/*
 * Copyright (c) 2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <platform_def.h>
#include <lib/mmio.h>
#include <rebel_h_pmu.h>
#include <common/debug.h>
#include <drivers/synopsys/qspi_bridge.h>
#include <drivers/delay_timer.h>

#include "gpio.h"

void plat_set_cpu_rvbar(uint32_t chiplet, uint32_t cluster, uint32_t cpu, uint64_t ep)
{
	mmio_write_32(CHIPLET_OFFSET * chiplet + SYSREG_CP0 + PER_SYSREG_CP * cluster +
				  RVBARADDR0_LOW + PERCPU_RVBARADDR_OFFSET * cpu, (uint32_t)ep);

	mmio_write_32(CHIPLET_OFFSET * chiplet + SYSREG_CP0 + PER_SYSREG_CP * cluster +
				  RVBARADDR0_HIGH + PERCPU_RVBARADDR_OFFSET * cpu, (uint32_t)(ep >> 32));

	INFO("Set RVBAR of chiplet: %d, cluster: %d, cpu: %d, ep: %lux\n", chiplet, cluster, cpu, ep);
}

void plat_pmu_cl_on(uint32_t chiplet, uint32_t cluster)
{
	mmio_write_32(CHIPLET_OFFSET * chiplet + CPMU + PERNONCPU_OFFSET * cluster +
				  CP0_NONCPU_CONFIGURATION, CL_ON_WITH_INITIATE_WAKEUP);

	while ((mmio_read_32(CHIPLET_OFFSET * chiplet + CPMU + PERNONCPU_OFFSET * cluster +
				  CP0_NONCPU_STATUS) & CL_STATUS_MASK) != CL_STATUS_ON)
		;

	INFO("cluster: %d turned on\n", cluster);
}

void plat_pmu_cpu_on(uint32_t chiplet, uint32_t cluster, uint32_t cpu)
{
	mmio_write_32(CHIPLET_OFFSET * chiplet + CPMU + PERCLUSTER_OFFSET * cluster +
				  CPU0_CONFIGURATION + PERCPU_OFFSET * cpu, CPU_ON_WITH_INITIATE_WAKEUP);

	while ((mmio_read_32(CHIPLET_OFFSET * chiplet + CPMU + PERCLUSTER_OFFSET * cluster +
				  CPU0_STATUS + PERCPU_OFFSET * cpu) & CPU_STATUS_MASK) != CPU_STATUS_ON)
		;

	INFO("cluster: %d, cpu: %d turned on\n", cluster, cpu);
}

void plat_pmu_cpu_off(uint32_t chiplet, uint32_t cluster, uint32_t cpu)
{
	mmio_write_32(CHIPLET_OFFSET * chiplet + CPMU + PERCLUSTER_OFFSET * cluster +
				  CPU0_CONFIGURATION + PERCPU_OFFSET * cpu, CPU_OFF_WITH_INITIATE_WAKEUP);

	while ((mmio_read_32(CHIPLET_OFFSET * chiplet + CPMU + PERCLUSTER_OFFSET * cluster +
				  CPU0_STATUS + PERCPU_OFFSET * cpu) & CPU_STATUS_MASK) != CPU_STATUS_OFF)
		;

	INFO("cluster: %d, cpu: %d turned off\n", cluster, cpu);
}

/* Expose count of chiplet(dual or quad) to RTOS via PMU */
void plat_set_secondary_chiplet_cnt(uint32_t chiplet, uint32_t cnt)
{
	mmio_write_32(CHIPLET_OFFSET * chiplet + CPMU + INFORM4, cnt);
}

uint32_t plat_get_secondary_chiplet_cnt(void)
{
	uint32_t ret, cnt = 0;
	uint32_t qspi_ch = 2;

	qspi_bridge_init(qspi_ch);

	for (uint32_t chiplet_id = 1; chiplet_id <= 3; chiplet_id++) {
		qspi_bridge_set_upper_addr(qspi_ch, 0x0, chiplet_id);
		ret = qspi_bridge_read_1word(qspi_ch, SYSREG_SYSREMAP_CHIPLET, chiplet_id);

		if (chiplet_id == ret)
			cnt++;
	}

	return cnt;
}

void plat_pmu_reset_rot(uint32_t chiplet)
{
	/*
	 * Software reset for PORESETn;
	 * This field is automatically cleared to LOW after software reset process is over.
	 */
	uint32_t val;

	val = mmio_read_32(CHIPLET_OFFSET * chiplet + CPMU + ROT_PORESETN_RESET);

	val &= SWRESET_PORESETN_MASK;
	val |= SWRESET_PORESETN;

	mmio_write_32(CHIPLET_OFFSET * chiplet + CPMU + ROT_PORESETN_RESET, val);

	NOTICE("reset RoT of chiplet-%d\n", chiplet);
}
