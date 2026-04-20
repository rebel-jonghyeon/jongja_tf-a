/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

/*
 * Security Monitor System Call implementations
 *
 * These functions run inside security monitor with elevated privileges.
 * Always add new syscalls to the end to preserve compatibility!
 */
#include <errno.h>
#include <string.h>
#include <cmrt_mpu.h>
#include <fboot.h>
#include <syscalls.h>
#include "supervisor.h"
#include "img.h"
#ifdef CONFIG_CMRT_CFI
#include "cfi.h"
#endif
#ifdef CONFIG_CMRT_DATASTORE
#include "datastore.h"
#endif

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

extern char __cmrt_version_head[];

__noinit static cmrt_omc_root_t root_table[CMRT_OTP_NUM_ROOTS + 1];
__noinit static cmrt_omc_root_t *current_root; /* currently active root entry */
__noinit static cmrt_omc_root_t *last_root; /* last activated root */
__noinit static bool silo_mode; /* single container mode */
__noinit static bool perso_mode; /* fboot container mode */

/* Null and dead root for comparisons. */
static const cmrt_omc_root_id_t null_root = {
	.hash = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

/* Downgrade protection words cached from OTP. */
__noinit static uint32_t machine_version;
__noinit static uint32_t supervisor_version;
__noinit static uint32_t user_version;

#define CASSERT1_VERIFY_SIG        (0x3954faf3UL)
#define CASSERT2_VERIFY_SIG        (0xf5cb6918UL)

#define CASSERT1_VERIFY_SIG2       (0x3e77abdaUL)
#define CASSERT2_VERIFY_SIG2       (0xfa6fe49bUL)

#define CASSERT1_VERIFY_PERMS      (0xb4f2d866UL)
#define CASSERT2_VERIFY_PERMS      (0x41e7fc05UL)

#define CASSERT1_CREATE_ROOT       (0xd75b011cUL)
#define CASSERT2_CREATE_ROOT       (0x19f69d76UL)
#define CASSERT1_OBLITERATE_ROOT   (0xd1289b2fUL)
#define CASSERT2_OBLITERATE_ROOT   (0x047ae0caUL)

#define CMIX_BITMAP_IS_SUBSET_OF   (0xca293013UL)
#define CMIX_RANGE_IS_SUBSET_OF    (0x546646f3UL)
#define CMIX_CAN_CREATE_ROOT       (0x27a5099fUL)
#define CMIX_CAN_OBLITERATE_ROOT   (0x857d389fUL)

/*
 * Utility functions.
 */
void set_perso_root(const cmrt_omc_root_t *root)
{
	cmrt_omc_root_t *perso_root = &root_table[CMRT_OTP_NUM_ROOTS];
	if (root != NULL) {
		(void)memcpy(perso_root, root, sizeof(cmrt_omc_root_t));
	} else {
		(void)memset(perso_root, 0, sizeof(cmrt_omc_root_t));
	}
	perso_mode = true;
}

static cmrt_omc_root_t *find_root(const cmrt_omc_root_id_t *id)
{
	for (int i = 0; i <= CMRT_OTP_NUM_ROOTS; i++) {
		if (fboot_memmatch(NULL, &root_table[i].id, id, sizeof(cmrt_omc_root_id_t))) {
			return &root_table[i];
		}
	}
	return NULL;
}

#ifdef CONFIG_CMRT_DATASTORE
static int root_index(const cmrt_omc_root_t *root)
{
	for (int i = 0; i <= CMRT_OTP_NUM_ROOTS; i++) {
		if (root == &root_table[i]) {
			return i;
		}
	}
	return 0;
}

static int current_root_index(void)
{
	if (current_root == NULL && has_supervisor()) {
		/* Non-silo supervisors can take this path. */
		return root_index(find_root(supervisor_root()));
	}
	return root_index(current_root);
}
#endif

/* p2 is not allowed to have any bits up that p1 does not have. */
static bool bitmap_is_subset_of(cmrt_cc_t cc, uint32_t p1, uint32_t p2)
{
	if ((p1 | p2) == p1) {
		(void)cmrt_cc_mix(cc, CMIX_BITMAP_IS_SUBSET_OF);
		return true;
	}
	return false;
}

/* Verify i2 is within i1 or i0 boundaries. */
#define LOWER_MASK OMC_SW_OTP_PERM_LOWER_MASK
#define UPPER_MASK OMC_SW_OTP_PERM_UPPER_MASK
static bool range_is_subset_of(cmrt_cc_t cc, uint32_t i0, uint32_t i1, uint32_t i2)
{
	uint32_t low0 = i0 & LOWER_MASK;
	uint32_t hi0  = (i0 & UPPER_MASK) >> 16;
	uint32_t rw0  = i0 & OMC_SW_OTP_PERM_RW;
	uint32_t low1 = i1 & LOWER_MASK;
	uint32_t hi1  = (i1 & UPPER_MASK) >> 16;
	uint32_t rw1  = i1 & OMC_SW_OTP_PERM_RW;
	uint32_t low2 = i2 & LOWER_MASK;
	uint32_t hi2  = (i2 & UPPER_MASK) >> 16;
	uint32_t rw2  = i2 & OMC_SW_OTP_PERM_RW;

	if (low2 > hi2 || low1 > hi1 || low0 > hi0) { return false; }

	if (((low0 <= low2) && (hi0 >= hi2) && ((rw0 | rw2) == rw0)) ||
	    ((low1 <= low2) && (hi1 >= hi2) && ((rw1 | rw2) == rw1))) {
		(void)cmrt_cc_mix(cc, CMIX_RANGE_IS_SUBSET_OF);
		return true;
	}
	return false;
}

static inline bool is_machine(void)
{
	/* Check previous privilege to see if functions here were called
	 * by a machine mode program (fboot, sboot, tboot, blank perso),
	 * or by a lower privilege program (supervisor) via system call. */
	ulong_t mstatus = csr_read(mstatus);
	if ((mstatus & MSTATUS_MPP_M) == 0 ||
	    (mstatus & MSTATUS_MPP_M) == MSTATUS_MPP_M) {
		return true;
	}
	return false;
}

static bool mpu_has_access(const void *address, size_t size, uint32_t mpu_mode)
{
	uint32_t privilege = is_machine() ? MPU_PRIVILEGE_M :
		has_supervisor() ? MPU_PRIVILEGE_S : MPU_PRIVILEGE_M;
	return cmrt_mpu_has_access((uintptr_t)address, size, privilege, mpu_mode);
}

/*
 * Verify child permissions to be a subset of the parents permissions.
 *
 * - parent must have a permission range(s) spanning over the ranges
 *   requested by child
 * - child cannot have capability bits set that the parent does not hold
 */
static int subset_permissions(cmrt_cc_t cc,
			      const cmrt_omc_root_perm_t *parent,
			      const cmrt_omc_root_perm_t *child)
{
	if (!bitmap_is_subset_of(cc, parent->slot_perm.val, child->slot_perm.val)) { return -EPERM; }
	if (!bitmap_is_subset_of(cc, parent->key_perm.val, child->key_perm.val)) { return -EPERM; }
	if (!bitmap_is_subset_of(cc, parent->feature_perm.val, child->feature_perm.val)) { return -EPERM; }
	if (!range_is_subset_of(cc, parent->sw_otp_perm[0].val, parent->sw_otp_perm[1].val, child->sw_otp_perm[0].val)) { return -EPERM; }
	if (!range_is_subset_of(cc, parent->sw_otp_perm[0].val, parent->sw_otp_perm[1].val, child->sw_otp_perm[1].val)) { return -EPERM; }
	if (!bitmap_is_subset_of(cc, parent->software_perm.val, child->software_perm.val)) { return -EPERM; }
	return 0;
}

/* Burn root, parameters are already checked.
 * If root is not null, write root; otherwise obliterate root.
 */
static int burn_root(cmrt_omc_t omc, int index, const cmrt_omc_root_t *root)
{
	if (root != NULL) {
		int res = cmrt_omc_write(omc, OTP_ROOT_OFFSET(index), root, sizeof(*root));
		if (res) { return res; }
		(void)memcpy(&root_table[index], root, sizeof(*root));
	} else {
		int res = cmrt_omc_obliterate(omc, OTP_ROOT_OFFSET(index));
		if (res) { return res; }
		(void)memset(&root_table[index], 0x00, sizeof(*root));
	}
	return 0;
}

/*
 * Ranges are set from the beginning of the ESW region but HW takes them from
 * the beginning of the OTP. Add ESW start value to both lower and upper.
 */
static uint32_t fix_perm_range(uint32_t value)
{
	uint32_t esw_start = cmrt_read_reg(CMRT_SIC_BASE, R_OTP_ESW_START_REGION);

	uint32_t low = value & LOWER_MASK;
	low += esw_start;
	if (low > LOWER_MASK) { low = LOWER_MASK; }
	value = (value & ~LOWER_MASK) | low;

	uint32_t high = value & UPPER_MASK;
	high += esw_start << 16;
	if (high > UPPER_MASK) { high = UPPER_MASK; }
	value = (value & ~UPPER_MASK) | high;

	return value;
}

void fboot_init_sm(cmrt_omc_t omc)
{
	/* Cache the root table, we have fboot permissions here. */
	uint32_t status = cmrt_read_reg(CMRT_SIC_BASE, R_DEVICE_ROOT_TABLE_STATUS);
	if ((status & DEVICE_ROOT_TABLE_STATUS_MASK) != DEVICE_ROOT_TABLE_STATUS_VALID) {
		/* HW OTP parsing has failed. */
		halt(-ENOEXEC, -EBADF, "Invalid root table status: 0x%08x", status);
	}
	for (uint32_t i = 0; i < CMRT_OTP_NUM_ROOTS; i++) {
		uint32_t root_status = (status >> (i * 2)) & ROOT_TABLE_STATUS_MASK;
		if (root_status != ROOT_TABLE_STATUS_VALID) {
			/* Root is not burned or has been obliterated. */
			(void)memset(&root_table[i], 0x00, sizeof(cmrt_omc_root_t));
			continue;
		}
		int res = cmrt_omc_read(omc, OTP_ROOT_OFFSET(i), &root_table[i], sizeof(cmrt_omc_root_t));
		if (res == -EIO) {
			/* ECC error in reading, clear this entry. */
			(void)memset(&root_table[i], 0x00, sizeof(cmrt_omc_root_t));
		} else if (res != 0) {
			/* Any other error is fatal. */
			halt(-ENOEXEC, res, "Failed to read root %d: %d", i, res);
		}
	}
	/* Cache the version words, we have fboot permissions here. */
	/* coverity[OVERRUN] */
	int res = cmrt_omc_read(omc, OTP_MACHINE_VERSION_OFFSET, &machine_version, sizeof(machine_version));
	if (res != 0) { halt(-ENOEXEC, res, "Failed to read version word at %d: %d", OTP_MACHINE_VERSION_OFFSET, res); }
	/* coverity[OVERRUN] */
	res = cmrt_omc_read(omc, OTP_SUPERVISOR_VERSION_OFFSET, &supervisor_version, sizeof(supervisor_version));
	if (res != 0) { halt(-ENOEXEC, res, "Failed to read version word at %d: %d", OTP_SUPERVISOR_VERSION_OFFSET, res); }
	/* coverity[OVERRUN] */
	res = cmrt_omc_read(omc, OTP_USER_VERSION_OFFSET, &user_version, sizeof(user_version));
	if (res != 0) { halt(-ENOEXEC, res, "Failed to read version word at %d: %d", OTP_USER_VERSION_OFFSET, res); }

#ifdef CONFIG_CMRT_DATASTORE
	/* Initialize data store. */
	data_store_init();
#endif
}

/* Setup HW security context */
void set_derive_path(const cmrt_omc_root_id_t *id, uint8_t silo)
{
#ifdef CONFIG_CMRT_PMU
	if (id == NULL) {
		if (current_root == NULL) { return; }
		/* Setting derive path in boot bypass for current root. */
		id = &current_root->id;
		silo = silo_mode;
	}
#endif
	LOG_INF("Set derive path for root %lx...", __builtin_bswap32(*(uint32_t *)id));
	/* Set KDC permissions and derive path. */
	cmrt_kdc_t kdc = cmrt_kdc_open(0);
	if (!cmrt_is_valid(kdc)) { halt(-ENOEXEC, -ENODEV, "no KDC"); }
	cmrt_kdc_drv_path_t drv_path;
	(void)memset(&drv_path, 0, sizeof(drv_path));
	/* First 32 bytes are container id */
	(void)memcpy((uint8_t *)&drv_path, (const uint8_t *)id, sizeof(cmrt_omc_root_id_t));
	uint8_t *silop = (uint8_t *)&drv_path;
	/* The 33rd byte is silo */
	silop[32] = silo;
	int res = cmrt_kdc_set_derive_path(kdc, &drv_path);
	cmrt_kdc_close(kdc);
	if (res != 0) { halt(-ENOEXEC, res, "Failed to set KDC permissions: %d", res); }
}

void set_root_permissions(cmrt_omc_t omc, const cmrt_omc_root_perm_t *perm, bool valid)
{
#ifdef CONFIG_CMRT_PMU
	if (valid && perm == NULL) {
		if (current_root == NULL) { return; }
		/* Setting permissions in boot bypass for current root. */
		perm = &current_root->perm;
	}
#endif
	LOG_INF("Set HW permissions");
	/* Set OMC permissions for the new root. */
	omc_perm_t omc_perm;
	omc_perm.sw_otp_perm[0].val = fix_perm_range(perm->sw_otp_perm[0].val);
	omc_perm.sw_otp_perm[1].val = fix_perm_range(perm->sw_otp_perm[1].val);
	omc_perm.slot_perm.val = perm->slot_perm.val;
	int res = cmrt_omc_permissions(omc, &omc_perm);
	if (res != 0) { halt(-ENOEXEC, res, "Failed to set OMC permissions: %d", res); }

	/* Set FMC permissions for the new root. */
	cmrt_fmc_t fmc = cmrt_fmc_open();
	if (!cmrt_is_valid(fmc)) { halt(-ENOEXEC, -ENODEV, "no FMC"); }
	res = cmrt_fmc_permissions(fmc, perm->feature_perm.val);
	cmrt_fmc_close(fmc);
	if (res != 0) { halt(-ENOEXEC, res, "Failed to set FMC permissions: %d", res); }

	/* Set KTC permissions */
	cmrt_ktc_t ktc = cmrt_ktc_open(0, 0);
	if (!cmrt_is_valid(ktc)) { halt(-ENOEXEC, -ENODEV, "no KTC"); }
	res = cmrt_ktc_permissions(ktc, &perm->key_perm);
	cmrt_ktc_close(ktc);
	if (res != 0) { halt(-ENOEXEC, res, "Failed to set KTC permissions: %d", res); }

	/* Set KDC permissions and derive path. */
	cmrt_kdc_t kdc = cmrt_kdc_open(0);
	if (!cmrt_is_valid(kdc)) { halt(-ENOEXEC, -ENODEV, "no KDC"); }
	res = cmrt_kdc_permissions(kdc, &perm->key_perm);
	cmrt_kdc_close(kdc);
	if (res != 0) { halt(-ENOEXEC, res, "Failed to set KDC permissions: %d", res); }

	if (valid) {
		if (current_root == NULL) {
			/* Set current root as valid. */
			current_root = last_root;
			if (&current_root->perm != perm) {
				/* Update cached root permissions,
				 * silo image may have reduced set of
				 * permissions in its footer. */
				memcpy(&current_root->perm, perm, sizeof(*perm));
			}
		}
	} else {
		/* Initialize variables. */
		last_root = NULL;
		current_root = NULL;
		silo_mode = false;
		perso_mode = false;
	}
}

/* Root index starts from zero for these functions. */
static bool can_create_root(cmrt_cc_t cc, const cmrt_omc_root_t *root, uint32_t index)
{
#define ROOT_CREATE_BITS 16u /* first bit to create root in OMC SLOT_PERMS */
	if ((root->perm.slot_perm.val & (1UL << (index + ROOT_CREATE_BITS))) != 0u) {
		(void)cmrt_cc_mix(cc, CMIX_CAN_CREATE_ROOT);
		return true;
	}
	return false;
}

static bool can_obliterate_root(cmrt_cc_t cc, const cmrt_omc_root_t *root, uint32_t index)
{
#define ROOT_OBLITERATE_BITS 24u /* first bit to obliterate root in OMC SLOT_PERMS */
	if ((root->perm.slot_perm.val & (1UL << (index + ROOT_OBLITERATE_BITS))) != 0u) {
		(void)cmrt_cc_mix(cc, CMIX_CAN_OBLITERATE_ROOT);
		return true;
	}
	return false;
}

/* System call to create new root. */
int fboot_create_root(int index, const cmrt_omc_root_t *new_root)
{
	if (new_root == NULL || !is_aligned(new_root, 4u) ||
	    index < 0 || index >= CMRT_OTP_NUM_ROOTS) {
		return -EINVAL;
	}

	if (!(silo_mode || current_root != NULL)) { return -EPERM; }

	/* Verify memory access */
	if (!mpu_has_access(new_root, sizeof(*new_root), MPU_MODE_READABLE)) {
		return -EACCES;
	}
	/* Check root table status register. */
	uint32_t status = cmrt_read_reg(CMRT_SIC_BASE, R_DEVICE_ROOT_TABLE_STATUS);
	bool status_valid = (status & DEVICE_ROOT_TABLE_STATUS_MASK) == DEVICE_ROOT_TABLE_STATUS_VALID;
	uint32_t root_status = (status >> ((uint32_t)index * 2)) & ROOT_TABLE_STATUS_MASK;
	if (status_valid && (root_status != ROOT_TABLE_STATUS_EMPTY)) {
		return -EEXIST;
	}
	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC | CMRT_O_OTP_COMMIT);
	if (!cmrt_is_valid(omc)) { return -ENODEV; }

	int res = -ENODEV;
	cmrt_cc_t cc = cmrt_cc_open();
	if (!cmrt_is_valid(cc)) { goto out; }
	res = cmrt_cc_assert(cc, CASSERT1_CREATE_ROOT, CASSERT2_CREATE_ROOT);

	/* Verify that the root is null and does not exist already. */
	res = -EEXIST;
	if (find_root(&new_root->id) != NULL) { goto out; }
	if (!fboot_memmatch(cc, root_table[index].id.hash, null_root.hash,
			    sizeof(cmrt_omc_root_id_t))) { goto out; }

	/* Verify if the current root is allowed to touch this index. */
	res = -EPERM;
	if (!can_create_root(cc, current_root, (uint32_t)index)) { goto out; }

	/* Verify container has the permissions to create such root. */
	const cmrt_omc_root_perm_t *perm = &current_root->perm;
	res = subset_permissions(cc, perm, &new_root->perm);
	if (res != 0) { goto out; }

	res = cmrt_cc_sync(cc);
	if (res != 0) { goto out; }

	/* Ok, burn and then verify this indeed happened. */
	res = burn_root(omc, index, new_root);
	if (res != 0) { goto out; }
	const cmrt_otp_layout_t *otp = cmrt_otp_layout(0);
	if (!fboot_memmatch(NULL, otp->roots[index].id.hash, new_root->id.hash,
			    sizeof(cmrt_omc_root_id_t))) {
		res = -EIO;
	}
 out:
	if (cc != NULL) { cmrt_cc_close(cc); }
	cmrt_omc_close(omc);
	return res;
}

