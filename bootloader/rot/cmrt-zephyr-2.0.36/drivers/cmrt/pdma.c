/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_pdma

#include <device.h>
#include <string.h>
#include <assert.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/sac_reg.h>
#include <drivers/cmrt/hs_aes_reg.h>
#include <drivers/cmrt/pdma.h>
#include <drivers/cmrt/pdma_reg.h>
#include <drivers/cmrt/dcm_reg.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define LOG_PDMA LOG_DBG
#define LOG_HEXDUMP_PDMA LOG_HEXDUMP_DBG

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_PDMA_BASE); /* device tree must match headers */
#define CMRT_PDMA_IRQ DT_INST_IRQN(0)

#define PDMA_STATUS_NOK_MASK ((PDMA_STATUS_STOPPED | PDMA_STATUS_ERROR) & ~PDMA_STATUS_BUSY)

typedef struct cmrt_pdma_context {
	/* ddc shall be first element because we don't use container_of */
	cmrt_dd_context_t ddc;
	uint32_t channel;
	uint32_t key_bank;
	uint32_t desc_count; /* No. of descriptors (desc.), current and queued. */
	uint32_t nr_failed;
} cmrt_pdma_context_t;

#define PDMA_NR_CONTEXTS (CMRT_HSAES_NR_CHANNELS * CMRT_HSAES_NR_KEY_BANKS)
static cmrt_pdma_context_t contexts[PDMA_NR_CONTEXTS];

#define MAX_NR_DESC (CMRT_PDMA_DESC_BRAM_SIZE / sizeof(cmrt_pdma_desc_t))

/* Maximum value of desc. slot "pointer", for current mode. */
#define MAX_P (MAX_NR_DESC - 1)
static struct {
	uint32_t ep;
	uint32_t queue_count;     /* No. of descriptors (desc) in BRAM. */
	uint8_t ref_count;        /* No. open contexts. */
	uint8_t s2c[MAX_NR_DESC]; /* Desc. slot no. (in BRAM) to index into "contexts". */
	uint64_t ch_ref_count[2];

} pdma;

static_assert(PDMA_NR_CONTEXTS <  (1 << (8*sizeof(pdma.ref_count)))-1,
	      "Number of PDMA context do not fit in pdma.ref_count.");
static_assert(CMRT_HSAES_NR_CHANNELS < (8*sizeof(pdma.ch_ref_count)),
	      "pdma.ch_ref_count can not accommodate all channels.");

static inline uint32_t pdma_status(void)
{
	return cmrt_core_status(R_BASE) & HWC_STATUS_STATUS_MASK;
}

static inline bool pdma_queue_full(void)
{
	return pdma.queue_count > MAX_P;
}

static uint32_t pdma_run_next_desc(void)
{
	/* Shift EP to run next queued desc. */
	uint32_t p = pdma.ep + 1;
	if (p > MAX_P) { p = 0; }
	sys_write32(p, R_BASE+R_PDMA_EP);
	pdma.ep = p;
	return p;
}

static cmrt_pdma_t pdma_last_desc_context(void)
{
	/* Find last desc. s Queue started. lot. */
	uint32_t p = pdma.ep ? pdma.ep - 1 : MAX_P;
	return contexts + pdma.s2c[p];
}

static int pdma_enqueue_desc(cmrt_pdma_t context, cmrt_pdma_desc_t *in)
{
	if ((pdma_status() & PDMA_STATUS_NOK_MASK) != 0) {
		return -EIO; /* Core is not running. */
	}
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	int ret = -EAGAIN;
	if (pdma_queue_full()) {
		goto out; /* No room. */
	}
	/* Find first unused desc. slot. */
	uint32_t p = pdma.ep + pdma.queue_count;
	p -= pdma.queue_count ? 1 : 0;
	if (p > MAX_P) { p -= MAX_P + 1; }
	/* Copy desc. to slot. */
	cmrt_pdma_desc_t *desc = (void *)(R_BASE+R_PDMA_DESC_BRAM);
	desc[p] = *in;

	/* Update book keeping. */
	pdma.s2c[p] = context - contexts;
	pdma.queue_count++;
	context->desc_count++;
	LOG_PDMA("desc queued at %d\n", p);

#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->ddc.sem);
#endif
	if (pdma.queue_count == 1) {
		pdma_run_next_desc();
		LOG_PDMA("enqueue_desc started queue.\n");
	}
	ret = 0;
out:
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&context->ddc, ret);
}

