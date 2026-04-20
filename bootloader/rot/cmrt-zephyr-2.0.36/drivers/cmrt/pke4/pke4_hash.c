/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#include <device.h>
#include <init.h>
#include <kernel.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>

#include "pke4_hash.h"

/*!
 * Hash regions.
 * @param algo hash algorithm to use
 * @param v vector of regions to hash
 * @param nv number of elements in \a v
 * @param phash output buffer for hash
 * @param nhash sizeo of \a phash
 * @return byte required for \a phash, or negative
 */
int get_hashv(uint32_t algo, const struct iov *v, size_t nv, void *phash,
	      size_t nhash)
{
	cmrt_hc_t hc = (cmrt_hc_t)cmrt_dd_open(DEVICE_DT_GET(DT_CHOSEN(rambus_pke_hc)), 0, NULL);
	if (hc == CMRT_INVALID_HANDLE) {
		return -ENODEV;
	}
	int res = cmrt_hc_init(hc, algo, NULL, 0);
	if (res != 0) {
		goto err;
	}
	for (; nv > 1u; --nv, ++v) {
		res = cmrt_hc_update(hc, v->p, v->n);
		if (res != 0) {
			goto err;
		}
	}
	res = cmrt_hc_final(hc, v->p, v->n, phash, &nhash);
	if (res == 0) {
		res = nhash;
	}
err:
	cmrt_hc_close(hc);
	return res;
}

int get_hash(uint32_t algo, const void *bufp, size_t size,
	     void *phash, size_t nhash)
{
	struct iov v = { (void *)bufp, size };
	return get_hashv(algo, &v, 1, phash, nhash);
}
