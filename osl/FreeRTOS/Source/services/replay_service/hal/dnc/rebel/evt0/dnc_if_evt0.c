/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2025 [Rebellions Inc.], All Rights Reserved.
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

#include "hal/interrupt.h"
#include "hal/dnc_if.h"
#include "hal/dnc/dnc_if_evt0.h"
#include "evt0/dnc_regs.h"
#include "rbln/log.h"
#include "replay.h"
#include "common/debug.h"

extern void __iomem *dnc_base[HW_SPEC_DNC_COUNT];

#define DNC_TASK_DONE_READ(id, off)			rl_readl_relaxed(dnc_base[id] + TASK_DONE + off)
#define DNC_TASK_DONE_WRITE(id, val, off)	rl_writel_relaxed(val, dnc_base[id] + TASK_DONE + off)
#define DNC_STATUS_WRITE(id, val, off)		rl_writel_relaxed(val, dnc_base[id] + STATUS + off)

#define DNC_TASK32_WRITE(id, val, off, exec_id) \
do { \
	rl_writel_relaxed(val, dnc_base[id] + TASK_32B + off); \
} while (0)

#define DNC_TASK32_CONFIG_WRITE(id, val, exec_id)	\
do { \
	rl_writeq_relaxed(val, dnc_base[id] + TASK_32B + TASK_DESC_CFG0); \
} while (0)



static void dnc_apply_task32_change(uint32_t dnc_id)
{
	union dnc_task_trig trig = { 0, };

	trig.apply_cfg = 1;
	DNC_TASK32_WRITE(dnc_id, trig.bits, ADDR_OFFSET_DNC_TASK_TRIG, 0);
}

void evt_dnc_init(uint32_t dnc_id)
{
	dnc_apply_task32_change(dnc_id);
}

uint64_t evt_dnc_get_irq_status(uint32_t dnc_id, void *dnc_done_psg)
{
	union dnc_reg_done_passage *done_psg = (union dnc_reg_done_passage *)dnc_done_psg;
	union irq_info irq_data;
	uint16_t cmd_id;
	uint8_t cmd_type = done_psg->done_rpt1.cmd_type;

	irq_data.exec_id.bits = done_psg->done_rpt0.bits;
	irq_data.hw_id = done_psg->done_rpt1.dnc_id;
	irq_data.cmd_type = cmd_type;
	cmd_id = irq_data.exec_id.cmd_id;

	if (dnc_id == 0) {
		FLOG_DBG(irq_data.exec_id.func_id, "DNC done (cid %d %s)\r\n", cmd_id,
				 cmd_type_string[cmd_type]);
		replay_dnc_notify(irq_data);
	}

	return irq_data.bits;
}

void evt_dnc_register_ops(struct dnc_ops *ops)
{
	ops->init = evt_dnc_init;
	ops->get_irq_status = evt_dnc_get_irq_status;
}
