/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2023 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _DNC_IF_H_
#define _DNC_IF_H_

#include <stdio.h>
#include <stdbool.h>

#define DNC_PROFILE_BASE_ADDR_LOW	(0x10000000UL)
#define DNC_PROFILE_BASE_ADDR_HIGH	(0x7UL)
#define DNC_PROFILE_MSG_SIZE	(0x100000)	//1MB, 16 x num per dnc

enum dnc_ip_ver {
	DNC_V0_0 = 0,	/* in REBEL_H PREVERSION */
	DNC_V1_0,		/* in REBEL_H EVT0 */
	DNC_V1_1,		/* in REBEL_H EVT1 */
};

typedef struct {
	uint8_t		tsync_chk_mode;
	uint8_t		tsync_chk_code;
	uint8_t		tsync_chk_group;
	uint8_t		tsync_chk_clr;
	uint8_t		tsync_set_mode;
	uint8_t 	tsync_set_code;
	uint8_t		tsync_set_group;
	uint8_t		target_dnc_id;

} __attribute__((packed)) DescTsyncInfo;

typedef struct {
	uint8_t		done_policy;
	uint16_t	dcrn_offset_addr;
	uint16_t	dcrn_size;
	uint16_t	uan_offset_addr;
	uint16_t	uan_size;
	uint64_t	dest_addr;
	uint32_t	stride;
	uint32_t	cdump_component;
	uint8_t		reserved[3];

} __attribute__((packed)) CdumpInfo_t;

int dnc_init(uint32_t cl_id);

extern struct dnc_ops {
	void (*init)(uint32_t dnc_id);
	uint64_t (*get_irq_status)(uint32_t dnc_id, void *done_passage);
} dnc_ops;

/*
 * table naming rule: COMP_TLB_TABLE_TYPE_DCL{TGT_DCL}_{DCL_NUM}_{DCL_DIR}
 * TGT_DCL: target DCL, DCL01 means this table used for both DCL0 and 1.
 * DCL_NUM: target DCL num, 2 means this table used for dual DCL workloads.
 * DCL_DIR: NORMAL or CROSS, CROSS means that virtual address for DCL0/1 use
 * physical address for DCL1/0.
 * detailed address mapping like below:
 * table_type == COMP_TLB_TABLE_TYPE_DCL01_2_NORMAL
 *	spm: va 0~64MB		-> PA 0x1F_E000_0000(DCL0, DCL1: 64MB)
 *	shm: va 64MB~128MB	-> PA 0x1F_E400_0000(DCL0, DCL1: 64MB)
 * table_type == COMP_TLB_TABLE_TYPE_DCL01_2_CROSS
 *	spm: va 0~32MB (DCL0)	-> PA 0x1F_E0x00_0000(DCL0: 32MB)
 *	spm: va 0~32MB (DCL1)	-> PA 0x1F_E200_0000(DCL1: 32MB)
 *	shm: va 64MB~128MB	-> PA 0x1F_E400_0000(DCL0, DCL1: 64MB)
 * table_type == COMP_TLB_TABLE_TYPE_DCL0_1_NORMAL
 *  spm va 0~32MB	-> 0x1F_E000_0000~0x1F_E200_0000(DCL0: 32MB)
 *  shm va 64~96MB	-> 0x1F_E400_0000~0x1F_E600_0000(DCL0: 32MB)
 * table_type == COMP_TLB_TABLE_TYPE_DCL1_1_CROSS
 *  spm va 0~32MB	-> 0x1F_E2000000~0x1F_E400_0000(DCL1: 32MB)
 *  shm va 64~96MB	-> 0x1F_E6000000~0x1F_E800_0000(DCL1: 32MB)
 */
enum comp_tlb_table_type {
	COMP_TLB_TABLE_TYPE_DCL01_2_NORMAL = 0,
	COMP_TLB_TABLE_TYPE_DCL01_2_CROSS,
	COMP_TLB_TABLE_TYPE_DCL0_1_NORMAL,
	COMP_TLB_TABLE_TYPE_DCL1_1_CROSS,
};

enum task16b_type {
	CLEAR 	= 1,
	SETREG,
	COMP_16B,
	LDUDMA_16B,
	LPUDMA_16B,
	STUDMA_16B,
	NWR,
	PWR,
	CDUMP,
};

/* done report mode */
enum dnc_autofetch_cmgr_mode {
	DNC_AUTOFETCH_MODE_REPORT_OFF = 0,
	DNC_AUTOFETCH_MODE_1 = 1,
	DNC_AUTOFETCH_MODE_2 = 2,
};

