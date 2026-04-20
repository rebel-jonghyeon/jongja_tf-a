/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */
#include <lib/libc/stdint.h>
#include <stddef.h>
#include <platform_def.h>
#include <lib/mmio.h>
#include <drivers/synopsys/qspi_boot.h>

#include <string.h>
#include <common/debug.h>

#define QSPI_BOOT_PERI_CP_BASE_ADDR			(QSPI_ROT_PRIVATE)

#define BUSY								(1)
#define IDLE								(0)
#define SSI_CLK_DIV_24						(0x18 >> 1)

#define NOR_CMD_DTR_QUAD_FAST_READ			(0xed)
#define NOR_CMD_QAUD_IO_WORD_READ			(0xe7)
#if (ZEBU == 1)
#define QSPI_BOOT_INCR_OPCODE				(NOR_CMD_DTR_QUAD_FAST_READ)
#define QSPI_BOOT_WRAP_OPCODE				(NOR_CMD_DTR_QUAD_FAST_READ)
#else
#define QSPI_BOOT_INCR_OPCODE				(NOR_CMD_QAUD_IO_WORD_READ)
#define QSPI_BOOT_WRAP_OPCODE				(NOR_CMD_QAUD_IO_WORD_READ)
#endif

#define FRAME_FORMAT_SPI_QUAD				(0x2)
#define INST_STANDARD_ADDR_FRF				(0x1)
#define LENGTH_OF_ADDR_24BIT				(0x6)
#define LENGTH_OF_INST_8BIT					(0x2)
#define WAIT_CYCLE_4						(0x4)
#define FIX_DFS_FOR_XIP_TX					(0x1)
#define XIP_MODE_8BIT						(0x2)

#define QSPI_TX_FIFO_WAIT_LEVEL				(28)

#define QSPI_BOOT_DEFAULT_SLAVE				(0)

static struct dwc_ssi_config qspi_boot_cfg = {
	.reg_base = (struct dwc_ssi *)QSPI_BOOT_PERI_CP_BASE_ADDR,
};

void qspi_boot_enable(uint32_t en)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;

	qspi_boot_reg->ssienr.ssic_en = en;
}

void qspi_boot_config(void)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;

	qspi_boot_enable(DISEN);

	qspi_boot_reg->baudr.sckdv = SSI_CLK_DIV_24;

	qspi_boot_reg->xip_incr_inst.incr_inst = QSPI_BOOT_INCR_OPCODE;
	qspi_boot_reg->xip_wrap_inst.wrap_inst = QSPI_BOOT_WRAP_OPCODE;

	qspi_boot_reg->xip_ctrl.frf = FRAME_FORMAT_SPI_QUAD;
	qspi_boot_reg->xip_ctrl.trans_type = INST_STANDARD_ADDR_FRF;
	qspi_boot_reg->xip_ctrl.addr_l = LENGTH_OF_ADDR_24BIT;
	qspi_boot_reg->xip_ctrl.inst_l = LENGTH_OF_INST_8BIT;
	qspi_boot_reg->xip_ctrl.dfs_hc = FIX_DFS_FOR_XIP_TX;
	qspi_boot_reg->xip_ctrl.ddr_en = DISEN;
	qspi_boot_reg->xip_ctrl.inst_en = EN;
	qspi_boot_reg->xip_ctrl.cont_xfer_en = DISEN;
	qspi_boot_reg->xip_ctrl.wait_cycles = WAIT_CYCLE_4;

	qspi_boot_reg->xip_ctrl.xip_mbl = XIP_MODE_8BIT;
	qspi_boot_reg->ctrlr0.spi_frf = QSPI_BOOT_CTRLR0_SPI_FRF_QSPI;
	qspi_boot_reg->ctrlr0.dfs = QSPI_BOOT_CTRLR0_DFS_32;

	qspi_boot_enable(EN);
}

#ifndef MHZ
#define MHZ	(1000000)
#endif

#define TARGET_SCLK_OUT		(5 * MHZ)
#define SSI_CLK_FREQ		(500 * MHZ)
#define SSI_BAUDR			(SSI_CLK_FREQ / TARGET_SCLK_OUT)

static void qspi_boot_wait_busy_state(void)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;
	uint32_t count = 0;

	while (!(qspi_boot_reg->sr.busy & BUSY)) {
		/* TODO: Tune the delay count */
		if (count++ > QSPI_BOOT_DEFAULT_DELAY_COUNT)
			break;
	}
}

static void qspi_boot_wait_idle(void)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;

	while (qspi_boot_reg->sr.busy & BUSY)
		;
}

