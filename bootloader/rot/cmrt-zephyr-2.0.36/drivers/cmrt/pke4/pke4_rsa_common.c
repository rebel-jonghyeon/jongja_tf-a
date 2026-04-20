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
#include <drivers/cmrt/pke4/pke4_math.h>
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#include "pke4_math.h"
#endif
#include "pke4_random.h"

int copy_rsa_parameters_to_pke(const cmrt_pke_copy_inputs *in)
{
	int ret = 0;

	uint32_t i;
#ifdef CMRT_PKE_CP_RANDOM_ORDER
	int j;

	uint8_t order[PKE_CP_ORDER_SIZE];
	uint8_t ordering[PKE_CP_ORDER_SIZE];
	uint8_t tmp;
#endif

	uint32_t *d1_ptr;
	uint32_t *d2_ptr;
	uint32_t *tmp_ptr;
	uint32_t iw;

#ifdef CMRT_PKE_CP_RANDOM_ORDER
	uint32_t wlength = ((in->length - 1) / sizeof(uint32_t) + 1);
	uint32_t rorder_length;

	ret = cmrt_pke_get_pseudo_random(ordering, PKE_CP_ORDER_SIZE, CMRT_PKE_NO_SLOT, 0);
	if (ret) {
		goto err;
	}

	if (wlength < PKE_CP_ORDER_SIZE) {
		rorder_length = wlength;
	} else {
		rorder_length = PKE_CP_ORDER_SIZE;
	}

	for (i = 0; i < rorder_length; i++) {
		order[i] = i;
	}

	for (i = 0; i < rorder_length; i++) {
		j = ordering[i] & (rorder_length - 1);
		tmp = order[i];
		order[i] = order[j];
		order[j] = tmp;
	}
#endif

	for (i = 0; (i < in->copies_to_make) && (ret == 0); i++) {
		if (in->copy_command[i].in != NULL) {
			memcpy(in->copy_command[i].out, in->copy_command[i].in, in->length);
		}
	}

#ifdef CONFIG_CMRT_PKE_32_BIT
	ret = cmrt_pke_get_pseudo_random(NULL, in->length, rsa_sign_tmp, in->length / sizeof(uint32_t));
#else /* 64-bit */
	ret = cmrt_pke_get_pseudo_random(NULL, in->length, rsa_sign_tmp, in->length / sizeof(uint64_t));
#endif
	if (ret) {
		goto err;
	}

	tmp_ptr = pke_addr(rsa_sign_tmp, NULL, in->length * 8);
	d1_ptr = pke_addr(rsa_sign_d0, NULL, in->length * 8);
	d2_ptr = pke_addr(rsa_sign_d1, NULL, in->length * 8);
	/* reblind private key */
	for (i = 0; i < (in->length / sizeof(uint32_t)); i++) {
		/* compute in random order? */
#ifdef CMRT_PKE_CP_RANDOM_ORDER
		iw = (i & 0xFFFE0) + order[i & 0x1f];
#else
		iw = i;
#endif

		d1_ptr[iw] ^= tmp_ptr[iw];
		d2_ptr[iw] ^= tmp_ptr[iw];
	}

err:
	return ret;
}
