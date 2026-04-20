#include <rebel_h.h>
#include <dd.h>
#include <hc.h>
#include <pke.h>
#include <dmac.h>
#include <rebel_h_integrity.h>
#include <logging/log.h>
#include <rebel_h_gpt.h>
#include <fboot.h>
#include <syscalls.h>
#include <drivers/cmrt/sac_mem.h>
#include <sac.h>
#include <sac_reg.h>
#include <errno.h>

#include <sac_custom.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(integrity, CONFIG_CMRT_LOG_LEVEL);

int img_footer_parse(void *blob, size_t size, cmrt_img_footer_t *footer)
{
	if (!is_aligned(blob, 4u) || !is_aligned(size, 4u) ||
		!blob || size == 0u || !footer) {
		return -EINVAL;
	}

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
	footer->metadata_length = *(uint32_t *)data;

	if (footer->metadata_length != METADATA_LENGTH) {
		return -EINVAL;
	}

	data += sizeof(uint32_t);
	footer->metadata_version = *(uint32_t *)data;

	if (footer->metadata_version != METADATA_VERSION) {
		return -EINVAL;
	}

	data += sizeof(uint32_t);
	footer->scid = *(cmrt_container_scid_t *)data;
	data += sizeof(cmrt_container_scid_t);

	footer->container_version = *(uint32_t *)data;
	data += sizeof(uint32_t);

	footer->permissions = *(cmrt_omc_root_perm_t *)data;
	data += sizeof(cmrt_omc_root_perm_t);

	footer->encryption_length = *(uint32_t *)data;
	data += sizeof(uint32_t);
	footer->encryption_data = NULL;

	footer->public_key_type = *(uint32_t *)data;
	data += sizeof(uint32_t);

	footer->public_key_length = *(uint32_t *)data;
	if (footer->public_key_length > MAXSIZEOF_PUBLIC_KEY) {
		return -EINVAL;
	}

	data += sizeof(uint32_t);
	footer->public_key = data;
	data += ROUND_UP(footer->public_key_length, sizeof(uint32_t));

	footer->signature_length = *(uint32_t *)data;
	if (footer->signature_length > MAXSIZEOF_SIGNATURE) {
		return -EINVAL;
	}
	data += sizeof(uint32_t);

	if (footer->public_key_type == PK_ECDSA_P384) {
		if (footer->public_key_length != PL_ECDSA_P384 ||
			footer->signature_length != SL_ECDSA_P384) {
			return -EINVAL;
		}
	} else {
		return -EINVAL;
	}

	footer->signature = data;
	data += footer->signature_length;

	if (footer->footer_length != *(uint32_t *)data) {
		return -EINVAL;
	}

	return footer->footer_length;
}

