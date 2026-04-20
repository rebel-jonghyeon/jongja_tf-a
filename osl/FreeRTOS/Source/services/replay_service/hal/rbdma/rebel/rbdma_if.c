/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2024 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#include <stdbool.h>
#include "gic.h"
#include "system_api.h"
#include "rbln/cache.h"
#include "hal/rbdma_if.h"
#include "rbdma_regs.h"
#include "g_sys_addrmap.h"
#include "rl_utils.h"
#include "rbln/abort.h"
#include "rl_sizes.h"
#include "rbln/log.h"
#include "rbln/rebel.h"
#include "hal/addr_map.h"
#include "hal/interrupt.h"
#include "hal/hw_spec.h"
#include "replay.h"
#include "common/profile.h"
#include "common/af_profile.h"

#include "common_test.h"	/* test_exception_mark() */
#include "common/debug.h"
#include "../../../../../drivers/smmu/smmu_pmu.h"

static union rbdma_ip_info4 info4;
static union rbdma_ip_info5 info5;
static union rbdma_ip_info3 info3;
static union rbdma_dump_size dump_size;

static uint64_t rbdma_base = NBUS_L_RBDMA_CFG_BASE;

#define RBDMA_BASE_CL(x) (NBUS_L_RBDMA_CFG_BASE + cl_base[x])

/* insert logmgr varaible for rbdma perf*/
static void *logmgr_dump_addr;
static bool logmgr_enabled;

#define CDMA_GLOBAL						(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_GLOBAL)
#define CDMA_TASK						(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_TASK)
#define CDMA_PT							(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_PT)
#define CDMA_DPLOG						(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_DPROFILE)
#define CDMA_TSYNC						(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_TSYNC)
#define CDMA_DBG_UTLB					(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_DBG_UTLB)
#define CDMA_DBG_TSYNC					(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_DBG_TSYNC)
#define CDMA_AUTO_FETCH					(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_AUTO_FETCH)

#define CDMA_TASK_WRITE(val, offset)	rl_writel_relaxed(val, (void *)(CDMA_TASK + offset))

#define CDMA_GLOBAL_WRITE(val, offset)	rl_writel_relaxed(val, (void *)(CDMA_GLOBAL + offset))
#define CDMA_GLOBAL_READ(offset)		rl_readl_relaxed((void *)(CDMA_GLOBAL + offset))

#define CDMA_DPLOG_WRITE(val, offset)	rl_writel_relaxed(val, (void *)(CDMA_DPLOG + offset))
#define CDMA_DPLOG_READ(offset)			rl_readl_relaxed((void *)(CDMA_DPLOG + offset))

#define CDMA_TSYNC_WRITE(val, offset)	rl_writel_relaxed(val, (void *)(CDMA_TSYNC + offset))
#define CDMA_TSYNC_READ(offset)			rl_readl_relaxed((void *)(CDMA_TSYNC + offset))

#define CDMA_AUTO_FETCH_WRITE(val, offset)  rl_writel_relaxed(val, (void*)(CDMA_AUTO_FETCH + offset))
#define CDMA_AUTO_FETCH_READ(offset)        rl_readl_relaxed((void*)(CDMA_AUTO_FETCH + offset))

#define EDMA_GLOBAL_WRITE(i, val, offset) \
rl_writel_relaxed(val, (void *)(rbdma_base + ((i + 8) << 12) + ADDR_OFFSET_RBDMA_EDMA_GLOBAL + offset))

#define EDMA_GLOBAL_READ(i, offset) \
rl_readl_relaxed((void *)(rbdma_base + ((i + 8) << 12) + ADDR_OFFSET_RBDMA_EDMA_GLOBAL + offset))


#define CDMA_GLOBAL_CL(x)						(RBDMA_BASE_CL(x) + ADDR_OFFSET_RBDMA_CDMA_GLOBAL)
#define CDMA_DPLOG_CL(x)						(RBDMA_BASE_CL(x) + ADDR_OFFSET_RBDMA_CDMA_DPROFILE)

#define CDMA_GLOBAL_WRITE_CL(x, val, offset)	rl_writel_relaxed(val, (void *)(CDMA_GLOBAL_CL(x) + offset))
#define CDMA_GLOBAL_READ_CL(x, offset)		rl_readl_relaxed((void *)(CDMA_GLOBAL_CL(x) + offset))

#define CDMA_DPLOG_WRITE_CL(x, val, offset)	rl_writel_relaxed(val, (void *)(CDMA_DPLOG_CL(x) + offset))
#define CDMA_DPLOG_READ_CL(x, offset)			rl_readl_relaxed((void *)(CDMA_DPLOG_CL(x) + offset))



#define HBM_CTRL_OFFSET			    0x40000
#define HBM_AM_INTERVAL			    0x49e8
#define HBM_AM_SINGLE_EN		    0x49e4
#define HBM_AM_STAT_AM_COMPLETE	    0x49ec

//#define PERF_DETAIL
struct hbm_am {
    const char *name;
    uint32_t offset;
};

#ifdef PERF_DETAIL
static struct hbm_am hbm_am_list[] = {
    {"AM_WR_CMD",               0xac00},
    {"AM_WR_AP_CMD",            0xac04},
    {"AM_RD_CMD",               0xac08},
    {"AM_RD_AP_CMD",            0xac0c},
    {"AM_REFRESH_CMD",          0xac10},
    {"AM_ACT_CMD",              0xac14},
    {"AM_PRECHARGE_CMD",        0xac18},
    {"AM_PRECHARGE_ALL_CMD",    0xac1c},
    {"AM_RD_TO_WR_SWITCH",      0xac28},
    {"AM_RO_AGE_LIMIT",         0xac2c},
    {"AM_RWM_CYCLE",            0xac30},
    {"AM_INTERVAL_COUNT_AXI1",  0xac34},
    {"AM_WAC_ACTIVE_AXI1",      0xac38},
    {"AM_WAC_STALL_AXI1",       0xac3c},
    {"AM_RAC_ACTIVE_AXI1",      0xac40},
    {"AM_RAC_STALL_AXI1",       0xac44},
    {"AM_WDC_ACTIVE_AXI1",      0xac48},
    {"AM_WDC_STALL_AXI1",       0xac4c},
    {"AM_RDC_ACTIVE_AXI1",      0xac50},
    {"AM_RDC_STALL_AXI1",       0xac54},
    {"AM_CTRLR_QUEUE_SUM",      0xac58},
};
#endif

/* for hbm perf w/ rbdma */
#define HBM_CTRL_WRITE(val, ch, offset)	rl_writel_relaxed(val, (void *)(DRAM_CNTL_BASE + ch * HBM_CTRL_OFFSET + offset))
#define HBM_CTRL_READ(ch, offset)		rl_readl_relaxed((void *)(DRAM_CNTL_BASE + ch * HBM_CTRL_OFFSET + offset))

