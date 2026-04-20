/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <sys/util.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/eac.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/util.h>
#ifdef CONFIG_CMRT_PMU
#include <drivers/cmrt/pmu.h>
#endif
#include <drivers/watchdog.h>
#include <drivers/cmrt/fboot.h>
#include <cmrt/fboot/fboot_config.h>
#include <rebel_h_gpt.h>

#include "mw_protocol.h"
#include "cmrt_container.h"
#include "pcie_service.h"
#include "qspi.h"

#ifdef CONFIG_TEST_REBEL_H
#include "test_main.h"
#endif

#ifdef CONFIG_CMRT_CALIPTRA_SUPPORT
#include "caliptra.h"
#endif

#include <logging/log.h>
#include <rebel_h.h>
#include "rebel_h_integrity.h"
#include "dma_pl330.h"
#include <drivers/cmrt/dmac.h>
#include <sys/byteorder.h>
#include <hc.h>
#include <pke.h>
LOG_MODULE_DECLARE(main, CONFIG_CMRT_LOG_LEVEL);

const static char version_info[] __version = SUPERVISOR_VERSION_INFO;
cmrt_mw_service_t srv;

#define SUPERVISOR_SAMPLE_STARTED		(0x5F030000)

#define SBOOT_N_DEST_ADDR				(0x1FF0010000ULL)
#define TBOOT_N_DEST_ADDR				(0x1FF0030000ULL)
#define TBOOT_U_DEST_ADDR				(0x1FF5C20000ULL)
#define CP0_BL31_DEST_ADDR				(0x0)
#define CP0_FREERTOS_DEST_ADDR			(0x200000)
#define CP1_BL31_DEST_ADDR				(0x14100000)
#define CP1_FREERTOS_DEST_ADDR			(0x14200000)
#define TBOOT_P0_C3_DEST_ADDR			(0x40000000)
#define TBOOT_P1_C3_DEST_ADDR			(0x40040000)

#define SYSREG_CP0						(0x1E01010000ULL)
#define RVBARADDR0_LOW					(0x354)
#define RVBARADDR0_HIGH					(0x358)
#define RVBARADDR0_LOW_PRI_VAL			(0x10000)
#define RVBARADDR0_HIGH_PRI_VAL			(0x1E)

#define CLUSTER0_NONCPU_CONFIGURATION	(0x2400)
#define CLUSTER0_NONCPU_STATUS			(0x2404)
#define CLUSTER0_CPU0_CONFIGURATION		(0x2000)
#define CLUSTER0_CPU0_STATUS			(0x2004)

#define INITIATE_WAKEUP					(0xF << 16)
#define LOCAL_PWR_ON					(0xF)

#define UPDATED_IMG_SRC_ADDR				(0x3F000000)

#define VERIFICATION_FAIL				(0xdead)

enum image_num_in_gpt {
	SBOOT_N = 1,
	TBOOT_S,
	TBOOT_N,
	TBOOT_P0,
	TBOOT_P1,
	TBOOT_U,
	CP0_BL31,
	CP0_FREERTOS,
	CP1_BL31,
	CP1_FREERTOS,
	TOTAL_IMAGE_NUM_IN_GPT = CP1_FREERTOS
};

enum mw_boot_sequence {
	NOT_STARTED,
	START_MAIN,
	LOAD_SBOOT_N,
	ASSIGN_RVBAR_OF_CP0,
	RESET_RELEASE_NONCPU,
	RESET_RELEASE_CPU0,
	TEST_READY_EXTERNAL_IP,
	RUNTIME_SERVICE,
};

static char *bin_names[] = {
	"SBOOT_N",
	"TBOOT_S",
	"TBOOT_N",
	"TBOOT_P0",
	"TBOOT_P1",
	"TBOOT_U",
	"CP0_BL31",
	"CP0_FREERTOS",
	"CP1_BL31",
	"CP1_FREERTOS",
	"TBOOT_P1_FOOTER",
	"TBOOT_P0_C3",
	"TBOOT_P1_C3"
};

struct dma_block_config img_info[] = {
	/* Sboot_n default info */
	{
		.dest_address = SBOOT_N_DEST_ADDR,
	},
	/* Tboot_s default info */
	{
	},
	/* tboot_n default info */
	{
		.dest_address = TBOOT_N_DEST_ADDR,
	},
	/* Tboot_p0 default info */
	{
	},
	/* Tboot_p1 default info */
	{
	},
	/* Tboot_u default info */
	{
		.dest_address = TBOOT_U_DEST_ADDR,
	},
	/* CP0_BL31 default info */
	{
		.dest_address = CP0_BL31_DEST_ADDR,
	},
	/* CP0_FREERTOS default info */
	{
		.dest_address = CP0_FREERTOS_DEST_ADDR,
	},
	/* CP1_BL31 default info */
	{
		.dest_address = CP1_BL31_DEST_ADDR,
	},
	/* CP1_FREERTOS default info */
	{
		.dest_address = CP1_FREERTOS_DEST_ADDR,
	},
	/* Tboot_p1_footer default info */
	{
	},
	/* Tboot_p0 for chiplet #3 default info */
	{
		.dest_address = TBOOT_P0_C3_DEST_ADDR,
	},
	/* Tboot_p1 for chiplet #3 default info */
	{
		.dest_address = TBOOT_P1_C3_DEST_ADDR,
	},
	/* Tboot_u_footer default info */
	{
	}
};

