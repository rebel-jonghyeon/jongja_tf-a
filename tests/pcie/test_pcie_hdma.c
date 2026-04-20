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

#include "rl_utils.h"
#include "rl_errors.h"
#include "rl_sizes.h"

#include "pcie_dw.h"
#include "pcie_dw_hdma.h"
#include "pcie_sysreg.h"
#include "pcie_rebelh.h"

static const char help_pcie_hdma[] =
	"[pcie prepare_data <seed value> <bat translated addr> <size>]\r\n"
	"[pcie hdma_ll <r/w> <sid> <ch>]\r\n"
	"[pcie hdma_nll <r/w> <sid> <sar> <dar> <size>]\r\n"
	"[pcie set_hdma_lut <ch> <sid> <ssid> <ssidv>]\r\n"
	"[pcie invalidate_hdma_lut <ch>]\r\n"
	"[pcie select_func] <ch> <vf_active> <func_num>\r\n"
	"\r\n";

struct pcie_hdma_element wch_elems[10][5];
struct pcie_descriptor wch_descriptor[10];
struct pcie_hdma_element rch_elems[10][5];
struct pcie_descriptor rch_descriptor[10];

struct pcie_hdma_element epf_elems0[10];
struct pcie_hdma_element epf_elems1[10];

static int32_t pcie_ep_prepare_dma_data(uint32_t val, uint32_t base, uint32_t size)
{
	uint32_t i;

	for (i = 0; i < size / 4; i++) {
		rl_writel(val + i, (uint32_t *)(base + (i * 4)));
	}

	return RL_OK;
}

static void pcie_ep_make_data_element(struct pcie_hdma_element *elems, uint32_t ctrl, uint32_t size,
									  uint64_t sar, uint64_t dar)
{
	elems->control = ctrl;
	elems->transfer_size = size;
	elems->sar_lo = LOWER_32_BITS(sar);
	elems->sar_hi = UPPER_32_BITS(sar);
	elems->dar_lo = LOWER_32_BITS(dar);
	elems->dar_hi = UPPER_32_BITS(dar);
}

static void pcie_ep_make_link_element(struct pcie_hdma_element *elems, uint32_t ctrl, uint64_t llp)
{
	elems->control = ctrl;
	elems->transfer_size = 0;
	elems->llp_lo = LOWER_32_BITS(llp);
	elems->llp_hi = UPPER_32_BITS(llp);
	elems->dar_lo = 0;
	elems->dar_hi = 0;
}

static void pcie_ep_make_hdma_descriptor(struct pcie_descriptor *hdma_desc, uint64_t next_location)
{
	struct pcie_hdma_element *elems = hdma_desc->elements;
	uint32_t offset, size, ctrl;
	uint64_t src_addr, dst_addr;

	ctrl = DAT_EL_CONTROL_CYCLE_BIT;
	src_addr = PCIE_HDMA_LOCAL_DAT_ADDR;
	dst_addr = PCIE_RC_MEM_ADDR;

	/* Data element #0 */
	offset = 0x2000;
	size = 0x18;
	pcie_ep_prepare_dma_data(0xAAAA0000, PCIE_HDMA_LOCAL_DAT_ADDR_CM7 + offset, size);
	pcie_ep_make_data_element(&elems[0], ctrl, size, src_addr + offset, dst_addr + offset);

	/* Data element #1 */
	offset = 0x2100;
	size = 0x10;
	pcie_ep_prepare_dma_data(0xAAAA1000, PCIE_HDMA_LOCAL_DAT_ADDR_CM7 + offset, size);
	pcie_ep_make_data_element(&elems[1], ctrl, size, src_addr + offset, dst_addr + offset);

	/* Data element #2 */
	offset = 0x2200;
	size = 0x30;
	pcie_ep_prepare_dma_data(0xAAAA2000, PCIE_HDMA_LOCAL_DAT_ADDR_CM7 + offset, size);
	pcie_ep_make_data_element(&elems[2], ctrl, size, src_addr + offset, dst_addr + offset);

	/* Link element */
	ctrl = LINK_EL_CONTROL_LLP | LINK_EL_CONTROL_CYCLE_BIT; /* Jump to another list */
	pcie_ep_make_link_element(&elems[3], ctrl, next_location);
}

