/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file cipher_int.h
 *
 * @brief Private APIs for the CMRT cipher core.
 */

#ifndef CMRT_CIPHER_INT_H
#define CMRT_CIPHER_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* Cipher Core I/O control */
struct cmrt_cipher_io {
	uint32_t base_addr;                       /* base address of core */
	uint32_t (*block_size)(uint32_t ctrl);    /* callback to get unit block size in bytes */
	uint32_t (*last_block)(uint32_t inbytes); /* callback to set R_CORE_LAST_BLOCK */
	int (*tag_len)(uint32_t ctrl);            /* callback to get tag len in bytes.
						   * argument is core control register. */
};

typedef const struct cmrt_cipher_io *cmrt_cio_t;

struct cmrt_cipher_context {
	struct cmrt_dd_context ddc;
	cmrt_cio_t cio;
	uint32_t flags;
	bool force_cmd;		/* force write of command register */
};

typedef struct cmrt_cipher_context *cmrt_cipher_t;

typedef enum cipher_flag_e {
	CIPHER_SKIP_LAST_BLOCK = 1UL << 0, /* affects handling of final block */
	CIPHER_SKIP_EMPTY_LAST_BLOCK = 1UL << 1 /* CCM  */
} cipher_flag_t;

/**
 * @brief Load key to cipher core
 *
 * @param cipher		cipher context
 * @param key			key to be loaded
 * @param keylen		size of key in bytes
 */
int cipher_load_key(cmrt_cipher_t cipher, const void *key, size_t keylen);

/**
 * @brief Load initial vector to cipher core
 *
 * @param cipher			cipher context
 * @param ivlen			original size of IV in bytes
 * @param iv 			IV to be loaded
 * @param bsize			aligned size of IV in bytes required by core
 */
int cipher_load_iv(cmrt_cipher_t cipher, size_t ivlen, const void *iv, size_t bsize);

/**
 * @brief Load AAD to cipher core
 *
 * @param cipher	cipher context
 * @param aad 		AAD to be loaded
 * @param adlen	size of AAD in bytes
 * @param final	true for final aad data
 */
int cipher_load_aad(cmrt_cipher_t ctl, const void *ad, size_t adlen, bool final);

/**
 * @brief Cipher update callback
 *
 * @param context	device driver handle
 * @param input	data to be updated
 * @param inlen	size of input in bytes
 * @param output	output of cipher core
 */
int cipher_update(cmrt_cipher_t context, const void *input, size_t inlen, void *output);

/**
 * @brief Cipher final callback
 *
 * @param context		device driver handle
 * @param input			data to be updated
 * @param inlen			size of input in bytes
 * @param output		output of cipher core
 */
int cipher_final(cmrt_cipher_t context, const void *input, size_t inlen, void *output);

/**
 * @brief Cipher update AAD
 *
 * @param context		device driver handle
 * @param aad 			AAD to be loaded
 * @param adlen			size of AAD in bytes
 * @param final			true for final aad data
 */
int cipher_update_aad(cmrt_cipher_t context, const void *aad, size_t aadlen, bool final);

/**
 * @brief Cipher final authenticated callback
 *
 * @param context		device driver handle
 * @param input			data to be updated
 * @param inlen			size of input in bytes
 * @param output		output of cipher core
 * @param tag			tag as either IN or OUT
 * @param taglen		size of tag in bytes
 */
int cipher_ae_final(cmrt_cipher_t context, const void *input, size_t inlen,
		    void *output, void *tag, size_t *taglen);

/**
 * @brief Cipher invalidate key
 *        Clears the key registers and all the internal registers
 *        including IV, AD, tag and counter detecting the number
 *        of encryption/decryption operations.
 *
 * @param context		device driver handle
 * @param flags			flags for special options, default 0
 */
int cipher_invalidate_key(cmrt_cipher_t context, uint32_t flags);

uint32_t cipher_set_command(cmrt_cipher_t base_addr, uint32_t cmd);
int cmrt_cipher_copy(cmrt_cio_t ctl, const uint32_t *input, size_t len,
		     uint32_t *output, bool is_final, bool setup);

#ifdef __cplusplus
}
#endif
#endif
