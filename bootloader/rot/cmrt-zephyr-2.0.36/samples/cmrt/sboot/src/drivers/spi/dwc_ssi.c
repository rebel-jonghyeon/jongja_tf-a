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
#include <rebel_h.h>
#include <rebel_h_gpt.h>
#include <stdint.h>
#include <fboot.h>
#include "dwc_ssi.h"
#include "sac_custom.h"
#include "timer.h"

#define QSPI_ROT_PRIVATE				(0x1E00500000ULL)

#define DISEN							(0)
#define EN								(1)
#define SPI_BUSY						(0x1)
#define FLASH_READY						(0x80)
#define RESET_VALUE						(0x0)

#define ERASE_4KB_COMMAND				(0x20)
#define PROGRAM_COMMAND					(0x32)
#define WRITE_ENABLE_COMMAND			(0x6)
#define READ_STATUS_COMMAND				(0x5)
#define READ_FLAG_STATUS_COMMAND		(0x70)
#define WRITE_ENABLE_LATCH				(0x2)
#define WRITE_ENABLE_LATCH_MASK			(0x2)

#define NOR_CMD_QAUD_IO_WORD_READ		(0xe7)
#define BOOT_QSPI_INCR_OPCODE			(NOR_CMD_QAUD_IO_WORD_READ)
#define BOOT_QSPI_WRAP_OPCODE			(NOR_CMD_QAUD_IO_WORD_READ)

#define SSI_CLK_DIV_6					(0x6 >> 1)
#define SSI_CLK_DIV_24					(0x18 >> 1)
#define FRAME_FORMAT_SPI_QUAD			(0x2)
#define INST_STANDARD_ADDR_FRF			(0x1)
#define LENGTH_OF_ADDR_24BIT			(0x6)
#define LENGTH_OF_INST_8BIT				(0x2)
#define WAIT_CYCLE_4					(0x4)
#define FIX_DFS_FOR_XIP_TX				(0x1)
#define XIP_MODE_8BIT					(0x2)
#define DFS_8BIT						(0x7)
#define DFS_24BIT						(0x17)
#define DFS_32BIT						(0x1F)
#define RX_ONLY_MODE					(0x2)
#define TX_ONLY_MODE					(0x1)
#define TX_FIFO_TRIGGER					(0x1)
#define MICROWIRE_FRAME_FORMAT			(0x2)

#define FLASH_TIMEOUT_MS				(500)

static inline void dwc_ssi_enable(volatile struct dwc_ssi *dwc_ssi, uint32_t en)
{
	dwc_ssi->ssienr.ssic_en = en;
}

void dwc_ssi_config(void)
{
	cmrt_sac_set_base(NULL, QSPI_ROT_PRIVATE);
	volatile struct dwc_ssi *const dwc_ssi = (struct dwc_ssi *)(CMRT_SAC_BASE + R_CPU_DATA);

	dwc_ssi_enable(dwc_ssi, DISEN);

	dwc_ssi->baudr.sckdv = SSI_CLK_DIV_24;

	dwc_ssi->xip_incr_inst.incr_inst = BOOT_QSPI_INCR_OPCODE;
	dwc_ssi->xip_wrap_inst.wrap_inst = BOOT_QSPI_WRAP_OPCODE;

	dwc_ssi->xip_ctrl.frf = FRAME_FORMAT_SPI_QUAD;
	dwc_ssi->xip_ctrl.trans_type = INST_STANDARD_ADDR_FRF;
	dwc_ssi->xip_ctrl.addr_l = LENGTH_OF_ADDR_24BIT;
	dwc_ssi->xip_ctrl.inst_l = LENGTH_OF_INST_8BIT;
	dwc_ssi->xip_ctrl.wait_cycles = WAIT_CYCLE_4;
	dwc_ssi->xip_ctrl.dfs_hc = FIX_DFS_FOR_XIP_TX;
	dwc_ssi->xip_ctrl.ddr_en = DISEN;
	dwc_ssi->xip_ctrl.inst_en = EN;
	dwc_ssi->xip_ctrl.cont_xfer_en = DISEN;
	dwc_ssi->xip_ctrl.xip_mbl = XIP_MODE_8BIT;

	dwc_ssi_enable(dwc_ssi, EN);
}

static uint32_t is_spi_available(void)
{
	cmrt_sac_set_base(NULL, QSPI_ROT_PRIVATE);
	volatile struct dwc_ssi *const dwc_ssi = (struct dwc_ssi *)(CMRT_SAC_BASE + R_CPU_DATA);

	if (dwc_ssi->sr.busy == SPI_BUSY) {
		return false;
	} else {
		return true;
	}
}

