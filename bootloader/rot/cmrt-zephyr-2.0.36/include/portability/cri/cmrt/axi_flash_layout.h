/*
 * Copyright (c) 2020 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file axi_flash_layout.h
 *
 * @brief Define layout of AXI Flash
 */

/*
 * +------------------------------+  --->  0x0
 * |   1MB supervisor image A     |
 * +------------------------------+  --->  0x0010_0000
 * |   1MB supervisor image B     |
 * +------------------------------+  --->  0x0020_0000
 * |   2MB TEEFS                  |
 * +------------------------------+  --->  0x0040_0000
 * |   8KB eOTP                   |
 * +------------------------------+  --->  0x0040_2000
 * |   27MB General Purpose       |
 * +------------------------------+  --->  0x0200_0000
 */

#ifndef CRI_AXI_FLASH_LAYOUT_H
#define CRI_AXI_FLASH_LAYOUT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Erase block size
 */
#define AXI_FLASH_ERASE_SZ 0x1000

/**
 * @brief Base offset
 */
#define AXI_FLASH_BASE 0x0

/**
 * @brief Supervisor image size
 */
#define AXI_FLASH_SPV_SZ 0x100000

/**
 * @brief Supervisor image A base
 */
#define AXI_FLASH_SPV_A AXI_FLASH_BASE

/**
 * @brief Supervisor image B base
 */
#define AXI_FLASH_SPV_B (AXI_FLASH_SPV_A + AXI_FLASH_SPV_SZ)

/**
 * @brief TEEFS size
 */
#define AXI_FLASH_TEEFS_SZ 0x200000

/**
 * @brief TEEFS base
 */
#define AXI_FLASH_TEEFS_BASE (AXI_FLASH_SPV_B + AXI_FLASH_SPV_SZ)

/**
 * @brief eOTP size
 */
#define AXI_FLASH_EOTP_SZ 0x2000

/**
 * @brief General Purpose Flash size
 */
#define AXI_FLASH_GP_SZ (27 * 1024 * 1024)

/**
 * @brief General Purpose Flash base
 */
#define AXI_FLASH_GP_BASE \
	(AXI_FLASH_TEEFS_BASE + AXI_FLASH_TEEFS_SZ + AXI_FLASH_EOTP_SZ)

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
