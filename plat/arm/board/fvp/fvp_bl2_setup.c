/*
 * Copyright (c) 2013-2025, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>

#include <common/debug.h>
#include <common/desc_image_load.h>
#include <drivers/arm/sp804_delay_timer.h>
#include <fvp_pas_def.h>
#include <lib/fconf/fconf.h>
#include <lib/fconf/fconf_dyn_cfg_getter.h>
<<<<<<< HEAD
#include <lib/transfer_list.h>
=======
#if TRANSFER_LIST
#include <transfer_list.h>
#endif
>>>>>>> upstream_import/upstream_v2_14_1

#include <plat/arm/common/plat_arm.h>
#include <plat/common/platform.h>
#include <platform_def.h>

#include "fvp_private.h"

<<<<<<< HEAD
static struct transfer_list_header *ns_tl __unused;
=======
#if ENABLE_RME
/*
 * The GPT library might modify the gpt regions structure to optimize
 * the layout, so the array cannot be constant.
 */
static pas_region_t pas_regions[] = {
	ARM_PAS_KERNEL,
	ARM_PAS_SECURE,
	ARM_PAS_REALM,
	ARM_PAS_EL3_DRAM,
#ifdef ARM_PAS_GPTS
	ARM_PAS_GPTS,
#endif
	ARM_PAS_KERNEL_1,
	ARM_PAS_PCI_MEM_1,
	ARM_PAS_PCI_MEM_2
};

static const arm_gpt_info_t arm_gpt_info = {
	.pas_region_base  = pas_regions,
	.pas_region_count = (unsigned int)ARRAY_SIZE(pas_regions),
	.l0_base = ARM_L0_GPT_BASE,
	.l1_base = ARM_L1_GPT_BASE,
	.l0_size = ARM_L0_GPT_SIZE,
	.l1_size = ARM_L1_GPT_SIZE,
	.pps = GPCCR_PPS_1TB,
	.pgs = GPCCR_PGS_4K
};
#endif /* ENABLE_RME */
>>>>>>> upstream_import/upstream_v2_14_1

void bl2_early_platform_setup2(u_register_t arg0, u_register_t arg1, u_register_t arg2, u_register_t arg3)
{
	arm_bl2_early_platform_setup(arg0, arg1, arg2, arg3);

	/* Initialize the platform config for future decision making */
	fvp_config_setup();
}

void bl2_platform_setup(void)
{
	arm_bl2_platform_setup();

#if TRANSFER_LIST
	ns_tl = transfer_list_init((void *)FW_NS_HANDOFF_BASE, FW_HANDOFF_SIZE);
	assert(ns_tl != NULL);
#endif
	/* Initialize System level generic or SP804 timer */
	fvp_timer_init();
}

#if ENABLE_RME
const arm_gpt_info_t *plat_arm_get_gpt_info(void)
{
	return &arm_gpt_info;
}
#endif /* ENABLE_RME */

/*******************************************************************************
 * This function returns the list of executable images
 ******************************************************************************/
struct bl_params *plat_get_next_bl_params(void)
{
	struct bl_params *arm_bl_params;
<<<<<<< HEAD
	const struct dyn_cfg_dtb_info_t *hw_config_info __unused;
	struct transfer_list_entry *te __unused;
=======
>>>>>>> upstream_import/upstream_v2_14_1
	bl_mem_params_node_t *param_node __unused;
	const struct dyn_cfg_dtb_info_t *fw_config_info __unused;
	const struct dyn_cfg_dtb_info_t *hw_config_info __unused;
	entry_point_info_t *ep __unused;
	uint32_t next_exe_img_id __unused;
	uintptr_t fw_config_base __unused;

	arm_bl_params = arm_get_next_bl_params();

<<<<<<< HEAD
#if !RESET_TO_BL2 && !EL3_PAYLOAD_BASE
	const struct dyn_cfg_dtb_info_t *fw_config_info;
	uintptr_t fw_config_base = 0UL;

=======
>>>>>>> upstream_import/upstream_v2_14_1
#if __aarch64__
	/* Get BL31 image node */
	param_node = get_bl_mem_params_node(BL31_IMAGE_ID);
#else /* aarch32 */
	/* Get SP_MIN image node */
	param_node = get_bl_mem_params_node(BL32_IMAGE_ID);
#endif /* __aarch64__ */
	assert(param_node != NULL);

<<<<<<< HEAD
=======
#if TRANSFER_LIST
	arm_bl_params->head = &param_node->params_node_mem;
	arm_bl_params->head->ep_info = &param_node->ep_info;
	arm_bl_params->head->image_id = param_node->image_id;