int fboot_obliterate_root(int index)
{
	if ((index < 0) || (index >= CMRT_OTP_NUM_ROOTS)) { return -EINVAL; }

	if (!(silo_mode || current_root != NULL)) { return -EPERM; }

	/* Check root table status register. */
	uint32_t status = cmrt_read_reg(CMRT_SIC_BASE, R_DEVICE_ROOT_TABLE_STATUS);
	bool status_valid = (status & DEVICE_ROOT_TABLE_STATUS_MASK) == DEVICE_ROOT_TABLE_STATUS_VALID;
	uint32_t root_status = (status >> ((uint32_t)index * 2)) & ROOT_TABLE_STATUS_MASK;
	if (status_valid && (root_status != ROOT_TABLE_STATUS_VALID)) {
		return -EINVAL;
	}
	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC | CMRT_O_OTP_COMMIT);
	if (!cmrt_is_valid(omc)) { return -ENODEV; }

	int res = -ENODEV;
	cmrt_cc_t cc = cmrt_cc_open();
	if (!cmrt_is_valid(cc)) { goto out; }
	res = cmrt_cc_assert(cc, CASSERT1_OBLITERATE_ROOT, CASSERT2_OBLITERATE_ROOT);

	/* Verify that the root is not null. */
	res = -EINVAL;
	if (fboot_memmatch(NULL, root_table[index].id.hash, null_root.hash,
			   sizeof(cmrt_omc_root_id_t))) { goto out; }

	/* Verify if the current root is allowed to touch this index. */
	res = -EPERM;
	if (!can_obliterate_root(cc, current_root, (uint32_t)index)) { goto out; }

	res = cmrt_cc_sync(cc);
	if (res != 0) { goto out; }

	/* Ok, kill the root. */
	res = burn_root(omc, index, NULL);
 out:
	if (cc != NULL) { cmrt_cc_close(cc); }
	cmrt_omc_close(omc);
	return res;
}

