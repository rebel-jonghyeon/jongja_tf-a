/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/*** GENERIC FUNCTIONS ***/

#include <errno.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#include <hexutil.h>

void hexdump(const void *data, size_t len)
{
	if (len > 256) {
		/* Sane limit to hexdump. */
		len = 256;
	}
	LOG_HEXDUMP_INF(data, len, "");
}

#include <perso.h>
#include <cri/cmrt.h>
#include <drivers/cmrt/cmrt.h>

#ifdef __ZEPHYR__
void cri_set_boot_status(uint32_t bits, uint32_t mask)
{
	cmrt_set_boot_status(bits, mask);
}
#endif

int cri_wait(unsigned int n, cri_handle_t const *handles, int timeout)
{
	return cmrt_wait(n, handles, timeout);
}

#include <stdlib.h>
#include <crisyscall-user.h>

int cri_exit(int rc)
{
	abort();
	return rc;
}

/*** SECURITY MONITOR ***/

#include <smcalls.h>
#include <drivers/cmrt/fboot.h>

int cri_mcall_exit(int major, int minor, bool reboot)
{
	if (reboot) {
		return fboot_reboot();
	}
	return fboot_halt(major, minor);
}

int cri_mcall_create_root(int index, const cmrt_omc_root_t *new_root)
{
	return fboot_create_root(index, new_root);
}

int cri_mcall_obliterate_root(int index)
{
	return fboot_obliterate_root(index);
}

int cri_mcall_soft_reset(void)
{
	return fboot_reset(0);
}

int cri_mcall_get_img_version(enum cri_image_version_id imageid, void *version, size_t *size)
{
	return fboot_get_image_version((enum cmrt_image_version_id) imageid, version, size);
}

/*** DEVICE DRIVERS ***/

#include <cri/cmrt/aes.h>
#include <drivers/cmrt/aes.h>

cri_aes_t cri_aes_open(uint32_t flags)
{
	return (cri_aes_t)cmrt_aes_open(flags);
}

void cri_aes_close(cri_aes_t context)
{
	cmrt_aes_close((cmrt_aes_t)context);
}

int cri_aes_kdc_cmd(cri_aes_t context, cri_aes_operation_t operation, cri_aes_mode_t mode, size_t keylen, size_t taglen, kdc_cmd_t *cmd)
{
	return cmrt_aes_kdc_cmd((cmrt_aes_t)context, (cmrt_aes_operation_t)operation, (cmrt_aes_mode_t)mode, keylen, taglen, (cmrt_kdc_cmd_t *)cmd);
}

#ifdef __ZEPHYR__
int cri_aes_load_kdc_key(cri_aes_t context, cri_kdc_t kdc, kdc_cmd_t *cmd)
{
	return cmrt_aes_load_kdc_key((cmrt_aes_t)context, (cmrt_kdc_t)kdc, (cmrt_kdc_cmd_t *)cmd);
}
#endif

int cri_aes_init(cri_aes_t context, cri_aes_operation_t operation, cri_aes_mode_t mode, const void *key, size_t keylen, const void *iv, size_t ivlen, size_t taglen)
{
	return cmrt_aes_init((cmrt_aes_t)context, (cmrt_aes_operation_t)operation, (cmrt_aes_mode_t)mode, key, keylen, iv, ivlen, taglen);
}

#ifdef CONFIG_CMRT_AES_XTS
int cri_aes_xts_set_offset(cri_aes_t context, uint32_t offset)
{
	return cmrt_aes_xts_set_offset((cmrt_aes_t)context, offset);
}
#endif

int cri_aes_update(cri_aes_t context, const void *input, size_t inlen, void *output)
{
	return cmrt_aes_update((cmrt_aes_t)context, input, inlen, output);
}

int cri_aes_update_aad(cri_aes_t context, const void *aad, size_t aadlen)
{
	return cmrt_aes_update_aad((cmrt_aes_t)context, aad, aadlen);
}

int cri_aes_final_aad(cri_aes_t context, const void *aad, size_t aadlen)
{
	return cmrt_aes_final_aad((cmrt_aes_t)context, aad, aadlen);
}

int cri_aes_final(cri_aes_t context, const void *input, size_t inlen, void *output)
{
	return cmrt_aes_final((cmrt_aes_t)context, input, inlen, output);
}

int cri_aes_ae_final(cri_aes_t context, const void *input, size_t inlen, void *output, void *tag, size_t *taglen)
{
	return cmrt_aes_ae_final((cmrt_aes_t)context, input, inlen, output, tag, taglen);
}

int cri_aes_flush(cri_aes_t context)
{
	ARG_UNUSED(context);
	return -ENOTSUP; /* flush is internal for KATs only */
}

#if IS_ENABLED(CMRT_AES_HAS_CCM)
int cri_aes_ccm_encode_nonce(void *buf, size_t buflen, const void *nonce, size_t noncelen, size_t ptlen, size_t taglen, int hasaad)
{
	return cmrt_aes_ccm_encode_nonce(buf, buflen, nonce, noncelen, ptlen, taglen, hasaad);
}

int cri_aes_ccm_encode_aad(void *buf, size_t buflen, const void *aad, size_t aadlen)
{
	return cmrt_aes_ccm_encode_aad(buf, buflen, aad, aadlen);
}
#endif

#include <cri/cmrt/cc.h>
#include <drivers/cmrt/cc.h>

cri_cc_t cri_cc_open(void)
{
	return (cri_cc_t)cmrt_cc_open();
}

