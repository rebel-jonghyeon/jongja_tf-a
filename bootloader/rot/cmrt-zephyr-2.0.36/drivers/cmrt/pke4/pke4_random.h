/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pke4_random.h
 *
 * @brief Convenience APIs for random number generation.
 */

#ifndef CMRT_PKE_RANDOM_H
#define CMRT_PKE_RANDOM_H

/**
 * @brief PKE RNG Interface
 * @defgroup pke_rng_interface PKE RNG Interface
 * @ingroup pke_rng_interfaces
 * @{
 * */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Convenience function to generate random data.
 *
 * Fill buf (of length len) with random data, taking care of all
 * device operations and reseeding.
 *
 * @param buf Output buffer.
 * @param len Length of ouitput in bytes.
 * @returns 0 on success, -ERRNO otherwise.
 */
int cmrt_pke_get_true_random(void *buf, size_t len);

/**
 * \brief No slots are setup for PKE PRNG to use
 */
#define CMRT_PKE_NO_SLOT -1

/**
 * @brief Convenience function to generate random data.
 *
 * Fill buf (of length len) with pseudo random data, using chosen
 * slot to receive pseudo random numbers from the PKE. If CMRT_PKE_NO_SLOT is
 * chosen the slots will be setup and the first slot will be used.
 *
 * @param buf Output buffer (may be NULL).
 * @param len Length of ouitput in bytes.
 * @param slot Slot number to use to receive random data in PKE.
 * @param slot_length Size of the slots
 * @returns 0 on success, -ERRNO otherwise.
 */
int cmrt_pke_get_pseudo_random(void *buf, size_t len, int32_t slot, uint32_t slot_length);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