static int verify_image(const cmrt_img_footer_t *footer, void *blob, size_t size)
{
	cmrt_cc_t cc = cmrt_cc_open();
	if (!cmrt_is_valid(cc)) { return -ENODEV; }

	int res = current_root != NULL ?
		cmrt_cc_assert(cc, CASSERT1_VERIFY_SIG, CASSERT2_VERIFY_SIG) :
		cmrt_cc_assert(cc, CASSERT1_VERIFY_SIG2, CASSERT2_VERIFY_SIG2);
	if (res != 0) { goto out; }

	cmrt_omc_root_t *root = find_root(&footer->scid.cid.root);
	if (root == NULL) {
		LOG_INF("Cannot find root for image %p", blob);
		res = -EPERM;
		goto out;
	}
	if (current_root != NULL && current_root != root) {
		LOG_INF("Need to switch roots");
		res = -EBUSY;
		goto out;
	}
	/* Verify signature against current root (or NULL). */
	res = fboot_verify_sig(cc, blob, size, current_root != NULL ?
			       current_root->id.hash : NULL, footer);
	if (res != 0) {
		LOG_INF("Failed to verify image signature: %d", res);
		goto out;
	}

	uint32_t load_permission = 0;
	uint32_t otp_version = has_supervisor() ? user_version : supervisor_version;
	switch (footer->scid.cid.handling_caveats) {
	case CAVEAT_NONE:
		load_permission = has_supervisor() ?
			OMC_SW_PERM_CONTAINER : OMC_SW_PERM_SUPERVISOR;
		break;
	case CAVEAT_SILO:
		load_permission = has_supervisor() ?
			OMC_SW_PERM_SILO_CONTAINER : perso_mode ?
			OMC_SW_PERM_FBOOT_CONTAINER : OMC_SW_PERM_SILO_SUPERVISOR;
		if (current_root != NULL) {
			/* Cannot start silo container as supervisor state is
			 * not clean because another container(s) have run. */
			LOG_INF("Cannot start silo image");
			res = -EBUSY;
			goto out;
		}
		break;
	case CAVEAT_BOOT: /* for optional tboot */
		load_permission = OMC_SW_PERM_TBOOT;
		if (has_supervisor() || has_tboot()) {
			LOG_INF("Only one tboot allowed");
			res = -EFAULT;
			goto out;
		}
		otp_version = machine_version;
		break;
	default:
		LOG_INF("Invalid handling caveat: %u",
		      footer->scid.cid.handling_caveats);
		res = -EINVAL;
		goto out;
	}

	/* Verify permission to load the image. */
	if ((load_permission & root->perm.software_perm.val &
	     footer->permissions.software_perm.val) == 0) {
		LOG_INF("No permission to load image type 0x%x 0x%x 0x%x",
			load_permission, root->perm.software_perm.val,
			footer->permissions.software_perm.val);
		res = -EPERM;
		goto out;
	}
	/* Verify footer version against minimum allowed version. */
	if (footer->container_version < otp_version) {
		LOG_INF("Image version 0x%x < OTP version 0x%x",
			footer->container_version, otp_version);
		res = -ESPIPE;
		goto out;
	}

	res = cmrt_cc_sync(cc);
	last_root = root;
out:
	cmrt_cc_close(cc);
	return res;
}

