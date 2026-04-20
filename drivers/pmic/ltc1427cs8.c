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
#include "rl_errors.h"
#include "pmic_mgr.h"
#include "ltc1427cs8.h"
#include "i2c.h"
#include "tca9548a.h"

/* DEVICE ADDRESS
 * only 0x2C
 * Three ltc1427cs8 devices are controlled by tca8548.
 */

struct ltc_config ltc_list[] = {
	{4, 0x2C, 2700.0f, 18000.0f, (1 << 1), 0},
	{5, 0x2C, 7500.0f, 10000.0f, (1 << 1), 0},
	{6, 0x2C, 5600.0f, 10000.0f, (1 << 1), 0}
};

static void save_register_value(struct ltc_config *cfg, uint8_t cmd, uint8_t data)
{
	cfg->last_cmd_value = cmd;
	cfg->last_data_value = data;
}

static uint32_t vout_to_dac(float vout, float r1, float r2)
{
	float iout = ((VREF_FLOAT * (1.0f + r1 / r2)) - vout) / r1 * 1000;

	if (iout < IOUT_MIN) {
		iout = IOUT_MIN;
	}

	if (iout > IOUT_MAX) {
		iout = IOUT_MAX;
	}

	return (uint32_t)(iout / IOUT_MAX * DAC_MAX_FLOAT);
}

int ltc1427_disable(uint32_t index)
{
	struct ltc_config *cfg = &ltc_list[index];
	int ret;
	uint8_t cmd_byte = cfg->last_cmd_value;
	uint8_t data_byte = cfg->last_data_value;

	if (index >= 3)
		return RL_BADARG;

	cmd_byte |= SHDN_BIT;

	ret = i2c_mux_enable_channel(cfg->ltc_addr, cfg->mux_channel);
	if (ret)
		return ret;

	ret = i2c_write_polling_o_d(I2C1_PERI0_ID, cfg->ltc_addr, (uint32_t)cmd_byte, &data_byte, 1);
	if (ret)
		return ret;

	ret = i2c_mux_disable_channel(cfg->ltc_addr, cfg->mux_channel);
	if (ret)
		return ret;

	save_register_value(cfg, cmd_byte, data_byte);

	return RL_OK;
}

int ltc1427_enable(uint32_t index)
{
	struct ltc_config *cfg = &ltc_list[index];
	int ret;
	uint8_t cmd_byte = cfg->last_cmd_value;
	uint8_t data_byte = cfg->last_data_value;

	if (index >= 3)
		return RL_BADARG;

	cmd_byte &= ~SHDN_BIT;

	ret = i2c_mux_enable_channel(cfg->ltc_addr, cfg->mux_channel);
	if (ret)
		return ret;

	ret = i2c_write_polling_o_d(I2C1_PERI0_ID, cfg->ltc_addr, (uint32_t)cmd_byte, &data_byte, 1);
	if (ret)
		return ret;

	ret = i2c_mux_disable_channel(cfg->ltc_addr, cfg->mux_channel);
	if (ret)
		return ret;

	save_register_value(cfg, cmd_byte, data_byte);

	return RL_OK;
}

int ltc1427_set_vout(uint32_t index, uint32_t target_vout)
{
	struct ltc_config *cfg = &ltc_list[index];
	int ret;
	uint32_t dac_val = vout_to_dac((float)target_vout, cfg->r1_ohm, cfg->r2_ohm);
	uint8_t cmd_byte  = (dac_val >> DAC_SHIFT_HIGH) & DAC_HIGH_MASK;
	uint8_t data_byte = dac_val & DAC_LOW_MASK;

	if (index >= 3)
		return RL_BADARG;

	ret = i2c_mux_enable_channel(cfg->ltc_addr, cfg->mux_channel);
	if (ret)
		return ret;

	ret = i2c_write_polling_o_d(I2C1_PERI0_ID, cfg->ltc_addr, (uint32_t)cmd_byte, &data_byte, 1);
	if (ret)
		return ret;

	ret = i2c_mux_disable_channel(cfg->ltc_addr, cfg->mux_channel);
	if (ret)
		return ret;

	save_register_value(cfg, cmd_byte, data_byte);

	return RL_OK;
}
