/**************************************************************************//**
 * @file     system_rebelh_cm7.c
 * @brief    This code based on CMSIS Device System Source File for
 *           ARMCM3 Device
 * @version  V0.1
 * @date     15. November 2023
 ******************************************************************************/
/*
 * Copyright 2024 Samsung Electronics Co., Ltd All Rights Reserved
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>

#include <FreeRTOS.h>
#include <ARMCM7_SP.h>
#include <cachel1_armv7.h>
#include "bat.h"
#include "rebel_h_platform.h"

/*----------------------------------------------------------------------------
 * Define & Globals
 *----------------------------------------------------------------------------
 */
#ifdef ZEBU
#define SYSTEM_CLOCK	(10000000)		/* set to 10MHz for ZEBU to improve UART response */
#else
#define SYSTEM_CLOCK	(1000000000)	/* Rebel's CM7 Frequency is 1GHz */
#endif

uint32_t SystemCoreClock = SYSTEM_CLOCK;  /* System Core Clock Frequency */

extern void *start_bss;
extern void *end_bss;

uint32_t INTERRUPT_RESERVED[64]		__attribute__((section(".interrupt")));

/*----------------------------------------------------------------------------
 * Exception Related Wrapper APIs
 *----------------------------------------------------------------------------
 */
void exception_enable(void)
{
	__DMB();
		SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;
	__DMB();
		SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA_Msk;
	__DMB();
		SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
	__DSB();
	__ISB();
}

void exception_priority(void)
{

}

/*----------------------------------------------------------------------------
 * Cache Related Wrapper APIs
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 * MPU Related Wrapper APIs
 *----------------------------------------------------------------------------
 */
static const ARM_MPU_Region_t table[] = {
	/* SRAM: Excutable/ Bufferable/ Cacheable/ sharable */
	{ .RBAR = ARM_MPU_RBAR(0U, 0x00000000U),
	  .RASR = ARM_MPU_RASR(0U, ARM_MPU_AP_FULL, 1U, 1U, 1U, 1U, 0U, ARM_MPU_REGION_SIZE_256KB) },
	/* Peri: Strongly ordered */
	{ .RBAR = ARM_MPU_RBAR(1U, 0x40000000U),
	  .RASR = ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 2U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_512MB) },
	{ .RBAR = ARM_MPU_RBAR(2U, 0x60000000U),
	  .RASR = ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 2U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_512MB) },
	{ .RBAR = ARM_MPU_RBAR(3U, 0x80000000U),
	  .RASR = ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 2U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_512MB) },
	{ .RBAR = ARM_MPU_RBAR(4U, 0xA0000000U),
	  .RASR = ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 2U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_512MB) },
	{ .RBAR = ARM_MPU_RBAR(5U, 0xC0000000U),
	  .RASR = ARM_MPU_RASR(1U, ARM_MPU_AP_FULL, 2U, 0U, 0U, 0U, 0U, ARM_MPU_REGION_SIZE_512MB) },
};

void mpu_configuration(void)
{
	ARM_MPU_Load(&(table[0]), sizeof(table) / sizeof(ARM_MPU_Region_t));
}

void mpu_enable(void)
{
	ARM_MPU_Enable(0U);
}

/*----------------------------------------------------------------------------
 * System Core Clock update function
 *----------------------------------------------------------------------------
 */
void SystemCoreClockUpdate(void)
{
	SystemCoreClock = SYSTEM_CLOCK;
}

/*----------------------------------------------------------------------------
 * System initialization function
 *----------------------------------------------------------------------------
 */
void mpu_clear(void)
{
	for (uint32_t i = 0U; i < 8U; ++i) {
		MPU->RNR = i;
		MPU->RBAR = 0U;
		MPU->RASR = 0U;
	}
}

void fpu_enable(void);

void bss_clear(void)
{
	void *start_addr_bss = &start_bss;
	void *end_addr_bss = &end_bss;

	memset(start_addr_bss, 0x0, (size_t)(end_addr_bss - start_addr_bss));
}

