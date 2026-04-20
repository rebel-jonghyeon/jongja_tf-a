/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <fboot.h>
#ifdef CONFIG_CMRT_CFI
#include <drivers/cmrt/util.h>
#endif

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define PERSO_STATUS_STARTED  0x930100ff
#define PERSO_STATUS_DONE     0x93010000
#define PERSO_STATUS_ERROR    0x93010100

const static char version_info[] __version = PERSO_VERSION_INFO;

int main(void)
{
	cmrt_set_boot_status(CONTAINER_RUNNING_ID, CONTAINER_RUNNING_ID);
	uint32_t lifecycle = cmrt_read_reg(CMRT_SIC_BASE, R_SCRATCH_0);
	if (lifecycle == 0 || lifecycle == 0xffffffff) {
	    lifecycle = DLC_TESTED;
	}
	cmrt_set_perso_status(PERSO_STATUS_STARTED);
	LOG_INF("Blank perso %s starting up", version_info);

	int res;
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP_INIT
	res = cmrt_init_oec_version();
	if (res) goto out;
#endif
#ifdef CONFIG_CMRT_CFI
	res = cmrt_burn_dgok();
	if (res) goto out;
#endif
	res = cmrt_set_lifecycle(lifecycle);
	if (res) goto out;

	LOG_INF("All done for blank perso");
 out:
	cmrt_set_boot_status(0, CONTAINER_RUNNING_ID);
	cmrt_set_perso_status((res < 0) ? PERSO_STATUS_ERROR : PERSO_STATUS_DONE);

	return res;
}
