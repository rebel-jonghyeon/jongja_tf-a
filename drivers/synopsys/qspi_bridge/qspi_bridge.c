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
#include <drivers/synopsys/qspi_bridge.h>
#include <drivers/delay_timer.h>
#include <string.h>

#include <stddef.h>
#include <platform_def.h>
#include <common/debug.h>

#ifndef MHZ
#define MHZ	(1000000)
#endif

#define TARGET_SCLK_OUT		(5 * MHZ)	/* 5MHz */
#define SSI_CLK_FREQ		(250 * MHZ)	/* 250MHz */
#define SSI_BAUDR			(SSI_CLK_FREQ / TARGET_SCLK_OUT)

/* default controller channel: QSPI2 PERI1
 * #define QSPI_BRIDGE_2_PERI_CP_BASE_ADDR (QSPI2_PERI0)
 * #define QSPI_BRIDGE_3_PERI_CP_BASE_ADDR (QSPI3_PERI0)
 */
#define QSPI_BRIDGE_2_PERI_CP_BASE_ADDR (QSPI2_PERI1)
#define QSPI_BRIDGE_3_PERI_CP_BASE_ADDR (QSPI3_PERI1)

#define QSPI_BRIDGE_NUMBER_OF_CHANNELS		(3)

#define QSPI_BRIDGE_CHIPLET_ID_1			(1)
#define QSPI_BRIDGE_CHIPLET_ID_2			(2)
#define QSPI_BRIDGE_CHIPLET_ID_3			(3)

#define USE_QUAD_DIE

struct dw_ssi_config qspi_cfg[QSPI_BRIDGE_NUMBER_OF_CHANNELS] = {
	{
		.regs = (struct dw_ssi_regs *)NULL,
		.configured = 0,
	},
	{
		.regs = (struct dw_ssi_regs *)NULL,
		.configured = 0,
	},
	{
		.regs = (struct dw_ssi_regs *)QSPI_BRIDGE_2_PERI_CP_BASE_ADDR,
		.configured = 0,
	},

};

struct dw_ssi_bridge_config qspi_bridge_cfg = {
	.regs = (struct dw_ssi_bridge_regs *)QSPI_BRIDGE_3_PERI_CP_BASE_ADDR,
	.configured = 0,
};

static void qspi_bridge_set_configured(uint32_t ch_num)
{
	if (ch_num < QSPI_BRIDGE_NUMBER_OF_CHANNELS)
		qspi_cfg[ch_num].configured = 1;
	else
		qspi_bridge_cfg.configured = 1;
}

static bool qspi_bridge_check_configured(uint32_t ch_num)
{
	if (ch_num < QSPI_BRIDGE_NUMBER_OF_CHANNELS)
		return qspi_cfg[ch_num].configured == 1;

	return qspi_bridge_cfg.configured == 1;
}

static void qspi_bridge_int_disable(uint32_t ch_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;

	regs->imr = DW_SPI_IMR_MASK;

}

static void qspi_bridge_ssi_disable(uint32_t ch_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;

	regs->ssienr = DW_SPI_SSIENR_DISABLE;

}

static void qspi_bridge_ssi_enable(uint32_t ch_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;

	regs->ssienr = DW_SPI_SSIENR_ENABLE;

}

static void qspi_bridge_int_config(uint32_t ch_num)
{
	/* todo */

}

static void qspi_bridge_check_busy(uint32_t ch_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;

	while ((regs->sr & 0x01) == 1)
		;

}

static int qspi_bridge_ser_enable(uint32_t ch_num, uint32_t slave_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;
	uint32_t reg_data;

	/* slave_num should be 1~3, chiplet id */
	if (slave_num > 0 && slave_num < 4) {
		qspi_bridge_check_busy(ch_num);

		slave_num--;
		reg_data = regs->ser;
		reg_data |= (1 << slave_num);
		regs->ser = reg_data;

		return 1;

	} else {
		/* error */
		return 0;
	}
}

static int qspi_bridge_ser_disable(uint32_t ch_num, uint32_t slave_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;
	uint32_t reg_data;

	/* slave_num should be 1~3 */
	if (slave_num > 0 && slave_num < 4) {
		qspi_bridge_check_busy(ch_num);

		slave_num--;
		reg_data = regs->ser;
		reg_data &= ~(1 << slave_num);
		regs->ser = reg_data;

		return 1;

	} else {
		/* error */
		return 0;
	}
}

