/*
 * Copyright 2025 Samsung Electronics Co, Ltd. All Rights Reserved.
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

/* dwc_ssi 2.00a, qspi */
#include <device.h>
#include <kernel.h>

/* CTRLR0 settings */
#define DW_CTRLR0_SCPH_BIT		(8)
#define DW_CTRLR0_SCPOL_BIT		(9)
#define DW_CTRLR0_SRL_BIT		(13)

#define DW_CTRLR0_SCPH			(BIT(DW_CTRLR0_SCPH_BIT))
#define DW_CTRLR0_SCPOL			(BIT(DW_CTRLR0_SCPOL_BIT))
#define DW_CTRLR0_SRL			(BIT(DW_CTRLR0_SRL_BIT))

#define DW_CTRLR0_SSI_IS_MST_BIT	(31)
#define DW_CTRLR0_SSI_IS_CONTROLLER	(uint32_t)((uint32_t)1 << DW_CTRLR0_SSI_IS_MST_BIT)
#define DW_CTRLR0_SSI_IS_TARGET		(uint32_t)(0 << DW_CTRLR0_SSI_IS_MST_BIT)

#define DW_CTRLR0_SLV_OE_BIT		(12)
#define DW_CTRLR0_SLV_OE			(0x1 << DW_CTRLR0_SLV_OE_BIT)

#define DW_CTRLR0_TMOD_BIT			(10)

#define DW_CTRLR0_TMOD_TX_RX		(0)
#define DW_CTRLR0_TMOD_TX			(0x1 << DW_CTRLR0_TMOD_BIT)
#define DW_CTRLR0_TMOD_RX			(0x2 << DW_CTRLR0_TMOD_BIT)
#define DW_CTRLR0_TMOD_EEPROM		(0x3 << DW_CTRLR0_TMOD_BIT)
#define DW_CTRLR0_TMOD_RESET		(0x3 << DW_CTRLR0_TMOD_BIT)

#define DW_CTRLR0_SPI_FRF_BIT		(22)
#define DW_CTRLR0_SPI_FRF_STANDARD	(0x00 << DW_CTRLR0_SPI_FRF_BIT)
#define DW_CTRLR0_SPI_FRF_QSPI		(0x2 << DW_CTRLR0_SPI_FRF_BIT)

/* IMR values */
#define DW_IMR_XRXOIM_BIT		(6)
#define DW_IMR_TXUIM_BIT		(7)
#define DW_IMR_AXIEM_BIT		(8)
#define DW_IMR_SPITEM_BIT		(10)
#define DW_IMR_DONEM_BIT		(11)

/* SPI_CTRLR0 values */
#define DW_SPI_CTRLR0_CLK_STRETCH_EN_BIT	(30)
#define DW_SPI_CTRLR0_CLK_STRETCH_EN_DISABLE	(BIT(DW_SPI_CTRLR0_CLK_STRETCH_EN_BIT))
#define DW_SPI_CTRLR0_CLK_STRETCH_EN_ENABLE	(0x0 << DW_SPI_CTRLR0_CLK_STRETCH_EN_BIT)

#define DW_SPI_CTRLR0_WAIT_CYCLES_BIT		(11)
#define DW_SPI_CTRLR0_WAIT_CYCLES_0			(0 << DW_SPI_CTRLR0_WAIT_CYCLES_BIT)
#define DW_SPI_CTRLR0_WAIT_CYCLES_4			(0x4 << DW_SPI_CTRLR0_WAIT_CYCLES_BIT)
#define DW_SPI_CTRLR0_WAIT_CYCLES_6			(0x6 << DW_SPI_CTRLR0_WAIT_CYCLES_BIT)
#define DW_SPI_CTRLR0_WAIT_CYCLES_8			(0x8 << DW_SPI_CTRLR0_WAIT_CYCLES_BIT)
#define DW_SPI_CTRLR0_WAIT_CYCLES_10		(0x10 << DW_SPI_CTRLR0_WAIT_CYCLES_BIT)
#define DW_SPI_CTRLR0_WAIT_CYCLES_24		(0x18 << DW_SPI_CTRLR0_WAIT_CYCLES_BIT)

#define DW_SPI_CTRLR0_INST_L_BIT			(8)
#define DW_SPI_CTRLR0_INST_L_8				(0x2 << DW_SPI_CTRLR0_INST_L_BIT)

