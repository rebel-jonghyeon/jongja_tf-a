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

#pragma once

union dwc_ssi_ctrlr0 {
	struct {
		uint32_t dfs:5; /* [4:0] */
		uint32_t rsvd_ctrlr0_5:1; /* [5:5] */
		uint32_t frf:2; /* [7:6] */
		uint32_t scph:1; /* [8:8] */
		uint32_t scpol:1; /* [9:9] */
		uint32_t tmod:2; /* [11:10] */
		uint32_t slv_oe:1; /* [12:12] */
		uint32_t srl:1; /* [13:13] */
		uint32_t sste:1; /* [14:14] */
		uint32_t rsvd_ctrlr0_15:1; /* [15:15] */
		uint32_t cfs:4; /* [19:16] */
		uint32_t rsvd_ctrlr0_20_21:2; /* [21:20] */
		uint32_t spi_frf:2; /* [23:22] */
		uint32_t spi_hyperbus_en:1; /* [24:24] */
		uint32_t spi_dws_en:1; /* [25:25] */
		uint32_t clk_loop_en:1; /* [26:26] */
		uint32_t rsvd_ctrlr0_27_30:4; /* [30:27] */
		uint32_t ssi_is_mst:1; /* [31:31] */
	};
	uint32_t val;
};

union dwc_ssi_ctrlr1 {
	struct {
		uint32_t ndf:16; /* [15:0] */
		uint32_t rsvd_ctrlr1:16; /* [31:16] */
	};
	uint32_t val;
};

union dwc_ssi_ssienr {
	struct {
		uint32_t ssic_en:1; /* [0:0] */
		uint32_t rsvd_ssienr:31; /* [31:1] */
	};
	uint32_t val;
};

union dwc_ssi_mwcr {
	struct {
		uint32_t mwmod:1; /* [0:0] */
		uint32_t mdd:1; /* [1:1] */
		uint32_t mhs:1; /* [2:2] */
		uint32_t rsvd_mwcr:29; /* [31:3] */
	};
	uint32_t val;
};

union dwc_ssi_ser {
	struct {
		uint32_t ser:1; /* [0:0] */
		uint32_t rsvd_ser:31; /* [31:1] */
	};
	uint32_t val;
};

union dwc_ssi_baudr {
	struct {
		uint32_t rsvd_baudr_0:1; /* [0:0] */
		uint32_t sckdv:15; /* [15:1] */
		uint32_t rsvd_baudr_16_31:16; /* [31:16] */
	};
	uint32_t val;
};

union dwc_ssi_txftlr {
	struct {
		uint32_t tft:5; /* [4:0] */
		uint32_t rsvd_txftlr:11; /* [15:5] */
		uint32_t txfthr:5; /* [20:16] */
		uint32_t rsvd_txfthr:11; /* [31:21] */
	};
	uint32_t val;
};

union dwc_ssi_rxftlr {
	struct {
		uint32_t rft:5; /* [4:0] */
		uint32_t rsvd_rxftlr:27; /* [31:5] */
	};
	uint32_t val;
};

union dwc_ssi_txflr {
	struct {
		uint32_t txtfl:6; /* [5:0] */
		uint32_t rsvd_txflr:26; /* [31:6] */
	};
	uint32_t val;
};

union dwc_ssi_rxflr {
	struct {
		uint32_t rxtfl:6; /* [5:0] */
		uint32_t rsvd_rxflr:26; /* [31:6] */
	};
	uint32_t val;
};

union dwc_ssi_sr {
	struct {
		uint32_t busy:1; /* [0:0] */
		uint32_t tfnf:1; /* [1:1] */
		uint32_t tfe:1; /* [2:2] */
		uint32_t rfne:1; /* [3:3] */
		uint32_t rff:1; /* [4:4] */
		uint32_t txe:1; /* [5:5] */
		uint32_t dcol:1; /* [6:6] */
		uint32_t rsvd_sr:8; /* [14:7] */
		uint32_t cmpltd_df:17; /* [31:15] */
	};
	uint32_t val;
};

