/*
 * Copyright (c) 2017-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pke.h
 *
 * @brief Private math APIs for the PKE driver.
 */

#ifndef CMRT_PKE_MATH_H
#define CMRT_PKE_MATH_H

#include <stdint.h>
#include <stddef.h>

#ifndef CRI_PKE_STANDALONE
#include <drivers/cmrt/pke.h>
#else
#include "pke.h"
#endif

/**
 * @brief PKE4 math driver
 * @ingroup cmrt_pke_driver
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_CMRT_FBOOT
#ifndef CONFIG_CMRT_FIPS140_MODE
/**
 * @brief Generate a prime number for RSA
 *
 * Generate a prime number in the interval [2^((bits-1)/2), 2^bits].
 *
 * @param context Pointer to the device.
 * @param bits Bit length of the requested prime.
 * @param slot Slot number to use for output (14 oor 15).
 * @param setup_needed Whether to setup parameters or use previously
 *            generated parameters.
 * @returns 0 on success, -ERRNO otherwise.
 */
#define SETUP_REQUIRED 1
#define SETUP_DONE 0
int cmrt_pke_generate_prime(cmrt_pke_t context,
			    uint32_t bits,
			    uint8_t slot_number,
			    uint8_t setup_needed);
#else
/**
 * @brief Generate a prime number for RSA
 *
 * Generate a prime number in the interval [2^((bits-1)/2), 2^bits].
 *
 * @param context Pointer to the device.
 * @param bits Bit length of the requested prime.
 * @param slot Slot number to use for output (14 oor 15).
 * @returns 0 on success, -ERRNO otherwise.
 */
int cmrt_pke_generate_prime(cmrt_pke_t pke,
			    uint32_t bits,
			    uint8_t slot_number);
#endif

#ifdef CONFIG_CMRT_FFDH
#define DH_GENERATE_P 4
#define DH_SETUP_REQUIRED 2
int cmrt_pke_generate_dh_prime(cmrt_pke_t pke,
			       uint32_t pbits,
			       uint8_t pslot_number,
			       uint32_t qbits,
			       uint8_t *q,
			       uint8_t flags);
#endif

/**
 * @brief Tests for primality using the Millewr-Rabin test.
 *
 * Tests for primality using the Millewr-Rabin test. The number of
 * test is defiend in FIPS186 as having a false positive rate of
 * less than 2^-100.
 *
 * @param context Pointer to the device.
 * @param bits Bit length of the candidate prime.
 * @param slot_number Slot number to used for candidate prime.
 * @param prime set to 0 or 1 for composite or prime, respectively.
 * @returns 0 on success, -ERRNO otherwise.
 */
int cmrt_pke_is_probable_prime(cmrt_pke_t context,
			       uint32_t bits,
			       uint8_t slot_number,
			       uint32_t *prime);

/**
 * @brief Generate an RSA key from two prime numbers
 *
 * Generates an RSA key from two prime numbers, we assume
 * that the public exponent e is 2^16 + 1. The function will
 * return whatever key elements are given valid pointer values.
 *
 * @param context Pointer to the device.
 * @param key The RSA key
 * @returns 0 on success, -ERRNO otherwise.
 */
int cmrt_pke_generate_rsa_keys(cmrt_pke_t context,
			       cmrt_rsa_key_t key);

/**
 * @brief Read the bit length of a big number
 *
 * This function is not side-channel reistant.
 *
 * @param a Pointer to a big number.
 * @param length Word length of the big number.
 * @param bit_length Returned bit length.
 * @returns 0 on success, -ERRNO otherwise.
 */
int cmrt_pke_get_bit_length(uint32_t *a,
			    const size_t length,
			    uint32_t *bit_length);

/**
 * @brief Copy RSA parameters into the PKE
 *
 * Copy RSA parameters into the PKE and reblind the
 * private exponent.
 *
 * @param in Structure detailing what to copy and
 * what security features are required.
 * @returns 0 on success, -ERRNO otherwise.
 */
int copy_rsa_parameters_to_pke(const cmrt_pke_copy_inputs * in);

#ifdef CONFIG_CMRT_RSA_CRT
int cmrt_pke_blind_rsa_crt_key_internal(cmrt_pke_t pke, cmrt_rsa_key_t key, uint8_t update);
#endif

int cmrt_pke_gcd(uint32_t *addrA,
		 uint32_t *addrB,
		 size_t length,
		 uint32_t **gcd);

int pke_eddsa_keygen(cmrt_pke_t pke,
		     cmrt_ecc_curve_t curve,
		     const void *priv_key,
		     void *pub_x,
		     void *prefix);

int cmrt_pke_binary_xgcd(const uint8_t slot_x,
			 const uint8_t slot_y,
			 const uint8_t slot_c,
			 const size_t len,
			 uint8_t slot_a,
			 uint8_t slot_b);

#endif /* FBOOT */

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
