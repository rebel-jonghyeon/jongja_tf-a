/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2025 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "g_sysfw_addrmap.h"
#include "sys_command_line.h"
#include "hal/rbdma_if.h"
#include "hal/dnc_if.h"
#include "hal/shm_if.h"
#include "hal/cmgr_if.h"
#include "hal/interrupt.h"
#include "hal/rdsn_if.h"
#include "hal/ptw.h"
#include "hal/tbu_wrapper.h"
#include "rbln/log.h"
#include "rl_utils.h"
#include "rl_sizes.h"
#include "common/command.h"
#include "common/page_table_gen.h"
#include "replay.h"
#include "rbln/rebel.h"
#include "../../../../drivers/smmu/smmu.h"
#include "../../../../drivers/smmu/smmu_pmu.h"
#include "chiplet.h"
#include "ici.h"
#include "task_adder.h"
#include "queue.h"
#include "common/rl_queue.h"

#include "common_test.h"
#include "vhs_if.h"
#include "timers.h"

#include "rl_errors.h"
#include "rbln/abort.h"
#include "rbln/log.h"
#include "rbln/core.h"
#include "chiplet.h"
#include "mailbox.h"
#include "core_timer.h"
#include "system_api.h"
#include "hal/hw_spec.h"
#include "gpio.h"
#include "hbm3.h"
#include "icon.h"
#include "terminal_task.h"

#include "rush_cli.h"

#define LOG_SHELL terminal_printf

extern uint8_t rbdma_perf_test(int argc, char *argv[]);

#define MAX_ARGS 10 // maximum length of argv for tc_param in replay_routine
#define MAX_ARG_LEN 10 // maximum length of element of argv for tc_param in replay_routine

/* This definition needs to be converted into a configuration */
//#define ENABLE_WAIT_ERUN
//#define SHM_SP_DUMP_PER_STREAM
//#define PROFILE_ENABLE

#ifdef PROFILE_ENABLE
#include "common/profile.h"
#include "common/af_profile.h"
#endif

//#define POWER_MODE_TEST
//#define SELF_TASK_FETCH_MODE

/*
 * XGPIOC_15 GROUP5, bit 1
 * GPIO_NBUS_L 0x1F_F353_0000 + 0xA0
 * 0x1F_F353_0000 + A4
 */
#if defined(POWER_MODE_TEST)
#define GPIO_TEST_CON  ((volatile uint32_t *)0x1FF35300A0)
#define GPIO_TEST_DAT  ((volatile uint32_t *)0x1FF35300A4)
#endif

uint32_t cur_cl_id;
const uint64_t cl_base[MAX_CHIPLET_COUNT] = {
	REBEL_H_CHIPLET0_PHYSICAL_START,
	REBEL_H_CHIPLET1_PHYSICAL_START,
	REBEL_H_CHIPLET2_PHYSICAL_START,
	REBEL_H_CHIPLET3_PHYSICAL_START,
};

static TaskHandle_t task_handle;
static QueueHandle_t ici_task_queue;
static QueueHandle_t xDataQueue_ucie_control_stress;
static TaskHandle_t main_task_handle;


uint32_t golden_addr;
uint32_t golden_size;
uint32_t passed_count;
uint32_t failed_count;
uint32_t stc_pass_cnt;
uint32_t stc_fail_cnt;

/* Exception flag — file-scope, accessed only via accessor functions below.
 * Wider-than-bool type ensures word-aligned atomic access on all targets.
 */
static uint32_t is_exception_occurred;

void test_exception_mark(void)
{
	__atomic_store_n(&is_exception_occurred, 1u, __ATOMIC_RELEASE);
}

void test_exception_clear(void)
{
	__atomic_store_n(&is_exception_occurred, 0u, __ATOMIC_RELEASE);
}

bool test_exception_occurred(void)
{
	return __atomic_load_n(&is_exception_occurred, __ATOMIC_ACQUIRE) != 0u;
}

workload_list model_list[] = {
	/* model_id, model_name, result_count, compare_mode, result_addr[], golden_addr[], out_size[] */
	{0, "No list", 1, COMPARE_MODE_PER_CHIPLET, {0x0}, {0x0}, {0x0}},
	{1, "bert_large", 1, COMPARE_MODE_PER_CHIPLET, {0x65000000}, {0x80000000}, {98304}},
	{2, "retinanet", 1, COMPARE_MODE_PER_CHIPLET, {0x48cc8000}, {0x80000000}, {212992}},
	{3, "resnet50_ss", 1, COMPARE_MODE_PER_CHIPLET, {0x43e00000}, {0x80000000}, {4096}},
	{4, "resnet50_ms", 1, COMPARE_MODE_PER_CHIPLET, {0x44000000}, {0x80000000}, {32768}},
	{5, "llama3.3_70b", 2, COMPARE_MODE_CHIPLET0_ONLY,
		{0x46ac00000, 0x57a600000},
		{0x740000000, 0x74003ea00},
		{256512, 256512}},
};

#define NUM_STC 1295

char stc_list[NUM_STC][64];
int current_stc_idx;

/* chiplet count which is configured at build option */
static const uint32_t chiplet_count_opt = CHIPLET_COUNT;

/******************************
 * [Sanity Test Item]
 * shm_exception_test
 * mglue_interrupt_test
 * rbdma_error_interrupt_test
 * dnc_report_dump_test
 ******************************/

#define SZ_6M	(SZ_2M + SZ_4M)

test_func_list item_list[] = {
	{0,     NULL,   "No list"},
	{1,     rdsn_config_test, "rdsn_config_test"},
	{2,     tsync_test, "tsync_test"},
	{3,     shm_tpg_test, "shm_tpg_test"},
	{4,     rbdma_dram_2_shm, "rbdma_dram_2_shm & rbdma_shm_2_dram"},

	{5,     rbdma_common_test_func, "rbdma_2KB_dram_2_dram", {DRAM, DRAM, SZ_2K}},
	{6,     rbdma_common_test_func, "rbdma_2MB_dram_2_dram", {DRAM, DRAM, SZ_2M}},
	{7,     rbdma_common_test_func, "rbdma_6MB_dram_2_dram", {DRAM, DRAM, SZ_6M}},
	{8,     rbdma_common_test_func, "rbdma_2KB_dram_2_shm", {DRAM, SHM, SZ_2K}},
	{9,     rbdma_common_test_func, "rbdma_2MB_dram_2_shm", {DRAM, SHM, SZ_2M}},
	{10,    rbdma_common_test_func, "rbdma_6MB_dram_2_shm", {DRAM, SHM, SZ_6M}},

	{11,    ldudma_dram_2_sp, "ldudma_dram_2_sp"},
	{12,    ldudma_4MB_near_sp, "ldudma_4MB_near_sp"},
	{13,    ldudma_4MB_far_sp,  "ldudma_4MB_far_sp"},
	{14,    ldudma_4MB_near_shm, "rbdma_dram_2_shm & ldudma_4MB_near_shm"},
	{15,    ldudma_4MB_far_shm, "rbdma_dram_2_shm & ldudma_4MB_far_shm"},

	{16,    lpudma_dram_2_sp, "lpudma_dram_2_sp"},
	{17,    lpudma_4MB_near_sp, "lpudma_4MB_near_sp"},
	{18,    lpudma_4MB_far_sp,  "lpudma_4MB_far_sp"},
	{19,    lpudma_4MB_near_shm, "rbdma_dram_2_shm & lpudma_4MB_near_shm"},
	{20,    lpudma_4MB_far_shm, "rbdma_dram_2_shm & lpudma_4MB_far_shm"},

	{21,    studma_sp_2_dram, "studma_sp_2_dram"},
	{22,    studma_4MB_near_sp, "studma_4MB_near_sp"},
	{23,    studma_4MB_far_sp, "studma_4MB_far_sp"},
	{24,    studma_4MB_near_shm, "studma_4MB_near_shm"},
	{25,    studma_4MB_far_shm, "studma_4MB_far_shm"},

	{26,    rbdma_dram_2_dram_all_port, "rbdma_dram_2_dram_all_port"},
	{27,    rbdma_burst_length, "rbdma_burst_length"},
	{28,    rbdma_large_memory_copy, "rbdma_large_memory_copy"},
	{29,    rbdma_data_shift, "rbdma_data_shift"},
	{30,    rbdma_sct_gth,   "rbdma_sct_gth"},
	{31,    rbdma_sct_gth_w_regular,  "rbdma_sct_gth_w_regular"},
	{32,    rbdma_report_dump,  "rbdma_report_dump"},
	{33,    cmgr_dnc_interop_test, "cmgr_dnc_interop_test"},
	{34,    cmgr_rbdma_interop_test, "cmgr_rbdma_interop_test"},
	{35,    rbdma_shm_2_shm, "shm_2_shm"},

	{36,    rbdma_dram_2_shm_tsync, "dram_2_shm_tsync"},
	{37,    rbdma_shm_2_dram_tsync, "shm_2_dram_tsync"},
	{38,    sp_tpg_test, "sp_tpg_test"},
	/* FIXME: temporary block ucie test for EVT1 */
	{39,    ucie_sanity_test, "ucie_sanity_test"},
	{40,    ucie_test, "ucie_test", {0, 0, 0, 0}},
	{41,	dcl_stress_test, "dcl_stress_test"},
	{42,	dram_harsh_stress_test, "dram_harsh_stress_test"},
	{43,	dram_all_array_test, "dram_all_array_test"},
};

void mailbox_event_notify(int inst, int channel)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if (task_handle != NULL) {
		vTaskNotifyGiveFromISR(task_handle, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

void process_mailbox_event(void)
{
	printf("%s\r\n", __func__);
	replay_routine();
}

void ici_callback_task(void *pvParameters)
{
	struct ici_callback_data received_data;

	while (1) {
		if (xQueueReceive(ici_task_queue, &received_data, portMAX_DELAY) == pdPASS) {
			if (received_data.func_type == ICI_BASIC_TEST_START)
				ici_trigger_ucie_basic_test(received_data.arg, received_data.size);
			else if (received_data.func_type == ICI_STC_TEST_START)
				ici_trigger_stc_test(received_data);
			else if (received_data.func_type == ICI_UCIE_STC_STRESS_START)
				ici_trigger_ucie_stc_stress_test(received_data.size);
			else if (received_data.func_type == ICI_POWER_MODE_UCIE_TEST_START)
				power_mode_ucie_test(4, (char *[]){"0", NULL});
			else if (received_data.func_type == ICI_HBM_PERF_TEST_START)
				ici_trigger_hbm_perf_test(received_data.arg);
			else if (received_data.func_type == ICI_AF_STC_TEST_START)
				ici_trigger_af_common_test(received_data);
			else if (received_data.func_type == ICI_QUAD_REPLAY_TEST_START)
				ici_trigger_ucie_quad_replay_test(received_data.arg, received_data.size);
			else if (received_data.func_type == ICI_DRAM_HARSH_STRESS_START)
				ici_trigger_dram_harsh_stress(received_data.size);
			else
				printf("%s: unknwon test type, do nothing", __func__);
		}
	}
}

void ici_callback_trigger(struct ici_callback_data callback_data)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	xQueueSendFromISR(ici_task_queue, &callback_data, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

#if defined(POWER_MODE_TEST)
static void pwr_gpio_set(void)
{
	*GPIO_TEST_DAT = 0xFF;
}

static void pwr_gpio_unset(void)
{
	*GPIO_TEST_DAT = 0x0;
}
#endif

void replay_task_init(TaskHandle_t handle)
{
	int i;
	task_handle = handle;

	printf("Build time: %s\n", __TIMESTAMP__);
	printf("Version: %s\n", GIT_VERSION);
	printf("%s\r\n", __func__);

	RLOG_DBG("chiplet count is %d\r\n", CHIPLET_COUNT);
	printf("chiplet count is %d\r\n", CHIPLET_COUNT);

	for (i = 0; i < chiplet_count_opt; i++)
		printf("chiplet[%d] base: %lx\r\n", i, cl_base[i]);

	cur_cl_id = get_chiplet_id();
	RLOG_INFO("chiplet id %u\r\n", cur_cl_id);
	printf("chiplet id %u\r\n", cur_cl_id);

	mailbox_register_callback(mailbox_event_notify);

	if (chiplet_count_opt > 1) {
		ici_task_queue = xQueueCreate(5, sizeof(struct ici_callback_data));
		static struct task_info ici_t_info = {
			.func = ici_callback_task,
			.task_name = "ici_callback_task",
			.stack_depth = configMINIMAL_STACK_SIZE,
			.param = NULL,
			.priority = 1,
			.affinity = 0x1,
			.handle = NULL
		};

		task_adder_enqueue(&ici_t_info);
		ici_init(cur_cl_id);
	}

	logbuf_init(cur_cl_id);

	hw_init();
	sw_init();

#if defined(INDICATOR_DEBUG_MODE)
	TEST_GPD2_CON |= 0x00000001;	// output mode GPD2[0]
//	GPIO_GPD_SET(2, 0, CON, GPIO_CON_OUTPUT);
#endif /* #if defined(INDICATOR_DEBUG_MODE) */

// This was applied just vdk_1.0(sort_mode)
//#ifdef SORT_MODE
//	printf("This is sorting mode\r\n");
	// for sorting func
//	udelay(10);
//	chip_sorting_routine();
//#endif

#if (0) /* 2026-03-09, this is for power vector only */
	/*
	 * applied default dnc skew value like 90 cycle, this is 6 x 16 = 96 cycle
	 */
	int ret = dnc_skew_set(1, (char*[]){"6"});

	if (!ret)
		printf("DNC skew application failed.");
#endif
}

void replay_task(void *pvParameters)
{
	for (;;) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		process_mailbox_event();
	}
}

void log_test_result(const char *module, const char *test_name, const char *status)
{
	printf("%-10s, %-20s, (%-10s)\r\n", module, test_name, status);
}

/*
 * Using its own chiplet ID, it runs a short test routine (rdsn_sanity_check())
 * on the local chiplet’s RDSN test engine. This sanity test covers RDSN router traffic
 * and is heavier than expected. After that, it configures the ID information of
 * the DNCs in each DCluster through rdsn_set_ids().
 * The same test is then repeated for the next chiplet ID, and finally, it completes
 * the test with its own chiplet ID for the final configuration.
 * In the quad-chiplet base, barriers between chiplets are required to maintain the above test.
 * Also, since each chiplet in rebel_q will operate based on its own chiplet base, this function
 * needs to be modified so that it only operattes on its own chiplet base.
 */
int rdsn_config_test(void *ctx)
{
	uint32_t cl_id = cur_cl_id;

	RLOG_INFO("%s\r\n", __func__);

#if SINGLE_CHIPLET_TEST
	// Run RDSN config with all possible cl_ids.
	for (int i = 0; i < MAX_CHIPLET_COUNT; i++) {
		// Rotate back to current chiplet id.
		cl_id = ((cl_id + 1) % MAX_CHIPLET_COUNT);
		RLOG_INFO("%s (cl_id: %d)\r\n", __func__, cl_id);
		if (rdsn_init(cl_id) < 0)
			return false;
	}
#endif

	if (rdsn_init(cl_id) < 0)
		return false;

	return 1;
}

/*
 * This test is a vector that checks the function of tsync using the pwr feature
 * in task16 mode through the Cbus posted write signal. Each DNC (dnc0/1/2/3, …) in DCL0
 * sends posted write packets to each DNC (dnc8/9/10, …) in DCL1, and each DNC verifies
 * the packets it has received.
 */
int tsync_test(void *ctx)
{
	RLOG_INFO("%s\r\n", __func__);

	if (posted_write_test(cur_cl_id) < 0)
		return false;

	return 1;
}

/*
 * The shared memory test and the interrupt operation of SGlue are verified through
 * the SHM test pattern generator engine. Using tpg_all mode, the TPG done status of
 * each slice is checked. The shm_exception_register() function intentionally injects
 * errors to trigger SHM exceptions and verify the operation of exception interrupts.
 * Since SHM exception cases are already covered in sort_mode, they were not included
 * in the basic vector.
 */
int shm_tpg_test(void *ctx)
{
	RLOG_INFO("%s\r\n", __func__);

	if (shm_init(cur_cl_id) < 0)
		return false;

	return 1;
}

static int dnc_fill_sp_all(const uint32_t val)
{
	int ret;
	uint32_t i;

	for (i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		ret = dnc_run_sp_test(i, val);
		if (ret < 0) {
			RLOG_ERR("Failed to clear SP of DNC%d, ret= %d\n", i, ret);
			return ret;
		}
	}

	return 0;
}

static inline int dnc_clear_sp_all(void)
{
	return dnc_fill_sp_all(0x00);
}

static int dnc_test_result_cmp_all(uint64_t src, uint64_t dst, uint32_t size)
{
	int ret;
	uint32_t i;

	for (i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		ret = basic_test_compare(src, dst + i * size, size);
		if (ret)
			return ret;
	}

	return 0;
}

/*
 * The TPG engine for scratch pad memory providers various test engines such as interleaving
 * mode, bank stress mode, and half bank stress mode. This function is a test to apply bank
 * stress to the scratch pad, and after the bank stress is performed, it clears the data to
 * 0x0 in the default mode.
 */
int sp_tpg_test(void *ctx)
{
	int ret = -1;

	RLOG_INFO("%s\r\n", __func__);

	ret = dnc_sp_mode_test(0x1, 0x2);	// bank-stress
	if (ret < 0)
		return false;

	ret = dnc_clear_sp_all();
	if (ret < 0)
		return false;

	return 1;
}

#define TPG_TIMEOUT_VALUE	1000000

static void do_stress_test(int cl_id, struct ici_chip_sorting_entry entry, int *task_id);

int dcl_stress_test(void *ctx)
{
	RLOG_INFO("%s\r\n", __func__);

	if (shm_test_mode_trigger() < 0)
		return false;

	if (dnc_sp_test_mode_trigger() < 0)
		return false;

	if (rdsn_test_mode_trigger() < 0)
		return false;

	if (rdsn_test_mode_check() < 0) {
		rl_abort_event(ERR_RDSN);
		return false;
	}

	if (dnc_sp_test_mode_check() < 0) {
		rl_abort_event(ERR_DNC);
		return false;
	}

	if (wait_for_shm_tpg_done(TPG_TIMEOUT_VALUE) < 0) {
		rl_abort_event(ERR_SHM);
		return false;
	}

	return 1;
}

#define DRAM_HARSH_STRESS_SRC_ADDR(x)     (cl_base[(x)] + 0x600000000)
#define DRAM_HARSH_STRESS_DST_ADDR(x)     (cl_base[(x)] + 0x700000000)
#define DRAM_HARSH_STRESS_SNAP_ADDR(x)    (cl_base[(x)] + 0x708000000)
#define DRAM_HARSH_STRESS_NOISE_A_ADDR(x) (cl_base[(x)] + 0x800000000)
#define DRAM_HARSH_STRESS_NOISE_B_ADDR(x) (cl_base[(x)] + 0x880000000)
#define DRAM_HARSH_STRESS_SIZE            SZ_128M
#define DRAM_HARSH_STRESS_NOISE_SIZE      SZ_128M
#define DRAM_HARSH_STRESS_BATCH           128
#define DRAM_HARSH_STRESS_SNAP_SIZE       SZ_2M
#define DRAM_HARSH_STRESS_SNAP_CHUNKS     (DRAM_HARSH_STRESS_SIZE / DRAM_HARSH_STRESS_SNAP_SIZE)
#define DRAM_HARSH_STRESS_SNAP_COUNT      127
#define DRAM_HARSH_STRESS_SNAP_INTERVAL   1   /* snapshot every N batches (0=disable) */
#define DRAM_HARSH_STRESS_FULL_DW_DUMP    1   /* 1=dump all 256bit on mismatch, 0=diff only */

/*
 * EVT1 addr bit swap (addr[28]<->addr[15], addr[29]<->addr[16]) is not applied
 * to RBDMA path. Limit CPU compare to the first 32KB of each region where
 * bit[15] and bit[16] are never set, avoiding false mismatches.
 * DMA sizes stay at 128MB for full PI/SI noise generation.
 */
#define DRAM_HARSH_STRESS_COMPARE_SIZE    SZ_32K

/*
 * Replicate the first COMPARE_SIZE bytes of src across the full SIZE region
 * using RBDMA doubling so that the entire 128MB buffer contains random data
 * for meaningful PI/SI noise on the bus.
 */
static void dram_harsh_stress_fill_src(int cl_id, uint64_t src_addr)
{
	uint64_t filled = DRAM_HARSH_STRESS_COMPARE_SIZE;
	int fill_tid = 0xDD450000;

	while (filled < DRAM_HARSH_STRESS_SIZE) {
		uint64_t chunk = filled;

		if (filled + chunk > DRAM_HARSH_STRESS_SIZE)
			chunk = DRAM_HARSH_STRESS_SIZE - filled;
		generate_rbdma_perf_task(fill_tid++,
			src_addr, src_addr + filled,
			chunk, 0xFF, 15, 0);
		rbdma_done_acc_count(cl_id, 1);
		rbdma_done_clear(cl_id);
		filled += chunk;
	}
}

static int dram_harsh_stress_compare(uint64_t src_addr, uint64_t dst_addr,
				     uint64_t size)
{
	volatile uint32_t *p_src = (volatile uint32_t *)src_addr;
	volatile uint32_t *p_dst = (volatile uint32_t *)dst_addr;
	uint32_t mismatch_count = 0;
	uint32_t skip_1bit = 0;
	uint64_t dw_count = size / 32; /* 256bit (32byte) dataword units */
	int dw_bit_errs;
	int word_bits;

	cpu_inv_dcache_range((uintptr_t)src_addr, size);
	cpu_inv_dcache_range((uintptr_t)dst_addr, size);
	dsb();

	for (uint64_t dw = 0; dw < dw_count; dw++) {
		uint64_t base = dw * 8; /* 8 x uint32_t = 32 bytes */

		dw_bit_errs = 0;

		for (int w = 0; w < 8; w++) {
			uint32_t xor_val = p_src[base + w] ^ p_dst[base + w];

			if (xor_val)
				dw_bit_errs += __builtin_popcount(xor_val);
		}

		if (dw_bit_errs == 0)
			continue;

		if (dw_bit_errs < 2) {
			skip_1bit++;
			continue;
		}

		mismatch_count++;
		if (mismatch_count <= 16) {
			uint64_t dw_addr = dst_addr + dw * 32;

			printf("[MISMATCH #%u] dataword=0x%lx (%dbit err in 256bit)\r\n",
			       mismatch_count, dw_addr, dw_bit_errs);
#if DRAM_HARSH_STRESS_FULL_DW_DUMP
			printf("  expected:");
			for (int w = 0; w < 8; w++)
				printf(" %08x", p_src[base + w]);
			printf("\r\n  actual  :");
			for (int w = 0; w < 8; w++)
				printf(" %08x", p_dst[base + w]);
			printf("\r\n  xor     :");
			for (int w = 0; w < 8; w++)
				printf(" %08x", p_src[base + w] ^ p_dst[base + w]);
			printf("\r\n");
#endif
			for (int w = 0; w < 8; w++) {
				uint32_t exp = p_src[base + w];
				uint32_t act = p_dst[base + w];

				if (exp != act) {
					word_bits = __builtin_popcount(exp ^ act);
					printf("  +0x%02x: expected=0x%08x actual=0x%08x xor=0x%08x (%dbit)\r\n",
					       w * 4, exp, act,
					       exp ^ act, word_bits);
				}
			}
		}
	}

	if (mismatch_count > 0)
		printf("DRAM Harsh Stress: %u dataword mismatches (%u 1bit-only skipped) in %llu bytes\r\n",
		       mismatch_count, skip_1bit, (unsigned long long)size);

	return mismatch_count;
}

static int dram_harsh_stress_run(int cl_id, int *task_id, int batch_count,
				 int *snap_idx)
{
	uint64_t src_addr = DRAM_HARSH_STRESS_SRC_ADDR(cl_id);
	uint64_t dst_addr = DRAM_HARSH_STRESS_DST_ADDR(cl_id);
	uint64_t snap_base = DRAM_HARSH_STRESS_SNAP_ADDR(cl_id);
	uint64_t noise_a = DRAM_HARSH_STRESS_NOISE_A_ADDR(cl_id);
	uint64_t noise_b = DRAM_HARSH_STRESS_NOISE_B_ADDR(cl_id);
	int queue_left;
	int submitted;
	int phase = 0;

	for (int batch = 0; batch < batch_count; batch++) {
		rbdma_done_clear(cl_id);
		submitted = 0;

		if (DRAM_HARSH_STRESS_SNAP_INTERVAL > 0 &&
		    batch > 0 &&
		    (batch % DRAM_HARSH_STRESS_SNAP_INTERVAL) == 0 &&
		    *snap_idx < DRAM_HARSH_STRESS_SNAP_COUNT) {
			uint64_t snap_off = (uint64_t)(*snap_idx %
				DRAM_HARSH_STRESS_SNAP_CHUNKS) *
				DRAM_HARSH_STRESS_SNAP_SIZE;
			uint64_t snap_addr = snap_base +
				(uint64_t)(*snap_idx) *
				DRAM_HARSH_STRESS_SNAP_SIZE;
			generate_rbdma_perf_task(*task_id,
				dst_addr + snap_off, snap_addr,
				DRAM_HARSH_STRESS_SNAP_SIZE,
				0xFF, 15, 0);
			dsb();
			(*task_id)++;
			if (*task_id >= 0xDD43FFFF)
				*task_id = 0xDD430000;
			submitted++;
			(*snap_idx)++;
		}

		queue_left = rbdma_global_normal_queue_status_cl(cl_id);
		dsb();
		while (queue_left > 1) {
			switch (phase & 7) {
			case 0: /* SRC -> DST */
				generate_rbdma_perf_task(*task_id,
					src_addr, dst_addr,
					DRAM_HARSH_STRESS_SIZE,
					0xFF, 15, 0);
				break;
			case 1: /* NOISE_A -> NOISE_B */
				generate_rbdma_perf_task(*task_id,
					noise_a, noise_b,
					DRAM_HARSH_STRESS_NOISE_SIZE,
					0xFF, 15, 0);
				break;
			case 2: /* SRC -> NOISE_A */
				generate_rbdma_perf_task(*task_id,
					src_addr, noise_a,
					DRAM_HARSH_STRESS_NOISE_SIZE,
					0xFF, 15, 0);
				break;
			case 3: /* NOISE_B -> NOISE_A */
				generate_rbdma_perf_task(*task_id,
					noise_b, noise_a,
					DRAM_HARSH_STRESS_NOISE_SIZE,
					0xFF, 15, 0);
				break;
			case 4: /* SRC -> DST (again) */
				generate_rbdma_perf_task(*task_id,
					src_addr, dst_addr,
					DRAM_HARSH_STRESS_SIZE,
					0xFF, 15, 0);
				break;
			case 5: /* DST -> NOISE_B */
				generate_rbdma_perf_task(*task_id,
					dst_addr, noise_b,
					DRAM_HARSH_STRESS_NOISE_SIZE,
					0xFF, 15, 0);
				break;
			case 6: /* NOISE_A -> NOISE_B */
				generate_rbdma_perf_task(*task_id,
					noise_a, noise_b,
					DRAM_HARSH_STRESS_NOISE_SIZE,
					0xFF, 15, 0);
				break;
			case 7: /* DST -> NOISE_A */
				generate_rbdma_perf_task(*task_id,
					dst_addr, noise_a,
					DRAM_HARSH_STRESS_NOISE_SIZE,
					0xFF, 15, 0);
				break;
			}
			dsb();
			phase++;
			(*task_id)++;
			if (*task_id >= 0xDD43FFFF)
				*task_id = 0xDD430000;
			submitted++;
			queue_left--;
		}

		shm_read_cdp_register((cl_id + 2) % 4);

		rbdma_done_acc_count(cl_id, submitted);
		rbdma_done_clear(cl_id);
	}

	return (phase - 1) & 7;
}

static int dram_harsh_stress_test_core(int iter_count)
{
	int cl_id = get_chiplet_id();
	int total_mismatch = 0;
	int noise_mismatch = 0;
	int snap_mismatch;
	int task_id = 0xDD430000;
	int snap_idx = 0;
	int last_phase_mod;
	uint64_t src_addr = DRAM_HARSH_STRESS_SRC_ADDR(cl_id);
	uint64_t noise_a = DRAM_HARSH_STRESS_NOISE_A_ADDR(cl_id);
	uint64_t noise_b = DRAM_HARSH_STRESS_NOISE_B_ADDR(cl_id);
	uint64_t snap_base = DRAM_HARSH_STRESS_SNAP_ADDR(cl_id);
	int snap_captured;

	for (int iter = 0; iter < iter_count; iter++) {
		rand_fill((void *)src_addr, DRAM_HARSH_STRESS_COMPARE_SIZE);
		cpu_flush_dcache_range((uintptr_t)src_addr,
				       DRAM_HARSH_STRESS_COMPARE_SIZE);
		dsb();

		dram_harsh_stress_fill_src(cl_id, src_addr);

		shm_test_mode_trigger();
		dnc_sp_test_mode_trigger();
		rdsn_test_mode_trigger();

		snap_idx = 0;
		last_phase_mod = dram_harsh_stress_run(cl_id, &task_id,
				      DRAM_HARSH_STRESS_BATCH, &snap_idx);

		rdsn_test_mode_check();
		dnc_sp_test_mode_check();
		wait_for_shm_tpg_done(TPG_TIMEOUT_VALUE);

		snap_captured = snap_idx;
		for (int s = 0; s < snap_captured; s++) {
			uint64_t snap_off = (uint64_t)(s %
				DRAM_HARSH_STRESS_SNAP_CHUNKS) *
				DRAM_HARSH_STRESS_SNAP_SIZE;
			uint64_t snap_addr = snap_base +
				(uint64_t)s * DRAM_HARSH_STRESS_SNAP_SIZE;
			snap_mismatch = dram_harsh_stress_compare(
				src_addr + snap_off, snap_addr,
				DRAM_HARSH_STRESS_COMPARE_SIZE);
			if (snap_mismatch > 0) {
				printf("SNAP slot %d (dst+0x%lx -> 0x%lx): %d mismatches\r\n",
				       s, snap_off, snap_addr, snap_mismatch);
				total_mismatch += snap_mismatch;
			}
		}

		if (last_phase_mod <= 2 || last_phase_mod == 7) {
			snap_mismatch = dram_harsh_stress_compare(
				src_addr, noise_a,
				DRAM_HARSH_STRESS_COMPARE_SIZE);
			if (snap_mismatch > 0) {
				printf("NOISE_A verify (phase=%d): %d mismatches\r\n",
				       last_phase_mod, snap_mismatch);
				noise_mismatch += snap_mismatch;
			}
		}
		if (last_phase_mod == 5) {
			snap_mismatch = dram_harsh_stress_compare(
				src_addr, noise_b,
				DRAM_HARSH_STRESS_COMPARE_SIZE);
			if (snap_mismatch > 0) {
				printf("NOISE_B verify (phase=%d): %d mismatches\r\n",
				       last_phase_mod, snap_mismatch);
				noise_mismatch += snap_mismatch;
			}
		}
	}

	return total_mismatch + noise_mismatch;
}

static int dram_harsh_stress_for_secondary(int iter_count)
{
	int cl_id = get_chiplet_id();
	int total_mismatch = 0;
	int noise_mismatch = 0;
	int snap_mismatch;
	int task_id = 0xDD440000;
	int snap_idx = 0;
	int last_phase_mod;
	uint64_t src_addr = DRAM_HARSH_STRESS_SRC_ADDR(cl_id);
	uint64_t noise_a = DRAM_HARSH_STRESS_NOISE_A_ADDR(cl_id);
	uint64_t noise_b = DRAM_HARSH_STRESS_NOISE_B_ADDR(cl_id);
	uint64_t snap_base = DRAM_HARSH_STRESS_SNAP_ADDR(cl_id);
	int snap_captured;

	for (int iter = 0; iter < iter_count; iter++) {
		rand_fill((void *)src_addr, DRAM_HARSH_STRESS_COMPARE_SIZE);
		cpu_flush_dcache_range((uintptr_t)src_addr,
				       DRAM_HARSH_STRESS_COMPARE_SIZE);
		dsb();

		dram_harsh_stress_fill_src(cl_id, src_addr);

		shm_test_mode_trigger();
		dnc_sp_test_mode_trigger();
		rdsn_test_mode_trigger();

		snap_idx = 0;
		last_phase_mod = dram_harsh_stress_run(cl_id, &task_id,
				      DRAM_HARSH_STRESS_BATCH, &snap_idx);

		rdsn_test_mode_check();
		dnc_sp_test_mode_check();
		wait_for_shm_tpg_done(TPG_TIMEOUT_VALUE);

		snap_captured = snap_idx;
		for (int s = 0; s < snap_captured; s++) {
			uint64_t snap_off = (uint64_t)(s %
				DRAM_HARSH_STRESS_SNAP_CHUNKS) *
				DRAM_HARSH_STRESS_SNAP_SIZE;
			uint64_t snap_addr = snap_base +
				(uint64_t)s * DRAM_HARSH_STRESS_SNAP_SIZE;
			snap_mismatch = dram_harsh_stress_compare(
				src_addr + snap_off, snap_addr,
				DRAM_HARSH_STRESS_COMPARE_SIZE);
			if (snap_mismatch > 0)
				total_mismatch += snap_mismatch;
		}

		if (last_phase_mod <= 2 || last_phase_mod == 7) {
			snap_mismatch = dram_harsh_stress_compare(
				src_addr, noise_a,
				DRAM_HARSH_STRESS_COMPARE_SIZE);
			if (snap_mismatch > 0)
				noise_mismatch += snap_mismatch;
		}
		if (last_phase_mod == 5) {
			snap_mismatch = dram_harsh_stress_compare(
				src_addr, noise_b,
				DRAM_HARSH_STRESS_COMPARE_SIZE);
			if (snap_mismatch > 0)
				noise_mismatch += snap_mismatch;
		}
	}

	return total_mismatch + noise_mismatch;
}

int dram_harsh_stress_test(void *ctx)
{
	int ret;
	int i;
	int iter_count = 1;
	struct ici_chip_sorting_entry entry = {0};
	test_func_list *item = ctx;

	if (item && item->args.trans_size > 0)
		iter_count = item->args.trans_size;

	RLOG_INFO("%s (iter=%d)\r\n", __func__, iter_count);

	/* ICI sync: all chiplets start together */
	if (cur_cl_id == 0) {
		for (i = 1; i < (int)chiplet_count_opt; i++)
			ici_send_sync_event(i);
		for (i = 1; i < (int)chiplet_count_opt; i++)
			ici_sync_receive_polling(i);
	} else {
		ici_wait_sync_event();
		ici_sync_message_clear();
	}

	rbdma_done_clear(get_chiplet_id());
	shm_randomize_cdp_register();

	if (get_chiplet_id() == 0) {
		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_DRAM_HARSH_STRESS;
		entry.size = iter_count;
		for (i = 1; i < (int)chiplet_count_opt; i++) {
			write_entry(i, &entry);
			dsb();
			ici_send_sync_event(i);
			ici_sync_receive_polling(i);
		}
		ret = dram_harsh_stress_test_core(iter_count);
	} else {
		ici_wait_sync_event();
		ici_sync_message_clear();
		dsb();
		read_entry(get_chiplet_id(), &entry);
		ret = dram_harsh_stress_for_secondary(entry.size > 0 ? entry.size : iter_count);
	}

	/* Drain remaining RBDMA */
	while (rbdma_global_normal_queue_status_cl(cur_cl_id) != 64)
		;
	while (rbdma_global_idle_status_cl(cur_cl_id) != 0xFF)
		;
	rbdma_done_clear(cur_cl_id);

	while (shm_check_cdp_register_clear(cur_cl_id) != 0)
		shm_clear_cdp_register();

	if (cur_cl_id == 0) {
		for (i = 1; i < (int)chiplet_count_opt; i++) {
			while (shm_check_cdp_register_clear(i) != 0)
				;
		}
	}

	if (ret > 0) {
		printf("DRAM_HARSH_STRESS_TEST: FAIL (%d total mismatches on CL%d)\r\n",
		       ret, cur_cl_id);
		return false;
	}

	// printf("DRAM_HARSH_STRESS_TEST: PASS (CL%d)\r\n", cur_cl_id);
	return true;
}

void ici_trigger_dram_harsh_stress(int iter_count)
{
	struct ici_chip_sorting_entry entry = {0};

	printf("dram harsh stress start (itercount: %d)\r\n", iter_count);
	entry.result = dram_harsh_stress_test(
		(void *)&(test_func_list){0, dram_harsh_stress_test,
			"dram_harsh_stress_test", {0, 0, (uint32_t)iter_count}});
	ici_message_clear(entry);
}

/*
 * dram_all_array_test (#43)
 *
 * Full DRAM array test per chiplet.
 *   - Test region per chiplet: [chiplet_base + 0x4000_0000,
 *                                chiplet_base + 0x7_EFFF_FFFF]
 *   - For each pattern: RBDMA write whole region, then RBDMA read
 *     whole region (ECC errors are caught by IRQ automatically).
 */

#define DRAM_AAT_START_OFF    0x40000000ULL
#define DRAM_AAT_END_OFF      0x7EFFFFFFFULL
#define DRAM_AAT_TOTAL_SIZE   (DRAM_AAT_END_OFF - DRAM_AAT_START_OFF + 1)
#define DRAM_AAT_CHUNK_SIZE   SZ_32M
#define DRAM_AAT_BATCH_SIZE   32

static void dram_aat_fill_pattern(void *addr, uint32_t size, uint32_t pattern)
{
	uint32_t *p = (uint32_t *)addr;
	uint32_t count = size / sizeof(uint32_t);

	for (uint32_t i = 0; i < count; i++)
		p[i] = pattern;
}

static int dram_all_array_test_core(int cl_id)
{
	static const uint32_t patterns[] = { 0xFFFFFFFF, 0x00000000, 0x55555555, 0xAAAAAAAA,
					   0x33333333, 0xCCCCCCCC, 0x5A5A5A5A, 0x3C3C3C3C };
	const size_t num_patterns = ARRAY_SIZE(patterns);

	uint64_t test_start = cl_base[cl_id] + DRAM_AAT_START_OFF;
	uint64_t test_size  = DRAM_AAT_TOTAL_SIZE;
	uint32_t chunk      = DRAM_AAT_CHUNK_SIZE;
	uint64_t buf_addr   = DCL0_SH_MEM_BASE_CL;
	uint32_t prev_opmode;
	int task_id = 0xDD450000 + (cl_id << 16);
	// uint32_t total_chunks = (uint32_t)((test_size + chunk - 1) / chunk);

	prev_opmode = rbdma_get_global_config_cdma_opmode0();
	rbdma_set_max_perf_mode(0x7);

	for (size_t pi = 0; pi < num_patterns; pi++) {
		uint64_t offset;
		int batch_cnt;
		uint32_t chunk_idx;
		uint32_t cur_size;

		dram_aat_fill_pattern((void *)buf_addr, chunk, patterns[pi]);
		cpu_flush_dcache_range((uintptr_t)buf_addr, chunk);
		dsb();

		offset = 0;
		batch_cnt = 0;
		chunk_idx = 0;

		while (offset < test_size) {
			cur_size = chunk;
			if (test_size - offset < chunk)
				cur_size = (uint32_t)(test_size - offset);

			generate_rbdma_task_tsync(task_id++,
				buf_addr, test_start + offset, cur_size,
				0x7, 0, 0xff,
				(batch_cnt == 0) ? 1 : 0);
			batch_cnt++;
			offset += cur_size;
			chunk_idx++;

			if (batch_cnt >= DRAM_AAT_BATCH_SIZE ||
			    offset >= test_size) {
				rbdma_tsync_by_cp();
				rbdma_done_acc_count(cl_id, batch_cnt);
				rbdma_done_clear(cl_id);
				// printf("  Write progress: %u/%u chunks\r\n",
				    //    chunk_idx, total_chunks);
				batch_cnt = 0;
			}
		}

		offset = 0;
		batch_cnt = 0;
		chunk_idx = 0;

		while (offset < test_size) {
			cur_size = chunk;
			if (test_size - offset < chunk)
				cur_size = (uint32_t)(test_size - offset);

			generate_rbdma_task_tsync(task_id++,
				test_start + offset, buf_addr, cur_size,
				0x7, 0, 0xff,
				(batch_cnt == 0) ? 1 : 0);
			batch_cnt++;
			offset += cur_size;
			chunk_idx++;

			if (batch_cnt >= DRAM_AAT_BATCH_SIZE ||
			    offset >= test_size) {
				rbdma_tsync_by_cp();
				rbdma_done_acc_count(cl_id, batch_cnt);
				rbdma_done_clear(cl_id);
				// printf("  Read progress: %u/%u chunks\r\n",
				    //    chunk_idx, total_chunks);
				batch_cnt = 0;
			}
		}
	}

	rbdma_set_global_config_cdma_opmode0(prev_opmode);
	return 0;
}

int dram_all_array_test(void *ctx)
{
	int ret;
	int i;

	(void)ctx;
	RLOG_INFO("%s\r\n", __func__);

	/* ICI sync: all chiplets start together */
	if (cur_cl_id == 0) {
		for (i = 1; i < (int)chiplet_count_opt; i++)
			ici_send_sync_event(i);
		for (i = 1; i < (int)chiplet_count_opt; i++)
			ici_sync_receive_polling(i);
	} else {
		ici_wait_sync_event();
		ici_sync_message_clear();
	}

	rbdma_done_clear(get_chiplet_id());

	if (get_chiplet_id() == 0) {
		struct ici_chip_sorting_entry entry = {0};

		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_DRAM_ALL_ARRAY;
		for (i = 1; i < (int)chiplet_count_opt; i++) {
			write_entry(i, &entry);
			dsb();
			ici_send_sync_event(i);
			ici_sync_receive_polling(i);
		}
		ret = dram_all_array_test_core(get_chiplet_id());
	} else {
		ici_wait_sync_event();
		ici_sync_message_clear();
		dsb();
		ret = dram_all_array_test_core(get_chiplet_id());
	}

	/* Drain remaining RBDMA */
	while (rbdma_global_normal_queue_status_cl(cur_cl_id) != 64)
		;
	while (rbdma_global_idle_status_cl(cur_cl_id) != 0xFF)
		;
	rbdma_done_clear(cur_cl_id);

	if (ret != 0) {
		printf("DRAM_ALL_ARRAY_TEST: FAIL (CL%d)\r\n", cur_cl_id);
		return false;
	}

	// printf("DRAM_ALL_ARRAY_TEST: PASS (CL%d)\r\n", cur_cl_id);
	return true;
}

int ldudma_dram_2_sp(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
		//generate task
		generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
		tb[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(src_addr, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);    //chiplet 0

	return 1;
}

int ldudma_4MB_near_sp(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	RLOG_INFO("from dram to dnc'sp 0,2,4,,,\r\n");
	// dram -> sp
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i%2 == 0) {
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);

	RLOG_INFO("task all done\r\n");
	RLOG_INFO("\r\nfrom sp to dnc'sp\r\n");
	// sp0 -> sp1
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i%2 != 0) {
			src_addr = DCL0_SP_MEM_BASE_CL + SZ_4M*(i-1);
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int ldudma_4MB_far_sp(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//   volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	RLOG_INFO("from dram to dnc'sp\r\n");
	// dram -> sp
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i < HW_SPEC_DNC_COUNT/2) {
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);

	RLOG_INFO("task all done\r\n");

	RLOG_INFO("\r\nfrom sp to dnc'sp\r\n");
	// sp0 -> sp8
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i > (HW_SPEC_DNC_COUNT-1)/2) {
			src_addr = DCL0_SP_MEM_BASE_CL + SZ_4M*(i-8);
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int ldudma_4MB_near_shm(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = DCL0_SH_MEM_BASE_CL;     // SHM base
	uint32_t trs_size   = SZ_4M;                // trs size is 4MB
	uint32_t task_id    = 0xDD3A0000;
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//   volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	// shm clear , cl0
	if (shm_init(cur_cl_id) < 0)
		return false;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		generate_rbdma_task(task_id | i << 12, src_addr, dst_addr + i*SZ_4M, trs_size, 0);
	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT);
	rbdma_done_clear(cur_cl_id);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		src_addr = DCL0_SH_MEM_BASE_CL + i*SZ_4M;
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
		//generate task
		dst_addr = 0;   // sp
		generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
		tb[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);    //chiplet 0

	return 1;
}

int ldudma_4MB_far_shm(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = DCL0_SH_MEM_BASE_CL;     // SHM base
	uint32_t trs_size   = SZ_4M;                // trs size is 2MB
	uint32_t task_id    = 0xDD3A0000;
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	// shm clear
	if (shm_init(cur_cl_id) < 0)
		return false;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		generate_rbdma_task(task_id | i << 12, src_addr, dst_addr + i*SZ_4M, trs_size, 0);
	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT);
	rbdma_done_clear(cur_cl_id);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i < HW_SPEC_DNC_COUNT/2)
			src_addr = DCL1_SH_MEM_BASE_CL + i*SZ_4M;
		else
			src_addr = DCL0_SH_MEM_BASE_CL + (i-8)*SZ_4M;
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
		//generate task
		dst_addr = 0;   // sp
		generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
		tb[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int lpudma_dram_2_sp(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	tlb_table_init();

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LPuDMA, src_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
		//generate task
		generate_udma_task(i, (enum cmd_mode)LPuDMA, src_addr, dst_addr, trs_size);
		tb[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LPuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int lpudma_4MB_near_sp(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	tlb_table_init();

	RLOG_INFO("from dram to dnc'sp\r\n");
	// dram -> sp
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i%2 == 0) {
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LPuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LPuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LPuDMA, tb[i]);

	RLOG_INFO("task all done\r\n");

	RLOG_INFO("\r\nfrom sp to dnc'sp\r\n");
	// sp0 -> sp1
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i%2 != 0) {
			src_addr = DCL0_SP_MEM_BASE_CL + SZ_4M*(i-1);
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LPuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LPuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LPuDMA, tb[i]);

	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int lpudma_4MB_far_sp(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	tlb_table_init();

	RLOG_INFO("from dram to dnc'sp\r\n");
	// dram -> sp
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i < HW_SPEC_DNC_COUNT/2) {
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LPuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LPuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LPuDMA, tb[i]);

	RLOG_INFO("task all done\r\n");

	RLOG_INFO("\r\nfrom sp to dnc'sp\r\n");
	// sp0 -> sp8
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i > (HW_SPEC_DNC_COUNT-1)/2) {
			src_addr = DCL0_SP_MEM_BASE_CL + SZ_4M*(i-8);
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LPuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LPuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LPuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int lpudma_4MB_near_shm(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = DCL0_SH_MEM_BASE_CL;     // SHM base
	uint32_t trs_size   = SZ_4M;                // trs size is 4MB
	uint32_t task_id    = 0xDD3A0000;
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	// shm clear
	if (shm_init(cur_cl_id) < 0)
		return false;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		generate_rbdma_task(task_id | i<<12, src_addr, dst_addr + i*SZ_4M, trs_size, 0);
	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT);
	rbdma_done_clear(cur_cl_id);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	tlb_table_init();

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		src_addr = DCL0_SH_MEM_BASE_CL + i*SZ_4M;
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LPuDMA, src_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
		//generate task
		dst_addr = 0;   // sp
		generate_udma_task(i, (enum cmd_mode)LPuDMA, src_addr, dst_addr, trs_size);
		tb[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LPuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int lpudma_4MB_far_shm(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = DCL0_SH_MEM_BASE_CL;     // SHM base
	uint32_t trs_size   = SZ_4M;                // trs size is 4MB
	uint32_t task_id    = 0xDD3A0000;
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//   volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	// shm clear
	if (shm_init(cur_cl_id) < 0)
		return false;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		generate_rbdma_task(task_id | i<<12, src_addr, dst_addr + i*SZ_4M, trs_size, 0);
	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT);
	rbdma_done_clear(cur_cl_id);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	tlb_table_init();

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i < HW_SPEC_DNC_COUNT/2)
			src_addr = DCL1_SH_MEM_BASE_CL + i*SZ_4M;
		else
			src_addr = DCL0_SH_MEM_BASE_CL + (i-8)*SZ_4M;
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LPuDMA, src_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
		//generate task
		dst_addr = 0;   // sp
		generate_udma_task(i, (enum cmd_mode)LPuDMA, src_addr, dst_addr, trs_size);
		tb[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LPuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int studma_sp_2_dram(void *ctx)
{
	uint64_t dst_addr   = DATA_OUT_BASE_ADDR;   // Dram output addr
	uint64_t src_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret = false;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	ldudma_dram_2_sp(&item_list[11]); // 6000_0000 -> SP

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)STuDMA, dst_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);

		//generate task
		generate_udma_task(i, (enum cmd_mode)STuDMA, src_addr, dst_addr, trs_size);
		tb[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)STuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");
	memset(&tb, 0x0, sizeof(uint32_t)*HW_SPEC_DNC_COUNT);
	dnc_done_acc_count_all_clear(cur_cl_id);


	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int studma_4MB_near_sp(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	RLOG_INFO("[LDuDMA] from dram to dnc'sp 0,2,4,,,\r\n");
	// dram -> sp 0,2,4,,,
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i%2 == 0) {
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);

	RLOG_INFO("task all done\r\n");

	RLOG_INFO("\r\n[STuDMA] from sp 0,2,4,,, to dnc'sp 1,3,5,,,\r\n");
	memset(&tb, 0x0, sizeof(uint32_t)*HW_SPEC_DNC_COUNT);

	// sp0 -> sp1
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i%2 == 0) {
			src_addr = 0;
			dst_addr = DCL0_SP_MEM_BASE_CL + i*SZ_4M + SZ_4M;
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)STuDMA, dst_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)STuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)STuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

