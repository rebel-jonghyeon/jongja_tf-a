/*
<<<<<<< HEAD:plat/arm/board/rdn2/rdn2_ras.c
 * Copyright (c) 2023, ARM Limited and Contributors. All rights reserved.
=======
 * Copyright (c) 2023-2024, Arm Limited and Contributors. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1:plat/arm/board/neoverse_rd/platform/rdn2/rdn2_ras.c
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>
<<<<<<< HEAD:plat/arm/board/rdn2/rdn2_ras.c
#include <sgi_ras.h>
#include <sgi_sdei.h>

struct sgi_ras_ev_map plat_ras_map[] = {
	/* Non Secure base RAM ECC CE interrupt */
	{SGI_SDEI_DS_EVENT_0, NS_RAM_ECC_CE_INT, SGI_RAS_INTR_TYPE_SPI},

	/* Non Secure base RAM ECC UE interrupt */
	{SGI_SDEI_DS_EVENT_0, NS_RAM_ECC_UE_INT, SGI_RAS_INTR_TYPE_SPI},

	/* CPU 1-bit ECC CE error interrupt */
	{SGI_SDEI_DS_EVENT_1, PLAT_CORE_FAULT_IRQ, SGI_RAS_INTR_TYPE_PPI}
=======

#include <nrd_ras.h>
#include <nrd_sdei.h>

struct nrd_ras_ev_map plat_ras_map[] = {
	/* Non Secure base RAM ECC CE interrupt */
	{NRD_SDEI_DS_EVENT_0, NRD_CSS_NS_RAM_ECC_CE_INT, NRD_RAS_INTR_TYPE_SPI},

	/* Non Secure base RAM ECC UE interrupt */
	{NRD_SDEI_DS_EVENT_0, NRD_CSS_NS_RAM_ECC_UE_INT, NRD_RAS_INTR_TYPE_SPI},

	/* CPU 1-bit ECC CE error interrupt */
	{NRD_SDEI_DS_EVENT_1, PLAT_CORE_FAULT_IRQ, NRD_RAS_INTR_TYPE_PPI}
>>>>>>> upstream_import/upstream_v2_14_1:plat/arm/board/neoverse_rd/platform/rdn2/rdn2_ras.c
};

/* RAS error record list definition, used by the common RAS framework. */
struct err_record_info plat_err_records[] = {
	/* Base element RAM Non-secure error record. */
<<<<<<< HEAD:plat/arm/board/rdn2/rdn2_ras.c
	ERR_RECORD_MEMMAP_V1(SOC_NS_RAM_ERR_REC_BASE, 4, NULL,
				&sgi_ras_sram_intr_handler, 0),
	ERR_RECORD_SYSREG_V1(0, 1, NULL, &sgi_ras_cpu_intr_handler, 0),
=======
	ERR_RECORD_MEMMAP_V1(NRD_CSS_NS_RAM_ERR_REC_BASE, 4, NULL,
				&nrd_ras_sram_intr_handler, 0),
	ERR_RECORD_SYSREG_V1(0, 1, NULL, &nrd_ras_cpu_intr_handler, 0),
>>>>>>> upstream_import/upstream_v2_14_1:plat/arm/board/neoverse_rd/platform/rdn2/rdn2_ras.c
};

/* RAS error interrupt list definition, used by the common RAS framework. */
struct ras_interrupt plat_ras_interrupts[] = {
	{
		.intr_number = PLAT_CORE_FAULT_IRQ,
		.err_record = &plat_err_records[1],
	}, {
<<<<<<< HEAD:plat/arm/board/rdn2/rdn2_ras.c
		.intr_number = NS_RAM_ECC_CE_INT,
		.err_record = &plat_err_records[0],
	}, {
		.intr_number = NS_RAM_ECC_UE_INT,
=======
		.intr_number = NRD_CSS_NS_RAM_ECC_CE_INT,
		.err_record = &plat_err_records[0],
	}, {
		.intr_number = NRD_CSS_NS_RAM_ECC_UE_INT,
>>>>>>> upstream_import/upstream_v2_14_1:plat/arm/board/neoverse_rd/platform/rdn2/rdn2_ras.c
		.err_record = &plat_err_records[0],
	},
};

/* Registers the RAS error record list with common RAS framework. */
REGISTER_ERR_RECORD_INFO(plat_err_records);
/* Registers the RAS error interrupt info list with common RAS framework. */
REGISTER_RAS_INTERRUPTS(plat_ras_interrupts);

/* Platform RAS handling config data definition */
<<<<<<< HEAD:plat/arm/board/rdn2/rdn2_ras.c
struct plat_sgi_ras_config ras_config = {
=======
struct plat_nrd_ras_config ras_config = {
>>>>>>> upstream_import/upstream_v2_14_1:plat/arm/board/neoverse_rd/platform/rdn2/rdn2_ras.c
	plat_ras_map,
	ARRAY_SIZE(plat_ras_map)
};
