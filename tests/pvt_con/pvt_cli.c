/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include <test_common.h>
#include <string.h>

#include <pvt_con.h>
#include <pvt_con_reg.h>
#include "pvt_cli.h"
#include "pvt_cli_show.h"
#include "pvt_cli_enable.h"
#include "pvt_cli_disable.h"
#include "pvt_cli_set.h"

extern uint64_t pvt_base_address[];
extern uint32_t pvt_n_sensors[];

uint8_t pvt_cli(int argc, char **argv)
{
	uint8_t ret = true;

	uint32_t value;
	uint32_t chiplet_id;
	uint32_t instance_id;

	if (argc == 0) {
		return false;
	}

	/* pvt show <target> */
	if (strcmp(argv[0], "show") == 0) {
		if (argc == 1) {
			return false;
		}

		/* pvt show process */
		if (strcmp(argv[1], "process") == 0) {
			pvt_cli_show_process();
		/* pvt show voltage */
		} else if (strcmp(argv[1], "voltage") == 0) {
			pvt_cli_show_voltage();
		/* pvt show temperature */
		} else if (strcmp(argv[1], "temperature") == 0) {
			pvt_cli_show_temperature();
		/* pvt show interrupt */
		} else if (strcmp(argv[1], "interrupt") == 0) {
			pvt_cli_show_interrupt();
		} else if (strcmp(argv[1], "dram") == 0) {
			pvt_cli_show_dram();
		} else {
			return false;
		}
	/* pvt enable <config> <chiplet_id> <instance_id> */
	} else if (strcmp(argv[0], "enable") == 0) {
		if (argc < 4) {
			return false;
		}
		chiplet_id	= atoi(argv[2]);
		instance_id	= atoi(argv[3]);

		/* pvt enable dfs         <chiplet_id> <instance_id> */
		if (strcmp(argv[1], "dfs") == 0) {
			pvt_cli_enable_dfs(chiplet_id, instance_id);
		/* pvt enable trip        <chiplet_id> <instance_id> */
		} else if (strcmp(argv[1], "trip") == 0) {
			pvt_cli_enable_trip(chiplet_id, instance_id);
		/* pvt enable process     <chiplet_id> <instance_id> */
		} else if (strcmp(argv[1], "process") == 0) {
			pvt_cli_enable_process(chiplet_id, instance_id);
		/* pvt enable voltage     <chiplet_id> <instance_id> */
		} else if (strcmp(argv[1], "voltage") == 0) {
			pvt_cli_enable_voltage(chiplet_id, instance_id);
		/* pvt enable temperature <chiplet_id> <instance_id> */
		} else if (strcmp(argv[1], "temperature") == 0) {
			pvt_cli_enable_temperature(chiplet_id, instance_id);
		} else {
			return false;
		}
	/* pvt disable <config> <chiplet_id} <instance_id> */
	} else if (strcmp(argv[0], "disable") == 0) {
		if (argc < 4) {
			return false;
		}
		chiplet_id	= atoi(argv[2]);
		instance_id	= atoi(argv[3]);

		/* pvt disable dfs         <chiplet_id> <instance_id> */
		if (strcmp(argv[1], "dfs") == 0) {
			pvt_cli_disable_dfs(chiplet_id, instance_id);
		/* pvt disable trip        <chiplet_id> <instance_id> */
		} else if (strcmp(argv[1], "trip") == 0) {
			pvt_cli_disable_trip(chiplet_id, instance_id);
		/* pvt disable process     <chiplet_id> <instance_id> */
		} else if (strcmp(argv[1], "process") == 0) {
			pvt_cli_disable_process(chiplet_id, instance_id);
		/* pvt disable voltage     <chiplet_id> <instance_id> */
		} else if (strcmp(argv[1], "voltage") == 0) {
			pvt_cli_disable_voltage(chiplet_id, instance_id);
		/* pvt disable temperature <chiplet_id> <instance_id> */
		} else if (strcmp(argv[1], "temperature") == 0) {
			pvt_cli_disable_temperature(chiplet_id, instance_id);
		} else {
			return false;
		}
	/* pvt set <config> <value> <chiplet_id} <instance_id> */
	} else if (strcmp(argv[0], "set") == 0) {
		if (argc < 5) {
			return false;
		}
		value		= atoi(argv[2]);
		chiplet_id	= atoi(argv[3]);
		instance_id	= atoi(argv[4]);

		/* pvt set dfs_trip_threshold <value> <chiplet_id> <instance_id> */
		if (strcmp(argv[1], "dfs_trip_threshold") == 0) {
			pvt_cli_set_dfs_trip_threshold(value, chiplet_id, instance_id);
		/* pvt set sampling_interval  <value> <chiplet_id> <instance_id> */
		} else if (strcmp(argv[1], "sampling_interval") == 0) {
			pvt_cli_set_sampling_interval(value, chiplet_id, instance_id);
		} else {
			return false;
		}
	}

	return ret;
}

static const char help_pvt[] =
	"[pvt show <sensor>]\n"
	" - [pvt show process]\n"
	" - [pvt show voltage]\n"
	" - [pvt show temperature]\n"
	" - [pvt show interrupt]\n"
	"[pvt enable <config> <chiplet_id} <instance_id>]\n"
	" - [pvt enable dfs         <chiplet_id> <instance_id>]\n"
	" - [pvt enable trip        <chiplet_id> <instance_id>]\n"
	" - [pvt enable process     <chiplet_id> <instance_id>]\n"
	" - [pvt enable voltage     <chiplet_id> <instance_id>]\n"
	" - [pvt enable temperature <chiplet_id> <instance_id>]\n"
	"[pvt disable <config> <chiplet_id} <instance_id>]\n"
	" - [pvt disable dfs         <chiplet_id> <instance_id>]\n"
	" - [pvt disable trip        <chiplet_id> <instance_id>]\n"
	" - [pvt disable process     <chiplet_id> <instance_id>]\n"
	" - [pvt disable voltage     <chiplet_id> <instance_id>]\n"
	" - [pvt disable temperature <chiplet_id> <instance_id>]\n"
	"[pvt set <config> <value> <chiplet_id} <instance_id>]\n"
	" - [pvt set dfs_trip_threshold <value> <chiplet_id> <instance_id>]\n"
	" - [pvt set sampling_interval  <value> <chiplet_id> <instance_id>]\n"
	"\n";

CLI_REGISTER(pvt, NULL, pvt_cli, help_pvt);