static void qspi_bridge_config_writemode(uint32_t ch_num, uint32_t txftlr_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;
	uint32_t temp;

	qspi_bridge_ssi_disable(ch_num);

	temp = regs->ctrlr0;
	temp &= ~(3 << DW_SPI_CTRLR0_TMOD_BIT);
	temp |= DW_SPI_CTRLR0_TMOD_TX;

	regs->ctrlr0 = temp;

	temp = 0U;
	temp |= DW_SPI_SPI_CTRLR0_INST_L_8;
	temp |= DW_SPI_SPI_CTRLR0_ADDR_L_24;
	temp |= DW_SPI_SPI_CTRLR0_TRANS_TYPE;

	regs->spi_ctrlr0 = temp;

	regs->ctrlr1 = 0;

	qspi_bridge_ssi_enable(ch_num);

	regs->txftlr = txftlr_num;
}

static void qspi_bridge_config_readmode(uint32_t ch_num, uint32_t ndf)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;
	uint32_t temp;

	qspi_bridge_ssi_disable(ch_num);

	temp = regs->ctrlr0;
	temp &= ~(3 << DW_SPI_CTRLR0_TMOD_BIT);
	temp |= DW_SPI_CTRLR0_TMOD_RX;

	regs->ctrlr0 = temp;

	temp = 0U;
	temp |= DW_SPI_SPI_CTRLR0_INST_L_8;
	temp |= DW_SPI_SPI_CTRLR0_ADDR_L_24;
	temp |= DW_SPI_SPI_CTRLR0_TRANS_TYPE;
	temp |= DW_SPI_SPI_CTRLR0_WAIT_CYCLES_24;
	regs->spi_ctrlr0 = temp;

	regs->txftlr = DW_SPI_TXFTLR_0WORD;

	regs->ctrlr1 = ndf;

	qspi_bridge_ssi_enable(ch_num);

}

static void qspi_bridge_config_ssi_controller(uint32_t ch_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;
	uint32_t temp = 0U;

	/* set ctlr0 */
	temp |= DW_SPI_CTRLR0_DFS_32;				/* Word size = 32 bit */
	temp |= DW_SPI_CTRLR0_SSI_IS_CONTROLLER;	/* SSI is controller*/
	temp |= DW_SPI_CTRLR0_TMOD_TX;				/* enhanced mode */
	temp |= DW_SPI_CTRLR0_SPI_FRF_QSPI;		/* standard SPI  DW_SPI_CTRLR0_SPI_FRF_QSPI ?*/
	regs->ctrlr0 = temp;

	/* same as default val */
	temp = 0U;
	temp |= DW_SPI_SPI_CTRLR0_INST_L_8;
	temp |= DW_SPI_SPI_CTRLR0_ADDR_L_24;
	temp |= DW_SPI_SPI_CTRLR0_TRANS_TYPE;
	regs->spi_ctrlr0 = temp;

	/* TXFTLR */
	temp = DW_SPI_TXFTLR_1WORD;
	regs->txftlr = temp;

	/* set baud for master mode */
	regs->baudr = (uint32_t)(SSI_BAUDR);

	regs->ctrlr1 = 0;
	regs->ddr_drive_edge = 0;
	regs->mwcr = 2;
	regs->rxftlr = 0;

}

void qspi_bridge_write_1word(uint32_t ch_num, uint64_t addr, uint32_t data, uint32_t slave_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;
	uint32_t converted_qspi_addr_field;

	INFO("QSPI Write addr: %lx, data: %x\n", addr, data);

	if (!qspi_bridge_ser_enable(ch_num, slave_num)) {
		INFO("QSPI error: slave num must be 1~3\n");
		return;
	}

	/* 0. config to write 1 word */
	qspi_bridge_config_writemode(ch_num, DW_SPI_TXFTLR_1WORD);

	converted_qspi_addr_field = (uint32_t)((addr >> 2) & 0x00ffffff);

	/* Caution: no delay between data writes */
	regs->drx[0] = DW_SPI_INSTRUCTION_WRITE;
	regs->drx[1] = converted_qspi_addr_field;
	regs->drx[2] = data;

	qspi_bridge_check_busy(ch_num);

	qspi_bridge_ser_disable(ch_num, slave_num);

	/* TODO: add a function to check WRITESTATUS0/1/2 return */
	udelay(1 * 10);
}

void qspi_bridge_write_16word(uint32_t ch_num, uint64_t addr, uint32_t *data, uint32_t slave_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;
	uint32_t converted_qspi_addr_field, i;

	if (!qspi_bridge_ser_enable(ch_num, slave_num)) {
		INFO("QSPI error: slave num must be 1~3\n");
		return;
	}

	/* 0. config to write 16 word */
	qspi_bridge_config_writemode(ch_num, DW_SPI_TXFTLR_16WORD);

	converted_qspi_addr_field = (uint32_t)((addr >> 2) & 0x00ffffff);

	/* Caution: no delay between data writes */
	regs->drx[0] = DW_SPI_INSTRUCTION_WRITE_16WORD;
	regs->drx[1] = converted_qspi_addr_field;
	for (i = 0; i < 16; i++) {
		regs->drx[2 + i] = data[i];
	}

	qspi_bridge_check_busy(ch_num);
	qspi_bridge_ser_disable(ch_num, slave_num);

	/* TODO: add a function to check WRITESTATUS0/1/2 return */
	udelay(10 * 10);
}

