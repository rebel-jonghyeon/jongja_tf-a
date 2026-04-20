/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include <rebel_h_platform.h>
#include "rl_utils.h"

#define SMMU_PMCG_EVCNTR0               0x22000
#define SMMU_PMCG_EVCNTR(n, stride)     (SMMU_PMCG_EVCNTR0 + (n) * (stride))
#define SMMU_PMCG_EVTYPER0              0x2400
#define SMMU_PMCG_EVTYPER(n)            (SMMU_PMCG_EVTYPER0 + (n) * 4)
#define SMMU_PMCG_SID_SPAN_SHIFT        29
#define SMMU_PMCG_SMR0                  0x2A00
#define SMMU_PMCG_CNTENSET0             0x2C00
#define SMMU_PMCG_CNTENCLR0             0x2C20
#define SMMU_PMCG_INTENSET0             0x2C40
#define SMMU_PMCG_INTENCLR0             0x2C60
#define SMMU_PMCG_OVSCLR0               0x22C80
#define SMMU_PMCG_OVSSET0               0x22CC0
#define SMMU_PMCG_SVR0					0x22600
#define SMMU_PMCG_SVR(n)				(SMMU_PMCG_SVR0 + (n) * 4)
#define SMMU_PMCG_CAPR					0x22D88
#define SMMU_PMCG_CFGR                  0x2E00
#define SMMU_PMCG_CFGR_SID_FILTER_TYPE  RL_BIT(23)
#define SMMU_PMCG_CFGR_MSI              RL_BIT(21)
#define SMMU_PMCG_CFGR_RELOC_CTRS       RL_BIT(20)
#define SMMU_PMCG_CFGR_SIZE             RL_GENMASK(13, 8)
#define SMMU_PMCG_CFGR_NCTR             RL_GENMASK(5, 0)
#define SMMU_PMCG_CR                    0x2E04
#define SMMU_PMCG_CR_ENABLE             RL_BIT(0)
#define SMMU_PMCG_CR_DISABLE            0x0
#define SMMU_PMCG_IIDR                  0x2E08
#define SMMU_PMCG_IIDR_PRODUCTID        RL_GENMASK(31, 20)
#define SMMU_PMCG_IIDR_VARIANT          RL_GENMASK(19, 16)
#define SMMU_PMCG_IIDR_REVISION         RL_GENMASK(15, 12)
#define SMMU_PMCG_IIDR_IMPLEMENTER      RL_GENMASK(11, 0)
#define SMMU_PMCG_CEID0                 0x2E20
#define SMMU_PMCG_CEID1                 0x2E28
#define SMMU_PMCG_IRQ_CTRL              0x2E50
#define SMMU_PMCG_IRQ_CTRL_IRQEN        RL_BIT(0)
#define SMMU_PMCG_IRQ_CTRL_DISABLE		0x0

#define SMMU_PMCG_MAX_COUNTERS 64

#define SMMU_PMU_ENABLE	0x1
#define SMMU_PMU_DISABLE	0x0
#define SMMU_PMCG_ALL_SID	0xFFFFFF
#define SMMU_PMCG_FLT_SID_SPAN	0x1
#define SMMU_PMCG_EVENT_CLEAR	0xFFFFFFFF
#define SMMU_PMCG_CAPTURE		0x1

int smmu_pmu_enable(void);
int smmu_pmu_add_evt(uint32_t evt_id);
void smmu_pmu_reset_all_counters(void);
void smmu_pmu_disable(void);
int smmu_pmu_reset_counter_by_evt(uint32_t evt_id);
int smmu_pmu_capture_counter(uint32_t evt_id);
void smmu_pmu_print_enabled_cnt(void);
int smmu_pmu_del_evt(uint32_t evt_id);
