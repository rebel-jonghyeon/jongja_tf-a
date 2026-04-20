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

/* dwc_ssi 2.00a, qspi */

/* CTRLR0 settings */
#define DW_SPI_CTRLR0_SCPH_BIT		(8)
#define DW_SPI_CTRLR0_SCPOL_BIT		(9)
#define DW_SPI_CTRLR0_SRL_BIT		(13)

#define DW_SPI_CTRLR0_SCPH			(BIT(DW_SPI_CTRLR0_SCPH_BIT))
#define DW_SPI_CTRLR0_SCPOL			(BIT(DW_SPI_CTRLR0_SCPOL_BIT))
#define DW_SPI_CTRLR0_SRL			(BIT(DW_SPI_CTRLR0_SRL_BIT))

#define DW_SPI_CTRLR0_SSI_IS_MST_BIT		(31)
#define DW_SPI_CTRLR0_SSI_IS_CONTROLLER		(uint32_t)((uint32_t)1 << DW_SPI_CTRLR0_SSI_IS_MST_BIT)
#define DW_SPI_CTRLR0_SSI_IS_TARGET			(uint32_t)(0 << DW_SPI_CTRLR0_SSI_IS_MST_BIT)

#define DW_SPI_CTRLR0_SLV_OE_BIT	(12)
#define DW_SPI_CTRLR0_SLV_OE		(BIT(DW_SPI_CTRLR0_SLV_OE_BIT))

#define DW_SPI_CTRLR0_TMOD_BIT		(10)

#define DW_SPI_CTRLR0_TMOD_TX_RX	(0)
#define DW_SPI_CTRLR0_TMOD_TX		(BIT(DW_SPI_CTRLR0_TMOD_BIT))
#define DW_SPI_CTRLR0_TMOD_RX		(2 << DW_SPI_CTRLR0_TMOD_BIT)
#define DW_SPI_CTRLR0_TMOD_EEPROM	(3 << DW_SPI_CTRLR0_TMOD_BIT)
#define DW_SPI_CTRLR0_TMOD_RESET	(3 << DW_SPI_CTRLR0_TMOD_BIT)

#define DW_SPI_CTRLR0_SPI_FRF_BIT	(22)
#define DW_SPI_CTRLR0_SPI_FRF_STANDARD	(0x00 << DW_SPI_CTRLR0_SPI_FRF_BIT)
#define DW_SPI_CTRLR0_SPI_FRF_QSPI	(0x2 << DW_SPI_CTRLR0_SPI_FRF_BIT)

/* IMR values */
#define DW_SPI_IMR_XRXOIM_BIT		(6)
#define DW_SPI_IMR_TXUIM_BIT		(7)
#define DW_SPI_IMR_AXIEM_BIT		(8)
#define DW_SPI_IMR_SPITEM_BIT		(10)
#define DW_SPI_IMR_DONEM_BIT		(11)

/* SPI_CTRLR0 values */
#define DW_SPI_SPI_CTRLR0_CLK_STRETCH_EN_BIT	(30)
#define DW_SPI_SPI_CTRLR0_CLK_STRETCH_EN_DISABLE	(BIT(DW_SPI_SPI_CTRLR0_CLK_STRETCH_EN_BIT))
#define DW_SPI_SPI_CTRLR0_CLK_STRETCH_EN_ENABLE	(0x0 << DW_SPI_SPI_CTRLR0_CLK_STRETCH_EN_BIT)

#define DW_SPI_SPI_CTRLR0_WAIT_CYCLES_BIT		(11)
#define DW_SPI_SPI_CTRLR0_WAIT_CYCLES_4			(0x4 << DW_SPI_SPI_CTRLR0_WAIT_CYCLES_BIT)
#define DW_SPI_SPI_CTRLR0_WAIT_CYCLES_8			(0x8 << DW_SPI_SPI_CTRLR0_WAIT_CYCLES_BIT)
#define DW_SPI_SPI_CTRLR0_WAIT_CYCLES_24		(0x18 << DW_SPI_SPI_CTRLR0_WAIT_CYCLES_BIT)

