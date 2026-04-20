/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_omc

#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/sic.h>
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
#include <drivers/cmrt/aes_reg.h>
#include <drivers/cmrt/hc_reg.h>
#endif
#include <string.h>
#include <errno.h>
#include <assert.h>

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_OMC_BASE); /* device tree must match headers */
#define CMRT_OMC_IRQ DT_INST_IRQN(0)

typedef struct cmrt_omc_context {
	cmrt_dd_context_t ddc;
	uint32_t last_irq;
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
	uint32_t command;
	void *buffer;
	size_t buflen;
#endif
} cmrt_omc_context_t;

#define OMC_CONTEXTS 1 /* only one active at a time */
CMRT_DD_CONTEXT static cmrt_omc_context_t contexts[OMC_CONTEXTS];

static inline uint32_t omc_status(void)
{
	uint32_t status = cmrt_core_status(R_BASE);
	return status & HWC_STATUS_STATUS_MASK;
}

static inline bool is_omc_ready(void)
{
	uint32_t status = omc_status();
	return (status == HWC_STATUS_IDLE_LOCKED) ||
		(status == HWC_STATUS_SUCCESS);
}

static int omc_write_internal(cmrt_omc_t context, uint32_t offset, const void *buffer, uint32_t buflen)
{
	int rv = -EIO;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	if (is_omc_ready()) {
		context->last_irq = 0;
		if (offset < sizeof(cmrt_otp_layout_t)) {
			/* Write to HW managed area. */
#ifdef CONFIG_MULTITHREADING
			k_sem_reset(&context->ddc.sem);
#endif
			/* Set up base addr. */
			sys_write32(offset, (mm_reg_t)(R_BASE+R_OTP_BASE_ADDR));
			/* Copy content. */
			uint32_t words = buflen >> 2;
			const uint32_t *values = buffer;
			for (uint32_t i = 0; i < words; i++) {
				sys_write32(values[i], (mm_reg_t)(R_BASE+R_OTP_WRITE_DATA0) + (i * 4u));
			}
			/* Issue ctrl request. */
			sys_write32((uint32_t)REQ_WRITE_INDIRECT, (mm_reg_t)(R_BASE+R_CORE_CONTROL));
		} else {
			/* Write to eSW area. */
			(void)memcpy(cmrt_otp_layout(offset), buffer, buflen);
#ifdef CONFIG_MULTITHREADING
			/* Signal for command completion. */
			k_sem_give(&context->ddc.sem);
#endif
		}
		rv = 0;
	}
	cmrt_dd_unlock(dd, mask);
	return rv;
}

static int is_root_offset(uint32_t offset)
{
	for (int i = 0; i < CMRT_OTP_NUM_ROOTS; i++) {
		if (offset == OTP_ROOT_OFFSET(i)) {
			return i;
		}
	}
	return -1;
}

static int is_keysplit_offset(uint32_t offset)
{
	for (int i = 0; i < CMRT_OTP_NUM_KEYSPLITS; i++) {
		if (offset == OTP_KEYSPLIT_OFFSET(i)) {
			return i;
		}
	}
	return -1;
}

static bool is_offset_ok(uint32_t offset, size_t buflen)
{
	/* Check valid offsets and respective sizes (and alignment). */
	switch (offset) {
	case OTP_LIFECYCLE_OFFSET:
		if (buflen == OTP_LIFECYCLE_SIZE) { return true; }
		break;
	case OTP_TDV_OFFSET:
		if (buflen == OTP_TDV_SIZE) { return true; }
		break;
	case OTP_STATUS_WORD_OFFSET:
		if (buflen == OTP_STATUS_WORD_SIZE) { return true; }
		break;
	case OTP_KEY_OBLITERATE_OFFSET:
		if (buflen == OTP_KEY_OBLITERATE_SIZE) { return true; }
		break;
	case OTP_DEVICE_ID_OFFSET:
		if (buflen == OTP_DEVICE_ID_SIZE) { return true; }
		break;
	case OTP_OEM_ID_OFFSET:
		if (buflen == OTP_OEM_ID_SIZE) { return true; }
		break;
	case OTP_DGOK_OFFSET:
		if (buflen == OTP_DGOK_SIZE) { return true; }
		break;
	case OTP_MACHINE_VERSION_OFFSET:
	case OTP_SUPERVISOR_VERSION_OFFSET:
	case OTP_USER_VERSION_OFFSET:
		if (buflen == sizeof(uint32_t)) { return true; }
		break;
	default:
		if (is_root_offset(offset) >= 0 && buflen == OTP_ROOT_SIZE) {
			return true;
		}
		if (is_keysplit_offset(offset) >= 0 && buflen == OTP_KEYSPLIT_SIZE) {
			return true;
		}
		if ((offset >= OTP_ESW_OFFSET &&
		     (offset + buflen) <= OTP_ESW_OFFSET + OTP_ESW_SIZE)) {
			return true;
		}
		break;
	}
	return false;
}

