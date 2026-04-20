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
#include "qspi_apb.h"
#include "rl_errors.h"
#include "cpu.h"

uint8_t test_main_qspiapb(int argc, char *argv[])
{
	uint32_t data_out = 0x12345678;
	uint32_t data_in[2];
	uint32_t ch_num = 0;

	printf("\nStart qspi_apb test\n");

	ch_num = (uint32_t)strtol(argv[0], NULL, 0);
	if (ch_num > 3) {
		printf("\nWrong channel num=%d\n", ch_num);
		return RL_ERROR;
	} else {
		printf("\nchannel num=%d\n", ch_num);
		qspi_apb_set(ch_num, DW_APB_SSI_CTRLR0_DFS_8, DW_APB_SSI_CTRLR0_TMOD_TX_RX,
					 DW_APB_SSI_CTRLR0_SPI_FRF_STANDARD, 250);

		printf("Enable loopback mode for the test\n");
		qspi_apb_enable_loopback(ch_num);
		qspi_apb_transfer(ch_num, (uint8_t *)&data_out, 0, 4, (uint8_t *)data_in, 0, 8);

		printf("Data_out  =0x%8x\n", data_out);
		printf("Data_in[0]=0x%8x\n", data_in[0]);
		printf("Data_in[1]=0x%8x\n", data_in[1]);
	}
	return 1;
}

static const char help_qspiapb[] =
	"[test_qspiapb]\r\n"
	" - [test_qspiapb channel]\r\n"
	"\r\n";

CLI_REGISTER(test_qspiapb, NULL, test_main_qspiapb, help_qspiapb);
