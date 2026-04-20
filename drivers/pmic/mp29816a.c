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
#include "mp29816a.h"

/* PMBUS ADDRESS
 * 0x30, 0x31, 0x32, 0x34, 0x36, 0x38, 0x3A
 * 0x30: en2-disable (rail1 16)
 * 0x31: en2-disable (rail1 16)
 * 0x32: en2-disable (rail1 16)
 * 0x34: en1, en2 same (rail1 2, rail2 2)
 * 0x36: en1, en2 same (rail1 2, rail2 2)
 * 0x38: en1, en2 same (rail1 2, rail2 2)
 * 0x3a: en1, en2 same (rail1 2, rail2 2)
 */

int mp29816a_set_page(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, PAGE, &reg_val, 1);
}

int mp29816a_get_page(uint16_t target_address)
{
	int ret;
	uint8_t reg_val;
	uint8_t result;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, PAGE, &reg_val, 1);
	if (ret)
		return ret;

	result = reg_val;
	return result;
}

int mp29816a_set_operation_page(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, OPERATION, &reg_val, 1);
}

int mp29816a_set_on_off_config_page(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, ON_OFF_CONFIG, &reg_val, 1);
}

int mp29816a_clear_fault(uint16_t target_address)
{
	uint8_t cmd = CLEAR_FAULTS;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mp29816a_set_phase(uint16_t target_address, uint32_t value)
{
	uint8_t reg_val[2];

	reg_val[0] = value & 0xFF;
	reg_val[1] = (value >> 8) & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, PHASE, reg_val, 2);
}

int mp29816a_store_user_all(uint16_t target_address)
{
	uint8_t cmd = STORE_USER_ALL;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mp29816a_restore_user_all(uint16_t target_address)
{
	uint8_t cmd = RESTORE_USER_ALL;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mp29816a_store_user_code(uint16_t target_address)
{
	uint8_t cmd = STORE_USER_CODE;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mp29816a_restore_user_code(uint16_t target_address)
{
	uint8_t cmd = RESTORE_USER_CODE;

	return i2c_write_polling_d(I2C0_PERI0_ID, target_address, &cmd, 1);
}

int mp29816a_set_vout_mode(uint16_t target_address, uint8_t value)
{
	uint8_t reg_val = value;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, VOUT_MODE, &reg_val, 1);
}

int mp29816a_set_vout_command(uint16_t target_address, uint32_t value)
{
	uint8_t reg_val[2];

	value = value / MP29816A_VID;
	reg_val[0] = value & 0xFF;
	reg_val[1] = (value >> 8) & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, VOUT_COMMAND, reg_val, 2);
}

int mp29816a_mfr_vout_droop(uint16_t target_address, uint32_t value)
{
	uint8_t reg_val[2];

	reg_val[0] = value & 0xFF;
	reg_val[1] = (value >> 8) & 0xFF;

	return i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, MFR_VOUT_SCALE_LOOP, reg_val, 2);
}

int mp29816a_read_byte_page(uint16_t target_address)
{
	int ret;
	uint8_t reg_val;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, STATUS_BYTE, &reg_val, 1);
	if (ret)
		return ret;

	return reg_val;
}

int mp29816a_read_word_page(uint16_t target_address)
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

int mp29816a_read_vout_pmbus(uint16_t target_address)
{
	int ret;
	uint8_t reg_val[2];
	uint32_t result;

	ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, READ_VOUT_PMBUS, reg_val, 2);
	if (ret)
		return ret;

	result = (reg_val[1] << 8) | reg_val[0];

	return result;
}

int mp29816a_set_vout(uint16_t target_address, uint32_t vout)
{
	int ret;

	ret = mp29816a_set_operation_page(target_address, OP_NORMAL_ON);
	if (ret)
		return ret;

	return mp29816a_set_vout_command(target_address, vout);
}

int mp29816a_get_vout(uint16_t target_address)
{
	uint32_t value;

	value = mp29816a_read_vout_pmbus(target_address) * MP29816A_VID;

	return value;
}

int mp29816a_enable_rail1(uint16_t target_address, uint32_t vout)
{
	int ret;
	uint32_t reg_val;

	ret = mp29816a_set_page(target_address, PAGE0_REG);
	if (ret)
		return ret;

	reg_val = CONF_ACTIVE_HIGH | CONF_REQUIRE_CTRL_PIN | CONF_REQUIRE_CMD | CONF_DEBUG_NOT_USE;
	ret = mp29816a_set_on_off_config_page(target_address, reg_val);
	if (ret)
		return ret;

	reg_val = PHASE_NUM_16 | PHASE_FORCE_16;
	ret = mp29816a_set_phase(target_address, reg_val);
	if (ret)
		return ret;

	ret = mp29816a_set_vout_mode(target_address, VOUT_MODE_VID);
	if (ret)
		return ret;

	ret = mp29816a_mfr_vout_droop(target_address, MFR_VID_LSB_1MV); // LSB : 1mV
	if (ret)
		return ret;

	ret = mp29816a_set_vout(target_address, vout);
	if (ret)
		return ret;

	ret = mp29816a_set_operation_page(target_address, OP_NORMAL_ON);
	if (ret)
		return ret;

	return RL_OK;
}

