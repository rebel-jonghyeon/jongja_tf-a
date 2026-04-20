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

#include <util.h>
#include <rebel_h_platform.h>
#include <stdlib.h>
#include <driver.h>
#include <interrupt.h>
#include "i2c.h"
#include "gic.h"
#include "rl_errors.h"
#include "cpu.h"

struct dw_apb_i2c_config i2c_config[] = {
	{
	.regs		= (struct dw_apb_i2c_regs *)I2C0_PERI0,
	.irq_num	= 202,
	.irq_prio	= 6,
	.data		= NULL,
	.len		= 0,
	.idx		= 0,
	.mode		= MASTER,
	.slave_addr = SLAVE_ADDR,
	},

	{
	.regs		= (struct dw_apb_i2c_regs *)I2C1_PERI0,
	.irq_num	= 203,
	.irq_prio	= 6,
	.data		= NULL,
	.len		= 0,
	.idx		= 0,
	.mode		= SLAVE,
	.slave_addr = SLAVE_ADDR,
	},

	{
	.regs		= (struct dw_apb_i2c_regs *)I2C0_PERI1,
	.irq_num	= 252,
	.irq_prio	= 6,
	.data		= NULL,
	.len		= 0,
	.idx		= 0,
	.mode		= MASTER,
	.slave_addr = SLAVE_ADDR,
	},

	{
	.regs		= (struct dw_apb_i2c_regs *)I2C1_PERI1,
	.irq_num	= 253,
	.irq_prio	= 6,
	.data		= NULL,
	.len		= 0,
	.idx		= 0,
	.mode		= MASTER,
	.slave_addr = SLAVE_ADDR,
	}
};

int i2c_probe_device(struct dw_apb_i2c_config *config)
{
	struct dw_apb_i2c_regs *regs = config->regs;
	uint32_t count;
	uint32_t saved_intr_mask;
	uint32_t stat;
	int ret = RL_TIMEOUT;

	(void)regs->clr_tx_abrt;
	(void)regs->clr_stop_det;
	__DSB();

	saved_intr_mask = regs->intr_mask;
	regs->intr_mask = 0;
	__DSB();

	for (count = 0; count < I2C_PROBE_TIMEOUT; count++) {
		if (regs->status & TFNF)
			break;
	}
	if (!(regs->status & TFNF)) {
		ret = RL_TIMEOUT;
		goto probe_done;
	}

	regs->data_cmd = I2C_RX | STOP;
	__DSB();

	for (count = 0; count < I2C_PROBE_TIMEOUT; count++) {
		stat = regs->raw_intr_stat;

		if (stat & I2C_TX_ABRT) {
			printf("NACK: addr=0x%x, abrt_src=0x%x\n",
			       i2c_get_tar(config), regs->tx_abrt_source);
			(void)regs->clr_tx_abrt;
			__DSB();

			for (count = 0; count < I2C_PROBE_TIMEOUT; count++) {
				if (regs->raw_intr_stat & STOP_DET_INTR)
					break;
			}
			(void)regs->clr_stop_det;
			__DSB();

			ret = RL_ERROR;
			goto probe_done;
		}
		if (stat & STOP_DET_INTR) {
			(void)regs->clr_stop_det;
			if (regs->status & RFNE)
				(void)regs->data_cmd;
			ret = RL_OK;
			goto probe_done;
		}
	}

	regs->enable |= IC_ENABLE_ABORT;
	__DSB();
	for (count = 0; count < I2C_PROBE_TIMEOUT; count++) {
		if (!(regs->enable & IC_ENABLE_ABORT))
			break;
	}
	(void)regs->clr_tx_abrt;
	(void)regs->clr_stop_det;
	__DSB();
	ret = RL_TIMEOUT;

probe_done:
	regs->intr_mask = saved_intr_mask;
	__DSB();
	return ret;
}

static int i2c_intr_stat(struct dw_apb_i2c_config *config, int value)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	return (regs->intr_stat & value);
}

static void i2c_clr_intr(struct dw_apb_i2c_config *config)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	(void)regs->clr_intr;
}

static void i2c_clr_rd_req(struct dw_apb_i2c_config *config)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	(void)regs->clr_rd_req;
}

void i2c_enable_interrupt(struct dw_apb_i2c_config *config, uint32_t value)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	regs->intr_mask |= value;
}

void i2c_disable_interrupt(struct dw_apb_i2c_config *config, uint32_t value)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	regs->intr_mask &= ~value;
}

static void i2c_disable(struct dw_apb_i2c_config *config)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	regs->enable &= ~ENABLE;
}

static void i2c_enable(struct dw_apb_i2c_config *config)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	regs->enable |= ENABLE;
}

int i2c_intr_timeout_high(struct dw_apb_i2c_config *config, uint32_t status_reg)
{
	struct dw_apb_i2c_config *cfg = config;
	volatile struct dw_apb_i2c_regs *regs = cfg->regs;
	uint32_t count = 0;

	do {
		if (count++ > ACK_TIMEOUT) {
			return RL_TIMEOUT;
		}
	} while ((cfg->idx != cfg->len) || !(regs->status & status_reg));

	__DSB();

	return RL_OK;
}

