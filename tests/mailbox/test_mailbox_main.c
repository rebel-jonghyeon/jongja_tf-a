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
#include <stdint.h>
#include <rebel_h_platform.h>
#include "test_common.h"
#include "mailbox.h"
#include "test_mailbox_main.h"

static const char mailbox_name[][30] = {
#if defined __TARGET_PCIE
	"MAILBOX_M2",
	"MAILBOX_CP0_M4",
	"MAILBOX_CP1_M5",
	"MAILBOX_PCIE_VF0",
	"MAILBOX_PCIE_VF1",
	"MAILBOX_PCIE_VF2",
	"MAILBOX_PCIE_VF3",
	"MAILBOX_PCIE_VF4",
	"MAILBOX_PCIE_VF5",
	"MAILBOX_PCIE_VF6",
	"MAILBOX_PCIE_VF7",
	"MAILBOX_PCIE_VF8",
	"MAILBOX_PCIE_VF9",
	"MAILBOX_PCIE_VF10",
	"MAILBOX_PCIE_VF11",
	"MAILBOX_PCIE_VF12",
	"MAILBOX_PCIE_VF13",
	"MAILBOX_PCIE_VF14",
	"MAILBOX_PCIE_VF15",
	"MAILBOX_PCIE_PF",
#else
	"MAILBOX_M0",
	"MAILBOX_CP0_M3",
	"MAILBOX_CP0_M4",
	"MAILBOX_CP1_M3",
	"MAILBOX_CP1_M4",

	"MAILBOX_PERI0_M5",
	"MAILBOX_PERI0_M7_CPU0",
	"MAILBOX_PERI0_M7_CPU1",
	"MAILBOX_PERI0_M8_CPU0",
	"MAILBOX_PERI0_M8_CPU1",
	"MAILBOX_PERI0_M9_CPU0",
	"MAILBOX_PERI0_M9_CPU1",
	"MAILBOX_PERI0_M10_CPU0",
	"MAILBOX_PERI0_M10_CPU1",
	"MAILBOX_PERI0_M11_CPU0",
	"MAILBOX_PERI0_M11_CPU1",
	"MAILBOX_PERI0_M12_CPU0",
	"MAILBOX_PERI0_M12_CPU1",

	"MAILBOX_PERI1_M7_CPU0",
	"MAILBOX_PERI1_M7_CPU1",
	"MAILBOX_PERI1_M8_CPU0",
	"MAILBOX_PERI1_M8_CPU1",
	"MAILBOX_PERI1_M9_CPU0",
	"MAILBOX_PERI1_M9_CPU1",
	"MAILBOX_PERI1_M10_CPU0",
	"MAILBOX_PERI1_M10_CPU1",
	"MAILBOX_PERI1_M11_CPU0",
	"MAILBOX_PERI1_M11_CPU1",
	"MAILBOX_PERI1_M12_CPU0",
	"MAILBOX_PERI1_M12_CPU1",

	"MAILBOX_PCIE_VF0",
	"MAILBOX_PCIE_VF1",
	"MAILBOX_PCIE_VF2",
	"MAILBOX_PCIE_VF3",
	"MAILBOX_PCIE_VF4",
	"MAILBOX_PCIE_VF5",
	"MAILBOX_PCIE_VF6",
	"MAILBOX_PCIE_VF7",
	"MAILBOX_PCIE_VF8",
	"MAILBOX_PCIE_VF9",
	"MAILBOX_PCIE_VF10",
	"MAILBOX_PCIE_VF11",
	"MAILBOX_PCIE_VF12",
	"MAILBOX_PCIE_VF13",
	"MAILBOX_PCIE_VF14",
	"MAILBOX_PCIE_VF15",
	"MAILBOX_PCIE_PF",
#endif
};

struct test_data {
	char str[10];
	int size;
	int channel;
	int index;
};

struct test_data arr[] = {
	{"ZERO", 4, DEFAULT_M_CHANNEL, DEFAULT_M_INDEX},
	{"A", 1, DEFAULT_M_CHANNEL, DEFAULT_M_INDEX},
	{"BB", 2, DEFAULT_M_CHANNEL, DEFAULT_M_INDEX},
	{"CCC", 3, DEFAULT_M_CHANNEL, DEFAULT_M_INDEX},
	{"DDDD", 4, DEFAULT_M_CHANNEL, DEFAULT_M_INDEX},
};

