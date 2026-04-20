/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include <stdio.h>

#include "hbm3.h"
#include "ddr_csr.h"
#include "icon.h"
#include "hbm3_irq.h"

struct hbm3_irq_config {
	uint32_t ch;
	struct ddr_csr *csr;
	uint32_t irq_num;
};

static struct hbm3_irq_config hbm3_irq_cfg[] = {
	{0, (struct ddr_csr *)(HBM3_CON_0_BASE), HBM_SS_IRQ_CH0},
	{1, (struct ddr_csr *)(HBM3_CON_1_BASE), HBM_SS_IRQ_CH1},
	{2, (struct ddr_csr *)(HBM3_CON_2_BASE), HBM_SS_IRQ_CH2},
	{3, (struct ddr_csr *)(HBM3_CON_3_BASE), HBM_SS_IRQ_CH3},
	{4, (struct ddr_csr *)(HBM3_CON_4_BASE), HBM_SS_IRQ_CH4},
	{5, (struct ddr_csr *)(HBM3_CON_5_BASE), HBM_SS_IRQ_CH5},
	{6, (struct ddr_csr *)(HBM3_CON_6_BASE), HBM_SS_IRQ_CH6},
	{7, (struct ddr_csr *)(HBM3_CON_7_BASE), HBM_SS_IRQ_CH7},
	{8, (struct ddr_csr *)(HBM3_CON_8_BASE), HBM_SS_IRQ_CH8},
	{9, (struct ddr_csr *)(HBM3_CON_9_BASE), HBM_SS_IRQ_CH9},
	{10, (struct ddr_csr *)(HBM3_CON_10_BASE), HBM_SS_IRQ_CH10},
	{11, (struct ddr_csr *)(HBM3_CON_11_BASE), HBM_SS_IRQ_CH11},
	{12, (struct ddr_csr *)(HBM3_CON_12_BASE), HBM_SS_IRQ_CH12},
	{13, (struct ddr_csr *)(HBM3_CON_13_BASE), HBM_SS_IRQ_CH13},
	{14, (struct ddr_csr *)(HBM3_CON_14_BASE), HBM_SS_IRQ_CH14},
	{15, (struct ddr_csr *)(HBM3_CON_15_BASE), HBM_SS_IRQ_CH15},
};