int studma_4MB_far_sp(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	RLOG_INFO("[LDuDMA] from dram to dnc'sp 0,1,2,,7\r\n");
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i < HW_SPEC_DNC_COUNT/2) {
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");


	RLOG_INFO("\r\n[STuDMA] from sp 0,1,2,,,7 to dnc'sp 8,9,10,,15\r\n");
	memset(&tb, 0x0, sizeof(uint32_t)*HW_SPEC_DNC_COUNT);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i < HW_SPEC_DNC_COUNT/2) {
			src_addr = 0;
			dst_addr = DCL1_SP_MEM_BASE_CL + SZ_4M*i;
			tb[i] = insert_or_find_tlb(i, (enum cmd_mode)STuDMA, dst_addr, trs_size);
			RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
			//generate task
			generate_udma_task(i, (enum cmd_mode)STuDMA, src_addr, dst_addr, trs_size);
			tb[i] += 1;
		}
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)STuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SP_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}


int studma_4MB_near_shm(void *ctx)
{
	uint64_t dst_addr   = DCL0_SH_MEM_BASE_CL;   // SHM MEM
	uint64_t src_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t task_id    = 0xDD3A0000;
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret = false;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	ldudma_dram_2_sp(&item_list[11]); // 6000_0000 -> SP

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		dst_addr = DCL0_SH_MEM_BASE_CL + i*SZ_4M;
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)STuDMA, dst_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
		src_addr = 0;   //sp
				//generate task
		generate_udma_task(i, (enum cmd_mode)STuDMA, src_addr, dst_addr, trs_size);
		tb[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)STuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");
	memset(&tb, 0x0, sizeof(uint32_t)*HW_SPEC_DNC_COUNT);
	dnc_done_acc_count_all_clear(cur_cl_id);

	// SHM -> dram
	src_addr = DCL0_SH_MEM_BASE_CL;
	dst_addr = DATA_OUT_BASE_ADDR;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		generate_rbdma_task(task_id | i<<12, src_addr + i*SZ_4M, dst_addr + i*SZ_4M, trs_size, 0);

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DATA_OUT_BASE_ADDR, trs_size);
	if (ret)
		return false;

	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT);
	rbdma_done_clear(cur_cl_id);

	return 1;
}

int studma_4MB_far_shm(void *ctx)
{
	uint64_t dst_addr   = DCL0_SH_MEM_BASE_CL;   // SHM MEM
	uint64_t src_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_4M;        // trs size is 4MB
	uint32_t task_id    = 0xDD3A0000;
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret = false;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	ldudma_dram_2_sp(&item_list[11]); // 6000_0000 -> SP

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (i < HW_SPEC_DNC_COUNT/2)
			dst_addr = DCL1_SH_MEM_BASE_CL + i*SZ_4M;
		else
			dst_addr = DCL0_SH_MEM_BASE_CL + (i-8)*SZ_4M;
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)STuDMA, dst_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);

		//generate task
		generate_udma_task(i, (enum cmd_mode)STuDMA, src_addr, dst_addr, trs_size);
		tb[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)STuDMA, tb[i]);
	RLOG_INFO("task all done\r\n");
	memset(&tb, 0x0, sizeof(uint32_t)*HW_SPEC_DNC_COUNT);
	dnc_done_acc_count_all_clear(cur_cl_id);

	// SHM -> SP
	src_addr = DCL0_SH_MEM_BASE_CL;
	dst_addr = DATA_OUT_BASE_ADDR;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		generate_rbdma_task(task_id | i<<12, src_addr + i*SZ_4M, dst_addr + i*SZ_4M, trs_size, 0);

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SH_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT);
	rbdma_done_clear(cur_cl_id);

	return 1;
}

/*
 * Generate a random pattern in DRAM
 * Transfer data from DRAM to SHM for each DNC slice using RBDMA (4MB x 16)
 * Copy the data back from SHM to DRAM
 * Compare the original DRAM data with the final result to verify consistency
 * In short, this is a DRAM ↔ SHM data transfer and verification routine using the RBDMA engine.
 */
int rbdma_dram_2_shm(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = DCL0_SH_MEM_BASE_CL;     // SHM base
	uint32_t trs_size   = SZ_4M;                // trs size is 4MB
	uint32_t task_id    = 0xDD3A0000;
	//    uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
	//    volatile uint32_t *dump_ptr;
	int ret = false;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	RLOG_INFO("\r\n[dram -> shm]\r\n");
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		generate_rbdma_task(task_id | i<<12, src_addr, dst_addr + i * SZ_4M, trs_size, 0);
	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT);
	rbdma_done_clear(cur_cl_id);

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DCL0_SH_MEM_BASE_CL, trs_size);
	if (ret)
		return false;

	cpu_inv_dcache_range((uintptr_t)DATA_OUT_BASE_ADDR, SZ_4M * 16);

	RLOG_INFO("\r\n[shm -> dram]\r\n");
	src_addr = DCL0_SH_MEM_BASE_CL;
	dst_addr = DATA_OUT_BASE_ADDR;
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		generate_rbdma_task(task_id | i<<12, src_addr + i*SZ_4M, dst_addr + i*SZ_4M, trs_size, 0);

	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT);
	rbdma_done_clear(cur_cl_id);

	ret = dnc_test_result_cmp_all(DATA_MEM_BASE_ADDR, DATA_OUT_BASE_ADDR, trs_size);
	if (ret)
		return false;

	return 1;
}

#define ARGS_STR_BUF_LEN			16
#define INVALID_MEM_BASE_ADDR_VAL	((uint64_t)(-1))

#define RBDMA_ARGC_NUM				3

static inline uint64_t mem_get_base_addr(const enum memory_type type)
{
	uint64_t addr;

	switch (type) {
	case DRAM:
		addr = DATA_MEM_BASE_ADDR;
		break;
	case SHM:
		addr = DCL0_SH_MEM_BASE_CL;
		break;
	case SP:
		addr = 0x0;
		break;
	default:
		addr = INVALID_MEM_BASE_ADDR_VAL;
		break;
	}

	return addr;
}

/*
 * Convert source DRAM base address and destination DRAM base address into string arguments.
 * Fill source DRAM with a random test pattern.
 * Use rbdma_test() to transfer data from source DRAM to destination DRAM.
 * Compare the original DRAM data with the copied DRAM data to verify consistency.
 */
int rbdma_common_test_func(void *ctx)
{
	int ret;
	uint64_t src_addr;
	uint64_t dst_addr;
	char src_addr_str[ARGS_STR_BUF_LEN];
	char dst_addr_str[ARGS_STR_BUF_LEN];
	char size_str[ARGS_STR_BUF_LEN];
	test_func_list *item = ctx;
	struct test_ctx_args *args = &item->args;

	RLOG_DBG("%s\n", item->function_name);

	src_addr = mem_get_base_addr(args->dma_src_dev);
	if (src_addr == INVALID_MEM_BASE_ADDR_VAL)
		return false;

	dst_addr = mem_get_base_addr(args->dma_dst_dev);
	if (dst_addr == INVALID_MEM_BASE_ADDR_VAL)
		return false;

	snprintf(src_addr_str, sizeof(src_addr_str), "%lx", src_addr);
	snprintf(dst_addr_str, sizeof(dst_addr_str), "%lx", dst_addr);
	snprintf(size_str, sizeof(size_str), "%lx", args->trans_size);

	rand_fill((void *)src_addr, args->trans_size);

	char *argv[RBDMA_ARGC_NUM] = {src_addr_str, dst_addr_str, size_str};

	if (!rbdma_test(RBDMA_ARGC_NUM, argv))
		return false;

	ret = basic_test_compare(src_addr, dst_addr, args->trans_size);
	if (ret < 0)
		return false;

	return true;
}

/*
 * Generate a random pattern in DRAM (32MB total = 4MB × 8 ports).
 * Initialize an RBDMA task descriptor (rb_desc_t).
 * For each port (0–7):
 * Assign source and destination DRAM addresses.
 * Set task ID and TE mask.
 * Generate the RBDMA task using generate_rbdma_task_opt().
 * Wait for completion of all tasks using rbdma_done_acc_count().
 * Clear the completion status with rbdma_done_clear().
 * Compare the original DRAM data and the copied DRAM data (total 32MB).
 * Return true if data matches, otherwise false.
 */
int rbdma_dram_2_dram_all_port(void *ctx)
{
	uint64_t src_addr = DATA_MEM_BASE_ADDR;
	uint64_t dst_addr = DATA_OUT_BASE_ADDR;
	uint32_t trs_size = SZ_4M;
	uint32_t task_id = 0xDD3A0000;
	uint8_t num_of_port = 8;    // num of TE is 8
	int ret = false;
	rb_desc_t   desc;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, SZ_4M * num_of_port);

	memset(&desc, 0x0, sizeof(rb_desc_t));

	desc.trs_size   = trs_size;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.task_type  = 0;    //
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 3;    //bl8

	for (int i = 0; i < num_of_port; i++) {
		src_addr    = DATA_MEM_BASE_ADDR + i*SZ_4M;
		dst_addr    = DATA_OUT_BASE_ADDR + i*SZ_4M;
		desc.task_id    = task_id | i<<12;
		desc.src_addr   = src_addr;
		desc.dst_addr   = dst_addr;
		desc.te_mask    = 0x1<<i;
		generate_rbdma_task_opt(desc);
	}

	rbdma_done_acc_count(cur_cl_id, num_of_port);	// num_of_port is 8

	rbdma_done_clear(cur_cl_id);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR, DATA_OUT_BASE_ADDR, SZ_4M * num_of_port);
	if (ret < 0)
		return false;

	return true;
}

/*
 * Fill DRAM source memory with random data.
 * Initialize the DMA descriptor structure.
 * Issue first DMA task: transfer data from DRAM → SHM with different burst length settings (read_bl=8, write_bl=4).
 * Invalidate CPU cache to ensure correct read from SHM.
 * Issue second DMA task: transfer data from SHM → DRAM with swapped burst length settings (read_bl=4, write_bl=8).
 * Wait for completion and clear DMA done flags.
 * Compare source and destination data to validate transfer correctness.
 */
int rbdma_burst_length(void *ctx)
{
	uint32_t trs_size = SZ_2M;
	uint32_t task_id = 0xDD3A0000;
	int ret = false;
	rb_desc_t   desc;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	memset(&desc, 0x0, sizeof(rb_desc_t));

	desc.task_id    = task_id | 0x1<<12;
	desc.src_addr   = DATA_MEM_BASE_ADDR;
	desc.dst_addr   = DCL0_SH_MEM_BASE_CL;
	desc.te_mask    = 0xff;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.trs_size   = trs_size;
	desc.task_type  = 0;    //
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 2;    //bl4
	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, 1);

	cpu_inv_dcache_range((uintptr_t)DATA_OUT_BASE_ADDR, trs_size);

	desc.task_id    = task_id | 0x2<<12;
	desc.src_addr   = DCL0_SH_MEM_BASE_CL;
	desc.dst_addr   = DATA_OUT_BASE_ADDR;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 3;    //bl8
	desc.read_qos   = 1;
	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, 2);

	rbdma_done_clear(cur_cl_id);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR, DATA_OUT_BASE_ADDR, trs_size);
	if (ret < 0)
		return false;

	return true;
}