union dwc_ssi_imr {
	struct {
		uint32_t txeim:1; /* [0:0] */
		uint32_t txoim:1; /* [1:1] */
		uint32_t rxuim:1; /* [2:2] */
		uint32_t rxoim:1; /* [3:3] */
		uint32_t rxfim:1; /* [4:4] */
		uint32_t mstim:1; /* [5:5] */
		uint32_t xrxoim:1; /* [6:6] */
		uint32_t txuim:1; /* [7:7] */
		uint32_t axiem:1; /* [8:8] */
		uint32_t rsvd_9_imr:1; /* [9:9] */
		uint32_t spitem:1; /* [10:10] */
		uint32_t donem:1; /* [11:11] */
		uint32_t rsvd_12_31_imr:20; /* [31:12] */
	};
	uint32_t val;
};

union dwc_ssi_isr {
	struct {
		uint32_t txeis:1; /* [0:0] */
		uint32_t txois:1; /* [1:1] */
		uint32_t rxuis:1; /* [2:2] */
		uint32_t rxois:1; /* [3:3] */
		uint32_t rxfis:1; /* [4:4] */
		uint32_t mstis:1; /* [5:5] */
		uint32_t xrxois:1; /* [6:6] */
		uint32_t txuis:1; /* [7:7] */
		uint32_t axies:1; /* [8:8] */
		uint32_t rsvd_9_risr:1; /* [9:9] */
		uint32_t spites:1; /* [10:10] */
		uint32_t dones:1; /* [11:11] */
		uint32_t rsvd_12_31_risr:20; /* [31:12] */
	};
	uint32_t val;
};

union dwc_ssi_risr {
	struct {
		uint32_t txeir:1; /* [0:0] */
		uint32_t txoir:1; /* [1:1] */
		uint32_t rxuir:1; /* [2:2] */
		uint32_t rxoir:1; /* [3:3] */
		uint32_t rxfir:1; /* [4:4] */
		uint32_t mstir:1; /* [5:5] */
		uint32_t xrxoir:1; /* [6:6] */
		uint32_t txuir:1; /* [7:7] */
		uint32_t axier:1; /* [8:8] */
		uint32_t rsvd_9_risr:1; /* [9:9] */
		uint32_t spiter:1; /* [10:10] */
		uint32_t doner:1; /* [11:11] */
		uint32_t rsvd_12_31_risr:20; /* [31:12] */
	};
	uint32_t val;
};

union dwc_ssi_txeicr {
	struct {
		uint32_t txeicr:1; /* [0:0] */
		uint32_t rsvd_txeicr:31; /* [31:1] */
	};
	uint32_t val;
};

union dwc_ssi_rxoicr {
	struct {
		uint32_t rxoicr:1; /* [0:0] */
		uint32_t rsvd_rxoicr:31; /* [31:1] */
	};
	uint32_t val;
};

union dwc_ssi_rxuicr {
	struct {
		uint32_t rxuicr:1; /* [0:0] */
		uint32_t rsvd_rxuicr:31; /* [31:1] */
	};
	uint32_t val;
};

union dwc_ssi_msticr {
	struct {
		uint32_t msticr:1; /* [0:0] */
		uint32_t rsvd_msticr:31; /* [31:1] */
	};
	uint32_t val;
};

union dwc_ssi_icr {
	struct {
		uint32_t icr:1; /* [0:0] */
		uint32_t rsvd_icr:31; /* [31:1] */
	};
	uint32_t val;
};