static void *otpcpy(cmrt_omc_t context, void *dest, const void *src, size_t n)
{
#ifdef CONFIG_MULTITHREADING
	ARG_UNUSED(context);
	return memcpy(dest, src, n);
#else
	/* Possible ECC errors must be checked for every word.
	 * If interrupts are available, context->last_irq is updated
	 * in the irq handler and memcpy can be used. */
	uint32_t *d = (uint32_t *)dest;
	uint32_t *s = (uint32_t *)src;
	n >>= 2; /* read words */
	while (n > 0) {
		*d++ = *s++;
		uint32_t pending = sys_read32((mm_reg_t)(R_BASE+R_CORE_INTERRUPT));
		sys_write32(pending, (mm_reg_t)(R_BASE+R_CORE_INTERRUPT));
		context->last_irq |= pending;
		n--;
	}
	return dest;
#endif
}

int z_impl_cmrt_omc_read(cmrt_omc_t context, uint32_t offset, void *buffer, size_t buflen)
{
	if (!cmrt_dd_valid(context) || !is_offset_ok(offset, buflen) ||
	    !is_aligned(buffer, 4u) || !is_aligned(buflen, 4u)) {
		return -EINVAL;
	}
	if (offset == OTP_DGOK_OFFSET || is_keysplit_offset(offset) >= 0) {
		return -EFAULT;
	}
	context->last_irq = 0;
	int rv = is_root_offset(offset);
	if (rv >= 0) {
		cmrt_omc_root_perm_t *perm = (cmrt_omc_root_perm_t *)((uint8_t *)buffer + sizeof(cmrt_omc_root_id_t));
		cmrt_omc_root_perm_t *from = cmrt_otp_layout(OTP_ROOT_OFFSET(rv) + sizeof(cmrt_omc_root_id_t));
		(void)otpcpy(context, perm, from, sizeof(cmrt_omc_root_perm_t));

		/* Permissions are stored inverted. */
		perm->slot_perm.val = ~perm->slot_perm.val;
		perm->key_perm.val = ~perm->key_perm.val;
		perm->feature_perm.val = ~perm->feature_perm.val;
		perm->sw_otp_perm[0].val = 0xffff8000UL ^ perm->sw_otp_perm[0].val;
		perm->sw_otp_perm[1].val = 0xffff8000UL ^ perm->sw_otp_perm[1].val;
		perm->software_perm.val = ~perm->software_perm.val;
		/* Root id is first in the buffer. Note is_offset_ok for: */
		/* coverity[OVERRUN] */
		buflen = sizeof(cmrt_omc_root_id_t);
	}
	(void)otpcpy(context, buffer, cmrt_otp_layout(offset), buflen);

	/* Check last interrupts for possible ECC error. */
	return (context->last_irq & OMC_READ_ECC_NOK_IRQ) != 0 ? -EIO : 0;
}

static bool is_valid_lifecycle(const void *buffer)
{
	const cmrt_otp_layout_t *otp = cmrt_otp_layout(0);
	uint32_t value = *(uint32_t *)buffer;
	if (value >= otp->h.life_cycle) {
		switch (value) {
		case DLC_TESTED:
		case DLC_PROVISIONED:
		case DLC_MISSION:
		case DLC_FRA:
		case DLC_DECOMMISSIONED:
			return true;
		}
	}
	return false;
}

