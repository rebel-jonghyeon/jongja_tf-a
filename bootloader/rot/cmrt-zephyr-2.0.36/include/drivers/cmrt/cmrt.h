/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file cmrt.h
 *
 * @brief Public APIs for the CMRT device drivers.
 */

#ifndef CMRT_CMRT_H
#define CMRT_CMRT_H

#include <stddef.h>
#include <stdbool.h>
#include <drivers/cmrt/hwc_reg.h>

#ifdef __ZEPHYR__
#include <toolchain.h>
/*
 * To define version information for CMRT builds:
 * static const char fboot_version[] __version = FBOOT_VERSION_INFO;
 */
#define __version __used Z_GENERIC_SECTION("version.1")
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Check context validity after open.
 *
 * @param context One of cmrt_dd_context_t supertypes like cmrt_sic_t.
 * @return true for valid context
 */
typedef void *cmrt_handle_t;

static inline bool cmrt_is_valid(cmrt_handle_t context)
{
	/* Native mode context is pointer.*/
	return context != NULL;
}

#define CMRT_INVALID_HANDLE ((cmrt_handle_t)NULL)

/*!
 * Timeout argument value for an infinite wait.
 */
#define CMRT_FOREVER (-1)

/**
 * @brief Wait on a set of contexts.
 *
 * The wait will return on either any of the contexts becoming ready,
 * or timeout elapsing.
 *
 * @param[in] n Number of handles to check.
 * @param[in] handles Array of handles of length \a numfds. All must be valid.
 * @param[in] timeout Timeout in milliseconds, CMRT_FOREVER for infinite.
 * @return Bitset of ready fds by index in \a fds, zero for timeout, and
 * -ERRNO on failure.
 */
__syscall int cmrt_wait(unsigned int n, cmrt_handle_t const *handles, int timeout);

/**
 * @defgroup CMRT_OPEN_FLAGS Device driver open flags
 * @brief Flags to cmrt_device_open(), for instance, cmrt_aes_open().
 * @{
 */

/**
 * @defgroup CMRT_O_PUBLIC_FLAGS Device driver public flags
 * @brief Device driver public flags
 * @ingroup CMRT_OPEN_FLAGS
 * @{
 */

#define CMRT_O_COMMON_MASK       0x0000FFFFUL

/**
 * Set to make the device driver operations synchronous. Typically there's
 * no need to call cmrt_device_sync() explicitly when this option is set.
 */
#define CMRT_O_SYNC      0x1UL

/**
 * Set to make all device driver operations asynchronous. At the moment this
 * only applies to cmrt_sic_open() and setting this flag means the application
 * needs to call cmrt_sic_sync() also after cmrt_sic_write().
 */
#define CMRT_O_ASYNC     0x2UL

/**
 * Indicates that another HWC will directly initialize and load key into the
 * HWC of this device. If specified, device driver only reserves device driver
 * context and does not itself take the HWC lock.
 */
#define CMRT_O_HWC_KEYED 0x4UL

/**
 * Executes KAT tests unconditionally
 */
#define CMRT_O_HWC_FORCE_KAT 0x8UL

/**
 * Don't execute KAT tests on open.
 */
#define CMRT_O_HWC_SKIP_KAT 0x10UL

/**
 * Don't wait for a free context in device driver open. This applies for
 * multithreaded mode where open will normally block until there's a context
 * available.
 */
#define CMRT_O_NO_WAIT 0x20UL

/**
 * Feed the low level watchdog when sync() is running. For some devices,
 * like SIC2, sync() may take a long time. In single threaded mode fboot
 * should use this flag when waiting for a perso container.
 */
#define CMRT_O_FEED_WDT 0x80L
/** @}*/

/**
 * @brief Device driver private flags
 * @defgroup CMRT_O_PRIVATE_FLAGS Device driver private flags
 * @ingroup CMRT_OPEN_FLAGS
 * @{
 */

#define CMRT_OP_MASK             0xFFFF0000UL
#define CMRT_OP_SHIFT            16

/**
 * When using emulated OTP, @ref CMRT_O_OTP_COMMIT flag can be specified to
 * @ref cmrt_omc_open. OMC driver then reserves HC and AES contexts.
 * @ref cmrt_omc_close /@ref cmrt_omc_close then auto commits OTP contents and
 * releases HC and AES contexts.
 * This flag has no effect if CONFIG_CMRT_OMC_EMULATED_OTP is not set.
 */
#define CMRT_O_OTP_COMMIT       (0x1UL << CMRT_OP_SHIFT)

/**
 * Request HSAES Linear AES-GCM operation mode.
 * Default mode is Bidirectional AES-GCM.
 */
#define CMRT_O_HSAES_LINEAR     (0x1UL << CMRT_OP_SHIFT)

/**
 * When opening TMC for the first time it instantiates unless this flag is set.
 */
#define CMRT_O_TMC_INSTANTIATED (0x1UL << CMRT_OP_SHIFT)

/**
 * Request TMC open to use in subsequent KDC operation.
 * At the moment, this is used in DGOK generation.
 */
#define CMRT_O_TMC_KDC          (0x2UL << CMRT_OP_SHIFT)
/** @}*/
/** @}*/

#ifdef __ZEPHYR__
#include <arch/common/sys_io.h>
/**
 * @brief Read HW core register.
 *
 * Allowed for all registers, HW takes care of access control.
 *
 * @param base Register base.
 * @param reg Register id.
 * @return Current value.
 */
static inline uint32_t cmrt_read_reg(uint32_t base, uint32_t reg)
{
	return sys_read32(base + reg);
}

/**
 * @brief Write HW core register.
 *
 * Allowed for all registers, HW takes care of access control.
 *
 * @param base Register base.
 * @param reg Register id.
 * @param value New value.
 */
static inline void cmrt_write_reg(uint32_t base, uint32_t reg, uint32_t value)
{
	sys_write32(value, base + reg);
}

/**
 * @brief Set boot status register.
 *
 * Boot status register R_SW_BOOT_STATUS is used to set the running
 * boot phase and other information. See values in sic_reg.h.
 *
 * @param bits Bits to set.
 * @param mask Affected bits.
 */
void cmrt_set_boot_status(uint32_t bits, uint32_t mask);
#endif

#ifdef __cplusplus
}
#endif

#include <syscalls/cmrt.h>

#endif