/*
 * Fill DRAM source memory with random data (4MB).
 * Initialize the RBDMA task descriptor.
 * Issue the first DMA task to transfer data from DRAM → SHM.
 * Invalidate CPU cache to ensure correct data read from SHM.
 * Issue the second DMA task to transfer data from SHM → DRAM.
 * Wait for completion of both tasks and clear the DMA done flags.
 * Compare the original DRAM data with the final DRAM destination to validate transfer correctness.
 */
int rbdma_large_memory_copy(void *ctx)
{
	uint32_t trs_size = SZ_4M;
	uint32_t task_id = 0xDD3A0000;
	int ret = false;
	rb_desc_t   desc;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	memset(&desc, 0x0, sizeof(rb_desc_t));

	desc.task_id    = task_id | 0x1<<12;
	desc.src_addr   = DATA_MEM_BASE_ADDR;
	desc.dst_addr   = DCL0_SH_MEM_BASE_CL;
	desc.trs_size   = trs_size;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.task_type  = 0;
	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, 1);

	cpu_inv_dcache_range((uintptr_t)DATA_OUT_BASE_ADDR, trs_size);

	desc.task_id    = task_id | 0x2<<12;
	desc.src_addr   = DCL0_SH_MEM_BASE_CL;
	desc.dst_addr   = DATA_OUT_BASE_ADDR;

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, 2);

	rbdma_done_clear(cur_cl_id);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR, DATA_OUT_BASE_ADDR, trs_size);
	if (ret < 0)
		return false;

	return true;
}

/*
 * Fill DRAM memory with random data (8KB).
 * Shift data backward in DRAM and verify.
 * Shift data forward in DRAM using data_shift and verify.
 * Copy data from DRAM → local SHM and verify.
 * Perform data_shift inside local SHM and verify.
 * Copy data from local SHM(DCL0) → other SHM(DCL1) and verify.
 * Perform data_shift in other SHM and verify.
 * Copy final data from other SHM → DRAM and verify.
 * Clear DMA completion flags.
 */
int rbdma_data_shift(void *ctx)
{
	uint32_t trs_size = SZ_8K;
	uint32_t task_id = 0xDD3A0000;
	int ret = false;
	int cnt = 1;
	rb_desc_t   desc;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DATA_MEM_BASE_ADDR;
	desc.dst_addr   = DATA_MEM_BASE_ADDR - SZ_8K;
	desc.trs_size   = trs_size;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 3;    //bl8

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR, DATA_MEM_BASE_ADDR - SZ_8K, trs_size);
	if (ret < 0)
		return false;

	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DATA_MEM_BASE_ADDR;
	desc.dst_addr   = DATA_MEM_BASE_ADDR + SZ_4K;   //0x20<<7
	desc.trs_size   = trs_size;
	desc.task_type  = 0xc;          //data_shift
	desc.num_of_chunk   = 0x2b9;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 3;    //bl8

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR - SZ_8K, DATA_MEM_BASE_ADDR + SZ_4K, trs_size);
	if (ret < 0)
		return false;

	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DATA_MEM_BASE_ADDR + SZ_4K;
	desc.dst_addr   = DCL0_SH_MEM_BASE_CL;
	desc.trs_size   = trs_size;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.read_qos   = 1;

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR - SZ_8K, DCL0_SH_MEM_BASE_CL, trs_size);
	if (ret < 0)
		return false;

	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DCL0_SH_MEM_BASE_CL;
	desc.dst_addr   = DCL0_SH_MEM_BASE_CL + SZ_4K;
	desc.trs_size   = trs_size;
	desc.task_type  = 0xc;          //data_shift
	desc.num_of_chunk   = 0xaad;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 3;    //bl8
	desc.read_qos   = 1;

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR - SZ_8K, DCL0_SH_MEM_BASE_CL + SZ_4K, trs_size);
	if (ret < 0)
		return false;

	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DCL0_SH_MEM_BASE_CL + SZ_4K;
	desc.dst_addr   = DCL1_SH_MEM_BASE_CL + SZ_16M;    // 0x1F_E600_0000 + 0x100_0000
	desc.trs_size   = trs_size;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.read_qos   = 1;

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR - SZ_8K, DCL1_SH_MEM_BASE_CL + SZ_16M, trs_size);
	if (ret < 0)
		return false;

	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DCL1_SH_MEM_BASE_CL + SZ_16M;
	desc.dst_addr   = DCL1_SH_MEM_BASE_CL + SZ_16M - SZ_8K;
	desc.trs_size   = trs_size;
	desc.task_type  = 0xc;
	desc.num_of_chunk   = 0x4da;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 3;    //bl8
	desc.read_qos   = 1;
	desc.write_qos  = 1;

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR - SZ_8K, DCL1_SH_MEM_BASE_CL + SZ_16M - SZ_8K, trs_size);
	if (ret < 0)
		return false;

	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DCL1_SH_MEM_BASE_CL + SZ_16M - SZ_8K;
	desc.dst_addr   = DATA_OUT_BASE_ADDR;
	desc.trs_size   = trs_size;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.write_qos  = 1;

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR - SZ_8K, DATA_OUT_BASE_ADDR, trs_size);
	if (ret < 0)
		return false;

	rbdma_done_clear(cur_cl_id);

	return true;
}

int rbdma_sct_gth(void *ctx)
{
	uint32_t trs_size = SZ_4K;
	uint32_t task_id = 0xDD3A0000;
	int ret = false;
	int cnt = 1;
	rb_desc_t   desc;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DATA_MEM_BASE_ADDR;
	desc.dst_addr   = DCL0_SH_MEM_BASE_CL;
	desc.trs_size   = trs_size;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 3;    //bl8

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = 0xCAFEF00D;
	desc.dst_addr   = DCL0_SH_MEM_BASE_CL + SZ_2K;
	desc.trs_size   = SZ_2K;
	desc.task_type  = 0x1; // constant copy
	desc.num_of_chunk   = 0x1a0;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.read_qos   = 1;
	desc.write_qos  = 1;

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	// scatter
	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DCL0_SH_MEM_BASE_CL;
	desc.dst_addr   = DCL1_SH_MEM_BASE_CL;
	desc.trs_size   = SZ_512;
	desc.task_type  = 0x3; // scatter
	desc.num_of_chunk   = 0x7;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.read_qos   = 1;

	generate_rbdma_chunk_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	// gather
	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DCL1_SH_MEM_BASE_CL;
	desc.dst_addr   = DATA_OUT_BASE_ADDR;
	desc.trs_size   = SZ_512;
	desc.task_type  = 0x2; // gather
	desc.num_of_chunk   = 0x7;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.read_qos   = 1;

	generate_rbdma_chunk_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR, DATA_OUT_BASE_ADDR, SZ_2K);
	if (ret < 0)
		return false;

	rbdma_done_clear(cur_cl_id);

	return true;
}

/*
 * Fill DRAM memory with random data (4KB).
 * Copy DRAM → local SHM using RBDMA.
 * Write a constant pattern to SHM for testing constant copy.
 * Perform scatter operation from local SHM(DCL0) → other SHM(DCL1).
 * Perform gather operation from other SHM → DRAM.
 * Verify data integrity between original DRAM and final DRAM.
 * Clear all DMA completion flags.
 */
int rbdma_sct_gth_w_regular(void *ctx)
{
	uint32_t trs_size = SZ_4K;
	uint32_t task_id = 0xDD3A0000;
	int ret = false;
	int cnt = 1;
	rb_desc_t   desc;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DATA_MEM_BASE_ADDR;
	desc.dst_addr   = DCL0_SH_MEM_BASE_CL;
	desc.trs_size   = trs_size;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 3;    //bl8

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++); // cl0

	// scatter w/ regular
	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DCL0_SH_MEM_BASE_CL;
	desc.dst_addr   = DCL1_SH_MEM_BASE_CL;
	desc.trs_size   = SZ_2K;
	desc.task_type  = 0x7; // scatter w/ regular
	desc.num_of_chunk   = 0x1;  // 2 pkt
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.read_qos   = 1;
	desc.write_qos   = 1;

	generate_rbdma_chunk_opt_regular(desc, SZ_4M);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	// gather w/ regular
	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | cnt<<12;
	desc.src_addr   = DCL1_SH_MEM_BASE_CL;
	desc.dst_addr   = DATA_OUT_BASE_ADDR;
	desc.trs_size   = SZ_2K;
	desc.task_type  = 0x6; // gather w/ regular
	desc.num_of_chunk   = 0x1;  // 2 pkt
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0xff;
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.write_qos   = 1;

	generate_rbdma_chunk_opt_regular(desc, SZ_4M);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR, DATA_OUT_BASE_ADDR, SZ_4K);
	if (ret < 0)
		return false;

	rbdma_done_clear(cur_cl_id);

	return true;
}

/*
 * Fill DRAM memory with random data (4MB).
 * Configure DMA done report destination in memory (rpt_base).
 * Launch a DMA task from DRAM → DRAM output, enabling the DMA report.
 * Wait for DMA completion and clear DMA done flags.
 * Verify data integrity between original DRAM and final DRAM.
 * Check the DMA report memory to ensure the reported task ID matches.
 */
int rbdma_report_dump(void *ctx)
{
	uint32_t trs_size = SZ_4M;
	uint64_t rpt_base   = 0x90000000;
	uint32_t task_id = 0xDD3A0000;
	int ret = false;
	rb_desc_t   desc;

	RLOG_INFO("%s\r\n", __func__);
	rand_fill((void *)DATA_MEM_BASE_ADDR, trs_size);

	rbdma_donerpt_config(rpt_base);

	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id | 0x1<<12;
	desc.src_addr   = DATA_MEM_BASE_ADDR;
	desc.dst_addr   = DATA_OUT_BASE_ADDR;
	desc.te_mask    = 0x91;
	desc.intr_disable   = 1;
	desc.en_donerpt_mst = 1;
	desc.en_invalid_pt  = 1;
	desc.no_tlb     = 1;
	desc.trs_size   = trs_size;
	desc.task_type  = 0;    //
	desc.read_bl    = 2;    //bl4
	desc.write_bl   = 2;    //bl4
	desc.read_qos   = 1;

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, 1);

	rbdma_done_clear(cur_cl_id);

	ret = basic_test_compare(DATA_MEM_BASE_ADDR, DATA_OUT_BASE_ADDR, trs_size);
	if (ret < 0)
		return false;

	volatile uint32_t *p_golden = (volatile uint32_t *)rpt_base;

	if (*p_golden != desc.task_id)
		return false;

	return true;
}

/*
 * Fill DRAM memory with random data (2MB).
 * Configure DNC reporting mode to CMGR.
 * Configure CMGR queues: LD → ST task mapping with notifications.
 * Clear scratchpad (SP) memory in each DNC.
 * Setup and launch LD (Load) tasks for each DNC to transfer from DRAM → SP.
 * Setup and launch ST (Store) tasks for each DNC to transfer SP → DRAM output, using TSYNC for synchronization check.
 * Display CMGR status and verify proper task execution.
 * Clear DNC sync registers, reset DNC reporting mode, and clear accumulated task counters.
 */
int cmgr_dnc_interop_test(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = 0x0;                  // SP base
	uint32_t trs_size   = SZ_2M;        // trs size is 2MB
	uint32_t ldcnt[HW_SPEC_DNC_COUNT] = {0, };
	uint32_t stcnt[HW_SPEC_DNC_COUNT] = {0, };
	DescTsyncInfo       sync_conf;
	cmgr_desc_t         cmgr_conf;
	int ret;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	dnc_rpt_mode_config(0x1);   // CMGR

	// cmgr config Q0
	memset(&cmgr_conf, 0x0, sizeof(cmgr_desc_t));
	cmgr_conf.cmd_id    = (enum cmd_mode)LDuDMA;
	cmgr_conf.affinity  = 0xffff;   // dncx16
	cmgr_conf.notification  = 0xffff;

	cmgr_conf.event_group_idx_dnc   = 0;
	cmgr_conf.event_code_dnc    = 0x1<<(enum cmd_mode)STuDMA;
	cmgr_conf.cmd_type  = (enum cmd_mode)LDuDMA;
	cmgr_config(cmgr_conf);   // recv:ldudma -> send:studma

	memset(&cmgr_conf, 0x0, sizeof(cmgr_desc_t));
	cmgr_conf.cmd_id    = (enum cmd_mode)STuDMA;
	cmgr_conf.affinity  = 0xffff;   // dncx16
	cmgr_conf.notification  = 0x200000;   // [21] CP intr
	cmgr_config(cmgr_conf);   //

	ret = dnc_clear_sp_all();
	if (ret)
		return false;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		ldcnt[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, ldcnt[i]);
		//generate task
		generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
		ldcnt[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, ldcnt[i]);
	RLOG_INFO("task all done\r\n");

	// tsync
	memset(&sync_conf, 0x0, sizeof(DescTsyncInfo));
	sync_conf.tsync_chk_mode    = 3;    // TC0
	sync_conf.tsync_chk_code    = (enum cmd_mode)LDuDMA;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		src_addr = 0;
		dst_addr = DATA_OUT_BASE_ADDR + i*SZ_2M;
		stcnt[i] = insert_or_find_tlb(i, (enum cmd_mode)STuDMA, dst_addr, trs_size);
		RLOG_INFO("[dnc%02d] tlb table set count is (%d)\r\n", i, stcnt[i]);
		//generate task
		generate_udma_task_opt(i, (enum cmd_mode)STuDMA, src_addr, dst_addr, trs_size, &sync_conf);
		stcnt[i] += 1;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_accumulate_count(i, (enum cmd_mode)STuDMA, stcnt[i]);

	RLOG_INFO("task all done\r\n");

	if (cmgr_display_status() == false)
		return false;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_sync_passage_reg_clear(i);
	dnc_rpt_mode_config(0x2);   // CP(default)
	dnc_done_acc_count_all_clear(cur_cl_id);
	cmgr_acc_count_clear();

	return true;
}

/*
 * Fill DRAM memory with random data (4MB).
 * Initialize SHM for the current chiplet.
 * Configure CMGR to monitor RBDMA completion events.
 * Setup CMGR queues for RBDMA tasks with notifications.
 * Launch RBDMA task: DRAM → SHM.
 * Launch RBDMA task: SHM → DRAM, including TSYNC check.
 * Display CMGR status to verify task completion.
 * Clear CMGR and RBDMA counters, disable events.
 */
int cmgr_rbdma_interop_test(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = DCL0_SH_MEM_BASE_CL;     // SHM base
	uint32_t trs_size   = SZ_4M;                // trs size is 4MB
	uint32_t task_id    = 1;       // cmd_id = 1
	int cnt = 1;
	//    volatile uint32_t *dump_ptr;
	//    int ret = false;
	rb_desc_t   desc;
	cmgr_desc_t         cmgr_conf;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr, trs_size);

	// shm clear
	if (shm_init(cur_cl_id) < 0)
		return false;

	rbdma_cmgr_config(cur_cl_id, 1);   // cmgr done event

	// cmgr config Q0
	memset(&cmgr_conf, 0x0, sizeof(cmgr_desc_t));
	cmgr_conf.cmd_id    = task_id;
	cmgr_conf.affinity  = 0x10000;   // rbdma
	cmgr_conf.notification  = 0x10000;

	cmgr_conf.event_group_idx_rbdma    = 0x1;
	cmgr_conf.cmd_type  = 0x4;  // rbdma_normal
	cmgr_config(cmgr_conf);

	//
	memset(&cmgr_conf, 0x0, sizeof(cmgr_desc_t));
	cmgr_conf.cmd_id    = task_id + 1;
	cmgr_conf.affinity  = 0x10000;   // rbdma
	cmgr_conf.notification  = 0x200000;
	cmgr_conf.cmd_type  = 0x4;  // rbdma_normal
	cmgr_config(cmgr_conf);

	RLOG_INFO("\r\n[dram -> shm]\r\n");
	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = task_id<<16;      //cmd_id
	desc.src_addr   = src_addr;
	desc.dst_addr   = dst_addr;
	desc.trs_size   = trs_size;
	desc.intr_disable   = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0x1;
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 3;    //bl8

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);

	RLOG_INFO("\r\n[shm -> dram]\r\n");
	memset(&desc, 0x0, sizeof(rb_desc_t));
	desc.task_id    = (task_id + 1)<<16;     //cmd_id
	desc.src_addr   = dst_addr;
	desc.dst_addr   = DATA_OUT_BASE_ADDR;
	desc.trs_size   = trs_size;
	desc.intr_disable   = 1;
	desc.no_tlb     = 1;
	desc.te_mask    = 0x2;
	desc.read_bl    = 3;    //bl8
	desc.write_bl   = 3;    //bl8
	desc.get_dnc_mask   = 0xffff;
	desc.get_tsync_gidx = 1;
	desc.get_tsync_en   = 1;

	generate_rbdma_task_opt(desc);
	rbdma_done_acc_count(cur_cl_id, cnt++);
	RLOG_INFO("task all done\r\n");

	if (cmgr_display_status() == false)
		return false;

	rbdma_cmgr_config(cur_cl_id, 0);   // cmgr done event off
	rbdma_done_clear(cur_cl_id);
	cmgr_acc_count_clear();

	return true;
}

/*
 * Fill DRAM memory with random data (4MB).
 * Transfer DRAM → DCL0 SHM using RBDMA per DNC slice.
 * Compare DRAM vs DCL0 SHM to verify data integrity.
 * Transfer DCL0 SHM → DCL1 SHM using RBDMA per DNC slice.
 * Compare DCL0 SHM vs DCL1 SHM to verify data integrity.
 */
int rbdma_shm_2_shm(void *ctx)
{
	uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
	uint64_t dst_addr   = DCL0_SH_MEM_BASE_CL;     // SHM base
	uint32_t trs_size   = SZ_4M;                // trs size is 4MB
	uint32_t task_id    = 0xDD3A0000;
	int ret = false;

	RLOG_INFO("%s\r\n", __func__);
	rand_fill((void *)src_addr, trs_size);

	RLOG_INFO("\r\n[dram -> dcl0_shm]\r\n");
	for (int i = 0; i < HW_SPEC_DNC_COUNT/2; i++)
		generate_rbdma_task(task_id | i<<12, src_addr, dst_addr + i*SZ_4M, trs_size, 0);

	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT/2);
	rbdma_done_clear(cur_cl_id);

	src_addr = DATA_MEM_BASE_ADDR;
	for (int i = 0; i < HW_SPEC_DNC_COUNT / 2; i++) {
		ret = basic_test_compare(src_addr, DCL0_SH_MEM_BASE_CL + i * SZ_4M, SZ_4M);
		if (ret < 0)
			return false;
	}

	RLOG_INFO("\r\n[dcl_0_shm -> dcl1_1_shm]\r\n");
	src_addr = DCL0_SH_MEM_BASE_CL;
	dst_addr = DCL1_SH_MEM_BASE_CL;
	for (int i = 0; i < HW_SPEC_DNC_COUNT/2; i++)
		generate_rbdma_task(task_id | i<<12, src_addr + i*SZ_4M, dst_addr + i*SZ_4M, trs_size, 0);

	rbdma_done_acc_count(cur_cl_id, HW_SPEC_DNC_COUNT/2);
	rbdma_done_clear(cur_cl_id);

	/* compare */
	src_addr = DCL0_SH_MEM_BASE_CL;
	dst_addr = DCL1_SH_MEM_BASE_CL;
	for (int i = 0; i < HW_SPEC_DNC_COUNT / 2; i++) {
		ret = basic_test_compare(src_addr + i * SZ_4M, dst_addr + i * SZ_4M, SZ_4M);
		if (ret < 0)
			return false;
	}

	return 1;
}

#ifndef POWER_MODE_TEST
int rbdma_dram_2_shm_tsync(void *ctx)
{
	uint32_t trs_size = SZ_32M;
	uint64_t src_addr0 = DATA_MEM_BASE_ADDR;
	uint64_t dst_addr0 = DCL0_SH_MEM_BASE_CL;
	uint64_t src_addr1 = DATA_MEM_BASE_ADDR + SZ_32M;
	uint64_t dst_addr1 = DCL1_SH_MEM_BASE_CL;
	uint32_t prev_global_config_cdma_opmode0_bits = 0;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr0, trs_size);
	rand_fill((void *)src_addr1, trs_size);

	prev_global_config_cdma_opmode0_bits = rbdma_get_global_config_cdma_opmode0();
	rbdma_set_max_perf_mode(0x7);

	RLOG_INFO("\r\n[dram -> dcl0_shm & dcl1_shm]\r\n");
	generate_rbdma_task_tsync(0xDD3A0000, src_addr0, dst_addr0, trs_size, 0x7, 0, 0xf, 1);
	generate_rbdma_task_tsync(0xDD3A0001, src_addr1, dst_addr1, trs_size, 0x7, 0, 0xf0, 0);

	rbdma_tsync_by_cp();
	rbdma_done_acc_count(cur_cl_id, 2);
	rbdma_done_clear(cur_cl_id);

	rbdma_set_global_config_cdma_opmode0(prev_global_config_cdma_opmode0_bits);

	if (basic_test_compare(src_addr0, dst_addr0, trs_size) < 0)
		return false;
	if (basic_test_compare(src_addr1, dst_addr1, trs_size) < 0)
		return false;

	return true;
}

int rbdma_shm_2_dram_tsync(void *ctx)
{
	uint32_t trs_size = SZ_32M;
	uint64_t src_addr0 = DCL0_SH_MEM_BASE_CL;
	uint64_t dst_addr0 = DATA_MEM_BASE_ADDR;
	uint64_t src_addr1 = DCL1_SH_MEM_BASE_CL;
	uint64_t dst_addr1 = DATA_MEM_BASE_ADDR + SZ_32M;
	uint32_t prev_global_config_cdma_opmode0_bits = 0;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr0, trs_size);
	rand_fill((void *)src_addr1, trs_size);

	prev_global_config_cdma_opmode0_bits = rbdma_get_global_config_cdma_opmode0();
	rbdma_set_max_perf_mode(0x7);

	RLOG_INFO("\r\n[dcl0_shm & dcl1_shm -> dram]\r\n");
	generate_rbdma_task_tsync(0xDD3A0000, src_addr0, dst_addr0, trs_size, 0x7, 0, 0xf, 1);
	generate_rbdma_task_tsync(0xDD3A0001, src_addr1, dst_addr1, trs_size, 0x7, 0, 0xf0, 0);
	rbdma_tsync_by_cp();
	rbdma_done_acc_count(cur_cl_id, 2);
	rbdma_done_clear(cur_cl_id);

	rbdma_set_global_config_cdma_opmode0(prev_global_config_cdma_opmode0_bits);

	if (basic_test_compare(src_addr0, dst_addr0, trs_size) < 0)
		return false;
	if (basic_test_compare(src_addr1, dst_addr1, trs_size) < 0)
		return false;

	return true;
}
#else
int rbdma_dram_2_shm_tsync(void *ctx)
{
	uint32_t trs_size = SZ_32M;
	uint64_t src_addr0 = DATA_MEM_BASE_ADDR;
	uint64_t dst_addr0 = DCL0_SH_MEM_BASE_CL;
	uint64_t src_addr1 = DATA_MEM_BASE_ADDR + SZ_32M;
	uint64_t dst_addr1 = DCL1_SH_MEM_BASE_CL;
	uint32_t prev_global_config_cdma_opmode0_bits = 0;
	uint32_t queue_left = 0;
	uint32_t total = 0;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr0, trs_size);
	rand_fill((void *)src_addr1, trs_size);

	pwr_gpio_set();

	prev_global_config_cdma_opmode0_bits = rbdma_get_global_config_cdma_opmode0();
	rbdma_set_max_perf_mode(0x7);

	for (int j = 0; j < 3000000; j++) {
		queue_left = rbdma_global_normal_queue_status_cl(0);
		if (queue_left > 2) {
			total++;
		/*
		 * 2025-10-01, te 0x33, 0xcc, sp_granule = (7 + 1) x (7 + 1) x 32KB = 2MB
		 */
			generate_rbdma_perf_task(0xDD3A0000 + total*2,
				src_addr0, dst_addr0, trs_size, 0x33, 0x7, 0);
			generate_rbdma_perf_task(0xDD3A0001 + total*2,
				src_addr1, dst_addr1, trs_size, 0xcc, 0x7, 0);
		}
	}
	while (rbdma_global_normal_queue_status_cl(0) != 64)
		; /* wait until queue status becomes max available */
//	printf("--> 0x%08x , total:%d\r\n", rbdma_global_idle_status_cl(0), total*2);
	while (rbdma_global_idle_status_cl(0) != 0xFF)
		; /* wait until queue status becomes idle state */
	pwr_gpio_unset();
	rbdma_done_clear(0);

	rbdma_set_global_config_cdma_opmode0(prev_global_config_cdma_opmode0_bits);

	return true;
}

int rbdma_shm_2_dram_tsync(void *ctx)
{
	uint32_t trs_size = SZ_32M;
	uint64_t src_addr0 = DCL0_SH_MEM_BASE_CL;
	uint64_t dst_addr0 = DATA_MEM_BASE_ADDR;
	uint64_t src_addr1 = DCL1_SH_MEM_BASE_CL;
	uint64_t dst_addr1 = DATA_MEM_BASE_ADDR + SZ_32M;
	uint32_t prev_global_config_cdma_opmode0_bits = 0;
	uint32_t queue_left = 0;
	uint32_t total = 0;

	RLOG_INFO("%s\r\n", __func__);

	rand_fill((void *)src_addr0, trs_size);
	rand_fill((void *)src_addr1, trs_size);

	pwr_gpio_set();

	prev_global_config_cdma_opmode0_bits = rbdma_get_global_config_cdma_opmode0();
	rbdma_set_max_perf_mode(0x7);

	for (int j = 0; j < 1000000; j++) {
		queue_left = rbdma_global_normal_queue_status_cl(0);
		if (queue_left > 2) {
			total++;
			/*
			 * 2025-10-01, te 0x33, 0xcc, sp_granule = (7 + 1) x (7 + 1) x 32KB = 2MB
			 */
			generate_rbdma_perf_task(0xDD3A0000 + total*2,
				src_addr0, dst_addr0, trs_size, 0x33, 0x7, 0);
			generate_rbdma_perf_task(0xDD3A0001 + total*2,
				src_addr1, dst_addr1, trs_size, 0xcc, 0x7, 0);
		}
	}
	while (rbdma_global_normal_queue_status_cl(0) != 64)
		; /* wait until queue status becomes max available */
	printf("--> 0x%08x , total:%d\r\n", rbdma_global_idle_status_cl(0), total*2);
	while (rbdma_global_idle_status_cl(0) != 0xFF)
		; /* wait until queue status becomes idle state */
	dsb();
	pwr_gpio_unset();
	rbdma_done_clear(0);

	rbdma_set_global_config_cdma_opmode0(prev_global_config_cdma_opmode0_bits);

	return true;
}
#endif

int ucie_sanity_test(void *ctx)
{
	const char *dram_marker = "UCIE_SANITY_TEST";
	const char *reg_marker = "UCIE";
	const uint32_t test_size = SZ_1M;
	int chip_id = get_chiplet_id();
	struct ici_chip_sorting_entry entry = {0};
	int cmp_result[4];
	int result;
	int i;

	if (chiplet_count_opt != MAX_CHIPLET_COUNT) {
		printf("Skip UCIe Sanity Test (Single Chiplet)\n");
		return true;
	}

	RLOG_INFO("%s\r\n", __func__);
	cpu_inv_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR, test_size);

	if (chip_id == 0) {
		ici_send_sync_event(1);
		ici_send_sync_event(2);
		ici_send_sync_event(3);
		ici_sync_receive_polling(1);
		ici_sync_receive_polling(2);
		ici_sync_receive_polling(3);

		rand_fill((void *)DATA_MEM_BASE_ADDR, test_size);
		for (i = 1; i < 4; i++) {
			memcpy((void *)(DATA_MEM_BASE_ADDR_CL(i)), (void *)DATA_MEM_BASE_ADDR_CL(0), test_size);
			cpu_flush_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR_CL(i), test_size);
		}

		for (i = 0; i < 4; i++) {
			snprintf((char *)DATA_MEM_BASE_ADDR_CL(i), strlen(dram_marker), "%s", dram_marker);
			cpu_flush_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR_CL(i), test_size);
		}
		RLOG_INFO("Write DRAM Data Done\r\n");

		while (1) {
			result = true;

			for (i = 1; i < 4; i++) {
				cpu_inv_dcache_range((uintptr_t)(DATA_MEM_BASE_ADDR_CL(0) + i * test_size),
									 test_size);
				cmp_result[i] = memcmp((void *)DATA_MEM_BASE_ADDR_CL(0),
									   (void *)(DATA_MEM_BASE_ADDR_CL(0) + i * test_size),
									   test_size - 1);
				RLOG_INFO("%p vs %p -> result %d\r\n", (void *)DATA_MEM_BASE_ADDR_CL(0),
						  (void *)(DATA_MEM_BASE_ADDR_CL(0) + i * test_size),
						  cmp_result[i]);
			}

			for (i = 1; i < 4; i++) {
				if (cmp_result[i] != 0)
					result = false;
			}
			if (result == true)
				break;
		}
		RLOG_INFO("Readback DRAM Done\r\n");

		memcpy(entry.arg, reg_marker, strlen(reg_marker));
		write_entry(1, &entry);
		write_entry(2, &entry);
		write_entry(3, &entry);
		RLOG_INFO("Write Register Done\r\n");

		while (1) {
			result = true;

			for (i = 1; i < 4; i++) {
				read_inst_entry(i, 0, &entry);
				RLOG_INFO("chiplet: %d\r\n", i);
				print_ici_chip_sorting_entry(&entry);
				if (entry.arg[i] != (i + '0')) {
					result = false;
					break;
				}
			}
			if (result == true)
				break;
		}
		RLOG_INFO("Readback Register Done\r\n");
	} else {
		ici_wait_sync_event();
		ici_sync_message_clear();

		RLOG_INFO("DATA_MEM_BASE_ADDR: %p\r\n", (void *)(DATA_MEM_BASE_ADDR));
		while (memcmp((void *)(DATA_MEM_BASE_ADDR), dram_marker, strlen(dram_marker) - 1) != 0) {
			RLOG_INFO("memcmp fail.. polling...\r\n");
			cpu_inv_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR, test_size);
		}
		RLOG_INFO("DRAM Polling Done\r\n");

		memcpy((void *)(DATA_MEM_BASE_ADDR_CL(0) + chip_id * test_size),
			   (void *)(DATA_MEM_BASE_ADDR),
			   test_size);
		cpu_flush_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR_CL(0) + chip_id * test_size,
							   test_size);
		RLOG_INFO("DRAM Writeback Done\r\n");

		while (1) {
			read_entry(chip_id, &entry);
			print_ici_chip_sorting_entry(&entry);
			if (memcmp(entry.arg, reg_marker, strlen(reg_marker)) == 0)
				break;
		}
		RLOG_INFO("Register Polling Done\r\n");

		entry.arg[chip_id] = chip_id + '0';
		write_entry(0, &entry);
		print_ici_chip_sorting_entry(&entry);
		RLOG_INFO("Register Writeback Done\r\n");
	}
	memset((void *)DATA_MEM_BASE_ADDR, 0, strlen(dram_marker));
	cpu_flush_dcache_range(DATA_MEM_BASE_ADDR, strlen(dram_marker));

	return true;
}