static bool pdma_handle_desc_done(void)
{
	if (pdma_status() != PDMA_STATUS_IDLE) {
		return false;
	}
	/* Core has processed all descs. */
	cmrt_pdma_t context = pdma_last_desc_context();
	if (context->desc_count) {
		context->desc_count--;
#ifdef CONFIG_MULTITHREADING
		if (context->desc_count == 0) {
			/* This context has no more descs. queued; wake up its owner thread. */
			k_sem_give(&context->ddc.sem);
		}
#endif
		/* Run next desc. if one or more are queued. */
		pdma.queue_count -= pdma.queue_count ? 1 : 0;
		if (pdma.queue_count) {
			pdma_run_next_desc();
			return true; /* Queue started. */
		}
	}
	return false;
}

#ifdef CONFIG_MULTITHREADING
static void pdma_irq_handler(void *arg)
{
	ARG_UNUSED(arg);

	LOG_PDMA("interrupt: 0x%0x\n", sys_read32(R_BASE+R_PDMA_INTERRUPT));
	LOG_PDMA("mask: 0x%0x\n", sys_read32(R_BASE+R_PDMA_INTERRUPT_MASK));
	LOG_PDMA("status: 0x%0x\n", sys_read32(R_BASE+R_PDMA_STATUS));
	LOG_PDMA("control: 0x%0x\n", sys_read32(R_BASE+R_PDMA_CONTROL));
	LOG_PDMA("SP: 0x%0x\n", sys_read32(R_BASE+R_PDMA_SP));
	LOG_PDMA("EP: 0x%0x\n", sys_read32(R_BASE+R_PDMA_EP));
	LOG_PDMA("Q count: %d\n", pdma.queue_count);

	/* Get and clear interrupt. */
	uint32_t interrupt = sys_read32(R_BASE+R_PDMA_INTERRUPT);
	sys_write32(interrupt, R_BASE+R_PDMA_INTERRUPT);

	if (interrupt) {
		if (interrupt & PDMA_INTERRUPT_DONE) {
			if (pdma_handle_desc_done()) {
				LOG_PDMA("isr started queue\n");
			}
		} else {
			/* Error, wake owner thread of current desc. */
			cmrt_pdma_t context = pdma_last_desc_context();
			context->nr_failed = context->desc_count;
			pdma.queue_count -= context->desc_count;
			context->desc_count = 0;
			k_sem_give(&context->ddc.sem);
		}
	}
}
#endif

static int pdma_poll_cb(cmrt_dd_context_t *ddc)
{
	cmrt_pdma_t context = (void *)ddc;

#ifndef CONFIG_MULTITHREADING
	if (pdma_handle_desc_done()) {
		LOG_PDMA("poll_cb started queue\n");
	}
#endif
	static uint32_t count;
	if (count++ == 0 || count % 100000 == 0) {
		LOG_PDMA("count %d\n", count);
		LOG_PDMA("interrupt: 0x%0x\n", sys_read32(R_BASE+R_PDMA_INTERRUPT));
		LOG_PDMA("mask: 0x%0x\n", sys_read32(R_BASE+R_PDMA_INTERRUPT_MASK));
		LOG_PDMA("status: 0x%0x\n", sys_read32(R_BASE+R_PDMA_STATUS));
		LOG_PDMA("control: 0x%0x\n", sys_read32(R_BASE+R_PDMA_CONTROL));
		LOG_PDMA("SP: 0x%0x\n", sys_read32(R_BASE+R_PDMA_SP));
		LOG_PDMA("EP: 0x%0x\n", sys_read32(R_BASE+R_PDMA_EP));
		LOG_PDMA("Q count: %d\n", pdma.queue_count);
	}
	/*
	 * A context can have multiple desc. queued, we have to wait for all
	 * of its descs. to complete, as long as core is not stuck.
	 */
	return ((pdma_status() & PDMA_STATUS_NOK_MASK) != 0 ||
		!context->desc_count) ? 0 : 1;
}

