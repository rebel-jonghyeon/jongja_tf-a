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

#include <time.h>

#include "FreeRTOS.h"
#include "task.h"

#include "bat.h"
#include "rebel_h_platform.h"

#include "pcie_dw.h"
#include "pcie_dw_msix.h"
#include "pcie_dw_iatu.h"
#include "pcie_dw_bar.h"
#include "pcie_dw_hdma.h"
#include "pcie_sysreg.h"
#include "pcie_doe.h"

#include "test_common.h"
#include "test_pcie.h"
#include "test_pcie_hdma.h"

#define PCIE_EP_PF_TEST_ADDR_BAT (DRAM_USER_BAT_BASE + 0x1000)
#define PCIE_EP_VF_TEST_ADDR_BAT (DRAM_USER_BAT_BASE + 0x2000)

#define PCIE_EP_TEST_REGION (DRAM_USER_BASE)
#define PCIE_EP_TEST_REGION_BAT (DRAM_USER_BAT_BASE)
#define PCIE_EP_TEST_DMA_REGION (DRAM_USER_BASE + 0x10000000)

#define PCIE_EP_TEST_HOST_REGION (PCIE_HOST_BASE)
#define PCIE_EP_TEST_HOST_REGION_BAT (PCIE_HOST_BAT_BASE)

#define IRQ_TYPE_UNDEFINED			-1
#define IRQ_TYPE_INTX				0
#define IRQ_TYPE_MSI				1
#define IRQ_TYPE_MSIX				2

#define COMMNAD_NOT_RECEIVED		0
#define COMMAND_RAISE_INTX_IRQ		BIT(0)
#define COMMAND_RAISE_MSI_IRQ		BIT(1)
#define COMMAND_RAISE_MSIX_IRQ		BIT(2)
#define COMMAND_READ				BIT(3)
#define COMMAND_WRITE				BIT(4)
#define COMMAND_COPY				BIT(5)
#define COMMAND_DOE					BIT(6)
#define COMMAND_IATU				BIT(7)

#define STATUS_READ_SUCCESS			BIT(0)
#define STATUS_READ_FAIL			BIT(1)
#define STATUS_WRITE_SUCCESS		BIT(2)
#define STATUS_WRITE_FAIL			BIT(3)
#define STATUS_COPY_SUCCESS			BIT(4)
#define STATUS_COPY_FAIL			BIT(5)
#define STATUS_IRQ_RAISED			BIT(6)
#define STATUS_SRC_ADDR_INVALID		BIT(7)
#define STATUS_DST_ADDR_INVALID		BIT(8)

#define FLAG_USE_DMA				BIT(0)

struct pci_epf_test_reg {
	uint32_t	magic;
	uint32_t	command;
	uint32_t	status;
	uint64_t	src_addr;
	uint64_t	dst_addr;
	uint32_t	size;
	uint32_t	checksum;
	uint32_t	irq_type;
	uint32_t	irq_number;
	uint32_t	flags;
} __packed;

/* num of HDMA data elements */
const int ll_num = 6;

uint32_t crc32_le(uint32_t crc, const uint8_t *data, size_t len)
{
	crc = ~crc;
	while (len--) {
		crc ^= *data++;
		for (int k = 0; k < 8; k++) {
			if (crc & 1)
				crc = (crc >> 1) ^ 0xED88320;
			else
				crc >>= 1;
		}
	}
	return ~crc;
}

void get_random_bytes(void *buf, int len)
{
	uint8_t *p = buf;
	static int seeded;

	if (!seeded) {
		srand(time(NULL));
		seeded = 1;
	}
	for (int i = 0; i < len; i++) {
		p[i] = rand() & 0xFF;
	}
}

static void pci_epf_test_raise_irq(volatile struct pci_epf_test_reg *reg, bool is_vf, uint32_t vf_id)
{
	reg->status |= STATUS_IRQ_RAISED;

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return;
	}

	uint8_t type = is_vf ? TYPE_VF : TYPE_PF; /* 0:PF, 1:VF */
	uint8_t func_id = is_vf ? vf_id : 0;
	uint8_t tc = 0;
	uint8_t vector = reg->irq_number;

	printf("Request MSI-X type[%s] Func ID[%d] TC[%d] vector[%d]\n",
		   (type == TYPE_PF) ? "PF" : "VF", func_id, tc, vector);

	pcie_raise_msix_irq(epc, type, func_id, tc, vector);
}

