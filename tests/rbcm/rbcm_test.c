/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2025 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"
#include "terminal_task.h"
#include "rbcm_core.h"
#include "rl_errors.h"
#include "rbcm_reg_model.h"
#include "rbcm_common.h"
#include "rbcm_test.h"
#include "rbcm_driver.h"
#include "rbcm_reg_access_test.h"
#include "test_common.h"

#define dev_fmt(fmt)	fmt

#define RBCM_IRQ_ENABLE  0
#define RBCM_IRQ_DISABLE 1

#define DEFAULT_UTG_ADDR 0x10000000
/* Port Loopback Test need more compl*/
#define RBCM_SKIP_PORT_LOOPBACK

static const char rbcm_test_help[] =
	"Usage: rbc_test <command> [options]\r\n"
	"Available commands:\r\n"
	"  sw_reset, scan_ttreg, dump_incomplete_ttreg, clear_ttreg, utg_write, utg_read, addr_remap\r\n"
	"  set_loopback, set_timeout, get_timeout, enable_irq, disable_irq, check_ucie, check_crc\r\n"
	"  reg_acc_test, test_all\r\n";

int32_t rbcm_module_valid(enum rbcm_module idx)
{
	if (idx < 0 || idx >= RBC_MODULE_COUNT) {
		RBCM_LOGE("Invalid RBC module enum value %d\r\n", (int)idx);
		return RL_BADARG;
	}

	return RL_OK;
}

static bool conv_str_to_uint64(const char *str, uint64_t *val)
{
	char *endptr;

	if (!str || !val)
		return false;

	*val = strtoull(str, &endptr, 0);

	/* Check for conversion errors: no digits found, or extra chars */
	if (endptr == str || *endptr != '\0') {
		RBCM_LOGE("Invalid number format: '%s'\r\n", str);
		return false;
	}

	return true;
}

static bool conv_str_to_uint32(const char *str, uint32_t *val)
{
	char *endptr;

	if (!str || !val)
		return false;

	*val = strtoul(str, &endptr, 0);

	/* Check for conversion errors: no digits found, or extra chars */
	if (endptr == str || *endptr != '\0') {
		RBCM_LOGE("Invalid number format: '%s'\r\n", str);
		return false;
	}

	return true;
}

static char *strtolowercase(char *s)
{
	char *orig = s;

	if (!s)
		return NULL;

	while (*s) {
		*s = tolower((unsigned char)*s);
		s++;
	}

	return orig;
}

static bool cli_validate(enum rbcm_module idx, int argc, int arg_index)
{
	if (rbcm_module_valid(idx) != RL_OK)
		return false;

	if (arg_index < argc) {
		RBCM_LOGE("Too many arguments\r\n");
		return false;
	}

	if (arg_index > argc) {
		RBCM_LOGE("Too few arguments\r\n");
		return false;
	}

	return true;
}

enum rbcm_module get_rbc_module_argument(const char *str_in)
{
	static const struct {
		const char *name;
		enum rbcm_module module;
	} module_map_table[] = {
		{ "c0s0", RBC_C0S0 }, { "c0s1", RBC_C0S1 },
		{ "c0e0", RBC_C0E0 }, { "c0e1", RBC_C0E1 },
		{ "c1n0", RBC_C1N0 }, { "c1n1", RBC_C1N1 },
		{ "c1e0", RBC_C1E0 }, { "c1e1", RBC_C1E1 },
		{ "c2n0", RBC_C2N0 }, { "c2n1", RBC_C2N1 },
		{ "c2e0", RBC_C2E0 }, { "c2e1", RBC_C2E1 },
		{ "c3s0", RBC_C3S0 }, { "c3s1", RBC_C3S1 },
		{ "c3e0", RBC_C3E0 }, { "c3e1", RBC_C3E1 },
		{ NULL, RBC_BLK_INVALID }
	};

	if (!str_in)
		return RBC_BLK_INVALID;

	for (int i = 0; module_map_table[i].name; ++i) {
		if (!strcasecmp(str_in, module_map_table[i].name))
			return module_map_table[i].module;
	}
	RBCM_LOGE("Invalid RBC module name '%s'\r\n", str_in);

	return RBC_BLK_INVALID;
}

static int32_t rbcm_reg_acc_test(enum rbcm_module idx)
{
	int32_t ret;

	rbcm_sw_reset(idx);
	ret = rbcm_run_reg_rst_test(idx);
	if (ret < 0) {
		RBCM_LOGE("Invalid Argument\r\n");
		goto acc_reg_out;
	}

	RBCM_LOGI("Register reset test -> %s(%d mismatches)\r\n",
			  (ret == 0 ? "PASSED" : "FAILED"), ret);

	ret = rbcm_run_reg_acc_test(idx);
	RBCM_LOGI("Register access test %s(%d mismatches)\r\n",
			  (ret == 0 ? "PASSED" : "FAILED"), ret);
	rbcm_sw_reset(idx);

	/*
	 * Re-enables the sub-block within RBC_M after the register access test.
	 * The test sometimes disables this block via rbc_config, and attempting to
	 * access its registers while disabled would cause a system hang. This ensures
	 * the block is in an active state.
	 */
	rbcm_recover_from_reset(idx);

acc_reg_out:
	return ret;
}

