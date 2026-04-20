/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_dmac

#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/dmac.h>
#include <drivers/cmrt/sac.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "dmac_int.h"

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_DMAC_BASE); /* device tree must match headers */
#define CMRT_DMAC_IRQ DT_INST_IRQN(0)

#define MAX_VCQ_LEN 2UL

typedef struct cmrt_dmac_context {
	cmrt_dd_context_t ddc;
	mm_reg_t vcq_bar;
	mm_reg_t vcq_head;
	mm_reg_t vcq_tail;
	mm_reg_t vcq_length;
	cmrt_dmac_desc_t *vcq_addr[MAX_VCQ_LEN];
	cmrt_dmac_desc_t vcq_desc[MAX_VCQ_LEN];
	size_t vcq_entries;
	int status;
} cmrt_dmac_channel_t;

#define DMAC_CHANNELS 1 /* only one channel in Cmrt */
CMRT_DD_CONTEXT static cmrt_dmac_channel_t channels[DMAC_CHANNELS];

#ifdef CONFIG_MULTITHREADING
#define DESC_STOP (DESC_STOP_BIT | DESC_INTERRUPT_BIT)
#else
#define DESC_STOP DESC_STOP_BIT
#endif

#ifdef CONFIG_SUPERVISOR_MODE
#define DESC_PRIV DESC_PRIV_SUPERVISOR
#else
#define DESC_PRIV DESC_PRIV_MACHINE
#endif

static inline uint32_t dmac_status(void)
{
	uint32_t status = cmrt_core_status(R_BASE);
	return status & HWC_STATUS_STATUS_MASK;
}

static inline bool is_dmac_locked(void)
{
	uint32_t status = dmac_status();
	return status == HWC_STATUS_IDLE_LOCKED || status == HWC_STATUS_SUCCESS;
}

static inline bool is_dmac_success(void)
{
	return dmac_status() == HWC_STATUS_SUCCESS;
}

static inline bool is_dmac_complete(void)
{
	uint32_t status = dmac_status();
	return status == HWC_STATUS_SUCCESS || IS_HWC_ERROR(status);
}

static int dmac_start(cmrt_dmac_channel_t *channel, int index)
{
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&channel->ddc.sem);
#endif
	/* Set values, clear interrupt flag and start transfer. */
	sys_write32((uintptr_t)&channel->vcq_addr[index], channel->vcq_bar);
	sys_write32(sizeof(uint32_t) * channel->vcq_entries, channel->vcq_tail);
	sys_write32(channel->vcq_entries, channel->vcq_length);

	sys_write32(DMAC_CONTROL_START, (mm_reg_t)(R_BASE+R_CORE_CONTROL));
	return 0;
}

static inline uint32_t cmrt_dmac_src_base(uint32_t addr)
{
	/* Set DMAC input base and return translated address. */
	uint64_t base = cmrt_sac_translate((uintptr_t)addr);
	sys_write32((base >> 32), (mm_reg_t)(CMRT_SAC_BASE+R_DMA_ADDR_IN_HI));
	return (uint32_t)base;
}

static inline uint32_t cmrt_dmac_dst_base(uint32_t addr)
{
	/* Set DMAC output base and return translated address. */
	uint64_t base = cmrt_sac_translate((uintptr_t)addr);
	sys_write32((base >> 32), (mm_reg_t)(CMRT_SAC_BASE+R_DMA_ADDR_OUT_HI));
	return (uint32_t)base;
}

static bool dmac_is_devaddr(uint32_t addr)
{
	return addr >= (CORE_ID_MIN << 12) && addr < ((CORE_ID_MAX + 1u) << 12);
}

