/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */

#pragma once

#include "cmu_ebus_d.h"
#include "cmu_ebus_r.h"
#include "cmu_ebus_u.h"
#include "cmu_nbus_d.h"
#include "cmu_nbus_l.h"
#include "cmu_nbus_u.h"
#include "cmu_pcie.h"
#include "cmu_peri.h"
#include "cmu_rot.h"
#include "cmu_sbus_d.h"
#include "cmu_sbus_l.h"
#include "cmu_sbus_u.h"
#include "cmu_wbus_d.h"
#include "cmu_wbus_u.h"

void cmu_init(uint32_t chiplet_id);
uint64_t get_pll_freq_f0434(volatile void *con0, volatile void *con3);
uint32_t get_div_ratio(volatile void *div);
