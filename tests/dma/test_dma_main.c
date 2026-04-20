/* Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include "test_common.h"
#include "pl330.h"
#include "test_dma_main.h"
#include "../../drivers/smmu/smmu.h"

static void isr_test(void)
{
	printf("PL330 ISR\n");
}

uint8_t test_main_dma(int argc, char *argv[])
{
	struct dma_config dma_cfg = {0};
	struct dma_block_config dma_block_cfg = {0};

	if (argc != 3)
		return 0;

	uint32_t channel = atoi(argv[0]);
	uint32_t sid = atoi(argv[1]);
	uint32_t ssid = atoi(argv[2]);
	const uint32_t data = 0xaa;
	const size_t size = 0x20;
	const uint64_t src_addr = 0x40000000;
	const uint64_t dst_addr = src_addr + size;

	printf("\r\n\nch->%d sid->%d ssid->%d\r\n", channel, sid, ssid);

	memset((void *)src_addr, data, size);

	dma_cfg.channel_direction = MEMORY_TO_MEMORY;
	dma_cfg.source_data_size = 1U;
	dma_cfg.dest_data_size = 1U;
	dma_cfg.source_burst_length = 1U;
	dma_cfg.dest_burst_length = 1U;
	dma_cfg.dma_callback = (dma_callback_t)isr_test;
	dma_cfg.block_count = 1U;
	dma_cfg.head_block = &dma_block_cfg;

	dma_block_cfg.block_size = size;
	dma_block_cfg.source_address = src_addr;
	dma_block_cfg.dest_address = dst_addr;

	dma_configure(channel, &dma_cfg);

	dma_set_amba_ovrd(sid, ssid, NONSEC);

	dma_start(channel);

	if (memcmp((void *)src_addr, (void *)dst_addr, size)) {
		printf("\r\nPL330 test failed!!\r\n");
		return 1;
	}

	memset((void *)src_addr, 0, size);
	memset((void *)dst_addr, 0, size);

	return 1;
}

static const char help_dma[] =
	"[test_dma {channel} {sid} {ssid}]\r\n"
	" * Test DMA330 with SMMU \r\n"
	"\r\n";

CLI_REGISTER(test_dma, NULL, test_main_dma, help_dma);
