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

#pragma once

/*	define Register information	*/
#define ENABLE					(0x1 << 0)
#define MASTER_MODE				(0x1 << 0)
#define STANDARD_MODE			(0x1 << 1)
#define FAST_MODE				(0x2 << 1)
#define HIGH_SPEED_MODE			(0x3 << 1)
#define BIT_10_ADDR_SLAVE		(0x1 << 3)
#define BIT_10_ADDR_MASTER		(0x1 << 4)
#define RESTART_EN				(0x1 << 5)
#define SLAVE_DISABLE			(0x1 << 6)
#define I2C_TX_EMPTY			(0x1 << 4)
#define I2C_RX_FULL				(0x1 << 2)
#define I2C_RD_REQ				(0x1 << 5)
#define RD_REQ_MASK				(0x1 << 5)
#define MST_ACTIVITY			(0x1 << 5)
#define SPECIAL					(0x1 << 11)
#define STOP					(0x1 << 9)
#define STOP_DET				(0x1 << 9)
#define RESTART					(0x1 << 10)
#define ACTIVITY				(0x1 << 0)
#define RX_FULL_MASK			(0x1 << 2)
#define TX_EMPTY_MASK			(0x1 << 4)
#define ACTIVITY_MASK			(0x1 << 8)
#define TFNF					(0x1 << 1)
#define RFNE					(0x1 << 3)
#define TFE						(0x1 << 2)
#define RFF						(0x1 << 4)
#define I2C_RX                  (0x1 << 8)
#define I2C_TX                  (0x0 << 8)
#define SOURCE_CLOCK			250000000
#define DEFAULT_FREQ			400000
#define MIN_SS_HCNT				0x1E
#define MIN_FS_HCNT				0x1E
#define MIN_HS_HCNT				0xA
#define MIN_SS_LCNT				0x20
#define MIN_FS_LCNT				0x20
#define MIN_HS_LCNT				0xC

#define UNMASK_ALL_INTR			0x7FFF
#define HS_MAR					0x1
#define AND_1B                  0xFF
#define SPEED_CLR               0x6
#define RX_THRESHOLD_MAX		0
#define TX_THRESHOLD_MAX		0
#define I2C0_PERI0_ID			0
#define I2C1_PERI0_ID			1
#define I2C0_PERI1_ID			2
#define I2C1_PERI1_ID			3
#define I2C_INSTANCE_COUNT		4
#define SHIFT_16BIT				16
#define SHIFT_8BIT				8
#define BYTE_4					4
#define	BYTE_2					2
#define BYTE_1					1
#define BIT_8					8
#define ACK_TIMEOUT				1000000
#define MASTER					1
#define	SLAVE					0
#define SLAVE_ADDR				0x20
#define SDA_HOLD_DEFAULT		0x300030

struct dw_apb_i2c_regs {
	/* offset : 0x00	*/
	volatile uint32_t con;
	volatile uint32_t tar;
	volatile uint32_t sar;
	volatile uint32_t hs_maddr;

	/* offset : 0x10    */
	volatile uint32_t data_cmd;
	union{
		volatile uint32_t ss_scl_hcnt;
		volatile uint32_t ufm_scl_hcnt;
	};
	union{
		volatile uint32_t ss_scl_lcnt;
		volatile uint32_t ufm_scl_lcnt;
	};
	union{
		volatile uint32_t fs_scl_hcnt;
		volatile uint32_t ufm_tbuf_cnt;
	};
	/* offset : 0x20    */
	volatile uint32_t fs_scl_lcnt;
	volatile uint32_t hs_scl_hcnt;
	volatile uint32_t hs_scl_lcnt;
	volatile uint32_t intr_stat;
	/* offset : 0x30    */
	volatile uint32_t intr_mask;
	volatile uint32_t raw_intr_stat;
	volatile uint32_t rx_tl;
	volatile uint32_t tx_tl;

	/* offset : 0x40    */
	volatile uint32_t clr_intr;
	volatile uint32_t clr_rx_under;
	volatile uint32_t clr_rx_over;
	volatile uint32_t clr_tx_over;

	/* offset : 0x50    */
	volatile uint32_t clr_rd_req;
	volatile uint32_t clr_tx_abrt;
	volatile uint32_t clr_rx_done;
	volatile uint32_t clr_activity;