int copy_image(uint32_t img_type, uint32_t length, struct dma_block_config img_info[])
{
	const struct device *d = device_get_binding("PL330");
	struct dma_driver_api *api = (struct dma_driver_api *)d->api;
	struct dma_config dma_cfg = {0};

	dma_cfg.channel_direction = MEMORY_TO_MEMORY;
	dma_cfg.source_data_size = 128U;
	dma_cfg.dest_data_size = 128U;
	dma_cfg.source_burst_length = 128U;
	dma_cfg.dest_burst_length = 128U;
	dma_cfg.block_count = 1U;
	dma_cfg.head_block = &img_info[img_type];

	if (img_type == IMG_TBOOT_U) {
		img_info[img_type].block_size = TBOOT_U_SRAM_MAX;

		uint64_t img_footer_addr = img_info[img_type].source_address + length - sizeof(uint32_t);

		cmrt_sac_set_base(NULL, GET_SAC_BASE(img_footer_addr));
		uint32_t img_footer_length = sys_read32(GET_SAC_R_CPU_DATA(img_footer_addr));

		img_info[IMG_TBOOT_U_FOOTER].block_size = img_footer_length;
		img_info[IMG_TBOOT_U_FOOTER].source_address = img_info[img_type].source_address + TBOOT_U_SRAM_MAX;
	}

	uint32_t res = api->config(d, 0, &dma_cfg);

	if (res == 0) {
		res = api->start(d, 0);
		if (res) {
			LOG_ERR("dma transfer fail, res : %d\n", res);
			return res;
		}
	} else {
		LOG_ERR("dma config fail, res : %d\n", res);
	}

	return res;
}

#define FROM_GPT1_TO_GPT2	(1)
#define FROM_GPT2_TO_GPT1	(2)
#define KB_4				(4096)
#define FLASH_OFFSET_MASK	(0x7FFFFFFF)
static int start_gpt_recovery(uint32_t direction)
{
	uint32_t temp_data[KB_4] = { 0, };
	int res;
	uint64_t source_address;
	uint64_t dest_address;
	uint32_t dest_address_offset = 0;
#ifdef CONFIG_WDT_CMRT
	/* Use the low level watchdog. */
	const struct device *wdt = device_get_binding(DT_LABEL(DT_ALIAS(watchdog0)));
#endif

	LOG_INF("Start GPT recovery");
	for (uint32_t copied_size = 0; copied_size < GPT_SIZE; copied_size += KB_4) {
		if (direction == FROM_GPT1_TO_GPT2) {
			source_address = GPT1_START_ADDRESS + copied_size;
			dest_address = GPT2_START_ADDRESS + copied_size;
			dest_address_offset = dest_address & FLASH_OFFSET_MASK;
		} else {
			source_address = GPT2_START_ADDRESS + copied_size;
			dest_address = GPT1_START_ADDRESS + copied_size;
			dest_address_offset = dest_address & FLASH_OFFSET_MASK;
		}

		cmrt_sac_set_base(NULL, GET_SAC_BASE(source_address));
		cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);

		if (!cmrt_is_valid(dmac)) {
			return -EBUSY;
		}

		res = cmrt_dmac_data(dmac, GET_SAC_OFFSET(source_address), (uint32_t)temp_data, KB_4, 0);
		cmrt_dmac_close(dmac);

		if (res) {
			LOG_ERR("Recovery image fail");
			return res;
		}

#ifdef CONFIG_WDT_CMRT
		/* Feed the watchdog before wait. */
		(void)wdt_feed(wdt, 0);
#endif

		res = write_flash_wrapper(dest_address_offset, temp_data, KB_4);
		if (res) {
			LOG_ERR("Flash recovery update fail");
			return res;
		}
	}
	LOG_INF("GPT recovery done");

	return 0;
}

