/*!
 * \file
 * Defines registers belonging to OMC.
 *
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_OMC_REG_H
#define CMRT_OMC_REG_H

#include <stdint.h>
#include <stddef.h>

#include "hwc_reg.h"

#define CMRT_OMC_BASE          0x00040000UL

/*****************
 * OMC registers *
 *****************/

#define R_OTP_BASE_ADDR        0x250UL
#define R_OTP_WRITE_DATA0      0x254UL
#define R_OTP_WRITE_DATA1      0x258UL
#define R_OTP_WRITE_DATA2      0x25CUL
#define R_OTP_WRITE_DATA3      0x260UL
#define R_OTP_WRITE_DATA4      0x264UL
#define R_OTP_WRITE_DATA5      0x268UL
#define R_OTP_WRITE_DATA6      0x26CUL
#define R_OTP_WRITE_DATA7      0x270UL
#define R_ESW_PERM_1           0x300UL
#define R_ESW_PERM_WORD_1      0x304UL
#define R_ESW_PERM_2           0x308UL
#define R_ESW_PERM_WORD_2      0x30CUL
#define R_OTP_SLOT_W           0x310UL

/* Far end of OMC register address */
#define R_OMC_MAX              (R_OTP_SLOT_W + 4u)


/********************************
 * Enum of CORE_STATUS register *
 * values in OMC                *
 ********************************/

#define OMC_STATUS_ERROR_IBA    0x80UL /* Invalid Base Address */
#define OMC_STATUS_ERROR_AD     0x82UL /* Access Denied */
#define OMC_STATUS_ERROR_IWV    0x83UL /* Enforced Region - Invalid Write Value */
#define OMC_STATUS_ERROR_INWA   0x84UL /* Invalid Nil Write Attempt */
#define OMC_STATUS_ERROR_NE     0x85UL /* Non-empty Write */
#define OMC_STATUS_ERROR_WDE    0x86UL /* Write Direct Error */
#define OMC_STATUS_SUCCESS_DATA_CORRECTION 0xF1UL

/********************************
 * Enum of CORE_CTRL register   *
 * values in OMC                *
 ********************************/
typedef enum cmrt_omc_crtl_request_t {
    REQ_NONE            = 0x00,
    REQ_VALIDATE_EMPTY  = 0x01,
    REQ_WRITE_INDIRECT  = 0x02,
    REQ_RESHADOW        = 0x15,
    REQ_OBLITERATE      = 0x20,
    REQ_FLUSH           = 0xFF,
} cmrt_omc_ctrl_request_t;

/*****************************
 * Definitions to OTP layout *
 *****************************/

#ifndef __KERNEL__
#define OTP_MEMORY_FILE "otpmem.bin"
#define ROM_MEMORY_FILE "rommem.bin"
#endif

/* OTP starts from virtual address 3MB */
#define OTP_ADDR_SPACE  (3UL * 1024UL * 1024UL)

typedef struct cmrt_omc_key_split_t cmrt_omc_key_split_t;
struct cmrt_omc_key_split_t {
    uint8_t         key[32];
};

typedef struct cmrt_omc_root_id_t cmrt_omc_root_id_t;
struct cmrt_omc_root_id_t  {
    uint8_t         hash[32];
};

typedef enum {
    PT_OTP_ESW_RW   = 0x64,
    PT_OTP_ESW_W    = 0x65,
    PT_OTP_ESW_R    = 0x66,
    PT_OTP_ESW_NONE = 0x0,
} cmrt_omc_perm_t;

#define OMC_SLOT_PERM_LIFECYCLE          (1UL << 0)
#define OMC_SLOT_PERM_TDV                (1UL << 1)
#define OMC_SLOT_PERM_DEVICE_ID          (1UL << 2)
#define OMC_SLOT_PERM_OEM_ID             (1UL << 3)
#define OMC_SLOT_PERM_PERSO_OBLITERATE   (1UL << 4)
#define OMC_SLOT_PERM_DELEGATION_ROOT    (1UL << 7)

#define OMC_SLOT_PERMS_DGOK              (1UL << 8)
#define OMC_SLOT_PERMS_KEYSPLIT_1        (1UL << 9)
#define OMC_SLOT_PERMS_KEYSPLIT_2        (1UL << 10)
#define OMC_SLOT_PERMS_KEYSPLIT_3        (1UL << 11)
#define OMC_SLOT_PERMS_KEYSPLIT_4        (1UL << 12)
#define OMC_SLOT_PERMS_KEYSPLIT_5        (1UL << 13)
#define OMC_SLOT_PERMS_KEYSPLIT_6        (1UL << 14)
#define OMC_SLOT_PERMS_KEYSPLIT_7        (1UL << 15)

