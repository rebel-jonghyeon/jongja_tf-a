/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>

#include <zephyr.h>
#include <sys/util.h>
#include <drivers/cmrt/dd.h>

#include "img.h"
#include "supervisor.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

int cmrt_img_footer_parse(void *blob, size_t size, cmrt_img_footer_t *footer)
{
	if (!is_aligned(blob, 4u) || !is_aligned(size, 4u) ||
	    blob == NULL || size == 0u || footer == NULL) { return -EINVAL; }

	(void)memset(footer, 0, sizeof(cmrt_img_footer_t));

	uint8_t *data = blob;
	data += size - sizeof(uint32_t);
	footer->footer_length = *(uint32_t *)data;
	if (((footer->footer_length & 3u) != 0u) ||
	    footer->footer_length < MINSIZEOF_FOOTER ||
	    footer->footer_length > size) {
		return -EINVAL;
	}
	data -= footer->footer_length - sizeof(uint32_t);
	LOG_INF("Parsing image footer at %p", data);

	footer->metadata_length = *(uint32_t *)data;
	if (footer->metadata_length != METADATA_LENGTH) { return -EINVAL; }
	data += sizeof(uint32_t);

	footer->metadata_version = *(uint32_t *)data;
	if (footer->metadata_version != METADATA_VERSION) { return -EINVAL; }
	data += sizeof(uint32_t);

	footer->scid = *(cmrt_container_scid_t *)data;
	data += sizeof(cmrt_container_scid_t);

	footer->container_version = *(uint32_t *)data;
	data += sizeof(uint32_t);

	footer->permissions = *(cmrt_omc_root_perm_t *)data;
	data += sizeof(cmrt_omc_root_perm_t);

	footer->encryption_length = *(uint32_t *)data;
	data += sizeof(uint32_t);
	if (footer->encryption_length != 0u) {
		if (footer->encryption_length != sizeof(cmrt_encryption_data_t)) {
			return -EINVAL;
		}
		footer->encryption_data = (cmrt_encryption_data_t *)data;
		if (footer->encryption_data->version == 1u) {
			switch (footer->encryption_data->key_src) {
			case CMRT_IMAGE_KEY_SRC_DS:
				break;
			case CMRT_IMAGE_KEY_SRC_KDC:
				switch (footer->encryption_data->keysplit_id) {
				case CMRT_IMAGE_KEYSPLIT_BNAK:
				case CMRT_IMAGE_KEYSPLIT_SNAK:
				case CMRT_IMAGE_KEYSPLIT_PNAK:
					/* Check it is allowed in footer. */
					if ((footer->permissions.key_perm.val &
					     (1UL << ((uint32_t)footer->encryption_data->keysplit_id - 1u))) == 0u) {
						return -EPERM;
					}
					break;
				case CMRT_IMAGE_KEYSPLIT_1:
				case CMRT_IMAGE_KEYSPLIT_2:
				case CMRT_IMAGE_KEYSPLIT_3:
				case CMRT_IMAGE_KEYSPLIT_4:
				case CMRT_IMAGE_KEYSPLIT_5:
				case CMRT_IMAGE_KEYSPLIT_6:
				case CMRT_IMAGE_KEYSPLIT_7:
					/* Check it is allowed in footer. */
					if ((footer->permissions.key_perm.val &
					     (1UL << ((uint32_t)footer->encryption_data->keysplit_id - 8u))) == 0u) {
						return -EPERM;
					}
					break;
				case CMRT_IMAGE_KEYSPLIT_DGOK:
					/* No permission required to use DGOK. */
					break;
				default:
					return -EINVAL;
				}
				break;
			default:
				return -EINVAL;
			}
		}
		data += footer->encryption_length;
	} else { footer->encryption_data = NULL; }

	footer->public_key_type = *(uint32_t *)data;
	data += sizeof(uint32_t);

	footer->public_key_length = *(uint32_t *)data;
	if (footer->public_key_length > MAXSIZEOF_PUBLIC_KEY) { return -EINVAL; }

	data += sizeof(uint32_t);
	footer->public_key = data;
	data += ROUND_UP(footer->public_key_length, sizeof(uint32_t));

	footer->signature_length = *(uint32_t *)data;
	if (footer->signature_length > MAXSIZEOF_SIGNATURE) { return -EINVAL; }
	data += sizeof(uint32_t);

	switch (footer->public_key_type) {
	case PK_UNSIGNED:
		if ((footer->public_key_length != PL_UNSIGNED) ||
		    (footer->signature_length != SL_UNSIGNED)) {
			return -EINVAL;
		}
		break;
	case PK_ECDSA_P256:
		if ((footer->public_key_length != PL_ECDSA_P256) ||
		    (footer->signature_length != SL_ECDSA_P256)) {
			return -EINVAL;
		}
		break;
	case PK_HMAC_SHA256:
		if ((footer->public_key_length != PL_HMAC_SHA256) ||
		    (footer->signature_length != SL_HMAC_SHA256)) {
			return -EINVAL;
		}
		break;
#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P521
	case PK_ECDSA_P521:
		if ((footer->public_key_length != PL_ECDSA_P521) ||
		    (footer->signature_length != SL_ECDSA_P521)) {
			return -EINVAL;
		}
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_RSA_VERIFY
	case PK_RSAPSS_3K:
		if ((footer->public_key_length != PL_RSAPSS_3K) ||
		    (footer->signature_length != SL_RSAPSS_3K)) {
			return -EINVAL;
		}
		break;
	case PK_RSAPSS_4K:
		if ((footer->public_key_length != PL_RSAPSS_4K) ||
		    (footer->signature_length != SL_RSAPSS_4K)) {
			return -EINVAL;
		}
		break;
#endif
#ifdef CONFIG_CMRT_SUPERVISOR_IN_ROM
	case PK_SHA256:
		if ((footer->public_key_length != PL_SHA256) ||
		    (footer->signature_length != SL_SHA256)) {
			return -EINVAL;
		}
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_LMS_VERIFY
	case PK_LMS:
		if ((footer->public_key_length != PL_LMS) ||
		    (footer->signature_length < SL_LMS_MIN) ||
		    (footer->signature_length > SL_LMS_MAX)) {
			return -EINVAL;
		}
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_LMS_HSS_VERIFY
	case PK_LMS_HSS:
		if ((footer->public_key_length != PL_LMS_HSS) ||
		    (footer->signature_length < SL_LMS_HSS_MIN) ||
		    (footer->signature_length > SL_LMS_HSS_MAX)) {
			return -EINVAL;
		}
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_VERIFY
	case PK_XMSS:
		if (((footer->public_key_length != PL_XMSS_256) &&
		     (footer->public_key_length != PL_XMSS_512)) ||
		    (footer->signature_length < SL_XMSS_MIN) ||
		    (footer->signature_length > SL_XMSS_MAX)) {
			return -EINVAL;
		}
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_MT_VERIFY
	case PK_XMSS_MT:
		if (((footer->public_key_length != PL_XMSS_MT_256) &&
		     (footer->public_key_length != PL_XMSS_MT_512)) ||
		    (footer->signature_length < SL_XMSS_MT_MIN) ||
		    (footer->signature_length > SL_XMSS_MT_MAX)) {
			return -EINVAL;
		}
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P384
	case PK_ECDSA_P384:
		if ((footer->public_key_length != PL_ECDSA_P384) ||
		    (footer->signature_length != SL_ECDSA_P384)) {
			return -EINVAL;
		}
		break;
#endif
	default:
		return -EINVAL;
	}

	footer->signature = data;
	data += footer->signature_length;

	if (footer->footer_length != *(uint32_t *)data) { return -EINVAL; }

	return footer->footer_length;
}

