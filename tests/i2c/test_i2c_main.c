/* Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 * PROPRIETARY/CONFIDENTIAL
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it
 * only in accordance with the terms of the license agreement you entered
 * into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NON-INFRINGEMENT.
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT
 * OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include "test_common.h"
#include "i2c.h"
#include "rl_errors.h"
#include "cpu.h"

#define EEPROM_TARGET_ADDR		0x50
#define LB_TARGET_ADDR	0x20

extern struct dw_apb_i2c_config i2c_config[4];

uint8_t test_main_i2c(int argc, char *argv[])
{
	struct dw_apb_i2c_config *cfg_0 = &i2c_config[0];
	struct dw_apb_i2c_config *cfg_1 = &i2c_config[1];
	uint32_t offset, target_freq;
	uint8_t data_master[4];
	uint8_t data_slave[4];
	int cmd_reg, ret;

	printf("\nStart i2c test\n");

	if (argc && (strcmp(argv[0], "set_speed") == 0)) {
		target_freq = (uint32_t)strtol(argv[1], NULL, 0);
		i2c_configure_baudrate(cfg_0, SOURCE_CLOCK, target_freq);
	} else if (argc && (strcmp(argv[0], "write_polling") == 0)) {
		data_master[0] = 0xde;
		data_master[1] = 0xad;
		data_master[2] = 0xbe;
		data_master[3] = 0xef;
		offset = (uint32_t)strtol(argv[1], NULL, 0);

		if (i2c_get_tar(cfg_0) != EEPROM_TARGET_ADDR)
			i2c_set_tar(cfg_0, EEPROM_TARGET_ADDR);

		ret = i2c_putready(cfg_0);
		if (ret)
			return ret;
		i2c_putdata(cfg_0, (offset >> 8));
		ret = i2c_putready(cfg_0);
		if (ret)
			return ret;
		i2c_putdata(cfg_0, (offset & 0xFF));

		for (int i = 0; i < 4; i++) {
			ret = i2c_putready(cfg_0);
			if (ret)
				return ret;
			cmd_reg = (i == 3) ? data_master[i] | STOP : data_master[i];
			i2c_putdata(cfg_0, cmd_reg);
		}
	} else if (argc && (strcmp(argv[0], "read_polling") == 0)) {
		for (int i = 0; i < sizeof(data_master); i++) {
			data_master[i] = 0;
		}
		offset = (uint32_t)strtol(argv[1], NULL, 0);

		i2c_disable_interrupt(cfg_0, RX_FULL_MASK);
		if (i2c_get_tar(cfg_0) != EEPROM_TARGET_ADDR)
			i2c_set_tar(cfg_0, EEPROM_TARGET_ADDR);

		ret = i2c_putready(cfg_0);
		if (ret)
			return ret;
		i2c_putdata(cfg_0, (offset >> 8));
		ret = i2c_putready(cfg_0);
		if (ret)
			return ret;
		i2c_putdata(cfg_0, (offset & 0xFF));

		for (int i = 0; i < 4; i++) {
			ret = i2c_putready(cfg_0);
			if (ret)
				return ret;

			cmd_reg = (i == 3) ? I2C_RX | STOP : I2C_RX;
			i2c_putdata(cfg_0, cmd_reg);
		}

		for (int i = 0; i < 4; i++) {
			ret = i2c_getready(cfg_0);
			if (ret)
				return ret;
			data_master[i] = i2c_getdata(cfg_0);
		}
		i2c_enable_interrupt(cfg_0, RX_FULL_MASK);
		printf("read polling data\n");
		for (int i = 0; i < 4; i++)
			printf("rx data[%d]: 0x%x\n", i, data_master[i]);

	} else if (argc && (strcmp(argv[0], "write_int") == 0)) {
		data_master[0] = 0x01;
		data_master[1] = 0x23;
		data_master[2] = 0x45;
		data_master[3] = 0x67;
		offset = (uint32_t)strtol(argv[1], NULL, 0);

		cfg_0->idx = 0;
		cfg_0->data = data_master;
		cfg_0->len = 4;

		if (i2c_get_tar(cfg_0) != EEPROM_TARGET_ADDR)
			i2c_set_tar(cfg_0, EEPROM_TARGET_ADDR);
		ret = i2c_putready(cfg_0);
		if (ret)
			return ret;
		i2c_putdata(cfg_0, (offset >> 8));
		ret = i2c_putready(cfg_0);
		if (ret)
			return ret;
		i2c_putdata(cfg_0, (offset & 0xFF));
		i2c_enable_interrupt(cfg_0, TX_EMPTY_MASK);
		ret = i2c_intr_timeout_high(cfg_0, TFE);
		if (ret)
			return ret;

	} else if (argc && (strcmp(argv[0], "read_int") == 0)) {
		for (int i = 0; i < sizeof(data_master); i++) {
			data_master[i] = 0;
		}
		offset = (uint32_t)strtol(argv[1], NULL, 0);

		cfg_0->idx = 0;
		cfg_0->data = data_master;
		cfg_0->len = 4;

		if (i2c_get_tar(cfg_0) != EEPROM_TARGET_ADDR)
			i2c_set_tar(cfg_0, EEPROM_TARGET_ADDR);

		ret = i2c_putready(cfg_0);
		if (ret)
			return ret;
		i2c_putdata(cfg_0, (offset >> 8));
		ret = i2c_putready(cfg_0);
		if (ret)
			return ret;
		i2c_putdata(cfg_0, (offset & 0xFF));

		for (int i = 0; i < cfg_0->len; i++) {
			ret = i2c_putready(cfg_0);
			if (ret)
				return ret;
			cmd_reg = (i == (cfg_0->len - 1)) ? I2C_RX | STOP : I2C_RX;
			i2c_putdata(cfg_0, cmd_reg);
		}

		ret = i2c_intr_timeout_low(cfg_0, RFNE);
		if (ret)
			return ret;

		printf("read intr data\n");
		for (int i = 0; i < 4; i++)
			printf("rx data[%d]: 0x%x\n", i, data_master[i]);

	} else if (argc && (strcmp(argv[0], "write_loopback") == 0)) {

		for (int i = 0; i < sizeof(data_slave); i++) {
			data_slave[i] = 0;
		}

		data_master[0] = 0xde;
		data_master[1] = 0xad;
		data_master[2] = 0xbe;
		data_master[3] = 0xef;

		cfg_0->idx = 0;
		cfg_0->data = data_master;
		cfg_0->len = 4;

		cfg_1->idx = 0;
		cfg_1->data = data_slave;
		cfg_1->len = 4;

		if (i2c_get_tar(cfg_0) != LB_TARGET_ADDR)
			i2c_set_tar(cfg_0, LB_TARGET_ADDR);

		for (int i = 0; i < cfg_0->len; i++) {
			ret = i2c_putready(cfg_0);
			if (ret)
				return ret;
			cmd_reg = (i == (cfg_0->len - 1)) ? data_master[i] | STOP : data_master[i];
			i2c_putdata(cfg_0, cmd_reg);
		}

		ret = i2c_intr_timeout_low(cfg_1, RFNE);
		if (ret)
			return ret;

		printf("\nmaster tx data\n");
		for (int i = 0; i < cfg_0->len; i++)
			printf("data[i]: 0x%x\n", data_master[i]);

		printf("\nslave rx data\n");
		for (int i = 0; i < cfg_1->len; i++)
			printf("data[i]: 0x%x\n", data_slave[i]);

	} else if (argc && (strcmp(argv[0], "read_loopback") == 0)) {
		for (int i = 0; i < sizeof(data_master); i++) {
			data_master[i] = 0;
		}

		data_slave[0] = 0x12;
		data_slave[1] = 0x34;
		data_slave[2] = 0x56;
		data_slave[3] = 0x78;

		cfg_0->idx = 0;
		cfg_0->data = data_master;
		cfg_0->len = 4;

		cfg_1->idx = 0;
		cfg_1->data = data_slave;
		cfg_1->len = 4;

		if (i2c_get_tar(cfg_0) != LB_TARGET_ADDR)
			i2c_set_tar(cfg_0, LB_TARGET_ADDR);

		for (int i = 0; i < cfg_0->len; i++) {
			ret = i2c_putready(cfg_0);
			if (ret)
				return ret;

			cmd_reg = (i == (cfg_0->len - 1)) ? I2C_RX | STOP : I2C_RX;
			i2c_putdata(cfg_0, cmd_reg);
		}

		ret = i2c_intr_timeout_low(cfg_0, RFNE);
		if (ret)
			return ret;

		printf("\nslave tx data\n");
		for (int i = 0; i < cfg_1->len; i++)
			printf("data[i]: 0x%x\n", data_slave[i]);

		printf("\nmaster rx data\n");
		for (int i = 0; i < cfg_0->len; i++)
			printf("data[i]: 0x%x\n", data_master[i]);

	}
	return 1;
}

static const char help_i2c[] =
	"[test_i2c [block]]\r\n"
	" - [test_i2c set_speed <target_freq>]\r\n"
	" - [test_i2c write_polling <offset>]\r\n"
	" - [test_i2c read_polling <offset>]\r\n"
	" - [test_i2c write_int <offset>]\r\n"
	" - [test_i2c read_int <offset>]\r\n"
	" - [test_i2c write_loopback]\r\n"
	" - [test_i2c read_loopback]\r\n"
	"\r\n";

CLI_REGISTER(test_i2c, NULL, test_main_i2c, help_i2c);
