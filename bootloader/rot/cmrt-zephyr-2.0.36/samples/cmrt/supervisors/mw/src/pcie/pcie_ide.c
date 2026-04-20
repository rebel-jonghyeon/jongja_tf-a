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

#include <drivers/cmrt/sac.h>
#include <rebel_h.h>
#include <stdio.h>
#include <ipm_samsung.h>
#include "pcie_ide.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(pcie_ide, CONFIG_CMRT_LOG_LEVEL);

#define SKIP_KEY_INSERT 0

/* Temporary Keys for the test.
 * The TX and RX keys here are matched with the XTOR's RX and TX keys.
 * Update XTOR's key, if update below keys.
 */
struct key_prog_data_object tx[3] = {
	KEY_PROG(STREAM_ID, KEY_SET_0, RXTXB_TX, SUB_STREAM_0, 0,
			 0x22222222, 0x22222222, 0x22222222, 0x22222222,
			 0x22222222, 0x22222222, 0x22222222, 0x22222222,
			 0x44444444, 0x44444444),
	KEY_PROG(STREAM_ID, KEY_SET_0, RXTXB_TX, SUB_STREAM_1, 0,
			 0x66666666, 0x66666666, 0x66666666, 0x66666666,
			 0x66666666, 0x66666666, 0x66666666, 0x66666666,
			 0x88888888, 0x88888888),
	KEY_PROG(STREAM_ID, KEY_SET_0, RXTXB_TX, SUB_STREAM_2, 0,
			 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa,
			 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa,
			 0xcccccccc, 0xcccccccc),
};

struct key_prog_data_object rx[3] = {
	KEY_PROG(STREAM_ID, KEY_SET_0, RXTXB_RX, SUB_STREAM_0, 0,
			 0x11111111, 0x11111111, 0x11111111, 0x11111111,
			 0x11111111, 0x11111111, 0x11111111, 0x11111111,
			 0x33333333, 0x33333333),
	KEY_PROG(STREAM_ID, KEY_SET_0, RXTXB_RX, SUB_STREAM_1, 0,
			 0x55555555, 0x55555555, 0x55555555, 0x55555555,
			 0x55555555, 0x55555555, 0x55555555, 0x55555555,
			 0x77777777, 0x77777777),
	KEY_PROG(STREAM_ID, KEY_SET_0, RXTXB_RX, SUB_STREAM_2, 0,
			 0x99999999, 0x99999999, 0x99999999, 0x99999999,
			 0x99999999, 0x99999999, 0x99999999, 0x99999999,
			 0xbbbbbbbb, 0xbbbbbbbb),
};

int32_t pcie_ide_key_claer(bool is_tx)
{
	int i;
	uint64_t base;

	if (is_tx) {
		base = PCIE_IDE_AES_TX_BASE;
	} else {
		base = PCIE_IDE_AES_RX_BASE;
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base));
	for (i = 0; i < KEY_DW_SIZE; i++) {
		cmrt_sac_write32(0, GET_SAC_OFFSET(base + AES_KEY_0 + (i * 4)));
	}

	cmrt_sac_write32(0, GET_SAC_OFFSET(base + AES_INITIAL_IV_LSW));
	cmrt_sac_write32(0, GET_SAC_OFFSET(base + AES_INITIAL_IV_MSW));

	return 0;
}

