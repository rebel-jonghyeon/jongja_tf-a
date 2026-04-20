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

#ifndef _RBDMA_IF_H_
#define _RBDMA_IF_H_

#include <stdbool.h>

typedef struct{
	uint32_t	task_id;		
	uint64_t    src_addr;
    uint64_t    dst_addr;
    uint32_t    trs_size;
    uint8_t     task_type;
    uint8_t     te_mask;
    uint8_t     read_bl;
    uint8_t     write_bl;
    uint8_t     read_qos;
    uint8_t     write_qos;
    uint8_t     en_invalid_pt;
    uint8_t     no_tlb;
    uint32_t    num_of_chunk;
    uint8_t     split_granule_l2;
    uint8_t     intr_disable;
    uint8_t     en_donerpt_mst;
    uint16_t    get_dnc_mask;
    uint8_t     get_tsync_gidx;
    uint8_t     get_tsync_en;
    uint8_t     reserved;
} __attribute__((packed)) rb_desc_t;


#define RBDMA_PROFILE_BASE_ADDR_LOW	(0x0UL)
#define RBDMA_PROFILE_BASE_ADDR_HIGH	(0x8UL)
#define RBDMA_PROFILE_BASE_ADDR ((RBDMA_PROFILE_BASE_ADDR_HIGH) << 32 | (RBDMA_PROFILE_BASE_ADDR_LOW))
#define RBDMA_PROFILE_MSG_SIZE	(0x100000)	//1MB

void rbdma_init(uint32_t cl_id);
void rbdma_done_acc_count(uint32_t cl_id, uint32_t count);
void rbdma_done_clear(uint32_t cl_id);

void generate_rbdma_task(uint32_t task_id, uint64_t src_addr, uint64_t dst_addr, uint32_t trs_size, uint8_t task_type);
void generate_rbdma_perf_task(uint32_t task_id, uint64_t src_addr, uint64_t dst_addr, uint32_t transfer_size, uint8_t te_affinity, uint32_t split_granule, uint8_t task_type);
void generate_rbdma_task_tsync(uint32_t task_id, uint64_t src_addr, uint64_t dst_addr, uint32_t transfer_size, uint32_t split_granule, uint8_t task_type, uint32_t te_mask, uint32_t is_tsync);
uint32_t rbdma_set_max_perf_mode(uint32_t sp_ratio);
uint32_t rbdma_get_global_config_cdma_opmode0(void);
void rbdma_set_global_config_cdma_opmode0(uint32_t bits);
void rbdma_tsync_by_cp(void);
void generate_rbdma_task_opt(rb_desc_t desc_conf);
void generate_rbdma_chunk_opt(rb_desc_t desc_conf);
void generate_rbdma_chunk_opt_regular(rb_desc_t desc_conf, uint32_t stride);
void rbdma_donerpt_config(uint64_t base_addr);
void generate_error_interrupt(void);
void rbdma_cmgr_config(uint32_t cl_id, uint8_t en_done);

void rbdma_enable_profile_mode();

void *rbdma_logmgr_dump_ptr(void);
void rbdma_logmgr_reset(void);
uint32_t rbdma_logmgr_get_dump_count(void);
uint32_t rbdma_logmgr_get_ovfl_count(void);
static inline uint32_t rbdma_logmgr_store(void)	{ return 0; }
uint32_t rbdma_logmgr_dump_start(uint32_t cl_id);
void rbdma_logmgr_dump_detail(void);
void rbdma_logmgr_exec_time(uint32_t method);
uint32_t rbdma_done_count(void);
uint32_t rbdma_done_count_cl(int cl_id);
uint32_t rbdma_global_normal_queue_status_cl(int cl_id);
uint32_t rbdma_global_idle_status_cl(int cl_id);

void rbdma_autofetch_run_proc0(uint64_t base_addr, uint32_t size);
void rbdma_autofetch_run_proc1(uint64_t base_addr, uint32_t size);

uint32_t get_rbdma_proc0_status();
uint32_t get_rbdma_clog_num_nrm_tdone_tstc0();

uint32_t rbmda_get_global_status_cdma_int();

void hbm_activity_monitor(uint32_t cl_id, uint32_t ch);

void rbdma_update_credit(uint8_t *task_credit, uint8_t *task_ext_credit, bool normal_qtype);

#endif /* _RBDMA_IF_H_ */
