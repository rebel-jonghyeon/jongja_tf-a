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

#ifndef __RBCM_DRIVER_H
#define __RBCM_DRIVER_H

#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "rbcm.h"
#include "rbcm_reg_model.h"
#include "rl_errors.h"
#include "rl_utils.h"

#define MAX_MSB_IDX (15)

void rbcm_sw_reset(enum rbcm_module idx);
void rbcm_sw_reset_all(void);
void rbcm_clear_ttreg(enum rbcm_module idx);
void rbcm_clear_ttreg_all(void);
void rbcm_dump_incomplete_ttreg(enum rbcm_module idx);
void rbcm_dump_chiplet_incomplete_ttreg(int chiplet_id);
void rbcm_recover_from_reset(enum rbcm_module idx);
int32_t rbcm_addr_remap(enum rbcm_module idx, uint32_t msb_from,
						uint32_t msb_to);
int32_t rbcm_user_traffic_generation(enum rbcm_module idx, enum rbc_port port,
									 int read_access, uint64_t target_address,
									 int next_user_transaction_id);
int32_t rbcm_dump_ttreg(enum rbcm_module idx, enum rbc_port port, int mode);
int32_t rbcm_enable_loopback(enum rbcm_module idx, enum rbc_lb_type lb_type);
int32_t rbcm_disable_loopback(enum rbcm_module idx, enum rbc_lb_type lb_type);
int32_t rbcm_set_timeout_interval(enum rbcm_module idx, uint32_t timeout_ns);
int32_t rbcm_get_timeout_interval(enum rbcm_module idx,
								  uint32_t *tick,
								  uint32_t *window,
								  uint64_t *timeout_ns,
								  uint32_t *rbcm_clk_mhz);
int32_t rbcm_configure_interrupts(enum rbcm_module idx, int disable, int port_err,
								  int timeout, int cbus_err, int utg_err,
								  int ttreg_err, int utg_done);
int32_t rbcm_dump_ucie_link_health(enum rbcm_module idx);
int32_t rbcm_dump_ucie_crc(enum rbcm_module idx);
const char *get_module_name(enum rbcm_module idx);
uint64_t get_rbcm_base(enum rbcm_module idx);
bool is_valid_reg_acc(enum rbcm_module idx);
bool rbcm_is_utg_recorded(enum rbcm_module idx, enum rbc_port port, int inbound,
						  int read_access, int axi_id);
#endif /* __RBCM_DRIVER_H */
