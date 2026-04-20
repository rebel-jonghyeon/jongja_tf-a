/*
 * Copyright (c) 2023-2024, Samsung Electronics Co., Ltd. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <arch_helpers.h>
#include <assert.h>
#include <platform_def.h>
#include <common/bl_common.h>
#include <common/debug.h>
#include <lib/mmio.h>
#include <lib/xlat_tables/xlat_tables_v2.h>
#include <drivers/ti/uart/uart_16550.h>
#include <rebel_h_pmu.h>
#include <rebel_h_pcie.h>
#include <rebel_h_plat.h>
#include <rebel_h_rbc.h>
#include <drivers/synopsys/qspi_bridge.h>
#include <drivers/aw/ucie.h>
#include <drivers/arm/pl330.h>
#ifndef ZEBU_POC
#include <cmu.h>
#endif /* ZEBU_POC */
#include <lib/sic/sic.h>
#include <drivers/synopsys/qspi_boot.h>
#include <drivers/generic_delay_timer.h>

#if USE_GPT
#include "drivers/partition/partition_simple.h"

extern char mcode[];
#endif /* USE_GPT */

/* Data structure which holds the extents of the trusted SRAM for BL1 */
static console_t rebel_console;
static meminfo_t bl1_tzram_layout;

enum sboot_n_boot_sequence {
	NOT_STARTED,
	HW_INIT,
	LOAD_TBOOT_P0,
	RESET_RELEASE_CM7,
	WAIT_PHY_SRAM_INIT_DONE,
	LOAD_TBOOT_P1,
	CM7_NOTIFY_LOAD_DONE,
	QSPI_BRIDGE_STATUS_CHECK,
	PMU_ENABLE_BLK_RBC,
	REQUEST_TBOOT_U_INTEGRITY,
	RESPONSE_TBOOT_U_INTEGRITY,
	INIT_BLK_RBC,
	REQUEST_TBOOT_N_INTEGRITY,
	RESPONSE_TBOOT_N_INTEGRITY,
};

#ifndef ZEBU_POC
static void _bl1_init_blk_rbc(const uint32_t bootmode)
{
#if ZEBU
	/*Single chiplet ZEBU image does not contain any BLK_RBC.*/
	if (set_num_of_chips_and_rbc_for_ZEBU() == 1)
		return;
#endif /* ZEBU */
	set_remap_table();

	repeat_func_for_all_rbc(cmu_init_rbc, CMU_RBC_BASE_OFFSET, 0);
	BOOT_LOG(CP0, SBOOT_N, REQUEST_TBOOT_N_INTEGRITY);
#if CHIPLET_COUNT > 1
	load_and_enable_ucie_link_for_CP(bootmode);
#endif
	BOOT_LOG(CP0, SBOOT_N, RESPONSE_TBOOT_N_INTEGRITY);
}
#endif /* ZEBU_POC */

meminfo_t *bl1_plat_sec_mem_layout(void)
{
	return &bl1_tzram_layout;
}

/*******************************************************************************
 * Perform any BL1 specific platform actions.
 ******************************************************************************/

#if USE_GPT
#define TBOOT_N_SRC_ADDR	(0x1f800E0000ULL)
#endif

