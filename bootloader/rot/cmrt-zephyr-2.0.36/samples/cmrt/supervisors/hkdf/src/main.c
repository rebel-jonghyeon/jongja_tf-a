/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <stdlib.h>
#include <sys/util.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/util.h>
#include <drivers/cmrt/fboot.h>
#include <cmrt/fboot/fboot_config.h>
#include <drivers/cmrt/pmu.h>
#include <drivers/cmrt/fmc.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/sac.h>
#ifdef CONFIG_CMRT_WDT
#include <drivers/cmrt/wdt.h>
#endif
#include <drivers/cmrt/emc.h>
#include <drivers/cmrt/tmc.h>
#include <drivers/cmrt/hc.h>
#include <cmrt/ucu/kdf.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

/* Example monolithic container that runs in supervisor mode. */

const static char version_info[] __version = SUPERVISOR_VERSION_INFO;

#define STACK_SIZE CONFIG_MAIN_STACK_SIZE
struct k_thread user_thread;
K_THREAD_STACK_DEFINE(user_stack, STACK_SIZE);

static alignas(4) uint8_t s_buffer[4096];

/* Global variables. */
static alignas(4) uint8_t pkr[32];
static alignas(4) uint8_t okm[1024];
static const char *cmd_core[] = {"s2hc", "s3hc"};

/* All other commands are documented below:  */
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
		LOG_ERR("Wrong number of parameters (%u)", argc);
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
		LOG_ERR("Wrong number of parameters (%u)", argc);
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
		LOG_ERR("Wrong number of parameters (%u)", argc);
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
		LOG_ERR("HKDF extract and expand, expected output (0) returned (%d)", ret);
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
		LOG_ERR("Short message!");
		return -EINVAL;
	}
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
		if (nap < ap2 || nap - buffer > *buflen) {
			LOG_ERR("Message format error: args length mismatch");
			return -EINVAL;
		}
		ap2 = nap;
	}
	*buflen = 0;
	uint8_t argl = argl_init(&argp);
	for (size_t i = 0; i < sizeof(cmd_table) / sizeof(*cmd_table); i++) {
		if (memcmp(argp, cmd_table[i].cmd, argl) == 0
			&& cmd_table[i].cmd[argl] == '\0') {
			argp += ((argl + 3) & ~3);
			return cmd_table[i].func(buffer, buflen,
						 argp, argc - 1);
		}
	}
	LOG_ERR("Invalid command '%.*s'", argl, argp);
	return -EINVAL;
}

static int wait_input(cmrt_wdt_t wdt, cmrt_sic_t sic, uint32_t flowid)
{
	while (true) {
		cmrt_handle_t handles[2] = { wdt, sic };
		int res = cmrt_wait(2, handles, CMRT_FOREVER);
		if (res < 0) {
			LOG_ERR("Failed in cmrt_wait: %d!", res);
			return res;
		}
#ifdef CONFIG_CMRT_WDT
		if (res & (1 << 0)) {
			LOG_INF("Watchdog needs food from 0x%x", flowid);
			res = cmrt_wdt_sync(wdt);
			if (res < 0) {
				LOG_ERR("Failed to feed watchdog: %d!", res);
				return res;
			}
			(void)cmrt_wdt_feed(wdt);
		}
#endif
		if (res & (1 << 1)) {
			res = cmrt_sic_sync(sic);
			if (res < 0) {
				LOG_ERR("Failed to read from HLOS: %d!", res);
				return res;
			}
			break; /* process the data */
		}
	}
	return 0;
}

