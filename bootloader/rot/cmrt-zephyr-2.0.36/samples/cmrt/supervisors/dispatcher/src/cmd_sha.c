/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <stdio.h>
#include <string.h>

#include <device.h>
#include <cri/cmrt/hc.h>

#include "common.h"

/*
 * Examples showing SHA2, SHA3, and HMAC operations using HC/HC2.
 *
 * It handles one data block, whose size is limited by available SAC memory
 * size. It pushes almost all of the data with cri_hc_update() call. The
 * trailing non-word size data, if any, is pushed with cri_hc_final() call.
 * It is possible to support data larger than SAC memory size. For that
 * cri_hc_update() is to be called multiple times. A minimum of 4 bytes must be
 * pushed with cri_hc_update() in each call. cri_hc_update() can only handle
 * data in multiple of word sizes. Input and output buffer address must always
 * word aligned.
 */

#define MAX_KEY_SIZE 144

typedef struct {
	u32_t hc_id;
	u32_t hash_size; /* in bits */
	u8_t truncated;
	u8_t sha3_shake;
	u32_t data_size;
	u8_t data[0];
} sha_args_t;

typedef struct {
	u32_t sha_family;
	u32_t hc_id;
	u32_t hash_size; /* in bits */
	u8_t truncated;
	u32_t key_len;
	u32_t data_size;
	u8_t data[0];
} hmac_args_t;

static bool check_compatibility(u32_t sha_family, u32_t hc_id);
static bool get_hash_algo(cri_hash_algo_t *algo, u32_t hash_size,
			  bool sha3, bool truncated, bool sha3_shake);
static bool get_block_size(u32_t *block_size, cri_hash_algo_t algo);

static int do_sha(const cri_hash_algo_t algo, const u32_t hc_id,
		  void *hmac_key, const u32_t key_len,
		  void *input, u32_t in_used,
		  void *output, u32_t *out_used, u32_t out_size)
{
	/* Open and initialize HC. */
	cri_hc_t hc = CRI_INVALID_HANDLE;
	if (hc_id == 1) {
		hc = cri_hc_open(0);
	} else {
#ifdef CONFIG_CMRT_HC2
		hc = cri_hc2_open(0);
#endif
	}
	if (!cri_is_valid(hc)) {
		err("HC open failed\n");
		return -EIO;
	}

	int ret = cri_hc_init(hc, algo, hmac_key, key_len);
	if (ret) {
		err("HC init failed %d\n", ret);
		goto out;
	}
/*
 * Push most of the data.
 * _update() can only handle data that is well aligned (in size and address)
 * to word boundary.
 */
	ret = cri_hc_update(hc, input, in_used & ~3);
	if (ret) {
		err("HC update failed %d\n", ret);
		goto out;
	}
/*
 * Push any remaining data and retrieve hash.
 * It is OK if data size is no a multiple of word size (4).
 */
	u32_t size;
	u32_t algov = (u32_t)algo;
	if (algov == HC_HASH_ALGO_SHAKE128 || algov == HC_HASH_ALGO_SHAKE256) {
		size = 512;
	} else {
		size = out_size;
	}
	ret = cri_hc_final(hc, ((char *) input) + (in_used & ~3),
			   in_used & 3, output, &size);
	if (ret) {
		err("HC final failed %d\n", ret);
		goto out;
	}
	*out_used = size;

out:
/* Close HC when done. */
	cri_hc_close(hc);
	return ret;
}

#ifdef CONFIG_SV_PERF_MEAS
static const char *hc_algo_names[] = {
		"SHA224",
		"SHA256",
		"SHA384",
		"SHA512",
		"SHA512-224",
		"SHA512-256",
		"SHA3-224",
		"SHA3-256",
		"SHA3-384",
		"SHA3-512"
};
#endif

static int sha2_run(void *input, u32_t in_used,
		    void *output, u32_t *out_used, u32_t out_size)
{
	int res;
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;
	plog_reset();
	plog_set_ref();
#endif

	sha_args_t *args = (sha_args_t *) input;
	if (!check_compatibility(2, args->hc_id)) {
		return -EINVAL;
	}
	info("SHA-2 command: hc %d, hash size %d, truncated %d, sha3_shake %d,\
	     data size %d\n", args->hc_id, args->hash_size, args->truncated,
	     args->sha3_shake, in_used);
	cri_hash_algo_t algo = 0;
	if (!get_hash_algo(&algo, args->hash_size, false, args->truncated,
	    args->sha3_shake)) {
		return -EINVAL;
	}
	res = do_sha(algo, args->hc_id, NULL, 0, args->data,
		     args->data_size, output, out_used, out_size);
#ifdef CONFIG_SV_PERF_MEAS
	cycles = plog_get_cycles();
	plog("SHA,%s,%d,%u", hc_algo_names[algo >> 8], args->data_size, cycles);
#endif
	return res;
}

