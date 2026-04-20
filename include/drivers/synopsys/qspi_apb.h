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
#define DW_APB_SPI_CTRLR0_SCPH_BIT		(6)
#define DW_APB_SPI_CTRLR0_SCPOL_BIT		(7)
#define DW_APB_SPI_CTRLR0_SRL_BIT		(11)

#define DW_APB_SPI_CTRLR0_SCPH			(BIT(DW_APB_SPI_CTRLR0_SCPH_BIT))
#define DW_APB_SPI_CTRLR0_SCPOL			(BIT(DW_APB_SPI_CTRLR0_SCPOL_BIT))
#define DW_APB_SPI_CTRLR0_SRL			(BIT(DW_APB_SPI_CTRLR0_SRL_BIT))

#define DW_APB_SPI_CTRLR0_TMOD_BIT		(8)

#define DW_APB_SPI_CTRLR0_TMOD_TX_RX	(0)
#define DW_APB_SPI_CTRLR0_TMOD_TX		(BIT(DW_APB_SPI_CTRLR0_TMOD_BIT))
#define DW_APB_SPI_CTRLR0_TMOD_RX		(2 << DW_APB_SPI_CTRLR0_TMOD_BIT)
#define DW_APB_SPI_CTRLR0_TMOD_EEPROM	(3 << DW_APB_SPI_CTRLR0_TMOD_BIT)

#define DW_APB_SPI_CTRLR0_SPI_FRF_BIT	(21)
#define DW_APB_SPI_CTRLR0_SPI_FRF_STANDARD	(0x00 << DW_APB_SPI_CTRLR0_SPI_FRF_BIT)
#define DW_APB_SPI_CTRLR0_SPI_FRF_QSPI	(0x2 << DW_APB_SPI_CTRLR0_SPI_FRF_BIT)

#define DW_APB_SPI_SPI_CTRLR0_WAIT_CYCLES_BIT		(11)
#define DW_APB_SPI_SPI_CTRLR0_WAIT_CYCLES_4			(0x4 << DW_APB_SPI_SPI_CTRLR0_WAIT_CYCLES_BIT)
#define DW_APB_SPI_SPI_CTRLR0_WAIT_CYCLES_8			(0x8 << DW_APB_SPI_SPI_CTRLR0_WAIT_CYCLES_BIT)
#define DW_APB_SPI_SPI_CTRLR0_WAIT_CYCLES_24		(0x18 << DW_APB_SPI_SPI_CTRLR0_WAIT_CYCLES_BIT)

#define DW_APB_SPI_SPI_CTRLR0_INST_L_BIT			(8)
#define DW_APB_SPI_SPI_CTRLR0_INST_L_0				(0x0 << DW_APB_SPI_SPI_CTRLR0_INST_L_BIT)
#define DW_APB_SPI_SPI_CTRLR0_INST_L_8				(0x2 << DW_APB_SPI_SPI_CTRLR0_INST_L_BIT)

#define DW_APB_SPI_SPI_CTRLR0_ADDR_L_BIT			(2)
#define DW_APB_SPI_SPI_CTRLR0_ADDR_L_24				(0x06 << DW_APB_SPI_SPI_CTRLR0_ADDR_L_BIT)
#define DW_APB_SPI_SPI_CTRLR0_ADDR_L_0				(0x00 << DW_APB_SPI_SPI_CTRLR0_ADDR_L_BIT)
#define DW_APB_SPI_SPI_CTRLR0_ADDR_L_8				(0x02 << DW_APB_SPI_SPI_CTRLR0_ADDR_L_BIT)

#define DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE_BIT		(0x0)
#define DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE_TT0		(0x0 << DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE_BIT)
#define DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE_TT1		(BIT(DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE_BIT))
#define DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE_TT2		(0x2 << DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE_BIT)
#define DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE			(DW_APB_SPI_SPI_CTRLR0_TRANS_TYPE_TT2)

#define DW_APB_SPI_TXFTLR_BIT						(0)
#define DW_APB_SPI_TXFTLR_0WORD						(0)
#define DW_APB_SPI_TXFTLR_1WORD						(BIT(DW_APB_SPI_TXFTLR_BIT))
#define DW_APB_SPI_TXFTLR_16WORD					(0x10 << DW_APB_SPI_TXFTLR_BIT)

