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

#include <rebel_h_platform.h>
#include <driver.h>
#include "rl_errors.h"
#include "pmic_mgr.h"
#include "i2c.h"
#include "g1505.h"

/*	PMBUS ADDRESS : 0xB0	*/

int g1505_set_page(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, PAGE, &reg_val, 1);
}

int g1505_get_page(uint16_t target_address)
{
	int ret;
	uint8_t value;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, PAGE, &value, 1);
	if (ret)
		return ret;

	return value;
}

int g1505_set_operation(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, OPERATION, &reg_val, 1);
}

int g1505_set_on_off_config(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, ON_OFF_CONFIG, &reg_val, 1);
}

int g1505_get_on_off_config(uint16_t target_address)
{
	int ret;
	uint8_t value;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, ON_OFF_CONFIG, &value, 1);
	if (ret)
		return ret;

	return value;
}

int g1505_clear_fault(uint16_t target_address)
{
	uint8_t cmd = CLEAR_FAULT;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

static int g1505_get_vout_mode(uint16_t target_address)
{
	int ret;
	uint8_t value;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, VOUT_MODE, &value, 1);
	if (ret)
		return ret;

	value &= 0x1F;

	return value;
}

int g1505_set_vout_command(uint16_t target_address, uint32_t vout)
{
	uint8_t reg_val[2];
	uint32_t word;
	uint32_t exponent = g1505_get_vout_mode(target_address);
	uint32_t mantissa = (vout * 1000) / (1 << exponent);

	if (mantissa > 0x7FF)
		mantissa &= 0x7FF;

	word = (exponent << 11) | mantissa;
	reg_val[0] = word & 0xFF;
	reg_val[1] = (word << 8) & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, VOUT_COMMAND, reg_val, 2);
}

int g1505_get_vout_command(uint16_t target_address)
{
	int ret;

	uint8_t reg_val[2];
	uint32_t exponent, mantissa, vout;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, VOUT_COMMAND, reg_val, 1);
	if (ret)
		return ret;

	exponent = (reg_val[1] >> 3) & 0x1F;
	mantissa = reg_val[0] | ((reg_val[1] & 7) << 8);

	vout = mantissa * (1 << exponent) / 1000;

	return vout;
}

int g1505_get_status_word(uint16_t target_address)
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

int g1505_get_status_vout(uint16_t target_address)
{
	int ret;
	uint8_t value;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, STATUS_VOUT, &value, 1);
	if (ret)
		return ret;

	return value;
}

int g1505_get_status_iout(uint16_t target_address)
{
	int ret;
	uint8_t value;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, STATUS_IOUT, &value, 1);
	if (ret)
		return ret;

	return value;
}