/* for hbm perf w/ rbdma - chiplet specific */
#define HBM_CTRL_WRITE_CL(cl_id, val, ch, offset)	rl_writel_relaxed(val, (void *)(cl_base[cl_id] + DRAM_CNTL_BASE + ch * HBM_CTRL_OFFSET + offset))
#define HBM_CTRL_READ_CL(cl_id, ch, offset)		rl_readl_relaxed((void *)(cl_base[cl_id] + DRAM_CNTL_BASE + ch * HBM_CTRL_OFFSET + offset))

static void rbdma_adjust_base(uint32_t cl_id)
{
	RLOG_DBG("adjust rbdma address clid: %d\r\n", cl_id);
	rbdma_base = cl_base[cl_id] + NBUS_L_RBDMA_CFG_BASE;
}

static const char * const rbdma_err_int_status_str_tbl[] = {
	"task executor parity error",	//0
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"task executor timeout",	//8
	"reserved",
	"dpdc error",				//10
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"control bus wrong command",	//16
	"page table error",			//17
	"page table overflow",		//18
	"reserved",
	"task queue overflow",		//20
	"data bus read error",		//21
	"data bus write error",		//22
	"fnsh interrupt fifo full write",	//23
	"reserved",					//24, burst length violation - spec_out
	"cbus_af_error",			//25
	"cbus_mst_error",			//26
};

static const char * const rbdma_err_info_app0_str_tbl[] = {
	// this is code value
	"wrong command",		//0
	"page table error",		//1
	"reserved",
	"wrong op of Queues", 	//3
	"RAS parity error",		//4
	"reserved",
	"RAS bus error",		//6
	"reserved",
	"dpdc error",			//8
	"reserved",
	"interrupt fifo full write",	//10
	"cntri_mst_read_error",		//11
	"cntri_slv_bl_error",		//12
	"cntri_mst_write_error",	//13
};

#define ID_INFO_STR		"ctx %d proc %d cid %d"

static void rbdma_reg_dump(void)
{
	uint32_t num_te = info3.num_of_executer;

	print_regs("CDMA Global", (uint64_t)CDMA_GLOBAL, 116);
	print_regs("CDMA Task", (uint64_t)CDMA_TASK, 32);
	print_regs("CDMA PT", (uint64_t)CDMA_PT, 22);
	print_regs("CDMA Debug and Profile", (uint64_t)CDMA_DPLOG, 79);
	print_regs("CDMA TSync", (uint64_t)CDMA_TSYNC, 24);
	print_regs("CDMA Debug Tsync", (uint64_t)CDMA_DBG_TSYNC, 512);
	print_regs("CDMA Debug UTLB", (uint64_t)CDMA_DBG_UTLB, 512);
	print_regs("CDMA Auto Fetch", (uint64_t)CDMA_AUTO_FETCH, 32);

	for (uint32_t i = 0; i < num_te; i++) {
		/* TE_x EDMA regbank offset = (TE index + 8) << 12 */
		uint64_t edma_cfg_base = rbdma_base + ((i + 8) << 12);

		RLOG_ERR("EDMA TE%u register dump\r\n", i);

		print_regs("EDMA Global", edma_cfg_base + ADDR_OFFSET_RBDMA_EDMA_GLOBAL, 27);
		print_regs("EDMA Debug", edma_cfg_base + ADDR_OFFSET_RBDMA_EDMA_DEBUG, 77);
		print_regs("EDMA Bus Profile", edma_cfg_base + ADDR_OFFSET_RBDMA_EDMA_BUSPRF, 32);
	}
}

#define RBDMA_ERR_BUS_READ		21
#define RBDMA_ERR_BUS_WRITE		22
#define RBDMA_ERR_FNSH_FIFO_FULL_WRITE	23

#define RBDMA_RECOVERABLE_MASK	(1u << RBDMA_ERR_FNSH_FIFO_FULL_WRITE)

#define RBDMA_SKIPPABLE_MASK	((1u << RBDMA_ERR_BUS_READ) | \
				 (1u << RBDMA_ERR_BUS_WRITE))

void rbdma_error_handler(void *data)
{
	union rbdma_global_err_intr_fifo err_fifo;
	union rbdma_global_err_intr_info_app0 info_app0;
	union rbdma_global_err_intr_info_app1 info_app1;
	union rbdma_td_ptid_init *ptid_init = (union rbdma_td_ptid_init *)&info_app1;
	union rbdma_global_intr_fifo_readable_num readable_num;
	union rbdma_global_fnsh_intr_fifo intr_fifo;
	uint32_t err_code;

#if defined(INDICATOR_DEBUG_MODE)
	TEST_GPD2_DAT |= 0x1;	// trigger GPD2[0]
#endif /* #if defined(INDICATOR_DEBUG_MODE) */

	abort_other_cores();

	readable_num.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_INTR_FIFO_READABLE_NUM);
	printf("readable_num: %#x (fnsh=%d, err=%d)\r\n",
	       readable_num.bits, readable_num.fnsh, readable_num.err);

	/* ERR_INTR_FIFO is a FIFO with multiple entries (readable_num.err).
	 * Drain ALL entries to prevent IRQ re-fire.
	 * Accumulate all error bits encountered across entries to decide recovery.
	 */
	uint32_t err_fifo_accum = 0;

	while (readable_num.err > 0) {
		err_fifo.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_ERR_INTR_FIFO);
		info_app0.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_ERR_INTR_INFO_APP0);
		info_app1.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_ERR_INTR_INFO_APP1);
		err_fifo_accum |= err_fifo.bits;

		while (err_fifo.bits) {
			int i = __builtin_ffs(err_fifo.bits) - 1;

			FLOG_ERR(ptid_init->func_id, "RBDMA ("ID_INFO_STR") error! %s\r\n", ptid_init->ctx_id,
					 ptid_init->thread_id, ptid_init->cmd_id, rbdma_err_int_status_str_tbl[i]);
			printf("(%02d)RBDMA ("ID_INFO_STR") error! %s\r\n", ptid_init->func_id,
				   ptid_init->ctx_id, ptid_init->thread_id, ptid_init->cmd_id,
				   rbdma_err_int_status_str_tbl[i]);
			RL_CLR_BIT(err_fifo.bits, i);
		}

		err_code = info_app0.bits & 0xf;
		printf("info_app0 : %#x(%s) %#x\r\n", info_app0.bits, rbdma_err_info_app0_str_tbl[err_code],
			   info_app1.bits);

		readable_num.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_INTR_FIFO_READABLE_NUM);
	}

	/* fnsh fifo full write: drain remaining fnsh entries with notify.
	 * Loop until empty (readable_num.fnsh may change between snapshots).
	 * Without replay_rbdma_notify, waiting tasks would hang.
	 */
	if (err_fifo_accum & (1u << RBDMA_ERR_FNSH_FIFO_FULL_WRITE)) {
		uint32_t drained = 0;

		while (1) {
			readable_num.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_INTR_FIFO_READABLE_NUM);
			if (!readable_num.fnsh)
				break;
			intr_fifo.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_FNSH_INTR_FIFO);
			replay_rbdma_notify(intr_fifo.cmd_id);
			drained++;
		}
		printf("fnsh fifo full write: drained %d entries with notify\r\n", drained);
	}

	/* Recoverable (fnsh fifo full write): skip abort, flag untouched.
	 * Skippable (bus read/write error): skip abort but mark test as failed.
	 */
	if (err_fifo_accum &&
	    !(err_fifo_accum & ~(RBDMA_RECOVERABLE_MASK | RBDMA_SKIPPABLE_MASK))) {
		if (err_fifo_accum & RBDMA_SKIPPABLE_MASK)
			test_exception_mark();
		printf("Skippable error: err_fifo_accum=%#x\r\n", err_fifo_accum);
		return;
	}

	/* Non-recoverable path: mark test as failed */
	test_exception_mark();

	rbdma_reg_dump();
	smmu_pmu_print_enabled_cnt();

	rl_abort_cur_ctx(ERR_RBDMA);
}

