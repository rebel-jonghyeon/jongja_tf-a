/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#ifndef CRI_PKE_STANDALONE
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/util.h>

#include <drivers/cmrt/pke4/pke4_driver.h>
#include <drivers/cmrt/pke4/pke4_reg.h>
#else

#include "pke4_driver.h"
#include "pke4_reg.h"
#endif

#include "pke4_random.h"

#ifndef CRI_PKE_STANDALONE

int cmrt_pke_get_true_random(void *buf, size_t len)
{
	struct iov v = { buf, len };
	if (cmrt_get_randomv(&v, 1) < 0) {
		return -EIO;
	}
	return 0;
}
#else
extern int cmrt_pke_get_true_random(void *buf, size_t len);
#endif

int cmrt_pke_get_pseudo_random(void *buf, size_t len, int32_t slot, uint32_t slot_length)
{
	int ret = 0;

	uint32_t length = 0;
	uint32_t bits;
	uint32_t slot_len;

#ifdef CONFIG_CMRT_PKE_32_BIT
	if (len < MAU_READ_REG(R_MAU_MIN_LEN) * sizeof(uint32_t)) {
		length = MAU_READ_REG(R_MAU_MIN_LEN);
	} else {
		length = ((len - 1) / sizeof(uint32_t)) + 1;
	}
	bits = length * 32;
#else /* 64-bit */
	if (len < MAU_READ_REG(R_MAU_MIN_LEN) * sizeof(uint64_t)) {
		length = MAU_READ_REG(R_MAU_MIN_LEN);
	} else {
		length = ((len - 1) / sizeof(uint64_t)) + 1;
	}
	bits = length * 64;
#endif

	if (slot_length < MAU_READ_REG(R_MAU_MIN_LEN)) {
		slot_len = MAU_READ_REG(R_MAU_MIN_LEN);
	} else {
		slot_len = slot_length;
	}

	ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, slot_len);
	if (slot == CMRT_PKE_NO_SLOT) {
		ISSUE_MAU_COMMAND(SET_MAND, SLOT(0), length);
	} else {
		ISSUE_MAU_COMMAND(SET_MAND, SLOT(slot), length);
	}
	ISSUE_MAU_COMMAND(COPY, R_MAU_ADDR_RNG, length);

	ret = cmrt_pke_wait();
	if (ret) {
		goto err;
	}

	if (buf != NULL) {
		if (slot == CMRT_PKE_NO_SLOT) {
			memcpy(buf, pke_addr(0, NULL, bits), len);
		} else {
			memcpy(buf, pke_addr(slot, NULL, bits), len);
		}
	}
err:
	return ret;
}
