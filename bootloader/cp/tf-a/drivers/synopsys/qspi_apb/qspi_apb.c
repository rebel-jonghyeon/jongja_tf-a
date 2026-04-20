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
#include <drivers/synopsys/qspi_apb.h>
#include <string.h>
#include <stddef.h>
#include <platform_def.h>
#include <common/debug.h>

#ifndef MHZ
#define MHZ					(1000000)
#endif
#define TARGET_SCLK_OUT		(5 * MHZ)
#define SSI_CLK_FREQ		(250 * MHZ)
#define SSI_BAUDR			(SSI_CLK_FREQ / TARGET_SCLK_OUT)

#define QSPI0_PERI_CP_BASE_ADDR (QSPI0_PERI0)
#define QSPI1_PERI_CP_BASE_ADDR (QSPI1_PERI0)

#define QSPI_NUMBER_OF_CHANNELS		(2)

struct qspi_apb_config qspi_apb_cfg[QSPI_NUMBER_OF_CHANNELS] = {
	{
		.regs = (struct qspi_apb_regs *)QSPI0_PERI_CP_BASE_ADDR,
		.configured = 0,
	},
	{
		.regs = (struct qspi_apb_regs *)QSPI1_PERI_CP_BASE_ADDR,
		.configured = 0,
	}
};

static void qspi_apb_set_configured(uint32_t ch_num)
{
	if (ch_num < QSPI_NUMBER_OF_CHANNELS)
		qspi_apb_cfg[ch_num].configured = 1;
}

static void qspi_apb_int_disable(uint32_t ch_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	regs->imr = DW_APB_SPI_IMR_MASK;
}

static void qspi_apb_disable(uint32_t ch_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	regs->ssienr = DW_APB_SPI_SSIENR_DISABLE;
}

static void qspi_apb_enable(uint32_t ch_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	regs->ssienr = DW_APB_SPI_SSIENR_ENABLE;
}

static void qspi_apb_wait_busy_state(uint32_t ch_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t count = 0;

	while (!(regs->sr & DW_APB_SPI_SR_BUSY_MASK)) {
		/* TODO: Tune the delay count */
		if (count++ > DW_APB_SPI_DEFAULT_DELAY_COUNT)
			break;
	}
}

static void qspi_apb_wait_idle(uint32_t ch_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	while (regs->sr & DW_APB_SPI_SR_BUSY_MASK)
		;
}

static void qspi_apb_ser_enable(uint32_t ch_num, uint32_t slave_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t reg_data;

	qspi_apb_wait_idle(ch_num);

	reg_data = regs->ser;
	reg_data |= BIT(slave_num);
	regs->ser = reg_data;
}

static void qspi_apb_ser_disable(uint32_t ch_num, uint32_t slave_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t reg_data;

	reg_data = regs->ser;
	reg_data &= ~BIT(slave_num);
	regs->ser = reg_data;
}

void qspi_apb_config_standard_ssi_controller(uint32_t ch_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t ctrlr0_val;

	ctrlr0_val = DW_APB_SPI_CTRLR0_DFS_8;
	ctrlr0_val |= DW_APB_SPI_CTRLR0_TMOD_TX;
	ctrlr0_val |= DW_APB_SPI_CTRLR0_SPI_FRF_STANDARD;
	regs->ctrlr0 = ctrlr0_val;

	regs->spi_ctrlr0 = DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE_TT0;

	regs->txftlr = DW_APB_SPI_TXFTLR_0WORD;

	regs->baudr = (uint32_t)(SSI_BAUDR);
	regs->ctrlr1 = DW_APB_SPI_CTRLR1_NDF_1WORD;
	regs->mwcr = 0;
	regs->rxftlr = 0;
}

void qspi_apb_config_ssi_controller(uint32_t ch_num, uint32_t dfs, uint32_t sel_txrx,
									uint32_t spi_frf, uint32_t inst_l, uint32_t addr,
									uint32_t trans_type, uint32_t wait_cycle, uint32_t ndf)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t ctrlr0_val;
	uint32_t spi_ctrlr0_val;

	qspi_apb_disable(ch_num);

	ctrlr0_val = dfs;
	ctrlr0_val |= sel_txrx;
	ctrlr0_val |= spi_frf;
	regs->ctrlr0 = ctrlr0_val;

	spi_ctrlr0_val = inst_l;
	spi_ctrlr0_val |= addr;
	spi_ctrlr0_val |= trans_type;
	spi_ctrlr0_val |= SPI_SET_WAIT_CYCLES(wait_cycle);
	regs->spi_ctrlr0 = spi_ctrlr0_val;

	regs->txftlr = DW_APB_SPI_TXFTLR_0WORD;

	regs->baudr = (uint32_t)(SSI_BAUDR);
	regs->ctrlr1 = ndf;
	regs->mwcr = 0;
	regs->rxftlr = 0;

	qspi_apb_enable(ch_num);
}