#define OMC_SLOT_PERMS_CREATE_ROOT_0     (1UL << 16)
#define OMC_SLOT_PERMS_CREATE_ROOT_1     (1UL << 17)
#define OMC_SLOT_PERMS_CREATE_ROOT_2     (1UL << 18)
#define OMC_SLOT_PERMS_CREATE_ROOT_3     (1UL << 19)
#define OMC_SLOT_PERMS_CREATE_ROOT_4     (1UL << 20)
#define OMC_SLOT_PERMS_CREATE_ROOT_5     (1UL << 21)
#define OMC_SLOT_PERMS_CREATE_ROOT_6     (1UL << 22)
#define OMC_SLOT_PERMS_CREATE_ROOT_7     (1UL << 23)

#define OMC_SLOT_PERMS_OBLITERATE_ROOT_0 (1UL << 24)
#define OMC_SLOT_PERMS_OBLITERATE_ROOT_1 (1UL << 25)
#define OMC_SLOT_PERMS_OBLITERATE_ROOT_2 (1UL << 26)
#define OMC_SLOT_PERMS_OBLITERATE_ROOT_3 (1UL << 27)
#define OMC_SLOT_PERMS_OBLITERATE_ROOT_4 (1UL << 28)
#define OMC_SLOT_PERMS_OBLITERATE_ROOT_5 (1UL << 29)
#define OMC_SLOT_PERMS_OBLITERATE_ROOT_6 (1UL << 30)
#define OMC_SLOT_PERMS_OBLITERATE_ROOT_7 (1UL << 31)


/*!
 * OMC slot permissions piece-wise split access.  The OTP permissions
 * field can split into four distinct bitmaps.
 */
struct cmrt_omc_slot_perm_s {
    uint8_t general_slots; /**< bitmap of slots allowed to access */
    uint8_t keysplits;     /**< accessible key splits */
    uint8_t root_creation; /**< roots allowed to create. */
    uint8_t root_obliteration; /**< bitmap of roots allowed to obliterate */
};


/*!
 * OTP slot permissions.
 */
typedef union cmrt_omc_slot_perm_t {
    struct cmrt_omc_slot_perm_s s; /**< field access */
    uint32_t val; /**< single 32-bit value */
} cmrt_omc_slot_perm_t;

#define OMC_KEY_PERM_BNAK (1UL << 0)
#define OMC_KEY_PERM_SNAK (1UL << 1)
#define OMC_KEY_PERM_PNAK (1UL << 2)


/*!
 * Split key permissions.  Go into cmrt_omc_key_perm_t.
 */
struct cmrt_omc_key_perm_s {
    uint8_t general_slots;
    uint8_t keysplits;
    uint16_t key_destinations;
};


/*!
 * Key permissions.
 */
typedef union cmrt_omc_key_perm_t {
    struct cmrt_omc_key_perm_s s;
    uint32_t val;
} cmrt_omc_key_perm_t;


typedef struct cmrt_omc_feature_perm_t cmrt_omc_feature_perm_t;
struct cmrt_omc_feature_perm_t {
    uint32_t val;
};

/*
 * We don't care about the lower two bits in the range masks
 * because permission ranges are taken as word aligned in the HW.
 */
#define OMC_SW_OTP_PERM_LOWER_MASK (0x00007FFCUL)
#define OMC_SW_OTP_PERM_UPPER_MASK (0x7FFC0000UL)
#define OMC_SW_OTP_PERM_R (1UL << 15)
#define OMC_SW_OTP_PERM_W (1UL << 31)
#define OMC_SW_OTP_PERM_RW (OMC_SW_OTP_PERM_R | OMC_SW_OTP_PERM_W)


/*!
 * OTP SW permission.
 */
typedef union cmrt_omc_sw_otp_perm_t {
    struct cmrt_omc_sw_otp_perm_u {
        uint16_t lower_and_read;
        uint16_t upper_and_write;
    } s;
    uint32_t val;
} cmrt_omc_sw_otp_perm_t;

