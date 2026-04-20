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
#include "hal/cmgr_if.h"
#include "gic.h"
#include "system_api.h"
#include "rbln/cache.h"
#include "cmgr_regs.h"
#include "g_sys_addrmap.h"
#include "rl_utils.h"
#include "rbln/abort.h"
#include "rl_sizes.h"
#include "rbln/log.h"
#include "rbln/rebel.h"
#include "hal/addr_map.h"
#include "hal/interrupt.h"
#include "hal/hw_spec.h"
#include "rl_errors.h"
#include "sys_command_line.h"
#include "common/debug.h"

static uint64_t cmgr_base = NBUS_U_CMD_MGR_BASE;

#define CMGR_CONFIG			(cmgr_base + ADDR_OFFSET_CMGR_CONFIG)
#define CMGR_CMD_EVENT		(cmgr_base + ADDR_OFFSET_CMGR_CMD_EVENT)
#define CMGR_QUEUE_CTL		(cmgr_base + ADDR_OFFSET_CMGR_QUEUE_CTL)
#define CMGR_STAT           (cmgr_base + ADDR_OFFSET_CMGR_STAT)
#define CMGR_QUEUE_STAT     (cmgr_base + ADDR_OFFSET_CMGR_QUEUE_STAT)
#define CMGR_QUEUE          (cmgr_base + ADDR_OFFSET_CMGR_QUEUE)

#define CMGR_CONFIG_WRITE(val, offset)  rl_writel_relaxed(val, (void *)(CMGR_CONFIG + offset))
#define CMGR_CONFIG_READ(offset)        rl_readl_relaxed((void *)(CMGR_CONFIG + offset))

#define CMGR_QUEUE_CTL_WRITE(val, offset)   rl_writel_relaxed(val, (void *)(CMGR_QUEUE_CTL + offset))
#define CMGR_QUEUE_CTL_READ(offset)        rl_readl_relaxed((void *)(CMGR_QUEUE_CTL + offset))

#define CMGR_CMD_EVENT_WRITE(val, offset)   rl_writel_relaxed(val, (void *)(CMGR_CMD_EVENT + offset))
#define CMGR_CMD_EVENT_READ(offset)        rl_readl_relaxed((void *)(CMGR_CMD_EVENT + offset))

#define CMGR_TASK_WRITE(val, offset)        rl_writeq_relaxed(val, (void *)(CMGR_CMD_EVENT + offset))

// temporally
uint32_t tmp_cmgr_status = 0;

static void cmgr_adjust_base(uint32_t cl_id)
{
	RLOG_DBG("adjust cmgr address clid: %d\r\n", cl_id);
	cmgr_base = cl_base[cl_id] + NBUS_U_CMD_MGR_BASE;
}

/* Reading the entire register will clear the interrupt  */
void cmgr_done_handler(void *data)
{
	union cmgr_config_intr_status_0     intr_status_0 = {0, };
	union cmgr_config_intr_status_1     intr_status_1 = {0, };

    intr_status_0.bits  = CMGR_CONFIG_READ(ADDR_OFFSET_CMGR_CONFIG_INTR_STATUS_0);
    tmp_cmgr_status     = intr_status_0.bits;
    RLOG_INFO("%-18s : %x\r\n", "[cmgr]intr_status_0", intr_status_0.bits);
    if (intr_status_0.intr_type == 0x1) {
        #if defined(INDICATOR_DEBUG_MODE)
            TEST_GPD2_DAT |= 0x1;	// trigger GPD2[0]
        #endif /* #if defined(INDICATOR_DEBUG_MODE) */

        printf("%-18s : intr_flag:%x\r\n", "[ERROR]intr_status_0", intr_status_0.intr_flag);
        printf("%-18s : intr_subinfo:%x\r\n", "[ERROR]intr_status_0", intr_status_0.intr_subinfo);
        printf("%-18s : intr_src:%x\r\n", "[ERROR]intr_status_0", intr_status_0.intr_src);
        // [16], [27:24], [31:28]
    }
    intr_status_1.bits  = CMGR_CONFIG_READ(ADDR_OFFSET_CMGR_CONFIG_INTR_STATUS_1);
    RLOG_INFO("%-18s : %x\r\n", "[cmgr]intr_status_1", intr_status_1.bits);
}

