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

/* DOE Data Object Header */
#define PCI_DOE_HEADER_1_VID		(0x0000FFFF)
#define PCI_DOE_HEADER_1_TYPE		(0x00FF0000)
#define PCI_DOE_HEADER_2_LENGTH		(0x0003FFFF)
#define PCI_DOE_HEADER_LEN			(0x2)

/* DOE_ERROR_FLAG Register */
#define DOE_ERROR_POISONED BIT(24)
#define DOE_ERROR_RBOX_FIFO_EMPTY BIT(23)
#define DOE_ERROR_WBOX_FIFO_EMPTY BIT(22)
#define DOE_ERROR_FIFO_EMPTY (DOE_ERROR_RBOX_FIFO_EMPTY | DOE_ERROR_WBOX_FIFO_EMPTY)
#define DOE_ERROR_RBOX_FIFO_FULL BIT(21)
#define DOE_ERROR_WBOX_FIFO_FULL BIT(20)
#define DOE_ERROR_FIFO_FULL (DOE_ERROR_RBOX_FIFO_FULL | DOE_ERROR_WBOX_FIFO_FULL)
#define DOE_ERROR_DW_MISMATCH BIT(18)
#define DOE_ERROR_ALL (DOE_ERROR_FIFO_EMPTY | DOE_ERROR_FIFO_FULL |\
					   DOE_ERROR_POISONED | DOE_ERROR_DW_MISMATCH)

/* REBELH has 64 FIFO depth for MB */
#define DOE_MAX_LENGTH	(64)

enum doe_error_status {
	DOE_ERROR_ABORT = 0x0,
	DOE_NO_ERROR = 0x1
};

union pcie_doe_caps_header {
	struct {
		uint32_t capability_id:16; /* [15:0] */
		uint32_t capability_ver:4; /* [19:16] */
		uint32_t next_cap_offset:12; /* [31:20] */
	};
	uint32_t val;
};

union pcie_doe_capabilities {
	struct {
		uint32_t irq_support:1; /* [0:0] */
		uint32_t irq_msg_nbr:11; /* [11:1] */
		uint32_t attention_support:1; /* [12:12] */
		uint32_t async_msg_support:1; /* [13:13] */
		uint32_t reserved0:18; /* [31:14] */
	};
	uint32_t val;
};

union pcie_doe_control {
	struct {
		uint32_t doe_abort:1; /* [0:0] */
		uint32_t irq_enable:1; /* [1:1] */
		uint32_t attention_not_need:1; /* [2:2] */
		uint32_t async_msg_en:1; /* [3:3] */
		uint32_t reserved0:27; /* [30:4] */
		uint32_t doe_go:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_doe_status {
	struct {
		uint32_t doe_busy:1; /* [0:0] */
		uint32_t irq_status:1; /* [1:1] */
		uint32_t doe_error:1; /* [2:2] */
		uint32_t async_msg_status:1; /* [3:3] */
		uint32_t doe_at_attention:1; /* [4:4] */
		uint32_t reserved0:26; /* [30:5] */
		uint32_t doe_ready:1; /* [31:31] */
	};
	uint32_t val;
};

union pcie_doe_write_data_mailbox {
	struct {
		uint32_t write_data_mailbox; /* [31:0] */
	};
	uint32_t val;
};

union pcie_doe_read_data_mailbox {
	struct {
		uint32_t read_data_mailbox; /* [31:0] */
	};
	uint32_t val;
};

union pcie_doe_error_flag {
	struct {
		uint32_t doe_length:18; /* [17:0] */
		uint32_t wbox_dw_mismatch:1; /* [18:18] */
		uint32_t rbox_dw_mismatch:1; /* [19:19] */
		uint32_t wbox_fifo_full:1; /* [20:20] */
		uint32_t rbox_fifo_full:1; /* [21:21] */
		uint32_t wbox_fifo_empty:1; /* [22:22] */
		uint32_t rbox_fifo_empty:1; /* [23:23] */
		uint32_t poisoned_error:1; /* [24:24] */
		uint32_t reserved0:1; /* [25:25] */
		uint32_t dw_mismatch_error_mask:1; /* [26:26] */
		uint32_t fifo_full_error_mask:1; /* [27:27] */
		uint32_t fifo_empty_error_mask:1; /* [28:28] */
		uint32_t poisoned_error_mask:1; /* [29:29] */
		uint32_t irq_clear:1; /* [30:30] */
		uint32_t rbox_dw_mismatch_check:1; /* [31:31] */
	};
	uint32_t val;
};

struct pcie_doe_register {
	union pcie_doe_caps_header doe_caps_header; /* offset : 0x0 */
	union pcie_doe_capabilities doe_capabilities; /* offset : 0x4 */
	union pcie_doe_control doe_control; /* offset : 0x8 */
	union pcie_doe_status doe_status; /* offset : 0xc */
	union pcie_doe_write_data_mailbox doe_write_data_mailbox; /* offset : 0x10 */
	union pcie_doe_read_data_mailbox doe_read_data_mailbox; /* offset : 0x14 */
	union pcie_doe_error_flag doe_error_flag; /* offset : 0x18 */
};

int32_t pcie_doe_setup(struct pcie_epc *dw_pcie_epc, uint32_t addr);
int32_t pcie_doe_read_wmb(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data);
int32_t pcie_doe_write_rmb(struct pcie_epc *dw_pcie_epc, int32_t len, uint32_t *payload);
