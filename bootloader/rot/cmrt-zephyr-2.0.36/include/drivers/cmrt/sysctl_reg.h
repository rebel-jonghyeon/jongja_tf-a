/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_SYSCTL_REG_H
#define CMRT_SYSCTL_REG_H

#define CMRT_SYSCTL_BASE              0x00000000UL

/* FPGA system control register offsets. */
#define R_SYSCTL_VERSION               0x00UL
#define R_SYSCTL_CONTROL               0x04UL
#define R_SYSCTL_STATUS                0x0CUL
#define R_SYSCTL_SW_SCRATCH            0x10UL
#define R_SYSCTL_SOC_INTERRUPT_IN      0x14UL
#define R_SYSCTL_SOC_INTERRUPT_OUT     0x18UL
#define R_SYSCTL_IDLE                  0x1CUL
#define R_SYSCTL_ISOLATE               0x20UL
#define R_SYSCTL_RESET_IN_PROGRESS     0x24UL
#define R_SYSCTL_POWER_MANAGEMENT      0x28UL
#define R_SYSCTL_FMC_TDV               0x2CUL
#define R_SYSCTL_FMC_OUTPUT            0x30UL
#define R_SYSCTL_KTC_OUTPUT0           0x34UL
#define R_SYSCTL_KTC_OUTPUT1           0x38UL
#define R_SYSCTL_KTC_OUTPUT2           0x3CUL
#define R_SYSCTL_KTC_OUTPUT3           0x40UL
#define R_SYSCTL_KTC_METADATA0         0x44UL
#define R_SYSCTL_KTC_METADATA1         0x48UL
#define R_SYSCTL_KTC_CONTROL           0x4CUL
#define KTC_CONTROL_KEY_CONSUMED (1 << 0)
#define KTC_CONTROL_KEY_VALID    (1 << 1)
#define R_SYSCTL_KTC_CORE_OUTPUT       0x50UL
#define KTC_CORE_OUTPUT_DEST(s) (((s) & 0xF0000) >> 16)
#define KTC_CORE_OUTPUT_BLOCKS(s) (((s) & 0xFF00) >> 8)
#define KTC_CORE_OUTPUT_BLOCKID(s) ((s) & 0xff)
#define R_SYSCTL_FIPS_MODE             0x54UL
#define R_SYSCTL_TRNG_CHARACTERISATION 0x58UL
#define R_SYSCTL_TRNG_VALIDATION1      0x5CUL
#define R_SYSCTL_TRNG_VALIDATION2      0x60UL
#define R_SYSCTL_TRNG_VALIDATION3      0x64UL
#define R_SYSCTL_FEATURE_OUT1          0x70UL
#define R_SYSCTL_FEATURE_OUT2          0x74UL
#define R_SYSCTL_FEATURE_OUT3          0x78UL

#define R_SYSCTL_DELAY_OTP            0x380UL
#define R_SYSCTL_DELAY_SAC            0x384UL

#define R_SYSCTL_PERF_COUNTER_CONFIG  0x3C0UL
#define R_SYSCTL_PERF_HW_BOOT_COUNT   0x3C4UL
#define R_SYSCTL_PERF_ADDRESS_1       0x3C8UL
#define R_SYSCTL_PERF_COUNT_1         0x3CCUL
#define R_SYSCTL_PERF_ADDRESS_2       0x3D0UL
#define R_SYSCTL_PERF_COUNT_2         0x3D4UL
#define R_SYSCTL_PERF_ADDRESS_3       0x3D8UL
#define R_SYSCTL_PERF_COUNT_3         0x3DCUL
#define R_SYSCTL_PERF_ADDRESS_4       0x3E0UL
#define R_SYSCTL_PERF_COUNT_4         0x3E4UL
#define R_SYSCTL_PERF_ADDRESS_5       0x3E8UL
#define R_SYSCTL_PERF_COUNT_5         0x3ECUL
#define R_SYSCTL_PERF_ADDRESS_6       0x3F0UL
#define R_SYSCTL_PERF_COUNT_6         0x3F4UL
#define R_SYSCTL_PERF_ADDRESS_7       0x3F8UL
#define R_SYSCTL_PERF_COUNT_7         0x3FCUL
#define R_SYSCTL_PERF_ADDRESS_8       0x400UL
#define R_SYSCTL_PERF_COUNT_8         0x404UL
#define R_SYSCTL_PERF_ADDRESS_9       0x408UL
#define R_SYSCTL_PERF_COUNT_9         0x40CUL
#define R_SYSCTL_PERF_ADDRESS_10      0x410UL
#define R_SYSCTL_PERF_COUNT_10        0x414UL

