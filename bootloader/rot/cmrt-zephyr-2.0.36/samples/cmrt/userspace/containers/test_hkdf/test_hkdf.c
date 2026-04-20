/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdalign.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/aes.h>
#include <drivers/cmrt/hc.h>
#include <cmrt/ucu/kdf.h>

#define BUFSZ 4096

/* Global variables. */
static alignas(4) uint8_t pkr[32];
static alignas(4) uint8_t okm[1024];
static const char *cmd_core[] = {"s2hc", "s3hc"};

/* Global buffer for receive and response messages from SIC. */
static alignas(4) uint8_t buffer[BUFSZ];

static void print_usage(void)
{
	LOG_INF("Usage:");
	LOG_INF("\thkdf-extract [core] [salt bytes] [ikm bytes]");
	LOG_INF("\thkdf-expand [core] [pkr bytes] [info bytes] [length]");
	LOG_INF("\thkdf-ext-exp [core] [salt bytes] [ikm bytes] [info bytes] [length]");
	LOG_INF("Note: Set %%00 or 0 for NULL parameter");
}

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

static int process_hkdf_extract(uint8_t *buffer, size_t *buflen,
				uint8_t *argp, uint32_t argc)
{
	if (argc != 3) {
		LOG_ERR("Wrong number of parameters (%lu)", argc);
		LOG_ERR("Usage: hkdf-extract CORE SALT IKM");
		return -EINVAL;
	}

	uint32_t salt_len, ikm_len, hc_len;
	uint8_t *salt_ptr, *ikm_ptr, *hc_ptr;
	const char *core = NULL;

	/* Getting input data */
	hc_len = argl_init(&argp);
	hc_ptr = argp;
	salt_len = argl_next(&argp, hc_len);
	salt_ptr = argp;
	ikm_len = argl_next(&argp, salt_len);
	ikm_ptr = argp;

	for (size_t i = 0; i < sizeof(cmd_core) / sizeof(*cmd_core); i++) {
		if (memcmp(hc_ptr, cmd_core[i], hc_len) == 0
		    && cmd_core[i][hc_len] == '\0') {
			core = cmd_core[i];
			break;
		}
	}

	if (core == NULL) {
		hc_ptr[hc_len] = '\0';
		LOG_ERR("Invalid core (%s), expected (s2hc|s3hc)", (char *) hc_ptr);
		return -EINVAL;
	}

	if (salt_len == 1 && (*salt_ptr == 0 || *salt_ptr == '0')) {
		salt_ptr = NULL;
		salt_len = 0;
	}

	cmrt_hc_t hc = cmrt_hc_open(core, 0);
	if (!cmrt_is_valid(hc)) {
		LOG_ERR("Cannot open %s", core);
		return -1;
	}

	/* Generates a pseudorandom key of 32 bytes */
	int ret = hkdf_extract(hc, salt_ptr, salt_len, ikm_ptr, ikm_len, pkr);

	if (ret != 0) {
		LOG_ERR("HKDF extract, expected output (0) returned (%d)", ret);
		return ret;
	}

	if (cmrt_is_valid(hc)) {
		LOG_INF("Closing %s", core);
		cmrt_hc_close(hc);
	}

	memcpy(buffer, pkr, sizeof(pkr));
	*buflen = sizeof(pkr);
	return 0;
}

static int process_hkdf_expand(uint8_t *buffer, size_t *buflen,
				uint8_t *argp, uint32_t argc)
{
	if (argc != 4) {
		LOG_ERR("Wrong number of parameters (%lu)", argc);
		LOG_ERR("Usage: hkdf-expand CORE PKR INFO LENGTH");
		return -EINVAL;
	}

	uint32_t pkr_len, info_len, length, hc_len;
	uint8_t *pkr_ptr, *info_ptr, *hc_ptr;
	const char *core = NULL;
	char *next;

	/* Getting input data */
	hc_len = argl_init(&argp);
	hc_ptr = argp;
	pkr_len = argl_next(&argp, hc_len);
	pkr_ptr = argp;
	info_len = argl_next(&argp, pkr_len);
	info_ptr = argp;
	argl_next(&argp, info_len);
	length = strtoul((char *) argp, &next, 0);

	if (next == (char *) argp) {
		LOG_ERR("Length cannot be parsed");
		return -EINVAL;
	}

	for (size_t i = 0; i < sizeof(cmd_core) / sizeof(*cmd_core); i++) {
		if (memcmp(hc_ptr, cmd_core[i], hc_len) == 0
		    && cmd_core[i][hc_len] == '\0') {
			core = cmd_core[i];
			break;
		}
	}

	if (core == NULL) {
		hc_ptr[hc_len] = '\0';
		LOG_ERR("Invalid core (%s), expected (s2hc|s3hc)", (char *) hc_ptr);
		return -EINVAL;
	}

	if (pkr_len != SHA256_BYTES) {
		LOG_ERR("Prk must have a length of 32 bytes");
		return -EINVAL;
	}

	if (info_len == 1 && (*info_ptr == 0 || *info_ptr == '0')) {
		info_ptr = NULL;
		info_len = 0;
	}

	if (length == 0) {
		LOG_ERR("Length must be greater than zero");
		return -EINVAL;
	}

	if (length > sizeof(okm)) {
		length = sizeof(okm);
	}

	cmrt_hc_t hc = cmrt_hc_open(core, 0);
	if (!cmrt_is_valid(hc)) {
		LOG_ERR("Cannot open %s", core);
		return -1;
	}

	/* Derives a cryptographic key of a specified length */
	int ret = hkdf_expand(hc, pkr_ptr, pkr_len, info_ptr, info_len, length, okm);

	if (ret != 0) {
		LOG_ERR("HKDF expand, expected output (0) returned (%d)", ret);
		return ret;
	}

	if (cmrt_is_valid(hc)) {
		LOG_INF("Closing %s", core);
		cmrt_hc_close(hc);
	}

	memcpy(buffer, okm, length);
	*buflen = length;
	return 0;
}

