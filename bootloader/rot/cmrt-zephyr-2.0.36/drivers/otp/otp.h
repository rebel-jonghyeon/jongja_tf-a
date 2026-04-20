/*
 * Copyright (c) 2021, Samsung Foundry
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_OTP_OTP_H_
#define ZEPHYR_DRIVERS_OTP_OTP_H_

#include <zephyr/types.h>
#include <stddef.h>
#include <sys/types.h>
#include <kernel.h>
#include <device.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Macro Definition
 ******************************************************************************/

#define TIMEOUT_REPEAT_MAX (0x00FFFFFF)

/* OTP_CON_CONTROL (0x0110) */
#define MASK_STANDBYCMD BIT(3)
#define MASK_PROGRAMCMD BIT(2)
#define MASK_READCMD BIT(1)
#define MASK_INITCMD BIT(0)

/* OTP_CON_CONFIG (0x0114) */
#define MASK_SW_PREREADING BIT(13)
#define MASK_RESPONSECON (BIT(11) | BIT(12))
#define MASK_RESPONSECON_NONSEC BIT(11)

/* OTP_IF (0x0118) */
#define MASK_IF_ADDR (0x0000FFFF)
#define MASK_IF_PROGRAMDATA BIT(31)
#define BIT_LOC_IF_PROGRAMDATA (31)

/* OTP_INT_STATUS (0x011C) */
#define MASK_PREREADINGDONE BIT(8)
#define SERIALIZE_DONE BIT(7)
#define MASK_PROGRAMLOCK BIT(6)
#define MASK_SECUREFAIL BIT(5)
#define MASK_PROGRAMFAIL BIT(4)
#define MASK_STANBY_DONE BIT(3)
#define MASK_PROGRAMDONE BIT(2)
#define MASK_READDONE BIT(1)
#define MASK_INITDONE BIT(0)
#define MASK_PROGRAM_STATUS (0x74)

#define MASK_ADDR_ALIGN (0x3)
#define BANK_SIZE_1024 (1024)
#define SHIFT_BANK_SIZE_1024 (10)
#define SHIFT_BYTE_LEN (2)
#define READ_32 (32)
#define WRITE_32 (32)
#define WORD_SIZE_4 (4)
#define WAIT_MSEC_10 (10)
#define BIT_8 (8)
#define MASK_WRITE_1 (1)
#define SHIFT_BITLEN_5 (5)
#define MASK_BITLEN_32 (0x1F)

#define PRODUCT_ID (0x0000)
#define PRODUCT_VER (0x0020)
#define LOCK0 (0x0100)
#define LOCK1 (0x0104)
#define SECURE_READ_DATA (0x0108)
#define NONSECURE_READ_DATA (0x010C)
#define CON_CONTROL (0x0110)
#define CON_CONFIG (0x0114)
#define IF (0x0118)
#define INT_STATUS (0x011C)
#define INT_EN (0x0120)
#define CON_TIME_PARA_0 (0x0124)
#define CON_TIME_PARA_1 (0x0128)
#define CON_TIME_PARA_2 (0x012C)
#define CON_TIME_PARA_3 (0x0130)
#define CON_TIME_PARA_4 (0x0134)
#define CON_TIME_PARA_5 (0x0138)
#define CON_TIME_PARA_6 (0x013C)
#define CON_TIME_PARA_7 (0x0140)
#define ADD_LOCK (0x0144)
#define LOCK_CUSTOM_0 (0x0148)
#define LOCK_CUSTOM_1 (0x014c)
#define CON_STATUS (0x0150)
#define SECURE_SPARE0 (0x0154)
#define TZPCCON_SPARE0 (0x0158)
#define NON_SECURE_SPARE0 (0x015C)

#define OTP_ECC_CTRL (0x1FF02100C4)
/*******************************************************************************
 * Types Definition
 ******************************************************************************/

enum nonsec_otpc_type {
	NON_SECURE_TYPE = 0,
	SECURE_TYPE,
	HARDWARE_TYPE,
	OTPC_NOT_USED,
};

typedef enum nonsec_otpc_type nonsec_otpc_type_t;

enum nonsec_otpc_operation {
	NONSECOTP_READ,
	NONSECOTP_WRITE,
};

typedef enum nonsec_otpc_operation nonsec_otpc_operation_t;

#define NO_FAIL (0)
#define INIT_FAIL BIT(0)
#define STANDBY_FAIL BIT(1)
#define PROGRAM_FAIL BIT(2)
#define LOCK_PROGRAM_FAIL BIT(3)
#define SECURE_FAIL BIT(4)
#define PROGRAM_LOCK BIT(5)
#define UNACCESSIBLE_REGION BIT(6)
#define TIME_OUT BIT(7)
#define MISALIGNED BIT(8)
#define INVALID_ADDR BIT(9)
#define INVALID_LEN BIT(10)
#define OMC_OPEN_FAIL BIT(11)
#define OMC_EIO_FAIL BIT(12)
#define OMC_READ_FAIL BIT(13)
#define NULL_POINTER BIT(14)
#define PRE_READING_FAIL BIT(15)
#define NO_ADDRESS BIT(16)

typedef struct {
} otpc_nonsec_config;

typedef struct {
	uint32_t	nonsec_otp_bank_type[32];
} otpc_dd_t;