static inline void remove_write_perm(uint32_t *val)
{
	*val &= (*val & OMC_SW_OTP_PERM_R) != 0 ? ~OMC_SW_OTP_PERM_W : 0;
}

static int verify_permissions(const cmrt_img_footer_t *footer)
{
	cmrt_cc_t cc = cmrt_cc_open();
	if (!cmrt_is_valid(cc)) { return -ENODEV; }

	int res = cmrt_cc_assert(cc, CASSERT1_VERIFY_PERMS, CASSERT2_VERIFY_PERMS);
	if (res != 0) { goto out; }

	if (current_root == NULL) {
		if (has_supervisor() &&
		    !(footer->scid.cid.handling_caveats == CAVEAT_SILO)) {
			/* Remove silo-only permissions from cached root. */
			last_root->perm.slot_perm.val = 0;
			remove_write_perm(&last_root->perm.sw_otp_perm[0].val);
			remove_write_perm(&last_root->perm.sw_otp_perm[1].val);
		}
	}
	/* Verify container permissions against the root. */
	res = subset_permissions(cc, &last_root->perm, &footer->permissions);
	if (res != 0) {
		LOG_INF("Image permissions are illegal");
		goto out;
	}
	res = cmrt_cc_sync(cc);
out:
	cmrt_cc_close(cc);
	return res;
}