int handle_bootdone_check_request(void)
{
	uint32_t recovery_flag = get_recovery_flag();

	if (recovery_flag == RECOVERY_FLAG_BOOT_FAIL) {
		start_gpt_recovery(FROM_GPT2_TO_GPT1);
		set_recovery_reason(RECOVERY_REASON_BOOT_FAIL, NULL);
		set_active_partition(ACTIVE_PART_ONE, NULL);
		set_recovery_flag(RECOVERY_FLAG_NORMAL, write_flash_wrapper);
		LOG_INF("Recovered image from GPT2 to GPT1");
		LOG_INF("Recovery reason : Boot fail");
	} else if (recovery_flag == RECOVERY_FLAG_FW_UPDATE) {
		start_gpt_recovery(FROM_GPT1_TO_GPT2);
		set_recovery_reason(RECOVERY_REASON_FW_UPDATE, NULL);
		set_active_partition(ACTIVE_PART_ONE, NULL);
		set_recovery_flag(RECOVERY_FLAG_NORMAL, write_flash_wrapper);
		LOG_INF("Recovered image from GPT1 to GPT2");
		LOG_INF("Recovery reason : FW update");
	} else if (recovery_flag == RECOVERY_FLAG_NORMAL) {
		LOG_INF("Recovery flag : Normal");
	} else {
		return -ENOTSUP;
	}
	LOG_INF("Active Partition : 0x%x", get_active_partition());

	return CMRT_MW_BOOTDONE_CHECK;
}

static int verify_image_in_hbm(void)
{
	cmrt_img_header_t hdr;
	uint64_t addr_to_verify;
	uint64_t footer_addr;
	uint32_t footer_length;
	cmrt_img_footer_t img_footer;
	cmrt_dmac_t dmac;
	cmrt_hc_t hc;
	cmrt_pke_t pke;
	int res;
#ifdef CONFIG_WDT_CMRT
	/* Use the low level watchdog. */
	const struct device *wdt = device_get_binding(DT_LABEL(DT_ALIAS(watchdog0)));
#endif
	uint8_t __aligned(4) footer_tmp_storage[FOOTER_MAX_LEN];

	for (int img_type = 0; img_type < TOTAL_IMAGE_NUM_IN_GPT; img_type++) {
#ifdef CONFIG_WDT_CMRT
		/* Feed the watchdog before wait. */
		(void)wdt_feed(wdt, 0);
#endif
		addr_to_verify = get_image_address(img_type, UPDATED_IMG_SRC_ADDR);
		cmrt_sac_set_base(NULL, GET_SAC_BASE(addr_to_verify));
		hdr.length = sys_read32(GET_SAC_R_CPU_DATA(addr_to_verify));
		hdr.mirror = sys_read32(GET_SAC_R_CPU_DATA(addr_to_verify + sizeof(hdr.length)));

		if (!cmrt_is_valid_hdr(&hdr, MAX_SIZE))
			return ERR_IMAGE_LOAD(img_type);

		if (img_type == IMG_TBOOT_S) {
		    addr_to_verify += sizeof(cmrt_img_header_t);
		} else {
		    addr_to_verify += (sizeof(cmrt_img_header_t) + NORMAL_IMG_PADDING_SIZE);
		}

		footer_addr = addr_to_verify + hdr.length - sizeof(uint32_t);
		cmrt_sac_set_base(NULL, GET_SAC_BASE(footer_addr));
		footer_length = sys_read32(GET_SAC_R_CPU_DATA(footer_addr));
		footer_addr -= (footer_length - sizeof(uint32_t));

		dmac = cmrt_dmac_open(CMRT_O_SYNC);

		if (!cmrt_is_valid(dmac)) {
			return -ENODEV;
		}

		cmrt_sac_set_base(NULL, GET_SAC_BASE(footer_addr));

		res = cmrt_dmac_data(dmac, (GET_SAC_OFFSET(footer_addr)), (uint32_t)footer_tmp_storage,
							 footer_length, 0);
		cmrt_dmac_close(dmac);
		if (res != 0) {
			LOG_ERR("Copy image from HBM fail");
			return res;
		}

		res = img_footer_parse(footer_tmp_storage, footer_length, &img_footer);
		if (res < 0) {
			return res;
		}

		hc = cmrt_hc_open(NULL, 0);

		res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_384, NULL, 0);
		if (res != 0) {
			cmrt_hc_close(hc);
			return res;
		}

		cmrt_sac_set_base(NULL, GET_SAC_BASE(addr_to_verify));

		uint32_t copied_len = 0;
		const uint32_t max_length = DMAC_MAX_SIZE;
		uint32_t length_to_hash = hdr.length - img_footer.signature_length -
								  sizeof(img_footer.footer_length);
		uint32_t length_to_send = 0;

		while (length_to_hash > 0) {
			if (length_to_hash >= max_length) {
				length_to_send = max_length;
			} else {
				length_to_send = length_to_hash;
			}
			res = cmrt_hc_update(hc, (void *)(GET_SAC_OFFSET(addr_to_verify) + copied_len),
								 length_to_send);
			length_to_hash -= length_to_send;
			copied_len += length_to_send;
		}
		res = cmrt_hc_update(hc, (uint8_t *)GET_SAC_OFFSET(addr_to_verify) + hdr.length -
							 sizeof(img_footer.footer_length), sizeof(img_footer.footer_length));

		size_t size = SHA512_BYTES;
		uint32_t digest[SHA3_384_WORDS];

		res = cmrt_hc_final(hc, NULL, 0, digest, &size);
		cmrt_hc_close(hc);
		if (res) {
			return res;
		}

		cmrt_ecc_curve_t curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P384);

		if (!curve) {
			return -ENODEV;
		}

		uint32_t digestlen = SHA384_BYTES;

		pke = cmrt_pke_open(CMRT_O_SYNC);

		if (!cmrt_is_valid(pke)) {
			return -ENODEV;
		}

		uint32_t curvelen = cmrt_pke_get_curve_length(curve);

		res = cmrt_pke_ecdsa_verify_hash(pke, curve, img_footer.public_key,
										 img_footer.public_key + curvelen,
										 digest, digestlen, img_footer.signature,
										 img_footer.signature + curvelen, NULL);
		cmrt_pke_close(pke);
		if (res) {
			LOG_INF("%s image verification is failed", bin_names[img_type]);
			return VERIFICATION_FAIL;
		}

		LOG_INF("%s image verification is passed", bin_names[img_type]);
	}

	return 0;
}

