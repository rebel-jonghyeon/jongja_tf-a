/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include "test_common.h"
#include "test_pcie.h"

static const char help_pcie[] =
	"pcie sub commands:\r\n"
	"msix, prepare_data, hdma_ll, hdma_nll, set_hdma_lut, invalidate_hdma_lut, select_func\r\n"
	"set_speed, get_speed, set_width, get_width\r\n"
	"find_cap, find_ext_cap, dis_cap, dis_ext_cap\r\n"
	"iatu, iatu_ib_reset, disable_region, iatu_ob, ob_wr, ob_rd\r\n"
	"hist, show_hist, clear_hist\r\n"
	"doe_send, doe_read, doe_setup, ide, ide_key\r\n"
	"dp, tba, ecnt, sd, sd_eq\r\n"
	"\r\n";

uint8_t pcie_commands(int argc, char *argv[])
{
	uint8_t ret = true;

	printf("\nStart pcie command\n");

	if (argc == 0) {

	} else if (argc >= 1) {
		if (strcmp(argv[0], "msix") == 0) {
			test_pcie_request_msix(argc, argv);
		} else if (strcmp(argv[0], "set_hdma_lut") == 0) {
			test_pcie_set_hdma_lut(argc, argv);
		} else if (strcmp(argv[0], "invalidate_hdma_lut") == 0) {
			test_pcie_invalidate_hdma_lut(argc, argv);
		} else if (strcmp(argv[0], "select_func") == 0) {
			test_pcie_select_function(argc, argv);
		} else if (strcmp(argv[0], "prepare_data") == 0) {
			test_pcie_prepare_data(argc, argv);
		} else if (strcmp(argv[0], "hdma_ll") == 0) {
			test_pcie_hdma_ll_mode(argc, argv);
		} else if (strcmp(argv[0], "hdma_nll") == 0) {
			test_pcie_hdma_non_ll_mode(argc, argv);
		} else if (strcmp(argv[0], "ide") == 0) {
			test_pcie_ide();
		} else if (strcmp(argv[0], "ide_key") == 0) {
			test_pcie_ide_key_swap(argc, argv);
		} else if (strcmp(argv[0], "find_cap") == 0) {
			test_pcie_find_capability(argc, argv);
		} else if (strcmp(argv[0], "find_ext_cap") == 0) {
			test_pcie_find_ext_capability(argc, argv);
		} else if (strcmp(argv[0], "dis_cap") == 0) {
			test_pcie_disable_capability(argc, argv);
		} else if (strcmp(argv[0], "dis_ext_cap") == 0) {
			test_pcie_disable_ext_capability(argc, argv);
		} else if (strcmp(argv[0], "set_speed") == 0) {
			test_pcie_set_speed(argc, argv);
		} else if (strcmp(argv[0], "set_width") == 0) {
			test_pcie_set_width(argc, argv);
		} else if (strcmp(argv[0], "get_speed") == 0) {
			test_pcie_get_speed();
		} else if (strcmp(argv[0], "get_width") == 0) {
			test_pcie_get_width();
		} else if (strcmp(argv[0], "show_iatu") == 0) {
			test_pcie_show_iatu_table();
		} else if (strcmp(argv[0], "iatu_ob") == 0) {
			test_pcie_iatu_outbound(argc, argv);
		} else if (strcmp(argv[0], "iatu") == 0) {
			test_pcie_iatu_inbound(argc, argv);
		} else if (strcmp(argv[0], "iatu_ib_reset") == 0) {
			test_pcie_iatu_disable_inbound_region_all();
		} else if (strcmp(argv[0], "hist") == 0) {
			test_pcie_history_store(argc, argv);
		} else if (strcmp(argv[0], "show_hist") == 0) {
			test_pcie_show_history(argc, argv);
		} else if (strcmp(argv[0], "clear_hist") == 0) {
			test_pcie_clear_buffer(argc, argv);
		} else if (strcmp(argv[0], "doe_send") == 0) {
			test_pcie_write_to_rmb(argc, argv);
		} else if (strcmp(argv[0], "doe_read") == 0) {
			test_pcie_doe_print_wmb_data(argc, argv);
		} else if (strcmp(argv[0], "doe_setup") == 0) {
			test_pcie_doe_setup_addr(argc, argv);
		} else if (strcmp(argv[0], "dp") == 0) {
			test_pcie_rasdp(argc, argv);
		} else if (strcmp(argv[0], "sd") == 0) {
			test_pcie_rasdes_sd(argc, argv);
		} else if (strcmp(argv[0], "sd_eq") == 0) {
			test_pcie_rasdes_sd_eq(argc, argv);
		} else if (strcmp(argv[0], "tba") == 0) {
			test_pcie_rasdes_tba(argc, argv);
		} else if (strncmp(argv[0], "ecnt", 4) == 0) {
			test_pcie_rasdes_ecnt(argc, argv);
		} else if (strcmp(argv[0], "disable_region") == 0) {
			test_pcie_iatu_disable_region(argc, argv);
		} else if (strcmp(argv[0], "ob_wr") == 0) {
			test_pcie_outbound_write(argc, argv);
		} else if (strcmp(argv[0], "ob_rd") == 0) {
			test_pcie_outbound_read(argc, argv);
		} else {
			printf("No pcie test case for %s\n", argv[0]);
			ret = false;
		}
	} else
		ret = false;

	return ret;
}

uint8_t test_pcie_main(int argc, char *argv[])
{
	uint8_t ret = true;

	if (argc >= 1) {
		if (strcmp(argv[0], "iatu") == 0) {
			test_pcie_iatu(argc, argv);
		} else if (strcmp(argv[0], "mode") == 0) {
			test_pcie_mode(argc, argv);
		} else if (strcmp(argv[0], "doe") == 0) {
			test_pcie_doe(argc, argv);
		} else if (strcmp(argv[0], "msix") == 0) {
			test_pcie_msix(argc, argv);
		} else {
			ret = false;
		}
	} else
		ret = false;

	return ret;
}

CLI_REGISTER(pcie, NULL, pcie_commands, help_pcie);
CLI_REGISTER(test_pcie, NULL, test_pcie_main, NULL);