int z_impl_cmrt_omc_write(cmrt_omc_t context, uint32_t offset, const void *buffer, size_t buflen)
{
	if (!cmrt_dd_valid(context) || !is_offset_ok(offset, buflen) ||
	    !is_aligned(buffer, 4u) || !is_aligned(buflen, 4u)) {
		return -EINVAL;
	}
	if ((offset == OTP_LIFECYCLE_OFFSET && !is_valid_lifecycle(buffer)) ||
	    offset == OTP_STATUS_WORD_OFFSET ||
#if defined(CONFIG_CRI_OMC_LAYOUT_VERSION) && CONFIG_CRI_OMC_LAYOUT_VERSION >= 2
	    offset == OTP_KEY_OBLITERATE_OFFSET ||
#endif
#if defined(CONFIG_CRI_OMC_LAYOUT_VERSION) && CONFIG_CRI_OMC_LAYOUT_VERSION >= 3
	    offset == OTP_ROOT_VALID_OFFSET ||
	    offset == OTP_ROOT_OBLITERATE_OFFSET ||
#endif
	    offset == OTP_DGOK_OFFSET) {
		return -EFAULT;
	}
	int rv = is_root_offset(offset);
	if (rv >= 0) {
		cmrt_omc_root_perm_t perm;
		const cmrt_omc_root_t *root = buffer;
		/* Permissions are stored inverted. */
		perm.slot_perm.val = ~root->perm.slot_perm.val;
		perm.key_perm.val = ~root->perm.key_perm.val;
		perm.feature_perm.val = ~root->perm.feature_perm.val;
		perm.sw_otp_perm[0].val = 0xffff8000UL ^ root->perm.sw_otp_perm[0].val;
		perm.sw_otp_perm[1].val = 0xffff8000UL ^ root->perm.sw_otp_perm[1].val;
		perm.software_perm.val = ~root->perm.software_perm.val;
		/* Must write perm before root id. */
		rv = omc_write_internal(context, offset + sizeof(cmrt_omc_root_id_t), &perm, sizeof(perm));
		if (rv == 0) { rv = cmrt_dd_sync((cmrt_dd_context_t *)context); }
		if (rv != 0) { return rv; }
		/* Root id is first in the buffer. Note is_offset_ok for: */
		/* coverity[OVERRUN] */
		buflen = sizeof(cmrt_omc_root_id_t);
	}
	rv = omc_write_internal(context, offset, buffer, buflen);
	return cmrt_dd_autosync(&context->ddc, rv);
}

/*
 * Return true if DGOK or keysplit is valid (burned and not obliterated).
 * index: DGOK = 0, KS = 1..7
 */
static bool is_otp_keysplit_valid(int index)
{
	static const uint32_t status_word_encodings[] = {
		OTP_PERSO_INVALID,
		OTP_VKS_VALID, OTP_KS_VALID1, OTP_KS_VALID2, OTP_KS_VALID3,
		OTP_KS_VALID4, OTP_KS_VALID5, OTP_KS_VALID6, OTP_KS_VALID7
	};

	static const uint32_t key_obliterate_word_encodings[] = {
		OTP_VKS_OBLITERATED,
		OTP_KS_OBLITERATED1, OTP_KS_OBLITERATED2, OTP_KS_OBLITERATED3,
		OTP_KS_OBLITERATED4, OTP_KS_OBLITERATED5, OTP_KS_OBLITERATED6,
		OTP_KS_OBLITERATED7
	};

	const uint32_t *sw = cmrt_otp_layout(OTP_STATUS_WORD_OFFSET);
	const uint32_t *kow = cmrt_otp_layout(OTP_KEY_OBLITERATE_OFFSET);

	return ((status_word_encodings[index + 1] & *sw) == status_word_encodings[index + 1]) && ((key_obliterate_word_encodings[index] & *kow) == 0u);
}

