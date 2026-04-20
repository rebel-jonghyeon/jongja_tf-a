/*
<<<<<<< HEAD
 * Copyright (c) 2022-2023, Arm Limited. All rights reserved.
=======
 * Copyright (c) 2022-2025, Arm Limited and Contributors. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>

<<<<<<< HEAD
#include <drivers/arm/rss_comms.h>
#include <drivers/measured_boot/rss/rss_measured_boot.h>
#include <lib/psa/measured_boot.h>
=======
#include <drivers/measured_boot/metadata.h>
#include <drivers/measured_boot/rse/rse_measured_boot.h>
>>>>>>> upstream_import/upstream_v2_14_1
#include <tools_share/zero_oid.h>

#include <plat/arm/common/plat_arm.h>
#include <platform_def.h>
#include <tc_rse_comms.h>

/* Table with platform specific image IDs and metadata. Intentionally not a
 * const struct, some members might set by bootloaders during trusted boot.
 */
struct rse_mboot_metadata tc_rse_mboot_metadata[] = {
	{
		.id = FW_CONFIG_ID,
		.slot = U(6),
		.signer_id_size = SIGNER_ID_MIN_SIZE,
<<<<<<< HEAD
		.sw_type = RSS_MBOOT_FW_CONFIG_STRING,
=======
		.sw_type = MBOOT_FW_CONFIG_STRING,
>>>>>>> upstream_import/upstream_v2_14_1
		.pk_oid = ZERO_OID,
		.lock_measurement = true },
	{
		.id = TB_FW_CONFIG_ID,
		.slot = U(7),
		.signer_id_size = SIGNER_ID_MIN_SIZE,
<<<<<<< HEAD
		.sw_type = RSS_MBOOT_TB_FW_CONFIG_STRING,
=======
		.sw_type = MBOOT_TB_FW_CONFIG_STRING,
>>>>>>> upstream_import/upstream_v2_14_1
		.pk_oid = ZERO_OID,
		.lock_measurement = true },
	{
		.id = BL2_IMAGE_ID,
		.slot = U(8),
		.signer_id_size = SIGNER_ID_MIN_SIZE,
<<<<<<< HEAD
		.sw_type = RSS_MBOOT_BL2_STRING,
=======
		.sw_type = MBOOT_BL2_IMAGE_STRING,
>>>>>>> upstream_import/upstream_v2_14_1
		.pk_oid = ZERO_OID,
		.lock_measurement = true },

	{
		.id = RSE_MBOOT_INVALID_ID }
};

void bl1_plat_mboot_init(void)
{
	/* Initialize the communication channel between AP and RSE */
	(void)plat_rse_comms_init();

<<<<<<< HEAD
	rss_measured_boot_init(tc_rss_mboot_metadata);
=======
	rse_measured_boot_init(tc_rse_mboot_metadata);
>>>>>>> upstream_import/upstream_v2_14_1
}

void bl1_plat_mboot_finish(void)
{
	/* Nothing to do. */
}