void rbdma_done_handler(void *data)
{
	union rbdma_global_intr_fifo_readable_num readable_num;
	union rbdma_global_fnsh_intr_fifo intr_fifo;

	while (1) {
        rl_profile_log_start(HANDLER);
		readable_num.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_INTR_FIFO_READABLE_NUM);
		if (!readable_num.fnsh)
			break;

		intr_fifo.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_FNSH_INTR_FIFO);
		FLOG_DBG(intr_fifo.func_id, "RBDMA done ("ID_INFO_STR")\r\n", intr_fifo.ctx_id,
				 intr_fifo.thread_id, intr_fifo.cmd_id);
		replay_rbdma_notify(intr_fifo.cmd_id);
        rl_profile_log(HANDLER, intr_fifo.cmd_id, COMMON_CMD_TYPE_DDMA);
	}
}

static void rbdma_get_ip_info(uint32_t cl_id)
{
	union rbdma_ip_info0 info0;
	union rbdma_ip_info1 info1;
	union rbdma_ip_info2 info2;

	info0.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_IP_INFO0);
	info1.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_IP_INFO1);
	info2.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_IP_INFO2);
	info3.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_IP_INFO3);
	info4.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_IP_INFO4);
	info5.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_IP_INFO5);

	info2.chiplet_id = cl_id;
	CDMA_GLOBAL_WRITE(info2.bits, ADDR_OFFSET_RBDMA_IP_INFO2);

	/* Max dram dump size of log manager */
	dump_size.bits = CDMA_DPLOG_READ(ADDR_OFFSET_RBDMA_DUMP_SIZE);

	RLOG_INFO("RBDMA HW INFO: rel_date: %#lx rbdma ver: %u MRV ver: %u.%u chiplet_id: %u\r\n",
			  info0.rel_date, info1.rbdma_ver, info1.maj_ver, info1.min_ver, info2.chiplet_id);
}

static void rbdma_change_tsync_dnc_cfg_baseaddr(uint32_t cl_id)
{
	union rbdma_tsync_dnc_cfg_baseaddr baseaddr;

	baseaddr.bits = 0x1FF20000U + 0x20000000U * cl_id;

	CDMA_TSYNC_WRITE(baseaddr.bits, ADDR_OFFSET_RBDMA_TSYNC_DNC_CFG_BASEADDR);
}

void rbdma_enable_profile_mode()
{
    union rbdma_control     control = {0, };
    union rbdma_dump_dest0  profile_dest0 = {0, };
    union rbdma_dump_dest1  profile_dest1 = {0, };

    control.enable = 1;
    control.reset_timer = 1;
    control.clear_buffer = 1;
    control.reset_dump = 1;

    profile_dest0.bits = RBDMA_PROFILE_BASE_ADDR_LOW;
    profile_dest1.bits = RBDMA_PROFILE_BASE_ADDR_HIGH;

    CDMA_DPLOG_WRITE(control.bits, ADDR_OFFSET_RBDMA_CONTROL);
    CDMA_DPLOG_WRITE(profile_dest0.bits, ADDR_OFFSET_RBDMA_DUMP_DEST0);
    CDMA_DPLOG_WRITE(profile_dest1.bits, ADDR_OFFSET_RBDMA_DUMP_DEST1);

}

void rbdma_init(uint32_t cl_id)
{
	union rbdma_global_config_cdma_opmode0 opmode0;
	union rbdma_global_config_cdma_intr_set0 intr;
	union rbdma_global_config_cdma_dplog_set dplog;
	union rbdma_global_donerpt_mst_base mst_base;

	rbdma_adjust_base(cl_id);

	opmode0.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);
	opmode0.en_cmgr_evt0 = 0;
	opmode0.en_cmgr_evt1 = 0;
	opmode0.en_cmgr_evt2 = 0;
	opmode0.en_auto_fetch = 0;
	opmode0.max_perf = 1;		// 0; //25-0814, by rbdma designer guide
	opmode0.split_granule = 0;
	opmode0.read_bl = 3;
	opmode0.write_bl = 3;
	opmode0.overwrite = 1;	/* CDMA configure overwrite over task descriptor's read and write bl field */
	opmode0.mp_mode = 0;
	CDMA_GLOBAL_WRITE(opmode0.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);

	intr.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0);
	intr.finish_intr_app_en = 0;
	intr.error_intr_app_en = 1;
	intr.en_mask_pterror = 1;	/* 1 means disabling interrupt */
	CDMA_GLOBAL_WRITE(intr.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_INTR_SET0);

	dplog.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_DPLOG_SET);
	dplog.en_log_event = 1;
	dplog.en_debug_cdma = 1;
	CDMA_GLOBAL_WRITE(dplog.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_DPLOG_SET);

	mst_base.bits = 0x0;
	CDMA_GLOBAL_WRITE(mst_base.bits, ADDR_OFFSET_RBDMA_GLOBAL_DONERPT_MST_BASE);

	rbdma_get_ip_info(cl_id);
	rbdma_change_tsync_dnc_cfg_baseaddr(cl_id);

	gic_irq_connect(INT_ID_RBDMA0_ERR, rbdma_error_handler, 0);
	gic_irq_connect(INT_ID_RBDMA1, rbdma_done_handler, 0);

	gic_irq_enable_dedicated_core(0, INT_ID_RBDMA0_ERR);
	gic_irq_enable_dedicated_core(0, INT_ID_RBDMA1);
}

#define RBDMA_TIMEOUT_THRESHOLD 3000000

