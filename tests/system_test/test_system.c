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
#include <arm_neon.h>
#include <stdint.h>
#include <cache.h>
#include "limits.h"
#include "test_common.h"
#include "system_test.h"
#include "FreeRTOS.h"
#include "dma_transaction.h"
#include "data_process.h"
#include "task.h"
#include "task_adder.h"
#include "rebel_h_platform.h"
#include "mailbox.h"

#define BLOCK_SIZE			(BIT(10)) /* 1024 * 1024 * 4byte * 4 core = 16MiB*/
#define SYSTEST_STACK_SIZE	(16 << 10)

enum {
	SYSTEST_REQ_TARGET_CHIP1 = 0x1,
	SYSTEST_REQ_TARGET_CHIP2,
	SYSTEST_REQ_TARGET_CHIP3,
	SYSTEST_RESP_TARGET_CHIP1,
	SYSTEST_RESP_TARGET_CHIP2,
	SYSTEST_RESP_TARGET_CHIP3,
	SYSTEST_DATA_COMP_PASS,
	SYSTEST_REQ_TARGET_TEST = 0xffff,
};

struct Data {
	uint32_t n;
	float32_t *A;
	float32_t *B[configNUMBER_OF_CORES];
	float32_t *C[configNUMBER_OF_CORES];
	float32_t *core01_E;
	float32_t *core23_E;
	uint32_t *core01_D;
	uint32_t *core23_D;
};

#define NUM_OF_CHIPLET	(4)

static struct Data primary_info[NUM_OF_CHIPLET];
static struct Data secondary_info;
static TaskHandle_t primary_handle[NUM_OF_CHIPLET];
static TaskHandle_t secondary_handle;

float32x4_t Elimit = {2, 2, 2, 2};
const uint64_t CA73_VIRTUAL_ADDR_BASE = 0x10000000000;

static uint64_t _convert_to_abs_addr(uint64_t addr)
{
	const uint64_t chiplet_offset = CHIPLET_OFFSET * CHIPLET_ID;

	return (addr & (CA73_VIRTUAL_ADDR_BASE - 1)) + chiplet_offset;
}

static uint64_t _convert_to_priv_addr(uint64_t addr)
{
	const uint64_t chiplet_offset = CHIPLET_OFFSET * CHIPLET_ID;

	return (addr | CA73_VIRTUAL_ADDR_BASE) - chiplet_offset;
}

static void *_alloc_heap(size_t size)
{
	void *ptr = pvPortMalloc(size);

	return (void *)_convert_to_abs_addr((uint64_t)ptr);
}

static void _free_heap(void *ptr)
{
	configASSERT(ptr);
	vPortFree((void *)_convert_to_priv_addr((uint64_t)ptr));
}

static void _primary_data_init(struct Data *input)
{
	const float32_t pi = 3.1415927410125732F;

	input->n = BLOCK_SIZE;
	configASSERT(!input->A);
	input->A = (float32_t *)_alloc_heap(input->n * input->n * sizeof(float32_t) * configNUMBER_OF_CORES);

	matrix_init_neon(input->A, input->n * 2, pi);
}

static void _primary_data_free(struct Data *input)
{
	_free_heap(input->A);
	input->A = NULL;
}

static void _secondary_result_init(void)
{
	uint64_t alloc_size = secondary_info.n * secondary_info.n * sizeof(float32_t);

	configASSERT(!secondary_info.core01_E);
	secondary_info.core01_E = (float32_t *)_alloc_heap(alloc_size);

	configASSERT(!secondary_info.core23_E);
	secondary_info.core23_E = (float32_t *)_alloc_heap(alloc_size);

	configASSERT(!secondary_info.core01_D);
	secondary_info.core01_D = (uint32_t *)_alloc_heap(alloc_size);

	configASSERT(!secondary_info.core23_D);
	secondary_info.core23_D = (uint32_t *)_alloc_heap(alloc_size);
}

static void _secondary_data_free(void)
{
	for (int i = 0; i < configNUMBER_OF_CORES; i++) {
		_free_heap(secondary_info.B[i]);
		secondary_info.B[i] = NULL;
		_free_heap(secondary_info.C[i]);
		secondary_info.C[i] = NULL;
	}

	_free_heap(secondary_info.core01_E);
	secondary_info.core01_E = NULL;
	_free_heap(secondary_info.core23_E);
	secondary_info.core23_E = NULL;
	_free_heap(secondary_info.core01_D);
	secondary_info.core01_D = NULL;
	_free_heap(secondary_info.core23_D);
	secondary_info.core23_D = NULL;
}

