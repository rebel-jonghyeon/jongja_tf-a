/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */

#include <zephyr.h>
#include <string.h>
#include <stdalign.h>
#include <stdint.h>
#include <assert.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/dmac.h>
#include <drivers/cmrt/fboot.h>
#include <drivers/cmrt/sac.h>
#include <drivers/cmrt/sac_mem.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/util.h>
#include <sys/util.h>

#include <cmrt/caliptra/flow.h>
#include <cmrt/caliptra/types.h>
#include <cmrt/caliptra/assets.h>
#include <cmrt/caliptra/x509.h>

#ifndef CONFIG_CMRT_SBOOT_IN_ROM
#include "sboot_img.h"
#endif
#include "common.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

const static char version_info[] __version = PERSO_VERSION_INFO;

#ifndef CONFIG_CMRT_FBOOT_HAS_ECDSA_P384
#error "Fboot must have support for EC NIST P384 signature for caliptra"
#endif

#define PERSO_FLOWID 123u

#define PERSO_STATUS_STARTED        0x930500ff
#define PERSO_STATUS_PART1_DONE     0x93050080
#define PERSO_STATUS_PART2_DONE     0x93050000
#define PERSO_STATUS_ERROR          0x93050100

/*
 * OTP ESW permissions depends upon size of sboot image and location
 * of OTP reserved words, therefore can't be fixed. See
 * setup_user_root_permissions().
 *
 * Access to keysplit 1 is not mandated by the spec, but it is allowed
 * for encrypted image support.
 *
 * Access to the lifecycle slot is granted.
 */
static cmrt_omc_root_t supervisor_root = {
	.id.hash = {
#include "pkhash_ecdsa_p384.inc"
	},
	.perm.slot_perm.val = 0,

	/* To support encrypted MW images. */
	.perm.key_perm.val = OMC_SLOT_PERMS_KEYSPLIT_1,
	.perm.feature_perm.val = 0,
	.perm.sw_otp_perm[0].val = 0,
	.perm.sw_otp_perm[1].val = 0,
	.perm.software_perm.val = (0XFFFFFFFF & ~OMC_SW_LOAD_PERM_MASK) | OMC_SW_PERM_SUPERVISOR,
};

static cmrt_omc_root_t user_root = {
	.id.hash = {
#include "pkhash_ecdsa_p384_2.inc"
	},
	.perm.slot_perm.val = OMC_SLOT_PERM_LIFECYCLE,

	/* To support encrypted user container image. */
	.perm.key_perm.val = OMC_SLOT_PERMS_KEYSPLIT_1,
	.perm.feature_perm.val = 0x7FFFFFFF,

	/* OTP eSW permissions are set in burn_roots(). */
	.perm.sw_otp_perm[0].val = 0,
	.perm.sw_otp_perm[1].val = 0,
	.perm.software_perm.val = (0XFFFFFFFF & ~OMC_SW_LOAD_PERM_MASK) | OMC_SW_PERM_SILO_CONTAINER,
};

static struct cmrt_perso_root roots[] = {
	{&supervisor_root, "Supervisor"},
	{&user_root, "User"},
	{NULL, ""}
};

static_assert(
	CONFIG_CRI_OMC_ROOTS_NUM + 1  >= sizeof(roots) / sizeof(struct cmrt_perso_root), \
	"too many roots for device");

static const cmrt_omc_key_split_t omc_keysplit0 = {
	.key = { 0x2e, 0xd4, 0xd0, 0x81, 0xa5, 0x11, 0xff, 0xde,
		 0xa6, 0x3e, 0xcb, 0x58, 0xc0, 0x50, 0x20, 0x23,
		 0x32, 0x92, 0x0a, 0x72, 0xe3, 0x0f, 0x9e, 0x80,
		 0x4c, 0xe3, 0xaf, 0xd8, 0xdb, 0x61, 0xaf, 0xf2
	}
};

typedef struct {
	uint32_t cmd;
	uint32_t use_tmc;
	cmrt_caliptra_field_entropy_t value;
} cmrt_caliptra_msg_write_field_entropy;

typedef struct {
	uint32_t cmd;
	uint32_t max_len;
	uint64_t sac_address;
} cmrt_caliptra_msg_export_idevid_csr;