static void pcie_ep_make_last_hdma_descriptor(struct pcie_descriptor *hdma_desc)
{
	struct pcie_hdma_element *elems = hdma_desc->elements;
	uint32_t offset, size, ctrl;
	uint64_t src_addr, dst_addr;

	ctrl = DAT_EL_CONTROL_CYCLE_BIT;
	src_addr = PCIE_HDMA_LOCAL_DAT_ADDR;
	dst_addr = PCIE_RC_MEM_ADDR;

	/* Data element #0 */
	offset = 0x2300;
	size = 0x18;
	pcie_ep_prepare_dma_data(0xBBBB0000, PCIE_HDMA_LOCAL_DAT_ADDR_CM7 + offset, size);
	pcie_ep_make_data_element(&elems[0], ctrl, size, src_addr + offset, dst_addr + offset);

	/* Data element #1 */
	offset = 0x2400;
	size = 0x10;
	pcie_ep_prepare_dma_data(0xBBBB1000, PCIE_HDMA_LOCAL_DAT_ADDR_CM7 + offset, size);
	pcie_ep_make_data_element(&elems[1], ctrl, size, src_addr + offset, dst_addr + offset);

	/* Data element #2 */
	offset = 0x2500;
	size = 0x30;
	pcie_ep_prepare_dma_data(0xBBBB2000, PCIE_HDMA_LOCAL_DAT_ADDR_CM7 + offset, size);
	pcie_ep_make_data_element(&elems[2], ctrl, size, src_addr + offset, dst_addr + offset);

	/* Link element */
	ctrl = LINK_EL_CONTROL_LLP;
	pcie_ep_make_link_element(&elems[3], ctrl, 0);
}

static void pcie_ep_make_hdma_read_descriptor(struct pcie_descriptor *hdma_desc, uint64_t next_location)
{
	struct pcie_hdma_element *elems = hdma_desc->elements;
	uint32_t offset, dst_offset, size, ctrl;
	uint64_t src_addr, dst_addr;

	ctrl = DAT_EL_CONTROL_CYCLE_BIT;
	src_addr = PCIE_RC_MEM_ADDR;
	dst_addr = PCIE_HDMA_LOCAL_DAT_ADDR;

	/* Data element #0 */
	offset = 0x2000;
	dst_offset = 0x3000;
	size = 0x18;
	pcie_ep_make_data_element(&elems[0], ctrl, size, src_addr + offset, dst_addr + dst_offset);

	/* Data element #1 */
	offset = 0x2100;
	dst_offset = 0x3100;
	size = 0x10;
	pcie_ep_make_data_element(&elems[1], ctrl, size, src_addr + offset, dst_addr + dst_offset);

	/* Data element #2 */
	offset = 0x2200;
	dst_offset = 0x3200;
	size = 0x30;
	pcie_ep_make_data_element(&elems[2], ctrl, size, src_addr + offset, dst_addr + dst_offset);

	/* Link element */
	ctrl = LINK_EL_CONTROL_LLP | LINK_EL_CONTROL_CYCLE_BIT; /* Jump to another list */
	pcie_ep_make_link_element(&elems[3], ctrl, next_location);
}

static void pcie_ep_make_last_hdma_read_descriptor(struct pcie_descriptor *hdma_desc)
{
	struct pcie_hdma_element *elems = hdma_desc->elements;
	uint32_t offset, dst_offset, size, ctrl;
	uint64_t src_addr, dst_addr;

	ctrl = DAT_EL_CONTROL_CYCLE_BIT;
	src_addr = PCIE_RC_MEM_ADDR;
	dst_addr = PCIE_HDMA_LOCAL_DAT_ADDR;

	/* Data element #0 */
	offset = 0x2300;
	dst_offset = 0x3300;
	size = 0x18;
	pcie_ep_make_data_element(&elems[0], ctrl, size, src_addr + offset, dst_addr + dst_offset);

	/* Data element #1 */
	offset = 0x2400;
	dst_offset = 0x3400;
	size = 0x10;
	pcie_ep_make_data_element(&elems[1], ctrl, size, src_addr + offset, dst_addr + dst_offset);

	/* Data element #2 */
	offset = 0x2500;
	dst_offset = 0x3500;
	size = 0x30;
	pcie_ep_make_data_element(&elems[2], ctrl, size, src_addr + offset, dst_addr + dst_offset);

	/* Link element */
	ctrl = LINK_EL_CONTROL_LLP;
	pcie_ep_make_link_element(&elems[3], ctrl, 0);
}

