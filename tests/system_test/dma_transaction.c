/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */
#include "dma_transaction.h"
#include "pl330.h"
#include "rebel_h_platform.h"

static void _flush_all_cache(void)
{
	asm volatile("mov x0, #1");
	asm volatile("MSR S1_1_C15_C14_0, x0");
	asm volatile("DSB sy");

	asm volatile("mov x0, #2");
	asm volatile("MSR S1_1_C15_C14_0, x0");
	asm volatile("DSB sy");
}

static void _systest_isr_test(void)
{
	printf("[SYSTEST] PL330 ISR\n");
}

void transfer_data(uint32_t target_chiplet_id, uint32_t *src, uint32_t *dst, size_t length)
{
	printf("src->%p dst->%p length->0x%lx\n", src, dst, length);
	struct dma_config dma_cfg = {0};
	struct dma_block_config dma_block_cfg = {0};
	const uint32_t channel = 0;
	const uint32_t sid = 0;
	const uint32_t ssid = 0;

	dma_cfg.channel_direction = MEMORY_TO_MEMORY;
	dma_cfg.source_data_size = 128U;
	dma_cfg.dest_data_size = 128U;
	dma_cfg.source_burst_length = 16U;
	dma_cfg.dest_burst_length = 16U;
	dma_cfg.dma_callback = (dma_callback_t)_systest_isr_test;
	dma_cfg.block_count = 1U;
	dma_cfg.head_block = &dma_block_cfg;

	size_t unaligned_len = length % (dma_cfg.source_data_size * dma_cfg.source_burst_length);

	length -= unaligned_len;
	if (length > 0) {
		dma_block_cfg.block_size = length;
		dma_block_cfg.source_address = (uint64_t)src;
		dma_block_cfg.dest_address = (uint64_t)dst;

		dma_configure(channel, &dma_cfg);
		dma_set_amba_ovrd(sid, ssid, NONSEC);
		dma_start(channel);
	}

	if (unaligned_len > 0) {
		uint8_t *src_bytes = (uint8_t *)src;
		uint8_t *dst_bytes = (uint8_t *)dst;

		src_bytes += length;
		dst_bytes += length;
		for (uint32_t offset = 0; offset < unaligned_len; dst_bytes++, src_bytes++, offset++) {
			*dst_bytes = *src_bytes;
		}
	}
	_flush_all_cache();
}
