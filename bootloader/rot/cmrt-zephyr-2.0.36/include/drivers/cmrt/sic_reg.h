/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_SIC_REG_H
#define CMRT_SIC_REG_H

#include "hwc_reg.h"

#define CMRT_SIC_BASE              0x00001000UL


#define R_BOOT_BYPASS_STATUS      0x124UL
#define BOOT_BYPASS_ALLOWED        (1UL << 0)
#define IN_MPU_RESET               (1UL << 1)
#define R_BOOT_BYPASS_VECTOR      0x128UL
#define R_POWER_DOWN_ALLOWED      0x12CUL
#define POWER_DOWN_ALLOWED         (1UL << 0)
#define R_HWC_ABORT               0x134UL
#define HWC_ABORT_HC               (1UL << 0)
#define HWC_ABORT_AES              (1UL << 1)
#define HWC_ABORT_KDC              (1UL << 2)
#define HWC_ABORT_TMC              (1UL << 3)
#define HWC_ABORT_KTC              (1UL << 4)
#define HWC_ABORT_OMC              (1UL << 5)
#define HWC_ABORT_CC               (1UL << 6)
#define HWC_ABORT_SAC              (1UL << 7)
#define HWC_ABORT_DMAC             (1UL << 8)
#define HWC_ABORT_PKE              (1UL << 9)
#define HWC_ABORT_UFC              (1UL << 10)
#define HWC_ABORT_FMC              (1UL << 11)
#define R_HWC_ABORT_DONE          0x138UL
#define R_HWC_CCC                 0x13CUL
#define HWC_CCC_DO                 (1UL << 0)
#define R_HWC_CCC_DONE            0x140UL
#define R_ESW_RESET               0x144UL
#define ESW_RESET_DO               (1UL << 0)
#define MPU_RESET_DO               (1UL << 1)
#define R_SAFETY_BIST_CONTROL     0x148UL
#define SAFETY_BIST_CONTROL_CHECKER_EN (1UL << 0)
#define SAFETY_BIST_CONTROL_AES   (1UL << 1)
#define SAFETY_BIST_CONTROL_HC    (1UL << 2)
#define SAFETY_BIST_CONTROL_CPU   (1UL << 3)
#define SAFETY_BIST_CONTROL_KDC   (1UL << 4)
#define SAFETY_BIST_CONTROL_MASK  (SAFETY_BIST_CONTROL_CHECKER_EN \
                                   | SAFETY_BIST_CONTROL_AES \
                                   | SAFETY_BIST_CONTROL_HC \
                                   | SAFETY_BIST_CONTROL_CPU \
                                   | SAFETY_BIST_CONTROL_KDC)
#define R_BOOT_CONTROL            0x150UL
#define R_PERSO_PUBLIC_KEY_HASH_0 0x200UL
#define PERSO_PUBLIC_KEY_HASH_REGS 8UL
#define R_OTP_ESW_START_REGION    0x220UL

#define R_FIPS_MODE               0x224UL
#define FIPS_MODE_RUNNING_FLAG   (0x00000100UL)
#define FIPS_MODE_ENTER_FLAG     (0x00000001UL)

#define R_DEFAULT_TMC_TRNG_CTRL   0x228UL
#define R_DEFAULT_TMC_TRNG_CFG    0x22CUL

#define R_DEFAULT_OTP_ACCESS_TIME 0x230UL
#define R_DEFAULT_TDV_BLANK_0     0x234UL
#define DEFAULT_TDV_BLANK_REGS     4UL

#define R_BOOT_STATUS             0x400UL
#define CPU_SRAM_BIST_IDLE         0b000000
#define CPU_SRAM_CHECK_IN_PROGRESS 0b010000
#define CPU_SRAM_CHECK_SUCCESSFUL  0b100000
#define CPU_SRAM_CHECK_FAILED      0b110000
#define R_SW_BOOT_STATUS          0x404UL
#define FBOOT_RUNNING_ID           (1UL << 0)
#define SBOOT_RUNNING_ID           (1UL << 1)
#define TBOOT_RUNNING_ID           (1UL << 2)
#define SUPERVISOR_RUNNING_ID      (1UL << 3)
#define CONTAINER_RUNNING_ID       (1UL << 4)
#define READY_TO_RUN_CONTAINER     (1UL << 5)
#define SWDT_HWC_ID_MASK           (0x0000ff00UL)
#define SWDT_HWC_CTX_MASK          (0xffff0000UL)
#define SWDT_HWC_ID(core_id)       (((uint32_t)(core_id) << 8) & SWDT_HWC_ID_MASK)
#define SWDT_HWC_CTX(ctx)          (((uint32_t)(ctx) << 16) & SWDT_HWC_CTX_MASK)
#define R_CYCLE_COUNTER_LOW       0x408UL
#define R_CYCLE_COUNTER_HIGH      0x40CUL
#define R_CMRT_INFO               0x410UL
#define CMRT_INFO_SIC_MASK         (0x7FUL)