int z_impl_cmrt_dmac_data(cmrt_dmac_t channel, uint32_t src_addr, uint32_t dst_addr, uint32_t size, cmrt_dmac_flags_t flags)
{
	if (!cmrt_dd_valid(channel) ||
	    !is_aligned(src_addr, 4u) || !is_aligned(dst_addr, 4u)) {
		/* Addresses must be word aligned. */
		return -EINVAL;
	}
	if (!is_aligned(size, 4u) || size < sizeof(uint32_t) ||
	    (size > (DMAC_DATA_DST_SIZE_MASK << 2))) {
		/* Only full words accepted, size can be max 0xffff words. */
		return -EINVAL;
	}
	if (!is_in_4gb((uintptr_t)src_addr, size) ||
	    !is_in_4gb((uintptr_t)dst_addr, size)) {
		/* Do not allow access outside SAC window. */
		return -EINVAL;
	}
	bool dma_to_device = dmac_is_devaddr(dst_addr);
	bool dma_from_device = dmac_is_devaddr(src_addr);
	if (dma_to_device && dma_from_device) {
		/* Cannot do dev-to-dev, only sram-to-dev or dev-to-sram. */
		return -EINVAL;
	}
	uint32_t dev_base = dma_to_device ? dst_addr : dma_from_device ? src_addr : 0;
	int rv = -EIO;
	cmrt_dd_t *dd = channel->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	flags &= (DESC_DECSRCADDR_BIT | DESC_DECDSTADDR_BIT |
#ifdef CONFIG_CMRT_CFI
		  DESC_CFI_BIT |
#endif
		  DESC_SWPSRCBYTES_BIT | DESC_SWPDSTBYTES_BIT);
#ifdef CONFIG_CMRT_SAC2
	if (is_sac_ptr((uintptr_t)src_addr)) {
		flags |= DESC_EXTSRC_BIT;
		src_addr = cmrt_dmac_src_base(src_addr);
	}
	if (is_sac_ptr((uintptr_t)dst_addr)) {
		flags |= DESC_EXTDST_BIT;
		dst_addr = cmrt_dmac_dst_base(dst_addr);
	}
#endif
	if (is_dmac_locked()) {
		if (dev_base != 0) {
			/* Transfer core lock to DMAC. */
			sys_write32(CORE_ID_DMAC << 8 | HWC_LOCK_PRIV,
				    dev_base + R_HWC_LOCK_MASTER);
		}
		(void)memset(&channel->vcq_desc, 0, sizeof(channel->vcq_desc));
		if (dma_to_device) {
			channel->vcq_desc[0].header =
				DESC_MODE_DATA | DESC_PRIV | flags;
			channel->vcq_desc[0].u.data.src_addr = src_addr;
			channel->vcq_desc[0].u.data.dst_addr =
				dst_addr + R_CORE_INPUT;
		} else if (dma_from_device) {
			channel->vcq_desc[0].header =
				DESC_MODE_DATA | DESC_PRIV | flags;
			channel->vcq_desc[0].u.data.src_addr =
				src_addr + R_CORE_OUTPUT;
			channel->vcq_desc[0].u.data.dst_addr = dst_addr;
		} else {
			channel->vcq_desc[0].header = DESC_MODE_DATA |
				DESC_PRIV | DESC_STOP | flags;
			channel->vcq_desc[0].u.data.dst_addr = dst_addr;
			channel->vcq_desc[0].u.data.src_addr = src_addr;
			channel->vcq_entries = 1;
		}
		channel->vcq_desc[0].u.data.dst_size = (size >> 2);
		if (dev_base != 0) {
			/*
			 * The core must be locked to DMAC, so create
			 * a CSR descriptor to move the lock to CPU.
			 */
			channel->vcq_desc[1].header =
				DESC_MODE_CSR | DESC_PRIV | DESC_STOP;
			channel->vcq_desc[1].u.csr.csr_addr0 =
				dev_base + R_HWC_LOCK_MASTER;
			channel->vcq_desc[1].u.csr.csr_data0 =
				HWC_LOCK_MASTER_CPU;
			channel->vcq_entries = 2;
		}
		rv = dmac_start(channel, 0);
	}
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&channel->ddc, rv);
}

