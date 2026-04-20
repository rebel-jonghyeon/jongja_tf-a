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

#include <logging/log.h>
#include <rebel_h.h>

#include <drivers/cmrt/fmc.h>
LOG_MODULE_DECLARE(main, CONFIG_CMRT_LOG_LEVEL);

const static char version_info[] __version = SUPERVISOR_VERSION_INFO;

/*
 * functions below(related to OTP) are only for feature test.
 * will be implemented in driver format.
 */
#define OTP_CON_PRIVATE				(0x1E00250000ULL)
#define OTP_CON_CONTROL				(0x110)
	#define STANDBY_CMD				(0x8)
	#define PROGRAM_CMD				(0x4)
	#define INIT_CMD				(0x1)
#define OTP_INT_STATUS				(0x11C)
	#define INIT_DONE				(0x1)
	#define PROGRAM_DONE			(0x4)
	#define SECURE_FAIL				(0x20)
#define OTP_IF						(0x118)
	#define PROGRAM_DATA			(0x80000000ULL)

#define FIPS_MODE_START_BIT_ADDR	(0x500)

#define FIPS_MODE_0					(0x1024)	/* preloading value in sfr */

int set_count_in_value(uint32_t value)
{
	uint32_t set_count = 0;

	for (int i = 0; i < 32; i++) {
		if (((value >> i) & BIT(0)) == BIT(0)) {
			set_count++;
		}
	}
	return set_count;
}

int is_fips_enabled(void)
{
	cmrt_sac_set_base(NULL, OTP_CON_PRIVATE);
	uint32_t fips_mode = cmrt_sac_read32(SAC_MEMORY_BASE + FIPS_MODE_0);

	LOG_INF("FIPS_MODE value in SFR(preloading) : 0x%x", fips_mode);

	uint32_t set_count = set_count_in_value(fips_mode);

	/*
	 * return 0 --> fips mode disabled
	 * return 1 --> fips mode enabled
	 */
	return !(set_count % 2);
}

void otp_init(void)
{
	LOG_INF("OTP init start");

	cmrt_sac_set_base(NULL, OTP_CON_PRIVATE);
	cmrt_sac_write32(INIT_CMD, SAC_MEMORY_BASE + OTP_CON_CONTROL);

	do {
		;
	} while ((cmrt_sac_read32(SAC_MEMORY_BASE + OTP_INT_STATUS) & BIT(0)) != INIT_DONE);

	LOG_INF("OTP init done");
}

/*
 * if fips-mode is on, calling this func will make fips-mode is off when next booting.
 * if fips-mode is off, calling this func will make fips-mode is on when next booting.
 */
int invert_fips_mode(void)
{
	cmrt_sac_set_base(NULL, OTP_CON_PRIVATE);
	uint32_t fips_mode = cmrt_sac_read32(SAC_MEMORY_BASE + FIPS_MODE_0); /* preload value in sfr */
	uint32_t set_count = set_count_in_value(fips_mode);

	if (set_count == 32) {
		LOG_INF("OTP FIPS_MODE all wasted");
		return -1;
	}

	for (int i = 0; i < 32; i++) {
		if (((fips_mode >> i) & BIT(0)) == BIT(0)) {
			continue;
		} else {
			LOG_INF("OTP FIPS_MODE program in [%d]bit", i);
			cmrt_sac_write32(PROGRAM_DATA | FIPS_MODE_START_BIT_ADDR | (BIT(i) - 1),
							 SAC_MEMORY_BASE + OTP_IF);
			cmrt_sac_write32(PROGRAM_CMD, SAC_MEMORY_BASE + OTP_CON_CONTROL);
			volatile uint32_t otp_int_status;

			do {
				otp_int_status = cmrt_sac_read32(SAC_MEMORY_BASE + OTP_INT_STATUS);
				if ((otp_int_status & BIT(5)) == SECURE_FAIL) {
					LOG_INF("OTP program secure fail");
					return -1;
				}
			} while ((otp_int_status & BIT(2)) != PROGRAM_DONE);

			cmrt_sac_write32(otp_int_status, SAC_MEMORY_BASE + OTP_INT_STATUS);

			break;
		}
	}

	cmrt_sac_write32(STANDBY_CMD, SAC_MEMORY_BASE + OTP_IF);

	return 0;
}

