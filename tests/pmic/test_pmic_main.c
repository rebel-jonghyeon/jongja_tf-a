/* Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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
#include "rl_errors.h"
#include "ltc1427cs8.h"
#include "mp29816a.h"
#include "mp5998.h"
#include "mpq8785.h"
#include "tca9548a.h"
#include "pmic_mgr.h"
#include "g1505.h"
#include "i2c.h"
#include "test_pmic_main.h"

uint8_t test_main_pmic(int argc, char *argv[])
{
	printf("\n-> Start\n");
	printf("pmic test\n");

	uint32_t vout = 0;
	uint16_t target_address;

	uint8_t initial_page;
	uint8_t target_page = 0;
	uint8_t reg_val;
	int ret;

	if (argc && (strcmp(argv[0], "ltc1427") == 0)) {
		if (!argv[2])
			goto error_cli;
		vout = (uint32_t)strtol(argv[2], NULL, 0);

		if (!argv[1])
			goto error_cli;
		if (strcmp(argv[1], "set") == 0) {
			printf("ltc1427 set vout %d\n", vout);
			ltc1427_set_vout(0, vout);
			ltc1427_set_vout(1, vout);
			ltc1427_set_vout(2, vout);
		}
	} else if (argc && (strcmp(argv[0], "mp29816a") == 0)) {
		if (!argv[2])
			goto error_cli;
		target_address = (uint32_t)strtol(argv[2], NULL, 0);
		if (!argv[3])
			goto error_cli;
		target_page = (uint8_t)strtol(argv[3], NULL, 0);

		ret = i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, PAGE, &reg_val, 1);
		if (ret)
			return ret;
		initial_page = reg_val;

		ret = mp29816a_set_page(target_address, target_page);
		if (ret)
			return ret;

		if (!argv[1])
			goto error_cli;
		if (strcmp(argv[1], "set") == 0) {
			if (!argv[4])
				goto error_cli;
			vout = (uint32_t)strtol(argv[4], NULL, 0);
			printf("mp29816a set target_address 0x%x %d vout %d\n", target_address, target_page, vout);
			mp29816a_set_vout(target_address, vout);
		} else if (strcmp(argv[1], "get") == 0) {
			printf("mp29816a get target_address 0x%x %d\n", target_address, target_page);
			vout = mp29816a_get_vout(target_address);
		} else {
			goto error_cli;
		}

		ret = mp29816a_set_page(target_address, initial_page);
		if (ret)
			return ret;

		printf("vout: %d\n", vout);

	} else if (argc && (strcmp(argv[0], "mp5998") == 0)) {
		if (!argv[2])
			goto error_cli;
		target_address = (uint32_t)strtol(argv[2], NULL, 0);

		if (!argv[1])
			goto error_cli;
		if (strcmp(argv[1], "get") == 0) {
			if (!argv[1])
				goto error_cli;
			printf("mp5998 get target_address 0x%x\n", target_address);
			vout = mp5998_read_vout(target_address);
		}

		printf("vout: %d\n", vout);

	} else if (argc && (strcmp(argv[0], "mpq8785") == 0)) {
		if (!argv[2])
			goto error_cli;
		target_address = (uint32_t)strtol(argv[2], NULL, 0);

		if (!argv[1])
			goto error_cli;
		if (strcmp(argv[1], "set") == 0) {
			if (!argv[3])
				goto error_cli;
			vout = (uint32_t)strtol(argv[3], NULL, 0);
			printf("mpq8785 set target_address 0x%x vout %d\n", target_address, vout);
			mpq8785_set_vout(target_address, vout);
		} else if (strcmp(argv[1], "get") == 0) {
			printf("mpq8785 get target_address 0x%x\n", target_address);
			vout = mpq8785_get_vout(target_address);
		} else {
			goto error_cli;
		}

		printf("vout: %d\n", vout);

	} else if (argc && (strcmp(argv[0], "g1505") == 0)) {
		target_address = (uint32_t)strtol(argv[2], NULL, 0);

		if (strcmp(argv[1], "set") == 0) {
			vout = (uint32_t)strtol(argv[3], NULL, 0);
			printf("g1505 set target_address 0x%x vout %d\n", target_address, vout);
			g1505_set_vout_command(target_address, vout);
		}

	} else if (argc && (strcmp(argv[0], "g1505") == 0)) {
		target_address = (uint32_t)strtol(argv[2], NULL, 0);
		if (strcmp(argv[1], "get") == 0) {
			printf("g1505 get target_address 0x%x\n", target_address);
			vout = g1505_get_vout_command(target_address);
		}
		printf("vout: %d\n", vout);
	} else if (argc && (strcmp(argv[0], "manual") == 0)) {

		uint8_t value[4] = {0};

		memset(value, 0, sizeof(value));

		uint32_t value_size = 0;

		if (strcmp(argv[1], "write") == 0) {
			target_address = (uint32_t)strtol(argv[2], NULL, 0);
			uint32_t offset = (uint32_t)strtol(argv[3], NULL, 0);
			uint32_t tmp = (uint32_t)strtol(argv[4], NULL, 0);

			memcpy(value, &tmp, 4);
			value_size = (uint32_t)strtol(argv[5], NULL, 0);
			i2c_write_polling_o_d(I2C0_PERI0_ID, target_address, offset, value, value_size);
		} else if (strcmp(argv[1], "read") == 0) {
			target_address = (uint32_t)strtol(argv[2], NULL, 0);
			uint32_t offset = (uint32_t)strtol(argv[3], NULL, 0);

			value_size = (uint32_t)strtol(argv[4], NULL, 0);
			i2c_read_polling_o_d(I2C0_PERI0_ID, target_address, offset, value, value_size);
		} else if (strcmp(argv[1], "cmd_only") == 0) {
			target_address = (uint32_t)strtol(argv[2], NULL, 0);
			uint32_t tmp = (uint32_t)strtol(argv[3], NULL, 0);

			memcpy(value, &tmp, 4);
			value_size = (uint32_t)strtol(argv[4], NULL, 0);
			i2c_write_polling_d(I2C0_PERI0_ID, target_address, value, value_size);
		}

		for (int i = 0; i < value_size; i++) {
			printf("value[%d]: 0x%x ", i, value[i]);
		}
		printf("\n");

	} else if (argc && (strcmp(argv[0], "mux") == 0)) {
		uint16_t target_address = (uint32_t)strtol(argv[2], NULL, 0);

		if (strcmp(argv[1], "enable") == 0) {
			uint8_t value = (uint32_t)strtol(argv[3], NULL, 0);

			i2c_mux_enable_channel(target_address, value);

		} else if (strcmp(argv[1], "disable") == 0) {
			uint8_t value = (uint32_t)strtol(argv[3], NULL, 0);

			i2c_mux_disable_channel(target_address, value);

		} else if (strcmp(argv[1], "check_ch") == 0) {
			uint8_t ch_state = i2c_mux_check_channel_state(target_address);

			printf("ch_state: 0x%x\n", ch_state);
		}
	} else if (argc && (strcmp(argv[0], "block") == 0)) {

		if (strcmp(argv[1], "set") == 0) {

			vout = (uint32_t)strtol(argv[3], NULL, 0);
			if (vout > 900 || vout < 700) {
				printf("Error: VOUT is out of allowed range (700 <= vout <= 900)\n");
				return RL_ERROR;
			}

			if (strcmp(argv[2], "cp") == 0) {
				mpq8785_set_vout(VDD_CP_CHIPLET02, vout);
				mpq8785_set_vout(VDD_CP_CHIPLET13, vout);
			} else if (strcmp(argv[2], "dcl") == 0) {
				mp29816a_set_vout(VDD_DCL, vout);
				mp29816a_set_vout(VDD_DCL_ODD, vout);
			} else if (strcmp(argv[2], "mem") == 0) {
				mpq8785_set_vout(VDD_MEM_CHIPLET02, vout);
				mpq8785_set_vout(VDD_MEM_CHIPLET13, vout);
			} else if (strcmp(argv[2], "rbc") == 0) {
				mpq8785_set_vout(A_VDD075_RBC_H_CHIPLET02, vout);
				mpq8785_set_vout(A_VDD075_RBC_H_CHIPLET13, vout);
				mpq8785_set_vout(A_VDD075_RBC_V_CHIPLET01, vout);
				mpq8785_set_vout(A_VDD075_RBC_V_CHIPLET23, vout);
			} else if (strcmp(argv[2], "rbcio") == 0) {
				mpq8785_set_vout(VDD_RBC_H_CHIPLET02, vout);
				mpq8785_set_vout(VDD_RBC_H_CHIPLET13, vout);
				mpq8785_set_vout(VDD_RBC_V_CHIPLET01, vout);
				mpq8785_set_vout(VDD_RBC_V_CHIPLET23, vout);
			} else {
				printf("Error: Invalid CLI command\n");
				return RL_ERROR;
			}

		} else if (strcmp(argv[1], "get") == 0) {

			if (strcmp(argv[2], "cp") == 0) {
				vout = mpq8785_get_vout(VDD_CP_CHIPLET02);
				printf("VDD_CP_CHIPLET02 vout : %d\n", vout);
				vout = mpq8785_get_vout(VDD_CP_CHIPLET13);
				printf("VDD_CP_CHIPLET13 vout : %d\n", vout);
			} else if (strcmp(argv[2], "dcl") == 0) {
				vout = mp29816a_get_vout(VDD_DCL);
				printf("VDD_DCL vout : %d\n", vout);
				vout = mp29816a_get_vout(VDD_DCL_ODD);
				printf("VDD_DCL_ODD vout : %d\n", vout);
			} else if (strcmp(argv[2], "mem") == 0) {
				vout = mpq8785_get_vout(VDD_MEM_CHIPLET02);
				printf("VDD_MEM_CHIPLET02 vout : %d\n", vout);
				vout = mpq8785_get_vout(VDD_MEM_CHIPLET13);
				printf("VDD_MEM_CHIPLET13 vout : %d\n", vout);
			} else if (strcmp(argv[2], "rbc") == 0) {
				vout = mpq8785_get_vout(A_VDD075_RBC_H_CHIPLET02);
				printf("A_VDD075_RBC_H_CHIPLET02 vout : %d\n", vout);
				vout = mpq8785_get_vout(A_VDD075_RBC_H_CHIPLET13);
				printf("A_VDD075_RBC_H_CHIPLET13 vout : %d\n", vout);
				vout = mpq8785_get_vout(A_VDD075_RBC_V_CHIPLET01);
				printf("A_VDD075_RBC_V_CHIPLET02 vout : %d\n", vout);
				vout = mpq8785_get_vout(A_VDD075_RBC_V_CHIPLET23);
				printf("A_VDD075_RBC_V_CHIPLET13 vout : %d\n", vout);
			} else if (strcmp(argv[2], "rbcio") == 0) {
				vout = mpq8785_get_vout(VDD_RBC_H_CHIPLET02);
				printf("VDD_RBC_H_CHIPLET02 vout : %d\n", vout);
				vout = mpq8785_get_vout(VDD_RBC_H_CHIPLET13);
				printf("VDD_RBC_H_CHIPLET13 vout : %d\n", vout);
				vout = mpq8785_get_vout(VDD_RBC_V_CHIPLET01);
				printf("VDD_RBC_V_CHIPLET01 vout : %d\n", vout);
				vout = mpq8785_get_vout(VDD_RBC_V_CHIPLET23);
				printf("VDD_RBC_V_CHIPLET23 vout : %d\n", vout);
			} else {
				printf("Error: Invalid CLI command\n");
				return RL_ERROR;
			}

		}

	} else {
		goto error_cli;
	}

	return 1;

error_cli:
	printf("Error: Invalid CLI command\n");
	return RL_ERROR;
}

static const char help_pmic[] =
	"[test_pmic]\r\n"
	" - [test_pmic ltc1427 set <vout>]\r\n"
	" - [test_pmic mp29816a set <target_address> <target_page> <vout>]\r\n"
	" - [test_pmic mp29816a get <target_address> <target_page>]\r\n"
	" - [test_pmic mp5998 get <target_address>]\r\n"
	" - [test_pmic mpq8785 set <target_address>  <vout>]\r\n"
	" - [test_pmic mpq8785 get <target_address>]\r\n"
	" - [test_pmic g1505 set <target_address> <vout>]\r\n"
	" - [test_pmic g1505 get <target_address>]\r\n"
	" - [test_pmic manual write <target_address> <offset> <value> <value_size>]\r\n"
	" - [test_pmic manual cmd_only <target_address> <value> <value_size>]\r\n"
	" - [test_pmic manual read <target_address> <offset> <value_size>]\r\n"
	" - [test_pmic mux enable <target_address> <value]\r\n"
	" - [test_pmic mux disable <target_address> <value]\r\n"
	" - [test_pmic mux check_ch <target_address>]\r\n"
	" - [test_pmic block set <block> <vout>]\r\n"
	" - [test_pmic block get <block>]\r\n"
	"\r\n";

CLI_REGISTER(test_pmic, NULL, test_main_pmic, help_pmic);
