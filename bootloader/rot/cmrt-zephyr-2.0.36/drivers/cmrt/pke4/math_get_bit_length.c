/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#ifndef CRI_PKE_STANDALONE
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/pke4/pke4_driver.h>
#include <drivers/cmrt/pke4/pke4_math.h>
#else
#include "pke.h"
#include "pke4_driver.h"
#include "pke4_math.h"
#endif

/* This function is not side channel resistant */
int cmrt_pke_get_bit_length(uint32_t *a,
			    const size_t length,
			    uint32_t *bit_length)
{
	int i, j;

	uint32_t found = 0;

	i = length - 1;
	*bit_length = length * 32;
	while ((found == 0) && (i >= 0)) {
		j = 31;
		while ((found == 0) && (j >= 0)) {
			if (((a[i] >> j) & 1) == 1) {
				found = 1;
			} else {
				*bit_length = *bit_length - 1;
				j--;
			}
		}
		i--;
	}

	return 0;
}