int i2c_intr_timeout_low(struct dw_apb_i2c_config *config, uint32_t status_reg)
{
	struct dw_apb_i2c_config *cfg = config;
	volatile struct dw_apb_i2c_regs *regs = cfg->regs;
	uint32_t count = 0;

	do {
		if (count++ > ACK_TIMEOUT) {
			return RL_TIMEOUT;
		}
	} while ((cfg->idx != cfg->len) || (regs->status & status_reg));

	__DSB();

	return RL_OK;
}

static int i2c_status_timeout(struct dw_apb_i2c_config *config, uint32_t status_reg)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);
	uint32_t count = 0;

	if (status_reg == ACTIVITY) {
		do {
			if (count++ > ACK_TIMEOUT) {
				return RL_TIMEOUT;
			}
		} while (regs->status & status_reg);
	} else {
		do {
			if (count++ > ACK_TIMEOUT) {
				return RL_TIMEOUT;
			}
		} while (!(regs->status & status_reg));
	}
	return RL_OK;
}

void i2c_configure_baudrate(struct dw_apb_i2c_config *config, uint32_t source_clk,
							uint32_t target_freq)
{
	struct dw_apb_i2c_config *cfg = config;
	volatile struct dw_apb_i2c_regs *regs = cfg->regs;

	uint32_t scl_period = source_clk / target_freq;
	uint32_t hcnt = scl_period / 2;
	uint32_t lcnt = scl_period - hcnt;

	i2c_disable(cfg);

	/*	speed mode : standard mode	*/
	if (target_freq <= 100000) {
		if (hcnt < MIN_SS_HCNT)
			hcnt = MIN_SS_HCNT;
		if (lcnt < MIN_SS_LCNT)
			lcnt = MIN_SS_LCNT;

		regs->con |= STANDARD_MODE;
		regs->con &= ~FAST_MODE;
		regs->ss_scl_hcnt = hcnt;
		regs->ss_scl_lcnt = lcnt;
	} else if ((target_freq > 100000) && (target_freq <= 1000000)) {
	/*	speed mode : fast mode	*/
		if (hcnt < MIN_FS_HCNT)
			hcnt = MIN_FS_HCNT;
		if (lcnt < MIN_FS_LCNT)
			lcnt = MIN_FS_LCNT;
		regs->con |= FAST_MODE;
		regs->con &= ~STANDARD_MODE;
		regs->fs_scl_hcnt = hcnt;
		regs->fs_scl_lcnt = lcnt;
	} else {
	/*	speed mode : high speed mode	*/
		if (hcnt < MIN_HS_HCNT)
			hcnt = MIN_HS_HCNT;
		if (lcnt < MIN_HS_LCNT)
			lcnt = MIN_HS_LCNT;
		regs->con |= HIGH_SPEED_MODE;
		regs->hs_maddr = HS_MAR;
		regs->hs_scl_hcnt = hcnt;
		regs->hs_scl_lcnt = lcnt;
	}
	i2c_enable(cfg);
}

void i2c_set_sar(struct dw_apb_i2c_config *config, uint16_t slave_address)
{
	struct dw_apb_i2c_config *cfg = config;
	volatile struct dw_apb_i2c_regs *regs = cfg->regs;

	i2c_disable(cfg);

	if ((slave_address >> BIT_8) > 0)
		regs->con |= BIT_10_ADDR_SLAVE;
	else
		regs->con &= ~BIT_10_ADDR_SLAVE;

	regs->sar = slave_address;

	i2c_enable(cfg);
}

uint32_t i2c_get_sar(struct dw_apb_i2c_config *config)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	return (regs->sar & 0x3FF);
}

void i2c_set_tar(struct dw_apb_i2c_config *config, uint16_t device_address)
{
	struct dw_apb_i2c_config *cfg = config;
	volatile struct dw_apb_i2c_regs *regs = cfg->regs;

	i2c_disable(cfg);

	if ((device_address >> BIT_8) > 0)
		regs->con |= BIT_10_ADDR_MASTER;
	else
		regs->con &= ~BIT_10_ADDR_MASTER;

	regs->tar = device_address;

	i2c_enable(cfg);
}

uint32_t i2c_get_tar(struct dw_apb_i2c_config *config)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	return (regs->tar & 0x3FF);
}

void i2c_putdata(struct dw_apb_i2c_config *config, int data)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	regs->data_cmd = data;
}

int i2c_putready(struct dw_apb_i2c_config *config)
{
	struct dw_apb_i2c_config *cfg = config;

	return i2c_status_timeout(cfg, TFNF);
}

int i2c_tfe_ready(struct dw_apb_i2c_config *config)
{
	struct dw_apb_i2c_config *cfg = config;

	return i2c_status_timeout(cfg, TFE);
}

int i2c_getdata(struct dw_apb_i2c_config *config)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	return (uint8_t)regs->data_cmd;
}

int i2c_busy_check(struct dw_apb_i2c_config *config)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	while ((regs->status & ACTIVITY))
		;

	return 0;
}

