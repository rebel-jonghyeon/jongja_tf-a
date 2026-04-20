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

#ifndef _REPLAY_H_
#define _REPLAY_H_

#include "FreeRTOS.h"
#include "task.h"

#include <stdint.h>
#include <stdbool.h>
#include "hal/hw_spec.h"
#include "hal/interrupt.h"
#include "common/command.h"
#include "common/ici.h"

#define BW_PROFILE

#define INVALID_DEP_SLOT_MASK	UINT64_MAX

#define PASS    (1)
#define FAIL    (0)
/* primitive vector */
#define HEADER_SIZE (32)
#define MAX_HEADER_PCK  (1024)

/* Host I/F w/ hdma */
#define TC_INFO_ADDR	((uintptr_t)0x7FDF00000)    //((uintptr_t)0x7FDF00000)
#define HDMA_DESC_BASE_ADDR	(0x7FE000000)    //((uintptr_t)0x7FE000000)
#define ITER_RESULT_ADDR (0x7FDE00000)
#define HDMA_DESC_OFFSET_INCR (0x100000)
#define HDMA_DESC_ADDR(channel_idx) (*((volatile struct hdma_desc *)(uintptr_t)(HDMA_DESC_BASE_ADDR + ((channel_idx)*HDMA_DESC_OFFSET_INCR))))

#define HDMA_EN_CH_WRCH_BASE	(0x1D80380000ULL)
#define HDMA_DOORBELL_WRCH_TRIGGER_BASE	(0x1D80380004ULL)
#define HDMA_CHANNEL_OFFSET_INCR (0x1000)
#define HDMA_EN_CH_WRCH(idx)						\
	(*((volatile uint32_t *)(uintptr_t)(HDMA_EN_CH_WRCH_BASE +	\
	((idx) * HDMA_CHANNEL_OFFSET_INCR))))
#define HDMA_DOORBELL_WRCH_TRIGGER(idx)					\
	(*((volatile uint32_t *)(uintptr_t)(HDMA_DOORBELL_WRCH_TRIGGER_BASE + \
	((idx) * HDMA_CHANNEL_OFFSET_INCR))))
/* HDMA Channel Register Information*/
// WR -> D2H / RD -> H2D
// WRCH_0 : 0x1D80380000
// RDCH_0 : 0x1D80380800
// WRCH_1 : 0x1D80381000
// RDCH_1 : 0x1D80381800
// ...

#define RBDMA_UCIE_STRESS_SRC_ADDR(x) (cl_base[(x)] + 0x600000000)
#define RBDMA_UCIE_STRESS_DST_ADDR(x) (cl_base[(x)] + 0x700000000)

/* CP1 is not used in cp-replayer; use as base (FW_CP1_BASE) */
#define REPLAY_BASE_ADDR		(0x780000000)
#define COMMAND_START			(0x1234)
#define DUMP_END				(0xFFFFFFFF)

#define STRM_COUNT 6
#define STRM_CONTROL 5
#define TOTAL_DUMP_SIZE		(SZ_1M * 128)
#define TOTAL_UNITS (4 * HW_SPEC_DNC_COUNT + 1 + 1)
#define UNIT_DUMP_SIZE ((TOTAL_DUMP_SIZE / TOTAL_UNITS) & ~0x7) /* 8Byte aligned */
#define GSN_WINDOW_SIZE 8192

enum ici_function_type {
	ICI_STRESS_TEST_START,
	ICI_STC_TEST_START,
	ICI_BASIC_TEST_START,
	ICI_REPLAY_TEST_START,
	ICI_UCIE_STC_STRESS_START,
	ICI_POWER_MODE_UCIE_TEST_START,
	ICI_HBM_PERF_TEST_START,
	ICI_AF_STC_TEST_START,
	ICI_QUAD_REPLAY_TEST_START,
	ICI_DRAM_HARSH_STRESS_START,
};
struct ici_callback_data {
	enum ici_function_type func_type;
	int size;
	char arg[8];
};


void replay_task_init(TaskHandle_t handle);
void replay_task(void *pvParameters);
void logbuf_init(uint32_t cl_id);
void hw_init(void);
void sw_init(void);

uint8_t common_test_start(int argc, char *argv[]);
uint8_t af_common_test(int argc, char *argv[]);

void log_test_result(const char *module, const char *test_name, const char *status);

void replay_init(uint32_t cl_id);
void trace_cmd_identify(int cmd_id);
void load_stc_data(int idx);
void replay_dnc_notify(union irq_info irq_data);
void replay_rbdma_notify(uint32_t cmd_id);
void replay_routine(void);

void chip_sorting_routine(void);

static uint8_t power_mode_ucie_test(int argc, char *argv[]);

void ici_callback_task(void *pvParameters);
void ici_callback_trigger(struct ici_callback_data callback_data);
void ici_callback_pick_rbdma_stc_data(struct ici_chip_sorting_entry entry);
void ici_callback_pick_rbdma_replay_test_data(struct ici_chip_sorting_entry entry);
void ici_trigger_ucie_stc_stress_test(int iter_count);
void ici_trigger_stc_test(struct ici_callback_data c_data);
void ici_trigger_af_common_test(struct ici_callback_data c_data);
void ici_trigger_ucie_quad_replay_test(char arg[], int iter_size);
void ici_trigger_ucie_basic_test(char arg[], int iter_size);
void ici_trigger_hbm_perf_test(char arg[]);
void ici_trigger_dram_harsh_stress(int iter_count);
int trigger_ucie_stress_test(void);

void print_tc_info(void);

uint8_t rbln_test_main(int argc, char *argv[]);

/* Bandwidth measurement functions */
uint64_t bw_measure_start(void);
void bw_measure_end_and_print(uint64_t start_cycle,
	uint64_t total_bytes, uint64_t cpu_freq, int print_bw);

#endif /* _REPLAY_H_ */
