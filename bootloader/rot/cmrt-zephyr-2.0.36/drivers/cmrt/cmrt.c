/*
 * Copyright (c) 2017-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file cmrt.c
 * @brief Public APIs for the CMRT board.
 */

#include <string.h>
#include <device.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/eac.h>
#ifdef CONFIG_CMRT_SAC_CONSOLE
#include <drivers/cmrt/sac.h>
#endif
#ifdef CONFIG_SUPERVISOR_MODE
#include <drivers/cmrt/tmc.h>
#endif
#include <sic_reg.h>
#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
#include <omc_reg.h>
#endif

#include <logging/log.h>
LOG_MODULE_REGISTER(cmrt, CONFIG_CMRT_LOG_LEVEL);

void cmrt_set_boot_status(uint32_t bits, uint32_t mask)
{
	uint32_t value = sys_read32((mm_reg_t)(CMRT_SIC_BASE+R_SW_BOOT_STATUS));
	value &= ~mask; value |= bits & mask;
	sys_write32(value, (mm_reg_t)(CMRT_SIC_BASE+R_SW_BOOT_STATUS));
}

uint32_t cmrt_core_status(uint32_t base)
{
	uint32_t status = sys_read32((mm_reg_t)(base + R_CORE_STATUS));
#ifdef CONFIG_CMRT_EAC
	/* Save core id and error information into error register.
	 * This may give some information of what is broken. */
	cmrt_eac_set_core_error(base >> 12, (status & HWC_STATUS_ERROR_MASK) >> 8);
#endif
	return status;
}

int cmrt_lock_core(uint32_t base)
{
	while (true) {
		uint32_t status = cmrt_core_status(base) & HWC_STATUS_STATUS_MASK;
		if (status == HWC_STATUS_AVAILABLE) {
			/* The normal case, lock the core. */
			sys_write32(HWC_LOCK_MASTER_CPU, (mm_reg_t)(base + R_HWC_LOCK_MASTER));
			status = cmrt_core_status(base) & HWC_STATUS_STATUS_MASK;
		}
		if (status == HWC_STATUS_IDLE_LOCKED) {
			/* Got locked, or was already locked. */
			return 0;
		}
		if (status != HWC_STATUS_UNAVAILABLE) {
			/* Core can be unavailable if HW uses it, for example,
			 * right after reset. Just wait for available state.
			 * Any other state is an error. */
#ifdef CONFIG_SUPERVISOR_MODE
			if (base == CMRT_TMC_BASE) {
				/* Allow TMC to be in locked states because
				 * init may have been started in machine. */
				return 0;
			}
#endif
			break;
		}
		cmrt_dd_yield();
	}
	return -EIO;
}

int cmrt_flush_core(uint32_t base)
{
	/* Flushing in busy state will raise a CPU trap. */
	(void)cmrt_wait_status_from(base, HWC_STATUS_BUSY);
	sys_write32(HWC_CONTROL_FLUSH, base + R_CORE_CONTROL);
	/* May need some time to be available after the flush. */
	uint32_t status = HWC_STATUS_AVAILABLE;
	return cmrt_wait_status_to(base, &status, 1);
}

int cmrt_wait_reg_from(mm_reg_t reg, uint32_t value, uint32_t mask)
{
	while (true) {
		uint32_t status = sys_read32(reg) & mask;
		if (status != value) {
			return (int)status;
		}
		cmrt_dd_yield();
	}
	return -EIO; /* not reached */
}

int cmrt_wait_status_from(uint32_t base, uint32_t value)
{
#ifdef CONFIG_CMRT_EAC
	/* Save core id to in case waiting here triggers the watchdog.
	 * This may give some information of what is broken. */
	cmrt_eac_set_core_error(base >> 12, 0);
#endif
	mm_reg_t reg = (mm_reg_t)(base + R_CORE_STATUS);
	return cmrt_wait_reg_from(reg, value, HWC_STATUS_STATUS_MASK);
}

int cmrt_wait_status_to(uint32_t base, const uint32_t *values, size_t num)
{
	while (true) {
		uint32_t status = cmrt_core_status(base) & HWC_STATUS_STATUS_MASK;
		for (unsigned i = 0; i < num; i++) {
			if (status == values[i]) {
				return i;
			}
		}
		if (IS_HWC_ERROR(status)) {
			break;
		}
		cmrt_dd_yield();
	}
	return -EIO;
}