static uint8_t basic_test(int argc, char *argv[])
{
	int num_of_test = ARRAY_SIZE(item_list);
	int idx = 0;
	int is_test_all = 0;
	int test_result = true;
	int loop = 1;
	int ret = 0;
	char result_string[20];

	printf("%s\r\n", __func__);
	RLOG_INFO("%s\r\n", __func__);

#if defined(POWER_MODE_TEST)
	*GPIO_TEST_CON = 0x11111111;
#endif /* #if defined(POWER_MODE_TEST) */

	if (argc == 0) {
		printf("%s {index} {iteration count}\r\n", __func__);
		test_result = false;
	}
	if (argc >= 1) {
		if ((strcmp(argv[0], "all") == 0) || (strcmp(argv[0], "ALL") == 0))
			is_test_all = 1;
		else {
			is_test_all = 0;
			idx = atoi(argv[0]);
			if (idx <= 0 || idx >= num_of_test) {
				printf("!!! check test list number !!!\r\n");
				test_result = false;
			}
		}
	}
	if (argc >= 2)
		loop = atoi(argv[1]);
	if (test_result == false) {
		snprintf((char *)ITER_RESULT_ADDR, 100, "[TEST FAIL] Basic Test \r\n");
		printf("%s\r\n", (char *)ITER_RESULT_ADDR);
		cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
		return false;
	}

	if (is_test_all == 1) {
		printf("------------------------------------------------------------------\r\n");
		printf(" %-7s | %-40s | %s\r\n", "Test ID", "Function Name", "Result");
		printf("------------------------------------------------------------------\r\n");
		passed_count = 0;
		failed_count = 0;

		for (int i = 1; i < num_of_test; i++) {
			int cnt = 0;

			for (cnt = 0; cnt < loop; cnt++) {
			#if defined(POWER_MODE_TEST)
				pwr_gpio_set();
			#endif /* #if defined(POWER_MODE_TEST) */

				test_exception_clear();
				ret = item_list[i].pfunc(&item_list[i]);
				dsb();
				if (test_exception_occurred()) {
					RLOG_ERR("[FAIL] Exception occurred during %s\r\n",
						 item_list[i].function_name);
					ret = false;
				}
				if (!ret)
					break;
			}
			snprintf(result_string, sizeof(result_string), "%s (%d/%d)", ret ? "PASS" : "FAIL", cnt, loop);
			printf(" %-7.02d | %-40s | %s\r\n",
				item_list[i].function_id,
				item_list[i].function_name,
				result_string);
			if (!ret) {
				failed_count++;
				test_result = false;
				#if defined(POWER_MODE_TEST)
					pwr_gpio_unset();
				#endif /* #if defined(POWER_MODE_TEST) */
			} else
				passed_count++;
				#if defined(POWER_MODE_TEST)
					pwr_gpio_unset();
				#endif /* #if defined(POWER_MODE_TEST) */
		}
		printf("------------------------------------------------------------------\r\n");
		printf(" Summary : (%d/%d) Passed, (%d) Failed\r\n",
			passed_count, num_of_test-1, failed_count);
		printf("------------------------------------------------------------------\r\n");
	} else {
		int cnt;

		printf(" %-7.02d | %-40s |\r\n",
			item_list[idx].function_id,
			item_list[idx].function_name);
		for (cnt = 0; cnt < loop; cnt++) {
			test_exception_clear();
			test_result = item_list[idx].pfunc(&item_list[idx]);
			dsb();
			if (test_exception_occurred()) {
				RLOG_ERR("[FAIL] Exception occurred during %s\r\n",
					 item_list[idx].function_name);
				test_result = false;
			}
			if (!test_result)
				break;
		}
		snprintf(result_string, sizeof(result_string), "%s (%d/%d)", test_result ? "PASS" : "FAIL", cnt, loop);
		log_test_result("UNIT", item_list[idx].function_name, result_string);
	}

#if defined(POWER_MODE_TEST)
	pwr_gpio_unset();
#endif /* #if defined(POWER_MODE_TEST) */

	if (test_result == true) {
		snprintf((char *)ITER_RESULT_ADDR, 100, "[TEST PASS] Basic Test\r\n");
		printf("%s", (char *)ITER_RESULT_ADDR);
	} else {
		snprintf((char *)ITER_RESULT_ADDR, 100, "[TEST FAIL] Basic Test \r\n");
		printf("%s\r\n", (char *)ITER_RESULT_ADDR);
	}
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);

	return test_result;
}

enum pkt_type {
	PKT_DNC_URQ,
	PKT_DNC_TASK,
	PKT_RBDMA_URQ,
	PKT_RBDMA_TASK,
	PKT_SKIP,
};

#define SYNC_NC_BASE_ADDR		(0x3DC00000ULL)
#define DDMA_SUBTASK_ID_MASK 0x03FF
#define DDMA_SUBTASK_ID_MIN 0xFC00
#define DDMA_SUBTASK_ID_MAX 0xFFFF
#define FIRST_SG_CMD_OR_NON_SG_CMD	0
#define MIDDLE_SG_CMD				1
#define LAST_SG_CMD					2
/* COMPUTE=0, LD=1, LP=2. COMPUTE has GSN dependency and HW queue often empty; LD/LP saturated */
#define STRM_COMPUTE					0
#define CLR_BIT(v, i)			RL_CLR_BIT(v, i)

//static volatile uint32_t *pktdump_ptr;
static int processing_sg_ddma;

/* Quad replay global variables */
static volatile int qr_ready[4];
static volatile bool qr_task1_init_done;
static struct rl_entry qrs_entry[MAX_CHIPLET_COUNT];
static uint64_t start_cycle;

static volatile uint32_t *pktdump_strm_ptr[STRM_COUNT][HW_SPEC_DNC_COUNT];
static volatile uint32_t gsn_done_board[GSN_WINDOW_SIZE];
static uint32_t gsn_of_cmd[DDMA_SUBTASK_ID_MAX + 1];
static uint8_t sg_pos_of_cmd[DDMA_SUBTASK_ID_MAX + 1];

/* EOCS Barrier for back-to-back stream synchronization (NC Shared Memory) */
static volatile uint32_t *global_eocs_done_cnt;
static volatile uint32_t *total_streams_to_replay;
/* CONTROL: gsn_dependency only after RBDMA DUMP_END (per-chiplet; RBDMA sets, CONTROL reads) */
static volatile uint32_t rbdma_reached_dump_end;
static volatile uint32_t quit_replay;
static volatile int *qr_processing[MAX_CHIPLET_COUNT][4];

static volatile uint32_t next_gsn_to_process = 1;
#ifdef QREPLAY_DEBUG
static volatile uint32_t *global_replay_resume_trigger;
static uint32_t send_cid[STRM_COUNT];
static uint32_t last_done[STRM_COUNT];
#endif

/* Hardware credit variables */
static uint8_t dnc_credit[HW_SPEC_DNC_QUEUE_NUM][HW_SPEC_DNC_COUNT];
static uint8_t ddma_task_credit;
static uint8_t ddma_task_ext_credit;
//static uint8_t ddma_turq_credit;

static uint32_t cmd_done_cnt;
struct psg { uint32_t d[8]; };

static uint32_t send_control_packets(volatile uint32_t *pkt_stream, int cmd_type)
{
	volatile uint32_t *origin_ptr = pkt_stream;
	volatile uint32_t *cur_ptr	= pkt_stream;

	cur_ptr++;					/* type */
	uint32_t pkt_cnt			= *cur_ptr++;
	uint64_t pkt_data_ptr		= (uint64_t)cur_ptr;
	uint32_t num_records = pkt_cnt / 2;
	uint32_t i = 0;

//	smmu_pmu_print_enabled_cnt();

	if (num_records >= 8) {
		/* 1. Write individual packets before the last 8 */
		for (; i < num_records - 8; i++, pkt_data_ptr += 16) {
			uint64_t addr = *(uint64_t *)pkt_data_ptr;
			uint32_t data = *(uint32_t *)(pkt_data_ptr + 0x8);
			*(volatile uint32_t *)addr = data;
		}

		/* 2. Prepare and write the last 8 packets as a 32-byte block */
		uint64_t base_addr = *(uint64_t *)pkt_data_ptr;
		struct psg psg;

		for (int j = 0; j < 8; j++) {
			uint32_t data = *(uint32_t *)(pkt_data_ptr + j * 16 + 0x8);
	#ifdef REPLAY_WORKER_SMMU_DEBUG
			uint64_t addr = *(uint64_t *)(pkt_data_ptr + j * 16);

			if ((addr & 0xFFF) == 0x804)
				data |= (1 << 4);
	#endif
			psg.d[j] = data;
	#ifdef REPLAY_WORKER_SMMU_DEBUG
			if (j == 1 || j == 2) {
				va = (uint64_t)data << 7;
				pa = ptw_virt_to_phys(va, (uint64_t *)0x51800000, &id_info);
				printf("[%s] va=%#lx, pa=%#lx\r\n", __func__, va, pa);
				if (j == 2)
					psg.d[j] = 0x23a78001;
			}
			if (j == 3)
				psg.d[j] = 0x1;
	#endif
		}
		*(volatile struct psg *)base_addr = psg;
		i = num_records;
	}
	pkt_stream += pkt_cnt * 2 + 2;

	return pkt_stream - origin_ptr;
}

/* Quad Replay: GSN dependency checking */
static bool check_gsn_dependency(uint32_t cur_gsn, uint32_t wait_cnt, volatile uint32_t *distances)
{
	for (uint32_t i = 0; i < wait_cnt; i++) {
		uint32_t target_gsn = cur_gsn - distances[i];
		uint32_t done_gsn = __atomic_load_n(&gsn_done_board[target_gsn % GSN_WINDOW_SIZE], __ATOMIC_ACQUIRE);

		/* Check if target_gsn is finished using 32-bit wrap-around safe comparison */
		if ((int32_t)(done_gsn - target_gsn) < 0)
			return false;
	}
	return true;
}

/* Quad Replay: Hardware credit management functions */
static bool is_hw_credit_available(int q, int i, int credit_required)
{
	if (dnc_credit[q][i] < credit_required) {
		dnc_update_credit(i, &dnc_credit[0][i], &dnc_credit[1][i],
				&dnc_credit[2][i], &dnc_credit[3][i]);
	}
	bool available = (dnc_credit[q][i] >= credit_required);

//	if (!available) {
//		RLOG_DBG("[CREDIT] cl%u DNC q%u d%u: INSUFFICIENT credit=%u, required=%u\r\n",
//		       cur_cl_id, q, i, dnc_credit[q][i], credit_required);
//	}

	return available;
}

static void consume_dnc_hw_credit(int q, int i, int credit_required)
{
	dnc_credit[q][i] -= credit_required;
}

static void consume_rbdma_hw_credit(int credit_required)
{
	ddma_task_credit--;
	ddma_task_ext_credit -= credit_required;
}

static uint32_t get_dnc_gsn_credit(volatile uint32_t *pkt_stream)
{
	uint32_t pkt_cnt = pkt_stream[1];
	uint32_t records = pkt_cnt / 2;
	uint32_t credit = 1;

	if (records > 8)
		credit += (records - 8);

	return credit;
}

static uint32_t get_rbdma_ext_gsn_credit(volatile uint32_t *pkt_stream)
{
	uint32_t pkt_cnt = pkt_stream[1];
	uint32_t records = pkt_cnt / 2;

	return records - 8;
}

static int update_ddma_credit(uint8_t task_required, uint8_t ext_entry_required)
{
	if (ddma_task_credit < task_required ||
		ddma_task_ext_credit < ext_entry_required) {
		rbdma_update_credit(&ddma_task_credit, &ddma_task_ext_credit, true);
	}

	/* Check if # of tlb entries available are enough to accept tlb transferred */
	if (task_required <= ddma_task_credit &&
		ext_entry_required <= ddma_task_ext_credit) {
		ddma_task_credit -= task_required;
		ddma_task_ext_credit -= ext_entry_required;
		return 0;
	}

	RLOG_DBG("[CREDIT] cl%u RBDMA: INSUFFICIENT task=%u (req=%u), ext=%u (req=%u)\r\n",
	       cur_cl_id, ddma_task_credit, task_required,
	       ddma_task_ext_credit, ext_entry_required);
	return -1;
}
#if (0)
static uint32_t check_dep(struct replay_cmd_info *cmd_info)
{
	uint64_t mask;

	/* Special case for a dep. mask of "0" */
	if (cmd_info->dep_slot_id_mask == 0x0) {
		/*  Always pass the dependency test */
		if (cmd_info->dep_slot_id_ref_cnt == 0x0)
			return 1;

		/* Dep slot ID is not available since it is referenced by other commands */
		if (replay_dep_slot.ref_cnt[cmd_info->dep_slot_id] != 0x0)
			return 0;
		else
			return 1;
	}

	/* General case */
	mask = replay_dep_slot.mask;

	if ((mask & cmd_info->dep_slot_id_mask) == 0x0) {
		/* Pre-processing to check if all the dependency bit are ready */
		uint64_t dm = cmd_info->dep_slot_id_mask;

		while (dm) {
			int i = __builtin_ffsll(dm) - 1;

			if (replay_dep_slot.ref_cnt[i] == 0)
				return 0;

			RL_CLR_BIT64(dm, i);
		}

		/* processing to update the dependency slot */
		dm = cmd_info->dep_slot_id_mask;
		while (dm) {
			int i = __builtin_ffsll(dm) - 1;

			replay_dep_slot.ref_cnt[i]--;
			RL_CLR_BIT64(dm, i);
		}
		return 1;
	} else { /* Failed to pass the dependency of an incoming command */
		return 0;
	}
}

static inline bool need_check_dep(uint64_t dep_slot_id_mask)
{
	/*
	 * If a task don't need to check get dependency,
	 * but needs to put dependency, dependency slot mask is dumped as UINT64_MAX.
	 * The last sg ddma subtask corresponds to this case.
	 */
	if (dep_slot_id_mask == INVALID_DEP_SLOT_MASK)
		return false;

	return true;
}
#endif

static int replayer_compare(uintptr_t addr1, uintptr_t addr2, uint32_t size)
{
	volatile uint32_t *p_result = (volatile uint32_t *)addr1;
	volatile uint32_t *p_golden = (volatile uint32_t *)addr2;

	cpu_inv_dcache_range((uintptr_t)addr1, size);
	cpu_inv_dcache_range((uintptr_t)addr2, size);

	for (int i = 0; i < size/sizeof(uint32_t); i++) {
		if (*p_result != *p_golden) {
			printf("--------------------------------------------------\r\n");
			printf("The value is different %#x(result) %#x(golden) , addr is %#lx\r\n",
					*p_result,
					*p_golden,
					addr1 + i*4);
			printf("--------------------------------------------------\r\n");
			return -1;
		}
		p_result++;
		p_golden++;
	}
	return 0;
}

void trace_cmd_identify(int cmd_id)
{
	RLOG_INFO("cmd_id %d\r\n", cmd_id);

#ifdef ENABLE_WAIT_ERUN
	dnc_get_status_registers();
#endif

	printf(".");
}

#ifdef ENABLE_WAIT_ERUN
//-------------------------------------------------------------------------------
const volatile uintptr_t dnc_reg_base[16] = {
	(const volatile uintptr_t) 0x1FF2000000, // 00
	(const volatile uintptr_t) 0x1FF2002000, // 01
	(const volatile uintptr_t) 0x1FF2004000, // 02
	(const volatile uintptr_t) 0x1FF2006000, // 03
	(const volatile uintptr_t) 0x1FF2008000, // 04
	(const volatile uintptr_t) 0x1FF200A000, // 05
	(const volatile uintptr_t) 0x1FF200C000, // 06
	(const volatile uintptr_t) 0x1FF200E000, // 07

	(const volatile uintptr_t) 0x1FF2800000, // 08
	(const volatile uintptr_t) 0x1FF2802000, // 09
	(const volatile uintptr_t) 0x1FF2804000, // 10
	(const volatile uintptr_t) 0x1FF2806000, // 11
	(const volatile uintptr_t) 0x1FF2808000, // 12
	(const volatile uintptr_t) 0x1FF280A000, // 13
	(const volatile uintptr_t) 0x1FF280C000, // 14
	(const volatile uintptr_t) 0x1FF280E000, // 15
};

static uint32_t get_rbdma_counter(void)
{
	const volatile uintptr_t rbdma_base_addr = 0x1FF3700000;
	const volatile uintptr_t clog_num_nrm_tdone_tstc0 = 0x404;

	return *(volatile uint32_t *)(rbdma_base_addr + clog_num_nrm_tdone_tstc0);
}

static void wait_rbdma_finish(uint32_t done_counter)
{
	uint32_t next_done_counter;
	int loop_counter = 0;

	for (loop_counter = 0; ; loop_counter++) {
		next_done_counter = get_rbdma_counter();
		if (next_done_counter - done_counter >= 1)
			break;
	}
}

static uint32_t get_dnc_counter(void)
{
	const volatile uintptr_t COMP_acc2          = 0x4C8;
	const volatile uintptr_t LDuDMA_acc2        = 0x4E8;
	uint32_t sum = 0;
	int i;

	for (i = 0; i < 16; i++) {
		sum = sum + *(volatile uint32_t *)(dnc_reg_base[i] + COMP_acc2);
		sum = sum + *(volatile uint32_t *)(dnc_reg_base[i] + LDuDMA_acc2);
	}
	return sum;
}

static void trigger_and_wait_dnc_finish(uint32_t done_counter)
{
	const volatile uintptr_t q_status_comp      = 0x580;
	const volatile uintptr_t q_status_ldudma    = 0x584;
	const volatile uintptr_t trig               = 0x834;

	volatile int loop_counter = 0;
	int i;
	int trig_offset = 0;
	int is_waiting_comp_cnt = 0;
	int is_waiting_ldudma_cnt = 0;

	loop_counter = 0;
	is_waiting_comp_cnt = 0;
	is_waiting_ldudma_cnt = 0;
	for (loop_counter = 0; ; loop_counter++) {
		is_waiting_comp_cnt = 0;
		is_waiting_ldudma_cnt = 0;
		for (i = 0; i < 16; i++) {
			is_waiting_comp_cnt     += ((*(volatile uint32_t *)(dnc_reg_base[i] + q_status_comp)) >> 0x6) & 0x1;
			is_waiting_ldudma_cnt   += ((*(volatile uint32_t *)(dnc_reg_base[i] + q_status_ldudma)) >> 0x6) & 0x1;
		}

		if (is_waiting_comp_cnt == 16) {
			trig_offset = 4;
			break;
		} else if (is_waiting_ldudma_cnt == 16) {
			trig_offset = 5;
			break;
		}
	}
	for (i = 0; i < 16; i++) {
		*(volatile uint32_t *)(dnc_reg_base[i] + trig) = (0x1 << trig_offset);
		//    RLOG_DBG("[%#llx] = %#lx\r\n", dnc_reg_base[i] + trig, 0x1 << trig_offset);
	}
	for (loop_counter = 0; ; loop_counter++) {
		if (get_dnc_counter() - done_counter)
			break;
	}
}
//--------------------------------------------------------------------------------
#endif

#ifdef SHM_SP_DUMP_PER_STREAM
void rbdma_shm_dump(uint32_t num)
{
	// d.save.b ./shm_contents.bin AZNC:0x900000000++0x40000000
	const volatile uintptr_t rbdma_base_addr = 0x1FF3700000;
	const volatile uintptr_t td_ptid_init = 0x200;
	const volatile uintptr_t td_srcaddress_or_const = 0x204;
	const volatile uintptr_t td_destaddress = 0x208;
	const volatile uintptr_t td_sizeof128block = 0x20C;
	const volatile uintptr_t td_run_conf0 = 0x218;
	const volatile uintptr_t td_run_conf1 = 0x21C;
	const volatile uintptr_t global_fnsh_intr_fifo = 0x128;

	volatile uint32_t counter_value = 0x0;

	char bin_file_name[40];
	volatile int break_here = 0;

	*(volatile uint32_t *)(rbdma_base_addr + td_ptid_init) = (0xF000 + num);
	*(volatile uint32_t *)(rbdma_base_addr + td_srcaddress_or_const) = (0x1FE4000000 >> 7);
	*(volatile uint32_t *)(rbdma_base_addr + td_destaddress) = (0x790000000 >> 7);
	*(volatile uint32_t *)(rbdma_base_addr + td_sizeof128block) = 0x80000;
	*(volatile uint32_t *)(rbdma_base_addr + td_run_conf0) = 0x0;
	*(volatile uint32_t *)(rbdma_base_addr + td_run_conf1) = 0xFA0009;
	while (1) {
		counter_value = *(volatile uint32_t *)(rbdma_base_addr + global_fnsh_intr_fifo);
		if (counter_value == (0xF000 + num))
			break;
	}
	snprintf(bin_file_name, sizeof(bin_file_name), "./shm_dump_%05d.bin", num);
	break_here = 1;
}

void rbdma_sp_dump(uint32_t num)
{
	// d.save.b ./sp_contents.bin AZNC:0x900000000++0x40000000
	const volatile uintptr_t rbdma_base_addr = 0x1FF3700000;
	const volatile uintptr_t td_ptid_init = 0x200;
	const volatile uintptr_t td_srcaddress_or_const = 0x204;
	const volatile uintptr_t td_destaddress = 0x208;
	const volatile uintptr_t td_sizeof128block = 0x20C;
	const volatile uintptr_t td_run_conf0 = 0x218;
	const volatile uintptr_t td_run_conf1 = 0x21C;
	const volatile uintptr_t global_fnsh_intr_fifo = 0x128;

	char bin_file_name[40];
	volatile int break_here = 0;

	*(volatile uint32_t *)(rbdma_base_addr + td_ptid_init) = (0xF0F0 + num);
	*(volatile uint32_t *)(rbdma_base_addr + td_srcaddress_or_const) = (0x1FE0000000 >> 7);
	*(volatile uint32_t *)(rbdma_base_addr + td_destaddress) = (0x790000000 >> 7);
	*(volatile uint32_t *)(rbdma_base_addr + td_sizeof128block) = 0x80000;
	*(volatile uint32_t *)(rbdma_base_addr + td_run_conf0) = 0x0;
	*(volatile uint32_t *)(rbdma_base_addr + td_run_conf1) = 0xFA0009;
	while (1) {
		if ((*(volatile uint32_t *)(rbdma_base_addr + global_fnsh_intr_fifo)) == (0xF0F0 + num))
			break;
	}

	snprintf(bin_file_name, sizeof(bin_file_name), "./sp_dump_%05d.bin", num);
	break_here = 1;
}
#endif

#ifdef PROFILE_ENABLE
static void log_mgr_store_exetime_rbdma(void *ptr, int cnt)
{
	struct log_mgr_entry *entry = (struct log_mgr_entry *)ptr;
	union exec_id id;
	int evt_id;

	for (int i = 0; i < cnt; i++) {
		id.bits = entry[i].exec_id;
		evt_id = __builtin_ffs(entry[i].evt_code) - 1;
		rl_profile_hwcounter(evt_id, entry[i].cycle_cnt, entry[i].exec_id, 16, COMMON_CMD_TYPE_DDMA);
	}

}
static void log_mgr_store_exetime_dnc(int dnc_id, void *ptr, int cnt)
{
	struct dnc_profile_entry *entry = (struct dnc_profile_entry *)ptr;
	union exec_id id;
	uint64_t que_t, pre_t, run_t;

	for (int i = 0; i < cnt; i++) {
		id.bits = entry[i].exec_id;
		que_t = entry[i].queueing_time;
		pre_t = entry[i].pre_time;
		run_t = entry[i].run_time;
		//RLOG_DBG("cid[%d] %lld\r\n", id.cmd_id, entry[i].run_time);
		rl_profile_hwcounter(DNC_QUEUE_TIME, que_t, entry[i].exec_id, dnc_id, 0);
		rl_profile_hwcounter(DNC_PRE_TIME, pre_t, entry[i].exec_id, dnc_id, 0);
		rl_profile_hwcounter(DNC_RUN_TIME, run_t, entry[i].exec_id, dnc_id, 0);
	}
}

static void get_profile_data(uint32_t cs_start_cycle)
{
	log_mgr_store_exetime_rbdma((void *)(RBDMA_PROFILE_BASE_ADDR), rbdma_logmgr_get_dump_count());
	int i;

	for (i = 0; i < 16; i++)
		log_mgr_store_exetime_dnc(i, DNC_PROFILE_PTR(i), DNC_PROFILE_GET_COUNT(i));
}
#endif