static int apply_permissions(const cmrt_img_footer_t *footer)
{
	if (has_supervisor()) {
		if (footer->scid.cid.handling_caveats == CAVEAT_SILO) {
			/* Set silo mode based on loaded user container. */
			silo_mode = true;
		}
		if (current_root == NULL) {
			/* Apply permissions for non-silo supervisor. */
			cmrt_omc_t omc = cmrt_omc_open(0);
			if (!cmrt_is_valid(omc)) { return -ENODEV; }
			const cmrt_omc_root_perm_t *perms = silo_mode ?
				&footer->permissions : &last_root->perm;
			set_root_permissions(omc, perms, true);
			set_derive_path(&last_root->id,
					silo_mode ? CAVEAT_SILO : CAVEAT_NONE);
			cmrt_omc_close(omc);
		}
	} else {
		/* Set derive path based on the image root. */
		uint8_t silo = footer->scid.cid.handling_caveats != CAVEAT_NONE ? CAVEAT_SILO : CAVEAT_NONE;
		set_derive_path(&footer->scid.cid.root, silo);
	}
	return 0;
}

static int decrypt_image(const cmrt_img_footer_t *footer, void *blob, size_t size)
{
	cmrt_encryption_data_t *ed = footer->encryption_data;
#ifdef CONFIG_CMRT_ENCRYPTED_IMAGE_SUPPORT
	if (ed == NULL) {
		/* Not encrypted, this is ok. */
		return 0;
	}
	uint32_t flags = ed->key_src == CMRT_IMAGE_KEY_SRC_KDC ? CMRT_O_HWC_KEYED : 0;
	cmrt_aes_t aes = cmrt_aes_open(flags);
	if (!cmrt_is_valid(aes)) {
		return -ENODEV;
	}
	int res = 0;
	void *key = NULL;
	uint8_t ds_key[KDC_KEY_SIZE];
	size_t keylen = sizeof(ds_key);
	if (ed->key_src == CMRT_IMAGE_KEY_SRC_DS) {
#ifdef CONFIG_CMRT_DATASTORE
		size_t ds_size = sizeof(ds_key);
		int index = current_root_index();
		uint32_t required = is_machine() ? 0 : DS_S_EXECUTE;
		res = data_store_read("CMRT_IMAGE_KEY_SRC_DS", sizeof("CMRT_IMAGE_KEY_SRC_DS") - 1, ds_key, &ds_size, required, index);
		if (res != 0 || ds_size != sizeof(ds_key)) {
			LOG_INF("Cannot read CMRT_IMAGE_KEY_SRC_DS: %d", res);
			goto out;
		}
		key = ds_key;
#else
		res = -ENOTSUP;
		goto out;
#endif
	} else { /* CMRT_IMAGE_KEY_SRC_KDC */
		cmrt_kdc_cmd_t cmd;
		(void)memset(&cmd, 0, sizeof(cmd));
#ifdef CONFIG_CMRT_EXPAND_DIVERSIFY_PATH
		/* Use full size (16 bytes) diversify path */
		cmd.diversify_len = 16;
		/* And the 16th byte is silo. */
		uint8_t *silop = (uint8_t *)cmd.diversify_path;
		silop[15] = footer->scid.cid.handling_caveats != CAVEAT_NONE ? 0x01 : 0x00;
#else
		cmd.diversify_len = sizeof(ed->diversify_path);
#endif
		(void)memcpy(cmd.diversify_path, &ed->diversify_path, sizeof(ed->diversify_path));
		cmd.base_key_id = ed->keysplit_id;
		res = cmrt_aes_kdc_cmd(aes, AES_DECRYPT, AES_GCM, KDC_KEY_SIZE, sizeof(ed->tag), &cmd);
		if (res != 0) {
			LOG_INF("Failed to setup AES key generation: %d", res);
			goto out;
		}
		cmrt_kdc_t kdc = cmrt_kdc_open(CMRT_O_SYNC);
		if (cmrt_is_valid(kdc)) {
			res = cmrt_kdc_derive_key(kdc, &cmd);
			cmrt_kdc_close(kdc);
		} else {
			res = -ENODEV;
		}
		if (res != 0) {
			LOG_INF("Failed to derive key for AES: %d", res);
			goto out;
		}
		keylen = 0; /* KDC derived */
	}
	res = cmrt_aes_init(aes, AES_DECRYPT, AES_GCM, key, keylen,
			   ed->iv, sizeof(ed->iv), sizeof(ed->tag));
	if (res != 0) {
		LOG_INF("AES init failed: %d", res);
		goto out;
	}
	res = cmrt_aes_final_aad(aes, NULL, 0);
	if (res != 0) {
		LOG_INF("AES AAD final failed: %d", res);
		goto out;
	}
	size_t taglen = sizeof(ed->tag);
	res = cmrt_aes_ae_final(aes, blob, size, blob, ed->tag, &taglen);
	if (res != 0) {
		LOG_INF("AES AE final failed: %d", res);
		goto out;
	}
	LOG_INF("Decrypted %d bytes.", size);
 out:
	cmrt_aes_close(aes);
	return res;
#else
	ARG_UNUSED(blob);
	ARG_UNUSED(size);
	/* No decryption support. */
	return (ed == NULL) ? 0 : -EFAULT;
#endif
}

