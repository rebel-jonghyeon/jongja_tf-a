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

#ifndef __RBCM_CORE_H
#define __RBCM_CORE_H

#include <stdint.h>
#include <stdbool.h>
#include <arch/system_api.h>

#include "rbcm_reg_model.h"
#include "rbcm.h"

struct aw_ucie;
/*
 * ┌─────────────────┐ ┌─────────────────┐
 * │                 │ │                 │
 * │                 │ │                 │
 * │              ┌──┐ ┌──┐              │
 * │    Chiplet0  │ E│ │E │  Chiplet2    │
 * │              └──┘ └──┘              │
 * │     ┌─────┐     │ │     ┌─────┐     │
 * │     │  S  │     │ │     │  N  │     │
 * └─────└─────┘─────┘ └─────└─────┘─────┘
 * ┌─────┌─────┐─────┐ ┌─────┌─────┐─────┐
 * │     │  N  │     │ │     │  S  │     │
 * │     └─────┘     │ │     └─────┘     │
 * │              ┌──┐ ┌──┐              │
 * │    Chiplet1  │ E│ │E │  Chiplet3    │
 * │              └──┘ └──┘              │
 * │                 │ │                 │
 * │                 │ │                 │
 * └─────────────────┘ └─────────────────┘
 * This shows the RBC modules and their relationships.
 */

#define RBC_C0S0_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x1FF5870000)
#define RBC_C0S1_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x1FF5C70000)
#define RBC_C0E0_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x1FF6070000)
#define RBC_C0E1_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x1FF6470000)
#define RBC_C1N0_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x3FF5070000)
#define RBC_C1N1_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x3FF5470000)
#define RBC_C1E0_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x3FF6070000)
#define RBC_C1E1_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x3FF6470000)
#define RBC_C2N0_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x5FF5070000)
#define RBC_C2N1_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x5FF5470000)
#define RBC_C2E0_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x5FF6070000)
#define RBC_C2E1_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x5FF6470000)
#define RBC_C3S0_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x7FF5870000)
#define RBC_C3S1_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x7FF5C70000)
#define RBC_C3E0_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x7FF6070000)
#define RBC_C3E1_SFR_ADDR   ((struct rbc_reg *)(uintptr_t)0x7FF6470000)

#define RBC_C0S0_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x1FF5820000)
#define RBC_C0S1_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x1FF5C20000)
#define RBC_C0E0_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x1FF6020000)
#define RBC_C0E1_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x1FF6420000)
#define RBC_C1N0_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x3FF5020000)
#define RBC_C1N1_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x3FF5420000)
#define RBC_C1E0_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x3FF6020000)
#define RBC_C1E1_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x3FF6420000)
#define RBC_C2N0_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x5FF5020000)
#define RBC_C2N1_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x5FF5420000)
#define RBC_C2E0_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x5FF6020000)
#define RBC_C2E1_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x5FF6420000)
#define RBC_C3S0_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x7FF5820000)
#define RBC_C3S1_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x7FF5C20000)
#define RBC_C3E0_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x7FF6020000)
#define RBC_C3E1_UCIE_ADDR  ((volatile struct aw_ucie *)(uintptr_t)0x7FF6420000)

#define INT_ID_BLK_RBC_V00_RBCM (302)
#define INT_ID_BLK_RBC_V01_RBCM (307)
#define INT_ID_BLK_RBC_V10_RBCM (312)
#define INT_ID_BLK_RBC_V11_RBCM (317)
#define INT_ID_BLK_RBC_H00_RBCM (322)
#define INT_ID_BLK_RBC_H01_RBCM (327)

#define INT_ID_BLK_RBC_N0_RBCM INT_ID_BLK_RBC_V00_RBCM
#define INT_ID_BLK_RBC_N1_RBCM INT_ID_BLK_RBC_V01_RBCM
#define INT_ID_BLK_RBC_S0_RBCM INT_ID_BLK_RBC_V10_RBCM
#define INT_ID_BLK_RBC_S1_RBCM INT_ID_BLK_RBC_V11_RBCM
#define INT_ID_BLK_RBC_E0_RBCM INT_ID_BLK_RBC_H00_RBCM
#define INT_ID_BLK_RBC_E1_RBCM INT_ID_BLK_RBC_H01_RBCM

#define RBCM_WR_TRANS                   (0)
#define RBCM_RD_TRANS                   (1)

#define RBCM_LOOPBACK_ENABLE            (0x3)
#define RBCM_LOOPBACK_DISABLE           (0)

#define RBCM_INBOUND                    (1)
#define RBCM_OUTBOUND                   (0)

/* Port Error Masks */
#define RBCM_PORT_ERR_N2U_OUT_WR_REQ    (0x01)
#define RBCM_PORT_ERR_N2U_OUT_WR_RESP   (0x02)
#define RBCM_PORT_ERR_N2U_OUT_RD_REQ    (0x04)
#define RBCM_PORT_ERR_N2U_OUT_RD_RESP   (0x08)
#define RBCM_PORT_ERR_U2N_IN_WR_REQ     (0x10)
#define RBCM_PORT_ERR_U2N_IN_WR_RESP    (0x20)
#define RBCM_PORT_ERR_U2N_IN_RD_REQ     (0x40)
#define RBCM_PORT_ERR_U2N_IN_RD_RESP    (0x80)

