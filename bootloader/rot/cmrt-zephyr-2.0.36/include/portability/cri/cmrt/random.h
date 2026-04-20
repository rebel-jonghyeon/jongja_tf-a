/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file random.h
 *
 * @brief Convenience APIs for random number generation.
 */

#ifndef CRI_RANDOM_H
#define CRI_RANDOM_H

/**
 * @brief Random number generation.
 * @{
 */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Convenience function to generate random data.
 *
 * Fill @p buf (of length @p len) with random data, taking care of all
 * device operations and reseeding.
 *
 * @param buf Output buffer.
 * @param len Length of @p buf.
 * @returns 0 on success, -ERRNO otherwise.
 */
int cri_get_random(void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
