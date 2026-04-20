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

#include "test_common.h"
#include "test_ca73_smp.h"
#include "test_ca73_context.h"
#include <cache.h>

/* TODO: Change these code after refactoring UART driver */
static uint64_t test_ca73_uart_per_core[] = {
	UART0_PERI0,
	UART1_PERI0,
	UART0_PERI1,
	UART1_PERI1,
};

/* TODO: Change these code after refactoring UART driver */
static void test_ca73_uart_init(uint64_t uart_regs)
{
	volatile struct dw_apb_uart_regs *regs = (volatile struct dw_apb_uart_regs *)uart_regs;
	uint32_t baud_rate = TARGET_BAUD_RATE * 16;
	uint32_t temp;

	/* Config MCR, No modem control support */
	regs->mcr = 0x0;

	/* set the DLAB to access the baud rate divisor registers */
	regs->lcr |= LCR_DLAB;

	/* Calculate dll/dlh/dlf */
	temp = 500000000UL / baud_rate;	/* Divisor */
	regs->dll = (temp & 0xff);
	regs->dlh = ((temp >> 8) & 0xff);

	temp = 500000000UL % baud_rate;	/* Fraction */
	regs->dlf = (((temp << DW_APB_UART_DLF_SIZE) + ((baud_rate + 1) / 2)) / baud_rate);

	/* Exit from setting dll/dlh */
	regs->lcr &= ~(LCR_DLAB);

	/* Set UART as 8n1 */
	temp = regs->lcr;
	temp &= ~(LCR_BC | LCR_SP | LCR_EPS_MASK | LCR_PEN_MASK | LCR_STOP_MASK | LCR_DLS_MASK);
	temp |= (LCR_DLS_(LCR_CS8) | LCR_STOP_(LCR_1_STB) | LCR_PEN_(LCR_PDIS));
	regs->lcr = temp;
}

/* TODO: Change these code after refactoring UART driver */
static void test_ca73_printf(char *s)
{
	volatile struct dw_apb_uart_regs *regs =
		(struct dw_apb_uart_regs *)test_ca73_uart_per_core[get_current_cpuid()];

	while (*s) {
		while (1) {
			if ((regs->lsr & (LSR_TEMT | LSR_THRE)) == (LSR_TEMT | LSR_THRE)) {
				regs->thr = (uint32_t)(*s);
				break;
			}
		}
		s++;
	}
}

/* GIC */
static inline void test_ca73_gic(void)
{
	/* TODO: Identify interrupt range that can be tested */
}

/* Tick Interrupt */
static inline void test_ca73_tick_irq(void)
{
	/* TODO */
}

/* SMP */
static inline void test_ca73_smp(void)
{
	TaskHandle_t handle[TEST_CA73_MAX_TASK];

	/* UART test */
	printf("[ca73] Start SMP UART test\n");
	test_ca73_create_tasks(handle, test_ca73_task_config_affinity_x);
	vTaskDelay(TEST_CA73_MAX_PRINTF);

	test_ca73_suspend_tasks(handle);
	test_ca73_delete_tasks(handle);
	printf("[ca73] End of SMP UART test\n");

	/* Affinity test */
	printf("[ca73] Start SMP Affinity test\n");
	test_ca73_create_tasks(handle, test_ca73_task_config_affinity_o);
	test_ca73_set_affinity(handle);
	vTaskDelay(TEST_CA73_MAX_PRINTF);

	test_ca73_suspend_tasks(handle);
	test_ca73_delete_tasks(handle);
	printf("[ca73] End of SMP Affinity test\n");

	/* Sequentially run tasks */
	printf("[ca73] Sequential test\n");
	test_ca73_create_tasks(handle, test_ca73_task_config_affinity_o);
	test_ca73_set_affinity(handle);
	test_ca73_suspend_tasks(handle);
	for (uint32_t i = 0; i < TEST_CA73_MAX_PRINTF; ++i) {
		vTaskResume(handle[i & (TEST_CA73_MAX_TASK - 1)]);
		vTaskDelay(1U);
		vTaskSuspend(handle[i & (TEST_CA73_MAX_TASK - 1)]);
	}

	test_ca73_delete_tasks(handle);
	printf("[ca73] End of sequential test\n");

	/* Access same address */
	printf("[ca73] Accessing same address\n");
	test_ca73_shared_data = 0;
	test_ca73_create_tasks(handle, test_ca73_task_config_access);
	test_ca73_set_affinity(handle);
	vTaskDelay(TEST_CA73_MAX_PRINTF);

	test_ca73_suspend_tasks(handle);
	test_ca73_delete_tasks(handle);
	printf("[ca73] End of accessing same address\n");

	/* Data transferring between cores */
	// printf("[ca73] Start data transferring\n");
	// test_ca73_shared_data = 0;
	// test_ca73_create_queue(test_ca73_queue, TEST_CA73_MAX_TASK * 2);
	// test_ca73_create_tasks(handle, test_ca73_task_config_transfer);
	// test_ca73_set_affinity(handle);
	// xQueueSend(test_ca73_queue[0], &test_ca73_shared_data, -1);
	// vTaskDelay(TEST_CA73_MAX_PRINTF);

	// test_ca73_suspend_tasks(handle);
	// test_ca73_delete_tasks(handle);
	// /* TODO: Need to remove Queue? How to remove Queue? */
	// printf("[ca73] End of data transferring\n");

	/* TODO: Get some feedback from Rebellions */
}