static void pci_epf_test_copy_by_dma(volatile struct pci_epf_test_reg *reg, bool is_vf, uint32_t vf_id)
{
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return;
	}

	uint64_t sar[ll_num], dar[ll_num], temp_region[ll_num];
	uint32_t size[ll_num];

	sar[0] = reg->src_addr;
	temp_region[0] = PCIE_EP_TEST_DMA_REGION;
	dar[0] = reg->dst_addr;
	size[0] = reg->size;

	for (int i = 1; i < ll_num; i++) {
		/* Notify host that the configuration is done */
		pci_epf_test_raise_irq(reg, is_vf, vf_id);

		/* Wait next command */
		while (!reg->command)
			;
		reg->command = 0;

		sar[i] = reg->src_addr;
		temp_region[i] = temp_region[i - 1] + size[i - 1];
		dar[i] = reg->dst_addr;
		size[i] = reg->size;
	}

	struct pcie_ep_hdma_controller *pcie_ep_hdmac = pcie_hdmac_create(epc);

	if (!pcie_ep_hdmac) {
		printf("Failed to create PCIe HDMA controller\n");
		return;
	}

	set_hdma_lut(epc, HDMA_READ_CH1 % 16, 0, 1, 1);
	pcie_hdma_select_function(pcie_ep_hdmac, HDMA_READ_CH1, is_vf, vf_id);
	epf_test_start_hdma_linked_list(pcie_ep_hdmac, HDMA_READ_CH1, ll_num / 2, sar, temp_region, size);

	pcie_hdma_select_function(pcie_ep_hdmac, HDMA_WRITE_CH1, is_vf, vf_id);
	epf_test_start_hdma_linked_list(pcie_ep_hdmac, HDMA_WRITE_CH1, ll_num / 2, temp_region, dar, size);
}

static void pci_epf_test_read(volatile struct pci_epf_test_reg *reg, bool is_vf, uint32_t vf_id)
{
	uint64_t sar = reg->src_addr;
	uint64_t dar = PCIE_EP_TEST_REGION;
	void *buf = (uint32_t *)(PCIE_EP_TEST_REGION_BAT);
	uint32_t size = reg->size;

	if (CHIPLET_ID == CHIPLET_ID3)
		dar += CHIPLET_BASE_ADDRESS;

	printf("Data Read from Host 0x%0*llx -> 0x%0*llx size: %d\n", 11, sar, 11, dar, size);

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return;
	}

	if (reg->flags & FLAG_USE_DMA) {
		struct pcie_ep_hdma_controller *pcie_ep_hdmac = pcie_hdmac_create(epc);

		if (!pcie_ep_hdmac) {
			printf("Failed to create PCIe HDMA controller\n");
			return;
		}

		pcie_hdma_select_function(pcie_ep_hdmac, HDMA_READ_CH0, is_vf, vf_id);
		set_hdma_lut(epc, HDMA_READ_CH0 % 16, 0, 1, 1);
		test_non_linked_list_read(pcie_ep_hdmac, sar, dar, size);
	} else {
		int8_t index;
		uint64_t base = PCIE_EP_TEST_HOST_REGION;
		uint64_t target = sar;
		void *src_addr = (uint32_t *)(PCIE_EP_TEST_HOST_REGION_BAT);

		if (CHIPLET_ID == CHIPLET_ID3)
			base += CHIPLET_BASE_ADDRESS;

		pcie_configure_outbound_address_match_mode(epc, base, target, size, &index, is_vf, vf_id);
		memcpy(buf, src_addr, size);
		pcie_iatu_disable_region(epc, DW_PCIE_OUTBOUND, index);
	}

	uint32_t crc32 = crc32_le(~0, buf, reg->size);

	if (crc32 == reg->checksum)
		reg->status |= STATUS_READ_SUCCESS;
	else
		reg->status |= STATUS_READ_FAIL;
}

static void pci_epf_test_write(volatile struct pci_epf_test_reg *reg, bool is_vf, uint32_t vf_id)
{
	uint64_t sar = PCIE_EP_TEST_REGION;
	uint64_t dar = reg->dst_addr;
	void *buf = (uint32_t *)(PCIE_EP_TEST_REGION_BAT);
	uint32_t size = reg->size;

	if (CHIPLET_ID == CHIPLET_ID3)
		sar += CHIPLET_BASE_ADDRESS;

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return;
	}

	get_random_bytes(buf, reg->size);
	reg->checksum = crc32_le(~0, buf, reg->size);

	if (reg->flags & FLAG_USE_DMA) {
		struct pcie_ep_hdma_controller *pcie_ep_hdmac = pcie_hdmac_create(epc);

		if (!pcie_ep_hdmac) {
			printf("Failed to create PCIe HDMA controller\n");
			return;
		}

		pcie_hdma_select_function(pcie_ep_hdmac, HDMA_WRITE_CH0, is_vf, vf_id);
		set_hdma_lut(epc, HDMA_WRITE_CH0, 0, 1, 1);
		test_non_linked_list_write(pcie_ep_hdmac, sar, dar, size);
	} else {
		int8_t index;
		uint64_t base = PCIE_EP_TEST_HOST_REGION;
		uint64_t target = dar;
		void *dst_addr = (uint32_t *)(PCIE_EP_TEST_HOST_REGION_BAT);

		if (CHIPLET_ID == CHIPLET_ID3)
			base += CHIPLET_BASE_ADDRESS;

		pcie_configure_outbound_address_match_mode(epc, base, target, size, &index, is_vf, vf_id);
		memcpy(dst_addr, buf, size);
		pcie_iatu_disable_region(epc, DW_PCIE_OUTBOUND, index);
	}

	reg->status |= STATUS_WRITE_SUCCESS;
}