static int process_hkdf_extract_expand(uint8_t *buffer, size_t *buflen,
				uint8_t *argp, uint32_t argc)
{
	if (argc != 5) {
		LOG_ERR("Wrong number of parameters (%lu)", argc);
		LOG_ERR("Usage: hkdf-ext-exp CORE SALT IKM INFO LENGTH");
		return -EINVAL;
	}

	uint32_t salt_len, ikm_len, hc_len;
	uint32_t info_len, length;
	uint8_t *salt_ptr, *ikm_ptr, *info_ptr, *hc_ptr;
	const char *core = NULL;
	char *next;

	/* Getting input data */
	hc_len = argl_init(&argp);
	hc_ptr = argp;
	salt_len = argl_next(&argp, hc_len);
	salt_ptr = argp;
	ikm_len = argl_next(&argp, salt_len);
	ikm_ptr = argp;
	info_len = argl_next(&argp, ikm_len);
	info_ptr = argp;
	argl_next(&argp, info_len);
	length = strtoul((char *) argp, &next, 0);

	if (next == (char *) argp) {
		LOG_ERR("Length cannot be parsed");
		return -EINVAL;
	}

	for (size_t i = 0; i < sizeof(cmd_core) / sizeof(*cmd_core); i++) {
		if (memcmp(hc_ptr, cmd_core[i], hc_len) == 0
		    && cmd_core[i][hc_len] == '\0') {
			core = cmd_core[i];
			break;
		}
	}

	if (core == NULL) {
		hc_ptr[hc_len] = '\0';
		LOG_ERR("Invalid core (%s), expected (s2hc|s3hc)", (char *) hc_ptr);
		return -EINVAL;
	}

	if (salt_len == 1 && (*salt_ptr == 0 || *salt_ptr == '0')) {
		salt_ptr = NULL;
		salt_len = 0;
	}

	if (info_len == 1 && (*info_ptr == 0 || *info_ptr == '0')) {
		info_ptr = NULL;
		info_len = 0;
	}

	if (length == 0) {
		LOG_ERR("Length must be greater than zero");
		return -EINVAL;
	}

	if (length > sizeof(okm)) {
		length = sizeof(okm);
	}

	cmrt_hc_t hc = cmrt_hc_open(core, 0);
	if (!cmrt_is_valid(hc)) {
		LOG_ERR("Cannot open %s", core);
		return -1;
	}

	/* Generates a pseudorandom key of 32 bytes and derives a
	 * cryptographic key of a specified length */
	int ret = hkdf_extract_expand(hc, salt_ptr, salt_len, ikm_ptr, ikm_len,
					info_ptr, info_len, length, okm);

	if (ret != 0) {
		LOG_ERR("HKDF-ext-exp, expected output (0) returned (%d)", ret);
		return ret;
	}

	if (cmrt_is_valid(hc)) {
		LOG_INF("Closing %s", core);
		cmrt_hc_close(hc);
	}

	memcpy(buffer, okm, length);
	*buflen = length;
	return 0;
}

static struct {
	const char *cmd;
	int (*func)(uint8_t *buffer, size_t *buflen,
		    uint8_t *argp, uint32_t argc);
} cmd_table[] = {
	{ "hkdf-extract", process_hkdf_extract },
	{ "hkdf-expand", process_hkdf_expand },
	{ "hkdf-ext-exp", process_hkdf_extract_expand },
};

static int process_message(uint8_t *buffer, size_t *buflen)
{
	if (*buflen < 8) {
		LOG_ERR("Short message");
		return -EINVAL;
	}
	int res = -EINVAL;
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

	*buflen = 0;
	uint32_t argl = argl_init(&argp);
	for (size_t i = 0; i < sizeof(cmd_table) / sizeof(*cmd_table); i++) {
		if (memcmp(argp, cmd_table[i].cmd, argl) == 0
		    && cmd_table[i].cmd[argl] == '\0') {
			argp += ((argl + 3) & ~3);
			return cmd_table[i].func(buffer, buflen,
						 argp, argc - 1);
		}
	}

	return res;
}

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
		res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read from HLOS: %d!", res);
			break;
		}

		LOG_INF("Got request from HLOS of %zu bytes", buflen);
		if (buflen) {
			LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Request from HLOS:");
		}

		/* Processing failure is a fatal error. */
		res = process_message(buffer, &buflen);
		if (res < 0) {
			LOG_INF("Failed to process the message: %d!", res);
			break;
		}

		/* The same buffer holds the response to HLOS. */
		LOG_INF("Sending response to HLOS of %zu bytes", buflen);
		if (buflen) {
			LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Response to HLOS:");
		}

		if (!buflen) {
			LOG_INF("Failed to process the message: %d", res);
			continue;
		}

		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
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