static int copy_image_in_hbm(void)
{
	uint32_t temp_data[KB_4] = { 0, };
	uint64_t source_address;
	uint64_t dest_address;
	int res;
#ifdef CONFIG_WDT_CMRT
	/* Use the low level watchdog. */
	const struct device *wdt = device_get_binding(DT_LABEL(DT_ALIAS(watchdog0)));
#endif

	for (uint32_t copied_size = 0; copied_size < GPT_SIZE; copied_size += KB_4) {
		source_address = UPDATED_IMG_SRC_ADDR + copied_size;
		dest_address = GPT1_START_ADDRESS + copied_size;

		cmrt_sac_set_base(NULL, GET_SAC_BASE(source_address));
		cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);

		if (!cmrt_is_valid(dmac)) {
			return -ENODEV;
		}

		res = cmrt_dmac_data(dmac, GET_SAC_OFFSET(source_address), (uint32_t)temp_data, KB_4, 0);
		cmrt_dmac_close(dmac);
		if (res) {
			LOG_ERR("Image copy to sram buffer failed");
			return res;
		}

#ifdef CONFIG_WDT_CMRT
		/* Feed the watchdog before wait. */
		(void)wdt_feed(wdt, 0);
#endif

		res = write_flash_wrapper((uint32_t)dest_address, temp_data, KB_4);
		if (res) {
			LOG_ERR("Image copy to flash GPT1 failed");
			return res;
		}
	}
	LOG_INF("Image copy to flash GPT1 completed successfully");

	return 0;
}

int handle_imgupdate_request(void)
{
	int res;

	res = verify_image_in_hbm();
	if (res)
		return res;

	LOG_INF("Set active partition to #2 as a fallback in case the update fails");
	set_active_partition(ACTIVE_PART_TWO, NULL);
	set_recovery_reason(RECOVERY_REASON_BOOT_FAIL, write_flash_wrapper);

	res = copy_image_in_hbm();
	if (res)
		return res;

	LOG_INF("Restore active partition to #1");
	set_active_partition(ACTIVE_PART_ONE, NULL);
	set_recovery_flag(RECOVERY_FLAG_FW_UPDATE, write_flash_wrapper);

	return CMRT_MW_LOAD_IMG_FROM_HBM;
}

static cmrt_container_t *cmd_container(const cmrt_mw_request_t *aux_command)
{
	int flowid = (int)aux_command->flowid;
	cmrt_container_t *ptr_container =
		cmrt_container_search_per_flowid(flowid);

	if (!ptr_container) {
		/* Container not found */
		LOG_INF("Container flowid %d was not found", flowid);
	}
	return ptr_container;
}

static int cmrt_mw_check_container(const cmrt_mw_request_t *aux_command)
{
	int aux = -CMRT_MW_CONTAINER_NOT_FOUND;
	cmrt_container_t *ptr_container = cmd_container(aux_command);

	if (ptr_container) {
		/* Return container state */
		aux = ptr_container->state;
	}
	return aux;
}

static int cmrt_mw_load_container(const cmrt_mw_request_t *aux_command, void *img, size_t img_size)
{
	int flowid = (int)aux_command->flowid;
	cmrt_container_t *ptr_container = cmrt_container_search_per_flowid(flowid);

	if (ptr_container) {
		/* Container was found */
		LOG_INF("Container flowid %d already exists", flowid);
		/* Remove container data loaded from SIC into memory */
		(void)memset(img, 0, img_size);

		return -CMRT_MW_CONTAINER_ALREADY_EXISTS;
	}
	return cmrt_container_load(flowid,
							   (int8_t)aux_command->container_priority,
							   (uint8_t *)img + sizeof(cmrt_mw_request_t),
							   img_size);
}

