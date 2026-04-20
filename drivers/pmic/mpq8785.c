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
#include "i2c.h"
#include "pmic_mgr.h"
#include "mpq8785.h"

/* PMBUS ADDRESS
 * 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x4E, 0x50, 0x51, 0x60, 0x61, 0x62, 0x63
 */

int mpq8785_set_page(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, OPERATION, &reg_val, 1);
}

int mpq8785_set_operation(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, OPERATION, &reg_val, 1);
}

int mpq8785_set_on_off_config(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, ON_OFF_CONFIG, &reg_val, 1);
}

int mpq8785_clear_fault(uint16_t target_address)
{
	uint8_t cmd = CLEAR_FAULT;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mpq8785_store_all(uint16_t target_address)
{
	uint8_t cmd = STORE_ALL;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mpq8785_restore_all(uint16_t target_address)
{
	uint8_t cmd = RESTORE_ALL;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mpq8785_set_vout_mode(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, VOUT_MODE, &reg_val, 1);
}

int mpq8785_read_vout_mode(uint16_t target_address)
{
	int ret;
	uint8_t value;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, VOUT_MODE, &value, 1);
	if (ret)
		return ret;

	return value;
}

int mpq8785_read_vout(uint16_t target_address)
{
	int ret;
	uint32_t vout_mode_reg, result;
	float lsb;
	uint8_t reg_val[2];

	vout_mode_reg = mpq8785_read_vout_mode(target_address);

	if ((vout_mode_reg & VOUT_MODE_SEL_MASK) == 0) {
		lsb = 1.953125f;
	} else {
		lsb = 1.5625f;
	}

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, READ_VOUT, reg_val, 2);
	if (ret)
		return ret;

	result = (reg_val[1] << 8) | reg_val[0];
	result = (uint32_t)(lsb * (float)result);

	return result;
}

int mpq8785_set_vout_command(uint16_t target_address, uint32_t vout)
{
	uint8_t vout_cmd_reg[2];
	uint32_t vout_cmd, vout_mode_reg;
	float lsb;

	vout_mode_reg = mpq8785_read_vout_mode(target_address);

	if ((vout_mode_reg & VOUT_MODE_SEL_MASK) == 0) {
		lsb = 1.953125f;
	} else {
		lsb = 1.5625f;
	}

	vout_cmd = (uint32_t)((float)vout / lsb);
	vout_cmd_reg[0] = vout_cmd & 0xFF;
	vout_cmd_reg[1] = (vout_cmd >> 8) & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, VOUT_COMMAND, vout_cmd_reg, 2);
}

int mpq8785_set_vin_on(uint16_t target_address, uint8_t vin)
{
	uint8_t reg_val = vin / 200;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, VIN_ON, &reg_val, 2);
}

int mpq8785_set_vin_off(uint16_t target_address, uint8_t vin)
{
	uint8_t reg_val = vin / 200;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, VIN_OFF, &reg_val, 2);
}

int mpq8785_read_word(uint16_t target_address)
{
	int ret;
	uint8_t reg_val[2];
	uint32_t result;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, STATUS_WORD, reg_val, 2);
	if (ret)
		return ret;

	result = (reg_val[1] << 8) | reg_val[0];

	return result;
}

int mpq8785_read_status_vout(uint16_t target_address)
{
	int ret;
	uint8_t value;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, STATUS_VOUT, &value, 1);
	if (ret)
		return ret;

	return value;
}

int mpq8785_set_vout(uint16_t target_address, uint32_t vout)
{
	return mpq8785_set_vout_command(target_address, vout);
}

int mpq8785_get_vout(uint16_t target_address)
{
	return mpq8785_read_vout(target_address);
}

int mpq8785_enable(uint16_t target_address, uint32_t vout)
{
	int ret;
	uint32_t reg_val;

	ret = mpq8785_set_page(target_address, PAGE_OPERATE_MODE);
	if (ret)
		return ret;

	ret = mpq8785_set_on_off_config(target_address, CONF_CTRL_ACTIVE_HIGH | CONF_TURN_ON_BUS_PIN);
	if (ret)
		return ret;

	ret = mpq8785_set_vout_mode(target_address, VOUT_MODE_SEL_VID);
	if (ret)
		return ret;

	ret = mpq8785_set_vout(target_address, vout);
	if (ret)
		return ret;

	reg_val = OP_OUTPUT_ON | OP_SOFT_SHUTDOWN | OP_VOUT_CMD_DATA;
	ret = mpq8785_set_operation(target_address, reg_val);
	if (ret)
		return ret;

	return RL_OK;
}

int mpq8785_disable(uint16_t target_address)
{
	int ret;
	uint32_t reg_val;

	ret = mpq8785_set_page(target_address, PAGE_OPERATE_MODE);
	if (ret)
		return ret;

	ret = mpq8785_set_on_off_config(target_address, CONF_CTRL_ACTIVE_HIGH | CONF_TURN_ON_BUS_PIN);
	if (ret)
		return ret;

	reg_val = OP_OUTPUT_OFF | OP_SOFT_SHUTDOWN | OP_VOUT_CMD_DATA;
	ret = mpq8785_set_operation(target_address, reg_val);
	if (ret)
		return ret;

	return RL_OK;
}