void hbm_activity_monitor(uint32_t cl_id, uint32_t ch)
{
#ifdef PERF_DETAIL
    struct hbm_am *am;
    uint32_t rdata;

    for(int i = 0; i < sizeof(hbm_am_list) / sizeof(struct hbm_am); i++){
        am = &hbm_am_list[i];
        rdata = HBM_CTRL_READ_CL(cl_id, ch, am->offset);
        printf("%s : %d\n", am->name, rdata);
    }
#endif
}

void rbdma_done_acc_count(uint32_t cl_id, uint32_t count)
{
	union rbdma_clog_num_nrm_tdone_tstc0	tdone = {0,};
	uint32_t timeout;
	uint32_t status = 1;

	timeout = 0;
	do{
		tdone.bits = CDMA_DPLOG_READ(ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC0);

		if(tdone.na == count){
			status = 0;
		}

		if (++timeout > RBDMA_TIMEOUT_THRESHOLD) {
            RLOG_ERR("RBDMA[%02d] Timeout Error! ACC:[%d] ACC:[%d]\r\n", tdone.bits, count);
            return;
        }
//		ndelay(1);
	} while(status);

#ifdef PERF_DETAIL
	HBM_CTRL_WRITE_CL(cl_id, 0, 0, HBM_AM_INTERVAL);
	HBM_CTRL_WRITE_CL(cl_id, 0, 0, HBM_AM_SINGLE_EN);
//	hbm_activity_monitor(cl_id, 0);
#endif

//	RLOG_INFO("cl%02d rbdma_done_acc_count():%d\r\n", cl_id, count);
}

void rbdma_done_clear(uint32_t cl_id)
{
	union rbdma_clog_clear clog_clear = {0,};

	clog_clear.clear = 1;
	CDMA_DPLOG_WRITE_CL(cl_id, clog_clear.bits, ADDR_OFFSET_RBDMA_CLOG_CLEAR);

	RLOG_INFO("CL%02d RBDMA done accumulated counter cleared.\r\n", cl_id);
}

void generate_rbdma_task(uint32_t task_id, uint64_t src_addr, uint64_t dst_addr, uint32_t transfer_size, uint8_t task_type)
{
	union rbdma_td_ptid_init    ptid_init = {0x0, };
	union rbdma_td_srcaddress_or_const  srcaddr = {0x0, };
	union rbdma_td_destaddress  destaddr = {0x0, };
	union rbdma_td_sizeof128block   trs_size = {0x0, };
	union rbdma_td_tsync_conf_mask  tsync_conf_mask = {0x0, };
	union rbdma_td_sync_conf_gidx   sync_conf_gidx = {0x0, };
	union rbdma_td_run_conf0        run_conf0 = {0x0, };
	union rbdma_td_run_conf1        run_conf1 = {0x0, };
	uint32_t task_data[8];
	volatile uint32_t __iomem *task_base;
	int i;

	ptid_init.bits = task_id;
	srcaddr.bits = src_addr>>7;
	destaddr.bits = dst_addr>>7;
	trs_size.bits = transfer_size>>7;
	tsync_conf_mask.bits = 0x0;
	sync_conf_gidx.bits = 0x0;
	run_conf0.task_type	= task_type;
	run_conf0.split_granule_l2 	= 1;
	run_conf0.ext_num_of_chunk	= 0x0;
	run_conf1.no_tlb	= 1;
	run_conf1.read_bl	= 3;
	run_conf1.write_bl	= 3;
	run_conf1.te_mask	= 0xff;

	// Prepare all 8 values in array for burst write
	task_data[0] = ptid_init.bits;
	task_data[1] = srcaddr.bits;
	task_data[2] = destaddr.bits;
	task_data[3] = trs_size.bits;
	task_data[4] = tsync_conf_mask.bits;
	task_data[5] = sync_conf_gidx.bits;
	task_data[6] = run_conf0.bits;
	task_data[7] = run_conf1.bits;

	// Burst write to consecutive addresses for CA73 optimization
	task_base = (volatile uint32_t __iomem *)CDMA_TASK;
	for (i = 0; i < 8; i++) {
		rl_writel_relaxed(task_data[i], task_base + i);
	}

	// Logging (kept for debugging)
	RLOG_INFO("\r\n%-18s : 0x%08x\r\n", "ptid_init", ptid_init.bits);
	RLOG_INFO("%-18s : 0x%08x (0x%lx)\r\n", "srcaddr", srcaddr.bits, src_addr);
	RLOG_INFO("%-18s : 0x%08x (0x%lx)\r\n", "destaddr", destaddr.bits, dst_addr);
	RLOG_INFO("%-18s : 0x%08x (0x%x)\r\n", "trs_size", trs_size.bits, transfer_size);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tsync_conf_mask", tsync_conf_mask.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "sync_conf_gidx", sync_conf_gidx.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "run_conf0", run_conf0.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "run_conf1", run_conf1.bits);
}

void generate_rbdma_perf_task(uint32_t task_id, uint64_t src_addr, uint64_t dst_addr, uint32_t transfer_size, uint8_t te_affinity, uint32_t split_granule, uint8_t task_type)
{
	union rbdma_td_ptid_init    ptid_init = {0x0, };
	union rbdma_td_srcaddress_or_const  srcaddr = {0x0, };
	union rbdma_td_destaddress  destaddr = {0x0, };
	union rbdma_td_sizeof128block   trs_size = {0x0, };
	union rbdma_td_tsync_conf_mask  tsync_conf_mask = {0x0, };
	union rbdma_td_sync_conf_gidx   sync_conf_gidx = {0x0, };
	union rbdma_td_run_conf0        run_conf0 = {0x0, };
	union rbdma_td_run_conf1        run_conf1 = {0x0, };
	uint32_t task_data[8];
	volatile uint32_t __iomem *task_base;
	int i;

	//printf("rbdma: 0x%x\r\n", task_id);

	ptid_init.bits = task_id;
	srcaddr.bits = src_addr>>7;
	destaddr.bits = dst_addr>>7;
	trs_size.bits = transfer_size>>7;
	tsync_conf_mask.bits = 0x0;
	sync_conf_gidx.bits = 0x0;
	run_conf0.task_type	= task_type;
	run_conf0.split_granule_l2 	= split_granule;
	run_conf0.ext_num_of_chunk	= 0x0;
	run_conf1.no_tlb	= 1;
	run_conf1.read_bl	= 3;
	run_conf1.write_bl	= 3;
	run_conf1.te_mask = te_affinity;

	// Prepare all 8 values in array for burst write
	task_data[0] = ptid_init.bits;
	task_data[1] = srcaddr.bits;
	task_data[2] = destaddr.bits;
	task_data[3] = trs_size.bits;
	task_data[4] = tsync_conf_mask.bits;
	task_data[5] = sync_conf_gidx.bits;
	task_data[6] = run_conf0.bits;
	task_data[7] = run_conf1.bits;

	// Burst write to consecutive addresses for CA73 optimization
	task_base = (volatile uint32_t __iomem *)CDMA_TASK;
	for (i = 0; i < 8; i++) {
		rl_writel_relaxed(task_data[i], task_base + i);
	}
#ifdef TASK_DEBUG
	// Logging (kept for debugging)
	RLOG_INFO("\r\n%-18s : 0x%08x\r\n", "ptid_init", ptid_init.bits);
	RLOG_INFO("%-18s : 0x%08x (0x%lx)\r\n", "srcaddr", srcaddr.bits, src_addr);
	RLOG_INFO("%-18s : 0x%08x (0x%lx)\r\n", "destaddr", destaddr.bits, dst_addr);
	RLOG_INFO("%-18s : 0x%08x (0x%x)\r\n", "trs_size", trs_size.bits, transfer_size);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tsync_conf_mask", tsync_conf_mask.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "sync_conf_gidx", sync_conf_gidx.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "run_conf0", run_conf0.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "run_conf1", run_conf1.bits);
#endif
}