void cri_cc_close(cri_cc_t context)
{
	cmrt_cc_close((cmrt_cc_t)context);
}

int cri_cc_assert(cri_cc_t context, uint32_t assert0, uint32_t assert1)
{
	return cmrt_cc_assert((cmrt_cc_t)context, assert0, assert1);
}

int cri_cc_mix(cri_cc_t context, uint32_t value)
{
	return cmrt_cc_mix((cmrt_cc_t)context, value);
}

int cri_cc_sync(cri_cc_t context)
{
	return cmrt_cc_sync((cmrt_cc_t)context);
}

#include <cri/cmrt/ccp.h>
#include <drivers/cmrt/ccp.h>

cri_ccp_t cri_ccp_open(uint32_t flags)
{
	return (cri_ccp_t)cmrt_ccp_open(flags);
}

void cri_ccp_close(cri_ccp_t dev)
{
	cmrt_ccp_close((cmrt_ccp_t)dev);
}

int cri_ccp_init(cri_ccp_t dev, int operation, int mode, const void *key,
		 size_t keylen, const void *iv, size_t ivlen, size_t taglen)
{
	return cmrt_ccp_init((cmrt_ccp_t)dev, operation, mode, key, keylen, iv, ivlen, taglen);
}

int cri_ccp_update(cri_ccp_t dev, const void *input, size_t inlen, void *output)
{
	return cmrt_ccp_update((cmrt_ccp_t)dev, input, inlen, output);
}

int cri_ccp_update_aad(cri_ccp_t dev, const void *aad, size_t aadlen)
{
	return cmrt_ccp_update_aad((cmrt_ccp_t)dev, aad, aadlen);
}

int cri_ccp_final_aad(cri_ccp_t dev, const void *aad, size_t aadlen)
{
	return cmrt_ccp_final_aad((cmrt_ccp_t)dev, aad, aadlen);
}

int cri_ccp_final(cri_ccp_t dev, const void *input, unsigned int inlen, void *output)
{
	return cmrt_ccp_final((cmrt_ccp_t)dev, input, inlen, output);
}

int cri_ccp_ae_final(cri_ccp_t dev, const void *input, size_t inlen, void *output, void *tag, size_t *taglen)
{
	return cmrt_ccp_ae_final((cmrt_ccp_t)dev, input, inlen, output, tag, taglen);
}

int cri_ccp_invalidate_key(cri_ccp_t dev, uint32_t flags)
{
	return cmrt_ccp_invalidate_key((cmrt_ccp_t)dev, flags);
}

#include <cri/cmrt/dmac.h>
#include <drivers/cmrt/dmac.h>

cri_dmac_t cri_dmac_open(uint32_t flags)
{
	return (cri_dmac_t)cmrt_dmac_open(flags);
}

void cri_dmac_close(cri_dmac_t channel)
{
	cmrt_dmac_close((cmrt_dmac_t)channel);
}

int cri_dmac_data(cri_dmac_t channel, uint32_t src_addr,
		  uint32_t dst_addr, uint32_t size)
{
	return cmrt_dmac_data(channel, src_addr, dst_addr, size, 0);
}

int cri_dmac_data_ex(cri_dmac_t channel, uint32_t src_addr,
		     uint32_t dst_addr, uint32_t size, uint32_t desc_flags)
{
	return cmrt_dmac_data((cmrt_dmac_t)channel, src_addr, dst_addr, size, desc_flags);
}

int cri_dmac_fill(cri_dmac_t channel, uint32_t fill_data,
		  uint32_t dst_addr, uint32_t size)

{
	return cmrt_dmac_fill((cmrt_dmac_t)channel, fill_data, dst_addr, size, 0);
}

int cri_dmac_fill_ex(cri_dmac_t channel, uint32_t fill_data,
		     uint32_t dst_addr, uint32_t size,
		     uint32_t desc_flags)
{
	return cmrt_dmac_fill((cmrt_dmac_t)channel, fill_data, dst_addr, size, desc_flags);
}

int cri_dmac_sync(cri_dmac_t channel)
{
	return cmrt_dmac_sync((cmrt_dmac_t)channel);
}

#ifdef __ZEPHYR__
#include <cri/cmrt/eac.h>
#include <drivers/cmrt/eac.h>
#include <drivers/cmrt/sic_reg.h>

uint32_t cri_eac_last_nmi_error(bool clear)
{
	return cmrt_read_reg(CMRT_SIC_BASE, R_CUSTOM_0);
}

uint32_t cri_eac_last_fatal_error(bool clear)
{
	return cmrt_read_reg(CMRT_SIC_BASE, R_CUSTOM_1);
}

void cri_eac_set_internal_error(uint32_t core_id, int major, int minor)
{
	ARG_UNUSED(core_id);
	cmrt_eac_set_internal_error(major, minor);
}

void cri_eac_halt(uint32_t core_id, int major, int minor)
{
	cmrt_eac_halt(core_id, major, minor);
}

void cri_eac_reboot(void)
{
	cmrt_eac_reboot();
}

void cri_eac_kat_error(uint32_t core_id, int major, int minor)
{
	cmrt_eac_kat_error(core_id, major, minor);
}
#endif

#include <cri/cmrt/fmc.h>
#include <drivers/cmrt/fmc.h>

cri_fmc_t cri_fmc_open(void)
{
	return (cri_fmc_t)cmrt_fmc_open();
}