static void _neon_data_init_and_proc(void *arg)
{
	uint32_t core_id = get_current_cpuid();
	struct Data *input = (struct Data *)arg;
	uint64_t alloc_size = input->n * input->n * sizeof(float32_t);
	float32_t *A = input->A + (input->n * input->n * core_id);

	arch_dcache_invd_range(A, alloc_size);
	configASSERT(!input->B[core_id]);
	input->B[core_id] = (float32_t *)_alloc_heap(alloc_size);
	matrix_copy_neon(A, input->B[core_id], input->n);

	configASSERT(!input->C[core_id]);
	input->C[core_id] = (float32_t *)_alloc_heap(alloc_size);
	matrix_copy_neon(input->B[core_id], input->C[core_id], input->n);

	matrix_multiply_neon(A, input->B[core_id], input->C[core_id], input->n, input->n, input->n);

	xTaskNotify(secondary_handle, 0, eIncrement);
	vTaskDelete(NULL);
}

static void _neon_comp_proc(struct Data *input)
{
	absolute_diff(input->C[0], input->C[1], input->core01_E, input->n, input->n);
	comp_less_than(input->core01_E, input->core01_D, Elimit, input->n, input->n);
	absolute_diff(input->C[2], input->C[3], input->core23_E, input->n, input->n);
	comp_less_than(input->core23_E, input->core23_D, Elimit, input->n, input->n);
}

static void _check_neon_result(struct Data *input)
{
	for (int idx = 0; idx < input->n; idx++) {
		uint32_t result = (input->core01_D[idx] & input->core23_D[idx]);
		const uint32_t ALL_PASS_VALUE = 0xffffffff;

		if (result != ALL_PASS_VALUE) {
			printf("CMP Fail!(result 0x%x\n", result);
			printf("core01_D[%d] 0x%x, core23_D[%d] 0x%x\n",
				   idx, input->core01_D[idx], idx, input->core23_D[idx]);
			while (1) {
			}
		}
	}
	printf("CMP Pass\n");
}

static int _send_mailbox_to_chiplet(uint32_t target_id, uint32_t data)
{
	int inst = IDX_MAILBOX_PERI0_M7_CPU0;
	int chan = SYSTEM_TEST_CHANNEL;
	int cpu = 0;

	ipm_samsung_write(inst, target_id, &data, sizeof(data), DEFAULT_M_INDEX);
	ipm_samsung_send(inst, target_id, chan, cpu);

	return 0;
}

static uint32_t * const SYSTEST_BUFFER_ARR[] = {
	(uint32_t *)CHIPLET0_SYSTEST_BUF,
	(uint32_t *)CHIPLET1_SYSTEST_BUF,
	(uint32_t *)CHIPLET2_SYSTEST_BUF,
	(uint32_t *)CHIPLET3_SYSTEST_BUF
};

static void _primary_req_proc(void *arg)
{
	uint64_t data_from_host = (uint64_t)arg;
	uint32_t target_chiplet_id = 0;
	uint32_t *dst_buffer = NULL;

	switch (data_from_host) {
	case SYSTEST_REQ_TARGET_CHIP1:
	case SYSTEST_REQ_TARGET_CHIP2:
	case SYSTEST_REQ_TARGET_CHIP3:
		target_chiplet_id = data_from_host;
		dst_buffer = SYSTEST_BUFFER_ARR[data_from_host];

		if (primary_handle[target_chiplet_id]) {
			printf("[Systest Fail] chiplet%d is on systest\n", target_chiplet_id);
			target_chiplet_id = 0;
		} else {
			primary_handle[target_chiplet_id] = xTaskGetCurrentTaskHandle();
		}
		break;
	case SYSTEST_REQ_TARGET_TEST:
		printf("systest xtor test req\n");
		_send_mailbox_to_chiplet(0, SYSTEST_REQ_TARGET_TEST); // Test 용
		break;
	default:
		break;
	}

	if (target_chiplet_id != 0 && dst_buffer) {
		_primary_data_init(&primary_info[target_chiplet_id]);
		transfer_data(target_chiplet_id, (uint32_t *)&primary_info[target_chiplet_id],
					  dst_buffer, sizeof(primary_info[target_chiplet_id]));
		printf("Send MailBox to Chiplet%d-CP0(data %ld)\n", target_chiplet_id, data_from_host);
		_send_mailbox_to_chiplet(target_chiplet_id, data_from_host);
	}

	vTaskDelete(NULL);
}

static void _primary_resp_proc(void *arg)
{
	uint64_t data_from_secondary = (uint64_t)arg;
	const uint32_t *buffer = NULL;
	uint32_t target_chiplet_id = 0;

	switch (data_from_secondary) {
	case SYSTEST_RESP_TARGET_CHIP1:
	case SYSTEST_RESP_TARGET_CHIP2:
	case SYSTEST_RESP_TARGET_CHIP3:
		target_chiplet_id = data_from_secondary - SYSTEST_REQ_TARGET_CHIP3;
		buffer = SYSTEST_BUFFER_ARR[target_chiplet_id];
		break;
	case SYSTEST_REQ_TARGET_TEST:
		printf("systest xtor test resp\n");
	default:
		break;
	}

	if (target_chiplet_id != 0) {
		printf("resp from chiplet%d\n", target_chiplet_id);
		_check_neon_result((struct Data *)buffer);
		_send_mailbox_to_chiplet(target_chiplet_id, SYSTEST_DATA_COMP_PASS);
		_primary_data_free(&primary_info[target_chiplet_id]);

		primary_handle[target_chiplet_id] = NULL;
	}

	vTaskDelete(NULL);
}