void generate_rbdma_task_tsync(uint32_t task_id, uint64_t src_addr, uint64_t dst_addr, uint32_t transfer_size, uint32_t split_granule, uint8_t task_type, uint32_t te_mask, uint32_t is_tsync)
{
	union rbdma_td_ptid_init    ptid_init = {0x0, };
	union rbdma_td_srcaddress_or_const  srcaddr = {0x0, };
	union rbdma_td_destaddress  destaddr = {0x0, };
	union rbdma_td_sizeof128block   trs_size = {0x0, };
	union rbdma_td_tsync_conf_mask  tsync_conf_mask = {0x0, };
	union rbdma_td_sync_conf_gidx   sync_conf_gidx = {0x0, };
	union rbdma_td_run_conf0        run_conf0 = {0x0, };
	union rbdma_td_run_conf1        run_conf1 = {0x0, };
	uint32_t task_data[8];
	volatile uint32_t __iomem *task_base;
	int i;

	ptid_init.bits = task_id;
	srcaddr.bits = src_addr>>7;
	destaddr.bits = dst_addr>>7;
	trs_size.bits = transfer_size>>7;

	if (is_tsync == 1) {
		tsync_conf_mask.bits = 0x1;
		sync_conf_gidx.bits = 0x8f;
	}
	else {
		tsync_conf_mask.bits = 0x0;
		sync_conf_gidx.bits = 0x0;
	}

	run_conf0.task_type	= task_type;
	run_conf0.split_granule_l2 	= split_granule;
	run_conf0.ext_num_of_chunk	= 0x0;
	run_conf1.no_tlb	= 1;
	run_conf1.read_bl	= 3;
	run_conf1.write_bl	= 3;
	run_conf1.te_mask = te_mask;
	if (is_tsync == 1) {
		run_conf1.intr_disable = 1;
	}

	// Prepare all 8 values in array for burst write
	task_data[0] = ptid_init.bits;
	task_data[1] = srcaddr.bits;
	task_data[2] = destaddr.bits;
	task_data[3] = trs_size.bits;
	task_data[4] = tsync_conf_mask.bits;
	task_data[5] = sync_conf_gidx.bits;
	task_data[6] = run_conf0.bits;
	task_data[7] = run_conf1.bits;

	// Burst write to consecutive addresses for CA73 optimization
	task_base = (volatile uint32_t __iomem *)CDMA_TASK;
	for (i = 0; i < 8; i++) {
		rl_writel_relaxed(task_data[i], task_base + i);
	}
#ifdef TASK_DEBUG
	// Logging (kept for debugging)
	RLOG_INFO("\r\n%-18s : 0x%08x\r\n", "ptid_init", ptid_init.bits);
	RLOG_INFO("%-18s : 0x%08x (0x%lx)\r\n", "srcaddr", srcaddr.bits, src_addr);
	RLOG_INFO("%-18s : 0x%08x (0x%lx)\r\n", "destaddr", destaddr.bits, dst_addr);
	RLOG_INFO("%-18s : 0x%08x (0x%x)\r\n", "trs_size", trs_size.bits, transfer_size);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tsync_conf_mask", tsync_conf_mask.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "sync_conf_gidx", sync_conf_gidx.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "run_conf0", run_conf0.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "run_conf1", run_conf1.bits);
#endif
}

uint32_t rbdma_set_max_perf_mode(uint32_t sp_ratio)
{
	union rbdma_global_config_cdma_opmode0 config_cdma_opmode = {0x0, };
	uint32_t prev_bits = 0;

	prev_bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);
	config_cdma_opmode.mp_hash_pos1 = 0xd;
	config_cdma_opmode.mp_hash_pos0 = 0xc;
	config_cdma_opmode.write_bl = 0x2;
	config_cdma_opmode.read_bl = 0x2;
	config_cdma_opmode.split_granule = (sp_ratio & 0x2f);
	config_cdma_opmode.max_perf = 0x1;
	CDMA_GLOBAL_WRITE(config_cdma_opmode.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);

	return prev_bits;
}

void rbdma_set_global_config_cdma_opmode0(uint32_t bits)
{
	CDMA_GLOBAL_WRITE(bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);
}

uint32_t rbdma_get_global_config_cdma_opmode0(void)
{
	return CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);
}

void rbdma_tsync_by_cp(void)
{
	union rbdma_tsync_dnc_get_info dnc_get_info = {0x0, };

	dnc_get_info.gidx = 0xf;
	dnc_get_info.dncid = 0x40;
	CDMA_TSYNC_WRITE(dnc_get_info.bits, ADDR_OFFSET_RBDMA_TSYNC_DNC_GET_INFO);
}

