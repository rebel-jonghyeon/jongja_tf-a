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
#include <common/desc_image_load.h>

#include <lib/mmio.h>
#include <lib/xlat_tables/xlat_tables_v2.h>
#include <drivers/ti/uart/uart_16550.h>
#include <drivers/hbm3/hbm3_init.h>
#include <drivers/aw/ucie.h>
#include <drivers/generic_delay_timer.h>
#include <cmu.h>
#include <rebel_h_plat.h>
#include <rebel_h_pmu.h>
#include <rebel_h_pcie.h>
#include <rebel_h_rbc.h>
#include <lib/sic/sic.h>

#include "drivers/smmu/smmu.h"
#include "drivers/mailbox/mailbox.h"
#include <bakery_lock.h>

#if USE_GPT
#include <drivers/arm/pl330.h>
#include "drivers/partition/partition_simple.h"

/* DRAM region for CMRT -> DRAM -> Chiplet3's PCIe SRAM */
#define TBOOT_P0_C3_BUF_BASE	(0x40000000ULL)
#define TBOOT_P1_C3_BUF_BASE	(0x40040000ULL)
#endif /* USE_GPT */

enum tboot_n_boot_sequence {
	NOT_STARTED,
	WAITING_UCIE_INIT,
	HW_INIT,
	HBM3_INIT,
	LOAD_CP0_BL31,
	LOAD_CP0_FREERTOS,
	LOAD_CP1_BL31,
	LOAD_CP1_FREERTOS,
	SEND_SBOOT_S_SECONDARY_CHIPLETS,
	SEND_TBOOT_S_SECONDARY_CHIPLETS,
	RESET_RELEASE_SECONDARY_ROTS,
	REQUEST_CP0_BL31_INTEGRITY,
	RESPONSE_CP0_BL31_INTEGRITY,
	REQUEST_CP0_FREERTOS_INTEGRITY,
	RESPONSE_CP0_FREERTOS_INTEGRITY,
	REQUEST_CP1_BL31_INTEGRITY,
	RESPONSE_CP1_BL31_INTEGRITY,
	REQUEST_CP1_FREERTOS_INTEGRITY,
	RESPONSE_CP1_FREERTOS_INTEGRITY,
	LOAD_SECONDARY_CP0_BL31,
	LOAD_SECONDARY_CP0_FREERTOS,
	LOAD_SECONDARY_CP1_BL31,
	LOAD_SECONDARY_CP1_FREERTOS,
	SET_RVBAR_AND_RESET_SECONDARY_CP0,
	SET_RVBAR_AND_RESET_SECONDARY_CP1,
};

static console_t rebel_console;

void tzpc_init_sysreg_bl2(void);

/*
 * Describes all image that tf-a.bl2 should load from an external storage device.
 * Currently, tf-a.bl31 / FreeRTOS_CP of CP0 is considered only.
 *
 * TODO: Remove 'IMAGE_ATTRIB_SKIP_LOADING' to verify a real scenario.
 * As on now, we're using the next images as pre-loaded(back-doored).
 */
static bl_mem_params_node_t bl2_mem_params_descs[] = {
	{	/* TF-A.BL31 of CP0 */
		.image_id = BL31_IMAGE_ID,
		SET_STATIC_PARAM_HEAD(ep_info, PARAM_EP, VERSION_2, entry_point_info_t,	SECURE |
							  EXECUTABLE | EP_FIRST_EXE), .ep_info.pc = BL31_BASE,
		.ep_info.spsr = SPSR_64(MODE_EL3, MODE_SP_ELX,
		DISABLE_ALL_EXCEPTIONS),
		SET_STATIC_PARAM_HEAD(image_info, PARAM_EP, VERSION_2, image_info_t,
							  IMAGE_ATTRIB_PLAT_SETUP | IMAGE_ATTRIB_SKIP_LOADING),
		.image_info.image_base = BL31_BASE,
		.image_info.image_max_size = BL31_LIMIT - BL31_BASE,
		.next_handoff_image_id = BL33_IMAGE_ID, /* as EL1 non-secure O/S */
	},
	{	/* FreeRTOS_CP of CP0 */
		.image_id = BL33_IMAGE_ID,
		SET_STATIC_PARAM_HEAD(ep_info, PARAM_EP, VERSION_2, entry_point_info_t, SECURE |
							  EXECUTABLE | EP_FIRST_EXE), .ep_info.pc = REBEL_H_FREERTOS_LOAD_BASE,
		.ep_info.spsr = SPSR_64(MODE_EL1, MODE_SP_ELX,
		DISABLE_ALL_EXCEPTIONS),
		SET_STATIC_PARAM_HEAD(image_info, PARAM_EP, VERSION_2, image_info_t,
							  IMAGE_ATTRIB_PLAT_SETUP | IMAGE_ATTRIB_SKIP_LOADING),
		.image_info.image_base = REBEL_H_FREERTOS_LOAD_BASE,
		.image_info.image_max_size = BL33_LIMIT - BL33_BASE,
		.next_handoff_image_id = INVALID_IMAGE_ID, /* End of boot-up process */
	},
};

