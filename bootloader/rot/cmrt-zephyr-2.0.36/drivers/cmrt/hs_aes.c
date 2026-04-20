/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_hs_aes

#include <device.h>
#include <string.h>
#include <assert.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/sac_reg.h>
#include <drivers/cmrt/hs_aes.h>
#include <drivers/cmrt/hs_aes_reg.h>
#include <drivers/cmrt/pdma_reg.h>
#include <drivers/cmrt/dcm_reg.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define LOG_HSAES LOG_DBG
#define LOG_HEXDUMP_HSAES LOG_HEXDUMP_DBG

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_HSAES_BASE); /* device tree must match headers */
#define CMRT_HSAES_IRQ DT_INST_IRQN(0)

#define HSAES_STATUS_NOK_MASK ((HSAES_STATUS_STOPPED | HSAES_STATUS_ERROR) & ~HSAES_STATUS_BUSY)

typedef struct cmrt_hs_aes_context {
	/* ddc shall be first element because we don't use container_of */
	cmrt_dd_context_t ddc;
	uint32_t channel;
	uint32_t key_bank;
	uint32_t decrypt;
	uint32_t desc_count;      /* No. of descriptors (desc.), current and queued. */
	uint32_t nr_failed;       /* No. of erred desc. */
} cmrt_hs_aes_context_t;

#define HSAES_NR_CONTEXTS (CMRT_HSAES_NR_CHANNELS * CMRT_HSAES_NR_KEY_BANKS)
static cmrt_hs_aes_context_t contexts[HSAES_NR_CONTEXTS];

#define MAX_NR_DESC (CMRT_HSAES_DESC_BRAM_SIZE/MIN(sizeof(cmrt_hs_aes_linear_desc_t), sizeof(cmrt_hs_aes_circular_desc_t)))
struct {
	uint32_t ep;
	uint32_t queue_count;     /* No. of desc. in BRAM. */
	uint8_t ref_count;        /* No. open contexts. HSAES mode may only change when no other context is open. */
	uint8_t s2c[MAX_NR_DESC]; /* Desc. slot no. (in BRAM) to index into "contexts". */
	uint32_t desc_size;       /* Size of a desc. for current mode. */
	uint32_t max_p;           /* Maximum value of desc. slot "pointer", for current mode. */
} hs_aes;

static_assert(HSAES_NR_CONTEXTS <  (1 << (8*sizeof(hs_aes.ref_count)))-1,
	      "Number of HSAES context do not fit in hs_aes.ref_count & hs_aes.s2c.");

static inline uint32_t hs_aes_status(void)
{
	return cmrt_core_status(R_BASE) & HWC_STATUS_STATUS_MASK;
}

static inline bool hs_aes_queue_full(void)
{
	return hs_aes.queue_count > hs_aes.max_p;
}

static int hs_aes_load_key(cmrt_hs_aes_t context, const void *key, size_t keylen, bool hkey)
{
	if ((hkey && keylen != CMRT_HSAES_HKEY_SIZE) ||
	    (!hkey && (keylen != CMRT_HSAES_HKEY_SIZE && keylen != CMRT_HSAES_KEY_SIZE))) {
		return -EINVAL;
	}
	cmrt_ktc_t ktc = cmrt_ktc_open(0, 0);
	if (!cmrt_is_valid(ktc)) {
		return -EBUSY;
	}
	cmrt_ktc_cmd_t cmd = { 0 };
	cmd.key = (void *)key;
	cmd.key_size = keylen;
	cmd.metadata[0] = context->key_bank |
		HSAES_KB(SET, CHANNEL, context->channel) |
		HSAES_KB(SET, HKEY, hkey) |
		HSAES_KB(SET, KEY_256_BIT, keylen == CMRT_HSAES_HKEY_SIZE ? 0 : 1);

	int ret = cmrt_ktc_export(ktc, &cmd);
	cmrt_ktc_close(ktc);
	return ret;
}

static int hs_aes_load_hkey(cmrt_hs_aes_t context, const void *key, size_t keylen)
{
	cmrt_aes_t aes = cmrt_aes_open(0);
	if (!cmrt_is_valid(aes)) {
		return -EBUSY;
	}
	uint8_t hkey[CMRT_HSAES_HKEY_SIZE] = { 0 };
	int ret = cmrt_aes_init(aes, AES_ENCRYPT, AES_ECB, key, keylen, 0, 0, 0);
	if (ret != 0) { goto out; }
	ret = cmrt_aes_final(aes, hkey, sizeof(hkey), hkey);
	if (ret != 0) { goto out; }
	ret = hs_aes_load_key(context, hkey, sizeof(hkey), 1);
 out:
	cmrt_aes_close(aes);
	return ret;
}

static uint32_t hs_aes_run_next_desc(void)
{
	/* Shift EP to run next queued desc. */
	uint32_t p = hs_aes.ep + 1;
	if (p > hs_aes.max_p) { p = 0; }
	sys_write32(p, R_BASE+R_HSAES_EP);
	hs_aes.ep = p;
	return p;
}

static cmrt_hs_aes_t hs_aes_last_desc_context(void)
{
	/* Find last desc. slot. */
	uint32_t p = hs_aes.ep ? hs_aes.ep - 1 : hs_aes.max_p;
	return contexts + hs_aes.s2c[p];
}

static int hs_aes_enqueue_desc(cmrt_hs_aes_t context, void *desc_in)
{
	if (hs_aes_status() & HSAES_STATUS_NOK_MASK) {
		return -EIO; /* Core is not running. */
	}
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	int ret = -EAGAIN;
	if (hs_aes_queue_full()) {
		goto out; /* No room. */
	}
	/* Find first unused desc. slot. */
	uint32_t p = hs_aes.ep + hs_aes.queue_count;
	p -= hs_aes.queue_count ? 1 : 0;
	if (p > hs_aes.max_p) {
		p -= hs_aes.max_p + 1;
	}
	/* Copy desc. to slot. */
	uint32_t mode = sys_read32(R_BASE+R_HSAES_MODE);
	if (mode == HSAES_MODE_LINEAR_DESC) {
		cmrt_hs_aes_linear_desc_t *desc = (void *)(R_BASE+R_HSAES_DESC_BRAM);
		desc[p] = *(cmrt_hs_aes_linear_desc_t *)desc_in;
	} else {
		cmrt_hs_aes_circular_desc_t *desc = (void *)(R_BASE+R_HSAES_DESC_BRAM);
		desc[p] = *(cmrt_hs_aes_circular_desc_t *)desc_in;
	}

	/* Update book keeping. */
	hs_aes.s2c[p] = context - contexts;
	hs_aes.queue_count++;
	context->desc_count++;
	LOG_HSAES("desc queued at %d\n", p);

#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->ddc.sem);
#endif
	if (hs_aes.queue_count == 1) {
		hs_aes_run_next_desc();
		LOG_HSAES("enqueue_desc started queue.\n");
	}
	ret = 0;
out:
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&context->ddc, ret);
}

static bool hs_aes_handle_desc_done(void)
{
	if (hs_aes_status() != HSAES_STATUS_IDLE) {
		return false;
	}
	/* Core has processed all descs. */
	cmrt_hs_aes_t context = hs_aes_last_desc_context();
	if (context->desc_count) {
		context->desc_count--;
#ifdef CONFIG_MULTITHREADING
		if (context->desc_count == 0) {
			/* This context has no more descs. queued; wake up its owner thread. */
			k_sem_give(&context->ddc.sem);
		}
#endif
		/* Run next desc. if one or more are queued. */
		hs_aes.queue_count -= hs_aes.queue_count ? 1 : 0;
		if (hs_aes.queue_count) {
			hs_aes_run_next_desc();
			return true; /* Queue started. */
		}
	}
	return false;
}

#ifdef CONFIG_MULTITHREADING
static void hs_aes_irq_handler(void *arg)
{
	ARG_UNUSED(arg);

	LOG_HSAES("interrupt: 0x%0x\n", sys_read32(R_BASE+R_HSAES_INTERRUPT));
	LOG_HSAES("mask: 0x%0x\n", sys_read32(R_BASE+R_HSAES_INTERRUPT_MASK));
	LOG_HSAES("status: 0x%0x\n", sys_read32(R_BASE+R_HSAES_STATUS));
	LOG_HSAES("control: 0x%0x\n", sys_read32(R_BASE+R_HSAES_CONTROL));
	LOG_HSAES("SP: 0x%0x\n", sys_read32(R_BASE+R_HSAES_SP));
	LOG_HSAES("EP: 0x%0x\n", sys_read32(R_BASE+R_HSAES_EP));
	LOG_HSAES("Q count: %d\n", hs_aes.queue_count);

	/* Get and clear interrupt. */
	uint32_t interrupt = sys_read32(R_BASE+R_HSAES_INTERRUPT);
	sys_write32(interrupt, R_BASE+R_HSAES_INTERRUPT);

	if (interrupt) {
		if (interrupt & HSAES_INTERRUPT_DONE) {
			if (hs_aes_handle_desc_done()) {
				LOG_HSAES("isr started queue\n");
			}
		} else {
			/* Error, wake owner thread of current desc. */
			cmrt_hs_aes_t context = hs_aes_last_desc_context();
			context->nr_failed = context->desc_count;
			hs_aes.queue_count -= context->desc_count;
			context->desc_count = 0;
			k_sem_give(&context->ddc.sem);
		}
	}
}
#endif

static int hs_aes_poll_cb(cmrt_dd_context_t *ddc)
{
	cmrt_hs_aes_t context = (void *)ddc;

#ifndef CONFIG_MULTITHREADING
	if (hs_aes_handle_desc_done()) {
		LOG_HSAES("poll_cb started queue\n");
	}
#endif
	static uint32_t count;
	if (count++ == 0 || count % 100000 == 0) {
		LOG_HSAES("count %d\n", count);
		LOG_HSAES("interrupt: 0x%0x\n", sys_read32(R_BASE+R_HSAES_INTERRUPT));
		LOG_HSAES("mask: 0x%0x\n", sys_read32(R_BASE+R_HSAES_INTERRUPT_MASK));
		LOG_HSAES("status: 0x%0x\n", sys_read32(R_BASE+R_HSAES_STATUS));
		LOG_HSAES("control: 0x%0x\n", sys_read32(R_BASE+R_HSAES_CONTROL));
		LOG_HSAES("SP: 0x%0x\n", sys_read32(R_BASE+R_HSAES_SP));
		LOG_HSAES("EP: 0x%0x\n", sys_read32(R_BASE+R_HSAES_EP));
		LOG_HSAES("Q count: %d\n", hs_aes.queue_count);
	}

	/*
	 * A context can have multiple desc. queued, we have to wait for all
	 * of its descs. to complete, as long as core is not stuck.
	 */
	return ((hs_aes_status() & HSAES_STATUS_NOK_MASK) ||
		!context->desc_count) ? 0 : 1;
}

static int hs_aes_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	ARG_UNUSED(mask);

	if (hs_aes_status() & HSAES_STATUS_NOK_MASK) {
		/*
		 * Core is stuck. We have to retire all queued descs.
		 * Visit all queued descs., mark them failed and unblock their
		 * owner threads.
		 */
		uint32_t p = hs_aes.ep ? hs_aes.ep - 1 : hs_aes.max_p;
		while (hs_aes.queue_count) {
			/* Find owner context of this desc. */
			cmrt_hs_aes_t context = contexts + hs_aes.s2c[p];
			if (++p > hs_aes.max_p) { p = 0; }
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
			hs_aes.queue_count--;
		}
	}
	cmrt_hs_aes_t context = (void *)ddc;
	return context->nr_failed;
}

int cmrt_hs_aes_abort(cmrt_hs_aes_t context)
{
	sys_write32(HSAES_CONTROL_ABORT, R_BASE+R_HSAES_CONTROL);
	uint32_t status = HSAES_STATUS_STOPPED;
	int ret = cmrt_wait_status_to(R_BASE+R_HSAES_STATUS, &status, 1);
	return ret ? -EIO : 0;
}

static int hs_aes_open_cb(cmrt_dd_context_t *ddc, void *arg)
{
	cmrt_hs_aes_t context = (void *)ddc;
	bool linear = context->ddc.flags & CMRT_O_HSAES_LINEAR;

	uint32_t mask = cmrt_dd_lock(ddc->dd);
	int ret;
	if (!hs_aes.ref_count) {
		/* First context to open. */

		/* Flush core and set mode. */
		sys_write32(HSAES_CONTROL_FLUSH, R_BASE+R_HSAES_CONTROL);
		uint32_t status = HSAES_STATUS_IDLE;
		ret = cmrt_wait_status_to(R_BASE+R_HSAES_STATUS, &status, 1);
		if (ret != 0) { goto out; } /* stuck core */
		sys_write32(linear ? HSAES_MODE_LINEAR_DESC : HSAES_MODE_CIRCULAR_DESC, R_BASE+R_HSAES_MODE);
		ret = cmrt_wait_status_to(R_BASE+R_HSAES_STATUS, &status, 1);
		if (ret != 0) { goto out; } /* stuck core */

		hs_aes.desc_size = linear ? sizeof(cmrt_hs_aes_linear_desc_t) : sizeof(cmrt_hs_aes_circular_desc_t);
		hs_aes.max_p = (CMRT_HSAES_DESC_BRAM_SIZE / hs_aes.desc_size) - 1;
		hs_aes.ep = hs_aes.queue_count = 0;
	}

	ret = -EBUSY;
	/* Current mode must match requested mode. */
	uint32_t mode = sys_read32(R_BASE+R_HSAES_MODE);
	if ((mode == HSAES_MODE_LINEAR_DESC) != linear) {
		goto out;
	}
	/* Initialize key, channel association. */
	int i = context - contexts;
	context->key_bank = i < CMRT_HSAES_NR_CHANNELS ?  0 : 1;
	context->channel = i < CMRT_HSAES_NR_CHANNELS ? i : i - CMRT_HSAES_NR_CHANNELS;
	context->desc_count = context->nr_failed = 0;

	/*
	 * In linear mode, desc. of different key_bank's and same channel must
	 * not interleave. This can not be insured at runtime easily. To
	 * prevent this, let's not fail open request if all contexts using
	 * key_bank 0 are in use.
	 */
	if (linear && i >= CMRT_HSAES_NR_CHANNELS) {
		goto out;
	}
	/* Update count of open contexts. */
	hs_aes.ref_count++;
	ret = 0;
out:
	cmrt_dd_unlock(ddc->dd, mask);
	return ret;
}

static void hs_aes_close_cb(cmrt_dd_context_t *ddc)
{
	cmrt_hs_aes_t context = (void *)ddc;

	/* We can't leave desc. queued, let's abort queue. */
	if (context->desc_count) {
		cmrt_hs_aes_abort(context);
	}
	/* Update count of open contexts. */
	hs_aes.ref_count--;
}

static const struct cmrt_driver_api hs_aes_driver_api = {
	.open_cb = hs_aes_open_cb,
	.find_cb = NULL,
	.poll_cb = hs_aes_poll_cb,
	.sync_cb = hs_aes_sync_cb,
	.close_cb = hs_aes_close_cb,
};

static cmrt_dd_t hs_aes_dd = {
	.base = CMRT_HSAES_BASE,
	.is_locking = 0,
	.context_count = HSAES_NR_CONTEXTS,
	.context_size = sizeof(cmrt_hs_aes_context_t),
#ifdef CONFIG_MULTITHREADING
	.irq_mask = HSAES_INTERRUPT_MASK,
#else
	.irq_mask = 0,
#endif
	.contexts = contexts,
};

static int cmrt_hs_aes_dd_init(const struct device *dev)
{
	cmrt_dd_t *dd = dev->data;
	hs_aes.ref_count = HSAES_NR_CONTEXTS;
	cmrt_dd_init(dd, dev);
#ifndef CONFIG_CMRT_FBOOT
	IRQ_CONNECT(CMRT_HSAES_IRQ, 0, hs_aes_irq_handler, NULL, 0);
#endif
	return 0;
}

DEVICE_DT_INST_DEFINE(0, cmrt_hs_aes_dd_init, NULL, &hs_aes_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      (void *)&hs_aes_driver_api);

cmrt_hs_aes_t cmrt_hs_aes_open(uint32_t flags)
{
	return (cmrt_hs_aes_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, 0);
}

void cmrt_hs_aes_close(cmrt_hs_aes_t context)
{
	uint8_t zeros[CMRT_HSAES_KEY_SIZE] = { 0 };
	hs_aes_load_key(context, zeros, CMRT_HSAES_KEY_SIZE, 0);
	hs_aes_load_key(context, zeros, CMRT_HSAES_HKEY_SIZE, 1);
	cmrt_dd_close((cmrt_dd_context_t *)context);
}

int cmrt_hs_aes_queue_at(cmrt_hs_aes_t context,
			 cmrt_aes_operation_t operation, cmrt_aes_mode_t mode,
			 const void *key, size_t keylen,
			 uint32_t at_count, uint64_t inbuf, uint64_t outbuf)
{
	if ((operation != CMRT_AES_ENCRYPT && operation != CMRT_AES_DECRYPT) ||
	    mode != CMRT_AES_GCM || at_count == 0 ||
	    (at_count * sizeof(cmrt_pdma_at_t)) > CMRT_PDMA_AT_SIZE ||
	    inbuf == 0 || outbuf == 0) {
		return -EINVAL;
	}
	if (key != NULL) {
		if (keylen != CMRT_HSAES_KEY_SIZE && keylen != (CMRT_HSAES_KEY_SIZE/2)) {
			return -EINVAL;
		}
	}
	/* Input/output buffers must align with DDR buffer boundaries. */
	if (!is_aligned((inbuf | outbuf), CMRT_DCM_DDR_BUFFER_SIZE-1)) {
		return -EINVAL;
	}
	cmrt_hs_aes_circular_desc_t d = {
		.in_addr = inbuf,
		.out_addr = outbuf,
		.F1 = HSAES(SET, SIZE, at_count) |
			HSAES(SET, KEY_BANK, context->key_bank) |
			HSAES(SET, CHANNEL, context->channel) |
			HSAES(SET, DECRYPT, operation == CMRT_AES_DECRYPT) |
			HSAES(SET, LINEAR, 0),
	};
	if (key != NULL) {
		/* Load keys */
		int ret = hs_aes_load_hkey(context, key, keylen);
		if (ret != 0) { return ret; }
		ret = hs_aes_load_key(context, key, keylen, 0);
		if (ret != 0) { return ret; }
	}
	return hs_aes_enqueue_desc(context, &d);
}

int cmrt_hs_aes_init(cmrt_hs_aes_t context,
		     cmrt_aes_operation_t operation, cmrt_aes_mode_t mode,
		     const void *key, size_t keylen,
		     uint64_t iv, size_t ivlen)
{
	if ((operation != CMRT_AES_ENCRYPT && operation != CMRT_AES_DECRYPT) ||
	    mode != CMRT_AES_GCM || iv == 0 || ivlen != CMRT_HSAES_IV_SIZE ||
	    (key == NULL && keylen != 0)) {
		return -EINVAL;
	}
	if (key != NULL) {
		if (keylen != CMRT_HSAES_KEY_SIZE && keylen != (CMRT_HSAES_KEY_SIZE/2)) {
			return -EINVAL;
		}
	}
	cmrt_hs_aes_linear_desc_t d = {
		.F1 = HSAES(SET, LINEAR, 1) |
			HSAES(SET, CHANNEL, context->channel) |
			HSAES(SET, KEY_BANK, context->key_bank) |
			HSAES(SET, DECRYPT, operation == CMRT_AES_DECRYPT),
		.F2 = HSAES(SET, SOP, 1),
		.meta_addr = iv,
	};
	context->decrypt = (operation == CMRT_AES_DECRYPT);
	if (key) {
		/* Load keys */
		int ret = hs_aes_load_hkey(context, key, keylen);
		if (ret != 0) { return ret; }
		ret = hs_aes_load_key(context, key, keylen, 0);
		if (ret != 0) { return ret; }
	}
	return hs_aes_enqueue_desc(context, &d);
}

int cmrt_hs_aes_update_aad(cmrt_hs_aes_t context, uint64_t aad, size_t aadlen)
{
	if (aad == 0 || aadlen == 0 ||
	    aadlen > (CMRT_HSAES_LIN_DESC_MAX_SIZE-1) ||
	    !is_aligned(aadlen, CMRT_HSAES_BLOCK_SIZE-1)) {
		return -EINVAL;
	}
	cmrt_hs_aes_linear_desc_t d = {
		.F1 = HSAES(SET, LINEAR, 1) |
			HSAES(SET, CHANNEL, context->channel) |
			HSAES(SET, KEY_BANK, context->key_bank) |
			HSAES(SET, DECRYPT, context->decrypt),
		.F2 = HSAES(SET, AD_SIZE, aadlen),
		.ad_addr = aad,
	};
	return hs_aes_enqueue_desc(context, &d);
}

inline int cmrt_hs_aes_final_aad(cmrt_hs_aes_t context, uint64_t aad, size_t aadlen)
{
	return cmrt_hs_aes_update_aad(context, aad, aadlen);
}

int cmrt_hs_aes_update(cmrt_hs_aes_t context, uint64_t input, size_t inlen, uint64_t output)
{
	if (input == 0 || output == 0 ||
	    inlen == 0 || inlen > (CMRT_HSAES_LIN_DESC_MAX_SIZE-1) ||
	    !is_aligned(inlen, CMRT_HSAES_BLOCK_SIZE-1)) {
		return -EINVAL;
	}
	cmrt_hs_aes_linear_desc_t d = (cmrt_hs_aes_linear_desc_t) {
		.in_addr = input,
		.out_addr = output,
		.F1 = HSAES(SET, LINEAR, 1) |
			HSAES(SET, CHANNEL, context->channel) |
			HSAES(SET, KEY_BANK, context->key_bank) |
			HSAES(SET, DECRYPT, context->decrypt) |
			HSAES(SET, SIZE, inlen),
	};
	return hs_aes_enqueue_desc(context, &d);
}

static int hs_aes_final(cmrt_hs_aes_t context, uint64_t tag, size_t *taglen)
{
	if (tag == 0 || taglen == NULL || *taglen != CMRT_HSAES_TAG_SIZE) {
		return -EINVAL;
	}
	cmrt_hs_aes_linear_desc_t d = (cmrt_hs_aes_linear_desc_t) {
		.F1 = HSAES(SET, LINEAR, 1) |
			HSAES(SET, CHANNEL, context->channel) |
			HSAES(SET, KEY_BANK, context->key_bank) |
			HSAES(SET, DECRYPT, context->decrypt),
		.F2 = HSAES(SET, EOP, 1),
		.meta_addr = tag - CMRT_HSAES_TAG_OFFSET,
	};
	return hs_aes_enqueue_desc(context, &d);
}

int cmrt_hs_aes_ae_final(cmrt_hs_aes_t context, uint64_t input, size_t inlen, uint64_t output, uint64_t tag, size_t *taglen)
{
	int ret = 0;
	if (inlen != 0) {
		ret = cmrt_hs_aes_update(context, input, inlen, output);
		if (ret != 0) { return ret; }
		ret = hs_aes_final(context, tag, taglen);
	}
	return ret;
}

int cmrt_hs_aes_sync(cmrt_hs_aes_t context)
{
	if ((context->ddc.flags & CMRT_O_SYNC) != 0u) {
		/* Already synced internally. */
		return 0;
	}
	return cmrt_dd_sync((cmrt_dd_context_t *)context);
}

int cmrt_hs_aes_kdc_cmd(cmrt_hs_aes_t context, size_t keylen, cmrt_kdc_cmd_t *cmd)
{
	if ((keylen != CMRT_HSAES_KEY_SIZE &&
	     keylen != (CMRT_HSAES_KEY_SIZE/2)) ||
	    cmd == NULL ||
	    cmd->diversify_len > (KDC_DIVERSIFY_PATH_WORDS*4)+1) {
		return -EINVAL;
	}
	cmd->dest = KDC_DEST_SW;
	cmd->key_size = KDC_SIZE_256;
	cmd->command0 = 0;
	cmd->command1 = 0;

	cmrt_kdc_t kdc = cmrt_kdc_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(kdc)) {
		return -EIO;
	}
	int ret = cmrt_kdc_derive_key(kdc, cmd);
	cmrt_kdc_close(kdc);
	if (ret != 0) { return ret; }
	ret = hs_aes_load_hkey(context, cmd->key, keylen);
	if (ret != 0) { return ret; }
	return hs_aes_load_key(context, cmd->key, keylen, 0);
}

void cmrt_hs_aes_get_channel_context(cmrt_hs_aes_t context, uint32_t *channel, uint32_t *key_bank)
{
	if (channel) {
		*channel = context->channel;
	}
	if (key_bank) {
		*key_bank = context->key_bank;
	}
}
