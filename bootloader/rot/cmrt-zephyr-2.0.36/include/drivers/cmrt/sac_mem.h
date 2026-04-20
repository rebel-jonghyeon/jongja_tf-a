/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file sac_mem.h
 *
 * @brief SAC memory definitions.
 */

#ifndef CMRT_SAC_MEM_H
#define CMRT_SAC_MEM_H

/**
 * @brief SAC Memory definitions
 * @defgroup sac_interface SAC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <device.h>

/**
 * SAC memory space is mapped into CMRT address space for the original SAC.
 * The SAC window size is defined in the device tree and it is typically 1GB
 * starting from 0x40000000.
 *
 * The new 64bit SAC2 uses the same CMRT address space, but SAC memory is
 * not mapped. With SAC2 addresses are only logical, with the SAC base address
 * they make 64bit addressing work in 32bit environment. The logical SAC
 * window size is 3GB starting from 0x40000000. This definition does not need
 * to come from the device tree for SAC2.
 */
#if defined(__ZEPHYR__) && defined(CONFIG_CMRT_SAC)
#define SAC_MEMORY_BASE DT_REG_ADDR(DT_NODELABEL(extmem))
#define SAC_MEMORY_SIZE DT_REG_SIZE(DT_NODELABEL(extmem))
#define IS_SAC_SPACE(a, s)			\
	(((uintptr_t)(a) >= SAC_MEMORY_BASE) &&	\
	 ((uintptr_t)(s) <= SAC_MEMORY_SIZE) &&	\
	 ((uintptr_t)(a) + (uintptr_t)(s) - SAC_MEMORY_BASE <= SAC_MEMORY_SIZE))
#else /* For SAC2 and for userspace always */
#define SAC_MEMORY_BASE 0x40000000UL
#define IS_SAC_SPACE(a, s) ((uintptr_t)(a) >= SAC_MEMORY_BASE)
#endif

/**
 * @brief Checks if pointer is valid SAC pointer.
 *
 * @returns true if @p ptr is a SAC pointer.
 */
static inline bool is_sac_ptr(uintptr_t ptr)
{
	return IS_SAC_SPACE(ptr, 0);
}

/**
 * @brief Checks if pointer is valid CMRT pointer.
 *
 * @returns true if @p ptr is a CMRT pointer.
 */
static inline bool is_cmrt_ptr(uintptr_t ptr)
{
	return !IS_SAC_SPACE(ptr, 0);
}

/**
 * @brief Check if address range is within 4GB.
 *
 * @param ptr Start address of the range.
 * @param len Size of the range in bytes.
 */
static inline bool is_in_4gb(uintptr_t ptr, size_t len)
{
	uint32_t value = (uint32_t)ptr;

	return (value + len) >= value;
}

#endif
/** @}*/
