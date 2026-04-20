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

#define DW_APB_SSI_CTRLR0_SCPH						(1)
#define DW_APB_SSI_CTRLR0_SCPOL						(1)
#define DW_APB_SSI_CTRLR0_SRL						(1)

#define DW_APB_SSI_CTRLR0_TMOD_TX_RX				(0)
#define DW_APB_SSI_CTRLR0_TMOD_TX					(1)
#define DW_APB_SSI_CTRLR0_TMOD_RX					(2)
#define DW_APB_SSI_CTRLR0_TMOD_EEPROM				(3)

#define DW_APB_SSI_CTRLR0_SPI_FRF_STANDARD			(0x0)
#define DW_APB_SSI_CTRLR0_SPI_FRF_QSPI				(0x2)

#define DW_APB_SSI_SPI_CTRLR0_WAIT_CYCLES_4			(0x4)
#define DW_APB_SSI_SPI_CTRLR0_WAIT_CYCLES_8			(0x8)
#define DW_APB_SSI_SPI_CTRLR0_WAIT_CYCLES_24		(0x18)

#define DW_APB_SSI_SPI_CTRLR0_INST_L_0				(0x0)
#define DW_APB_SSI_SPI_CTRLR0_INST_L_8				(0x2)

#define DW_APB_SSI_SPI_CTRLR0_ADDR_L_24				(0x06)
#define DW_APB_SSI_SPI_CTRLR0_ADDR_L_0				(0x00)
#define DW_APB_SSI_SPI_CTRLR0_ADDR_L_8				(0x02)

#define DW_APB_SSI_SPI_CTRLR0_TRANS_TYPE_TT0		(0)
#define DW_APB_SSI_SPI_CTRLR0_TRANS_TYPE_TT1		(1)
#define DW_APB_SSI_SPI_CTRLR0_TRANS_TYPE_TT2		(2)
#define DW_APB_SSI_SPI_CTRLR0_TRANS_TYPE			(DW_APB_SSI_SPI_CTRLR0_TRANS_TYPE_TT2)

#define DW_APB_SSI_TXFTLR_0WORD						(0)
#define DW_APB_SSI_TXFTLR_1WORD						(1)
#define DW_APB_SSI_TXFTLR_16WORD					(0x10)

#define DW_APB_SSI_CTRLR1_NDF_1WORD					(0)
#define DW_APB_SSI_CTRLR1_NDF_2WORD					(1)
#define DW_APB_SSI_CTRLR1_NDF_16WORD				(15)

#define DW_APB_SSI_INSTRUCTION_WRITE				(0x80)			/* 1 word */
#define DW_APB_SSI_INSTRUCTION_WRITE_16WORD			(0x83)			/* 16 word */
#define DW_APB_SSI_INSTRUCTION_WRITE_2WAIT			(0x10)

#define DW_APB_SSI_INSTRUCTION_WRITE_STATUS_2WAIT	(0xD0)

#define DW_APB_SSI_INSTRUCTION_READ_REQ				(0x20)
#define DW_APB_SSI_INSTRUCTION_READ_0WAIT			(0x00)
#define DW_APB_SSI_INSTRUCTION_READ_2WAIT			(0x10)
#define DW_APB_SSI_INSTRUCTION_READ_8WAIT			(0x60)
#define DW_APB_SSI_INSTRUCTION_READ_16WAIT			(0x68)
#define DW_APB_SSI_INSTRUCTION_READ_24WAIT			(0x70)

#define DW_APB_SSI_INSTRUCTION_READ_32				(0x04)
#define DW_APB_SSI_INSTRUCTION_READ_16				(0x03)

#define DW_APB_SSI_INSTRUCTION_READ_STATUS_0WAIT	(0x40)
#define DW_APB_SSI_INSTRUCTION_READ_STATUS_1WAIT	(0x48)
#define DW_APB_SSI_INSTRUCTION_READ_STATUS_2WAIT	(0x50)

