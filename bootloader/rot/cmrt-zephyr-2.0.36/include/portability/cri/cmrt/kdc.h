/*
 * Copyright (c) 2017-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file kdc.h
 *
 * @brief Public APIs for the KDC driver.
 */

#ifndef CRI_KDC_H
#define CRI_KDC_H

/**
 * @brief KDC Interface
 * @defgroup kdc_interface KDC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <kdc_reg.h>
#include <omc_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_kdc_t;

#define KDC_MAX_PATH_LEN (KDC_DIVERSIFY_PATH_WORDS * 4u)
#else
typedef struct cmrt_kdc_context *cri_kdc_t;
#endif

#define HWC_LOCK_MASTER_KDC ((CORE_ID_KDC << 8) | HWC_LOCK_MAST_PRV_S | HWC_LOCK_MAST_PRV_M)

typedef struct {
#define KDC_DERIVE_PATH_SIZE 33
	/** derive path is 33 bytes and it must be word aligned */
	uint32_t path[(KDC_DERIVE_PATH_SIZE >> 2) + 1];
} kdc_drv_path_t;

typedef struct {
	/** Internal use. Don't touch it */
	uint32_t ctrl;

	/**
	 * For DEST_COMMAND_0. When dest is set to AES or HMAC,
	 * this value will be combined with LOAD_KEY and then fed
	 * to HWC_CONTROL register of HC or AES core.
	 * For example, if HMAC is the dest, and if SHA-256 is the algo,
	 * the value of command0 shall be HC_HASH_ALGO_SHA_256.
	 * Not needed when burning DGOK.
	 * <BR>
	 * When dest is set to a KTC destination (0x10 - 0x1F) the value of
	 * command0 is used for lower 32bits of key metadata. KTC transfers
	 * metadata, along with key, to SOC.
	 */
	uint32_t command0;

	/**
	 * For DEST_COMMAND_1. If dest is set to AES or HMAC, KDC
	 * will update crypto core's HWC_LOCK_MASTER to this value.
	 * Not needed when burning DGOK.
	 * <BR>
	 * When dest is set to a KTC destination (0x10 - 0x1F) the value of
	 * command1 is used for upper 32bits of key metadata. KTC transfers
	 * metadata, along with key, to SOC.
	 */
	uint32_t command1;

	/**
	 * KEY_ID_XXX, e.g. KEY_ID_DGOK.
	 * Not needed when burning DGOK.
	 */
	uint32_t base_key_id;

	/**
	 * KDC_DEST_XXX, e.g. KDC_DEST_HMAC.
	 * Not needed when burning DGOK.
	 */
	uint32_t dest;

	/**
	 * KDC_SIZE_XXX. KDC can send either 256 or 128 bits of output key to
	 * _other_ HW cores. For destination KDC_DEST_SW and KDC_DEST_KREG key
	 * size is always 256 bits.
	 */
	uint32_t key_size;

	/** Lengh of diversify_path. must be [2, 17], and must be 1 more than
	 * the actual number of octets in diversify_path.
	 */
	uint32_t diversify_len;

	/** The actual number octets in diversify_path must be within [1, 16]. */
	uint32_t diversify_path[KDC_DIVERSIFY_PATH_WORDS];

	/** Output key buffer */
	uint32_t key[KDC_KEY_SIZE / 4];
} kdc_cmd_t;

/**
 * @brief Open KDC context for subsequent operations.
 *
 * Open and reserve a KDC context. May block for a context to be available.
 *
 * @param flags Zero to call cri_kdc_sync after an operation,
 *              CRI_O_SYNC to autosync all operations.
 * @return Context handle on success or NULL on error.
 */
cri_kdc_t cri_kdc_open(uint32_t flags);

/**
 * @brief Close KDC context, reverse of open.
 *
 * Close and free previously opened KDC context.
 *
 * @param context Pointer to the device.
 */
void cri_kdc_close(cri_kdc_t context);