int fboot_load_image(void *blob, size_t size, cmrt_raw_footer_t *raw, cmrt_usr_footer_t *usr)
{
	if (blob == NULL || !is_aligned(blob, 4u) || size == 0u ||
	    raw == NULL || !is_aligned(raw, 4u) ||
	    ((uintptr_t)raw >= (uintptr_t)blob &&
	     (uintptr_t)raw < ((uintptr_t)blob + size))) {
		return -EINVAL;
	}
	if (has_supervisor() &&
	    (usr == NULL || !is_aligned(usr, 4u) ||
	     ((uintptr_t)usr >= (uintptr_t)blob &&
	      (uintptr_t)usr < ((uintptr_t)blob + size)))) {
		return -EINVAL;
	}
	LOG_INF("Load image at %p size %d", blob, size);

	if (silo_mode) {
		/* A silo container has been loaded; now no container
		 * can be loaded, until reset is done. */
		LOG_INF("Will not start image %p", blob);
		return -EBUSY;
	}

	/* Verify memory access */
	uint32_t mpu_mode = MPU_MODE_READABLE | MPU_MODE_WRITABLE;
#ifdef CONFIG_CMRT_SUPERVISOR_IN_ROM
	if (IS_IN_ROM((uint32_t)blob) && IS_IN_ROM((uint32_t)blob + size)) {
	    mpu_mode &= ~MPU_MODE_WRITABLE;
	}
#endif
	if (!mpu_has_access(blob, size, mpu_mode)) {
		LOG_INF("No access to image");
		return -EACCES;
	}
	if (!mpu_has_access(raw, sizeof(*raw), MPU_MODE_READABLE | MPU_MODE_WRITABLE)) {
		LOG_INF("No access to raw footer");
		return -EACCES;
	}
	if (has_supervisor() && !mpu_has_access(usr, sizeof(*usr), MPU_MODE_READABLE | MPU_MODE_WRITABLE)) {
		LOG_INF("No access to usr footer");
		return -EACCES;
	}
	cmrt_img_footer_t footer;
	int res = cmrt_img_footer_parse(blob, size, &footer);
	if (res < 0) {
		LOG_INF("Failed to parse image footer: %d", res);
		return res;
	}
	int left = size - res;
	res = verify_image(&footer, blob, size);
	if (res == 0) { res = verify_permissions(&footer); }
	if (res == 0) { res = apply_permissions(&footer); }
	if (res != 0) { return res; }

	res = decrypt_image(&footer, blob, left);
	if (res != 0) { return res; }

	res = cmrt_raw_footer_parse(blob, left, has_supervisor(), raw);
	if (res < 0) { return res; }
	left -= res;

	if (has_supervisor()) {
		res = cmrt_usr_footer_parse(blob, left, raw, usr);
		if (res < 0) { return res; }
		left -= res;
	}
#ifdef CONFIG_CMRT_CFI
	res = cmrt_cfi_load_metadata(blob, left, raw);
	if (res != 0) { return res; }
#endif
	if (has_supervisor()) {
		/* Loaded user container. */
		cmrt_raw_image_init(raw);
	} else {
		/* Loaded either tboot or supervisor. */
		supervisor_update(size, &footer, raw);
	}
	LOG_INF("Image load OK.");
	return footer.scid.cid.handling_caveats;
}

int fboot_halt(int major, int minor)
{
	LOG_INF("Halt for reason %d:%d", -minor, -major);
	cmrt_eac_halt(CORE_ID_CPU, major, minor);

	return 0; /* keep compiler happy */
}

int fboot_reboot(void)
{
	cmrt_eac_reboot();

	return 0; /* keep compiler happy */
}

int fboot_reset(uint32_t info)
{
	LOG_INF("Reset with info 0x%x", info);
#if IS_ENABLED(CMRT_SIC_BOOT_CONTROL)
	/* Write dedicated boot control register. */
	cmrt_write_reg(CMRT_SIC_BASE, R_BOOT_CONTROL, info);
#else
	/* Set soft reset flags to boot bypass registers. */
	cmrt_write_reg(CMRT_SIC_BASE, R_BOOT_BYPASS_STATUS, BOOT_BYPASS_ALLOWED | IN_MPU_RESET);
	cmrt_write_reg(CMRT_SIC_BASE, R_BOOT_BYPASS_VECTOR, info);

	/* Do the reset with CCC. */
	cmrt_clear_container_context();
#endif
	cmrt_eac_reset();

	return 0; /* keep compiler happy */
}

/* PMU driver updates this in cmrt_pmu_restore_os. Always zero if no PMU. */
int cmrt_pmu_events; /* start from zero after any reset */

