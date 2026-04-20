/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2024 [Rebellions Inc.], All Rights Reserved.
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

#include <stdint.h>
#include "system_api.h"
#include "gic.h"
#include "hal/rdsn_if.h"
#include "hal/hw_spec.h"
#include "g_rdsn_head.h"
#include "g_sys_addrmap.h"
#include "hal/interrupt.h"
#include "hal/hw_spec.h"
#include "rl_errors.h"
#include "rl_utils.h"
#include "rbln/log.h"

static const uint64_t rdsn_cfg_base[HW_SPEC_DC_COUNT] = {
	DCL0_MGLUE_CFG_BASE,
#ifndef DCL_SINGLE
	DCL1_MGLUE_CFG_BASE,
#endif
};

static void __iomem *base[HW_SPEC_DC_COUNT];

#define RDSN_READ(id, offset)		rl_readl_relaxed(base[id] + offset)
#define RDSN_WRITE(id, val, offset)	rl_writel_relaxed(val, base[id] + offset)

#define RDSN_TIMEOUT_US					1000
#define RDSN_STATUS0_ALL_PREPARED       0x000F000F

static void rdsn_adjust_base(uint32_t cl_id)
{
	RLOG_DBG("adjust rdsn address clid: %d\r\n", cl_id);

	for (int i = 0; i < HW_SPEC_DC_COUNT; i++)
		base[i] = (void __iomem *)(cl_base[cl_id] + rdsn_cfg_base[i]);
//for debug
//	for (int i = 0; i < HW_SPEC_DC_COUNT; i++)
//		printf("=>> %lx\r\n", base[i]);
}

static bool rdsn_is_prepared(int dc_id)
{
	union rdsn_head_status0 status0 = { 0, };
	uint32_t timeout_cnt = 0;

	do {
		status0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_STATUS0);
		if ((status0.bits & RDSN_STATUS0_ALL_PREPARED) == RDSN_STATUS0_ALL_PREPARED) {
			RLOG_DBG("RDSN(dcluster%d) is prepared\r\n", dc_id);

			return true;
		}

		udelay(1);
	} while (timeout_cnt++ < RDSN_TIMEOUT_US);

	RLOG_ERR("%s: dcluster:%d rdsn init timeout: status(%#x)\r\n", __func__, dc_id, status0.bits);
	printf("%s: dcluster:%d rdsn init timeout: status(%#x)\r\n", __func__, dc_id, status0.bits);

	return false;
}

static int rdsn_sanity_check(int dc_id)
{
	union rdsn_head_ctrl1 ctrl1	=	{0, };
	union rdsn_head_ctrl0 ctrl0	=	{0, };
	union rdsn_head_te0_rpt0 te0_rpt0	=	{0, };
	union rdsn_head_te3_rpt0 te3_rpt0	=	{0, };
	uint32_t timeout_cnt = 0;

	ctrl1.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_CTRL1);
	// for test
//	ctrl1.dtest_pat_even	= 0x1;
//	ctrl1.dtest_pat_odd	= 0x0;
	ctrl1.dtest_short = 1;
	RDSN_WRITE(dc_id, ctrl1.bits, ADDR_OFFSET_RDSN_HEAD_CTRL1);

	ctrl0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_CTRL0);
	ctrl0.trig_dtest0 = 1;
	ctrl0.trig_dtest3 = 1;
	RDSN_WRITE(dc_id, ctrl0.bits, ADDR_OFFSET_RDSN_HEAD_CTRL0);

	do {
		te0_rpt0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_TE0_RPT0);
		te3_rpt0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_TE3_RPT0);
		if (te0_rpt0.valid && te0_rpt0.pass && te3_rpt0.valid && te3_rpt0.pass) {
			RLOG_DBG("RDSN(dcluster%d) sanity check is passed\r\n", dc_id);
			return RL_OK;
		}

		udelay(1);
	} while (timeout_cnt++ < RDSN_TIMEOUT_US);

	RLOG_ERR("%s: dcluter%d, te0_rpt0(valid %d, pass %d), te3_rpt0(valid %d, pass %d)\r\n",
			 __func__, dc_id, te0_rpt0.valid, te0_rpt0.pass, te3_rpt0.valid, te3_rpt0.pass);
	printf("\r\n%s() dcluster%d\r\n", __func__, dc_id);
	printf("%-8s | %-8s | %-8s | %-8s\r\n", "Report", "TimeOut", "Valid", "Pass");
	printf("%-8s | %-8d | %-8d | %-8d\r\n", "TE0_RPT0",
		te0_rpt0.timeout, te0_rpt0.valid, te0_rpt0.pass);
	printf("%-8s | %-8d | %-8d | %-8d\r\n", "TE3_RPT0",
		te3_rpt0.timeout, te3_rpt0.valid, te3_rpt0.pass);

	return RL_TIMEOUT;
}