static int run_replayer(uint64_t result_addr, uint64_t golden_addr, uint32_t output_size)
{
#if (0)
	int cmd_cnt                = *pktdump_ptr;
	volatile uint32_t *cur_ptr = pktdump_ptr + 2;
	struct replay_cmd_info *cmd_info;
	int set_dep_id;
	int cmd_id;
	uint32_t type = 0;
	int is_test_passed = 0;

	printf("replay START!!!\r\n");

	while (1) {
		if (*cur_ptr++ != COMMAND_START) {
			RLOG_ERR("cmd does not start with COMMAND_START(0x1234), cur_ptr: %#llx\r\n", cur_ptr);
			RLOG_ERR("replayer is terminated due to abnormal pktdump.\r\n");
			break;
		}

		cmd_id = *cur_ptr++;
		//trace_cmd_identify(cmd_id);

		/* New sg ddma command can be started when all previous sg-ddma subtasks have completed */
		if (cmd_id == RBDMA_SUBTASK_ID_MIN) {
			while (processing_sg_ddma == 1)
				__asm__ volatile("nop");

			processing_sg_ddma = 1;
		}

		/* get depndency data */
		cmd_info                      = &replay_cmd_info[cmd_id];
		cmd_info->dep_slot_id         = *cur_ptr++;
		cmd_info->dep_slot_id_ref_cnt = *cur_ptr++;
		cmd_info->dep_slot_id_mask    = *(volatile uint64_t *)cur_ptr;
		cur_ptr += 2;
#ifdef PROFILE_ENABLE
		rl_profile_log_start(CM_FETCH_DEPCHECK);
#endif
		if (need_check_dep(cmd_info->dep_slot_id_mask)) {
			type = *cur_ptr;

			/* wait until dependency is resolved */
			while (!check_dep(cmd_info))
				__asm__ volatile("nop");

			/* Update depdency slot */
			if (cmd_info->dep_slot_id_ref_cnt > 0) {
				set_dep_id = cmd_info->dep_slot_id;
				__atomic_or_fetch(&replay_dep_slot.mask, (0x1ULL << set_dep_id), __ATOMIC_RELAXED);
				replay_dep_slot.ref_cnt[set_dep_id] = cmd_info->dep_slot_id_ref_cnt;
			}

			if (type == PKT_SKIP) {
				cmd_cnt--;
				if (cmd_info->dep_slot_id_ref_cnt)
					__atomic_and_fetch(&replay_dep_slot.mask, ~(0x1ULL << cmd_info->dep_slot_id), __ATOMIC_RELAXED);
			}
		}
#ifdef PROFILE_ENABLE
		rl_profile_log(CM_FETCH_DEPCHECK, cmd_id, type);
#endif

#ifdef ENABLE_WAIT_ERUN
		//-----------------------------------------------------------------
		uint32_t done_counter = 0;

		if (type == PKT_RBDMA_TASK || type == PKT_RBDMA_URQ)
			done_counter = get_rbdma_counter();
		else if (type == PKT_DNC_TASK)
			done_counter = get_dnc_counter();
		//-----------------------------------------------------------------
#endif
		cur_ptr += send_control_packets(cur_ptr, cmd_id);

#ifdef ENABLE_WAIT_ERUN
		//-----------------------------------------------------------------
		if (type == PKT_RBDMA_TASK || type == PKT_RBDMA_URQ)
			wait_rbdma_finish(done_counter);
		else if (type == PKT_DNC_TASK) {
			trigger_and_wait_dnc_finish(done_counter);

#ifdef SHM_SP_DUMP_PER_STREAM
		if (cmd_id % 100 == 0) {
			rbdma_shm_dump(cmd_id);
			rbdma_sp_dump(cmd_id);
		}
#endif
#endif
		//-----------------------------------------------------------------
		if (*cur_ptr == DUMP_END)
			break;
	}

	/* wait until the last command done */
	while (cmd_cnt != cmd_done_cnt)
		__asm__ volatile("nop");

	if (replayer_compare(result_addr, golden_addr, output_size) < 0)
		is_test_passed = 0;
	else
		is_test_passed = 1;

	// clear acc
	rbdma_done_clear(cur_cl_id);
	dnc_done_acc_count_all_clear(cur_cl_id);

	printf("%d/%d replayer END!!!\r\n", cmd_done_cnt, cmd_cnt);
	return is_test_passed;
#endif
return 0;
}

void replay_notify_common(uint32_t cmd_id)
{
	uint32_t gsn = gsn_of_cmd[cmd_id];

	if (gsn != 0)
		gsn_done_board[gsn % GSN_WINDOW_SIZE] = gsn;
}

void replay_dnc_notify(union irq_info irq_data)
{
	uint32_t cmd_id = irq_data.exec_id.cmd_id;

	if (irq_data.hw_id == 0) {
		replay_notify_common(cmd_id);
		RLOG_DBG("DNC done cid %u\r\n", irq_data.exec_id.cmd_id);
	}
}

void replay_rbdma_notify(uint32_t cmd_id)
{
	replay_notify_common(cmd_id);

	if (cmd_id >= DDMA_SUBTASK_ID_MIN) {
		if (sg_pos_of_cmd[cmd_id] == LAST_SG_CMD) {
			processing_sg_ddma = 0;
			RLOG_DBG("cid %u Set processing_sg_ddma to 0 (LAST_SG_CMD finished)\r\n", cmd_id);
		}
	}
#ifdef REPLAY_DEBUG
	last_done[4] = cmd_id;
#endif
}

static void replay_worker(uint32_t stream_mask, int start_d, int end_d)
{
	volatile uint32_t *local_ptrs[STRM_COUNT][HW_SPEC_DNC_COUNT];
	int d_begin[STRM_COUNT], d_end[STRM_COUNT];
	int drain_rounds[STRM_COUNT];
	uint32_t streams_done_mask = 0;
	/* Track how many EOCS barriers each unit has passed individually */
	uint32_t unit_eocs_cnt[STRM_COUNT][HW_SPEC_DNC_COUNT] = {{0}};

	for (int s = 0; s < 4; s++) {
		d_begin[s] = start_d;
		d_end[s] = end_d;
		drain_rounds[s] = (s == STRM_COMPUTE) ? 6 : 1;
	}
	d_begin[4] = d_begin[5] = d_end[4] = d_end[5] = 0;
	drain_rounds[4] = 6;
	drain_rounds[5] = 1;

	/* Initialize local pointers for assigned units */
	for (int s = 0; s < STRM_COUNT; s++) {
		if (!(stream_mask & (1 << s)))
			continue;

		for (int d = d_begin[s]; d <= d_end[s]; d++)
			local_ptrs[s][d] = pktdump_strm_ptr[s][d];
	}

	while (1) {
		uint32_t mask = stream_mask;

		while (mask) {
			int s = __builtin_ffsll(mask) - 1;
			bool all_units_in_stream_finished = true;
			int rounds_left = drain_rounds[s];
			bool progress;

			CLR_BIT(mask, s);

			do {
				progress = false;
				for (int d = d_begin[s]; d <= d_end[s]; d++) {
					volatile uint32_t *ptr = local_ptrs[s][d];

					if (!ptr || *ptr == 0)
						continue;

					/* 1. Handle Multi-Stream Barrier (DUMP_END) per unit */
					if (*ptr == DUMP_END) {
						if (unit_eocs_cnt[s][d] >= *total_streams_to_replay)
							continue;
						all_units_in_stream_finished = false;
						if (*global_eocs_done_cnt <= unit_eocs_cnt[s][d])
							continue;
#ifdef REPLAY_DEBUG
						if (unit_eocs_cnt[s][d] == 0 && !*global_replay_resume_trigger)
							continue;
#endif
						local_ptrs[s][d]++;
						unit_eocs_cnt[s][d]++;
						continue;
					}

					if (*ptr == COMMAND_START) {
						all_units_in_stream_finished = false;
						uint32_t gsn = ptr[1];
						uint32_t cid = ptr[2];
						uint32_t s_type = ptr[3];
						uint32_t sg_pos = ptr[4];
						uint32_t wait_cnt = ptr[5];

						volatile uint32_t *distances = &ptr[6];

#ifdef REPLAY_DEBUG
						/* Strict GSN ordering for debugging */
						if (gsn != next_gsn_to_process)
							continue;
#endif

						/* 2. Check logical dependency at the command level */
						if (wait_cnt > 0 && d == d_begin[s]) {
							if (!check_gsn_dependency(gsn, wait_cnt, distances))
								break;
						}

						/* SG-DDMA control: Check this before consuming hardware credits */
						if (s_type == 4 && (cid & 0xFFFF) == DDMA_SUBTASK_ID_MIN) {
							if (processing_sg_ddma == 1)
								continue;
							processing_sg_ddma = 1;
							dmb();
						}

						/* 3. Check hardware credit (Task Queue) for this specific unit */
						uint32_t credit_required = 1;

						if (s <= 3) {
							credit_required = get_dnc_gsn_credit(ptr + 6 + wait_cnt);
							if (!is_hw_credit_available(s, d, credit_required)) {
							// 2026-03-25 debug
							//	RLOG_DBG(
							//		"[CREDIT] cl%u GSN%u: DNC credit FAIL (q=%u d=%u req=%u)\r\n",
							//		cur_cl_id, gsn, s, d, credit_required);
								continue;
							}
							consume_dnc_hw_credit(s, d, credit_required);
						} else if (s == 4) {
							credit_required = get_rbdma_ext_gsn_credit(ptr + 6 + wait_cnt);
							if (update_ddma_credit(1, credit_required) != RL_OK) {
								RLOG_DBG(
									"[CREDIT] cl%u GSN%u: RBDMA credit FAIL (task=1 ext=%u)\r\n",
									cur_cl_id, gsn, credit_required);
								continue;
							}
						}

						RLOG_DBG("Replaying GSN %u (CID %#x Type %u Unit %d)\r\n",
							 gsn, cid & 0xFFFF, s_type, d);

#ifdef REPLAY_DEBUG
						send_cid[s_type] = cid;
#endif
						/* EOCS control */
						bool is_eocs = (cid & (1U << 31));

						/* GSN mapping: master unit only */
						if (d == 0) {
							gsn_of_cmd[cid & 0xFFFF] = gsn;
							sg_pos_of_cmd[cid & 0xFFFF] = (uint8_t)sg_pos;
						}

						dmb();

						/* 4. Fire packet for this unit */
						uint32_t offset = send_control_packets(ptr + 6 + wait_cnt, s);

						local_ptrs[s][d] += 6 + wait_cnt + offset;
						progress = true;

						dmb();

						/* 5. Wait for hardware completion (Master Unit only) */
						if (is_eocs && d == 0) {
							RLOG_DBG("EOCS CS #%u\r\n", unit_eocs_cnt[s][d]);
							//hbm3_temp_func(0, NULL);
							gsn_done_board[gsn % GSN_WINDOW_SIZE] = gsn;
							/* Master (CL0): bump global EOCS counter (barrier release) */
							if (cur_cl_id == 0)
								(*global_eocs_done_cnt)++;
						}

#ifdef REPLAY_DEBUG
						if (d == 0) {
							while (!gsn_done_board[gsn % GSN_WINDOW_SIZE])
								__asm__ volatile("nop");
							next_gsn_to_process++;
						}
#endif
					}
				}
				rounds_left--;
			} while (progress && rounds_left > 0);

			if (all_units_in_stream_finished) {
				/* Only log once when stream is first marked as finished */
				if (!(streams_done_mask & (1 << s)))
					RLOG_DBG("s %u finished\r\n", s);
				streams_done_mask |= (1 << s);
			}
		}

		if (streams_done_mask == stream_mask) {
			RLOG_DBG("All streams done\r\n");
			break;
		}
	}
}

static void enqueue_to_req(uint32_t opcode, uint32_t cl_id)
{
	qrs_entry[cl_id].cp.opcode = opcode;
	cpu_flush_dcache_range((uintptr_t)(&qrs_entry[cl_id]), sizeof(struct rl_entry));
	int ret = rl_cs_enqueue(&qrs_entry[cl_id], cl_id);

	RLOG_DBG("cl_id=%u: [cq] req eq opcode:%d, target_cl_id: %u, ret=%d\r\n", cur_cl_id, opcode, cl_id, ret);
	if (ret != 0)
		printf("cl_id=%u: Failed to enqueue opcode=%d to cl_id=%u, ret=%d\r\n", cur_cl_id, opcode, cl_id, ret);
}

static void handle_qr_entry(struct rl_entry *entry)
{
	static bool first_run = true;
	uint64_t pt_base_ipa = 0x51800000;	/* notice */

	RLOG_DBG("cur_cl_id=%u: %s: OPCODE %u\r\n", cur_cl_id, __func__, entry->cp.opcode);

	if (entry->cp.opcode == RL_QUEUE_OPCODE_QR_START) {
		if (first_run) {
			/* S2 translation already initialized in quad_replay_start */
			printf("First run: activating SMMU context\r\n");
			smmu_activate_ctx(0, 0, pt_base_ipa);
			ptw_flush_page_tables(pt_base_ipa, 0);
			first_run = false;
		}
		for (int i = 0; i < 4; i++)
			qr_ready[i] = 1;
	} else {
		RLOG_ERR("invalid opcode: %d\r\n", entry->cp.opcode);
	}

	dmb(); //memory barrier
	rl_cs_dequeue();
}

/*
 * Check if all qr_processing flags are cleared for all chiplets and all tasks
 * Returns 1 if any flag is still set, 0 if all are cleared
 */
static int is_any_qr_processing_active(void)
{
	dmb();  /* Read barrier: 다른 chiplet의 write가 보이도록 보장 */
	for (int i = 0; i < MAX_CHIPLET_COUNT; i++) {
		for (int j = 0; j < 4; j++) {
			if (*qr_processing[i][j] == 1) {
				dmb();  /* Read barrier: 읽기 완료 보장 */
				return 1;
			}
		}
	}
	dmb();  /* Read barrier: 읽기 완료 보장 */
	return 0;
}

/*
 * Check if any qr_processing flag is active for a specific chiplet
 * Returns 1 if any flag is still set, 0 if all are cleared
 */
static int is_local_qr_processing_active(uint32_t cl_id)
{
	for (int j = 0; j < 4; j++) {
		if (*qr_processing[cl_id][j] == 1)
			return 1;
	}
	return 0;
}

/*
 * Wait for all qr_processing flags to be cleared across all chiplets and tasks
 * Uses busy-wait with nop instruction (for high-frequency polling)
 */
static void wait_all_qr_processing_done_busy(void)
{
	uint32_t timeout_count = 0;
	const uint32_t MAX_TIMEOUT = 1000000;  /* 약 1초 (CPU frequency에 따라 조정) */

	while (is_any_qr_processing_active()) {
		__asm__ volatile("nop");
		timeout_count++;
		if (timeout_count > MAX_TIMEOUT) {
			RLOG_ERR("%s timeout!\r\n", __func__);
			/* Debug: 어떤 flag가 아직 set되어 있는지 출력 */
			for (int i = 0; i < MAX_CHIPLET_COUNT; i++) {
				for (int j = 0; j < 4; j++) {
					if (*qr_processing[i][j] == 1)
						RLOG_ERR("qr_processing[%d][%d] still set!\r\n", i, j);
				}
			}
			break;  /* Hang 방지 */
		}
	}
	dmb();
}

/*
 * Wait for all qr_processing flags to be cleared across all chiplets and tasks
 * Uses vTaskDelay to yield CPU (for FreeRTOS task context)
 */
static void wait_all_qr_processing_done_yield(void)
{
	uint32_t timeout_ms = 0;
	const uint32_t MAX_TIMEOUT_MS = 5000;  /* 5초 */

	while (is_any_qr_processing_active()) {
		vTaskDelay(pdMS_TO_TICKS(10)); /* Yield to other tasks */
		timeout_ms += 10;
		if (timeout_ms > MAX_TIMEOUT_MS) {
			RLOG_ERR("%s timeout!\r\n", __func__);
			/* Debug: 어떤 flag가 아직 set되어 있는지 출력 */
			for (int i = 0; i < MAX_CHIPLET_COUNT; i++) {
				for (int j = 0; j < 4; j++) {
					if (*qr_processing[i][j] == 1)
						RLOG_ERR("qr_processing[%d][%d] still set!\r\n", i, j);
				}
			}
			break;  /* Hang 방지 */
		}
	}
	dmb();
}

/*
 * Wait for local chiplet's qr_processing flags to be cleared
 * Uses vTaskDelay to yield CPU (for FreeRTOS task context)
 */
static void wait_local_qr_processing_done(uint32_t cl_id)
{
	while (is_local_qr_processing_active(cl_id))
		vTaskDelay(pdMS_TO_TICKS(10));
	dmb();
}

/*
 * Set all qr_processing flags to 1 for all chiplets and all tasks
 * Should only be called by chiplet 0
 */
static void set_all_qr_processing_flags(void)
{
	for (int i = 0; i < MAX_CHIPLET_COUNT; i++) {
		for (int j = 0; j < 4; j++)
			*qr_processing[i][j] = 1;
	}
	dmb();
}

void qr_task0(void *param)
{
	struct rl_entry *req_entry;

	RLOG_INFO("cur_cl_id=%u: qr task0 (DNC 0-2) is started\r\n", cur_cl_id);

	while (1) {
		req_entry = rl_cs_peek();
		if (req_entry) {
			RLOG_DBG("cur_cl_id=%u: %s peeked entry, opcode=%u\r\n",
				 cur_cl_id, __func__, req_entry->cp.opcode);
			handle_qr_entry(req_entry);
		}

		if (*qr_processing[cur_cl_id][0] && qr_ready[0]) {
			RLOG_DBG("cur_cl_id=%u: qr_processing[%u][0]=%d, qr_ready[0]=%d, calling replay_worker\r\n",
				cur_cl_id, cur_cl_id, *qr_processing[cur_cl_id][0], qr_ready[0]);
			dmb();
			/* Core 0: DNC 0-2 */
		#ifdef REPLAY_WORKDER_DEBUG
			replay_worker(0b111111, 0, 15);
		#else
			replay_worker(0b111, 0, 2);
		#endif

			dmb();
			/* Flag를 먼저 클리어한 후 qr_ready 클리어 (순서 중요!) */
			*qr_processing[cur_cl_id][0] = 0;
			dsb();  /* Data Synchronization Barrier: 다른 chiplet에서 보이도록 보장 */
			qr_ready[0] = 0;

			if (cur_cl_id == 0) {
				wait_all_qr_processing_done_busy();

				RLOG_INFO("e2e: \r\n");
			}
		}
	}
}

/*
 * Initialize or reset pktdump_strm_ptr pointers for quad replay
 * This function sets up the stream pointers for packet dump processing
 */
static void init_pktdump_strm_ptr(void)
{
	int unit_idx = 0;

	for (int s = 0; s < STRM_COUNT; s++) {
		int max_d = (s == STRM_CONTROL || s == 4) ? 1 : HW_SPEC_DNC_COUNT;

		for (int d = 0; d < max_d; d++) {
			uint64_t offset = (uint64_t)unit_idx * UNIT_DUMP_SIZE;
			uintptr_t strm_base = REPLAY_BASE_ADDR + (cur_cl_id * CHIPLET_OFFSET);

			pktdump_strm_ptr[s][d] = (volatile uint32_t *)(strm_base + offset);
		//	printf("s %d, d %d, pktdump_strm_ptr %#lx\r\n", s, d, pktdump_strm_ptr[s][d]);
			unit_idx++;
		}
		/* Clear unused pointers for single-unit streams */
		if (s == STRM_CONTROL || s == 4) {
			for (int d = 1; d < HW_SPEC_DNC_COUNT; d++)
				pktdump_strm_ptr[s][d] = NULL;
		}
	}
}

static void qr_task1_init(void)
{
	RLOG_INFO("%s called\r\n", __func__);

	/* Initialize pktdump_strm_ptr for quad replay */
	init_pktdump_strm_ptr();

	cpu_inv_dcache_range((uintptr_t)(REPLAY_BASE_ADDR + (cur_cl_id * CHIPLET_OFFSET)), TOTAL_DUMP_SIZE);

	/* Initialize GSN done board */
	memset((void *)gsn_done_board, 0, sizeof(gsn_done_board));
	memset(gsn_of_cmd, 0, sizeof(gsn_of_cmd));
	memset(sg_pos_of_cmd, 0, sizeof(sg_pos_of_cmd));

	processing_sg_ddma = 0;
#ifdef REPLAY_DEBUG
	next_gsn_to_process = 1;
#endif

	/*
	 * Use Flat Mapping (VA == PA) for the global synchronization counter.
	 * This NC (Non-Cacheable) region at 0x3DC00000 is shared across all chiplets.
	 * Initialize pointers BEFORE dereferencing them.
	 */
	global_eocs_done_cnt = (volatile uint32_t *) SYNC_NC_BASE_ADDR;
#ifdef QREPLAY_DEBUG
	global_replay_resume_trigger = (volatile uint32_t *) (SYNC_NC_BASE_ADDR + 0x8);
#endif
	total_streams_to_replay = (volatile uint32_t *) (SYNC_NC_BASE_ADDR + 0x10);

	// TODO
	*total_streams_to_replay = 2;	// enc + dec

	/* Initialize global counters (only chiplet 0) - AFTER pointer initialization */
	if (cur_cl_id == 0) {
		*global_eocs_done_cnt = 0;
		rbdma_reached_dump_end = 0;
#ifdef REPLAY_DEBUG
		*global_replay_resume_trigger = 0;
#endif
	}

	for (int i = 0; i < MAX_CHIPLET_COUNT; i++) {
		for (int j = 0; j < 4; j++)
			qr_processing[i][j] = (volatile int *)(SYNC_NC_BASE_ADDR + 0x18 + (i * 4 + j) * 0x8);
	}

	qr_task1_init_done = true;
	printf("%s done\r\n", __func__);
}

// Quad replay task functions
static void qr_task1(void *pvParameters)
{
	RLOG_INFO("qr task1 (DNC 3-6 + RBDMA) is started\r\n");
#ifndef REPLAY_WORKDER_DEBUG
	while (1) {
		if (*qr_processing[cur_cl_id][1] && qr_ready[1]) {
			dmb();
			/* Core 1: DNC 3-6 + RBDMA */
			replay_worker(0b111 | (1 << 4), 3, 6);
			dmb();
			/* Flag를 먼저 클리어한 후 qr_ready 클리어 (순서 중요!) */
			*qr_processing[cur_cl_id][1] = 0;
			dsb();  /* Data Synchronization Barrier: 다른 chiplet에서 보이도록 보장 */
			qr_ready[1] = 0;
		}
	}
#else
	while (1)
		;
#endif
}

static void qr_task2(void *pvParameters)
{
	RLOG_INFO("qr task2 (DNC 7-10 + CONTROL) is started\r\n");
#ifndef REPLAY_WORKDER_DEBUG
	while (1) {
		if (*qr_processing[cur_cl_id][2] && qr_ready[2]) {
			dmb();
			/* Core 2: DNC 7-10 + CONTROL */
			replay_worker(0b111 | (1 << 5), 7, 10);
			dmb();
			/* Flag를 먼저 클리어한 후 qr_ready 클리어 (순서 중요!) */
			*qr_processing[cur_cl_id][2] = 0;
			dsb();  /* Data Synchronization Barrier: 다른 chiplet에서 보이도록 보장 */
			qr_ready[2] = 0;
		}
	}
#else
	while (1)
		;
#endif
}

static void qr_task3(void *pvParameters)
{
	RLOG_INFO("qr task3 (DNC 11-15) is started\r\n");
#ifndef REPLAY_WORKDER_DEBUG
	while (1) {
		if (*qr_processing[cur_cl_id][3] && qr_ready[3]) {
			dmb();
			/* Core 3: DNC 11-15 */
			replay_worker(0b111, 11, 15);
			dmb();
			/* Flag를 먼저 클리어한 후 qr_ready 클리어 (순서 중요!) */
			*qr_processing[cur_cl_id][3] = 0;
			dsb();  /* Data Synchronization Barrier: 다른 chiplet에서 보이도록 보장 */
			qr_ready[3] = 0;
		}
	}
#else
	while (1)
		;
#endif
}

// Task info structure for quad replay
struct freertos_task_info {
	TaskFunction_t task_func;
	void (*init_func)(void);
	const char *task_name;
	UBaseType_t priority;
	UBaseType_t affinity;
};

#define CS_TASK_PRIORITY 1
#define CPU_ID_0 0
#define CPU_ID_1 1
#define CPU_ID_2 2
#define CPU_ID_3 3

void replay_init(uint32_t cl_id)
{
	/*
	 * ERRATA: 2026-01-05, SGLUE_ERRATUM_01
	 * SGLUE could detect the unxepected chiplet#
	 * the corresponding interrupt should be disabled.
	 */
#if EVT_VER == 1
	shm_override_reset_value(cl_id);
#endif

	dnc_init(cl_id);
	rbdma_init(cl_id);
	shm_init(cl_id);
	cmgr_init(cl_id);

	//25, 0728, test
	//   test_cdump_mode();

	rush_cli_init();

	start_cycle = get_current_count();
	dmb();
}

static uint8_t quad_replay_start(int argc, char *argv[])
{
	int model_idx = 0;
	int iteration_count;
	uint32_t task_cnt;
	int is_test_passed = 0;
	uint64_t pt_base_ipa = 0x51800000;	/* notice */
//	uint64_t start_cycle = 0ULL;
//	uint64_t cpu_freq = 2000000000ULL;
	uint32_t compare_mode;
	uint64_t result_addr;
	uint64_t golden_addr;
	uint32_t out_size;

	RLOG_INFO("cur_cl_id=%u: %s() called\r\n", cur_cl_id, __func__);
//	start_cycle = bw_measure_start();

	/* Validate argc: need at least model_idx and iteration_count */
	if (argc < 2) {
		printf("\r\nquad_replay_start {idx} {iteration count}\r\n");
		printf("Error: argc=%d, need at least 2 arguments\r\n", argc);
		return false;
	}

	/* Parse and validate model_idx */
	model_idx = atoi(argv[0]);
	if (model_idx < 0 || model_idx >= ARRAY_SIZE(model_list)) {
		printf("\r\nError: Invalid model_idx=%d (valid range: 0-%zu)\r\n",
			model_idx, ARRAY_SIZE(model_list) - 1);
		return false;
	}
	compare_mode = model_list[model_idx].compare_mode;

	/* Parse and validate iteration_count */
	iteration_count = atoi(argv[1]);
	if (iteration_count <= 0) {
		printf("\r\nError: Invalid iteration_count=%d (must be > 0)\r\n", iteration_count);
		return false;
	}

	printf("%s: model_idx=%d, iteration_count=%d\r\n",
		__func__, model_idx, iteration_count);
	RLOG_INFO("%s: model_idx=%d (%s), iteration_count=%d\r\n",
			__func__, model_idx, model_list[model_idx].model_name, iteration_count);

#ifdef PROFILE_ENABLE
	/* Initialize profile buffer at the start of quad_replay_start */
	rl_profile_init();
	RLOG_INFO("Profile buffer initialized\r\n");
#endif

	/* DTC needs SHM interleaving */
	comp_tlb_interleaving(0, NULL);

	/* Reset flags for re-initialization */
	qr_task1_init_done = false;

	/* PMU cleanup before re-enable (if already enabled) */
	/* Check if PMU is already enabled and cleanup if needed */
	int pmu_ret = smmu_pmu_enable();

	if (pmu_ret == RL_ERROR) {
		/* PMU already enabled, cleanup first */
		smmu_pmu_del_evt(1);  /* Remove existing event */
		smmu_pmu_disable();    /* Disable PMU */
		smmu_pmu_enable();     /* Re-enable PMU */
	}

	/* Add PMU event (ignore error if already exists) */
	smmu_pmu_add_evt(1);

	// added tbu_wrapper_init
	tbu_wrapper_init(cur_cl_id);

	/*
	 * S2 (Stage 2) must be initialized and enabled BEFORE S1 context activation
	 * forcely "0" for quad replay
	 */
	printf("First run: initializing S2 translation\r\n");
	ptw_register_s2t_handler(0);
	ptw_init_smmu_s2(0);	/* This calls smmu_s2_enable internally */
	if (smmu_sync() != 0) {
		printf("SMMU sync failed on chiplet %u\r\n", cur_cl_id);
		return false;
	}
	/* Ensure S2 configuration is committed before activating S1 context */
	smmu_sync();
	dsb();  /* Hardware register access - wait for completion */

	/* Activate SMMU context (needed for re-initialization) */
	printf("Activating SMMU context for quad replay\r\n");
	smmu_activate_ctx(0, 0, pt_base_ipa);
	ptw_flush_page_tables(pt_base_ipa, 0);
	dsb();  /* Page table flush completion - wait for completion */

	// Create tasks for quad replay
	static struct freertos_task_info tasks_cl1[] = {
		{ qr_task0, qr_task1_init, "qr0", CS_TASK_PRIORITY, BIT(CPU_ID_0) },
		{ qr_task1, NULL, "qr1", CS_TASK_PRIORITY, BIT(CPU_ID_1) },
		{ qr_task2, NULL, "qr2", CS_TASK_PRIORITY, BIT(CPU_ID_2) },
		{ qr_task3, NULL, "qr3", CS_TASK_PRIORITY, BIT(CPU_ID_3) },
	};

	task_cnt = sizeof(tasks_cl1) / sizeof(struct freertos_task_info);

	static TaskHandle_t task_handles[4] = {NULL, NULL, NULL, NULL};

	for (int i = 0; i < task_cnt; i++) {
		if (tasks_cl1[i].init_func != NULL)
			tasks_cl1[i].init_func();
		BaseType_t ret = xTaskCreateAffinitySet(
			tasks_cl1[i].task_func,
			tasks_cl1[i].task_name,
			configMINIMAL_STACK_SIZE,
			NULL,
			tasks_cl1[i].priority,
			tasks_cl1[i].affinity,
			&task_handles[i]
		);
		if (ret != pdPASS)
			printf("Failed to create task %s\r\n", tasks_cl1[i].task_name);
		else
			RLOG_INFO("Successfully created task %s\r\n", tasks_cl1[i].task_name);
	}

	/* Wait for all tasks to be ready before starting iterations
	 * Ensure qr_task1_init is completed and all tasks have started
	 */
	if (cur_cl_id == 0) {
		/* Wait for local qr_task1_init to complete */
		while (!qr_task1_init_done)
			vTaskDelay(pdMS_TO_TICKS(10));
		/* Give tasks time to start and reach their main loops */
		vTaskDelay(pdMS_TO_TICKS(50));
		RLOG_INFO("All tasks are ready, starting iterations\r\n");
	} else {
		/* For non-chiplet-0, wait for local initialization */
		while (!qr_task1_init_done)
			vTaskDelay(pdMS_TO_TICKS(10));
		/* Give tasks time to start */
		vTaskDelay(pdMS_TO_TICKS(50));
	}

	/* Run iterations: each iteration sets qr_processing, waits for completion, then repeats */
	for (int iter = 1; iter <= iteration_count; iter++) {
		RLOG_INFO(" %d/%d\r\n", iter, iteration_count);

#ifdef PROFILE_ENABLE
		/* Reset profile buffer at the start of each iteration to prevent buffer overflow */
		rl_profile_init();
#endif

		/* Reset global_eocs_done_cnt for each iteration (chiplet 0 only) */
		if (cur_cl_id == 0) {
			*global_eocs_done_cnt = 0;
			dmb();
		}

		/* Reset pktdump_strm_ptr pointers to initial positions for each iteration */
		init_pktdump_strm_ptr();

		/* Reset GSN-related arrays for each iteration */
		memset((void *)gsn_done_board, 0, sizeof(gsn_done_board));
		memset(gsn_of_cmd, 0, sizeof(gsn_of_cmd));
		memset(sg_pos_of_cmd, 0, sizeof(sg_pos_of_cmd));

		/* Reset processing state variables for each iteration */
		processing_sg_ddma = 0;
		cmd_done_cnt = 0;

		/* Reset qr_ready flags for each iteration (all chiplets) */
		for (int i = 0; i < 4; i++)
			qr_ready[i] = 0;
		dmb();

		/* Initialize qr_processing and trigger iteration
		 * CL0 sets qr_processing flags for all chiplets in shared memory
		 */
		if (cur_cl_id == 0)
			set_all_qr_processing_flags();

		/* Each chiplet enqueues RL_QUEUE_OPCODE_QR_START to its own local queue */
		enqueue_to_req(RL_QUEUE_OPCODE_QR_START, cur_cl_id);

		/* Wait for all tasks to complete their work for this iteration */
		if (cur_cl_id == 0) {
			/* Wait until all qr_processing flags are cleared (all tasks completed) */
			wait_all_qr_processing_done_yield();
		} else {
			/* For non-chiplet-0, wait for local tasks to complete */
			wait_local_qr_processing_done(cur_cl_id);
		}

	//	bw_measure_end_and_print(start_cycle, 1, cpu_freq, false);

		/* Wait for all hardware operations to complete
		 * Add delay to allow hardware to finish writing results to memory
		 */
		vTaskDelay(pdMS_TO_TICKS(100));  /* Adjust delay as needed */
		dsb();  /* Hardware operations completion - wait for completion */

		if (compare_mode == COMPARE_MODE_CHIPLET0_ONLY) {
			result_addr = model_list[model_idx].result_addr[0];
			golden_addr = model_list[model_idx].golden_addr[0];
			out_size = model_list[model_idx].out_size[0];
			if (replayer_compare(result_addr, golden_addr, out_size) < 0)
				is_test_passed = 0;
			else
				is_test_passed = 1;

			result_addr = model_list[model_idx].result_addr[1];
			golden_addr = model_list[model_idx].golden_addr[1];
			out_size = model_list[model_idx].out_size[1];
			if (replayer_compare(result_addr, golden_addr, out_size) < 0)
				is_test_passed = 0;
			else
				is_test_passed = 1;
		} else {
			result_addr = cl_base[cur_cl_id] + model_list[model_idx].result_addr[0];
			golden_addr = cl_base[cur_cl_id] + model_list[model_idx].golden_addr[0];
			out_size = model_list[model_idx].out_size[0];
			if (replayer_compare(result_addr, golden_addr, out_size) < 0)
				is_test_passed = 0;
			else
				is_test_passed = 1;
		}

		/* Compare failed: clear condition and exit iteration loop */
		if (is_test_passed == 0) {
			rbdma_done_clear(cur_cl_id);
			dnc_done_acc_count_all_clear(cur_cl_id);
			break;
		}

		if (iter == iteration_count)
			printf("\r\nIteration %d/%d completed\r\n", iter, iteration_count);
		else {
			if ((iter&0xF) == 0xF)
				printf("\r\n");
			else
				printf(".");
		}

		rbdma_done_clear(cur_cl_id);
		dnc_done_acc_count_all_clear(cur_cl_id);
	}
	printf("\r\n");

	/* Delete all created tasks */
	for (int i = 0; i < task_cnt; i++) {
		if (task_handles[i] != NULL) {
			vTaskDelete(task_handles[i]);
			task_handles[i] = NULL;
		}
	}

	/* Return success if all iterations completed */
	dsb();
	/* 1. TBU wrapper disable (All chiplets) */
	tbu_wrapper_deinit(cur_cl_id);

	/* 2. S2 translation configuration and STE restore
	 * func_id=0 for S2 translation configuration and STE restore
	 */
	smmu_s2_disable(0);

	/* 3. PMU cleanup */
	smmu_pmu_del_evt(1);  /* Remove PMU event */
	smmu_pmu_disable();    /* Disable PMU */

	dsb();  /* Hardware register access - wait for completion */
	printf("tbu_wrapper_deinit done\r\n");
	printf("smmu_s2_disable done\r\n");
	printf("smmu_pmu cleanup done\r\n");

	return is_test_passed;
}

int parse_mem_header_info(enum cmp_header_type cmp_header_type)
{
	volatile uint32_t *table_ptr = (volatile uint32_t *)DATA_MEM_BASE_ADDR;
	mem_data_header_t   mem_header_info;
	uint32_t    data[8];
	//int     idx = 0 ;
	int     ret = -1;

	memset(&mem_header_info, 0x0, sizeof(mem_data_header_t));
	//printf("struct size : %d\r\n", sizeof(mem_data_header_t));

	while (1) {
		for (int i = 0; i < sizeof(mem_data_header_t)/sizeof(uint32_t); i++)
			data[i] = *table_ptr++;
		memcpy(&mem_header_info, &data, sizeof(mem_data_header_t));
		//memcpy((void *)&mem_header_info, (const void *)(table_ptr + i*HEADER_SIZE), HEADER_SIZE);

		if (mem_header_info.size > 0) {
#ifdef PRINT_RESULT_COMPARE
			RLOG_INFO("idx:%d type:%x db_cur_offset_addr:%#x\r\n",
					idx++,
					mem_header_info.type,
					mem_header_info.db_cur_offset_addr);
#endif
			if (mem_header_info.type == (enum data_type)FINAL_SHM_DATA) {
				if (cmp_header_type != SKIP_CMP_SHM) {
#ifdef PRINT_RESULT_COMPARE
					printf("-----------------------------------------------------------------\r\n");
					printf("%25s ", "This is SHM Golden Data | ");
					printf("%10s %#lx %10s %#x\r\n",
						"addr:",
						mem_header_info.db_cur_offset_addr,
						"size:",
						mem_header_info.size);
#endif
					golden_addr = mem_header_info.db_cur_offset_addr;
					golden_size = mem_header_info.size;
					ret = result_compare(golden_addr, golden_size);
					if (ret < 0)
						return ret;
				}
			} else if (mem_header_info.type == (enum data_type)FINAL_SP_DATA) {
#ifdef PRINT_RESULT_COMPARE
				printf("-----------------------------------------------------------------\r\n");
				printf("%25s ", "This is SP Golden Data | ");
				printf("%10s %#lx %10s %#x\r\n",
						"addr:",
						mem_header_info.db_cur_offset_addr,
						"size:",
						mem_header_info.size);
#endif
				golden_addr = mem_header_info.db_cur_offset_addr;
				golden_size = mem_header_info.size;
				ret = result_compare(golden_addr, golden_size);
				if (ret < 0)
					return ret;
			}
		} else {
			return ret;
		}
	}
}

int result_compare(uintptr_t addr, uint32_t size)
{
	/*
	 * volatile required for hardware memory-mapped I/O access
	 * checkpatch: ignore volatile warning - hardware register access
	 */
	volatile uint32_t *p_golden = (volatile uint32_t *)(DATA_MEM_BASE_ADDR_CL(cur_cl_id) + addr);
	volatile uint32_t *p_result = (volatile uint32_t *)(DATA_OUT_BASE_ADDR_CL(cur_cl_id) + addr);

	cpu_inv_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR_CL(cur_cl_id) + addr, size);
	cpu_inv_dcache_range((uintptr_t)DATA_OUT_BASE_ADDR_CL(cur_cl_id) + addr, size);
	dsb();

	for (int i = 0; i < size/sizeof(uint32_t); i++) {
		if (*p_result != *p_golden) {
			printf("--------------------------------------------------\r\n");
			printf("The value is different %#x(result) %#x(golden) , addr is %#lx\r\n",
					*p_result,
					*p_golden,
					DATA_OUT_BASE_ADDR_CL(cur_cl_id) + (addr + i*4));
			printf("--------------------------------------------------\r\n");
			return -1;
		}
		p_result++;
		p_golden++;
	}

	return 0;
}

