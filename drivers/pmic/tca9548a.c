/*
 * Copyright 2025 Samsung Electronics Co, Ltd. All Rights Reserved.
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

#include <util.h>
#include <rebel_h_platform.h>
#include <stdlib.h>
#include <driver.h>
#include "tca9548a.h"
#include "pmic_mgr.h"
#include "i2c.h"
#include "rl_errors.h"

/* I2C TARGET ADDRESS : 0x70	*/

int i2c_mux_check_channel_state(uint16_t target_address)
{
	int ret;
	uint8_t ch_state;

	ret = i2c_read_polling_d(I2C1_PERI0_ID, target_address, &ch_state, 1);
	if (ret)
		return ret;

	return ch_state;
}

int i2c_mux_enable_channel(uint16_t target_address, uint32_t ch)
{
	int ret;
	uint8_t prev, new_val;
	uint32_t channel = ch;

	prev = i2c_mux_check_channel_state(target_address);
	new_val = prev | (1 << channel);

	ret = i2c_write_polling_d(I2C1_PERI0_ID, target_address, &new_val, 1);
	if (ret)
		return ret;

	return RL_OK;
}

int i2c_mux_disable_channel(uint16_t target_address, uint32_t ch)
{
	int ret;
	uint8_t prev, new_val;
	uint32_t channel = ch;

	prev = i2c_mux_check_channel_state(target_address);
	new_val = prev & ~(1 << channel);

	ret = i2c_write_polling_d(I2C1_PERI0_ID, target_address, &new_val, 1);
	if (ret)
		return ret;

	return RL_OK;
}