static void polling_hdma_transfer_done(struct pcie_epc *epc, uint32_t channel)
{
	const struct dw_pcie_config *cfg = epc->cfg;

	volatile struct pcie_ctrl_pf0_hdma_cap_hdma_register *hdma_reg;
	uint32_t current_status;

	if (channel >= HDMA_WRITE_CH0 && channel <= HDMA_WRITE_CH15) {
		hdma_reg = cfg->hdma_base[channel];

		do {
			current_status = hdma_reg->pf0_hdma_cap_hdma_status_off_wrch.status;
		} while (current_status == CHAN_STAT_RUNNING);
	} else if (channel >= HDMA_READ_CH0 && channel <= HDMA_READ_CH15) {
		hdma_reg = cfg->hdma_base[channel - HDMA_READ_CH0];

		do {
			current_status = hdma_reg->pf0_hdma_cap_hdma_status_off_rdch.status;
		} while (current_status == CHAN_STAT_RUNNING);
	} else {
		printf("%s: Detected invalid channel number (%d)\n", __func__, channel);
		return;
	}

	printf("HDMA channel#%d: Data transfer complete!\n", channel);
}

void test_non_linked_list_write(struct pcie_ep_hdma_controller *hdmac, uint64_t sar,
								uint64_t dar, uint32_t size)
{
	struct pcie_hdma_block_config hdma_cfg_blk;
	struct pcie_hdma_config hdma_cfg;
	uint8_t channel = HDMA_WRITE_CH0;

	hdma_cfg_blk.source_address = sar;
	hdma_cfg_blk.dest_address = dar;
	hdma_cfg_blk.block_size = size;

	hdma_cfg.head_block = &hdma_cfg_blk;
	hdma_cfg.hdma_callback = NULL;
	hdma_cfg.callback_arg = NULL;

	dw_hdma_config(hdmac, channel, &hdma_cfg);
	pcie_hdma_transfer_start(hdmac, channel);

	polling_hdma_transfer_done(hdmac->epc, channel);
}

void test_non_linked_list_read(struct pcie_ep_hdma_controller *hdmac, uint64_t sar,
							   uint64_t dar, uint32_t size)
{
	struct pcie_hdma_block_config hdma_cfg_blk;
	struct pcie_hdma_config hdma_cfg;
	uint8_t channel = HDMA_READ_CH0;

	hdma_cfg_blk.source_address = sar;
	hdma_cfg_blk.dest_address = dar;
	hdma_cfg_blk.block_size = size;

	hdma_cfg.head_block = &hdma_cfg_blk;
	hdma_cfg.hdma_callback = NULL;
	hdma_cfg.callback_arg = NULL;

	dw_hdma_config(hdmac, channel, &hdma_cfg);
	pcie_hdma_transfer_start(hdmac, channel);

	polling_hdma_transfer_done(hdmac->epc, channel);
}

/*
 * Brief explanation
 * : For linked list mode write test, create two descriptors on BLK_PCIE INIMEM, which this location
 * was specified by rebellions.
 * Each descriptor has three data elements and one link element.
 * Data for a data element are prepared when a descriptor is created.
 * After data and descriptors are prepared, HDMA write is triggered.
 */
static void test_linked_list_write(struct pcie_ep_hdma_controller *hdmac, uint32_t ch)
{
	struct pcie_hdma_block_config hdma_cfg_blk;
	struct pcie_hdma_config hdma_cfg;

	/* Prepare descriptor */
	wch_descriptor[0].elements = wch_elems[0];
	wch_descriptor[1].elements = wch_elems[1];

	uint64_t next_desc_address = (uint32_t)(wch_descriptor[1].elements) + BLK_PCIE_INTMEM_BASE;

	pcie_ep_make_hdma_descriptor(&wch_descriptor[0], next_desc_address);
	pcie_ep_make_last_hdma_descriptor(&wch_descriptor[1]);

	/* Prepare hdma config */
	hdma_cfg_blk.source_address = (uint32_t)(wch_descriptor[0].elements) + BLK_PCIE_INTMEM_BASE;

	hdma_cfg.head_block = &hdma_cfg_blk;
	hdma_cfg.hdma_callback = NULL;
	hdma_cfg.callback_arg = NULL;

	dw_hdma_config(hdmac, ch, &hdma_cfg);
	pcie_hdma_transfer_start(hdmac, ch);

	polling_hdma_transfer_done(hdmac->epc, ch);
}

/*
 * Brief explanation
 * : For linked list mode read test, create two descriptors on BLK_PCIE INIMEM, which this location
 * was specified by rebellions.
 * Each descriptor has three data elements and one link element.
 * After descriptors are prepared, HDMA read is triggered.
 *
 * To read data from xtor in zebu, it is recommended to perform the HDMA write test above before
 * performing this HDMA read test.
 */