/*
 * First 16 bits of software permissions control access to SAC memory,
 * Each bit applies to a chunk in respective SAC memory, for example,
 * if SAC memory space is 512kB then the lowest bit applies to the
 * lowest 32kB chunk in it. Access is always RW for the SAC memory.
 * This makes it possible to set area permissions for SAC memory without
 * changing current root permission structures in OTP.
 */
#define OMC_SW_PERM_SAC_BITS 16u
#define OMC_SW_PERM_SAC_MASK 0x0000FFFFUL
/*
 * Bit for defining debug mode for containers. Set this on for enabling
 * debug logs for the container and other supporting features in middleware.
 * Note that middleware must be compiled to have debug support for this bit
 * to have any effect.
 */
#define OMC_SW_PERM_DEBUG_MODE (1UL << 31)

/*
 * Bits in cmrt_omc_software_perm_t for fboot containers,
 * possible TBOOT image, silo-mode supervisors, non-silo supervisors,
 * silo-mode user containers and non-silo user containers.
 *
 * For example, when fboot container is loaded, its footer must have bit
 * OMC_SW_PERM_FBOOT_CONTAINER set and the signing root must have the bit set.
 */
#define OMC_SW_PERM_TBOOT           (1UL << 30) /* CAVEAT_SILO */
#define OMC_SW_PERM_FBOOT_CONTAINER (1UL << 29) /* CAVEAT_SILO */
#define OMC_SW_PERM_SILO_SUPERVISOR (1UL << 28) /* CAVEAT_SILO */
#define OMC_SW_PERM_SUPERVISOR      (1UL << 27) /* CAVEAT_NONE */
#define OMC_SW_PERM_SILO_CONTAINER  (1UL << 26) /* CAVEAT_SILO */
#define OMC_SW_PERM_CONTAINER       (1UL << 25) /* CAVEAT_NONE */
#define OMC_SW_LOAD_PERM_MASK (                            \
    OMC_SW_PERM_TBOOT | OMC_SW_PERM_FBOOT_CONTAINER |      \
    OMC_SW_PERM_SILO_SUPERVISOR | OMC_SW_PERM_SUPERVISOR | \
    OMC_SW_PERM_SILO_CONTAINER | OMC_SW_PERM_CONTAINER)

typedef struct cmrt_omc_software_perm_t cmrt_omc_software_perm_t;
struct cmrt_omc_software_perm_t {
    uint32_t val;
};

typedef struct cmrt_omc_root_perm_t cmrt_omc_root_perm_t;
struct cmrt_omc_root_perm_t {
    cmrt_omc_slot_perm_t slot_perm;
    cmrt_omc_key_perm_t key_perm;
    cmrt_omc_feature_perm_t feature_perm;
    cmrt_omc_sw_otp_perm_t sw_otp_perm[2];
    cmrt_omc_software_perm_t software_perm;
};

typedef struct cmrt_omc_root_t cmrt_omc_root_t;
struct cmrt_omc_root_t {
    cmrt_omc_root_id_t id;
    cmrt_omc_root_perm_t perm;
};

typedef struct omc_perm_t omc_perm_t;
struct omc_perm_t {
    cmrt_omc_sw_otp_perm_t sw_otp_perm[2];
    cmrt_omc_slot_perm_t slot_perm;
};

#define OMC_FULL_PERM                         \
    ((omc_perm_t) {                           \
        .sw_otp_perm[0].val = 0x1FFFFUL << 15,  \
        .sw_otp_perm[1].val = 0x1FFFFUL << 15,  \
        .slot_perm.val = 0xFFFFFFFFUL,          \
    })

typedef struct cmrt_otp_head_t cmrt_otp_head_t;
struct cmrt_otp_head_t {
    /* Enforced Value Region. */

    /* R) All
     * W) PT_OTP_SLOT_W CSB M/S
     */
    uint32_t        life_cycle;

#define OMC_TDV_WORDS 4u
    uint32_t        test_debug_vector[OMC_TDV_WORDS];

    uint32_t        status_word;

#if defined(CONFIG_CRI_OMC_LAYOUT_VERSION) && CONFIG_CRI_OMC_LAYOUT_VERSION >= 2
    uint32_t        key_obliterate;
#endif
#if defined(CONFIG_CRI_OMC_LAYOUT_VERSION) && CONFIG_CRI_OMC_LAYOUT_VERSION >= 3
    uint32_t        root_valid;
    uint32_t        root_obliterate;
#endif