uint32_t qspi_bridge_read_1word(uint32_t ch_num, uint64_t addr, uint32_t slave_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;
	uint32_t converted_qspi_addr_field, temp_data = 0, i;

	converted_qspi_addr_field = (uint32_t)((addr >> 2) & 0x00ffffff);

	if (!qspi_bridge_ser_enable(ch_num, slave_num)) {
		INFO("QSPI error: slave num must be 1~3\n");
		return 0;
	}

	/* direct read approach */
	qspi_bridge_config_readmode(ch_num, DW_SPI_CTRLR1_NDF_1WORD);

	/* no delay between data writes */
	regs->drx[0] = DW_SPI_INSTRUCTION_READ_24WAIT;	// quad mode
	regs->drx[1] = converted_qspi_addr_field;

	/* may need some delays for busy flag before read busy flag */
	qspi_bridge_check_busy(ch_num);

	i = 0;
	while (i == 0)
		i =  regs->rxflr;

	temp_data = regs->drx[0];

	qspi_bridge_ser_disable(ch_num, slave_num);

	INFO("QSPI Read addr: %lx, data: %x\n", addr, temp_data);

	return temp_data;

}

void qspi_bridge_read_16word(uint32_t ch_num, uint64_t addr, uint32_t *data, uint32_t slave_num)
{
	volatile struct dw_ssi_regs *regs = qspi_cfg[ch_num].regs;
	uint32_t converted_qspi_addr_field, *temp_data = data;
	uint32_t i;

	converted_qspi_addr_field = (uint32_t)((addr >> 2) & 0x00ffffff);

	if (!qspi_bridge_ser_enable(ch_num, slave_num)) {
		INFO("QSPI error: slave num must be 1~3\n");
		return;
	}

	/* direct read approach */
	qspi_bridge_config_readmode(ch_num, DW_SPI_CTRLR1_NDF_16WORD);

	/* no delay between data writes */
	regs->drx[0] = DW_SPI_INSTRUCTION_READ_24WAIT | DW_SPI_INSTRUCTION_READ_16;
	regs->drx[1] = converted_qspi_addr_field;

	/* TODO: add a function to check WRITESTATUS0/1/2 return */

	qspi_bridge_check_busy(ch_num);

	i = 0;
	while (i < 16)
		i =  regs->rxflr;

	while (i > 0) {
		*temp_data = regs->drx[i];
		temp_data++;
		i--;
	}

	qspi_bridge_ser_disable(ch_num, slave_num);
}

void qspi_bridge_init(uint32_t ch_num)
{
	/* todo : gpio setting */

	/* set ctlr0 */
	if (ch_num < QSPI_BRIDGE_NUMBER_OF_CHANNELS) {
		/* Masking interrupt and making sure controller is disabled */
		qspi_bridge_ssi_disable(ch_num);

		qspi_bridge_int_disable(ch_num);
		qspi_bridge_int_config(ch_num);
		qspi_bridge_config_ssi_controller(ch_num);

		qspi_bridge_set_configured(ch_num);

		qspi_bridge_ssi_enable(ch_num);
	} else {
		INFO("Initialize Controller mode only for ch0~2\n");
	}

	INFO("Designware SPI driver initialized on device: %d\n", ch_num);

}

void qspi_bridge_set_upper_addr(uint32_t ch_num, uint64_t addr, uint32_t slave_num)
{
	if (slave_num > 0) {
		qspi_bridge_write_1word(ch_num, DW_SPI_SYSREG_ADDRESS, ((uint32_t)addr) & 0xFC000000, slave_num);
	}
}

