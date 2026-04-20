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

#include <stdio.h>
#include "gic.h"
#include "hal/interrupt.h"
#include "hal/tbu_wrapper.h"
#include "hal/hw_spec.h"
#include "autogen/g_sys_addrmap.h"
#include "rbln/log.h"
#include "rbln/rebel.h"
#include "rbln/abort.h"
#include "rl_utils.h"

static uint64_t base;

#define	EBUS_D_SYSREG_SMMU_ETC			(base + EBUS_D_SYSREG_BASE + EBUS_D_SYSREG_SMMU_ETC_OFF)
#define	EBUS_R_SYSREG_SMMU_ETC			(base + EBUS_R_SYSREG_BASE + EBUS_R_SYSREG_SMMU_ETC_OFF)
#define	EBUS_U_SYSREG_SMMU_ETC			(base + EBUS_U_SYSREG_BASE + EBUS_U_SYSREG_SMMU_ETC_OFF)
#define	NBUS_D_SYSREG_SMMU_ETC			(base + NBUS_D_SYSREG_BASE + NBUS_D_SYSREG_SMMU_ETC_OFF)
#define	NBUS_L_SYSREG_SMMU_ETC			(base + NBUS_L_SYSREG_BASE + NBUS_L_SYSREG_SMMU_ETC_OFF)
#define	WBUS_D_TBU_IF_EN				(base + WBUS_D_SYSREG_BASE + WBUS_D_TBU_IF_EN_OFF)
#define	WBUS_D_TBU_ERR_IRPT_EN			(base + WBUS_D_SYSREG_BASE + WBUS_D_TBU_ERR_IRPT_EN_OFF)
#define	WBUS_U_TBU_IF_EN				(base + WBUS_U_SYSREG_BASE + WBUS_U_TBU_IF_EN_OFF)
#define	WBUS_U_TBU_ERR_IRPT_EN			(base + WBUS_U_SYSREG_BASE + WBUS_U_TBU_ERR_IRPT_EN_OFF)

#define BUS_WRITE(val, reg)				rl_writel_relaxed(val, (void *)(reg))

static void adjust_base(uint32_t cl_id)
{
	base = cl_base[cl_id];
}

void tbu_wrapper_irq_hdl(void *idx)
{
	RLOG_DBG("Interrupt(%p) was injected. This interrupt should not occur.", idx);
	rl_abort_event(ERR_UNKNOWN);
}

void tbu_wrapper_irq_deinit(void)
{
	gic_irq_disable(TBU_DGLUE_CL0_CH0_ERR_IRPT);
	gic_irq_disable(TBU_DGLUE_CL0_CH1_ERR_IRPT);
	gic_irq_disable(TBU_DGLUE_CL0_CH2_ERR_IRPT);
	gic_irq_disable(TBU_DGLUE_CL0_CH3_ERR_IRPT);
	gic_irq_disable(TBU_DGLUE_CL1_CH0_ERR_IRPT);
	gic_irq_disable(TBU_DGLUE_CL1_CH1_ERR_IRPT);
	gic_irq_disable(TBU_DGLUE_CL1_CH2_ERR_IRPT);
	gic_irq_disable(TBU_DGLUE_CL1_CH3_ERR_IRPT);
	gic_irq_disable(TBU_RBDMA_0_ERR_IRPT);
	gic_irq_disable(TBU_RBDMA_1_ERR_IRPT);
	gic_irq_disable(TBU_RBDMA_2_ERR_IRPT);
	gic_irq_disable(TBU_RBDMA_3_ERR_IRPT);
	gic_irq_disable(TBU_RBDMA_4_ERR_IRPT);
	gic_irq_disable(TBU_RBDMA_5_ERR_IRPT);
	gic_irq_disable(TBU_RBDMA_6_ERR_IRPT);
	gic_irq_disable(TBU_RBDMA_7_ERR_IRPT);
}

void tbu_wrapper_irq_init(void)
{
	gic_irq_connect(TBU_DGLUE_CL0_CH0_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_DGLUE_CL0_CH1_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_DGLUE_CL0_CH2_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_DGLUE_CL0_CH3_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_DGLUE_CL1_CH0_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_DGLUE_CL1_CH1_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_DGLUE_CL1_CH2_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_DGLUE_CL1_CH3_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_RBDMA_0_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_RBDMA_1_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_RBDMA_2_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_RBDMA_3_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_RBDMA_4_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_RBDMA_5_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_RBDMA_6_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);
	gic_irq_connect(TBU_RBDMA_7_ERR_IRPT, tbu_wrapper_irq_hdl, NULL);

	gic_irq_enable_dedicated_core(0, TBU_DGLUE_CL0_CH0_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_DGLUE_CL0_CH1_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_DGLUE_CL0_CH2_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_DGLUE_CL0_CH3_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_DGLUE_CL1_CH0_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_DGLUE_CL1_CH1_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_DGLUE_CL1_CH2_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_DGLUE_CL1_CH3_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_RBDMA_0_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_RBDMA_1_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_RBDMA_2_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_RBDMA_3_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_RBDMA_4_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_RBDMA_5_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_RBDMA_6_ERR_IRPT);
	gic_irq_enable_dedicated_core(0, TBU_RBDMA_7_ERR_IRPT);
}

