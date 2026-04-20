/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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
#include <stdint.h>
#include "nor.h"
#include <rebel_h_platform.h>
#include "../psci/psci.h"
#include <rebel_h_sip.h>

int read_flash(uint32_t offset, void *buffer, uint32_t size)
{
	struct arm_smccc_res res;

	arm_smccc_smc(REBEL_H_SMC_FLASH_READ,
				  offset, (unsigned long)buffer, size, 0,
				  0, 0, 0,
				  &res);
	return res.x0;
}

int write_flash(uint32_t offset, void *data, uint32_t size)
{
	struct arm_smccc_res res;

	arm_smccc_smc(REBEL_H_SMC_FLASH_WRITE,
				  offset, (unsigned long)data, size, 0,
				  0, 0, 0,
				  &res);
	return res.x0;
}

int erase_flash(uint32_t offset, uint32_t size)
{
	struct arm_smccc_res res;

	arm_smccc_smc(REBEL_H_SMC_FLASH_ERASE,
				  offset, size, 0, 0,
				  0, 0, 0,
				  &res);
	return res.x0;
}