void cmrt_dd_yield(void)
{
#ifdef CONFIG_CMRT_SAC_CONSOLE
	cmrt_sac_console_copy();
#endif
#ifdef CONFIG_MULTITHREADING
	if (k_is_preempt_thread()) {
		k_yield();
	}
#endif
}

bool cmrt_dd_valid(cmrt_handle_t handle)
{
	cmrt_dd_context_t *context = handle;
	return context != NULL && context->tid == K_CURRENT_GET();
}

static inline void *incptr(void *p, size_t n) { return (char *)p + n; }

void cmrt_dd_init(cmrt_dd_t *dd, const struct device *dev)
{
#ifdef CONFIG_MULTITHREADING
	k_sem_init(&dd->sem, dd->context_count, dd->context_count);
	k_mutex_init(&dd->mutex);
#endif
	dd->dev = dev;
	const struct cmrt_driver_api *api = dev->api;
	void *contexts = dd->contexts;
	for (size_t i = 0; i < dd->context_count; i++) {
		cmrt_dd_context_t *context = contexts;
		(void)memset(context, 0, dd->context_size);
		context->dd = dd;
#ifdef CONFIG_MULTITHREADING
		k_sem_init(&context->sem, 0, 1);
#endif
		if (api->close_cb != NULL) {
			api->close_cb(context);
		}
		contexts = incptr(contexts, dd->context_size);
	}
}

int cmrt_dev_init(const struct device *dev)
{
	cmrt_dd_t *dd = dev->data;
	cmrt_dd_init(dd, dev);
	return 0;
}

static inline mm_reg_t dd_reg(const cmrt_dd_t *dd, uint32_t reg)
{
	return (mm_reg_t)(dd->base + reg);
}

bool cmrt_is_locked(uint32_t base)
{
	uint32_t st = cmrt_core_status(base) & HWC_STATUS_STATUS_MASK;
	return (st != HWC_STATUS_AVAILABLE) && (st != HWC_STATUS_UNAVAILABLE);
}

uint32_t cmrt_dd_lock(cmrt_dd_t *dd)
{
	uint32_t mask = dd->irq_mask;
	if (dd->irq_mask != 0u) {
		if (dd->is_locking == 0u || cmrt_is_locked(dd->base)) {
			mask = sys_read32(dd_reg(dd, R_CORE_INTERRUPT_MASK));
			sys_write32(0, dd_reg(dd, R_CORE_INTERRUPT_MASK));
		}
	}
	return mask;
}

static inline uint32_t cmrt_lock_driver(cmrt_dd_t *dd)
{
#ifdef CONFIG_MULTITHREADING
	(void)k_mutex_lock(&dd->mutex, K_FOREVER);
#endif
	return cmrt_dd_lock(dd);
}

void cmrt_dd_unlock(cmrt_dd_t *dd, uint32_t mask)
{
	if (dd->irq_mask != 0u) {
		if (dd->is_locking == 0u || cmrt_is_locked(dd->base)) {
			sys_write32(mask, dd_reg(dd, R_CORE_INTERRUPT_MASK));
		}
	}
}

static inline void cmrt_unlock_driver(cmrt_dd_t *dd, uint32_t mask)
{
	cmrt_dd_unlock(dd, mask);
#ifdef CONFIG_MULTITHREADING
	k_mutex_unlock(&dd->mutex);
#endif
}

void *cmrt_dd_find_context(cmrt_dd_t *dd, void *arg, int (*find_cb)(cmrt_dd_context_t *ddc, void *arg))
{
	void *contexts = dd->contexts;
	for (size_t i = 0; i < dd->context_count; i++) {
		cmrt_dd_context_t *context = contexts;
		if (context->tid != NULL) {
			if (find_cb == NULL || find_cb(context, arg) == 0) {
				return context;
			}
		}
		contexts = incptr(contexts, dd->context_size);
	}
	return NULL;
}

static void cmrt_dd_close_context(cmrt_dd_context_t *context)
{
	context->tid = NULL;
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->sem);
	/* Make context available. */
	cmrt_dd_t *dd = context->dd;
	k_sem_give(&dd->sem);
#endif
}