void generate_rbdma_task_opt(rb_desc_t desc_conf)
{
	union rbdma_td_ptid_init    ptid_init = {0x0, };
	union rbdma_td_srcaddress_or_const  srcaddr = {0x0, };
	union rbdma_td_destaddress  destaddr = {0x0, };
	union rbdma_td_sizeof128block   trs_size = {0x0, };
	union rbdma_td_tsync_conf_mask  tsync_conf_mask = {0x0, };
	union rbdma_td_sync_conf_gidx   sync_conf_gidx = {0x0, };
	union rbdma_td_run_conf0        run_conf0 = {0x0, };
	union rbdma_td_run_conf1        run_conf1 = {0x0, };
	uint32_t task_data[8];
	volatile uint32_t __iomem *task_base;
	int i;

	ptid_init.bits = desc_conf.task_id;
	srcaddr.bits = desc_conf.src_addr>>7;
	destaddr.bits = desc_conf.dst_addr>>7;
	trs_size.bits = desc_conf.trs_size>>7;
	tsync_conf_mask.bits = desc_conf.get_dnc_mask;
	sync_conf_gidx.get_tsync_en = desc_conf.get_tsync_en;
	sync_conf_gidx.get_tsync_gidx = desc_conf.get_tsync_gidx;
	run_conf0.task_type	= desc_conf.task_type;
	run_conf0.split_granule_l2 	= desc_conf.split_granule_l2;
	run_conf0.ext_num_of_chunk	= desc_conf.num_of_chunk;
	run_conf1.intr_disable	= desc_conf.intr_disable;
	run_conf1.en_donerpt_mst	= desc_conf.en_donerpt_mst;
	run_conf1.en_invalid_pt 	= desc_conf.en_invalid_pt;
	run_conf1.no_tlb	= desc_conf.no_tlb;
	run_conf1.read_bl	= desc_conf.read_bl;
	run_conf1.write_bl	= desc_conf.write_bl;
	run_conf1.te_mask	= desc_conf.te_mask;
	run_conf1.read_qos	= desc_conf.read_qos;
	run_conf1.write_qos	= desc_conf.write_qos;

	// Prepare all 8 values in array for burst write
	task_data[0] = ptid_init.bits;
	task_data[1] = srcaddr.bits;
	task_data[2] = destaddr.bits;
	task_data[3] = trs_size.bits;
	task_data[4] = tsync_conf_mask.bits;
	task_data[5] = sync_conf_gidx.bits;
	task_data[6] = run_conf0.bits;
	task_data[7] = run_conf1.bits;

	/*
	 * volatile required for hardware memory-mapped I/O access
	 * Burst write to consecutive addresses for CA73 optimization
	 */
	task_base = (volatile uint32_t __iomem *)CDMA_TASK;
	for (i = 0; i < 8; i++) {
		rl_writel_relaxed(task_data[i], task_base + i);
	}

#ifdef TASK_DEBUG
	// Logging (kept for debugging)
	RLOG_INFO("\r\n%-18s : 0x%08x\r\n", "ptid_init", ptid_init.bits);
	RLOG_INFO("%-18s : 0x%08x (0x%lx)\r\n", "srcaddr", srcaddr.bits, desc_conf.src_addr);
	RLOG_INFO("%-18s : 0x%08x (0x%lx)\r\n", "destaddr", destaddr.bits, desc_conf.dst_addr);
	RLOG_INFO("%-18s : 0x%08x (0x%x)\r\n", "trs_size", trs_size.bits, desc_conf.trs_size);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tsync_conf_mask", tsync_conf_mask.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "sync_conf_gidx", sync_conf_gidx.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "run_conf0", run_conf0.bits);
	RLOG_INFO("%-18s : 0x%08x\r\n", "run_conf1", run_conf1.bits);
#endif
}

void generate_rbdma_chunk_opt(rb_desc_t desc_conf)
{
	union rbdma_tde_chk_base_addr_msb 	chk_base_addr_msb = {0x0, };
	uint64_t	chk_base_addr = 0;

	// chunk config
	chk_base_addr_msb.chk1_stride_msb	= 0x0;	// [40:39], chiplet??
	RLOG_INFO("\r\n%-18s : 0x%08x\r\n", "chk_base_addr_msb", chk_base_addr_msb.bits);
	CDMA_TASK_WRITE(chk_base_addr_msb.bits, ADDR_OFFSET_RBDMA_TDE_CHK_BASE_ADDR_MSB);

	if(desc_conf.task_type == 3){	// scatter
		chk_base_addr = desc_conf.dst_addr;
	}else if(desc_conf.task_type == 2){		// gather
		chk_base_addr = desc_conf.src_addr;
	}	
	RLOG_INFO("%-18s : 0x%08x\r\n", "chk1_base_addr", (chk_base_addr + SZ_4M)>>7);
	CDMA_TASK_WRITE( (chk_base_addr + SZ_4M)>>7, ADDR_OFFSET_RBDMA_TDE_CHK1_BASE_ADDR_OR_STRIDE);

	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk1_size", (desc_conf.trs_size>>7));
	CDMA_TASK_WRITE( (desc_conf.trs_size>>7), ADDR_OFFSET_RBDMA_TDE_CHK1_SIZE);

	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk2_base_addr", (chk_base_addr + SZ_4M*2)>>7);
	CDMA_TASK_WRITE( (chk_base_addr + SZ_4M*2)>>7, ADDR_OFFSET_RBDMA_TDE_CHK2_BASE_ADDR);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk2_size", (desc_conf.trs_size>>7));
	CDMA_TASK_WRITE( (desc_conf.trs_size>>7), ADDR_OFFSET_RBDMA_TDE_CHK2_SIZE);

	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk3_base_addr", (chk_base_addr + SZ_4M*3)>>7);
	CDMA_TASK_WRITE( (chk_base_addr + SZ_4M*3)>>7, ADDR_OFFSET_RBDMA_TDE_CHK3_BASE_ADDR);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk3_size", (desc_conf.trs_size>>7));
	CDMA_TASK_WRITE( (desc_conf.trs_size>>7), ADDR_OFFSET_RBDMA_TDE_CHK3_SIZE);

	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk4_base_addr", (chk_base_addr + SZ_4M*4)>>7);
	CDMA_TASK_WRITE( (chk_base_addr + SZ_4M*4)>>7, ADDR_OFFSET_RBDMA_TDE_CHK4_BASE_ADDR);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk4_size", (desc_conf.trs_size>>7));
	CDMA_TASK_WRITE( (desc_conf.trs_size>>7), ADDR_OFFSET_RBDMA_TDE_CHK4_SIZE);

	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk5_base_addr", (chk_base_addr + SZ_4M*5)>>7);
	CDMA_TASK_WRITE( (chk_base_addr + SZ_4M*5)>>7, ADDR_OFFSET_RBDMA_TDE_CHK5_BASE_ADDR);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk5_size", (desc_conf.trs_size>>7));
	CDMA_TASK_WRITE( (desc_conf.trs_size>>7), ADDR_OFFSET_RBDMA_TDE_CHK5_SIZE);

	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk6_base_addr", (chk_base_addr + SZ_4M*6)>>7);
	CDMA_TASK_WRITE( (chk_base_addr + SZ_4M*6)>>7, ADDR_OFFSET_RBDMA_TDE_CHK6_BASE_ADDR);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk6_size", (desc_conf.trs_size>>7));
	CDMA_TASK_WRITE( (desc_conf.trs_size>>7), ADDR_OFFSET_RBDMA_TDE_CHK6_SIZE);

	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk7_base_addr", (chk_base_addr + SZ_4M*7)>>7);
	CDMA_TASK_WRITE( (chk_base_addr + SZ_4M*7)>>7, ADDR_OFFSET_RBDMA_TDE_CHK7_BASE_ADDR);
	RLOG_INFO("%-18s : 0x%08x\r\n", "tde_chk7_size", (desc_conf.trs_size>>7));
	CDMA_TASK_WRITE( (desc_conf.trs_size>>7), ADDR_OFFSET_RBDMA_TDE_CHK7_SIZE);

	generate_rbdma_task_opt(desc_conf);
}

void generate_rbdma_chunk_opt_regular(rb_desc_t desc_conf, uint32_t stride)
{
	union rbdma_tde_chk_base_addr_msb 	chk_base_addr_msb = {0x0, };

	// chunk config
	chk_base_addr_msb.chk1_stride_msb	= 0x0;	// [40:39], chiplet??
	RLOG_INFO("\r\n%-18s : 0x%08x\r\n", "chk_base_addr_msb", chk_base_addr_msb.bits);
	CDMA_TASK_WRITE(chk_base_addr_msb.bits, ADDR_OFFSET_RBDMA_TDE_CHK_BASE_ADDR_MSB);

	RLOG_INFO("%-18s : 0x%08x\r\n", "chk_stride", stride);
	//25-0817, debug
	CDMA_TASK_WRITE(stride>>7, ADDR_OFFSET_RBDMA_TDE_CHK1_BASE_ADDR_OR_STRIDE);

	generate_rbdma_task_opt(desc_conf);
}

void rbdma_donerpt_config(uint64_t base_addr)
{
	union rbdma_global_donerpt_mst_base mst_base;
	union rbdma_tde_donerpt_mst 	donerpt_mst = {0, };
	
	mst_base.bits = base_addr>>16;
	RLOG_INFO("\r\n%-18s : 0x%08x\r\n", "donerpt_mst_base", mst_base.bits);
	CDMA_GLOBAL_WRITE(mst_base.bits, ADDR_OFFSET_RBDMA_GLOBAL_DONERPT_MST_BASE);

	donerpt_mst.offset = 0x0;
	RLOG_INFO("\r\n%-18s : 0x%08x\r\n", "tde_donerpt_mst", donerpt_mst.bits);
	CDMA_TASK_WRITE(donerpt_mst.bits, ADDR_OFFSET_RBDMA_TDE_DONERPT_MST);
}

void rbdma_cmgr_config(uint32_t cl_id, uint8_t en_done)
{
	union rbdma_global_config_cdma_opmode0 opmode0;
	union rbdma_global_rbdma_cfg_cmgr_base cmgr_base;

	opmode0.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);
	opmode0.en_cmgr_evt2 = en_done;
	CDMA_GLOBAL_WRITE(opmode0.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);

	//25-0813, for chiplet working w/ cmgr
	cmgr_base.bits = 0x1ff32000 + (cl_base[cur_cl_id]>>8);
	CDMA_GLOBAL_WRITE(cmgr_base.bits, ADDR_OFFSET_RBDMA_GLOBAL_RBDMA_CFG_CMGR_BASE);
}

void generate_error_interrupt(void)
{
	CDMA_GLOBAL_WRITE(0xffffffff, ADDR_OFFSET_RBDMA_GLOBAL_NORMALTQUEUE_STATUS);

	udelay(1);
}

void *rbdma_logmgr_dump_ptr(void)
{
	return logmgr_dump_addr;
}

void rbdma_logmgr_reset(void)
{
	union rbdma_control ctrl = { 0, };

	if (!logmgr_enabled) {
		printf("rbdma logmgr not enabled\r\n");
		return;
	}

	ctrl.enable = ctrl.reset_timer = ctrl.clear_buffer = ctrl.reset_dump = 1;
	CDMA_DPLOG_WRITE(ctrl.bits, ADDR_OFFSET_RBDMA_CONTROL);
	inv_dcache_range((uintptr_t)logmgr_dump_addr, 8 * (dump_size.size + 1));
	HBM_CTRL_WRITE_CL(cur_cl_id, 0x10000000, 0, HBM_AM_INTERVAL);
	HBM_CTRL_WRITE_CL(cur_cl_id, 0x1, 0, HBM_AM_SINGLE_EN);
}

uint32_t rbdma_logmgr_get_dump_count(void)
{
	union rbdma_dump_status dump_status;

	dump_status.bits = CDMA_DPLOG_READ(ADDR_OFFSET_RBDMA_DUMP_STATUS);

    return dump_status.dump_count;
}

uint32_t rbdma_logmgr_get_ovfl_count(void)
{
	union rbdma_status1 status1;

	status1.bits = CDMA_DPLOG_READ(ADDR_OFFSET_RBDMA_STATUS1);

	return status1.num_full;
}

uint32_t rbdma_logmgr_dump_start(uint32_t cl_id)
{
	union rbdma_config cfg = { 0, };
	union rbdma_event_mask evt_msk = { 0, };
	union rbdma_dump_dest0 dump_dest0;
	union rbdma_dump_dest1 dump_dest1 = { 0, };
	union rbdma_control ctrl = { 0, };
	uint64_t dump_dest = cl_base[cl_id];

	if (logmgr_enabled) {
		printf("rbdma logmgr alread enabled, only reset it\r\n");
		rbdma_logmgr_reset();
		return 0;
	}

	cfg.full_policy = RBDMA_CONFIG_FULL_POLICY_OVWR;
	cfg.rsln = 0;
	CDMA_DPLOG_WRITE(cfg.bits, ADDR_OFFSET_RBDMA_CONFIG);

	/*
	 * event1: rbdma task queue in
	 * event2: rbdma task queue out
	 * event4: rbdma task start
	 * event8: rbdma task done
	 */
	evt_msk.enbl_evt01 = 1;
	evt_msk.enbl_evt02 = 0; /* event2 rbdma task queue out is disabled to prevent overflow of the buffer */
	evt_msk.enbl_evt04 = 1;
	evt_msk.enbl_evt08 = 1;
	CDMA_DPLOG_WRITE(evt_msk.bits, ADDR_OFFSET_RBDMA_EVENT_MASK);

	if (!logmgr_dump_addr) {
		logmgr_dump_addr = pvPortMalloc(8 * (dump_size.size + 1));
		inv_dcache_range((uintptr_t)logmgr_dump_addr, 8 * (dump_size.size + 1));
		if (!logmgr_dump_addr) {
			printf("%s: failed to alloc dump_addr\r\n", __func__);
			return -10;
		}
	}
	printf("\nlogmgr_dump size : %d\n", (8*(dump_size.size + 1)));

	dump_dest = dump_dest + (uint64_t)logmgr_dump_addr - FREERTOS_VA_OFFSET;
	dump_dest0.bits = (uint32_t)dump_dest;
	dump_dest1.addr = (dump_dest >> 32) & RL_BITFIELD_MASK(8);

	CDMA_DPLOG_WRITE(dump_dest0.bits, ADDR_OFFSET_RBDMA_DUMP_DEST0);
	CDMA_DPLOG_WRITE(dump_dest1.bits, ADDR_OFFSET_RBDMA_DUMP_DEST1);

	ctrl.enable = ctrl.reset_timer = ctrl.clear_buffer = ctrl.reset_dump = 1;
	CDMA_DPLOG_WRITE(ctrl.bits, ADDR_OFFSET_RBDMA_CONTROL);

	logmgr_enabled = true;
	rbdma_logmgr_reset();
	return 0;
}