	/* offset : 0x60    */
	volatile uint32_t clr_stop_det;
	volatile uint32_t clr_start_det;
	volatile uint32_t clr_gen_call;
	volatile uint32_t enable;

	/* offset : 0x70    */
	volatile uint32_t status;
	volatile uint32_t txflr;
	volatile uint32_t rxflr;
	volatile uint32_t sda_hold;

	/* offset : 0x80    */
	volatile uint32_t tx_abrt_source;
	volatile uint32_t slv_data_nack_only;
	volatile uint32_t dma_cr;
	volatile uint32_t dma_tdlr;

	/* offset : 0x90    */
	volatile uint32_t dma_rdlr;
	volatile uint32_t dma_setup;
	volatile uint32_t ack_general_call;
	volatile uint32_t enable_status;

	/* offset : 0xa0    */
	union{
		volatile uint32_t fs_spklen;
		volatile uint32_t ufm_spklen;
	};
	volatile uint32_t hs_spklen;
	volatile uint32_t clr_restart_det;
	volatile uint32_t scl_stuck_at_low_timeout;

	/* offset : 0xb0    */
	volatile uint32_t sda_stuck_at_low_timeout;
	volatile uint32_t clr_scl_stuck_det;
	volatile uint32_t device_id;
	volatile uint32_t smbus_clock_low_sext;

	/* offset : 0xc0    */
	volatile uint32_t smbus_clock_low_mext;
	volatile uint32_t smbus_thigh_max_idle_count;
	volatile uint32_t smbus_intr_stat;
	volatile uint32_t smbus_intr_mask;

	/* offset : 0xd0    */
	volatile uint32_t smbus_intr_raw_status;
	volatile uint32_t clr_smbus_intr;
	volatile uint32_t optional_sar;
	volatile uint32_t smbus_udid_lsb;

	/* offset : 0xe0 ~ 0xf3    */
	volatile uint32_t reserved[(0xf4 - 0xe0) / sizeof(uint32_t)];

	/* offset : 0xf4    */
	volatile uint32_t comp_param_1;
	volatile uint32_t comp_version;
	volatile uint32_t comp_type;
};

struct dw_apb_i2c_config {
	struct dw_apb_i2c_regs *regs;
	uint32_t irq_num;
	uint32_t irq_prio;
	uint8_t *data;
	uint8_t len;
	volatile uint32_t idx;
	uint32_t mode;
	uint32_t slave_addr;
};

#define I2C_TX_ABRT             (0x1 << 6)
#define STOP_DET_INTR           (0x1 << 9)
#define IC_ENABLE_ABORT         (0x1 << 1)
#define I2C_PROBE_TIMEOUT       5000
int i2c_probe_device(struct dw_apb_i2c_config *config);
void i2c_enable_interrupt(struct dw_apb_i2c_config *config, uint32_t value);
void i2c_disable_interrupt(struct dw_apb_i2c_config *config, uint32_t value);
void i2c_configure_baudrate(struct dw_apb_i2c_config *config, uint32_t source_clk, uint32_t target_freq);
void i2c_set_sar(struct dw_apb_i2c_config *config, uint16_t slave_address);
uint32_t i2c_get_sar(struct dw_apb_i2c_config *config);
void i2c_set_tar(struct dw_apb_i2c_config *config, uint16_t device_address);
uint32_t i2c_get_tar(struct dw_apb_i2c_config *config);
void i2c_putdata(struct dw_apb_i2c_config *config, int data);
int i2c_putready(struct dw_apb_i2c_config *config);
int i2c_getdata(struct dw_apb_i2c_config *config);
int i2c_getready(struct dw_apb_i2c_config *config);
int i2c_tfe_ready(struct dw_apb_i2c_config *config);
int i2c_busy_check(struct dw_apb_i2c_config *config);
void i2c_set_master_mode(struct dw_apb_i2c_config *config);
void i2c_set_slave_mode(struct dw_apb_i2c_config *config);
int i2c_intr_timeout_high(struct dw_apb_i2c_config *config, uint32_t status_reg);
int i2c_intr_timeout_low(struct dw_apb_i2c_config *config, uint32_t status_reg);
int i2c_idle_ready(struct dw_apb_i2c_config *config);