REGISTER_BL_IMAGE_DESCS(bl2_mem_params_descs)

#if RESET_TO_BL2 /* In case of BL2 entry is EL3 based */
void bl2_el3_early_platform_setup(u_register_t arg0, u_register_t arg1,	u_register_t arg2,
								  u_register_t arg3)
{
	console_16550_register(PLAT_UART0_PERI0, PLAT_UART_CLOCK, PLAT_BAUDRATE, &rebel_console);

	console_set_scope(&rebel_console, CONSOLE_FLAG_BOOT | CONSOLE_FLAG_CRASH |
					  CONSOLE_FLAG_RUNTIME);

#ifndef ZEBU_POC
	/* FIXME: HBMC/DRAM: Temporarily placed here with MMU disabled */
	INFO("BL2: init HBM/DRAM world\n");
	hbm3_init(0);
#else
	NOTICE("BL2: skip hbm3_init(0)\n");
#endif /* ZEBU_POC */
}

void bl2_el3_plat_arch_setup(void)
{
	mmap_add_region(BL2_BASE, BL2_BASE, (BL_CODE_END - BL2_BASE),
					MT_MEMORY | MT_RO | MT_SECURE);
	mmap_add_region(BL_CODE_END, BL_CODE_END, BL2_LIMIT - BL_CODE_END,
					MT_MEMORY | MT_RW | MT_SECURE);
	mmap_add_region(PLAT_UART0_PERI0, PLAT_UART0_PERI0, SFR_SIZE,
					MT_DEVICE | MT_RW | MT_SECURE);

	init_xlat_tables();

	enable_mmu_el3(0);
}
#else /* RESET_TO_BL2 */

#ifdef REBELH_543_TEST
static void rbdma_rbc_ch1_test_rebelh_543(void)
{
	uint32_t data = 0;
	const uint32_t pattern = 0x12345678;
	const uint64_t src = 0x40000000;
	const uint64_t dst = 0x2040000000;

	printf("[CHIP0] RBDMA test..\n");
	data = mmio_read_32(0x1ff370008c); printf("[CHIP0] 0x1ff370008c: %x\n", data);
	mmio_write_32(0x1ff370008c, 0x00401780);
	data = mmio_read_32(0x1ff3700090); printf("[CHIP0] 0x1ff3700090: %x\n", data);
	mmio_write_32(0x1ff3700090, 0x00000006);
	data = mmio_read_32(0x1ff3700000); printf("[CHIP0] 0x1ff3700000: %x\n", data);
	data = mmio_read_32(0x1ff3700004); printf("[CHIP0] 0x1ff3700004 : %x\n", data);
	data = mmio_read_32(0x1ff3700008); printf("[CHIP0] 0x1ff3700008 : %x\n", data);
	data = mmio_read_32(0x1ff370000c); printf("[CHIP0] 0x1ff370000c : %x\n", data);
	data = mmio_read_32(0x1ff3700010); printf("[CHIP0] 0x1ff3700010 : %x\n", data);
	data = mmio_read_32(0x1ff3700014); printf("[CHIP0] 0x1ff3700014 : %x\n", data);
	mmio_write_32(0x1ff3700008, 0x00000000);

	printf("[CHIP0] src buffer setting..\n");
	for (int offset = 0; offset < (1 << 20); offset += 4) {
		if (offset % (1 << 14) == 0)
			printf("s 0x%lx\n", src + offset);
		mmio_write_32(src + offset, pattern);
	}

	mmio_write_32(0x1ff3700300, 0x08000200);
	mmio_write_32(0x1ff3700304, 0x0a000200);
	mmio_write_32(0x1ff3700340, 0x00000100);
	mmio_write_32(0x1ff3700350, 0x00000000);
	mmio_write_32(0x1ff3700354, 0x00000001);
	mmio_write_32(0x1ff3700200, 0x00000000);
	mmio_write_32(0x1ff3700204, 0x02000000);
	mmio_write_32(0x1ff3700208, 0x02800000);
	mmio_write_32(0x1ff370020c, 0x00002000);
	mmio_write_32(0x1ff3700210, 0x00000000);
	mmio_write_32(0x1ff3700214, 0x00000000);
	mmio_write_32(0x1ff3700218, 0x00000100);
	mmio_write_32(0x1ff370021c, 0x0ffa0205);

	printf("[CHIP0] checking..\n");
	do {
		data = mmio_read_32(0x1ff3700120);
	} while ((data & 0x1) != 0x1);
	data = mmio_read_32(0x1ff3700128); printf("[CHIP0] 0x1ff3700128: %x\n", data);

	printf("[CHIP0] result..\n");
	for (long offset = 0; offset < (1 << 20); offset += 4) {
		if (offset % (1 << 14) == 0)
			printf("d 0x%lx\n", dst + offset);
		data = mmio_read_32(dst + offset);
		if (data != pattern)
			printf("[CHIP0] 0x%lx -> 0x%x\n", dst + offset, data);
	}
	printf("Test Done\n");
}
#endif /* REBELH_543_TEST */

