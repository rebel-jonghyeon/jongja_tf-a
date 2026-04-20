/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_pke

#include <device.h>
#include <init.h>
#include <kernel.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <kernel_structs.h>
#include <drivers/cmrt/tmc.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/util.h>
#include <drivers/cmrt/crypto/pke_dpasl.h>
#include <drivers/cmrt/pke4/pke4_reg.h>
#include "pke_string.h"

#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
#include "kat/pke_kat.h"
#endif

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#if (CONFIG_CMRT_PKE_VERSION < 0x040000)
#error wrong PKE version
#endif

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_PKE_BASE); /* device tree must match headers */
#define CMRT_PKE_IRQ DT_INST_IRQN(0)

#define CMRT_PKERAM_BASE DT_REG_ADDR(DT_NODELABEL(pkeram))
#define CMRT_PKERAM_SIZE DT_REG_SIZE(DT_NODELABEL(pkeram))
static uint32_t *const pke_ram = (uint32_t *)(uintptr_t)CMRT_PKERAM_BASE;

#define PKE_CONTEXTS 1
CMRT_DD_CONTEXT static cmrt_pke_context_t contexts[PKE_CONTEXTS];

#ifdef CONFIG_MULTITHREADING
static volatile uint32_t pke_interrupt;

#define MANUAL_COMPLETE_IRQ (1u << 7)
static_assert((MANUAL_COMPLETE_IRQ & PKE_IRQ_MASK) == 0,
	      "manual flag clashes with real irq");
#endif

static inline uint32_t read_mau_status(void)
{
	return sys_read32((mm_reg_t)(R_PKE_BASE+R_MAU_STATUS));
}

static inline MCG_UNIT_STATUS mcg_status(uint32_t mau_status)
{
	return (MCG_UNIT_STATUS)((mau_status & MAU_MCG_MASK) >> MAU_MCG_OFFSET);
}

static inline MAU_STATE mau_state(uint32_t mau_status)
{
	return (MAU_STATE)((mau_status & MAU_CORE_MASK) >> MAU_CORE_OFFSET);
}

static inline uint32_t pke_status(void)
{
	return sys_read32((mm_reg_t)(R_BASE + R_CORE_STATUS))
	       & HWC_STATUS_STATUS_MASK;
}

static void pke_flush_error(uint32_t mau_status)
{
	uint32_t mau_cause = (mau_status & MAU_MAU_ERROR_CAUSE_MASK)
			     >> MAU_MAU_ERROR_CAUSE_OFFSET;
	uint32_t mcg_cause = (mau_status & MAU_MCG_ERROR_CAUSE_MASK)
			     >> MAU_MCG_ERROR_CAUSE_OFFSET;
	if (mau_cause != 0u || mcg_cause != 0u) {
		LOG_DBG("PKE error mau_cause:0x%x mcg_cause:0x%x mau:0x%x mcg:0x%x\n",
			mau_cause, mcg_cause, mau_state(mau_status),
			mcg_status(mau_status));
	}
	sys_write32((uint32_t)PKE_FLUSH_ERROR,
		    (mm_reg_t)(R_PKE_BASE + R_PKE_RESET_CTRL));
	sys_write32((uint32_t)0, (mm_reg_t)(R_PKE_BASE + R_PKE_RESET_CTRL));
}

int is_pke_idle(void)
{
	uint32_t mau_status = read_mau_status();
	MCG_UNIT_STATUS mcg = mcg_status(mau_status);
	if (mcg == MCG_STATUS_ERROR || mcg == MCG_STATUS_PANIC) {
		LOG_DBG("Error flushing\n");
		pke_flush_error(mau_status);
	}

	if (pke_status() == HWC_STATUS_IDLE_LOCKED &&
	    mcg_status(mau_status) == MCG_STATUS_IDLE &&
	    mau_state(mau_status) == MAU_STATUS_READY) {
		return 0;
	} else {
		return -EIO;
	}
}