#define DW_SPI_SPI_CTRLR0_INST_L_BIT			(8)
#define DW_SPI_SPI_CTRLR0_INST_L_8				(0x2 << DW_SPI_SPI_CTRLR0_INST_L_BIT)

#define DW_SPI_SPI_CTRLR0_ADDR_L_BIT			(2)
#define DW_SPI_SPI_CTRLR0_ADDR_L_24				(0x06 << DW_SPI_SPI_CTRLR0_ADDR_L_BIT)
#define DW_SPI_SPI_CTRLR0_ADDR_L_0				(0x00 << DW_SPI_SPI_CTRLR0_ADDR_L_BIT)
#define DW_SPI_SPI_CTRLR0_ADDR_L_8				(0x02 << DW_SPI_SPI_CTRLR0_ADDR_L_BIT)

#define DW_SPI_SPI_CTRLR0_TRANS_TYPE_BIT		(0x0)
#define DW_SPI_SPI_CTRLR0_TRANS_TYPE_TT0		(0x0 << DW_SPI_SPI_CTRLR0_TRANS_TYPE_BIT)
#define DW_SPI_SPI_CTRLR0_TRANS_TYPE_TT1		(BIT(DW_SPI_SPI_CTRLR0_TRANS_TYPE_BIT))
#define DW_SPI_SPI_CTRLR0_TRANS_TYPE_TT2		(0x2 << DW_SPI_SPI_CTRLR0_TRANS_TYPE_BIT)
#define DW_SPI_SPI_CTRLR0_TRANS_TYPE			(DW_SPI_SPI_CTRLR0_TRANS_TYPE_TT2)

#define DW_SPI_TXFTLR_BIT						(16)
#define DW_SPI_TXFTLR_0WORD						(0)
#define DW_SPI_TXFTLR_1WORD						(BIT(DW_SPI_TXFTLR_BIT))
#define DW_SPI_TXFTLR_16WORD					(0x10 << DW_SPI_TXFTLR_BIT)

#define DW_SPI_CTRLR1_BIT						(0)
#define DW_SPI_CTRLR1_NDF_1WORD					(0 << DW_SPI_CTRLR1_BIT)
#define DW_SPI_CTRLR1_NDF_16WORD				(15 << DW_SPI_CTRLR1_BIT)

#define DW_SPI_INSTRUCTION_WRITE				(0x80)			/* 1 word */
#define DW_SPI_INSTRUCTION_WRITE_16WORD			(0x83)			/* 16 word */
#define DW_SPI_INSTRUCTION_WRITE_2WAIT			(0x10)

#define DW_SPI_INSTRUCTION_WRITE_STATUS_2WAIT	(0xD0)

#define DW_SPI_INSTRUCTION_READ_REQ				(0x20)
#define DW_SPI_INSTRUCTION_READ_0WAIT			(0x00)
#define DW_SPI_INSTRUCTION_READ_2WAIT			(0x10)
#define DW_SPI_INSTRUCTION_READ_8WAIT			(0x60)
#define DW_SPI_INSTRUCTION_READ_16WAIT			(0x68)
#define DW_SPI_INSTRUCTION_READ_24WAIT			(0x70)

#define DW_SPI_INSTRUCTION_READ_32				(0x04)
#define DW_SPI_INSTRUCTION_READ_16				(0x03)

#define DW_SPI_INSTRUCTION_READ_STATUS_0WAIT	(0x40)
#define DW_SPI_INSTRUCTION_READ_STATUS_1WAIT	(0x48)
#define DW_SPI_INSTRUCTION_READ_STATUS_2WAIT	(0x50)

/* SYSREG address, 0x1E04310004 at ML3_DEV04 temporarily */
#define DW_SPI_SYSREG_ADDRESS					(0x1E04310160)

/* todo - other DFS */
#define DW_SPI_CTRLR0_DFS_8			(0x07)
#define DW_SPI_CTRLR0_DFS_32		(0x1F)

#define DW_SPI_SSIENR_ENABLE		(1)
#define DW_SPI_SSIENR_DISABLE		(0)