/* In case of BL2 entry is EL1 based */
void bl2_early_platform_setup2(u_register_t arg0, u_register_t arg1, u_register_t arg2,
							   u_register_t arg3)
{
	console_16550_register(PLAT_UART0_PERI0, PLAT_UART_CLOCK, PLAT_BAUDRATE, &rebel_console);

	console_set_scope(&rebel_console, CONSOLE_FLAG_BOOT | CONSOLE_FLAG_CRASH |
					  CONSOLE_FLAG_RUNTIME);

#ifndef ZEBU_POC
	char noti[] = "end";

	/* Enable generic timer clock source */
	mmio_write_32(CSS600_CNTGEN + CNTCR, CNTEN);

	generic_delay_timer_init();

	uint32_t bootmode = pmu_get_bootmode();
	/*
	 * Check the number of secondary chiplets
	 * This will return
	 * 1-chiplet: 0
	 * 2-chiplet: 1
	 * 4-chiplet: 3
	 */
#if CHIPLET_COUNT > 1
	uint32_t secondary_chiplet_cnt = plat_get_secondary_chiplet_cnt();

	NOTICE("BL2: Detected secondary chiplet count: %d\n", secondary_chiplet_cnt);
	BOOT_LOG(CP0, TBOOT_N, WAITING_UCIE_INIT);
	wait_ucie_link_up_for_CP();
#else
	/* single chiplet only based */
	uint32_t secondary_chiplet_cnt = 0;
#endif

	for (uint32_t chiplet_id = 0; chiplet_id <= secondary_chiplet_cnt; chiplet_id++)
		plat_set_secondary_chiplet_cnt(chiplet_id, secondary_chiplet_cnt);

	BOOT_LOG(CP0, TBOOT_N, HW_INIT);

	for (uint32_t chiplet_id = 0; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
		NOTICE("BL2: Init CMU of chiplet-%d\n", chiplet_id);
		cmu_init_bl2(CHIPLET_OFFSET * chiplet_id);
	}

#if CHIPLET_COUNT > 1
	ucie_link_up_for_others();
#endif /* CHIPLET_COUNT */
	BOOT_LOG(CP0, TBOOT_N, HBM3_INIT);

	uint32_t hbm_ret = 0;

	for (uint32_t chiplet_id = 0; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
		NOTICE("BL2: Init HBM of chiplet-%d\n", chiplet_id);
		if (hbm3_init(chiplet_id)) {
			hbm_ret |= (1 << chiplet_id);
		}
	}
	if (hbm_ret) {
		for (uint32_t chiplet_id = 0; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
			if (hbm_ret & (1 << chiplet_id))
				ERROR("HBM Boot on chiplet%d FAIL\n", chiplet_id);
		}
		asm("b .");
	}

#if !ZEBU
	NOTICE("BL2: Run ECC init\n");
	for (uint32_t chiplet_id = 0; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
		hbm_ecc_scrub_init(chiplet_id);
	}
#endif

#if defined(HBM_EOM)
	// Draw All Channel EOM
	for (uint32_t chiplet_id = 0; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
		NOTICE("BL2: Run HBM%d EOM\n", chiplet_id);
		run_eom(chiplet_id);

		// Draw 64 DQ EOM per Channel
		// run_eom_dq(0);
	}

	asm("b .");
#elif defined(HBM_AMT)
	for (uint32_t chiplet_id = 0; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
		NOTICE("BL2: Run HBM%d AMT\n", chiplet_id);
		run_memtest(chiplet_id);
	}
#endif

	tzpc_init_sysreg_bl2();

	NOTICE("BL2: EVT version: 0x%x\n", GET_REVISION);

#if USE_GPT
	gpt_partition_init();
	NOTICE("BL2: gpt init is done\n");
#endif /* USE_GPT */
	switch (bootmode) {
	case SECURE_XIP_BOOT:
		BOOT_LOG(CP0, TBOOT_N, SEND_SBOOT_S_SECONDARY_CHIPLETS);
#if USE_GPT
		/* In case of XIP bootmode, tboot_n needs to transfer sboot_s */
		for (uint32_t chiplet_id = 1; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
			NOTICE("BL2: Secure XIP boot path, load sboot_s for chiplet-%d\n", chiplet_id);
			dma_load_image(XIP_DEST_ADDR_SBOOT_S + chiplet_id * CHIPLET_OFFSET,
						   XIP_FLASH_BASE_ADDR,
						   XIP_DEST_SIZE_SBOOT_S);
		}
		/*
		 * In XIP boot mode, the behavior after tboot_s is performed in the same way
		 * as the secure OTP boot.
		 */
#endif /* USE_GPT */
	case SECURE_OTP_BOOT:
		BOOT_LOG(CP0, TBOOT_N, SEND_TBOOT_S_SECONDARY_CHIPLETS);
#if USE_GPT
		for (uint32_t chiplet_id = 1; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
			NOTICE("BL2: Secure boot path, load tboot_s for chiplet-%d\n", chiplet_id);
			dma_load_image(GPT_DEST_ADDR_TBOOT_S + chiplet_id * CHIPLET_OFFSET,
						   gpt_get_address_by_entry(GPT_ENTITY_INDEX_TBOOT_S)
						   - GPT_HEADER_FIELD_SIZE,
						   gpt_get_length_by_entry(GPT_ENTITY_INDEX_TBOOT_S)
						   + GPT_HEADER_FIELD_SIZE);
		}
#endif /* USE_GPT */
		/* Reset secondary chiplet's ROT */
		BOOT_LOG(CP0, TBOOT_N, RESET_RELEASE_SECONDARY_ROTS);
		for (uint32_t chiplet_id = 1; chiplet_id <= secondary_chiplet_cnt; chiplet_id++)
			plat_pmu_reset_rot(chiplet_id);

		/* Enabling Chiplet-3's PCIe is supported on EVT1/QUAD only */
		if (secondary_chiplet_cnt == 3 && GET_REVISION == REVISION_EVT1) {

#if USE_GPT
			NOTICE("BL2: TBOOT_P0 for chiplet-3 request\n");
			request_to_cmrt(CMRT_MW_LOAD_TBOOT_P0_C3);

			dma_load_image(GPT_DEST_ADDR_TBOOT_P0 + CHIPLET_ID3 * CHIPLET_OFFSET,
						   TBOOT_P0_C3_BUF_BASE,
						   GPT_DEST_SIZE_TBOOT_P0);
			NOTICE("BL2: TBOOT_P0 for chiplet-3 request done\n");
#endif /* USE_GPT */
			NOTICE("BL2: Release reset of chiplet-3's CM7\n");
			pmu_release_cm7(CHIPLET_ID3);

#if PCIE_PHY_SRAM_LOAD
			cm7_wait_phy_sram_init_done(CHIPLET_ID3);
#if USE_GPT
			NOTICE("BL2: TBOOT_P1 for chiplet-3 request\n");
			request_to_cmrt(CMRT_MW_LOAD_TBOOT_P1_C3);

			mmio_write_32(SYSREG_PCIE + MUX_CR_PARA_SEL, MUX_CR_PARA_SEL_BROADCAST);
			dma_load_image(GPT_DEST_ADDR_TBOOT_P1_PHY0 + CHIPLET_ID3 * CHIPLET_OFFSET,
						   TBOOT_P1_C3_BUF_BASE,
						   GPT_DEST_SIZE_TBOOT_P1);

			mmio_write_32(PHY0_APB2CR_PARA_PCIE + CHIPLET_ID3 * CHIPLET_OFFSET + MUX_SWITCH,
						  MUX_VALUE);

			dma_load_image(GPT_DEST_ADDR_TBOOT_P1_PHY0 + CHIPLET_ID3 * CHIPLET_OFFSET,
						   TBOOT_P1_C3_BUF_BASE + GPT_DEST_SIZE_TBOOT_P1,
						   GPT_DEST_SIZE_TBOOT_P1);

			mmio_write_32(PHY0_APB2CR_PARA_PCIE + CHIPLET_ID3 * CHIPLET_OFFSET + MUX_SWITCH, 0);
			mmio_write_32(SYSREG_PCIE + MUX_CR_PARA_SEL, MUX_CR_PARA_SEL_SEPARATE);

			NOTICE("BL2: TBOOT_P1 for chiplet-3 request done\n");
#endif /* USE_GPT */
			cm7_notify_load_done(CHIPLET_ID3);
#endif /* PCIE_PHY_SRAM_LOAD */
		} /* End of the condition, Secure boot & EVT1 & QUAD case for chiplet-3 PCIe */

		/* SMMU early init */
		smmu_early_init(secondary_chiplet_cnt);

		ipm_samsung_write(IDX_MAILBOX_CP0_M4, 0, noti, sizeof(noti) - 1, M_CPU1);
		ipm_samsung_send(IDX_MAILBOX_CP0_M4, 0, DRAM_INIT_DONE_CHANNEL, M_CPU1);

		NOTICE("BL2: CP0_BL31 request\n");
		BOOT_LOG(CP0, TBOOT_N, REQUEST_CP0_BL31_INTEGRITY);
#if USE_GPT
		request_to_cmrt(CMRT_MW_LOAD_CP0_BL31);
#endif /* USE_GPT */
		BOOT_LOG(CP0, TBOOT_N, RESPONSE_CP0_BL31_INTEGRITY);
		NOTICE("BL2: CP0_BL31 request done\n");

		NOTICE("BL2: CP0_FREERTOS request\n");
		BOOT_LOG(CP0, TBOOT_N, REQUEST_CP0_FREERTOS_INTEGRITY);
#if USE_GPT
		request_to_cmrt(CMRT_MW_LOAD_CP0_FREERTOS);
#endif /* USE_GPT */
		BOOT_LOG(CP0, TBOOT_N, RESPONSE_CP0_FREERTOS_INTEGRITY);
		NOTICE("BL2: CP0_FREERTOS request done\n");

		NOTICE("BL2: CP1_BL31 request\n");
		BOOT_LOG(CP0, TBOOT_N, REQUEST_CP1_BL31_INTEGRITY);
		request_to_cmrt(CMRT_MW_LOAD_CP1_BL31);
		BOOT_LOG(CP0, TBOOT_N, RESPONSE_CP1_BL31_INTEGRITY);
		NOTICE("BL2: CP1_BL31 request done\n");

		NOTICE("BL2: CP1_FREERTOS request\n");
		BOOT_LOG(CP0, TBOOT_N, REQUEST_CP1_FREERTOS_INTEGRITY);
		request_to_cmrt(CMRT_MW_LOAD_CP1_FREERTOS);
		BOOT_LOG(CP0, TBOOT_N, RESPONSE_CP1_FREERTOS_INTEGRITY);
		NOTICE("BL2: CP1_FREERTOS request done\n");

		break;
	case NORMAL_BOOT:
	case WFD_BOOT:
		/* Enabling Chiplet-3's PCIe is supported on EVT1/QUAD only */
		if (secondary_chiplet_cnt == 3 && GET_REVISION == REVISION_EVT1) {
#if USE_GPT
			NOTICE("BL2: Load tboot_p0 for chiplet-3\n");
			dma_load_image(GPT_DEST_ADDR_TBOOT_P0 + CHIPLET_ID3 * CHIPLET_OFFSET,
						   TBOOT_P0_SRC_ADDR + IMAGE_SIZE_FIELD,
						   GPT_DEST_SIZE_TBOOT_P0);
#endif /* USE_GPT */
			NOTICE("BL2: Release reset of chiplet-3's CM7\n");
			pmu_release_cm7(CHIPLET_ID3);

#if PCIE_PHY_SRAM_LOAD
			cm7_wait_phy_sram_init_done(CHIPLET_ID3);
#if USE_GPT
			NOTICE("BL2: Load tboot_p1 for chiplet-3\n");

			mmio_write_32(SYSREG_PCIE + MUX_CR_PARA_SEL, MUX_CR_PARA_SEL_BROADCAST);
			dma_load_image(GPT_DEST_ADDR_TBOOT_P1_PHY0 + CHIPLET_ID3 * CHIPLET_OFFSET,
						   TBOOT_P1_SRC_ADDR + IMAGE_SIZE_FIELD,
						   GPT_DEST_SIZE_TBOOT_P1);

			mmio_write_32(PHY0_APB2CR_PARA_PCIE + CHIPLET_ID3 * CHIPLET_OFFSET + MUX_SWITCH,
						  MUX_VALUE);

			dma_load_image(GPT_DEST_ADDR_TBOOT_P1_PHY0 + CHIPLET_ID3 * CHIPLET_OFFSET,
						   TBOOT_P1_SRC_ADDR + IMAGE_SIZE_FIELD + GPT_DEST_SIZE_TBOOT_P1,
						   GPT_DEST_SIZE_TBOOT_P1);

			mmio_write_32(PHY0_APB2CR_PARA_PCIE + CHIPLET_ID3 * CHIPLET_OFFSET + MUX_SWITCH, 0);
			mmio_write_32(SYSREG_PCIE + MUX_CR_PARA_SEL, MUX_CR_PARA_SEL_SEPARATE);
#endif /* USE_GPT */
			cm7_notify_load_done(CHIPLET_ID3);
#endif /* PCIE_PHY_SRAM_LOAD */
		}

		/* SMMU early init */
		smmu_early_init(secondary_chiplet_cnt);

		ipm_samsung_write(IDX_MAILBOX_CP0_M4, 0, noti, sizeof(noti) - 1, M_CPU1);
		ipm_samsung_send(IDX_MAILBOX_CP0_M4, 0, DRAM_INIT_DONE_CHANNEL, M_CPU1);

#if USE_GPT
		BOOT_LOG(CP0, TBOOT_N, LOAD_CP0_BL31);
		NOTICE("BL2: Chiplet 0 load start\n");
		dma_load_image(GPT_DEST_ADDR_BL31,
					   gpt_get_address_by_entry(GPT_ENTITY_INDEX_BL31),
					   gpt_get_length_by_entry(GPT_ENTITY_INDEX_BL31));
		NOTICE("BL2: BL31 load is done\n");

		BOOT_LOG(CP0, TBOOT_N, LOAD_CP0_FREERTOS);
		dma_load_image(GPT_DEST_ADDR_FREERTOS,
					   gpt_get_address_by_entry(GPT_ENTITY_INDEX_FREERTOS),
					   gpt_get_length_by_entry(GPT_ENTITY_INDEX_FREERTOS));
		NOTICE("BL2: FREERTOS load is done\n");

		BOOT_LOG(CP0, TBOOT_N, LOAD_CP1_BL31);
		dma_load_image(GPT_DEST_ADDR_BL31_CP1,
					   gpt_get_address_by_entry(GPT_ENTITY_INDEX_BL31_CP1),
					   gpt_get_length_by_entry(GPT_ENTITY_INDEX_BL31_CP1));
		NOTICE("BL2: BL31 CP1 load is done\n");

		BOOT_LOG(CP0, TBOOT_N, LOAD_CP1_FREERTOS);
		dma_load_image(GPT_DEST_ADDR_FREERTOS_CP1,
					   gpt_get_address_by_entry(GPT_ENTITY_INDEX_FREERTOS_CP1),
					   gpt_get_length_by_entry(GPT_ENTITY_INDEX_FREERTOS_CP1));
		NOTICE("BL2: FREERTOS CP1 load is done\n");
#endif /* USE_GPT */
		break;
	default:
		ERROR("Unexpected bootmode : %d\n", bootmode);
		assert(0);
		break;
	}
#if USE_GPT
	for (uint32_t i = 1; i < secondary_chiplet_cnt + 1; i++) {
		NOTICE("BL2: Chiplet %d load start\n", i);
		BOOT_LOG(CP0, TBOOT_N, LOAD_SECONDARY_CP0_BL31);
		dma_load_image(GPT_DEST_ADDR_BL31 + i * CHIPLET_OFFSET,
					   GPT_DEST_ADDR_BL31,
					   gpt_get_length_by_entry(GPT_ENTITY_INDEX_BL31));
		NOTICE("BL2: BL31 load is done\n");

		BOOT_LOG(CP0, TBOOT_N, LOAD_SECONDARY_CP0_FREERTOS);
		dma_load_image(GPT_DEST_ADDR_FREERTOS + i * CHIPLET_OFFSET,
					   GPT_DEST_ADDR_FREERTOS,
					   gpt_get_length_by_entry(GPT_ENTITY_INDEX_FREERTOS));
		NOTICE("BL2: FREERTOS load is done\n");

		BOOT_LOG(CP0, TBOOT_N, LOAD_SECONDARY_CP1_BL31);
		dma_load_image(GPT_DEST_ADDR_BL31_CP1 + i * CHIPLET_OFFSET,
					   GPT_DEST_ADDR_BL31_CP1,
					   gpt_get_length_by_entry(GPT_ENTITY_INDEX_BL31_CP1));
		NOTICE("BL2: BL31 CP1 load is done\n");

		BOOT_LOG(CP0, TBOOT_N, LOAD_SECONDARY_CP1_FREERTOS);
		dma_load_image(GPT_DEST_ADDR_FREERTOS_CP1 + i * CHIPLET_OFFSET,
					   GPT_DEST_ADDR_FREERTOS_CP1,
					   gpt_get_length_by_entry(GPT_ENTITY_INDEX_FREERTOS_CP1));
		NOTICE("BL2: FREERTOS CP1 load is done\n");
	}
#endif /* USE_GPT */
#ifdef REBELH_543_TEST
	rbdma_rbc_ch1_test_rebelh_543();
#endif /* REBELH_543_TEST */

	BOOT_LOG(CP0, TBOOT_N, SET_RVBAR_AND_RESET_SECONDARY_CP0);
	for (uint32_t chiplet_id = 1; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
		NOTICE("BL2: Re-reset CP0.cpu0 of chiplet-%d\n", chiplet_id);
		plat_set_cpu_rvbar(chiplet_id, CLUSTER_CP0, CPU0, BL31_BASE);
		if (!(bootmode == SECURE_OTP_BOOT || bootmode == SECURE_XIP_BOOT)) {
			plat_pmu_cpu_off(chiplet_id, CLUSTER_CP0, CPU0);
		} else {
			plat_pmu_cl_on(chiplet_id, CLUSTER_CP0);
		}
		plat_pmu_cpu_on(chiplet_id, CLUSTER_CP0, CPU0);
	}

	rebel_bakery_lock_init();
	NOTICE("BL2: Release a reset of CP1.cpu0\n");
	BOOT_LOG(CP0, TBOOT_N, SET_RVBAR_AND_RESET_SECONDARY_CP1);

	for (uint32_t chiplet_id = 0; chiplet_id <= secondary_chiplet_cnt; chiplet_id++) {
		plat_set_cpu_rvbar(chiplet_id, CLUSTER_CP1, CPU0, GPT_DEST_ADDR_BL31_CP1);
		plat_pmu_cl_on(chiplet_id, CLUSTER_CP1);
		plat_pmu_cpu_on(chiplet_id, CLUSTER_CP1, CPU0);
	}

	if (secondary_chiplet_cnt == 3 && GET_REVISION == REVISION_EVT1) {
		ipm_samsung_write(IDX_MAILBOX_CP0_M4_C3, 0, noti, sizeof(noti) - 1, M_CPU1);
		ipm_samsung_send(IDX_MAILBOX_CP0_M4_C3, 0, DRAM_INIT_DONE_CHANNEL, M_CPU1);
	}
#endif /* ZEBU_POC */
}