static void qspi_boot_ser_enable(void)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;
	uint32_t reg_data;

	qspi_boot_wait_idle();

	reg_data = qspi_boot_reg->ser.val;
	reg_data |= BIT(QSPI_BOOT_DEFAULT_SLAVE);
	qspi_boot_reg->ser.val = reg_data;
}

static void qspi_boot_ser_disable(void)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;
	uint32_t reg_data;

	reg_data = qspi_boot_reg->ser.val;
	reg_data &= ~BIT(QSPI_BOOT_DEFAULT_SLAVE);
	qspi_boot_reg->ser.val = reg_data;
}

void qspi_boot_std_tx_d_multiple(uint32_t *tx_data, uint32_t tx_num)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;

	qspi_boot_ser_enable();

	for (uint32_t i = 0; i < tx_num; i++)
		qspi_boot_reg->dr0.dr = *tx_data++;

	qspi_boot_wait_busy_state();
	qspi_boot_wait_idle();

	qspi_boot_ser_disable();
}

uint32_t qspi_boot_enhance_rx_i_d_once(uint32_t inst)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;
	uint32_t ret;
	uint32_t fifo_level;

	qspi_boot_ser_enable();

	qspi_boot_reg->dr0.dr = inst;

	qspi_boot_wait_idle();

	fifo_level = 0;

	while (!(fifo_level == 1))
		fifo_level = qspi_boot_reg->rxflr.rxtfl;

	ret = qspi_boot_reg->dr0.dr;

	qspi_boot_ser_disable();

	return ret;
}

uint32_t qspi_boot_enhance_rx_i_d_two(uint32_t inst)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;
	uint32_t ret, ret1;
	uint32_t fifo_level;

	qspi_boot_ser_enable();

	qspi_boot_reg->dr0.dr = inst;

	qspi_boot_wait_idle();

	fifo_level = 0;

	while (!(fifo_level == 2))
		fifo_level = qspi_boot_reg->rxflr.rxtfl;

	ret = qspi_boot_reg->dr0.dr;
	ret1 = qspi_boot_reg->dr0.dr;

	ret |= (ret1 << 8);

	qspi_boot_ser_disable();

	return ret;
}

void qspi_boot_std_tx_rx_d_multiple(uint32_t *rx_data, uint32_t *tx_data,
									uint32_t rx_num, uint32_t tx_num)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;
	uint32_t i;
	uint32_t rxflr_val;
	uint32_t *ptrtxdata = tx_data;
	uint32_t *ptrrxdata = rx_data;

	qspi_boot_ser_enable();

	for (i = 0; i < tx_num; i++)
		qspi_boot_reg->dr0.dr = ptrtxdata[i];

	for (i = 0; i < rx_num; i++)
		qspi_boot_reg->dr0.dr = 0;

	/* TOOD: may need to wait for the busy state before waiting for idle flag */
	qspi_boot_wait_idle();

	rxflr_val = 0;
	while (rxflr_val < rx_num + tx_num)
		rxflr_val = qspi_boot_reg->rxflr.rxtfl;

	for (i = 0; i < tx_num; i++)
		qspi_boot_reg->dr0.dr;

	for (i = 0; i < rx_num; i++)
		ptrrxdata[i] = qspi_boot_reg->dr0.dr;

	qspi_boot_ser_disable();
}

void qspi_boot_config_controller(uint32_t dfs, uint32_t sel_txrx,
								 uint32_t spi_frf, uint32_t inst_l, uint32_t addr,
								 uint32_t trans_type, uint32_t wait_cycle, uint32_t ndf)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;

	qspi_boot_enable(DISEN);

	qspi_boot_reg->ctrlr0.dfs = dfs;
	qspi_boot_reg->ctrlr0.tmod = sel_txrx;
	qspi_boot_reg->ctrlr0.spi_frf = spi_frf;

	qspi_boot_reg->spi_ctrlr0.inst_l = inst_l;
	qspi_boot_reg->spi_ctrlr0.addr_l = addr;
	qspi_boot_reg->spi_ctrlr0.trans_type = trans_type;
	qspi_boot_reg->spi_ctrlr0.wait_cycles = wait_cycle;

	qspi_boot_reg->txftlr.tft = QSPI_BOOT_TXFTLR_0WORD;

	qspi_boot_reg->baudr.sckdv = (uint32_t)(SSI_BAUDR) >> 1;
	qspi_boot_reg->ctrlr1.ndf = ndf;
	qspi_boot_reg->mwcr.val = 0;
	qspi_boot_reg->rxftlr.rft = 0;

	qspi_boot_enable(EN);
}

