/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <cri/cmrt/dd.h>
#include <cri/cmrt/timer_reg.h>
#include "common.h"


enum perf_command {
	PERF_STATUS = 1,
	PERF_RESET = 2,
	PERF_GET_DATA = 4
};

struct perf_args {
	uint32_t command;
	/* just keep as of now */
	uint32_t args[2];
	uint32_t nbytes;
	uint8_t data[0];
};

enum {
	PERF_STATE_IDLE,
	PERF_STATE_INPROG
};

#define PERF_LOG_BUF_SIZE		8192
#define PERF_LOG_BUF_OUTBOUND		128
#define PERF_LOG_TOT_BUF		(PERF_LOG_BUF_SIZE + PERF_LOG_BUF_OUTBOUND)

struct perf_log {
	int32_t status;
	int32_t size;
	uint8_t 	data[PERF_LOG_TOT_BUF];
} perf;

static uint32_t cycle_ref_low, cycle_ref_high;

int plog_init(void)
{
	return 0;
}

int plog_reset(void)
{
	perf.size = 0;
	perf.data[0] = 0;
	perf.status = PERF_STATE_IDLE;
	return 0;
}

void plog_set_ref (void)
{
	perf.status = PERF_STATE_INPROG;

	cycle_ref_high = cri_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_HIGH);
	cycle_ref_low = cri_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_LOW);
	uint32_t high2 = cri_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_HIGH);
	/*
	 * 2 gibicycles is more than enough to complete the above three
	 * cri_read_reg() calls (and if not all certainty is lost anyway).
	 */
	if (cycle_ref_high != high2 && cycle_ref_low < (1 << 31)) {
		cycle_ref_high = high2;
	}
}

uint32_t plog_get_cycles(void)
{
	uint32_t now_high = cri_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_HIGH);
	uint32_t now_low = cri_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_LOW);
	uint32_t now_high_2 = cri_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_HIGH);

	if (now_high != now_high_2 && now_low < (1 << 31)) {
		now_high = now_high_2;
	}

	switch (now_high - cycle_ref_high) {
	case 0:
		break;
	case 1:
		if (now_low < cycle_ref_low) {
			break;
		}
#if __GNUC__ >= 7 || defined (__clang__) && __clang_major__ >= 12
		__attribute__ ((fallthrough));
#endif
	default:
/*
		log("ERROR: Cycle counter rotated %d times\n",
		    now_high - cycle_ref_high);
		log("ref_hi:%u, ref_lo:%u, now_hi:%u, now_lo:%u\n",
		    cycle_ref_high, cycle_ref_low, now_high, now_low);
*/
		return 0;
	}
	return now_low - cycle_ref_low;
}

uint8_t *plog_log_at (void)
{
	/* calc new address to append new data */
	perf.size += strlen(perf.data + perf.size);
	if (perf.size) {
		strcpy(perf.data + perf.size, "\n");
		perf.size += 1;
	}
	if (perf.size >= PERF_LOG_BUF_SIZE) {
		/* will corrupt adjacent memory data.
		safer, reset to zero (circular buffer) */
		perf.size = 0;
	}
	/*
	printk("\nplog_log_at = %x ; size = %d",
		(uint32_t)(perf.data + perf.size), perf.size);
	*/
	return (perf.data + perf.size);
}

static int perf_run(void *input, uint32_t in_used,
		   void *output, uint32_t *out_used, uint32_t out_size)
{
	struct perf_args *args = input;
	uint32_t size = 0;
	if (args->command == PERF_GET_DATA) {
		/* plog_log_at(); */
		size = strlen(perf.data);
		memcpy(output, perf.data, size);
		/*
		printk("%s\nstr size = %d\nHex :", perf.data, size);
		for (int i = 0; i < size; i++) {
			printk("%x ", ((uint8_t *)output)[i]);
		}
		*/
		*out_used = size;
		return 0;
	} else if (args->command == PERF_STATUS) {
		sprintf(output, "\nAllocation : STATIC\nSize : %d\nUsed : %d\nTYPE : Circular",
			PERF_LOG_BUF_SIZE, strlen(perf.data));
		*out_used = strlen(output);
		return 0;
	} else if (args->command == PERF_RESET) {
		plog_reset();
		sprintf(output, " RESET done\n");
		*out_used = strlen(output);
		return 0;
	} else {
		*out_used = size;
		return -1;
	}
}

const cmd_t cmd_perf = { CMDID_PERF, "Perf", "Performance Cycles data", perf_run };