static int32_t rbcm_cli_reg_acc_test(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_C0S0;
	int opt;

	optind = 0;
	while ((opt = getopt(argc, argv, "m:")) != -1) {
		switch (opt) {
		case 'm':
			idx = get_rbc_module_argument(optarg);
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	return rbcm_reg_acc_test(idx);
}

static int32_t rbcm_cli_sw_reset(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_C0S0;
	int opt;
	int reset_all = 0;

	optind = 0;
	while ((opt = getopt(argc, argv, "am:")) != -1) {
		switch (opt) {
		case 'a':
			reset_all = 1;
			break;
		case 'm':
			idx = get_rbc_module_argument(optarg);
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	RBCM_LOGI("Sw reset %s modules.\r\n", reset_all ? "all" : get_module_name(idx));
	if (reset_all)
		rbcm_sw_reset_all();
	else
		rbcm_sw_reset(idx);

	return RL_OK;
}

static int32_t rbcm_cli_addr_remap(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_C0S0;
	uint32_t msb_src, msb_dst;
	int opt;

	optind = 0;
	while ((opt = getopt(argc, argv, "m:")) != -1) {
		switch (opt) {
		case 'm':
			idx = get_rbc_module_argument(optarg);
			if (rbcm_module_valid(idx) != RL_OK)
				return RL_BADARG;
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (argc - optind != 2)
		return RL_BADARG;

	if (rbcm_module_valid(idx) != RL_OK)
		return RL_BADARG;

	if (!conv_str_to_uint32(argv[optind], &msb_src) ||
	    !conv_str_to_uint32(argv[optind + 1], &msb_dst)) {
		return RL_BADARG;
	}

	RBCM_LOGI("Remapping RBC Port %s MSB from %u to %u\r\n",
			  get_module_name(idx), msb_src, msb_dst);

	return rbcm_addr_remap(idx, msb_src, msb_dst);
}

static int32_t rbcm_cli_utg(int argc, char *argv[], int read_access)
{
	enum rbcm_module idx = RBC_C0S0;
	uint32_t port = 0;
	uint64_t addr = DEFAULT_UTG_ADDR; // Default address
	uint32_t repeat_count = 1;
	int opt;

	optind = 0;
	while ((opt = getopt(argc, argv, "m:p:r:a:")) != -1) {
		switch (opt) {
		case 'm':
			idx = get_rbc_module_argument(optarg);
			break;
		case 'p':
			if (!conv_str_to_uint32(optarg, &port))
				return RL_BADARG;
			if (port >= RBC_PORT_COUNT) {
				RBCM_LOGE("Invalid port index %u (max %d)\r\n",
						  port, RBC_PORT_INVALID - 1);
				return RL_BADARG;
			}
			break;
		case 'r':
			if (!conv_str_to_uint32(optarg, &repeat_count))
				return RL_BADARG;
			break;
		case 'a':
			if (!conv_str_to_uint64(optarg, &addr))
				return RL_BADARG;
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	if (repeat_count == 0)
		repeat_count = 1;

	RBCM_LOGI("UTG: Module %s, Port %u, %s, Addr 0x%lx, Repeat %u\r\n",
			  get_module_name(idx), port, read_access ? "Read" : "Write",
			  (unsigned long)addr, repeat_count);

	for (uint32_t i = 0; i < repeat_count; i++) {
		int32_t result;

		result = rbcm_user_traffic_generation(idx, port, read_access,
											  addr, i * 16);
		if (result != RL_OK)
			return result;
	}

	return RL_OK;
}

static int32_t rbcm_cli_utg_write(int argc, char *argv[])
{
	return rbcm_cli_utg(argc, argv, RBCM_WR_TRANS);
}

static int32_t rbcm_cli_utg_read(int argc, char *argv[])
{
	return rbcm_cli_utg(argc, argv, RBCM_RD_TRANS);
}

static int32_t rbcm_cli_dump_incomplete_ttreg(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_C0S0;
	int opt;
	int run_all = 0;

	optind = 0;
	while ((opt = getopt(argc, argv, "am:")) != -1) {
		switch (opt) {
		case 'a':
			run_all = 1;
			break;
		case 'm':
			idx = get_rbc_module_argument(optarg);
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (run_all) {
		for (int i = 0; i < RBC_MODULE_COUNT; i++) {
			RBCM_LOGI("Dumping incomplete TTREG for %s\r\n", get_module_name(i));
			rbcm_dump_incomplete_ttreg(i);
		}
		return RL_OK;
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	RBCM_LOGI("Dumping incomplete TTREG for %s\r\n", get_module_name(idx));
	rbcm_dump_incomplete_ttreg(idx);

	return RL_OK;
}

static int32_t rbcm_cli_scan_ttreg(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_C0S0;
	uint32_t port = 0;
	int mode = 0; /* Default: Outbound */
	int opt;

	optind = 0;
	while ((opt = getopt(argc, argv, "m:p:b:")) != -1) {
		switch (opt) {
		case 'm':
			idx = get_rbc_module_argument(optarg);
			break;
		case 'p':
			if (!conv_str_to_uint32(optarg, &port))
				return RL_BADARG;
			if (port >= RBC_PORT_COUNT) {
				RBCM_LOGE("Invalid port index %u\r\n", port);
				return RL_BADARG;
			}
			break;
		case 'b':
			if (!strcasecmp(optarg, "inbound"))
				mode = RBCM_INBOUND;
			else if (!strcasecmp(optarg, "outbound"))
				mode = RBCM_OUTBOUND;
			else
				return RL_BADARG;
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	RBCM_LOGI("Scan TTREG %s, Port %u, Mode %s\r\n", get_module_name(idx), port,
			  mode == RBCM_INBOUND ? "Inbound" : "Outbound");

	return rbcm_dump_ttreg(idx, port, mode);
}

static int32_t rbcm_cli_clear_ttreg(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_BLK_INVALID;
	int clear_all = 1;
	int opt;

	optind = 0;
	while ((opt = getopt(argc, argv, "m:")) != -1) {
		switch (opt) {
		case 'm':
			idx = get_rbc_module_argument(optarg);
			clear_all = 0;
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (clear_all)
		idx = 0; /* Set idx to 0 to validate arguments */

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	RBCM_LOGI("Clear TTREG %s\r\n", clear_all ? "all" : get_module_name(idx));

	if (clear_all)
		rbcm_clear_ttreg_all();
	else
		rbcm_clear_ttreg(idx);

	return RL_OK;
}

static int32_t rbcm_cli_set_loopback(int argc, char *argv[])
{
	enum rbc_lb_type lb_type = RBC_LB_PORT;
	int enable = RBCM_LOOPBACK_ENABLE;
	enum rbcm_module idx = RBC_C0S0;
	int opt;

	optind = 0;
	while ((opt = getopt(argc, argv, "m:l:d")) != -1) {
		switch (opt) {
		case 'm':
			idx = get_rbc_module_argument(optarg);
			break;
		case 'l':
			if (!strcasecmp(optarg, "Port"))
				lb_type = RBC_LB_PORT;
			else if (!strcasecmp(optarg, "Inner"))
				lb_type = RBC_LB_INNER;
			else if (!strcasecmp(optarg, "Outer"))
				lb_type = RBC_LB_OUTER;
			else
				return RL_BADARG;
			break;
		case 'd':
			enable =
				RBCM_LOOPBACK_DISABLE; /* -d flag means disable */
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	RBCM_LOGI("Setting RBC Port %s loopback mode to %d, %s\r\n",
			  get_module_name(idx), lb_type,
			  enable == RBCM_LOOPBACK_ENABLE ? "enabled" : "disabled");
	if (enable == RBCM_LOOPBACK_DISABLE)
		return rbcm_disable_loopback(idx, lb_type);
	else if (enable == RBCM_LOOPBACK_ENABLE)
		return rbcm_enable_loopback(idx, lb_type);

	return RL_BADARG;
}

static int32_t rbcm_cli_set_timeout(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_C0S0;
	uint32_t timeout_ns = 0;
	int opt;

	optind = 0;
	while ((opt = getopt(argc, argv, "t:m:")) != -1) {
		switch (opt) {
		case 'm':
			idx = get_rbc_module_argument(optarg);
			break;
		case 't':
			if (!conv_str_to_uint32(optarg, &timeout_ns))
				return RL_BADARG;
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	if (timeout_ns == 0) {
		RBCM_LOGI("No timeout provided, using default %u ns\r\n", TIMEOUT_NS_DEFAULT);
		timeout_ns = TIMEOUT_NS_DEFAULT;
	}

	RBCM_LOGI("Setting RBC Port %s timeout to %u ns\r\n",
			  get_module_name(idx), timeout_ns);

	return rbcm_set_timeout_interval(idx, timeout_ns);
}

static int32_t rbcm_cli_get_timeout(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_C0S0;
	uint32_t tick = 0;
	uint32_t window = 0;
	uint32_t rbcm_clk_mhz = 0;
	uint64_t timeout_ns = 0;
	int32_t ret;
	int opt;

	optind = 0;
	while ((opt = getopt(argc, argv, "m:")) != -1) {
		switch (opt) {
		case 'm':
			idx = get_rbc_module_argument(optarg);
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	ret = rbcm_get_timeout_interval(idx, &tick, &window,
									&timeout_ns, &rbcm_clk_mhz);
	if (ret != RL_OK)
		return ret;

	RBCM_LOGI("RBC Port %s timeout: tick=%u window=%u rbcm_clk=%uMHz timeout=%llu ns\r\n",
			  get_module_name(idx), tick, window, rbcm_clk_mhz,
			  (unsigned long long)timeout_ns);

	return RL_OK;
}

static int32_t rbcm_cli_set_irq(int argc, char *argv[], int is_disable_cmd)
{
	enum rbcm_module idx = RBC_C0S0;
	int port_err = 0, timeout = 0, cbus_err = 0, utg_err = 0, ttreg_err = 0, utg_done = 0;
	int opt;
	int all_modules = 0;
	int module_specified = 0;

	optind = 0;
	while ((opt = getopt(argc, argv, "a:m:")) != -1) {
		switch (opt) {
		case 'a':
			if (!optarg || strcasecmp(optarg, "all"))
				return RL_BADARG;
			all_modules = 1;
			break;
		case 'm':
			idx = get_rbc_module_argument(optarg);
			module_specified = 1;
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	/* -a and -m are mutually exclusive */
	if (all_modules && module_specified) {
		RBCM_LOGE("-a and -m cannot be used together\r\n");
		return RL_BADARG;
	}

	if (!all_modules) {
		if (rbcm_module_valid(idx) != RL_OK) {
			RBCM_LOGE("Invalid RBC module %s\r\n", get_module_name(idx));
			return RL_BADARG;
		}
	}

	if (optind == argc) {
		/* No specific IRQ type provided, enable/disable all */
		port_err = 1; timeout = 1; cbus_err = 1;
		utg_err = 1; ttreg_err = 1; utg_done = 1;
	} else {
		struct irq_map_entry {
			const char *name;
			int *flag;
		};

		struct irq_map_entry irq_map[] = {
			{ "port", &port_err },   { "timeout", &timeout },
			{ "cbus", &cbus_err },   { "ttreg", &ttreg_err },
			{ "utg_done", &utg_done },   { "utg_err", &utg_err },
		};

		for (int i = optind; i < argc; i++) {
			char param_buf[32];

			strncpy(param_buf, argv[i], sizeof(param_buf) - 1);
			param_buf[sizeof(param_buf) - 1] = '\0';
			strtolowercase(param_buf);

			if (strstr(param_buf, "all")) {
				port_err = 1; timeout = 1; cbus_err = 1;
				utg_err = 1; ttreg_err = 1; utg_done = 1;
				break;
			}

			for (int j = 0; j < ARRAY_SIZE(irq_map); j++) {
				if (strstr(param_buf, irq_map[j].name))
					*irq_map[j].flag = 1;
			}
		}
	}

	if (all_modules) {
		int32_t final_ret = RL_OK;

		for (int i = 0; i < RBC_MODULE_COUNT; i++) {
			int32_t r = rbcm_configure_interrupts(i, is_disable_cmd, port_err, timeout,
												  cbus_err, utg_err, ttreg_err,
												  utg_done);
			if (r != RL_OK)
				final_ret = r;
		}
		return final_ret;
	}

	return rbcm_configure_interrupts(idx, is_disable_cmd, port_err, timeout,
								     cbus_err, utg_err, ttreg_err, utg_done);
}

static int32_t rbcm_cli_enable_irq(int argc, char *argv[])
{
	return rbcm_cli_set_irq(argc, argv, RBCM_IRQ_ENABLE);
}

static int32_t rbcm_cli_disable_irq(int argc, char *argv[])
{
	return rbcm_cli_set_irq(argc, argv, RBCM_IRQ_DISABLE);
}

static int32_t rbcm_cli_check_ucie(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_C0S0;
	int opt;
	int run_all = 0;
	int module_specified = 0;

	optind = 0;
	while ((opt = getopt(argc, argv, "am:")) != -1) {
		switch (opt) {
		case 'a':
			run_all = 1;
			break;
		case 'm':
			idx = get_rbc_module_argument(optarg);
			module_specified = 1;
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if ((run_all && module_specified) || (run_all && optind != argc))
		return RL_BADARG;

	if (run_all) {
		int32_t ret = RL_OK;

		for (int i = 0; i < RBC_MODULE_COUNT; i++) {
			int32_t result = rbcm_dump_ucie_link_health(i);

			if (result != RL_OK)
				ret = result;
		}
		return ret;
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	return rbcm_dump_ucie_link_health(idx);
}

static int32_t rbcm_cli_check_crc(int argc, char *argv[])
{
	enum rbcm_module idx = RBC_C0S0;
	int opt;
	int run_all = 0;
	int module_specified = 0;

	optind = 0;
	while ((opt = getopt(argc, argv, "am:")) != -1) {
		switch (opt) {
		case 'a':
			run_all = 1;
			break;
		case 'm':
			idx = get_rbc_module_argument(optarg);
			module_specified = 1;
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if ((run_all && module_specified) || (run_all && optind != argc))
		return RL_BADARG;

	if (run_all) {
		int32_t ret = RL_OK;

		for (int i = 0; i < RBC_MODULE_COUNT; i++) {
			int32_t result = rbcm_dump_ucie_crc(i);

			if (result != RL_OK)
				ret = result;
		}
		return ret;
	}

	if (!cli_validate(idx, argc, optind))
		return RL_BADARG;

	return rbcm_dump_ucie_crc(idx);
}

static enum rbcm_module get_remote_module(enum rbcm_module idx)
{
	/* Mapping table for remote modules, indexed by enum rbcm_module */
	static const enum rbcm_module remote_map[] = {
		[RBC_C0S0] = RBC_C1N1, [RBC_C1N1] = RBC_C0S0,
		[RBC_C0S1] = RBC_C1N0, [RBC_C1N0] = RBC_C0S1,
		[RBC_C0E0] = RBC_C2E1, [RBC_C2E1] = RBC_C0E0,
		[RBC_C0E1] = RBC_C2E0, [RBC_C2E0] = RBC_C0E1,
		[RBC_C1E0] = RBC_C3E1, [RBC_C3E1] = RBC_C1E0,
		[RBC_C1E1] = RBC_C3E0, [RBC_C3E0] = RBC_C1E1,
		[RBC_C2N0] = RBC_C3S1, [RBC_C3S1] = RBC_C2N0,
		[RBC_C2N1] = RBC_C3S0, [RBC_C3S0] = RBC_C2N1,
	};

	if (idx < 0 || idx >= RBC_MODULE_COUNT)
		return RBC_BLK_INVALID;

	return remote_map[idx];
}

static int32_t test_loopback_inner(enum rbcm_module idx, enum rbc_port port)
{
	enum rbcm_module remote = get_remote_module(idx);
	uint64_t addr = DEFAULT_UTG_ADDR;
	int ret = RL_OK;

	rbcm_clear_ttreg_all();
	rbcm_enable_loopback(idx, RBC_LB_INNER);
	rbcm_user_traffic_generation(idx, port, RBCM_WR_TRANS, addr, 0);
	if (!rbcm_is_utg_recorded(idx, port, RBCM_OUTBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - No OB Packet Recorded\r\n", get_module_name(idx), port);
		ret = RL_ERROR;
		goto cleanup;
	}

	if (rbcm_is_utg_recorded(remote, port, RBCM_INBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - Unexpected IB Packet Remote\r\n", get_module_name(remote), port);
		ret = RL_ERROR;
		goto cleanup;
	}

cleanup:
	rbcm_disable_loopback(idx, RBC_LB_INNER);
	rbcm_clear_ttreg_all();

	return ret;
}

static int32_t test_loopback_outer(enum rbcm_module idx, enum rbc_port port)
{
	enum rbcm_module remote = get_remote_module(idx);
	uint64_t addr = DEFAULT_UTG_ADDR;
	int ret = RL_OK;

	rbcm_clear_ttreg_all();
	rbcm_enable_loopback(remote, RBC_LB_OUTER);
	rbcm_user_traffic_generation(idx, port, RBCM_WR_TRANS, addr, 0);
	if (!rbcm_is_utg_recorded(idx, port, RBCM_OUTBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - No OB packet\r\n", get_module_name(idx), port);
		ret = RL_ERROR;
		goto cleanup;
	}
	if (!rbcm_is_utg_recorded(remote, port, RBCM_INBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - No IB packet Remote\r\n", get_module_name(remote), port);
		ret = RL_ERROR;
		goto cleanup;
	}

cleanup:
	rbcm_disable_loopback(remote, RBC_LB_OUTER);
	rbcm_clear_ttreg_all();
	return ret;
}

static int32_t test_loopback_port(enum rbcm_module idx, enum rbc_port port)
{
	enum rbcm_module remote = get_remote_module(idx);
	uint64_t addr = DEFAULT_UTG_ADDR;
	int ret = RL_OK;

	rbcm_clear_ttreg_all();
	rbcm_enable_loopback(remote, RBC_LB_PORT);
	rbcm_user_traffic_generation(idx, port, RBCM_WR_TRANS, addr, 0);
	if (!rbcm_is_utg_recorded(idx, port, RBCM_OUTBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - No OB packet\r\n", get_module_name(idx), port);
		ret = RL_ERROR;
		goto cleanup;
	}
	if (!rbcm_is_utg_recorded(idx, port, RBCM_INBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - No IB packet\r\n", get_module_name(idx), port);
		ret = RL_ERROR;
		goto cleanup;
	}
	if (!rbcm_is_utg_recorded(remote, port, RBCM_OUTBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - No OB packet remote\r\n", get_module_name(remote), port);
		ret = RL_ERROR;
		goto cleanup;
	}
	if (!rbcm_is_utg_recorded(remote, port, RBCM_INBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - No IB packet remote\r\n", get_module_name(remote), port);
		ret = RL_ERROR;
		goto cleanup;
	}

cleanup:
	/* Disable Port Loopback Mode */
	rbcm_disable_loopback(remote, RBC_LB_PORT);
	rbcm_clear_ttreg_all();

	return ret;
}

int32_t rbcm_test_loopback(enum rbcm_module idx, enum rbc_port port)
{
	int ret = RL_OK;

	ret = test_loopback_inner(idx, port);
	RBCM_LOGI("%s, Port %d -- Inner Loopback Test -> %s\r\n", get_module_name(idx), port,
			  (ret == RL_OK ? "PASSED" : "FAILED"));
#ifndef RBCM_SKIP_PORT_LOOPBACK
	ret = test_loopback_port(idx, port);
	RBCM_LOGI("%s, Port %d -- Port Loopback Test -> %s\r\n", get_module_name(idx), port,
			  (ret == RL_OK ? "PASSED" : "FAILED"));
#endif
#ifndef RBCM_SKIP_OUTER_LOOPBACK
	ret = test_loopback_outer(idx, port);
	RBCM_LOGI("%s, Port %d -- Outer Loopback Test -> %s\r\n", get_module_name(idx), port,
			  (ret == RL_OK ? "PASSED" : "FAILED"));
#endif
	return ret;
}

static int32_t rbcm_test_loopback_all(void)
{
	int32_t ret = RL_OK;

	for (int i = 0; i < RBC_MODULE_COUNT; i++) {
		for (int port = 0; port < (RBC_PORT_COUNT - 1); port++) {
			/*
			 * Loop iterates only up to RBC_PORT_COUNT - 1 because Port2 is used
			 * exclusively for command transmission.
			 * Loopback is not applied to Port2, so it is skipped in this process.
			 */
			RBCM_LOGI("Testing Loopback for Module %s, Port %d\r\n", get_module_name(i), port);
			ret = rbcm_test_loopback(i, port);
			if (ret != RL_OK)
				break;
		}
	}

	return ret;
}

static int32_t rbcm_test_ttreg(enum rbcm_module idx, enum rbc_port port)
{
	uint64_t addr = DEFAULT_UTG_ADDR;
	int32_t ret = RL_OK;

	rbcm_clear_ttreg_all();
	rbcm_enable_loopback(idx, RBC_LB_INNER);
	rbcm_user_traffic_generation(idx, port, RBCM_WR_TRANS, addr, 0);
	if (!rbcm_is_utg_recorded(idx, port, RBCM_OUTBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("No OB recorded for idx %s, port %d\r\n", get_module_name(idx), port);
		ret = RL_ERROR;
		goto out;
	}
	rbcm_clear_ttreg_all();
	if (rbcm_is_utg_recorded(idx, port, RBCM_OUTBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("OB should NOT recorded for idx %s, port %d\r\n", get_module_name(idx), port);
		ret = RL_ERROR;
		goto out;
	}

out:
	rbcm_disable_loopback(idx, RBC_LB_INNER);

	return ret;
}

static int32_t rbcm_test_soft_reset(enum rbcm_module idx)
{
	int32_t ret = RL_OK;
	int port = 0;

	rbcm_clear_ttreg_all();
	rbcm_enable_loopback(idx, RBC_LB_INNER);
	rbcm_user_traffic_generation(idx, port, RBCM_WR_TRANS, DEFAULT_UTG_ADDR, 0);
	if (!rbcm_is_utg_recorded(idx, port, RBCM_OUTBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - No OB Packet Recorded\r\n", get_module_name(idx), port);
		ret = RL_ERROR;
		goto cleanup;
	}
	rbcm_sw_reset(idx);
	if (rbcm_is_utg_recorded(idx, port, RBCM_OUTBOUND, RBCM_WR_TRANS, 0)) {
		RBCM_LOGE("%s, Port %d - Unexpected OB Packet after Sw Rst\r\n",
				  get_module_name(idx), port);
		ret = RL_ERROR;
		goto cleanup;
	}

cleanup:
	rbcm_clear_ttreg_all();
	rbcm_disable_loopback(idx, RBC_LB_INNER);

	return ret;
}

static void run_loopback_suite(struct test_counts *counts)
{
	for (int i = 0; i < RBC_MODULE_COUNT; i++) {
		for (int port = 0; port < (RBC_PORT_COUNT - 1); port++) {
			int32_t ret;

			counts->total++;
			RBCM_LOGI("Testing Loopback for Module %s, Port %d\r\n", get_module_name(i), port);
			ret = rbcm_test_loopback(i, port);
			if (ret == RL_OK)
				counts->pass++;
			else
				counts->fail++;
		}
	}
}

static void run_ttreg_suite(struct test_counts *counts)
{
	for (int i = 0; i < RBC_MODULE_COUNT; i++) {
		for (int port = 0; port < (RBC_PORT_COUNT - 1); port++) {
			int32_t ret;

			counts->total++;
			ret = rbcm_test_ttreg(i, port);
			RBCM_LOGI("Testing TTREG for Module %s, Port %d -> %s\r\n", get_module_name(i), port,
					  ret == RL_OK ? "PASSED" : "FAILED");
			if (ret == RL_OK)
				counts->pass++;
			else
				counts->fail++;
		}
	}
}

static void run_regacc_suite(struct test_counts *counts)
{
	for (int i = 0; i < RBC_MODULE_COUNT; i++) {
		int32_t ret;

		counts->total++;
		ret = rbcm_reg_acc_test(i);
		RBCM_LOGI("Testing Reg Access for Module %s -> %s\r\n", get_module_name(i),
				  ret == RL_OK ? "PASSED" : "FAILED");
		if (ret == RL_OK)
			counts->pass++;
		else
			counts->fail++;
	}
}

static void run_softreset_suite(struct test_counts *counts)
{
	for (int i = 0; i < RBC_MODULE_COUNT; i++) {
		int32_t ret;

		counts->total++;
		ret = rbcm_test_soft_reset(i);
		RBCM_LOGI("Testing Soft Reset for Module %s -> %s\r\n", get_module_name(i),
				  ret == RL_OK ? "PASSED" : "FAILED");
		if (ret == RL_OK)
			counts->pass++;
		else
			counts->fail++;
	}
}

static void print_summary_table(int run_loopback_tests,
								int run_ttreg_tests,
								int run_reg_acc_tests,
								int run_softrst_tests,
								const struct test_counts *loopback,
								const struct test_counts *ttreg,
								const struct test_counts *regacc,
								const struct test_counts *softrst)
{
	RBCM_LOGI("\r\n");
	RBCM_LOGI("+----------------+--------+--------+--------+\r\n");
	RBCM_LOGI("| Test           |  Total | Passed | Failed |\r\n");
	RBCM_LOGI("+----------------+--------+--------+--------+\r\n");
	if (run_loopback_tests)
		RBCM_LOGI("| Loopback       | %6d | %6d | %6d |\r\n",
				  loopback->total, loopback->pass, loopback->fail);
	if (run_ttreg_tests)
		RBCM_LOGI("| TTREG          | %6d | %6d | %6d |\r\n",
				  ttreg->total, ttreg->pass, ttreg->fail);
	if (run_reg_acc_tests)
		RBCM_LOGI("| Reg Access     | %6d | %6d | %6d |\r\n",
				  regacc->total, regacc->pass, regacc->fail);
	if (run_softrst_tests)
		RBCM_LOGI("| Soft Reset     | %6d | %6d | %6d |\r\n",
				  softrst->total, softrst->pass, softrst->fail);
	RBCM_LOGI("+----------------+--------+--------+--------+\r\n");
}

static int handle_t_arg(const char *optarg,
						int *run_loopback_tests,
						int *run_ttreg_tests,
						int *run_reg_acc_tests,
						int *run_softrst_tests)
{
	char local_buf[128];
	char *token;

	strncpy(local_buf, optarg, sizeof(local_buf) - 1);
	local_buf[sizeof(local_buf) - 1] = '\0';

	if (!strcasecmp(local_buf, "all")) {
		*run_loopback_tests = 1;
		*run_ttreg_tests = 1;
		*run_reg_acc_tests = 1;
		*run_softrst_tests = 1;

		return RL_OK;
	}

	token = strtok(local_buf, ",");
	while (token) {
		if (!strcasecmp(token, "loopback"))
			*run_loopback_tests = 1;
		else if (!strcasecmp(token, "ttreg"))
			*run_ttreg_tests = 1;
		else if (!strcasecmp(token, "reg_acc"))
			*run_reg_acc_tests = 1;
		else if (!strcasecmp(token, "soft_reset"))
			*run_softrst_tests = 1;
		else
			return RL_BADARG;
		token = strtok(NULL, ",");
	}

	return RL_OK;
}

static int parse_test_all_opts(int argc, char *argv[],
							   int *run_loopback_tests,
							   int *run_ttreg_tests,
							   int *run_reg_acc_tests,
							   int *run_softrst_tests)
{
	int opt;

	optind = 0;
	while ((opt = getopt(argc, argv, "t:")) != -1) {
		switch (opt) {
		case 't':
			if (handle_t_arg(optarg, run_loopback_tests,
							 run_ttreg_tests, run_reg_acc_tests,
							 run_softrst_tests) != RL_OK)
				return RL_BADARG;
			break;
		case 'h':
			return RL_BADARG;
		default:
			break;
		}
	}

	if (!*run_loopback_tests && !*run_ttreg_tests &&
	    !*run_reg_acc_tests && !*run_softrst_tests) {
		*run_loopback_tests = 1;
		*run_ttreg_tests = 1;
		*run_reg_acc_tests = 1;
		*run_softrst_tests = 1;
	}

	return RL_OK;
}

static int32_t rbcm_cli_test_all(int argc, char *argv[])
{
	int run_loopback_tests = 0;
	int run_reg_acc_tests = 0;
	int run_ttreg_tests = 0;
	int run_softrst_tests = 0;
	struct test_counts loopback = { 0 };
	struct test_counts ttreg = { 0 };
	struct test_counts regacc = { 0 };
	struct test_counts softrst = { 0 };

	if (parse_test_all_opts(argc, argv, &run_loopback_tests,
							&run_ttreg_tests, &run_reg_acc_tests,
							&run_softrst_tests) != RL_OK)
		return RL_BADARG;

	if (run_reg_acc_tests)
		run_regacc_suite(&regacc);
	if (run_loopback_tests)
		run_loopback_suite(&loopback);
	if (run_ttreg_tests)
		run_ttreg_suite(&ttreg);
	if (run_softrst_tests)
		run_softreset_suite(&softrst);

	print_summary_table(run_loopback_tests, run_ttreg_tests,
						run_reg_acc_tests, run_softrst_tests,
						&loopback, &ttreg, &regacc, &softrst);

	return RL_OK;
}

static const struct rbcm_cli_cmd rbcm_cmds[] = {
	{ "sw_reset", rbcm_sw_reset_help, rbcm_cli_sw_reset },
	{ "scan_ttreg", rbcm_scan_ttreg_help, rbcm_cli_scan_ttreg },
	{ "dump_incomplete_ttreg", rbcm_dump_incomplete_ttreg_help, rbcm_cli_dump_incomplete_ttreg },
	{ "clear_ttreg", rbcm_clear_ttreg_help, rbcm_cli_clear_ttreg },
	{ "utg_write", rbcm_utg_write_help, rbcm_cli_utg_write },
	{ "utg_read", rbcm_utg_read_help, rbcm_cli_utg_read },
	{ "addr_remap", rbcm_addr_remap_help, rbcm_cli_addr_remap },
	{ "set_loopback", rbcm_set_loopback_help, rbcm_cli_set_loopback },
	{ "set_timeout", rbcm_set_timeout_help, rbcm_cli_set_timeout },
	{ "get_timeout", rbcm_get_timeout_help, rbcm_cli_get_timeout },
	{ "enable_irq", rbcm_enable_irq_help, rbcm_cli_enable_irq },
	{ "disable_irq", rbcm_disable_irq_help, rbcm_cli_disable_irq },
	{ "check_crc", rbcm_check_crc_help, rbcm_cli_check_crc },
	{ "check_ucie", rbcm_check_ucie_help, rbcm_cli_check_ucie },
	{ "reg_acc_test", rbcm_reg_acc_test_help, rbcm_cli_reg_acc_test },
	{ "test_all", rbcm_test_all_help, rbcm_cli_test_all }
};

static int32_t rbcm_cli_dispatch(int argc, char *argv[])
{
	int32_t ret;

	if (argc == 0)
		return RL_BADARG;

	for (int i = 0; i < ARRAY_SIZE(rbcm_cmds); i++) {
		if (!strcasecmp(argv[0], rbcm_cmds[i].name)) {
			ret = rbcm_cmds[i].handler(argc, argv);
			if (ret != RL_OK)
				RBCM_LOGI("Usage: %s\r\n", rbcm_cmds[i].help);
			return RL_OK;
		}
	}

	RBCM_LOGE("Unknown rbc_test command '%s'\r\n", argv[0]);

	return RL_BADARG;
}

uint8_t rbcm_cli_handler(int argc, char *argv[])
{
	return (rbcm_cli_dispatch(argc, argv) == RL_OK);
}

CLI_REGISTER(rbc_test, NULL, rbcm_cli_handler, rbcm_test_help);