void bl1_early_platform_setup(void)
{
	/*
	 * Mask PCIe's PERST path to PMU reset handler for chiplet-0
	 * Instead, Chiplet-0 FreeRTOS_PCIE will handle ISR to reset secondary chiplets
	 * and will unmask this bit to reset self.
	 */
	mmio_clrbits_32(CPMU_PRIVATE + MASK_WDT_RESET_REQUEST, MASK_WDT_RESET_REQUEST_PCIE_PERST);

	if (IS_NORMAL_BOOT) {
		UPDATE_RESET_LOG;
	}

#ifndef ZEBU_POC
	mmio_write_32(CSS600_CNTGEN + CNTCR, CNTEN); // Enable generic counter
#endif /* ZEBU_POC */
	generic_delay_timer_init();
	BOOT_LOG(CP0, SBOOT_N, HW_INIT);

	uint32_t bootmode = pmu_get_bootmode();
#ifndef ZEBU_POC
	cmu_init_bl1(bootmode);
#endif /* ZEBU_POC */

	console_16550_register(PLAT_UART0_PERI0,
						   PLAT_UART_CLOCK,
						   PLAT_BAUDRATE,
						   &rebel_console);

	console_set_scope(&rebel_console, CONSOLE_FLAG_BOOT | CONSOLE_FLAG_CRASH |
					  CONSOLE_FLAG_RUNTIME);

	uint32_t bootreason = pmu_get_bootreason();

	NOTICE("Boot mode: %s (%d)\n", pmu_get_bootmode_str(bootmode), bootmode);
	NOTICE("Boot reason: %s (0x%08x)\n", pmu_get_bootreason_str(bootreason), bootreason);

#if CHIPLET_COUNT > 1
#if USE_GPT
	pmu_reset_secondary_chiplet(bootreason);
#endif /* USE_GPT */
#endif /* CHIPLET_COUNT */

#ifndef ZEBU_POC
	switch (bootmode) {

	case SECURE_OTP_BOOT:
	case SECURE_XIP_BOOT:
		BOOT_LOG(CP0, SBOOT_N, QSPI_BRIDGE_STATUS_CHECK);
		/*
		 * TODO: add QSPI bridge status check seq. by using REQ/STATUS command at silicon phase.
		 *		 Currently, instead, we're indirectly checking QSPI status by using a direct
		 *		 read/write command inside the next pmu/ucie functions to save the ZEBU time.
		 */

		BOOT_LOG(CP0, SBOOT_N, PMU_ENABLE_BLK_RBC);
		pmu_enable_blk_rbc();

		WAIT_BOOT_DONE(ROT);

		NOTICE("BL1: TBOOT_U request\n");
		BOOT_LOG(CP0, SBOOT_N, REQUEST_TBOOT_U_INTEGRITY);
#if ZEBU
		/*Single chiplet ZEBU image does not contain any BLK_RBC.*/
		if (set_num_of_chips_and_rbc_for_ZEBU() > 1)
#endif /* ZEBU */
			request_to_cmrt(CMRT_MW_LOAD_TBOOT_U);
		BOOT_LOG(CP0, SBOOT_N, RESPONSE_TBOOT_U_INTEGRITY);
		NOTICE("BL1: TBOOT_U request done\n");

		BOOT_LOG(CP0, SBOOT_N, INIT_BLK_RBC);
		_bl1_init_blk_rbc(bootmode);

		NOTICE("BL1: TBOOT_N request\n");
		BOOT_LOG(CP0, SBOOT_N, REQUEST_TBOOT_N_INTEGRITY);
#if USE_GPT
		request_to_cmrt(CMRT_MW_LOAD_TBOOT_N);
#endif /* USE_GPT */
		BOOT_LOG(CP0, SBOOT_N, RESPONSE_TBOOT_N_INTEGRITY);
		NOTICE("BL1: TBOOT_N request done\n");

		break;
	case NORMAL_BOOT:
	case WFD_BOOT:
#if USE_GPT
		qspi_boot_config();

		BOOT_LOG(CP0, SBOOT_N, LOAD_TBOOT_P0);
		INFO("Load tboot_p0\n");
		dma_load_image(GPT_DEST_ADDR_TBOOT_P0, TBOOT_P0_SRC_ADDR + IMAGE_SIZE_FIELD,
					   GPT_DEST_SIZE_TBOOT_P0);
#endif /* USE_GPT */
		BOOT_LOG(CP0, SBOOT_N, RESET_RELEASE_CM7);
		INFO("Release reset of CM7\n");
		pmu_release_cm7(CHIPLET_ID0);

		NOTICE("BL1: pmu_release_cm7 complete\n");
		/* Wait for PCIe PHY SRAM init done after cm7 released */
		BOOT_LOG(CP0, SBOOT_N, WAIT_PHY_SRAM_INIT_DONE);
#if PCIE_PHY_SRAM_LOAD
		cm7_wait_phy_sram_init_done(CHIPLET_ID0);
#endif /* PCIE_PHY_SRAM_LOAD */
		BOOT_LOG(CP0, SBOOT_N, LOAD_TBOOT_P1);
#if USE_GPT
#if PCIE_PHY_SRAM_LOAD
		mmio_write_32(SYSREG_PCIE + MUX_CR_PARA_SEL, MUX_CR_PARA_SEL_BROADCAST);
		/* TODO: check and verify TBOOT_P1 manually at least once */
		dma_load_image(GPT_DEST_ADDR_TBOOT_P1_PHY0, TBOOT_P1_SRC_ADDR + IMAGE_SIZE_FIELD,
					   GPT_DEST_SIZE_TBOOT_P1);

		mmio_write_32(PHY0_APB2CR_PARA_PCIE + MUX_SWITCH, MUX_VALUE);

		dma_load_image(GPT_DEST_ADDR_TBOOT_P1_PHY0,
					   TBOOT_P1_SRC_ADDR + IMAGE_SIZE_FIELD + GPT_DEST_SIZE_TBOOT_P1,
					   GPT_DEST_SIZE_TBOOT_P1);

		mmio_write_32(PHY0_APB2CR_PARA_PCIE + MUX_SWITCH, 0);

		mmio_write_32(SYSREG_PCIE + MUX_CR_PARA_SEL, MUX_CR_PARA_SEL_SEPARATE);

		NOTICE("BL1: TP0/1 load done\n");
#endif /* PCIE_PHY_SRAM_LOAD */
#endif /* USE_GPT */

#if PCIE_PHY_SRAM_LOAD
		/* Notify tboot_p1 is ready to PHY SRAM to PCIe world */
		BOOT_LOG(CP0, SBOOT_N, CM7_NOTIFY_LOAD_DONE);
		cm7_notify_load_done(CHIPLET_ID0);
#endif /* PCIE_PHY_SRAM_LOAD */
		BOOT_LOG(CP0, SBOOT_N, QSPI_BRIDGE_STATUS_CHECK);
		/*
		 * TODO: add QSPI bridge status check seq. by using REQ/STATUS command at silicon phase.
		 *		 Currently, instead, we're indirectly checking QSPI status by using a direct
		 *		 read/write command inside the next pmu/ucie functions to save the ZEBU time.
		 */
#if CHIPLET_COUNT > 1
		BOOT_LOG(CP0, SBOOT_N, PMU_ENABLE_BLK_RBC);
		pmu_enable_blk_rbc();

		BOOT_LOG(CP0, SBOOT_N, INIT_BLK_RBC);
		_bl1_init_blk_rbc(bootmode);
#endif /* CHIPLET_COUNT */

#if USE_GPT
		NOTICE("BL1 - BL2 load\n");
		dma_load_image(GPT_DEST_ADDR_TBOOT_N, TBOOT_N_SRC_ADDR + 0x10, GPT_DEST_SIZE_TBOOT_N);
		NOTICE("BL1 - BL2 load is done\n");
#endif

		break;
	default:
		ERROR("Unexpected bootmode : %d\n", bootmode);
		assert(0);
		break;
	}
#endif /* ZEBU_POC */

	/* Allow BL1 to see the whole Trusted RAM */
	bl1_tzram_layout.total_base = SEC_SRAM_BASE;
	bl1_tzram_layout.total_size = SEC_SRAM_SIZE;
}

