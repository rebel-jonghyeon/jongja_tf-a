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

#pragma once

#define CHIPLET_OFFSET					(0x2000000000ULL)
#define SYSREG_SYSREMAP_PRIVATE			(0x1E00220000ULL)
#define CPMU_PRIVATE					(0x1E00230000ULL)
#define QSPI_ROT						(0x1E00500000ULL)
#define QSPI_BOOT						QSPI_ROT
#define UART0_PERI0_BOOTROM				(0x1FF9040000ULL)

#define BL1_FLASH_OFFSET				(0x1F80004000ULL)
#define BL1_SIZE_MAX					(0xA000)
#define IMAGE_OFFSET					(0x10)
#define BL1_ENTRY_DEST					(0x1FF0010000ULL)
#define BL1_ENTRY						(0x1E00010000ULL)

/* CPMU_PRIVATE */
#define OM_STAT	(0x0)
#define OM_MASK	(0x7)
#define NORMAL_BOOT	(0x5)

/* Chiplet ID(Die ID) */
#define CHIPLET	(0x444)
#define ID_MASK	(0x3)
#if (CHIPLET_COUNT > 1)
#define CHIPLET_ID			(*(uint32_t *)(SYSREG_SYSREMAP_PRIVATE + CHIPLET) & ID_MASK)
#else
#define CHIPLET_ID			0
#endif /* CHIPLET_COUNT */
#define ID0	(0x0)

/* Boot log sfr */
#define BOOT_LOG_ADDR					(CPMU_PRIVATE + 0x980)
#define BOOT_FLAG_ADDR					(CPMU_PRIVATE + 0x984)

/* Boot binary index */
#define BOOT_FBOOT_N					(1)
#define BOOT_SBOOT_N					(2)

/* Boot log */
#define BOOT_CP0_STEP_SIZE				(5)
#define BOOT_ROT_STEP_SIZE				(5)
#define BOOT_CM7_STEP_SIZE				(4)
#define BOOT_CP1_STEP_SIZE				(2)
#define BOOT_CP0_BIN_SIZE				(3)
#define BOOT_ROT_BIN_SIZE				(2)
#define BOOT_CM7_BIN_SIZE				(2)
#define BOOT_CP1_BIN_SIZE				(2)
#define BOOT_RESET_TYPE_SIZE			(5)
#define BOOT_CHIPLET_ID_SIZE			(2)

#define BOOT_CP0_STEP_OFFSET			(0)
#define BOOT_ROT_STEP_OFFSET			(BOOT_CP0_STEP_OFFSET + BOOT_CP0_STEP_SIZE)
#define BOOT_CM7_STEP_OFFSET			(BOOT_ROT_STEP_OFFSET + BOOT_ROT_STEP_SIZE)
#define BOOT_CP1_STEP_OFFSET			(BOOT_CM7_STEP_OFFSET + BOOT_CM7_STEP_SIZE)
#define BOOT_CP0_BIN_OFFSET				(BOOT_CP1_STEP_OFFSET + BOOT_CP1_STEP_SIZE)
#define BOOT_ROT_BIN_OFFSET				(BOOT_CP0_BIN_OFFSET + BOOT_CP0_BIN_SIZE)
#define BOOT_CM7_BIN_OFFSET				(BOOT_ROT_BIN_OFFSET + BOOT_ROT_BIN_SIZE)
#define BOOT_CP1_BIN_OFFSET				(BOOT_CM7_BIN_OFFSET + BOOT_CM7_BIN_SIZE)
#define BOOT_RESET_TYPE_OFFSET			(BOOT_CP1_BIN_OFFSET + BOOT_CP1_BIN_SIZE)
#define BOOT_CHIPLET_ID_OFFSET			(BOOT_RESET_TYPE_OFFSET + BOOT_RESET_TYPE_SIZE)

#define CPMU_RESET_VAL					(*(uint32_t *)(CPMU_PRIVATE + 0x404))
#define FSB(x)							\
	do {								\
		uint32_t i = 0;					\
										\
		while (!((x) & 0x1)) {			\
			i++;						\
			(x) >>= 1;					\
		}								\
		(x) = i;						\
	} while (0)

#define _BOOT_GET_MASK(size, offset)	(~(((1 << (size)) - 1) << (offset)))

#define _BOOT_MASK(cpu)											\
	(_BOOT_GET_MASK(BOOT_##cpu##_SIZE, BOOT_##cpu##_OFFSET))

#define _WAIT_BOOT_FLAG											\
	while (*(volatile uint32_t *)BOOT_FLAG_ADDR)

#define _SET_BOOT_FLAG(val)										\
	(*(volatile uint32_t *)BOOT_FLAG_ADDR) = (val)

#define INIT_BOOT_LOG(chiplet)									\
	(*(volatile uint32_t *)BOOT_LOG_ADDR) = (chiplet) << BOOT_CHIPLET_ID_OFFSET

#define _SET_BOOT_LOG(cpu, bin, n)								\
	do {														\
		uint32_t log = *(volatile uint32_t *)BOOT_LOG_ADDR;	\
																\
		log &= _BOOT_MASK(cpu##_BIN);							\
		log &= _BOOT_MASK(cpu##_STEP);							\
		log |= (n) << (BOOT_##cpu##_STEP_OFFSET);				\
		log |= (BOOT_##bin) << (BOOT_##cpu##_BIN_OFFSET);		\
		(*(volatile uint32_t *)BOOT_LOG_ADDR) = log;			\
	} while (0)

#define BOOT_LOG(cpu, bin, step)								\
	do {														\
		_WAIT_BOOT_FLAG;										\
		_SET_BOOT_FLAG(1);										\
		_SET_BOOT_LOG(cpu, bin, step);							\
		_SET_BOOT_FLAG(0);										\
	} while (0)