static void test_linked_list_read(struct pcie_ep_hdma_controller *hdmac, uint32_t ch)
{
	struct pcie_hdma_block_config hdma_cfg_blk;
	struct pcie_hdma_config hdma_cfg;

	/* Prepare descriptor */
	rch_descriptor[0].elements = rch_elems[0];
	rch_descriptor[1].elements = rch_elems[1];

	uint64_t next_desc_address = (uint32_t)(rch_descriptor[1].elements) + BLK_PCIE_INTMEM_BASE;

	pcie_ep_make_hdma_read_descriptor(&rch_descriptor[0], next_desc_address);
	pcie_ep_make_last_hdma_read_descriptor(&rch_descriptor[1]);

	/* Prepare hdma config */
	hdma_cfg_blk.load_link_pointer = (uint32_t)(rch_descriptor[0].elements) + BLK_PCIE_INTMEM_BASE;

	hdma_cfg.head_block = &hdma_cfg_blk;
	hdma_cfg.hdma_callback = NULL;
	hdma_cfg.callback_arg = NULL;

	dw_hdma_config(hdmac, ch, &hdma_cfg);
	pcie_hdma_transfer_start(hdmac, ch);

	polling_hdma_transfer_done(hdmac->epc, ch);
}

static void epf_make_hdma_descriptor(struct pcie_hdma_element *elems, struct pcie_hdma_element *next_elems,
									 int32_t num, uint64_t *src_addr, uint64_t *dst_addr,
									 uint32_t *size)
{
	uint32_t ctrl;
	int i;

	/* Data elements */
	for (i = 0; i < num; i++) {
		ctrl = DAT_EL_CONTROL_CYCLE_BIT;
		pcie_ep_make_data_element(&elems[i], ctrl, size[i], src_addr[i], dst_addr[i]);
	}

	/* Link element */
	if (next_elems) {
		uint64_t next_desc_address = (uint32_t)next_elems + BLK_PCIE_INTMEM_BASE;

		ctrl = LINK_EL_CONTROL_LLP | LINK_EL_CONTROL_CYCLE_BIT; /* Jump to another list */
		pcie_ep_make_link_element(&elems[i], ctrl, next_desc_address);

	} else {
		ctrl = LINK_EL_CONTROL_LLP;
		pcie_ep_make_link_element(&elems[i], ctrl, 0);
	}
}

void epf_test_start_hdma_linked_list(struct pcie_ep_hdma_controller *hdmac, uint32_t ch, int32_t num,
									 uint64_t *src_addr, uint64_t *dst_addr, uint32_t *size)
{
	epf_make_hdma_descriptor(epf_elems0, epf_elems1, num, src_addr, dst_addr, size);
	epf_make_hdma_descriptor(epf_elems1, 0, num, src_addr + num, dst_addr + num, size);

	struct pcie_hdma_block_config hdma_cfg_blk;
	struct pcie_hdma_config hdma_cfg;

	/* Prepare hdma config */
	hdma_cfg_blk.load_link_pointer = (uint32_t)(epf_elems0) + BLK_PCIE_INTMEM_BASE;
	hdma_cfg.head_block = &hdma_cfg_blk;
	hdma_cfg.hdma_callback = NULL;
	hdma_cfg.callback_arg = NULL;

	dw_hdma_config(hdmac, ch, &hdma_cfg);
	pcie_hdma_transfer_start(hdmac, ch);

	polling_hdma_transfer_done(hdmac->epc, ch);
}

void test_pcie_set_hdma_lut(int argc, char *argv[])
{
	uint32_t ch, sid, ssid, ssidv;
	struct pcie_epc *epc;

	if (argc != 5) {
		printf("Check command\n%s", help_pcie_hdma);
		return;
	}

	ch = strtoul(argv[1], NULL, 0);
	sid = strtoul(argv[2], NULL, 0);
	ssid = strtoul(argv[3], NULL, 0);
	ssidv = strtoul(argv[4], NULL, 0);

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return;
	}

	set_hdma_lut(epc, ch, sid, ssid, ssidv);
}

void test_pcie_invalidate_hdma_lut(int argc, char *argv[])
{
	uint32_t ch;
	struct pcie_epc *epc;

	if (argc != 2) {
		printf("Check command\n%s", help_pcie_hdma);
		return;
	}

	ch = strtoul(argv[1], NULL, 0);

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return;
	}

	invalidate_hdma_lut(epc, ch);
}

