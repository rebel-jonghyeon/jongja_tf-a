/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file dd.h
 *
 * @brief Private APIs for the CMRT device drivers.
 */

#ifndef CMRT_DD_H
#define CMRT_DD_H

#include <stdbool.h>
#include <zephyr/types.h>
#include <device.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sac.h>

#ifdef __cplusplus
extern "C" {
#endif

#define is_aligned(p, n) ((((uintptr_t)(p)) & ((n) - 1u)) == 0u)

/*
 * Specific linker section for device driver contexts.
 * See function is_dd_context for syscall context validation.
 */
#include <linker/linker-defs.h>
#define CMRT_DD_CONTEXT __attribute__((__section__(".cmrt_dd_context")))
#define DD_CONTEXT_START (uintptr_t)&__cmrt_dd_context_start
#define DD_CONTEXT_END (uintptr_t)&__cmrt_dd_context_end

#define HWC_LOCK_PRIV (HWC_LOCK_MAST_PRV_S | HWC_LOCK_MAST_PRV_M)
#define HWC_LOCK_MASTER_CPU ((CORE_ID_CPU << 8) | HWC_LOCK_MAST_PRV_S | HWC_LOCK_MAST_PRV_M)
#define CMRT_DD_WILDCARD 0xFFFFFFFFUL

#ifdef CONFIG_MULTITHREADING
#define K_CURRENT_GET() k_current_get()
#else
#define K_CURRENT_GET() (k_tid_t)(uintptr_t)1
#endif

/*
 * Device context generic part. Device driver specific context
 * structure must follow right after the generic part.
 */
typedef struct cmrt_dd_context {
	struct cmrt_dd *dd;     /**< back pointer to owning device */
	k_tid_t tid;
	struct k_sem sem;       /**< signal/wait port */
	/*
	 * Non-zero, if another HW core has loaded a key into this HW core.
	 * The other HW core transfers HW core lock after loading the key.
	 * Hence when SW opens this core, there is no need to lock it
	 * explicitly. Also the initial state of the HW core is expected to be
	 * IDLE_WITH_KEY rather than AVAILABLE.
	 */
	uint32_t flags;
} cmrt_dd_context_t;

/*
 * Generic device (driver) structure. Driver initializes most fields.
 * Callback functions are being called in cmrt_dd functions.
 */
typedef struct cmrt_dd {
	const struct device *dev; /**< back-pointer for context */
	uint32_t base;
	uint8_t is_locking;
	uint8_t context_count;
	uint16_t context_size;
	uint32_t irq_mask;
	void *contexts;
	/* Caller is expected to initialize all above, but none below. */
#ifdef CONFIG_MULTITHREADING
	struct k_mutex mutex;
	struct k_sem sem; /**< context semaphore */
#endif
} cmrt_dd_t;


/*!
 * Generic CMRT driver API.  These are always cmrt_dd_open,
 * cmrt_dd_close, and cmrt_dd_sync() / NULL.  They are placed into driver_api,
 * even if not directly callable.
 */
__subsystem struct cmrt_driver_api {
	int (*open_cb)(cmrt_dd_context_t *ddc, void *arg);
#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
	void (*open_kat)(cmrt_dd_context_t *ddc);
#endif
	int (*find_cb)(cmrt_dd_context_t *ddc, void *arg);
	int (*poll_cb)(cmrt_dd_context_t *ddc);
	int (*sync_cb)(cmrt_dd_context_t *ddc, uint32_t *mask);
	void (*close_cb)(cmrt_dd_context_t *ddc);
};

/**
 * @brief Syscall verify device driver contexts.
 *
 * @param context Pointer to the context to verify.
 * @param api Pointer to context API functions.
 */
void cmrt_dd_syscall_verify(cmrt_dd_context_t *context, const struct cmrt_driver_api *api);

/**
 * @brief Initialize device driver contexts.
 *
 * Calls close_cb to initialize each context.
 *
 * @param dd CMRT device driver structure pointer.
 * @param dev Zephyr device driver structure pointer.
 */
void cmrt_dd_init(cmrt_dd_t *dd, const struct device *dev);

/**
 * Initializer calling cmrt_dd_init for a CMRT device.
 */
int cmrt_dev_init(const struct device *dev);

/**
 * @brief Open a device driver context.
 *
 * Calls find_cb with arg first to find out if context is already open.
 * Calls find_cb again to make sure it's not reserved for any other thread.
 * Calls open_cb with given arg to reserve and initialize the context.
 *
 * @param dev Pointer to the device.
 * @param flags Flags to callback, @see cmrt_open_flag
 * @param arg Possible argument to the callbacks.
 * @return Pointer to the context semaphore or NULL on failure.
 */
cmrt_dd_context_t *cmrt_dd_open(const struct device *dev, uint32_t flags, void *arg);

/**
 * @brief Return context semaphore handle.
 *
 * @param context One of cmrt_dd_context_t supertypes like cmrt_sic_t.
 * @return Pointer to the semaphore.
 */
static inline struct k_sem *cmrt_dd_sem(void *context)
{
	cmrt_dd_context_t *c = context;

	return &c->sem;
}

/**
 * @brief Close a device driver context.
 *
 * Calls find_cb with arg to find the context.
 * Calls close_cb to reset context to initial values.
 *
 * @param context Pointer to the device.
 */
void cmrt_dd_close(cmrt_dd_context_t *context);

/**
 * @brief Find a device driver context.
 *
 * Calls given find_cb with given arg.
 *
 * @param dd Device driver structure pointer.
 * @param arg Possible argument to open_cb.
 * @param find_cb Callback to call for each context, should return 0
 * @return Pointer to the found context or NULL.
 */
void *cmrt_dd_find_context(cmrt_dd_t *dd, void *arg, int (*find_cb)(cmrt_dd_context_t *ddc, void *arg));

/**
 * @brief Lock device driver context.
 *
 * Locks a mutex to guard against concurrent access.
 * Clears core interrupt mask for cores that have set dd->irq_mask non zero.
 *
 * @param dd Device driver structure pointer.
 * @return Old value of core interrupt mask.
 */
uint32_t cmrt_dd_lock(cmrt_dd_t *dd);

/**
 * @brief Unlock device driver context.
 *
 * Unlocks the mutex that guards against concurrent access.
 * Sets core interrupt mask for cores that have set dd->irq_mask non zero.
 *
 * @param dd Device driver structure pointer.
 * @param mask Value for core interrupt mask.
 */
void cmrt_dd_unlock(cmrt_dd_t *dd, uint32_t mask);

/**
 * @brief Poll for device driver operation.
 *
 * Calls poll_cb to check if context operation is ready.
 * Return value from poll_cb should be:
 *  > 0: continue polling
 * == 0: finished with success
 *  < 0: finished with error
 *
 * @param context context pointer from open
 * @return Zero for ready, positive for busy, -ERRNO otherwise.
 */
int cmrt_dd_poll(cmrt_dd_context_t *context);

/**
 * @brief Synchronize device driver operation.
 *
 * Takes the context semaphore and
 * calls poll_cb to check if context operation is ready.
 * Calls sync_cb for driver specific sync action if poll_cb returned zero.
 *
 * @param context context pointer from open
 * @return poll_cb error or sync_cb return value
 */
int cmrt_dd_sync(cmrt_dd_context_t *context);

/**
 * @brief Call sync automatically
 *
 * Calls cmrt_dd_sync if CMRT_O_SYNC is set for the context.
 * Called from device driver functions that require syncing.
 *
 * @param context context pointer from open
 * @param rv return value from the driver function
 * @return cmrt_dd_sync return value
 */
int cmrt_dd_autosync(cmrt_dd_context_t *context, int rv);

/**
 * @brief Flush device.
 *
 * Issues a flush and potentially re-locks the hardware core without
 * releasing the context.  If the device was originally opened in
 * CMRT_O_HWC_KEYED mode then we don't lock the hardware for the CPU,
 * since in that case the intention is that another core will deliver
 * the key and lock the core.
 *
 * @param context Device context.
 * @return Zero on success, -ERRNO on failure.
 */
int cmrt_dd_flush(cmrt_dd_context_t *context);

/**
 * @brief Return core status.
 *
 * Read and return core status, updates error registers.
 *
 * @param base Core register base.
 * @return Core status register value.
 */
uint32_t cmrt_core_status(uint32_t base);

/**
 * @brief Lock a core for CPU.
 *
 * Low level HW core locking.
 *
 * @param base Core register base.
 * @return 0 or -EFAULT on error.
 */
int cmrt_lock_core(uint32_t base);

/**
 * @brief Check if core is locked.
 *
 * Low level HW core lock check.
 *
 * @param base Core register base.
 * @return True if core is locked.
 */
bool cmrt_is_locked(uint32_t base);

/**
 * @brief Flush a core.
 *
 * Low level HW core flushing.
 *
 * @param base Core register base.
 * @return 0 or -EFAULT on error.
 */
int cmrt_flush_core(uint32_t base);

/**
 * @brief Wait register value change.
 *
 * @param reg Register address.
 * @param value Status value to go out from.
 * @param mask Mask to use.
 * @return The new register value.
 */
int cmrt_wait_reg_from(mm_reg_t reg, uint32_t value, uint32_t mask);

/**
 * @brief Wait status update for a core.
 *
 * @param base Core register base.
 * @param value Status value to go out from.
 * @return The new status value.
 */
int cmrt_wait_status_from(uint32_t base, uint32_t value);

/**
 * @brief Wait status update for a core.
 *
 * @param base Core register base.
 * @param values Status values to wait for.
 * @param num Number of status values.
 * @return index of status in \a values or -EIO
 * @retval -EIO on a hardware error
 */
int cmrt_wait_status_to(uint32_t base, const uint32_t *values, size_t num);

/**
 * @brief Yield CPU.
 *
 *  The CPU yield is performed differently;
 * - a nop for non-multi-threading
 * - k_yield() for Zephyr multi-threading
 */
void cmrt_dd_yield(void);

/**
 * @brief Check context validity.
 *
 * @return True for valid context, false otherwise.
 */
bool cmrt_dd_valid(cmrt_handle_t context);

/**
 * @brief Frees context for all devices based on thread id.
 *
 * @param tid Thread Id to search contexts.
 */
void cmrt_dd_free(k_tid_t tid);

#ifdef CONFIG_CMRT_SAC2
#define cmrt_read32(a) cmrt_sac_read32((uintptr_t)(a))
#define cmrt_write32(d, a) cmrt_sac_write32((d), (uintptr_t)(a))
#define cmrt_memcpy(d, s, n) cmrt_sac_memcpy((void *)(d), (void *)(s), (n))
#else
#define cmrt_read32(a) sys_read32((uintptr_t)(a))
#define cmrt_write32(d, a) sys_write32((d), (uintptr_t)(a))
#define cmrt_memcpy(d, s, n) memcpy((void *)(d), (void *)(s), (n))
#endif

#ifdef __cplusplus
}
#endif

#endif