void system_init(void)
{
	/* Cache related configuration */
	SCB_EnableICache();
	SCB_EnableDCache();

	/* Exception related configuration */
	exception_enable();
	exception_priority();

	/* MPU related configuration */
	mpu_clear();
	mpu_configuration();
	mpu_enable();

	/* Enable FPU */
	fpu_enable();

	/* Clear BSS */
	bss_clear();

	/* BAT Setting */
	if (CHIPLET_ID == CHIPLET_ID0) {
		bat_set_page(3, DRAM_USER_BAT_BASE, DRAM_USER_BASE, BAT_SZ_256M);
		bat_set_page(4, PCIE_HOST_BAT_BASE, PCIE_HOST_BASE, BAT_SZ_128M);
		bat_set_page(5, PCIE_IMSIX_BAT_BASE, PCIE_IMSIX_BASE, BAT_SZ_4K);
		bat_set_page(6, PCIE_DBI_REG_BAT_BASE, PCIE_DBI_BASE, BAT_SZ_256M);
		bat_set_page(7, PCIE_DBI2_REG_BAT_BASE, PCIE_DBI2_BASE, BAT_SZ_4K);
		bat_set_page(8, PCIE_DBI_PF_ELBI_REG_BAT_BASE, PCIE_DBI_PF_ELBI_BASE, BAT_SZ_4K);
		bat_set_page(9, PCIE_DBI_VF_ELBI_REG_BAT_BASE, PCIE_DBI_VF_ELBI_BASE, BAT_SZ_64M);
		bat_set_page(10, PCIE_IATU_HDMA_PORT_REG_BAT_BASE, PCIE_IATU_HDMA_PORT_BASE, BAT_SZ_16M);
		bat_set_page(11, PCIE_MSIX_TABLE_BAT_BASE, PCIE_MSIX_TABLE_PBA_BASE, BAT_SZ_256M);
#ifndef ZEBU_POC
		bat_set_page(12, IP_BLK_SYS_REG_BAT_BASE_CHIPLET0, IP_BLK_SYS_REG_BASE_CHIPLET0, BAT_SZ_128M);
		bat_set_page(13, IP_BLK_SYS_REG_BAT_BASE_CHIPLET1, IP_BLK_SYS_REG_BASE_CHIPLET1, BAT_SZ_128M);
		bat_set_page(14, IP_BLK_SYS_REG_BAT_BASE_CHIPLET2, IP_BLK_SYS_REG_BASE_CHIPLET2, BAT_SZ_128M);
		bat_set_page(15, IP_BLK_SYS_REG_BAT_BASE_CHIPLET3, IP_BLK_SYS_REG_BASE_CHIPLET3, BAT_SZ_128M);
#endif /* ZEBU_POC */
	} else if (CHIPLET_ID == CHIPLET_ID3) {
		bat_set_page(3, DRAM_USER_BAT_BASE, DRAM_USER_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_256M);
		bat_set_page(4, PCIE_HOST_BAT_BASE, PCIE_HOST_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_128M);
		bat_set_page(5, PCIE_IMSIX_BAT_BASE, PCIE_IMSIX_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_4K);
		bat_set_page(6, PCIE_DBI_REG_BAT_BASE, PCIE_DBI_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_256M);
		bat_set_page(7, PCIE_DBI2_REG_BAT_BASE, PCIE_DBI2_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_4K);
		bat_set_page(8, PCIE_DBI_PF_ELBI_REG_BAT_BASE, PCIE_DBI_PF_ELBI_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_4K);
		bat_set_page(9, PCIE_DBI_VF_ELBI_REG_BAT_BASE, PCIE_DBI_VF_ELBI_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_64M);
		bat_set_page(10, PCIE_IATU_HDMA_PORT_REG_BAT_BASE, PCIE_IATU_HDMA_PORT_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_16M);
		bat_set_page(11, PCIE_MSIX_TABLE_BAT_BASE, PCIE_MSIX_TABLE_PBA_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_256M);
#ifndef ZEBU_POC
		bat_set_page(12, IP_BLK_SYS_REG_BAT_BASE_CHIPLET0, IP_BLK_SYS_REG_BASE + CHIPLET_BASE_ADDRESS, BAT_SZ_128M);
		bat_set_page(13, IP_BLK_SYS_REG_BAT_BASE_CHIPLET1, IP_BLK_SYS_REG_BASE_CHIPLET0, BAT_SZ_128M);
		bat_set_page(14, IP_BLK_SYS_REG_BAT_BASE_CHIPLET2, IP_BLK_SYS_REG_BASE_CHIPLET1, BAT_SZ_128M);
		bat_set_page(15, IP_BLK_SYS_REG_BAT_BASE_CHIPLET3, IP_BLK_SYS_REG_BASE_CHIPLET2, BAT_SZ_128M);
#endif /* ZEBU_POC */
	}
}