#define DW_APB_SPI_CTRLR1_BIT						(0)
#define DW_APB_SPI_CTRLR1_NDF_1WORD					(0 << DW_APB_SPI_CTRLR1_BIT)
#define DW_APB_SPI_CTRLR1_NDF_2WORD					(BIT(DW_APB_SPI_CTRLR1_BIT))
#define DW_APB_SPI_CTRLR1_NDF_16WORD				(15 << DW_APB_SPI_CTRLR1_BIT)

#define DW_APB_SPI_INSTRUCTION_WRITE				(0x80)			/* 1 word */
#define DW_APB_SPI_INSTRUCTION_WRITE_16WORD			(0x83)			/* 16 word */
#define DW_APB_SPI_INSTRUCTION_WRITE_2WAIT			(0x10)

#define DW_APB_SPI_INSTRUCTION_WRITE_STATUS_2WAIT	(0xD0)

#define DW_APB_SPI_INSTRUCTION_READ_REQ				(0x20)
#define DW_APB_SPI_INSTRUCTION_READ_0WAIT			(0x00)
#define DW_APB_SPI_INSTRUCTION_READ_2WAIT			(0x10)
#define DW_APB_SPI_INSTRUCTION_READ_8WAIT			(0x60)
#define DW_APB_SPI_INSTRUCTION_READ_16WAIT			(0x68)
#define DW_APB_SPI_INSTRUCTION_READ_24WAIT			(0x70)

#define DW_APB_SPI_INSTRUCTION_READ_32				(0x04)
#define DW_APB_SPI_INSTRUCTION_READ_16				(0x03)

#define DW_APB_SPI_INSTRUCTION_READ_STATUS_0WAIT	(0x40)
#define DW_APB_SPI_INSTRUCTION_READ_STATUS_1WAIT	(0x48)
#define DW_APB_SPI_INSTRUCTION_READ_STATUS_2WAIT	(0x50)

#define DW_APB_SPI_CTRLR0_DFS_BIT		(16)
#define DW_APB_SPI_CTRLR0_DFS_8			(0x07 << DW_APB_SPI_CTRLR0_DFS_BIT)
#define DW_APB_SPI_CTRLR0_DFS_16		(0x0F << DW_APB_SPI_CTRLR0_DFS_BIT)
#define DW_APB_SPI_CTRLR0_DFS_32		(0x1F << DW_APB_SPI_CTRLR0_DFS_BIT)

#define DW_APB_SPI_SSIENR_ENABLE		(1)
#define DW_APB_SPI_SSIENR_DISABLE		(0)

/* SR bits and values */
#define DW_APB_SPI_SR_BUSY_BIT		(0)
#define DW_APB_SPI_SR_TFNF_BIT		(1)
#define DW_APB_SPI_SR_RFNE_BIT		(3)
#define DW_APB_SPI_SR_BUSY_MASK		(BIT(DW_APB_SPI_SR_BUSY_BIT))

#define DW_APB_SPI_IMR_MASK				(0x0)
/* IMR bits */
#define DW_APB_SPI_IMR_TXEIM_BIT		(0)
#define DW_APB_SPI_IMR_TXOIM_BIT		(1)
#define DW_APB_SPI_IMR_RXUIM_BIT		(2)
#define DW_APB_SPI_IMR_RXOIM_BIT		(3)
#define DW_APB_SPI_IMR_RXFIM_BIT		(4)
#define DW_APB_SPI_IMR_MSTIM_BIT		(5)

/* IMR values */
#define DW_APB_SPI_IMR_TXEIM		(BIT(DW_APB_SPI_IMR_TXEIM_BIT))
#define DW_APB_SPI_IMR_TXOIM		(BIT(DW_APB_SPI_IMR_TXOIM_BIT))
#define DW_APB_SPI_IMR_RXUIM		(BIT(DW_APB_SPI_IMR_RXUIM_BIT))
#define DW_APB_SPI_IMR_RXOIM		(BIT(DW_APB_SPI_IMR_RXOIM_BIT))
#define DW_APB_SPI_IMR_RXFIM		(BIT(DW_APB_SPI_IMR_RXFIM_BIT))
#define DW_APB_SPI_IMR_MSTIM		(BIT(DW_APB_SPI_IMR_MSTIM_BIT))