static uint32_t is_tx_available(void)
{
	cmrt_sac_set_base(NULL, QSPI_ROT_PRIVATE);
	volatile struct dwc_ssi *const dwc_ssi = (struct dwc_ssi *)(CMRT_SAC_BASE + R_CPU_DATA);

	if (is_spi_available() == false || dwc_ssi->sr.tfnf == 0x0) {
		return false;
	} else {
		return true;
	}
}

static uint32_t is_rx_available(void)
{
	cmrt_sac_set_base(NULL, QSPI_ROT_PRIVATE);
	volatile struct dwc_ssi *const dwc_ssi = (struct dwc_ssi *)(CMRT_SAC_BASE + R_CPU_DATA);

	if (is_spi_available() == false || dwc_ssi->sr.rfne == 0x0) {
		return false;
	} else {
		return true;
	}
}

static uint32_t read_flash_status(void)
{
	cmrt_sac_set_base(NULL, QSPI_ROT_PRIVATE);
	volatile struct dwc_ssi *const dwc_ssi = (struct dwc_ssi *)(CMRT_SAC_BASE + R_CPU_DATA);

	while (is_tx_available() == false) {
		;
	}
	dwc_ssi_enable(dwc_ssi, DISEN);

	dwc_ssi->spi_ctrlr0.val = RESET_VALUE;
	dwc_ssi->spi_ctrlr0.inst_l = LENGTH_OF_INST_8BIT;

	dwc_ssi->ctrlr0.val = RESET_VALUE;
	dwc_ssi->ctrlr0.dfs = DFS_8BIT;
	dwc_ssi->ctrlr0.tmod = RX_ONLY_MODE;

	dwc_ssi_enable(dwc_ssi, EN);

	while (is_tx_available() == false) {
		;
	}
	dwc_ssi->dr0.val = READ_STATUS_COMMAND;

	while (is_rx_available() == false) {
		;
	}

	return dwc_ssi->dr0.val;
}

static uint32_t read_flash_flag_status(void)
{
	cmrt_sac_set_base(NULL, QSPI_ROT_PRIVATE);
	volatile struct dwc_ssi *const dwc_ssi = (struct dwc_ssi *)(CMRT_SAC_BASE + R_CPU_DATA);

	while (is_tx_available() == false) {
		;
	}
	dwc_ssi_enable(dwc_ssi, DISEN);

	dwc_ssi->spi_ctrlr0.val = RESET_VALUE;
	dwc_ssi->spi_ctrlr0.inst_l = LENGTH_OF_INST_8BIT;

	dwc_ssi->ctrlr0.val = RESET_VALUE;
	dwc_ssi->ctrlr0.dfs = DFS_8BIT;
	dwc_ssi->ctrlr0.tmod = RX_ONLY_MODE;

	dwc_ssi_enable(dwc_ssi, EN);

	while (is_tx_available() == false) {
		;
	}
	dwc_ssi->dr0.val = READ_FLAG_STATUS_COMMAND;

	while (is_rx_available() == false) {
		;
	}

	return dwc_ssi->dr0.val;
}

static uint32_t is_flash_available(void)
{
	if ((read_flash_flag_status() & FLASH_READY) == FLASH_READY) {
		return true;
	} else {
		return false;
	}

}

static int write_enable_command(void)
{
	volatile uint64_t start_ms = get_uptime_ms();
	volatile uint64_t end_ms;

	while (is_flash_available() == false) {
		end_ms = get_uptime_ms();

		if (end_ms - start_ms > FLASH_TIMEOUT_MS) {
			return -ETIMEDOUT;
		}
	}

	cmrt_sac_set_base(NULL, QSPI_ROT_PRIVATE);

	volatile struct dwc_ssi *const dwc_ssi = (struct dwc_ssi *)(CMRT_SAC_BASE + R_CPU_DATA);

	while (is_tx_available() == false) {
		;
	}
	dwc_ssi_enable(dwc_ssi, DISEN);

	dwc_ssi->spi_ctrlr0.val = RESET_VALUE;

	dwc_ssi->ctrlr0.val = RESET_VALUE;
	dwc_ssi->ctrlr0.dfs = DFS_8BIT;
	dwc_ssi->ctrlr0.tmod = TX_ONLY_MODE;

	dwc_ssi->txftlr.val = RESET_VALUE;

	dwc_ssi_enable(dwc_ssi, EN);

	while (is_tx_available() == false) {
		;
	}

	dwc_ssi->dr0.val = WRITE_ENABLE_COMMAND;

	return 0;
}

