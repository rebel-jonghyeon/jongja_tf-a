/*
<<<<<<< HEAD
 * Copyright (c) 2021-2023, Arm Limited. All rights reserved.
=======
 * Copyright (c) 2021-2025, Arm Limited. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <stdint.h>

#include <plat/arm/common/plat_arm.h>
#include <plat/common/platform.h>

#include <common/desc_image_load.h>
#include <drivers/auth/crypto_mod.h>
#include <event_measure.h>
#include <event_print.h>

<<<<<<< HEAD
=======
extern event_log_metadata_t fvp_event_log_metadata[];

>>>>>>> upstream_import/upstream_v2_14_1
int plat_mboot_measure_image(unsigned int image_id, image_info_t *image_data)
{
	int err;

	/* Calculate image hash and record data in Event Log */
	err = event_log_measure_and_record(image_data->image_base,
					   image_data->image_size,
					   image_id,
					   fvp_event_log_metadata);
	if (err != 0) {
		ERROR("%s%s image id %u (%i)\n",
		      "Failed to ", "record in event log", image_id, err);
		return err;
	}

<<<<<<< HEAD
	/* Calculate image hash and record data in RSS */
	err = rss_mboot_measure_and_record(fvp_rss_mboot_metadata,
					   image_data->image_base,
					   image_data->image_size,
					   image_id);
	if (err != 0) {
		ERROR("%s%s image id %u (%i)\n",
		      "Failed to ", "record in RSS", image_id, err);
		rc = (rc == 0) ? err : -1;
	}

	return rc;
=======
	return 0;
}

int plat_mboot_measure_key(const void *pk_oid, const void *pk_ptr,
			   size_t pk_len)
{
	return 0;
>>>>>>> upstream_import/upstream_v2_14_1
}

int plat_mboot_measure_key(const void *pk_oid, const void *pk_ptr,
			   size_t pk_len)
{
	return rss_mboot_set_signer_id(fvp_rss_mboot_metadata, pk_oid, pk_ptr,
				       pk_len);
}