const cmd_t cmd_sha2 = { CMDID_SHA2, "SHA2",
			 "Compute SHA2 digest over input data", sha2_run };

#if defined(CONFIG_CMRT_S3HC) || defined(CONFIG_CMRT_S3HC2)
static int sha3_run(void *input, u32_t in_used,
		    void *output, u32_t *out_used, u32_t out_size)
{
	int res;
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;
	plog_reset();
	plog_set_ref();
#endif

	sha_args_t *args = (sha_args_t *) input;
	if (!check_compatibility(3, args->hc_id)) {
		return -EINVAL;
	}
	info("SHA-3 command: hc %d, hash size %d, trunc %d, sha3_shake %d,\
	     data size %d\n", args->hc_id, args->hash_size, args->truncated,
	     args->sha3_shake, in_used);
	cri_hash_algo_t algo = 0;
	if (!get_hash_algo(&algo, args->hash_size, true,
	    args->truncated, args->sha3_shake)) {
		return -EINVAL;
	}
	res = do_sha(algo, args->hc_id, NULL, 0, args->data,
		     args->data_size, output, out_used, out_size);
#ifdef CONFIG_SV_PERF_MEAS
	cycles = plog_get_cycles();
	plog("SHA,%s,%d,%u", hc_algo_names[algo >> 8], args->data_size, cycles);
#endif
	return res;
}

const cmd_t cmd_sha3 = { CMDID_SHA3, "SHA3",
			 "Compute SHA3 digest over input data", sha3_run };
#endif

static int hmac_run(void *input, u32_t in_used,
		    void *output, u32_t *out_used, u32_t out_size)
{
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;
	plog_reset();
	plog_set_ref();
#endif

	hmac_args_t *args = (hmac_args_t *) input;
	int res = -EINVAL;
	info("HMAC cmd: SHA-%d hc %d, hash size %d, trunc %d, data size %d\n",
	     args->sha_family, args->hc_id, args->hash_size,
	     args->truncated, in_used);

	if (!check_compatibility(args->sha_family, args->hc_id)) {
		return res;
	}
	cri_hash_algo_t algo = 0;
	const bool is_sha3 = args->sha_family == 3;
	if (!get_hash_algo(&algo, args->hash_size, is_sha3, args->truncated, 0)) {
		return res;
	}
	printk("Algo: 0x%x\n", algo);
	u32_t block_size = 0;
	if (!get_block_size(&block_size, algo)) {
		return res;
	}

	char *key_in = args->data;
	HEXDUMP_VAR(args->data, args->data_size);
	HEXDUMP_VAR(key_in, args->key_len);

	alignas(4) u8_t key[MAX_KEY_SIZE] = {0};
	u32_t key_length = MAX_KEY_SIZE;
	printk("Keylen: %d, Block size: %d\n", args->key_len, block_size);
	/* RFC 2104 secret key size limited to block size*/
	if (args->key_len > block_size) {
		info("Hash HMAC key first %d/%d\n", args->key_len, block_size);

		res = do_sha(algo, args->hc_id, NULL, 0, key_in,
			     args->key_len, key, &key_length, key_length);
		if (res) {
			err("HMAC key hashing failed %d\n", res);
			return res;
		}

	} else {
		memcpy(key, key_in, args->key_len);
		key_length = args->key_len;
	}
	HEXDUMP_VAR(key, key_length);

	char *msg = key_in + ((args->key_len + 3) & ~3);
	u32_t key_padding = ((args->key_len + 3) & ~3) - args->key_len;
	u32_t data_size = args->data_size - args->key_len - key_padding;
	HEXDUMP_VAR(msg, data_size);
	res = do_sha(algo, args->hc_id, key, key_length,  msg,
		     data_size, output, out_used, out_size);
#ifdef CONFIG_SV_PERF_MEAS
	cycles = plog_get_cycles();
	plog("HMAC,HMAC-%s,%d,%d,%u", hc_algo_names[algo >> 8], args->data_size,
		args->key_len * 8, cycles);
#endif
	return res;
}