int cmrt_dmac_crypto(cmrt_dmac_t channel, uint32_t dev_base, uint32_t src_addr, uint32_t dst_addr, uint32_t data_size, cmrt_dmac_flags_t flags)
{
	if (!cmrt_dd_valid(channel) ||
	    !is_aligned(src_addr, 4u) || !is_aligned(dst_addr, 4u)) {
		/* Addresses must be word aligned. */
		return -EINVAL;
	}
	if (data_size > (DMAC_DATA_DST_SIZE_MASK << 2)) {
		/* Sizes can be max 0xffff words. */
		return -EINVAL;
	}
	if (!is_in_4gb((uintptr_t)src_addr, data_size) ||
	    !is_in_4gb((uintptr_t)dst_addr, data_size)) {
		/* Do not allow access outside SAC window. */
		return -EINVAL;
	}
	if (dmac_is_devaddr(src_addr) || dmac_is_devaddr(dst_addr)) {
		/* Source and destination can be data only. */
		return -EINVAL;
	}
	int rv = -EIO;
	cmrt_dd_t *dd = channel->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	flags &= (DESC_DECSRCADDR_BIT | DESC_DECDSTADDR_BIT |
		  DESC_SWPSRCBYTES_BIT | DESC_SWPDSTBYTES_BIT);
#ifdef CONFIG_CMRT_SAC2
	if (is_sac_ptr((uintptr_t)src_addr)) {
		flags |= DESC_EXTSRC_BIT;
		src_addr = cmrt_dmac_src_base(src_addr);
	}
	if (is_sac_ptr((uintptr_t)dst_addr)) {
		flags |= DESC_EXTDST_BIT;
		dst_addr = cmrt_dmac_dst_base(dst_addr);
	}
#endif
	if (is_dmac_locked()) {
		/* Transfer core lock to DMAC. */
		sys_write32(CORE_ID_DMAC << 8 | HWC_LOCK_PRIV,
			    dev_base + R_HWC_LOCK_MASTER);

		(void)memset(&channel->vcq_desc, 0, sizeof(channel->vcq_desc));
		uint32_t src_words = src_addr != 0 ? (data_size + 3u) >> 2 : 0;
		uint32_t dst_words = dst_addr != 0 ? (data_size + 3u) >> 2 : 0;
		/*
		 * Create a crypto descriptor to handle
		 * - all input not yet handled elsewhere
		 * - all output
		 */
		channel->vcq_desc[0].header =
			DESC_MODE_CRYPTO | DESC_PRIV | flags;
		channel->vcq_desc[0].u.crypto.device_addr = dev_base;
		channel->vcq_desc[0].u.crypto.src_addr = src_addr;
		channel->vcq_desc[0].u.crypto.dst_addr = dst_addr;
		channel->vcq_desc[0].u.crypto.srcdst_size =
			(src_words << 16) | dst_words;
		/*
		 * ...and a CSR descriptor to give back the core lock
		 */
		channel->vcq_desc[1].header =
			DESC_MODE_CSR | DESC_PRIV | DESC_STOP;
		channel->vcq_desc[1].u.csr.csr_addr0 =
			dev_base + R_HWC_LOCK_MASTER;
		channel->vcq_desc[1].u.csr.csr_data0 = HWC_LOCK_MASTER_CPU;
		channel->vcq_entries = 2;
		rv = dmac_start(channel, 0);
	}
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&channel->ddc, rv);
}

int cmrt_dmac_helper(uint32_t dev_base, uint32_t src_addr, uint32_t dst_addr, uint32_t data_size, uint32_t block_size, cmrt_dmac_flags_t flags)
{
	cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);
	if (!cmrt_dd_valid(dmac)) { return -ENODEV; }

	bool dma_to_device = dmac_is_devaddr(dst_addr);
	bool dma_from_device = dmac_is_devaddr(src_addr);

	int rv = 0;
	while (data_size >= block_size) {
		/* Move batch of data. */
		uint32_t dmalen = (data_size > (DMAC_DATA_DST_SIZE_MASK << 2)) ?
			(DMAC_DATA_DST_SIZE_MASK << 2) : data_size;
		dmalen &= ~(block_size - 1u);
		if (dev_base != 0) {
			rv = cmrt_dmac_crypto(dmac, dev_base, src_addr, dst_addr, dmalen, flags);
		} else {
			rv = cmrt_dmac_data(dmac, src_addr, dst_addr, dmalen, flags);
		}
		if (rv != 0) { goto out; }
		if (!dma_to_device && dst_addr != 0) {
			dst_addr += dmalen;
		}
		if (!dma_from_device && src_addr != 0) {
			src_addr += dmalen;
		}
		data_size -= dmalen;
	}
	/* Return bytes left. */
	rv = (int)data_size;
 out:
	cmrt_dmac_close(dmac);
	return rv;
}

int z_impl_cmrt_dmac_fill(cmrt_dmac_t channel, uint32_t fill_data, uint32_t dst_addr, uint32_t size, cmrt_dmac_flags_t flags)
{
	if (!cmrt_dd_valid(channel) || !is_aligned(dst_addr, 4u)) {
		/* Addresses must be word aligned. */
		return -EINVAL;
	}
	if (!is_aligned(size, 4u) || size < sizeof(uint32_t) ||
	    (size > (DMAC_FILL_DST_SIZE_MASK << 2))) {
		/* Only full words accepted, size can be max 0xffff words. */
		return -EINVAL;
	}
	if (!is_in_4gb((uintptr_t)dst_addr, size)) {
		/* Do not allow access outside SAC window. */
		return -EINVAL;
	}
	int rv = -EIO;
	cmrt_dd_t *dd = channel->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	flags &= DESC_DECDSTADDR_BIT;
#ifdef CONFIG_CMRT_SAC2
	if (is_sac_ptr((uintptr_t)dst_addr)) {
		flags |= DESC_EXTDST_BIT;
		dst_addr = cmrt_dmac_dst_base(dst_addr);
	}
#endif
	if (is_dmac_locked()) {
		(void)memset(&channel->vcq_desc, 0, sizeof(channel->vcq_desc));
		channel->vcq_desc[0].header = DESC_MODE_FILL |
			DESC_PRIV | DESC_STOP | flags;
		channel->vcq_desc[0].u.fill.dst_size = (size >> 2);
		channel->vcq_desc[0].u.fill.dst_addr = dst_addr;
		channel->vcq_desc[0].u.fill.fill_data = fill_data;
		channel->vcq_entries = 1;
		rv = dmac_start(channel, 0);
	}
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&channel->ddc, rv);
}

