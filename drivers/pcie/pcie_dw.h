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

#include <stdbool.h>
#include <driver.h>

#include "pcie_ctrl_register.h"
#include "pcie_subctrl_register.h"
#include "pcie_ide_apb_register.h"
#include "pcie_generated_config.h"

/* PF0_PCIE_CAP_DEVICE_CAPABILITIES (0x74) */
#define MAX_128B_SIZE 0x0
#define MAX_256B_SIZE 0x1
#define MAX_512B_SIZE 0x2
#define MAX_1024B_SIZE 0x3
#define MAX_2048B_SIZE 0x4

/* PF0_PORT_LOGIC_LINK_CTRL_OFF (0x710) */
#define LINK_CAPABLE_X1 0x1
#define LINK_CAPABLE_X2 0x3
#define LINK_CAPABLE_X4 0x7
#define LINK_CAPABLE_X8 0xF
#define LINK_CAPABLE_X16 0x1F
#define LINK_CAPABLE_X32 0x3F

/* PF0_PORT_LOGIC_GEN3_RELATED_OFF (0x890) */
#define RATE_SHADOW_SEL_GEN3 0x0
#define RATE_SHADOW_SEL_GEN4 0x1
#define RATE_SHADOW_SEL_GEN5 0x2

/* PF0_PORT_LOGIC_AUX_CLK_FREQ_OFF (0xB40) */
#define AUX_CLK_50M 50

/* 64Bit Address */
#define UPPER_32_BITS(x) (((x) >> 32) & 0xFFFFFFFF)
#define LOWER_32_BITS(x) ((x) & 0xFFFFFFFF)

/* PCI Capabilities */
#define PCI_CAP_ID(x)		((x) & 0xFF)
#define PCI_CAP_NEXT_MASK	(0x0000FF00)
#define PCI_CAP_NEXT(x)		(((x) & PCI_CAP_NEXT_MASK) >> 8)
#define PCI_CAP_POINTER(x)	((x) & 0xFF)

/* Extended Capabilities */
#define PCI_CFG_SPACE_SIZE		256
#define PCI_EXT_CAP_ID_MASK		(0x0000FFFF)
#define PCI_EXT_CAP_ID(x)		((x) & PCI_EXT_CAP_ID_MASK)
#define PCI_EXT_CAP_VER_MASK	(0x000F0000)
#define PCI_EXT_CAP_VER(x)		(((x) & PCI_EXT_CAP_VER_MASK) >> 16)
#define PCI_EXT_CAP_NEXT_MASK	(0xFFF00000)
#define PCI_EXT_CAP_NEXT(x)		(((x) & PCI_EXT_CAP_NEXT_MASK) >> 20)

#define PCI_EXT_CAP_ID_PASID	0x1B	/* Process Address Space ID */
#define PCI_EXT_CAP_ID_ATS	0x0F	/* Address Translation Services */

/* RAS-DES Event Counter */
#define RASDES_ECNT_GROUP(x) (((x) & 0xF00) >> 8)
#define RASDES_ECNT_EVENT(x) ((x) & 0xFF)

#define PCIE_GEN4_MARGINING_NUM_TIMING_STEPS	(0xE)		/* 14 steps (= 0.4UI / 1/35UI) */
#define PCIE_GEN4_MARGINING_NUM_VOLTAGE_STEPS	(0x7D)		/* 125 steps (= 200mV / 1.6mV) */
#define PCIE_GEN4_MARGINING_MAX_TIMING_OFFSET	(0x28)		/* 0.4UI Max */
#define PCIE_GEN4_MARGINING_MAX_VOLTAGE_OFFSET	(0x14)		/* 200mV Max */

#define PCIE_GEN5_MARGINING_NUM_TIMING_STEPS	(0xE)		/* 14 steps (= 0.4UI / 1/35UI) */
#define PCIE_GEN5_MARGINING_NUM_VOLTAGE_STEPS	(0x7D)		/* 125 steps (= 200mV / 1.6mV) */
#define PCIE_GEN5_MARGINING_MAX_TIMING_OFFSET	(0x28)		/* 0.4UI Max */
#define PCIE_GEN5_MARGINING_MAX_VOLTAGE_OFFSET	(0x14)		/* 200mV Max */

enum pcie_speed {
	GEN1 = 1,
	GEN2 = 2,
	GEN3 = 3,
	GEN4 = 4,
	GEN5 = 5
};

enum pcie_state {
	UNINITIALIZED = 0,
	LINK_UP,
	POST_INIT_DONE
};

enum pcie_func_type {
	TYPE_PF,
	TYPE_VF
};

