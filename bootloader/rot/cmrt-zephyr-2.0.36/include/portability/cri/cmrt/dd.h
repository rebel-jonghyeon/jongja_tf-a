/*
 * Copyright (c) 2017-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file cmrt_dd.h
 *
 * @brief Private APIs for the CMRT device drivers.
 */

#ifndef CRI_CMRT_DD_H
#define CRI_CMRT_DD_H

#include <stdbool.h>
#include <zephyr/types.h>
#include <device.h>
#include <cri/cmrt.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Use this attribute for functions that need to be compiled in even
 * though they are not used directly in fboot. Let's use existing
 * TEXT section in include/arch/riscv32/common/linker.ld for now.
 */
#ifdef CONFIG_CRI_FBOOT
#define __keep __attribute__((__section__(".openocd_debug")))
#else
#define __keep
#endif

#define HWC_LOCK_PRIV (HWC_LOCK_MAST_PRV_S | HWC_LOCK_MAST_PRV_M)
#define HWC_LOCK_MASTER_CPU ((CORE_ID_CPU << 8) | HWC_LOCK_MAST_PRV_S | HWC_LOCK_MAST_PRV_M)
#define CMRT_DD_WILDCARD 0xFFFFFFFFUL

/*
 * Device context generic part. Device driver specific context
 * structure must follow right after the generic part.
 */
typedef struct cmrt_dd_context {
	struct cmrt_dd *dd; /**< back pointer to owning device */
	k_tid_t tid;
	struct k_sem sem; /**< signal/wait port */
	/*
	 * Non-zero, if another HW core has loaded a key into this HW core.
	 * The other HW core transfers HW core lock after loading the key.
	 * Hence when SW opens this core, there is no need to lock it
	 * explicitly. Also the initial state of the HW core is expected to be
	 * IDLE_WITH_KEY rather than AVAILABLE.
	 */
	u32_t flags;
} cmrt_dd_context_t;

/*
 * Generic device (driver) structure. Driver initializes most fields.
 * Callback functions are being called in cmrt_dd functions.
 */
typedef struct cmrt_dd {
	struct device *dev; /**< back-pointer for context */
	u8_t core_id;
	u8_t is_locking;
	u8_t context_count;
	u16_t context_size;
	u16_t irq_mask;
	void *contexts;
	/* Caller is expected to initialize all above, but none below. */
#ifdef CONFIG_MULTITHREADING
	struct k_mutex mutex;
	struct k_sem sem; /**< context semaphore */
#endif
	u32_t offset;
} cmrt_dd_t;


/*!
 * Generic CMRT driver API.  These are always cmrt_dd_open,
 * cmrt_dd_close, and cmrt_dd_sync() / NULL.  They are placed into driver_api,
 * even if not directly callable.
 */
struct cmrt_driver_api {
	int (*open_cb)(cmrt_dd_context_t *ddc, void *arg);
	int (*find_cb)(cmrt_dd_context_t *ddc, void *arg);
	int (*poll_cb)(cmrt_dd_context_t *ddc);
	int (*sync_cb)(cmrt_dd_context_t *ddc, u32_t *mask);
	void (*close_cb)(cmrt_dd_context_t *ddc);
};

/**
 * @brief Initialize device driver contexts.
 *
 * Calls close_cb to initialize each context.
 *
 * @param dd Device driver structure pointer.
 */
void cmrt_dd_init(cmrt_dd_t *dd, struct device *dev);

/**
 * @brief Open a device driver context.
 *
 * Calls find_cb with arg first to find out if context is already open.
 * Calls find_cb again to make sure it's not reserved for any other thread.
 * Calls open_cb with given arg to reserve and initialize the context.
 *
 * @param dev Pointer to the device.
 * @param flags Flags to callback, @see cri_open_flag
 * @param arg Possible argument to the callbacks.
 * @return Pointer to the context semaphore or NULL on failure.
 */
cmrt_dd_context_t *cmrt_dd_open_flags(struct device *dev, u32_t flags, void *arg);

/**
 * @brief Open a device driver context.
 *
 * Calls find_cb with arg first to find out if context is already open.
 * Calls find_cb again to make sure it's not reserved for any other thread.
 * Calls open_cb with given arg to reserve and initialize the context.
 *
 * @param dev Pointer to the device.
 * @param arg Possible argument to the callbacks.
 * @return Pointer to the context semaphore or NULL on failure.
 */
static inline cmrt_dd_context_t *cmrt_dd_open(struct device *dev, void *arg)
{
	return cmrt_dd_open_flags(dev, 0, arg);
}

/**
 * @brief Return context semaphore handle.
 *
 * @param context One of cmrt_dd_context_t supertypes like cri_sic_t.
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
 * @param dev Pointer to the device.
 * @param tid Thread id or zero for current thread.
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
u32_t cmrt_dd_lock(cmrt_dd_t *dd);

/**
 * @brief Unlock device driver context.
 *
 * Unlocks the mutex that guards against concurrent access.
 * Sets core interrupt mask for cores that have set dd->irq_mask non zero.
 *
 * @param dd Device driver structure pointer.
 * @param mask Value for core interrupt mask.
 */
void cmrt_dd_unlock(cmrt_dd_t *dd, u32_t mask);

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
 * Calls cmrt_dd_sync if CRI_O_SYNC is set for the context.
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
 * CRI_O_HWC_KEYED mode then we don't lock the hardware for the CPU,
 * since in that case the intention is that another core will deliver
 * the key and lock the core.
 *
 * @param context Device context.
 * @return Zero on success, -ERRNO on failure.
 */
int cmrt_dd_flush(cmrt_dd_context_t *context);

/**
 * @brief Lock a core for CPU.
 *
 * Blocks until core is locked in supervisor mode, does not block in
 * machine mode.
 *
 * @param core_id ID of the core to lock
 * @return 0 or -EFAULT on error.
 */
int cri_cmrt_lock_core(u32_t core_id);

/**
 * @brief Wait status update for a core.
 *
 * @param reg Status register address
 * @param from Status value to go out from
 * @return New status or -EBUSY on error.
 */
int cri_wait_status_from(u32_t reg, u32_t from);

/**
 * @brief Wait status update for a core with custom retry count.
 *
 * @param reg Status register address
 * @param from Status value to go out from
 * @param retries Number of status read retries till it times out
 * @return New status or -EBUSY on error.
 */
int cri_wait_status_from_retry(u32_t reg, u32_t from, int retries);

/**
 * @brief Wait status update for a core.
 *
 * @param reg Status register address
 * @param to Status value to go out from
 * @param timeout Number of rounds to wait for.
 * @return Zero on success or -EIO on error or -EBUSY on timeout.
 */
int cri_wait_status_to(u32_t reg, u32_t to, int timeout);

/**
 * @brief Wait status update for a core with multiple values.
 * @param reg Status register address
 * @param mask Used status mask
 * @param to Status values to go out from
 * @param to_size Number of statuses values
 * @param timeout Number of rounds to wait for.
 * @return Current status or -EBUSY on timeout.
 */

int wait_status_to_any_of(mm_reg_t reg, u32_t mask, const u32_t to[],
			  unsigned to_size, int timeout);


/**
 * @brief Read HW core register.
 *
 * Allowed for all registers, HW takes care of access control.
 *
 * @param base Register base.
 * @param reg Register id.
 * @return Current value.
 */
static inline uint32_t cri_read_reg(uint32_t base, uint32_t reg)
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
static inline void cri_write_reg(uint32_t base, uint32_t reg, uint32_t value)
{
	sys_write32(value, base + reg);
}


/*!
 * Yield CPU.  The CPU yield is performed differently;
 * - a nop for non-multi-threading
 * - k_yield() for Zephyr multi-threading
 */
static inline void cri_dd_yield(void)
{
#ifdef CONFIG_MULTITHREADING
	if (k_is_preempt_thread()) {
		k_yield();
	}
#else
	arch_nop();
#endif
}

#ifdef __cplusplus
}
#endif

#endif
