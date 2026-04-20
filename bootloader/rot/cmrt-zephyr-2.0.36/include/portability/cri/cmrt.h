/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file cmrt.h
 *
 * @brief Public APIs for the CMRT device drivers.
 */

#ifndef CRI_CMRT_H
#define CRI_CMRT_H

#include <stddef.h>
#include <stdbool.h>
#include <hwc_reg.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef void *cri_handle_t;

static inline bool cri_is_valid(cri_handle_t context)
{
	/* Native mode context is pointer.*/
	return context != NULL;
}

#define CRI_INVALID_HANDLE ((cri_handle_t)NULL)

/*!
 * CMRT device enumeration.
 */
typedef enum cri_dev_e {
	CRI_DEV_INVALID,        /**< invalid/uninitialized device */
	CRI_DEV_SIC,            /**< SIC device */
	CRI_DEV_OMC,            /**< OTP memory controller */
	CRI_DEV_DMAC,           /**< DMA controller */
	CRI_DEV_HC,             /**< HC hash core */
	CRI_DEV_PKE,            /**< PKE private key engine */
	CRI_DEV_AES,            /**< AES engine */
	CRI_DEV_TMC,            /**< TMC core */
	CRI_DEV_FMC,            /**< FMC core */
	CRI_DEV_UFC,            /**< UFC core */
	CRI_DEV_KDC,            /**< Key derivation core */
	CRI_DEV_RSA,            /**< RSA core */
	CRI_DEV_KTC,            /**< KTC core */
	CRI_DEV_SID,            /**< SOC IRQ driver */
	CRI_DEV_CSHC,           /**< CSHC compact SHA hash core */
	CRI_DEV_WHC,            /**< Whirlpool hash core */
	CRI_DEV_CCP,            /**< ChaChaPolyWrapper unit */
	CRI_DEV_WATCHDOG,       /**< CMRT Watchdog wrapper */
	CRI_DEV_SM3,            /**< SM3 core */
	CRI_DEV_SM4             /**< SM4 core */
} cri_dev_e;

/**
 * @brief Open a device
 *
 * @param dev ID of the device
 * @param flags Reserved for future expansion. Must be zero.
 * @param ... Device specific arguments. Only SIC requires one extra
 *            argument to specific flow ID.
 */
cri_handle_t cri_open(cri_dev_e id, unsigned flags, ...);

/**
 * Close a device context handle.
 * @param h file to close
 * @return zero on success or negative value on error
 */
int cri_close(cri_handle_t h);


/*!
 * Timeout argument value for an infinite wait.
 */
#define CRI_FOREVER (-1)


/**
 * @brief Wait on a set of contexts.
 *
 * The wait will return on either any of the contexts becoming ready,
 * or timeout elapsing.
 *
 * @param[in] n Number of handles to check.
 * @param[in] handles Array of handles of length \a numfds. All must be valid.
 * @param[in] timeout Timeout in milliseconds, CRI_FOREVER for infinite.
 * @return Bitset of ready fds by index in \a fds, zero for timeout, and
 * -ERRNO on failure.
 */
int cri_wait(unsigned int n, cri_handle_t const *handles, int timeout);

/**
 * @defgroup CRI_O_XXX
 * Flags to cri_device_open(), for instance, cri_aes_open().
 */

/**
 * @}
 * @defgroup CRI_O_PUBLIC_FLAGS Device driver public flags
 * @ingroup CRI_O_XXX
 * @{
 */

#define CRI_O_COMMON_MASK       0x0000FFFFUL

/**
 * Set to make the device driver operations synchronous. Typically there's
 * no need to call cri_device_sync() explicitly when this option is set.
 */
#define CRI_O_SYNC      0x1UL

/**
 * Set to make all device driver operations asynchronous. At the moment this
 * only applies to cri_sic_open() and setting this flag means the application
 * needs to call cri_sic_sync() also after cri_sic_write().
 */
#define CRI_O_ASYNC     0x2UL

/**
 * Indicates that another HWC will directly initialize and load key into the
 * HWC of this device. If specified, device driver only reserves device driver
 * context and does not itself take the HWC lock.
 */
#define CRI_O_HWC_KEYED 0x4UL

/**
 * Executes KAT tests unconditionally
 */
#define CRI_O_HWC_FORCE_KAT 0x8UL

/**
 * Don't execute KAT tests on open.
 */
#define CRI_O_HWC_SKIP_KAT 0x10UL

/**
 * Don't wait for a free context in device driver open. This applies for
 * multithreaded mode where open will normally block until there's a context
 * available.
 */
#define CRI_O_NO_WAIT 0x20UL

/**
 * @}
 * @defgroup CRI_O_PRIVATE_FLAGS Device driver private flags
 * @ingroup CRI_O_XXX
 * @{
 */

#define CRI_OP_MASK             0xFFFF0000UL
#define CRI_OP_SHIFT            16

/**
 * When using emulated OTP, @ref CRI_O_OTP_COMMIT flag can be specified to
 * @ref cri_otp_open. OMC driver then reserves HC and AES contexts.
 * @ref cri_otp_close/@ref cri_otp_sclose then auto commits OTP contents and
 * releases HC and AES contexts. This flag is NOP if CONFIG_CRI_OMC_EMULATED_OTP
 * is not set.
 */
#define CRI_O_OTP_COMMIT       (0x1UL << CRI_OP_SHIFT)

/**
 * Request HSAES Linear AES-GCM operation mode.
 * Default mode is Bidirectional AES-GCM.
 */
#define CRI_O_HSAES_LINEAR     (0x1UL << CRI_OP_SHIFT)

#ifdef __cplusplus
}
#endif

#endif
