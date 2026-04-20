/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/util.h>

#include <logging/log.h>
#ifdef USER_CONTAINER
#include <container.h>
#else
LOG_MODULE_REGISTER(tmc);
#endif

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/tmc.h>
#include <drivers/cmrt/util.h>

#define MATCH(argp, argl, lstr) \
	((argl == sizeof(lstr)-1) && (memcmp(argp, lstr, sizeof(lstr)-1) == 0))

#define MAX_BUFLEN (256 + 4)
alignas(4) uint8_t buffer[MAX_BUFLEN];

static void print_usage(void)
{
	LOG_INF("COMMAND: tmc-set-config [CONFIG] [CONTROL]");
	LOG_INF("         tmc-generate {BUFFER} {SIZE}");
	LOG_INF("         tmc-instantiate {BUFFER} {SIZE}");
	LOG_INF("         tmc-reseed-generate {BUFFER} {SIZE}");
	LOG_INF("         tmc-uninstantiate {BUFFER} {SIZE}");
	LOG_INF("         tmc-reseed {BUFFER} {SIZE}");
	LOG_INF("         tmc-health-check {BUFFER} {SIZE}");
	LOG_INF("         tmc-close");
	LOG_INF("SIZE  : Random data size in bytes (<=32)");
	LOG_INF("BUFFER: Buffer for random numbers: valid-ptr, null-ptr");
	LOG_INF("performance enable|disable|get|clear");
}

/* Max amount of performance entries */
#define PERFDATAENTRIES 32