#define DW_APB_SSI_CTRLR0_DFS_8						(0x07)
#define DW_APB_SSI_CTRLR0_DFS_16					(0x0F)
#define DW_APB_SSI_CTRLR0_DFS_32					(0x1F)

#define DW_APB_SSI_SSIENR_ENABLE					(1)
#define DW_APB_SSI_SSIENR_DISABLE					(0)

/* SR bits and values */
#define DW_APB_SSI_SR_BUSY_MASK						(1)

#define DW_APB_SSI_IMR_MASK							(0x0)

#define DW_APB_SSI_FIFO_DEPTH						(32)

/* Flash opcodes */
#define SPI_NOR_CMD_READ			0x03	/* Read data */
#define SPI_NOR_CMD_RDID			0x9F	/* Read JEDEC ID */
#define SPI_NOR_CMD_RDSR			0x05	/* Read status register */
#define SPI_NOR_CMD_WRSR			0x01	/* Write status register */
#define SPI_NOR_CMD_RDFSR			0x70	/* Read flag status register */
#define SPI_NOR_CMD_MULTI_RDID		0xAF
#define SPI_NOR_CMD_ENTER_QUAD		0x35	/* Enter QUAD mode */
#define SPI_NOR_CMD_RESET_QUAD		0xF5	/* Reset QUAD mode */
#define SPI_NOR_CMD_QIOFR			0xEB	/* Quard in/out fast read */
#define SPI_NOR_CMD_READ_FAST		0x0B	/* Read data */
#define SPI_NOR_CMD_WRITE_VOL_REG	0x81	/* Write volatile register */
#define SPI_NOR_CMD_READ_VOL_REG	0x85	/* Read volatile register */
#define SPI_NOR_CMD_BULK_ERASE		0x60	/* Bulk erase */
#define SPI_NOR_CMD_SECTOR_ERASE	0xD8	/* Sector erase */
#define SPI_NOR_CMD_SUBSECTOR_ERASE	0x20	/* Subsector 4K erase */

#define SPI_NOR_CMD_PAGE_PROGRAM	0x02	/* Page program */
#define SPI_NOR_CMD_QUAD_PROGRAM	0x32	/* Quad program */

#define SPI_NOR_CMD_WRITE_ENABLE	0x06	/* Write enable */
#define SPI_NOR_CMD_READ_DISC_PARAM	0x5A	/* Read discovery param */
#define SPI_NOR_CMD_READ_OTP		0x4B	/* Read OTP */
#define SPI_NOR_CMD_WRITE_OTP		0x42	/* Write OTP */

/* Other values & definitions */
#define DW_APB_SSI_DEFAULT_DELAY_COUNT		10000
#define DW_APB_SSI_WAIT_0				0
#define DW_APB_SSI_WAIT_8				8
#define DW_APB_SSI_WAIT_10				10

#define SPI_NOR_FLASH_ID				0x20
#define SPI_NOR_FLASH_FSR_READY			0x80
#define SPI_NOR_FLASH_FSR_READY_MASK	0x80
#define SPI_NOR_FLASH_SR_WRITE_ENABLE_MASK	0x3
#define SPI_NOR_FLASH_SR_WRITE_ENABLE	0x2
#define SPI_NOR_FLASH_ERASED_DATA		0xFF

#define SPI_NOR_FLASH_TEST_DATA			0x55
#define SPI_NOR_FLASH_TEST_ADDR			0x0
#define SPI_NOR_FLASH_TEST_SECTOR		0x0
#define SPI_NOR_FLASH_DEFAULT_VOL_CONFIG	0xFB

