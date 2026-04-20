/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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
#include <lib/libc/stdint.h>
#include <stddef.h>
#include <platform_def.h>
#include <lib/mmio.h>
#include <drivers/synopsys/qspi_boot.h>
#include <drivers/flash/mt25q_flash.h>
#include <common/debug.h>

#define SPI_NOR_FLASH_ID					(0x20)
#define SPI_NOR_FLASH_FSR_READY				(0x80)
#define SPI_NOR_FLASH_FSR_READY_MASK		(0x80)
#define SPI_NOR_FLASH_SR_WRITE_ENABLE_MASK	(0x3)
#define SPI_NOR_FLASH_SR_WRITE_ENABLE		(0x2)

#define ERASE_SIZE_LIMIT				(0x1000000)
#define ERASE_SIZE_4K					(0x1000)
#define ERASE_SIZE_32K					(0x8000)
#define ERASE_SIZE_64K					(0x10000)

#define ERASE_4K_COUNT(x)				(((x) >> 12) & 0x7)
#define ERASE_32K_COUNT(x)				(((x) >> 15) & 0x1)
#define ERASE_64K_COUNT(x)				(((x) >> 16) & 0xFF)

static uint32_t flash_spi_mode = FLASH_SPI_SINGLE_MODE;

static void gpt_32bit_memcpy(void *dst, const void *src, size_t len_t)
{
	const uint32_t *s = src;
	uint32_t *d = dst;
	uint32_t len;

	len = len_t >> 2;

	while (len--)
		*d++ = *s++;
}

static uint32_t flash_spi_get_mode(void)
{
	return flash_spi_mode;
}

static void flash_spi_set_mode(uint32_t mode)
{
	if (mode >= FLASH_SPI_SINGLE_MODE && mode <= FLASH_SPI_QUAD_MODE)
		flash_spi_mode = mode;
}

uint32_t flash_read_one_register(uint32_t cmd)
{
	qspi_boot_config_controller(QSPI_BOOT_CTRLR0_DFS_8,
								QSPI_BOOT_CTRLR0_TMOD_RX,
								QSPI_BOOT_CTRLR0_SPI_FRF_QSPI,
								QSPI_BOOT_SPI_CTRLR0_INST_L_8,
								QSPI_BOOT_SPI_CTRLR0_ADDR_L_0,
								QSPI_BOOT_SPI_CTRLR0_TRANS_TYPE_TT2,
								QSPI_BOOT_WAIT_0,
								QSPI_BOOT_CTRLR1_NDF_1WORD);
	return qspi_boot_enhance_rx_i_d_once(cmd);
}

static uint32_t flash_spi_set_quad_mode(void)
{
	uint32_t inst_val;
	uint32_t data_val;

	qspi_boot_enable(EN);

	qspi_boot_config_controller(QSPI_BOOT_CTRLR0_DFS_8,
								QSPI_BOOT_CTRLR0_TMOD_TX_RX,
								QSPI_BOOT_CTRLR0_SPI_FRF_STANDARD,
								QSPI_BOOT_SPI_CTRLR0_INST_L_0,
								QSPI_BOOT_SPI_CTRLR0_ADDR_L_0,
								QSPI_BOOT_SPI_CTRLR0_TRANS_TYPE_TT0,
								QSPI_BOOT_WAIT_0,
								QSPI_BOOT_CTRLR1_NDF_2WORD);

	inst_val = SPI_NOR_CMD_RDID;
	qspi_boot_std_tx_rx_d_multiple(&data_val, &inst_val, 1, 1);

	printf("flash_spi_set_quad_mode, data_val=0x%x\n", data_val);
	if (data_val != SPI_NOR_FLASH_ID)
		return -1;

	inst_val = SPI_NOR_CMD_ENTER_QUAD;
	qspi_boot_std_tx_d_multiple(&inst_val, 1);

	flash_spi_mode = FLASH_SPI_QUAD_MODE;

	return 0;
}

