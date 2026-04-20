/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file hc_int.h
 *
 * @brief Private APIs for the CMRT hash cores.
 */

#ifndef CMRT_HC_INT_H
#define CMRT_HC_INT_H

#include <stdint.h>
#include <stdbool.h>

#include <drivers/cmrt/dd.h>
#include "kat/hc_kat.h"

typedef struct cmrt_hc_dd {
	cmrt_dd_t dd;
	const struct hc_known *kat;
} cmrt_hc_dd_t;

#endif
