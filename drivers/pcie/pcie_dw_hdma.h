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

#include "driver.h"

#define PCIE_MAX_HDMA_CHANNELS 32

#define PCIE_CC_NUM_HDMA_RD_TAG 128

#define PCIE_CX_REMOTE_MAX_TAG 63

#define DAT_EL_CONTROL_CYCLE_BIT BIT(0)
#define DAT_EL_CONTROL_LLP		 BIT(2)
#define DAT_EL_CONTROL_LWIE		 BIT(3)
#define DAT_EL_CONTROL_RWIE		 BIT(4)

#define LINK_EL_CONTROL_CYCLE_BIT		 BIT(0)
#define LINK_EL_CONTROL_TCB				 BIT(1)
#define LINK_EL_CONTROL_LLP				 BIT(2)
#define LINK_EL_CONTROL_ELEMENT_PREFETCH (BIT_MASK(22) & ~BIT_MASK(17))

#define HDMA_WRITE_CH0  0
#define HDMA_WRITE_CH1  1
#define HDMA_WRITE_CH2  2
#define HDMA_WRITE_CH3  3
#define HDMA_WRITE_CH4  4
#define HDMA_WRITE_CH5  5
#define HDMA_WRITE_CH6  6
#define HDMA_WRITE_CH7  7
#define HDMA_WRITE_CH8  8
#define HDMA_WRITE_CH9  9
#define HDMA_WRITE_CH10 10
#define HDMA_WRITE_CH11 11
#define HDMA_WRITE_CH12 12
#define HDMA_WRITE_CH13 13
#define HDMA_WRITE_CH14 14
#define HDMA_WRITE_CH15 15
#define HDMA_READ_CH0   16
#define HDMA_READ_CH1   17
#define HDMA_READ_CH2   18
#define HDMA_READ_CH3   19
#define HDMA_READ_CH4   20
#define HDMA_READ_CH5   21
#define HDMA_READ_CH6   22
#define HDMA_READ_CH7   23
#define HDMA_READ_CH8   24
#define HDMA_READ_CH9   25
#define HDMA_READ_CH10  26
#define HDMA_READ_CH11  27
#define HDMA_READ_CH12  28
#define HDMA_READ_CH13  29
#define HDMA_READ_CH14  30
#define HDMA_READ_CH15  31

#define HDMA_CH_CONTEXT_OFF 0x2000

#define HDMA_INT_STATUS_STOP		BIT(0)
#define HDMA_INT_STATUS_WATERMARK	BIT(1)
#define HDMA_INT_STATUS_ABORT		BIT(2)

struct pcie_hdma_block_config {
	union {
		uint64_t source_address;
		uint64_t load_link_pointer;
	};
	uint64_t dest_address;
	uint32_t block_size;
};

enum pcie_hdma_type {
	PCIE_HDMA_READ = 0,
	PCIE_HDMA_WRITE,
	PCIE_HDMA_UNKNOWN
};

enum pcie_hdmac_chan_status {
	CHAN_STAT_RESERVED = 0,
	CHAN_STAT_RUNNING,
	CHAN_STAT_ABORT,
	CHAN_STAT_STOPPED
};

enum pcie_hdma_error {
	/* No error to report */
	PCIE_HDMA_CLEAR = 0x0,
	/* Unsupported request CPL while reading a linked list element */
	PCIE_HDMA_LL_CPL_UR = 0x1,
	/* Completer abort CPL while reading a linked list element */
	PCIE_HDMA_LL_CPL_CA = 0x2,
	/* Poisoned data CPL when reading a linked list element */
	PCIE_HDMA_LL_CPL_EP = 0x3,
	/* CPL timeout while reading data from the source */
	PCIE_HDMA_DATA_CPL_TIMEOUT = 0x8,
	/* Unsupported request CPL while reading data from the source */
	PCIE_HDMA_DATA_CPL_UR = 0x9,
	/* Completer abort CPL while reading data from the source */
	PCIE_HDMA_DATA_CPL_CA = 0xA,
	/* Poisoned data CPL while reading data from the source */
	PCIE_HDMA_DATA_CPL_EP = 0xB,
	/* Error response received while writing data to the destination */
	PCIE_HDMA_DATA_MWR = 0xC,
	PCIE_HDMA_MAX_ERRORS
};

enum dw_hdma_chan_mode {
	NON_LINKED_LIST_MODE = 0,
	LINKED_LIST_MODE
};

enum dw_hdma_chan_attr {
	NON_LINKED_LIST_HDMA_WRITE = 0,
	NON_LINKED_LIST_HDMA_READ,
	LINKED_LIST_HDMA_WRITE,
	LINKED_LIST_HDMA_READ,
	INVALID_CHANNEL
};

enum pcie_hdma_channel_direction {
	DW_PCIE_INVALID_HDMA = 0,
	DW_PCIE_WRITE_HDMA,
	DW_PCIE_READ_HDMA
};

struct chan_plat_data {
	/* Priority for transfer: 0 to 7. 0 being lowest, and 7 highest. */
	uint8_t priority;
	/* Mode for HDMA for the channel, specified as enum dw_hdma_chan_mode */
	uint8_t mode;
	/* Enable channel. */
	uint8_t enable;
	/* Direction: enum hdma_channel_direction */
	uint8_t direction;
	/* Maximum transfers that can be pending with the HDMA driver for this channel. */
	uint16_t max_transfers;
	/* Flags specific to a HDMA controller. TBD as a union of bit fields for each
	 * controller. Eg. PCIe HDMA can enable disable abort intr perchannel, and not per
	 * transfer for multi block linked list mode.
	 */
	uint32_t flags;
};

struct pcie_ep_hdma_controller {
	/* Back pointer to the PCIe EP controller */
	struct pcie_epc *epc;
	/* Number of channels for read/write HDMA. Max is 32 */
	uint8_t num_channels;
	struct chan_plat_data chan_data[PCIE_MAX_HDMA_CHANNELS];
	struct pcie_hdma_config *hdma_cfg;
	bool is_created;
};

struct pcie_hdma_config {
	struct pcie_hdma_block_config *head_block;
	void *callback_arg;
	void (*hdma_callback)(void *callback_arg,
						  struct pcie_ep_hdma_controller *pcie_ep_hdmac,
						  uint32_t channel,
						  int32_t error_code);
};

/* Data/link element of a HDMA descriptor in linked list mode */
struct pcie_hdma_element {
	uint32_t control;
	uint32_t transfer_size;
	union {
		uint32_t sar_lo;
		uint32_t llp_lo;
	};
	union {
		uint32_t sar_hi;
		uint32_t llp_hi;
	};
	uint32_t dar_lo;
	uint32_t dar_hi;
};

struct pcie_descriptor {
	struct pcie_hdma_element *elements;
};

struct pcie_ep_hdma_controller *pcie_hdmac_create(struct pcie_epc *epc);
int32_t pcie_hdma_transfer_start(struct pcie_ep_hdma_controller *hdmac, uint8_t channel);
int32_t pcie_hdma_select_function(struct pcie_ep_hdma_controller *hdmac, uint32_t channel,
								  bool vf_active, uint32_t func_num);
int32_t dw_hdma_config(struct pcie_ep_hdma_controller *hdmac, uint32_t channel,
					   struct pcie_hdma_config *cfg);