static int omc_obliterate_internal(cmrt_omc_t context, uint32_t offset)
{
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	if (is_omc_ready()) {
#ifdef CONFIG_MULTITHREADING
		k_sem_reset(&context->ddc.sem);
#endif
		sys_write32(offset, (mm_reg_t)(R_BASE+R_OTP_BASE_ADDR));
		sys_write32((uint32_t)REQ_OBLITERATE, (mm_reg_t)(R_BASE+R_CORE_CONTROL));
	}
	cmrt_dd_unlock(dd, mask);
	return 0;
}

int z_impl_cmrt_omc_obliterate(cmrt_omc_t context, uint32_t offset)
{
	if (!cmrt_dd_valid(context)) { return -EINVAL; }

	int rv = -ENOENT;
	int index = is_keysplit_offset(offset);
	if ((index >= 0 && is_otp_keysplit_valid(index + 1)) ||
	    (offset == OTP_DGOK_OFFSET && is_otp_keysplit_valid(0)) ||
	    (is_root_offset(offset) >= 0)) {
		/* Obliterate keysplit, DGOK, or root. */
		rv = omc_obliterate_internal(context, offset);
	} else if (offset == OTP_STATUS_WORD_OFFSET) {
		/* Obliterate perso root. */
		uint32_t value = OTP_PERSO_INVALID;
		rv = omc_write_internal(context, OTP_STATUS_WORD_OFFSET, &value, sizeof(value));
	}
	return cmrt_dd_autosync(&context->ddc, rv);
}

int cmrt_omc_reshadow(cmrt_omc_t context)
{
	if (!cmrt_dd_valid(context)) { return -EINVAL; }

	int rv = -EIO;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	if (is_omc_ready()) {
#ifdef CONFIG_MULTITHREADING
		k_sem_reset(&context->ddc.sem);
#endif
		/* issue ctrl request */
		sys_write32((uint32_t)REQ_RESHADOW, (mm_reg_t)(R_BASE+R_CORE_CONTROL));
		rv = 0;
	}
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&context->ddc, rv);
}

#ifndef CONFIG_SUPERVISOR_MODE
static cmrt_omc_perm_t otp_esw_perm(uint32_t val)
{
	switch (val & OMC_SW_OTP_PERM_RW) {
	case OMC_SW_OTP_PERM_RW:
		return PT_OTP_ESW_RW;
	case OMC_SW_OTP_PERM_W:
		return PT_OTP_ESW_W;
	case OMC_SW_OTP_PERM_R:
		return PT_OTP_ESW_R;
	default:
		return PT_OTP_ESW_NONE;
	}
}

static inline uint32_t otp_esw_perm_word(uint32_t val)
{
	return val & ~OMC_SW_OTP_PERM_RW;
}
#endif

int cmrt_omc_permissions(cmrt_omc_t context, const omc_perm_t *perm)
{
#ifdef CONFIG_SUPERVISOR_MODE
	ARG_UNUSED(context);
	ARG_UNUSED(perm);
	return -EPERM;
#else
	if (!cmrt_dd_valid(context) || perm == NULL) { return -EINVAL; }

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	uint32_t val = (uint32_t)otp_esw_perm(perm->sw_otp_perm[0].val);
	sys_write32(val, (mm_reg_t)(R_BASE+R_ESW_PERM_1));
	val = otp_esw_perm_word(perm->sw_otp_perm[0].val);
	sys_write32(val, (mm_reg_t)(R_BASE+R_ESW_PERM_WORD_1));
	val = (uint32_t)otp_esw_perm(perm->sw_otp_perm[1].val);
	sys_write32(val, (mm_reg_t)(R_BASE+R_ESW_PERM_2));
	val = otp_esw_perm_word(perm->sw_otp_perm[1].val);
	sys_write32(val, (mm_reg_t)(R_BASE+R_ESW_PERM_WORD_2));
	sys_write32(perm->slot_perm.val, (mm_reg_t)(R_BASE+R_OTP_SLOT_W));
	cmrt_dd_unlock(dd, mask);
	return 0;
#endif
}

#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
static inline uint32_t oec_status(void)
{
	uint32_t status = sys_read32((mm_reg_t)(CMRT_OEC_BASE+R_OEC_STATUS));
	return status & HWC_STATUS_STATUS_MASK;
}