void tbu_wrapper_disable(void)
{
	BUS_WRITE(0, EBUS_D_SYSREG_SMMU_ETC);
	BUS_WRITE(0, EBUS_R_SYSREG_SMMU_ETC);
	BUS_WRITE(0, EBUS_U_SYSREG_SMMU_ETC);
	BUS_WRITE(0, NBUS_D_SYSREG_SMMU_ETC);
	BUS_WRITE(0, NBUS_L_SYSREG_SMMU_ETC);
	BUS_WRITE(0, WBUS_D_TBU_IF_EN);
	BUS_WRITE(0, WBUS_D_TBU_ERR_IRPT_EN);
	BUS_WRITE(0, WBUS_U_TBU_IF_EN);
	BUS_WRITE(0, WBUS_U_TBU_ERR_IRPT_EN);
}

void tbu_wrapper_enable(void)
{
	uint32_t val;

	val = EBUS_D_ERR_IRPT_EN_BIT | EBUS_D_TBU_IF_EN_BIT;
	BUS_WRITE(val, EBUS_D_SYSREG_SMMU_ETC);

	val = EBUS_R_ERR_IRPT_EN_CL1_BIT | EBUS_R_TBU_IF_EN_CL1_BIT |
			EBUS_R_ERR_IRPT_EN_CL0_BIT | EBUS_R_TBU_IF_EN_CL0_BIT;
	BUS_WRITE(val, EBUS_R_SYSREG_SMMU_ETC);

	val = EBUS_U_ERR_IRPT_EN_BIT | EBUS_U_TBU_IF_EN_BIT;
	BUS_WRITE(val, EBUS_U_SYSREG_SMMU_ETC);

	val = NBUS_D_ERR_IRPT_EN_RBDMA_7_BIT | NBUS_D_ERR_IRPT_EN_RBDMA_6_BIT |
			NBUS_D_ERR_IRPT_EN_RBDMA_5_BIT | NBUS_D_ERR_IRPT_EN_RBDMA_4_BIT |
			NBUS_D_TBU_IF_EN_RBDMA_7_BIT | NBUS_D_TBU_IF_EN_RBDMA_6_BIT |
			NBUS_D_TBU_IF_EN_RBDMA_5_BIT | NBUS_D_TBU_IF_EN_RBDMA_4_BIT;
	BUS_WRITE(val, NBUS_D_SYSREG_SMMU_ETC);

	val = NBUS_L_ERR_IRPT_EN_RBDMA_3_BIT | NBUS_L_ERR_IRPT_EN_RBDMA_2_BIT |
			NBUS_L_ERR_IRPT_EN_RBDMA_1_BIT | NBUS_L_ERR_IRPT_EN_RBDMA_0_BIT |
			NBUS_L_TBU_IF_EN_RBDMA_3_BIT | NBUS_L_TBU_IF_EN_RBDMA_2_BIT |
			NBUS_L_TBU_IF_EN_RBDMA_1_BIT | NBUS_L_TBU_IF_EN_RBDMA_0_BIT;
	BUS_WRITE(val, NBUS_L_SYSREG_SMMU_ETC);

	val = WBUS_D_TBU_I_TBU_IF_EN_BIT;
	BUS_WRITE(val, WBUS_D_TBU_IF_EN);

	val = WBUS_D_TBU_I_ERR_IRPT_EN_BIT;
	BUS_WRITE(val, WBUS_D_TBU_ERR_IRPT_EN);

	val = WBUS_U_TBU_I_TBU_IF_EN_BIT;
	BUS_WRITE(val, WBUS_U_TBU_IF_EN);

	val = WBUS_U_TBU_I_ERR_IRPT_EN_BIT;
	BUS_WRITE(val, WBUS_U_TBU_ERR_IRPT_EN);
}

int tbu_wrapper_deinit(uint32_t cl_id)
{
	adjust_base(cl_id);

	tbu_wrapper_disable();
	tbu_wrapper_irq_deinit();

	return 0;
}

int tbu_wrapper_init(uint32_t cl_id)
{
	adjust_base(cl_id);

	tbu_wrapper_irq_init();
	tbu_wrapper_enable();

	return 0;
}