	arm_bl2_setup_next_ep_info(param_node);
#elif !RESET_TO_BL2 && !EL3_PAYLOAD_BASE
	fw_config_base = 0UL;

>>>>>>> upstream_import/upstream_v2_14_1
	/* Update the next image's ep info with the FW config address */
	fw_config_info = FCONF_GET_PROPERTY(dyn_cfg, dtb, FW_CONFIG_ID);
	assert(fw_config_info != NULL);

	fw_config_base = fw_config_info->config_addr;
	assert(fw_config_base != 0UL);

	param_node->ep_info.args.arg1 = (uint32_t)fw_config_base;
<<<<<<< HEAD

	/* Update BL33's ep info with the NS HW config address */
	param_node = get_bl_mem_params_node(BL33_IMAGE_ID);
	assert(param_node != NULL);

#if TRANSFER_LIST
	/* Update BL33's ep info with NS HW config address  */
	te = transfer_list_find(ns_tl, TL_TAG_FDT);
	assert(te != NULL);

	param_node->ep_info.args.arg1 = TRANSFER_LIST_SIGNATURE |
					REGISTER_CONVENTION_VERSION_MASK;
	param_node->ep_info.args.arg2 = 0;
	param_node->ep_info.args.arg3 = (uintptr_t)ns_tl;
	param_node->ep_info.args.arg0 =
		te ? (uintptr_t)transfer_list_entry_data(te) : 0;
#else
	hw_config_info = FCONF_GET_PROPERTY(dyn_cfg, dtb, HW_CONFIG_ID);
	assert(hw_config_info != NULL);

	param_node->ep_info.args.arg1 = hw_config_info->secondary_config_addr;
#endif /* TRANSFER_LIST */
#endif /* !RESET_TO_BL2 && !EL3_PAYLOAD_BASE */
=======
#endif /* TRANSFER_LIST */
>>>>>>> upstream_import/upstream_v2_14_1

	return arm_bl_params;
}

int bl2_plat_handle_post_image_load(unsigned int image_id)
{
<<<<<<< HEAD
#if !RESET_TO_BL2 && !EL3_PAYLOAD_BASE
	if (image_id == HW_CONFIG_ID) {
		const struct dyn_cfg_dtb_info_t *hw_config_info;
		struct transfer_list_entry *te __unused;

		const bl_mem_params_node_t *param_node =
			get_bl_mem_params_node(image_id);
=======
#if !RESET_TO_BL2 && !EL3_PAYLOAD_BASE && !TRANSFER_LIST
	if (image_id == HW_CONFIG_ID) {
		const struct dyn_cfg_dtb_info_t *hw_config_info __unused;
		struct transfer_list_entry *te __unused;
		bl_mem_params_node_t *param_node __unused;

		param_node = get_bl_mem_params_node(image_id);
>>>>>>> upstream_import/upstream_v2_14_1
		assert(param_node != NULL);

		hw_config_info = FCONF_GET_PROPERTY(dyn_cfg, dtb, HW_CONFIG_ID);
		assert(hw_config_info != NULL);

<<<<<<< HEAD
#if TRANSFER_LIST
		/* Update BL33's ep info with NS HW config address  */
		te = transfer_list_add(ns_tl, TL_TAG_FDT,
				       param_node->image_info.image_size,
				       (void *)hw_config_info->config_addr);
		assert(te != NULL);
#else
=======
>>>>>>> upstream_import/upstream_v2_14_1
		memcpy((void *)hw_config_info->secondary_config_addr,
		       (void *)hw_config_info->config_addr,
		       (size_t)param_node->image_info.image_size);

		/*
		 * Ensure HW-config device tree is committed to memory, as the HW-Config
		 * might be used without cache and MMU enabled at BL33.
		 */
		flush_dcache_range(hw_config_info->secondary_config_addr,
				   param_node->image_info.image_size);
<<<<<<< HEAD
#endif /* TRANSFER_LIST */
	}
#endif /* !RESET_TO_BL2 && !EL3_PAYLOAD_BASE */

	return arm_bl2_plat_handle_post_image_load(image_id);
}
=======
	}
#endif /* !RESET_TO_BL2 && !EL3_PAYLOAD_BASE && !TRANSFER_LIST*/

	return arm_bl2_plat_handle_post_image_load(image_id);
}

uintptr_t plat_get_hw_dt_base(void)
{
	const struct dyn_cfg_dtb_info_t *hw_config_info;

	hw_config_info = FCONF_GET_PROPERTY(dyn_cfg, dtb, HW_CONFIG_ID);
	if (hw_config_info == NULL) {
		return 0U;
	}

	return hw_config_info->secondary_config_addr;
}
>>>>>>> upstream_import/upstream_v2_14_1