/* MMU */
static inline void test_ca73_mmu(void)
{
	/* Read test using MMU table */
	/* TODO */

	/* Cacheable test */
	printf("[ca73] Start cacheable test\n");

	size_t cache_line_size = arch_dcache_line_size_get();
	uint64_t cacheable = 0x0003F000000ULL;
	uint64_t non_cacheable = 0x00040000000ULL;
	uint64_t test_hex = 0xDEFAC8EDDEADBEEF;

	/* Cacheable region */
	*(uint64_t *)cacheable = test_hex;
	arch_dcache_flush_range((void *)cacheable, cache_line_size);

	cacheable += cache_line_size;
	*(uint64_t *)cacheable = test_hex;
	arch_dcache_invd_range((void *)cacheable, cache_line_size);

	cacheable += cache_line_size;
	*(uint64_t *)cacheable = test_hex;
	arch_dcache_flush_and_invd_range((void *)cacheable, cache_line_size);

	/* Non-cacheable region */
	*(uint64_t *)non_cacheable = test_hex;
	arch_dcache_flush_range((void *)non_cacheable, cache_line_size);

	non_cacheable += cache_line_size;
	*(uint64_t *)non_cacheable = test_hex;
	arch_dcache_invd_range((void *)non_cacheable, cache_line_size);

	non_cacheable += cache_line_size;
	*(uint64_t *)non_cacheable = test_hex;
	arch_dcache_flush_and_invd_range((void *)non_cacheable, cache_line_size);
	printf("[ca73] End of cacheable test\n");
}

/* Context Switching */
static inline void test_ca73_context_switching(void)
{
	TaskHandle_t handle[TEST_CA73_MAX_TASK];

	/* TODO: Vector context switching */

	/* FPU context switching */
	printf("[ca73] Start FPU Context Switching test\n");
	test_ca73_create_tasks(handle, test_ca73_task_config_fpu_context);
	test_ca73_set_affinity(handle);
	vTaskDelay(TEST_CA73_MAX_PRINTF);

	test_ca73_suspend_tasks(handle);
	test_ca73_delete_tasks(handle);
	printf("[ca73] End of FPU Context Switching test\n");

	/* TODO: Get some feedback from Rebellions */
}

/* TODO: Add more tests */

static void (*test_ca73_sequence[])(void) = {
	// test_ca73_gic,
	// test_ca73_tick_irq,
	// test_ca73_smp,
	test_ca73_mmu,
	// test_ca73_context_switching,
};

uint8_t test_ca73_cli(int argc, char *argv[])
{
	uint8_t ret = true;

	printf("\nStart CA73 architecture test\n");

	/* Init UART1/2/3 for ca73 test */
	/* TODO: Change these code after refactoring UART driver */
	test_ca73_uart_init(test_ca73_uart_per_core[0]);
	test_ca73_uart_init(test_ca73_uart_per_core[1]);
	test_ca73_uart_init(test_ca73_uart_per_core[2]);
	test_ca73_uart_init(test_ca73_uart_per_core[3]);

	for (uint32_t i = 0; i < sizeof(test_ca73_sequence) / sizeof(void (*)(void)); ++i) {
		test_ca73_sequence[i]();
	}

	/* TODO: Need to disable UART1/2/3? */

	return ret;
}

static const char help_ca73[] = "[ca73]\n * Test for CA73 architecture code\n\r\n";

CLI_REGISTER(ca73, NULL, test_ca73_cli, help_ca73);
