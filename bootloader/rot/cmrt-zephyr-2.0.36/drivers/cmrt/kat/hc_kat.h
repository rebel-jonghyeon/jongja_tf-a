/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_HC_KAT_H
#define CMRT_HC_KAT_H

#include <device.h>
#include <drivers/cmrt/dd.h>


typedef struct hc_kat {
	cmrt_hash_algo_t algo;
	const uint8_t *key;
	size_t keylen;
	const uint8_t *input;
	size_t inlen;
	const uint8_t *output;
	size_t outlen;
} hc_kat_t;

struct hc_known {
	size_t n;
	const struct hc_kat *v;
};

extern const struct hc_known s2hc_known;
extern const struct hc_known s3hc_known;

int hc_init_kat(const struct device *dev);
void hc_open_kat(cmrt_dd_context_t *context);

#endif
