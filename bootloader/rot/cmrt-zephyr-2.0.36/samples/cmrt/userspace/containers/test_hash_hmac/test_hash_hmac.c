/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/util.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/hc.h>

static void print_usage(void)
{
	LOG_INF("First message:   ALGO CORE [KEY]");
	LOG_INF("Next message(s): DATA or unaligned/empty for final");
	LOG_INF("ALGO:  sha-224|sha-256|sha-384|sha-512|sha-512_224|sha-512_256|");
	LOG_INF("       sha3-224|sha3-256|sha3-384|sha3-512|shake128|shake256|whirlpool");
	LOG_INF("CORE:  s2hc|s3hc|cshc|whc");
	LOG_INF("KEY:   ascii or binary");
	LOG_INF("DATA:  ascii or binary");
}

/*
 * yet to find a home...
 */
static inline uint32_t argl_init(uint8_t **argpp)
{
	const uint32_t argl = **(uint32_t**)argpp;
	*argpp += sizeof(uint32_t);
	return argl;
}
static inline uint32_t argl_next(uint8_t **argpp, uint32_t argl)
{
	*argpp += ((argl + 3) & ~3);
	argl = **(uint32_t**)argpp;
	*argpp += sizeof(uint32_t);
	return argl;
}

static cmrt_hc_t hc = CMRT_INVALID_HANDLE;
cmrt_hash_algo_t algo;

static struct {
	const char *str;
	cmrt_hash_algo_t algo;
} cmd_algo[] = {
	{ "sha-224", CMRT_HASH_SHA224 },
	{ "sha-256", CMRT_HASH_SHA256 },
	{ "sha-384", CMRT_HASH_SHA384 },
	{ "sha-512_224", CMRT_HASH_SHA512_224 },
	{ "sha-512_256", CMRT_HASH_SHA512_256 },
	{ "sha-512", CMRT_HASH_SHA512 },
	{ "sha3-224", CMRT_HASH_SHA3_224 },
	{ "sha3-256", CMRT_HASH_SHA3_256 },
	{ "sha3-384", CMRT_HASH_SHA3_384 },
	{ "sha3-512", CMRT_HASH_SHA3_512 },
	{ "shake128", CMRT_HASH_SHAKE128 },
	{ "shake256", CMRT_HASH_SHAKE256 },
};

static const char *cmd_core[] = { "s2hc", "s3hc", "cshc", "whc" };