/*!
 * Poll completed status, will not test for interrupts.
 */
static inline bool is_pke_complete(void)
{
	uint32_t mau_status = read_mau_status();
	MCG_UNIT_STATUS mcg = mcg_status(mau_status);
	MAU_STATE mau = mau_state(mau_status);
	return pke_status() == HWC_STATUS_IDLE_LOCKED &&
	       (mcg == MCG_STATUS_IDLE || mcg == MCG_STATUS_ERROR ||
		mcg == MCG_STATUS_PANIC) &&
	       (mau == MAU_STATUS_READY || mau == MAU_STATUS_ERROR ||
		mau == MAU_STATUS_PANIC);
}


/* Read and clear irqs in a more or less atomic way. */
uint32_t cmrt_pke_irqs(void)
{
	/* Read core interrupt */
	uint32_t core  = sys_read32((mm_reg_t)(R_BASE + R_CORE_INTERRUPT));

	/* Get and clear interrupt, first internal interrupt. */
	uint32_t isr = sys_read32((mm_reg_t)(R_PKE_BASE + R_MAU_IFC_ISR));
	sys_write32(isr, (mm_reg_t)(R_PKE_BASE + R_MAU_IFC_ISR));

	/* Now clear interrupts before previous to prevent resignaling */
	sys_write32(core, (mm_reg_t)(R_BASE + R_CORE_INTERRUPT));

	return isr;
}


int cmrt_pke_complete(cmrt_pke_context_t *pke)
{
	assert(pke);
	(void)cmrt_pke_irqs(); /* clear irqs always */
	/* this could be slightly streamlined for the automatic sync case,
	   but result in more code and potentially different results.
	   The overhead to pay is still less than going through a
	   separate call to synchronize.
	*/
#ifdef CONFIG_MULTITHREADING
	/* This is updated non-atomically, which is a race (if a real
	 * irq happens concurrently.  However, it is really sufficient
	 * to get any wakeup condition set as the flags of the cores
	 * are read and tested instead of these recorded interrupt
	 * flags.
	 */
	pke_interrupt |= MANUAL_COMPLETE_IRQ;
	k_sem_give(&pke->ddc.sem); /* signal any wait condition */
#endif
	return cmrt_dd_autosync(&pke->ddc, 0);
}


int cmrt_pke_issue_mcg_command(cmrt_pke_context_t *context, uint32_t cmd)
{
	assert(context->cmd == 0UL);
	assert(cmd != 0UL);
	context->cmd = cmd;
#ifdef CONFIG_MULTITHREADING
	(void)cmrt_pke_irqs();		/* clear any pending irqs */
	k_sem_reset(&context->ddc.sem); /* no busy check */
	pke_interrupt = ~(MAU_TO_IDLE_IRQ | FIFO_ERROR_IRQ | MAU_ERROR_IRQ
			   | MCG_ERROR_IRQ | MANUAL_COMPLETE_IRQ);
#endif
	sys_write32(cmd, (mm_reg_t)(R_PKE_BASE + R_MAU_MCG_COMMAND));
	return 0;
}

uint32_t *pke_addr(uint32_t slot, const struct dpa_ecc_curve_struct *curve, const uint32_t bits)
{
	uint32_t length = 0;
	uint32_t *addr;

	if ((bits != 0) && (curve == NULL)) {
#ifdef CONFIG_CMRT_PKE_32_BIT
		length = bits / 32;
#else
		length = bits / 64;
#endif
	} else if (curve != NULL) {
#ifdef CONFIG_CMRT_PKE_32_BIT
		length = curve->length;
#else /* 64 bit */
		length = (((curve->length - 1) / 2) + 1);
#endif
	} else {
		return NULL;
	}

	addr = CPU_SRAM_ADDRESS(slot * length);
	return addr;
}