void qspi_boot_config_for_flash(uint32_t dfs, uint32_t sel_txrx,
								uint32_t spi_frf, uint32_t inst_l, uint32_t addr,
								uint32_t trans_type, uint32_t wait_cycle, uint32_t ndf)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;

	qspi_boot_enable(DISEN);

	qspi_boot_reg->ctrlr0.dfs = dfs;
	qspi_boot_reg->ctrlr0.tmod = sel_txrx;
	qspi_boot_reg->ctrlr0.spi_frf = spi_frf;

	qspi_boot_reg->spi_ctrlr0.inst_l = inst_l;
	qspi_boot_reg->spi_ctrlr0.addr_l = addr;
	qspi_boot_reg->spi_ctrlr0.trans_type = trans_type;
	qspi_boot_reg->spi_ctrlr0.wait_cycles = wait_cycle;

	qspi_boot_reg->txftlr.tft = QSPI_BOOT_TXFTLR_0WORD;

	qspi_boot_reg->baudr.sckdv = (uint32_t)(SSI_BAUDR) >> 1;
	qspi_boot_reg->ctrlr1.ndf = ndf;
	qspi_boot_reg->mwcr.val = 0;
	qspi_boot_reg->rxftlr.rft = 0;

	qspi_boot_enable(EN);
}

void qspi_boot_enhance_tx_i_once(uint32_t inst)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;

	qspi_boot_ser_enable();

	qspi_boot_reg->dr0.dr = inst;

	qspi_boot_wait_busy_state();
	qspi_boot_wait_idle();

	qspi_boot_ser_disable();
}

void qspi_boot_enhance_tx_i_a_once(uint32_t inst, uint32_t addr)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;

	qspi_boot_ser_enable();

	qspi_boot_reg->dr0.dr = inst;
	qspi_boot_reg->dr0.dr = addr;

	qspi_boot_wait_busy_state();
	qspi_boot_wait_idle();

	qspi_boot_ser_disable();
}

void qspi_boot_enhance_tx_i_a_d_once(uint32_t inst, uint32_t addr, uint32_t data)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;

	qspi_boot_ser_enable();

	qspi_boot_reg->dr0.dr = inst;
	qspi_boot_reg->dr0.dr = addr;
	qspi_boot_reg->dr0.dr = data;

	qspi_boot_wait_busy_state();
	qspi_boot_wait_idle();

	qspi_boot_ser_disable();
}

void qspi_boot_enhance_tx_i_a_d_256(uint32_t inst, uint32_t addr, uint32_t *data)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;
	uint32_t *data32 = (uint32_t *)data;

	qspi_boot_ser_enable();

	qspi_boot_reg->dr0.dr = inst;
	qspi_boot_reg->dr0.dr = addr;

	for (int i = 0; i < 64; i++) {
		qspi_boot_reg->dr0.dr = *data32++;

		while (qspi_boot_reg->txflr.txtfl > QSPI_TX_FIFO_WAIT_LEVEL)
			;
	}

	qspi_boot_wait_busy_state();
	qspi_boot_wait_idle();

	qspi_boot_ser_disable();
}

void qspi_boot_enhance_tx_i_a_d_size(uint32_t inst, uint32_t addr, uint32_t *data, uint32_t size)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;
	uint32_t *data32 = (uint32_t *)data;
	uint32_t wordsize = size >> 2;

	qspi_boot_ser_enable();

	qspi_boot_reg->dr0.dr = inst;
	qspi_boot_reg->dr0.dr = addr;

	for (int i = 0; i < wordsize; i++) {
		qspi_boot_reg->dr0.dr = *data32++;

		while (qspi_boot_reg->txflr.txtfl > QSPI_TX_FIFO_WAIT_LEVEL)
			;
	}

	qspi_boot_wait_busy_state();
	qspi_boot_wait_idle();

	qspi_boot_ser_disable();
}

uint32_t qspi_boot_enhance_rx_i_a_d_once(uint32_t inst, uint32_t addr)
{
	volatile struct dwc_ssi *qspi_boot_reg = qspi_boot_cfg.reg_base;
	uint32_t ret;
	uint32_t fifo_level;

	qspi_boot_ser_enable();

	qspi_boot_reg->dr0.dr = inst;
	qspi_boot_reg->dr0.dr = addr;

	qspi_boot_wait_idle();

	fifo_level = 0;

	while (!(fifo_level == 1))
		fifo_level = qspi_boot_reg->rxflr.rxtfl;

	ret = qspi_boot_reg->dr0.dr;

	qspi_boot_ser_disable();

	return ret;
}