int i2c_idle_ready(struct dw_apb_i2c_config *config)
{
	struct dw_apb_i2c_config *cfg = config;

	return i2c_status_timeout(cfg, ACTIVITY);
}

int i2c_getready(struct dw_apb_i2c_config *config)
{
	struct dw_apb_i2c_config *cfg = config;

	return i2c_status_timeout(cfg, RFNE);
}

static uint32_t i2c_get_rxflr(struct dw_apb_i2c_config *config)
{
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(config->regs);

	return regs->rxflr;
}

void i2c_set_master_mode(struct dw_apb_i2c_config *config)
{
	struct dw_apb_i2c_config *cfg = config;
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(cfg->regs);

	i2c_disable(cfg);

	regs->con = (SLAVE_DISABLE | RESTART_EN | STANDARD_MODE | MASTER_MODE);
	regs->rx_tl = RX_THRESHOLD_MAX;
	regs->tx_tl = TX_THRESHOLD_MAX;
	regs->sda_hold = SDA_HOLD_DEFAULT;
	i2c_disable_interrupt(cfg, TX_EMPTY_MASK);
	i2c_enable_interrupt(cfg, RX_FULL_MASK);

	cfg->mode = MASTER;

	i2c_enable(cfg);
}

void i2c_set_slave_mode(struct dw_apb_i2c_config *config)
{
	struct dw_apb_i2c_config *cfg = config;
	volatile struct dw_apb_i2c_regs *regs = (struct dw_apb_i2c_regs *)(cfg->regs);

	i2c_disable(cfg);

	regs->con = STANDARD_MODE;
	regs->rx_tl = RX_THRESHOLD_MAX;
	regs->tx_tl = TX_THRESHOLD_MAX;
	regs->sda_hold = SDA_HOLD_DEFAULT;
	if (i2c_get_sar(cfg) != cfg->slave_addr)
		i2c_set_sar(cfg, cfg->slave_addr);

	i2c_enable_interrupt(cfg, RX_FULL_MASK | RD_REQ_MASK);
	i2c_disable_interrupt(cfg, TX_EMPTY_MASK);

	cfg->mode = SLAVE;

	i2c_enable(cfg);
}

static void i2c_isr(void *cb_ref)
{
	if (!cb_ref)
		return;

	struct dw_apb_i2c_config *cfg = (struct dw_apb_i2c_config *)(cb_ref);
	int rx_fl;

	if (cfg->mode == MASTER) {
		if (i2c_intr_stat(cfg, I2C_TX_EMPTY)) {
			i2c_disable_interrupt(cfg, TX_EMPTY_MASK);
			for (int i = 0; i < cfg->len; i++) {
				if (cfg->idx == (cfg->len - 1))
					i2c_putdata(cfg, cfg->data[cfg->idx] | STOP);
				else
					i2c_putdata(cfg, cfg->data[cfg->idx]);
				cfg->idx++;
			}
		}
		if (i2c_intr_stat(cfg, I2C_RX_FULL)) {
			i2c_disable_interrupt(cfg, RX_FULL_MASK);

			rx_fl = i2c_get_rxflr(cfg);
			for (int i = 0; i < rx_fl; i++) {
				cfg->data[cfg->idx] = i2c_getdata(cfg);
				cfg->idx++;
			}
			i2c_enable_interrupt(cfg, RX_FULL_MASK);
		}
	} else if (cfg->mode == SLAVE) {
		if (i2c_intr_stat(cfg, I2C_RX_FULL)) {
			i2c_disable_interrupt(cfg, RX_FULL_MASK);

			rx_fl = i2c_get_rxflr(cfg);
			for (int i = 0; i < rx_fl; i++) {
				cfg->data[cfg->idx] = i2c_getdata(cfg);
				cfg->idx++;
			}
			i2c_enable_interrupt(cfg, RX_FULL_MASK);
		}
		if (i2c_intr_stat(cfg, I2C_RD_REQ)) {
			i2c_disable_interrupt(cfg, RD_REQ_MASK);
			for (int i = 0; i < cfg->len; i++) {
				i2c_putdata(cfg, cfg->data[cfg->idx]);
				cfg->idx++;
			}
			i2c_clr_rd_req(cfg);
			i2c_enable_interrupt(cfg, RD_REQ_MASK);
		}
	}
}

static int i2c_init(void)
{
	for (int i = 0; i < I2C_INSTANCE_COUNT; i++) {
		struct dw_apb_i2c_config *cfg = &i2c_config[i];

		if (cfg->mode == MASTER)
			i2c_set_master_mode(cfg);
		else if (cfg->mode == SLAVE)
			i2c_set_slave_mode(cfg);

		i2c_configure_baudrate(cfg, SOURCE_CLOCK, 400000);

		connect_interrupt_with_handler(i2c_config[i].irq_num, i2c_config[i].irq_prio,
									   IRQ_TYPE_LEVEL, i2c_isr, (void *)(&i2c_config[i]));
	}

	return RL_OK;
}

#ifndef ZEBU_POC
#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(6, i2c_init);
#endif
#endif /* ZEBU_POC */
