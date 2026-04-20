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

#ifndef _COMMON_TEST_H_
#define _COMMON_TEST_H_

#include <stdint.h>
#include <stdbool.h>
#include "hal/dnc_if.h"
#include "hal/dnc/dnc_if_evt0.h"
#include "hal/hw_spec.h"
#include "hal/interrupt.h"
#include "common/command.h"

#define PAGE_SIZE_2MB	(2 * 1024 * 1024)
#define UDMA_MAX_TRANSFER_SIZE (4 * 1024 * 1024)

// PA = VA - 0x100000000 + 0x40000000
static inline uint64_t apply_cl_base(uint64_t base_offset) {
	return cl_base[cur_cl_id] + base_offset;
}

#define DATA_MEM_BASE_ADDR_CL(x) (cl_base[(x)] + 0x60000000)
#define DATA_CMD_BASE_ADDR_CL(x) (cl_base[(x)] + 0x54200000)
#define DATA_OUT_BASE_ADDR_CL(x) (cl_base[(x)] + 0x80000000)

#define DATA_MEM_BASE_ADDR	(apply_cl_base(0x60000000))	// input data
#define DATA_CMD_BASE_ADDR	(apply_cl_base(0x54200000)) // command data
#define DATA_OUT_BASE_ADDR	(apply_cl_base(0x80000000))	// output data

//#define MEM_DATA_SIZE (0x4400000)	//evt0
#define MEM_DATA_SIZE (0x8000000)

#define CMD_DATA_SIZE (0x20000)
//#define PREWORKING_AUTOFETCH_LIMIT_OFFSET (0x00001FE0) // stc_3001L nc_half
#define PREWORKING_AUTOFETCH_LIMIT_OFFSET (0x00002070) // stc_3001L nc_rdcd
//#define PREWORKING_AUTOFETCH_LIMIT_OFFSET (0x00001C90) // stc_3004L nc_rdcd

#define PRELOAD_COMP_TASK_ISIZE (0x2280) // stc_3001L nc_half, stc_3001L nc_rdcd
//#define PRELOAD_COMP_TASK_ISIZE (0x2000) // stc_3004L nc_rdcd

// new macros to applied CL base offset
#define DCL0_SP_MEM_BASE_CL apply_cl_base(DCL0_SP_MEM_BASE)
#define DCL1_SP_MEM_BASE_CL apply_cl_base(DCL1_SP_MEM_BASE)
#define DCL0_SH_MEM_BASE_CL apply_cl_base(DCL0_SH_MEM_BASE)
#define DCL1_SH_MEM_BASE_CL apply_cl_base(DCL1_SH_MEM_BASE)

#define TYPE_CMDID      (0xC3DID)
#define TYPE_EOF        (0xE0F0000C3DULL)
#define TYPE_RBDMA      (0xDD3A)
#define TYPE_DNC        (0xD17C)
#define TYPE_POWER_VECTOR	(0xD17C9A0F7EC70000)

#define TLB_QUEUE_SIZE  (16)

enum cmp_header_type {
	ALL_CMP = 0,
	SKIP_CMP_SHM = 1,
};

enum data_type{
	INIT_DATA	= 0,
	SP_DATA		,
	SHM_DATA	,
	FINAL_SP_DATA	,
	FINAL_SHM_DATA	,
};

enum cmd_mode{
    COMP = 0,
    LDuDMA,
    LPuDMA,
    STuDMA,
};

typedef struct{
	uint16_t	type;		// type of data
	uint16_t	dnc_id;		// dnc_id
	uint32_t	db_cur_offset_addr;		//cur address in db
	uint32_t	db_next_offset_addr;	//next address in db
	uint32_t	start_addr;		//memory address
	uint32_t	size;
	uint32_t 	start_slot;
	uint32_t 	num_of_slot;
	uint32_t	reserved;
} __attribute__((packed)) mem_data_header_t;

typedef struct{
	unsigned long long	addr;
	unsigned long long	data;
} cmd_stream_t;

typedef struct{
    uint8_t ldudma_tlb_count;
    uint8_t ldudma_count;
    uint8_t lpudma_tlb_count;
    uint8_t lpudma_count;
    uint8_t studma_tlb_count;
    uint8_t studma_count;
    uint8_t comp_tlb_count;
    uint8_t comp_count;
} __attribute__((packed)) cmd_count_t;

typedef int (*CommonTestFunction)(void *ctx);

/* Exception flag accessors.
 *
 * The underlying state is a file-scope static variable in replay.c, accessed
 * only through these helpers. Marked by shm/dnc/rbdma exception handlers during
 * test execution. Cleared by the test loop before each test, checked after
 * test returns. Allows any test function to be failed when an exception
 * handler fires, regardless of whether the function itself performs data
 * comparison.
 *
 * Implementation uses __atomic_* with ACQUIRE/RELEASE ordering to ensure
 * correct visibility across cores (SMP) and between IRQ handlers and
 * the main test loop.
 */