#define R_SOC_VERSION             0x420UL
#define R_BUILDER_VERSION         0x424UL
#define R_KERNEL_VERSION          0x428UL
#define R_SDK_VERSION             0x42CUL

#define R_HW_VERSION_0            0x430UL
#define R_HW_VERSION_1            0x434UL
#define R_HW_VERSION_2            0x438UL
#define R_HW_VERSION_3            0x43CUL

/* Outgoing interrupts */
#define R_SOC_INTERRUPT_OUT       0x500UL
#define R_SOC_INTERRUPT_OUT_MASK  0x504UL
#define SOC_MESSAGE_INTERRUPT_OUT (1UL << 0)
#define SOC_PMU_INTERRUPT_OUT     (1UL << 1)
#define SOC_INTERRUPT_OUT_MASK    (SOC_MESSAGE_INTERRUPT_OUT | SOC_PMU_INTERRUPT_OUT)

/* Incoming interrupts */
#define HLOS2ESW_INTERRUPT_NR     8UL
#define HLOS2ESW_INTERRUPT_IN     (1UL << HLOS2ESW_INTERRUPT_NR)
#define ESW2HLOS_INTERRUPT_NR     9UL
#define ESW2HLOS_INTERRUPT_IN     (1UL << ESW2HLOS_INTERRUPT_NR)
#define SIC_IRQ_MASK              (HLOS2ESW_INTERRUPT_IN | ESW2HLOS_INTERRUPT_IN)
#define SOC_INTERRUPT_IN_0        0UL
#define SOC_INTERRUPT_IN_1        1UL
#define SOC_INTERRUPT_IN_2        2UL
#define SOC_INTERRUPT_IN_3        3UL
#define SOC_INTERRUPT_IN_4        4UL
#define SOC_INTERRUPT_IN_5        5UL
#define SOC_INTERRUPT_IN_6        6UL
#define SOC_INTERRUPT_IN_7        7UL
#define SOC_INTERRUPT_IN_8        8UL
#define SOC_INTERRUPT_IN_9        9UL
#define SOC_INTERRUPT_IN_10       10UL
#define SOC_INTERRUPT_IN_11       11UL
#define SOC_INTERRUPT_IN_12       12UL
#define SOC_INTERRUPT_IN_13       13UL
#define SOC_INTERRUPT_IN_14       14UL
#define SOC_INTERRUPT_IN_15       15UL
#define SOC_INTERRUPT_IN_16       16UL
#define SOC_INTERRUPT_IN_17       17UL
#define SOC_INTERRUPT_IN_18       18UL
#define SOC_INTERRUPT_IN_19       19UL
#define SOC_INTERRUPT_IN_20       20UL
#define SOC_INTERRUPT_IN_21       21UL
#define SOC_INTERRUPT_IN_22       22UL
#define SOC_INTERRUPT_IN_23       23UL
#define SOC_INTERRUPT_IN_24       24UL
#define SOC_INTERRUPT_IN_25       25UL
#define SOC_INTERRUPT_IN_26       26UL
#define SOC_INTERRUPT_IN_27       27UL
#define SOC_INTERRUPT_IN_28       28UL
#define SOC_INTERRUPT_IN_29       29UL
#define SOC_INTERRUPT_IN_30       30UL
#define SOC_INTERRUPT_IN_31       31UL

#if defined(CONFIG_CRI_CMRT)
/* Only for CMRTv1, CMRTv2 defines these elsewhere. */
#if defined(CONFIG_SOC_NUM_IRQS)
#if defined(CONFIG_CMRT_SIC2)
#define SIC2_IRQ_MASK ((1 << CONFIG_CRI_SIC_INSTANCES) - 1)
#define SOC_INTERRUPT_IN_MASK     ((~0u >> (32 - CONFIG_SOC_NUM_IRQS)) & ~SIC2_IRQ_MASK)
#else
#define SOC_INTERRUPT_IN_MASK     ((~0u >> (32 - CONFIG_SOC_NUM_IRQS)) & ~SIC_IRQ_MASK)
#endif
#if !defined(CONFIG_CMRT_V1)
/* Irq number to use in IRQ_CONNECT(), 8 and 9 are reserved. */
#define CMRT_SOC_IRQ(nr)          (CONFIG_NUM_IRQS + nr)
#endif
#endif
#endif

