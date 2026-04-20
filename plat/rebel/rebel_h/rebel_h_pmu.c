/*
 * Copyright (c) 2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <platform_def.h>
#include <lib/mmio.h>
#include <rebel_h_pmu.h>
#include <rebel_h_plat.h>
#include <common/debug.h>
#include <drivers/synopsys/qspi_bridge.h>
#include <drivers/delay_timer.h>
#include "gpio.h"

void pmu_release_cm7(uint32_t chiplet_id)
{
#ifndef ZEBU_POC
	uint32_t val;

	if (chiplet_id == CHIPLET_ID1 || chiplet_id == CHIPLET_ID2) {
		ERROR("CM7 not allowed for chiplet_id: %d\n", chiplet_id);
		return;
	}

	val = mmio_read_32(PMU_BASE + CHIPLET_OFFSET * chiplet_id  + PCIE_OPTION);
	val &= ~PCIE_ISOLATION;
	mmio_write_32(PMU_BASE + CHIPLET_OFFSET * chiplet_id  + PCIE_OPTION, val);

	mmio_write_32(PMU_BASE + CHIPLET_OFFSET * chiplet_id  + CM7_CPU_PCIE_OPTION, ENABLE_CPU);
#endif /* ZEBU_POC */
}

char *pmu_get_bootmode_str(uint32_t id)
{
	char *str;

	switch (id) {

	case SECURE_OTP_BOOT:
		str = "SECURE_OTP_BOOT";
		break;
	case SECURE_XIP_BOOT:
		str = "SECURE_XIP_BOOT";
		break;
	case NORMAL_BOOT:
		str = "NORMAL_BOOT";
		break;
	case WFD_BOOT:
		str = "WFD_BOOT";
		break;
	default:
		str = "UNKNOWN";
		break;
	}

	return str;
}

uint32_t pmu_get_bootmode(void)
{
#ifndef ZEBU_POC
	return mmio_read_32(PMU_BASE + OM_STAT);
#else
	return NORMAL_BOOT;
#endif /* ZEBU_POC */
}

char *pmu_get_bootreason_str(uint32_t id)
{
	char *str;

	switch (id) {

	case SWRESET:
		str = "Software reset";
		break;
	case WRESET:
		str = "Warm reset";
		break;
	case CLUSTER1_WDTRESET_L2:
		str = "Watchdog reset by cluster1/level2";
		break;
	case CLUSTER0_WDTRESET_L2:
		str = "Watchdog reset by cluster0/level2";
		break;
	case CLUSTER1_WDTRESET_L1:
		str = "Watchdog reset by cluster1/level1";
		break;
	case CLUSTER0_WDTRESET_L1:
		str = "Watchdog reset by cluster0/level1";
		break;
	case HOTRESET_GLOBAL:
		str = "HOTRESET_GLOBAL";
		break;
	case PCIE_PERST:
		str = "PCIE_PERST";
		break;
	case PINRESET:
		str = "Cold reset(POR)";
		break;
	default:
		str = "UNKNOWN";
		break;
	}

	return str;
}

uint32_t pmu_get_bootreason(void)
{
#ifndef ZEBU_POC
	return mmio_read_32(PMU_BASE + RST_STAT);
#else
	return PINRESET;
#endif /* ZEBU_POC */
}

#define CONFIGURATION				U(0x0)
#define STATUS						U(0x4)
#define OPTION						U(0x8)
#define UCIE_ISOLATION				BIT(29)
#define STATUS_BLK_ON				U(0xF)
#define STATUS_BLK_MASK				U(0xF)
#define INITIATE_WAKEUP_FROM_LOWPWR	BIT(31)