void test_exception_mark(void);
void test_exception_clear(void);
bool test_exception_occurred(void);

#define MAX_RESULT_COUNT	2	/* Maximum number of results per workload */

/* Comparison mode for result verification */
#define COMPARE_MODE_CHIPLET0_ONLY	0	/* Compare only chiplet0's result with golden */
#define COMPARE_MODE_PER_CHIPLET		1	/* Compare each chiplet's result with its own golden */

typedef struct{
	uint32_t	model_id;
	const char *model_name;
	uint32_t	result_count;					/* Number of results (1 to MAX_RESULT_COUNT) */
	uint32_t	compare_mode;					/* CHIPLET0_ONLY or PER_CHIPLET */
	uint64_t	result_addr[MAX_RESULT_COUNT];	/* Array of result addresses */
	uint64_t	golden_addr[MAX_RESULT_COUNT];	/* Array of golden addresses */
	uint32_t	out_size[MAX_RESULT_COUNT];		/* Array of output sizes */
} workload_list;

enum memory_type {
	DRAM,
	SHM,
	SP
};

struct test_ctx_args {
	enum memory_type dma_src_dev;
	enum memory_type dma_dst_dev;
	uint32_t trans_size;
	uint32_t is_ucie_stress_test;
};

typedef struct {
	uint32_t function_id;
	CommonTestFunction pfunc;
	const char *function_name;

	struct test_ctx_args args;
} test_func_list;

typedef struct{
	uint32_t is_valid[TLB_QUEUE_SIZE];
	uint32_t addr[TLB_QUEUE_SIZE];
} tlb_set_t;

int rdsn_config_test(void *ctx);
int tsync_test(void *ctx);
int shm_tpg_test(void *ctx);

int rbdma_common_test_func(void *ctx);

int rbdma_dram_2_shm(void *ctx);		//4MB

int ldudma_dram_2_sp(void *ctx);
int ldudma_4MB_near_sp(void *ctx);
int ldudma_4MB_far_sp(void *ctx);
int ldudma_4MB_near_shm(void *ctx);
int ldudma_4MB_far_shm(void *ctx);

int lpudma_dram_2_sp(void *ctx);
int lpudma_4MB_near_sp(void *ctx);
int lpudma_4MB_far_sp(void *ctx);
int lpudma_4MB_near_shm(void *ctx);
int lpudma_4MB_far_shm(void *ctx);

int studma_sp_2_dram(void *ctx);
int studma_4MB_near_sp(void *ctx);
int studma_4MB_far_sp(void *ctx);
int studma_4MB_near_shm(void *ctx);
int studma_4MB_far_shm(void *ctx);

int rbdma_dram_2_dram_all_port(void *ctx);
int rbdma_burst_length(void *ctx);
int rbdma_large_memory_copy(void *ctx);

int rbdma_shm_2_shm(void *ctx);
int rbdma_dram_2_shm_tsync(void *ctx);
int rbdma_shm_2_dram_tsync(void *ctx);
int sp_tpg_test(void *ctx);
int ucie_sanity_test(void *ctx);
int ucie_test(void *ctx);
int dcl_stress_test(void *ctx);
int dram_harsh_stress_test(void *ctx);
int dram_all_array_test(void *ctx);

void dummy_function(void);
void tlb_table_init(void);
int insert_or_find_tlb(uint8_t dnc_id, uint8_t cmd, uint64_t addr, uint32_t size);

int parse_command_info(bool do_compare);
int parse_mem_header_info(enum cmp_header_type cmp_header_type);
int run_common_test(bool do_compare);
int rbdma_data_shift(void *ctx);
int rbdma_sct_gth(void *ctx);
int rbdma_sct_gth_w_regular(void *ctx);
int rbdma_report_dump(void *ctx);

int cmgr_dnc_interop_test(void *ctx);
int cmgr_rbdma_interop_test(void *ctx);

int dnc_report_cdump(void);

uint8_t ldudma_test(int argc, char *argv[]);
uint8_t lpudma_test(int argc, char *argv[]);
uint8_t studma_test(int argc, char *argv[]);
uint8_t checksum_test(int argc, char *argv[]);
uint8_t rbdma_test(int argc, char *argv[]);

/* STC vector */
int result_compare(uintptr_t addr, uint32_t size);
/* Unit vector */
int basic_test_compare(uint64_t src_addr, uint64_t dst_addr, uint32_t size);

uint64_t gen_states(uint64_t* state);
uint64_t gen_64b_rand(uint64_t s[4]);
void rand_fill(void *addr, size_t size);

int preworking_power_vector(void);
int precompare_power_vector(void);

#endif /* _COMMON_TEST_H_ */