static void pci_epf_test_doe(volatile struct pci_epf_test_reg *reg)
{
	struct pcie_epc *epc = pcie_get_epc();
	struct dw_pcie_drv *data = epc->drv;
	uint32_t *src_addr = data->doe_fifo_addr;
	uint32_t payload[10] = {0,};
	uint32_t len;
	int i;

	src_addr++; /* length is in second DW */
	len = sys_read32((uint32_t)src_addr);

	payload[1] = len & PCI_DOE_HEADER_2_LENGTH;
	for (i = 2; i < len; i++) {
		payload[i] = sys_read32((uint32_t)(++src_addr));
	}

	pcie_doe_write_rmb(epc, len, payload);
}

static void pci_epf_test_iatu(volatile struct pci_epf_test_reg *reg, bool is_vf, uint32_t vf_id)
{
	struct pcie_epc *epc;
	struct pcie_bar_info *bar_info;
	int32_t index;
	int i;

	epc = pcie_get_epc();
	if (!epc) {
		printf("Failed to get PCIe epc\n");
		return;
	}
	bar_info = epc->drv->bar_info;

	for (i = 0; i < 3; i++) {
		if (i != 0) {
			/* Wait next command */
			while (!reg->command)
				;
			reg->command = 0;
		}

		/* Disable default iatu region */
		index = pcie_find_iatu_region_by_bar_num(epc, reg->flags);
		pcie_iatu_disable_region(epc, DW_PCIE_INBOUND, index);

		/* Configure iatu region */
		pcie_configure_inbound_address_match_mode(epc, reg->src_addr, bar_info[reg->flags].phys_addr,
												  bar_info[reg->flags].size, is_vf, vf_id);

		/* Notify host that the configuration is done */
		pci_epf_test_raise_irq(reg, is_vf, vf_id);

		/* Wait for host to finish the test */
		while (!reg->command)
			;
		reg->command = 0;

		/* Restore default iatu region */
		pcie_iatu_disable_match_mode_region(epc, ADDRESS_MATCH_MODE);
		pcie_set_bar(epc->cfg, epc->drv, &bar_info[reg->flags]);

		pci_epf_test_raise_irq(reg, is_vf, vf_id);
	}
}

uint8_t pcie_epf_main(int argc, char *argv[])
{
	bool loop = true;

	volatile struct pci_epf_test_reg *reg;
	uint32_t command;
	uint32_t vf_id = 0;
	bool is_vf = false;
	uint32_t loop_slt = 1;

	if (argc == 1) {
		if (strcmp(argv[0], "clean") == 0) {
			printf("clear DRAM\n");
			memset((void *)PCIE_EP_PF_TEST_ADDR_BAT, 0, sizeof(struct pci_epf_test_reg));
			for (int i = 0; i < 16; i++)
				memset((void *)(PCIE_EP_VF_TEST_ADDR_BAT + i * 0x1000000), 0, sizeof(struct pci_epf_test_reg));

			return true;
		} else {
			loop_slt = strtoul(argv[0], NULL, 0);
			printf("loop %d times\n", loop_slt);
		}
	}

	for (int slt = 0; slt < loop_slt; slt++) {

		while (loop) {
			reg = (struct pci_epf_test_reg *)(PCIE_EP_PF_TEST_ADDR_BAT);
			command = reg->command;
			if (command)
				break;

			for (int i = 0; i < 16; i++) {
				reg = (struct pci_epf_test_reg *)(PCIE_EP_VF_TEST_ADDR_BAT + i * 0x1000000);
				command = reg->command;
				if (command) {
					vf_id = i;
					is_vf = true;
					loop = false;
					break;
				}
			}
			if (loop)
				vTaskDelay(1);
		}

		reg->command = 0;
		reg->status = 0;

		switch (command) {
		case COMMAND_RAISE_MSIX_IRQ:
			printf("COMMAND_RAISE_MSIX_IRQ Received\n");
			pci_epf_test_raise_irq(reg, is_vf, vf_id);
			break;
		case COMMAND_READ:
			printf("COMMAND_READ Received\n");
			pci_epf_test_read(reg, is_vf, vf_id);
			pci_epf_test_raise_irq(reg, is_vf, vf_id);
			break;
		case COMMAND_WRITE:
			printf("COMMAND_WRITE Received\n");
			pci_epf_test_write(reg, is_vf, vf_id);
			pci_epf_test_raise_irq(reg, is_vf, vf_id);
			break;
		case COMMAND_COPY:
			printf("COMMAND_COPY Received\n");
			pci_epf_test_copy_by_dma(reg, is_vf, vf_id);
			pci_epf_test_raise_irq(reg, is_vf, vf_id);
			break;
		case COMMAND_DOE:
			printf("COMMAND_DOE Received\n");
			pci_epf_test_doe(reg);
			pci_epf_test_raise_irq(reg, is_vf, vf_id);
			break;
		case COMMAND_IATU:
			printf("COMMAND_IATU Received\n");
			pci_epf_test_iatu(reg, is_vf, vf_id);
			break;
		default:
			printf("Invalid command 0x%x\n", reg->command);
		}

	}

	return true;
}

CLI_REGISTER(pcie_epf, NULL, pcie_epf_main, "pcie_epf");