int fboot_reset_info(uint32_t *info)
{
	if (info != NULL) {
		if (!is_aligned(info, 4u)) { return -EINVAL; }

		if (!mpu_has_access(info, sizeof(uint32_t), MPU_MODE_READABLE | MPU_MODE_WRITABLE)) {
			return -EACCES;
		}
#if IS_ENABLED(CMRT_SIC_BOOT_CONTROL)
		*info = cmrt_read_reg(CMRT_SIC_BASE, R_BOOT_CONTROL);
#else
		uint32_t reg = cmrt_read_reg(CMRT_SIC_BASE, R_BOOT_BYPASS_STATUS);
		*info = (reg == (BOOT_BYPASS_ALLOWED | IN_MPU_RESET)) ?
			cmrt_read_reg(CMRT_SIC_BASE, R_BOOT_BYPASS_VECTOR) : 0;
#endif
	}
	return cmrt_pmu_events;
}

static int otp_version_helper(uint32_t offset, uint32_t *version, bool is_set)
{
	uint32_t *cached_version;
	switch (offset) {
	case OTP_MACHINE_VERSION_OFFSET:
		cached_version = &machine_version;
		break;
	case OTP_SUPERVISOR_VERSION_OFFSET:
		cached_version = &supervisor_version;
		break;
	case OTP_USER_VERSION_OFFSET:
		cached_version = &user_version;
		break;
	default:
		return -EINVAL;
	}
	int res = 0;
	if (is_set) {
		cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC | CMRT_O_OTP_COMMIT);
		if (!cmrt_is_valid(omc)) {
			return -ENODEV;
		}
		res = cmrt_omc_write(omc, offset, version, sizeof(*version));
		cmrt_omc_close(omc);
		if (res == 0) {
			/* Update cached version. */
			*cached_version = *version;
		}
	} else {
		/* Return version to caller. */
		*version = *cached_version;
	}
	return res;
}

static int parse_version_field(uint32_t head, size_t *offset, size_t *size)
{
	union version_field_head {
		struct {
			uint8_t magic;
			uint8_t unused;
			uint8_t sz_words;
			uint8_t offset_words; /* Offset to data from end of this header. */
		} fields;
		uint32_t value;
	} h = { .value = head };

	if (h.fields.magic != 0x43u)  {
		return -ENOENT;
	}
	size_t len = sizeof(uint32_t) * h.fields.sz_words;
	int res = (len > *size) ? -ENOSPC : 0;
	*size = len;
	*offset = sizeof(uint32_t) * (h.fields.offset_words + 1); /* Including head itself. */
	return res;
}

static int binary_version_helper(uint32_t const *head, void *version, size_t *size)
{
	if ((head == NULL) || (version == NULL) || (size == NULL)) {
		return -EINVAL;
	}
	uint32_t offset;
	int res = parse_version_field(*(uint32_t *)head, &offset, size);
	if (res != 0) {
		return res;
	}
	(void)memcpy(version, (const void *)&head[offset>>2], *size);
	return 0;
}

static int sboot_version_helper(void *version, size_t *size)
{
#ifdef CONFIG_CMRT_SBOOT_IN_ROM
	uint32_t const *head = (uint32_t const *)(RISCV_ROM_BASE + sizeof(cmrt_img_header_t));
	return binary_version_helper(head, version, size);
#else
	cmrt_omc_t omc = cmrt_omc_open(0);
	if (!cmrt_is_valid(omc)) {
		return -ENODEV;
	}
	/* Read version field header. */
	uint32_t otp_offset = cmrt_otp_esw_start();
	otp_offset += sizeof(cmrt_img_header_t);
	uint32_t head;
	int res = cmrt_omc_read(omc, otp_offset, &head, sizeof(head));
	uint32_t version_offset;
	if (res == 0) {
		/* Find size and offset of version data. */
		res = parse_version_field(head, &version_offset, size);
	}
	if (res == 0) {
		/* Read version data. */
		otp_offset += version_offset;
		res = cmrt_omc_read(omc, otp_offset, version, *size);
	}
	cmrt_omc_close(omc);
	return res;
#endif
}

int fboot_get_image_version(enum cmrt_image_version_id image, void *version, size_t *size)
{
	if (version == NULL || !is_aligned(version, 4u) ||
	    size == NULL || !is_aligned(size, 4u)) {
		return -EINVAL;
	}
	if (!mpu_has_access(size, sizeof(size_t), MPU_MODE_READABLE | MPU_MODE_WRITABLE)) {
		return -EACCES;
	}
	if (!mpu_has_access(version, *size, MPU_MODE_READABLE | MPU_MODE_WRITABLE)) {
		return -EACCES;
	}
	switch (image) {
	case CMRT_FBOOT_IMAGE_VERSION: {
		uint32_t const *head = (uint32_t const *)__cmrt_version_head;
		return binary_version_helper(head, version, size);
	}
	case CMRT_SBOOT_IMAGE_VERSION:
		return sboot_version_helper(version, size);
	case CMRT_TBOOT_IMAGE_VERSION:
	case CMRT_SUPERVISOR_IMAGE_VERSION: {
		uint32_t const *head = (uint32_t const *)supervisor_image(image);
		return binary_version_helper(head, version, size);
	}
	default:
		break;
	}
	return -EINVAL;
}

int fboot_get_enforced_version(enum cmrt_enforced_version_id image, uint32_t *version)
{
	if (version == NULL || !is_aligned(version, 4u)) {
		return -EINVAL;
	}
	if (!mpu_has_access(version, sizeof(*version), MPU_MODE_READABLE | MPU_MODE_WRITABLE)) {
		return -EACCES;
	}
	return otp_version_helper((uint32_t)image, version, false);
}

int fboot_set_enforced_version(enum cmrt_enforced_version_id image, uint32_t version)
{
	if (!(silo_mode || current_root != NULL)) {
		return -EPERM;
	}
	/* coverity[OVERRUN] */
	return otp_version_helper((uint32_t)image, &version, true);
}