void cri_fmc_close(cri_fmc_t context)
{
	cmrt_fmc_close((cmrt_fmc_t)context);
}

int cri_fmc_feature_read(cri_fmc_t context, uint32_t addr, uint32_t *data)
{
	return cmrt_fmc_read((cmrt_fmc_t)context, addr, data);
}

int cri_fmc_feature_write(cri_fmc_t context, uint32_t addr, uint32_t data, uint32_t mask)
{
	return cmrt_fmc_write((cmrt_fmc_t)context, addr, data, mask);
}

int cri_fmc_gpio_read(cri_fmc_t context, uint32_t addr, uint32_t *data)
{
	ARG_UNUSED(context);
	ARG_UNUSED(addr);
	ARG_UNUSED(data);
	return -ENOTSUP; /* not supported in v2 */
}

int cri_fmc_gpio_write(cri_fmc_t context, uint32_t addr, uint32_t data, uint32_t mask)
{
	ARG_UNUSED(context);
	ARG_UNUSED(addr);
	ARG_UNUSED(data);
	ARG_UNUSED(mask);
	return -ENOTSUP; /* not supported in v2 */
}

#ifdef __ZEPHYR__
int cri_fmc_set_perm_bitmap(cri_fmc_t context, uint32_t bitmap)
{
	return cmrt_fmc_permissions((cmrt_fmc_t)context, bitmap);
}
#endif

int cri_fmc_set_debug_mode(cri_fmc_t context)
{
	cmrt_fmc_set_debug_mode((cmrt_fmc_t)context);
	return 0;
}

#include <cri/cmrt/hc.h>
#include <drivers/cmrt/hc.h>

cri_hc_t cri_hc_open(uint32_t flags)
{
	return (cri_hc_t)cmrt_hc_open(NULL, flags);
}

cri_hc_t cri_cshc_open(uint32_t flags)
{
	return (cri_hc_t)cmrt_cshc_open(flags);
}

cri_hc_t cri_whc_open(uint32_t flags)
{
	return (cri_hc_t)cmrt_whc_open(flags);
}

cri_hc_t cri_hc2_open(uint32_t flags)
{
	return (cri_hc_t)cmrt_hc2_open(flags);
}

cri_hc_t cri_hc_open_by_name(const char *name, uint32_t flags)
{
	return (cri_hc_t)cmrt_hc_open(name, flags);
}

void cri_hc_close(cri_hc_t context)
{
	cmrt_hc_close((cmrt_hc_t)context);
}

int cri_hc_kdc_cmd(cri_hc_t context, cri_hash_algo_t algo, size_t keylen, kdc_cmd_t *cmd)
{
	return cmrt_hc_kdc_cmd((cmrt_hc_t)context, (cmrt_hash_algo_t)algo, keylen, (cmrt_kdc_cmd_t *)cmd);
}

int cri_hc_init(cri_hc_t context, cri_hash_algo_t algo, const void *key, size_t keylen)
{
	return cmrt_hc_init((cmrt_hc_t)context, (cmrt_hash_algo_t)algo, key, keylen);
}

int cri_hc_update(cri_hc_t context, const void *input, size_t inlen)
{
	return cmrt_hc_update((cmrt_hc_t)context, input, inlen);
}

int cri_hc_final(cri_hc_t context, const void *input, size_t inlen, void *output, size_t *outlen)
{
	return cmrt_hc_final((cmrt_hc_t)context, input, inlen, output, outlen);
}

int cri_hc_flush(cri_hc_t context)
{
	ARG_UNUSED(context);
	return -ENOTSUP; /* flush is internal for KATs only */
}

#include <cri/cmrt/kdc.h>
#include <drivers/cmrt/kdc.h>

cri_kdc_t cri_kdc_open(uint32_t flags)
{
	return (cri_kdc_t)cmrt_kdc_open(flags);
}

void cri_kdc_close(cri_kdc_t context)
{
	cmrt_kdc_close((cmrt_kdc_t)context);
}

#ifdef __ZEPHYR__
int cri_kdc_burn_dgok(cri_kdc_t context, kdc_cmd_t *cmd)
{
	return cmrt_kdc_burn_dgok((cmrt_kdc_t)context, (cmrt_kdc_cmd_t *)cmd);
}

int cri_kdc_set_derive_path(cri_kdc_t context, const kdc_drv_path_t *drv_path)
{
	return cmrt_kdc_set_derive_path((cmrt_kdc_t)context, (cmrt_kdc_drv_path_t *)drv_path);
}
#endif

int cri_kdc_derive_key(cri_kdc_t context, kdc_cmd_t *cmd)
{
	if (cmd != NULL) {
		/* Driver adds +1 to diversify_len. */
		cmd->diversify_len--;
	}
	return cmrt_kdc_derive_key((cmrt_kdc_t)context, (cmrt_kdc_cmd_t *)cmd);
}

int cri_kdc_diversify_key(cri_kdc_t context, kdc_cmd_t *cmd)
{
	if (cmd != NULL) {
		/* Driver adds +1 to diversify_len. */
		cmd->diversify_len--;
	}
	return cmrt_kdc_diversify_key((cmrt_kdc_t)context, (cmrt_kdc_cmd_t *)cmd);
}

int cri_kdc_sync(cri_kdc_t context)
{
	return cmrt_kdc_sync((cmrt_kdc_t)context);
}

#ifdef __ZEPHYR__
int cri_kdc_set_permissions(cri_kdc_t context, const cmrt_omc_key_perm_t *perm)
{
	return cmrt_kdc_permissions((cmrt_kdc_t)context, perm);
}