#ifdef TEST_DMAC_LOCK
int cmrt_dmac_lock(cmrt_dmac_t channel, uint32_t dev_addr)
{
	int rv = -EIO;
	cmrt_dd_t *dd = channel->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	if (is_dmac_locked()) {
		(void)memset(&channel->vcq_desc, 0, sizeof(channel->vcq_desc));
		channel->vcq_desc[0].header =
			DESC_MODE_LOCK | DESC_PRIV | DESC_STOP;
		channel->vcq_desc[0].u.lock.device_addr = dev_addr;
		channel->vcq_desc[0].u.lock.retry_interval = 1000;
		channel->vcq_entries = 1;
		rv = dmac_start(channel, 0);
	}
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&channel->ddc, rv);
}
#endif /* TEST_DMAC_LOCK */

int cmrt_dmac_csr(cmrt_dmac_t channel, uint32_t csr_data0, uint32_t csr_addr0, uint32_t csr_data1, uint32_t csr_addr1)
{
	if (!dmac_is_devaddr(csr_addr0) ||
	    (csr_addr1 != 0u && !dmac_is_devaddr(csr_addr1))) {
		return -EINVAL;
	}
	int rv = -EIO;
	cmrt_dd_t *dd = channel->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	if (is_dmac_locked()) {
		(void)memset(&channel->vcq_desc, 0, sizeof(channel->vcq_desc));
		channel->vcq_desc[0].header =
			DESC_MODE_CSR | DESC_PRIV | DESC_STOP;
		if (csr_addr1 != 0u) {
			channel->vcq_desc[0].header |= DESC_VALIDCSR1_BIT;
		}
		channel->vcq_desc[0].u.csr.csr_addr0 = csr_addr0;
		channel->vcq_desc[0].u.csr.csr_data0 = csr_data0;
		channel->vcq_desc[0].u.csr.csr_addr1 = csr_addr1;
		channel->vcq_desc[0].u.csr.csr_data1 = csr_data1;
		channel->vcq_entries = 1;
		rv = dmac_start(channel, 0);
	}
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&channel->ddc, rv);
}

static int dmac_poll_cb(cmrt_dd_context_t *ddc)
{
	ARG_UNUSED(ddc);

	bool complete = is_dmac_complete();
	if (complete && !is_dmac_success()) {
		cmrt_dmac_channel_t *channel = (cmrt_dmac_channel_t *)ddc;
		if (channel->vcq_entries == 2) {
			/* This is failed crypto/data operation with HW core.
			 * Run the CSR operation because that was not ran. */
			(void)cmrt_dd_flush(ddc);
			channel->status = -EIO; /* for sync_cb */
			channel->vcq_entries = 1;
			(void)dmac_start(channel, 1);
#ifdef CONFIG_MULTITHREADING
			/* Wait here for the CSR operation. */
			(void)k_sem_take(&ddc->sem, K_FOREVER);
#endif
			complete = is_dmac_complete();
		}
	}
	return complete ? 0 : 1;
}

static int dmac_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	ARG_UNUSED(ddc);
	ARG_UNUSED(mask);

	if (is_dmac_success()) {
		cmrt_dmac_channel_t *channel = (cmrt_dmac_channel_t *)ddc;
		return channel->status; /* possibly set in poll_cb */
	}
	return -EIO;
}

static void dmac_init_channel_cb(cmrt_dd_context_t *ddc)
{
	cmrt_dmac_channel_t *channel = (cmrt_dmac_channel_t *)ddc;
	channel->vcq_bar = (mm_reg_t)(R_BASE+R_VCQ_BAR0);
	channel->vcq_head = (mm_reg_t)(R_BASE+R_VCQ_HEAD0);
	channel->vcq_tail = (mm_reg_t)(R_BASE+R_VCQ_TAIL0);
	channel->vcq_length = (mm_reg_t)(R_BASE+R_VCQ_LENGTH0);
	for (size_t j = 0; j < MAX_VCQ_LEN; j++) {
		channel->vcq_addr[j] = &channel->vcq_desc[j];
	}
	channel->status = 0;
}