void bl2_plat_arch_setup(void)
{
	mmap_add_region(BL2_BASE, BL2_BASE, (BL_CODE_END - BL2_BASE),
					MT_MEMORY | MT_RO | MT_SECURE);
	mmap_add_region(BL_CODE_END, BL_CODE_END, BL2_LIMIT - BL_CODE_END,
					MT_MEMORY | MT_RW | MT_SECURE);
	mmap_add_region(ADDR_MASK_2M(PLAT_UART0_PERI0), ADDR_MASK_2M(PLAT_UART0_PERI0),
					SIZE_2M_REGION,	MT_DEVICE | MT_RW | MT_SECURE);

	mmap_add_region(ADDR_MASK_2M(MAILBOX_CP0_M4), ADDR_MASK_2M(MAILBOX_CP0_M4),
					SIZE_2M_REGION,	MT_DEVICE | MT_RW | MT_SECURE);
	mmap_add_region(ADDR_MASK_2M(MAILBOX_CP0_M4_C3), ADDR_MASK_2M(MAILBOX_CP0_M4_C3),
					SIZE_2M_REGION, MT_DEVICE | MT_RW | MT_SECURE);

	mmap_add_region(ADDR_MASK_2M(SYSREG_SYSREMAP_PRIVATE), ADDR_MASK_2M(SYSREG_SYSREMAP_PRIVATE),
					SIZE_2M_REGION,	MT_DEVICE | MT_RW | MT_SECURE);
	mmap_add_region(ADDR_MASK_2M(SYSREG_NBUS_D), ADDR_MASK_2M(SYSREG_NBUS_D),
					SIZE_2M_REGION,	MT_DEVICE | MT_RW | MT_SECURE);
	mmap_add_region(ADDR_MASK_2M(TCU), ADDR_MASK_2M(TCU),
					SIZE_2M_REGION,	MT_DEVICE | MT_RW | MT_SECURE);
	mmap_add_region(ADDR_MASK_2M(SMMU_STE_BASE_ADDR), ADDR_MASK_2M(SMMU_STE_BASE_ADDR),
					SIZE_2M_REGION,	MT_DEVICE | MT_RW | MT_SECURE);
	mmap_add_region(ADDR_MASK_2M(SMMU_ACP_MEM_ADDR), ADDR_MASK_2M(SMMU_ACP_MEM_ADDR),
					SIZE_2M_REGION, MT_MEMORY | MT_RW | MT_SECURE | MT_SHAREABILITY_ISH);
	mmap_add_region(ADDR_MASK_2M(XIP_FLASH_BASE_ADDR), ADDR_MASK_2M(XIP_FLASH_BASE_ADDR),
					SIZE_2M_REGION * 8,	MT_MEMORY | MT_RO | MT_SECURE);

	init_xlat_tables();

	enable_mmu_el1(0);
}
#endif /* RESET_TO_BL2 */