enum rasdp_counter_region {
	ADM_RX_PATH = 0x0,
	L3_RX_PATH = 0x1,
	L2_RX_PATH = 0x2,
	DMA_INBOUND_PATH = 0x3,
	AXI_INBOUND_REQ_PATH = 0x4,
	AXI_INBOUND_CMPL_PATH = 0x5,
	ADM_TX_PATH = 0x6,
	L3_TX_PATH = 0x7,
	L2_TX_PATH = 0x8,
	DMA_OUTBOUND_PATH = 0x9,
	AXI_OUTBOUND_REQ_PATH = 0xa,
	AXI_OUTBOUND_CMPL_PATH = 0xb,
	CXS_TX_RX_PATH = 0xc,
	DTIM_TX_RX_PATH = 0xd,
	CXL_TX_RX_PATH = 0xe
};

enum rasdp_err_inj_type {
	ERR_INJ_NONE = 0,
	ERR_INJ_1_BIT = 1,
	ERR_INJ_2_BIT = 2
};

enum rasdp_err_inj_count {
	ERR_INJ_EVERY_TLP = 0,
	ERR_INJ_1 = 1,
	ERR_INJ_2 = 2
};

enum rasdes_tba_report_type {
	TBA_ONE_CYCLE = 0x0,
	TBA_TX_L0S = 0x1,
	TBA_RX_L0S = 0x2,
	TBA_L0 = 0x3,
	TBA_L1 = 0x4,
	TBA_L1_1 = 0x5,
	TBA_L1_2 = 0x6,
	TBA_CFG_RCVRY = 0x7,
	TBA_TX_RX_L0S_OR_L0P = 0x8,
	TBA_L1_AUX = 0x9,
	TBA_1_CYCLE = 0x10,
	TBA_TX_L0S_ = 0x11,
	TBA_RX_L0S_ = 0x12,
	TBA_L0_ = 0x13,
	TBA_L1_ = 0x14,
	TBA_CFG_RCVRY_ = 0x17,
	TBA_TX_RX_L0S_ = 0x18,
	TBA_TX_PCIE_TLP = 0x20,
	TBA_RX_PCIE_TLP = 0x21,
	TBA_TX_CCIX_TLP = 0x22,
	TBA_RX_CCIX_TLP = 0x23
};

enum rasdes_tba_duration {
	TBA_MANUAL = 0x0,
	TBA_1_MS = 0x1,
	TBA_2_MS = 0x2,
	TBA_100_MS = 0x3,
	TBA_1_S = 0x4,
	TBA_2_S = 0x5,
	TBA_4_S = 0x6,
	TBA_4_US = 0xFF
};

enum rasdes_ecnt_en {
	ECNT_PER_EVENT_OFF = 0x1,
	ECNT_PER_EVENT_ON = 0x3,
	ECNT_ALL_OFF = 0x5,
	ECNT_ALL_ON = 0x7
};

enum rasdes_ecnt_clr {
	ECNT_NO_CHANGE = 0x0,
	ECNT_PER_CLEAR = 0x1,
	ECNT_NO_CHANGE_2 = 0x2,
	ECNT_ALL_CLEAR = 0x3,
};

enum rasdes_sd_status {
	SD_L1_PER_LANE = 0x0,
	SD_L1_LTSSM = 0x1,
	SD_PM = 0x2,
	SD_L2 = 0x3,
	SD_L3_FC = 0x4,
	SD_L3 = 0x5
};

enum rasdes_sd_ltssm_variable {
	DIR_SPEED_CHANGE = 0x0,
	CHANGED_SPEED_RCVRY = 0x1,
	SUCCESSFUL_SPEED_NEGO = 0x2,
	UPCFG_CAPABLE = 0x3,
	SEL_DE_EMPHASIS = 0x4,
	START_EQ_W_PRESET = 0x5,
	EQ_DONE_8GT = 0x6,
	EQ_DONE_16GT = 0x7
};

enum rasdes_sd_eq_status {
	SD_EQ_STATUS1 = 0x0,
	SD_EQ_STATUS2 = 0x1,
	SD_EQ_STATUS3 = 0x2
};

enum rasdes_sd_eq_rate {
	SD_EQ_RATE_GEN3 = 0x0,
	SD_EQ_RATE_GEN4 = 0x1,
	SD_EQ_RATE_GEN5 = 0x2,
	SD_EQ_RATE_GEN6 = 0x3
};

struct pcie_epc {
	struct dw_pcie_drv *drv;
	struct dw_pcie_config *cfg;
};