int mp29816a_disable_rail1(uint16_t target_address)
{
	int ret;
	uint32_t reg_val;

	ret = mp29816a_set_page(target_address, PAGE0_REG);
	if (ret)
		return ret;

	reg_val = CONF_ACTIVE_HIGH | CONF_REQUIRE_CTRL_PIN | CONF_REQUIRE_CMD | CONF_DEBUG_NOT_USE;
	ret = mp29816a_set_on_off_config_page(target_address, reg_val);
	if (ret)
		return ret;

	reg_val = PHASE_NUM_16 | PHASE_FORCE_16;
	ret = mp29816a_set_phase(target_address, reg_val);
	if (ret)
		return ret;

	ret = mp29816a_set_operation_page(target_address, OP_SOFT_OFF);
	if (ret)
		return ret;

	return RL_OK;
}

int mp29816a_enable_rail1_rail2(uint16_t target_address, uint32_t vout)
{
	int ret;
	uint32_t reg_val;

	ret = mp29816a_set_page(target_address, PAGE0_REG);
	if (ret)
		return ret;

	reg_val = CONF_ACTIVE_HIGH | CONF_REQUIRE_CTRL_PIN | CONF_REQUIRE_CMD | CONF_DEBUG_NOT_USE;
	ret = mp29816a_set_on_off_config_page(target_address, reg_val);
	if (ret)
		return ret;

	reg_val = PHASE_NUM_2 | PHASE_FORCE_2;
	ret = mp29816a_set_phase(target_address, reg_val);
	if (ret)
		return ret;

	ret = mp29816a_set_vout_mode(target_address, VOUT_MODE_VID);
	if (ret)
		return ret;

	ret = mp29816a_mfr_vout_droop(target_address, MFR_VID_LSB_1MV); // LSB : 1mV
	if (ret)
		return ret;

	ret = mp29816a_set_vout(target_address, vout);
	if (ret)
		return ret;

	ret = mp29816a_set_operation_page(target_address, OP_NORMAL_ON);
	if (ret)
		return ret;

	ret = mp29816a_set_page(target_address, PAGE1_REG);
	if (ret)
		return ret;

	reg_val = CONF_ACTIVE_HIGH | CONF_REQUIRE_CTRL_PIN | CONF_REQUIRE_CMD | CONF_DEBUG_NOT_USE;
	ret = mp29816a_set_on_off_config_page(target_address, reg_val);
	if (ret)
		return ret;

	reg_val = PHASE_NUM_2 | PHASE_FORCE_2;
	ret = mp29816a_set_phase(target_address, reg_val);
	if (ret)
		return ret;

	ret = mp29816a_set_vout_mode(target_address, VOUT_MODE_VID);
	if (ret)
		return ret;

	ret = mp29816a_mfr_vout_droop(target_address, MFR_VID_LSB_1MV); // LSB : 1mV
	if (ret)
		return ret;

	ret = mp29816a_set_vout(target_address, vout);
	if (ret)
		return ret;

	ret = mp29816a_set_operation_page(target_address, OP_NORMAL_ON);
	if (ret)
		return ret;

	return RL_OK;
}

int mp29816a_disable_rail1_rail2(uint16_t target_address)
{
	int ret;
	uint32_t reg_val;

	ret = mp29816a_set_page(target_address, PAGE0_REG);
	if (ret)
		return ret;

	reg_val = CONF_ACTIVE_HIGH | CONF_REQUIRE_CTRL_PIN | CONF_REQUIRE_CMD | CONF_DEBUG_NOT_USE;
	ret = mp29816a_set_on_off_config_page(target_address, reg_val);
	if (ret)
		return ret;

	reg_val = PHASE_NUM_2 | PHASE_FORCE_2;
	ret = mp29816a_set_phase(target_address, reg_val);
	if (ret)
		return ret;

	ret = mp29816a_set_operation_page(target_address, OP_SOFT_OFF);
	if (ret)
		return ret;

	ret = mp29816a_set_page(target_address, PAGE1_REG);
	if (ret)
		return ret;

	reg_val = CONF_ACTIVE_HIGH | CONF_REQUIRE_CTRL_PIN | CONF_REQUIRE_CMD | CONF_DEBUG_NOT_USE;
	ret = mp29816a_set_on_off_config_page(target_address, reg_val);
	if (ret)
		return ret;

	reg_val = PHASE_NUM_2 | PHASE_FORCE_2;
	ret = mp29816a_set_phase(target_address, reg_val);
	if (ret)
		return ret;

	ret = mp29816a_set_operation_page(target_address, OP_SOFT_OFF);
	if (ret)
		return ret;

	return RL_OK;
}