void tzpc_init_sysreg_bl2(void)
{
	/* TODO, check if valid */

	/* SYSREG_ROT */
	/* TZPC_PROT0STAT SFR description
	 * [31:17] : Reserved							/ [16] : Used for SYSREG_SYSREMAP.TrustZone info
	 * [15:14] : Not used							/ [13] : CSSYS_DP		/ [12] : DMA330
	 * [11] : Not used		/ [10] : MAILBOX_M2		/ [9] : MAILBOX_M1	/ [8] : MAILBOX_M0
	 * [7] : OTP_CON_CPU	/ [6] : PVT_CON			/ [5] : OTP_CON_SOC	/ [4] : GPIO
	 * [3] : Central_PMU	/ [2] : SYSREG_SYSREMAP	/ [1] : SYSREG_ROT	/ [0] : CMU_ROT
	 */
	// mmio_write_32(SYSREG_ROT + SYSREG_ROT_TZPC_PROT0SET, U(0x000137FF));

	/* SYSREG_CP0/1 */
	/* TZPC_PROT0STAT SFR desciption
	 * [31:6] : Reserved								/ [5] : MAILBOX_M4	/ [4] : MAILBOX_M3
	 * [3] : ADD_CON_CP		/ [2] : SYSREG_BUSCSR_CP	/ [1] : Reserved	/ [0] : CMU_CP
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31:0] : Reserved
	 */
	mmio_write_32(SYSREG_CP0 + SYSREG_CP_TZPC_PROT0SET, U(0x0000003D));
	mmio_write_32(SYSREG_CP1 + SYSREG_CP_TZPC_PROT0SET, U(0x0000003D));
	mmio_write_32(SYSREG_CP0 + SYSREG_CP_TZPC_PROT1SET, U(0x00000000));
	mmio_write_32(SYSREG_CP1 + SYSREG_CP_TZPC_PROT1SET, U(0x00000000));

	/* SYSREG_DRAM */
	/* TZPC_PROT0STAT SFR description
	 * 0x40 : HBMC (4MB) ??				/ 0x80 || 0x9F : HBMPHY_ICON (1MB + 64KB) ??
	 * [31:4] : Reserved
	 * [3] : TrustZoneInfo for PHY+ICON	/ [2] : TrustZoneInfo for Controller	/
	 * [1] : TrustZoneInfo for SYSREG(tie_1)	/ [0] : TrustZoneInfo for CMU
	 */
	mmio_write_32(SYSREG_DRAM + SYSREG_DRAM_TZPC_PROT0SET, U(0x0000000F));

	/* SYSREG_EBUS */

	/* SYSREG_NBUS */
	/* TZPC_PROT0STAT SFR description
	 * [31:16] : Not Used	/ [15] : TrustZoneInfo_SYSREG_BUSCSR_NBUS__CONTROL_SYSREG_TZPC
	 * [14:11] : Not used	/ [10] : NOC_C_NBUS_L			/ [9] : NOC_D_NBUS_L_W	/
	 * [8] : NOC_D_NBUS_L_R
	 * [7:4] : Not used
	 * [3] : GPIO_NBUS_L	/ [2] : SYSREG_BUSCSR_NBUS_L	/ [1] : SYSREG_NBUS_L	/
	 * [0] : CMU_NBUS_L
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31:28] : Not used	/ [27] : Clears_the_corresponding_decode_protection_output
	 * [26:16] : Not used
	 * [15] : CBUS DBG TZPC	/ [14:0] : Not used
	 */

	mmio_write_32(SYSREG_NBUS_D + SYSREG_NBUS_TZPC_PROT1SET, U(0x00008000));

	/* SYSREG_PCIE */
	/* TZPC_PROT0STAT SFR description
	 * [31:19] : Not used
	 *						/ [18] : NOC_PCIE to TZPC_DBI				/ [17:16] : Not used
	 * [15] : VDM			/ [14] : IAT			/ [13] : IDE		/ [12] : Not used
	 * [11:9] : Not used												/ [8] : pcie_sub_ctrl_inst
	 * [7] : Not used		/ [6] : MAILBOX			/ [5] : GPIO_PCIE	/ [4] : WDT_PCIE
	 * [3] : UART_PCIE		/ [2] : SYSREG_BUSSCSR	/ [1] : SYSREG_PCIE	/ [0] : CMU_PCIE
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31:16] : Not used
	 * [15] : PHY3_APB2CR_PARA	/ [14] : PHY3_APB2CR_PARA	/ [13] : PHY3_APB2CR_PARA	/
	 * [12] : PHY3_APB2CR_PARA
	 * [11] : PHY2_APB2CR_PARA	/ [10] : PHY2_APB2CR_PARA	/ [9] : PHY2_APB2CR_PARA	/
	 * [8] : PHY2_APB2CR_PARA
	 * [7] : PHY1_APB2CR_PARA	/ [6] : PHY1_APB2CR_PARA	/ [5] : PHY1_APB2CR_PARA	/
	 * [4] : PHY1_APB2CR_PARA
	 * [3] : PHY0_APB2CR_PARA	/ [2] : PHY0_APB2CR_PARA	/ [1] : PHY0_APB2CR_PARA	/
	 * [0] : PHY0_APB2CR_PARA
	 */
	// mmio_write_32(SYSREG_PCIE + SYSREG_PCIE_TZPC_PROT0SET, U(0x0004F17F));
	// mmio_write_32(SYSREG_PCIE + SYSREG_PCIE_TZPC_PROT1SET, U(0x0000FFFF));

	/* SYSREG_PERI0/1 */
	/* TZPC_PROT0STAT SFR description
	 * [31:12] : Not used
	 * [11] : GPIO_PERI	/ [10] : PWM_PERI	/ [9] : WDT1_PERI	/ [8] : WDT0_PERI
	 * [7] : I2C1_PERI	/ [6] : I2C0_PERI	/ [5] : UART1_PERI	/ [4] : UART0_PERI
	 * [3:2] : Not used						/ [1] : SYSREG_PERI	/ [0] : CMU_PERI
	 */
	/* TZPC_PROT1STAT SFR description
	 * [31:10] : Not used									/ [9] : MAILBOX_PERI_M14	/
	 [8] : MAILBOX_PERI_M13
	 * [7] : MAILBOX_PERI_M12	/ [6] : MAILBOX_PERI_M11	/ [5] : MAILBOX_PERI_M10	/
	 [4] : MAILBOX_PERI_M9
	 * [3] : MAILBOX_PERI_M8	/ [2] : MAILBOX_PERI_M7		/ [1] : MAILBOX_PERI_M6		/
	 [0] : MAILBOX_PERI_M5
	 */
	mmio_write_32(SYSREG_PERI0 + SYSREG_PERI_TZPC_PROT0SET, U(0x00000FF3));
	mmio_write_32(SYSREG_PERI0 + SYSREG_PERI_TZPC_PROT1SET, U(0x000003FF));

	mmio_write_32(SYSREG_PERI1 + SYSREG_PERI_TZPC_PROT0SET, U(0x00000FF3));
	mmio_write_32(SYSREG_PERI1 + SYSREG_PERI_TZPC_PROT1SET, U(0x000003FF));
	/* SYSREG_SBUS */

	/* SYSREG_WBUS */
	mmio_write_32(SYSREG_WBUS_U + SYSREG_WBUS_TZPC_PROT0SET, U(0x00000307));
}

void bl2_platform_setup(void)
{
	/* TODO: Enable storage I/F controller and some others */
	/* NOTE: MMU already enabled here */
}

uint32_t plat_get_syscnt_freq2(void)
{
	return CORE_TIMER_FREQ;
}
