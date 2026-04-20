/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#ifndef LIBPAD_H
#define LIBPAD_H


#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * Flags to supply in cri_pss_params.
 */
enum cri_pss_flag {
       CRI_PSS_PREHASHED = 1 << 0
};


/*!
 * PSS signature padding parameters.
 */
struct cri_pss_params {
	uint32_t bits;	/*!< length of key in bits */
	uint8_t hlen;	/*!< hash output in bytes */
	uint8_t flags;	/*!< hash flags */
	uint16_t halgo;	/*!< hash algorithm used */
	uint32_t slen;	/*!< salt length in bytes, maximum 64 */
};


/*!
 * Pad a signature with PSS.
 * Uses the hash core, and random numbers.
 */
int cri_pss_enc(const struct cri_pss_params *params,
		const void *msg, size_t msglen, void *encoded);


/*!
 * Verify a PSS-encoded signature.  The input length must be
 * params->bits / 8 bytes.
 * @param params algorithm parameters
 * @param msg original message
 * @param msglen length of original message
 * @param encoded signature, the buffer is garbled
 * @return > 0 on a verified signature, otherwise on success
 */
int cri_pss_verify(const struct cri_pss_params *params,
		   const void *msg, size_t msglen, void *encoded);


/*!
 * Parameters for OAEP operations.  The parameters will generally stay
 * constant for multiple operations.
 */
struct cri_oaep_params {
	uint32_t bits; /**< bits in key, 1024,2048,4096, 8192 */
	uint16_t hlen; /**< hash algorithm output length in bytes */
	uint16_t halgo; /**< hash core (HC) algorithm identifier to override */
	const char *label; /**< octet string of lable */
	size_t llen; /**< length of label in bytes */
};


/*!
 * Encode a message.  Generally, msg is expected to be a pre-hashed
 * digest.
 * @param params general key parameters
 * @param msg message buffer (typically a digest)
 * @param msglen length of \a msg in bytes, must be less or equal to key
 * @param pout encoding output buffer, must hold the size of the key
 */
int cri_oaep_enc(const struct cri_oaep_params *params,
		 const void *msg, size_t msglen, void *pout);


/*!
 * Decode a OAEP decoded message.
 * @param params OAEP algorithm parameters
 * @param encoded the encoded input message of params->bits / 8 bytes
 * @param pout output buffer
 * @return length of message in bytes or < 0 for padding failure
 */
int cri_oaep_dec(const struct cri_oaep_params *params,
		 const void *encoded, void *pout);


#ifdef __cplusplus
}
#endif


#endif