void cri_kdc_disable(void)
{
	cmrt_kdc_disable();
}

int cri_kdc_set_hw_state(cri_kdc_t context, uint8_t hw_state)
{
	return cmrt_kdc_set_hw_state((cmrt_kdc_t)context, hw_state);
}

int cri_kdc_flush(cri_kdc_t context)
{
	ARG_UNUSED(context);
	return -ENOTSUP; /* flush is internal for KATs only */
}
#endif

#include <cri/cmrt/ktc.h>
#include <drivers/cmrt/ktc.h>

cri_ktc_t cri_ktc_open(void)
{
	return (cri_ktc_t)cmrt_ktc_open(CMRT_O_SYNC, 0);
}

void cri_ktc_close(cri_ktc_t context)
{
	cmrt_ktc_close((cmrt_ktc_t)context);
}

int cri_ktc_export_key(cri_ktc_t context, const ktc_cmd_t *cmd)
{
	return cmrt_ktc_export((cmrt_ktc_t)context, (const cmrt_ktc_cmd_t *)cmd);
}

#ifdef __ZEPHYR__
int cri_ktc_set_permissions(cri_ktc_t context, const cmrt_omc_key_perm_t *perm)
{
	return cmrt_ktc_permissions((cmrt_ktc_t)context, perm);
}
#endif

#include <cri/cmrt/omc.h>
#include <drivers/cmrt/omc.h>

cri_otp_t cri_otp_open(uint32_t flags)
{
	return (cri_otp_t)cmrt_omc_open(flags);
}

void cri_otp_close(cri_otp_t context)
{
	cmrt_omc_close((cmrt_omc_t)context);
}

int cri_otp_sync(cri_otp_t context)
{
	return cmrt_omc_sync((cmrt_omc_t)context);
}

#ifdef __ZEPHYR__
int cri_otp_reshadow(cri_otp_t context)
{
	return cmrt_omc_reshadow((cmrt_omc_t)context);
}
#endif

int cri_otp_write_device_id(cri_otp_t context, const uint8_t *data, size_t datalen)
{
	return cmrt_omc_write((cmrt_omc_t)context, OTP_DEVICE_ID_OFFSET, (const void *)data, datalen);
}

int cri_otp_write_oem_id(cri_otp_t context, const uint8_t *data, size_t datalen)
{
	return cmrt_omc_write((cmrt_omc_t)context, OTP_OEM_ID_OFFSET, (const void *)data, datalen);
}

int cri_otp_set_lifecycle(cri_otp_t context, uint32_t lc)
{
	return cmrt_omc_write((cmrt_omc_t)context, OTP_LIFECYCLE_OFFSET, (const void *)&lc, sizeof(lc));
}

#ifdef __ZEPHYR__
int cri_otp_setup_privilege(cri_otp_t context, const omc_perm_t *perm)
{
	return cmrt_omc_permissions((cmrt_omc_t)context, perm);
}
#endif

int cri_otp_write_keysplit(cri_otp_t context, int index, const cmrt_omc_key_split_t *keysplit)
{
	return cmrt_omc_write((cmrt_omc_t)context, OTP_KEYSPLIT_OFFSET(index), (const void *)keysplit, sizeof(*keysplit));
}

int cri_otp_obliterate_keysplit(cri_otp_t context, int index)
{
	return cmrt_omc_obliterate((cmrt_omc_t)context, OTP_KEYSPLIT_OFFSET(index));
}

int cri_otp_obliterate_dgok(cri_otp_t context)
{
	return cmrt_omc_obliterate((cmrt_omc_t)context, OTP_DGOK_OFFSET);
}

int cri_otp_read_root(cri_otp_t context, int index, cmrt_omc_root_t *root)
{
	return cmrt_omc_read((cmrt_omc_t)context, OTP_ROOT_OFFSET(index), (void *)root, sizeof(*root));
}

int cri_otp_write_root(cri_otp_t context, int index, const cmrt_omc_root_t *root)
{
	return cmrt_omc_write((cmrt_omc_t)context, OTP_ROOT_OFFSET(index), (const void *)root, sizeof(*root));
}

int cri_otp_obliterate_root(cri_otp_t context, int index)
{
	return cmrt_omc_obliterate((cmrt_omc_t)context, OTP_ROOT_OFFSET(index));
}

int cri_otp_obliterate_perso(cri_otp_t context)
{
	return cmrt_omc_obliterate((cmrt_omc_t)context, OTP_STATUS_WORD_OFFSET);
}

int cri_otp_set_tdv(cri_otp_t context, const uint32_t tdv[OMC_TDV_WORDS])
{
	return cmrt_omc_write((cmrt_omc_t)context, OTP_TDV_OFFSET, (const void *)tdv, sizeof(*tdv));
}

static int convert_esw_rsvd_offset(uint32_t offset)
{
	switch (offset) {
	case OTP_TBOOT_VERSION_WORD_OFFSET: return OTP_MACHINE_VERSION_OFFSET;
	case OTP_SUPERVISOR_VERSION_WORD_OFFSET: return OTP_SUPERVISOR_VERSION_OFFSET;
	default: break;
	}
	return (uint32_t)-1; /* invalid offset */
}


int cri_otp_read_esw_rsvd(cri_otp_t context, uint32_t offset, uint32_t *word)
{
	offset = convert_esw_rsvd_offset(offset);
	return cmrt_omc_read((cmrt_omc_t)context, offset, (void *)word, sizeof(*word));
}

