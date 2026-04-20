/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_TMC_REG_H
#define CMRT_TMC_REG_H

#include <stdint.h>
#include "hwc_reg.h"

#define CMRT_TMC_BASE      0x00004000UL

/* TMC R_CORE_INTERRUPT bits. */
#define TMC_TRNG_ERROR         (1UL << 0)

/* TMC TRNG_DATA regs are in R_CORE_COUTPUT. */
#define TMC_OUTPUT_REGS        8UL
#define TMC_OUTPUT_SIZE        (TMC_OUTPUT_REGS * sizeof(uint32_t))

/* TMCv1 registers. */
#define R_TRNG_CONTROL         0x300UL
#define R_TRNG_STATUS_ERROR    0x310UL
#define R_TRNG_CONFIG          0x318UL
#define R_TRNG_FRODETUNE       0x324UL
#define R_TRNG_ALARMSTOP       0x32CUL
#define R_TRNG_SPB_TEST_CONFIG 0x338UL

/* TMCv2 registers. */
#define R_DRBG2_CONTROL         0x134UL
#define R_TRNG2_OUTPUT_0        0x300UL
#define R_TRNG2_OUTPUT_1        0x304UL
#define R_TRNG2_OUTPUT_2        0x308UL
#define R_TRNG2_OUTPUT_3        0x30CUL
#define R_TRNG2_STATUS          0x310UL
#define R_TRNG2_CONTROL         0x314UL
#define R_TRNG2_CONFIG          0x318UL
#define R_TRNG2_ALARMCNT        0x31CUL
#define TRNG2_ALARMCNT_8_FRO     0x0200FFUL
#define TRNG2_ALARMCNT_24_FRO    0x0600FFUL
#define R_TRNG2_FROENABLE       0x320UL
#define TRNG2_FROENABLE_8_FRO    0x00000FFUL
#define TRNG2_FROENABLE_24_FRO   0xFFFFFFUL
#define R_TRNG2_FRODETUNE       0x324UL
#define R_TRNG2_ALARMMASK       0x328UL
#define R_TRNG2_ALARMSTOP       0x32CUL
#define R_TRNG2_RAW_L           0x330UL
#define R_TRNG2_RAW_H           0x334UL
#define R_TRNG2_SPB_TESTS       0x338UL
#define R_TRNG2_COUNT           0x33CUL
#define R_TRNG2_RUN_CNT         0x340UL
#define R_TRNG2_RUN_1           0x344UL
#define R_TRNG2_RUN_2           0x348UL
#define R_TRNG2_RUN_3           0x34CUL
#define R_TRNG2_RUN_4           0x350UL
#define R_TRNG2_RUN_5           0x354UL
#define R_TRNG2_RUN_6_UP        0x358UL
#define R_TRNG2_MONOBITCNT      0x35CUL
#define R_TRNG2_POKER_3_0       0x360UL
#define R_TRNG2_POKER_7_4       0x364UL
#define R_TRNG2_POKER_B_8       0x368UL
#define R_TRNG2_POKER_F_C       0x36CUL
#define R_TRNG2_TEST            0x370UL
#define R_TRNG2_OPTIONS         0x378UL
#define R_TRNG2_EIP_REV         0x37CUL

#define TMC_CONTROL_GENERATE        0x01UL
#define TMC_CONTROL_INSTANTIATE     0x03UL
#define TMC_CONTROL_RESEED_GENERATE 0x04UL
#define TMC_CONTROL_UNINSTANTIATE   0x05UL
#define TMC_CONTROL_RESEED          0x06UL
#define TMC_CONTROL_HEALTH_CHECK    0x07UL

#define TMC_TRNG_CONTROL_STUCK_NRGB_MASK (1UL << 9)
#define TMC_TRNG_CONFIG_READ_TIMEOUT_1   (1UL << 16)

/* Used in validation mode instead of SUCCESS 0xF0 */
#define HWC_TMC_STATUS_SUCCESS_TEST  0xF3UL

#define R_TRNG2_EXTERNAL_ENTROPY_CONTROL 0x150UL

#define TMC_EXT_CTRL_NRBG_ONLY 0x00UL
#define TMC_EXT_CTRL_EXT_ONLY  0x01UL
#define TMC_EXT_CTRL_MIXED     0x03UL

#define R_TRNG2_EXTERNAL_ENTROPY_STATUS  0x154UL

#define TMC_EXT_ST_NEED_DATA ((1UL << 0) | (1UL << 9))
#define TMC_EXT_ST_DATA_FULL (1UL << 1)

#define TMC_EXT_NEED_DATA(v) (((v) & TMC_EXT_ST_NEED_DATA) == TMC_EXT_ST_NEED_DATA)
#define TMC_EXT_DATA_FULL(v) (((v) & TMC_EXT_ST_DATA_FULL) == TMC_EXT_ST_DATA_FULL)

/* WO. 128 bit wide. 0x200 - 0x20F */
#define R_TRNG2_EXTERNAL_ENTROPY_DATA    0x200UL

#endif