    /* W1O Region */
    /*
     * R) All
     * W) PT_OTP_SLOT_W CSB M/S
     */

#define OMC_DEVICE_ID_WORDS 3
#define OMC_OEM_ID_WORDS 2
    uint32_t        device_id[OMC_DEVICE_ID_WORDS];
    uint32_t        oem_id[OMC_OEM_ID_WORDS];

    /*
     * R) PT_USE_KEYS_R ISB
     * W) PT_OTP_SLOT_W CSB M/S, ISB
     */
    cmrt_omc_key_split_t dgok;
};

#if defined(CONFIG_CRI_OMC_KEYSPLITS_NUM) && defined(CONFIG_CRI_OMC_ROOTS_NUM)

/*!
 * OTP layout
 */
typedef struct cmrt_otp_layout_t {
    cmrt_otp_head_t h;
    cmrt_omc_key_split_t keysplits[CONFIG_CRI_OMC_KEYSPLITS_NUM];

    /*
     * R) All
     * W) PT_OTP_SLOT_W CSB M
     */
    cmrt_omc_root_t     roots[CONFIG_CRI_OMC_ROOTS_NUM];
} cmrt_otp_layout_t;

#define OTP_KEYSPLIT(i)     offsetof(cmrt_otp_layout_t, keysplits[(i)])
#define OTP_ROOT_ID(i)      offsetof(cmrt_otp_layout_t, roots[(i)])
#define OTP_ROOT_PERM(i)    (OTP_ROOT_ID(i) + sizeof(cmrt_omc_root_id_t))

#define is_invalid_omc_keysplit(ks) ((ks) >= CONFIG_CMRT_OMC_KEYSPLITS_NUM)

#endif

/* Write Indirect Success */
#define OMC_WRITE_IND_OK_IRQ        (1UL << 0)
/* Write Indirect Error */
#define OMC_WRITE_IND_NOK_IRQ       (1UL << 1)
#define OMC_READ_ECC_OK_IRQ         (1UL << 2)
#define OMC_READ_ECC_NOK_IRQ        (1UL << 3)
#define OMC_IRQ_MASK \
    (OMC_WRITE_IND_OK_IRQ|OMC_WRITE_IND_NOK_IRQ|\
     OMC_READ_ECC_OK_IRQ|OMC_READ_ECC_NOK_IRQ)

/*
 * Cmrt lifecycle states.
 */
#define DLC_BLANK          0x00000000UL /* Untested device */
#define DLC_TESTED         0x00000500UL /* Partially tested device */
#define DLC_PROVISIONED    0x00010D01UL /* Fully tested, provisioned device */
#define DLC_MISSION        0x20010D03UL /* Ready for deployment in field */
#define DLC_FRA            0x70010DA3UL /* RMA device */
#define DLC_DECOMMISSIONED 0x7C034DA3UL /* Non-functional device */

/* status word encodings */
#define OTP_PERSO_INVALID       0x20000002UL
#define OTP_VKS_VALID           0x00000500UL
#define OTP_KS_VALID1           0x00010801UL
#define OTP_KS_VALID2           0x00802004UL
#define OTP_KS_VALID3           0x00141000UL
#define OTP_KS_VALID4           0x00088048UL
#define OTP_KS_VALID5           0x500000A0UL
#define OTP_KS_VALID6           0x0C024000UL
#define OTP_KS_VALID7           0x00600210UL

/* key_obliterate encodings */
#define OTP_VKS_OBLITERATED     0x00000500UL
#define OTP_KS_OBLITERATED1     0x00010801UL
#define OTP_KS_OBLITERATED2     0x00802004UL
#define OTP_KS_OBLITERATED3     0x00141000UL
#define OTP_KS_OBLITERATED4     0x00088048UL
#define OTP_KS_OBLITERATED5     0x500000A0UL
#define OTP_KS_OBLITERATED6     0x0C024000UL
#define OTP_KS_OBLITERATED7     0x00600210UL

/* root_valid and root_obliterate encodings */
#define OTP_ROOT0_STATUS        0x00000500UL
#define OTP_ROOT1_STATUS        0x00010801UL
#define OTP_ROOT2_STATUS        0x00802004UL
#define OTP_ROOT3_STATUS        0x00141000UL
#define OTP_ROOT4_STATUS        0x00088048UL
#define OTP_ROOT5_STATUS        0x500000A0UL
#define OTP_ROOT6_STATUS        0x0C024000UL
#define OTP_ROOT7_STATUS        0x00600210UL
#endif
