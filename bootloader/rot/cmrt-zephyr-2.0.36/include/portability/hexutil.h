/*
 * Copyright (c) 2018-2019 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file hexutil.h
 *
 * @brief Public APIs for the hexutil library.
 */

#ifndef HEXUTIL_H
#define HEXUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/**
 * @brief Simple hexdump using printk.
 *
 * Output is equal to command line 'hexdump -C'.
 *
 * @param data Pointer to data.
 * @param len Length of data.
 */
void hexdump(const void *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif
