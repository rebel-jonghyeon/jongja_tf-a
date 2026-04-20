/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <stdbool.h>
#include <container.h>
#include <logging/log.h>
#include <errno.h>
#include <drivers/cmrt/fboot.h>
#include <drivers/cmrt/sac.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/dmac.h>
#include <drivers/cmrt/sic.h>

#include <cmrt/caliptra/assets.h>
#include <cmrt/caliptra/flow.h>
#include <cmrt/caliptra/handover.h>
#include <cmrt/caliptra/platdep.h>
#include <cmrt/caliptra/x509.h>

#define FLOWID 124

#define CMD_EXPORT_OWNER_CSRS 4
#define CMD_EXPORT_IDEVID_CERT_CHAIN 5
#define CMD_UPDATE_FIELD_ENTROPY 6
#define CMD_EXIT 100

typedef struct {
	uint32_t cmd;
	uint32_t max_len;
	uint64_t sac_address;
} msg_export_object_t;

typedef struct {
	uint32_t cmd;
	cmrt_caliptra_field_entropy_t value;
} msg_update_field_entropy_t;

typedef struct {
	uint32_t unused;
	uint32_t size; /* Size of SAC area that can be used. */
	uint64_t sac_address; /* Physical address of SAC area. */
	uint32_t pos; /* Offset from sac_address. */
} sac_writer_state_t;

int cmrt_caliptra_plat_datastore_read(const char *name, size_t namelen,
				      void *data, size_t *datalen)
{
	return fboot_data_store_read(name, namelen, data, datalen, true);
}

int cmrt_caliptra_plat_datastore_write(const char *name, size_t namelen,
				       const void *data, size_t datalen)
{
	return fboot_data_store_write(name, namelen, data, datalen, false);
}

int cmrt_caliptra_plat_datastore_grant(const char *name, size_t namelen,
				       int root, uint32_t attr)
{
	return fboot_data_store_grant(name, namelen, attr, root, false);
}

static inline bool buffer_in_sac_window(uint32_t address, size_t size)
{
	const uint32_t sacmem_begin = SAC_MEMORY_BASE;
	const uint32_t sacmem_end = UINT32_MAX;
	const uint32_t buf_end = address + size;
	return ((address >= sacmem_begin) &&
		(address <= sacmem_end) &&
		(buf_end <= sacmem_end) &&
		(buf_end >= address));
}

static int sac_write_object(sac_writer_state_t *s, uint8_t *object, size_t len)
{
	int res = 0;
	size_t wlen = ROUND_UP(len, 4u);
	if (s->pos + wlen > s->size ||
	    s->pos + wlen <= s->pos) {
		return -ENOBUFS;
	}
	uint64_t sac_addr = s->sac_address + s->pos;
	uint32_t sac_hi = (uint32_t)(sac_addr >> 32);
	uint32_t sac_lo = (uint32_t)sac_addr;
	if (sac_hi != 0u) {
		LOG_WRN("the upper 32 bits of SAC address must be zero: %lx", sac_hi);
		res = -EINVAL;
	}
	uint32_t cmrt_sac_addr = sac_lo + SAC_MEMORY_BASE;
	if (!buffer_in_sac_window(cmrt_sac_addr, wlen)) {
		res = -ENXIO;
	}

	if (res == 0) {
		/* Write object to SAC. */
		res = -ENODEV;
		cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);
		if (cmrt_is_valid(dmac)) {
			res = cmrt_dmac_data(dmac, (uintptr_t)object, cmrt_sac_addr + 4, wlen, 0);
			if (res == 0) {
				/* Write size header. */
				cmrt_sac_write32(len, cmrt_sac_addr);
				LOG_INF("saved object at sac_address 0x%0llx bytes 0x%x", sac_addr+4, len);
			}
			cmrt_dmac_close(dmac);
		}
	}
	if (res == 0) {
		s->pos += wlen + 4;
		LOG_INF("next %0lx", s->pos);
	}

	return res;
}

static int export_rtas(sac_writer_state_t *s, cmrt_caliptra_rta_id_t *ids, int n)
{
	alignas(4) uint8_t der[CMRT_CALIPTRA_MAX_DER_LEN];
	int res = 0;
	for (int i = 0; res == 0 && i < n; i++) {
		size_t der_len = sizeof(der);
		res = cmrt_caliptra_rta_retrieve(ids[i], der, &der_len, false);
		LOG_INF("get rta %u", ids[i]);
		if (res == 0) {
			res = sac_write_object(s, der, der_len);
		}
	}
	return res;
}

static int export_owner_csrs(sac_writer_state_t *s)
{
	cmrt_caliptra_rta_id_t ids[] = {
		CMRT_CALIPTRA_RTA_OWNER_LDevID_CSR,
		CMRT_CALIPTRA_RTA_OWNER_ALIASFMC_CSR
	};
	return export_rtas(s, ids, ARRAY_SIZE(ids));
}