void set_tdv(void)
{
	uint32_t tdv[4];

	tdv[0] = 0xffffffff;
	tdv[1] = 0xffffffff;
	tdv[2] = 0xffffffff;
	tdv[3] = 0xffffffff;
	cmrt_fmc_t fmc = cmrt_fmc_open();

	uint32_t tdv_read[4];

	for (uint32_t i = 0; i < (uint32_t)CMRT_FMC_TDV_SIZE; i++) {
		cmrt_fmc_write(fmc, FMC_TDV_OFFSET + i * 4u,
					   tdv[i], 0xffffffffu);
		LOG_INF("***************TDV[%u] written: 0x%x", i, tdv[i]);
	}
	(uint32_t)cmrt_fmc_set_debug_mode(fmc);

	for (uint32_t i = 0; i < (uint32_t)CMRT_FMC_TDV_SIZE; i++) {
		cmrt_fmc_read(fmc, FMC_TDV_OFFSET + i * 4u, &tdv_read[i]);
		LOG_INF("***************TDV[%u] read 0x%x", i, tdv_read[i]);
	}
	cmrt_fmc_close(fmc);
}

int main(void)
{
	LOG_INF("start main\n");
	cmrt_set_boot_status(SUPERVISOR_RUNNING_ID, SUPERVISOR_RUNNING_ID);
#ifdef SUPERVISOR_SAMPLE_STARTED
	cmrt_write_reg(CMRT_SIC_BASE, R_SCRATCH_0, SUPERVISOR_SAMPLE_STARTED);
#endif

	otp_init();
	if (is_fips_enabled() == 1) {
		LOG_INF("currently, FIPS MODE is **ENABLED**");
		if (invert_fips_mode() == 0) {
			LOG_INF("write FIPS_MODE 1 bit in OTP to disable FIPS_MODE done.");
			LOG_INF("FIPS_MODE will be off when reboot");
			LOG_INF("Also can check otp mem by this command,"
					" memory -store top.dut.BLK_ROT.OTP_CON_SOC_mem_wrapper."
					"sf_otp64kb_cp_s101_ln04lpp_3207000_inst.mem1 -file otp_dump_c0.txt");
			LOG_INF(" memory -store top.dut1.BLK_ROT.OTP_CON_SOC_mem_wrapper."
					"sf_otp64kb_cp_s101_ln04lpp_3207000_inst.mem1 -file otp_dump_c1.txt");
			LOG_INF(" memory -store top.dut2.BLK_ROT.OTP_CON_SOC_mem_wrapper."
					"sf_otp64kb_cp_s101_ln04lpp_3207000_inst.mem1 -file otp_dump_c2.txt");
			LOG_INF(" memory -store top.dut3.BLK_ROT.OTP_CON_SOC_mem_wrapper."
					"sf_otp64kb_cp_s101_ln04lpp_3207000_inst.mem1 -file otp_dump_c3.txt");
			LOG_INF("dump file will be generated in zebu.run/zrci.db/");

			LOG_INF("waiting reset,   force top.nRESET_tri 'b0 -radix bin -deposit");
			LOG_INF("		force top.nRESET_tri 'b1 -radix bin -deposit");

			LOG_INF("set tdv sfr with fmc.");
			set_tdv();
			LOG_INF("try to attach to RISC-V (expect not available)");
			__asm__("j .");
		} else {
			LOG_INF("write FIPS_MODE 1 bit in OTP to disable FIPS_MODE fail.");
			__asm__("j .");
		}
	} else {
		LOG_INF("currently, FIPS MODE is **DISABLED**");
		LOG_INF("set tdv sfr with fmc.");
		set_tdv();

		LOG_INF("try t32 attach to RISC-V (expect available)");
		__asm__("j .");
	}

	return 0;
}
