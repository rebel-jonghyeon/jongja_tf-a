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

#include "rl_errors.h"
#include "rl_utils.h"
#include "rebel_h_platform.h"
#include "test_common.h"
#include "mailbox.h"
#include "pcie_dw.h"
#include "pcie_dw_ide.h"
#include "pcie_doe.h"
#include "test_ide.h"

#define DIV_ROUND_UP(val, dev) (((val) + (dev) - 1) / (dev))

/* Address to save DOE Data */
#define DOE_MESSAGE_ADDR (DRAM_USER_BAT_BASE)

/* Use same Stream ID into both Ports associated with a given Link IDE Stream. */
#define STREAM_ID (1)

/* The number of iteration times */
#define TIMES_KEY_PROG (6)
#define TIMES_KEY_SET_GO (6)

static bool received_key_set_go[2][3] = {0, };
static bool ide_disable = true;

int32_t write_to_rmb(uint32_t data_len, void *data)
{
	struct pcie_epc *epc = pcie_get_epc();
	uint32_t payload[DOE_MAX_LENGTH] = {0,};
	int32_t ret = RL_ERROR;
	uint32_t doe_len = DIV_ROUND_UP(data_len, 4) + PCI_DOE_HEADER_LEN;

	if (doe_len > DOE_MAX_LENGTH) {
		return RL_BADLEN;
	}

	payload[0] = 0;
	payload[1] = doe_len & PCI_DOE_HEADER_2_LENGTH;
	memcpy(&payload[2], data, data_len);

	printf("Write to DOE READ MB\n");
	ret = pcie_doe_write_rmb(epc, doe_len, payload);
	if (ret) {
		printf("Error occurred\n");
	}

	return ret;
}

static int32_t parse_doe_data(uint32_t *doe_addr)
{
	volatile int32_t temp;
	uint32_t *src_addr = doe_addr;

	/* STEP 1: Check if DOE message updated */
	printf("1 - Waiting DOE Messge from HOST...\n");
	src_addr++; /* length is in second DW */
	while (1) {
		temp = rl_readl(src_addr);
		if (temp)
			break;
	}
	rl_writel(0, src_addr);
	printf("1 - Got DOE Messge from HOST...\n");

	/* SETP 2: Parse Data */
	uint32_t data = rl_readl(++src_addr);
	uint8_t protocol_id = PROTO_ID_FROM_DW(data);
	uint8_t obj_id = OBJ_ID_FROM_DW(data);

	printf("2 - Protocol id: 0x%x\tObj_id: 0x%x\n", protocol_id, obj_id);
	if (protocol_id != PROTOCOL_ID_IDE) { /* if not IDE */
		printf("Protocol ID invalid\n");
		return RL_ERROR;
	}

	/* STEP 3: Process according to Object type */
	switch (obj_id) {
	case ID_KEY_PROG:
		printf("3-1: KEY_PROG Received\n");
		/* STEP 3-1-1: Install key on the KEY_x_IDE by RoT */
		struct key_prog_data_object *key_prg_data = (struct key_prog_data_object *)(src_addr);

		printf("3-1-1: Send mailbox to Rot\n");
		ipm_samsung_write(IDX_MAILBOX_M2, CHIPLET_ID, key_prg_data, sizeof(struct key_prog_data_object), CPU0);
		ipm_samsung_send(IDX_MAILBOX_M2, CHIPLET_ID, PCIE_IDE_FROM_CM7_CHANNEL, CPU0);

		/* STEP 3-1-2: Wait key insert done by RoT */
		printf("3-1-2: Waiting key insert done...\n");
		while (1) {
			/*
			 * Read the word from the end of doe_fifo_addr to know if key insert has been completed
			 * Address could be changed but update address in drivers/pcie/pcie_dw_ide.c also.
			 */
			temp = rl_readl(doe_addr + DOE_MAX_LENGTH);
			if (temp == MB_RECEIVED_KEY_INSERT_DONE)
				break;
		}
		rl_writel(0, doe_addr + DOE_MAX_LENGTH);
		printf("3-1-2: Key installed done\n");

		/* STEP 3-1-3: Send KP_ACK to Host */
		printf("3-1-3: Send KP_ACK to Host");
		struct ide_km_data_object kp_ack_data = {0,};

		kp_ack_data.object_id = ID_KP_ACK;
		kp_ack_data.protocol_id = PROTOCOL_ID_IDE;
		kp_ack_data.header1 = key_prg_data->header.header1;

		write_to_rmb(sizeof(struct ide_km_data_object), &kp_ack_data);

		break;

	case ID_K_SET_GO:
		printf("3-2: K_SET_GO Received\n");
		/* STEP 3-2-1: Ready to receive traffic a given stream in a given Key Set */
		bool flag = true;
		struct ide_km_data_object *k_set_go_data = (struct ide_km_data_object *)(src_addr);

		received_key_set_go[k_set_go_data->rxtx][k_set_go_data->sub_stream] = true;

		/* STEP 3-2-2: Check if K_SET_GO received for all sub-stream */
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (!received_key_set_go[i][j]) {
					flag = false;
					break;
				}
			}
		}

		/* STEP 3-2-3: Enable IDE stream or key swap */
		if (flag) {
			/* Clear key_set_go flags */
			memset(received_key_set_go, 0, sizeof(received_key_set_go));

			if (ide_disable) {
				/* Enable IDE */
				struct pcie_epc *epc = pcie_get_epc();
				struct pcie_ide_cfg ide_cfg;

				ide_cfg.enable_tbit = true;
				ide_cfg.is_link_stream = true;
				pcie_ide_setup(epc, &ide_cfg);
				pcie_ide_enable_stream(epc, true, STREAM_ID);
				ide_disable = false;
				printf("STEP 3-2-3: IDE Stream Enabled!!!!\n");
			} else {
				/* Swap the key set */
				struct pcie_epc *epc = pcie_get_epc();

				pcie_ide_swap_key(epc, true, k_set_go_data->key_set);
				printf("STEP 3-2-3: Key swaped!!!!\n");
			}
		}

		/* STEP 3-2-4: Send K_GOSTOP_ACK to Host */
		printf("3-2-4: Send K_GOSTOP_ACK to Host");
		struct ide_km_data_object k_gostop_ack_data = {0,};

		k_gostop_ack_data.object_id = ID_K_GOSTOP_ACK;
		k_gostop_ack_data.protocol_id = PROTOCOL_ID_IDE;
		k_gostop_ack_data.header1 = k_set_go_data->header1;

		write_to_rmb(sizeof(struct ide_km_data_object), &k_gostop_ack_data);

		break;

	default:
		printf("Object ID invalid\n");
		return RL_ERROR;
	}

	printf("\n\n");

	return RL_OK;
}

uint8_t test_pcie_ide_key_mg(int argc, char *argv[])
{
	struct pcie_epc *epc = pcie_get_epc();
	struct dw_pcie_drv *data = epc->drv;
	uint32_t loop_num = TIMES_KEY_PROG + TIMES_KEY_PROG + TIMES_KEY_SET_GO; /* Initial Key + Backup Key + K_set_go */

	if (argc)
		loop_num = strtoul(argv[0], NULL, 0);

	while (loop_num--) {
		/* Parse Message Data */
		parse_doe_data(data->doe_fifo_addr);
	}

	return true;
}

CLI_REGISTER(test_ide, NULL, test_pcie_ide_key_mg, NULL);