static int32_t pcie_ide_insert_key(struct key_prog_data_object *obj)
{
	uint64_t base;
	uint32_t ctrl;
	int i;
	uint8_t idx = obj->header.sub_stream + INITIAL_LS_PR_IDX;

	if (obj->header.rxtx)
		base = PCIE_IDE_AES_TX_BASE;
	else
		base = PCIE_IDE_AES_RX_BASE;

	if (obj->header.key_set) {
		idx += BACKUP_OFFSET_IDX;
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base));
	for (i = 0; i < KEY_DW_SIZE; i++) {
		cmrt_sac_write32(obj->key_dw[KEY_DW_SIZE - (i + 1)],
						 GET_SAC_OFFSET(base + AES_KEY_0 + (i * 4)));
	}

	cmrt_sac_write32(obj->ifv_dw0, GET_SAC_OFFSET(base + AES_INITIAL_IV_LSW));
	cmrt_sac_write32(obj->ifv_dw1, GET_SAC_OFFSET(base + AES_INITIAL_IV_MSW));

	ctrl = cmrt_sac_read32(GET_SAC_OFFSET(base + AES_CTRL));
	ctrl &= ~AES_CTRL_CTX_IDX_MASK;
	ctrl |= idx;
	cmrt_sac_write32(ctrl, GET_SAC_OFFSET(base + AES_CTRL));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base + AES_STAT));
	while (cmrt_sac_read32(GET_SAC_OFFSET(base + AES_STAT)) & BIT(0))
		;

	LOG_INF("done key insert 0x%x", ctrl);

	return 0;
}

#if SKIP_KEY_INSERT
static void check_pcie_enabled(void)
{
	cmrt_sac_set_base(NULL, GET_SAC_BASE(SFR_SMLH_LTSSM_STATE));
	uint32_t data = cmrt_sac_read32(GET_SAC_OFFSET(SFR_SMLH_LTSSM_STATE));

	LOG_INF("Wait PCIe LTSSM L0 STATE");
	do {
		cmrt_sac_set_base(NULL, GET_SAC_BASE(SFR_SMLH_LTSSM_STATE));
		data = cmrt_sac_read32(GET_SAC_OFFSET(SFR_SMLH_LTSSM_STATE));
	} while ((data & LTSSM_STATE_MASK) != LTSSM_STATE_L0);
}

static int32_t pcie_ide_program_key(void)
{
	int32_t i;

	check_pcie_enabled();

	for (i = 0; i < 3; i++) {
		pcie_ide_insert_key(&tx[i]);
		pcie_ide_insert_key(&rx[i]);
	}

	return 0;
}
#endif /* SKIP_KEY_INSERT */

static void pcie_mailbox_cb(const struct device *ipmdev, const int chan)
{
	struct ipm_samsung_api *api = (struct ipm_samsung_api *)ipmdev->api;
	uint32_t obj_id;

	LOG_INF("Enter %s chan: %d", __func__, chan);

	api->receive(ipmdev, &obj_id, sizeof(obj_id), 0);
	obj_id = OBJ_ID_FROM_DW(obj_id);

	if (obj_id == ID_KEY_PROG) {
		struct key_prog_data_object data;

		api->receive(ipmdev, &data, sizeof(struct key_prog_data_object), 0);

		/* Install KEY */
		pcie_ide_insert_key(&data);
	}

	/* Send Done */
	const struct device *d = device_get_binding("MAILBOX_M2");
	cmrt_sac_set_base(NULL, GET_SAC_BASE(SYSREG_SYSREMAP + CHIPLET_ID));
	uint32_t target_id = cmrt_sac_read32(GET_SAC_OFFSET(SYSREG_SYSREMAP + CHIPLET_ID));

	api->write(d, target_id, "done", sizeof("done") - 1, 0);
	api->send(d, target_id, PCIE_IDE_FROM_ROT_CHANNEL, CPU1);
}

static int register_m7_mailbox(void)
{
	const char *label = "MAILBOX_M2";
	const struct device *d = device_get_binding(label);

	if (!d) {
		LOG_INF("Missing %s ------------- %s", label, __func__);
		return -ENXIO;
	}

	struct ipm_samsung_api *api = (struct ipm_samsung_api *)d->api;

	if (!api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d, __func__);
		return -EFAULT;
	}

	LOG_INF("%s(%s)", __func__, label);
	api->register_callback(d, pcie_mailbox_cb);

	return 0;
}

void pcie_ide_init(void)
{
#if SKIP_KEY_INSERT
	pcie_ide_program_key();
#endif /* SKIP_KEY_INSERT */
	register_m7_mailbox();
}
