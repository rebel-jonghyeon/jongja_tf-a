/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
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

#include <logging/log.h>
#ifdef USER_CONTAINER
#include <container.h>
#else
LOG_MODULE_REGISTER(lms);
#include <drivers/cmrt/tmc.h>
#endif
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/util.h>
#include <cmrt/shsig/lms.h>
#include <cmrt/shsig/lms_ots.h>

#define BUFSZ 16384

#define MATCH(argp, argl, lstr) \
	((argl == sizeof(lstr)-1) && (memcmp(argp, lstr, sizeof(lstr)-1) == 0))

/* Global buffer for receive and response messages from SIC. */
alignas(4) uint8_t buffer[BUFSZ];

cmrt_hc_t hc = CMRT_INVALID_HANDLE;

/* Max amount of performance entries */
#define PERFDATAENTRIES 32

/* List of output keys for the perf info */
enum {
	PERF_KEY_HC_OPEN = 0,
	PERF_KEY_HC_CLOSE = 1,
	PERF_KEY_LMS_VERIFY = 2,
	PERF_KEY_HSS_VERIFY = 3,
};

typedef struct __packed {
	uint8_t kind;
	uint32_t value;
} perf_data_entry_t;

typedef struct __packed {
	uint8_t entry_count;
	perf_data_entry_t entries[PERFDATAENTRIES];
} perf_data_t;

static bool collect_perf_data = false;
static perf_data_t perf_data = { 0 };

static void perf_clear() {
	memset(&perf_data, 0, sizeof(perf_data));
}

static void perf_append(uint8_t kind, uint32_t value) {
	if (perf_data.entry_count >= PERFDATAENTRIES) {
		LOG_WRN("Performance data buffer full, skipping...");
		return;
	}
	perf_data_entry_t* entry = &perf_data.entries[perf_data.entry_count++];
	entry->kind = kind;
	entry->value = value;
}

static void perf_get(size_t* _buflen) {
	size_t size = sizeof(uint8_t) + perf_data.entry_count * sizeof(perf_data_entry_t);
	memcpy(buffer, &perf_data, size);
	*_buflen = size;
}

static uint64_t perf_curr_measure = 0;

static void perf_start() {
	if (!collect_perf_data) {
		return;
	}
	perf_curr_measure = cmrt_perf_ref();
}

static void perf_end(uint8_t kind) {
	if (!collect_perf_data || perf_curr_measure == 0) {
		return;
	}
	uint32_t cycles = (uint32_t)(cmrt_perf_ref() - perf_curr_measure);
	perf_curr_measure = 0;

	LOG_INF("Performance: kind=%d cycles=%lu", kind, (unsigned long)cycles);
	perf_append(kind, cycles);
}

static void print_usage(void)
{
	LOG_INF("COMMAND:  open|close|init|update|final\n");

	LOG_INF("open USE_HC2  use second hash core if available");
	LOG_INF("USE_HC2:      boolean (0 or 1), use HC2 or not\n");

	LOG_INF("close         close the hc context/core\n");

	LOG_INF("lms-verify PUBKEY SIGN DATA");
	LOG_INF("PUBKEY    : public key");
	LOG_INF("SIGNATURE : signature");
	LOG_INF("MESSAGE   : data to be verified");

	LOG_INF("hss-verify PUBKEY SIGN DATA");
	LOG_INF("PUBKEY    : public key");
	LOG_INF("SIGNATURE : signature");
	LOG_INF("MESSAGE   : data to be verified\n");

	LOG_INF("performance enable|disable|get|clear");
}

static void debug_print_blob(uint8_t *blob, size_t sz, const char *info_text)
{
#ifdef CONFIG_DEBUG
#define _MAX_DBG_LEN 64
	if (!blob || !sz) return;

	size_t sz_hex = sz*2;
	uint8_t blob_hex[_MAX_DBG_LEN*2];
	size_t written = bin2hex(blob, MIN(sz, _MAX_DBG_LEN), (char*)blob_hex, _MAX_DBG_LEN*2);

	LOG_DBG("%s%.*s%s", info_text, (int)sz_hex, blob_hex,
		(written < sz_hex) ? "..." /*cropped*/ : "" );
#undef _MAX_DBG_LEN
#else
	(void)blob; (void)sz; (void)info_text;
#endif
}

