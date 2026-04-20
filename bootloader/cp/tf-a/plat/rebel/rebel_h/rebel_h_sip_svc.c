#include <platform_def.h>
#include <smccc_helpers.h>
#include <common/runtime_svc.h>
#include <lib/mmio.h>
#include "rebel_sip_svc.h"
#include <rebel_h_sip.h>
#include <drivers/flash/mt25q_flash.h>

static uintptr_t generate_sys_cm_interrupt(void *handle)
{
	mmio_write_32(SYSREG_ROT + SYS_CM_INTERRUPT, GEN_INTERRUPT);

	SMC_RET1(handle, SMC_OK);
}

uintptr_t rebel_plat_sip_handler(uint32_t smc_fid,
								 u_register_t x1, u_register_t x2,
								 u_register_t x3, u_register_t x4,
								 void *cookie,
								 void *handle,
								 u_register_t flags)
{
	uint32_t res = 0;

	switch (smc_fid) {
	case REBEL_H_SMC_SYS_CM_INTERRUPT:
		return generate_sys_cm_interrupt(handle);

	case REBEL_H_SMC_FLASH_READ:
		res = read_flash((uint32_t)x1, (void *)x2, (uint32_t)x3);
		if (res == 0) {
			SMC_RET1(handle, SMC_OK);
		} else {
			SMC_RET1(handle, SMC_UNK);
		}

	case REBEL_H_SMC_FLASH_WRITE:
		write_flash((uint32_t)x1, (void *)x2, (uint32_t)x3);
		if (res == 0) {
			SMC_RET1(handle, SMC_OK);
		} else {
			SMC_RET1(handle, SMC_UNK);
		}

	case REBEL_H_SMC_FLASH_ERASE:
		erase_flash((uint32_t)x1, (uint32_t)x2);
		if (res == 0) {
			SMC_RET1(handle, SMC_OK);
		} else {
			SMC_RET1(handle, SMC_UNK);
		}

	default:
		ERROR("%s: unhandled SMC (0x%x)\n", __func__, smc_fid);
		SMC_RET1(handle, SMC_UNK);
	}
}