static int rdsn_set_ids(int dc_id, int chiplet_id)
{
	union rdsn_head_ctrl1 ctrl1;
	union rdsn_head_ctrl0 ctrl0;
	union rdsn_head_status0 status0;
	uint32_t timeout_cnt = 0;

	ctrl1.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_CTRL1);
	ctrl1.dclst_id = dc_id;
	ctrl1.chiplet_id = chiplet_id;
	RDSN_WRITE(dc_id, ctrl1.bits, ADDR_OFFSET_RDSN_HEAD_CTRL1);

	ctrl0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_CTRL0);
	ctrl0.cfg_chiplet_id_trig = 1;
	RDSN_WRITE(dc_id, ctrl0.bits, ADDR_OFFSET_RDSN_HEAD_CTRL0);

	do {
		status0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_STATUS0);
		if ((status0.bits & RDSN_STATUS0_ALL_PREPARED) == RDSN_STATUS0_ALL_PREPARED) {
			RLOG_DBG("dcluster%d chiplet%d are set to RDSN successfully\r\n", dc_id, chiplet_id);

			return RL_OK;
		}

		udelay(1);
	} while (timeout_cnt++ < RDSN_TIMEOUT_US);

	RLOG_ERR("%s: failed to set dcluster%d chiplet%d\r\n", __func__, dc_id, chiplet_id);
	printf("%s: failed to set dcluster%d chiplet%d\r\n", __func__, dc_id, chiplet_id);

	return RL_TIMEOUT;
}

#ifdef RDSN_ENABLED
int rdsn_init(uint32_t cl_id)
{
	int ret;

	rdsn_adjust_base(cl_id);

	for (int i = 0; i < HW_SPEC_DC_COUNT; i++) {
		/* check rdsn initialization status */
		if (!rdsn_is_prepared(i)) {
			RLOG_ERR("RDSN%d is not prepared\r\n", i);
			return RL_TIMEOUT;
		}
		ret = rdsn_sanity_check(i);
		if (ret)
			return ret;
		RLOG_DBG("RDSN%d set chiplet_id:%d\r\n", i, cl_id);
		ret = rdsn_set_ids(i, cl_id);
		if (ret)
			return ret;
	}

	return RL_OK;
}
#else
int rdsn_init(uint32_t cl_id) { return RL_OK; }
#endif /* RDSN_ENABLED */

int rdsn_custom_config(uint32_t cl_id)
{
	union rdsn_head_ctrl1 ctrl1 = {0, };
	uint32_t reg = 0;
	uint32_t timeout_cnt = 0;

	rdsn_adjust_base(cl_id);

	for (int i = 0; i < HW_SPEC_DC_COUNT; i++) {
		ctrl1.bits = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_CTRL1);
		ctrl1.custom_config = 1;
		RDSN_WRITE(i, ctrl1.bits, ADDR_OFFSET_RDSN_HEAD_CTRL1);

		RLOG_DBG("RDSN%d set chiplet_id:%d\r\n", i, cl_id);

		for (int col = 0; col < 4; col++) {
			for (int row = 0; row < 4; row++) {
				/*
				 * [19:16]Address of Router's RegMap,
				 * [15:12]D/R/C Channel, [11:4]RTID, [0]mode:configuration
				 * 0x2, even packet
				 */
				reg = 0x1 | row<<4 | col<<8 | 0x7<<12 | 0x2<<16;
				RDSN_WRITE(i, reg, ADDR_OFFSET_RDSN_HEAD_CMD00);
				/*
				 * odd packet
				 */
				reg = 0x1f00;	//enable arbiter[12:8]
				RDSN_WRITE(i, reg, ADDR_OFFSET_RDSN_HEAD_CMD00);

				/*
				 * 0x6, even packet
				 */
				reg = 0x1 | row<<4 | col<<8 | 0x7<<12 | 0x6<<16;
				RDSN_WRITE(i, reg, ADDR_OFFSET_RDSN_HEAD_CMD00);

				/*
				 * odd packet
				 */
				reg = 0x1 | 0x1<<8;	// [27:8]threshold for starvation report, [0]starvation en
				RDSN_WRITE(i, reg, ADDR_OFFSET_RDSN_HEAD_CMD00);
			}
		}

		do {
			reg = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_STATUS2);
			timeout_cnt++;
			if (timeout_cnt > RDSN_TIMEOUT_US) {
				printf("[RDSN] %s timeout\r\n", __func__);
				break;
			}

		} while (reg != 0x1100);

		ctrl1.custom_config = 0;
		RDSN_WRITE(i, ctrl1.bits, ADDR_OFFSET_RDSN_HEAD_CTRL1);

		if (!rdsn_is_prepared(i)) {
			RLOG_ERR("RDSN%d is not prepared\r\n", i);
			return RL_TIMEOUT;
		}
	}

	return RL_OK;
}