static inline bool is_oec_ready(void)
{
	uint32_t status = oec_status();
	return (status == HWC_STATUS_AVAILABLE) ||
		(status == HWC_STATUS_SUCCESS);
}

static inline int oec_command(cmrt_omc_t context, uint32_t address)
{
	if (is_oec_ready()) {
		context->last_irq = 0;
		sys_write32(address, (mm_reg_t)(CMRT_OEC_BASE+R_OEC_ADDRESS));
		sys_write32(context->command, (mm_reg_t)(CMRT_OEC_BASE+R_OEC_CONTROL));
		return 0;
	}
	return -EIO;
}
#endif

int z_impl_cmrt_oec_read(cmrt_omc_t context, uint32_t address, void *buffer, size_t buflen)
{
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
	if (!cmrt_dd_valid(context) || buffer == NULL || buflen == 0 ||
	    buflen > OEC_MAX_DATA_BYTES || !is_aligned(buflen, 4u)) {
		return -EINVAL;
	}
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->ddc.sem);
#endif
	context->command = OEC_CONTROL_READ;
	context->buffer = buffer;
	context->buflen = buflen;
	int rv = oec_command(context, address);
	cmrt_dd_unlock(dd, mask);

	return cmrt_dd_autosync(&context->ddc, rv);
#else
	ARG_UNUSED(context); ARG_UNUSED(address);
	ARG_UNUSED(buffer); ARG_UNUSED(buflen);
	return -ENODEV;
#endif
}

int z_impl_cmrt_oec_write(cmrt_omc_t context, uint32_t address, const void *buffer, size_t buflen)
{
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
	if (!cmrt_dd_valid(context) || buffer == NULL || buflen == 0u ||
	    buflen > OEC_MAX_DATA_BYTES || !is_aligned(buflen, 4u)) {
		return -EINVAL;
	}
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->ddc.sem);
#endif
	const uint32_t *words = buffer;
	for (uint32_t i = 0, w = 0; i < buflen; i += 4, w++) {
		sys_write32(words[w], CMRT_OEC_BASE+R_OEC_INPUT+i);
	}
	context->command = OEC_CONTROL_WRITE;
	int rv = oec_command(context, address);
	cmrt_dd_unlock(dd, mask);

	return cmrt_dd_autosync(&context->ddc, rv);
#else
	ARG_UNUSED(context); ARG_UNUSED(address);
	ARG_UNUSED(buffer); ARG_UNUSED(buflen);
	return -ENODEV;
#endif
}

int z_impl_cmrt_oec_commit(cmrt_omc_t context)
{
	if (!cmrt_dd_valid(context)) { return -EINVAL; }
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->ddc.sem);
#endif
	context->command = OEC_CONTROL_COMMIT;
	int rv = oec_command(context, 0);
	cmrt_dd_unlock(dd, mask);

	return cmrt_dd_autosync(&context->ddc, rv);
#else
	ARG_UNUSED(context);
	return 0;
#endif
}

static int omc_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	ARG_UNUSED(ddc);
	ARG_UNUSED(mask);

	/* Check OMC status. */
	if (!is_omc_ready()) {
		return -EIO;
	}
	cmrt_omc_context_t *context = (cmrt_omc_context_t *)ddc;
	if ((context->last_irq & OMC_WRITE_IND_NOK_IRQ) != 0 ||
	    (context->last_irq & OMC_READ_ECC_NOK_IRQ) != 0) {
		/* Error interrupts should be reflected in core status
		 * but in case they are not, we'll fail here. */
		return -EIO;
	}
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
	if (!is_oec_ready()) {
		return -EIO;
	}
	if (context->command == OEC_CONTROL_READ) {
		uint32_t *words = context->buffer;
		for (int i = 0, w = 0; i < context->buflen; i += 4, w++) {
			words[w] = sys_read32((mm_reg_t)(CMRT_OEC_BASE+R_OEC_OUTPUT+i));
		}
		context->buffer = NULL;
		context->buflen = 0;
	}
#endif
	return 0;
}

