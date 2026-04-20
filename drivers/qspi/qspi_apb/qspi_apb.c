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
#include <stdint.h>
#include <driver.h>
#include <rebel_h_platform.h>
#include <qspi_apb.h>
#include "rl_errors.h"

#define TARGET_SCLK_AVSBUS		(1 * MHZ)
#define SSI_CLK_FREQ			(250 * MHZ)
#define AVS_SSI_BAUDR			(SSI_CLK_FREQ / TARGET_SCLK_AVSBUS)

#define QSPI0_PERI0_CP_BASE_ADDR (QSPI0_PERI0)
#define QSPI1_PERI0_CP_BASE_ADDR (QSPI1_PERI0)
#define QSPI0_PERI1_CP_BASE_ADDR (QSPI0_PERI1)
#define QSPI1_PERI1_CP_BASE_ADDR (QSPI1_PERI1)

#define QSPI_TEST_LOOPBACK			(0)

#define QSPI_NUMBER_OF_CHANNELS		(4)

struct qspi_apb_config qspi_apb_cfg[QSPI_NUMBER_OF_CHANNELS] = {
	{
		.regs = (struct dw_apb_ssi *)QSPI0_PERI0_CP_BASE_ADDR,
		.configured = 0,
	},
	{
		.regs = (struct dw_apb_ssi *)QSPI1_PERI0_CP_BASE_ADDR,
		.configured = 0,
	},
	{
		.regs = (struct dw_apb_ssi *)QSPI0_PERI1_CP_BASE_ADDR,
		.configured = 0,
	},
	{
		.regs = (struct dw_apb_ssi *)QSPI1_PERI1_CP_BASE_ADDR,
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
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;

	regs->imr.val = DW_APB_SSI_IMR_MASK;
}

static void qspi_apb_disable(uint32_t ch_num)
{
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;

	regs->ssienr.ssi_en = DW_APB_SSI_SSIENR_DISABLE;
}

static void qspi_apb_enable(uint32_t ch_num)
{
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;

	regs->ssienr.ssi_en = DW_APB_SSI_SSIENR_ENABLE;
}

static void qspi_apb_wait_busy_state(uint32_t ch_num)
{
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t count = 0;

	while (!(regs->sr.busy & DW_APB_SSI_SR_BUSY_MASK)) {
		/* TODO: Tune the delay count */
		if (count++ > DW_APB_SSI_DEFAULT_DELAY_COUNT)
			break;
	}
}

static void qspi_apb_wait_idle(uint32_t ch_num)
{
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;

	while (regs->sr.busy & DW_APB_SSI_SR_BUSY_MASK)
		;
}

static void qspi_apb_ser_enable(uint32_t ch_num, uint32_t slave_num)
{
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t reg_data;

	qspi_apb_wait_idle(ch_num);

	reg_data = regs->ser.ser;
	reg_data |= BIT(slave_num);
	regs->ser.ser = reg_data;
}

static void qspi_apb_ser_disable(uint32_t ch_num, uint32_t slave_num)
{
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t reg_data;

	reg_data = regs->ser.ser;
	reg_data &= ~BIT(slave_num);
	regs->ser.ser = reg_data;
}

void qspi_apb_enable_loopback(uint32_t ch_num)
{
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;

	qspi_apb_disable(ch_num);
	regs->ctrlr0.srl = 1;
	qspi_apb_enable(ch_num);
}

static void qspi_apb_set_default(uint32_t ch_num)
{
	qspi_apb_set(ch_num, DW_APB_SSI_CTRLR0_DFS_8, DW_APB_SSI_CTRLR0_TMOD_TX_RX,
				 DW_APB_SSI_CTRLR0_SPI_FRF_STANDARD, AVS_SSI_BAUDR);
}

void qspi_apb_set(uint32_t ch_num, uint32_t dfs, uint32_t sel_txrx, uint32_t spi_frf, uint32_t data_rate)
{
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;

	qspi_apb_disable(ch_num);

	regs->ctrlr0.dfs = dfs;
	regs->ctrlr0.tmod = sel_txrx;
	regs->ctrlr0.spi_frf = spi_frf;

	regs->spi_ctrlr0.inst_l = 0;
	regs->spi_ctrlr0.addr_l = 0;
	regs->spi_ctrlr0.trans_type = DW_APB_SSI_SPI_CTRLR0_TRANS_TYPE_TT2;
	regs->spi_ctrlr0.wait_cycles = 0;

	regs->txftlr.tft = DW_APB_SSI_TXFTLR_0WORD;

	regs->baudr.sckdv = data_rate;
	regs->ctrlr1.ndf = 0;
	regs->mwcr.val = 0;
	regs->rxftlr.rft = 0;

#if QSPI_TEST_LOOPBACK
	regs->ctrlr0.srl = 1;
#endif
	qspi_apb_enable(ch_num);
}

int qspi_apb_transfer(uint32_t ch_num,
					  uint8_t *tx_buf, uint32_t tx_ofs, uint32_t tx_len,
					  uint8_t *rx_buf, uint32_t rx_ofs, uint32_t rx_len)
{
	volatile struct dw_apb_ssi *regs = qspi_apb_cfg[ch_num].regs;
	uint32_t i;
	uint32_t tx_totlen = tx_len + tx_ofs;
	uint32_t rxflr_val;
	volatile uint32_t dummy;

#if QSPI_TEST_LOOPBACK
	printf("qspi_apb_transfer\n");
#endif

	qspi_apb_ser_enable(ch_num, DW_APB_SSI_DEFAULT_SLAVE);

	int flag = (tx_len == 0);

	flag ^= !tx_buf;
	if (flag)
		return RL_ERROR;

	flag = (rx_len == 0);
	flag ^= !rx_buf;
	if (flag)
		return RL_ERROR;

	for (i = 0; i < tx_ofs; i++)
		regs->dr0.dr = QSPI_APB_DUMMY_TX_ZERO;

	for (i = 0; i < tx_len; i++)
		regs->dr0.dr = *tx_buf++;

	for (i = 0; i < rx_len; i++)
		regs->dr0.dr = QSPI_APB_DUMMY_TX_FF;

	qspi_apb_wait_idle(ch_num);

	rxflr_val = 0;
	while (rxflr_val < tx_totlen + rx_len)
		rxflr_val = regs->rxflr.rxtfl;

	for (i = 0; i < rx_ofs; i++) {
		dummy = sys_read8((uint64_t)&regs->dr0.dr);
#if QSPI_TEST_LOOPBACK
		printf("rxflr = 0x%2x\n", regs->rxflr.rxtfl);
		printf("dummy = 0x%2x\n", dummy);
#endif
	}

	for (i = 0; i < rx_len; i++)
		*rx_buf++ = regs->dr0.dr;

	qspi_apb_ser_disable(ch_num, DW_APB_SSI_DEFAULT_SLAVE);

	return RL_OK;
}

int qspi_apb_init(void)
{
	uint32_t ch_num;

	for (ch_num = 0; ch_num < QSPI_NUMBER_OF_CHANNELS; ch_num++) {
		qspi_apb_disable(ch_num);
		qspi_apb_int_disable(ch_num);
		qspi_apb_set_default(ch_num);
		qspi_apb_set_configured(ch_num);
		qspi_apb_enable(ch_num);
	}

	return RL_OK;
}

#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(1, qspi_apb_init);
#endif