#define RBCH00_CONFIGURATION		U(0x42C0)
#define RBCH01_CONFIGURATION		U(0x42E0)
#define RBCV00_CONFIGURATION		U(0x4300)
#define RBCV01_CONFIGURATION		U(0x4320)
#define RBCV10_CONFIGURATION		U(0x4340)
#define RBCV11_CONFIGURATION		U(0x4360)
#define PER_RBC_OFFSET				U(0x0020)
#define ACTIVE_RBC_COUNT			U(0x4)
void pmu_enable_blk_rbc(void)
{
#ifndef ZEBU_POC
	uint32_t val, secondary_chiplet_cnt;
	uint32_t qspi_ch = 2;
	uint64_t base;

	/* QSPI init for primary die */
	qspi_bridge_init(qspi_ch);

	/* Check the secondary chiplet connections */
	secondary_chiplet_cnt = plat_get_secondary_chiplet_cnt();

	/*
	 * Check how many secondary chiplet exists
	 * If it's single chiplet case, this will return early, not to enable RBC block
	 */
	NOTICE("BL1: Detected secondary chiplet count: %d\n", secondary_chiplet_cnt);
	if (secondary_chiplet_cnt == 0)
		return;

	uint64_t pmu_rbc_config_offset[][ACTIVE_RBC_COUNT] = {
		{RBCV10_CONFIGURATION, RBCV11_CONFIGURATION, RBCH00_CONFIGURATION, RBCH01_CONFIGURATION},
		{RBCV00_CONFIGURATION, RBCV01_CONFIGURATION, RBCH00_CONFIGURATION, RBCH01_CONFIGURATION},
		{RBCV00_CONFIGURATION, RBCV01_CONFIGURATION, RBCH00_CONFIGURATION, RBCH01_CONFIGURATION},
		{RBCV10_CONFIGURATION, RBCV11_CONFIGURATION, RBCH00_CONFIGURATION, RBCH01_CONFIGURATION},
	};
	uint32_t chiplet_id = 0;

	/* For primary die */
	for (uint32_t i = 0; i < ACTIVE_RBC_COUNT; i++) {
		base = PMU_BASE + pmu_rbc_config_offset[chiplet_id][i];

		val = mmio_read_32(base + OPTION);
		val &= ~UCIE_ISOLATION;
		mmio_write_32(base + OPTION, val);

		val = mmio_read_32(base + CONFIGURATION);
		val |= INITIATE_WAKEUP_FROM_LOWPWR;
		mmio_write_32(base + CONFIGURATION, val);

		while ((mmio_read_32(base + STATUS) & STATUS_BLK_MASK) != STATUS_BLK_ON)
			;
	}

	/* For secondary die, enable BLK_RBC as per chiplet count */
	for	(chiplet_id = 1; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
		for (uint32_t i = 0; i < ACTIVE_RBC_COUNT; i++) {
			base = CPMU_PRIVATE + pmu_rbc_config_offset[chiplet_id][i];

			val = qspi_bridge_read_1word(qspi_ch, base + OPTION, chiplet_id);
			val &= ~UCIE_ISOLATION;
			qspi_bridge_write_1word(qspi_ch, base + OPTION, val, chiplet_id);

			val = qspi_bridge_read_1word(qspi_ch, base + CONFIGURATION, chiplet_id);
			val |= INITIATE_WAKEUP_FROM_LOWPWR;
			qspi_bridge_write_1word(qspi_ch, base + CONFIGURATION, val, chiplet_id);

			while ((qspi_bridge_read_1word(qspi_ch, base + STATUS, chiplet_id) & STATUS_BLK_MASK)
					!= STATUS_BLK_ON)
				;
		}
	}
#endif /* ZEBU_POC */
}

void pmu_reset_blk_dram(uint32_t chiplet_id)
{
	uint32_t rdata = 0;

	mmio_write_32(PMU_BASE + CHIPLET_OFFSET * chiplet_id + LPI_DRAM_CTRL1, IGNORE_LPI_SMC);

	// Reset
	NOTICE("BLK_DRAM Partial RESET\n");
	mmio_write_32(PMU_BASE + CHIPLET_OFFSET * chiplet_id + DRAM_CONFIGURATION, LOCAL_PWR_CFG_LOW);
	mdelay(10);

	// Reset release
	mmio_write_32(PMU_BASE + CHIPLET_OFFSET * chiplet_id + DRAM_CONFIGURATION, LOCAL_PWR_CFG_HIGH);
	mdelay(10);
	do {
		rdata = mmio_read_32(PMU_BASE + CHIPLET_OFFSET * chiplet_id + DRAM_STATUS);
	} while ((rdata & 0xF) != 0xF); // 0xF: reset release, 0x0: reset
	NOTICE("BLK_DRAM Partial RESET Released\n");

	mmio_write_32(PMU_BASE + CHIPLET_OFFSET * chiplet_id + LPI_DRAM_CTRL1, ACK_LPI_SMC);
}

void pmu_reset_secondary_chiplet(uint32_t bootreason)
{
#if (ZEBU == 0)
	if (REVISION_EVT1 == GET_REVISION && HOTRESET_GLOBAL == bootreason) {
		uint32_t ch = 2;
		uint32_t val = 1;

		for (uint32_t cl_id = CHIPLET_ID1; cl_id <= CHIPLET_ID3; cl_id++) {
			qspi_bridge_set_upper_addr(ch, CPMU_PRIVATE, cl_id);
			qspi_bridge_write_1word(ch,	CPMU_PRIVATE + SWRESET_OFFSET, val, cl_id);
		}
	} else {
		GPIO_GPD_SET(0, 0, CON, GPIO_CON_OUTPUT);
		GPIO_GPD_SET(0, 1, CON, GPIO_CON_OUTPUT);
		GPIO_GPD_SET(0, 2, CON, GPIO_CON_OUTPUT);

		GPIO_GPD_SET(0, 0, DAT, 0U & GPIO_ONE_BIT);
		GPIO_GPD_SET(0, 1, DAT, 0U & GPIO_ONE_BIT);
		GPIO_GPD_SET(0, 2, DAT, 0U & GPIO_ONE_BIT);

		mdelay(1);

		GPIO_GPD_SET(0, 0, DAT, GPIO_ONE_BIT);
		GPIO_GPD_SET(0, 1, DAT, GPIO_ONE_BIT);
		GPIO_GPD_SET(0, 2, DAT, GPIO_ONE_BIT);

		mdelay(1);
	}
	return;
#endif
}