int test_mailbox_inter_chiplet(int inst, int target_id, int chan, int cpu)
{
	printf("from Mailbox: %s, chan: %d target_id: %d\n", mailbox_name[inst], chan, (int)target_id);
	ipm_samsung_write(inst, target_id, arr[chan].str, arr[chan].size, arr[chan].index);
	ipm_samsung_send(inst, target_id, chan, cpu);

	if (inst < IDX_MAILBOX_PCIE_VF0) {
		printf("from Mailbox: %s, chan: %d target_id: %d\n", mailbox_name[inst], chan,
			   (int)target_id);
		ipm_samsung_write(inst, target_id, arr[chan].str, arr[chan].size, arr[chan].index);
		ipm_samsung_send(inst, target_id, chan, cpu);
	}

	return 0;
}

int test_mailbox_loopback(int inst, int chan, int cpu)
{
	uint32_t target_id = CHIPLET_ID;

	printf("from Mailbox: %s, chan: %d target_id: %d\n", mailbox_name[inst], chan, (int)target_id);
	ipm_samsung_write(inst, target_id, arr[chan].str, arr[chan].size, arr[chan].index);
	ipm_samsung_send(inst, target_id, chan, cpu);

	if (inst < IDX_MAILBOX_PCIE_VF0) {
		printf("from Mailbox:%s, chan: %d target_id: %d\n", mailbox_name[inst], chan,
			   (int)target_id);
		ipm_samsung_write(inst, target_id, arr[chan].str, arr[chan].size, arr[chan].index);
		ipm_samsung_send(inst, target_id, chan, cpu);
	}

	return 0;
}