static int cmrt_mw_unload_container(cmrt_mw_request_t *aux_command)
{
	int aux = -CMRT_MW_CONTAINER_NOT_FOUND;
	cmrt_container_t *ptr_container = cmd_container(aux_command);

	if (ptr_container) {
		aux = cmrt_container_unload(ptr_container);
	}
	return aux;
}

static int cmrt_mw_start_container(const cmrt_mw_request_t *aux_command)
{
	int aux = -CMRT_MW_CONTAINER_NOT_FOUND;
	cmrt_container_t *ptr_container = cmd_container(aux_command);

	if (ptr_container) {
		aux = cmrt_container_run_resume(ptr_container);
	}
	return aux;
}

static int cmrt_mw_stop_container(const cmrt_mw_request_t *aux_command)
{
	int aux = -CMRT_MW_CONTAINER_NOT_FOUND;
	cmrt_container_t *ptr_container = cmd_container(aux_command);

	if (ptr_container) {
		/* WARNING: We are forcing the following sequence:
		 * RUNNING -> SUSPEND -> ABORT
		 */
		if (ptr_container->state == CMRT_CONTAINER_RUNNING) {
			aux = cmrt_container_suspend(ptr_container);
		} else {
			aux = cmrt_container_stop(ptr_container);
		}
	}
	return aux;
}

static int cmrt_mw_send_response(cmrt_mw_service_t *ptr_service, int ret)
{
	int res = 0;

	cmrt_mw_response_t resp = {};
	size_t sz = sizeof(cmrt_mw_response_t);

	if (ret < 0) {
		resp.error = (uint32_t)-ret;
	} else {
		resp.status = (uint32_t)ret;
	}

	res = cmrt_sic_write(ptr_service->sic, &resp, sz, ptr_service->peerid);
	if (res < 0) {
		LOG_INF("Failed to setup write to HLOS for flowid %d: %d",
				(int)ptr_service->flowid, res);
	}
	return res;
}

int cmrt_mw_send_log_header_response(cmrt_mw_service_t *ptr_service)
{
	LOG_INF("MW %s()", __func__);
	/* TODO */
	return 0;
}

int cmrt_mw_send_ps_response(cmrt_mw_service_t *ptr_service, cmrt_container_status_t *ptr_data,
							 int *data_size)
{
	ARG_UNUSED(data_size);
	int res = 0;

	cmrt_mw_command_ps_containers_response_t resp = {};
	size_t sz = sizeof(cmrt_mw_command_ps_containers_response_t);

	/* MW RESPONSE */
	resp.mw_response.error = 0;
	resp.mw_response.status = 0;

	/* CMD HEADER */
	resp.cmd_header.command = CMRT_MW_COMMAND_PS;
	resp.cmd_header.version = 1;
	resp.cmd_header.size = CONFIG_CMRT_NUM_CONTAINERS;

	/* CMD RESPONSE */
	for (int i = 0; i < CONFIG_CMRT_NUM_CONTAINERS; i++) {
		resp.cmd_response[i].flowid = (uint32_t)ptr_data[i].flowid;
		resp.cmd_response[i].container_priority = ptr_data[i].thread_priority;
		resp.cmd_response[i].state = (uint32_t)ptr_data[i].state;
	}

	/* SEND RESPONSE */
	res = cmrt_sic_write(ptr_service->sic, &resp, sz, ptr_service->peerid);

	if (res < 0) {
		LOG_INF("Failed to setup write to HLOS for flowid %d: %d",
				(int)ptr_service->flowid, res);
	}
	return res;
}

