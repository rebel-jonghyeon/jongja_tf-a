/*
 * Copyright (c) 2019-2024 Cryptography Research, Inc. (CRI).
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

int cmrt_pke_generate_prime(cmrt_pke_t pke,
			   uint32_t bits,
			   uint8_t slot_number,
			   uint8_t flags)
{
	int ret = -EIO;

	const uint32_t minimum[] = { 0x754abe9f, 0x597d89b3, 0xf9de6484, 0xb504f333 };

	uint32_t counter = 0;
	uint32_t test;
	uint32_t *result = pke_addr(slot_number, NULL, bits);
	uint32_t length = bits / 32;
	uint32_t prime = 0;

	do {
		ret = cmrt_pke_get_true_random(result, length * sizeof(uint32_t));
		if (ret) {
			goto err;
		}

		result[0] |= 1;

		test = 0;
		if (result[length - 1] > minimum[3]) {
			test = 1;
		} else if ((result[length - 1] == minimum[3]) &&
			   (result[length - 2] > minimum[2])) {
			test = 1;
		} else if ((result[length - 1] == minimum[3]) &&
			   (result[length - 2] == minimum[2]) &&
			   (result[length - 3] > minimum[1])) {
			test = 1;
		} else if ((result[length - 1] == minimum[3]) &&
			   (result[length - 2] == minimum[2]) &&
			   (result[length - 3] == minimum[1]) &&
			   (result[length - 4] > minimum[0])) {
			test = 1;
		}

		if (test == 1) {
			ret = cmrt_pke_is_probable_prime(pke, bits, slot_number, &prime);
			if (ret) {
				goto err;
			}
		}

		counter++;
	} while ((prime == 0) && (counter < 5 * bits));

	if (prime == 1) {
		ret = 0;
	} else {
		ret = -ERANGE;
	}
err:
	return ret;
}
