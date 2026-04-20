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

#include "pcie_dw.h"
#include "pcie_dw_hdma.h"
#include "pcie_sysreg.h"
#include "sysreg_buscsr_pcie_register.h"
#include "pcie_rebelh.h"

void set_hdma_lut(struct pcie_epc *epc, uint32_t ch, uint32_t sid, uint32_t ssid, uint32_t ssidv)
{
	struct dw_pcie_config *cfg = epc->cfg;

	volatile struct sysreg_buscsr_pcie_register *sysreg_buscsr_base = cfg->sysreg_buscsr_base;

	/* NOTE
	 * Assume that,
	 * 1) write channel 0 and read channel 16 are used for non-linked list mode.
	 * 2) write channel 1 ~ 15 and read channel 17 ~ 31 are used for linked list mode.
	 */
	if (ch == HDMA_WRITE_CH0 || ch == HDMA_READ_CH0) {
		sysreg_buscsr_base->sm_hdma_sid_lut0.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid = BIT(0);
	} else if (ch == HDMA_WRITE_CH1 || ch == HDMA_READ_CH1) {
		sysreg_buscsr_base->sm_hdma_sid_lut1.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(1);
	} else if (ch == HDMA_WRITE_CH2 || ch == HDMA_READ_CH2) {
		sysreg_buscsr_base->sm_hdma_sid_lut2.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(2);
	} else if (ch == HDMA_WRITE_CH3 || ch == HDMA_READ_CH3) {
		sysreg_buscsr_base->sm_hdma_sid_lut3.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(3);
	} else if (ch == HDMA_WRITE_CH4 || ch == HDMA_READ_CH4) {
		sysreg_buscsr_base->sm_hdma_sid_lut4.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(4);
	} else if (ch == HDMA_WRITE_CH5 || ch == HDMA_READ_CH5) {
		sysreg_buscsr_base->sm_hdma_sid_lut5.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(5);
	} else if (ch == HDMA_WRITE_CH6 || ch == HDMA_READ_CH6) {
		sysreg_buscsr_base->sm_hdma_sid_lut6.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(6);
	} else if (ch == HDMA_WRITE_CH7 || ch == HDMA_READ_CH7) {
		sysreg_buscsr_base->sm_hdma_sid_lut7.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(7);
	} else if (ch == HDMA_WRITE_CH8 || ch == HDMA_READ_CH8) {
		sysreg_buscsr_base->sm_hdma_sid_lut8.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(8);
	} else if (ch == HDMA_WRITE_CH9 || ch == HDMA_READ_CH9) {
		sysreg_buscsr_base->sm_hdma_sid_lut9.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(9);
	} else if (ch == HDMA_WRITE_CH10 || ch == HDMA_READ_CH10) {
		sysreg_buscsr_base->sm_hdma_sid_lut10.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(10);
	} else if (ch == HDMA_WRITE_CH11 || ch == HDMA_READ_CH11) {
		sysreg_buscsr_base->sm_hdma_sid_lut11.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(11);
	} else if (ch == HDMA_WRITE_CH12 || ch == HDMA_READ_CH12) {
		sysreg_buscsr_base->sm_hdma_sid_lut12.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(12);
	} else if (ch == HDMA_WRITE_CH13 || ch == HDMA_READ_CH13) {
		sysreg_buscsr_base->sm_hdma_sid_lut13.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(13);
	} else if (ch == HDMA_WRITE_CH14 || ch == HDMA_READ_CH14) {
		sysreg_buscsr_base->sm_hdma_sid_lut14.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(14);
	} else if (ch == HDMA_WRITE_CH15 || ch == HDMA_READ_CH15) {
		sysreg_buscsr_base->sm_hdma_sid_lut15.data = SET_HDMA_LUT(sid, ssid, ssidv);
		sysreg_buscsr_base->sm_hdma_sid_lut.valid |= BIT(15);
	}
}

void invalidate_hdma_lut(struct pcie_epc *epc, uint32_t ch)
{
	struct dw_pcie_config *cfg = epc->cfg;

	volatile struct sysreg_buscsr_pcie_register *sysreg_buscsr_base = cfg->sysreg_buscsr_base;

	if (ch == HDMA_WRITE_CH0 || ch == HDMA_READ_CH0) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(0);
	} else if (ch == HDMA_WRITE_CH1 || ch == HDMA_READ_CH1) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(1);
	} else if (ch == HDMA_WRITE_CH2 || ch == HDMA_READ_CH2) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(2);
	} else if (ch == HDMA_WRITE_CH3 || ch == HDMA_READ_CH3) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(3);
	} else if (ch == HDMA_WRITE_CH4 || ch == HDMA_READ_CH4) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(4);
	} else if (ch == HDMA_WRITE_CH5 || ch == HDMA_READ_CH5) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(5);
	} else if (ch == HDMA_WRITE_CH6 || ch == HDMA_READ_CH6) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(6);
	} else if (ch == HDMA_WRITE_CH7 || ch == HDMA_READ_CH7) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(7);
	} else if (ch == HDMA_WRITE_CH8 || ch == HDMA_READ_CH8) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(8);
	} else if (ch == HDMA_WRITE_CH9 || ch == HDMA_READ_CH9) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(9);
	} else if (ch == HDMA_WRITE_CH10 || ch == HDMA_READ_CH10) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(10);
	} else if (ch == HDMA_WRITE_CH11 || ch == HDMA_READ_CH11) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(11);
	} else if (ch == HDMA_WRITE_CH12 || ch == HDMA_READ_CH12) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(12);
	} else if (ch == HDMA_WRITE_CH13 || ch == HDMA_READ_CH13) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(13);
	} else if (ch == HDMA_WRITE_CH14 || ch == HDMA_READ_CH14) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(14);
	} else if (ch == HDMA_WRITE_CH15 || ch == HDMA_READ_CH15) {
		sysreg_buscsr_base->sm_hdma_sid_lut.valid &= ~BIT(15);
	}
}