static void _secondary_proc(void *arg)
{
	uint64_t data_from_primary = (uint64_t)arg;
	uint32_t chiplet_id = CHIPLET_ID;
	uint32_t resp_data = 0;
	uint32_t *src_buffer = NULL;
	const uint32_t PRIMARY_ID = 0;

	switch (data_from_primary) {
	case SYSTEST_REQ_TARGET_CHIP1:
	case SYSTEST_REQ_TARGET_CHIP2:
	case SYSTEST_REQ_TARGET_CHIP3:
		src_buffer = SYSTEST_BUFFER_ARR[chiplet_id];
		resp_data = SYSTEST_REQ_TARGET_CHIP3 + chiplet_id;
		break;
	case SYSTEST_DATA_COMP_PASS:
		_secondary_data_free();
		break;
	default:
	}

	if (src_buffer) {
		struct Data *input = (struct Data *)src_buffer;

		secondary_info.A = input->A;
		secondary_info.n = input->n;

		static struct task_info t_info = {
			.func = _neon_data_init_and_proc,
			.task_name = "neon_data_proc",
			.stack_depth = SYSTEST_STACK_SIZE,
			.param = (void *)&secondary_info,
			.priority = 1,
			.affinity = 0,
			.handle = NULL,
		};
		uint32_t noti_val = 0;

		for (uint32_t core_num = 0; core_num < configNUMBER_OF_CORES; core_num++) {
			t_info.affinity = BIT(core_num);
			task_adder_enqueue(&t_info);
		}
		_secondary_result_init();
		do {
			xTaskNotifyWait(0x0, 0x0, &noti_val, portMAX_DELAY);
		} while (noti_val < configNUMBER_OF_CORES);

		_neon_comp_proc(&secondary_info);

		transfer_data(PRIMARY_ID, (uint32_t *)&secondary_info, (uint32_t *)src_buffer, sizeof(secondary_info));
		printf("Send MailBox to Chiplet%d-CP0(data %d)\n", PRIMARY_ID, resp_data);
		_send_mailbox_to_chiplet(PRIMARY_ID, resp_data);
		secondary_handle = NULL;
	}

	vTaskDelete(NULL);
}

static void _pcie_mailbox_handler(uint32_t chiplet_id)
{
	if (chiplet_id != 0)
		return;

	uint64_t data_from_host = 0;
	const uint32_t ZERO = 0;
	static struct task_info t_info = {
		.func = _primary_req_proc,
		.task_name = "primary_req_proc",
		.stack_depth = SYSTEST_STACK_SIZE,
		.param = NULL,
		.priority = 1,
		.affinity = 0x1,
		.handle = NULL,
	};

	// Host to Chiplet0 CP0 Mailbox callback
	ipm_samsung_receive(IDX_MAILBOX_PCIE_PF, &data_from_host, sizeof(data_from_host), DEFAULT_M_INDEX);
	ipm_samsung_write(IDX_MAILBOX_PCIE_PF, chiplet_id, &ZERO, sizeof(ZERO), DEFAULT_M_INDEX); // Clear data
	t_info.param = (void *)data_from_host;

	printf("PCIE PF data : 0x%lx\n", data_from_host);

	task_adder_enqueue(&t_info);
}

static void _ipc_mailbox_handler(uint32_t chiplet_id)
{
	uint64_t data_from_chiplet = 0;
	const uint32_t ZERO = 0;
	static struct task_info t_info = {
		.func = NULL,
		.task_name = NULL,
		.stack_depth = SYSTEST_STACK_SIZE,
		.param = NULL,
		.priority = 1,
		.affinity = 0x1,
		.handle = NULL,
	};

	// Chiplet# CP0 to Chiplet# CP0 Mailbox callback
	ipm_samsung_receive(IDX_MAILBOX_PERI0_M7_CPU0, &data_from_chiplet, sizeof(data_from_chiplet), DEFAULT_M_INDEX);
	ipm_samsung_write(IDX_MAILBOX_PERI0_M7_CPU0, chiplet_id, &ZERO, sizeof(ZERO), DEFAULT_M_INDEX);
	t_info.param = (void *)data_from_chiplet;

	printf("PERI0_M7_CPU0 data : 0x%lx\n", data_from_chiplet);

	if (chiplet_id == 0) {
		t_info.func = _primary_resp_proc;
		t_info.task_name = "_primary_resp_proc";
		t_info.handle = &primary_handle[chiplet_id];
	} else {
		t_info.func = _secondary_proc;
		t_info.task_name = "secondary_proc";
		t_info.handle = &secondary_handle;
	}

	task_adder_enqueue(&t_info);
}

void system_test_cb(void)
{
	uint32_t chiplet_id = CHIPLET_ID;

	printf("chiplet:%d received request\n", chiplet_id);

	_pcie_mailbox_handler(chiplet_id);
	_ipc_mailbox_handler(chiplet_id);
}