#define DW_SPI_CTRLR0_ADDR_L_BIT			(2)
#define DW_SPI_CTRLR0_ADDR_L_24				(0x06 << DW_SPI_CTRLR0_ADDR_L_BIT)
#define DW_SPI_CTRLR0_ADDR_L_0				(0x00 << DW_SPI_CTRLR0_ADDR_L_BIT)
#define DW_SPI_CTRLR0_ADDR_L_8				(0x02 << DW_SPI_CTRLR0_ADDR_L_BIT)

#define DW_SPI_CTRLR0_TRANS_TYPE_BIT		(0x0)
#define DW_SPI_CTRLR0_TRANS_TYPE_TT0		(0x0 << DW_SPI_CTRLR0_TRANS_TYPE_BIT)
#define DW_SPI_CTRLR0_TRANS_TYPE_TT1		(BIT(DW_SPI_CTRLR0_TRANS_TYPE_BIT))
#define DW_SPI_CTRLR0_TRANS_TYPE_TT2		(0x2 << DW_SPI_CTRLR0_TRANS_TYPE_BIT)
#define DW_SPI_CTRLR0_TRANS_TYPE			(DW_SPI_CTRLR0_TRANS_TYPE_TT2)

#define DW_SPI_CTRLR0_DDR_EN				(0x1 << 16)
#define DW_SPI_CTRLR0_DDR_DISABLE			(0 << 16)

#define DW_TXFTLR_BIT						(16)
#define DW_TXFTLR_0WORD						(0)
#define DW_TXFTLR_1WORD						(BIT(DW_TXFTLR_BIT))
#define DW_TXFTLR_16WORD					(0x10 << DW_TXFTLR_BIT)

#define DW_CTRLR1_BIT						(0)
#define DW_CTRLR1_NDF_1WORD					(0 << DW_CTRLR1_BIT)
#define DW_CTRLR1_NDF_16WORD				(15 << DW_CTRLR1_BIT)

#define DW_INSTRUCTION_WRITE				(0x80)			/* 1 word */
#define DW_INSTRUCTION_WRITE_16WORD			(0x83)			/* 16 word */
#define DW_INSTRUCTION_WRITE_2WAIT			(0x10)

#define DW_INSTRUCTION_WRITE_STATUS_2WAIT	(0xD0)

#define DW_INSTRUCTION_READ_REQ				(0x20)
#define DW_INSTRUCTION_READ_0WAIT			(0x00)
#define DW_INSTRUCTION_READ_2WAIT			(0x10)
#define DW_INSTRUCTION_READ_8WAIT			(0x60)
#define DW_INSTRUCTION_READ_16WAIT			(0x68)
#define DW_INSTRUCTION_READ_24WAIT			(0x70)

#define DW_INSTRUCTION_READ_32				(0x04)
#define DW_INSTRUCTION_READ_16				(0x03)

#define DW_INSTRUCTION_READ_STATUS_0WAIT	(0x40)
#define DW_INSTRUCTION_READ_STATUS_1WAIT	(0x48)
#define DW_INSTRUCTION_READ_STATUS_2WAIT	(0x50)

/* SYSREG address, 0x1E04310004 at ML3_DEV04 temporarily */
#define DW_SYSREG_ADDRESS					(0x1E04310160)

/* todo - other DFS */
#define DW_CTRLR0_DFS_8			(0x07)
#define DW_CTRLR0_DFS_24		(0x17)
#define DW_CTRLR0_DFS_32		(0x1F)

#define DW_SSIENR_ENABLE		(1)
#define DW_SSIENR_DISABLE		(0)

/* SR bits and values */
#define DW_SR_BUSY_BIT			(0x1 << 0)
#define DW_SR_TFNF_BIT			(0x1 << 1)
#define DW_SR_RFNE_BIT			(0x1 << 3)

#define DW_IMR_MASK				(0x0)
#define DW_IMR_TXEIM_BIT		(0)
#define DW_IMR_TXOIM_BIT		(1)
#define DW_IMR_RXUIM_BIT		(2)
#define DW_IMR_RXOIM_BIT		(3)
#define DW_IMR_RXFIM_BIT		(4)
#define DW_IMR_MSTIM_BIT		(5)

/* IMR values */
#define DW_IMR_TXEIM		(BIT(DW_IMR_TXEIM_BIT))
#define DW_IMR_TXOIM		(BIT(DW_IMR_TXOIM_BIT))
#define DW_IMR_RXUIM		(BIT(DW_IMR_RXUIM_BIT))
#define DW_IMR_RXOIM		(BIT(DW_IMR_RXOIM_BIT))
#define DW_IMR_RXFIM		(BIT(DW_IMR_RXFIM_BIT))
#define DW_IMR_MSTIM		(BIT(DW_IMR_MSTIM_BIT))

