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
#include <drivers/cmrt/dmac.h>
#include <drivers/cmrt/sic.h>

#define BUFSZ 4096

/* Global variables. */

/* Global buffer for receive and response messages from SIC. */
static alignas(4) uint8_t buffer[BUFSZ];

/* Global RAM buffer to use in dmac core. */
static alignas(4) uint8_t dmac_buf[BUFSZ];

/* Global dmac context */
static cmrt_dmac_t dmac = CMRT_INVALID_HANDLE;

static void print_usage(void)
{
	LOG_INF("Message:   COPY|FILL|READ|GETBUF [SRC | FILL_DATA] DST DATALEN");
	LOG_INF("SRC:       Source data address (copy)");
	LOG_INF("FILL_DATA: Fill data value (fill)");
	LOG_INF("DST:       Destination address");
	LOG_INF("DATALEN:   Data length in bytes");
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

static void reset_static_vars(void)
{
	dmac = CMRT_INVALID_HANDLE;
}

static int dmac_open(void)
{
	dmac = cmrt_dmac_open(0);
	if (!cmrt_is_valid(dmac)) {
		LOG_ERR("Cannot open DMAC context!");
		return -1;
	}
	LOG_INF("dmac context opened");
	return 0;
}

static void dmac_close(void)
{
	if (cmrt_is_valid(dmac)) {
		LOG_INF("Closing DMAC context (resets state)");
		cmrt_dmac_close(dmac);
		reset_static_vars();
	}
}

static int process_message_copy(uint8_t *argp, uint32_t argl, uint8_t *out, size_t *outlen)
{
	int res = 0;
	uint32_t src = 0;
	uint32_t dst = 0;
	size_t datalen = 0;

	*outlen = 0;

	/* Get SRC parameter */
	if (argl != 4) {
		argp[argl] = '\0';
		LOG_ERR("Invalid SRC %s", (char *)argp);
		return -EINVAL;
	}
	src = *((uint32_t*) argp);
	LOG_INF("copy -> src: %lu", src);
	argl = argl_next(&argp, argl);

	/* Get DST parameter */
	if (argl != 4) {
		argp[argl] = '\0';
		LOG_ERR("Invalid DST %s", (char *)argp);
		return -EINVAL;
		}
		dst = *((uint32_t*) argp);
		LOG_INF("copy -> dst: %lu", dst);
		argl = argl_next(&argp, argl);

	/* Get DATALEN parameter */
	if (argl != 4) {
		argp[argl] = '\0';
		LOG_ERR("Invalid DATALEN %s", (char *)argp);
		return -EINVAL;
	}
	datalen = *((uint32_t*) argp);
	LOG_INF("copy -> datalen: %u", datalen);
	argl = argl_next(&argp, argl);

	res = dmac_open();
	if (res) {
		memcpy(out, &res, 4);
		*outlen = 4;
		return res;
	}

	res = cmrt_dmac_data(dmac, src, dst, datalen, 0);
	if (res) {
		memcpy(out, &res, 4);
		*outlen = 4;
		LOG_ERR("DMAC copy failed: %d", res);
		return res;
	}

	dmac_close();

	return res;
}

static int process_message_fill(uint8_t *argp, uint32_t argl, uint8_t *out, size_t *outlen)
{
	int res = 0;
	uint32_t fill_data= 0;
	uint32_t dst = 0;
	size_t datalen = 0;

	*outlen = 0;

	/* Get FILL_DATA parameter */
	if (argl != 4) {
		argp[argl] = '\0';
		LOG_ERR("Invalid FILL_DATA %s", (char *)argp);
		return -EINVAL;
	}
	fill_data = *((uint32_t*) argp);
	LOG_INF("fill -> fill_data: %lu", fill_data);
	argl = argl_next(&argp, argl);

	/* Get DST parameter */
	if (argl != 4) {
		argp[argl] = '\0';
		LOG_ERR("Invalid DST %s", (char *)argp);
		return -EINVAL;
		}
		dst = *((uint32_t*) argp);
		LOG_INF("fill -> dst: %lu", dst);
		argl = argl_next(&argp, argl);

	/* Get DATALEN parameter */
	if (argl != 4) {
		argp[argl] = '\0';
		LOG_ERR("Invalid DATALEN %s", (char *)argp);
		return -EINVAL;
	}
	datalen = *((uint32_t*) argp);
	LOG_INF("fill -> datalen: %u", datalen);
	argl = argl_next(&argp, argl);

	res = dmac_open();
	if (res) {
		memcpy(out, &res, 4);
		*outlen = 4;
		return res;
	}

	res = cmrt_dmac_fill(dmac, fill_data, dst, datalen, 0);
	if (res) {
		memcpy(out, &res, 4);
		*outlen = 4;
		LOG_ERR("DMAC fill failed: %d", res);
		return res;
	}

	dmac_close();

	return res;
}

static int process_message_read(uint8_t *argp, uint32_t argl, uint8_t *out, size_t *outlen)
{
	int res = 0;
	uint32_t dst = 0;
	size_t datalen = 0;

	*outlen = 0;

	/* Get DST parameter */
	if (argl != 4) {
		argp[argl] = '\0';
		LOG_ERR("Invalid DST %s", (char *)argp);
		return -EINVAL;
		}
		dst = *((uint32_t*) argp);
		LOG_INF("read -> dst: %lu", dst);
		argl = argl_next(&argp, argl);

	/* Get DATALEN parameter */
	if (argl != 4) {
		argp[argl] = '\0';
		LOG_ERR("Invalid DATALEN %s", (char *)argp);
		return -EINVAL;
	}
	datalen = *((uint32_t*) argp);
	LOG_INF("read -> datalen: %u", datalen);
	argl = argl_next(&argp, argl);

	res = dmac_open();
	if (res) {
		memcpy(out, &res, 4);
		*outlen = 4;
		return res;
	}

	res = cmrt_dmac_data(dmac, dst, (uint32_t) out, datalen, 0);
	if (res) {
		memcpy(out, &res, 4);
		*outlen = 4;
		LOG_ERR("DMAC read failed: %d", res);
		return res;
	}
	*outlen = datalen;

	dmac_close();

	return res;
}

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
	uint32_t argl = argl_init(&argp);

	if (memcmp(argp, "COPY", argl) == 0) {
		LOG_INF("Selection: COPY");
		argl = argl_next(&argp, argl);
		*buflen = BUFSZ;
		res = process_message_copy(argp, argl, buffer, buflen);
	} else if (memcmp(argp, "FILL", argl) == 0) {
		LOG_INF("Selection: FILL");
		argl = argl_next(&argp, argl);
		*buflen = BUFSZ;
		res = process_message_fill(argp, argl, buffer, buflen);
	} else if (memcmp(argp, "READ", argl) == 0) {
		LOG_INF("Selection: READ");
		argl = argl_next(&argp, argl);
		*buflen = BUFSZ;
		res = process_message_read(argp, argl, buffer, buflen);
	} else if (memcmp(argp, "GETBUF", argl) == 0) {
		LOG_INF("Selection: GETBUF");
		uint32_t buf_address = (uint32_t) dmac_buf;
		LOG_INF("getbuf -> buf_address: %lu", (uint32_t) buf_address);
		memcpy(buffer, &buf_address, 4);
		*buflen = 4;
		res = 0;
	} else {
		LOG_ERR("Invalid selection (COPY|FILL|READ): %s", (char *)argp);
	}

	if (res) {
		dmac_close();
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

		if (!buflen) { continue; }
		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
	dmac_close();
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