typedef struct {
	uint64_t base;
	uint64_t ecc_parity_base;
	uint64_t ecc_base;
	void (*irq_config_func)(void);
} otp_samsung_device_config;

/* Device data structure */
typedef struct {
	uint32_t ecc_parity_addr_offset;
	uint32_t bank_num;
	uint32_t bank_type[64];
	uint32_t parity_bank_type[64];
} otp_samsung_data;

/***************************************************************
 * Exported Functions Prototypes
 ***************************************************************/

typedef uint32_t (*otp_device_info_t)(const struct device *dev);

typedef uint32_t (*otp_product_id_t)(const struct device *dev, uint32_t *id);

typedef uint32_t (*otp_read_32_t)(const struct device *dev,
								   uint32_t bit_addr,
								   uint32_t *data_32,
								   size_t byte_len);

typedef uint32_t (*otp_read_32_parity_t)(const struct device *dev,
										 uint32_t bit_addr,
										 uint32_t *data_32,
										 size_t byte_len);

typedef uint32_t (*otp_read_32_ecc_t)(const struct device *dev,
									  uint32_t bit_addr,
									  uint32_t *data_32,
									  size_t byte_len);

typedef uint32_t (*otp_read_32_omc_t)(const struct device *dev,
									  uint32_t offset,
									  uint32_t *data_32,
									  size_t byte_len);

typedef uint32_t (*otp_read_chipid)(const struct device *dev, uint32_t *data);

typedef uint32_t (*otp_write_t)(const struct device *dev,
								uint32_t addr,
								uint32_t *data,
								uint32_t ecc_enable,
								size_t bit_len);

__subsystem struct otp_driver_api {
	otp_device_info_t device_info;
	otp_product_id_t product_id;
	otp_read_32_t read_32;
	otp_read_32_parity_t read_32_parity;
	otp_read_32_ecc_t read_32_ecc;
	otp_read_32_omc_t read_32_omc;
	otp_write_t write;
};

__syscall uint32_t samsung_otpc_device_info(const struct device *dev);

static inline uint32_t z_impl_samsung_otpc_device_info(const struct device *dev)
{
	const struct  otp_driver_api *api =
	(const struct otp_driver_api *)dev->api;

	__ASSERT(api->device_info, "Callback pointer should not be NULL");
	return api->device_info(dev);
}

__syscall uint32_t samsung_otpc_product_id(const struct device *dev, uint32_t *id);

static inline uint32_t z_impl_samsung_otpc_product_id(const struct device *dev,
													  uint32_t *id)
{
	const struct  otp_driver_api *api =
	(const struct otp_driver_api *)dev->api;

	__ASSERT(api->product_id, "Callback pointer should not be NULL");
	return api->product_id(dev, id);
}

__syscall uint32_t samsung_otpc_read_32(const struct device *dev,
										uint32_t bit_addr,
										uint32_t *data_32,
										size_t byte_len);

static inline uint32_t z_impl_samsung_otpc_read_32(const struct device *dev,
												   uint32_t bit_addr,
												   uint32_t *data_32,
												   size_t byte_len)
{
	const struct  otp_driver_api *api =
		(const struct otp_driver_api *)dev->api;

	__ASSERT(api->read_32, "Callback pointer should not be NULL");
	return api->read_32(dev, bit_addr, data_32, byte_len);
}

__syscall uint32_t samsung_otpc_read_32_ecc(const struct device *dev,
											uint32_t bit_addr,
											uint32_t *data_32,
											size_t byte_len);

static inline uint32_t z_impl_samsung_otpc_read_32_ecc(const struct device *dev,
													   uint32_t bit_addr,
													   uint32_t *data_32,
													   size_t byte_len)
{
	const struct  otp_driver_api *api =
		(const struct otp_driver_api *)dev->api;

	__ASSERT(api->read_32_ecc, "Callback pointer should not be NULL");
	return api->read_32_ecc(dev, bit_addr, data_32, byte_len);
}

__syscall uint32_t samsung_otpc_read_32_omc(const struct device *dev,
											uint32_t offset,
											uint32_t *data_32,
											size_t byte_len);

static inline uint32_t z_impl_samsung_otpc_read_32_omc(const struct device *dev,
													   uint32_t offset,
													   uint32_t *data_32,
													   size_t byte_len)
{
	const struct  otp_driver_api *api =
		(const struct otp_driver_api *)dev->api;

	__ASSERT(api->read_32_ecc, "Callback pointer should not be NULL");
	return api->read_32_ecc(dev, offset, data_32, byte_len);
}

__syscall uint32_t samsung_otpc_write(const struct device *dev,
									  uint32_t addr,
									  uint32_t *data,
									  uint32_t ecc_enable,
									  size_t bit_len);

static inline uint32_t z_impl_samsung_otpc_write(const struct device *dev,
												 uint32_t addr,
												 uint32_t *data,
												 uint32_t ecc_enable,
												 size_t bit_len)
{
	const struct  otp_driver_api *api =
	(const struct otp_driver_api *)dev->api;

	__ASSERT(api->write, "Callback pointer should not be NULL");
	return api->write(dev, addr, data, ecc_enable, bit_len);
}

#ifdef __cplusplus
}
#endif

#include <syscalls/otp.h>

#endif
