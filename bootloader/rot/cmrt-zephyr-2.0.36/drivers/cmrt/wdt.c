/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/wdt.h>
#include <drivers/watchdog.h>
#include <task_wdt/task_wdt.h>
#include <string.h>
#include <errno.h>

typedef struct cmrt_wdt_context {
	cmrt_dd_context_t ddc;
	int task_wdt_id;
} cmrt_wdt_context_t;

#define WDT_CONTEXTS CONFIG_TASK_WDT_CHANNELS
CMRT_DD_CONTEXT static cmrt_wdt_context_t contexts[WDT_CONTEXTS];

static void task_wdt_cb(int channel_id, void *user_data)
{
	/*
	 * Typically this would be the place to call task_wdt_feed or
	 * halt/reboot. We signal the thread instead to do the feeding
	 * and rely on the HW watchdog to fire if that does not happen.
	 */
	cmrt_wdt_context_t *context = (cmrt_wdt_context_t *)user_data;
	k_sem_give(&context->ddc.sem);
}

static int wdt_open_cb(cmrt_dd_context_t *ddc, void *args)
{
	cmrt_wdt_context_t *context = (cmrt_wdt_context_t *)ddc;
	uint32_t period = (uint32_t)args;
	if (period < CONFIG_TASK_WDT_MIN_TIMEOUT) {
		period = CONFIG_TASK_WDT_MIN_TIMEOUT;
	}
	context->task_wdt_id = task_wdt_add(period, task_wdt_cb, context);
	return context->task_wdt_id < 0 ? context->task_wdt_id : 0;
}

static void wdt_close_cb(cmrt_dd_context_t *ddc)
{
	cmrt_wdt_context_t *context = (cmrt_wdt_context_t *)ddc;
	task_wdt_delete(context->task_wdt_id);
}

static int cmrt_wdt_init(const struct device *dev)
{
	cmrt_dd_t *dd = dev->data;
	cmrt_dd_init(dd, dev);
	/* Backup SW watchdog with HW. */
	const struct device *hw_wdt = DEVICE_DT_GET(DT_ALIAS(watchdog0));
	/* Feed once at bootup. */
	wdt_feed(hw_wdt, 0);
	return task_wdt_init(hw_wdt);
}

static cmrt_dd_t wdt_dd = {
	.base = 0,
	.is_locking = 0,
	.context_count = WDT_CONTEXTS,
	.context_size = sizeof(cmrt_wdt_context_t),
	.irq_mask = 0,
	.contexts = contexts,
};

static const struct cmrt_driver_api wdt_driver_api = {
	.open_cb = wdt_open_cb,
	.find_cb = NULL,
	.poll_cb = NULL,
	.sync_cb = NULL,
	.close_cb = wdt_close_cb,
};

DEVICE_DEFINE(wdt, "wdt",
	      cmrt_wdt_init, NULL, &wdt_dd, NULL,
	      POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
	      &wdt_driver_api);

cmrt_wdt_t z_impl_cmrt_wdt_open(uint32_t flags, uint32_t period)
{
	return (cmrt_wdt_t)cmrt_dd_open(DEVICE_GET(wdt), flags, (void *)period);
}

void z_impl_cmrt_wdt_close(cmrt_wdt_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_wdt_sync(cmrt_wdt_t context)
{
	if (!cmrt_dd_valid(context)) {
		return -EINVAL;
	}
	return cmrt_dd_sync((cmrt_dd_context_t *)context);
}

int z_impl_cmrt_wdt_feed(cmrt_wdt_t context)
{
	if (!cmrt_dd_valid(context)) {
		return -EINVAL;
	}
	/* Skip context locking and unlocking here. */
	return task_wdt_feed(context->task_wdt_id);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_wdt_context(cmrt_wdt_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &wdt_driver_api);
}

static inline cmrt_wdt_t z_vrfy_cmrt_wdt_open(uint32_t flags, uint32_t period)
{
	return z_impl_cmrt_wdt_open(flags, period);
}
#include <syscalls/cmrt_wdt_open_mrsh.c>

static inline void z_vrfy_cmrt_wdt_close(cmrt_wdt_t context)
{
	z_syscall_verify_wdt_context(context);
	z_impl_cmrt_wdt_close(context);
}
#include <syscalls/cmrt_wdt_close_mrsh.c>

static inline int z_vrfy_cmrt_wdt_sync(cmrt_wdt_t context)
{
	z_syscall_verify_wdt_context(context);
	return z_impl_cmrt_wdt_sync(context);
}
#include <syscalls/cmrt_wdt_sync_mrsh.c>

static inline int z_vrfy_cmrt_wdt_feed(cmrt_wdt_t context)
{
	z_syscall_verify_wdt_context(context);
	return z_impl_cmrt_wdt_feed(context);
}
#include <syscalls/cmrt_wdt_feed_mrsh.c>

#endif /* CONFIG_USERSPACE */
