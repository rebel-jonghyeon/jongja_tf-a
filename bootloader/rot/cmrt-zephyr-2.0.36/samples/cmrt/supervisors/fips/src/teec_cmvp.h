/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_TEEC_H
#define CMRT_TEEC_H

#include <stdint.h>
#include <stddef.h>

#include <cri/cmrt/fips/fips_types.h>

#include "cmvp_sw.h"
#include "fips.h"

#define FIPS_LOCAL_ADDRESS ((int) ('F'+'I'+'P'+'S'))

typedef struct {
	size_t size;
	uint8_t *data;
} io_t;

int process_tee_message(fips_state_t *state, io_t *input);

#endif
