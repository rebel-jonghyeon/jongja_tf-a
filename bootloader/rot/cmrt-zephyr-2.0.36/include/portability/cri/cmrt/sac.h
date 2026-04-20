/*
 * Copyright (c) 2017-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file sac.h
 *
 * @brief Public APIs for the SAC driver.
 */

#ifndef CRI_SAC_H
#define CRI_SAC_H

/**
 * @brief SAC Interface
 * @defgroup sac_interface SAC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <sac_reg.h>
#include <omc_reg.h>
#include <sac_mem.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set SAC segment configuration.
 *
 * Set SAC segment configuration.
 *
 * @param value Configuration value (bits 31:30: segment, 29:0: size mask).
 * @param index Segment register index (0 to CONFIG_CRI_SAC_NUM_SEGMENTS - 1).
 * @return Zero on success, -ERRNO on error.
 */
int cri_sac_segment_config(uint32_t value, uint32_t index);

/**
 * @brief Flush SAC to get back to idle state.
 *
 * Flush SAC to get back to idle state.
 *
 * @return Zero on success, -ERRNO on error.
 */
int cri_sac_request_flush(void);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