static int pdma_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	ARG_UNUSED(mask);

	if ((pdma_status() & PDMA_STATUS_NOK_MASK) != 0) {
		/*
		 * Core is stuck. We have to retire all queued descs.
		 * Visit all queued descs., mark them failed and unblock their
		 * owner threads.
		 */
		uint32_t p = pdma.ep ? pdma.ep - 1 : MAX_P;
		while (pdma.queue_count) {
			/* Find owner context of this desc. */
			cmrt_pdma_t context = contexts + pdma.s2c[p];
			if (++p > MAX_P) { p = 0; }
			if (context->desc_count == 0) { continue; }
			context->nr_failed++;
			context->desc_count--;
#ifdef CONFIG_MULTITHREADING
			if (context->desc_count == 0) {
				/*
				 * It is the last desc. of this context, now
				 * unblock the thread that waits on it.
				 */
				k_sem_give(&context->ddc.sem);
			}
#endif
			pdma.queue_count--;
		}
	}
	cmrt_pdma_t context = (void *)ddc;
	return context->nr_failed;
}

int cmrt_pdma_abort(cmrt_pdma_t context)
{
	sys_write32(PDMA_CONTROL_ABORT, R_BASE+R_PDMA_CONTROL);
	uint32_t status = PDMA_STATUS_STOPPED;
	int ret = cmrt_wait_status_to(R_BASE+R_PDMA_STATUS, &status, 1);
	return ret ? -EIO : 0;
}

static int pdma_change_channel_ref_count(uint32_t channel, int change)
{
	const uint8_t ch_ref_mask = 3;
	/*
	 * Locate channel reference count, which is a two bit value. 64 channel
	 * ref counts are packed into two 64bit variables.
	 */
	uint64_t *ch_ref = pdma.ch_ref_count;
	uint8_t shift = channel * 2;
	if (channel >= (CMRT_HSAES_NR_CHANNELS >> 1)) {
		ch_ref++;
		shift -= 64;
	}
	int32_t count = (*ch_ref >> shift) & ch_ref_mask;

	/* A channel can be used by up to two contexts. */
	count += change;
	if (count < 0 || count > 2) {
		return 1;
	}
	/* Update channel reference count. */
	*ch_ref &= ~(((uint64_t)ch_ref_mask) << shift);
	*ch_ref |= ((uint64_t)count) << shift;
	return 0;
}

static int pdma_open_cb(cmrt_dd_context_t *ddc, void *arg)
{
	uint32_t channel = (uint32_t)arg;
	cmrt_pdma_t context = (void *)ddc;

	if (channel >= CMRT_HSAES_NR_CHANNELS) {
		return -EINVAL;
	}
	if (!pdma.ref_count) {
		/* First context to open. */

		/* Flush core */
		sys_write32(PDMA_CONTROL_FLUSH, R_BASE+R_PDMA_CONTROL);
		uint32_t status = PDMA_STATUS_IDLE;
		int ret = cmrt_wait_status_to(R_BASE+R_PDMA_STATUS, &status, 1);
		if (ret) { return ret; } /* stuck core */
		pdma.ep = pdma.queue_count = 0;

		/* Also flush DCM. */
		sys_write32(DCM_CONTROL_FLUSH, CMRT_DCM_BASE+R_DCM_CONTROL);
	}

	uint32_t mask = cmrt_dd_lock(ddc->dd);
	int ret = -EAGAIN;
	if (pdma_change_channel_ref_count(channel, 1) != 0) {
		goto out;
	}
	context->channel = channel;
	context->desc_count = context->nr_failed = 0;

	/* Update count of open contexts. */
	pdma.ref_count++;
	ret = 0;
out:
	cmrt_dd_unlock(ddc->dd, mask);
	return ret;
}

static void pdma_close_cb(cmrt_dd_context_t *ddc)
{
	cmrt_pdma_t context = (void *)ddc;

	/* We can't leave desc. queued, let's abort queue. */
	if (context->desc_count) {
		cmrt_pdma_abort(context);
	}
	(void)pdma_change_channel_ref_count(context->channel, -1);

	/* Update count of open contexts. */
	pdma.ref_count--;
}