/* SR bits and values */
#define DW_SPI_SR_BUSY_BIT		(0)
#define DW_SPI_SR_TFNF_BIT		(1)
#define DW_SPI_SR_RFNE_BIT		(3)

#define DW_SPI_IMR_MASK				(0x0)
/* IMR bits (ISR valid as well) */
#define DW_SPI_IMR_TXEIM_BIT		(0)
#define DW_SPI_IMR_TXOIM_BIT		(1)
#define DW_SPI_IMR_RXUIM_BIT		(2)
#define DW_SPI_IMR_RXOIM_BIT		(3)
#define DW_SPI_IMR_RXFIM_BIT		(4)
#define DW_SPI_IMR_MSTIM_BIT		(5)

/* IMR values */
#define DW_SPI_IMR_TXEIM		(BIT(DW_SPI_IMR_TXEIM_BIT))
#define DW_SPI_IMR_TXOIM		(BIT(DW_SPI_IMR_TXOIM_BIT))
#define DW_SPI_IMR_RXUIM		(BIT(DW_SPI_IMR_RXUIM_BIT))
#define DW_SPI_IMR_RXOIM		(BIT(DW_SPI_IMR_RXOIM_BIT))
#define DW_SPI_IMR_RXFIM		(BIT(DW_SPI_IMR_RXFIM_BIT))
#define DW_SPI_IMR_MSTIM		(BIT(DW_SPI_IMR_MSTIM_BIT))

/* ISR values (same as IMR) */
#define DW_SPI_ISR_TXEIS		DW_SPI_IMR_TXEIM
#define DW_SPI_ISR_TXOIS		DW_SPI_IMR_TXOIM
#define DW_SPI_ISR_RXUIS		DW_SPI_IMR_RXUIM
#define DW_SPI_ISR_RXOIS		DW_SPI_IMR_RXOIM
#define DW_SPI_ISR_RXFIS		DW_SPI_IMR_RXFIM
#define DW_SPI_ISR_MSTIS		DW_SPI_IMR_MSTIM

#define DW_SPI_FIFO_DEPTH			(32)

#define DW_SPI_IMR_UNMASK		(DW_SPI_IMR_TXEIM | \
					 DW_SPI_IMR_TXOIM | \
					 DW_SPI_IMR_RXUIM | \
					 DW_SPI_IMR_RXOIM | \
					 DW_SPI_IMR_RXFIM)

#define DW_SPI_IMR_MASK_TX		(~(DW_SPI_IMR_TXEIM | \
					   DW_SPI_IMR_TXOIM))

#define DW_SPI_IMR_MASK_RX		(~(DW_SPI_IMR_RXUIM | \
					   DW_SPI_IMR_RXOIM | \
					   DW_SPI_IMR_RXFIM))

#define DW_SPI_ISR_ERRORS_MASK		(DW_SPI_ISR_TXOIS | \
					 DW_SPI_ISR_RXUIS | \
					 DW_SPI_ISR_RXOIS | \
					 DW_SPI_ISR_MSTIS)

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
};

struct dw_ssi_config {
	struct dw_ssi_regs *regs;
	uint32_t	configured;

};

struct dw_ssi_bridge_regs {
	/* Offset: 0x00 */
	volatile uint32_t ctrlr0;	/* Control Register 0								(RW) */
	volatile uint32_t reserved_ctrlr1;
	volatile uint32_t ssienr;	/* SSI Enable Register							(RW) */
	volatile uint32_t reserved_mwcr;

	/* Offset: 0x10 */
	volatile uint32_t reserved_ser;
	volatile uint32_t rxfbtr;	/* Receive FIFO Burst Threshold Register			(RW) */
	volatile uint32_t txftlr;	/* Transmit FIFO Threshold Level					(RW) */
	volatile uint32_t rxftlr;	/* Receive FIFO Threshold Level						(RW) */

	/* Offset: 0x20 */
	volatile uint32_t reserved_txflr;
	volatile uint32_t reserved_rxflr;
	volatile uint32_t sr;		/* Status Register									(RW) */
	volatile uint32_t imr;		/* Interrupt Mask Register							(RW) */

