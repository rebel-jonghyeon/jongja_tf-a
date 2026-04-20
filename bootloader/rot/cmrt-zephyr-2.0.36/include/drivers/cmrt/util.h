/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_UTIL_H
#define CMRT_UTIL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <drivers/cmrt/tmc.h>
#include <drivers/cmrt/omc.h>

#define cmrt_set_perso_status(status) cmrt_write_reg(CMRT_SIC_BASE, R_SCRATCH_0, (status))

/**
 * Execute a CCC (clear container context) operation.
 *
 * Flushes the current security context from HW cores.
 */
void cmrt_clear_container_context(void);

/**
 * Assert the canary core with static values.
 *
 * Some operations (for example setting permissions) require that the
 * canary core is asserted at least once.
 *
 * @return Zero success, -ERRNO on error.
 */
int cmrt_assert_canary(void);

/**
 * Go into debug mode for JTAG
 *
 * Sets the debug mode for JTAG connection. Note that caller must have
 * asserted the canary core and set FMC permission for the first internal
 * slot. In image footer that is "write_feature_block": [ 0 ].
 *
 * Going to debug mode is a one way street. Key derivations and other
 * security critical operations yield different results after debug mode
 * has been set.
 *
 * SIC SCRATCH_0 register can be used by the HLOS to synchronize entering
 * debug mode. After setting debug mode this function will busy-wait until
 * SCRATCH_0 register has the required value.
 *
 * @param scratch Value to wait in scratch register or zero for no wait.
 * @return Zero success, -ERRNO on error.
 */
int cmrt_debug_mode(uint32_t scratch);

/**
 * Input output vector.
 */
struct iov {
	void *p;        /**! Pointer to buffer */
	size_t n;       /**! Size of the buffer */
};

/**
 * Get high quality random data from TMC in IO vectors.
 *
 * @param v Array of struct @ref iov.
 * @param nv Number of elements in array @p v.
 */
int cmrt_get_randomv(const struct iov *v, size_t nv);

/**
 * Get high quality random data from TMC.
 *
 * @param buf Buffer for the output.
 * @param len Requested number of bytes.
 */
__syscall int cmrt_get_random(void *buf, size_t len);

/**
 * Get entropy from EMC in IO vectors.
 *
 * Entropy is lower quality random data. Use cmrt_get_randomv() if in doubt.
 *
 * @param v Array of struct @ref iov.
 * @param nv Number of elements in array @p v.
 */
int cmrt_get_entropyv(const struct iov *v, size_t nv);

/**
 * Get entropy from EMC.
 *
 * Entropy is lower quality random data. Use cmrt_get_random() if in doubt.
 *
 * @param buf Buffer for the output.
 * @param len Requested number of bytes.
 */
__syscall int cmrt_get_entropy(void *buf, size_t len);

/**
 * Set lifecycle to OTP.
 *
 * @param value Lifecycle value.
 * @return Zero on success, ERRNO on error.
 */
int cmrt_set_lifecycle(uint32_t value);

/**
 * Burn DGOK.
 *
 * @return Zero on success, ERRNO on error.
 */
int cmrt_burn_dgok(void);

/**
 * Initialize OEC version.
 *
 * If OEC version is 0 then it is changed to 1, otherwise do nothing.
 *
 * @return Zero on success, ERRNO on error.
 */
int cmrt_init_oec_version(void);

/**
 * Get start offset for the application OTP area.
 * Application area starts right after the (possible) sboot image.
 *
 * @param omc Already opened OMC handle, it will not be closed.
 * @return Offset to the start of application OTP area, or zero in error.
 */
uint32_t cmrt_otp_app_start(cmrt_omc_t omc);

/**
 * Get timer counter reference value for performance measurement.
 *
 * @return 64bit counter value
 */
__syscall uint64_t cmrt_perf_ref(void);

/**
 * Get number of passed cycles for performance measurement.
 *
 * @return 64bit counter value
 */
static inline uint64_t cmrt_perf_cycles(uint64_t ref)
{
	return cmrt_perf_ref() - ref;
}

/**
 * Get system uptime in ms since boot up.
 * Zephyr has similar functions, but not as a syscall.
 *
 * @return 64bit uptime in ms
 */
__syscall uint64_t cmrt_uptime_get(void);

/**
 * Busy wait for a small number of CPU cycles.
 *
 * Should be used to wait for few cycles within device drivers
 * due to HW requirements. Use k_busy_wait() for longer waiting.
 * Preferably, don't use busy waiting at all.
 *
 * @param cycles Number of CPU cycles to wait.
 */
void cmrt_wait_cycles(uint32_t cycles);

/**
 * Read default TMC initialization configuration from SIC.
 * The resulting structure can be given to cmrt_tmc_open with CMRT_O_TMC_INIT.
 *
 * @param params Pointer to the result.
 */
__syscall void cmrt_init_tmc_config(cmrt_tmc_init_params_t *params);

/**
 * Access bits.  The bits define the access level as a combination of bits.
 */
enum BufferAccessBit {
	CMRT_ACCESS_NONE = 0,  /**< empty place holder */
	CMRT_ACCESS_READ = 1,	/**< buffer is fully readable */
	CMRT_ACCESS_WRITE = 2,	/**< buffer is fully writable */
	CMRT_ACCESS_PRIVATE = 4, /**< private buffer, not part is shared */
	CMRT_ACCESS_INTERNAL = 8 /**< private memory area (SRAM) */
};

/**
 * Verify buffer access for current thread.  The buffer can be
 * - private/exclusive, or shared
 * - readable or writable
 * SRAM buffers only can ever be private. No other thread with the same
 * privilege (i.e. user thread) has access to it either.  External addresses
 * will always result in shared access.
 *
 * The full buffer must have access.  The return value is a combination of
 * bits in.
 * @param flags tested flags, which can be used to test for a subset of all access
 * @param pbuf buffer to test
 * @param nbuf size of pbuf in bytes
 * @return access flags; all are tested, return may include bits not in \a flags but is guaranteed to test all inside
 */
__syscall uint32_t cmrt_access(uint32_t flags, const void *pbuf, size_t nbuf);


/**
 * Exit active container.  The function can only be called from within an
 * active user thread.
 *
 * @param exit_value informal exit value
 */
__syscall void cmrt_exit_container(int exit_value);


#include <syscalls/util.h>

#endif
