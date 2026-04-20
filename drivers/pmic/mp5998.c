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
#include "i2c.h"
#include "mp5998.h"

/* PMBUS ADDRESS
 * 0x56, 0x57, 0x58
 */

int mp5998_set_enable(uint16_t target_address)
{
	uint8_t reg_val = MOSFET_ENABLE;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, OPERATION, &reg_val, 1);
}

int mp5998_set_disable(uint16_t target_address)
{
	uint8_t reg_val = MOSFET_DISABLE;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, OPERATION, &reg_val, 1);
}

int mp5998_clear_fault(uint16_t target_address)
{
	uint8_t cmd = CLEAR_FAULT;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mp5998_store_all(uint16_t target_address)
{
	uint8_t cmd = STORE_ALL;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mp5998_restore_all(uint16_t target_address)
{
	uint8_t cmd = RESTORE_ALL;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mp5998_set_vin_on(uint16_t target_address, float vin)
{
	uint32_t reg_val = (uint32_t)(vin * 64.0f);
	uint8_t data[2];

	data[0] = reg_val & 0xFF;
	data[1] = (reg_val >> 8) & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, VIN_ON, data, 2);
}

int mp5998_set_vin_off(uint16_t target_address, float vin)
{
	uint32_t reg_val = (uint32_t)(vin * 64.0f);
	uint8_t data[2];

	data[0] = reg_val & 0xFF;
	data[1] = (reg_val >> 8) & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, VIN_OFF, data, 2);
}

int mp5998_set_power_good_on(uint16_t target_address, float pg_v)
{
	uint32_t reg_val = (uint32_t)(pg_v * 64.0f);
	uint8_t data[2];

	data[0] = reg_val & 0xFF;
	data[1] = (reg_val >> 8) & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, POWER_GOOD_ON, data, 2);
}

int mp5998_set_power_good_off(uint16_t target_address, float pg_v)
{
	uint32_t reg_val = (uint32_t)(pg_v * 64.0f);
	uint8_t data[2];

	data[0] = reg_val & 0xFF;
	data[1] = (reg_val >> 8) & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, POWER_GOOD_OFF, data, 2);
}

int mp5998_set_ton_delay(uint16_t target_address, float delay)
{
	uint32_t reg_val = (uint8_t)(delay * 10.0f);
	uint8_t data[2];

	data[0] = reg_val & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, TON_DELAY, data, 2);
}

int mp5998_set_toff_delay(uint16_t target_address, float delay)
{
	uint32_t reg_val = (uint8_t)(delay * 10.0f);
	uint8_t data[2];

	data[0] = reg_val & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, TOFF_DELAY, data, 2);
}

int mp5998_read_status_byte(uint16_t target_address)
{
	int ret;
	uint8_t reg_val;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, STATUS_BYTE, &reg_val, 1);
	if (ret)
		return ret;

	return reg_val;
}

int mp5998_read_status_word(uint16_t target_address)
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

int mp5998_read_status_cml(uint16_t target_address)
{
	int ret;
	uint8_t reg_val;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, STATUS_CML, &reg_val, 1);
	if (ret)
		return ret;

	return reg_val;
}

float mp5998_read_vout(uint16_t target_address)
{
	int ret;
	uint8_t reg_val[2];
	float vout;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, READ_VOUT, reg_val, 2);
	if (ret)
		return ret;

	vout = ((float)((reg_val[1] << 8) | reg_val[0])) / 64.0f;

	return vout;
}

float mp5998_read_iout(uint16_t target_address)
{
	int ret;
	uint8_t reg_val[2];
	float iout;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, READ_IOUT, reg_val, 2);
	if (ret)
		return ret;

	iout = ((float)((reg_val[1] << 8) | reg_val[0])) / 62.5f;

	return iout;
}