void flash_check_ready(void)
{
	uint32_t reg_val;

	reg_val = 0;
	while (!(reg_val & SPI_NOR_FLASH_FSR_READY_MASK)) {
		reg_val = flash_read_one_register(SPI_NOR_CMD_RDFSR);
	}
}

void flash_write_mode(uint32_t cmd)
{
	qspi_boot_config_controller(QSPI_BOOT_CTRLR0_DFS_8,
								QSPI_BOOT_CTRLR0_TMOD_TX,
								QSPI_BOOT_CTRLR0_SPI_FRF_QSPI,
								QSPI_BOOT_SPI_CTRLR0_INST_L_8,
								QSPI_BOOT_SPI_CTRLR0_ADDR_L_0,
								QSPI_BOOT_SPI_CTRLR0_TRANS_TYPE_TT2,
								QSPI_BOOT_WAIT_0,
								QSPI_BOOT_CTRLR1_NDF_1WORD);

	qspi_boot_enhance_tx_i_once(cmd);
}

void flash_write_mode_i_a(uint32_t cmd, uint32_t addr)
{
	qspi_boot_config_controller(QSPI_BOOT_CTRLR0_DFS_8,
								QSPI_BOOT_CTRLR0_TMOD_TX,
								QSPI_BOOT_CTRLR0_SPI_FRF_QSPI,
								QSPI_BOOT_SPI_CTRLR0_INST_L_8,
								QSPI_BOOT_SPI_CTRLR0_ADDR_L_24,
								QSPI_BOOT_SPI_CTRLR0_TRANS_TYPE_TT2,
								QSPI_BOOT_WAIT_0,
								QSPI_BOOT_CTRLR1_NDF_1WORD);

	qspi_boot_enhance_tx_i_a_once(cmd, addr);
}

void write_flash_fast_256_data(uint32_t cmd, uint32_t addr, uint32_t *data)
{
	qspi_boot_config_for_flash(QSPI_BOOT_CTRLR0_DFS_32,
							   QSPI_BOOT_CTRLR0_TMOD_TX,
							   QSPI_BOOT_CTRLR0_SPI_FRF_QSPI,
							   QSPI_BOOT_SPI_CTRLR0_INST_L_8,
							   QSPI_BOOT_SPI_CTRLR0_ADDR_L_24,
							   QSPI_BOOT_SPI_CTRLR0_TRANS_TYPE_TT2,
							   QSPI_BOOT_WAIT_0,
							   QSPI_BOOT_CTRLR1_NDF_1WORD);

	qspi_boot_enhance_tx_i_a_d_256(cmd, addr, (uint32_t *)data);
}

void write_flash_fast_size_data(uint32_t cmd, uint32_t addr, uint32_t *data, uint32_t size)
{
	qspi_boot_config_for_flash(QSPI_BOOT_CTRLR0_DFS_32,
							   QSPI_BOOT_CTRLR0_TMOD_TX,
							   QSPI_BOOT_CTRLR0_SPI_FRF_QSPI,
							   QSPI_BOOT_SPI_CTRLR0_INST_L_8,
							   QSPI_BOOT_SPI_CTRLR0_ADDR_L_24,
							   QSPI_BOOT_SPI_CTRLR0_TRANS_TYPE_TT2,
							   QSPI_BOOT_WAIT_0,
							   QSPI_BOOT_CTRLR1_NDF_1WORD);

	qspi_boot_enhance_tx_i_a_d_size(cmd, addr, (uint32_t *)data, size);
}

void enable_write(void)
{
	uint32_t reg_val;

	flash_write_mode(SPI_NOR_CMD_WRITE_ENABLE);
	reg_val = flash_read_one_register(SPI_NOR_CMD_RDSR);
	while ((reg_val & SPI_NOR_FLASH_SR_WRITE_ENABLE_MASK) != SPI_NOR_FLASH_SR_WRITE_ENABLE) {
		reg_val = flash_read_one_register(SPI_NOR_CMD_RDSR);
		printf("flash enable_write: retry -- SPI_NOR_CMD_RDSR=0x%x\n", reg_val);
	}
}