	/* Offset: 0x30 */
	volatile uint32_t isr;		/* Interrupt Status Register						(RW) */
	volatile uint32_t risr;		/* Raw Interrupt Status Register					(RW) */
	volatile uint32_t txuicr;	/*			(RW) */
	volatile uint32_t rxoicr;	/* Receive FIFO Overflow Interrupt Clear Register	(RW) */

	/* Offset: 0x40 */
	volatile uint32_t spimecr;	/*			(RW) */
	volatile uint32_t ahbecr;	/*			(RW) */
	volatile uint32_t icr;		/* Interrupt Clear Register								(RW) */
	volatile uint32_t reserved_dmacr;

	/* Offset: 0x50 */
	volatile uint32_t reserved_dmatdlr;
	volatile uint32_t reserved_axiawlen;
	volatile uint32_t idr;				/* Identification Register						(RW) */
	volatile uint32_t ssic_version_id;	/* DWC_ssi component version						(RW) */
};

struct dw_ssi_bridge_config {
	struct dw_ssi_bridge_regs *regs;
	uint32_t	configured;
};

/**
 * @brief SPI buffer structure
 *
 * @param buf is a valid pointer on a data buffer, or NULL otherwise.
 * @param len is the length of the buffer or, if buf is NULL, will be the
 *    length which as to be sent as dummy bytes (as TX buffer) or
 *    the length of bytes that should be skipped (as RX buffer).
 */
struct spi_buf {
	void *buf;
	uint32_t len;
};

/**
 * @brief SPI buffer array structure
 */
struct spi_buf_set {
	/** Pointer to an array of spi_buf, or NULL */
	const struct spi_buf *buffers;
	/** Length of the array pointed by @a buffers */
	uint32_t count;
};

/**
 * @brief qspi initialization for a specific channel
 *			with disabling ssi and interrupt sources
 * @param ch_num channel number
 * @return none
 */
void qspi_bridge_init(uint32_t ch_num);

/**
 * @brief	Set the upper address(26:32) of APB access in the target.
 * @param	ch_num channel number,
 * @param	addr memory address,
 * @param	slave_num slave number, chiplet id = 1~3
 * @return none
 */
void qspi_bridge_set_upper_addr(uint32_t ch_num, uint64_t addr, uint32_t slave_num);

/**
 * @brief Write 1 word to bridge mode slave
 *
 * @param	ch_num channel number,
 * @param	addr memory address,
 * @param	data data to write,
 * @param	slave_num slave number, chiplet id = 1~3
 *
 * @return	none
 */
void qspi_bridge_write_1word(uint32_t ch_num, uint64_t addr, uint32_t data, uint32_t slave_num);

/**
 * @brief Controller writes 16 words to bridge mode slave
 *
 * @param	ch_num channel number,
 * @param	addr memory address,
 * @param	*data data buffer pointer to write
 * @param	slave_num slave number, chiplet id = 1~3
 *
 * @return	none
 */
void qspi_bridge_write_16word(uint32_t ch_num, uint64_t addr, uint32_t *data, uint32_t slave_num);

/**
 * @brief Controller reads 1 word from bridge mode slave
 *
 * @param	ch_num channel number,
 * @param	addr memory address,
 * @param	slave_num slave number, chiplet id = 1~3
 *
 * @return	data to be read
 */
uint32_t qspi_bridge_read_1word(uint32_t ch_num, uint64_t addr, uint32_t slave_num);

/**
 * @brief Controller reads 16 words from bridge mode slave
 *
 * @param	ch_num channel number,
 * @param	addr memory address,
 * @param	data to be read and returned
 * @param	slave_num slave number, chiplet id = 1~3
 *
 * @return	none
 */
void qspi_bridge_read_16word(uint32_t ch_num, uint64_t addr, uint32_t *data, uint32_t slave_num);

/**
 * @brief qspi_bridge test function. Include "drivers/synopsys/qspi_bridge.h".
 *
 * @param	none
 *
 * @return	1 on pass, 0 on fail
 */
uint32_t qspi_bridge_test(void);