static int pke_open_cb(cmrt_dd_context_t *ddc, void *arg)
{
	ARG_UNUSED(arg);
	cmrt_pke_context_t *context = (cmrt_pke_context_t *)ddc;
	context->cmd = 0UL;
	/* PKE_PRNG_SEED is initiated here */
	uint32_t seed[4];
	if (cmrt_get_entropy(seed, sizeof(seed)) < 0) {
		return -ENXIO;
	}
	sys_write32(seed[0], (mm_reg_t)(R_PKE_BASE+R_MAU_MCG_PKE_PRNG_SEED_1));
	sys_write32(seed[1], (mm_reg_t)(R_PKE_BASE+R_MAU_MCG_PKE_PRNG_SEED_2));
	sys_write32(seed[2], (mm_reg_t)(R_PKE_BASE+R_MAU_MCG_PKE_PRNG_SEED_3));
	sys_write32(seed[3], (mm_reg_t)(R_PKE_BASE+R_MAU_MCG_PKE_PRNG_SEED_4));

#ifdef CONFIG_MULTITHREADING
	pke_interrupt = 0;
	/* Enable MAU interrupts. */
	sys_write32(MAU_TO_IDLE_IRQ, (mm_reg_t)(R_PKE_BASE+R_MAU_IFC_ICR));
#endif

	return 0;
}

typedef enum curveType_t {
	INVALID_CURVE_PARAMS = -1, /* (SPEC_MOD_DISABLED | SPEC_MOD_IN_ROM) */
	ROM_CURVE = 0,
	RAM_CURVE = 1
} curveType_t;

static int pke_mcg_response(cmrt_pke_context_t *context)
{
	int ret = 0;
	uint32_t length;

	uint32_t mau_status = read_mau_status();
	MCG_UNIT_STATUS mcg = mcg_status(mau_status);
	if (mcg == MCG_STATUS_ERROR || mcg == MCG_STATUS_PANIC) {
		pke_flush_error(mau_status);
		ret = -EINVAL;
	}

	cmrt_pke_response_t *const resp = &context->response;
	if (resp->curve != NULL) {
		length = cmrt_pke_get_curve_length(resp->curve);
	} else {
		length = resp->bits / 8;
	}

	for (int i = 0; (i < resp->copies_to_make) && (ret == 0); i++) {
		if (resp->bits != 0) {
			memcpy(resp->ret_param[i].rAddr, resp->ret_param[i].pkeAddr, resp->ret_param[i].bits / 8);
#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE) || \
		defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
		} else if (resp->curve != NULL) {
			if ((resp->curve->curve_is_Montgomery == TRUE) ||
			    (resp->curve->curve_is_Edwards == TRUE)) {
				if (resp->ret_param[i].bits != 0) {
					memcpy(resp->ret_param[i].rAddr,
					       resp->ret_param[i].pkeAddr,
					       resp->ret_param[i].bits / 8);
				} else {
					memcpy(resp->ret_param[i].rAddr,
					       resp->ret_param[i].pkeAddr,
					       length);
				}
			} else {
				ret = COPY_FROM_PKE(resp->ret_param[i].pkeAddr,
						    length,
						    resp->ret_param[i].rAddr,
						    resp->slot);
			}
#endif
		} else {
			ret = COPY_FROM_PKE(resp->ret_param[i].pkeAddr,
					    length,
					    resp->ret_param[i].rAddr,
					    resp->slot);
		}
	}

	(void)memset(resp, 0, sizeof(cmrt_pke_response_t));
	context->cmd = 0UL;
	return ret;
}

static int pke_poll_cb(cmrt_dd_context_t *ddc)
{
	ARG_UNUSED(ddc);
#ifdef CONFIG_MULTITHREADING
	/* there can be an interrupt sent before going to idle: does
	it make sense to really wait for the interrupt as the wait is
	instead always on the completion and idleness of the interface
	instead
	*/
	return (pke_interrupt & (MAU_TO_IDLE_IRQ | FIFO_ERROR_IRQ
				 | MAU_ERROR_IRQ | MCG_ERROR_IRQ
				 | MANUAL_COMPLETE_IRQ)) ? 0 : 1;
#else
	return is_pke_complete() ? 0 : 1;
#endif
}