/* Processes all messages received via SIC. */
int cmrt_mw_message_processing(cmrt_mw_service_t *ptr_service)
{
	int res = 0;

	cmrt_mw_request_t *aux_command = NULL;
	uint32_t offset = 0;
	uint32_t img_type;

	if (ptr_service->mem_dir == CMRT_SIC_ALIGN_RIGHT) {
		offset = ptr_service->max_buflen - ROUND_UP(ptr_service->buflen, sizeof(uint32_t));
	}

	aux_command = (cmrt_mw_request_t *)(ptr_service->buffer + offset);

	cmrt_container_update_malfunctioning();

	LOG_INF("Command: 0x%x, FlowId: %d, Length: %d",
			aux_command->cmd, aux_command->flowid, aux_command->length);

	switch (aux_command->cmd) {
	case CMRT_MW_CHECK_CONTAINER:
		LOG_INF("CMRT_MW_CHECK_CONTAINER");
		res = cmrt_mw_check_container(aux_command);
		return res;
	case CMRT_MW_LOAD_CONTAINER:
		LOG_INF("CMRT_MW_LOAD_CONTAINER");
		res = cmrt_mw_load_container(aux_command, ptr_service->buffer + offset,
									 aux_command->length);
		return res;
	case CMRT_MW_UNLOAD_CONTAINER:
		LOG_INF("CMRT_MW_UNLOAD_CONTAINER");
		res = cmrt_mw_unload_container(aux_command);
		return res;
	case CMRT_MW_START_CONTAINER:
		LOG_INF("CMRT_MW_START_CONTAINER");
		res = cmrt_mw_start_container(aux_command);
		return res;
	case CMRT_MW_STOP_CONTAINER:
		LOG_INF("CMRT_MW_STOP_CONTAINER");
		res = cmrt_mw_stop_container(aux_command);
		return res;
	case CMRT_MW_PROBE_CONTAINER:
		LOG_INF("CMRT_MW_PROBE_CONTAINER");
		res = cmrt_mw_check_container(aux_command);
		return res;
	case CMRT_MW_QUERY_CONTAINER:
		LOG_INF("CMRT_MW_QUERY_CONTAINER");
		return -CMRT_MW_COMMAND_NOT_SUPPORTED;
	case CMRT_MW_LOAD_TBOOT_U:
	case CMRT_MW_LOAD_TBOOT_N:
	case CMRT_MW_LOAD_CP0_BL31:
	case CMRT_MW_LOAD_CP0_FREERTOS:
	case CMRT_MW_LOAD_CP1_BL31:
	case CMRT_MW_LOAD_CP1_FREERTOS:
	case CMRT_MW_LOAD_TBOOT_P0_C3:
	case CMRT_MW_LOAD_TBOOT_P1_C3:
		img_type = aux_command->cmd - CUSTOM_CMRT_COMMAND_BASE;
		LOG_INF("CMRT_MW_LOAD_IMAGES 0x%x, %s\n", img_type, bin_names[img_type]);

		uint32_t result = 0;

		result = start_image(img_type, copy_image, img_info, NULL, NULL);
		if (result != 0) {
			LOG_INF("Failed to load CMRT_MW_LOAD_IMAGES 0x%x, %s\nres = %d\n", img_type,
					bin_names[img_type], result);
			handling_img_error(write_flash_wrapper);
		}
		return CMRT_MW_DO_NOT_RESPOND;
	case CMRT_MW_BOOTDONE_CHECK:
		LOG_INF("CMRT_MW_BOOTDONE_CHECK");
		return handle_bootdone_check_request();
	case CMRT_MW_LOAD_IMG_FROM_HBM:
		LOG_INF("CMRT_MW_LOAD_IMG_FROM_HBM");
		return handle_imgupdate_request();
	case CMRT_MW_READ_LOGS:
		LOG_INF("CMRT_MW_READ_LOGS");
		(void)cmrt_mw_send_log_header_response(ptr_service);
		return CMRT_MW_DO_NOT_RESPOND;
	case CMRT_MW_SOFT_RESET:
		LOG_INF("CMRT_MW_SOFT_RESET");
		(void)cmrt_mw_send_response(ptr_service, res);
		fboot_reset(1); /* set non-zero info for fboot_reset_info */
		break; /* Not reachable */
	case CMRT_MW_PS_CONTAINERS:
		LOG_INF("CMRT_MW_PS_CONTAINERS");
		int aux_size = cmrt_container_number_of_containers();
		cmrt_container_status_t ptr_data[CONFIG_CMRT_NUM_CONTAINERS];

		if (!cmrt_container_statuses(ptr_data, &aux_size)) {
			LOG_INF("Failed to copy data for command PS.");
			/* Return value for failed PS command is missing. */
			return res;
		}
		(void)cmrt_mw_send_ps_response(ptr_service, ptr_data, &aux_size);
		return CMRT_MW_DO_NOT_RESPOND;
	case CMRT_MW_LOAD_CONTAINER | CMRT_MW_START_CONTAINER:
		LOG_INF("CMRT_RUN_CONTAINER");
		res = cmrt_mw_load_container(aux_command, (ptr_service->buffer + offset),
									 aux_command->length);
		if (res < 0) {
			LOG_INF("Failed to load container.");
		} else {
			res = cmrt_mw_start_container(aux_command);
		}
		return res;
	default:
		LOG_INF("UNKNOWN COMMAND");
		return -CMRT_MW_COMMAND_NOT_FOUND;
	}
	return -CMRT_MW_COMMAND_NOT_FOUND;
}

