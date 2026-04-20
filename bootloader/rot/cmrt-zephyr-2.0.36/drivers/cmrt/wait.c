/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <kernel.h>
#include <device.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/dd.h>

enum { CMRT_MAX_WAIT_HANDLES = 8 };

int z_impl_cmrt_wait(unsigned int n, cmrt_handle_t const *handles, int timeout)
{
	if (n > CMRT_MAX_WAIT_HANDLES) {
		return -EINVAL;
	}
	if (n == 0) {
		if (timeout >= 0) {
#ifdef CONFIG_MULTITHREADING
			(void)k_sleep(K_MSEC(timeout));
#else
			k_busy_wait(1000 * timeout);
#endif
			return 0;
		}
		return -EINVAL;
	}
	if (handles == NULL) {
		return -EINVAL;
	}
#ifdef CONFIG_MULTITHREADING
	int ret = -EINVAL;
	struct k_poll_event events[CMRT_MAX_WAIT_HANDLES] = { 0 };

	for (unsigned int i = 0; i < n; ++i) {
		cmrt_handle_t h = handles[i];
		/* NULL handles are supported by k_poll. */
		uint32_t type = cmrt_is_valid(h) ?
			K_POLL_TYPE_SEM_AVAILABLE : K_POLL_TYPE_IGNORE;
		void *obj = cmrt_is_valid(h) ? cmrt_dd_sem(h) : NULL;
		k_poll_event_init(&events[i], type,
				  K_POLL_MODE_NOTIFY_ONLY, obj);
		if (type != K_POLL_TYPE_IGNORE) {
			/* Must have at least one valid handle. */
			ret = 0;
		}
	}
	if (ret < 0) {
		return ret;
	}
	ret = k_poll(events, (int)n, timeout < 0 ? K_FOREVER : K_MSEC(timeout));
	if (ret >= 0) { /* success, get list of ready descriptors */
		unsigned int ready = 0;
		for (unsigned int i = 0; i < n; ++i) {
			if (events[i].state == K_POLL_STATE_SEM_AVAILABLE) {
				ready |= 1u << i;
			}
		}
		ret = (int)ready;
	}
#else
	int ret = -EAGAIN;
	do {
		for (int t = 0; t < 100; t++) {
			unsigned int ready = 0;
			for (unsigned int i = 0; i < n; ++i) {
				cmrt_handle_t h = handles[i];
				/* NULL handles are supported here, too. */
				if (h != NULL && cmrt_dd_poll(h) == 0) {
					ready |= 1u << i;
				}
			}
			if (ready != 0 || timeout == 0) {
				return (int)ready;
			}
			k_busy_wait(10); /* 100 * 10us = 1ms */
		}
		if (timeout > 0) {
			timeout--;
		}
	} while (timeout != 0);
#endif
	return (ret == -EAGAIN) ? 0 : ret;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline int z_vrfy_cmrt_wait(unsigned int n, cmrt_handle_t const *handles, int timeout)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(handles, sizeof(cmrt_handle_t) * n));
	for (int i = 0; i < n; i++) {
		cmrt_dd_context_t *ddc = (cmrt_dd_context_t *)handles[i];
		cmrt_dd_syscall_verify(ddc, ddc->dd->dev->api);
	}
	return z_impl_cmrt_wait(n, handles, timeout);
}
#include <syscalls/cmrt_wait_mrsh.c>

#endif /* CONFIG_USERSPACE */
