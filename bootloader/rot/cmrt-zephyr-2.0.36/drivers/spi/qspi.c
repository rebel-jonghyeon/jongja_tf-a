/*
 * Copyright (c) 2019 Linaro Limited
 * Copyright (c) 2025 Samsung Electronics Co, Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT samsung_qspi

#include "qspi.h"
#include <drivers/cmrt/sac.h>
#include <rebel_h.h>
#include <device.h>
#include <stdint.h>
#include <soc.h>
#include <kernel.h>
#include <errno.h>

#define DEV_CFG(dev) \
	((const struct qspi_samsung_device_config * const)(dev)->config)
#define QSPI_SAMSUNG_REGS(dev) \
	(uint64_t)(DEV_CFG(dev)->base)

#define RETURN_IF_ERROR(x) \
	do { if (x) return -ETIMEDOUT; } while (0)
#define END_IF_ERROR(x) \
	do { if (x) return; } while (0)

#include <logging/log.h>
LOG_MODULE_DECLARE(qspi, CONFIG_CMRT_LOG_LEVEL);

struct qspi_samsung_device_config {
	uint64_t base;
};

static void qspi_int_disable(void)
{
	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	regs->imr = DW_IMR_MASK;
}

static void qspi_ssi_disable(void)
{
	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	regs->ssienr &= ~DW_SSIENR_ENABLE;
}

static void qspi_ssi_enable(void)
{
	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	regs->ssienr = DW_SSIENR_ENABLE;
}

static int qspi_check_busy(void)
{
	int64_t timeout = k_uptime_get() + TIMEOUT_MS;

	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	while ((regs->sr & DW_SR_BUSY_BIT) == DW_SR_BUSY_BIT) {
		if (k_uptime_get() > timeout) {
			LOG_ERR("spi check busy timeout error\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static int tx_available(void)
{
	int64_t timeout = k_uptime_get() + TIMEOUT_MS;

	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	while (((regs->sr & DW_SR_TFNF_BIT) == 0) || ((regs->sr & DW_SR_BUSY_BIT) == DW_SR_BUSY_BIT)) {
		if (k_uptime_get() > timeout) {
			LOG_ERR("spi tx available timeout error\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static int rx_available(void)
{
	int64_t timeout = k_uptime_get() + TIMEOUT_MS;

	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	while (((regs->sr & DW_SR_RFNE_BIT) == 0) || ((regs->sr & DW_SR_BUSY_BIT) == DW_SR_BUSY_BIT)) {
		if (k_uptime_get() > timeout) {
			LOG_ERR("spi rx available timeout error\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static void qspi_ser_enable(uint32_t slave_num)
{
	uint32_t reg_data;

	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	qspi_ssi_disable();

	reg_data = regs->ser;
	reg_data |= BIT(slave_num);
	regs->ser = reg_data;

	qspi_ssi_enable();
}

static void qspi_ser_disable(uint32_t slave_num)
{
	uint32_t reg_data;

	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	qspi_ssi_disable();

	reg_data = regs->ser;
	reg_data &= ~BIT(slave_num);
	regs->ser = reg_data;

	qspi_ssi_enable();
}

static void qspi_config_ssi_controller(uint32_t addr, uint32_t inst, uint32_t wait_cycle,
									   uint32_t trans_type, uint32_t ddr, uint32_t dfs,
									   uint32_t tmod, uint32_t frf, uint32_t ndf)
{
	uint32_t ctrlr0_val;
	uint32_t spi_ctrlr0_val;
	uint32_t ctrlr1_val;

	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	qspi_ssi_disable();

	spi_ctrlr0_val = addr | inst | wait_cycle | trans_type | ddr;
	regs->spi_ctrlr0 = spi_ctrlr0_val;

	ctrlr0_val = dfs | tmod | frf;
	regs->ctrlr0 = ctrlr0_val;

	ctrlr1_val = ndf;
	regs->ctrlr1 = ctrlr1_val;

	qspi_ssi_enable();
}

static int qspi_ssi_rx_i_o_multi(uint32_t inst, uint32_t offset, uint32_t *buf, uint32_t loop_count)
{
	uint32_t *buffer = (uint32_t *)buf;

	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	for (uint32_t i = 0; i < loop_count; i++) {
		if ((i % 32) == 0) {
			RETURN_IF_ERROR(tx_available());
			regs->drx[0] = inst;
			regs->drx[0] = offset + (4 * i);
			RETURN_IF_ERROR(rx_available());
		}

		buffer[i] = regs->drx[0];
	}

	RETURN_IF_ERROR(qspi_check_busy());

	return 0;
}

static int qspi_ssi_rx_i(uint32_t inst)
{
	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	RETURN_IF_ERROR(tx_available());
	regs->drx[0] = inst;
	RETURN_IF_ERROR(rx_available());

	return regs->drx[0];
}

static int qspi_ssi_tx_i(uint32_t inst)
{
	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	RETURN_IF_ERROR(tx_available());
	regs->drx[0] = inst;
	RETURN_IF_ERROR(qspi_check_busy());

	return 0;
}

static int qspi_ssi_tx_i_o(uint32_t inst, uint32_t offset)
{
	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	RETURN_IF_ERROR(tx_available());
	regs->drx[0] = inst;
	regs->drx[0] = offset;
	RETURN_IF_ERROR(qspi_check_busy());

	return 0;
}

static int qspi_ssi_tx_i_o_d(uint32_t inst, uint32_t offset, uint32_t *data, uint32_t loop_count)
{
	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);

	RETURN_IF_ERROR(tx_available());
	regs->drx[0] = inst;
	regs->drx[0] = offset;

	for (uint32_t i = 0; i < loop_count; i++) {
		regs->drx[0] = data[i];
	}

	RETURN_IF_ERROR(qspi_check_busy());

	return 0;
}

static int check_read_status(void)
{
	qspi_config_ssi_controller(DW_SPI_CTRLR0_ADDR_L_0, DW_SPI_CTRLR0_INST_L_8,
							   DW_SPI_CTRLR0_WAIT_CYCLES_0, DW_SPI_CTRLR0_TRANS_TYPE_TT0,
							   DW_SPI_CTRLR0_DDR_DISABLE, DW_CTRLR0_DFS_8, DW_CTRLR0_TMOD_RX,
							   DW_CTRLR0_SPI_FRF_STANDARD, DW_CTRLR1_NDF_1WORD);

	return qspi_ssi_rx_i(READ_STATUS_COMMAND);
}

static int check_read_flag_status(void)
{
	qspi_config_ssi_controller(DW_SPI_CTRLR0_ADDR_L_0, DW_SPI_CTRLR0_INST_L_8,
							   DW_SPI_CTRLR0_WAIT_CYCLES_0, DW_SPI_CTRLR0_TRANS_TYPE_TT0,
							   DW_SPI_CTRLR0_DDR_DISABLE, DW_CTRLR0_DFS_8, DW_CTRLR0_TMOD_RX,
							   DW_CTRLR0_SPI_FRF_STANDARD, DW_CTRLR1_NDF_1WORD);

	return qspi_ssi_rx_i(READ_FLAG_STATUS);
}

static int check_flash_available(void)
{
	int64_t timeout = k_uptime_get() + TIMEOUT_MS;

	volatile int ret;

	while ((ret = check_read_flag_status()) < 0 || !(ret & FLASH_READY)) {

		if (k_uptime_get() > timeout) {
			LOG_ERR("spi check flash available timeout error\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static int write_enable_command(void)
{
	qspi_config_ssi_controller(DW_SPI_CTRLR0_ADDR_L_0, DW_SPI_CTRLR0_INST_L_8,
							   DW_SPI_CTRLR0_WAIT_CYCLES_0, DW_SPI_CTRLR0_TRANS_TYPE_TT0,
							   DW_SPI_CTRLR0_DDR_DISABLE, DW_CTRLR0_DFS_8, DW_CTRLR0_TMOD_TX,
							   DW_CTRLR0_SPI_FRF_STANDARD, DW_CTRLR1_NDF_1WORD);

	RETURN_IF_ERROR(qspi_ssi_tx_i(WRITE_ENABLE_COMMAND));

	return 0;
}

static int check_write_enable_command_available(void)
{
	int64_t timeout = k_uptime_get() + TIMEOUT_MS;

	volatile int ret;

	while ((ret = check_read_status()) < 0 || !(ret & WRITE_ENABLE_LATCH)) {

		if (k_uptime_get() > timeout) {
			LOG_ERR("spi check write enable command timeout error\n");
			return -ETIMEDOUT;
		}
	}
	return 0;
}

void erase_flash(const struct device *d, uint32_t erase_cmd, uint32_t offset)
{
	uint64_t backup_sac_addr = cmrt_sac_get_base(NULL);
	uint64_t base = QSPI_SAMSUNG_REGS(d);

	cmrt_sac_set_base(NULL, base);

	qspi_ser_enable(DW_SSI_DEFAULT_SLAVE);

	END_IF_ERROR(write_enable_command());

	END_IF_ERROR(check_write_enable_command_available());

	qspi_config_ssi_controller(DW_SPI_CTRLR0_ADDR_L_0, DW_SPI_CTRLR0_INST_L_8,
							   DW_SPI_CTRLR0_WAIT_CYCLES_0, DW_SPI_CTRLR0_TRANS_TYPE_TT0,
							   DW_SPI_CTRLR0_DDR_DISABLE, DW_CTRLR0_DFS_24, DW_CTRLR0_TMOD_TX,
							   DW_CTRLR0_SPI_FRF_STANDARD, DW_CTRLR1_NDF_1WORD);

	END_IF_ERROR(qspi_ssi_tx_i_o(erase_cmd, offset));

	END_IF_ERROR(check_flash_available());

	qspi_ser_disable(DW_SSI_DEFAULT_SLAVE);

	cmrt_sac_set_base(NULL, backup_sac_addr);
}

static int raw_write_flash(uint32_t inst, uint32_t offset, void *data, uint32_t size)
{
	uint32_t *arr = (uint32_t *)data;
	const uint32_t loop_count = size / sizeof(uint32_t);

	RETURN_IF_ERROR(write_enable_command());

	RETURN_IF_ERROR(check_write_enable_command_available());

	qspi_config_ssi_controller(DW_SPI_CTRLR0_ADDR_L_24, DW_SPI_CTRLR0_INST_L_8,
							   DW_SPI_CTRLR0_WAIT_CYCLES_0, DW_SPI_CTRLR0_TRANS_TYPE_TT0,
							   DW_SPI_CTRLR0_DDR_DISABLE, DW_CTRLR0_DFS_32, DW_CTRLR0_TMOD_TX,
							   DW_CTRLR0_SPI_FRF_QSPI, loop_count - 1);

	RETURN_IF_ERROR(qspi_ssi_tx_i_o_d(inst, offset, arr, loop_count));

	RETURN_IF_ERROR(check_flash_available());

	return 0;
}

static void qspi_config_xip(void);
int write_flash(const struct device *d, uint32_t inst, uint32_t offset, void *data, uint32_t size)
{
	uint64_t backup_sac_addr = cmrt_sac_get_base(NULL);
	const uint32_t write_count = size / 256;
	uint32_t *arr = (uint32_t *)data;
	uint64_t base = QSPI_SAMSUNG_REGS(d);

	cmrt_sac_set_base(NULL, base);

	qspi_ser_enable(DW_SSI_DEFAULT_SLAVE);

	for (int i = 0; i < write_count; i++) {
		RETURN_IF_ERROR(raw_write_flash(inst, offset, (void *)&arr[i * 64], 256));
		offset += 256;
	}

	if ((size % 256) > 0)
		RETURN_IF_ERROR(raw_write_flash(inst, offset, (void *)&arr[write_count * 64], size % 256));

	qspi_ser_disable(DW_SSI_DEFAULT_SLAVE);

	qspi_config_xip();

	cmrt_sac_set_base(NULL, backup_sac_addr);

	return 0;
}

int write_flash_wrapper(uint32_t offset, uint32_t *data, uint32_t data_size)
{
	const struct device *d = device_get_binding("QSPI");

	erase_flash(d, ERASE_4KB_COMMAND, offset);
	return write_flash(d, PROGRAM_COMMAND, offset, (void *)data, data_size);
}

void read_flash(const struct device *d, uint32_t inst, uint32_t offset, void *buffer, uint32_t size)
{
	uint64_t backup_sac_addr = cmrt_sac_get_base(NULL);
	uint32_t loop_count = size / sizeof(uint32_t);
	uint64_t base = QSPI_SAMSUNG_REGS(d);

	cmrt_sac_set_base(NULL, base);

	qspi_ser_enable(DW_SSI_DEFAULT_SLAVE);

	qspi_config_ssi_controller(DW_SPI_CTRLR0_ADDR_L_24, DW_SPI_CTRLR0_INST_L_8,
							   DW_SPI_CTRLR0_WAIT_CYCLES_8, DW_SPI_CTRLR0_TRANS_TYPE_TT1,
							   DW_SPI_CTRLR0_DDR_EN, DW_CTRLR0_DFS_32, DW_CTRLR0_TMOD_RX,
							   DW_CTRLR0_SPI_FRF_QSPI, loop_count - 1);

	END_IF_ERROR(qspi_ssi_rx_i_o_multi(inst, offset, buffer, loop_count));

	qspi_ser_disable(DW_SSI_DEFAULT_SLAVE);

	cmrt_sac_set_base(NULL, backup_sac_addr);
}

static void qspi_config_xip(void)
{
	volatile struct dw_ssi_regs *const regs = (struct dw_ssi_regs *)(CMRT_SAC_BASE + R_CPU_DATA);
	uint32_t ctrl_val;

	qspi_ssi_disable();

	regs->baudr = QSPI_BAUDR;

	regs->xip_incr_inst = NOR_CMD_QAUD_IO_WORD_READ;
	regs->xip_wrap_inst = NOR_CMD_QAUD_IO_WORD_READ;

	ctrl_val = XIP_QUAD_SPI_FORMAT | XIP_TRANS_TYPE_TT1 | XIP_ADDR_L_24 | XIP_WAIT_CYCLES_4;
	ctrl_val |= XIP_DFS_HC | XIP_INST_EN | XIP_MBL_8 | XIP_INST_L_8;
	regs->xip_ctrl = ctrl_val;

	regs->ctrlr0 |= DW_CTRLR0_DFS_32 | DW_CTRLR0_SPI_FRF_QSPI;

	qspi_ssi_enable();
}

static const struct qspi_samsung_api qspi_samsung_driver_api = {
	.write = write_flash,
	.read = read_flash,
	.erase = erase_flash,
};

static int qspi_init(const struct device *d)
{
	uint64_t backup_sac_addr = cmrt_sac_get_base(NULL);
	uint64_t base = QSPI_SAMSUNG_REGS(d);

	cmrt_sac_set_base(NULL, base);

	qspi_ssi_disable();
	qspi_int_disable();
	qspi_config_xip();
	qspi_ssi_enable();

	cmrt_sac_set_base(NULL, backup_sac_addr);

	return 0;
}

#define SAMSUNG_SPI_DEVICE_INIT(inst_num)											\
	static const struct qspi_samsung_device_config qspi_samsung_cfg_##inst_num = {	\
		.base = DT_INST_REG_ADDR(inst_num),											\
	};																				\
																					\
	DEVICE_DT_INST_DEFINE(															\
		inst_num,																	\
		&qspi_init,																	\
		NULL,																		\
		NULL,																		\
		&qspi_samsung_cfg_##inst_num,												\
		PRE_KERNEL_2,																\
		CONFIG_KERNEL_INIT_PRIORITY_DEVICE,											\
		&qspi_samsung_driver_api)

DT_INST_FOREACH_STATUS_OKAY(SAMSUNG_SPI_DEVICE_INIT);