int cmrt_pke_wait(void)
{
	while (!is_pke_complete()) {
		/* busy poll, yield is too expensive */
	}
	return is_pke_idle();
}

static int pke_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	int res = -EINTR;
	ARG_UNUSED(mask);

	if (is_pke_complete()) {
		cmrt_pke_context_t *pke = (cmrt_pke_context_t *)ddc;
		res = pke_mcg_response(pke);
#ifdef CONFIG_MULTITHREADING
		pke_interrupt = 0;
#endif
	}
	return res;
}


#ifdef CONFIG_MULTITHREADING
static uint32_t pke_irqs; /* counter statistics */

static void pke_irq_handler(void *arg)
{
	ARG_UNUSED(arg);
	uint32_t irqs = cmrt_pke_irqs();
	++pke_irqs;
	if (irqs != 0) {
		pke_interrupt |= irqs;
		k_sem_give(&contexts[0].ddc.sem);
	}
}
#endif

static void pke_close_cb(cmrt_dd_context_t *ddc)
{
	cmrt_pke_context_t *context = (cmrt_pke_context_t *)ddc;
	if (context->cmd != 0UL) {
		while (is_pke_idle() != 0) {
			cmrt_dd_yield();
		}
	}
	(void)memset(pke_ram, 0, CMRT_PKERAM_SIZE);
}

static cmrt_dd_t pke_dd = {
	.base = CMRT_PKE_BASE,
	.is_locking = 1,
	.context_count = PKE_CONTEXTS,
	.context_size = sizeof(cmrt_pke_context_t),
#ifdef CONFIG_MULTITHREADING
	.irq_mask = PKE_CORE_IRQ,
#else
	.irq_mask = 0,
#endif
	.contexts = contexts,
};

static const struct cmrt_driver_api pke_driver_api = {
	.open_cb = pke_open_cb,
#ifdef CONFIG_CMRT_FIPS_140_MODE
	.open_kat = pke_open_kat,
#endif
	.find_cb = NULL,
	.poll_cb = pke_poll_cb,
	.sync_cb = pke_sync_cb,
	.close_cb = pke_close_cb,
};

static int cmrt_pke_init(const struct device *dev)
{
	/* Init PKE contexts. */
	cmrt_dd_t *dd = dev->data;
	cmrt_dd_init(dd, dev);

#ifdef CONFIG_MULTITHREADING
	/* Setup IRQ handler for the driver. */
	IRQ_CONNECT(CMRT_PKE_IRQ, 0, pke_irq_handler, NULL, 0);
	pke_interrupt = 0;
#endif

	return 0;
}

DEVICE_DT_INST_DEFINE(0, cmrt_pke_init, NULL, &pke_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &pke_driver_api);

#ifdef CONFIG_CMRT_FIPS_140_MODE
SYS_INIT(pke_init_kat, POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY);
#endif

cmrt_pke_t z_impl_cmrt_pke_open(uint32_t flags)
{
	return (cmrt_pke_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, NULL);
}