/**
 * @brief Burn DGOK to OTP.
 *
 * Burn DGOK to OTP. Caller must call cri_kdc_sync to wait for completion.
 * This can be done only once and is typically executed at device
 * personalization in machine mode. Caller must call cri_kdc_sync,
 * or CRI_O_SYNC must be set in cri_kdc_open.
 *
 * @note The driver stores a reference to the @p cmd parameter that is
 * used in cri_kdc_sync(). Callers must ensure that the parameter
 * value lives at least until cri_kdc_sync() is called.
 *
 * @param context Pointer to the device.
 * @param cmd In and Out parameters.
 * @return Zero on success, -ERRNO on error.
 */
int cri_kdc_burn_dgok(cri_kdc_t context, kdc_cmd_t *cmd);

/**
 * @brief Set derive path of KDC.
 *
 * Derive path is locked once written until CCC or reset.
 * Derive path is typically set in the machine mode by the security monitor.
 *
 * @param context Pointer to the device.
 * @param drv_path Pointer to derive path
 * @return Zero on success, -ERRNO on error.
 */
int cri_kdc_set_derive_path(cri_kdc_t context, const kdc_drv_path_t *drv_path);

/**
 * @brief Derive key.
 *
 * Derive key. Caller must call cri_kdc_sync to wait for completion.
 * Key will be derived based on the previously set derive path and
 * diversify path within the cmd. Caller must call cri_kdc_sync,
 * or CRI_O_SYNC must be set in cri_kdc_open.
 *
 * @note The driver stores a reference to the @p cmd parameter that is
 * used in cri_kdc_sync(). Callers must ensure that the parameter
 * value lives at least until cri_kdc_sync() is called.
 *
 * @param context Pointer to the device.
 * @param cmd In and Out parameters.
 * @return Zero on success, -ERRNO on error.
 */
int cri_kdc_derive_key(cri_kdc_t context, kdc_cmd_t *cmd);

/**
 * @brief Diversify key.
 *
 * Diversify key. Can be called after cri_kdc_derive_key in case full
 * diversify path did not fit into the first command. Note that dest
 * field in first command must be KDC_DEST_KREG in that case.
 * Caller must call cri_kdc_sync, or CRI_O_SYNC must be set in cri_kdc_open.
 *
 * @note The driver stores a reference to the @p cmd parameter that is
 * used in cri_kdc_sync(). Callers must ensure that the parameter
 * value lives at least until cri_kdc_sync() is called.
 *
 * @param context Pointer to the device.
 * @param cmd In and Out parameters.
 * @return Zero on success, -ERRNO on error.
 */
int cri_kdc_diversify_key(cri_kdc_t context, kdc_cmd_t *cmd);

/**
 * @brief Synchronize KDC operation to get the result.
 *
 * Wait for completion of ongoing KDC operation.
 * Does return immediately if operation has been completed.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_kdc_sync(cri_kdc_t context);

/**
 * @brief Set KDC permissions
 *
 * Permissions are locked once written until CCC or reset.
 * Setting requires canary to be valid. Permissions are typically set
 * by the machine mode security monitor.
 *
 * @param context Pointer to the device.
 * @param perm Pointer to permissions
 * @return Zero on success, -ERRNO on error.
 */
int cri_kdc_set_permissions(cri_kdc_t context, const cmrt_omc_key_perm_t *perm);

/**
 * @brief Disable KDC core
 *
 * Disable KDC core. Any use after disabling will result into a CPU trap.
 *
 * @note This function must be called from machine privilege. It can only be
 * called once.
 */
void cri_kdc_disable(void);

/**
 * @brief Set KDC hardware state
 *
 * Setting the hardware state is optional, it is typically used at boot
 * time to make it impossible to generate the same keys with the same input
 * after boot. Hardware state is locked once written and will be internally
 * added into key derivation path for all key derivations.
 *
 * @param context Pointer to the device.
 * @param hw_state Value for new state.
 * @return Zero on success, -ERRNO on error.
 */
int cri_kdc_set_hw_state(cri_kdc_t context, uint8_t hw_state);

/**
 * @brief Flush the KDC core.
 *
 * Issues a FLUSH command to the core without releasing the context.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_kdc_flush(cri_kdc_t context);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
