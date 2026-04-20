/*
 * Copyright (c) 2023-2024 Cryptography Research, Inc. (CRI).
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
#include <stdbool.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/ktc.h>
#include <drivers/cmrt/sic.h>


#define BUFSZ 16384

#define MATCH(argp, argl, lstr) \
	((argl == sizeof(lstr)-1) && (memcmp(argp, lstr, sizeof(lstr)-1) == 0))

/* Global buffer for receive and response messages from SIC. */
alignas(4) uint8_t buffer[BUFSZ];


cmrt_ktc_t ktc = CMRT_INVALID_HANDLE;

static void print_usage(void)
{
	LOG_INF("COMMAND:  open|close|transfer_key\n");

	LOG_INF("open TIMEOUT");
	LOG_INF("TIMEOUT    : 0\n");
	LOG_INF("close        close the ktc context/core\n");

	LOG_INF("transfer_key DESTINATION KEY_SIZE KEY");
	LOG_INF("DESTINATION : {0-15}");
	LOG_INF("KEY_SIZE    : up to 4080, must be multiple of 16");
	LOG_INF("KEY         : ABCDEF0123456789\n");

}

/* Converts a (decimal) string into a uint32_t. Returns the parsed number.
 * Processes exactly `sl` bytes from the string `s`.
 * On conversion error sets errno to -EINVAL and returns 0.
 *
 * Encountering a nullbyte is a a conversion error.
 * An empty string (`sl`== 0) is a conversion error.
 * No wrapparound checks on the parsed number or on `sl`.
 * */
static uint32_t conv_strl2u32(const char *s, size_t sl)
{
	uint32_t acc = 0;
	const char *s_end = s + sl; /* no ovf check */
	for (; (size_t)s < (size_t)s_end; ++s) {
		char v = *s;
		if (v < '0' || v > '9') {
			errno = EINVAL;
			return 0;
		}
		v -= '0';
		acc *= 10; /* no ovf check */
		acc += v;
	}
	return acc;
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

static int process_transfer_key(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	int res = -1;

	if (argc != 3) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -EINVAL;
	}

	if (!cmrt_is_valid(ktc)) {
		LOG_ERR("%s: KTC not open", __func__);
		return -EIO;
	}

	uint32_t argl = argl_init(&argp);
	int dest_slot = (int)conv_strl2u32((char *)argp, argl);

	argl = argl_next(&argp, argl);
	int k_size = (int)conv_strl2u32((char *)argp, argl);

	uint32_t key_len = argl = argl_next(&argp, argl);
	uint8_t *key = argp;
	uint32_t key_buf[KTC_MAX_KEY_SIZE / sizeof(uint32_t)] = {};
	memcpy(key_buf, key, key_len);


	cmrt_ktc_cmd_t cmd = {
		.metadata = { 0x1234, 0x5678 },
		.destination = dest_slot,
		.key_size = k_size,
		.key = key_buf
	};
	res = cmrt_ktc_export(ktc, &cmd);
	if (res == 0) { res = cmrt_ktc_sync(ktc); }
	memcpy(buffer, &res, sizeof(res));
	*_buflen = sizeof(res);
	return res;

}


static void ktc_close(void) {
	if (cmrt_is_valid(ktc)) {
		cmrt_ktc_close(ktc);
		LOG_INF("Closing KTC context");
		ktc = CMRT_INVALID_HANDLE;
	}
}

static int process_open(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	(void) _buflen;

	if (argc != 1) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		return -EINVAL;
	}


	if (cmrt_is_valid(ktc)) {
		LOG_ERR("%s: KTC already open", __func__);
		return -EIO;
	}
	uint32_t argl = argl_init(&argp);
	int t_out = (int)conv_strl2u32((char *)argp, argl);
	ktc = cmrt_ktc_open(0, t_out);


	if (!cmrt_is_valid(ktc)) {
		LOG_ERR("%s: Cannot open KTC", __func__);
		return -EIO;
	}

	return 0;
}

static int process_close(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	(void) _buflen;
	(void) argp;
	(void) argc;


	if (!cmrt_is_valid(ktc)) {
		LOG_ERR("%s: KTC is already closed", __func__);
		return -EIO;
	}

	ktc_close();

	return 0;
}

static int process_message(uint8_t *buffer, size_t *_buflen)
{
	uint8_t *argp = buffer;
	uint32_t argc = argl_init(&argp);
	/*
	 * Check argument array length matches message length, then
	 * commands can trust the lengths of inputs given to them.
	 */
	const uint8_t *ap2 = argp;
	for (size_t i = 0; i < argc; i++) {
		const int alen = *(uint32_t*)ap2;
		const uint8_t *const nap = ap2 + ((alen + 7) & ~3);
		if (nap < ap2 || (size_t)(nap - buffer) > *_buflen) {
			LOG_ERR("Message format error: args length mismatch");
			return -EINVAL;
		}
		ap2 = nap;
	}
	*_buflen = 0;
	uint32_t argl = argl_init(&argp);
	uint8_t *argp_next = argp + ((argl + 3) & ~3); /* revisit how to do */
	argc--;

	/* dispatch OPERATION */

	if (MATCH(argp, argl, "open")) {
		return process_open(argp_next, argc, _buflen);
	}
	if (MATCH(argp, argl, "close")) {
		return process_close(argp_next, argc, _buflen);
	}
	if (MATCH(argp, argl, "transfer_key")) {
		return process_transfer_key(argp_next, argc, _buflen);
	}

	/* else */
	argp[argl] = '\0';
	LOG_ERR("%s: Invalid COMMAND", argp);
	return 0;
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
		/* memset(buffer, 0, sizeof(buffer)); */
		res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read from HLOS: %d!", res);
			break;
		}

		LOG_INF("Got request from HLOS of %zu bytes", buflen);
		if (buflen)
			LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Request from HLOS:");

		/* Processing failure is a fatal error. */
		res = process_message(buffer, &buflen);
		// if (res < 0) {
		// 	LOG_INF("Failed to process the message: %d!", res);
		// 	break;
		// }
		/* The same buffer holds the response to HLOS. */
		LOG_INF("Sending response to HLOS of %zu bytes", buflen);
		if (buflen)
			LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Response to HLOS:");

		if (!buflen) continue;
		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
	if (cmrt_is_valid(ktc)) {
		ktc_close();
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