uint8_t test_main_mailbox(int argc, char *argv[])
{
	printf("\nStart mailbox test\n");

	if (argc < 1) {
		return false;
	} else {
		for (int i = 0; i < IDX_MAILBOX_END; ++i) {
			ipm_samsung_register_callback(i, default_cb);
		}

		if (strcmp(argv[0], "internal") == 0) {
		#if defined __TARGET_PCIE
			test_mailbox_loopback(IDX_MAILBOX_M2, 0, CPU0);
			test_mailbox_loopback(IDX_MAILBOX_M2, 5, CPU0);
			test_mailbox_loopback(IDX_MAILBOX_CP0_M4, 1, CPU0);
			test_mailbox_loopback(IDX_MAILBOX_CP0_M4, 6, CPU0);
			test_mailbox_loopback(IDX_MAILBOX_CP0_M4, 2, CPU0);
			test_mailbox_loopback(IDX_MAILBOX_CP0_M4, 7, CPU0);
		#else
			test_mailbox_loopback(IDX_MAILBOX_M0, 0, CPU0);
			test_mailbox_loopback(IDX_MAILBOX_M0, 5, CPU0);
			test_mailbox_loopback(IDX_MAILBOX_CP0_M3, 1, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_CP0_M3, 6, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_CP0_M4, 2, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_CP0_M4, 7, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_CP1_M3, 3, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_CP1_M3, 5, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_CP1_M4, 4, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_CP1_M4, 6, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_CP0_M3, 0, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_CP1_M3, 1, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_PERI0_M9_CPU0, 1, CPU0);
			test_mailbox_loopback(IDX_MAILBOX_PERI0_M9_CPU1, 1, CPU1);
			test_mailbox_loopback(IDX_MAILBOX_PERI0_M10_CPU0, 1, CPU0);
			test_mailbox_loopback(IDX_MAILBOX_PERI0_M10_CPU1, 1, CPU1);

		/* Test for inter chiplet mailbox */
		/* FIXME:
		 * For this test, a multi-chiplet environment including ucie is required.
		 */
		/*	switch (CHIPLET_ID) {
		 *		case 0: // from C0_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 0, 0, CPU0);			// to C0_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M7_CPU0, 0, 0, CPU0);	// to C0_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M9_CPU0, 0, 0, CPU0);	// to C0_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 1, 0, CPU0);			// to C1_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M7_CPU0, 1, 0, CPU0);	// to C1_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M9_CPU0, 1, 0, CPU0);	// to C1_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 2, 0, CPU0);			// to C2_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M7_CPU0, 2, 0, CPU0);	// to C2_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M9_CPU0, 2, 0, CPU0);	// to C2_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 3, 0, CPU0);			// to C3_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M7_CPU0, 3, 0, CPU0);	// to C3_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M9_CPU0, 3, 0, CPU0);	// to C3_CP1
		 *			break;
		 *		case 1: // from C1_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 0, 0, CPU0);			// to C0_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M7_CPU1, 0, 0, CPU1);	// to C0_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M9_CPU1, 0, 0, CPU1);	// to C0_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 1, 0, CPU0);			// to C1_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M7_CPU1, 1, 0, CPU1);	// to C1_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M9_CPU1, 1, 0, CPU1);	// to C1_CP1

		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 2, 0, CPU0);			// to C2_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M7_CPU1, 2, 0, CPU1);	// to C2_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M9_CPU1, 2, 0, CPU1);	// to C2_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 3, 0, CPU0);			// to C3_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M7_CPU1, 3, 0, CPU1);	// to C3_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M9_CPU1, 3, 0, CPU1);	// to C3_CP1
		 *			break;
		 *		case 2: // from C2_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 0, 0, CPU0);			// to C0_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M8_CPU0, 0, 0, CPU0);	// to C0_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M10_CPU0, 0, 0, CPU0);	// to C0_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 1, 0, CPU0);			// to C1_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M8_CPU0, 1, 0, CPU0);	// to C1_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M10_CPU0, 1, 0, CPU0);	// to C1_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 2, 0, CPU0);			// to C2_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M8_CPU0, 2, 0, CPU0);	// to C2_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M10_CPU0, 2, 0, CPU0);	// to C2_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 3, 0, CPU0);			// to C3_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M8_CPU0, 3, 0, CPU0);	// to C3_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M10_CPU0, 3, 0, CPU0);	// to C3_CP1
		 *			break;
		 *		case 3: // from C3_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 0, 0, CPU0);			// to C0_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M8_CPU1, 0, 0, CPU1);	// to C0_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M10_CPU1, 0, 0, CPU1);	// to C0_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 1, 0, CPU0);			// to C1_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M8_CPU1, 1, 0, CPU1);	// to C1_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M10_CPU1, 1, 0, CPU1);	// to C1_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 2, 0, CPU0);			// to C2_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M8_CPU1, 2, 0, CPU1);	// to C2_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M10_CPU1, 2, 0, CPU1);	// to C2_CP1
		 *
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M5, 3, 0, CPU0);			// to C3_ROT
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M8_CPU1, 3, 0, CPU1);	// to C3_CP0
		 *			test_mailbox_inter_chiplet(IDX_MAILBOX_M10_CPU1, 3, 0, CPU1);	// to C3_CP1
		 *			break;
		 *		default:
		 *			break;
		 *	}
		 */
		#endif
		} else if (strcmp(argv[0], "pcie") == 0) {
			int cpu;
		#if defined __TARGET_PCIE
			cpu = CPU1;
		#elif (__TARGET_CP == 0)
			cpu = CPU0;
		#endif
			if (argc >= 2) {
				int inst = IDX_MAILBOX_PCIE_VF0 + atoi(argv[1]);

				if (inst < IDX_MAILBOX_PCIE_VF0 || inst > IDX_MAILBOX_PCIE_PF)
					return false;

				int chan = 0;

				if (argc == 3)
					chan = atoi(argv[2]);

				test_mailbox_loopback(inst, chan, cpu);
			} else {
				int chan = 0;

				for (int i = IDX_MAILBOX_PCIE_VF0; i <= IDX_MAILBOX_PCIE_PF; ++i) {
					test_mailbox_loopback(i, (chan++ % 9), cpu);
				}
			}
		} else {
			printf("Not supported yet\n");
		}
	}

	return true;
}

static const char help_mailbox[] =
	"[test_mailbox <vector>]\r\n"
	" - [test_mailbox internal]\r\n"
	" - [test_mailbox pcie]\r\n"
	" - [test_mailbox external]\r\n"
	"\r\n";

CLI_REGISTER(test_mailbox, NULL, test_main_mailbox, help_mailbox);
