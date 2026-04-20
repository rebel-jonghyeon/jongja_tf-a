/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#ifndef RSAPAD_H
#define RSAPAD_H


#include <stdint.h>
#include <stddef.h>
#include <drivers/cmrt/hc.h>

#ifdef __cplusplus
extern "C" {
#endif


/*!
 * Flags to supply in cmrt_pss_params.
 */
enum cmrt_pss_flag {
       CMRT_PSS_PREHASHED = 1 << 0 /*!< message is already hashed */
};


/*!
 * PSS signature padding parameters.  These are parameter values for
 * the padding which are typically held constant across multiple
 * processed messages.
 */
struct cmrt_pss_params {
	uint32_t bits;	/*!< length of key in bits */
	uint8_t hlen;	/*!< hash output length in bytes */
	uint8_t flags;	/*!< flags from cmrt_pss_flag */
	uint16_t halgo;	/*!< hash algorithm used */
	uint32_t slen;	/*!< salt length in bytes, maximum 64 */
};


/*!
 * Pad a signature with PSS.
 * Uses the hash core passed in, and random numbers.  The hash core
 * must be capable of supporting the specified hash algorithm.
 * @param hc open hash core handle
 * @param params algorithm parameters
 * @param msg original message
 * @param msglen length of original message
 * @param encoded signature, the buffer is garbled
 * @return >= 0 on a correctly encoded signature, otherwise error code
 */
int cmrt_pss_enc(cmrt_hc_t hc,
		 const struct cmrt_pss_params *params,
		 const void *msg, size_t msglen, void *encoded);


/*!
 * Verify a PSS-encoded signature.  The input length must be
 * params->bits / 8 bytes.  The hash core must support the used hash
 * algorithm specified in \a params.
 * @param hc open hash core handle
 * @param params algorithm parameters
 * @param msg original message
 * @param msglen length of original message
 * @param encoded signature, the buffer is garbled
 * @return >= 0 on a verified signature, otherwise error code
 */
int cmrt_pss_verify(cmrt_hc_t hc,
		    const struct cmrt_pss_params *params,
		    const void *msg, size_t msglen, void *encoded);


/*!
 * Parameters for OAEP operations.  The parameters will generally stay
 * constant for multiple operations.  The parameters will select the
 * hash algorithm based on \a halgo.  If \a halgo is 0, the hash
 * algorithm is selected based on the length \a hlen.
 */
struct cmrt_oaep_params {
	uint32_t bits;	/**< size of key in bits */
	uint16_t hlen;	/**< hash algorithm output length in bytes */
	uint16_t halgo; /**< cmrt_hash_algo_t to use or default from hlen */
	const char *label; /**< pointer to label */
	size_t llen;	   /**< length of label in bytes */
};


/*!
 * Encode a message.  Generally, msg is expected to be a pre-hashed
 * digest.  The hash core is still used during the creation of the
 * encoded message and must support the hash algorithm in \a params.
 * @param hc open hash core handle
 * @param params general key parameters
 * @param message message buffer (typically a digest)
 * @param mlen length of \a message in bytes, must be less or equal to key
 * @param dst encoding output buffer, must hold the size of the OAEP-encoded
 * output (key size)
 * @return < 0 for errors, otherwise a success
 */
int cmrt_oaep_enc(cmrt_hc_t hc,
		  const struct cmrt_oaep_params *params,
		  const void *message, uint32_t mlen,
		  void *dst);


/*!
 * Decode a OAEP decoded message.
 * @param hc open hash core handle
 * @param params OAEP algorithm parameters
 * @param encoded the encoded input message of params->bits / 8 bytes
 * @param pout output buffer
 * @return length of message in bytes or < 0 for padding failure
 */
int cmrt_oaep_dec(cmrt_hc_t hc,
		  const struct cmrt_oaep_params *params,
		  const void *encoded, void *pout);


#ifdef __cplusplus
}
#endif


#endif