/* ISR values (same as IMR) */
#define DW_APB_SPI_ISR_TXEIS		DW_APB_SPI_IMR_TXEIM
#define DW_APB_SPI_ISR_TXOIS		DW_APB_SPI_IMR_TXOIM
#define DW_APB_SPI_ISR_RXUIS		DW_APB_SPI_IMR_RXUIM
#define DW_APB_SPI_ISR_RXOIS		DW_APB_SPI_IMR_RXOIM
#define DW_APB_SPI_ISR_RXFIS		DW_APB_SPI_IMR_RXFIM
#define DW_APB_SPI_ISR_MSTIS		DW_APB_SPI_IMR_MSTIM

#define DW_APB_SPI_FIFO_DEPTH			(32)

#define DW_APB_SPI_IMR_UNMASK		(DW_APB_SPI_IMR_TXEIM | \
					 DW_APB_SPI_IMR_TXOIM | \
					 DW_APB_SPI_IMR_RXUIM | \
					 DW_APB_SPI_IMR_RXOIM | \
					 DW_APB_SPI_IMR_RXFIM)

#define DW_APB_SPI_IMR_MASK_TX		(~(DW_APB_SPI_IMR_TXEIM | \
					   DW_APB_SPI_IMR_TXOIM))

#define DW_APB_SPI_IMR_MASK_RX		(~(DW_APB_SPI_IMR_RXUIM | \
					   DW_APB_SPI_IMR_RXOIM | \
					   DW_APB_SPI_IMR_RXFIM))

#define DW_APB_SPI_ISR_ERRORS_MASK		(DW_APB_SPI_ISR_TXOIS | \
					 DW_APB_SPI_ISR_RXUIS | \
					 DW_APB_SPI_ISR_RXOIS | \
					 DW_APB_SPI_ISR_MSTIS)

/* Other values & definitions */
#define DW_APB_SPI_DEFAULT_DELAY_COUNT		10000
#define DW_APB_SPI_WAIT_0				0
#define DW_APB_SPI_WAIT_8				8
#define DW_APB_SPI_WAIT_10				10

#define SPI_SET_WAIT_CYCLES(x)			((x) << 11)

#define DW_APB_SPI_DEFAULT_SLAVE	0

struct qspi_apb_regs {
	/* Offset: 0x00 */
	volatile uint32_t ctrlr0;	/* Control Register 0								(RW) */
	volatile uint32_t ctrlr1;	/* Control Register 1								(RW) */
	volatile uint32_t ssienr;	/* SSI Enable Register								(RW) */
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
	volatile uint32_t txoicr;	/* Transmit FIFO Error Int Clear Registers			(RW) */
	volatile uint32_t rxoicr;	/* Receive FIFO Overflow Interrupt Clear Register	(RW) */

	/* Offset: 0x40 */
	volatile uint32_t rxuicr;	/* Receive FIFO Underflow Interrupt Clear Register	(RW) */
	volatile uint32_t msticr;	/* Multi-Controller Interrupt Clear Register		(RW) */
	volatile uint32_t icr;		/* Interrupt Clear Register							(RW) */
	volatile uint32_t dmacr;	/* DMA Control Register								(RW) */

	/* Offset: 0x50 */
	volatile uint32_t dmatdlr;	/* DMA Transmit Data Level							(RW) */
	volatile uint32_t dmardlr;	/* DMA Receive Data Level							(RW) */
	volatile uint32_t idr;		/* Identification Register							(RW) */
	volatile uint32_t ssic_version_id;	/* version									(RW) */

	/* Offset: 0x60 */
	volatile uint32_t drx[36];	/* Data Register									(RW) */

	/* Offset: 0xF0 */
	volatile uint32_t rx_sample_delay;	/* RX Sample Delay Register					(RW) */
	volatile uint32_t spi_ctrlr0;		/* SPI_CTRLR0 - SPI Control Register		(RW) */
	volatile uint32_t txd_drive_edge;	/* apb_ssi - Transmit Drive Edge Register	(RW) */
	volatile uint32_t rsvd;				/* reserved									(RW) */
};

struct qspi_apb_config {
	struct qspi_apb_regs *regs;
	uint32_t configured;
};

int qspi_apb_init(void);
