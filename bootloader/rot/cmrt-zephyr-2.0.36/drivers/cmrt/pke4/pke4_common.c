/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#ifndef CRI_PKE_STANDALONE
#include <device.h>
#include <init.h>
#include <kernel.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>

#include <drivers/cmrt/crypto/pke_dpasl.h>
#include <drivers/cmrt/crypto/pke_common.h>

#include <drivers/cmrt/pke4/pke4_driver.h>
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#endif

#if defined(ENABLE_MAU_STATISTICS) || defined(DEBUG_MAU_COMMANDS)
#include <sys/printk.h>

enum {
	MAU_CMD_OPCODE_POS = 25,
	MAU_CMD_OPCODE_SIZE = 7,
	OP_CODE_MASK = 0x7f,
	STAT_COUNT = 0x20
};
unsigned counter[STAT_COUNT] = {0};

void mau_statistics(uint32_t reset, uint32_t print)
{
	if (print) {
		printk("TOTAL   LOAD  STORE SMDL   SPAR  COPY  MADD  MSUB  SMAND MMUL  SMQ   IMUL  MON   IADD  ISUB  COMP  IDSE\n");
		printk("%07u %05u %05u %05u %05u %05u %05u %05u %05u %05u %05u %05u %05u %05u %05u %05u %05u\n",
		       counter[0], counter[LOAD], counter[STORE],
		       counter[STORE_MOD_DBL], counter[SET_PARAMS], counter[COPY],
		       counter[MOD_ADD], counter[MOD_SUB], counter[SET_MAND],
		       counter[MONT_MUL], counter[STORE_MONT_SQR], counter[INT_MUL],
		       counter[MONTGOMERIZE], counter[INT_ADD], counter[INT_SUB],
		       counter[COMPARE], counter[INT_DIV_SMALL_EXACT]);
	}
	if (reset) {
		for (int i = 0; i < STAT_COUNT; ++i)
			counter[i] = 0;
	}
}

void update_mau_statistics(uint32_t cmd)
{
#ifdef ENABLE_MAU_STATISTICS
	uint32_t mauOPCODE = ((cmd >> MAU_CMD_OPCODE_POS) &
			      ((1 << MAU_CMD_OPCODE_SIZE) - 1));
	++counter[mauOPCODE];
	++counter[0];
#endif
#ifdef DEBUG_MAU_COMMANDS
	printk("MAU_COMMAND: cmd:0x%02x addr:0x%03x len:0x%03x\n",
	       cmd >> 25, (cmd >> 10) & ((1 << 10) - 1),
	       (cmd & ((1 << 10) - 1)));
#endif
}
#endif