void rdsn_interrupt_status(uint32_t cl_id)
{
	uint32_t reg = 0;

	rdsn_adjust_base(cl_id);

	for (int i = 0; i < HW_SPEC_DC_COUNT; i++) {
		reg = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_INTR_VEC0);
		printf("\r\n%-15s : 0x%08x\r\n", "intr_vec0", reg);
		reg = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_INTR_VEC1);
		printf("%-15s : 0x%08x\r\n", "intr_vec1", reg);
		reg = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_INTR_VEC2);
		printf("%-15s : 0x%08x\r\n", "intr_vec2", reg);
		reg = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_INTR_VEC3);
		printf("%-15s : 0x%08x\r\n", "intr_vec3", reg);
	}
}

static void mglue_error_handler(void *data)
{
	union rdsn_head_ctrl0 ctrl0 = {0, };
	uint32_t reg = 0;

	for (int i = 0; i < HW_SPEC_DC_COUNT; i++) {
		reg = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_INTR_VEC0);
		RLOG_DBG("\r\n%-15s : 0x%08x\r\n", "intr_vec0", reg);
		printf("\r\n%-15s : 0x%08x\r\n", "intr_vec0", reg);

		reg = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_INTR_VEC1);
		RLOG_DBG("%-15s : 0x%08x\r\n", "intr_vec1", reg);
		printf("%-15s : 0x%08x\r\n", "intr_vec1", reg);

		reg = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_INTR_VEC2);
		RLOG_DBG("%-15s : 0x%08x\r\n", "intr_vec2", reg);
		printf("%-15s : 0x%08x\r\n", "intr_vec2", reg);

		reg = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_INTR_VEC3);
		RLOG_DBG("%-15s : 0x%08x\r\n", "intr_vec3", reg);
		printf("%-15s : 0x%08x\r\n", "intr_vec3", reg);

		printf("mglue error handler!!!\r\n");

		ctrl0.bits = RDSN_READ(i, ADDR_OFFSET_RDSN_HEAD_CTRL0);
		ctrl0.clear_rdsn = 1;
		ctrl0.clear_head = 1;
		RDSN_WRITE(i, ctrl0.bits, ADDR_OFFSET_RDSN_HEAD_CTRL0);
	}
}

void mglue_interrupt_register(uint32_t cl_id)
{
	gic_irq_connect(INT_ID_MGLUE_EXCEPTION, mglue_error_handler, 0);
	gic_irq_enable_dedicated_core(0, INT_ID_MGLUE_EXCEPTION);
}

int rdsn_test_mode_trigger(void)
{
	union rdsn_head_ctrl1 ctrl1	= {0, };
	union rdsn_head_ctrl0 ctrl0	= {0, };
	uint32_t dc_id = 0;

	for (dc_id = 0; dc_id < HW_SPEC_DC_COUNT; dc_id++) {
		if (!rdsn_is_prepared(dc_id)) {
			RLOG_ERR("RDSN%d is not prepared\r\n", dc_id);
			return RL_TIMEOUT;
		}
		ctrl1.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_CTRL1);
		ctrl1.dtest_short = 0;		// full mesh test
		RDSN_WRITE(dc_id, ctrl1.bits, ADDR_OFFSET_RDSN_HEAD_CTRL1);
		dsb();

		ctrl0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_CTRL0);
		ctrl0.trig_dtest0 = 1;
		ctrl0.trig_dtest3 = 1;
		RDSN_WRITE(dc_id, ctrl0.bits, ADDR_OFFSET_RDSN_HEAD_CTRL0);
	}

	return RL_OK;
}

int rdsn_test_mode_check(void)
{
	union rdsn_head_te0_rpt0 te0_rpt0 =	{0, };
	union rdsn_head_te3_rpt0 te3_rpt0 =	{0, };
	uint32_t dc_id = 0;
	uint32_t timeout_cnt = 0;

	do {
		int done_cnt = 0;

		for (dc_id = 0; dc_id < HW_SPEC_DC_COUNT; dc_id++) {
			te0_rpt0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_TE0_RPT0);
			te3_rpt0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_TE3_RPT0);
			if (te0_rpt0.valid && te0_rpt0.pass && te3_rpt0.valid && te3_rpt0.pass)
				done_cnt++;
		}

		if (done_cnt == HW_SPEC_DC_COUNT)
			return RL_OK;

		udelay(1);
	} while (timeout_cnt++ < RDSN_TIMEOUT_US);

	for (dc_id = 0; dc_id < HW_SPEC_DC_COUNT; dc_id++) {
		te0_rpt0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_TE0_RPT0);
		te3_rpt0.bits = RDSN_READ(dc_id, ADDR_OFFSET_RDSN_HEAD_TE3_RPT0);

		printf("\r\n%s() dcluster%d\r\n", __func__, dc_id);
		printf("%-8s | %-8s | %-8s | %-8s\r\n", "Report", "TimeOut", "Valid", "Pass");
		printf("%-8s | %-8d | %-8d | %-8d\r\n", "TE0_RPT0",
			te0_rpt0.timeout, te0_rpt0.valid, te0_rpt0.pass);
		printf("%-8s | %-8d | %-8d | %-8d\r\n", "TE3_RPT0",
			te3_rpt0.timeout, te3_rpt0.valid, te3_rpt0.pass);
	}
	return RL_TIMEOUT;
}
