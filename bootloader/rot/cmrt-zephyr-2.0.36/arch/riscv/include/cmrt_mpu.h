/*
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_MPU_H
#define CMRT_MPU_H

#include <stdint.h>
#include <drivers/cmrt/mpu_reg.h>

/**
 * @brief Make an MPU region and return it.
 *
 * @param address End address for the region.
 * @param privilege Privilege for the region, e.g. MPU_PRIVILEGE_M.
 * @param bits Mode and other attributes for the region, e.g. MPU_MODE_WRITABLE.
 *
 * @return Encoded MPU region.
 */
inline uint32_t cmrt_mpu_encode_region(uint32_t address, uint32_t privilege, uint32_t bits)
{
    return address >> 2 | privilege | bits;
}

#define CMRT_MPU_ADDRESS(r) (((r) & MPU_ADDRESS_MASK) << 2)
#define CMRT_MPU_BITS(r) ((r) & MPU_BITS_MASK)
#define CMRT_MPU_PRIVILEGE(r) ((r) & MPU_PRIVILEGE_MASK)

/**
 * @brief Read MPU region from the HW.
 *
 * @param index Region index.
 * @return Encoded MPU region.
 */
uint32_t cmrt_mpu_read_region(int index);

/**
 * @brief Write MPU region to the HW.
 *
 * @param index Region index.
 * @param region Encoded MPU region.
 */
void cmrt_mpu_write_region(int index, uint32_t region);

/**
 * @brief Write MPU regions to the HW.
 *
 * Read MPU regions from the HW starting from the given index.
 * Regions are read up to the end with possible zero padding.
 *
 * @param index Region index.
 * @param regions Pointer to the region array.
 */
void cmrt_mpu_read_regions(int index, uint32_t regions[CONFIG_CMRT_MPU_NUM_REGIONS]);

/**
 * @brief Write MPU regions to the HW.
 *
 * Write MPU regions to the HW starting from the given index.
 * Regions are written up to the end with possible zero padding.
 *
 * @param index Region index.
 * @param regions Pointer to the region array.
 */
void cmrt_mpu_write_regions(int index, const uint32_t regions[CONFIG_CMRT_MPU_NUM_REGIONS]);

/**
 * @brief Return first user MPU region index.
 *
 * @return First user MPU region index.
 */
int cmrt_mpu_first_user(void);

/**
 * @brief Return first free MPU region index.
 *
 * @return First free MPU region index.
 */
int cmrt_mpu_first_free(void);

/**
 * @brief Check if there is access to given address with given parameters.
 *
 * Check if there is access to given address with given parameters.
 *
 * @param address Start address to check.
 * @param size End address to check.
 * @param privilege Privilege for the region.
 * @param bits Mode and other attributes for the region.
 * @return true for access OK or false for no access.
 */
bool cmrt_mpu_has_access(uint32_t address, uint32_t size, uint32_t privilege, uint32_t bits);

#endif