void rbdma_logmgr_dump_detail(void)
{
#ifdef PERF_DETAIL
	uint32_t logmgr_dump_count = 0;
	struct log_mgr_entry *entry = (struct log_mgr_entry *)rbdma_logmgr_dump_ptr();

	logmgr_dump_count = rbdma_logmgr_get_dump_count();

	printf("logmgr dump count : %d\r\n", logmgr_dump_count);
	for(int i = 0; i < logmgr_dump_count; i++){
		printf("exec_id : %08x\n", entry[i].exec_id);
		printf("evt_code : %d\n", entry[i].evt_code);
		printf("cycle_cnt : %d\n", entry[i].cycle_cnt);
	}
#endif
}

void rbdma_logmgr_exec_time(uint32_t method)
{
	uint32_t logmgr_dump_count = 0;
	struct log_mgr_entry *entry = (struct log_mgr_entry *)rbdma_logmgr_dump_ptr();

	logmgr_dump_count = rbdma_logmgr_get_dump_count();

	printf("Task execution cycle count(NOC clk)\n");
	if (method == 0) {
		for(int i = 0; i < logmgr_dump_count/2; i++){
			printf("%d\n", entry[i*2+1].cycle_cnt - entry[i*2].cycle_cnt);
		}
	}
	else if (method == 1) {
		for(int i = 0; i < logmgr_dump_count/4; i++){
			printf("%d\n", entry[i*4+3].cycle_cnt - entry[i*4].cycle_cnt);
		}
	}
}

uint32_t rbdma_done_count(void)
{
	return CDMA_DPLOG_READ(ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC0);
}

uint32_t rbdma_done_count_cl(int cl_id)
{
	return CDMA_DPLOG_READ_CL(cl_id, ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC0);
}
uint32_t rbdma_global_normal_queue_status_cl(int cl_id)
{
	//printf("clid: %d\r\n", cl_id);
	//printf("cl_base: %llx\r\n", cl_base[cl_id]);
	return CDMA_GLOBAL_READ_CL(cl_id, ADDR_OFFSET_RBDMA_GLOBAL_NORMALTQUEUE_STATUS);
}

uint32_t rbdma_global_idle_status_cl(int cl_id)
{
	return CDMA_GLOBAL_READ_CL(cl_id, ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_INT);
}

void rbdma_autofetch_run_proc0(uint64_t base_addr, uint32_t size)
{
	union rbdma_global_config_cdma_opmode0 opmode0;

    opmode0.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);
    opmode0.en_auto_fetch = 1;
    CDMA_GLOBAL_WRITE(opmode0.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);

    union rbdma_global_config_cdma_opmode1 opmode1;
    opmode1.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE1);
    opmode1.af_tdq_watermark = 0x3e;
    CDMA_GLOBAL_WRITE(opmode1.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE1);

    union rbdma_proc0_ptr proc0_ptr = {0, };
    proc0_ptr.header = (uint32_t)(base_addr & 0xffffffff);
    CDMA_AUTO_FETCH_WRITE(proc0_ptr.bits, ADDR_OFFSET_RBDMA_PROC0_PTR);

    union rbdma_proc0_ptr_bytesize proc0_ptr_bytesize = {0, };
    proc0_ptr_bytesize.msb_ptr = (uint32_t)(base_addr >> 32 & 0xff);
    proc0_ptr_bytesize.size = size;
    CDMA_AUTO_FETCH_WRITE(proc0_ptr_bytesize.bits, ADDR_OFFSET_RBDMA_PROC0_PTR_BYTESIZE);

    //CDMA_AUTO_FETCH_WRITE(0x80000004, 0x8); // proc0_run
}

void rbdma_autofetch_run_proc1(uint64_t base_addr, uint32_t size)
{
	union rbdma_global_config_cdma_opmode0 opmode0;

    opmode0.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);
    opmode0.en_auto_fetch = 1;
    CDMA_GLOBAL_WRITE(opmode0.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);

    union rbdma_global_config_cdma_opmode1 opmode1;
    opmode1.bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE1);
    opmode1.af_tdq_watermark = 0x3e;
    CDMA_GLOBAL_WRITE(opmode1.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE1);

    union rbdma_proc1_ptr proc1_ptr = {0, };
    proc1_ptr.header = (uint32_t)(base_addr & 0xffffffff);
    CDMA_AUTO_FETCH_WRITE(proc1_ptr.bits, ADDR_OFFSET_RBDMA_PROC1_PTR);

    union rbdma_proc1_ptr_bytesize proc1_ptr_bytesize = {0, };
    proc1_ptr_bytesize.msb_ptr = (uint32_t)(base_addr >> 32 & 0xff);
    proc1_ptr_bytesize.size = size;
    CDMA_AUTO_FETCH_WRITE(proc1_ptr_bytesize.bits, ADDR_OFFSET_RBDMA_PROC1_PTR_BYTESIZE);

    //CDMA_AUTO_FETCH_WRITE(0x80000004, 0x18); // proc0_run
}

uint32_t get_rbdma_proc0_status(){
    union rbdma_proc0_status proc0_status = {0, };
    proc0_status.bits = CDMA_AUTO_FETCH_READ(ADDR_OFFSET_RBDMA_PROC0_STATUS);
    return proc0_status.bits;
}

uint32_t get_rbdma_clog_num_nrm_tdone_tstc0(){
    union rbdma_clog_num_nrm_tdone_tstc0 tstc0 = {0, };
    tstc0.bits = CDMA_DPLOG_READ(ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC0);
    return tstc0.bits;
}

uint32_t rbmda_get_global_status_cdma_int(){
    return CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_STATUS_CDMA_INT);
}

/* SSW-2844 */
#define RBDMA_RESTRICT_TASK_CREDIT	52

void rbdma_update_credit(uint8_t *task_credit, uint8_t *task_ext_credit, bool normal_qtype)
{
	if (normal_qtype) {
		*task_credit = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_NORMALTQUEUE_STATUS);
		*task_ext_credit = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_NORMALTQUEUE_EXT_STATUS);

		*task_credit = MIN(*task_credit, RBDMA_RESTRICT_TASK_CREDIT);
	} else {
		*task_credit = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_URGENTTQUEUE_STATUS);
		*task_ext_credit = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_URGENTTQUEUE_EXT_STATUS);
	}
}
