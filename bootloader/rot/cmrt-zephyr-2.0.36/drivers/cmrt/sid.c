/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <device.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/sid.h>
#include <drivers/cmrt/sic.h>

typedef struct cmrt_sid_context {
	/* ddc shall be first element because we don't use contain_of */
	cmrt_dd_context_t ddc;

	/* IRQs reserved by this context. */
	uint32_t reserved;

	/* IRQs state, enabled IRQs are monitored, shared with ISR. */
	uint32_t enabled;

	/* Pending IRQs, shared with ISR. */
	uint32_t pending;

	/* Pointer to caller result. */
	uint32_t *irqs;
} cmrt_sid_context_t;

#define SID_CONTEXTS 2
CMRT_DD_CONTEXT static cmrt_sid_context_t contexts[SID_CONTEXTS];

static uint32_t free_irqs = CMRT_SOC_INTERRUPT_IN_MASK;

static void sid_irq_handler(const void *arg)
{
	uint32_t irq = 1u << (uint32_t)arg;
	for (int i = 0; i < SID_CONTEXTS; i++) {
		if (contexts[i].enabled & irq) {
			/* Record IRQs status and signal thread. */
			contexts[i].pending |= irq;
#ifdef CONFIG_MULTITHREADING
			k_sem_give(&contexts[i].ddc.sem);
#endif
			/* Change state of triggered IRQs to unmonitored. */
			contexts[i].enabled &= ~irq;
		}
	}
	irq_disable(CMRT_SOC_IRQ((uint32_t)arg));
}

static void sid_close_cb(cmrt_dd_context_t *ddc)
{
	cmrt_sid_context_t *context = (cmrt_sid_context_t *)ddc;
	/* Free IRQs and reset context. */
	free_irqs |= context->reserved;
	while (context->enabled != 0) {
		uint32_t irq = find_msb_set(context->enabled) - 1u;
		irq_disable(CMRT_SOC_IRQ(irq));
		context->enabled &= ~(1u << irq);
	}
	context->reserved = context->pending = 0;
	context->irqs = NULL;
}

static int sid_open_cb(cmrt_dd_context_t *ddc, void *args)
{
	/* Fail if an invalid IRQ is requested */
	uint32_t irqs = (uint32_t)args;
	/* Coverity uses incorrect value for CMRT_SOC_INTERRUPT_IN_MASK. */
	/* coverity[DEADCODE] */
	if ((irqs & ~CMRT_SOC_INTERRUPT_IN_MASK) != 0) {
		return -EINVAL;
	}
	/* Fail if any requested IRQ is busy */
	cmrt_sid_context_t *context = (cmrt_sid_context_t *)ddc;
	if ((free_irqs & irqs) != irqs) {
		return -EBUSY;
	}
	/* Reserve IRQs */
	free_irqs &= ~irqs;
	context->reserved = irqs;
	/* Connect to SID handler. */
	while (irqs != 0) {
		uint32_t irq = find_msb_set(irqs) - 1u;
		irq_connect_dynamic(CMRT_SOC_IRQ(irq), 0, sid_irq_handler, (void *)irq, 0);
		irqs &= ~(1u << irq);
	}
	return 0;
}

int z_impl_cmrt_sid_watch(cmrt_sid_t context, uint32_t watch, uint32_t *irqs)
{
	if (!cmrt_dd_valid(context) || (watch & ~context->reserved) != 0) {
		return -EINVAL; /* unreserved IRQ bits specified */
	}
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	/* Update state of only selected IRQs. */
	context->enabled = watch;
	context->irqs = irqs;
	while (watch != 0) {
		uint32_t irq = find_msb_set(watch) - 1u;
		irq_enable(CMRT_SOC_IRQ(irq));
		watch &= ~(1u << irq);
	}
#ifdef CONFIG_MULTITHREADING
	/* Reset the poll semaphore. */
	(void)k_sem_reset(cmrt_dd_sem(context));
#endif
	cmrt_dd_unlock(dd, mask);

	return cmrt_dd_autosync(&context->ddc, 0);
}

static int sid_poll_cb(cmrt_dd_context_t *ddc)
{
	cmrt_sid_context_t *context = (cmrt_sid_context_t *)ddc;
	return (context->pending != 0) ? 0 : 1;
}

static int sid_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	ARG_UNUSED(mask);

	cmrt_sid_context_t *context = (cmrt_sid_context_t *)ddc;
	if (context->irqs != NULL) {
		*context->irqs = context->pending;
	}
	context->pending = 0;
	return 0;
}

static int cmrt_sid_init(const struct device *dev)
{
	cmrt_dd_t *dd = dev->data;
	cmrt_dd_init(dd, dev);
	return 0;
}

static cmrt_dd_t sid_dd = {
	.base = 0,
	.is_locking = 0,
	.context_count = SID_CONTEXTS,
	.context_size = sizeof(cmrt_sid_context_t),
	.irq_mask = 0,
	.contexts = contexts,
};

static const struct cmrt_driver_api sid_driver_api = {
	.open_cb = sid_open_cb,
	.find_cb = NULL,
	.poll_cb = sid_poll_cb,
	.sync_cb = sid_sync_cb,
	.close_cb = sid_close_cb,
};

DEVICE_DEFINE(sid, "sid", cmrt_sid_init, NULL, &sid_dd, NULL,
	      POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
	      (void *)&sid_driver_api);

cmrt_sid_t z_impl_cmrt_sid_open(uint32_t flags, uint32_t irqs)
{
	return (cmrt_sid_t)cmrt_dd_open(DEVICE_GET(sid), flags, (void *)irqs);
}

void z_impl_cmrt_sid_close(cmrt_sid_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_sid_sync(cmrt_sid_t context)
{
	if (!cmrt_dd_valid(context)) {
		return -EINVAL;
	}
	if (context->ddc.flags & CMRT_O_SYNC) {
		/* Already synced internally. */
		return 0;
	}
	return cmrt_dd_sync((cmrt_dd_context_t *)context);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_sid_context(cmrt_sid_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &sid_driver_api);
}

static inline cmrt_sid_t z_vrfy_cmrt_sid_open(uint32_t flags, uint32_t irqs)
{
	return z_impl_cmrt_sid_open(flags, irqs);
}
#include <syscalls/cmrt_sid_open_mrsh.c>

static inline void z_vrfy_cmrt_sid_close(cmrt_sid_t context)
{
	z_syscall_verify_sid_context(context);
	z_impl_cmrt_sid_close(context);
}
#include <syscalls/cmrt_sid_close_mrsh.c>

static inline int z_vrfy_cmrt_sid_watch(cmrt_sid_t context, uint32_t watch, uint32_t *irqs)
{
	z_syscall_verify_sid_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(irqs, sizeof(*irqs)));
	return z_impl_cmrt_sid_watch(context, watch, irqs);
}
#include <syscalls/cmrt_sid_watch_mrsh.c>

static inline int z_vrfy_cmrt_sid_sync(cmrt_sid_t context)
{
	z_syscall_verify_sid_context(context);
	return z_impl_cmrt_sid_sync(context);
}
#include <syscalls/cmrt_sid_sync_mrsh.c>

#endif /* CONFIG_USERSPACE */
