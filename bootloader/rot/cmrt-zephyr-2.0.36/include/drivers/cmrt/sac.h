/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file sac.h
 *
 * @brief Public APIs for the SAC driver.
 */

#ifndef CMRT_SAC_H
#define CMRT_SAC_H

/**
 * @brief SAC Interface
 * @defgroup sac_interface SAC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <string.h>
#include <drivers/cmrt/sac_reg.h>
#include <drivers/cmrt/sac_mem.h>
#include <kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __ZEPHYR__
/**
 * @brief Set SAC configuration.
 *
 * Set SAC configuration. Machine mode only.
 *
 * For original SAC with segment registers:
 * @param value Configuration value (bits 31:30: segment, 29:0: size mask).
 * @param index Segment register index (0 to CONFIG_CMRT_SAC_NUM_SEGMENTS - 1).
 * For new 64bit segmentless SAC:
 * @param value Limit SAC address width, write-once until reset.
 * @param index Must be zero.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_sac_set_config(uint32_t value, uint32_t index);

/**
 * @brief Set SAC address base
 *
 * SAC address base must be aligned to 2K boundary.
 *
 * @note remapping will generally invalidate all short (32-bit
 * logical) addresses stored.  This includes all buffers used in
 * asynchronous operations, which must not be in progress when this
 * function is called.
 *
 * @param thread Thread ID or NULL for current.
 * @param base SAC address base.
 * @return Zero on success, -ERRNO on error.
 * @retval -EINVAL either \a thread or \a base is invalid
 */
int cmrt_sac_set_base(k_tid_t thread, uint64_t base);

/**
 * @brief Get SAC address base
 *
 * @param thread Thread ID or NULL for current.
 * @return SAC address base.
 */
uint64_t cmrt_sac_get_base(k_tid_t thread);

/**
 * @brief Translate logical SAC address to real 64bit address.
 *
 * @param addr Logical SAC address
 */
static inline uint64_t cmrt_sac_translate(uintptr_t addr)
{
	uint64_t base = cmrt_sac_get_base(NULL);

	return base + (uint64_t)(addr - SAC_MEMORY_BASE);
}

/**
 * @brief Check SAC access for a thread
 *
 * Application can implement this function to check for thread SAC access.
 * The existing implementation is a stub, CMRT does not provide SAC memory
 * access control.
 *
 * @param thread Thread ID or NULL for current.
 * @param addr SAC address to check.
 * @param size Size of the memory access.
 * @param write True to check for write access.
 * @return true for access allowed, false otherwise
 */
bool cmrt_sac_has_access(const k_tid_t thread, uint64_t addr, size_t size, bool write);

#ifdef CONFIG_CMRT_SAC_CONSOLE
/**
 * @brief Set SAC address base for console logging.
 *
 * SAC address base must be aligned to 2K boundary.
 *
 * @param base SAC console address base.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_sac_set_console_base(uint64_t base);

/**
 * @brief Get SAC address base for console logging.
 *
 * @return SAC console address base.
*/
uint64_t cmrt_sac_get_console_base(void);

/**
 * @brief Copy RAM console buffer to SAC.
 *
 * Buffer will be copied to address pointed by CONFIG_CMRT_SAC_CONSOLE.
 * RAM console buffer size is defined in CONFIG_RAM_CONSOLE_BUFFER_SIZE.
 */
void cmrt_sac_console_copy(void);
#endif
#endif

/**
 * @brief Read a byte from SAC
 *
 * This function makes direct read access to SAC at offset @p addr.
 *
 * CMRT SAC addresses are 64bit. Actual SAC address is formed by adding provided
 * offset with the SAC base for CPU access, @ref cmrt_sac_set_base().
 *
 * The SAC base needs to be set once to define a 3GB window. This function
 * accesses a memory location in this window. The SAC base can be updated if
 * needed.
 *
 * @param addr The lower 32 bits of SAC address, don't need to be word aligned.
 * @return 8bit value at given 64bit address
 */
__syscall uint8_t cmrt_sac_read8(uintptr_t addr);