void cmgr_workload_converter_init(){
    union cmgr_config_config    config = {0, };
    config.acc_cnt_en    = 1;
    CMGR_CONFIG_WRITE(config.bits, ADDR_OFFSET_CMGR_CONFIG_CONFIG);

    union cmgr_queue_ctlqueue_0_0 ctlqueue = {0, };
    ctlqueue.bits = CMGR_QUEUE_CTL_READ(ADDR_OFFSET_CMGR_QUEUE_CTLQUEUE_0_0);
    ctlqueue.queue_en = 1;
    CMGR_QUEUE_CTL_WRITE(ctlqueue.bits, ADDR_OFFSET_CMGR_QUEUE_CTLQUEUE_0_0);
    
}

void cmgr_init(uint32_t cl_id)
{
    cmgr_adjust_base(cl_id);

    union cmgr_config_config    config = {0, };

    //25-0811, it need set w/ global id??
    union cmgr_config_ip_info2  global_id = {0, };

    global_id.bits = cl_id;
    CMGR_CONFIG_WRITE(global_id.bits, ADDR_OFFSET_CMGR_CONFIG_IP_INFO2);

    //25-0812, u have to set, this field on quad chiplet base
    config.noti_chiplet_base_addr_mode  = 1;
    config.acc_cnt_en    = 1;
    CMGR_CONFIG_WRITE(config.bits, ADDR_OFFSET_CMGR_CONFIG_CONFIG);

  	gic_irq_connect(INT_ID_CMGR, cmgr_done_handler, 0);
	gic_irq_enable_dedicated_core(0, INT_ID_CMGR);
}

void cmgr_config(cmgr_desc_t desc_conf)
{
    union cmgr_queue_ctlqueue_0_0   ctlqueue_0_0 = {0, };
    union cmgr_cmd_event_cmd_info_id    cmd_info_id = {0, };
    union cmgr_cmd_event_cmd_info_affinity  cmd_info_affinity = {0, };
    union cmgr_cmd_event_cmd_info_notification  cmd_info_noti = {0, };
    union cmgr_cmd_event_cmd_info_control   cmd_info_control = {0, };

    // queue en
    ctlqueue_0_0.queue_en   = 0x1;
    CMGR_QUEUE_CTL_WRITE(ctlqueue_0_0.bits, ADDR_OFFSET_CMGR_QUEUE_CTLQUEUE_0_0);
    RLOG_INFO("%-18s : 0x%08x\r\n", "ctlqueue_0_0", ctlqueue_0_0.bits);

    cmd_info_id.cmd_id      = desc_conf.cmd_id;
    CMGR_CMD_EVENT_WRITE(cmd_info_id.bits, ADDR_OFFSET_CMGR_CMD_EVENT_CMD_INFO_ID);
    RLOG_INFO("%-18s : 0x%08x\r\n", "cmd_id", cmd_info_id.bits);

    cmd_info_affinity.bits  = desc_conf.affinity;
    CMGR_CMD_EVENT_WRITE(cmd_info_affinity.bits, ADDR_OFFSET_CMGR_CMD_EVENT_CMD_INFO_AFFINITY);
    RLOG_INFO("%-18s : 0x%08x\r\n", "cmd_affinity", cmd_info_affinity.bits);

    cmd_info_noti.target    = desc_conf.notification;  // dncx16, rbdma
    cmd_info_noti.event_code_dnc        = desc_conf.event_code_dnc;
    cmd_info_noti.event_group_idx_dnc   = desc_conf.event_group_idx_dnc;
    CMGR_CMD_EVENT_WRITE(cmd_info_noti.bits, ADDR_OFFSET_CMGR_CMD_EVENT_CMD_INFO_NOTIFICATION);
    RLOG_INFO("%-18s : 0x%08x\r\n", "cmd_noti", cmd_info_noti.bits);

    cmd_info_control.event_group_idx_rbdma  = desc_conf.event_group_idx_rbdma;
    cmd_info_control.cmd_type               = desc_conf.cmd_type;    
    CMGR_CMD_EVENT_WRITE(cmd_info_control.bits, ADDR_OFFSET_CMGR_CMD_EVENT_CMD_INFO_CONTROL);
    RLOG_INFO("%-18s : 0x%08x\r\n\r\n", "cmd_control", cmd_info_control.bits);
}