int cri_otp_write_esw_rsvd(cri_otp_t context, uint32_t offset, uint32_t word)
{
	offset = convert_esw_rsvd_offset(offset);
	return cmrt_omc_write((cmrt_omc_t)context, offset, (const void *)&word, sizeof(word));
}

#include <cmrt/fboot/img_format.h>

int cri_otp_is_esw_area(cri_otp_t context, const uint32_t *address)
{
	ARG_UNUSED(context);

	if ((uintptr_t)address < CMRT_OTP_BASE ||
	    (uintptr_t)address >= (CMRT_OTP_BASE + CMRT_OTP_SIZE)) {
		return -EINVAL;
	}
	uint32_t offset = (uintptr_t)address - (uintptr_t)CMRT_OTP_BASE;
	if (offset < sizeof(cmrt_otp_layout_t)) {
		return -EACCES; /* HW managed */
	}
	if (offset < OTP_ESW_OFFSET ||
	    offset >= (OTP_ESW_OFFSET + OTP_ESW_SIZE)) {
		return 0; /* valid eSW but reserved */
	}
#ifdef CONFIG_CRI_SBOOT_IN_ROM
	return 1; /* ok, no sboot in OTP */
#else
	cmrt_img_header_t *hdr = cmrt_otp_layout(OTP_ESW_OFFSET);
	if (!cmrt_is_valid_hdr(hdr, OTP_ESW_SIZE)) {
		return -EBADF; /* invalid sboot header */
	}
	if (offset < (hdr->length + sizeof(*hdr))) {
		return 0; /* valid eSW but reserved */
	}
#endif
	return 1; /* ok, unreserved eSW */
}

int cri_otp_oec_read(cri_otp_t context, uint32_t address, void *buffer, size_t *len)
{
	return cmrt_oec_read((cmrt_omc_t)context, address, buffer, *len);
}

int cri_otp_oec_write(cri_otp_t context, uint32_t address, const void *buffer, size_t len)
{
	return cmrt_oec_write((cmrt_omc_t)context, address, buffer, len);
}

int cri_otp_oec_commit(cri_otp_t context)
{
	return cmrt_oec_commit((cmrt_omc_t)context);
}

cri_aes_t cri_otp_oec_derive(cri_otp_t context, cri_aes_operation_t operation, uint8_t keysplit)
{
	ARG_UNUSED(context);
	ARG_UNUSED(operation);
	ARG_UNUSED(keysplit);
	return NULL; /* should not be external function */
}

#include <cri/cmrt/pke.h>
#include <drivers/cmrt/pke.h>

static inline int sync(cmrt_pke_t pke, int res)
{
	if (res >= 0) {
		res = cmrt_pke_sync(pke);
	}
	return res;
}

cri_ecc_curve_t cri_pke_get_curve(uint32_t curve)
{
	return (cri_ecc_curve_t) cmrt_pke_get_curve(curve);
}

uint32_t cri_pke_get_curve_length(cri_ecc_curve_t curve)
{
	return cmrt_pke_get_curve_length((cmrt_ecc_curve_t) curve);
}

cri_pke_t cri_pke_open(uint32_t flags)
{
	/* Flags are passed through unmodified: the sync flag was
	 * never supported under v1, any of the synchronous functions
	 * are now manually synchronized in the wrapper API, resulting
	 * in a performance hit.
	 */
	return (cri_pke_t)cmrt_pke_open(flags & ~CRI_O_SYNC);
}

void cri_pke_close(cri_pke_t context)
{
	cmrt_pke_close((cmrt_pke_t) context);
}

int cri_pke_sync(cri_pke_t context)
{
	return cmrt_pke_sync((cmrt_pke_t) context);
}

int cri_pke_flush(cri_pke_t context)
{
	return cmrt_pke_flush((cmrt_pke_t) context);
}

