#ifndef __RBCM_H
#define __RBCM_H

#include <stdint.h>
#include "rbcm_reg_model.h"
#include "../rbc/registers/aw_ucie_reg.h"

enum rbcm_link_speed {
	TARGET_LINK_SPEED_4GT = 0,
	TARGET_LINK_SPEED_8GT,
	TARGET_LINK_SPEED_12GT,
	TARGET_LINK_SPEED_16GT,
	TARGET_LINK_SPEED_24GT,
	TARGET_LINK_SPEED_32GT,
};

enum rbcm_link_width {
	TARGET_LINK_WIDTH_X8 = 1,
	TARGET_LINK_WIDTH_X16,
	TARGET_LINK_WIDTH_X32,
	TARGET_LINK_WIDTH_X64,
	TARGET_LINK_WIDTH_X128,
	TARGET_LINK_WIDTH_X256,
};

enum rbcm_module {
	RBC_C0S0, RBC_C0S1, RBC_C0E0, RBC_C0E1,
	RBC_C1N0, RBC_C1N1, RBC_C1E0, RBC_C1E1,
	RBC_C2N0, RBC_C2N1, RBC_C2E0, RBC_C2E1,
	RBC_C3S0, RBC_C3S1, RBC_C3E0, RBC_C3E1,
	/*---------------------- */
	RBC_BLK_INVALID
};

enum rbc_port {
	RBC_PORT0 = 0,
	RBC_PORT1 = 1,
	RBC_PORT2 = 2,
	/*---------------------- */
	RBC_PORT_INVALID
};

enum rbc_lb_type {
	RBC_LB_PORT = 0,
	RBC_LB_INNER = 1,
	RBC_LB_OUTER = 2,
	/*---------------------- */
	RBC_LB_INVALID
};

struct rbcm_data {
	enum rbcm_module module;
	const char *name;
	int32_t chiplet_id;
	uint32_t intr_id;
	uint64_t addr_remap_in_val;
	uint64_t addr_remap_out_val;
	volatile struct aw_ucie *ucie;
	struct rbc_reg *reg;
};

#define RBC_MODULE_COUNT RBC_BLK_INVALID
#define RBC_PORT_COUNT   RBC_PORT_INVALID

#endif /* __RBCM_H */