int cmrt_raw_footer_parse(void *blob, size_t size, bool relocate, cmrt_raw_footer_t *raw)
{
	if (!is_aligned(blob, 4u) || !is_aligned(size, 4u)) { return -EINVAL; }

	cmrt_raw_footer_t *footer = (cmrt_raw_footer_t *)((uint8_t *)blob + size) - 1;
	LOG_INF("Parsing raw footer at %p", footer);

	/* We must have complete footer. */
	if (footer->verlen != sizeof(cmrt_raw_footer_t)) {
		LOG_INF("Footer has to be complete %u != %u",
			footer->verlen, sizeof(cmrt_raw_footer_t));
		return -EINVAL;
	}
	if (relocate) {
		uint32_t offset = (uint32_t)(uintptr_t)blob - footer->load_address;
		if (offset != 0u) {
			LOG_INF("Relocate offset 0x%x", offset);
			footer->text_start += offset;
			footer->text_end += offset;
			footer->rodata_start += offset;
			footer->rodata_end += offset;
			footer->bss_start += offset;
			footer->bss_end += offset;
			footer->noinit_start += offset;
			footer->noinit_end += offset;
			footer->data_start += offset;
			footer->data_end += offset;
			footer->entry_point += offset;
			footer->load_address += offset;
			footer->relocation_offset += offset;
		}
	}
	/* Section limits must be word aligned. */
	uint32_t raw_end = (uint32_t)(uintptr_t)footer;
	uint32_t raw_start = (uint32_t)(uintptr_t)blob;
	const uint32_t *fp = (const uint32_t *)footer;
	for (size_t i = 0; i < RAW_SECT_FIELDS; i++) {
		if ((fp[i] & 0x03u) != 0u) {
			LOG_INF("Section limits must be word aligned fp[%u]=%x",
				i, fp[i]);
			return -EINVAL;
		}
	}
	/* Load address must be word aligned, entry point half-word aligned */
	if (!is_aligned(footer->load_address, 4u) || !is_aligned(footer->entry_point, 2u)) {
		LOG_INF("Load address must be word aligned, entry point half-word aligned la:%x e:%x",
			footer->load_address, footer->entry_point);
		return -EINVAL;
	}
	/* Section fields must be in order. */
	for (size_t i = 0; i < RAW_SECT_FIELDS-1u; i++) {
		if (fp[i] > fp[i+1u]) {
			LOG_INF("Section fields must be in order fp[%u]=%x > %x",
				i, fp[i], fp[i+1u]);
			return -EINVAL;
		}
	}
#ifdef CONFIG_CMRT_SUPERVISOR_IN_ROM
	/* ROM images are verified in ROM but ran in SRAM.
	 * Make the following sanity checks work in this case. */
	if (IS_IN_ROM((uint32_t)blob) && IS_IN_ROM((uint32_t)blob + size)) {
		blob = (void *)(uintptr_t)footer->text_start;
		raw_start = footer->text_start;
		raw_end = footer->data_end;
	}
#endif
	/* Text, rodata and data must be inside loaded image. */
	if (footer->text_start < raw_start || footer->data_end > raw_end) {
		LOG_INF("Text, rodata and data must be inside loaded image s:%x<rs:%x e:%x>re:%x",
			footer->text_start, raw_start, footer->data_end, raw_end);
		return -EINVAL;
	}
	/* Load address must be equal to the image start. */
	if (footer->load_address != (uint32_t)(uintptr_t)blob) {
		LOG_INF("Load address is not equal to the image start %x != %x",
			footer->load_address, (uint32_t)(uintptr_t)blob);
		return -EINVAL;
	}
	/* Entry point must be inside text section. */
	uint32_t entry = footer->entry_point;
	if (entry < footer->text_start || entry >= footer->text_end) {
		LOG_INF("Entry point is not inside text section entry:%x s:%x e:%x",
			entry, footer->text_start, footer->text_end);
		return -EINVAL;
	}
	if (raw != NULL) { (void)memcpy(raw, footer, sizeof(*footer)); }

	LOG_INF("Text at 0x%x entry at 0x%x", footer->text_start, entry);

	return footer->verlen;
}

