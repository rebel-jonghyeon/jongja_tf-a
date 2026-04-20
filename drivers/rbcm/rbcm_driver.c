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
#include <driver.h>

#include "rbcm_driver.h"
#include "rbcm_core.h"
#include "rbcm_common.h"

#define dev_fmt(fmt)	"[UCIe] " fmt

struct rbcm_data rbcm[RBC_MODULE_COUNT] = {
	RBCM_ENTRY(0, S0, "CL0_V10 (C0S0)"),
	RBCM_ENTRY(0, S1, "CL0_V11 (C0S1)"),
	RBCM_ENTRY(0, E0, "CL0_H00 (C0E0)"),
	RBCM_ENTRY(0, E1, "CL0_H01 (C0E1)"),
	RBCM_ENTRY(1, N0, "CL1_V00 (C1N0)"),
	RBCM_ENTRY(1, N1, "CL1_V01 (C1N1)"),
	RBCM_ENTRY(1, E0, "CL1_H00 (C1E0)"),
	RBCM_ENTRY(1, E1, "CL1_H01 (C1E1)"),
	RBCM_ENTRY(2, N0, "CL2_V00 (C2N0)"),
	RBCM_ENTRY(2, N1, "CL2_V01 (C2N1)"),
	RBCM_ENTRY(2, E0, "CL2_H00 (C2E0)"),
	RBCM_ENTRY(2, E1, "CL2_H01 (C2E1)"),
	RBCM_ENTRY(3, S0, "CL3_V10 (C3S0)"),
	RBCM_ENTRY(3, S1, "CL3_V11 (C3S1)"),
	RBCM_ENTRY(3, E0, "CL3_H00 (C3E0)"),
	RBCM_ENTRY(3, E1, "CL3_H01 (C3E1)")
};

static struct rbcm_data *get_rbcm_module(enum rbcm_module idx)
{
	if (idx >= 0 && idx < RBC_BLK_INVALID)
		return &rbcm[idx];
	else
		return NULL;
}

void rbcm_sw_reset(enum rbcm_module idx)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry) {
		RBCM_LOGE("Invalid rbcm index %d\r\n", idx);
		return;
	}

	rbcm_core_sw_reset(entry);
}

void rbcm_sw_reset_all(void)
{
	for (int i = 0; i < RBC_MODULE_COUNT; i++)
		rbcm_sw_reset(i);
}

void rbcm_clear_ttreg(enum rbcm_module idx)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry) {
		RBCM_LOGE("Invalid rbcm index %d\r\n", idx);
		return;
	}

	rbcm_core_clear_ttreg(entry);
}

void rbcm_clear_ttreg_all(void)
{
	for (int i = 0; i < RBC_MODULE_COUNT; i++)
		rbcm_clear_ttreg(i);
}

void rbcm_dump_chiplet_incomplete_ttreg(int chiplet_id)
{
	for (int i = 0; i < RBC_MODULE_COUNT; i++) {
		if (rbcm[i].chiplet_id == chiplet_id)
			rbcm_core_dump_incomplete_ttreg(&rbcm[i]);
	}
}

void rbcm_dump_incomplete_ttreg(enum rbcm_module idx)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry) {
		RBCM_LOGE("Invalid rbcm index %d\r\n", idx);
		return;
	}

	rbcm_core_dump_incomplete_ttreg(entry);
}

void rbcm_recover_from_reset(enum rbcm_module idx)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry) {
		RBCM_LOGE("Invalid rbcm index %d\r\n", idx);
		return;
	}

	rbcm_core_recover_from_reset(entry);
}

int32_t rbcm_addr_remap(enum rbcm_module idx, uint32_t msb_from,
						uint32_t msb_to)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	if (msb_from > MAX_MSB_IDX || msb_to > MAX_MSB_IDX) {
		RBCM_LOGE("Invalid MSB index (0-15 allowed)\r\n");
		return RL_BADARG;
	}

	return rbcm_core_addr_remap(entry, msb_from, msb_to);
}