static int omc_poll_cb(cmrt_dd_context_t *ddc)
{
	ARG_UNUSED(ddc);
	bool rv = omc_status() != HWC_STATUS_BUSY;
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
	rv &= oec_status() != HWC_STATUS_BUSY;
#endif
	return rv ? 0 : 1;
}

#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
static int oec_open_cb(cmrt_dd_context_t *ddc, void *arg)
{
	ARG_UNUSED(ddc);
	ARG_UNUSED(arg);
#ifdef CONFIG_CMRT_FBOOT
	uint32_t aes_status = cmrt_core_status(CMRT_AES_BASE) & HWC_STATUS_STATUS_MASK;
	uint32_t hc_status = cmrt_core_status(CMRT_HC_BASE) & HWC_STATUS_STATUS_MASK;
	if (aes_status != HWC_STATUS_AVAILABLE || hc_status != HWC_STATUS_AVAILABLE) {
	    return -EBUSY;
	}
#endif
	return 0;
}

static void oec_close_cb(cmrt_dd_context_t *ddc)
{
	cmrt_omc_context_t *context = (cmrt_omc_context_t *)ddc;
	if (context->command != 0u) {
		/* OEC was used, flush it here. */
		sys_write32(HWC_CONTROL_FLUSH, (mm_reg_t)(CMRT_OEC_BASE+R_OEC_CONTROL));
	}
}
#endif

#ifdef CONFIG_MULTITHREADING
static void omc_irq_handler(void *arg)
{
	ARG_UNUSED(arg);

	/* Get and clear interrupt, first internal interrupt. */
	uint32_t pending = sys_read32((mm_reg_t)(R_BASE+R_CORE_INTERRUPT));
	sys_write32(pending, (mm_reg_t)(R_BASE+R_CORE_INTERRUPT));

	/* Save the interrupt reason. */
	contexts[0].last_irq |= pending;

	/* Signal for command completion. */
	k_sem_give(&contexts[0].ddc.sem);
}
#endif

static int cmrt_omc_init(const struct device *dev)
{
	cmrt_dd_t *dd = dev->data;
	cmrt_dd_init(dd, dev);

#ifdef CONFIG_MULTITHREADING
	/* Setup IRQ handler for the driver. */
	IRQ_CONNECT(CMRT_OMC_IRQ, 0, omc_irq_handler, NULL, 0);
#endif
	return 0;
}

static cmrt_dd_t omc_dd = {
	.base = CMRT_OMC_BASE,
	.is_locking = 1,
	.context_count = OMC_CONTEXTS,
	.context_size = sizeof(cmrt_omc_context_t),
#ifdef CONFIG_MULTITHREADING
	.irq_mask = OMC_IRQ_MASK,
#else
	.irq_mask = 0,
#endif
	.contexts = &contexts,
};

static const struct cmrt_driver_api omc_driver_api = {
	.find_cb = NULL,
	.poll_cb = omc_poll_cb,
	.sync_cb = omc_sync_cb,
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
	.open_cb = oec_open_cb,
	.close_cb = oec_close_cb,
#endif
};

DEVICE_DT_INST_DEFINE(0, cmrt_omc_init, NULL, &omc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		      (void *)&omc_driver_api);

#ifndef CONFIG_SUPERVISOR_MODE
#define OMC_BOOT_MAX_RETRIES 5000000
static bool omc_wait_shadowing(void)
{
	/*
	 * At boot OMC reports BUSY status until it has parsed some of the OTP
	 * enforced region. This is visible in the SIC.DEVICE_ROOT_TABLE_STATUS
	 * register. Wait while shadowing is in progress.
	 */
	for (int i = 0; i < OMC_BOOT_MAX_RETRIES; i++) {
		uint32_t drts = sys_read32(CMRT_SIC_BASE+R_DEVICE_ROOT_TABLE_STATUS);
		if ((drts & DEVICE_ROOT_TABLE_STATUS_MASK) != 0) {
			return true; /* shadowing done */
		}
		arch_nop();
#ifdef CONFIG_WDT_CMRT
		extern int wdt_cmrt_feed(const struct device *dev, int channel_id);
		if ((i % 1024u) == 0) {
			(void)wdt_cmrt_feed(NULL, 0);
		}
#endif
	}
	return false; /* not finished in time */
}
#endif