static int check_integrity(uint32_t img_type, struct dma_block_config img_info[], uint32_t length)
{
	uint8_t __aligned(4) footer_tmp_storage[FOOTER_MAX_LEN];
	uint64_t image_addr_to_verify = img_info[img_type].dest_address;
	uint64_t footer_addr;
	uint32_t footer_length;
	uint32_t mux_value = 0;
	uint32_t res;

	if (img_type == IMG_TBOOT_P1) {
		footer_addr = img_info[IMG_TBOOT_P1_FOOTER].source_address;
		footer_length = img_info[IMG_TBOOT_P1_FOOTER].block_size;
	} else if (img_type == IMG_TBOOT_U) {
		footer_addr = img_info[IMG_TBOOT_U_FOOTER].source_address;
		footer_length = img_info[IMG_TBOOT_U_FOOTER].block_size;
	} else {
		footer_addr = image_addr_to_verify + length - sizeof(uint32_t);
		cmrt_sac_set_base(NULL, GET_SAC_BASE(footer_addr));
		footer_length = sys_read32(GET_SAC_R_CPU_DATA(footer_addr));
		footer_addr -= (footer_length - sizeof(uint32_t));
	}

	cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);

	if (!cmrt_is_valid(dmac)) {
		return -ENODEV;
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(footer_addr));

	res = cmrt_dmac_data(dmac, (GET_SAC_OFFSET(footer_addr)), (uint32_t)footer_tmp_storage,
						 footer_length, 0);
	cmrt_dmac_close(dmac);

	if (res != 0) {
		return res;
	}

	cmrt_img_footer_t img_footer;

	res = img_footer_parse(footer_tmp_storage, footer_length, &img_footer);
	if (res < 0) {
		return res;
	}

	cmrt_hc_t hc = cmrt_hc_open(NULL, 0);

	if (!cmrt_is_valid(hc))
		return -EIO;

	res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_384, NULL, 0);
	if (res != 0) {
		cmrt_hc_close(hc);
		return res;
	}

	if (img_type == IMG_TBOOT_P1) {
		cmrt_sac_set_base(NULL, GET_SAC_BASE(PHY0_APB2CR_PARA_PCIE + MUX_SWITCH));
		mux_value = sys_read32(GET_SAC_R_CPU_DATA(MUX_SWITCH));
	}

	uint32_t f_len_size = sizeof(img_footer.footer_length);

	cmrt_sac_set_base(NULL, GET_SAC_BASE(image_addr_to_verify));

	if (img_type == IMG_TBOOT_P1) {
		res = cmrt_hc_update(hc, (void *)GET_SAC_OFFSET(image_addr_to_verify), TBOOT_P1_SRAM_MAX);
		if (res != 0) {
			cmrt_hc_close(hc);
			return res;
		}
		cmrt_sac_set_base(NULL, GET_SAC_BASE(PHY0_APB2CR_PARA_PCIE + MUX_SWITCH));
		sys_write32(mux_value | MUX_VALUE, GET_SAC_R_CPU_DATA(MUX_SWITCH));
		cmrt_sac_set_base(NULL, GET_SAC_BASE(image_addr_to_verify));
		res = cmrt_hc_update(hc, (void *)GET_SAC_OFFSET(image_addr_to_verify), TBOOT_P1_SRAM_MAX);
		if (res != 0) {
			cmrt_hc_close(hc);
			return res;
		}
		cmrt_sac_set_base(NULL, GET_SAC_BASE(PHY0_APB2CR_PARA_PCIE + MUX_SWITCH));
		sys_write32(mux_value, GET_SAC_R_CPU_DATA(MUX_SWITCH));
		length -= (TBOOT_P1_SRAM_MAX * 2);
		if (length != FOOTER_SIZE) {
			cmrt_hc_close(hc);
			return -EINVAL;
		}
		res = cmrt_hc_update(hc, (void *)(footer_tmp_storage),
							 length - img_footer.signature_length - f_len_size);
		if (res != 0) {
			cmrt_hc_close(hc);
			return res;
		}
		res = cmrt_hc_update(hc, (uint8_t *)(footer_tmp_storage) + length - f_len_size, f_len_size);
		if (res != 0) {
			cmrt_hc_close(hc);
			return res;
		}
	} else if (img_type == IMG_TBOOT_U) {
		res = cmrt_hc_update(hc, (void *)GET_SAC_OFFSET(image_addr_to_verify), TBOOT_U_SRAM_MAX);
		if (res != 0) {
			cmrt_hc_close(hc);
			return res;
		}
		length -= TBOOT_U_SRAM_MAX;
		if (length != FOOTER_SIZE) {
			cmrt_hc_close(hc);
			return -EINVAL;
		}
		res = cmrt_hc_update(hc, (void *)(footer_tmp_storage),
							 length - img_footer.signature_length - f_len_size);
		if (res != 0) {
			cmrt_hc_close(hc);
			return res;
		}
		res = cmrt_hc_update(hc, (uint8_t *)(footer_tmp_storage) + length - f_len_size, f_len_size);
		if (res != 0) {
			cmrt_hc_close(hc);
			return res;
		}
	} else {
		uint32_t copied_len = 0;
		const uint32_t max_length = DMAC_MAX_SIZE;

		uint32_t length_to_hash = length - img_footer.signature_length - f_len_size;
		uint32_t length_to_send = 0;

		while (length_to_hash > 0) {
			if (length_to_hash >= max_length) {
				length_to_send = max_length;
			} else {
				length_to_send = length_to_hash;
			}
			res = cmrt_hc_update(hc, (void *)(GET_SAC_OFFSET(image_addr_to_verify) + copied_len),
								 length_to_send);
			if (res != 0) {
				cmrt_hc_close(hc);
				return res;
			}
			length_to_hash -= length_to_send;
			copied_len += length_to_send;
		}
		res = cmrt_hc_update(hc, (uint8_t *)GET_SAC_OFFSET(image_addr_to_verify) + length - f_len_size, f_len_size);
		if (res != 0) {
			cmrt_hc_close(hc);
			return res;
		}
	}

	size_t size = SHA512_BYTES;
	uint32_t digest[SHA3_384_WORDS];

	res = cmrt_hc_final(hc, NULL, 0, digest, &size);
	cmrt_hc_close(hc);
	if (res != 0) {
		return res;
	}

	cmrt_ecc_curve_t curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P384);
	uint32_t digestlen = SHA384_BYTES;
	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);

	if (!curve || !cmrt_is_valid(pke)) {
		return -ENODEV;
	}

	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	res = cmrt_pke_ecdsa_verify_hash(pke, curve, img_footer.public_key,
									 img_footer.public_key + curvelen,
									 digest, digestlen, img_footer.signature,
									 img_footer.signature + curvelen, NULL);

	cmrt_pke_close(pke);

	return res;
}