int basic_test_compare(uint64_t src_addr, uint64_t dst_addr, uint32_t size)
{
	volatile uint32_t *p_golden = (volatile uint32_t *)src_addr;
	volatile uint32_t *p_result = (volatile uint32_t *)dst_addr;

	cpu_inv_dcache_range((uintptr_t)p_golden, size);
	cpu_inv_dcache_range((uintptr_t)p_result, size);
	dsb();

	for (int i = 0; i < size/sizeof(uint32_t); i++) {
		if (*p_result != *p_golden) {
			printf("-------------------------------------------------------\r\n");
			printf("Data Mismatch Detected!\r\n");
			printf("Golden Addr : 0x%lx, Result Addr : 0x%lx\r\n", src_addr + i*4, dst_addr + i*4);
			printf("Golden Value: 0x%08x, Result Value: 0x%08x\r\n", *p_golden, *p_result);
			printf("-------------------------------------------------------\r\n");

			volatile uint32_t *golden_start = p_golden;   // mismatch 지점부터 시작
			volatile uint32_t *result_start = p_result;

			size_t dump_words = 1024; // 1024 word = 4KB

			printf("Golden Data Dump (src_addr: 0x%lx ~ 0x%lx)\r\n",
				(uintptr_t)(golden_start), (uintptr_t)(golden_start + dump_words - 1));
			for (int j = 0; j < dump_words; j++) {
				if (j % 4 == 0)
					printf("\n[0x%04x] ", j * 16); // offset 표시
				printf("%08x ", *(p_golden + j));
			}
			printf("\r\n");

			printf("Result Data Dump (dst_addr: 0x%lx ~ 0x%lx)\r\n",
				(uintptr_t)(result_start), (uintptr_t)(result_start + dump_words - 1));
			for (int j = 0; j < dump_words; j++) {
				if (j % 4 == 0)
					printf("\n[0x%04x] ", j * 16); // offset 표시
				printf("%08x ", *(p_result + j));
			}
			printf("\n");
			printf("--------------------------------------------------\r\n");
			// for trace
			rl_abort_cur_ctx(ERR_TASK);
			return -1;
		}
		p_result++;
		p_golden++;
		if (i % 1024 == 0)
			RLOG_INFO(".");
	}
	RLOG_INFO("\r\n");

	return 0;
}

int parse_command_info(bool do_compare)
{
	/*
	 * volatile required for hardware memory-mapped I/O access
	 */
	volatile uint64_t *cmd_ptr = (volatile uint64_t *)DATA_CMD_BASE_ADDR_CL(cur_cl_id);
	cmd_count_t    dnc_acc;
	uint32_t    task_type = 0;
	uint32_t    dnc_id = 0;
	uint32_t    command = 0;
	uint32_t    cmd_stream_id = 0;
	uint32_t    rbdma_acc_count = 0;
	uint32_t    dnc_acc_count = 0;
	uint64_t    addr = 0;
	uint64_t    data = 0;
	int    ret = -1;

	memset(&dnc_acc, 0x0, sizeof(cmd_count_t));

	// parse packet
	while (1) {
		//RLOG_INFO("(ptr:%#lx)\t ", cmd_ptr);
		addr = *cmd_ptr;
		cmd_ptr++;
		data = *cmd_ptr;
		cmd_ptr++;

		//printf("[Packet] ADDR:%#lx, DATA:%#x\r\n", addr, data);

		if (addr != TYPE_EOF) {
			task_type = addr >> 32;
			dnc_id  = addr & 0xff;
			command = (addr & 0xff00)>>8;
			cmd_stream_id = (addr & 0xff0000)>>16;

			// check acc routine
			if (task_type == TYPE_RBDMA) {
				RLOG_INFO("RBDMA Accumulated Counter Checking...\r\n");
				rbdma_acc_count = data & 0xff;
				rbdma_done_acc_count(0, rbdma_acc_count);

			} else if (task_type == TYPE_DNC) {
				if (dnc_check_slot_mask(dnc_id) == RL_OK) {
					RLOG_INFO("DNC[%02d] CMD[%02x] Accumulated Counter Checking...\r\n", dnc_id, command);
					// data info
					memcpy(&dnc_acc, &data, sizeof(cmd_count_t));

					if (command == (enum cmd_mode)COMP) {
						dnc_acc_count = dnc_acc.comp_count; // skip comp tlb
					} else if (command == (enum cmd_mode)LDuDMA) {
						dnc_acc_count = dnc_acc.ldudma_tlb_count + dnc_acc.ldudma_count; // skip comp tlb
					} else if (command == (enum cmd_mode)LPuDMA) {
						dnc_acc_count = dnc_acc.lpudma_tlb_count + dnc_acc.lpudma_count;
					} else if (command == (enum cmd_mode)STuDMA) {
						dnc_acc_count = dnc_acc.studma_tlb_count + dnc_acc.studma_count;
					}
					RLOG_INFO("DNC[%02d], CMD:[%02x], ACC#:[%d]\t\t", dnc_id, command, dnc_acc_count);
					dnc_done_accumulate_count(dnc_id, command, dnc_acc_count);
					//udelay(1);

				}
			} else {
				if (addr >= (apply_cl_base(0x1FF3700000))) {
					// write addr & data
					*(volatile uint32_t *)(uintptr_t)(addr) = (uint32_t)data;
				} else {
					int slot = dnc_detect_slot(addr);

					if (dnc_check_slot_mask(slot) == RL_OK) {
						// if cmd is comp, power throttling mode check
						// write addr & data
						*(volatile uint32_t *)(uintptr_t)(addr) = (uint32_t)data;
					}
				}
			}
		} else {
			if (do_compare) {
				if (data == TYPE_POWER_VECTOR)
					ret = parse_mem_header_info(SKIP_CMP_SHM);
				else
					ret = parse_mem_header_info(ALL_CMP);
			} else {
				ret = 0;
			}
			return ret;
		}
	}

	return -1;
}

int run_common_test(bool do_compare)
{
	int ret = -1;

	ret = parse_command_info(do_compare);
	//printf("\r\n");

	return ret;
}


// Dummy function used to inject STC data via Trace32
void load_stc_data(int stc_tc_idx)
{
	RLOG_INFO("GETTING STC DATA\n");

	printf("Getting STC data\n");
}

//-----------------------------------------------------------------------
uint8_t stc_test(int argc, char *argv[])
{
	int num_of_test = ARRAY_SIZE(stc_list);
	int idx;
	int iter_cnt = 0;
	int stc_fail_event = true;

	printf("%s\r\n", __func__);

	if (argc > 2) {
		printf("stc test {index}\r\n");
		return false;
	}
	if (argc > 0 && (strcmp(argv[0], "all") == 0 || strcmp(argv[0], "ALL") == 0)) {
		iter_cnt = atoi(argv[1]);

		for (int i = 0; i < num_of_test; i++) {
			if (strncmp(stc_list[i], "EOF", 3) == 0) {
				printf("End of testlist detected. Breaking out of %s...\r\n", __func__);
				num_of_test = i;
				break;
			}
			current_stc_idx = i;
			load_stc_data(i);
			printf("test_name: %-10s\r\n", stc_list[i]);

			cpu_inv_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR, SZ_64M);
			cpu_inv_dcache_range((uintptr_t)DATA_CMD_BASE_ADDR, SZ_1M);

			for (int loop = 0; loop < iter_cnt; loop++) {
				printf("\r\n(%d/%d) iteration test", loop+1, iter_cnt);
				bool do_compare = (loop == iter_cnt - 1);

				if (run_common_test(do_compare) < 0) {
					stc_fail_event = false;
					log_test_result("STC", stc_list[i], "FAIL");
				} else {
					log_test_result("STC", stc_list[i], "PASS");

					dnc_clear_sp_all();
					if (shm_init(cur_cl_id) < 0)
						printf("shm_clear ERROR\r\n");
				}
				rbdma_done_clear(cur_cl_id);
				dnc_done_acc_count_all_clear(cur_cl_id);
			}
			if (stc_fail_event == false)
				stc_fail_cnt++;
			else
				stc_pass_cnt++;
			stc_fail_event = true;
		}
		printf("------------------------------------------\r\n");
		printf("(%d/%d) Total (%d) patterns has failed.\r\n", stc_pass_cnt, num_of_test, stc_fail_cnt);
		printf("------------------------------------------\r\n");
	} else {
		idx = atoi(argv[0]);
		iter_cnt = atoi(argv[1]);
		if (idx >= 0 && idx < num_of_test) {
			current_stc_idx = idx;
			load_stc_data(idx);
			printf("test_name: %-10s\r\n", stc_list[idx]);

			cpu_inv_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR, SZ_64M);
			cpu_inv_dcache_range((uintptr_t)DATA_CMD_BASE_ADDR, SZ_1M);

			for (int loop = 0; loop < iter_cnt; loop++) {
				printf("\r\n(%d/%d) iteration test", loop+1, iter_cnt);
				bool do_compare = (loop == iter_cnt - 1);

				if (run_common_test(do_compare) < 0) {
					log_test_result("STC", stc_list[idx], "FAIL");
					rbdma_done_clear(cur_cl_id);
					dnc_done_acc_count_all_clear(cur_cl_id);

					return false;
				}
				log_test_result("STC", stc_list[idx], "PASS");
				rbdma_done_clear(cur_cl_id);
				dnc_done_acc_count_all_clear(cur_cl_id);

				/* FIXME: need to check return value? */
				dnc_clear_sp_all();

				if (shm_init(cur_cl_id) < 0)
					printf("shm_clear ERROR\r\n");
				//25, 0728
				//    for (int ll = 0; ll < HW_SPEC_DNC_COUNT; ll++) {
				//        measure_backpressue(ll);
				//    }
			}
		} else {
			printf("!!! check test list number !!!\r\n");
			return false;
		}
	}
	stc_pass_cnt = 0;
	stc_fail_cnt = 0;

	return true;
}

uint8_t common_test_start(int argc, char *argv[])
{
	int loop = 1;

	cpu_inv_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR_CL(cur_cl_id), SZ_128M);
	cpu_inv_dcache_range((uintptr_t)DATA_CMD_BASE_ADDR_CL(cur_cl_id), SZ_1M);

	if (argc == 0) {
		printf("%s\r\n", "common_test_start {cnt}");
		return false;
	} else if (argc <= 1) {
		loop = atoi(argv[0]);
	} else {
		printf("invalid argument\r\n");
		return false;
	}

	int is_pass = 0;

#if defined(POWER_MODE_TEST)
	pwr_gpio_set();
#endif

#ifdef DNC_DISPLAY_DEBUG
	dnc_clear_profile_log();
#endif
	for (int i = 0; i < loop; i++) {
		// 마지막 루프(loop-1)에서만 compare 수행
		bool do_compare = (i == loop - 1);

		if (run_common_test(do_compare) < 0) {
			snprintf((char *)ITER_RESULT_ADDR, 100,
				"[TEST FAIL] (%d/%d) STC test\r\n", i+1, loop);
			printf("%s", (char *)ITER_RESULT_ADDR);
			is_pass = 0;
		} else {
			printf(".");
			if ((i&0xF) == 0xF)
				printf("\n");
			is_pass = 1;
		}
		if (i == loop - 1) {
			/* FIXME: need to check return value? */
			dnc_clear_sp_all();
			if (shm_zero_init(cur_cl_id) < 0)
				printf("shm_clear ERROR\r\n");
			// clear acc
			rbdma_done_clear(cur_cl_id);
			dnc_done_acc_count_all_clear(cur_cl_id);
			snprintf((char *)ITER_RESULT_ADDR, 100,
				"[TEST PASS] (%d/%d) STC test\r\n", i+1, loop);
			printf("%s", (char *)ITER_RESULT_ADDR);
			printf("Test Done\r\n");
		}
		// clear acc
		rbdma_done_clear(cur_cl_id);
		dnc_done_acc_count_all_clear(cur_cl_id);

		if (is_pass == 0)
			return -1;
	}
#ifdef DNC_DISPLAY_DEBUG
	for (int dnc_id = 0; dnc_id < HW_SPEC_DNC_COUNT; dnc_id++)
		dnc_display_profile(dnc_id);
#endif

#if defined(POWER_MODE_TEST)
	pwr_gpio_unset();
#endif
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	return true;
}

uint8_t ucie_quad_replay_test(int argc, char *argv[])
{
	if (get_chiplet_id() != 0) {
		printf("test only available on chiplet 0");
		return 0;
	}
	if (argc < 2) {
		printf("\r\nquad_replay_start {idx} {iteration count}\r\n");
		return 0;
	}

	uint8_t test_result[4];
	struct ici_chip_sorting_entry entry = {0};

	entry.message_valid = 1;
	entry.task_type = TASK_TYPE_QUAD_REPLAY_TEST;
	strncpy(entry.arg, argv[0], 7);
	entry.size = atoi(argv[1]);

	ici_send_event_chip_sorting(&entry, 1);
	ici_send_event_chip_sorting(&entry, 2);
	ici_send_event_chip_sorting(&entry, 3);
	test_result[0] = quad_replay_start(argc, argv);
	ici_message_receive_polling(1);
	ici_message_receive_polling(2);
	ici_message_receive_polling(3);

	read_entry(1, &entry);
	test_result[1] = entry.result;
	read_entry(2, &entry);
	test_result[2] = entry.result;
	read_entry(3, &entry);
	test_result[3] = entry.result;

	for (int i = 0; i < 4; i++)
		printf("test_result[%d]: %d\r\n", i, test_result[i]);
	snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s] / CL1:[%s] / CL2:[%s] / CL3:[%s]",
		(test_result[0] == 1) ? "PASS" : "FAIL",
		(test_result[1] == 1) ? "PASS" : "FAIL",
		(test_result[2] == 1) ? "PASS" : "FAIL",
		(test_result[3] == 1) ? "PASS" : "FAIL");
	printf("%s\r\n", (char *)ITER_RESULT_ADDR);
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	dsb();
	for (int i = 0; i < 4; i++) {
		if (test_result[i] == -1)
			return -1;
	}
	return 1;
}

static uint8_t common_test_for_ucie_stress(void)
{
	/* volatile required for hardware memory-mapped I/O access */
	volatile uint64_t *cmd_ptr = (volatile uint64_t *)DATA_CMD_BASE_ADDR;
	cmd_count_t    dnc_acc;
	uint32_t    task_type = 0;
	uint32_t    dnc_id = 0;
	uint32_t    command = 0;
	uint32_t    cmd_stream_id = 0;
	uint32_t    dnc_acc_count = 0;
	uint64_t    addr = 0;
	uint64_t    data = 0;

	memset(&dnc_acc, 0x0, sizeof(cmd_count_t));
	while (1) {
		addr = *cmd_ptr;
		cmd_ptr++;
		data = *cmd_ptr;
		cmd_ptr++;

		if (addr != TYPE_EOF) {
			task_type = addr >> 32;
			dnc_id  = addr & 0xff;
			command = (addr & 0xff00)>>8;
			cmd_stream_id = (addr & 0xff0000)>>16;

			if (task_type == TYPE_RBDMA) {

			} else if (task_type == TYPE_DNC) {
				if (dnc_check_slot_mask(dnc_id) == RL_OK) {
					// data info
					memcpy(&dnc_acc, &data, sizeof(cmd_count_t));

					if (command == (enum cmd_mode)COMP)
						dnc_acc_count = dnc_acc.comp_count; // skip comp tlb
					else if (command == (enum cmd_mode)LDuDMA)
						dnc_acc_count = dnc_acc.ldudma_tlb_count + dnc_acc.ldudma_count; // skip comp tlb
					else if (command == (enum cmd_mode)LPuDMA)
						dnc_acc_count = dnc_acc.lpudma_tlb_count + dnc_acc.lpudma_count;
					else if (command == (enum cmd_mode)STuDMA)
						dnc_acc_count = dnc_acc.studma_tlb_count + dnc_acc.studma_count;

					dnc_done_accumulate_count(dnc_id, command, dnc_acc_count);
				}
			} else {
				if (addr >= (apply_cl_base(0x1FF3700000))) {
					// don't do rbmda
				} else {
					int slot = dnc_detect_slot(addr);

					if (dnc_check_slot_mask(slot) == RL_OK) {
						// if cmd is comp, power throttling mode check
						// write addr & data
						*(volatile uint32_t *)(uintptr_t)(addr) = (uint32_t)data;
					}
				}
			}
		} else {
			break;
		}
	}
	dnc_done_acc_count_all_clear(cur_cl_id);
	return 0;
}

void print_tc_info(void)
{
	volatile struct tc_info *tc = (volatile struct tc_info *)TC_INFO_ADDR;

	printf("name:%s\r\n", tc->name);
	printf("type:%d\r\n", tc->type);
	printf("param:%s\r\n", tc->param);
	printf("iter_per_test:%d\r\n", tc->iter_per_test);
	printf("#number:%d\r\n", tc->nr);

	volatile char *tc_pointer = (volatile char *)(tc->data);

	for (int i = 0; i < tc->nr; i++) {
		uint32_t el_type = *((volatile uint32_t *)tc_pointer);

		if (el_type == DATA_EL_TYPE_DMA) {
			const volatile struct tc_dma_info *elem = (const volatile struct tc_dma_info *)tc_pointer;

			printf("------- elemnt %d -------\r\n", i);
			printf("%-12s : %d (DMA)\r\n", "el_type", elem->el_type);
			printf("%-12s : %d\r\n", "dir", elem->dir);
			printf("%-12s : %d\r\n", "type", elem->type);
			printf("%-12s : %d\r\n", "channel", elem->channel);
			printf("%-12s : 0x%lx\r\n", "offset", elem->offset);
			printf("%-12s : 0x%lx\r\n", "size", elem->size);
			tc_pointer += sizeof(struct tc_dma_info);
		} else if (el_type == DATA_EL_TYPE_DB) {
			const volatile struct tc_db_info *elem = (const volatile struct tc_db_info *)tc_pointer;

			printf("------- elemnt %d -------\r\n", i);
			printf("%-12s : %d (DB)\r\n", "el_type", elem->el_type);
			printf("%-12s : %d\r\n", "idx", elem->idx);
			printf("%-12s : %d\r\n", "mailbox", elem->mailbox);
			tc_pointer += sizeof(struct tc_db_info);
		}
	}
}

void ici_callback_pick_rbdma_replay_test_data(struct ici_chip_sorting_entry entry)
{
	int chipid = get_chiplet_id();

	printf("ici command: pick rbmda data for replay_test, chiplet id:%d\r\n", chipid);

#ifdef LEGACY_DEBUG
	volatile struct tc_info *tc = (volatile struct tc_info *)TC_INFO_ADDR;
	volatile char *tc_pointer = (volatile char *)(tc->data);
	int rbdma_task_cnt = 1;

	printf("ici command: pick rbmda data for replay_test, chiplet id:%d\r\n", chipid);

	for (int i = 0; i < tc->nr; i++) {
		uint32_t el_type = *((volatile uint32_t *)tc_pointer);

		if (el_type == DATA_EL_TYPE_DMA) {
			const volatile struct tc_dma_info *elem = (const volatile struct tc_dma_info *)tc_pointer;

			printf("pick replay_test vector: src(%llx), dst(%llx), size(%d)\r\n",
				elem->offset, cl_base[chipid] + elem->offset, RL_ALIGN_SIZE(elem->size, 128));
			generate_rbdma_task(rbdma_task_cnt, elem->offset, cl_base[chipid] + elem->offset, RL_ALIGN_SIZE(elem->size, 128), 0);
			rbdma_task_cnt++;
			tc_pointer += sizeof(struct tc_dma_info);

		} else if (el_type == DATA_EL_TYPE_DB) {
			continue;
		}
	}

	rbdma_done_acc_count(chipid, rbdma_task_cnt);
	rbdma_done_clear(chipid);
#endif
}

void ici_callback_pick_rbdma_stc_data(struct ici_chip_sorting_entry entry)
{
	int chipid = get_chiplet_id();

	printf("ici command: pick rbmda data, chiplet id:%d\r\n", chipid);
	generate_rbdma_task(1, DATA_MEM_BASE_ADDR_CL(0), DATA_MEM_BASE_ADDR_CL(chipid), MEM_DATA_SIZE, 0);
	generate_rbdma_task(2, DATA_CMD_BASE_ADDR_CL(0) + CMD_DATA_SIZE*chipid, DATA_CMD_BASE_ADDR_CL(chipid), CMD_DATA_SIZE, 0);
	rbdma_done_acc_count(chipid, 2);
	rbdma_done_clear(chipid);
	printf("ici command done : pick rbmda data, chiplet id:%d\r\n", chipid);
}

static void do_stress_test(int cl_id, struct ici_chip_sorting_entry entry, int *task_id)
{
	uint64_t src_addr;
	uint64_t dst_addr;
	int rbdma_on = 0;
	int opponent_id = 0;
	int queue_left = 0;

	rbdma_on = (entry.ucie_stress_rbdma_on_mask >> cl_id) & 0x1;
	if (entry.ucie_traffic_direction == UCIE_TRAFFIC_DIRECTION_HORIZONTAL)
		opponent_id = (cl_id + 2) % 4;
	else if (entry.ucie_traffic_direction == UCIE_TRAFFIC_DIRECTION_VERTICAL)
		opponent_id = (-cl_id + 5) % 4;
	else
		return;

	if (entry.ucie_stress_pattern == UCIE_STRESS_PATTERN_WRITE) {
		src_addr = RBDMA_UCIE_STRESS_SRC_ADDR(cl_id);
		dst_addr = RBDMA_UCIE_STRESS_DST_ADDR(opponent_id);
	} else {
		src_addr = RBDMA_UCIE_STRESS_SRC_ADDR(opponent_id);
		dst_addr = RBDMA_UCIE_STRESS_DST_ADDR(cl_id);
	}

	if (rbdma_on == 1) {
		queue_left = rbdma_global_normal_queue_status_cl(cl_id);
		dsb();
		//printf("queue left : %d / dir: %d / opponent: %d\r\n", queue_left, entry.ucie_traffic_direction, opponent_id);
		//printf("src: 0x%lx / dst: 0x%lx\r\n", src_addr, dst_addr);
		while (queue_left > 1) {
		#ifndef POWER_MODE_TEST
			//generate_rbdma_perf_task(*task_id, src_addr, dst_addr, entry.size, 0x33, 1, 0);
			generate_rbdma_task(*task_id, src_addr, dst_addr, entry.size, 0);
		#else
			/*
			 * 2025-10-01, If the task descriptor's sp_granule value is 15 and
			 * the global sp_granule value is 0x0. it has a size of 1 x 16 x 32KB
			 * (global_config_cdma_opmode0.split_granule[13:8] + 1) x
			 * (this field + 1) x 32KB
			 */
			generate_rbdma_perf_task(*task_id,
				src_addr, dst_addr, entry.size, 0xFF, 15, 0);
		#endif
			dsb();
			(*task_id)++;
			if (*task_id >= 0xFFFF0000)
				*task_id = 0xDD3B0000;
			queue_left--;
		}
		if (entry.ucie_stress_test_type == UCIE_STRESS_TEST_TYPE_RBDMA_AND_STC)
			common_test_for_ucie_stress();
	}
}

void ici_trigger_ucie_quad_replay_test(char arg[], int iter_size)
{
	char *argv[MAX_ARGS];
	char char_str[MAX_ARGS][MAX_ARG_LEN] = {'\0', };
	struct ici_chip_sorting_entry entry = {0};

	strncpy(char_str[0], arg, 7);
	snprintf(char_str[1], MAX_ARG_LEN, "%d", iter_size);
	argv[0] = char_str[0];
	argv[1] = char_str[1];
	printf("argv[0] = %s\r\n", argv[0]);
	printf("argv[1] = %s\r\n", argv[1]);

	entry.result = quad_replay_start(2, argv);
	ici_message_clear(entry);
}

void ici_trigger_ucie_basic_test(char arg[], int iter_size)
{
	char *argv[MAX_ARGS];
	char char_str[MAX_ARGS][MAX_ARG_LEN] = {'\0', };
	struct ici_chip_sorting_entry entry = {0};

	RLOG_INFO("ici command: trigger_ucie_basic_test\r\n");
	strncpy(char_str[0], arg, 7);
	snprintf(char_str[1], MAX_ARG_LEN, "%d", iter_size);
	argv[0] = char_str[0];
	argv[1] = char_str[1];

	printf("argv[0] = %s\r\n", argv[0]);
	printf("argv[1] = %s\r\n", argv[1]);
	entry.result = basic_test(2, argv);
	ici_message_clear(entry);
}

static uint8_t hbm_perf_test_func(int argc, char **argv);

void ici_trigger_hbm_perf_test(char arg[])
{
	struct ici_chip_sorting_entry entry = {0};
	char *argv[MAX_ARGS];
	char char_str[MAX_ARGS][MAX_ARG_LEN] = {'\0', };

	RLOG_INFO("ici command: trigger_hbm_perf_test\r\n");

	/* Parse compare argument if provided */
	if (strlen(arg) > 0) {
		strncpy(char_str[0], arg, MAX_ARG_LEN - 1);
		argv[0] = char_str[0];
		entry.result = hbm_perf_test_func(1, argv);
	} else {
		entry.result = hbm_perf_test_func(0, NULL);
	}

	ici_message_clear(entry);
}

int ucie_test_for_secondary_chiplet(int is_control_stress_on)
{
	struct ici_chip_sorting_entry entry = {0};
	int chipid = get_chiplet_id();
	int task_id = 0xDD3B0000;
	int queue_value = 0;
	int prev_traffic_direction = -1;

	while (1) { // infinite loop on purpose
		read_entry(chipid, &entry);
		dsb();
		if (prev_traffic_direction != entry.ucie_traffic_direction) {
			prev_traffic_direction = entry.ucie_traffic_direction;
			if (is_control_stress_on == 1)
				xQueueSend(xDataQueue_ucie_control_stress, &entry.ucie_traffic_direction, 0);
		}
		if (entry.message_valid == 1) {
			if (entry.ucie_stress_test_type == UCIE_STRESS_TEST_TYPE_HALT)
				break;
			do_stress_test(chipid, entry, &task_id);
		}
	}
	entry.result = 0;
	entry.message_valid = 0;
	for (int i = 0; i < 10; i++) {
		queue_value = rbdma_global_normal_queue_status_cl(chipid);
		//printf("waiting rbdma task to be finished: %d\r\n", queue_value);
		if (queue_value == 64) {
			entry.result = 1;
			break;
		}
		mdelay(1000);
	}
	ici_message_clear(entry);
	return 1;
}