/* task fetch mode */
enum dnc_autofetch_task_fetch_mode {
	DNC_AUTOFETCH_TASK_FETCH_MODE_OFF = 0,
	DNC_AUTOFETCH_TASK_FETCH_MODE_1 = 1,	/* legacy mode */
	DNC_AUTOFETCH_TASK_FETCH_MODE_2 = 2,	/* self-task fetch mode */
};

typedef struct{
	uint32_t task_id;
	uint16_t queuing_time;
	uint64_t pre_time;
	uint64_t run_time;
} __attribute__((packed)) profile_time_t;

int dnc_run_sp_test(int dnc_id, uint32_t pattern);
int dnc_sp_mode_test(uint32_t pattern, uint8_t mode);
int dnc_sp_test_mode_trigger(void);
int dnc_sp_test_mode_check(void);

void dnc_config_comp_tlb_init(uint8_t dnc_id);
void dnc_done_acc_count_all_clear(uint8_t cl_id);
void dnc_done_acc_count_clear(uint8_t dnc_id);
void dnc_done_accumulate_count(int dnc_id, uint32_t cmd, uint32_t count);
void dnc_all_clear(uint8_t cl_id);
//void dnc_reset(uint8_t dnc_id);
int dnc_check_slot_mask(int slot);
int dnc_detect_slot(uint64_t address);
void dnc_display_profile(uint8_t dnc_id);
void dnc_clear_profile_log(void);
void dnc_sync_passage_reg_clear(uint8_t dnc_id);

uint8_t dnc_skew_set(int argc, char *argv[]);
void dnc_skew_delay(uint8_t dnc_id, uint8_t delay);
int posted_write_test(uint32_t cl_id);
void pwr_config(uint8_t dnc_id, uint64_t addr, uint32_t data);
uint8_t comp_tlb_interleaving(int argc, char *argv[]);

int dnc_checksum(int dnc_id, uint32_t addr, uint32_t size);
void dnc_tlb_update(uint8_t dnc_id, uint8_t tlb_idx, uint8_t cmd, uint64_t addr, uint8_t bl);
void generate_udma_task(uint8_t dnc_id, uint8_t cmd, uint64_t src_addr, uint64_t dst_addr, uint32_t trs_size);
void generate_udma_task_opt(uint8_t dnc_id, uint8_t cmd, uint64_t src_addr, uint64_t dst_addr, uint32_t trs_size, DescTsyncInfo *tsync_info);
void timeout_config(uint8_t dnc_id, uint8_t mode, uint64_t threshold);

void apply_multicyle(int dnc_id);
void read_secded_status(void);
void measure_backpressue(int dnc_id);
void test_cdump_mode(void);

void dnc_sp_test_status(int dnc_id);
void dnc_get_status_registers(void);
void dnc_rpt_mode_config(int mode);
void dnc_cdump_mode(CdumpInfo_t	cinfo);

#define DNC_PROFILE_PTR(x) dnc_profile_ptr(x)
void* dnc_profile_ptr(int dnc_id);

#define DNC_PROFILE_GET_COUNT(x) dnc_profile_get_count(x)
uint32_t dnc_profile_get_count(int dnc_id);

uint32_t dnc_comp_done_count(int dnc_id);
uint32_t dnc_ldudma_done_count(int dnc_id);

void dnc_comp_rpt_mode_config(int mode);
void dnc_ldudma_rpt_mode_config(int mode);

uint32_t dnc_get_q_status();

void dnc_autofetch_cmgr(enum dnc_autofetch_cmgr_mode mode);
void dnc_autofetch_config(enum dnc_autofetch_task_fetch_mode mode);
void dnc_selffetch_config(enum dnc_autofetch_task_fetch_mode mode, uint8_t cmd_type, uint32_t task_count);
void dnc_autofetch_invoke(int cmd);
void dnc_selffetch_invoke(int cmd);
void preload_comp_task(int iter);
void dnc_autofetch_addr_reset(void);
void dnc_wr_arbitration_config(void);
void dnc_tlb_preload(uint8_t dnc_id, uint8_t clr_type, uint32_t value);
void dnc_update_credit(int dnc_id, uint8_t *comp_credits, uint8_t *udma_credits,
	uint8_t *lpudma_credits, uint8_t *studma_credits);
#endif /* _DNC_IF_H_ */