/* List of output keys for the perf info */
enum {
	PERF_KEY_TMC_OPEN = 0,
	PERF_KEY_TMC_COMMAND = 1,
	PERF_KEY_TMC_CLOSE = 2,
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

static void perf_clear()
{
	memset(&perf_data, 0, sizeof(perf_data));
}

static void perf_append(uint8_t kind, uint32_t value)
{
	if (perf_data.entry_count >= PERFDATAENTRIES) {
		LOG_WRN("Performance data buffer full, skipping...");
		return;
	}
	perf_data_entry_t* entry = &perf_data.entries[perf_data.entry_count++];
	entry->kind = kind;
	entry->value = value;
}

static void perf_get(size_t* _buflen)
{
	size_t size = sizeof(uint8_t) + perf_data.entry_count * sizeof(perf_data_entry_t);
	memcpy(buffer, &perf_data, size);
	*_buflen = size;
}

static uint64_t perf_curr_measure = 0;

static void perf_start()
{
	if (!collect_perf_data) {
		return;
	}
	perf_curr_measure = cmrt_perf_ref();
}

static void perf_end(uint8_t kind)
{
	if (!collect_perf_data || perf_curr_measure == 0) {
		return;
	}
	uint32_t cycles = (uint32_t)(cmrt_perf_ref() - perf_curr_measure);
	perf_curr_measure = 0;

	LOG_INF("Performance: kind=%d cycles=%lu", kind, (unsigned long)cycles);
	perf_append(kind, cycles);
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

static cmrt_tmc_t tmc = CMRT_INVALID_HANDLE;

static int tmc_init(cmrt_tmc_init_params_t *conf)
{
	cmrt_tmc_init_params_t params;
	if (!tmc) {
		if (!conf || conf->config == 0 || conf->control == 0) {
			LOG_INF("Initializing TMC with default parameters");
			cmrt_init_tmc_config(&params);
		} else {
			params.control = conf->control;
			params.config = conf->config;
			params.detune_limit = 8;
		}
		LOG_DBG("%s: TMC Control=0x%lx config=0x%lx", __func__, (long unsigned int)params.control, (long unsigned int)params.config);
		perf_start();
		tmc =  cmrt_tmc_open(CMRT_O_SYNC, &params);
		perf_end(PERF_KEY_TMC_OPEN);
		if (!cmrt_is_valid(tmc)) {
			LOG_ERR("cmrt_tmc_open failed");
			return -ENODEV;
		}
	}
	return 0;
}

static int handle_config(uint32_t argl, uint8_t *argp)
{
	int res = -1;
	argl = argl_next(&argp, argl);
	LOG_HEXDUMP_INF(argp, argl, "Config Value:");
	uint32_t config = (uint32_t)strtoul((const char *)argp, NULL, 0);
	argl = argl_next(&argp, argl);
	LOG_HEXDUMP_INF(argp, argl, "Control Value:");
	uint32_t control = (uint32_t)strtoul((const char *)argp, NULL, 0);
	cmrt_tmc_init_params_t conf = { .config = config,
					.control = control,
					.detune_limit = 8};
	res = tmc_init(&conf);
	return res;
}

static int handle_close()
{
	if (cmrt_is_valid(tmc)) {
		LOG_INF("Closing TMC context");
		perf_start();
		cmrt_tmc_close(tmc);
		perf_end(PERF_KEY_TMC_CLOSE);
		tmc = CMRT_INVALID_HANDLE;
	}
	return 0;
}

static int handle_tmc_command(cmrt_tmc_command_t cmd, uint32_t argl, uint8_t *argp, uint32_t argc, uint8_t *buffer, size_t *buflen)
{
	int res = 0;
	size_t rsize = 0;
	uint8_t *rnd_buffer = buffer + sizeof(uint32_t);
	if (argc == 3 && argl > 0) {
		if (MATCH(argp, argl, "null-ptr")) {
			rnd_buffer = NULL;
		}
		argl = argl_next(&argp, argl);
		rsize = (size_t)strtoul((const char *)argp, NULL, 0);
	}

	if (rsize > 32) {
		LOG_ERR("Data size to request must be <= 256 bytes");
		res = -1;
		memcpy(buffer, &res, sizeof(res));
		*buflen = sizeof(res);
		return res;
	}
	LOG_INF("handle_tmc_command: cmd:%u buffer:%p len:%u", cmd, rnd_buffer, rsize);
	if (cmrt_is_valid(tmc)) {
		perf_start();
		res = cmrt_tmc_command(tmc, cmd, rnd_buffer, rsize);
		perf_end(PERF_KEY_TMC_COMMAND);
		if (res) {
			LOG_ERR("TMC command failed");
		}
	} else {
		LOG_DBG("No valid TMC context, use tmc-set-config command");
		res = -1; /* should we fail here */
	}
	if (res == 0) {
		*buflen = rsize;
	} else {
		*buflen = sizeof(res);
	}
	memcpy(buffer, &res, sizeof(res));
	return res;
}

static int process_performance(uint8_t* argp, uint32_t argc, size_t *_buflen)
{

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

static int process_message(uint8_t *buffer, size_t *buflen)
{
	int res = 0;
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
	LOG_INF("Command: %s", (char *)argp);
	if (MATCH(argp, argl, "tmc-set-config")) {
		res = handle_config(argl, argp);
		if (res){
			LOG_ERR("TMC Initialization failed");
		}
		memcpy(buffer, &res, sizeof(res));
		*buflen = sizeof(res);
		return res;
	}
	if (MATCH(argp, argl, "tmc-close")) {
		res = handle_close();
		if (res){
			LOG_ERR("TMC Close failed");
		}
		memcpy(buffer, &res, sizeof(res));
		*buflen = sizeof(res);
		return res;
	}
	if (MATCH(argp, argl, "tmc-generate")) {
		return handle_tmc_command(CMRT_TMC_GENERATE, argl_next(&argp, argl), argp, argc, buffer, buflen);
	}
	if (MATCH(argp, argl, "tmc-instantiate")) {
		return handle_tmc_command(CMRT_TMC_INSTANTIATE, argl_next(&argp, argl), argp, argc, buffer, buflen);
	}
	if (MATCH(argp, argl, "tmc-reseed-generate")) {
		return handle_tmc_command(CMRT_TMC_RESEED_GENERATE, argl_next(&argp, argl), argp, argc, buffer, buflen);
	}
	if (MATCH(argp, argl, "tmc-uninstantiate")) {
		return handle_tmc_command(CMRT_TMC_UNINSTANTIATE, argl_next(&argp, argl), argp, argc, buffer, buflen);
	}
	if (MATCH(argp, argl, "tmc-reseed")) {
		return handle_tmc_command(CMRT_TMC_RESEED, argl_next(&argp, argl), argp, argc, buffer, buflen);
	}
	if (MATCH(argp, argl, "tmc-health-check")) {
		return handle_tmc_command(CMRT_TMC_HEALTH_CHECK, argl_next(&argp, argl), argp, argc, buffer, buflen);
	}
	uint8_t *argp_next = argp + ((argl + 3) & ~3);
	argc--;
	if (MATCH(argp, argl, "performance")) {
		return process_performance(argp_next, argc,  buflen);
	}

	/* else Invalid command */
	argp[argl] = '\0';
	LOG_ERR("%s: Invalid TMC command", (char *)argp);
	return 0;
}

#ifdef USER_CONTAINER
static int main_loop(uint32_t flowid)
{
	LOG_INF("Test (TMC) main loop starting...\n");
#else
int main(void)
{
	LOG_INF("Kernel (TMC) starting...\n");
	uint32_t flowid = 100;
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

		/* Processing failure is a fatal error. */
		LOG_HEXDUMP_DBG(buffer, MIN(buflen, 32), "Request from HLOS:");
		res = process_message(buffer, &buflen);

		/* The same buffer holds the response to HLOS. */
		LOG_HEXDUMP_DBG(buffer, buflen, "Response to HLOS:");

		if (!buflen) continue;
		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
	if (cmrt_is_valid(tmc)) {
		cmrt_tmc_close(tmc);
	}
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