typedef struct {
	uint32_t cmd;
	uint32_t chain_len;
	uint64_t sac_address;
} cmrt_caliptra_msg_import_idevid_cert_chain;

#define CMRT_CALIPTRA_CMD_WRITE_FIELD_ENTROPY 1
#define CMRT_CALIPTRA_CMD_EXPORT_IDEVID_CSR 2
#define CMRT_CALIPTRA_CMD_IMPORT_IDEVID_CERT_CHAIN 3

static cmrt_caliptra_oam_t oam;
static alignas(4) uint8_t fboot_ver[48];
static size_t fboot_ver_len = sizeof(fboot_ver);
static alignas(4) uint8_t sboot_ver[48];
static size_t sboot_ver_len = sizeof(sboot_ver);
static cmrt_caliptra_deviceinfo_t devinfo;

static int write_field_entropy(const cmrt_caliptra_msg_write_field_entropy *const msg)
{
	int res = 0;
	cmrt_caliptra_field_entropy_t value;

	if (msg->use_tmc == 1) {
		res = cmrt_get_random(&value, sizeof(value));
	} else {
		(void)memcpy(&value, &msg->value, sizeof(value));
	}
	if (res == 0) {
		res = cmrt_caliptra_oam_write_field_entropy(oam, &value);
	}
	return res;
}

/* Check if the given [address, address+size] buffer is inside the 3GB
 * SAC window starting at 0x4000_0000.
 */
static inline bool buffer_in_sac_window(uint32_t address, size_t size)
{
	const uint32_t sacmem_begin = SAC_MEMORY_BASE;
	const uint32_t sacmem_end = UINT32_MAX;
	const uint32_t buf_end = address + size;
	/* Some of the following checks may be redundant, as
	* 'sacmem_end' is UINT32_MAX, but good to have them if it
	* ever changes. Check for unsigned wraparound.
	*/
	return ((address >= sacmem_begin) &&
		(address <= sacmem_end) &&
		(buf_end <= sacmem_end) &&
		(buf_end >= address));
}

static int generate_idevid_csr(void *buf, size_t *len)
{
	int res;

	cmrt_caliptra_uds_t uds_seed;
	res = cmrt_caliptra_oam_read_uds_seed(oam, &uds_seed);
	cmrt_caliptra_digest_t uds_hash;
	if (res == 0) {
		/* Temporarily release OMC while deobfuscating the UDS
		 * hash because KDC needs it.
		 */
		cmrt_caliptra_oam_close(oam);
		res = cmrt_caliptra_derive_uds_hash(&uds_seed, &uds_hash);
		(void)cmrt_caliptra_oam_open(oam);
	}

	/* IDevID {priv, pub} := eccKPDF(udsHash, "IDevID key pair") */
	cmrt_caliptra_privkey_t idevid_priv;
	cmrt_caliptra_pubkey_t idevid_pub;
	if (res == 0) {
		res = cmrt_caliptra_ecckpdf(&uds_hash, sizeof(uds_hash),
					    CMRT_KP_INFO_IDevID, strlen(CMRT_KP_INFO_IDevID),
					    &idevid_priv, &idevid_pub);
	}

	cmrt_caliptra_tcb_t idevid = {
		.identity = CMRT_CALIPTRA_ID_IDevID,
		.privkey = &idevid_priv,
		.pubkey = &idevid_pub,
	};
	cmrt_caliptra_tcbinfo_t tcbis[] = {
		{
			.version = fboot_ver,
			.version_len = fboot_ver_len,
			.layer = 0,
		},
		{
			.version = sboot_ver,
			.version_len = sboot_ver_len,
			.layer = 0,
		},
	};

	cmrt_caliptra_csr_params_t idevid_csr_par = {
		.subject = &idevid,
		.deviceinfo = &devinfo,
		.tcbinfos = tcbis,
		.tcbinfos_len = ARRAY_SIZE(tcbis),
	};
	if (res == 0) {
		res = cmrt_caliptra_write_csr(buf, len, &idevid_csr_par);
		if (res != 0) {
			LOG_INF("failed to generate CSR: %d", res);
		}
	}

	/* Clear assets from memory. */
	cmrt_caliptra_zeroize(&uds_seed, sizeof(uds_seed));
	cmrt_caliptra_zeroize(&uds_hash, sizeof(uds_hash));
	cmrt_caliptra_zeroize(&idevid_priv, sizeof(idevid_priv));
	cmrt_caliptra_zeroize(&idevid_pub, sizeof(idevid_pub));
	return res;
}

static int export_idevid_csr(const cmrt_caliptra_msg_export_idevid_csr *const msg)
{
	alignas(4) static uint8_t idevid_csr[1024];
	size_t idevid_csr_len = sizeof(idevid_csr);

	int res = generate_idevid_csr(idevid_csr, &idevid_csr_len);

	uint32_t sac_lo = (uint32_t)msg->sac_address;
	uint32_t sac_hi = (uint32_t)(msg->sac_address >> 32);
	uint64_t last_base = cmrt_sac_set_base(NULL, (uint64_t)sac_hi << 32);
	uint32_t cmrt_sac_addr = sac_lo + SAC_MEMORY_BASE;

	size_t wlen = ROUND_UP(idevid_csr_len + 4, 4u);
	if (wlen > msg->max_len) {
		res = -ENOBUFS;
	}

	if ((res == 0) && !buffer_in_sac_window(cmrt_sac_addr, msg->max_len)) {
		res = -ENXIO;
	}

	if (res == 0) {
		/* Write IDEVID CSR to SAC. */
		res = -ENODEV;
		cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);
		if (cmrt_is_valid(dmac)) {
			res = cmrt_dmac_data(dmac, (uintptr_t)idevid_csr, cmrt_sac_addr + 4, wlen, 0);
			if (res == 0) {
				/* Write size header. */
				cmrt_sac_write32(idevid_csr_len, cmrt_sac_addr);
			}
			cmrt_dmac_close(dmac);
		}
	}
	(void)cmrt_sac_set_base(NULL, last_base);
	return res;
}

static int import_idevid_cert_chain(const cmrt_caliptra_msg_import_idevid_cert_chain *const msg)
{
	uint32_t sac_lo = (uint32_t)msg->sac_address;
	uint32_t sac_hi = (uint32_t)(msg->sac_address >> 32);

	uint64_t last_base = cmrt_sac_set_base(NULL, (uint64_t)sac_hi << 32);
	uint32_t cmrt_sac_addr = sac_lo + SAC_MEMORY_BASE;

	int res = 0;
	if (!buffer_in_sac_window(cmrt_sac_addr, msg->chain_len)) {
		res = -ENXIO;
	}
	alignas(4) static uint8_t chain[CMRT_CALIPTRA_IDEVID_CHAIN_MAX_LEN];
	if (res == 0 && (msg->chain_len > sizeof(chain))) {
		/* Data would overflow. */
		res = -ENOBUFS;
	}

	/* Copy data to buffer. */
	if (res == 0) {
		res = -ENODEV;
		size_t size = (msg->chain_len + 3) & ~3;
		cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);
		if (cmrt_is_valid(dmac)) {
			res = cmrt_dmac_data(dmac, cmrt_sac_addr,
					     (uint32_t)(uintptr_t)chain, size, 0);
			cmrt_dmac_close(dmac);
		}
	}

	if (res == 0) {
		/* Write buffer to OTP. */
		if (res == 0) {
			res = cmrt_caliptra_oam_write_idevid_cert_chain(oam, chain, msg->chain_len);
		}
	}
	(void)cmrt_sac_set_base(NULL, last_base);
	return res;
}

typedef union cmrt_caliptra_setup_message {
	/* Each message starts with the command word. */
	uint32_t cmd;
	cmrt_caliptra_msg_write_field_entropy wfe;
	cmrt_caliptra_msg_export_idevid_csr eic;
	cmrt_caliptra_msg_import_idevid_cert_chain iicc;
} cmrt_caliptra_setup_message_t;

typedef enum {
	done_write_field_entropy = 1,
	done_export_idevid_csr = 2,
	done_import_idevid_cert_chain = 4,

	done_all = (done_write_field_entropy |
		    done_export_idevid_csr |
		    done_import_idevid_cert_chain),
} setup_state_t;