#define R_INTERNAL_HW_ERR_INFO    0x508UL
#define HW_PARITY_ERROR            (1UL << 0)
#define HW_PANIC                   (1UL << 1)
#define SW_HALT                    (1UL << 2)
#define R_INTERNAL_SW_ERR_INFO    0x50CUL
#define R_OTP_HW_ERR_INFO         0x510UL
#define OTP_STATUS_PARSED          (1UL << 0)
#define OTP_ERROR_LIFECYCLE        (1UL << 1)

#define R_SAFETY_DIAGNOSIS_0      0x520UL
#define SAFETY_DIAG_EAC_BUS_ALARM                (1UL << 0)
#define SAFETY_DIAG_EAC_REG_ALARM                (1UL << 1)
#define SAFETY_DIAG_SIC_BUS_ALARM                (1UL << 3)
#define SAFETY_DIAG_SIC_REG_ALARM                (1UL << 4)
#define SAFETY_DIAG_AES_BUS_ALARM                (1UL << 6)
#define SAFETY_DIAG_AES_REG_ALARM                (1UL << 7)
#define SAFETY_DIAG_AES_STATE_ENC_ALARM          (1UL << 8)
#define SAFETY_DIAG_HC_BUS_ALARM                 (1UL << 9)
#define SAFETY_DIAG_HC_REG_ALARM                 (1UL << 10)
#define SAFETY_DIAG_HC_STATE_ENC_ALARM           (1UL << 11)
#define SAFETY_DIAG_DMAC_BUS_ALARM               (1UL << 12)
#define SAFETY_DIAG_DMAC_REG_ALARM               (1UL << 13)
#define SAFETY_DIAG_DMAC_STATE_ENC_ALARM         (1UL << 14)
#define SAFETY_DIAG_FMC_BUS_ALARM                (1UL << 15)
#define SAFETY_DIAG_FMC_REG_ALARM                (1UL << 16)
#define SAFETY_DIAG_FMC_STATE_ENC_ALARM          (1UL << 17)
#define SAFETY_DIAG_KTC_BUS_ALARM                (1UL << 18)
#define SAFETY_DIAG_KTC_REG_ALARM                (1UL << 19)
#define SAFETY_DIAG_KTC_STATE_ENC_ALARM          (1UL << 20)
#define SAFETY_DIAG_PKE_BUS_ALARM                (1UL << 21)
#define SAFETY_DIAG_PKE_REG_AND_LOGIC_ALARM      (1UL << 22)
#define SAFETY_DIAG_PKE_STATE_ENC_ALARM          (1UL << 23)
#define SAFETY_DIAG_TMC_BUS_ALARM                (1UL << 24)
#define SAFETY_DIAG_TMC_REG_ALARM                (1UL << 25)
#define SAFETY_DIAG_TMC_STATE_ENC_ALARM          (1UL << 26)
#define SAFETY_DIAG_KDC_BUS_ALARM                (1UL << 27)
#define SAFETY_DIAG_KDC_REG_ALARM                (1UL << 28)
#define SAFETY_DIAG_KDC_STATE_ENC_ALARM          (1UL << 29)
#define SAFETY_DIAG_ESW_KAT_ERR                  (1UL << 31)

