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

#pragma once

#define MB_RECEIVED_KEY_INSERT_DONE (0xCBCBCBCB)

#define IDE_CFG_S0_PR BIT(0)
#define IDE_CFG_S0_NPR BIT(1)
#define IDE_CFG_S0_CPL BIT(2)

struct pcie_ide_cfg {
	bool is_link_stream; /* link stream or selective stream */
	bool enable_tbit;
};

int32_t pcie_ide_setup(struct pcie_epc *epc, struct pcie_ide_cfg *ide_cfg);
int32_t pcie_ide_enable_stream(struct pcie_epc *epc, bool is_link_stream, uint8_t stream_id);
int32_t pcie_ide_swap_key(struct pcie_epc *epc, bool is_link_stream, uint8_t new_key);