static void cmrt_mw_main_loop(int flowid)
{
	/* Initialize all containers to a known value before proceeding. */
	cmrt_container_initialize();

#ifdef CONFIG_CMRT_IMAGE_AUTOLOAD_SUPPORT
#ifdef CONFIG_CMRT_CALIPTRA_SUPPORT
	cmrt_caliptra_fmc_context_t caliptra_context;
	int caliptra_res = cmrt_caliptra_fmc_init(&caliptra_context);

	if (caliptra_res != 0) {
		LOG_ERR("caliptra fmc init failed %d", caliptra_res);
	}
#endif
	int autoload_size;
	size_t autoload_sizeof = sizeof(autoload_size);

	/* Sboot may have autoloaded an image to the start of unused SRAM. */
	if (fboot_data_store_read("AUTOLOAD_SIZE", sizeof("AUTOLOAD_SIZE") - 1,
							  &autoload_size, &autoload_sizeof, false) == 0) {
		cmrt_container_t *container = &cmrt_containers[0];

		LOG_INF("Trying to autoload container at 0x%p:%d",
				container->ptr_img, autoload_size);
		if (cmrt_mw_load_container(container->ptr_img, container->ptr_img,
								   (size_t)autoload_size) == 0) {
#ifdef CONFIG_CMRT_CALIPTRA_SUPPORT
			if (caliptra_res == 0) {
				caliptra_res = cmrt_caliptra_fmc_flow(&caliptra_context,
													  container->ptr_img, autoload_size);
				if (caliptra_res != 0) {
					LOG_ERR("caliptra failed %d", caliptra_res);
				}
			}
#endif
			(void)cmrt_mw_start_container(container->ptr_img);
		}
	}
#endif
	/* Sets SIC memory alignment to left */
	srv.mem_dir = 0;

	/* Sets flow id. */
	srv.flowid = (uint32_t)flowid;

	/* Opening SIC with feeding in sync and 500ms HLOS timeout. */
	srv.sic = cmrt_sic_open(CMRT_O_FEED_WDT, SET_SICTIMEOUT(srv.flowid, 500));
	if (!cmrt_is_valid(srv.sic)) {
		LOG_INF("MW %s(): Failed to open flowid %d", __func__, srv.flowid);
		return;
	}
#ifdef CONFIG_WDT_CMRT
	/* Use the low level watchdog. */
	const struct device *wdt = device_get_binding(DT_LABEL(DT_ALIAS(watchdog0)));

	if (!wdt) {
		LOG_INF("MW %s(): Cannot find watchdog!", __func__);
		return;
	}
	/* set 2.8s timeout value */
	struct wdt_timeout_cfg cfg = {
		.window = {.max = 0xb2f},
	};
	(void)wdt_install_timeout(wdt, &cfg);
	wdt_setup(wdt, 0);
	(void)wdt_feed(wdt, 0);
#endif

	LOG_INF("Waiting for MW commands in flow %d ...", srv.flowid);

	/* Main processing loop. */
	while (true) {
		/* Container selection as SIC buffer.
		 * At this stage we are going to select which container
		 * is going to act as buffer for SIC.
		 */
		cmrt_container_t *ptr_container = NULL;
		size_t container_size = 0;

		cmrt_container_get_next_empty(&ptr_container, &container_size);
		srv.buffer = (uint8_t *)ptr_container->ptr_img;

		if (container_size == 0) {
			/* Defaulting to small buffer. No images can be
			 * loaded as there are not containers available.
			 */
			srv.buflen = sizeof(cmrt_mw_service_t);
			srv.max_buflen = sizeof(cmrt_mw_service_t);
			srv.mem_dir = 0;
			cmrt_set_boot_status(0, READY_TO_RUN_CONTAINER);
		} else {
			/* There is at least one container available. */
			srv.buflen = container_size;
			srv.max_buflen = container_size;
			srv.mem_dir = (uint32_t)ptr_container->img_write_direction;
			cmrt_set_boot_status(READY_TO_RUN_CONTAINER, READY_TO_RUN_CONTAINER);
		}

		if (cmrt_container_is_there_one_running()) {
			cmrt_set_boot_status(CONTAINER_RUNNING_ID, CONTAINER_RUNNING_ID);
		} else {
			cmrt_set_boot_status(0, CONTAINER_RUNNING_ID);
			static int low_power_events;
			int res = fboot_reset_info(NULL);

			if (low_power_events < res) {
				/* Just note. Could do some actions here. */
				low_power_events = res;
				LOG_INF("Woke up from sleep");
			}
#ifdef CONFIG_CMRT_PMU
			/* Advertise low power before wait. */
			(void)cmrt_pmu_low_power(true);
#endif
		}

		/* Setting SIC in read mode. */
		int res = cmrt_sic_read(srv.sic, srv.buffer, &srv.buflen, &srv.peerid, srv.mem_dir);

		if (res < 0) {
			LOG_INF("MW %s(): Failed to setup read for flowid %d: %d",
					__func__, (int)srv.flowid, res);
			break;
		}
		BOOT_LOG(ROT, ROT_MW, BOOT_DONE(ROT));

		while (true) {
#ifdef CONFIG_WDT_CMRT
			/* Feed the watchdog before wait. */
			(void)wdt_feed(wdt, 0);
#endif
			/* Blocking call to receive data from SIC. */
			res = cmrt_wait(1, (cmrt_handle_t)&srv.sic, 500);

			if (res < 0) {
				LOG_INF("MW() %s: Failed to wait from HLOS: %d", __func__, res);
				break;
			}
#ifdef CONFIG_WDT_CMRT
			/* Feed the watchdog before sync. */
			(void)wdt_feed(wdt, 0);
#endif
			if (res & (1 << 0)) {
				/* SIC data received, complete it. */
				res = cmrt_sic_sync(srv.sic);

				if (res < 0) {
					LOG_INF("MW %s(): Failed to read from HLOS: %d\n", __func__, res);
					break;
				}
				/* Read satisfactory. Proceed to process the message. */
#ifdef CONFIG_WDT_CMRT
				/* Feed the watchdog before MW operation. */
				(void)wdt_feed(wdt, 0);
#endif
				res = cmrt_mw_message_processing(&srv);

				if (res != CMRT_MW_DO_NOT_RESPOND) {
					(void)cmrt_mw_send_response(&srv, res);
				}
				LOG_INF("...cmrt_wait returned for flow %d", srv.flowid);
				break;
			}
		}
	}
	cmrt_sic_close(srv.sic);
}