uint32_t erase_flash(uint32_t offset, uint32_t size)
{
	uint32_t ret;
	uint32_t addr = offset;

	if (flash_spi_get_mode() != FLASH_SPI_QUAD_MODE) {
		ret = flash_spi_set_quad_mode();
		if (ret) {
			printf("Fail changing to Quad mode, ret=%d\n", ret);
			__asm__("b .");
		}
	}

	if (size >= ERASE_SIZE_LIMIT) {
		enable_write();

		printf("\nbulk erase\n");
		flash_write_mode(SPI_NOR_CMD_BULK_ERASE);

	} else {
		uint32_t loop_4k = ERASE_4K_COUNT(size);
		uint32_t loop_32k = ERASE_32K_COUNT(size);
		uint32_t loop_64k = ERASE_64K_COUNT(size);

		for (uint32_t i = 0; i < loop_64k; i++) {
			printf("\n64k erase, i=0x%x, addr=0x%x\n", i, addr);
			enable_write();
			flash_write_mode_i_a(SPI_NOR_CMD_SECTOR_ERASE, addr);
			addr += ERASE_SIZE_64K;

			flash_check_ready();
		}

		for (uint32_t i = 0; i < loop_32k; i++) {
			printf("\n32k erase, i=0x%x, addr=0x%x\n", i, addr);
			enable_write();
			flash_write_mode_i_a(SPI_NOR_CMD_SUBSECTOR_32K_ERASE, addr);
			addr += ERASE_SIZE_32K;

			flash_check_ready();
		}

		for (uint32_t i = 0; i < loop_4k; i++) {
			printf("\n4k erase, i=0x%x, addr=0x%x\n", i, addr);
			enable_write();
			flash_write_mode_i_a(SPI_NOR_CMD_SUBSECTOR_4K_ERASE, addr);
			addr += ERASE_SIZE_4K;

			flash_check_ready();
		}

	}

	flash_check_ready();

	return 0;
}

uint32_t read_flash(uint32_t offset, uint32_t *dst, uint32_t size)
{
	flash_write_mode(SPI_NOR_CMD_RESET_QUAD);
	flash_spi_set_mode(FLASH_SPI_SINGLE_MODE);

	qspi_boot_config();

	gpt_32bit_memcpy((void *)dst, (void *)(XIP_FLASH_BASE_ADDR + offset), (size_t)size);

	return 0;
}

uint32_t write_flash(uint32_t offset, void *data, uint32_t size)
{
	uint32_t flash_addr = 0;
	uint32_t *dram_addr = (uint32_t *)data;
	uint32_t ret;
	uint32_t size_loop = size >> 8;
	uint32_t size_sub = size & 0xff;

	if (flash_spi_get_mode() != FLASH_SPI_QUAD_MODE) {
		ret = flash_spi_set_quad_mode();
		if (ret) {
			printf("Fail changing to Quad mode\n");
			__asm__("b .");
		}
	}

	printf("write_flash, size=0x%x, loop=0x%x, sub=0x%x\n", size, size_loop, size_sub);

	uint32_t i;

	flash_addr = offset;

	for (i = 0; i < size_loop; i++) {
		enable_write();
		write_flash_fast_256_data(SPI_NOR_CMD_QUAD_PROGRAM, flash_addr, (uint32_t *)(dram_addr + i * 0x40));
		flash_check_ready();

		flash_addr += 0x100;
	}

	if (size_sub > 0) {
		enable_write();
		write_flash_fast_size_data(SPI_NOR_CMD_QUAD_PROGRAM, flash_addr, (uint32_t *)(dram_addr + i * 0x40),
								   size_sub);
		flash_check_ready();
	}

	printf("write_flash_fast_256_data from 0x%lx\n\n", (uint64_t)dram_addr);
	flash_check_ready();

	qspi_boot_config();

	return 0;
}
