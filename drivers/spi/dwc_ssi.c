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
#include <stdint.h>
#include "dwc_ssi.h"

static void dwc_ssi_enable(volatile struct dwc_ssi *dwc_ssi, bool en)
{
	if (en)
		dwc_ssi->ssienr.ssic_en = EN;
	else
		dwc_ssi->ssienr.ssic_en = DISEN;
}

void dwc_ssi_set_buadrate(volatile struct dwc_ssi *dwc_ssi, uint32_t div)
{
	dwc_ssi_enable(dwc_ssi, DISEN);
	dwc_ssi->baudr.val = div;
	dwc_ssi_enable(dwc_ssi, EN);
}

void dwc_ssi_set_xip_cmd(volatile struct dwc_ssi *dwc_ssi, bool rw, uint16_t cmd)
{
	dwc_ssi_enable(dwc_ssi, DISEN);

	if (rw == XIP_READ) {
		dwc_ssi->xip_incr_inst.incr_inst = cmd;
		dwc_ssi->xip_wrap_inst.wrap_inst = cmd;

	} else if (rw == XIP_WRITE) {
		dwc_ssi->xip_write_incr_inst.incr_write_inst = cmd;
		dwc_ssi->xip_write_wrap_inst.wrap_write_inst = cmd;
	}

	dwc_ssi_enable(dwc_ssi, EN);
}

void dwc_ssi_set_xip_ctrl(volatile struct dwc_ssi *dwc_ssi, uint32_t ctrl)
{
	uint32_t val;

	dwc_ssi_enable(dwc_ssi, DISEN);

	val = dwc_ssi->xip_ctrl.val;
	val &= ~DUMMY_MASK;
	val |= ctrl;
	dwc_ssi->xip_ctrl.val = val;

	dwc_ssi_enable(dwc_ssi, EN);
}