/* ISR values (same as IMR) */
#define DW_ISR_TXEIS		DW_IMR_TXEIM
#define DW_ISR_TXOIS		DW_IMR_TXOIM
#define DW_ISR_RXUIS		DW_IMR_RXUIM
#define DW_ISR_RXOIS		DW_IMR_RXOIM
#define DW_ISR_RXFIS		DW_IMR_RXFIM
#define DW_ISR_MSTIS		DW_IMR_MSTIM

#define DW_IMR_UNMASK		(DW_IMR_TXEIM | \
					 DW_IMR_TXOIM | \
					 DW_IMR_RXUIM | \
					 DW_IMR_RXOIM | \
					 DW_IMR_RXFIM)

#define DW_IMR_MASK_TX		(~(DW_IMR_TXEIM | \
					   DW_IMR_TXOIM))

#define DW_IMR_MASK_RX		(~(DW_IMR_RXUIM | \
					   DW_IMR_RXOIM | \
					   DW_IMR_RXFIM))

#define DW_ISR_ERRORS_MASK		(DW_ISR_TXOIS | \
					 DW_ISR_RXUIS | \
					 DW_ISR_RXOIS | \
					 DW_ISR_MSTIS)

#define DW_FIFO_DEPTH					(32)
#define ERASE_4KB_COMMAND				(0x20)
#define ERASE_64KB_COMMAND				(0xD8)
#define PROGRAM_COMMAND					(0x32)
#define WRITE_ENABLE_LATCH				(0x2)
#define NOR_CMD_QAUD_IO_WORD_READ       (0xE7)
#define XIP_QUAD_SPI_FORMAT				(2)
#define XIP_TRANS_TYPE					(2)
#define XIP_TRANS_TYPE_TT1				(0x1 << XIP_TRANS_TYPE)
#define XIP_ADDR_L						(4)
#define XIP_ADDR_L_24					(6 << XIP_ADDR_L)
#define XIP_INST_L						(9)
#define XIP_INST_L_8					(2 << XIP_INST_L)
#define XIP_WAIT_CYCLES					(13)
#define XIP_WAIT_CYCLES_4				(0x4 << XIP_WAIT_CYCLES)
#define XIP_DFS_HC						(0x1 << 18)
#define XIP_DDR_EN						(0x1 << 19)
#define XIP_INST_EN						(0x1 << 22)
#define XIP_CONT_XFER_EN				(0x1 << 23)
#define XIP_MBL							(26)
#define XIP_MBL_8						(0x2 << XIP_MBL)
#define READ_STATUS_COMMAND				(0x5)
#define WRITE_ENABLE_COMMAND			(6)
#define TXFTHR_1						(1)
#define QSPI_BAUDR						(0x18)
#define DW_SSI_DEFAULT_SLAVE			0
#define READ_FLAG_STATUS				0x70
#define FLASH_READY						(0x1 << 7)
#define FLASH_BUSY						0

#define TIMEOUT_MS						2000

struct dw_ssi_regs {
	/* Offset: 0x00 */
	volatile uint32_t ctrlr0;	/* Control Register 0								(RW) */
	volatile uint32_t ctrlr1;	/* Control Register 1								(RW) */
	volatile uint32_t ssienr;	/* SSI Enable Register							(RW) */
	volatile uint32_t mwcr;		/* Microwire Control Register						(RW) */

	/* Offset: 0x10 */
	volatile uint32_t ser;		/* Target Enable Register							(RW) */
	volatile uint32_t baudr;	/* Baud Rate Select									(RW) */
	volatile uint32_t txftlr;	/* Transmit FIFO Threshold Level					(RW) */
	volatile uint32_t rxftlr;	/* Receive FIFO Threshold Level						(RW) */

	/* Offset: 0x20 */
	volatile uint32_t txflr;	/* Transmit FIFO Level Register						(RW) */
	volatile uint32_t rxflr;	/* Receive FIFO Level Register						(RW) */
	volatile uint32_t sr;		/* Status Register									(RW) */
	volatile uint32_t imr;		/* Interrupt Mask Register							(RW) */

