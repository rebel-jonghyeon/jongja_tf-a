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
#include <interrupt.h>
#include "i2c.h"
#include "rl_errors.h"
#include "pmic_mgr.h"

extern struct dw_apb_i2c_config i2c_config[4];

int i2c_write_polling_o_d(uint32_t id, uint16_t device, uint32_t offset, uint8_t *data, uint8_t len)
{
	struct dw_apb_i2c_config *cfg = &i2c_config[id];

	int cmd_reg, ret;

	if (i2c_get_tar(cfg) != device)
		i2c_set_tar(cfg, device);

	ret = i2c_putready(cfg);
	if (ret)
		return ret;
	i2c_putdata(cfg, offset);

	for (int i = 0; i < len; i++) {
		ret = i2c_tfe_ready(cfg);
		if (ret)
			return ret;

		if (i == len - 1) {
			cmd_reg = data[i] | STOP;
		} else
			cmd_reg = data[i];

		i2c_putdata(cfg, cmd_reg);
	}

	i2c_idle_ready(cfg);

	return RL_OK;
}

int i2c_write_polling_d(uint32_t id, uint16_t device, uint8_t *data, uint8_t len)
{
	struct dw_apb_i2c_config *cfg = &i2c_config[id];

	int cmd_reg, ret;

	if (i2c_get_tar(cfg) != device)
		i2c_set_tar(cfg, device);

	for (int i = 0; i < len; i++) {
		ret = i2c_putready(cfg);
		if (ret)
			return ret;
		cmd_reg = (i == len - 1) ? data[i] | STOP : data[i];
		i2c_putdata(cfg, cmd_reg);
	}

	i2c_idle_ready(cfg);

	return RL_OK;
}

int i2c_read_polling_o_d(uint32_t id, uint16_t device, uint32_t offset, uint8_t *data, uint8_t len)
{
	struct dw_apb_i2c_config *cfg = &i2c_config[id];

	int cmd_reg, ret;

	i2c_disable_interrupt(cfg, RX_FULL_MASK);

	if (i2c_get_tar(cfg) != device)
		i2c_set_tar(cfg, device);

	ret = i2c_probe_device(cfg);
	if (ret)
		return ret;

	ret = i2c_putready(cfg);
	if (ret)
		return ret;

	i2c_putdata(cfg, offset);

	for (int i = 0; i < len; i++) {
		if (i == len - 1)
			cmd_reg = I2C_RX | STOP;
		else
			cmd_reg = I2C_RX;

		i2c_putdata(cfg, cmd_reg);
	}

	for (int i = 0; i < len; i++) {
		ret = i2c_getready(cfg);
		if (ret)
			return ret;
		data[i] = i2c_getdata(cfg);
	}

	i2c_idle_ready(cfg);

	i2c_enable_interrupt(cfg, RX_FULL_MASK);

	return RL_OK;
}

int i2c_read_polling_d(uint32_t id, uint16_t device, uint8_t *data, uint8_t len)
{
	struct dw_apb_i2c_config *cfg = &i2c_config[id];

	int cmd_reg, ret;

	i2c_disable_interrupt(cfg, RX_FULL_MASK);

	if (i2c_get_tar(cfg) != device)
		i2c_set_tar(cfg, device);

	for (int i = 0; i < len; i++) {
		ret = i2c_putready(cfg);
		if (ret)
			return ret;

		cmd_reg = (i == len - 1) ? I2C_RX | STOP : I2C_RX;
		i2c_putdata(cfg, cmd_reg);
	}

	for (int i = 0; i < len; i++) {
		ret = i2c_getready(cfg);
		if (ret)
			return ret;
		data[i] = i2c_getdata(cfg);
	}

	i2c_idle_ready(cfg);

	i2c_enable_interrupt(cfg, RX_FULL_MASK);

	return RL_OK;
}

int i2c_write_int_o_d(uint32_t id, uint16_t device, uint32_t offset, uint8_t *data, uint8_t len)
{
	struct dw_apb_i2c_config *cfg = &i2c_config[id];
	int ret;

	cfg->idx = 0;
	cfg->data = data;
	cfg->len = len;

	if (i2c_get_tar(cfg) != device)
		i2c_set_tar(cfg, device);

	ret = i2c_putready(cfg);
	if (ret)
		return ret;
	i2c_putdata(cfg, offset);

	i2c_enable_interrupt(cfg, TX_EMPTY_MASK);

	ret = i2c_intr_timeout_high(cfg, TFE);
	if (ret)
		return ret;

	i2c_idle_ready(cfg);

	return RL_OK;
}

int i2c_read_int_o_d(uint32_t id, uint16_t device, uint32_t offset, uint8_t *data, uint8_t len)
{
	struct dw_apb_i2c_config *cfg = &i2c_config[id];

	int ret, cmd_reg;

	cfg->idx = 0;
	cfg->data = data;
	cfg->len = len;

	if (i2c_get_tar(cfg) != device)
		i2c_set_tar(cfg, device);

	ret = i2c_putready(cfg);
	if (ret)
		return ret;
	i2c_putdata(cfg, offset);

	for (int i = 0; i < cfg->len; i++) {
		ret = i2c_putready(cfg);
		if (ret)
			return ret;

		cmd_reg = (i == len - 1) ? I2C_RX | STOP : I2C_RX;
		i2c_putdata(cfg, cmd_reg);
	}

	ret = i2c_intr_timeout_low(cfg, RFNE);
	if (ret)
		return ret;

	i2c_idle_ready(cfg);

	return RL_OK;
}