uint32_t qspi_apb_enhance_rx_i_d_once(uint32_t ch_num, uint32_t inst)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t ret;
	uint32_t fifo_level;

	qspi_apb_ser_enable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	regs->drx[0] = inst;

	qspi_apb_wait_idle(ch_num);

	fifo_level = 0;

	while (!(fifo_level == 1))
		fifo_level = regs->rxflr;

	ret = regs->drx[0];

	qspi_apb_ser_disable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	return ret;
}

void qspi_apb_enhance_tx_i_d_once(uint32_t ch_num, uint32_t inst, uint32_t data)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	qspi_apb_ser_enable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	regs->drx[0] = inst;
	regs->drx[0] = data;

	qspi_apb_wait_busy_state(ch_num);
	qspi_apb_wait_idle(ch_num);

	qspi_apb_ser_disable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);
}

void qspi_apb_enhance_tx_d_once(uint32_t ch_num, uint32_t inst)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	qspi_apb_ser_enable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	regs->drx[0] = inst;

	qspi_apb_wait_busy_state(ch_num);
	qspi_apb_wait_idle(ch_num);

	qspi_apb_ser_disable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);
}

uint32_t qspi_apb_enhance_rx_i_a_d_once(uint32_t ch_num, uint32_t inst, uint32_t addr)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t ret;
	uint32_t fifo_level;

	qspi_apb_ser_enable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	regs->drx[0] = inst;
	regs->drx[0] = addr;

	qspi_apb_wait_idle(ch_num);

	fifo_level = 0;

	while (!(fifo_level == 1))
		fifo_level = regs->rxflr;

	ret = regs->drx[0];

	qspi_apb_ser_disable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	return ret;
}

void qspi_apb_enhance_tx_i_once(uint32_t ch_num, uint32_t inst)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	qspi_apb_ser_enable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	regs->drx[0] = inst;

	qspi_apb_wait_busy_state(ch_num);
	qspi_apb_wait_idle(ch_num);

	qspi_apb_ser_disable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);
}

void qspi_apb_enhance_tx_i_a_once(uint32_t ch_num, uint32_t inst, uint32_t addr)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	qspi_apb_ser_enable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	regs->drx[0] = inst;
	regs->drx[0] = addr;

	qspi_apb_wait_busy_state(ch_num);
	qspi_apb_wait_idle(ch_num);

	qspi_apb_ser_disable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);
}

void qspi_apb_enhance_tx_i_a_d_once(uint32_t ch_num, uint32_t inst,
									uint32_t addr, uint32_t data)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	qspi_apb_ser_enable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	regs->drx[0] = inst;
	regs->drx[0] = addr;
	regs->drx[0] = data;

	qspi_apb_wait_busy_state(ch_num);
	qspi_apb_wait_idle(ch_num);

	qspi_apb_ser_disable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);
}

void qspi_apb_std_tx_rx_d_multiple(uint32_t ch_num,
								   uint32_t *rx_data, uint32_t *tx_data,
								   uint32_t rx_num, uint32_t tx_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t i;
	uint32_t rxflr_val;
	uint32_t *ptrtxdata = tx_data;
	uint32_t *ptrrxdata = rx_data;

	qspi_apb_ser_enable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	for (i = 0; i < tx_num; i++)
		regs->drx[0] = ptrtxdata[i];

	for (i = 0; i < rx_num; i++)
		regs->drx[0] = 0;

	qspi_apb_wait_idle(ch_num);

	rxflr_val = 0;
	while (rxflr_val < rx_num + tx_num)
		rxflr_val = regs->rxflr;

	for (i = 0; i < tx_num; i++)
		regs->drx[0];

	for (i = 0; i < rx_num; i++)
		ptrrxdata[i] = regs->drx[0];

	qspi_apb_ser_disable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);
}

void qspi_apb_std_tx_d_multiple(uint32_t ch_num, uint32_t *tx_data, uint32_t tx_num)
{
	volatile struct qspi_apb_regs *regs = qspi_apb_cfg[ch_num].regs;

	qspi_apb_ser_enable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);

	for (uint32_t i = 0; i < tx_num; i++)
		regs->drx[0] = *tx_data++;

	qspi_apb_wait_busy_state(ch_num);
	qspi_apb_wait_idle(ch_num);

	qspi_apb_ser_disable(ch_num, DW_APB_SPI_DEFAULT_SLAVE);
}

int qspi_apb_init(void)
{
	uint32_t ch_num;

	for (ch_num = 0; ch_num < QSPI_NUMBER_OF_CHANNELS; ch_num++) {
		qspi_apb_disable(ch_num);
		qspi_apb_int_disable(ch_num);
		qspi_apb_config_standard_ssi_controller(ch_num);
		qspi_apb_set_configured(ch_num);
		qspi_apb_enable(ch_num);
	}

	return 0;
}
