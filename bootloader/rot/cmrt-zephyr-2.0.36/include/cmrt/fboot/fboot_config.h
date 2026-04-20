/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef FBOOT_CONFIG_H
#define FBOOT_CONFIG_H

#include <stdint.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/cmrt.h>

/*
 * Sboot is located at the beginning of OTP's eSW region (or in ROM).
 */
#ifdef CONFIG_CMRT_SBOOT_IN_ROM
#define SBOOT_LOCSIZE (CONFIG_CMRT_MACHINE_ROM_SIZE)
#define SBOOT_MAXSIZE (SBOOT_LOCSIZE - sizeof(uint32_t) * 2)
#else
#define SBOOT_LOCSIZE (CMRT_OTP_SIZE)
#define SBOOT_MAXSIZE (SBOOT_LOCSIZE - sizeof(cmrt_otp_layout_t) - CONFIG_CMRT_OMC_ESW_RSVD_WORDS * sizeof(uint32_t) - sizeof(uint32_t) * 2)
#endif

/*
 * Sboot is copied to the end of SRAM.
 */
#define SBOOT_START (CONFIG_SRAM_BASE_ADDRESS + KB(CONFIG_SRAM_SIZE) - SBOOT_LOCSIZE)

/*
 * Supervisor is located in ROM after sboot or in Flash.
 */
#ifdef CONFIG_CMRT_SUPERVISOR_IN_ROM
#define OS_LOCATION_A (RISCV_ROM_BASE + CONFIG_CMRT_MACHINE_ROM_SIZE)
#else
#include <drivers/cmrt/sac_mem.h>
#define OS_LOCATION_A (SAC_MEMORY_BASE + (CONFIG_FPGA_EXTMEM_SIZE / 2))
#ifdef CONFIG_CMRT_AB_LOCATION_SUPPORT
#define OS_LOCATION_B (OS_LOCATION_A + (CONFIG_FPGA_EXTMEM_SIZE / 4))
#endif
#endif

#endif
