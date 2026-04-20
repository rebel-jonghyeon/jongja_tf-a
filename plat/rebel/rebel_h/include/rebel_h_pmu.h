/*
 * Copyright (c) 2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef REBEL_H_PMU_H
#define REBEL_H_PMU_H

#include <stdint.h>
#include <lib/utils_def.h>
/**
 * @brief Release a reset of CM7 core of PCIe block
 *
 * @return None
 */
void pmu_release_cm7(uint32_t chiplet_id);
void pmu_reset_secondary_chiplet(uint32_t bootreason);
void pmu_enable_blk_rbc(void);

char *pmu_get_bootmode_str(uint32_t id);
uint32_t pmu_get_bootmode(void);
#define SECURE_OTP_BOOT				U(0x1)
#define SECURE_XIP_BOOT				U(0x3)
#define WFD_BOOT					U(0x4)
#define NORMAL_BOOT					U(0x5)

char *pmu_get_bootreason_str(uint32_t id);
uint32_t pmu_get_bootreason(void);
#define SWRESET					U(1 << 29)
#define WRESET					U(1 << 28)
#define CLUSTER1_WDTRESET_L2	U(1 << 26)
#define CLUSTER0_WDTRESET_L2	U(1 << 25)
#define CLUSTER1_WDTRESET_L1	U(1 << 24)
#define CLUSTER0_WDTRESET_L1	U(1 << 23)
#define HOTRESET_GLOBAL			U(1 << 21)
#define PCIE_PERST				U(1 << 20)
#define PINRESET				U(1 << 16)

#define SWRESET_OFFSET			U(0x400)

#define ROT_PORESETN_RESET		U(0x2C08)
#define SWRESET_PORESETN		U(1 << 0)
#define SWRESET_PORESETN_MASK	~(SWRESET_PORESETN)

#define CPU_RESET_DISABLE_FROM_LEVEL2RESET	U(0x0418)
#define PEND_CLUSTER1						U(1)
#define PEND_CLUSTER0						U(0)

void pmu_reset_blk_dram(uint32_t chiplet_id);
#define LPI_DRAM_CTRL1			U(0x58)
#define IGNORE_LPI_SMC			U(0xFFFF0000)
#define ACK_LPI_SMC				U(0x0)
#define DRAM_CONFIGURATION		U(0x4260)
#define LOCAL_PWR_CFG_LOW		U(0)
#define LOCAL_PWR_CFG_HIGH		U(0xF)
#define DRAM_STATUS				U(0x4264)

#endif /* REBEL_H_PMU_H */