int32_t rbcm_user_traffic_generation(enum rbcm_module idx, enum rbc_port port,
									 int read_access, uint64_t target_address,
									 int next_user_transaction_id)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	return rbcm_core_user_traffic_generation(entry, port,
											 read_access, target_address,
											 next_user_transaction_id);
}

int32_t rbcm_dump_ttreg(enum rbcm_module idx, enum rbc_port port, int mode)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry) {
		RBCM_LOGE("Invalid rbcm index %d\r\n", idx);
		return RL_BADARG;
	}

	return rbcm_core_dump_ttreg(entry, port, mode);
}

int32_t rbcm_enable_loopback(enum rbcm_module idx, enum rbc_lb_type lb_type)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	return rbcm_core_set_loopback_mode(entry, lb_type, RBCM_LOOPBACK_ENABLE);
}

int32_t rbcm_disable_loopback(enum rbcm_module idx, enum rbc_lb_type lb_type)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	return rbcm_core_set_loopback_mode(entry, lb_type, RBCM_LOOPBACK_DISABLE);
}

int32_t rbcm_set_timeout_interval(enum rbcm_module idx, uint32_t timeout_ns)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	return rbcm_core_set_timeout_interval(entry, timeout_ns);
}

int32_t rbcm_get_timeout_interval(enum rbcm_module idx,
								  uint32_t *tick,
								  uint32_t *window,
								  uint64_t *timeout_ns,
								  uint32_t *rbcm_clk_mhz)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	return rbcm_core_get_timeout_interval(entry, tick, window, timeout_ns,
					     rbcm_clk_mhz);
}

int32_t rbcm_configure_interrupts(enum rbcm_module idx, int disable, int port_err,
								  int timeout, int cbus_err, int utg_err,
								  int ttreg_err, int utg_done)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	return rbcm_core_configure_interrupts(entry, disable, port_err, timeout,
								   cbus_err, utg_err, ttreg_err, utg_done);
}

int32_t rbcm_dump_ucie_link_health(enum rbcm_module idx)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	return rbcm_core_dump_ucie_link_health(entry);
}

int32_t rbcm_dump_ucie_crc(enum rbcm_module idx)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	return rbcm_core_dump_ucie_crc(entry);
}

uint64_t get_rbcm_base(enum rbcm_module idx)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return 0;

	return (uint64_t)(uintptr_t)entry->reg;
}

const char *get_module_name(enum rbcm_module idx)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	return (entry) ? entry->name : NULL;
}

bool rbcm_is_utg_recorded(enum rbcm_module idx, enum rbc_port port, int inbound,
						  int read_access, int axi_id)
{
	struct rbcm_data *entry = get_rbcm_module(idx);

	if (!entry)
		return RL_BADARG;

	return rbcm_core_is_utg_recorded(entry, port, inbound,
									 read_access, axi_id);
}

static void rbcm_init_irq_handler(void)
{
	for (int i = 0; i < RBC_MODULE_COUNT; i++) {
		struct rbcm_data *entry = get_rbcm_module(i);

		if (entry->chiplet_id == CHIPLET_ID) {
			gic_irq_connect(entry->intr_id, rbcm_irq_handler,
							(void *)entry);
			gic_irq_enable(entry->intr_id);
		}
	}
}

static void rbcm_set_timeout_interval_all(uint32_t timeout_ns)
{
	for (int i = 0; i < RBC_MODULE_COUNT; i++) {
		struct rbcm_data *entry = get_rbcm_module(i);

		if (entry->chiplet_id == CHIPLET_ID)
			rbcm_core_set_timeout_interval(entry, timeout_ns);
	}
}

int rbcm_driver_init(void)
{
	rbcm_init_irq_handler();
	/* Set default timeout interval for all RBC modules */
	rbcm_set_timeout_interval_all(TIMEOUT_NS_DEFAULT);
	return 0;
}

#if CHIPLET_COUNT > 1
DRIVER_INIT_ENTRY_DEFINE(5, rbcm_driver_init);
#endif