/**
 * @brief Write a byte to SAC
 *
 * This function makes direct write access to SAC to write @p data at offset
 * @p addr.
 *
 * CMRT SAC2 addresses are 64bit. Actual SAC2 address is formed by adding
 * provided offset with the SAC base for CPU access, @ref cmrt_sac_set_base().
 * The SAC base needs to be set once to define a 3GB window. This function
 * accesses a memory location in this window. The SAC base can be updated if
 * needed.
 *
 * @param addr The lower 32 bits of SAC address, don't need to be word aligned.
 * @param data The 32bit value to write.
 */
__syscall void cmrt_sac_write8(uint8_t data, uintptr_t addr);

/**
 * @brief Read a word from SAC
 *
 * This function makes direct read access to SAC at offset @p addr.
 *
 * CMRT SAC addresses are 64bit. Actual SAC address is formed by adding provided
 * offset with the SAC base for CPU access, @ref cmrt_sac_set_base().
 *
 * The SAC base needs to be set once to define a 3GB window. This function
 * accesses a memory location in this window. The SAC base can be updated if
 * needed.
 *
 * @param addr The lower 32 bits of SAC address, must be word aligned.
 * @return 32bit value at given 64bit address
 */
__syscall uint32_t cmrt_sac_read32(uintptr_t addr);

/**
 * @brief Write a word to SAC
 *
 * This function makes direct write access to SAC to write @p data at offset
 * @p addr.
 *
 * CMRT SAC2 addresses are 64bit. Actual SAC2 address is formed by adding
 * provided offset with the SAC base for CPU access, @ref cmrt_sac_set_base().
 * The SAC base needs to be set once to define a 3GB window. This function
 * accesses a memory location in this window. The SAC base can be updated if
 * needed.
 *
 * @param addr The lower 32 bits of SAC address, must be word aligned.
 * @param data The 32bit value to write.
 */
__syscall void cmrt_sac_write32(uint32_t data, uintptr_t addr);

/**
 * @brief Memory copy in SAC
 *
 * Like standard memcpy but takes care of possible SAC addresses.
 * Note that source and destination must be word aligned, and the last
 * possibly uneven bytes will be copied as a full word.
 *
 * CMRT SAC2 addresses are 64bit. Actual SAC2 address is formed by adding
 * provided offset with the SAC base for CPU access, @ref cmrt_sac_set_base().
 * The SAC base needs to be set once to define a 3GB window. This function
 * accesses a memory location in this window. The SAC base can be updated if
 * needed.
 *
 * @param dst Word aligned destination address.
 * @param src Word aligned source address.
 * @param num Number of bytes to copy.
 * @return pointer to dst
 */
__syscall void *cmrt_sac_memcpy(void *dst, const void *src, size_t num);

/**
 * @brief Read a word from SAC within 2K window
 *
 * Direct read for device drivers.
 * Data will be read directly from the SAC device registers,
 * which have a 2K window starting from thread SAC base.
 *
 * @param addr Offset in the 2K window, must be word aligned.
 * @return 32bit value at given 64bit address
 */
static inline uint32_t cmrt_sac_reg_read32(uintptr_t addr)
{
#ifdef CONFIG_CMRT_SAC2
	uintptr_t offset = addr & ~CPU_ADDR_LO_MASK & ~0x3u;
	return sys_read32((mm_reg_t)(CMRT_SAC_BASE + R_CPU_DATA + offset));
#else
	return cmrt_sac_read32(addr);
#endif
}

/**
 * @brief Write a word to SAC within 2K window
 *
 * Direct write for device drivers.
 * Data will be written directly to the SAC device registers,
 * which have a 2K window starting from thread SAC base.
 *
 * @param addr Offset in the 2K window, must be word aligned.
 * @param data The 32bit value to write.
 */
static inline void cmrt_sac_reg_write32(uint32_t data, uintptr_t addr)
{
#ifdef CONFIG_CMRT_SAC2
	uintptr_t offset = addr & ~CPU_ADDR_LO_MASK & ~0x3u;
	sys_write32(data, (mm_reg_t)(CMRT_SAC_BASE + R_CPU_DATA + offset));
#else
	cmrt_sac_write32(data, addr);
#endif
}

#ifdef __cplusplus
}
#endif

#include <syscalls/sac.h>

#endif
/** @}*/