struct dw_pcie_config {
	struct pcie_ctrl_register *dbi_base;
	struct pcie_ctrl_dbi2_register *dbi2_base;
	struct pcie_ctrl_port_register *port_base;
	struct pcie_ctrl_vf_pf0_register *vf_base[16];
	struct pcie_ctrl_pf0_atu_cap_iatu_register *iatu_base[64];
	struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_base[16];
	struct pcie_subctrl_register *subctrl_base;
	struct sysreg_pcie_register *sysreg_base;
	struct sysreg_buscsr_pcie_register *sysreg_buscsr_base;
	struct pcie_doe_register *doe_base;
	struct pcie_ide_apb_register *ide_apb_base;
	struct pcie_msix_tbl *msix_tbl;
	struct pcie_msix_tbl *vf_msix_tbl[16];
	uint32_t pcs_base;
	uint32_t phy_base;
	uint8_t num_lanes;
};

struct dw_pcie_drv {
	struct pcie_epc *pcie_epc_ptr;
	uint8_t state;
	struct pcie_bar_info *bar_info;
	struct pcie_iatu_info *iatu_info;
	uint32_t *doe_fifo_addr;
};

struct pcie_epc *pcie_get_epc(void);
void pcie_dbi_ro_wr_enable(const struct dw_pcie_config *cfg, bool en);
int32_t pcie_link_setup(const struct dw_pcie_config *cfg);
int32_t pcie_set_speed(struct pcie_epc *dw_pcie_epc, uint8_t speed);
int32_t pcie_set_width(struct pcie_epc *dw_pcie_epc, uint8_t width);
void pcie_eq_setup(const struct dw_pcie_config *cfg);
void pcie_cap_setup(const struct dw_pcie_config *cfg);
int32_t pcie_find_capability(struct pcie_epc *dw_pcie_epc, const uint32_t cap);
int32_t pcie_find_ext_capability(struct pcie_epc *dw_pcie_epc, const uint32_t cap);
bool pcie_disable_capability(struct pcie_epc *dw_pcie_epc, const uint32_t cap);
bool pcie_disable_ext_capability(struct pcie_epc *dw_pcie_epc, const uint32_t cap);
int32_t pcie_get_speed(struct pcie_epc *dw_pcie_epc);
int32_t pcie_get_width(struct pcie_epc *dw_pcie_epc);
int32_t pcie_rasdp_enable_error_injection(struct pcie_epc *dw_pcie_epc, bool en, uint8_t loc,
										  uint8_t count, uint8_t type);
int32_t pcie_rasdp_get_count(struct pcie_epc *dw_pcie_epc, bool corr, uint8_t sel);
uint8_t pcie_rasdp_get_region(struct pcie_epc *dw_pcie_epc, bool corr);
int32_t pcie_rasdp_select_region(struct pcie_epc *dw_pcie_epc, bool corr, uint8_t region);
int32_t pcie_rasdp_clear_count(struct pcie_epc *dw_pcie_epc, bool corr);
int32_t pcie_rasdes_get_tba_info(struct pcie_epc *dw_pcie_epc, uint8_t *report, uint8_t *duration);
int32_t pcie_rasdes_start_tba(struct pcie_epc *dw_pcie_epc, uint8_t report, uint8_t duration);
int32_t pcie_rasdes_stop_tba(struct pcie_epc *dw_pcie_epc);
uint64_t pcie_rasdes_get_tba_data(struct pcie_epc *dw_pcie_epc);
int32_t pcie_rasdes_select_ecnt(struct pcie_epc *dw_pcie_epc, uint8_t group, uint8_t event, uint8_t lane);
int32_t pcie_rasdes_get_selected_ecnt(struct pcie_epc *dw_pcie_epc, uint8_t *group, uint8_t *event, uint8_t *lane);
int32_t pcie_rasdes_get_ecnt_data(struct pcie_epc *dw_pcie_epc, uint32_t *data);
int32_t pcie_rasdes_enable_ecnt(struct pcie_epc *dw_pcie_epc, uint8_t en);
int32_t pcie_rasdes_clear_ecnt(struct pcie_epc *dw_pcie_epc, bool all);
int32_t pcie_rasdes_sd_l1_lane_sel(struct pcie_epc *dw_pcie_epc, int8_t lane_num);
int32_t pcie_rasdes_get_sd_status(struct pcie_epc *dw_pcie_epc, int32_t sel, uint32_t *data);
int32_t pcie_rasdes_sd_eq_rate_sel(struct pcie_epc *dw_pcie_epc, int8_t eq_rate_sel);
int32_t pcie_rasdes_sd_eq_lane_sel(struct pcie_epc *dw_pcie_epc, int8_t eq_lane_sel);
int32_t pcie_rasdes_get_sd_eq_status(struct pcie_epc *dw_pcie_epc, int32_t sel, uint32_t *data);
void pcie_lane_margin_setup(const struct dw_pcie_config *cfg);
int32_t pcie_rasdp_enable_error_mode(struct pcie_epc *dw_pcie_epc, bool en);
int32_t pcie_rasdp_clear_error_mode(struct pcie_epc *dw_pcie_epc);