#define R_SAFETY_DIAGNOSIS_1      0x524UL
#define SAFETY_DIAG_PMU_LOGIC_ALARM              (1UL << 0)
#define SAFETY_DIAG_PMU_STATE_ENC_ALARM          (1UL << 1)
#define SAFETY_DIAG_MPU_BUS_ALARM                (1UL << 3)
#define SAFETY_DIAG_MPU_REG_AND_LOGIC_ALARM      (1UL << 4)
#define SAFETY_DIAG_BCU_STATE_ENC_ALARM          (1UL << 6)
#define SAFETY_DIAG_SAC_BUS_ALARM                (1UL << 9)
#define SAFETY_DIAG_SAC_REG_ALARM                (1UL << 10)
#define SAFETY_DIAG_SRAM_BUS_ALARM               (1UL << 12)
#define SAFETY_DIAG_SRAM_STATE_ENC_ALARM         (1UL << 13)
#define SAFETY_DIAG_SRAM_MEM_CHK_ALARM           (1UL << 14)
#define SAFETY_DIAG_PLIC_BUS_ALARM               (1UL << 15)
#define SAFETY_DIAG_PLIC_REG_ALARM               (1UL << 16)
#define SAFETY_DIAG_CPU_BUS_ALARM                (1UL << 18)
#define SAFETY_DIAG_CPU_REG_AND_LOGIC_ALARM      (1UL << 19)
#define SAFETY_DIAG_TIM_BUS_ALARM                (1UL << 21)
#define SAFETY_DIAG_TIM_REG_ALARM                (1UL << 22)
#define SAFETY_DIAG_TIM_WD_ALARM                 (1UL << 23)
#define SAFETY_DIAG_OMC_BUS_ALARM                (1UL << 24)
#define SAFETY_DIAG_OMC_REG_ALARM                (1UL << 25)
#define SAFETY_DIAG_OMC_STATE_ENC_ALARM          (1UL << 26)
#define SAFETY_DIAG_CC_BUS_ALARM                 (1UL << 27)
#define SAFETY_DIAG_CC_REG_ALARM                 (1UL << 28)
#define SAFETY_DIAG_CC_STATE_ENC_ALARM           (1UL << 29)
#define SAFETY_DIAG_EXT_MECH_ALARM               (1UL << 31)

#define R_SCRATCH_0               0x530UL
#define R_DEVICE_LIFECYCLE        0x540UL
#define R_CUSTOM_0                0x544UL
#define R_CUSTOM_1                0x548UL
#define R_CUSTOM_2                0x54CUL
#define R_CUSTOM_3                0x550UL
#define R_CUSTOM_4                0x554UL
#define R_CUSTOM_5                0x558UL
#define R_CUSTOM_6                0x55CUL
#define R_CUSTOM_7                0x560UL
#define R_CUSTOM_8                0x564UL
#define R_CUSTOM_9                0x568UL
#define R_CUSTOM_10               0x56CUL
#define R_CUSTOM_11               0x570UL
#define R_CUSTOM_12               0x574UL
#define R_CUSTOM_13               0x578UL
#define R_CUSTOM_14               0x57CUL
#define R_CUSTOM_15               0x580UL
#define R_CUSTOM_16               0x584UL
#define R_CUSTOM_17               0x588UL
#define R_CUSTOM_18               0x58CUL
#define R_CUSTOM_19               0x590UL
#define R_CUSTOM_20               0x594UL
#define R_CUSTOM_21               0x598UL
#define R_CUSTOM_22               0x59CUL
#define R_CUSTOM_23               0x5A0UL
#define SIC_CUSTOM_REGS           24UL /* max 24, by default 4 */

#define R_DEVICE_KEYS_PERSO_STATUS 0x5B4UL
#define KEYS_PERSO_STATUS_PERSO_OBLITERATED (1UL << 0)
#define KEYS_PERSO_STATUS_DGOK_VALID        (1UL << 1)
#define KEYS_PERSO_STATUS_KEYSPLIT_1_VALID  (1UL << 2)
#define KEYS_PERSO_STATUS_KEYSPLIT_2_VALID  (1UL << 3)
#define KEYS_PERSO_STATUS_KEYSPLIT_3_VALID  (1UL << 4)
#define KEYS_PERSO_STATUS_KEYSPLIT_4_VALID  (1UL << 5)
#define KEYS_PERSO_STATUS_KEYSPLIT_5_VALID  (1UL << 6)
#define KEYS_PERSO_STATUS_KEYSPLIT_6_VALID  (1UL << 7)
#define KEYS_PERSO_STATUS_KEYSPLIT_7_VALID  (1UL << 8)
#define DEVICE_KEYS_PERSO_STATUS_VALID      (1UL << 30)
#define DEVICE_KEYS_PERSO_STATUS_UPDATED    (1UL << 31 | 1UL << 30)
#define DEVICE_KEYS_PERSO_STATUS_MASK       (1UL << 31 | 1UL << 30)

#define R_DEVICE_ROOT_TABLE_STATUS 0x5B8UL
#define ROOT_TABLE_STATUS_EMPTY       0x1UL
#define ROOT_TABLE_STATUS_VALID       0x2UL
#define ROOT_TABLE_STATUS_OBLITERATED 0x3UL
#define ROOT_TABLE_STATUS_MASK        0x3UL
#define DEVICE_ROOT_TABLE_STATUS_VALID   (1UL << 30)
#define DEVICE_ROOT_TABLE_STATUS_UPDATED (1UL << 31 | 1UL << 30)
#define DEVICE_ROOT_TABLE_STATUS_MASK    (1UL << 31 | 1UL << 30)

