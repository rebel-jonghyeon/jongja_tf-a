/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_emc

#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/emc.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_EMC_BASE); /* device tree must match headers */

typedef struct cmrt_emc_context {
	/* ddc shall be first element because we don't use contain_of */
	cmrt_dd_context_t ddc;
	uint8_t *buffer;
	size_t buflen;
} cmrt_emc_context_t;

#define EMC_CONTEXTS 1
CMRT_DD_CONTEXT static cmrt_emc_context_t contexts[EMC_CONTEXTS];

static inline uint32_t emc_status(uint32_t *outwords)
{
	uint32_t status = cmrt_core_status(R_BASE);
	*outwords = (status & HWC_STATUS_OUTWORDS_MASK) >>
		HWC_STATUS_OUTWORDS_SHIFT;
	return status & HWC_STATUS_STATUS_MASK;
}

static int emc_poll_cb(cmrt_dd_context_t *ddc)
{
	cmrt_emc_context_t *context = (cmrt_emc_context_t *)ddc;
	uint32_t outwords, status = emc_status(&outwords);
	if (status != EMC_STATUS_AVAILABLE &&
	    status != EMC_STATUS_DATA_AVAILABLE) {
		return -EIO;
	}
	/* Read as much as there is, or as much as we need. */
	uint32_t words = MIN(outwords, ROUND_UP(context->buflen, sizeof(uint32_t)) >> 2);
	uint32_t buffer[EMC_OUTPUT_REGS];
	for (size_t i = 0; i < words; i++) {
		/* Copy full words to a temp buffer. */
		buffer[i] = sys_read32((mm_reg_t)(R_BASE+R_CORE_OUTPUT+i*4u));
	}
	/* Then copy exact number of bytes to caller buffer. */
	size_t bytes = MIN(outwords << 2, context->buflen);
	(void)memcpy(context->buffer, buffer, bytes);
	context->buffer += bytes;
	context->buflen -= bytes;

	return context->buflen == 0 ? 0 : 1;
}

int cmrt_emc_read(cmrt_emc_t context, void *buffer, size_t buflen)
{
	if (!cmrt_dd_valid(context) || buffer == NULL || buflen == 0) {
		return -EINVAL;
	}
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->ddc.sem);
	k_sem_give(&context->ddc.sem);
#endif
	context->buffer = buffer;
	context->buflen = buflen;

	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&context->ddc, 0);
}

static cmrt_dd_t emc_dd = {
	.base = CMRT_EMC_BASE,
	.is_locking = 0,
	.context_count = EMC_CONTEXTS,
	.context_size = sizeof(cmrt_emc_context_t),
	.irq_mask = 0,
	.contexts = contexts,
};

static const struct cmrt_driver_api emc_driver_api = {
	.open_cb = NULL,
	.find_cb = NULL,
	.poll_cb = emc_poll_cb,
	.sync_cb = NULL,
	.close_cb = NULL,
};

DEVICE_DT_INST_DEFINE(0, cmrt_dev_init, NULL, &emc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &emc_driver_api);

cmrt_emc_t cmrt_emc_open(uint32_t flags)
{
	return (cmrt_emc_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, NULL);
}

void cmrt_emc_close(cmrt_emc_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int cmrt_emc_sync(cmrt_emc_t context)
{
	if (!cmrt_dd_valid(context)) {
		return -EINVAL;
	}
	if ((context->ddc.flags & CMRT_O_SYNC) != 0u) {
		/* Already synced internally. */
		return 0;
	}
	return cmrt_dd_sync((cmrt_dd_context_t *)context);
}
