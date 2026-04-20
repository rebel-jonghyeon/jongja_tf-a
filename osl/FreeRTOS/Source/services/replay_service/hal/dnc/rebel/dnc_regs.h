/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2023 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _DNC_REGS_COMMON_H_
#define _DNC_REGS_COMMON_H_

#include <stdint.h>
#include "g_sys_addrmap.h"

#include "g_dnc_memory_map.h"
#include "g_dnc_config.h"
#include "g_dnc_status.h"
#include "g_dnc_task_32b.h"
#include "g_dnc_task_done.h"
#include "g_dnc_exception.h"
#include "g_dnc_address.h"
#include "g_dnc_sync.h"
#include "g_dnc_init_cfg.h"
#include "g_dnc_uan_base.h"
#include "g_dnc_uan_nc.h"
#include "g_dnc_uan_ab.h"
#include "g_dnc_uan_sp.h"
#include "g_dnc_uan_udma.h"
#include "g_dnc_task_16b.h"

#include "g_dnc_uan_unit.h"

#include "hal/hw_spec.h"

struct __attribute__((packed, aligned(4))) dnc_reg_task_passage {
	union dnc_task_desc_id desc_id;
	union dnc_task_desc_mode desc_mode;
	union dnc_task_desc_prog0 desc_prog0;
	union dnc_task_desc_prog1 desc_prog1;
	union dnc_task_desc_prog2 desc_prog2;
	union dnc_task_desc_tsync desc_tsync;
//	uint32_t desc_tsync;
	union dnc_task_desc_cfg0 desc_cfg0;
	union dnc_task_desc_cfg1 desc_cfg1;
};

union dnc_reg_done_passage {
	struct __attribute__((packed)) {
		union dnc_task_done_done_rpt0 done_rpt0;
		uint32_t done_rpt1;
	};
	uint64_t bits;
};

union err_exception1 {
	struct __attribute__((packed)) {
		uint32_t ncore0_tu : 1;
		uint32_t ncore0_vu : 1;
		uint32_t ncore0_xvu : 1;
		uint32_t ncore0_ablu : 1;
		uint32_t ncore0_absu : 1;
		uint32_t ncore0_splu : 1;
		uint32_t ncore0_spsu : 1;
		uint32_t ncore0_rsvd : 1;	//8
		uint32_t ncore1_tu : 1;
		uint32_t ncore1_vu : 1;
		uint32_t ncore1_xvu : 1;
		uint32_t ncore1_ablu : 1;
		uint32_t ncore1_absu : 1;
		uint32_t ncore1_splu : 1;
		uint32_t ncore1_spsu : 1;
		uint32_t ncore1_rsvd : 1;	//8
		uint32_t ex_nclu : 1;
		uint32_t ex_ncsu : 1;
		uint32_t sp_ue : 1;
		uint32_t sp_perr : 1;
		uint32_t rsvd20 : 4;	//rsvd20~23	//8
		uint32_t ext_dbus_ue : 1;
		uint32_t ext_cbus_ue : 1;
		uint32_t pwr_single_only_vio : 1;
		uint32_t rsvd27 : 1;
		uint32_t tsync_token_ovf : 1;
		uint32_t rsvd29 : 3;	//rsvd29~31	//8
	};
	uint32_t bits;
};

union err_exception2 {
	struct __attribute__((packed)) {
		uint32_t ext_dbus_rd_resp0 : 1;
		uint32_t ext_dbus_rd_resp1 : 1;
		uint32_t ext_dbus_wr_resp0 : 1;
		uint32_t ext_dbus_wr_resp1 : 1;
		uint32_t ext_cbus_rd_resp0 : 1;
		uint32_t ext_cbus_rd_resp1 : 1;
		uint32_t ext_cbus_wr_resp0 : 1;
		uint32_t ext_cbus_wr_resp1 : 1;
		uint32_t reserved : 24;
	};
	uint32_t bits;
};
union err_exception3 {
	struct __attribute__((packed)) {
		uint32_t sp_ce : 1;
		uint32_t dbus_ce : 1;
		uint32_t cbus_ce : 1;
		uint32_t reserved : 29;
	};
	uint32_t bits;
};


#define CONFIG								ADDR_OFFSET_DNC_CONFIG
#define STATUS								ADDR_OFFSET_DNC_STATUS
#define TASK_32B							ADDR_OFFSET_DNC_TASK_32B
#define EXCEPTION							ADDR_OFFSET_DNC_EXCEPTION
#define ADDRESS								ADDR_OFFSET_DNC_ADDRESS
#define SYNC								ADDR_OFFSET_DNC_SYNC
#define UAN									ADDR_OFFSET_DNC_UAN
#define TASK_DONE							ADDR_OFFSET_DNC_TASK_DONE
#define TASK_DESC_CFG0						ADDR_OFFSET_DNC_TASK_DESC_CFG0
#define TASK_DESC_CFG1						ADDR_OFFSET_DNC_TASK_DESC_CFG1

#define TASK_16B 							ADDR_OFFSET_DNC_TASK_16B

#define DNC_CFG_SIZE                                        0x2000
#define DNC_TASK_EXT_PARA_COUNT								4
#define CMD_DESCR_DNC_TASK_COUNT							5
#define CMD_DESCR_DNC_PARA_DIFF_NUM							2
#define CMD_DESCR_DNC_PARA_UPDATE_HDR_NUM					2

#endif /* _DNC_REGS_COMMON_H_ */