int fboot_prepare_boot_bypass(const void *stack, const void *function)
{
#ifdef CONFIG_CMRT_PMU
	if (stack == NULL || !is_aligned(stack, ARCH_STACK_PTR_ALIGN) ||
	    function == NULL || !is_aligned(function, 2u)) {
		return -EINVAL;
	}
	/* The stack must have the state structure at bottom. */
	if (!mpu_has_access(stack, sizeof(struct __esf), MPU_MODE_READABLE | MPU_MODE_WRITABLE)) {
		return -EACCES;
	}
	/* At least one compressed instruction must be executable. */
	if (!mpu_has_access(function, sizeof(uint16_t), MPU_MODE_READABLE | MPU_MODE_EXECUTABLE)) {
		return -EACCES;
	}
	/* Add command bits to the status, we can use the lower bits. */
	uint32_t status = (uint32_t)(uintptr_t)stack;
	status |= BOOT_BYPASS_ALLOWED; /* this tells HW about boot bypass */
	uint32_t vector = (uint32_t)(uintptr_t)function;
	cmrt_write_reg(CMRT_SIC_BASE, R_BOOT_BYPASS_STATUS, status);
	cmrt_write_reg(CMRT_SIC_BASE, R_BOOT_BYPASS_VECTOR, vector);
	extern void cmrt_pmu_save_os(void);
	cmrt_pmu_save_os();
	return 0;
#else
	ARG_UNUSED(stack);
	ARG_UNUSED(function);
	/* No PMU support. */
	return -EFAULT;
#endif
}

int fboot_data_store_read(const void *name, size_t namelen, void *data, size_t *datalen, bool user)
{
#ifdef CONFIG_CMRT_DATASTORE
	if (name == NULL || namelen == 0 ||
	    data == NULL || datalen == NULL ||
	    !is_aligned(datalen, 4u)) {
		return -EINVAL;
	}
	if (!mpu_has_access(name, namelen, MPU_MODE_READABLE) ||
	    !mpu_has_access(datalen, sizeof(size_t), MPU_MODE_READABLE | MPU_MODE_WRITABLE) ||
	    !mpu_has_access(data, *datalen, MPU_MODE_WRITABLE)) {
		return -EACCES;
	}
	int root = current_root_index();
	uint32_t required = is_machine() ? 0 : user ? DS_U_READ : DS_S_READ;
	return data_store_read(name, namelen, data, datalen, required, root);
#else
	ARG_UNUSED(name);
	ARG_UNUSED(namelen);
	ARG_UNUSED(data);
	ARG_UNUSED(datalen);
	ARG_UNUSED(user);
	return -ENOTSUP;
#endif
}

int fboot_data_store_write(const void *name, size_t namelen, const void *data, size_t datalen, bool user)
{
#ifdef CONFIG_CMRT_DATASTORE
	if (name == NULL || namelen == 0) {
		return -EINVAL;
	}
	if (!mpu_has_access(name, namelen, MPU_MODE_READABLE) ||
	    !mpu_has_access(data, datalen, MPU_MODE_READABLE)) {
		/* NULL data and zero datalen does not fail here. */
		return -EACCES;
	}
	int root = current_root_index();
	uint32_t required = is_machine() ? 0 : user ? DS_U_WRITE : DS_S_WRITE;
	return data_store_write(name, namelen, data, datalen, required, root);
#else
	ARG_UNUSED(name);
	ARG_UNUSED(namelen);
	ARG_UNUSED(data);
	ARG_UNUSED(datalen);
	ARG_UNUSED(user);
	return -ENOTSUP;
#endif
}

int fboot_data_store_grant(const void *name, size_t namelen, uint32_t attributes, int index, bool user)
{
#ifdef CONFIG_CMRT_DATASTORE
	if (name == NULL || namelen == 0) {
		return -EINVAL;
	}
	if (!mpu_has_access(name, namelen, MPU_MODE_READABLE)) {
		return -EACCES;
	}
	if (index < 0 || index > CMRT_OTP_NUM_ROOTS) {
		/* Use current root for invalid values. */
		index = current_root_index();
	}
	int root = current_root_index();
	uint32_t required = is_machine() ? 0 : user ? DS_U_GRANT : DS_S_GRANT;
	return data_store_grant(name, namelen, attributes, required, index, root);
#else
	ARG_UNUSED(name);
	ARG_UNUSED(namelen);
	ARG_UNUSED(attributes);
	ARG_UNUSED(index);
	ARG_UNUSED(user);
	return -ENOTSUP;
#endif
}

#include <cmrt/fboot/syscall_ids.h>

const void * const fboot_syscall_table[FBOOT_SYSCALL_MAX] = {
	[FBOOT_SYSCALL_LOAD_IMAGE] = fboot_load_image,
	[FBOOT_SYSCALL_CREATE_ROOT] = fboot_create_root,
	[FBOOT_SYSCALL_OBLITERATE_ROOT] = fboot_obliterate_root,
	[FBOOT_SYSCALL_HALT] = fboot_halt,
	[FBOOT_SYSCALL_REBOOT] = fboot_reboot,
	[FBOOT_SYSCALL_RESET] = fboot_reset,
	[FBOOT_SYSCALL_RESET_INFO] = fboot_reset_info,
	[FBOOT_SYSCALL_GET_IMAGE_VERSION] = fboot_get_image_version,
	[FBOOT_SYSCALL_GET_ENFORCED_VERSION] = fboot_get_enforced_version,
	[FBOOT_SYSCALL_SET_ENFORCED_VERSION] = fboot_set_enforced_version,
	[FBOOT_SYSCALL_PREPARE_BOOT_BYPASS] = fboot_prepare_boot_bypass,
	[FBOOT_SYSCALL_DATA_STORE_READ] = fboot_data_store_read,
	[FBOOT_SYSCALL_DATA_STORE_WRITE] = fboot_data_store_write,
	[FBOOT_SYSCALL_DATA_STORE_GRANT] = fboot_data_store_grant,
};

GEN_ABS_SYM_BEGIN(fboot_syscall_syms)
GEN_ABSOLUTE_SYM(FBOOT_SYSCALL_TABLE_SIZE, sizeof(fboot_syscall_table) / sizeof(void *));
GEN_ABS_SYM_END