static int process_command(const cmrt_caliptra_setup_message_t *const msg,
			   size_t len, uint32_t *done)
{
	if (done == NULL) {
		return -EINVAL;
	}
	int res = -EINVAL;
	switch (msg->cmd) {
	case CMRT_CALIPTRA_CMD_WRITE_FIELD_ENTROPY:
		LOG_INF("Running command WRITE_FIELD_ENTROPY");
		if (len == sizeof(cmrt_caliptra_msg_write_field_entropy)) {
			if ((*done & done_write_field_entropy) == 0u) {
				res = write_field_entropy(&msg->wfe);
			} else {
				res = -EEXIST;
			}
			if (res == 0) {
				*done |= done_write_field_entropy;
			}
		}
		break;
	case CMRT_CALIPTRA_CMD_EXPORT_IDEVID_CSR:
		LOG_INF("Running command EXPORT_IDEVID_CSR");
		if (len == sizeof(cmrt_caliptra_msg_export_idevid_csr)) {
			res = export_idevid_csr(&msg->eic);
			if (res == 0) {
				*done |= done_export_idevid_csr;
			}
		}
		break;
	case CMRT_CALIPTRA_CMD_IMPORT_IDEVID_CERT_CHAIN:
		LOG_INF("Running command IMPORT_IDEVID_CERT_CHAIN");
		if (len == sizeof(cmrt_caliptra_msg_import_idevid_cert_chain)) {
			res = import_idevid_cert_chain(&msg->iicc);
			if (res == 0) {
				*done |= done_import_idevid_cert_chain;
			}
		}
		break;
	default:
		LOG_INF("Unknown command %u\n", msg->cmd);
		return -EINVAL;
	}
	LOG_INF("Command returned: %d", res);
	return res;
}

static int process_sic_message(void)
{
	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, PERSO_FLOWID);
	if (!cmrt_is_valid(sic)) {
		LOG_INF("Cannot open SIC");
		return -ENODEV;
	}

	int res = 0;
	uint32_t done = 0;
	/* Process SIC messages as long as no error occurs and all possible
	 * commands are not executed. */
	while ((done & done_all) != done_all) {
		uint32_t peerid;
		cmrt_caliptra_setup_message_t msg;
		size_t buflen = sizeof(msg);

		/* Wait for command from HLOS over SIC. */
		LOG_INF("Waiting for SIC command... done %d", done);
		res = cmrt_sic_read(sic, &msg, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read SIC message from HLOS: %d!\n", res);
			break;
		}

		/* Process command. */
		LOG_INF("New command... peer %u", peerid);

		if (buflen < sizeof(uint32_t)) {
			LOG_INF("Invalid command");
			continue;
		}
		res = process_command(&msg, buflen, &done);

		/* Send return code over SIC to HLOS. */
		int ret2 = cmrt_sic_write(sic, &res, sizeof(res), peerid);
		if (ret2) {
			LOG_INF("Failed to setup SIC write to HLOS: %d!", ret2);
			res = ret2;
			break;
		}
	}
	return res;
}

static bool have_oem_id(void)
{
	bool nonzero = false;
	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC);
	int res = -ENODEV;
	if (cmrt_is_valid(omc)) {
		uint32_t oem_id[2];
		res = cmrt_omc_read(omc, OTP_OEM_ID_OFFSET, oem_id, sizeof(oem_id));
		if (res == 0) {
			nonzero = (oem_id[0] != 0u) || (oem_id[1] != 0u);
		}
		cmrt_omc_close(omc);
	}
	if (res != 0) {
		LOG_INF("Failed to read OEM ID: %d!", res);
	}
	return nonzero;
}

static void setup_user_root_permissions(void)
{
#ifdef CONFIG_CMRT_SBOOT_IN_ROM
	size_t sboot_img_len = 0;
#endif
	cmrt_omc_root_perm_t *perm = &user_root.perm;
#ifdef CONFIG_CMRT_OMC_ESW_RSVD_FIRST
	/* Allow access to reserved words. */
	uint32_t start = 0;
	uint32_t end = (CONFIG_CMRT_OMC_ESW_RSVD_WORDS * sizeof(uint32_t)) - 4;
	perm->sw_otp_perm[0].val = OMC_SW_OTP_PERM_RW | start | (end << 16);

	/* Allow access from field entropy to end of OTP. */
	start = (CONFIG_CMRT_OMC_ESW_RSVD_WORDS * sizeof(uint32_t)) \
		 + sboot_img_len \
		 + CMRT_CALIPTRA_UDS_LEN;
	end = CMRT_OTP_SIZE - sizeof(cmrt_otp_layout_t) - 4;
	perm->sw_otp_perm[1].val = OMC_SW_OTP_PERM_RW | start | (end << 16);
#else
	/* Allow access from field entropy to end of OTP, including reserved words. */
	uint32_t start = sboot_img_len + CMRT_CALIPTRA_UDS_LEN;
	uint32_t end = CMRT_OTP_SIZE - sizeof(cmrt_otp_layout_t) - 4;
	perm->sw_otp_perm[0].val = OMC_SW_OTP_PERM_RW | start | (end << 16);

	perm->sw_otp_perm[1].val = 0;
#endif
}