#define DW_APB_SSI_DEFAULT_SLAVE	0
#define QSPI_APB_DUMMY_TX_FF			(0xFF)
#define QSPI_APB_DUMMY_TX_ZERO			(0x00)
#define QSPI_APB_DUMMY_TX_TEST			(0xa5)
union dw_apb_ssi_ctrlr0 {
	struct {
		uint32_t dfs:4; /* [3:0] */
		uint32_t frf:2; /* [5:4] */
		uint32_t scph:1; /* [6:6] */
		uint32_t scpol:1; /* [7:7] */
		uint32_t tmod:2; /* [9:8] */
		uint32_t slv_oe:1; /* [10:10] */
		uint32_t srl:1; /* [11:11] */
		uint32_t cfs:4; /* [15:12] */
		uint32_t dfs_32:5; /* [20:16] */
		uint32_t spi_frf:2; /* [22:21] */
		uint32_t rsvd_ctrlr0_23:1; /* [23:23] */
		uint32_t sste:1; /* [24:24] */
		uint32_t seconv:1; /* [25:25] */
		uint32_t rsvd_ctrlr0:6; /* [31:26] */
	};
	uint32_t val;
};

union dw_apb_ssi_ctrlr1 {
	struct {
		uint32_t ndf:16; /* [15:0] */
		uint32_t rsvd_ctrlr1:16; /* [31:16] */
	};
	uint32_t val;
};

union dw_apb_ssi_ssienr {
	struct {
		uint32_t ssi_en:1; /* [0:0] */
		uint32_t rsvd_ssienr:31; /* [31:1] */
	};
	uint32_t val;
};

union dw_apb_ssi_mwcr {
	struct {
		uint32_t mwmod:1; /* [0:0] */
		uint32_t mdd:1; /* [1:1] */
		uint32_t mhs:1; /* [2:2] */
		uint32_t rsvd_mwcr:29; /* [31:3] */
	};
	uint32_t val;
};

union dw_apb_ssi_ser {
	struct {
		uint32_t ser:1; /* [0:0] */
		uint32_t rsvd_ser:31; /* [31:1] */
	};
	uint32_t val;
};

union dw_apb_ssi_baudr {
	struct {
		uint32_t sckdv:16; /* [15:0] */
		uint32_t rsvd_baudr:16; /* [31:16] */
	};
	uint32_t val;
};

union dw_apb_ssi_txftlr {
	struct {
		uint32_t tft:5; /* [4:0] */
		uint32_t rsvd_txftlr:27; /* [31:5] */
	};
	uint32_t val;
};

union dw_apb_ssi_rxftlr {
	struct {
		uint32_t rft:5; /* [4:0] */
		uint32_t rsvd_rxftlr:27; /* [31:5] */
	};
	uint32_t val;
};

union dw_apb_ssi_txflr {
	struct {
		uint32_t txtfl:6; /* [5:0] */
		uint32_t rsvd_txflr:26; /* [31:6] */
	};
	uint32_t val;
};

union dw_apb_ssi_rxflr {
	struct {
		uint32_t rxtfl:6; /* [5:0] */
		uint32_t rsvd_rxflr:26; /* [31:6] */
	};
	uint32_t val;
};

union dw_apb_ssi_sr {
	struct {
		uint32_t busy:1; /* [0:0] */
		uint32_t tfnf:1; /* [1:1] */
		uint32_t tfe:1; /* [2:2] */
		uint32_t rfne:1; /* [3:3] */
		uint32_t rff:1; /* [4:4] */
		uint32_t rsvd_txe:1; /* [5:5] */
		uint32_t dcol:1; /* [6:6] */
		uint32_t rsvd_sr:25; /* [31:7] */
	};
	uint32_t val;
};

union dw_apb_ssi_imr {
	struct {
		uint32_t txeim:1; /* [0:0] */
		uint32_t txoim:1; /* [1:1] */
		uint32_t rxuim:1; /* [2:2] */
		uint32_t rxoim:1; /* [3:3] */
		uint32_t rxfim:1; /* [4:4] */
		uint32_t mstim:1; /* [5:5] */
		uint32_t rsvd_imr:26; /* [31:6] */
	};
	uint32_t val;
};

