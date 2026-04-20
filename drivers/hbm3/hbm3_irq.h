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

#include <driver.h>
#include "stdlib.h"
#include <interrupt.h>
#include <string.h>
// #include "gic.h"

// IRQ per channel
#define HBM_SS_IRQ_CH0 162
#define HBM_SS_IRQ_CH1 163
#define HBM_SS_IRQ_CH2 164
#define HBM_SS_IRQ_CH3 165
#define HBM_SS_IRQ_CH4 166
#define HBM_SS_IRQ_CH5 167
#define HBM_SS_IRQ_CH6 168
#define HBM_SS_IRQ_CH7 169
#define HBM_SS_IRQ_CH8 170
#define HBM_SS_IRQ_CH9 171
#define HBM_SS_IRQ_CH10 172
#define HBM_SS_IRQ_CH11 173
#define HBM_SS_IRQ_CH12 174
#define HBM_SS_IRQ_CH13 175
#define HBM_SS_IRQ_CH14 176
#define HBM_SS_IRQ_CH15 177

#define MAX_HBM3IRQ_NUM 30
#define HBM3IRQ_BITS 0x3FFFFFFF

enum HBM3_INTR_BITPOS {
	HBM3_INTR_BITPOS_AXI_DECERRR              =  0,
	HBM3_INTR_BITPOS_UNC_DQPERR_ON_WT         =  1,
	HBM3_INTR_BITPOS_UNC_DQPERR_ON_RD         =  2,
	HBM3_INTR_BITPOS_ECC1BIT_DET              =  3,
	HBM3_INTR_BITPOS_ECC1BIT_THRESH           =  4,
	HBM3_INTR_BITPOS_UNC_ECC2BIT              =  5,
	HBM3_INTR_BITPOS_AXI_WDATAIN_PERR_BIT     =  6,
	HBM3_INTR_BITPOS_WTDATA_PERROUT_BIT       =  7,
	HBM3_INTR_BITPOS_AXI_DECERRR_PS1          =  8,
	HBM3_INTR_BITPOS_UNC_DQPERR_ON_WT_PS1     =  9,
	HBM3_INTR_BITPOS_UNC_DQPERR_ON_RD_PS1     = 10,
	HBM3_INTR_BITPOS_ECC1BIT_DET_PS1          = 11,
	HBM3_INTR_BITPOS_ECC1BIT_THRESH_PS1       = 12,
	HBM3_INTR_BITPOS_UNC_ECC2BIT_PS1          = 13,
	HBM3_INTR_BITPOS_AXI_WDATAIN_PERR_BIT_PS1 = 14,
	HBM3_INTR_BITPOS_WTDATA_PERROUT_BIT_PS1   = 15,
	HBM3_INTR_BITPOS_CA_PERR_DET              = 16,
	HBM3_INTR_BITPOS_CATTRIP                  = 17,
	HBM3_INTR_BITPOS_TEMPCHNG                 = 18,
	HBM3_INTR_BITPOS_CSR_PARERR               = 19,
	HBM3_INTR_BITPOS_DFI_TRAINING_COMPLETE    = 20,
	HBM3_INTR_BITPOS_DFI_INIT_COMPLETE        = 21,
	HBM3_INTR_BITPOS_PSLVERR                  = 23,
	HBM3_INTR_BITPOS_MEMARRAY_CORR_ERR        = 24,
	HBM3_INTR_BITPOS_MEMARRAY_UNC_ERR         = 25,
	HBM3_INTR_BITPOS_MEMARRAY_INVALID_SEV     = 26,
	HBM3_INTR_BITPOS_MEMARRAY_CORR_ERR_PS1    = 27,
	HBM3_INTR_BITPOS_MEMARRAY_UNC_ERR_PS1     = 28,
	HBM3_INTR_BITPOS_MEMARRAY_INVALID_SEV_PS1 = 29
};

int hbm3_interrupt_mask(uint32_t ch, uint32_t irq_mask);
int hbm3_interrupt_clear(uint32_t ch);
int hbm3_interrupt_gen(uint32_t ch, uint32_t irq);
int hbm3_interrupt_enable(uint32_t ch);
int hbm3_interrupt_disable(uint32_t ch);
int hbm3_interrupt_init(void);
