/*
<<<<<<< HEAD
 * Copyright (c) 2021-2023, Arm Limited. All rights reserved.
=======
 * Copyright (c) 2021-2025, Arm Limited. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>

#if TRANSFER_LIST
#include <tpm_event_log.h>
#endif
#include <plat/arm/common/plat_arm.h>
#include <tools_share/zero_oid.h>

#include <drivers/auth/crypto_mod.h>
#include <drivers/measured_boot/metadata.h>
#include <event_measure.h>
#include <event_print.h>
#include <tools_share/zero_oid.h>

/* Event Log data */
#if TRANSFER_LIST
static uint8_t *event_log;
#else
static uint8_t event_log[PLAT_ARM_EVENT_LOG_MAX_SIZE];
#endif

static const struct event_log_hash_info crypto_hash_info = {
	.func = crypto_mod_calc_hash,
	.ids = (const uint32_t[]){ CRYPTO_MD_ID },
	.count = 1U,
};

/* FVP table with platform specific image IDs, names and PCRs */
const event_log_metadata_t fvp_event_log_metadata[] = {
	{ FW_CONFIG_ID, MBOOT_FW_CONFIG_STRING, PCR_0 },
	{ TB_FW_CONFIG_ID, MBOOT_TB_FW_CONFIG_STRING, PCR_0 },
	{ BL2_IMAGE_ID, MBOOT_BL2_IMAGE_STRING, PCR_0 },

<<<<<<< HEAD
	{ EVLOG_INVALID_ID, NULL, (unsigned int)(-1) }	/* Terminator */
};

/* FVP table with platform specific image IDs and metadata. Intentionally not a
 * const struct, some members might set by bootloaders during trusted boot.
 */
struct rss_mboot_metadata fvp_rss_mboot_metadata[] = {
	{
		.id = FW_CONFIG_ID,
		.slot = U(6),
		.signer_id_size = SIGNER_ID_MIN_SIZE,
		.sw_type = RSS_MBOOT_FW_CONFIG_STRING,
		.pk_oid = ZERO_OID,
		.lock_measurement = true },
	{
		.id = TB_FW_CONFIG_ID,
		.slot = U(7),
		.signer_id_size = SIGNER_ID_MIN_SIZE,
		.sw_type = RSS_MBOOT_TB_FW_CONFIG_STRING,
		.pk_oid = ZERO_OID,
		.lock_measurement = true },
	{
		.id = BL2_IMAGE_ID,
		.slot = U(8),
		.signer_id_size = SIGNER_ID_MIN_SIZE,
		.sw_type = RSS_MBOOT_BL2_STRING,
		.pk_oid = ZERO_OID,
		.lock_measurement = true },

	{
		.id = RSS_MBOOT_INVALID_ID }
=======
	{ EVLOG_INVALID_ID, NULL, (unsigned int)(-1) } /* Terminator */
>>>>>>> upstream_import/upstream_v2_14_1
};

void bl1_plat_mboot_init(void)
{
	size_t event_log_max_size;
	int rc;

<<<<<<< HEAD
	rss_measured_boot_init(fvp_rss_mboot_metadata);
=======
#if TRANSFER_LIST
	event_log_max_size = PLAT_ARM_EVENT_LOG_MAX_SIZE;

	event_log =
		transfer_list_event_log_extend(secure_tl, event_log_max_size);
	assert(event_log != NULL);
#else
	event_log_max_size = sizeof(event_log);
#endif

	rc = event_log_init_and_reg(event_log, event_log + event_log_max_size,
				    &crypto_hash_info);
	if (rc < 0) {
		ERROR("Failed to initialize event log (%d).\n", rc);
		panic();
	}

	rc = event_log_write_header();
	if (rc < 0) {
		ERROR("Failed to write event log header (%d).\n", rc);
		panic();
	}
>>>>>>> upstream_import/upstream_v2_14_1
}

void bl1_plat_mboot_finish(void)
{
	size_t event_log_cur_size = event_log_get_cur_size(event_log);

#if TRANSFER_LIST
	uint8_t *rc = transfer_list_event_log_finish(
		secure_tl, (uintptr_t)event_log + event_log_cur_size);

	/* Ensure changes are visible to the next stage. */
	flush_dcache_range((uintptr_t)secure_tl, secure_tl->size);

	if (rc != NULL) {
		return;
	}
#else
	int rc = arm_set_tb_fw_info((uintptr_t)event_log, event_log_cur_size,
				PLAT_ARM_EVENT_LOG_MAX_SIZE);
	if (rc == 0) {
		return;
	}
#endif

	/*
	 * Panic if we fail to set up the event log for the next stage. This is a fatal
	 * error because, on the FVP platform, BL2 software assumes that a valid
	 * Event Log buffer exists and will use the same Event Log buffer to append image
	 * measurements.
	 */
	panic();
}
