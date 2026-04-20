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
#include <stdio.h>
#include <uart.h>
#include <rebel_h_platform.h>
#include <image.h>
#include <string.h>
#include <drivers/spi/dwc_ssi.h>
#include <drivers/flash/nor.h>
#include "dma.h"

extern void safe_zone(void);

static void qspi_init(void);

int __main(void)
{
	uart_init();
	INIT_BOOT_LOG(CHIPLET_ID);
	BOOT_LOG(CP0, FBOOT_N, 6);

#ifndef SBOOT_N_PRELOAD
	/* Check a size of next image */
	uint32_t image_size;

	memcpy(&image_size, (void *)(BL1_FLASH_OFFSET), 4);

	if (image_size == 0 || image_size > BL1_SIZE_MAX) {
		BOOT_LOG(CP0, FBOOT_N, 7);
		printf("ERROR: image size error : %d bytes\n", image_size);
		safe_zone();
	}
	BOOT_LOG(CP0, FBOOT_N, 8);

	/* Configuration for Flash-read performance */
	qspi_init();
	BOOT_LOG(CP0, FBOOT_N, 9);

	/*
	 * DMA copy
	 * Src: BL1_OFFSET + IMAGE_OFFSET (First 8 Byte has a size info)
	 * Dst: BL1_ENTRY (0x1E_0001_0000 == 0x1F_F001_0000)
	 * Size: Given by the sboot_n's image header
	 */
	dma_load(BL1_FLASH_OFFSET + IMAGE_OFFSET, BL1_ENTRY_DEST, image_size);
#endif
	BOOT_LOG(CP0, FBOOT_N, 10);

	jump_to_next_image(BL1_ENTRY);

	/* Not expected here */
	safe_zone();

	return 0;
}

static void qspi_init(void)
{
	/*
	 * QSPI <-> Flash settings
	 * SPI clock: 20MHz (IP: 40MHz --(div:1/2)--> sclk_out: 20MHz)
	 * XIP Read command: 0xe7 (command/addr/data:1-4-4 STR, dummy: 4 cycle)
	 */
	volatile struct dwc_ssi *qspi_boot = (struct dwc_ssi *)QSPI_BOOT;

	dwc_ssi_set_buadrate(qspi_boot, DIV2);

	dwc_ssi_set_xip_ctrl(qspi_boot, CONT_XFER_EN | DUMMY4);
}
