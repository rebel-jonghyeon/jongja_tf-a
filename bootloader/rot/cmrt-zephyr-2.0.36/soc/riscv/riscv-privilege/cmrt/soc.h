/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */
#ifndef RISCV_CMRT_SOC_H
#define RISCV_CMRT_SOC_H

#include <soc_common.h>
#include <devicetree.h>

/* Timer configuration */
#define RISCV_MTIME_BASE             0x0007414CUL
#define RISCV_MTIMECMP_BASE          0x00074154UL

#define CONFIG_CMRT_ROM_BASE DT_REG_ADDR(DT_NODELABEL(rom))
#define CONFIG_CMRT_ROM_SIZE DT_REG_SIZE(DT_NODELABEL(rom))
#define CONFIG_CMRT_PKERAM_SIZE DT_REG_SIZE(DT_NODELABEL(pkeram))

/* lib-c hooks required RAM defined variables */
#ifdef CONFIG_SUPERVISOR_MODE
#define RISCV_ROM_BASE               (CONFIG_CMRT_ROM_BASE +	\
				      CONFIG_PIX_OFFSET)
#define RISCV_ROM_SIZE               (CONFIG_CMRT_ROM_SIZE -	\
				      CONFIG_PIX_OFFSET)
#define RISCV_RAM_BASE               (CONFIG_SRAM_BASE_ADDRESS +	\
				      CONFIG_CMRT_PKERAM_SIZE +		\
				      CONFIG_CMRT_MACHINE_RAM_SIZE +	\
				      CONFIG_PIX_OFFSET)
#define RISCV_RAM_SIZE               (KB(CONFIG_SRAM_SIZE) -		\
				      CONFIG_CMRT_PKERAM_SIZE -		\
				      CONFIG_CMRT_MACHINE_RAM_SIZE -	\
				      CONFIG_PIX_OFFSET)
#else
#define RISCV_ROM_BASE               (CONFIG_CMRT_ROM_BASE +	\
				      CONFIG_PIX_OFFSET)
#define RISCV_ROM_SIZE               (CONFIG_CMRT_ROM_SIZE -	\
				      CONFIG_PIX_OFFSET)
#define RISCV_RAM_BASE               (CONFIG_SRAM_BASE_ADDRESS +	\
				      CONFIG_CMRT_PKERAM_SIZE +		\
				      CONFIG_PIX_OFFSET)
#define RISCV_RAM_SIZE               (KB(CONFIG_SRAM_SIZE) -	\
				      CONFIG_CMRT_PKERAM_SIZE -	\
				      CONFIG_PIX_OFFSET)
#endif

#endif /* RISCV_CMRT_SOC_H */