#ifdef CONFIG_USERSPACE
static void cmrt_dd_free_context(const struct device *dev, k_tid_t tid)
{
	if (dev == NULL) {
		return;
	}

	cmrt_dd_t *dd = dev->data;
	/* Close contexts for given thread. */
	void *contexts = dd->contexts;
	for (size_t i = 0; i < dd->context_count; i++) {
		cmrt_dd_context_t *context = contexts;
		if (context->tid == tid) {
			cmrt_dd_close(context);
		}
		contexts = incptr(contexts, dd->context_size);
	}
}

void cmrt_dd_free(k_tid_t tid)
{
	/* Close thread contexts for all CMRT devices. */
#ifdef CONFIG_CMRT_AES
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(aes)), tid);
#endif
#ifdef CONFIG_CMRT_CC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(cc)), tid);
#endif
#ifdef CONFIG_CMRT_CCP
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(ccp)), tid);
#endif
#ifdef CONFIG_CMRT_DMAC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(dmac)), tid);
#endif
#ifdef CONFIG_CMRT_EMC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(emc)), tid);
#endif
#ifdef CONFIG_CMRT_FMC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(fmc)), tid);
#endif
#ifdef CONFIG_CMRT_HC
	cmrt_dd_free_context(device_get_binding(DT_LABEL(DT_NODELABEL(hc0))), tid);
#endif
#ifdef CONFIG_CMRT_WHC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(whc)), tid);
#endif
#ifdef CONFIG_CMRT_CSHC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(cshc)), tid);
#endif
#ifdef CONFIG_CMRT_HC2
	cmrt_dd_free_context(device_get_binding(DT_LABEL(DT_NODELABEL(hc3))), tid);
#endif
#ifdef CONFIG_CMRT_KDC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(kdc)), tid);
#endif
#ifdef CONFIG_CMRT_KTC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(ktc)), tid);
#endif
#ifdef CONFIG_CMRT_OMC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(omc)), tid);
#endif
#if defined(CONFIG_CMRT_SIC) || defined(CONFIG_CMRT_SIC2)
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(sic)), tid);
#endif
#ifdef CONFIG_CMRT_SID
	cmrt_dd_free_context(device_get_binding("sid"), tid);
#endif
#ifdef CONFIG_CMRT_TMC
	cmrt_dd_free_context(DEVICE_DT_GET(DT_NODELABEL(tmc)), tid);
#endif
#ifdef CONFIG_CMRT_WDT
	cmrt_dd_free_context(device_get_binding("wdt"), tid);
#endif
}
#endif

static cmrt_dd_context_t *cmrt_dd_open_context(cmrt_dd_t *dd)
{
	void *contexts = dd->contexts;
	for (size_t i = 0; i < dd->context_count; i++) {
		cmrt_dd_context_t *context = contexts;
		if (context->tid == NULL) {
			context->tid = K_CURRENT_GET();
			return context;
		}
		contexts = incptr(contexts, dd->context_size);
	}
	return NULL;
}

static inline bool cmrt_dd_wait_context(cmrt_dd_t *dd, bool wait)
{
#ifdef CONFIG_MULTITHREADING
	k_timeout_t timeout = wait ? K_FOREVER : K_NO_WAIT;
	int res = k_sem_take(&dd->sem, timeout);
	if (res == -EBUSY) {
		/* Can happen only with K_NO_WAIT. */
		return false;
	}
	return true;
#else
	ARG_UNUSED(dd);
	ARG_UNUSED(wait);
	return true;
#endif
}

#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
/*
 * Called from cmrt_dd_open_kat() function to determine if the core
 * is in a state where we can safely run KAT.  If CMRT_O_HWC_FORCE_KAT
 * was specified in the open flags then signal errors if KAT cannot
 * be run.
 */