uint32_t cmrt_otp_esw_start(void)
{
	uint32_t esw_start = cmrt_read_reg(CMRT_SIC_BASE, R_OTP_ESW_START_REGION);
#ifdef CONFIG_CMRT_OMC_ESW_RSVD_FIRST
	esw_start += CONFIG_CMRT_OMC_ESW_RSVD_WORDS * sizeof(uint32_t);
#endif
	return esw_start;
}

cmrt_omc_t z_impl_cmrt_omc_open(uint32_t flags)
{
#ifndef CONFIG_SUPERVISOR_MODE
	if (!omc_wait_shadowing()) { return NULL; }
#endif
	return (cmrt_omc_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, NULL);
}

void z_impl_cmrt_omc_close(cmrt_omc_t context)
{
	if (cmrt_dd_valid(context)) {
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
		if ((context->ddc.flags & CMRT_O_OTP_COMMIT) != 0u) {
			int rv = cmrt_oec_commit(context);
			if (rv == 0) {
				(void)cmrt_dd_sync((cmrt_dd_context_t *)context);
			}
		}
#endif
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_omc_sync(cmrt_omc_t context)
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

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_omc_context(cmrt_omc_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &omc_driver_api);
}

static inline cmrt_omc_t z_vrfy_cmrt_omc_open(uint32_t flags)
{
	return z_impl_cmrt_omc_open(flags);
}
#include <syscalls/cmrt_omc_open_mrsh.c>

static inline void z_vrfy_cmrt_omc_close(cmrt_omc_t context)
{
	z_syscall_verify_omc_context(context);
	z_impl_cmrt_omc_close(context);
}
#include <syscalls/cmrt_omc_close_mrsh.c>

static inline int z_vrfy_cmrt_omc_read(cmrt_omc_t context, uint32_t offset, void *buffer, size_t buflen)
{
	z_syscall_verify_omc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buffer, buflen));
	return z_impl_cmrt_omc_read(context, offset, buffer, buflen);
}
#include <syscalls/cmrt_omc_read_mrsh.c>

static inline int z_vrfy_cmrt_omc_write(cmrt_omc_t context, uint32_t offset, const void *buffer, size_t buflen)
{
	z_syscall_verify_omc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(buffer, buflen));
	return z_impl_cmrt_omc_write(context, offset, buffer, buflen);
}
#include <syscalls/cmrt_omc_write_mrsh.c>

static inline int z_vrfy_cmrt_omc_obliterate(cmrt_omc_t context, uint32_t offset)
{
	z_syscall_verify_omc_context(context);
	return z_impl_cmrt_omc_obliterate(context, offset);
}
#include <syscalls/cmrt_omc_obliterate_mrsh.c>

static inline int z_vrfy_cmrt_omc_sync(cmrt_omc_t context)
{
	z_syscall_verify_omc_context(context);
	return z_impl_cmrt_omc_sync(context);
}
#include <syscalls/cmrt_omc_sync_mrsh.c>

static inline int z_vrfy_cmrt_oec_read(cmrt_omc_t context, uint32_t address, void *buffer, size_t buflen)
{
	z_syscall_verify_omc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buffer, buflen));
	return z_impl_cmrt_oec_read(context, address, buffer, buflen);
}
#include <syscalls/cmrt_oec_read_mrsh.c>

static inline int z_vrfy_cmrt_oec_write(cmrt_omc_t context, uint32_t address, const void *buffer, size_t buflen)
{
	z_syscall_verify_omc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(buffer, buflen));
	return z_impl_cmrt_oec_write(context, address, buffer, buflen);
}
#include <syscalls/cmrt_oec_write_mrsh.c>

static inline int z_vrfy_cmrt_oec_commit(cmrt_omc_t context)
{
	z_syscall_verify_omc_context(context);
	return z_impl_cmrt_oec_commit(context);
}
#include <syscalls/cmrt_oec_commit_mrsh.c>

#endif /* CONFIG_USERSPACE */
