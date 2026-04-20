/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_OTP_OFF_H
#define CMRT_OTP_OFF_H

#include <stddef.h>
#include <stdint.h>
#include <drivers/cmrt/omc_reg.h>

/*
 * OTP offsets and respective field sizes for cmrt_omc_read,
 * cmrt_omc_write and cmrt_omc_obliterate.
 */
#define OTP_LIFECYCLE_OFFSET        offsetof(cmrt_otp_head_t, life_cycle)
#define OTP_TDV_OFFSET              offsetof(cmrt_otp_head_t, test_debug_vector)
#define OTP_STATUS_WORD_OFFSET      offsetof(cmrt_otp_head_t, status_word)
#if defined(CONFIG_CRI_OMC_LAYOUT_VERSION) && CONFIG_CRI_OMC_LAYOUT_VERSION >= 2
#define OTP_KEY_OBLITERATE_OFFSET   offsetof(cmrt_otp_head_t, key_obliterate)
#endif
#if defined(CONFIG_CRI_OMC_LAYOUT_VERSION) && CONFIG_CRI_OMC_LAYOUT_VERSION >= 3
#define OTP_ROOT_VALID_OFFSET       offsetof(cmrt_otp_head_t, root_valid)
#define OTP_ROOT_OBLITERATE_OFFSET  offsetof(cmrt_otp_head_t, root_obliterate)
#endif
#define OTP_DEVICE_ID_OFFSET        offsetof(cmrt_otp_head_t, device_id)
#define OTP_OEM_ID_OFFSET           offsetof(cmrt_otp_head_t, oem_id)
#define OTP_DGOK_OFFSET             offsetof(cmrt_otp_head_t, dgok)
#define OTP_KEYSPLIT_OFFSET(i)      offsetof(cmrt_otp_layout_t, keysplits[(i)])
#define OTP_ROOT_OFFSET(i)          offsetof(cmrt_otp_layout_t, roots[(i)])

#define OTP_LIFECYCLE_SIZE          sizeof(((cmrt_otp_head_t *)0)->life_cycle)
#define OTP_TDV_SIZE                sizeof(((cmrt_otp_head_t *)0)->test_debug_vector)
#define OTP_STATUS_WORD_SIZE        sizeof(((cmrt_otp_head_t *)0)->status_word)
#define OTP_KEY_OBLITERATE_SIZE     sizeof(((cmrt_otp_head_t *)0)->key_obliterate)
#define OTP_DEVICE_ID_SIZE          sizeof(((cmrt_otp_head_t *)0)->device_id)
#define OTP_OEM_ID_SIZE             sizeof(((cmrt_otp_head_t *)0)->oem_id)
#define OTP_DGOK_SIZE               sizeof(((cmrt_otp_head_t *)0)->dgok)
#define OTP_KEYSPLIT_SIZE           sizeof(cmrt_omc_key_split_t)
#define OTP_ROOT_SIZE               sizeof(cmrt_omc_root_t)

/*
 * Reserved words are in the beginning or in the end of the eSW area.
 * Size for a reserved word is always sizeof(uint32_t).
 */
#ifdef CONFIG_CMRT_OMC_ESW_RSVD_FIRST
#define OTP_MACHINE_VERSION_OFFSET    (sizeof(cmrt_otp_layout_t))
#define OTP_SUPERVISOR_VERSION_OFFSET (OTP_MACHINE_VERSION_OFFSET + sizeof(uint32_t))
#define OTP_USER_VERSION_OFFSET       (OTP_SUPERVISOR_VERSION_OFFSET + sizeof(uint32_t))
#define OTP_ESW_OFFSET                 (sizeof(cmrt_otp_layout_t) + CONFIG_CMRT_OMC_ESW_RSVD_WORDS * sizeof(uint32_t))

#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
/* Emulated OTP reserves last 256 bits. */
#define OTP_ESW_SIZE (CMRT_OTP_SIZE - OTP_ESW_OFFSET - 8 * sizeof(uint32_t))
#else
#define OTP_ESW_SIZE (CMRT_OTP_SIZE - OTP_ESW_OFFSET)
#endif

#else /* CONFIG_CMRT_OMC_ESW_RSVD_FIRST */

#define OTP_MACHINE_VERSION_OFFSET    (CMRT_OTP_SIZE - sizeof(uint32_t))
#define OTP_SUPERVISOR_VERSION_OFFSET (OTP_MACHINE_VERSION_OFFSET - sizeof(uint32_t))
#define OTP_USER_VERSION_OFFSET       (OTP_SUPERVISOR_VERSION_OFFSET - sizeof(uint32_t))
#define OTP_ESW_OFFSET                (sizeof(cmrt_otp_layout_t))

#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
/* Emulated OTP reserves last 256 bits. */
#define OTP_ESW_SIZE (CMRT_OTP_SIZE - OTP_ESW_OFFSET - CONFIG_CMRT_OMC_ESW_RSVD_WORDS * sizeof(uint32_t) - 8 * sizeof(uint32_t))
#else
#define OTP_ESW_SIZE (CMRT_OTP_SIZE - OTP_ESW_OFFSET - CONFIG_CMRT_OMC_ESW_RSVD_WORDS * sizeof(uint32_t))
#endif
#endif /* CONFIG_CMRT_OMC_ESW_RSVD_FIRST */

#endif