static bool should_run_open_kat(cmrt_dd_context_t *context)
{
	uint32_t flags = context->flags;
	bool is_keyed = (flags & CMRT_O_HWC_KEYED) != 0u;
	bool force_kat = (flags & CMRT_O_HWC_FORCE_KAT) != 0u;
	bool skip_kat = (flags & CMRT_O_HWC_SKIP_KAT) != 0u;
	uint32_t base = context->dd->base;
	uint32_t core_id = base >> 12;

	if (force_kat && skip_kat) {
		skip_kat = false;
	}
	if (skip_kat) {
		return false;
	}
#ifdef CONFIG_CMRT_FIPS_140_MODE
	/* Only run if forced. */
	if (!force_kat) {
		return false;
	}
#endif
	/* Check if the core is in a state where we can run KATs. */
	uint32_t status = cmrt_core_status(base) & HWC_STATUS_STATUS_MASK;
	if (is_keyed) {
		/*
		 * If opened in CMRT_O_HWC_KEYED mode, expect core
		 * status to be AVAILABLE.  If not, return silently,
		 * unless KATs were explicitly requested, in which
		 * case signal an error.
		 */
		if (status != HWC_STATUS_AVAILABLE) {
#ifndef CONFIG_CMRT_FIPS_140_MODE
			if (!force_kat) {
				return false;
			}
#endif
			cmrt_eac_kat_error(core_id, -EXDEV, -EBUSY);
		}
	} else {
		/*
		 * In non-keyed mode the core should be IDLE_LOCKED.
		 * If not, return silently, unless KATs were
		 * explicitly requested.
		 */
		if (status != HWC_STATUS_IDLE_LOCKED) {
#ifndef CONFIG_CMRT_FIPS_140_MODE
			if (!force_kat) {
				return false;
			}
#endif
			cmrt_eac_kat_error(core_id, -EXDEV, -EBUSY);
		}
	}
	/* Otherwise let's run KATs. */
	return true;
}

static void cmrt_dd_open_kat(cmrt_dd_context_t *context)
{
	if (should_run_open_kat(context)) {
		/*
		 * If we are here then the core status is AVAILABLE, so we can
		 * go ahead and run the KATs, almost.  One remaning issue is
		 * if the device was opened in CMRT_O_HWC_KEYED mode, as in
		 * that case the HC driver will not lock the core, and also
		 * cmrt_hc_init() behaves differently.  To be able to run the
		 * tests, we temporarily remove CMRT_O_HWC_KEYED from the flags
		 * and lock the core manually.
		 */
		bool is_keyed = (context->flags & CMRT_O_HWC_KEYED) != 0u;
		uint32_t base = context->dd->base;
		uint32_t core_id = base >> 12;
		if (is_keyed) {
			if (cmrt_lock_core(base) != 0) {
				cmrt_eac_kat_error(core_id, -EXDEV, -EFAULT);
			}
			context->flags &= ~CMRT_O_HWC_KEYED;
		}
		/* Now run the KATs, will halt if it does not pass. */
		const struct cmrt_driver_api *api = context->dd->dev->api;
		api->open_kat(context);
		/* Restore the CMRT_O_HWC_KEYED flag and unlock the core. */
		if (is_keyed) {
			context->flags |= CMRT_O_HWC_KEYED;
			int rc = cmrt_dd_flush(context);
			if (rc != 0) {
				cmrt_eac_kat_error(core_id, -EXDEV, rc);
			}
		}
	}
}
#endif

cmrt_dd_context_t *cmrt_dd_open(const struct device *dev, uint32_t flags, void *arg)
{
	if (dev == NULL) {
		return NULL;
	}
	cmrt_dd_t *dd = dev->data;
	if (!cmrt_dd_wait_context(dd, (flags & CMRT_O_NO_WAIT) == 0u)) {
		/* CMRT_O_NO_WAIT specified but no free contexts. */
		return NULL;
	}
	uint32_t mask = cmrt_lock_driver(dd);
	cmrt_dd_context_t *context = cmrt_dd_open_context(dd);
	if (context == NULL) {
		/* This can happen in single thread mode if caller already
		 * opened all contexts. In multithreaded mode we should have
		 * a free context since we got the semaphore in wait.
		 * Go out here also if only the driver context is claimed. */
		cmrt_unlock_driver(dd, mask);
		return context;
	}
	context->flags = flags;
	if (dd->is_locking == 1u && (flags & CMRT_O_HWC_KEYED) == 0u) {
		if (cmrt_is_locked(dd->base) || cmrt_lock_core(dd->base) < 0) {
			/* Locking failed, bail out. */
			cmrt_unlock_driver(dd, mask);
			cmrt_dd_close_context(context);
			return NULL;
		}
	}
	const struct cmrt_driver_api *api = dev->api;
	if ((api->find_cb != NULL && (cmrt_dd_find_context(dd, arg, api->find_cb) != NULL)) ||
	    (api->open_cb != NULL && api->open_cb(context, arg) != 0)) {
		/* Callbacks failed, bail out. */
		cmrt_unlock_driver(dd, mask);
		cmrt_dd_close(context);
		return NULL;
	}
	cmrt_unlock_driver(dd, mask | dd->irq_mask); /* enable interrupts */
#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
	if (api->open_kat != NULL) {
		cmrt_dd_open_kat(context);
	}
#endif
	return context;
}