uint32_t qspi_bridge_test(void)
{
	uint32_t temp;
	uint32_t temp_data[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	uint32_t datain[16] = {0};

	qspi_bridge_init(2);

	if (qspi_bridge_check_configured(2) == true)
		INFO("\nDesignware QSPI2 is configured.\n");

	NOTICE("\nTo start, press any key on UART0..\n\n");

	while ((*(volatile uint32_t *)(UART0_PERI0 + 0x14) & 0x01) == 0)
		;

	/* Address configuration */
	qspi_bridge_set_upper_addr(2, 0x0, QSPI_BRIDGE_CHIPLET_ID_1);
#ifdef USE_QUAD_DIE
	/* add quad test - start*/
	qspi_bridge_set_upper_addr(2, 0x0, QSPI_BRIDGE_CHIPLET_ID_2);
	qspi_bridge_set_upper_addr(2, 0x0, QSPI_BRIDGE_CHIPLET_ID_3);
	qspi_bridge_write_1word(2, 0x1e00010000, 0xaaaa1111, QSPI_BRIDGE_CHIPLET_ID_1);
	qspi_bridge_write_1word(2, 0x1e00010000, 0xaaaa2222, QSPI_BRIDGE_CHIPLET_ID_2);
	qspi_bridge_write_1word(2, 0x1e00010000, 0xaaaa3333, QSPI_BRIDGE_CHIPLET_ID_3);
	temp = qspi_bridge_read_1word(2, 0x1e00010000, QSPI_BRIDGE_CHIPLET_ID_1);
	NOTICE("---- READ  addr=0x1e00010000, data=0x%X, expected 0xaaaa1111\n\n", temp);
	temp = qspi_bridge_read_1word(2, 0x1e00010000, QSPI_BRIDGE_CHIPLET_ID_2);
	NOTICE("---- READ  addr=0x1e00010000, data=0x%X, expected 0xaaaa2222\n\n", temp);
	temp = qspi_bridge_read_1word(2, 0x1e00010000, QSPI_BRIDGE_CHIPLET_ID_3);
	NOTICE("---- READ  addr=0x1e00010000, data=0x%X, expected 0xaaaa3333\n\n", temp);
	/* add quad test - end */
#endif

	/* single test */
	NOTICE("\n\n");
	NOTICE("Write 1 word 4 times\n");
	qspi_bridge_write_1word(2, 0x1e00010000, 0xaaaa5555, QSPI_BRIDGE_CHIPLET_ID_1);
	qspi_bridge_write_1word(2, 0x1e00010004, 0x5555aaaa, QSPI_BRIDGE_CHIPLET_ID_1);
	qspi_bridge_write_1word(2, 0x1e00010008, 0x12345678, QSPI_BRIDGE_CHIPLET_ID_1);
	qspi_bridge_write_1word(2, 0x1e0001000c, 0x87654321, QSPI_BRIDGE_CHIPLET_ID_1);

	NOTICE("Write 16 words to 0x1e00010010 and 0x1e00020000\n");
	qspi_bridge_write_16word(2, 0x1e00010010, temp_data, QSPI_BRIDGE_CHIPLET_ID_1);
	qspi_bridge_write_16word(2, 0x1e00020000, temp_data, QSPI_BRIDGE_CHIPLET_ID_1);

	NOTICE("Read 1 word 4 times\n");
	temp = qspi_bridge_read_1word(2, 0x1e00010000, QSPI_BRIDGE_CHIPLET_ID_1);
	NOTICE("---- READ  addr=0x1e00010000, data=0x%X, expected 0xaaaa5555\n\n", temp);
	temp = qspi_bridge_read_1word(2, 0x1e00010004, QSPI_BRIDGE_CHIPLET_ID_1);
	NOTICE("---- READ  addr=0x1e00010004, data=0x%X, expected 0x5555aaaa\n\n", temp);
	temp = qspi_bridge_read_1word(2, 0x1e00010008, QSPI_BRIDGE_CHIPLET_ID_1);
	NOTICE("---- READ  addr=0x1e00010008, data=0x%X, expected 0x12345678\n\n", temp);
	temp = qspi_bridge_read_1word(2, 0x1e0001000c, QSPI_BRIDGE_CHIPLET_ID_1);
	NOTICE("---- READ  addr=0x1e0001000c, data=0x%X, expected 0x87654321\n\n", temp);

	NOTICE("Read 16 words and compare 0~15\n");
	qspi_bridge_read_16word(2, 0x1e00010010, datain, QSPI_BRIDGE_CHIPLET_ID_1);

	for (int i = 0; i < 16; i++) {
		if (temp_data[i] == datain[i])
			NOTICE("ok %d\n", i);
		else {
			NOTICE("NG %d\n", i);
			return 0;
		}
	}

	for (int i = 0; i < 16; i++) {
		datain[i] = 0xff;
	}

	NOTICE("Read 16 words and compare 0~15\n");
	qspi_bridge_read_16word(2, 0x1e00020000, datain, QSPI_BRIDGE_CHIPLET_ID_1);

	for (int i = 0; i < 16; i++) {
		if (temp_data[i] == datain[i])
			NOTICE("ok %d\n", i);
		else {
			NOTICE("NG %d\n", i);
			return 0;
		}
	}

	asm volatile ("b .");

	return 1;
}
