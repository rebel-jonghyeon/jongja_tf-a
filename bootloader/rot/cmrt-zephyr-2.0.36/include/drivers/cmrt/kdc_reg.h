/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_KDC_REG_H
#define CMRT_KDC_REG_H

#include "hwc_reg.h"

#define CMRT_KDC_BASE             0x00050000UL

#define R_KDC_KEY_CONTROL         R_CORE_KEY_CONTROL
#define R_KDC_KEY0                R_CORE_KEY
#define R_KDC_KEY1                0x214UL
#define R_KDC_KEY2                0x218UL
#define R_KDC_KEY3                0x21CUL
#define R_KDC_KEY4                0x220UL
#define R_KDC_KEY5                0x224UL
#define R_KDC_KEY6                0x228UL
#define R_KDC_KEY7                0x22CUL
#define R_DERIVE_PATH0            0x300UL
#define R_DERIVE_PATH1            0x304UL
#define R_DERIVE_PATH2            0x308UL
#define R_DERIVE_PATH3            0x30CUL
#define R_DERIVE_PATH4            0x310UL
#define R_DERIVE_PATH5            0x314UL
#define R_DERIVE_PATH6            0x318UL
#define R_DERIVE_PATH7            0x31CUL
#define R_DERIVE_PATH8            0x320UL
#define R_DIVERSIFY_PATH0         0x324UL
#define R_DIVERSIFY_PATH1         0x328UL
#define R_DIVERSIFY_PATH2         0x32CUL
#define R_DIVERSIFY_PATH3         0x330UL
#define R_KDC_DEST                0x354UL
#define R_DEST_COMMAND0           0x358UL
#define R_DEST_COMMAND1           0x35CUL
#define R_OTP_USE_KEYS            0x360UL
#define R_KDC_HW_STATE            0x364UL
#define R_DISABLE_KDC             0x368UL

#define KDC_HW_STATE_MASK         0x0ffUL

/* Number of R_KDC_KEY registers */
#define KDC_KEY_WORDS               8UL

/* Numeber of R_DERIVE_PATH registers */
#define KDC_DERIVE_PATH_WORDS       9UL

/* Numeber of R_DIVERSIFY_PATH registers */
#define KDC_DIVERSIFY_PATH_WORDS    4UL

/* Control commands for R_CORE_CONTROL */
#define KDC_CTRL_DERIVE     0x01UL
#define KDC_CTRL_DIVERSIFY  0x02UL
#define KDC_CTRL_BURN_DGOK  0x05UL

#define is_valid_kdc_diversify_len(x) \
	((x) >= 1u && (x) <= 17u)

#define is_invalid_kdc_keysplit_id(key_id)			     \
	((((key_id) & ~KEY_ID_OTP_KPMASK) != KEY_ID_OTP_KEYSPLIT) || \
	 (((key_id) & KEY_ID_OTP_KPMASK) == 0u))

/* The values the can be written to R_KDC_KEY_CONTROL.
 * The register is writable only when STATUS is
 * IDLE_LOCKED, SUCCESS, or ERROR.
 */
typedef union {
	struct {
#define KEY_ID_DGOK         0x00u
#define KEY_ID_BNAK         0x01u
#define KEY_ID_SNAK         0x02u
#define KEY_ID_PNAK         0x03u
#define KEY_ID_OTP_KEYSPLIT 0x10u
#define KEY_ID_OTP_KPMASK   0x0Fu
#define KEY_ID_EXT_KEYSPLIT 0x30u
#define KEY_ID_SELF_TEST    0x40u
		uint8_t base_key_id;

		uint8_t pad1;

		/* The length in bytes of the contents
		 * located in DIVERSIFY_PATH. The valid
		 * values are [2, 17].
		 */
		uint8_t path_len;
		uint8_t pad2;
	} s;
	uint32_t val;
} kdc_key_ctrl_t;

/* KDC status is a combination of
 * error code and core id(s).
 */
typedef union {
	struct {
#define KDC_STATUS_DGOKSW_READY 0xF1
		uint8_t st;

		/* KDC specific error info */
#define KDC_ERR_KREG            0x01u
#define KDC_ERR_DIVERSIFY_LEN   0x02u
#define KDC_ERR_PERMISSION      0x03u
#define KDC_ERR_HC              0x04u
#define KDC_ERR_AES             0x05u
#define KDC_ERR_TMC             0x06u
#define KDC_ERR_OMC             0x07u
#define KDC_ERR_KTC             0x08u
		uint8_t err;

		/* ID of first core locked in case of error */
		uint8_t core1;
		/* ID of second core locked in case of error */
		uint8_t core2;
	} s;
	uint32_t val;
} kdc_status_t;

/* Value to be written to R_KDC_DEST */
typedef union {
	struct {
#define KDC_DEST_KREG   0x00u
#define KDC_DEST_AES    0x01u
#define KDC_DEST_HMAC   0x02u
#define KDC_DEST_HMAC2  0x04u
#define KDC_DEST_KEYBUS_MASK 0x10u
#define KDC_DEST_SW     0xFFu
		uint8_t dest;

#define KDC_SIZE_256    0x00u
#define KDC_SIZE_128    0x01u
		uint8_t size;
		uint16_t pad;
	} s;
	uint32_t val;
} kdc_dest_t;

#define KDC_SUCCESS_IRQ     (1UL << 0)
#define KDC_ERROR_IRQ       (1UL << 1)
#define KDC_DGOK_READY_IRQ  (1UL << 2)
#define KDC_IRQ_MASK        (KDC_SUCCESS_IRQ | KDC_ERROR_IRQ | KDC_DGOK_READY_IRQ)

#define KDC_KEY_SIZE          32UL
#define KDC_SMALL_KEY_SIZE    16UL

/* Value for R_DISABLE_KDC */
#define DISABLE_KDC           1UL
#endif