void z_impl_cmrt_pke_close(cmrt_pke_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_pke_sync(cmrt_pke_t context)
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

int z_impl_cmrt_pke_flush(cmrt_pke_t context)
{
	int res = cmrt_dd_flush((cmrt_dd_context_t *)context);
	(void)memset(pke_ram, 0, CMRT_PKERAM_SIZE);
	return res;
}

/* Report MAU FIFO status.  If MAU is in error state, report < 0, otherwise,
 * if it can be written to (0 - fifo full, > 0 - space in fifo)
 */
static int maufeed(void)
{
	uint32_t status = read_mau_status();
	uint32_t fifo = (status & MAU_FIFO_MASK) >> MAU_FIFO_OFFSET;
	if ((((status >> (MAU_CORE_OFFSET + 1)) & 1u) != 0u)
	    || (fifo == FIFO_STATUS_ERROR)) {
		return -1; /* error */
	}
	return fifo != FIFO_STATUS_FULL; /* can fill in */
}

int cmrt_pke_mau_command_sequence(const uint32_t *command_word,
				  const uint32_t command_length,
				  const uint32_t variable_length)
{
	/* if the mau status is error, or, the fifo is in error, it is
	 * an error.  This function will not finish if the status
	 * register reads 0 constantly!
	 */
	for (uint32_t i = 0; i < command_length; i++) {
		int fifo, retries = 8 << 20; /* a high limit */
		do {
			fifo = maufeed();
		} while ((fifo == 0) && (--retries >= 0));
		if (fifo <= 0) {
			LOG_DBG("mau fail seq %p #%u/%u\n",
				command_word, i, command_length);
			(void)cmrt_pke_wait(); /* for side effects */
			return -1;
		}
		sys_write32(command_word[i] | variable_length,
			    (mm_reg_t)(R_PKE_BASE + R_MAU_MAU_COMMAND));
	}

	return cmrt_pke_wait();
}

int cmrt_pke_clear_ram(void)
{
	uint32_t length = MAU_READ_REG(R_MAU_MAX_LEN);

	static const uint32_t cmds_zero[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(LOAD,          R_MAU_ZERO),
		SLOT_CMD(STORE,         SLOT(0)),
		SLOT_CMD(STORE,         SLOT(1)),
		SLOT_CMD(STORE,         SLOT(2)),
		SLOT_CMD(STORE,         SLOT(3)),
		SLOT_CMD(STORE,         SLOT(4)),
		SLOT_CMD(STORE,         SLOT(5)),
		SLOT_CMD(STORE,         SLOT(6)),
		SLOT_CMD(STORE,         SLOT(7)),
	};

	return cmrt_pke_mau_command_sequence(cmds_zero, sizeof(cmds_zero)/sizeof(uint32_t), length);
}

cmrt_ecc_curve_t cmrt_pke_verify_curve(cmrt_ecc_curve_t curve)
{
	if (curve == NULL ||
	    curve->length == 0 ||
	    curve->length > MAX_EC_CURVE_LENGTH_W) {
		return NULL;
	}

	return curve;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

cmrt_ecc_curve_t cmrt_pke_verify_user_curve(cmrt_ecc_curve_t curve)
{
	cmrt_ecc_curve_t pcurve = z_impl_cmrt_pke_get_curve((uint32_t)curve);
	Z_OOPS(pcurve == NULL);
	return pcurve;
}

void z_syscall_verify_pke_context(cmrt_pke_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &pke_driver_api);
}

static inline cmrt_pke_t z_vrfy_cmrt_pke_open(uint32_t flags)
{
	return z_impl_cmrt_pke_open(flags);
}
#include <syscalls/cmrt_pke_open_mrsh.c>

static inline void z_vrfy_cmrt_pke_close(cmrt_pke_t context)
{
	z_syscall_verify_pke_context(context);
	return z_impl_cmrt_pke_close(context);
}
#include <syscalls/cmrt_pke_close_mrsh.c>

static inline int z_vrfy_cmrt_pke_sync(cmrt_pke_t context)
{
	z_syscall_verify_pke_context(context);
	return z_impl_cmrt_pke_sync(context);
}
#include <syscalls/cmrt_pke_sync_mrsh.c>

static inline int z_vrfy_cmrt_pke_flush(cmrt_pke_t context)
{
	z_syscall_verify_pke_context(context);
	return z_impl_cmrt_pke_flush(context);
}
#include <syscalls/cmrt_pke_flush_mrsh.c>

#endif /* CONFIG_USERSPACE */