void cmrt_raw_image_init(const cmrt_raw_footer_t *raw)
{
	/* Init bss. */
	if (raw && raw->bss_end > raw->bss_start) {
		(void)memset((void *)(uintptr_t)raw->bss_start, 0, raw->bss_end - raw->bss_start);
	}
}

int cmrt_usr_footer_parse(void *blob, size_t size, const cmrt_raw_footer_t *raw, cmrt_usr_footer_t *usr)
{
	if (!is_aligned(blob, 4u) || !is_aligned(size, 4u)) { return -EINVAL; }

	cmrt_usr_footer_t *footer = (cmrt_usr_footer_t *)((uint8_t *)blob + size) - 1;
	LOG_INF("Parsing usr footer at %p", footer);

	/* We must have complete footer. */
	if (footer->verlen != sizeof(cmrt_usr_footer_t)) {
		LOG_INF("Footer has to be complete %u != %u",
			footer->verlen, sizeof(cmrt_usr_footer_t));
		return -EINVAL;
	}

	uint32_t offset = raw->relocation_offset;
	if (offset != 0u) {
		footer->global_pointer += offset;
		footer->relo_start += offset;
		footer->relo_end += offset;
		footer->got_start += offset;
		footer->got_end += offset;
	}

	/* Relocation data must be within a non-executable part of the
	 * image, and GOT in a read-only data section (rodata).
	 */
	uint32_t image_start = (uintptr_t)blob;
	uint32_t image_end = image_start + size;
	if (footer->relo_start < raw->rodata_start ||
	    footer->relo_end > image_end ||
	    footer->relo_end < footer->relo_start ||
	    footer->got_start < raw->rodata_start ||
	    footer->got_end > raw->rodata_end ||
	    footer->got_end < footer->got_start) {
		return -EINVAL;
	}
	/* Actual relocation takes place in supervisor. */
	if (usr != NULL) { (void)memcpy(usr, footer, sizeof(*footer)); }

	return footer->verlen + footer->relo_end - footer->relo_start;
}