int cmgr_display_status(void)
{
    union cmgr_config_intr_status_0     intr_status_0 = {0, };

    intr_status_0.bits  = tmp_cmgr_status;

    RLOG_INFO("--------------------------------------------------\r\n");
    RLOG_INFO("%-15s : 0x%0x\r\n", "intr_type", intr_status_0.intr_type);
    RLOG_INFO("%-15s : 0x%0x\r\n", "intr_cnt", intr_status_0.intr_cnt);
    RLOG_INFO("%-15s : 0x%0x\r\n", "intr_flag", intr_status_0.intr_flag);
    RLOG_INFO("%-15s : 0x%0x\r\n", "intr_subinfo", intr_status_0.intr_subinfo);
    RLOG_INFO("%-15s : 0x%0x\r\n", "intr_src", intr_status_0.intr_src);
    RLOG_INFO("--------------------------------------------------\r\n");

    if(intr_status_0.intr_type == 0x2){
        RLOG_INFO("\r\nnotification generate!!\r\n");
    
        return true;
    }    

    RLOG_INFO("Check CDMA dbg_tsync register 0x1ff3702000 ~ \r\n");
    RLOG_INFO("Check CMGR STAT register (tcnt) 0x1ff3200a00 ~ \r\n");
    RLOG_INFO("Check CMGR STAT register (noti) 0x1ff3200b80 ~ \r\n");

    return false;
}

void cmgr_acc_count_clear(void)
{
    union cmgr_config_ctl     config_ctl = {0, };

    config_ctl.acc_cnt_clr = 1;
    CMGR_CONFIG_WRITE(config_ctl.bits, ADDR_OFFSET_CMGR_CONFIG_CTL);
}

void cmgr_autofetch_run(uint64_t af_str_addr, uint32_t af_size){

    union cmgr_queue_ctlqueue_0_afl0_0 afl0_0 = {0, };
    afl0_0.af_str_addr = af_str_addr >> 8;
    CMGR_QUEUE_CTL_WRITE(afl0_0.bits, ADDR_OFFSET_CMGR_QUEUE_CTLQUEUE_0_AFL0_0);

    union cmgr_queue_ctlqueue_0_afl0_1 afl0_1 = {0, };
    afl0_1.af_size = af_size;
    afl0_1.af_credit = 0x200;
    CMGR_QUEUE_CTL_WRITE(afl0_1.bits, ADDR_OFFSET_CMGR_QUEUE_CTLQUEUE_0_AFL0_1);

    union cmgr_queue_ctlqueue_0_0 queue_0_0 = {0, };
    queue_0_0.bits = CMGR_QUEUE_CTL_READ(ADDR_OFFSET_CMGR_QUEUE_CTLQUEUE_0_0);
    queue_0_0.af_en = 1;
    CMGR_QUEUE_CTL_WRITE(queue_0_0.bits, ADDR_OFFSET_CMGR_QUEUE_CTLQUEUE_0_0);

    union cmgr_config_config config = {0, };
    config.bits = CMGR_CONFIG_READ(ADDR_OFFSET_CMGR_CONFIG_CONFIG);
    config.af_en = 1;
    CMGR_CONFIG_WRITE(config.bits, ADDR_OFFSET_CMGR_CONFIG_CONFIG);
}

