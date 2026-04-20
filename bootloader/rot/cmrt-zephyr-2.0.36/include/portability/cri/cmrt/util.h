#ifndef CRI_CMRT_UTIL_H
#define CRI_CMRT_UTIL_H

/**
 * Execute a CCC (clear container context) operation.
 *
 * Flushes the current security context from HW cores.
 */
void cri_clear_container_context(void);

/**
 * Assert the canary core with static values.
 *
 * Some operations (for example setting permissions) require that the
 * canary core is asserted at least once.
 *
 * @return Zero success, -ERRNO on error.
 */
int cri_assert_canary(void);

#endif