/* R_SYSCTL_CONTROL */
#define CMRT_SYSCTL_RESET_HARD     (1UL << 0)
#define CMRT_SYSCTL_RESET_POWERON  (1UL << 1)
#define CMRT_SYSCTL_RESET_PDMA     (1UL << 8)
#define CMRT_SYSCTL_RESET_MASK     (CMRT_SYSCTL_RESET_HARD | CMRT_SYSCTL_RESET_POWERON)

/* R_SYSCTL_POWER_MANAGEMENT */
#define CMRT_SYSCTL_PMU_CSYSREQ    (1UL << 0)
#define CMRT_SYSCTL_PMU_CSYSACTIVE (1UL << 1)
#define CMRT_SYSCTL_PMU_CSYSACK    (1UL << 2)

/* R_SYSCTL_FIPS_MODE */
#define CMRT_SYSCTL_FIPS_ENTER     (1UL << 0)
#define CMRT_SYSCTL_FIPS_MODE      (1UL << 1)

/* R_SYSCTL_PERF_COUNTER_CONFIG */
#define CMRT_SYSCTL_PC_ENABLE_1          (1UL << 0)
#define CMRT_SYSCTL_PC_ON_WRITE_1        (1UL << 1)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_1  (1UL << 2)
#define CMRT_SYSCTL_PC_ENABLE_2          (1UL << 3)
#define CMRT_SYSCTL_PC_ON_WRITE_2        (1UL << 4)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_2  (1UL << 5)
#define CMRT_SYSCTL_PC_ENABLE_3          (1UL << 6)
#define CMRT_SYSCTL_PC_ON_WRITE_3        (1UL << 7)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_3  (1UL << 8)
#define CMRT_SYSCTL_PC_ENABLE_4          (1UL << 9)
#define CMRT_SYSCTL_PC_ON_WRITE_4        (1UL << 10)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_4  (1UL << 11)
#define CMRT_SYSCTL_PC_ENABLE_5          (1UL << 12)
#define CMRT_SYSCTL_PC_ON_WRITE_5        (1UL << 13)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_5  (1UL << 14)
#define CMRT_SYSCTL_PC_ENABLE_6          (1UL << 15)
#define CMRT_SYSCTL_PC_ON_WRITE_6        (1UL << 16)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_6  (1UL << 17)
#define CMRT_SYSCTL_PC_ENABLE_7          (1UL << 18)
#define CMRT_SYSCTL_PC_ON_WRITE_7        (1UL << 19)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_7  (1UL << 20)
#define CMRT_SYSCTL_PC_ENABLE_8          (1UL << 21)
#define CMRT_SYSCTL_PC_ON_WRITE_8        (1UL << 22)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_8  (1UL << 23)
#define CMRT_SYSCTL_PC_ENABLE_9          (1UL << 24)
#define CMRT_SYSCTL_PC_ON_WRITE_9        (1UL << 25)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_9  (1UL << 26)
#define CMRT_SYSCTL_PC_ENABLE_10         (1UL << 27)
#define CMRT_SYSCTL_PC_ON_WRITE_10       (1UL << 28)
#define CMRT_SYSCTL_PC_DISABLE_ON_HIT_10 (1UL << 29)

#endif
