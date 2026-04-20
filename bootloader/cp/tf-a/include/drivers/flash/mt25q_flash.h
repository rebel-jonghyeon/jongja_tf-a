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

/* MT25QUxxx NOR flash based command */
#define SPI_NOR_CMD_READ				(0x03)  /* Read data */
#define SPI_NOR_CMD_RDID				(0x9F)  /* Read JEDEC ID */
#define SPI_NOR_CMD_RDSR				(0x05)  /* Read status register */
#define SPI_NOR_CMD_WRSR				(0x01)  /* Write status register */
#define SPI_NOR_CMD_RDFSR				(0x70)  /* Read flag status register */
#define SPI_NOR_CMD_MULTI_RDID			(0xAF)
#define SPI_NOR_CMD_ENTER_QUAD			(0x35)  /* Enter QUAD mode */
#define SPI_NOR_CMD_RESET_QUAD			(0xF5)  /* Reset QUAD mode */
#define SPI_NOR_CMD_QIOFR				(0xEB)  /* Quard in/out fast read */
#define SPI_NOR_CMD_READ_FAST			(0x0B)  /* Read data */
#define SPI_NOR_CMD_WRITE_VOL_REG		(0x81)  /* Write volatile register */
#define SPI_NOR_CMD_READ_VOL_REG		(0x85)  /* Read volatile register */
#define SPI_NOR_CMD_READ_ENH_VOL_REG	(0x65)  /* Read enhanced volatile register */
#define SPI_NOR_CMD_WRITE_ENH_VOL_REG	(0x61)  /* Wrtie enhanced volatile register */

#define SPI_NOR_CMD_BULK_ERASE			(0xC7)  /* Bulk erase */
#define SPI_NOR_CMD_SECTOR_ERASE		(0xD8)  /* Sector erase */
#define SPI_NOR_CMD_SUBSECTOR_32K_ERASE	(0x52)  /* Subsector 32K erase */
#define SPI_NOR_CMD_SUBSECTOR_4K_ERASE	(0x20)  /* Subsector 4K erase */

#define SPI_NOR_CMD_PAGE_PROGRAM		(0x02)  /* Page program */
#define SPI_NOR_CMD_QUAD_PROGRAM		(0x32)  /* Quad program */

#define SPI_NOR_CMD_WRITE_ENABLE		(0x06)  /* Write enable */
#define SPI_NOR_CMD_READ_DISC_PARAM		(0x5A)  /* Read discovery param */
#define SPI_NOR_CMD_READ_OTP			(0x4B)  /* Read OTP */
#define SPI_NOR_CMD_WRITE_OTP			(0x42)  /* Write OTP */

#define SPI_NOR_CMD_WRITE_NVCR			(0xB1)  /* Write NVCR */
#define SPI_NOR_CMD_READ_NVCR			(0xB5)  /* Readd NVCR */

#define FLASH_SPI_SINGLE_MODE			(0)
#define FLASH_SPI_DUAL_MODE				(1)
#define FLASH_SPI_QUAD_MODE				(2)

uint32_t erase_flash(uint32_t offset, uint32_t size);
uint32_t read_flash(uint32_t offset, uint32_t *dst, uint32_t size);
uint32_t write_flash(uint32_t offset, void *data, uint32_t size);