union dw_apb_ssi_isr {
	struct {
		uint32_t txeis:1; /* [0:0] */
		uint32_t txois:1; /* [1:1] */
		uint32_t rxuis:1; /* [2:2] */
		uint32_t rxois:1; /* [3:3] */
		uint32_t rxfis:1; /* [4:4] */
		uint32_t mstis:1; /* [5:5] */
		uint32_t rsvd_isr:26; /* [31:6] */
	};
	uint32_t val;
};

union dw_apb_ssi_risr {
	struct {
		uint32_t txeir:1; /* [0:0] */
		uint32_t txoir:1; /* [1:1] */
		uint32_t rxuir:1; /* [2:2] */
		uint32_t rxoir:1; /* [3:3] */
		uint32_t rxfir:1; /* [4:4] */
		uint32_t mstir:1; /* [5:5] */
		uint32_t rsvd_risr:26; /* [31:6] */
	};
	uint32_t val;
};

union dw_apb_ssi_txoicr {
	struct {
		uint32_t txoicr:1; /* [0:0] */
		uint32_t rsvd_txoicr:31; /* [31:1] */
	};
	uint32_t val;
};

union dw_apb_ssi_rxoicr {
	struct {
		uint32_t rxoicr:1; /* [0:0] */
		uint32_t rsvd_rxoicr:31; /* [31:1] */
	};
	uint32_t val;
};

union dw_apb_ssi_rxuicr {
	struct {
		uint32_t rxuicr:1; /* [0:0] */
		uint32_t rsvd_rxuicr:31; /* [31:1] */
	};
	uint32_t val;
};

union dw_apb_ssi_msticr {
	struct {
		uint32_t msticr:1; /* [0:0] */
		uint32_t rsvd_msticr:31; /* [31:1] */
	};
	uint32_t val;
};

union dw_apb_ssi_icr {
	struct {
		uint32_t icr:1; /* [0:0] */
		uint32_t rsvd_icr:31; /* [31:1] */
	};
	uint32_t val;
};

union dw_apb_ssi_dmacr {
	struct {
		uint32_t rdmae:1; /* [0:0] */
		uint32_t tdmae:1; /* [1:1] */
		uint32_t rsvd_dmacr:30; /* [31:2] */
	};
	uint32_t val;
};

union dw_apb_ssi_dmatdlr {
	struct {
		uint32_t dmatdl:5; /* [4:0] */
		uint32_t rsvd_dmatdlr:27; /* [31:5] */
	};
	uint32_t val;
};

union dw_apb_ssi_dmardlr {
	struct {
		uint32_t dmardl:5; /* [4:0] */
		uint32_t rsvd_dmardlr:27; /* [31:5] */
	};
	uint32_t val;
};