#define R_SBOOT_HASH_0            0x5E0UL
#define SIC_SBOOT_HASH_REGS       8UL

/* SIC1 messaging registers */
#define R_ESW2HLOS_D0             0x600UL
#define R_ESW2HLOS_D1             0x604UL
#define R_ESW2HLOS_D2             0x608UL
#define R_ESW2HLOS_D3             0x60CUL
#define R_ESW2HLOS_D4             0x610UL
#define R_ESW2HLOS_D5             0x614UL
#define R_ESW2HLOS_D6             0x618UL
#define R_ESW2HLOS_D7             0x61CUL
#define R_ESW2HLOS_LENGTH         0x620UL

#define R_HLOS2ESW_D0             0x630UL
#define R_HLOS2ESW_D1             0x634UL
#define R_HLOS2ESW_D2             0x638UL
#define R_HLOS2ESW_D3             0x63CUL
#define R_HLOS2ESW_D4             0x640UL
#define R_HLOS2ESW_D5             0x644UL
#define R_HLOS2ESW_D6             0x648UL
#define R_HLOS2ESW_D7             0x64CUL
#define R_HLOS2ESW_LENGTH         0x650UL

/* SIC2 messaging registers */
#define R_ESW2HLOS0_D0            0x600UL
#define R_ESW2HLOS0_D1            0x604UL
#define R_ESW2HLOS0_D2            0x608UL
#define R_ESW2HLOS0_D3            0x60CUL
#define R_HLOS2ESW0_D0            0x610UL
#define R_HLOS2ESW0_D1            0x614UL
#define R_HLOS2ESW0_D2            0x618UL
#define R_HLOS2ESW0_D3            0x61CUL
#define R_HLOS2ESW0_LOCK          0x620UL

#define R_ESW2HLOS1_D0            0x624UL
#define R_ESW2HLOS1_D1            0x628UL
#define R_ESW2HLOS1_D2            0x62CUL
#define R_ESW2HLOS1_D3            0x630UL
#define R_HLOS2ESW1_D0            0x634UL
#define R_HLOS2ESW1_D1            0x638UL
#define R_HLOS2ESW1_D2            0x63CUL
#define R_HLOS2ESW1_D3            0x640UL
#define R_HLOS2ESW1_LOCK          0x644UL

#define SIC_INSTANCE_OFFSET       0x24UL
#define MAX_SIC_INSTANCES         64UL

/*
 * Definitions for the SIC messaging protocol.
 */
#define SIC_DATA_REGS 8UL
#define SIC2_DATA_REGS 4UL

#ifndef _ASMLANGUAGE

typedef struct {
    uint32_t hdr;
} cmrt_sic_header_t;

#endif

/*
 * Commands for the SIC messaging protocol v1.
 */
#define CMD_REQUEST  1UL
#define CMD_RESPONSE 2UL
#define CMD_DATA     3UL

/*
 * Commands for the SIC messaging protocol v2.
 */
#define CMD_CONTROL  4UL

#define GET_HEADER_VER(h) (((h) & 0xf0000000UL) >> 28)
#define GET_HEADER_SRC(h) (((h) & 0x0fff0000UL) >> 16)
#define GET_HEADER_CMD(h) (((h) & 0x0000f000UL) >> 12)
#define GET_HEADER_DST(h)  ((h) & 0x00000fffUL)
#define SET_HEADER_VER(h, v) ((h) = ((h) & 0x0fffffffUL) | (((v) & 0xfUL) << 28))
#define SET_HEADER_SRC(h, v) ((h) = ((h) & 0xf000ffffUL) | (((v) & 0xfffUL) << 16))
#define SET_HEADER_CMD(h, v) ((h) = ((h) & 0xffff0fffUL) | (((v) & 0xfUL) << 12))
#define SET_HEADER_DST(h, v) ((h) = ((h) & 0xfffff000UL) | ((v) & 0xfffUL))

#define IS_HLOS_FLOWID(f) (((f) & 0x800UL) != 0u)

#define ESW_DD_FLOWID     0x000UL /* eSW SIC device driver flowid */
#define HLOS_DD_FLOWID    0x800UL /* HLOS kernel driver flowid */

#define MIN_ESW_FLOWID    0x000UL
#define MAX_ESW_FLOWID    0x7FFUL
#define MIN_HLOS_FLOWID   0x800UL
#define MAX_HLOS_FLOWID   0xFFFUL