static int part1(void)
{
	int res = cmrt_burn_dgok();
	if (res == 0) {
		res = cmrt_perso_write_otp_keysplit(0, &omc_keysplit0);
	}
	if (res == 0) {
		res = cmrt_perso_burn_device_id();
	}
	if (res == 0) {
		const uint32_t oem_id[2] = { 1 };
		res = cmrt_perso_burn_oem_id(oem_id, sizeof(oem_id));
	}
	if (res == 0) {
		LOG_INF("Reboot needed. Reboot CMRT and reload this perso.");
		cmrt_set_perso_status(PERSO_STATUS_PART1_DONE);
	}
	return res;
}

static int part2(void)
{
	setup_user_root_permissions();
	int res = cmrt_perso_create_roots(roots);
#ifndef CONFIG_CMRT_SBOOT_IN_ROM
	if (res == 0) {
		res = cmrt_perso_burn_sboot(sboot_img, sboot_img_len);
	}
#endif
	if (res == 0) {
		res = fboot_get_image_version(CMRT_FBOOT_IMAGE_VERSION,
					      fboot_ver, &fboot_ver_len);
		if (res == 0) {
			fboot_ver_len = strlen(fboot_ver);
		}
	}
	if (res == 0) {
		res = fboot_get_image_version(CMRT_SBOOT_IMAGE_VERSION,
					      sboot_ver, &sboot_ver_len);
		if (res == 0) {
			sboot_ver_len = strlen(sboot_ver);
		}
	}
	if (res == 0) {
		res = cmrt_caliptra_get_deviceinfo(&devinfo);
	}

	if (res == 0) {
		res = cmrt_caliptra_oam_open(oam);
		if (res == 0) {
			res = cmrt_caliptra_oam_init(oam, 0);
		}
		if (res == 0) {
			cmrt_caliptra_uds_t seed;
			res = cmrt_get_random(&seed, sizeof(seed));
			if (res == 0) {
				res = cmrt_caliptra_oam_write_uds_seed(oam, &seed);
				LOG_INF("writing UDS seed result: %d", res);
			}
			cmrt_caliptra_zeroize(&seed, sizeof(seed));
		}
	}
	if (res == 0) {
		LOG_INF("sic loop");
		res = process_sic_message();
	}
	cmrt_caliptra_oam_close(oam);
	if (res == 0) {
		res = cmrt_set_lifecycle(DLC_PROVISIONED);
		LOG_INF("All done for caliptra setup perso");
		cmrt_set_perso_status(PERSO_STATUS_PART2_DONE);
	}
	return res;
}

int main(void)
{
	cmrt_set_boot_status(CONTAINER_RUNNING_ID, CONTAINER_RUNNING_ID);
	cmrt_set_perso_status(PERSO_STATUS_STARTED);
	LOG_INF("Caliptra setup perso %s starting up", version_info);

	/* Personalization work is divided in two parts. The first
	 * part burns DGOK. Next, CMRT has to be restarted, so that
	 * the DGOK status in SIC.DEVICE_KEYS_PERSO_STATUS register is
	 * updated and DGOK can be used in the second part.
	 */
	int res = 0;
	if (!have_oem_id()) {
		res = part1();
	} else {
		res = part2();
	}
	cmrt_set_boot_status(0, CONTAINER_RUNNING_ID);
	if (res != 0) {
		cmrt_set_perso_status(PERSO_STATUS_ERROR);
	}

	return fboot_halt(-EFAULT, res);
}