static const struct cmrt_driver_api pdma_driver_api = {
	.open_cb = pdma_open_cb,
	.find_cb = NULL,
	.poll_cb = pdma_poll_cb,
	.sync_cb = pdma_sync_cb,
	.close_cb = pdma_close_cb,
};

static cmrt_dd_t pdma_dd = {
	.base = CMRT_PDMA_BASE,
	.is_locking = 0,
	.context_count = PDMA_NR_CONTEXTS,
	.context_size = sizeof(cmrt_pdma_context_t),
#ifdef CONFIG_MULTITHREADING
	.irq_mask = PDMA_INTERRUPT_MASK,
#else
	.irq_mask = 0,
#endif
	.contexts = contexts,
};

static int cmrt_pdma_init(const struct device *dev)
{
	cmrt_dd_t *dd = dev->data;
	pdma.ref_count = PDMA_NR_CONTEXTS;
	cmrt_dd_init(dd, dev);
#ifdef CONFIG_MULTITHREADING
	IRQ_CONNECT(CMRT_PDMA_IRQ, 0, pdma_irq_handler, NULL, 0);
	irq_enable(CMRT_PDMA_IRQ);
#endif
	return 0;
}

DEVICE_DT_INST_DEFINE(0, cmrt_pdma_init, NULL, &pdma_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      (void *)&pdma_driver_api);

cmrt_pdma_t cmrt_pdma_open(uint32_t flags, uint32_t channel, uint32_t key_bank)
{
	if (key_bank > 1) {
		return NULL;
	}
	cmrt_pdma_t context = (cmrt_pdma_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, (void *)channel);
	if (context) {
		context->key_bank = key_bank;
	}
	return context;
}

void cmrt_pdma_close(cmrt_pdma_t context)
{
	cmrt_dd_close((cmrt_dd_context_t *)context);
}

int cmrt_pdma_copy(cmrt_pdma_t context, uint64_t at_addr, uint32_t at_count,
		   uint64_t inbuf, uint64_t outbuf, bool update_at)
{
	/* at_addr must be 256 bits aligned */
	if (at_addr == 0 || (at_addr & 31) != 0 || at_count == 0 ||
	    (at_count * sizeof(cmrt_pdma_at_t)) > CMRT_PDMA_AT_SIZE ||
	    (inbuf == 0 && outbuf == 0) ||
	    (update_at && (inbuf == 0 || outbuf == 0))) {
		return -EINVAL;
	}
	uint8_t type = update_at ? PDMA_DESC_BIDI_AT : PDMA_DESC_BIDI;
	size_t align = CMRT_DCM_DDR_BUFFER_SIZE - 1;
	if (inbuf == 0) {
		type = PDMA_DESC_OUT;
		align = CMRT_PDMA_DATA_WIDTH - 1;
	}
	if (outbuf == 0) {
		type = PDMA_DESC_IN;
		align = CMRT_PDMA_DATA_WIDTH - 1;
	}
	/* In bidirectional mode input/output buffers must align with DDR buffer boundaries. */
	if (!is_aligned((inbuf | outbuf), align)) {
		return -EINVAL;
	}
	cmrt_pdma_desc_t d = (cmrt_pdma_desc_t) {
		 .at_addr =  at_addr,
		 .in_dst_addr = inbuf,
		 .out_src_addr = outbuf,
		 .F2 = PDMA(SET, AT_ROWS, at_count) |
			PDMA(SET, CHANNEL, context->channel) |
			PDMA(SET, KEY_BANK, context->key_bank) |
			PDMA(SET, TYPE, type),
	};
	return pdma_enqueue_desc(context, &d);
}

int cmrt_pdma_sync(cmrt_pdma_t context)
{
	if ((context->ddc.flags & CMRT_O_SYNC) != 0u) {
		/* Already synced internally. */
		return 0;
	}
	return cmrt_dd_sync((cmrt_dd_context_t *)context);
}

void cmrt_pdma_get_channel_context(cmrt_pdma_t context, uint32_t *channel, uint32_t *key_bank)
{
	if (channel) {
		*channel = context->channel;
	}
	if (key_bank) {
		*key_bank = context->key_bank;
	}
}