static void main_loop(void *p1, void *p2, void *p3)
{
	uint32_t flowid = (uint32_t)p1;
	uint32_t period = (uint32_t)p2;
	size_t bufmax;
	uint8_t *buffer;

	/* User thread can only write to the stack
	 * Supervisor thread can benefit from a (bigger)
	 * bss buffer for some cmd like load-img
	 */
	if (1 == flowid) {
		buffer = alloca(1024 + 4);
		bufmax = 1024;
	} else {
		buffer = s_buffer;
		bufmax = sizeof(s_buffer) - 4;
	}
	uint32_t cmd_count = 0;

#ifdef CONFIG_CMRT_WDT
	cmrt_wdt_t wdt = cmrt_wdt_open(0, period);
	LOG_INF("Watchdog period %dms for 0x%x", period, flowid);
#else
	cmrt_wdt_t wdt = NULL;
	ARG_UNUSED(period);
#endif
	cmrt_sic_t sic = cmrt_sic_open(0, flowid);
	if (!cmrt_is_valid(sic)) {
		LOG_ERR("Cannot open SIC");
		return;
	}
	LOG_INF("Waiting for SIC input on 0x%x...", (unsigned int)flowid);
	for (;;) {
		size_t buflen = bufmax;
		uint32_t peerid;
		(void)memset(buffer, 0, buflen);
		int res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_ERR("Failed to read from HLOS: %d!", res);
			break;
		}
		/* Write command number to CUSTOM_0 for HLOS. */
		cmrt_sic_write_reg(R_CUSTOM_0, cmd_count);

		res = wait_input(wdt, sic, flowid);
		if (res < 0) {
			LOG_ERR("Failed to wait input: %d!", res);
			break;
		}
		LOG_INF("Message #%d: %d bytes from 0x%x to 0x%x", cmd_count,
			buflen, (unsigned int)peerid, (unsigned int)flowid);
#ifdef CONFIG_CMRT_WDT
		/* Feed the watchdog always before an operation. */
		(void)cmrt_wdt_feed(wdt);
#endif
		res = process_message(buffer, &buflen);
		if (res < 0) {
			LOG_INF("Failed to process the message: %d!", res);
			buflen = 0;
		}
		/* Write command result to CUSTOM_1 for HLOS. */
		cmrt_sic_write_reg(R_CUSTOM_1, res);

		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_ERR("Failed to write to HLOS: %d!", res);
			break;
		}
		cmd_count++;
	}
	cmrt_sic_close(sic);
#ifdef CONFIG_CMRT_WDT
	cmrt_wdt_close(wdt);
#endif
}

#if 1 /* samples may have its own code, 0x5fXX, to be recognized from HLOS */
#define SUPERVISOR_SAMPLE_STARTED 0x5f060000
#endif

void main(void)
{
	uint32_t info;
	/* Read possible reset info before idle thread overwrites it. */
	int res = fboot_reset_info(&info);

	cmrt_set_boot_status(SUPERVISOR_RUNNING_ID, SUPERVISOR_RUNNING_ID);
#ifdef SUPERVISOR_SAMPLE_STARTED
	cmrt_write_reg(CMRT_SIC_BASE, R_SCRATCH_0, SUPERVISOR_SAMPLE_STARTED);
#endif
	/* Write non-zero values to SIC registers. */
	cmrt_write_reg(CMRT_SIC_BASE, R_KERNEL_VERSION, 0x01234567);
	cmrt_write_reg(CMRT_SIC_BASE, R_SDK_VERSION, 0x89abcdef);

	/* Running in supervisor mode here. */
	LOG_INF("Supervisor (hkdf) %s running...", version_info);
	if (res == 0) {
		/* Write info to CUSTOM_1 for HLOS. */
		cmrt_write_reg(CMRT_SIC_BASE, R_CUSTOM_1, info);
		LOG_INF("...booting up with info 0x%x after soft reset", info);
	}
	print_usage();
	(void)k_thread_create(&user_thread, user_stack, STACK_SIZE,
			      main_loop, (void *)1, (void *)10000, NULL,
			      -1, K_USER, K_MSEC(0));
	main_loop((void *)0, (void *)5000, NULL);
	cmrt_set_boot_status(0, SUPERVISOR_RUNNING_ID);
}