static uint8_t ucie_stc_test(int argc, char *argv[])
{
	int i;
	uint8_t test_result[4];
	struct ici_chip_sorting_entry entry = {0};

	if (get_chiplet_id() != 0) {
		printf("test only available on chiplet 0");
		return 0;
	}

	/*
	 * data copy for looping STC vector
	 *  MEM_DATA:   0x60000000 ~ 0x64400000
	 *  CMD_DATA_0: 0x54200000 ~ 0x54220000
	 *  CMD_DATA_1: 0x54220000 ~ 0x54240000
	 *  CMD_DATA_2: 0x54240000 ~ 0x54260000
	 *  CMD_DATA_3: 0x54260000 ~ 0x54280000
	 *
	 */
	if (chiplet_count_opt > 1) {
		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_RBDMA_PICK_STC_VECTOR;
		printf("STC Vector send event to chiplet\r\n");
		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);

		printf("polling receive\r\n");
		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);

		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_STC;
		entry.size = atoi(argv[0]);
		printf("size: %d\r\n", entry.size);

		printf("send stc start\r\n");
		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);
	}

	printf("common test start\r\n");
	test_result[0] = common_test_start(argc, argv);

	if (chiplet_count_opt > 1) {
		printf("start polling\r\n");
		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);
		read_entry(1, &entry);
		test_result[1] = entry.result;
		read_entry(2, &entry);
		test_result[2] = entry.result;
		read_entry(3, &entry);
		test_result[3] = entry.result;
	}

	for (i = 0; i < chiplet_count_opt; i++) {
		printf("test_result[%d]: %d\r\n", i, test_result[i]);
		if (test_result[i] != 1)
			memcpy((void *)DATA_OUT_BASE_ADDR_CL(0), (void *)DATA_OUT_BASE_ADDR_CL(i), SZ_64M);
	}

	if (chiplet_count_opt > 1) {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s] / CL1:[%s] / CL2:[%s] / CL3:[%s]",
				 (test_result[0] == 1) ? "PASS" : "FAIL",
				 (test_result[1] == 1) ? "PASS" : "FAIL",
				 (test_result[2] == 1) ? "PASS" : "FAIL",
				 (test_result[3] == 1) ? "PASS" : "FAIL");
	} else {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s]",
				 (test_result[0] == 1) ? "PASS" : "FAIL");
	}
	printf("%s\r\n", (char *)ITER_RESULT_ADDR);
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	dsb();

	for (i = 0; i < chiplet_count_opt; i++) {
		if (test_result[i] == -1)
			return -1;
	}

	return 1;
}

static uint8_t ucie_af_stc_test(int argc, char *argv[])
{
	int i;
	uint8_t test_result[4];
	struct ici_chip_sorting_entry entry = {0};

	if (get_chiplet_id() != 0) {
		printf("test only available on chiplet 0");
		return 0;
	}

	/*
	 * data copy for looping STC vector
	 *  MEM_DATA:   0x60000000 ~ 0x64400000 -> 0x80000000
	 *  CMD_DATA_0: 0x54200000 ~ 0x54220000
	 *  CMD_DATA_1: 0x54220000 ~ 0x54240000
	 *  CMD_DATA_2: 0x54240000 ~ 0x54260000
	 *  CMD_DATA_3: 0x54260000 ~ 0x54280000
	 */
	if (chiplet_count_opt > 1) {
		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_RBDMA_PICK_STC_VECTOR;
		printf("STC Vector send event to chiplet\r\n");
		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);

		printf("polling receive\r\n");
		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);

		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_AF_STC;
		entry.size = atoi(argv[0]);
		printf("size: %d\r\n", entry.size);
		printf("send af stc start\r\n");
		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);
	}

	printf("af common test start\r\n");
	test_result[0] = af_common_test(argc, argv);

	if (chiplet_count_opt > 1) {
		printf("start polling\r\n");

		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);

		read_entry(1, &entry);
		test_result[1] = entry.result;
		read_entry(2, &entry);
		test_result[2] = entry.result;
		read_entry(3, &entry);
		test_result[3] = entry.result;
	}

	for (i = 0; i < chiplet_count_opt; i++) {
		printf("test_result[%d]: %d\r\n", i, test_result[i]);
		if (test_result[i] != 1)
			memcpy((void *)DATA_OUT_BASE_ADDR_CL(0), (void *)DATA_OUT_BASE_ADDR_CL(i), SZ_64M);
	}

	if (chiplet_count_opt > 1) {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s] / CL1:[%s] / CL2:[%s] / CL3:[%s]",
				 (test_result[0] == 1) ? "PASS" : "FAIL",
				 (test_result[1] == 1) ? "PASS" : "FAIL",
				 (test_result[2] == 1) ? "PASS" : "FAIL",
				 (test_result[3] == 1) ? "PASS" : "FAIL");
	} else {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s]",
				 (test_result[0] == 1) ? "PASS" : "FAIL");
	}
	printf("%s\r\n", (char *)ITER_RESULT_ADDR);
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	dsb();

	for (i = 0; i < chiplet_count_opt; i++) {
		if (test_result[i] == -1)
			return -1;
	}

	return 1;
}

static uint8_t basic_test_all_chiplet(int argc, char *argv[])
{
	int i;
	uint8_t test_result[4] = {0,};
	struct ici_chip_sorting_entry entry = {0};

	if (get_chiplet_id() != 0) {
		printf("only chiplet 0 is allowed to execute basic_test_all_chipelt\r\n");
		return 0;
	}

	if (argc < 2) {
		printf("usage: %s {index} {iteration count}\r\n", __func__);
		return false;
	}
	strncpy(entry.arg, argv[0], 7);
	entry.size = atoi(argv[1]);

	printf("CL0: %s start\r\n", __func__);

	if (chiplet_count_opt > 1) {
		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_BASIC_TEST;

		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);
	}
	test_result[0] = basic_test(argc, argv);

	if (chiplet_count_opt > 1) {
		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);
		read_entry(1, &entry);
		test_result[1] = entry.result;
		read_entry(2, &entry);
		test_result[2] = entry.result;
		read_entry(3, &entry);
		test_result[3] = entry.result;
	}

	for (i = 0; i < chiplet_count_opt; i++) {
		printf("test_result[%d]: %d\r\n", i, test_result[i]);
		if (test_result[i] != 1) {
			printf("flush mismatched data : %d\r\n", i);
			memcpy((void *)DATA_OUT_BASE_ADDR_CL(0), (void *)DATA_OUT_BASE_ADDR_CL(i), SZ_64M);
			cpu_flush_dcache_range((uintptr_t)DATA_OUT_BASE_ADDR_CL(0), SZ_64M);
		}
	}

	if (chiplet_count_opt > 1) {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s] / CL1:[%s] / CL2:[%s] / CL3:[%s]\0",
				 (test_result[0] == 1) ? "PASS" : "FAIL",
				 (test_result[1] == 1) ? "PASS" : "FAIL",
				 (test_result[2] == 1) ? "PASS" : "FAIL",
				 (test_result[3] == 1) ? "PASS" : "FAIL");
	} else {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s]\0",
				 (test_result[0] == 1) ? "PASS" : "FAIL");
	}
	printf("%s\r\n", (char *)ITER_RESULT_ADDR);
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	dsb();

	for (i = 0; i < chiplet_count_opt; i++)
		if (test_result[i] == -1)
			return -1;

	printf("all basic test done\r\n");
	return 1;
}

static uint8_t common_test_all_chiplet(int argc, char *argv[])
{
	int i;
	uint8_t test_result[4] = {0,};
	struct ici_chip_sorting_entry entry = {0};

	if (get_chiplet_id() != 0) {
		printf("only chiplet 0 is allowed to execute %s\r\n", __func__);
		return 0;
	}

	if (argc < 1) {
		printf("usage: %s {count}\r\n", __func__);
		return false;
	}
	entry.size = atoi(argv[0]);

	printf("CL0: %s start\r\n", __func__);

	if (chiplet_count_opt > 1) {
		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_STC;

		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);
	}

	test_result[0] = common_test_start(argc, argv);

	if (chiplet_count_opt > 1) {
		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);
		read_entry(1, &entry);
		test_result[1] = entry.result;
		read_entry(2, &entry);
		test_result[2] = entry.result;
		read_entry(3, &entry);
		test_result[3] = entry.result;
	}

	for (i = 0; i < chiplet_count_opt; i++) {
		printf("test_result[%d]: %d\r\n", i, test_result[i]);
		if (test_result[i] != 1) {
			printf("flush mismatched data : %d\r\n", i);
			memcpy((void *)DATA_OUT_BASE_ADDR_CL(0),
				   (void *)DATA_OUT_BASE_ADDR_CL(i), SZ_64M);
			cpu_flush_dcache_range((uintptr_t)DATA_OUT_BASE_ADDR_CL(0), SZ_64M);
		}
	}

	if (chiplet_count_opt > 1) {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s] / CL1:[%s] / CL2:[%s] / CL3:[%s]\0",
				 (test_result[0] == 1) ? "PASS" : "FAIL",
				 (test_result[1] == 1) ? "PASS" : "FAIL",
				 (test_result[2] == 1) ? "PASS" : "FAIL",
				 (test_result[3] == 1) ? "PASS" : "FAIL");
	} else {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s]\0",
				 (test_result[0] == 1) ? "PASS" : "FAIL");
	}
	printf("%s\r\n", (char *)ITER_RESULT_ADDR);
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	dsb();

	for (i = 0; i < chiplet_count_opt; i++)
		if (test_result[i] == -1)
			return -1;

	printf("all common test done\r\n");

	return 1;
}


void vWorkerTask_ucie_control_stress(void *pvParameters)
{
	int opponent_id = 0;
	int valid_data;

	RLOG_INFO("task started\r\n");
	if (xQueueReceive(xDataQueue_ucie_control_stress, &valid_data, portMAX_DELAY) == pdPASS)
		RLOG_INFO("receive data\r\n");

	while (1) {
		if (xQueueReceive(xDataQueue_ucie_control_stress, &valid_data, 0) == pdPASS) {
			if (valid_data == UCIE_TRAFFIC_DIRECTION_HORIZONTAL)
				opponent_id = (cur_cl_id + 2) % 4;
			else if (valid_data == UCIE_TRAFFIC_DIRECTION_VERTICAL)
				opponent_id = (-cur_cl_id + 5) % 4;
			else
				continue;
		}

		/*
		 * CDP register (Cbus Data Passage)
		 * When WRM (Wirte Ranged Module) is triggered data in CDP registers are duplicated to the SRAM
		 * Writing to CDP register has no effect as long as the WRM is not triggered
		 * In the VDK, nobody uses WRM so these registers are used as a dummy registers
		 */
		shm_read_cdp_register(opponent_id);

		if (valid_data == -1)
			break;
	}

	xTaskNotifyGive(main_task_handle);
	vTaskDelete(NULL);
}

static int ucie_test_core(int is_stc_on, int iter_count)
{
	// total (rbdma_stress_max_size * entry.size) bytes will be transfered through UCIe
	const int rbdma_stress_max_size = 128; // configurable
	struct ici_chip_sorting_entry entry = {0};
	int chipid = get_chiplet_id();
	int task_id = 0xDD3B0000;
	int acc_count[4];
	int test_result = true;
	int acc_max;
	int acc_min;
	int acc_diff;
	int pass_count;

	entry.ucie_stress_pattern = UCIE_STRESS_PATTERN_READ;
	entry.task_type = TASK_TYPE_NONE;
	entry.size = 0x80000000;
	entry.ucie_stress_rbdma_on_mask = 0xF;
	entry.message_valid = 0;
	entry.ucie_traffic_direction = UCIE_TRAFFIC_DIRECTION_NONE;

	if (chipid != 0) { // fail fast
		printf("only for chiplet 0");
		return 1;
	}

	if (is_stc_on == 1)
		entry.ucie_stress_test_type = UCIE_STRESS_TEST_TYPE_RBDMA_AND_STC;
	else
		entry.ucie_stress_test_type = UCIE_STRESS_TEST_TYPE_ONLY_RBDMA;

	for (int i = 0; i < iter_count; i++) {
		for (int chip_index = 0; chip_index < 4; chip_index++)
			rbdma_done_clear(chip_index);

		if (entry.ucie_traffic_direction == UCIE_TRAFFIC_DIRECTION_HORIZONTAL)
			entry.ucie_traffic_direction = UCIE_TRAFFIC_DIRECTION_VERTICAL;
		else
			entry.ucie_traffic_direction = UCIE_TRAFFIC_DIRECTION_HORIZONTAL;

		entry.message_valid = 0;
		write_entry(1, &entry);
		write_entry(2, &entry);
		write_entry(3, &entry);
		dsb();
		entry.message_valid = 1;
		write_entry(1, &entry);
		write_entry(2, &entry);
		write_entry(3, &entry);
		dsb();

		xQueueSend(xDataQueue_ucie_control_stress, &entry.ucie_traffic_direction, 0);
		while (1) {
			pass_count = 0;
			acc_count[0] = rbdma_done_count_cl(0);
			acc_max = acc_count[0];
			acc_min = acc_count[0];
			for (int chip_index = 0; chip_index < 4; chip_index++) {
				acc_count[chip_index] = rbdma_done_count_cl(chip_index);
				if (acc_count[chip_index] > acc_max)
					acc_max = acc_count[chip_index];
				if (acc_count[chip_index] < acc_min)
					acc_min = acc_count[chip_index];
				acc_diff = acc_max - acc_min;
				if (acc_count[chip_index] > rbdma_stress_max_size)
					pass_count++;
			}
			if (pass_count == 4)
				break;

			if (acc_diff > (5 * rbdma_stress_max_size)) {
				test_result = false;
				break;
			}
			do_stress_test(chipid, entry, &task_id);
		}
		if (test_result == false)
			break;
	}
	if (test_result == false) {
		printf("UCIE_TEST FAILED with %s Direction: \r\n",
			((entry.ucie_traffic_direction == UCIE_TRAFFIC_DIRECTION_HORIZONTAL) ?
			"Horizontal" : "Vertical"));
		for (int i = 0; i < 4; i++)
			printf(" * Chiplet %d : acc count = %d\r\n", i, acc_count[i]);
	}

	memset(&entry, 0, sizeof(struct ici_chip_sorting_entry));
	entry.message_valid = 1;
	entry.ucie_stress_test_type = UCIE_STRESS_TEST_TYPE_HALT;
	ici_send_event_chip_sorting(&entry, 1);
	ici_send_event_chip_sorting(&entry, 2);
	ici_send_event_chip_sorting(&entry, 3);
	return test_result;
}

static uint8_t ucie_stress_test(int argc, char *argv[])
{
	int i;
	int iter_count;
	uint8_t test_result[4] = {0,};
	struct ici_chip_sorting_entry entry = {0};

	if (chiplet_count_opt != MAX_CHIPLET_COUNT) {
		printf("Skip UCIe Stress Test (Single Chiplet)\n");
		return true;
	}

	printf("%s start\r\n", __func__);
	if (argc < 1) {
		printf("usage: %s {iteration count}\r\n", __func__);
		return false;
	}
	iter_count = atoi(argv[1]);
	printf("ucie stress test start (itercount: %d)\r\n", iter_count);

	entry.size = iter_count;
	entry.task_type = TASK_TYPE_UCIE_STC_STRESS;
	entry.message_valid = 1;

	ici_send_event_chip_sorting(&entry, 1);
	ici_send_event_chip_sorting(&entry, 2);
	ici_send_event_chip_sorting(&entry, 3);

	rand_fill((void *)RBDMA_UCIE_STRESS_SRC_ADDR(cur_cl_id), SZ_2G);
	for (i = 0; i < iter_count; i++) {
		test_result[0] = ucie_test((void *)&(test_func_list) {0, ucie_test, "ucie_test", {0, 0, 0, 1}});
		printf(".");
		if (i % 16 == 0)
			printf("\r\n");
	}

	ici_message_receive_polling(1);
	ici_message_receive_polling(2);
	ici_message_receive_polling(3);

	read_entry(1, &entry);
	test_result[1] = entry.result;
	read_entry(2, &entry);
	test_result[2] = entry.result;
	read_entry(3, &entry);
	test_result[3] = entry.result;

	for (i = 0; i < 4; i++) {
		printf("test_result[%d]: %d\r\n", i, test_result[i]);
		if (test_result[i] != 1) {
			printf("flush mismatched data : %d\r\n", i);
			memcpy((void *)DATA_OUT_BASE_ADDR_CL(0), (void *)DATA_OUT_BASE_ADDR_CL(i), SZ_64M);
			cpu_flush_dcache_range((uintptr_t)DATA_OUT_BASE_ADDR_CL(0), SZ_64M);
		}
	}

	snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s] / CL1:[%s] / CL2:[%s] / CL3:[%s]\0",
			 (test_result[0] == 1) ? "PASS" : "FAIL",
			 (test_result[1] == 1) ? "PASS" : "FAIL",
			 (test_result[2] == 1) ? "PASS" : "FAIL",
			 (test_result[3] == 1) ? "PASS" : "FAIL");
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	printf("%s\r\n", (char *)ITER_RESULT_ADDR);

	for (i = 0; i < 4; i++)
		if (test_result[i] == -1)
			return -1;

	printf("all ucie stress test done\r\n");

	return 1;
}

void ici_trigger_ucie_stc_stress_test(int iter_count)
{
	printf("ucie stress test start (itercount: %d)\r\n", iter_count);
	rand_fill((void *)RBDMA_UCIE_STRESS_SRC_ADDR(cur_cl_id), SZ_2G);
	for (int i = 0; i < iter_count; i++) {
		ucie_test((void *)&(test_func_list){0, ucie_test, "ucie_test", {0, 0, 0, 1}});
		printf(".");
		if (i % 16 == 0)
			printf("\r\n");
	}
}

static int power_mode_ucie_test_core(int chip1, int chip2, int rbdma_stress_max_size)
{
	struct ici_chip_sorting_entry entry = {0};
	int chipid = get_chiplet_id();
	int task_id = 0xDD3B0000;
	int test_result = true;
	int acc_diff;

	entry.ucie_stress_pattern = UCIE_STRESS_PATTERN_READ;
	entry.task_type = TASK_TYPE_POWER_MODE_UCIE_TEST;
	entry.size = 0x80000000;
	entry.ucie_stress_rbdma_on_mask = (0x1 << chip1) | (0x1 << chip2);
	if (abs(chip1 - chip2) == 1)
		entry.ucie_traffic_direction = UCIE_TRAFFIC_DIRECTION_VERTICAL;
	else
		entry.ucie_traffic_direction = UCIE_TRAFFIC_DIRECTION_HORIZONTAL;

	entry.message_valid = 0;
	write_entry(1, &entry);
	write_entry(2, &entry);
	write_entry(3, &entry);
	dsb();
	entry.message_valid = 1;
	write_entry(1, &entry);
	write_entry(2, &entry);
	write_entry(3, &entry);
	dsb();

	while (1) {
		acc_diff = abs(rbdma_done_count_cl(chip1) - rbdma_done_count_cl(chip2));
		if (acc_diff > (5 * rbdma_stress_max_size)) {
			test_result = false;
			break;
		} else if (rbdma_done_count_cl(chip1) > rbdma_stress_max_size) {
			test_result = true;
			break;
		}
		do_stress_test(chipid, entry, &task_id);
	}
	if (test_result == false) {
		printf("POWER_MODE: UCIE_TEST FAILED !!\r\n");
		printf(" - acc count of chiplet %d : %d", chip1, rbdma_done_count_cl(chip1));
		printf(" - acc count of chiplet %d : %d", chip2, rbdma_done_count_cl(chip2));
	} else {
		printf("POWER_MODE: UCIE_TEST DONE\r\n");
		printf(" - acc count of chiplet %d : %d\r\n", chip1, rbdma_done_count_cl(chip1));
		printf(" - acc count of chiplet %d : %d\r\n", chip2, rbdma_done_count_cl(chip2));
	}

	memset(&entry, 0, sizeof(struct ici_chip_sorting_entry));
	entry.message_valid = 1;
	entry.ucie_stress_test_type = UCIE_STRESS_TEST_TYPE_HALT;

	ici_send_event_chip_sorting(&entry, 1);
	ici_send_event_chip_sorting(&entry, 2);
	ici_send_event_chip_sorting(&entry, 3);

	while (rbdma_global_normal_queue_status_cl(chip1) != 64)
		; /* wait until queue status becomes max available */
	while (rbdma_global_idle_status_cl(chip1) != 0xFF)
		; /* wait until queue status becomes idle state */
	while (rbdma_global_normal_queue_status_cl(chip2) != 64)
		; /* wait until queue status becomes max available */
	while (rbdma_global_idle_status_cl(chip2) != 0xFF)
		; /* wait until queue status becomes idle state */

	return test_result;
}

static uint8_t power_mode_ucie_test(int argc, char *argv[])
{
	int chip1;
	int chip2;
	int iter_count;
	int ret;
	struct ici_chip_sorting_entry entry = {0};

	if (chiplet_count_opt != MAX_CHIPLET_COUNT) {
		printf("Skip Power Mode UCIe Test (Single Chiplet)\n");
		return true;
	}

	if (argc < 3) {
		printf("usage: %s {chip1} {chip2} {iter count}\r\n", __func__);
		return false;
	}

	if (get_chiplet_id() == 0) {
		chip1 = atoi(argv[0]);
		chip2 = atoi(argv[1]);
		iter_count = atoi(argv[2]);

		rbdma_done_clear(0);
		rbdma_done_clear(1);
		rbdma_done_clear(2);
		rbdma_done_clear(3);
		dsb();

		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_POWER_MODE_UCIE_TEST;

		printf("sending event message to chiplet 1, 2, 3\r\n");
		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);
		printf("send message done, starting test\r\n");
		printf(" - test target chiplet: %d %d\r\n", chip1, chip2);
		printf(" - test iteration count: %d\r\n", iter_count);

		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);
		dsb();

		ret = power_mode_ucie_test_core(chip1, chip2, iter_count);
	} else {
		ici_message_clear(entry);
		printf("message received, starting test\r\n");

		ret = ucie_test_for_secondary_chiplet(0);
	}

	return ret;
}

int ucie_test(void *ctx)
{
	int ret;
	int i;
	struct ici_chip_sorting_entry entry = {0};
	const int task_quit_message = -1;
	test_func_list *item = ctx;
	struct test_ctx_args *args = &item->args;
	int is_ucie_stress_test = args->is_ucie_stress_test;

	if (chiplet_count_opt != MAX_CHIPLET_COUNT) {
		printf("Skip UCIe Test (Single Chiplet)\n");
		return true;
	}

	RLOG_INFO("%s\r\n", __func__);

	if (is_ucie_stress_test == 0)
		rand_fill((void *)RBDMA_UCIE_STRESS_SRC_ADDR(cur_cl_id), SZ_2G);

	if (cur_cl_id == 0) {
		for (i = 1; i <= 3; i++)
			ici_send_sync_event(i);
		for (i = 1; i <= 3; i++)
			ici_sync_receive_polling(i);
	} else {
		ici_wait_sync_event();
		ici_sync_message_clear();
	}

	entry.task_type = TASK_TYPE_NONE;
	entry.message_valid = 0;
	entry.ucie_traffic_direction = UCIE_TRAFFIC_DIRECTION_NONE;

	shm_randomize_cdp_register();
	main_task_handle = xTaskGetCurrentTaskHandle();
	xDataQueue_ucie_control_stress = xQueueCreate(10, sizeof(int));
	xQueueSend(xDataQueue_ucie_control_stress, &entry.ucie_traffic_direction, 0);
	xTaskCreate(vWorkerTask_ucie_control_stress, "UCIEControlBusWorker", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);

	if (get_chiplet_id() == 0) {
		for (i = 1; i <= 3; i++) {
			write_entry(i, &entry);
			dsb();
			ici_send_sync_event(i);
			ici_sync_receive_polling(i);
		}
		ret = ucie_test_core(is_ucie_stress_test, 1*4);
	} else {
		ici_wait_sync_event();
		ici_sync_message_clear();
		dsb();
		ret = ucie_test_for_secondary_chiplet(1);
	}

	xQueueSend(xDataQueue_ucie_control_stress, &task_quit_message, 0);
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

	while (shm_check_cdp_register_clear(cur_cl_id) != 0)
		shm_clear_cdp_register();

	if (cur_cl_id == 0) {
		for (i = 1; i < 4; i++) {
			while (shm_check_cdp_register_clear(i) != 0)
				;
		}
	}

	return ret;
}

void ici_trigger_stc_test(struct ici_callback_data c_data)
{
	int argc = 1;
	char *argv[MAX_ARGS];
	char char_str[MAX_ARG_LEN];
	struct ici_chip_sorting_entry entry = {0};

	snprintf(char_str, MAX_ARG_LEN, "%d", c_data.size);
	argv[0] = char_str;

	entry.message_valid = 0;
	entry.result = common_test_start(argc, argv);
	ici_message_clear(entry);
}

void ici_trigger_af_common_test(struct ici_callback_data c_data)
{
	int argc = 1;
	char *argv[MAX_ARGS];
	char char_str[MAX_ARG_LEN];
	struct ici_chip_sorting_entry entry = {0};

	snprintf(char_str, MAX_ARG_LEN, "%d", c_data.size);
	argv[0] = char_str;

	entry.message_valid = 0;
	entry.result = af_common_test(argc, argv);
	ici_message_clear(entry);
}

void print_hdma_desc(void)
{
	for (int i = 0; i < 16; i++) {
		const volatile struct hdma_desc	*list = &HDMA_DESC_ADDR(i);

		printf("------- h_desc %d -------\r\n", i);
		printf("%-12s : %d\r\n", "ch_control", list->channel_control);
		printf("%-12s : %d\r\n", "transfer_size", list->transfer_size);
		printf("%-12s : 0x%lx\r\n", "sar", list->sar);
		printf("%-12s : 0x%lx\r\n", "dar", list->dar);
	}
}

#define REPLAY_TEST_TIMEOUT_MS	(600 * 1000)	/* 600 seconds */

static void replay_timeout_callback(TimerHandle_t xTimer)
{
	test_exception_mark();
	RLOG_ERR("[TIMEOUT] Test did not complete within %d s\r\n",
		 REPLAY_TEST_TIMEOUT_MS / 1000);
	printf("[TIMEOUT] Test did not complete within %d s\r\n",
	       REPLAY_TEST_TIMEOUT_MS / 1000);
}

void replay_routine(void)
{
	TimerHandle_t timeout_timer;

	printf("%s\r\n", __func__);

	if (get_chiplet_id() != 0) {
		printf("[ERROR] replay_routine is only allowed on chiplet0\r\n");
		return;
	}
	cpu_inv_dcache_range((uintptr_t)TC_INFO_ADDR, SZ_4M*8);
	cpu_inv_dcache_range((uintptr_t)HDMA_DESC_BASE_ADDR, SZ_2M);

	volatile struct tc_info *tc = (volatile struct tc_info *)TC_INFO_ADDR;

	// parsing tc->param
	char param_original_string[64] = {'\0',};
	char arg_buffer[MAX_ARGS][MAX_ARG_LEN] = {'\0', };
	char *token;
	char *delimiter = " ";
	char *context = NULL;

	int argc = 0;
	char *argv[MAX_ARGS] = {0, };
	uint8_t test_result = 2;
	char iter_per_test[MAX_ARG_LEN];

	if (strlen((const char *)tc->param) == 0) {
		// set to default value
		// argc = 1
		// argv = {"1"}
		argc = 1;
		strncpy(arg_buffer[0], "1", MAX_ARG_LEN - 1);
		arg_buffer[0][MAX_ARG_LEN - 1] = '\0';
		argv[0] = arg_buffer[0];
	} else {
		strncpy(param_original_string, (const char *)tc->param, 64 - 1);
		token = strtok_r(param_original_string, delimiter, &context);
		while (token != NULL && argc < MAX_ARGS) {
			strncpy(arg_buffer[argc], token, MAX_ARG_LEN - 1);
			argv[argc] = arg_buffer[argc];
			argc++;
			token = strtok_r(NULL, delimiter, &context);
		}
	}

	snprintf(iter_per_test, 10, "%d", tc->iter_per_test);
	argv[argc] = iter_per_test;
	argc++;

	/* Start timeout timer before test execution */
	timeout_timer = xTimerCreate("test_timeout",
				     pdMS_TO_TICKS(REPLAY_TEST_TIMEOUT_MS),
				     pdFALSE,
				     NULL,
				     replay_timeout_callback);
	if (timeout_timer)
		xTimerStart(timeout_timer, 0);

	printf("TEST NAME: ( %s )\r\n", tc->name);
	if (tc->type == (uint32_t)DATA_TC_TYPE_STC) {
		printf("run common_test\r\n");
		test_result = common_test_start(argc, argv);
	} else if (tc->type == (uint32_t)DATA_TC_TYPE_UNIT_TEST) {
		printf("run basic_test_all_chiplet\r\n");
		test_result = basic_test_all_chiplet(argc, argv);
	} else if (tc->type == (uint32_t)DATA_TC_TYPE_UCIE_STC) {
		printf("run ucie_stc_test\r\n");
		argv[0] = iter_per_test;
		argc = 1;
		test_result = ucie_stc_test(argc, argv);
	} else if (tc->type == (uint32_t)DATA_TC_TYPE_UCIE_STRESS) {
		rand_fill((void *)RBDMA_UCIE_STRESS_SRC_ADDR(cur_cl_id), SZ_2G);
		ucie_stc_test(1, (char *[]){"1", NULL});
		test_result = ucie_stress_test(argc, argv);
	} else if (tc->type == (uint32_t)DATA_TC_TYPE_UCIE_QUAD_REPLAY_TEST) {
		for (int i = 0; i < argc; i++)
			printf("  argv[%d]: %s\r\n", i, argv[i] ? argv[i] : "(null)");
		test_result = ucie_quad_replay_test(argc, argv);
	} else if (tc->type == (uint32_t)DATA_TC_TYPE_UCIE_AF_STC_POWER) {
		printf("run ucie_af_stc_test\r\n");
		argv[0] = iter_per_test;
		argc = 1;
		test_result = ucie_af_stc_test(argc, argv);
	}

	/* Test completed: cancel and delete timeout timer */
	if (timeout_timer) {
		xTimerStop(timeout_timer, 0);
		xTimerDelete(timeout_timer, 0);
	}

	volatile char *tc_pointer = (volatile char *)(tc->data);

	for (int i = 0; i < tc->nr; i++) {
		uint32_t el_type = *((volatile uint32_t *)tc_pointer);

		if (el_type == DATA_EL_TYPE_DMA) {
			const volatile struct tc_dma_info *elem = (const volatile struct tc_dma_info *)tc_pointer;

			/* dir==1: WRCH path; HDMA_EN_CH_WRCH==1: channel enabled — then doorbell */
			if (elem->dir == 1) {
				uint32_t wrch_en = HDMA_EN_CH_WRCH(elem->channel);

				if (wrch_en == 1U) {
					HDMA_DOORBELL_WRCH_TRIGGER(elem->channel) = 0x1;
					printf("Device to host: Trigger HDMA Doorbell, channel: %d\r\n", elem->channel);
				} else
					printf("Device to host: HDMA_EN_CH_WRCH is disabled for channel %d\r\n",
						elem->channel);
			}
			tc_pointer += sizeof(struct tc_dma_info);
		} else if (el_type == DATA_EL_TYPE_DB)
			tc_pointer += sizeof(struct tc_db_info);
	}

	if (test_result == 1)
		printf("TEST worked successfully\r\n");
	else if (test_result == 2)
		printf("Test not executed\r\n");
	else
		printf("TEST fail\r\n");
}