#define FLOWID_MASK       0xFFFUL
/* In v2 flowid is in bits 0-11, sicid in bits 16-27. */
#define GET_FLOWID(f) ((f) & FLOWID_MASK)
#define SET_FLOWID(f, i) ((f) | ((i) & FLOWID_MASK))
#define GET_SICID(f) (((f) & 0x0FFF0000UL) >> 16)
#define SET_SICID(f, i) ((f) | (((i) & 0x00000FFFUL) << 16))
#define LOCAL_SICID 0x00000FFFUL
#define IS_LOCAL_SICID(f) (GET_SICID(f) == LOCAL_SICID)
#define SET_LOCAL_SICID(f) (SET_SICID(f, LOCAL_SICID))
/* In v2 flowid is in bits 0-11, timeout in bits 12-31. */
#define GET_SICTIMEOUT(f) (((f) & 0xFFFFF000UL) >> 12)
#define SET_SICTIMEOUT(f, i) ((f) | (((i) & 0x000FFFFFUL) << 12))

/*
 * Sideband v1 information in R_HLOS2ESW_LENGTH and R_ESW2HLOS_LENGTH.
 * The same values are used as CMD_CONTROL commands in v2.
 */
#define SIDEBAND_MASK     0xfffff000UL
#define SIDEBAND_RESERVED 0x00UL
#define SIDEBAND_PING     0x01UL /* Check if eSW SIC driver is alive */
#define SIDEBAND_PONG0    0x02UL /* SIC driver is alive, no listeners */
#define SIDEBAND_PONG1    0x03UL /* SIC driver is alive, 1+ listeners */
#define SIDEBAND_PONG2    0x04UL /* SIC driver is alive, flow is served */
#define SIDEBAND_ENOSPC   0x08UL /* Not enough buffer space for the request */
#define SIDEBAND_EBUSY    0x09UL /* Buffer is not receiving, try again */
#define SIDEBAND_ENOENT   0x0aUL /* Destination not found for the request */
#define SIDEBAND_EPIPE    0x0bUL /* Currently serving another request */
#define SIDEBAND_EPERM    0x0cUL /* Container does not have access to SAC area */
#define SIDEBAND_RESET    0x0fUL /* Reset communications */

#ifndef _ASMLANGUAGE

/*
 * HLOS messaging protocol v1 structures.
 */
typedef struct {
    cmrt_sic_header_t hdr;
    uint32_t address;
    uint32_t length;
} cmrt_sic_request_t;

typedef struct {
    cmrt_sic_header_t hdr;
    uint32_t address;
    uint32_t length;
} cmrt_sic_response_t;

typedef struct {
    cmrt_sic_header_t hdr;
    uint32_t data[SIC_DATA_REGS - 1];
} cmrt_sic_mdata_t;

typedef struct {
    uint32_t data[SIC_DATA_REGS];
} cmrt_sic_raw_t;

typedef union {
    cmrt_sic_header_t hdr;
    cmrt_sic_request_t req;
    cmrt_sic_response_t res;
    cmrt_sic_mdata_t data;
    cmrt_sic_raw_t raw;
} cmrt_sic_message_t;

/*
 * HLOS messaging protocol v2 structures.
 */
typedef struct {
    cmrt_sic_header_t hdr;
    uint32_t length;
    uint32_t address_high;
    uint32_t address_low;
} cmrt_sic2_request_t;

typedef struct {
    cmrt_sic_header_t hdr;
    uint32_t length;
    uint32_t address_high; /* status if length is zero */
    uint32_t address_low; /* error if length is zero */
} cmrt_sic2_response_t;

typedef struct {
    cmrt_sic_header_t hdr;
    uint32_t data[SIC2_DATA_REGS - 1];
} cmrt_sic2_data_t;

typedef struct {
    cmrt_sic_header_t hdr;
    uint32_t cmd;
    uint32_t data[SIC2_DATA_REGS - 2];
} cmrt_sic2_control_t;

typedef struct {
    uint32_t data[SIC2_DATA_REGS];
} cmrt_sic2_raw_t;

typedef union {
    cmrt_sic_header_t hdr;
    cmrt_sic2_request_t req;
    cmrt_sic2_response_t res;
    cmrt_sic2_data_t data;
    cmrt_sic2_control_t ctrl;
    cmrt_sic2_raw_t raw;
} cmrt_sic2_message_t;

#endif
#endif