static bool hbm3_controller_interrupt(struct hbm3_irq_config *cfg, uint32_t bitpos)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)cfg->csr;
	uint32_t stat;
	bool is_assert = false;

	/* Handle the specific interrupt event */
	switch (bitpos) {
	case HBM3_INTR_BITPOS_AXI_DECERRR:
		printf("HBM3 Channel %d: Out of range AXI address error detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->axi_if_stat_axi_decerr.stat_axi_decerr;
		printf("STAT_AXI_DECERR : 0x%08x\n", stat);

		is_assert = true;
		break;
	case HBM3_INTR_BITPOS_UNC_DQPERR_ON_WT:
		printf("HBM3 Channel %d: Uncorrectable DQ parity error corresponding to write detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->parity_error_stat_write_data_parity_error.stat_write_data_parity_error;
		printf("STAT_WRITE_DATA_PARITY_ERROR : 0x%08x\n", stat);

		is_assert = true;
		break;
	case HBM3_INTR_BITPOS_UNC_DQPERR_ON_RD:
		printf("HBM3 Channel %d: Uncorrectable DQ parity error corresponding to read detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->parity_error_stat_read_data_parity_error.stat_read_data_parity_error;
		printf("STAT_READ_DATA_PARITY_ERROR : 0x%08x\n", stat);

		is_assert = true;
		break;
	case HBM3_INTR_BITPOS_ECC1BIT_DET:
		printf("HBM3 Channel %d: 1-bit ECC error detected during read. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->ecc_stat_err_stat_ecc_1bit_error_addr.stat_ecc_1bit_error_addr;
		printf("STAT_ECC_1BIT_ERROR_ADDR : 0x%08x\n", stat);
		stat = hbm3_mc->ecc_stat_err_stat_ecc_1bit_pos.stat_ecc_1bit_pos;
		printf("STAT_ECC_1BIT_POS : 0x%08x\n", stat);
		stat = hbm3_mc->ecc_stat_err_stat_ecc_1bit_rmw.stat_ecc_1bit_rmw;
		printf("STAT_ECC_1BIT_RMW : 0x%08x\n", stat);
		break;
	case HBM3_INTR_BITPOS_ECC1BIT_THRESH:
		printf("HBM3 Channel %d: 1-bit ECC error detected above threshold value during read. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->ecc_stat_err_stat_int_ecc_1bit_thresh.stat_int_ecc_1bit_thresh;
		printf("STAT_INT_ECC_1BIT_THRESH : 0x%08x\n", stat);
		/* TODO: determine whether to fail if 1-bit ECC exceeds thresholds */
		break;
	case HBM3_INTR_BITPOS_UNC_ECC2BIT:
		printf("HBM3 Channel %d: Uncorrectable 2-bit ECC error detected during read. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->ecc_stat_err_stat_ecc_2bit_error_addr.stat_ecc_2bit_error_addr;
		printf("STAT_ECC_2BIT_ERROR_ADDR : 0x%08x\n", stat);
		stat = hbm3_mc->ecc_stat_err_stat_ecc_2bit_rmw.stat_ecc_2bit_rmw;
		printf("STAT_ECC_2BIT_RMW : 0x%08x\n", stat);

		is_assert = true;
		break;
	case HBM3_INTR_BITPOS_CA_PERR_DET:
		printf("HBM3 Channel %d: CA parity error detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->parity_error_stat_ca_parity_error.stat_ca_parity_error;
		printf("STAT_CA_PARITY_ERROR : 0x%08x\n", stat);
		break;
	case HBM3_INTR_BITPOS_CATTRIP:
		printf("HBM3 Channel %d: CATTRIP detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->dfi_stat_dfi_cattrip.stat_dfi_cattrip;
		printf("STAT_DFI_CATTRIP : 0x%08x\n", stat);

		is_assert = true;
		break;
	case HBM3_INTR_BITPOS_TEMPCHNG:
		printf("HBM3 Channel %d: Temperature change detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->dfi_stat_dfi_tcr_temp.stat_dfi_tcr_temp;
		printf("STAT_DFI_TCR_TEMP : 0x%08x\n", stat);
		break;
	case HBM3_INTR_BITPOS_CSR_PARERR:
		printf("HBM3 Channel %d: CSR parity error detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->data_int_stat_csr_parity_error.val;
		printf("STAT_CSR_PARITY_ERROR : 0x%08x\n", stat);
		break;
	case HBM3_INTR_BITPOS_DFI_TRAINING_COMPLETE:
		printf("HBM3 Channel %d: DFI training complete. IRQ_BIT %02d.\n", cfg->ch,
			   bitpos);
		stat = hbm3_mc->dfi_stat_dfi_training_error.stat_dfi_training_error;
		printf("STAT_DFI_TRAINING_ERROR : 0x%08x\n", stat);
		break;
	case HBM3_INTR_BITPOS_DFI_INIT_COMPLETE:
		printf("HBM3 Channel %d: DFI initialization complete. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->dfi_stat_dfi_error.stat_dfi_error;
		printf("STAT_DFI_ERROR : 0x%08x\n", stat);
		stat = hbm3_mc->dfi_stat_dfi_error_info.stat_dfi_error_info;
		printf("STAT_DFI_ERROR_INFO : 0x%08x\n", stat);
		break;
	case HBM3_INTR_BITPOS_PSLVERR:
		printf("HBM3 Channel %d: APB PSLVERR error detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		break;
	case HBM3_INTR_BITPOS_MEMARRAY_CORR_ERR:
		printf("HBM3 Channel %d: Memory array correctable error detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->mc_base4_stat_mem_array_mbit_corr_err.stat_mem_array_mbit_corr_err;
		printf("STAT_MEM_ARRAY_MBIT_CORR_ERR : 0x%08x\n", stat);
		break;
	case HBM3_INTR_BITPOS_MEMARRAY_UNC_ERR:
		printf("HBM3 Channel %d: Memory array uncorrectable error detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		icon_get_ecs_error_log(get_hbm_cfg(CHIPLET_ID), cfg->ch);
		// TODO: Icon temperature read

		is_assert = true;
		break;
	case HBM3_INTR_BITPOS_MEMARRAY_INVALID_SEV:
		printf("HBM3 Channel %d: Memory array invalid severity detected. IRQ_BIT %02d.\n",
			   cfg->ch, bitpos);
		stat = hbm3_mc->mc_base4_stat_mem_array_severity_code.stat_mem_array_severity_code;
		printf("STAT_MEM_ARRAY_SERVERITY_CODE : 0x%08x\n", stat);

		is_assert = true;
		break;
	/* Unsupported case: Parity bits of controller AXI port are tied */
	case HBM3_INTR_BITPOS_AXI_WDATAIN_PERR_BIT:
	case HBM3_INTR_BITPOS_WTDATA_PERROUT_BIT:
	/* Unsupported case: Pseudo channel 1 */
	case HBM3_INTR_BITPOS_AXI_DECERRR_PS1:
	case HBM3_INTR_BITPOS_UNC_DQPERR_ON_WT_PS1:
	case HBM3_INTR_BITPOS_UNC_DQPERR_ON_RD_PS1:
	case HBM3_INTR_BITPOS_ECC1BIT_DET_PS1:
	case HBM3_INTR_BITPOS_ECC1BIT_THRESH_PS1:
	case HBM3_INTR_BITPOS_UNC_ECC2BIT_PS1:
	case HBM3_INTR_BITPOS_AXI_WDATAIN_PERR_BIT_PS1:
	case HBM3_INTR_BITPOS_WTDATA_PERROUT_BIT_PS1:
	case HBM3_INTR_BITPOS_MEMARRAY_CORR_ERR_PS1:
	case HBM3_INTR_BITPOS_MEMARRAY_UNC_ERR_PS1:
	case HBM3_INTR_BITPOS_MEMARRAY_INVALID_SEV_PS1:
	default:
		printf("HBM3 Channel %d: Unsupported IRQ_BIT %02d.\n", cfg->ch, bitpos);

		is_assert = true; // Mark as assert for unknown interrupts
		break;
	}

	return is_assert;
}

void hbm3_interrupt_handler(struct hbm3_irq_config *cfg)
{
	uint32_t ulPreviousMask;
	uint32_t bitpos;
	bool is_assert = false;

	ulPreviousMask = portENTER_CRITICAL_FROM_ISR();

	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)cfg->csr;

	uint32_t irq = hbm3_mc->mc_base3_stat_interrupt_0.stat_interrupt;

	printf("hbm3 ch%d irq 0x%08x called\r\n", cfg->ch, irq);

	while (irq) {
		bitpos = __builtin_ctz(irq); // Find the first set bit position
		irq = (irq & ~(1 << bitpos)); // Clear the bit

		is_assert |= hbm3_controller_interrupt(cfg, bitpos);
	}

	if (is_assert) {
		printf("HBM3 Channel %d: Asserted interrupt.\n", cfg->ch);
		// TODO: add assert handling logic here
	}

	hbm3_interrupt_clear(cfg->ch);
	portEXIT_CRITICAL_FROM_ISR(ulPreviousMask);
}

int hbm3_interrupt_mask(uint32_t ch, uint32_t irq_mask)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)(HBM3_CON_0_BASE + (ch * HBM3_CON_BASE_OFFSET));

	uint32_t mask = hbm3_mc->mc_base3_init_interrupt_mask_0.val;

	mask = mask | irq_mask;

	hbm3_mc->mc_base3_init_interrupt_mask_0.init_interrupt_mask = mask;

	return 0;
}

int hbm3_interrupt_clear(uint32_t ch)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)(HBM3_CON_0_BASE + (ch * HBM3_CON_BASE_OFFSET));

	uint32_t irq = hbm3_mc->mc_base3_stat_interrupt_0.stat_interrupt;

	irq = irq & (HBM3IRQ_BITS);

	hbm3_mc->mc_base3_stat_interrupt_0.stat_interrupt = irq;

	return 0;
}

int hbm3_interrupt_gen(uint32_t ch, uint32_t irq)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)(HBM3_CON_0_BASE + (ch * HBM3_CON_BASE_OFFSET));

	hbm3_mc->mc_base3_init_interrupt_gen_0.init_interrupt_gen = irq;

	return 0;
}

int hbm3_interrupt_enable(uint32_t ch)
{
	uint32_t irq_num = HBM_SS_IRQ_CH0 + ch;

	connect_interrupt_with_handler(irq_num, 0, IRQ_TYPE_LEVEL,
								   hbm3_interrupt_handler, &hbm3_irq_cfg[ch]);
	return 0;
}

int hbm3_interrupt_disable(uint32_t ch)
{
	uint32_t irq_num = HBM_SS_IRQ_CH0 + ch;

	connect_interrupt_with_handler(irq_num, 0, IRQ_TYPE_LEVEL,
								   hbm3_interrupt_handler, &hbm3_irq_cfg[ch]);
	return 0;
}

int hbm3_interrupt_init(void)
{
	for (uint32_t ch = 0; ch < HBM3_NUM_CH; ch++) {
		hbm3_interrupt_clear(ch);
		hbm3_interrupt_mask(ch, 1 << HBM3_INTR_BITPOS_DFI_INIT_COMPLETE);
		hbm3_interrupt_enable(ch);
	}

	return 0;
}

#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(10, hbm3_interrupt_init);
#endif