void bl1_plat_arch_setup(void)
{
	mmap_add_region(BL1_RO_BASE, BL1_RO_BASE, (BL1_RO_LIMIT - BL1_RO_BASE),
					MT_MEMORY | MT_RO | MT_SECURE);
	mmap_add_region(BL1_RW_BASE, BL1_RW_BASE, (BL1_RW_LIMIT - BL1_RW_BASE),
					MT_MEMORY | MT_RW | MT_SECURE);
	mmap_add_region(BL2_BASE, BL2_BASE, (BL2_LIMIT - BL2_BASE),
					MT_MEMORY | MT_RW | MT_SECURE);
	mmap_add_region(PLAT_UART0_PERI0, PLAT_UART0_PERI0, 0x1000,
					MT_DEVICE | MT_RW | MT_SECURE);
	mmap_add_region(SYSREG_ROT, SYSREG_ROT, SFR_SIZE,
					MT_DEVICE | MT_RW | MT_SECURE);

	mmap_add_region(QSPI2_PERI0, QSPI2_PERI0, SFR_SIZE,	MT_DEVICE | MT_RW | MT_SECURE);
	mmap_add_region(QSPI3_PERI0, QSPI3_PERI0, SFR_SIZE, MT_DEVICE | MT_RW | MT_SECURE);
	/* TODO
	 *	mmap_add_region(QSPI2_PERI1, QSPI2_PERI1, SFR_SIZE,
	 *				MT_DEVICE | MT_RW | MT_SECURE);
	 *	mmap_add_region(QSPI3_PERI1, QSPI3_PERI1, SFR_SIZE,
	 *				MT_DEVICE | MT_RW | MT_SECURE);
	 */
	mmap_add_region(CPMU_PRIVATE, CPMU_PRIVATE, SFR_SIZE, MT_DEVICE | MT_RW | MT_SECURE);
#if USE_GPT
	mmap_add_region(DMA_ROT, DMA_ROT, SFR_SIZE,	MT_DEVICE | MT_RW | MT_SECURE);
	mmap_add_region(SYSREG_SYSREMAP, SYSREG_SYSREMAP, SFR_SIZE, MT_DEVICE | MT_RW | MT_SECURE);

	uint64_t mcode_addr = ((uint64_t)mcode & 0xFFFF000) | (0x1FFULL << 28);

	mmap_add_region(mcode_addr, mcode_addr, 0x2000,	MT_DEVICE | MT_RW | MT_SECURE);
#endif /* USE_GPT */

	init_xlat_tables();

	enable_mmu_el3(0);
}

void bl1_platform_setup(void)
{
	/* TODO: Enable storage I/F to load the next image */
}

struct image_desc *bl1_plat_get_image_desc(unsigned int image_id)
{
	/*
	 * TODO: add a case of real scenario to load an image from a storage
	 * As of now, we're using the pre-loaded(back-door) desc. for bl2
	 */
	static image_desc_t bl2_pre_loaded_img_desc = BL2_PRELOADED_IMAGE_DESC;

	return &bl2_pre_loaded_img_desc;
}

int bl1_plat_handle_post_image_load(unsigned int image_id)
{
	/*
	 * TODO: please consider to use "plat/common/plat_bl1_common.c" later
	 * As of now, to skip a real loading process on ZEBU(Currently, pre-loading the bl2),
	 * this returns 0 while doing nothing.
	 */
	return 0;
}

uint32_t plat_get_syscnt_freq2(void)
{
	return CORE_TIMER_FREQ;
}