#ifdef CONFIG_MULTITHREADING
static void dmac_irq_handler(void *arg)
{
	ARG_UNUSED(arg);

	/* Get and clear interrupt. */
	uint32_t pending = sys_read32((mm_reg_t)(R_BASE+R_CORE_INTERRUPT));
	sys_write32(pending, (mm_reg_t)(R_BASE+R_CORE_INTERRUPT));

	/* Signal for command completion. */
	k_sem_give(&channels[0].ddc.sem);
}
#endif

static cmrt_dd_t dmac_dd = {
	.base = CMRT_DMAC_BASE,
	.is_locking = 1,
	.context_count = DMAC_CHANNELS,
	.context_size = sizeof(cmrt_dmac_channel_t),
#ifdef CONFIG_MULTITHREADING
	.irq_mask = DMAC_INTERRUPT_MASK,
#else
	.irq_mask = 0,
#endif
	.contexts = channels,
};

static const struct cmrt_driver_api dmac_driver_api = {
	.open_cb = NULL,
	.find_cb = NULL,
	.poll_cb = dmac_poll_cb,
	.sync_cb = dmac_sync_cb,
	.close_cb = dmac_init_channel_cb,
};

static int cmrt_dmac_init(const struct device *dev)
{
	/* Init DMA channels. */
	cmrt_dd_t *dd = dev->data;
	cmrt_dd_init(dd, dev);

#ifdef CONFIG_MULTITHREADING
	/* Setup IRQ handler for the driver. */
	IRQ_CONNECT(CMRT_DMAC_IRQ, 0, dmac_irq_handler, NULL, 0);
#endif

	return 0;
}

DEVICE_DT_INST_DEFINE(0, cmrt_dmac_init, NULL, &dmac_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      (void *)&dmac_driver_api);

cmrt_dmac_t z_impl_cmrt_dmac_open(uint32_t flags)
{
	return (cmrt_dmac_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, NULL);
}

void z_impl_cmrt_dmac_close(cmrt_dmac_t channel)
{
	if (cmrt_dd_valid(channel)) {
		cmrt_dd_close((cmrt_dd_context_t *)channel);
	}
}

int z_impl_cmrt_dmac_sync(cmrt_dmac_t channel)
{
	if (!cmrt_dd_valid(channel)) {
		return -EINVAL;
	}
	if ((channel->ddc.flags & CMRT_O_SYNC) != 0u) {
		/* Already synced internally. */
		return 0;
	}
	return cmrt_dd_sync((cmrt_dd_context_t *)channel);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_dmac_channel(cmrt_dmac_t channel)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)channel, &dmac_driver_api);
}

static inline cmrt_dmac_t z_vrfy_cmrt_dmac_open(uint32_t flags)
{
	return z_impl_cmrt_dmac_open(flags);
}
#include <syscalls/cmrt_dmac_open_mrsh.c>

static inline void z_vrfy_cmrt_dmac_close(cmrt_dmac_t channel)
{
	z_syscall_verify_dmac_channel(channel);
	z_impl_cmrt_dmac_close(channel);
}
#include <syscalls/cmrt_dmac_close_mrsh.c>

static inline int z_vrfy_cmrt_dmac_data(cmrt_dmac_t channel, uint32_t src_addr, uint32_t dst_addr, uint32_t size, uint32_t flags)
{
	z_syscall_verify_dmac_channel(channel);
	Z_OOPS(Z_SYSCALL_MEMORY_READ((void *)src_addr, size));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE((void *)dst_addr, size));
	return z_impl_cmrt_dmac_data(channel, src_addr, dst_addr, size, flags);
}
#include <syscalls/cmrt_dmac_data_mrsh.c>

static inline int z_vrfy_cmrt_dmac_fill(cmrt_dmac_t channel, uint32_t fill_data, uint32_t dst_addr, uint32_t size, uint32_t flags)
{
	z_syscall_verify_dmac_channel(channel);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE((void *)dst_addr, size));
	return z_impl_cmrt_dmac_fill(channel, fill_data, dst_addr, size, flags);
}
#include <syscalls/cmrt_dmac_fill_mrsh.c>

static inline int z_vrfy_cmrt_dmac_sync(cmrt_dmac_t channel)
{
	z_syscall_verify_dmac_channel(channel);
	return z_impl_cmrt_dmac_sync(channel);
}
#include <syscalls/cmrt_dmac_sync_mrsh.c>

#endif /* CONFIG_USERSPACE */