int main(void)
{
	LOG_INF("start main\n");
	BOOT_LOG(ROT, ROT_MW, START_MAIN);
	cmrt_set_boot_status(SUPERVISOR_RUNNING_ID, SUPERVISOR_RUNNING_ID);

#ifdef SUPERVISOR_SAMPLE_STARTED
	cmrt_write_reg(CMRT_SIC_BASE, R_SCRATCH_0, SUPERVISOR_SAMPLE_STARTED);
#endif
	if (get_chiplet_id() == CHIPLET_PRIMARY) {
		gpt_init();
		BOOT_LOG(ROT, ROT_MW, LOAD_SBOOT_N);
		LOG_INF("load sboot_n\n");

		uint32_t result = 0;

		result = start_image(IMG_SBOOT_N, copy_image, img_info, NULL, NULL);
		if (result != 0) {
			LOG_INF("Failed to load sboot_n\nres = %d\n", result);
			handling_img_error(write_flash_wrapper);
		}

		BOOT_LOG(ROT, ROT_MW, ASSIGN_RVBAR_OF_CP0);
		cmrt_sac_set_base(NULL, GET_SAC_BASE(SYSREG_CP0 + RVBARADDR0_LOW));
		cmrt_sac_write32(RVBARADDR0_LOW_PRI_VAL, GET_SAC_OFFSET(SYSREG_CP0 + RVBARADDR0_LOW));
		cmrt_sac_write32(RVBARADDR0_HIGH_PRI_VAL,
						 GET_SAC_OFFSET(SYSREG_CP0 + RVBARADDR0_HIGH));

		BOOT_LOG(ROT, ROT_MW, RESET_RELEASE_NONCPU);
		cmrt_sac_set_base(NULL, GET_SAC_BASE(CPMU_PRIVATE + CLUSTER0_NONCPU_CONFIGURATION));
		uint32_t sfr_reset_value = cmrt_sac_read32(GET_SAC_OFFSET(CPMU_PRIVATE + CLUSTER0_NONCPU_CONFIGURATION));

		cmrt_sac_write32(INITIATE_WAKEUP | sfr_reset_value,
						 GET_SAC_OFFSET(CPMU_PRIVATE + CLUSTER0_NONCPU_CONFIGURATION));

		while ((cmrt_sac_read32(GET_SAC_OFFSET(CPMU_PRIVATE + CLUSTER0_NONCPU_STATUS)) &
			   LOCAL_PWR_ON) != LOCAL_PWR_ON)
			;

		BOOT_LOG(ROT, ROT_MW, RESET_RELEASE_CPU0);
		cmrt_sac_set_base(NULL, GET_SAC_BASE(CPMU_PRIVATE + CLUSTER0_CPU0_CONFIGURATION));
		sfr_reset_value = cmrt_sac_read32(GET_SAC_OFFSET(CPMU_PRIVATE + CLUSTER0_CPU0_CONFIGURATION));
		cmrt_sac_write32(INITIATE_WAKEUP | sfr_reset_value,
						 GET_SAC_OFFSET(CPMU_PRIVATE + CLUSTER0_CPU0_CONFIGURATION));
		while ((cmrt_sac_read32(GET_SAC_OFFSET(CPMU_PRIVATE + CLUSTER0_CPU0_STATUS)) & LOCAL_PWR_ON)
			   != LOCAL_PWR_ON)
			;
	}
	/* Running in supervisor mode here. */
	LOG_INF("Supervisor (MW) %s running...", version_info);

	uint32_t info;

	(void)fboot_reset_info(&info);
	LOG_INF("...after %s reset", info != 0 ? "soft" : "hard");

	BOOT_LOG(ROT, ROT_MW, TEST_READY_EXTERNAL_IP);
#ifdef CONFIG_TEST_REBEL_H
	register_test_cb();
#endif

	if (get_chiplet_id() == CHIPLET_PRIMARY) {
		pcie_ide_init();
	}

	BOOT_LOG(ROT, ROT_MW, RUNTIME_SERVICE);
	cmrt_mw_main_loop(0);

	cmrt_set_boot_status(0, SUPERVISOR_RUNNING_ID);
	return 0;
}