int cri_pke_ecdsa_verify(cri_pke_t context, cri_ecc_curve_t curve, const void *pub_x, const void *pub_y, const void *digest, const void *sign_r, const void *sign_s, void *rprime)
{
	return cmrt_pke_ecdsa_verify((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, pub_x, pub_y, digest, sign_r, sign_s, rprime);
}

int cri_pke_ecdsa_verify_hash(cri_pke_t context, cri_ecc_curve_t curve, const void *pub_x, const void *pub_y, const void *digest, unsigned int digest_len, const void *sign_r, const void *sign_s, void *rprime)
{
	return cmrt_pke_ecdsa_verify_hash((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, pub_x, pub_y, digest, digest_len, sign_r, sign_s, rprime);
}

int cri_pke_ecdsa_sign(cri_pke_t context, cri_ecc_curve_t curve, const void *priv_key, const void *digest, void *sign_r, void *sign_s)
{
	return cmrt_pke_ecdsa_sign((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, priv_key, digest, sign_r, sign_s);
}

int cri_pke_ecdsa_sign_hash(cri_pke_t context, cri_ecc_curve_t curve, const void *priv_key, const void *digest, unsigned int digest_len, void *sign_r, void *sign_s)
{
	return cmrt_pke_ecdsa_sign_hash((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, priv_key, digest, digest_len, sign_r, sign_s);
}

int cri_pke_ecdsa_keygen(cri_pke_t context, cri_ecc_curve_t curve, const void *priv_key, void *pub_x, void *pub_y)
{
	return cmrt_pke_ecdsa_keygen((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, priv_key, pub_x, pub_y);
}

int cri_pke_rsa_public_key_primitive(cri_pke_t context, uint32_t bits, const uint32_t *mod, const uint32_t *public_key, const uint32_t *signature, uint32_t *message)
{
	return cmrt_pke_rsa_public_key_primitive((cmrt_pke_t) context, bits, (const uint8_t*) mod, (const uint8_t *) public_key, (const uint8_t *) signature, (uint8_t *) message);
}

int cri_pke_ecdh_keygen(cri_pke_t context, cri_ecc_curve_t curve, const void *priv_key, void *pub_x)
{
	return cmrt_pke_ecdh_keygen((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, priv_key, pub_x);
}

int cri_pke_ecdh(cri_pke_t dev, cri_ecc_curve_t curve, const void *priv_key, const void *peer_key, void *shared_secret)
{
	return cmrt_pke_ecdh((cmrt_pke_t) dev, (cmrt_ecc_curve_t) curve, priv_key, peer_key, shared_secret);
}

int cri_pke_rfc7748_keygen(cri_pke_t context, cri_ecc_curve_t curve, const void *priv_key, void *pub_x)
{
	return cmrt_pke_rfc7748_keygen((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, priv_key, pub_x);
}

int cri_pke_rfc7748(cri_pke_t context, cri_ecc_curve_t curve, const void *priv_key, const void *pub_x, void *shared_secret)
{
	return cmrt_pke_rfc7748((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, priv_key, pub_x, shared_secret);
}

int cri_pke_eddsa_sign(cri_pke_t context, cri_ecc_curve_t curve, const void *priv_key, const void *message, unsigned int msglen, void *sign_r, void *sign_s)
{
	return cmrt_pke_eddsa_sign((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, priv_key, message, msglen, sign_r, sign_s);
}

int cri_pke_eddsa_verify(cri_pke_t context, cri_ecc_curve_t curve, const void *pub_x, const void *message, unsigned int msglen, const void *sign_r, const void *sign_s, void *rprime)
{
	return cmrt_pke_eddsa_verify((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, pub_x, message, msglen, sign_r, sign_s, rprime);
}

int cri_pke_eddsa_keygen(cri_pke_t context, cri_ecc_curve_t curve, const void *priv_key, void *pub_x)
{
	return cmrt_pke_eddsa_keygen((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, priv_key, pub_x);
}

int cri_pke_validate_ecc_xy_key(cri_pke_t context, cri_ecc_curve_t curve, const void *pub_x, const void *pub_y)
{
	return cmrt_pke_validate_ecc_xy_key((cmrt_pke_t) context, (cmrt_ecc_curve_t) curve, pub_x, pub_y);
}

#include <string.h>

int cri_pke_rsa_private_key_primitive(cri_pke_t context, uint32_t bits, const uint32_t *mod, const uint32_t *public_exp, const uint32_t *priv_exp, const uint32_t *message, uint32_t *signature)
{
	struct cmrt_rsa_ctx ctx;
	uint32_t mask = 0;

	memset(&ctx, 0, sizeof(ctx));
	ctx.key.bits = bits;
	ctx.key.mask = (uint8_t *)&mask;
	ctx.key.flags = 0;
	ctx.key.n = (uint8_t *)mod;
	ctx.key.e = (uint8_t *)public_exp;
	ctx.key.elength = bits / 8;
	ctx.key.d = (uint8_t *)priv_exp;
	ctx.signature = (uint8_t *)signature;
	ctx.message = (uint8_t *)message;

	int res = cmrt_pke_rsa_sign((cmrt_pke_t) context, &ctx);
	if (res >= 0) {
		res = cmrt_pke_sync(context);
	}
	return res;
}

#include <drivers/cmrt/util.h>

int cri_pke_rsa_crt_primitive(cri_pke_t dev, const struct cri_rsa_key *key, const uint32_t *message, uint32_t *signature, uint32_t *scratch, size_t scratch_size)
{
	cmrt_pke_t pke = (cmrt_pke_t)dev;
	uint32_t mask = 0;

	struct cmrt_rsa_ctx ctx = {
		.key.bits = key->bits,
		.key.n = (uint8_t *)key->n,
		.key.e = (uint8_t *)key->e,
		.key.elength = key->bits / 8,
		.key.d = (uint8_t *)key->d,
		.key.p = (uint8_t *)key->p,
		.key.q = (uint8_t *)key->q,
		.key.dp = (uint8_t *)key->dp,
		.key.dq = (uint8_t *)key->dq,
		.key.iq = (uint8_t *)key->iq,

		.key.mask = (uint8_t *)&mask,
		.signature = (uint8_t *)signature,
		.message = (uint8_t *)message
	};
	int res = sync(pke, cmrt_pke_rsa_crt_sign(pke, &ctx));
	(void)memset(scratch, 0, scratch_size);
	return res;
}

int cri_pke_rsa_keygen(cri_pke_t dev,
		       const struct cri_rsa_keygen_params *params,
		       struct cri_rsa_key *key)
{
	int res = -1;
	if (params && key) {
		struct cmrt_rsa_key v2key = {
			.bits = params->bits,
			.flags = 0,
			.n = (uint8_t *)key->n,
			.e = (uint8_t *)key->e,
			.elength = params->bits / 8,
			.d = (uint8_t *)key->d,
			.p = (uint8_t *)key->p,
			.q = (uint8_t *)key->q,
			.dp = (uint8_t *)key->dp,
			.dq = (uint8_t *)key->dq,
			.iq = (uint8_t *)key->iq
		};
		cmrt_pke_t pke = (cmrt_pke_t)dev;

#ifdef CONFGI_CMRT_RSA_CRT
		if (key->p) {
			res = cmrt_pke_rsa_crt_key_gen(pke, &v2key);
		} else
#endif
		{
			res = cmrt_pke_rsa_key_gen(pke, &v2key);
		}
		res = sync(pke, res);
	}
	return res;
}

#ifdef CONFIG_CMRT_FFDH

int cri_pke_ffdh(cri_pke_t context, size_t mod_size, const void *p, const void *q, const void *g, const void *priv_key, const void *peer_key, void *pub_key, void *shared_key)
{
	/* From drivers/cri/cmrt/pke3/ffdh.c:153 mod_size is used for p,q,g sizes as well. */
	uint32_t aux_mod_size = (uint32_t) mod_size;
	uint32_t aux_mod_size_bits = aux_mod_size << 3;

	const struct cmrt_ffdh_param aux_ffdh_param = {
		.mod_size = aux_mod_size,
		.mod_bits = aux_mod_size_bits,
		.p = (uint8_t *) p,
		.q = (uint8_t *) q,
		.g = (uint8_t *) g,
		.grp_size = aux_mod_size,
		.grp_bits = aux_mod_size_bits,
		.gen_size = aux_mod_size
	};

	cmrt_pke_t pke = (cmrt_pke_t)context;
	int res = cmrt_pke_ffdh(pke, &aux_ffdh_param, priv_key, peer_key,
				pub_key, shared_key);
	return sync(pke, res);
}

int cri_pke_ffdh_keygen(cri_pke_t context, size_t mod_size, const void *q, void *priv_key)
{
	cmrt_pke_t pke = (cmrt_pke_t)context;
	int res = cmrt_pke_ffdh_private_keygen(pke, mod_size, q, priv_key);
	return sync(pke, res);
}

int cri_pke_ffdh_verify(cri_pke_t context, size_t psize, const uint32_t *p, size_t qsize, const uint32_t *q, size_t gsize, const uint32_t *g)
{
	cmrt_pke_t pke = (cmrt_pke_t)context;
	const struct cmrt_ffdh_param aux_ffdh_param = {
		.mod_size = psize,
		.mod_bits = psize << 3,
		.p = (uint8_t *) p,
		.q = (uint8_t *) q,
		.g = (uint8_t *) g,
		.grp_size = qsize,
		.grp_bits = qsize << 3,
		.gen_size = gsize
	};

	return sync(pke, cmrt_pke_ffdh_verify(pke, &aux_ffdh_param));
}

int cri_pke_ffdh_parmgen(cri_pke_t context, size_t pbits, size_t qbits, uint32_t *presult, uint32_t *qresult, uint32_t *gresult)
{
	cmrt_pke_t pke = (cmrt_pke_t)context;
	struct cmrt_ffdh_param aux_ffdh_param = {
		.mod_size = pbits >> 3,
		.mod_bits = pbits,
		.p = (uint8_t *) presult,
		.q = (uint8_t *) qresult,
		.g = (uint8_t *) gresult,
		.grp_size = qbits >> 3,
		.grp_bits = qbits,
		.gen_size = 0
	};

	int res = cmrt_pke_ffdh_parmgen(pke, pbits, qbits, &aux_ffdh_param);
	return sync(pke, res);
}

#endif /* CONFIG_CMRT_FFDH  */

#ifdef CONFIG_CMRT_FIPS_140_MODE
int cri_pke_ecc_pairwise_consistency_check(cri_ecc_curve_t curve,
					   const uint32_t asset_type,
					   const uint8_t *private_key,
					   const uint8_t *pub_x,
					   const uint8_t *pub_y)
{
	ARG_UNUSED(asset_type);
	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	int rc = cmrt_pke_ecc_pairwise_consistency_check(pke, curve, private_key, pub_x, pub_y);
	cmrt_pke_close(pke);
	return rc;
}
#endif

#ifdef __ZEPHYR__
#include <cri/cmrt/pmu.h>
#include <drivers/cmrt/pmu.h>

int cri_pmu_low_power(bool allowed)
{
	return cmrt_pmu_low_power(allowed);
}

void cri_pmu_to_idle(void)
{
	cmrt_pmu_to_idle();
}

void cri_pmu_from_idle(void)
{
}
#endif

#include <cri/cmrt/sac.h>
#ifdef __ZEPHYR__
#include <drivers/cmrt/sac.h>

int cri_sac_segment_config(uint32_t value, uint32_t index)
{
	return cmrt_sac_set_config(value, index);
}

int cri_sac_request_flush(void)
{
	return -ENOTSUP; /* flush is internal for KATs only */
}
#else
int cri_sac_segment_config(uint32_t value, uint32_t index)
{
	ARG_UNUSED(value);
	ARG_UNUSED(index);
	return -ENOTSUP; /* not supported by the user mode */
}
#endif

#include <cri/cmrt/sic.h>
#include <drivers/cmrt/sic.h>

cri_sic_t cri_sic_open(uint32_t flags, uint32_t flowid)
{
	return (cri_sic_t)cmrt_sic_open(flags, flowid);
}

void cri_sic_close(cri_sic_t context)
{
	cmrt_sic_close((cmrt_sic_t)context);
}

int cri_sic_read(cri_sic_t context, void *buffer, size_t *buflen, uint32_t *peerid)
{
	return cmrt_sic_read((cmrt_sic_t)context, buffer, buflen, peerid, 0);
}

int cri_sic_write(cri_sic_t context, const void *buffer, size_t buflen, uint32_t peerid)
{
	return cmrt_sic_write((cmrt_sic_t)context, buffer, buflen, peerid);
}

int cri_sic_sync(cri_sic_t context)
{
	return cmrt_sic_sync((cmrt_sic_t)context);
}

#ifdef __ZEPHYR__
bool cri_sic_is_idle(void)
{
	return cmrt_sic_is_idle();
}
#endif

#include <cri/cmrt/sid.h>
#include <drivers/cmrt/sid.h>

cri_sid_t cri_sid_open(uint32_t flags, uint32_t irqs)
{
	return (cri_sid_t)cmrt_sid_open(flags, irqs);
}

void cri_sid_close(cri_sid_t dev)
{
	cmrt_sid_close((cmrt_sid_t)dev);
}

int cri_sid_watch(cri_sid_t dev, uint32_t state, uint32_t mask, uint32_t *irqs)
{
	ARG_UNUSED(mask);
	return cmrt_sid_watch((cmrt_sid_t)dev, state, irqs);
}

int cri_sid_sync(cri_sid_t dev)
{
	return cmrt_sid_sync((cmrt_sid_t)dev);
}

#include <cri/cmrt/tmc.h>
#include <drivers/cmrt/tmc.h>
#include <drivers/cmrt/util.h>

cri_tmc_t cri_tmc_open(uint32_t flags)
{
	return (cri_tmc_t)cmrt_tmc_open(flags, NULL);
}

#ifdef __ZEPHYR__
cri_tmc_t cri_tmc_open_kdc(void)
{
	return (cri_tmc_t)cmrt_tmc_open(CMRT_O_TMC_KDC, NULL);
}
#endif

void cri_tmc_close(cri_tmc_t context)
{
	cmrt_tmc_close((cmrt_tmc_t)context);
}

int cri_tmc_reseed(cri_tmc_t context, uint8_t *buffer, uint32_t size)
{
	return cmrt_tmc_command((cmrt_tmc_t)context, CMRT_TMC_RESEED_GENERATE, (void *)buffer, (size_t)size);
}

int cri_tmc_generate(cri_tmc_t context, uint8_t *buffer, size_t size)
{
	return cmrt_tmc_command((cmrt_tmc_t)context, CMRT_TMC_GENERATE, (void *)buffer, (size_t)size);
}

int cri_tmc_sync(cri_tmc_t context)
{
	return cmrt_tmc_sync((cmrt_tmc_t)context);
}

#ifdef CONFIG_CMRT_FIPS_140_MODE
int cri_tmc_command(cri_tmc_t context, uint32_t command, uint32_t *buffer, uint32_t length)
{
	return cmrt_tmc_command((cmrt_tmc_t)context, command, (void *)buffer, (size_t)length);
}
#endif

/*** User containers ***/

#ifndef __ZEPHYR__
#include <container.h>
extern int main(void);
#endif

#include <cri/cmrt/random.h>
#include <drivers/cmrt/util.h>

int cri_get_random(void *buf, size_t len)
{
	return cmrt_get_random(buf, len);
}

#include <crisyscall-user.h>
#include <drivers/cmrt/fboot.h>

int cri_create_root(int index, cmrt_omc_root_t *new_root)
{
	return fboot_create_root(index, new_root);
}

int cri_obliterate_root(int index)
{
	return fboot_obliterate_root(index);
}

int cri_get_img_version(enum cri_image_version_id imageid, void *version, size_t *size)
{
	enum cmrt_image_version_id aux_image_id;
	switch (imageid) {
		case CMRT_FBOOT_VERSION:
			aux_image_id = CMRT_FBOOT_IMAGE_VERSION;
			return fboot_get_image_version(aux_image_id, version, size);
		case CMRT_SBOOT_VERSION:
			aux_image_id = CMRT_SBOOT_IMAGE_VERSION;
			return fboot_get_image_version(aux_image_id, version, size);
		case CMRT_SUPERVISOR_VERSION:
			aux_image_id = CMRT_SUPERVISOR_IMAGE_VERSION;
			return fboot_get_image_version(aux_image_id, version, size);
		default:
			return -EINVAL;
	}
}

int cri_get_uptime(int64_t *uptime)
{
	if (uptime == NULL) {
		return -EINVAL;
	}
	*uptime = cmrt_uptime_get();
	return 0;
}

int cri_uptime_delta(int64_t *ref)
{
	if (ref == NULL) {
		return -EINVAL;
	}
	int64_t now = cmrt_uptime_get();
	int64_t delta = now - *ref;
	if ((delta >> 31) != 0) {
		/* Larger than the return value. */
		return -EFBIG;
	}
	return (int)delta;
}

int cri_get_cycles(uint64_t *cycles)
{
	if (cycles == NULL) {
		return -EINVAL;
	}
	*cycles = cmrt_perf_ref();
	return 0;
}

int cri_cycles_delta(uint64_t *ref)
{
	if (ref == NULL) {
		return -EINVAL;
	}
	uint64_t now = cmrt_perf_ref();
	uint64_t delta = now - *ref;
	if ((delta >> 31) != 0) {
		/* Larger than the return value. */
		return -EFBIG;
	}
	return (int)delta;
}