void cmrt_dd_close(cmrt_dd_context_t *context)
{
	if (context != NULL) {
		cmrt_dd_t *dd = context->dd;
		uint32_t mask = cmrt_lock_driver(dd);
		const struct cmrt_driver_api *api = dd->dev->api;
		if ((api != NULL) && (api->close_cb != NULL)) {
			api->close_cb(context);
		}
		cmrt_dd_close_context(context);
		if (dd->is_locking == 1u && cmrt_is_locked(dd->base)) {
			(void)cmrt_flush_core(dd->base);
		}
		cmrt_unlock_driver(dd, mask);
	}
}

int cmrt_dd_flush(cmrt_dd_context_t *context)
{
	int ret = 0;
	if (context != NULL) {
		cmrt_dd_t *dd = context->dd;
		uint32_t mask = cmrt_dd_lock(dd);
		if (dd->is_locking == 1u) {
			if (cmrt_is_locked(dd->base)) {
				ret = cmrt_flush_core(dd->base);
			}
			if ((context->flags & CMRT_O_HWC_KEYED) == 0u) {
				ret = cmrt_lock_core(dd->base);
			}
		}
		cmrt_dd_unlock(dd, mask);
	}
	return ret;
}

int cmrt_dd_poll(cmrt_dd_context_t *context)
{
#ifdef CONFIG_WDT_CMRT
	extern int wdt_cmrt_feed(const struct device *dev, int channel_id);
	if ((context->flags & CMRT_O_FEED_WDT) != 0) {
	    (void)wdt_cmrt_feed(NULL, 0);
	}
#endif
	int rv = 0;
	cmrt_dd_t *dd = context->dd;
	const struct cmrt_driver_api *api = dd->dev->api;
	if (api->poll_cb != NULL) {
		uint32_t mask = cmrt_dd_lock(dd);
		rv = api->poll_cb(context);
		cmrt_dd_unlock(dd, mask);
	}
	return rv;
}

int cmrt_dd_sync(cmrt_dd_context_t *context)
{
#ifdef CONFIG_MULTITHREADING
	/* Note that k_sem_take can return -EAGAIN. Not sure if the semaphore
	 * is ready then but calling k_sem_take again will block indefinitely.
	 * Don't care about the return value, in the worst case we will just
	 * do some busy polling below in cmrt_dd_poll. */
	(void)k_sem_take(&context->sem, K_FOREVER);
#endif
	int rv = 0;
	while ((rv = cmrt_dd_poll(context)) > 0) {
		cmrt_dd_yield();
	}
	if (rv == 0) {
		cmrt_dd_t *dd = context->dd;
		const struct cmrt_driver_api *api = dd->dev->api;
		if (api->sync_cb != NULL) {
			uint32_t mask = cmrt_dd_lock(dd);
			rv = api->sync_cb(context, &mask);
			cmrt_dd_unlock(dd, mask);
		}
	}
	return rv;
}

int cmrt_dd_autosync(cmrt_dd_context_t *context, int rv)
{
	if ((context != NULL) && ((context->flags & CMRT_O_SYNC) != 0u) && (rv == 0)) {
		rv = cmrt_dd_sync(context);
	}
	return rv;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>
void cmrt_dd_syscall_verify(cmrt_dd_context_t *context, const struct cmrt_driver_api *api)
{
	/* Make sure the context is within context memory. */
	Z_OOPS(Z_SYSCALL_VERIFY((uintptr_t)context >= DD_CONTEXT_START &&
				(uintptr_t)context < DD_CONTEXT_END));
	/* Make sure context API matches the driver API. */
	Z_OOPS(Z_SYSCALL_VERIFY(context->dd->dev->api == api));
	/* The context must be owned by the calling thread. */
	Z_OOPS(Z_SYSCALL_VERIFY(context->tid == k_current_get()));
}
#endif