const cmd_t cmd_hmac = { CMDID_HMAC,
			 "HMAC",
			 "Compute keyed-hash message authentication code",
			 hmac_run };

static bool check_compatibility(const u32_t sha_family, const u32_t hc_id)
{
	bool ret = true;
	switch (hc_id) {
	case 1:
		if (sha_family == 3) {
#ifndef CONFIG_CMRT_S3HC
			err("Invalid config without S3HC\n");
			ret = false;
#endif
		}
		break;
	case 2:
#ifndef CONFIG_CMRT_HC2
		err("Invalid config without HC2\n");
		ret = false;
#endif
		if (sha_family == 2) {
#ifndef CONFIG_CMRT_S2HC2
			err("Invalid config without S2HC2\n");
			ret = false;
#endif
		}
		if (sha_family == 3) {
#ifndef CONFIG_CMRT_S3HC2
			err("Invalid config without S3HC2\n");
			ret = false;
#endif
		}
		break;
	default:
		err("Unsupported HC %d\n", hc_id);
		ret = false;
		break;
	}
	if (sha_family != 2 && sha_family != 3) {
		err("Invalid SHA-%d family\n", sha_family);
		ret = false;
	}
	return ret;
}

static bool get_hash_algo(cri_hash_algo_t *algo, const u32_t hash_size,
			  const bool sha3, const bool truncated,
			  const bool sha3_shake)
{
	switch (hash_size) {
	case 128:
		*algo = CRI_HASH_SHAKE128;
		break;
	case 224:
		if (truncated) {
			*algo = CRI_HASH_SHA512_224;
		} else {
			*algo = sha3 ? CRI_HASH_SHA3_224 : CRI_HASH_SHA224;
		}
		break;
	case 256:
		if (truncated) {
			*algo = CRI_HASH_SHA512_256;
		} else if (sha3_shake) {
			*algo = CRI_HASH_SHAKE256;
			break;
		} else {
			*algo = sha3 ? CRI_HASH_SHA3_256 : CRI_HASH_SHA256;
		}
		break;
	case 384:
		*algo = sha3 ? CRI_HASH_SHA3_384 : CRI_HASH_SHA384;
		break;
	case 512:
		*algo = sha3 ? CRI_HASH_SHA3_512 : CRI_HASH_SHA512;
		break;
	default:
		err("Invalid hash size %d\n", hash_size);
		return false;
	}
	return true;
}

/*
 * RFC 2104 And https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.202.pdf:[20,23]
 * Secret key max length is hash function's block size.
 * Block size:
 *   SHA224 and SHA256 is 512 bits (64 bytes)
 *   SHA384, SHA512, SHA512/224, and SHA512/256 is 1024 bits (128 bytes)
 *   SHA3-224 is 1152 bits (144 bytes)
 *   SHA3-256 is 1088 bits (136 bytes)
 *   SHA3-384 is 832 bits (104 bytes)
 *   SHA3-512 is 576 bits (72 bytes)
 *   SHAKE128 is 1344 bits (168 bytes)
 *   SHAKE256 is 1088 bits (136 bytes)
 * If key is longer than block size, the key must be hashed.
 * The resulting digest is then used as the key for hashing
 * the input data.
 */
static bool get_block_size(u32_t *block_size, const cri_hash_algo_t algo)
{
	switch (algo) {
	case CRI_HASH_SHA224: /* intentional fallthrough */
	case CRI_HASH_SHA256:
		*block_size = 64;
		break;
	case CRI_HASH_SHA384: /* intentional fallthrough */
	case CRI_HASH_SHA512: /* intentional fallthrough */
	case CRI_HASH_SHA512_224: /* intentional fallthrough */
	case CRI_HASH_SHA512_256:
		*block_size = 128;
		break;
	case CRI_HASH_SHA3_224:
		*block_size = 144;
		break;
	case CRI_HASH_SHA3_256:
		*block_size = 136;
		break;
	case CRI_HASH_SHA3_384:
		*block_size = 104;
		break;
	case CRI_HASH_SHA3_512:
		*block_size = 72;
		break;
	case CRI_HASH_SHAKE128:
		*block_size = 168;
		break;
	case CRI_HASH_SHAKE256:
		*block_size = 136;
		break;
	default:
		err("Invalid hash algo 0x%x\n", algo);
		return false;
	}
	return true;
}