/* TTREG Error Masks */
#define RBCM_TTREG_ERR_OB_WR            (0x1)
#define RBCM_TTREG_ERR_OB_RD            (0x2)
#define RBCM_TTREG_ERR_IB_WR            (0x4)
#define RBCM_TTREG_ERR_IB_RD            (0x8)

/* UTG Done Masks */
#define RBCM_UTG_DONE_P0_W              (0x01)
#define RBCM_UTG_DONE_P0_R              (0x02)
#define RBCM_UTG_DONE_P1_W              (0x04)
#define RBCM_UTG_DONE_P1_R              (0x08)
#define RBCM_UTG_DONE_P2_W              (0x10)
#define RBCM_UTG_DONE_P2_R              (0x20)

#define RBCM_CHANNEL_COUNT              (12)
#define TTREG_MAX_ENTRIES               (128)
#define RBCM_DEFAULT_POLL_TIMEOUT       (1000)
#define RBCM_TTREG_POLL_TIMEOUT         (1000)
#define RBCM_UTG_DONE_ALL_MASK          (0x3F)

#define RBC_ADDR_REMAP_IN_VAL           (0xfedcba9876543210ULL)
#define RBC_ADDR_REMAP_OUT_VAL          (0xfedcba9876543210ULL)

#define RBCM_ENTRY(chip_idx, type_inst_suffix, name_str) \
{ \
	.chiplet_id = chip_idx, \
	.reg = RBC_C##chip_idx##type_inst_suffix##_SFR_ADDR, \
	.ucie = RBC_C##chip_idx##type_inst_suffix##_UCIE_ADDR, \
	.intr_id = INT_ID_BLK_RBC_##type_inst_suffix##_RBCM, \
	.name = name_str, \
	.module = RBC_C##chip_idx##type_inst_suffix, \
	.addr_remap_in_val = RBC_ADDR_REMAP_IN_VAL, \
	.addr_remap_out_val = RBC_ADDR_REMAP_OUT_VAL \
}

enum rbcm_ttreg_status {
	RBCM_TTREG_PENDING,
	RBCM_TTREG_ACC_FAIL,
	RBCM_TTREG_DBL_BIT_ERR,
	RBCM_TTREG_ERROR,
	RBCM_TTREG_IDLE,
	RBCM_TTREG_BUSY,
	RBCM_TTREG_COMPLETED,
	RBCM_TTREG_UNKNOWN
};

struct rbcm_ttreg_ret_data {
	struct rbc_reg_ttreg_ret_0_t ret_0;
	struct rbc_reg_ttreg_ret_1_t ret_1;
	struct rbc_reg_ttreg_ret_2_t ret_2;
	struct rbc_reg_ttreg_ret_3_t ret_3;

	uint64_t address;
	enum rbcm_ttreg_status status;
};

struct rbcm_direct_link {
	int src_id;
	int dst_id;
	enum rbcm_module module;
};

void rbcm_core_sw_reset(struct rbcm_data *entry);
void rbcm_core_clear_ttreg(struct rbcm_data *entry);
void rbcm_core_recover_from_reset(struct rbcm_data *entry);
void rbcm_core_sel_path_rbc_v10(void);
void rbcm_core_sel_path_rbc_v11(void);
int32_t rbcm_core_addr_remap(struct rbcm_data *entry, uint32_t msb_from,
							 uint32_t msb_to);
int32_t rbcm_core_user_traffic_generation(struct rbcm_data *entry, enum rbc_port port,
										  int read_access, uint64_t target_address,
										  int next_user_transaction_id);
int32_t rbcm_core_dump_ttreg(struct rbcm_data *entry, enum rbc_port port, int mode);
int32_t rbcm_core_set_loopback_mode(struct rbcm_data *entry,
									enum rbc_lb_type lb_type, uint32_t lb_val);
int32_t rbcm_core_set_timeout_interval(struct rbcm_data *entry,
									   uint32_t timeout_ns);
int32_t rbcm_core_get_timeout_interval(struct rbcm_data *entry,
									   uint32_t *tick,
									   uint32_t *window,
									   uint64_t *timeout_ns,
									   uint32_t *rbcm_clk_mhz);
int32_t rbcm_core_configure_interrupts(struct rbcm_data *entry, int disable, int port_err,
									   int timeout, int cbus_err, int utg_err,
									   int ttreg_err, int utg_done);
bool rbcm_core_is_utg_recorded(struct rbcm_data *entry, enum rbc_port port, int inbound,
							   int read_access, int axi_id);
int32_t rbcm_core_dump_ucie_link_health(struct rbcm_data *entry);
int32_t rbcm_core_dump_ucie_crc(struct rbcm_data *entry);
void rbcm_core_dump_incomplete_ttreg(struct rbcm_data *entry);
void rbcm_core_dump_all_chiplet_incomplete_ttreg(void);
void rbcm_core_dump_chiplet_incomplete_ttreg(int chiplet_id);
void rbcm_irq_handler(void *arg);

#endif /* __RBCM_CORE_H */