void test_pcie_prepare_data(int argc, char *argv[])
{
	uint32_t seed, addr_cm7, size;

	if (argc != 4) {
		printf("Check command\n%s", help_pcie_hdma);
		return;
	}

	seed = strtoul(argv[1], NULL, 0);
	addr_cm7 = strtoul(argv[2], NULL, 0);
	size = strtoul(argv[3], NULL, 0);

	pcie_ep_prepare_dma_data(seed, addr_cm7, size);
}

int32_t test_pcie_hdma_non_ll_mode(int argc, char *argv[])
{
	char *rw;
	uint64_t sar, dar;
	uint32_t size;
	struct pcie_epc *epc;
	struct pcie_ep_hdma_controller *pcie_ep_hdmac;

	printf("PCIe HDMA non-linked list mode test\n");

	if (argc != 5) {
		printf("Check command\n%s", help_pcie_hdma);
		return RL_BADARG;
	}

	rw = argv[1];
	sar = strtoull(argv[2], NULL, 0);
	dar = strtoull(argv[3], NULL, 0);
	size = strtoul(argv[4], NULL, 0);

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return RL_BADARG;
	}

	pcie_ep_hdmac = pcie_hdmac_create(epc);
	if (!pcie_ep_hdmac) {
		printf("Failed to create PCIe HDMA controller\n");
		return RL_ERROR;
	}

	if (strcmp(rw, "w") == 0)
		test_non_linked_list_write(pcie_ep_hdmac, sar, dar, size);
	else if (strcmp(rw, "r") == 0)
		test_non_linked_list_read(pcie_ep_hdmac, sar, dar, size);
	else {
		printf("Please enter proper option (r/w)\n");
		return RL_ERROR;
	}

	return RL_OK;
}

int32_t test_pcie_hdma_ll_mode(int argc, char *argv[])
{
	char *rw;
	uint32_t ch;
	struct pcie_epc *epc;
	struct pcie_ep_hdma_controller *pcie_ep_hdmac;

	printf("PCIe HDMA linked list mode test\n");

	if (argc != 3) {
		printf("Check command\n%s", help_pcie_hdma);
		return RL_BADARG;
	}

	rw = argv[1];
	ch = strtoul(argv[2], NULL, 0);

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return RL_ERROR;
	}

	pcie_ep_hdmac = pcie_hdmac_create(epc);
	if (!pcie_ep_hdmac) {
		printf("Failed to create PCIe HDMA controller\n");
		return RL_ERROR;
	}

	if (strcmp(rw, "w") == 0 && (ch <= HDMA_WRITE_CH0 || ch > HDMA_WRITE_CH15)) {
		printf("HDMA write channel for linked list mode should be in the range 1 to 15\n");
		return RL_ERROR;
	} else if (strcmp(rw, "r") == 0 && (ch <= HDMA_READ_CH0 || ch > HDMA_READ_CH15)) {
		printf("HDMA read channel for linked list mode should be in the range 17 to 31\n");
		return RL_ERROR;
	} else if (strcmp(rw, "r") != 0 && strcmp(rw, "w") != 0) {
		printf("Please enter proper option (r/w)\n");
		return RL_ERROR;
	}

	if (strcmp(rw, "w") == 0)
		test_linked_list_write(pcie_ep_hdmac, ch);
	else if (strcmp(rw, "r") == 0)
		test_linked_list_read(pcie_ep_hdmac, ch);

	return RL_OK;
}

int32_t test_pcie_select_function(int argc, char *argv[])
{
	bool vf_active;
	uint32_t ch, func_num;
	struct pcie_epc *epc;
	struct pcie_ep_hdma_controller *pcie_ep_hdmac;

	if (argc != 4) {
		printf("Check command\n%s", help_pcie_hdma);
		return RL_BADARG;
	}

	ch = strtoul(argv[1], NULL, 0);
	vf_active = strtoul(argv[2], NULL, 0);
	func_num = strtoul(argv[3], NULL, 0);

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return RL_ERROR;
	}

	pcie_ep_hdmac = pcie_hdmac_create(epc);
	if (!pcie_ep_hdmac) {
		printf("Failed to create PCIe HDMA controller\n");
		return RL_ERROR;
	}

	pcie_hdma_select_function(pcie_ep_hdmac, ch, vf_active, func_num);

	return RL_OK;
}