static int export_idevid_cert_chain(sac_writer_state_t *s)
{
	cmrt_caliptra_rta_id_t ids[] = {
		CMRT_CALIPTRA_RTA_ALIASRT_CERT,
		CMRT_CALIPTRA_RTA_ALIASFMC_CERT,
		CMRT_CALIPTRA_RTA_LDevID_CERT
	};
	int res = export_rtas(s, ids, ARRAY_SIZE(ids));

	alignas(4) uint8_t der[CMRT_CALIPTRA_IDEVID_CHAIN_MAX_LEN];
	size_t der_len = sizeof(der);
	if (res == 0) {
		cmrt_caliptra_oam_t oam;
		res = cmrt_caliptra_oam_open(oam);
		if (res == 0) {
			res = cmrt_caliptra_oam_init(oam, OTP_ESW_OFFSET + SBOOT_IMG_LEN);
		}
		if (res == 0) {
			res = cmrt_caliptra_oam_read_idevid_cert_chain(oam, der, &der_len);
			cmrt_caliptra_oam_close(oam);
		}
	}
	if (res == 0) {
		res = sac_write_object(s, der, der_len);
	}
	return res;
}

static int update_field_entropy(msg_update_field_entropy_t *msg)
{
	cmrt_caliptra_oam_t oam;
	int res = cmrt_caliptra_oam_open(oam);
	if (res == 0) {
		res = cmrt_caliptra_oam_init(oam, OTP_ESW_OFFSET + SBOOT_IMG_LEN);
	}
	if (res == 0) {
		res = cmrt_caliptra_oam_write_field_entropy(oam, &msg->value);
		cmrt_caliptra_oam_close(oam);
	}
	return res;
}

static bool stop = false; /* Exit sic loop. */
static int process_command(void *msg, size_t len)
{
	int res = -EINVAL;
	uint32_t cmd = *(uint32_t *)msg;
	switch (cmd) {
	case CMD_EXPORT_OWNER_CSRS:
		LOG_INF("Running command CMD_EXPORT_OWNER_CSRS");
		if (len == sizeof(msg_export_object_t)) {
			sac_writer_state_t *s = msg;
			s->pos = 0;
			res = export_owner_csrs(s);
		}
		break;
	case CMD_EXPORT_IDEVID_CERT_CHAIN:
		LOG_INF("Running command CMD_EXPORT_IDEVID_CERT_CHAIN");
		if (len == sizeof(msg_export_object_t)) {
			sac_writer_state_t *s = msg;
			s->pos = 0;
			res = export_idevid_cert_chain(s);
		}
		break;
	case CMD_UPDATE_FIELD_ENTROPY:
		LOG_INF("Running command CMD_UPDATE_FIELD_ENTROPY");
		if (len == sizeof(msg_update_field_entropy_t)) {
			msg_update_field_entropy_t *m = msg;
			res = update_field_entropy(m);
		}
		break;
	case CMD_EXIT:
		LOG_INF("Container asked to stop\n");
		stop = true;
		res = 0;
		break;
	default:
		LOG_INF("Unknown command %lu\n", cmd);
		break;
	}
	LOG_INF("Command returned: %d", res);
	return res;
}

static int process_sic_message(void)
{
	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, FLOWID);
	if (!cmrt_is_valid(sic)) {
		LOG_INF("Cannot open SIC");
		return -ENODEV;
	}

	/* Process SIC messages in a loop until commanded to stop or a sic error occurs. */
	int res = 0;
	while (!stop && res == 0) {
		union {
			msg_export_object_t eo;
			msg_update_field_entropy_t ufe;
			sac_writer_state_t i;
		} msg;
		uint32_t peerid;
		size_t buflen = sizeof(msg);

		LOG_INF("Waiting for SIC command...");
		res = cmrt_sic_read(sic, &msg, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read SIC message from HLOS: %d!\n", res);
			continue;
		}

		/* Process command. */
		LOG_INF("New command... peer %lu", peerid);

		if (buflen < sizeof(uint32_t)) {
			LOG_INF("Invalid command");
			continue;
		}
		int cmd_result = process_command(&msg, buflen);

		/* Send return code over SIC to HLOS. */
		res = cmrt_sic_write(sic, &cmd_result, sizeof(cmd_result), peerid);
		if (res) {
			LOG_INF("Failed to setup SIC write to HLOS: %d!", res);
			continue;
		}
	}
	return res;
}

void container(void *p1, void *p2, void *p3)
{
	(void)p1;
	(void)p2;
	(void)p3;
	LOG_INF("caliptra_rt starting");
	int res = process_sic_message();
	LOG_INF("Container main_loop exited with %d", res);
}