	/* Offset: 0x30 */
	volatile uint32_t isr;		/* Interrupt Status Register						(RW) */
	volatile uint32_t risr;		/* Raw Interrupt Status Register					(RW) */
	union {
		volatile uint32_t txeicr;	/* dwc_ssi - Transmit FIFO Error Int Clear Registers	(RW) */
		volatile uint32_t txoicr;	/* apb_ssi- Transmit FIFO Overflow Int Clear Registers	(RW) */
	};
	volatile uint32_t rxoicr;	/* Receive FIFO Overflow Interrupt Clear Register	(RW) */

	/* Offset: 0x40 */
	volatile uint32_t rxuicr;	/* Receive FIFO Underflow Interrupt Clear Register	(RW) */
	volatile uint32_t msticr;	/* Multi-Controller Interrupt Clear Register		(RW) */
	volatile uint32_t icr;		/* Interrupt Clear Register							(RW) */
	volatile uint32_t dmacr;	/* DMA Control Register								(RW) */

	/* Offset: 0x50 */
	union {
		volatile uint32_t dmatdlr;	/* DMA Transmit Data Level							(RW) */
		volatile uint32_t axiawlen; /* Destination Burst Length							(RW) */
	};
	union {
		volatile uint32_t dmardlr;	/* DMA Receive Data Level							(RW) */
		volatile uint32_t axiarlen; /* Source Burst Length								(RW) */
	};
	volatile uint32_t idr;			   /* Identification Register						(RW) */
	volatile uint32_t ssic_version_id; /* DWC_ssi component version						(RW) */

	/* Offset: 0x60 */
	volatile uint32_t drx[36]; /* Identification Register								(RW) */

	/* Offset: 0xF0 */
	volatile uint32_t rx_sample_delay; /* RX Sample Delay Register						(RW) */
	volatile uint32_t spi_ctrlr0;	   /* SPI_CTRLR0 - SPI Control Register				(RW) */
	union {
		volatile uint32_t ddr_drive_edge;  /* dwc_ssi - Transmit Drive Edge Register	(RW) */
		volatile uint32_t txd_drive_edge;  /* apb_ssi - Transmit Drive Edge Register	(RW) */
	};
	volatile uint32_t xip_mode_bits;   /* eXecute in Place - Mode bits					(RW) */

	/* Offset: 0x100 */
	volatile uint32_t xip_incr_inst;
	volatile uint32_t xip_wrap_inst;
	volatile uint32_t xip_ctrl;
	volatile uint32_t xip_ser;

	/* Offset: 0x110 */
	volatile uint32_t xip_xrxoicr;
	volatile uint32_t xip_cnt_time_out;
	volatile uint32_t spi_ctrlr1;
	volatile uint32_t spitecr;

	/* Offset: 0x120 */
	volatile uint32_t spidr;
	volatile uint32_t spiar;
	volatile uint32_t axiar0;
	volatile uint32_t axiar1;

	/* Offset: 0x130 */
	volatile uint32_t axiecr;
	volatile uint32_t donecr;
	volatile uint32_t reserved[1];

	/* Offset: 0x140 */
	volatile uint32_t xip_write_incr_inst;
	volatile uint32_t xip_write_wrap_inst;
	volatile uint32_t xip_write_ctrl;
};

typedef void (*qspi_samsung_callback_t)(const struct device *ipmdev, const int chan);
typedef void (*qspi_samsung_callback_t)(const struct device *qspidev, const int chan);
typedef void (*qspi_samsung_read_t)(const struct device *qspidev, uint32_t inst, uint32_t offset,
									void *data, uint32_t size);
typedef int (*qspi_samsung_write_t)(const struct device *qspidev, uint32_t inst, uint32_t offset,
									void *buffer, uint32_t size);
typedef void (*qspi_samsung_erase_t)(const struct device *qspidev, uint32_t erase_cmd,
									uint32_t offset);
typedef void (*qspi_samsung_register_callback_t)(const struct device *qspidev,
												qspi_samsung_callback_t cb);

struct qspi_samsung_api {
	qspi_samsung_write_t write;
	qspi_samsung_read_t read;
	qspi_samsung_erase_t erase;
	qspi_samsung_register_callback_t register_callback;
};

int write_flash(const struct device *d, uint32_t inst, uint32_t offset, void *data, uint32_t size);
void read_flash(const struct device *d, uint32_t inst, uint32_t offset, void *buffer,
				uint32_t size);
int write_flash_wrapper(uint32_t offset, uint32_t *data, uint32_t data_size);
void erase_flash(const struct device *d, uint32_t erase_cmd, uint32_t offset);