union dw_apb_ssi_idr {
	struct {
		uint32_t idcode; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_ssi_version_id {
	struct {
		uint32_t ssi_comp_version; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr0 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr1 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr2 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr3 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr4 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr5 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr6 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr7 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr8 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr9 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr10 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr11 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr12 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr13 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr14 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr15 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr16 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr17 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr18 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr19 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr20 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr21 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr22 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr23 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr24 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr25 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr26 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr27 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr28 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr29 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr30 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr31 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr32 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr33 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr34 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_dr35 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dw_apb_ssi_rx_sample_dly {
	struct {
		uint32_t rsd:8; /* [7:0] */
		uint32_t rsvd_rx_sample_dly:24; /* [31:8] */
	};
	uint32_t val;
};

union dw_apb_ssi_spi_ctrlr0 {
	struct {
		uint32_t trans_type:2; /* [1:0] */
		uint32_t addr_l:4; /* [5:2] */
		uint32_t rsvd_spi_ctrlr0_6_7:2; /* [7:6] */
		uint32_t inst_l:2; /* [9:8] */
		uint32_t rsvd_spi_ctrlr0_10:1; /* [10:10] */
		uint32_t wait_cycles:5; /* [15:11] */
		uint32_t spi_ddr_en:1; /* [16:16] */
		uint32_t inst_ddr_en:1; /* [17:17] */
		uint32_t spi_rxds_en:1; /* [18:18] */
		uint32_t rsvd_spi_ctrlr0:13; /* [31:19] */
	};
	uint32_t val;
};

union dw_apb_ssi_rsvd {
	struct {
		uint32_t rsvd; /* [31:0] */
	};
	uint32_t val;
};

struct dw_apb_ssi {
	union dw_apb_ssi_ctrlr0 ctrlr0; /* offset : 0x0 */
	union dw_apb_ssi_ctrlr1 ctrlr1; /* offset : 0x4 */
	union dw_apb_ssi_ssienr ssienr; /* offset : 0x8 */
	union dw_apb_ssi_mwcr mwcr; /* offset : 0xc */
	union dw_apb_ssi_ser ser; /* offset : 0x10 */
	union dw_apb_ssi_baudr baudr; /* offset : 0x14 */
	union dw_apb_ssi_txftlr txftlr; /* offset : 0x18 */
	union dw_apb_ssi_rxftlr rxftlr; /* offset : 0x1c */
	union dw_apb_ssi_txflr txflr; /* offset : 0x20 */
	union dw_apb_ssi_rxflr rxflr; /* offset : 0x24 */
	union dw_apb_ssi_sr sr; /* offset : 0x28 */
	union dw_apb_ssi_imr imr; /* offset : 0x2c */
	union dw_apb_ssi_isr isr; /* offset : 0x30 */
	union dw_apb_ssi_risr risr; /* offset : 0x34 */
	union dw_apb_ssi_txoicr txoicr; /* offset : 0x38 */
	union dw_apb_ssi_rxoicr rxoicr; /* offset : 0x3c */
	union dw_apb_ssi_rxuicr rxuicr; /* offset : 0x40 */
	union dw_apb_ssi_msticr msticr; /* offset : 0x44 */
	union dw_apb_ssi_icr icr; /* offset : 0x48 */
	union dw_apb_ssi_dmacr dmacr; /* offset : 0x4c */
	union dw_apb_ssi_dmatdlr dmatdlr; /* offset : 0x50 */
	union dw_apb_ssi_dmardlr dmardlr; /* offset : 0x54 */
	union dw_apb_ssi_idr idr; /* offset : 0x58 */
	union dw_apb_ssi_ssi_version_id ssi_version_id; /* offset : 0x5c */
	union dw_apb_ssi_dr0 dr0; /* offset : 0x60 */
	union dw_apb_ssi_dr1 dr1; /* offset : 0x64 */
	union dw_apb_ssi_dr2 dr2; /* offset : 0x68 */
	union dw_apb_ssi_dr3 dr3; /* offset : 0x6c */
	union dw_apb_ssi_dr4 dr4; /* offset : 0x70 */
	union dw_apb_ssi_dr5 dr5; /* offset : 0x74 */
	union dw_apb_ssi_dr6 dr6; /* offset : 0x78 */
	union dw_apb_ssi_dr7 dr7; /* offset : 0x7c */
	union dw_apb_ssi_dr8 dr8; /* offset : 0x80 */
	union dw_apb_ssi_dr9 dr9; /* offset : 0x84 */
	union dw_apb_ssi_dr10 dr10; /* offset : 0x88 */
	union dw_apb_ssi_dr11 dr11; /* offset : 0x8c */
	union dw_apb_ssi_dr12 dr12; /* offset : 0x90 */
	union dw_apb_ssi_dr13 dr13; /* offset : 0x94 */
	union dw_apb_ssi_dr14 dr14; /* offset : 0x98 */
	union dw_apb_ssi_dr15 dr15; /* offset : 0x9c */
	union dw_apb_ssi_dr16 dr16; /* offset : 0xa0 */
	union dw_apb_ssi_dr17 dr17; /* offset : 0xa4 */
	union dw_apb_ssi_dr18 dr18; /* offset : 0xa8 */
	union dw_apb_ssi_dr19 dr19; /* offset : 0xac */
	union dw_apb_ssi_dr20 dr20; /* offset : 0xb0 */
	union dw_apb_ssi_dr21 dr21; /* offset : 0xb4 */
	union dw_apb_ssi_dr22 dr22; /* offset : 0xb8 */
	union dw_apb_ssi_dr23 dr23; /* offset : 0xbc */
	union dw_apb_ssi_dr24 dr24; /* offset : 0xc0 */
	union dw_apb_ssi_dr25 dr25; /* offset : 0xc4 */
	union dw_apb_ssi_dr26 dr26; /* offset : 0xc8 */
	union dw_apb_ssi_dr27 dr27; /* offset : 0xcc */
	union dw_apb_ssi_dr28 dr28; /* offset : 0xd0 */
	union dw_apb_ssi_dr29 dr29; /* offset : 0xd4 */
	union dw_apb_ssi_dr30 dr30; /* offset : 0xd8 */
	union dw_apb_ssi_dr31 dr31; /* offset : 0xdc */
	union dw_apb_ssi_dr32 dr32; /* offset : 0xe0 */
	union dw_apb_ssi_dr33 dr33; /* offset : 0xe4 */
	union dw_apb_ssi_dr34 dr34; /* offset : 0xe8 */
	union dw_apb_ssi_dr35 dr35; /* offset : 0xec */
	union dw_apb_ssi_rx_sample_dly rx_sample_dly; /* offset : 0xf0 */
	union dw_apb_ssi_spi_ctrlr0 spi_ctrlr0; /* offset : 0xf4 */
	uint32_t reserved_1;
	union dw_apb_ssi_rsvd rsvd; /* offset : 0xfc */
};

struct qspi_apb_config {
	struct dw_apb_ssi *regs;
	uint32_t configured;
};

/**
 * @fn		void qspi_apb_enable_loopback(uint32_t ch_num)
 * @brief	Enable loopback mode
 * @param	ch_num qspi apb channel number
 * @return	none
 */
void qspi_apb_enable_loopback(uint32_t ch_num);

/**
 * @fn		void qspi_apb_set(uint32_t ch_num, uint32_t dfs, uint32_t sel_txrx, uint32_t spi_frf, uint32_t data_rate)
 * @brief	Perform qspi_apb initialization with given arguments
 * @param	ch_num qspi apb channel number
 * @param	dfs data frame size
 * @param	sel_txrx tmod
 * @param	spi_frf spi frame format
 * @param	data_rate data rate
 * @return	none
 */
void qspi_apb_set(uint32_t ch_num, uint32_t dfs, uint32_t sel_txrx, uint32_t spi_frf, uint32_t data_rate);

/**
 * @fn		int qspi_apb_transfer(...)
 * @brief	Transceive tx/rx data
 * @param	ch_num qspi apb channel number
 * @param	tx_buf tx buffer pointer
 * @param	tx_ofs tx offset
 * @param	tx_len valid tx data length
 * @param	rx_buf rx buffer pointer
 * @param	rx_ofs rx offset
 * @param	rx_len valid rx data length
 * @return	RL_OK on success, RL_ERROR on failure
 */
int qspi_apb_transfer(uint32_t ch_num,
					  uint8_t *tx_buf, uint32_t tx_ofs, uint32_t tx_len,
					  uint8_t *rx_buf, uint32_t rx_ofs, uint32_t rx_len);

/**
 * @fn		int qspi_apb_init(void)
 * @brief	Perform qspi_apb initialization with default settings
 * @param	none
 * @return	RL_OK on success, RL_ERROR on failure
 */
int qspi_apb_init(void);