static uint8_t shm_all_clear(int argc, char *argv[])
{
	if (shm_init(cur_cl_id) < 0)
		return false;

	return true;
}

void logbuf_init(uint32_t cl_id)
{
	uintptr_t base = (uintptr_t)LOG_BUF_BASE;
	uintptr_t offset = (uintptr_t)cl_id * CHIPLET_OFFSET;

	memset((void *)(base + offset), 0, SZ_2M);
	cpu_clean_dcache_range(base + offset, SZ_2M);
}

void hw_init(void)
{
	enable_irq();
	enable_fiq();
	enable_abort_interrupt(0);  // core 0
	RLOG_DBG("%s done\r\n", __func__);
	printf("%s done\r\n", __func__);
}

void sw_init(void)
{
	rl_cpu_set_core_ready_status(HART_ID_0);

	replay_init(cur_cl_id);	// RBLN Init

	RLOG_DBG("%s done\r\n", __func__);
	printf("%s done\r\n", __func__);
}

static uint8_t display_basic_test(int argc, char *argv[])
{
	int num_of_test = ARRAY_SIZE(item_list); // sizeof(item_list) / sizeof(item_list[0]);

	printf("This is basic test list\r\n\r\n");

	for (int i = 1; i < num_of_test; i++)
		printf("test#%02d | [%-10s]\r\n", item_list[i].function_id, item_list[i].function_name);

	return true;
}


void chip_sorting_routine(void)
{
	basic_test(1, (char *[]){"all", NULL});
	stc_test(2, (char *[]){"all", "100", NULL});
}


static uint8_t replay_ver(int argc, char *argv[])
{
	LOG_SHELL("Build timestamp: %s\n", __TIMESTAMP__);
	LOG_SHELL("Version: %s\n", GIT_VERSION);
	if (strcmp(CUSTOM_MSG, ""))
		LOG_SHELL("Custom msg: %s\n", CUSTOM_MSG);

	return true;
}

static uint8_t hbm3_temp_func(int argc, char **argv)
{
	icon_print_dram_temperature(icon_get_dram_temperature(get_hbm_cfg(CHIPLET_ID)));
	icon_print_channel_temperature(icon_get_channel_temperature(get_hbm_cfg(CHIPLET_ID)));

	return true;
}

static uint8_t hbm_perf_test_func(int argc, char **argv)
{
	uint64_t src_addr_base = 0x700000000ULL;
	uint64_t dst_addr_base = 0x800000000ULL;
	uint64_t src_addr, dst_addr;
	uint32_t trs_size = 0x80000000;
	uint8_t te_affinity = 0xff;
	uint32_t spl_grnl = 0xf;
	uint32_t iter = 1;
	uint32_t enable_compare = 1;
	char src_addr_str[32];
	char dst_addr_str[32];
	char trs_size_str[32];
	char te_affinity_str[32];
	char spl_grnl_str[32];
	char iter_str[32];
	char compare_str[32];
	char *rbdma_argv[7];

	/* Parse compare argument if provided */
	if (argc > 0) {
		enable_compare = (uint32_t)strtoul(argv[0], NULL, 16);
		if (enable_compare > 1) {
			printf("Invalid compare value. Using default: 1\r\n");
			enable_compare = 0;
		}
	}

	/* Calculate chiplet-specific addresses */
	src_addr = src_addr_base + (cur_cl_id * CHIPLET_OFFSET);
	dst_addr = dst_addr_base + (cur_cl_id * CHIPLET_OFFSET);

	/* Convert to hex strings for rbdma_perf_test */
	snprintf(src_addr_str, sizeof(src_addr_str), "%llx", src_addr);
	snprintf(dst_addr_str, sizeof(dst_addr_str), "%llx", dst_addr);
	snprintf(trs_size_str, sizeof(trs_size_str), "%x", trs_size);
	snprintf(te_affinity_str, sizeof(te_affinity_str), "%x", te_affinity);
	snprintf(spl_grnl_str, sizeof(spl_grnl_str), "%x", spl_grnl);
	snprintf(iter_str, sizeof(iter_str), "%x", iter);
	snprintf(compare_str, sizeof(compare_str), "%x", enable_compare);

	rbdma_argv[0] = src_addr_str;
	rbdma_argv[1] = dst_addr_str;
	rbdma_argv[2] = trs_size_str;
	rbdma_argv[3] = te_affinity_str;
	rbdma_argv[4] = spl_grnl_str;
	rbdma_argv[5] = iter_str;
	rbdma_argv[6] = compare_str;

	printf("HBM Perf Test - Chiplet %d\r\n", cur_cl_id);
	printf("  src_addr: 0x%llx\r\n", src_addr);
	printf("  dst_addr: 0x%llx\r\n", dst_addr);
	printf("  trs_size: 0x%x\r\n", trs_size);
	printf("  te_affinity: 0x%x\r\n", te_affinity);
	printf("  spl_grnl: 0x%x\r\n", spl_grnl);
	printf("  iter: %d\r\n", iter);
	printf("  compare: %d (%s)\r\n", enable_compare, enable_compare ? "enabled" : "disabled");

	return rbdma_perf_test(7, rbdma_argv);
}

static uint8_t hbm_perf_test_all_chiplet(int argc, char *argv[])
{
	int i;
	uint8_t test_result[4] = {0,};
	struct ici_chip_sorting_entry entry = {0};
	char compare_arg[8] = {'\0',};

	if (get_chiplet_id() != 0) {
		printf("only chiplet 0 is allowed to execute %s\r\n", __func__);
		return 0;
	}

	/* Parse compare argument if provided */
	if (argc > 0) {
		strncpy(compare_arg, argv[0], 7);
		strncpy(entry.arg, argv[0], 7);
	} else {
		/* Default: compare enabled */
		strncpy(compare_arg, "1", 7);
		strncpy(entry.arg, "1", 7);
	}

	printf("CL0: %s start\r\n", __func__);

	if (chiplet_count_opt > 1) {
		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_HBM_PERF_TEST;

		/* Send event to chiplet 1, 2, 3 */
		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);
	}

	/* Execute test on chiplet 0 */
	test_result[0] = hbm_perf_test_func(argc, argv);

	if (chiplet_count_opt > 1) {
		/* Wait for completion of chiplet 1, 2, 3 */
		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);

		/* Read results from chiplet 1, 2, 3 */
		read_entry(1, &entry);
		test_result[1] = entry.result;
		read_entry(2, &entry);
		test_result[2] = entry.result;
		read_entry(3, &entry);
		test_result[3] = entry.result;
	}

	/* Print results */
	for (i = 0; i < chiplet_count_opt; i++) {
		printf("test_result[%d]: %d\r\n", i, test_result[i]);
		if (test_result[i] != 1) {
			printf("flush mismatched data : %d\r\n", i);
			memcpy((void *)DATA_OUT_BASE_ADDR_CL(0),
				   (void *)DATA_OUT_BASE_ADDR_CL(i), SZ_64M);
			cpu_flush_dcache_range((uintptr_t)DATA_OUT_BASE_ADDR_CL(0), SZ_64M);
		}
	}

	/* Format and print final result */
	if (chiplet_count_opt > 1) {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s] / CL1:[%s] / CL2:[%s] / CL3:[%s]\0",
				 (test_result[0] == 1) ? "PASS" : "FAIL",
				 (test_result[1] == 1) ? "PASS" : "FAIL",
				 (test_result[2] == 1) ? "PASS" : "FAIL",
				 (test_result[3] == 1) ? "PASS" : "FAIL");
	} else {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s]",
				 (test_result[0] == 1) ? "PASS" : "FAIL");
	}
	printf("%s\r\n", (char *)ITER_RESULT_ADDR);
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	dsb();

	/* Check for any failures */
	for (i = 0; i < chiplet_count_opt; i++) {
		if (test_result[i] == -1)
			return -1;
	}

	printf("all hbm perf test done\r\n");

	return 1;
}

static uint8_t ucie_perf_test_func(int argc, char **argv)
{
	uint64_t src_addr_base = 0x700000000ULL;
	uint64_t dst_addr_base = 0x800000000ULL;
	uint64_t src_addr, dst_addr;
	uint32_t trs_size = 0x80000000;
	uint8_t te_affinity = 0xff;
	uint32_t spl_grnl = 0xf;
	uint32_t iter = 1;
	uint32_t enable_compare = 0;
	char src_addr_str[32];
	char dst_addr_str[32];
	char trs_size_str[32];
	char te_affinity_str[32];
	char spl_grnl_str[32];
	char iter_str[32];
	char compare_str[32];
	char *rbdma_argv[7];
	uint8_t ret;
	int chiplet_id;

	if (chiplet_count_opt != MAX_CHIPLET_COUNT) {
		printf("Skip UCIe Perf Test (Single Chiplet)\n");
		return true;
	}

	/* Parse compare argument if provided */
	if (argc > 0) {
		enable_compare = (uint32_t)strtoul(argv[0], NULL, 16);
		if (enable_compare > 1) {
			printf("Invalid compare value. Using default: 0\r\n");
			enable_compare = 0;
		}
	}

	/* Only chiplet 0 can execute this test */
	if (cur_cl_id != 0) {
		printf("Only chiplet 0 can execute this test. Current chiplet: %d\r\n", cur_cl_id);
		return false;
	}

	printf("UCIE Perf Test - Chiplet %d\r\n", cur_cl_id);
	printf("  trs_size: 0x%x\r\n", trs_size);
	printf("  te_affinity: 0x%x\r\n", te_affinity);
	printf("  spl_grnl: 0x%x\r\n", spl_grnl);
	printf("  iter: %d\r\n", iter);
	printf("  compare: %d (%s)\r\n", enable_compare, enable_compare ? "enabled" : "disabled");

	/* Prepare common parameters */
	snprintf(trs_size_str, sizeof(trs_size_str), "%x", trs_size);
	snprintf(te_affinity_str, sizeof(te_affinity_str), "%x", te_affinity);
	snprintf(spl_grnl_str, sizeof(spl_grnl_str), "%x", spl_grnl);
	snprintf(iter_str, sizeof(iter_str), "%x", iter);
	snprintf(compare_str, sizeof(compare_str), "%x", enable_compare);

	rbdma_argv[2] = trs_size_str;
	rbdma_argv[3] = te_affinity_str;
	rbdma_argv[4] = spl_grnl_str;
	rbdma_argv[5] = iter_str;
	rbdma_argv[6] = compare_str;

	/* First test: chiplet 1 */
	chiplet_id = 1;
	src_addr = src_addr_base + (chiplet_id * CHIPLET_OFFSET);
	dst_addr = dst_addr_base + (chiplet_id * CHIPLET_OFFSET);

	snprintf(src_addr_str, sizeof(src_addr_str), "%llx", src_addr);
	snprintf(dst_addr_str, sizeof(dst_addr_str), "%llx", dst_addr);

	rbdma_argv[0] = src_addr_str;
	rbdma_argv[1] = dst_addr_str;

	printf("\r\n--- Test 1: Chiplet %d ---\r\n", chiplet_id);
	printf("  src_addr: 0x%llx\r\n", src_addr);
	printf("  dst_addr: 0x%llx\r\n", dst_addr);

	ret = rbdma_perf_test(7, rbdma_argv);
	if (!ret) {
		printf("UCIE Perf Test 1 (Chiplet %d) FAILED\r\n", chiplet_id);
		return false;
	}
	printf("UCIE Perf Test 1 (Chiplet %d) PASSED\r\n", chiplet_id);

	/* Second test: chiplet 2 */
	chiplet_id = 2;
	src_addr = src_addr_base + (chiplet_id * CHIPLET_OFFSET);
	dst_addr = dst_addr_base + (chiplet_id * CHIPLET_OFFSET);

	snprintf(src_addr_str, sizeof(src_addr_str), "%llx", src_addr);
	snprintf(dst_addr_str, sizeof(dst_addr_str), "%llx", dst_addr);

	rbdma_argv[0] = src_addr_str;
	rbdma_argv[1] = dst_addr_str;

	printf("\r\n--- Test 2: Chiplet %d ---\r\n", chiplet_id);
	printf("  src_addr: 0x%llx\r\n", src_addr);
	printf("  dst_addr: 0x%llx\r\n", dst_addr);

	ret = rbdma_perf_test(7, rbdma_argv);
	if (!ret) {
		printf("UCIE Perf Test 2 (Chiplet %d) FAILED\r\n", chiplet_id);
		return false;
	}
	printf("UCIE Perf Test 2 (Chiplet %d) PASSED\r\n", chiplet_id);

	printf("\r\nUCIE Perf Test - All tests completed successfully\r\n");
	return true;
}

int preworking_autofetch(uint32_t offset)
{
	/*
	 * volatile required for hardware memory-mapped I/O access
	 * checkpatch: ignore volatile warning - hardware register access
	 */
	volatile uint64_t *cmd_ptr = (volatile uint64_t *)
		(DATA_CMD_BASE_ADDR_CL(cur_cl_id) + offset);
	volatile uint64_t *limit_addr = (volatile uint64_t *)
		(DATA_CMD_BASE_ADDR_CL(cur_cl_id) + PREWORKING_AUTOFETCH_LIMIT_OFFSET);
	cmd_count_t    dnc_acc;
	uint32_t    task_type = 0;
	uint32_t    dnc_id = 0;
	uint32_t    command = 0;
	uint32_t    cmd_stream_id = 0;
	uint32_t    rbdma_acc_count = 0;
	uint32_t    dnc_acc_count = 0;
	uint64_t    addr = 0;
	uint64_t    data = 0;

	memset(&dnc_acc, 0x0, sizeof(cmd_count_t));

	// parse packet
	while (1) {
		/*
		 * offset이 0 : ~ PREWORKING_AUTOFETCH_LIMIT_OFFSET
		 * offset : PREWORKING_AUTOFETCH OFFSET offset ~
		 */
		if (offset == 0 && (uintptr_t)cmd_ptr >= (uintptr_t)limit_addr)
			return 0;

		//RLOG_INFO("(ptr:%#lx)\t ", cmd_ptr);
		addr = *cmd_ptr;
		cmd_ptr++;
		data = *cmd_ptr;
		cmd_ptr++;

		//printf("[Packet] ADDR:%#lx, DATA:%#x\r\n", addr, data);

		if (addr != TYPE_EOF) {
			task_type = addr >> 32;
			dnc_id  = addr & 0xff;
			command = (addr & 0xff00)>>8;
			cmd_stream_id = (addr & 0xff0000)>>16;

			// check acc routine
			if (task_type == TYPE_RBDMA) {
				RLOG_INFO("RBDMA Accumulated Counter Checking...\r\n");
				rbdma_acc_count = data & 0xff;
				rbdma_done_acc_count(0, rbdma_acc_count);

			} else if (task_type == TYPE_DNC) {
				if (dnc_check_slot_mask(dnc_id) == RL_OK) {
					RLOG_INFO("DNC[%02d] CMD[%02x] Accumulated Counter Checking...\r\n",
						  dnc_id, command);
					// data info
					memcpy(&dnc_acc, &data, sizeof(cmd_count_t));

					if (command == (enum cmd_mode)COMP)
						dnc_acc_count = dnc_acc.comp_count; // skip comp tlb
					else if (command == (enum cmd_mode)LDuDMA)
						// skip comp tlb
						dnc_acc_count = dnc_acc.ldudma_tlb_count +
							dnc_acc.ldudma_count;
					else if (command == (enum cmd_mode)LPuDMA)
						dnc_acc_count = dnc_acc.lpudma_tlb_count + dnc_acc.lpudma_count;
					else if (command == (enum cmd_mode)STuDMA)
						dnc_acc_count = dnc_acc.studma_tlb_count + dnc_acc.studma_count;

					RLOG_INFO("DNC[%02d], CMD:[%02x], ACC#:[%d]\t\t",
						  dnc_id, command, dnc_acc_count);
					dnc_done_accumulate_count(dnc_id, command, dnc_acc_count);
					//udelay(1);
				}
			} else {
				if (addr >= (apply_cl_base(0x1FF3700000))) {
					// write addr & data
					// checkpatch: ignore volatile warning - hardware register access
					*(volatile uint32_t *)(uintptr_t)(addr) = (uint32_t)data;
				} else {
					int slot = dnc_detect_slot(addr);

					if (dnc_check_slot_mask(slot) == RL_OK) {
						// if cmd is comp, power throttling mode check
						// write addr & data
						// checkpatch: ignore volatile warning - hardware register access
						*(volatile uint32_t *)(uintptr_t)(addr) = (uint32_t)data;
					}
				}
			}
		} else {
			return 0;
		}
	}

	return -1;
}

int preworking_power_vector(void)
{
	return preworking_autofetch(0);
}

int precompare_power_vector(void)
{
	return preworking_autofetch(PREWORKING_AUTOFETCH_LIMIT_OFFSET);
}

uint8_t af_common_test(int argc, char *argv[])
{
	int loop = 1;
	int task_count = 1200;

	cpu_inv_dcache_range((uintptr_t)DATA_MEM_BASE_ADDR_CL(cur_cl_id), SZ_128M);
	cpu_inv_dcache_range((uintptr_t)DATA_CMD_BASE_ADDR_CL(cur_cl_id), SZ_1M);

	if (argc == 0) {
		printf("%s %s\r\n", __func__, "{cnt}");
		return false;
	} else if (argc <= 1) {
		loop = atoi(argv[0]);
	} else {
		printf("invalid argument\r\n");
		return false;
	}

	int is_pass = 0;

#if defined(POWER_MODE_TEST)
	pwr_gpio_set();
#endif

	for (int iter = 0; iter < loop; iter++) {
		if (iter == 0) {
			if (preworking_power_vector() < 0) {
				return false;
			}

			dnc_done_acc_count_all_clear(cur_cl_id);

			// 1. autofetch configure & preload comp task
			preload_comp_task(task_count);
		#ifdef SELF_TASK_FETCH_MODE
			dnc_selffetch_config(DNC_AUTOFETCH_TASK_FETCH_MODE_2, (enum cmd_mode)COMP, task_count);
			dnc_autofetch_cmgr(DNC_AUTOFETCH_MODE_REPORT_OFF);
		#else
			dnc_autofetch_config(DNC_AUTOFETCH_TASK_FETCH_MODE_1);
			dnc_autofetch_cmgr(DNC_AUTOFETCH_MODE_REPORT_OFF);
		#endif
		}
	#ifdef DNC_DISPLAY_DEBUG
		dnc_clear_profile_log();
	#endif

	#ifdef SELF_TASK_FETCH_MODE
		// 2. selffetch invoke
		dnc_selffetch_invoke((enum cmd_mode)COMP);

		// 3. wait for selffetch done
		for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
			dnc_done_accumulate_count(i, (enum cmd_mode)COMP, task_count);
	#else
		// 2. autofetch invoke
		dnc_autofetch_invoke((enum cmd_mode)COMP);

		// 3. wait for autofetch done
		for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
			dnc_done_accumulate_count(i, (enum cmd_mode)COMP, task_count + 1);
	#endif

		// 4. studma & rbdma store result data
		bool do_compare = (iter == loop - 1);

		if (do_compare) {
			precompare_power_vector();
			if (parse_mem_header_info(SKIP_CMP_SHM) < 0) {
				snprintf((char *)ITER_RESULT_ADDR, 100,
					"[TEST FAIL] (%d/%d) af common test\r\n", iter+1, loop);
				printf("%s", (char *)ITER_RESULT_ADDR);
				is_pass = 0;
			} else {
				printf(".");
				if ((iter & 0xF) == 0xF)
					printf("\n");
				is_pass = 1;
			}
		} else {
			printf(".");
			if ((iter & 0xF) == 0xF)
				printf("\n");
			is_pass = 1;
	}

	// 5. clear acc & reset autofetch address
	dnc_autofetch_addr_reset();
	rbdma_done_clear(cur_cl_id);
	dnc_done_acc_count_all_clear(cur_cl_id);

	if (iter == loop - 1) {
		dnc_autofetch_config(DNC_AUTOFETCH_TASK_FETCH_MODE_OFF);
		dnc_autofetch_cmgr(DNC_AUTOFETCH_MODE_2);
	#ifdef DNC_DISPLAY_DEBUG
		for (int dnc_id = 0; dnc_id < HW_SPEC_DNC_COUNT; dnc_id++)
			dnc_display_profile(dnc_id);
	#endif
	}

	if (is_pass == 0)
		return false;
	}
#if defined(POWER_MODE_TEST)
	pwr_gpio_unset();
#endif
	snprintf((char *)ITER_RESULT_ADDR, 100,
		"[TEST PASS] (%d/%d) af common test\r\n", loop, loop);
	printf("%s", (char *)ITER_RESULT_ADDR);
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);

	return true;
}

static uint8_t af_common_test_all_chiplet(int argc, char *argv[])
{
	int i;
	uint8_t test_result[4] = {0,};
	struct ici_chip_sorting_entry entry = {0};

	if (get_chiplet_id() != 0) {
		printf("only chiplet 0 is allowed to execute %s\r\n", __func__);
		return 0;
	}

	if (argc < 1) {
		printf("usage: %s {count}\r\n", __func__);
		return false;
	}
	entry.size = atoi(argv[0]);

	printf("CL0: %s start\r\n", __func__);

	if (chiplet_count_opt > 1) {
		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_AF_STC;

		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);
	}

	test_result[0] = af_common_test(argc, argv);

	if (chiplet_count_opt > 1) {
		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);
		read_entry(1, &entry);
		test_result[1] = entry.result;
		read_entry(2, &entry);
		test_result[2] = entry.result;
		read_entry(3, &entry);
		test_result[3] = entry.result;
	}

	for (i = 0; i < chiplet_count_opt; i++) {
		printf("test_result[%d]: %d\r\n", i, test_result[i]);
		if (test_result[i] != 1) {
			printf("flush mismatched data : %d\r\n", i);
			memcpy((void *)DATA_OUT_BASE_ADDR_CL(0),
				   (void *)DATA_OUT_BASE_ADDR_CL(i), SZ_64M);
			cpu_flush_dcache_range((uintptr_t)DATA_OUT_BASE_ADDR_CL(0), SZ_64M);
		}
	}

	if (chiplet_count_opt > 1) {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s] / CL1:[%s] / CL2:[%s] / CL3:[%s]\0",
				 (test_result[0] == 1) ? "PASS" : "FAIL",
				 (test_result[1] == 1) ? "PASS" : "FAIL",
				 (test_result[2] == 1) ? "PASS" : "FAIL",
				 (test_result[3] == 1) ? "PASS" : "FAIL");
	} else {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s]\0",
				 (test_result[0] == 1) ? "PASS" : "FAIL");
	}
	printf("%s\r\n", (char *)ITER_RESULT_ADDR);
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	dsb();

	for (i = 0; i < chiplet_count_opt; i++)
		if (test_result[i] == -1)
			return -1;

	printf("all af common test done\r\n");

	return 1;
}

static const char help_common_test_start[] = "[common_test_start] {count}\r\n"
	" * start common test\r\n"
	"\r\n";

static const char help_common_test_all_chiplet[] = "[common_test_all_chiplet] {count}\r\n"
	" * run common_test_start for all chiplet\r\n"
	"\r\n";

static const char help_af_common_test_all_chiplet[] = "[af_common_test_all_chiplet] {count}\r\n"
	" * run af_common_test for all chiplet\r\n"
	"\r\n";

static const char help_basic_test[] = "[basic_test] {idx}\r\n"
	" * start basic test, idx or all\r\n"
	"\r\n";

static const char help_stc_test[] = "[stc_test] {idx}\r\n"
	" * start stc test, idx or all\r\n"
	"\r\n";

static const char hbm3_temp_help[] = "[hbm3_temp]\n"
	" * HBM3 Temperature read\n"
	"\r\n";

static const char hbm_perf_test_help[] = "[hbm_perf_test]\n"
	" * HBM Performance test\n"
	" * ex) hbm_perf_test\n"
	"\r\n";

static const char ucie_perf_test_help[] = "[ucie_perf_test_help]\n"
	" * UCIE Performance test\n"
	" * ex) ucie_perf_test\n"
	"\r\n";

static uint8_t dram_harsh_stress_cli(int argc, char *argv[])
{
	int i;
	int iter_count = 1;
	uint8_t test_result[4] = {0,};
	struct ici_chip_sorting_entry entry = {0};

	if (get_chiplet_id() != 0) {
		printf("only chiplet 0 is allowed to execute %s\r\n", __func__);
		return 0;
	}

	if (argc > 0)
		iter_count = atoi(argv[0]);
	if (iter_count < 1)
		iter_count = 1;

	printf("=== DRAM Harsh Stress Test (iter=%d) ===\r\n", iter_count);

	if (chiplet_count_opt > 1) {
		entry.message_valid = 1;
		entry.task_type = TASK_TYPE_DRAM_HARSH_STRESS;
		entry.size = iter_count;

		ici_send_event_chip_sorting(&entry, 1);
		ici_send_event_chip_sorting(&entry, 2);
		ici_send_event_chip_sorting(&entry, 3);
	}

	test_result[0] = dram_harsh_stress_test(
		(void *)&(test_func_list){0, dram_harsh_stress_test,
			"dram_harsh_stress_test", {0, 0, (uint32_t)iter_count}});

	if (chiplet_count_opt > 1) {
		ici_message_receive_polling(1);
		ici_message_receive_polling(2);
		ici_message_receive_polling(3);

		read_entry(1, &entry);
		test_result[1] = entry.result;
		read_entry(2, &entry);
		test_result[2] = entry.result;
		read_entry(3, &entry);
		test_result[3] = entry.result;
	}

	for (i = 0; i < (int)chiplet_count_opt; i++)
		printf("CL%d: %s\r\n", i, (test_result[i] == 1) ? "PASS" : "FAIL");

	if (chiplet_count_opt > 1) {
		snprintf((char *)ITER_RESULT_ADDR, 100,
			 "CL0:[%s] / CL1:[%s] / CL2:[%s] / CL3:[%s]",
			 (test_result[0] == 1) ? "PASS" : "FAIL",
			 (test_result[1] == 1) ? "PASS" : "FAIL",
			 (test_result[2] == 1) ? "PASS" : "FAIL",
			 (test_result[3] == 1) ? "PASS" : "FAIL");
	} else {
		snprintf((char *)ITER_RESULT_ADDR, 100, "CL0:[%s]",
			 (test_result[0] == 1) ? "PASS" : "FAIL");
	}
	printf("%s\r\n", (char *)ITER_RESULT_ADDR);
	cpu_flush_dcache_range((uintptr_t)ITER_RESULT_ADDR, 100);
	dsb();

	for (i = 0; i < (int)chiplet_count_opt; i++)
		if (test_result[i] != 1)
			return -1;

	printf("all dram harsh stress test done\r\n");
	return 1;
}

CLI_REGISTER(common_test_start, NULL, common_test_start, help_common_test_start);
CLI_REGISTER(stc_test, NULL, stc_test, help_stc_test);
CLI_REGISTER(basic_test, NULL, basic_test, help_basic_test);
CLI_REGISTER(display_basic_test, NULL, display_basic_test, "[display_basic_test]\r\n * baisc_test item list\r\n\r\n");
CLI_REGISTER(shm_all_clear, NULL, shm_all_clear, "[shm_all_clear]\r\n * shared memory all clear\r\n\r\n");
CLI_REGISTER(ucie_stress_test, NULL, ucie_stress_test, "[ucie_stress_test]\r\n * infinite loop for ucie stress test\r\n\r\n");
CLI_REGISTER(ucie_stc_test, NULL, ucie_stc_test, "[ucie_stc_test]\r\n * run stc for all chiplets\r\n");
CLI_REGISTER(basic_test_all_chiplet, NULL, basic_test_all_chiplet, "[basic_test_all_chiplet]\r\n * run basic_test for all chiplet\r\n\r\n");
CLI_REGISTER(common_test_all_chiplet, NULL, common_test_all_chiplet, help_common_test_all_chiplet);
CLI_REGISTER(power_mode_ucie_test, NULL, power_mode_ucie_test, "[power_mode_ucie_test]\r\n * run powermode test for ucie\r\n\r\n");
CLI_REGISTER(replay_ver, NULL, replay_ver, "[replay_ver]\r\n * build timestamp, version info\r\n\r\n");
CLI_REGISTER(hbm3_temp, NULL, hbm3_temp_func, hbm3_temp_help);
CLI_REGISTER(hbm_perf_test, NULL, hbm_perf_test_func, hbm_perf_test_help);
CLI_REGISTER(hbm_perf_test_all_chiplet, NULL, hbm_perf_test_all_chiplet,
	"[hbm_perf_test_all_chiplet] {compare}\r\n * run hbm_perf_test for all chiplet\r\n * compare: 0=disabled, 1=enabled (default: 1)\r\n\r\n");
CLI_REGISTER(ucie_perf_test, NULL, ucie_perf_test_func, ucie_perf_test_help);
CLI_REGISTER(af_common_test, NULL, af_common_test, "[af_common_test]\r\n * run af common test\r\n\r\n");
CLI_REGISTER(af_common_test_all_chiplet, NULL, af_common_test_all_chiplet, help_af_common_test_all_chiplet);
CLI_REGISTER(dram_harsh_stress, NULL, dram_harsh_stress_cli,
	"[dram_harsh_stress] {iter_count}\r\n"
	" * DRAM harsh stress test on all chiplets\r\n"
	" * Generates max PI/SI noise via RBDMA + DCL IPs + UCIe\r\n"
	" * iter_count: number of stress iterations (default: 1)\r\n\r\n");