static int process_init(uint8_t *buffer, size_t *buflen)
{
	if (*buflen < 8) {
		LOG_ERR("Short message");
		return -EINVAL;
	}
	uint8_t *argp = buffer;
	uint32_t argc = argl_init(&argp);
	/*
	 * Check argument array length matches message length, then
	 * rest of the code can trust the lengths of inputs given...
	 */
	const uint8_t *ap2 = argp;
	for (size_t i = 0; i < argc; i++) {
		const int alen = *(uint32_t*)ap2;
		const uint8_t *const nap = ap2 + ((alen + 7) & ~3);
		if (nap < ap2 || (size_t)(nap - buffer) > *buflen) {
			LOG_ERR("Message format error: args length mismatch");
			return -EINVAL;
		}
		ap2 = nap;
	}
	uint32_t argl = argl_init(&argp);

	algo = (cmrt_hash_algo_t)-1;
	for (size_t i = 0; i < sizeof(cmd_algo) / sizeof(*cmd_algo); i++) {
		if (memcmp(argp, cmd_algo[i].str, argl) == 0
		    && cmd_algo[i].str[argl] == '\0') {
			algo = cmd_algo[i].algo;
			break;
		}
	}
	if (algo == (cmrt_hash_algo_t)-1) {
		argp[argl] = '\0';
		LOG_ERR("Invalid ALGO %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	const char *core = NULL;
	for (size_t i = 0; i < sizeof(cmd_core) / sizeof(*cmd_core); i++) {
		if (memcmp(argp, cmd_core[i], argl) == 0
		    && cmd_core[i][argl] == '\0') {
			core = cmd_core[i];
			break;
		}
	}
	if (core == NULL) {
		argp[argl] = '\0';
		LOG_ERR("Invalid CORE %s", (char *)argp);
		return -EINVAL;
	}
	argl = argl_next(&argp, argl);

	const uint8_t *key = NULL;
	size_t keylen = 0;

	if (argc > 2 && argl > 0) {
		// there is a key
		key = argp;
		keylen = argl;
	}
	/* note: in the future there could be message... */

	static uint8_t hashed_key[512/8];
	hc = cmrt_hc_open(core, 0);
	if (!cmrt_is_valid(hc)) {
		LOG_ERR("cmrt_hc_open failed for %s", core);
		return -ENODEV;
	}
	/*
	 * RFC 2104: if key length is larger than 512/1024 bits, hash the
	 * key first, then use the digest as new key.
	 * SHA224 and SHA256 is 512 bits (64 bytes)
	 * SHA384, SHA512, SHA512/224, and SHA512/256 is 1024 bits (128 bytes)
	 * SHA3-224 is 1152 bits (144 bytes)
	 * SHA3-256 is 1088 bits (136 bytes)
	 * SHA3-384 is 832 bits (104 bytes)
	 * SHA3-512 is 576 bits (72 bytes)
	 * SHAKE128 is 1344 bits (168 bytes)
	 * SHAKE256 is 1088 bits (136 bytes)
	 */
	int hash_key = 0;

	switch (algo) {
	case CMRT_HASH_SHA224:
	case CMRT_HASH_SHA256:
		if (keylen > 512 / 8)
			hash_key = 1;
		break;
	case CMRT_HASH_SHA384:
	case CMRT_HASH_SHA512:
	case CMRT_HASH_SHA512_224:
	case CMRT_HASH_SHA512_256:
		if (keylen > 1024 / 8)
			hash_key = 1;
		break;
	case CMRT_HASH_SHA3_224:
		if (keylen > 1152 / 8)
			hash_key = 1;
		break;
	case CMRT_HASH_SHA3_256:
		if (keylen > 1088 / 8)
			hash_key = 1;
		break;
	case CMRT_HASH_SHA3_384:
		if (keylen > 832 / 8)
			hash_key = 1;
		break;
	case CMRT_HASH_SHA3_512:
		if (keylen > 576 / 8)
			hash_key = 1;
		break;
	case CMRT_HASH_SHAKE128:
		if (keylen > 1344 / 8)
			hash_key = 1;
		break;
	case CMRT_HASH_SHAKE256:
		if (keylen > 1088 / 8)
			hash_key = 1;
		break;
	}
	if (hash_key) {
		int err = -EINVAL;

		err = cmrt_hc_init(hc, algo, 0, 0);
		if (err) {
			LOG_ERR("Cannot init hash: %d", err);
			return -EINVAL;
		}
		err = cmrt_hc_update(hc, key, keylen & ~3);
		if (err) {
			LOG_ERR("Cannot update hash: %d", err);
			return -EINVAL;
		}
		unsigned int hashed_key_len = sizeof(hashed_key);

		err = cmrt_hc_final(hc, key + (keylen & ~3), keylen & 3,
				    hashed_key, &hashed_key_len);
		if (err) {
			LOG_ERR("Cannot final hash: %d", err);
			return -EINVAL;
		}
		key = hashed_key;
		keylen = hashed_key_len;
	}
	int res = cmrt_hc_init(hc, algo, key, keylen);
	LOG_INF("cmrt_hc_init with algo=0x%x keylen=%d: %d", algo, keylen, res);
	if (res != 0) { return res; }
	*buflen = 0; /* return zero data to HLOS */
	return 0;
}

static int process_update(uint8_t *buffer, size_t *buflen)
{
	int res = cmrt_hc_update(hc, buffer, *buflen);
	LOG_INF("cmrt_hc_update with inlen=%d: %d", (int)*buflen, res);
	if (res != 0) { return res; }
	*buflen = 0; /* return zero data to HLOS */
	return 0;
}

static int process_final(uint8_t *buffer, size_t *buflen, size_t outlen)
{
	int res = cmrt_hc_final(hc, buffer, *buflen, buffer, &outlen);
	LOG_INF("cmrt_hc_final with outlen=%d: %d", (int)outlen, res);
	if (res != 0) { return res; }
	*buflen = outlen; /* return outlen data to HLOS */
	return 0;
}

static int process_message(uint8_t *buffer, size_t *buflen, size_t maxlen)
{
	int res = 0;
	if (!cmrt_is_valid(hc)) {
		/* Core is not open, this must be init. */
		res = process_init(buffer, buflen);
	} else {
		/* Core is open, this is either update or final. */
		if (*buflen > 0 && (*buflen & 0x3) == 0) {
			res = process_update(buffer, buflen);
		} else {
			res = process_final(buffer, buflen, maxlen);
			if (algo != CMRT_HASH_SHAKE128 &&
			    algo != CMRT_HASH_SHAKE256) {
				/* No output anymore, close the core. */
				cmrt_hc_close(hc);
				hc = CMRT_INVALID_HANDLE;
				LOG_INF("cmrt_hc_close");
			}
		}
	}
	return res;
}

#define MAX_BUFLEN (8192 + 4)
alignas(4) uint8_t buffer[MAX_BUFLEN];
#define MAX_OUTLEN 64

static int main_loop(uint32_t flowid)
{
	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, flowid);
	if (!cmrt_is_valid(sic)) {
		LOG_INF("Cannot open SIC");
		return -ENODEV;
	}
	LOG_INF("Waiting for SIC input on flow 0x%x...", (unsigned int)flowid);

	int res = 0;
	while (true) {
		uint32_t peerid;
		size_t buflen = sizeof(buffer) - 4;
		/* memset(buffer, 0, sizeof(buffer)); */
		res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read from HLOS: %d!", res);
			break;
		}
		/* Processing failure is a fatal error. */
		LOG_HEXDUMP_DBG(buffer, MIN(buflen, 16), "Request from HLOS:");
		res = process_message(buffer, &buflen, MAX_OUTLEN);
		if (res < 0) {
			LOG_INF("Failed to process the message: %d!", res);
			break;
		}
		/* The same buffer holds the response to HLOS. */
		LOG_HEXDUMP_DBG(buffer, MIN(buflen, 16), "Response to HLOS:");
		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
	if (cmrt_is_valid(hc)) {
		cmrt_hc_close(hc);
	}
	return res;
}

void container(void *p1, void *p2, void *p3)
{
	(void)p2;
	(void)p3;
	print_usage();
	int res = main_loop((uint32_t)p1);
	LOG_ERR("Container main_loop exited with %d!", res);
}