static int validate_header(uint32_t img_type, uint32_t *length, struct dma_block_config img_info[])
{
	uint64_t gpt_base = get_active_partition_base();

	img_info[img_type].source_address = get_image_address(img_type, gpt_base);

	uint64_t src = img_info[img_type].source_address;
	cmrt_img_header_t hdr;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(src));
	hdr.length = sys_read32(GET_SAC_R_CPU_DATA(src));
	hdr.mirror = sys_read32(GET_SAC_R_CPU_DATA(src + sizeof(hdr.length)));
	*length = hdr.length;

	if (img_type == IMG_TBOOT_S) {
		img_info[img_type].source_address += sizeof(cmrt_img_header_t);
	} else {
		img_info[img_type].source_address += (sizeof(cmrt_img_header_t)
											  + NORMAL_IMG_PADDING_SIZE);
	}

	uint32_t aligned_length = (((*length) & 0xffff) != 0x0) ?
							  ((*length & ~(uint32_t)0xffff) + 0x10000) : *length;

	img_info[img_type].block_size = aligned_length;

	return !cmrt_is_valid_hdr(&hdr, MAX_SIZE);
}

int start_image(uint32_t img_type,
				int (*copy_image)(uint32_t img_type, uint32_t length,
								  struct dma_block_config img_info[]),
				struct dma_block_config img_info[],
				uint32_t (*fboot_supervisor_clear)(void),
				int (*fboot_supervisor_start)(void))
{
	uint32_t length;
	int res = validate_header(img_type, &length, img_info);

	if (res) {
		LOG_ERR("%d validate_header Fail! length = %d, res = %d\n", img_type, length, res);

		return res;
	}

	if (img_type == IMG_TBOOT_S) {
		if (!fboot_supervisor_clear) {
			LOG_ERR("%d No fboot_supervisor_clear\n", img_type);
			return -ESRCH;
		}

		img_info[img_type].dest_address = fboot_supervisor_clear();
	}

	res = copy_image(img_type, length, img_info);
	if (res) {
		LOG_ERR("%d copy_image Fail! length = %d, res = %d\n", img_type, length, res);
		return res;
	}

	if (img_type == IMG_TBOOT_S) {
		cmrt_raw_footer_t raw;

		res = fboot_load_image((uint32_t *)(uintptr_t)img_info[img_type].dest_address,
							   (size_t)length, &raw, NULL);
		if (res < 0) {
			LOG_ERR("%d fboot_load_image Fail! length = %d res = %d\n", img_type, length, res);
			return res;
		}

		if (!fboot_supervisor_start) {
			LOG_ERR("%d No fboot_supervisor_start\n", img_type);
			return -ESRCH;
		}

		return fboot_supervisor_start();
	}

	return check_integrity(img_type, img_info, length);
}