static void hc_close(void) {
	if (cmrt_is_valid(hc)) {
		LOG_INF("Closing HC context");
		cmrt_hc_close(hc);

		hc = CMRT_INVALID_HANDLE;
	}
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

static int process_lms_verify(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	int rc = -1;

	if (argc != 3) {
		LOG_ERR("Error wrong number of parameters (%lu)", (unsigned long)argc);
		return -EINVAL;
	}

	if (!cmrt_is_valid(hc)) {
		LOG_ERR("%s: HC not open", __func__);
		return -EIO;
	}

	uint32_t argl = argl_init(&argp);
	uint32_t plen = argl;
	uint8_t *pk = argp;
	debug_print_blob(pk, plen, "pk 0x");

	uint32_t mlen = argl = argl_next(&argp, argl);
	uint8_t *msg = argp;
	debug_print_blob(msg, mlen, "msg 0x");

	uint32_t slen = argl = argl_next(&argp, argl);
	uint8_t *sig = argp;
	debug_print_blob(sig, slen, "sig 0x");

	LOG_DBG("cmrt_lms_verify with plen=%lu mlen=%lu slen=%lu",
		(unsigned long)plen, (unsigned long)mlen, (unsigned long)slen);
	perf_start();
	rc = cmrt_lms_verify(hc, pk, msg, mlen, sig);
	perf_end(PERF_KEY_LMS_VERIFY);
	LOG_DBG("cmrt_lms_verify res: %d", rc);

	memcpy(buffer, &rc, sizeof(rc));
	*_buflen = sizeof(rc);

	return 0;
}

static int process_hss_verify(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	int rc = -1;

	if (argc != 3) {
		LOG_ERR("Error wrong number of parameters (%lu)", (unsigned long)argc);
		return -EINVAL;
	}

	if (!cmrt_is_valid(hc)) {
		LOG_ERR("%s: HC not open", __func__);
		return -EIO;
	}
	uint32_t argl = argl_init(&argp);
	uint32_t plen = argl;
	uint8_t *pk = argp;
	debug_print_blob(pk, plen, "pk 0x");

	uint32_t mlen = argl = argl_next(&argp, argl);
	uint8_t *msg = argp;
	debug_print_blob(msg, mlen, "msg 0x");

	uint32_t slen = argl = argl_next(&argp, argl);
	uint8_t *sig = argp;
	debug_print_blob(sig, slen, "sig 0x");

	LOG_DBG("cmrt_lms_hss_verify with plen=%lu mlen=%lu slen=%lu",
		(unsigned long)plen, (unsigned long)mlen, (unsigned long)slen);
	perf_start();
	rc = cmrt_lms_hss_verify(hc, pk, msg, mlen, sig);
	perf_end(PERF_KEY_HSS_VERIFY);
	LOG_DBG("cmrt_lms_hss_verify res: %d", rc);

	memcpy(buffer, &rc, sizeof(rc));
	*_buflen = sizeof(rc);

	return 0;
}

static int process_open(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	(void) _buflen;

	if (argc != 1) {
		LOG_ERR("%s: invalid number of args", __func__);
		return -1;
	}

	/* USE_HC2 */
	uint32_t argl = argl_init(&argp);
	bool use_hc2 = MATCH(argp, argl, "1");

	LOG_DBG("%s: use_hc2=%d", __func__, use_hc2);

	if (cmrt_is_valid(hc)) {
		LOG_ERR("%s: HC already open", __func__);
		return -1;
	}

	perf_start();

	if (use_hc2) {
		hc = cmrt_hc2_open(0);
	} else {
		hc = cmrt_hc_open(NULL, 0);
	}

	perf_end(PERF_KEY_HC_OPEN);

	if (!cmrt_is_valid(hc)) {
		LOG_ERR("%s: Cannot open HC", __func__);
		return -1;
	}

	return 0;
}

static int process_close(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	(void) _buflen;
	(void) argp;
	(void) argc;

	if (!cmrt_is_valid(hc)) {
		LOG_ERR("%s: HC is already closed", __func__);
		return -1;
	}

	perf_start();

	hc_close();

	perf_end(PERF_KEY_HC_CLOSE);

	return 0;
}

static int process_performance(uint8_t* argp, uint32_t argc, size_t *_buflen) {

	if (argc != 1) {
		LOG_ERR("%s: invalid number of args", __func__);
		return -1;
	}

	uint32_t argl = argl_init(&argp);

	if (MATCH(argp, argl, "enable")) {
		LOG_INF("Enabling performance data recollection...");
		collect_perf_data = true;
		return 0;
	}
	if (MATCH(argp, argl, "disable")) {
		LOG_INF("Disabling performance data recollection...");
		collect_perf_data = false;
		return 0;
	}
	if (MATCH(argp, argl, "clear")) {
		LOG_INF("Clearing performance data...");
		perf_clear();
		return 0;
	}
	if (MATCH(argp, argl, "get")) {
		LOG_INF("Getting performance data...");
		perf_get(_buflen);
		return 0;
	}

	LOG_ERR("%s: Invalid performance OPTION", argp);
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
	if (MATCH(argp, argl, "lms-verify")) {
		return process_lms_verify(argp_next, argc, _buflen);
	}
	if (MATCH(argp, argl, "hss-verify")) {
		return process_hss_verify(argp_next, argc, _buflen);
	}
	if (MATCH(argp, argl, "performance")) {
		return process_performance(argp_next, argc, _buflen);
	}

	/* else */
	argp[argl] = '\0';
	LOG_ERR("%s: Invalid COMMAND", argp);
	return 0;
}

#ifdef USER_CONTAINER
static int main_loop(uint32_t flowid)
{
	LOG_INF("Test (LMS) main loop starting...\n");
#else
int main(void)
{
	LOG_INF("Kernel (LMS) starting...\n");
	uint32_t flowid = 100;
	cmrt_tmc_init_params_t *tmc_params = NULL;
	/* Open TMC to force initialization of the TRNG */
	cmrt_tmc_t tmc = cmrt_tmc_open(0, tmc_params);
	cmrt_tmc_close(tmc);
#endif
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
		if (res < 0) {
			LOG_INF("Failed to process the message: %d!", res);
			break;
		}

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
	hc_close();
	return res;
}

#ifdef USER_CONTAINER
void container(void *p1, void *p2, void *p3)
{
	(void)p2;
	(void)p3;
	print_usage();
	int res = main_loop((uint32_t)p1);
	LOG_ERR("Container main_loop exited with %d!", res);
}
#endif