union dwc_ssi_dmacr {
	struct {
		uint32_t rdmae:1; /* [0:0] */
		uint32_t tdmae:1; /* [1:1] */
		uint32_t idmae:1; /* [2:2] */
		uint32_t atw:2; /* [4:3] */
		uint32_t rsvd_dmacr5:1; /* [5:5] */
		uint32_t ainc:1; /* [6:6] */
		uint32_t rsvd_dmacr7:1; /* [7:7] */
		uint32_t acache:4; /* [11:8] */
		uint32_t aprot:3; /* [14:12] */
		uint32_t aid:6; /* [20:15] */
		uint32_t rsvd_dmacr:11; /* [31:21] */
	};
	uint32_t val;
};

union dwc_ssi_dmatdlr {
	struct {
		uint32_t dmatdl:5; /* [4:0] */
		uint32_t rsvd_dmatdlr:27; /* [31:5] */
	};
	uint32_t val;
};

union dwc_ssi_dmardlr {
	struct {
		uint32_t dmardl:5; /* [4:0] */
		uint32_t rsvd_dmardlr:27; /* [31:5] */
	};
	uint32_t val;
};

union dwc_ssi_idr {
	struct {
		uint32_t idcode; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_ssic_version_id {
	struct {
		uint32_t ssic_comp_version; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr0 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr1 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr2 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr3 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr4 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr5 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr6 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr7 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr8 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr9 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr10 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr11 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr12 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr13 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr14 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr15 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr16 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr17 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr18 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr19 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr20 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr21 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr22 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr23 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr24 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr25 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr26 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr27 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr28 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr29 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr30 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr31 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr32 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr33 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr34 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_dr35 {
	struct {
		uint32_t dr; /* [31:0] */
	};
	uint32_t val;
};

union dwc_ssi_rx_sample_delay {
	struct {
		uint32_t rsd:8; /* [7:0] */
		uint32_t rsvd0_rx_sample_delay:8; /* [15:8] */
		uint32_t se:1; /* [16:16] */
		uint32_t rsvd1_rx_sample_delay:15; /* [31:17] */
	};
	uint32_t val;
};

union dwc_ssi_spi_ctrlr0 {
	struct {
		uint32_t trans_type:2; /* [1:0] */
		uint32_t addr_l:4; /* [5:2] */
		uint32_t rsvd_spi_ctrlr0_6:1; /* [6:6] */
		uint32_t xip_md_bit_en:1; /* [7:7] */
		uint32_t inst_l:2; /* [9:8] */
		uint32_t rsvd_spi_ctrlr0_10:1; /* [10:10] */
		uint32_t wait_cycles:5; /* [15:11] */
		uint32_t spi_ddr_en:1; /* [16:16] */
		uint32_t inst_ddr_en:1; /* [17:17] */
		uint32_t spi_rxds_en:1; /* [18:18] */
		uint32_t xip_dfs_hc:1; /* [19:19] */
		uint32_t xip_inst_en:1; /* [20:20] */
		uint32_t ssic_xip_cont_xfer_en:1; /* [21:21] */
		uint32_t rsvd_spi_ctrlr0_22:1; /* [22:22] */
		uint32_t rxds_vl_en:1; /* [23:23] */
		uint32_t spi_dm_en:1; /* [24:24] */
		uint32_t spi_rxds_sig_en:1; /* [25:25] */
		uint32_t xip_mbl:2; /* [27:26] */
		uint32_t rsvd_spi_ctrlr0_28:1; /* [28:28] */
		uint32_t xip_prefetch_en:1; /* [29:29] */
		uint32_t clk_stretch_en:1; /* [30:30] */
		uint32_t rsvd_spi_ctrlr0:1; /* [31:31] */
	};
	uint32_t val;
};

union dwc_ssi_ddr_drive_edge {
	struct {
		uint32_t tde:8; /* [7:0] */
		uint32_t rsvd_ddr_drive_edge:24; /* [31:8] */
	};
	uint32_t val;
};

union dwc_ssi_xip_mode_bits {
	struct {
		uint32_t xip_md_bits:16; /* [15:0] */
		uint32_t rsvd_xip_md_bits:16; /* [31:16] */
	};
	uint32_t val;
};

union dwc_ssi_xip_incr_inst {
	struct {
		uint32_t incr_inst:16; /* [15:0] */
		uint32_t rsvd_incr_inst:16; /* [31:16] */
	};
	uint32_t val;
};

union dwc_ssi_xip_wrap_inst {
	struct {
		uint32_t wrap_inst:16; /* [15:0] */
		uint32_t rsvd_wrap_inst:16; /* [31:16] */
	};
	uint32_t val;
};

union dwc_ssi_xip_ctrl {
	struct {
		uint32_t frf:2; /* [1:0] */
		uint32_t trans_type:2; /* [3:2] */
		uint32_t addr_l:4; /* [7:4] */
		uint32_t rsvd_xip_ctrl_8:1; /* [8:8] */
		uint32_t inst_l:2; /* [10:9] */
		uint32_t rsvd_spi_ctrlr0_11:1; /* [11:11] */
		uint32_t md_bits_en:1; /* [12:12] */
		uint32_t wait_cycles:5; /* [17:13] */
		uint32_t dfs_hc:1; /* [18:18] */
		uint32_t ddr_en:1; /* [19:19] */
		uint32_t inst_ddr_en:1; /* [20:20] */
		uint32_t rxds_en:1; /* [21:21] */
		uint32_t inst_en:1; /* [22:22] */
		uint32_t cont_xfer_en:1; /* [23:23] */
		uint32_t xip_hyperbus_en:1; /* [24:24] */
		uint32_t rxds_sig_en:1; /* [25:25] */
		uint32_t xip_mbl:2; /* [27:26] */
		uint32_t rsvd_xip_ctrl_28:1; /* [28:28] */
		uint32_t xip_prefetch_en:1; /* [29:29] */
		uint32_t rxds_vl_en:1; /* [30:30] */
		uint32_t rsvd_xip_ctrl:1; /* [31:31] */
	};
	uint32_t val;
};

union dwc_ssi_xip_ser {
	struct {
		uint32_t ser:1; /* [0:0] */
		uint32_t rsvd_ser:31; /* [31:1] */
	};
	uint32_t val;
};

union dwc_ssi_xrxoicr {
	struct {
		uint32_t xrxoicr:1; /* [0:0] */
		uint32_t rsvd_xrxoicr:31; /* [31:1] */
	};
	uint32_t val;
};

union dwc_ssi_xip_cnt_time_out {
	struct {
		uint32_t xtoc:8; /* [7:0] */
		uint32_t rsvd_xtoc:24; /* [31:8] */
	};
	uint32_t val;
};

union dwc_ssi_spi_ctrlr1 {
	struct {
		uint32_t dyn_ws:3; /* [2:0] */
		uint32_t rsvd_spi_ctrlr1_3_7:5; /* [7:3] */
		uint32_t max_ws:4; /* [11:8] */
		uint32_t rsvd_spi_ctrlr1_12_15:4; /* [15:12] */
		uint32_t cs_min_high:4; /* [19:16] */
		uint32_t rsvd_spi_ctrlr1_20_31:12; /* [31:20] */
	};
	uint32_t val;
};

union dwc_ssi_xip_write_incr_inst {
	struct {
		uint32_t incr_write_inst:16; /* [15:0] */
		uint32_t rsvd_incr_inst_16to31:16; /* [31:16] */
	};
	uint32_t val;
};

union dwc_ssi_xip_write_wrap_inst {
	struct {
		uint32_t wrap_write_inst:16; /* [15:0] */
		uint32_t rsvd_wrap_inst_16to31:16; /* [31:16] */
	};
	uint32_t val;
};

union dwc_ssi_xip_write_ctrl {
	struct {
		uint32_t wr_frf:2; /* [1:0] */
		uint32_t wr_trans_type:2; /* [3:2] */
		uint32_t wr_addr_l:4; /* [7:4] */
		uint32_t wr_inst_l:2; /* [9:8] */
		uint32_t wr_spi_ddr_en:1; /* [10:10] */
		uint32_t wr_inst_ddr_en:1; /* [11:11] */
		uint32_t xipwr_hyperbus_en:1; /* [12:12] */
		uint32_t xipwr_rxds_sig_en:1; /* [13:13] */
		uint32_t xipwr_dm_en:1; /* [14:14] */
		uint32_t rsvd_xip_writectrl_15:1; /* [15:15] */
		uint32_t xipwr_wait_cycles:5; /* [20:16] */
		uint32_t xipwr_dfs_hc:1; /* [21:21] */
		uint32_t rsvd_xip_writectrl_22to31:10; /* [31:22] */
	};
	uint32_t val;
};

struct dwc_ssi {
	union dwc_ssi_ctrlr0 ctrlr0; /* offset : 0x0 */
	union dwc_ssi_ctrlr1 ctrlr1; /* offset : 0x4 */
	union dwc_ssi_ssienr ssienr; /* offset : 0x8 */
	union dwc_ssi_mwcr mwcr; /* offset : 0xc */
	union dwc_ssi_ser ser; /* offset : 0x10 */
	union dwc_ssi_baudr baudr; /* offset : 0x14 */
	union dwc_ssi_txftlr txftlr; /* offset : 0x18 */
	union dwc_ssi_rxftlr rxftlr; /* offset : 0x1c */
	union dwc_ssi_txflr txflr; /* offset : 0x20 */
	union dwc_ssi_rxflr rxflr; /* offset : 0x24 */
	union dwc_ssi_sr sr; /* offset : 0x28 */
	union dwc_ssi_imr imr; /* offset : 0x2c */
	union dwc_ssi_isr isr; /* offset : 0x30 */
	union dwc_ssi_risr risr; /* offset : 0x34 */
	union dwc_ssi_txeicr txeicr; /* offset : 0x38 */
	union dwc_ssi_rxoicr rxoicr; /* offset : 0x3c */
	union dwc_ssi_rxuicr rxuicr; /* offset : 0x40 */
	union dwc_ssi_msticr msticr; /* offset : 0x44 */
	union dwc_ssi_icr icr; /* offset : 0x48 */
	union dwc_ssi_dmacr dmacr; /* offset : 0x4c */
	union dwc_ssi_dmatdlr dmatdlr; /* offset : 0x50 */
	union dwc_ssi_dmardlr dmardlr; /* offset : 0x54 */
	union dwc_ssi_idr idr; /* offset : 0x58 */
	union dwc_ssi_ssic_version_id ssic_version_id; /* offset : 0x5c */
	union dwc_ssi_dr0 dr0; /* offset : 0x60 */
	union dwc_ssi_dr1 dr1; /* offset : 0x64 */
	union dwc_ssi_dr2 dr2; /* offset : 0x68 */
	union dwc_ssi_dr3 dr3; /* offset : 0x6c */
	union dwc_ssi_dr4 dr4; /* offset : 0x70 */
	union dwc_ssi_dr5 dr5; /* offset : 0x74 */
	union dwc_ssi_dr6 dr6; /* offset : 0x78 */
	union dwc_ssi_dr7 dr7; /* offset : 0x7c */
	union dwc_ssi_dr8 dr8; /* offset : 0x80 */
	union dwc_ssi_dr9 dr9; /* offset : 0x84 */
	union dwc_ssi_dr10 dr10; /* offset : 0x88 */
	union dwc_ssi_dr11 dr11; /* offset : 0x8c */
	union dwc_ssi_dr12 dr12; /* offset : 0x90 */
	union dwc_ssi_dr13 dr13; /* offset : 0x94 */
	union dwc_ssi_dr14 dr14; /* offset : 0x98 */
	union dwc_ssi_dr15 dr15; /* offset : 0x9c */
	union dwc_ssi_dr16 dr16; /* offset : 0xa0 */
	union dwc_ssi_dr17 dr17; /* offset : 0xa4 */
	union dwc_ssi_dr18 dr18; /* offset : 0xa8 */
	union dwc_ssi_dr19 dr19; /* offset : 0xac */
	union dwc_ssi_dr20 dr20; /* offset : 0xb0 */
	union dwc_ssi_dr21 dr21; /* offset : 0xb4 */
	union dwc_ssi_dr22 dr22; /* offset : 0xb8 */
	union dwc_ssi_dr23 dr23; /* offset : 0xbc */
	union dwc_ssi_dr24 dr24; /* offset : 0xc0 */
	union dwc_ssi_dr25 dr25; /* offset : 0xc4 */
	union dwc_ssi_dr26 dr26; /* offset : 0xc8 */
	union dwc_ssi_dr27 dr27; /* offset : 0xcc */
	union dwc_ssi_dr28 dr28; /* offset : 0xd0 */
	union dwc_ssi_dr29 dr29; /* offset : 0xd4 */
	union dwc_ssi_dr30 dr30; /* offset : 0xd8 */
	union dwc_ssi_dr31 dr31; /* offset : 0xdc */
	union dwc_ssi_dr32 dr32; /* offset : 0xe0 */
	union dwc_ssi_dr33 dr33; /* offset : 0xe4 */
	union dwc_ssi_dr34 dr34; /* offset : 0xe8 */
	union dwc_ssi_dr35 dr35; /* offset : 0xec */
	union dwc_ssi_rx_sample_delay rx_sample_delay; /* offset : 0xf0 */
	union dwc_ssi_spi_ctrlr0 spi_ctrlr0; /* offset : 0xf4 */
	union dwc_ssi_ddr_drive_edge ddr_drive_edge; /* offset : 0xf8 */
	union dwc_ssi_xip_mode_bits xip_mode_bits; /* offset : 0xfc */
	union dwc_ssi_xip_incr_inst xip_incr_inst; /* offset : 0x100 */
	union dwc_ssi_xip_wrap_inst xip_wrap_inst; /* offset : 0x104 */
	union dwc_ssi_xip_ctrl xip_ctrl; /* offset : 0x108 */
	union dwc_ssi_xip_ser xip_ser; /* offset : 0x10c */
	union dwc_ssi_xrxoicr xrxoicr; /* offset : 0x110 */
	union dwc_ssi_xip_cnt_time_out xip_cnt_time_out; /* offset : 0x114 */
	union dwc_ssi_spi_ctrlr1 spi_ctrlr1; /* offset : 0x118 */
	uint32_t reserved_1[9];
	union dwc_ssi_xip_write_incr_inst xip_write_incr_inst; /* offset : 0x140 */
	union dwc_ssi_xip_write_wrap_inst xip_write_wrap_inst; /* offset : 0x144 */
	union dwc_ssi_xip_write_ctrl xip_write_ctrl; /* offset : 0x148 */
};

#define DISEN			(0)
#define EN				(1)

#define DIV2			(2)
#define DIV4			(4)

#define XIP_READ		(0)
#define XIP_WRITE		(1)

#define DUMMY_MASK		(0x1f << 13)
#define DUMMY4			(0x4 << 13)
#define DUMMY8			(0x8 << 13)
#define DDR_EN			(0x1 << 19)
#define CONT_XFER_EN	(0x1 << 23)

void dwc_ssi_set_buadrate(volatile struct dwc_ssi *dwc_ssi, uint32_t div);
void dwc_ssi_set_xip_cmd(volatile struct dwc_ssi *dwc_ssi, bool rw, uint16_t cmd);
void dwc_ssi_set_xip_ctrl(volatile struct dwc_ssi *dwc_ssi, uint32_t ctrl);
