/*
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pke.h
 *
 * @brief Private hash APIs for the PKE driver.
 */

#ifndef CMRT_PKE_HASH_H
#define CMRT_PKE_HASH_H

#include <stdint.h>
#include <stddef.h>

#include <drivers/cmrt/util.h>

/**
 * @brief PKE4 math driver
 * @ingroup cmrt_pke_driver
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

int get_hash(uint32_t algo, const void *bufp, size_t size,
	     void *phash, size_t nhash);

int get_hashv(uint32_t algo, const struct iov *v, size_t nv, void *phash,
	      size_t nhash);


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