static int erase_flash(uint32_t erase_cmd, uint32_t offset)
{
	int res;

	res = write_enable_command();
	if (res) {
		return res;
	}

	cmrt_sac_set_base(NULL, QSPI_ROT_PRIVATE);

	volatile struct dwc_ssi *const dwc_ssi = (struct dwc_ssi *)(CMRT_SAC_BASE + R_CPU_DATA);
	volatile uint32_t read_status = read_flash_status();

	volatile uint64_t start_ms = get_uptime_ms();
	volatile uint64_t end_ms;

	while ((read_status & WRITE_ENABLE_LATCH_MASK) != WRITE_ENABLE_LATCH) {
		read_status = read_flash_status();
		end_ms = get_uptime_ms();

		if (end_ms - start_ms > FLASH_TIMEOUT_MS) {
			return -ETIMEDOUT;
		}
	}

	while (is_tx_available() == false) {
		;
	}
	dwc_ssi_enable(dwc_ssi, DISEN);

	dwc_ssi->spi_ctrlr0.val = RESET_VALUE;
	dwc_ssi->spi_ctrlr0.inst_l = LENGTH_OF_INST_8BIT;

	dwc_ssi->ctrlr0.val = RESET_VALUE;
	dwc_ssi->ctrlr0.dfs = DFS_24BIT;
	dwc_ssi->ctrlr0.tmod = TX_ONLY_MODE;

	dwc_ssi->txftlr.val = RESET_VALUE;
	dwc_ssi->txftlr.txfthr = TX_FIFO_TRIGGER;

	dwc_ssi_enable(dwc_ssi, EN);

	dwc_ssi->dr0.val = erase_cmd;
	while (is_tx_available() == false)
		;
	dwc_ssi->dr0.val = offset;

	return 0;
}

int write_flash_256b(uint32_t offset, uint32_t *data, uint32_t data_size)
{
	uint64_t backup_sac_addr = cmrt_sac_get_base(NULL);
	uint32_t ndf;
	int res;

	res = erase_flash(ERASE_4KB_COMMAND, offset);
	if (res) {
		return res;
	}

	res = write_enable_command();
	if (res) {
		return res;
	}

	volatile uint32_t read_status = read_flash_status();

	while ((read_status & WRITE_ENABLE_LATCH_MASK) != WRITE_ENABLE_LATCH) {
		write_enable_command();
		read_status = read_flash_status();
	}

	while (is_tx_available() == false) {
		;
	}

	cmrt_sac_set_base(NULL, QSPI_ROT_PRIVATE);
	volatile struct dwc_ssi *const dwc_ssi = (struct dwc_ssi *)(CMRT_SAC_BASE + R_CPU_DATA);

	dwc_ssi_enable(dwc_ssi, DISEN);

	dwc_ssi->spi_ctrlr0.val = RESET_VALUE;
	dwc_ssi->spi_ctrlr0.addr_l = LENGTH_OF_ADDR_24BIT;
	dwc_ssi->spi_ctrlr0.inst_l = LENGTH_OF_INST_8BIT;

	dwc_ssi->ctrlr0.val = RESET_VALUE;
	dwc_ssi->ctrlr0.dfs = DFS_32BIT;
	dwc_ssi->ctrlr0.tmod = TX_ONLY_MODE;
	dwc_ssi->ctrlr0.spi_frf = MICROWIRE_FRAME_FORMAT;
	if ((data_size % sizeof(uint32_t)) != 0) {
		ndf = (data_size / sizeof(uint32_t)) + 1;
	} else {
		ndf = data_size / sizeof(uint32_t);
	}
	dwc_ssi->ctrlr1.ndf = ndf;

	dwc_ssi->txftlr.val = RESET_VALUE;

	dwc_ssi_enable(dwc_ssi, EN);

	dwc_ssi->dr0.val = PROGRAM_COMMAND;
	while (is_tx_available() == false) {
		;
	}
	dwc_ssi->dr0.val = offset;

	for (uint32_t i = 0; i < ndf; i++) {
		dwc_ssi->dr0.val = data[i];
	}

	cmrt_sac_set_base(NULL, backup_sac_addr);

	return 0;
}
