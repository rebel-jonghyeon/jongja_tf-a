/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2025 [Rebellions Inc.], All Rights Reserved.
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

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "g_sysfw_addrmap.h"
#include "autogen/g_sys_addrmap.h"
#include "sys_command_line.h"
#include "hal/rbdma_if.h"
#include "hal/dnc_if.h"
#include "hal/shm_if.h"
#include "hal/rdsn_if.h"
#include "hal/interrupt.h"
#include "rbln/log.h"
#include "rl_utils.h"
#include "rl_sizes.h"
#include "common/command.h"
#include "common/page_table_gen.h"
#include "replay.h"
#include "rbln/rebel.h"
#include "common_test.h"
#include "rl_errors.h"
#include "common_test.h"
#include "core_timer.h"
#include "system_api.h"
#include "rbln/core.h"
#include "rbln/rand.h"

extern uint32_t dnc_cdump_flag;

tlb_set_t	ldtlb_info[HW_SPEC_DNC_COUNT];
tlb_set_t	lptlb_info[HW_SPEC_DNC_COUNT];
tlb_set_t	sttlb_info[HW_SPEC_DNC_COUNT];

#ifndef DRAM_SIZE_PER_CL
#define DRAM_SIZE_PER_CL (DRAMEXTENDEDBASE - DRAMUSERREGIONBASE)
#endif

static void rbdma_gpio_drive(int src_cl, bool asserted)
{
    static const uintptr_t gpio_con_addrs[] = {
        0x1ff3530060ULL,
        0x3ff3530060ULL,
        0x5ff3530060ULL,
        0x7ff3530060ULL,
    };
    static const uintptr_t gpio_dat_addrs[] = {
        0x1ff3530064ULL,
        0x3ff3530064ULL,
        0x5ff3530064ULL,
        0x7ff3530064ULL,
    };

    if (src_cl < 0 || src_cl >= (int)(sizeof(gpio_dat_addrs) / sizeof(gpio_dat_addrs[0])))
        return;

    volatile uint32_t *con = (volatile uint32_t *)gpio_con_addrs[src_cl];
    volatile uint32_t *dat = (volatile uint32_t *)gpio_dat_addrs[src_cl];

    *con = 0x00100000U;
    *dat = asserted ? 0x3eU : 0x1eU;
}

static bool addr_in_range(uint64_t addr, uint64_t base, uint64_t size)
{
    return (addr >= base) && (addr < (base + size));
}

static bool is_shm_addr(uint64_t addr)
{
    for (uint32_t i = 0; i < MAX_CHIPLET_COUNT; i++) {
        uint64_t base = cl_base[i];

        if (addr_in_range(addr, base + DCL0_SH_MEM_BASE, RL_SHM_SIZE) ||
            addr_in_range(addr, base + DCL1_SH_MEM_BASE, RL_SHM_SIZE))
            return true;
    }

    return false;
}

static int get_chip_id_from_addr(uint64_t addr)
{
    for (uint32_t i = 0; i < MAX_CHIPLET_COUNT; i++) {
        uint64_t base = cl_base[i];

        if (addr_in_range(addr, base + DRAMUSERREGIONBASE, DRAM_SIZE_PER_CL) ||
            addr_in_range(addr, base + DCL0_SH_MEM_BASE, RL_SHM_SIZE) ||
            addr_in_range(addr, base + DCL1_SH_MEM_BASE, RL_SHM_SIZE) ||
            addr_in_range(addr, base + DCL0_SP_MEM_BASE, RL_SPM_SIZE) ||
            addr_in_range(addr, base + DCL1_SP_MEM_BASE, RL_SPM_SIZE))
            return i;
    }

    return RL_ERROR;
}

void dummy_function(void)
{
    printf("aaa");
}

void tlb_table_init(void)
{
    memset(&ldtlb_info, 0x0, sizeof(tlb_set_t)*HW_SPEC_DNC_COUNT);
    memset(&lptlb_info, 0x0, sizeof(tlb_set_t)*HW_SPEC_DNC_COUNT);
    memset(&sttlb_info, 0x0, sizeof(tlb_set_t)*HW_SPEC_DNC_COUNT);
}

/**
 * @brief 대역폭 측정을 시작합니다.
 * @return 측정 시작 시점의 CPU cycle 값
 */
uint64_t bw_measure_start(void)
{
	rl_cpu_enable_cycle();
	return rl_cpu_read_cycle();
}

/**
 * @brief 대역폭 측정을 종료하고 결과를 출력합니다.
 * @param start_cycle 측정 시작 시점의 CPU cycle 값
 * @param total_bytes 전송된 총 바이트 수
 * @param cpu_freq CPU 주파수 (Hz), 기본값 2000000000ULL (2GHz)
 * @param print_bw true이면 GB/s를 출력, false이면 출력하지 않음
 */
void bw_measure_end_and_print(uint64_t start_cycle,
	uint64_t total_bytes, uint64_t cpu_freq, int print_bw)
{
	uint64_t end_cycle = rl_cpu_read_cycle();
	uint64_t duration_cycles = end_cycle - start_cycle;
	uint64_t duration_ns = (duration_cycles * 1000000000ULL) / cpu_freq;

//	printf("\r\nstart_cycle: %llu, end_cycle: %llu\r\n", start_cycle, end_cycle);
	if (print_bw) {
		/* GB/s = (bytes transferred) / (duration in seconds) / (10^9 bytes/GB)
		 * duration_ns is in nanoseconds, so divide by 10^9 to get seconds,
		 * then divide by 10^9 to convert bytes to GB
		 * Formula: (total_bytes) / (duration_ns / 10^9) / 10^9
		 * = (total_bytes * 10^9) / duration_ns
		 * To maintain precision, multiply first then divide
		 */
		uint64_t bandwidth_gbs = 0;

		if (duration_ns > 0) {
			/* Calculate(GByte): total_bytes / duration_ns
			 * This gives GB/s directly without intermediate
			 * divisions that lose precision
			 */
			bandwidth_gbs = total_bytes / duration_ns;
		}
		printf("Execution time: %llu cycles (%llu ns) - %llu GB/s\r\n",
			duration_cycles, duration_ns, bandwidth_gbs);
	} else {
		printf("Execution time: %llu cycles (%llu ns)\r\n", duration_cycles, duration_ns);
	}

	rl_cpu_disable_cycle();
}

/* the studma nees to bl config when the transfer has far area. */
int insert_or_find_tlb(uint8_t dnc_id, uint8_t cmd, uint64_t addr, uint32_t size)
{
	uint8_t bl = 0;
	uint32_t cnt = 0;
	const uint32_t start_idx = ((uint64_t)addr >> 21);
	const uint32_t end_idx = (addr + size + PAGE_SIZE_2MB - 1) >> 21;
	uint64_t cl_base = cur_cl_id * CHIPLET_OFFSET;
	uint64_t cl_end = cl_base + CHIPLET_OFFSET - 1;

	if (addr < cl_base || addr > cl_end) {
		bl = 3;
	} else if ((addr & 0x1FFFFFFFFF) < DCL0_SP_MEM_BASE) {
		bl = 3;
	} else {
		/*
		 * if the destination address is within its own cluster, bl1(0) otherwise bl8(3)
		 */
		if (cmd == STuDMA) {
			if (dnc_id < HW_SPEC_DNC_COUNT / 2) {
				if (((addr >= DCL0_SP_MEM_BASE_CL) &&
					(addr < (DCL0_SP_MEM_BASE_CL + SZ_32M))) ||
					((addr >= DCL0_SH_MEM_BASE_CL) &&
					(addr < (DCL0_SH_MEM_BASE_CL + SZ_32M))))
					bl = 0;
				else
					bl = 3;
			} else {
				if (((addr >= DCL1_SP_MEM_BASE_CL) &&
					(addr < (DCL1_SP_MEM_BASE_CL + SZ_32M))) ||
					((addr >= DCL1_SH_MEM_BASE_CL) &&
					(addr < (DCL1_SH_MEM_BASE_CL + SZ_32M))))
					bl = 0;
				else
					bl = 3;
			}
		} else {
			bl = 0;
		}
	}

	while ((start_idx + cnt) < end_idx) {
		dnc_tlb_update(dnc_id, cnt, cmd, addr + cnt * PAGE_SIZE_2MB, bl);
		cnt++;
	}

	return cnt;
}

static const char help_ldudma_test[] = "[ldudma_test]\r\n"
	" * ldudma_test {dnc id}, {src_addr}, {dst_addr}, {size}\r\n"
	" * src_addr : dram or shm or other sp\r\n"
	" * dst_addr : own's sp addr\r\n"
	" * ex) ldudma_test 0 60000000 0 400000\r\n\r\n";

static const char help_lpudma_test[] = "[lpudma_test]\r\n"
	" * lpudma_test {dnc id}, {src_addr}, {dst_addr}, {size}\r\n"
	" * src_addr : dram or shm or other sp\r\n"
	" * dst_addr : own's sp addr\r\n"
	" * ex) lpudma_test 0 60000000 0 400000\r\n\r\n";

static const char help_studma_test[] = "[studma_test]\r\n"
	" * studma_test {dnc id}, {src_addr}, {dst_addr}, {size}\r\n"
	" * src_addr : own's sp addr\r\n"
	" * dst_addr : dram or shm or other sp\r\n"
	" * ex) studma_test 1 0 80000000 400000\r\n\r\n";

static const char help_checksum_test[] = "[checksum_test]\r\n"
	" * checksum_test {dnc id}, {start_addr}, {size}\r\n"
	" * start_addr : own's sp addr\r\n"
	" * ex) checksum_test 0 0 400000\r\n\r\n";

static const char help_rbdma_test[] = "[rbdma_test]\r\n"
	" * rbdma_test {src_addr}, {dst_addr}, {size}\r\n"
	" * src_addr : dram or shm\r\n"
	" * dst_addr : dram or shm\r\n"
	" * ex) rbdma_test 60000000 1fe4000000 400000\r\n\r\n";

static const char help_rbdma_perf_test[] = "[rbdma_perf_test]\r\n"
	" * rbdma_perf_test {src_addr}, {dst_addr}, {size}, {te}, {spl_grnl}, {iter}, {compare}\r\n"
	" * src_addr : dram\r\n"
	" * dst_addr : dram\r\n"
	" * size : trs size\r\n"
	" * te : te affinity\r\n"
	" * spl_grnl : granule 0~15\r\n"
	" * iter : iter 1~4\r\n";

static const char help_rbdma_dram_2_shm_perf_test[] = "[rbdma_dram_2_shm_perf_test]\r\n"
	" * rbdma_dram_2_shm_perf_test {dram_addr}, {direction}, {size}\r\n"
	" * dram_addr : dram\r\n"
	" * direction : dram -> shm (0) or shm -> dram (1)\r\n"
	" * ex) rbdma_dram_2_shm_perf_test 60000000 0 2000000\r\n\r\n";

static const char help_test_oto[] = "[test_oto]\r\n"
					" * test_oto {src_pa} {dst_pa} {block_size} {te_mask} {duration_sec} {compare} {gpio_ctrl}\r\n"
					"\r\n";

uint8_t ldudma_test(int argc, char *argv[])
{
    uint8_t dnc_id;
    uint64_t src_addr;
    uint32_t dst_addr;
    uint32_t trs_size;
    uint32_t tb = 0;

	if (argc < 4) {
		printf("%s\r\n", help_ldudma_test);
		return false;
	}else {
		dnc_id = atoi(argv[0]);
        if(dnc_id > HW_SPEC_DNC_COUNT){
            printf("\r\n[check dnc_id's configration.] dnc_id was configured as dnc%02d.\r\n", dnc_id);
            return false;
        }
        src_addr = (uint64_t)strtoul(argv[1], NULL, 16);

        dst_addr = (uint64_t)strtoul(argv[2], NULL, 16);
        if(dst_addr > 0x400000){
            printf("\r\n[check dst_addr's configration.] dst_addr was configured as 0x%x.\r\n", dst_addr);
            return false;
        }

        trs_size = (uint32_t)strtoul(argv[3], NULL, 16);
        if(trs_size > 0x400000){
            printf("\r\n[check trs_size's configration.] trs_size was configured as 0x%x(%d).\r\n", trs_size, trs_size);
            return false;
        }
        printf("\r\n[dnc%02d] 0x%lx -> 0x%x(SP) 0x%x(%d)\r\n", dnc_id, src_addr, dst_addr, trs_size, trs_size);
	}

    tb = insert_or_find_tlb(dnc_id, (enum cmd_mode)LDuDMA, src_addr, trs_size);
    printf("tlb table set count is (%d)\r\n", tb);

    //generate task
    generate_udma_task(dnc_id, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);

    dnc_done_accumulate_count(dnc_id, (enum cmd_mode)LDuDMA, 1 + tb);

    dnc_done_acc_count_all_clear(cur_cl_id);

	return true;
}

uint8_t lpudma_test(int argc, char *argv[])
{
    uint8_t dnc_id;
    uint64_t src_addr;
    uint32_t dst_addr;
    uint32_t trs_size;
    uint32_t tb = 0;

	if (argc < 4) {
		printf("%s\r\n", help_lpudma_test);
		return false;
	}else {
		dnc_id = atoi(argv[0]);
        if(dnc_id > HW_SPEC_DNC_COUNT){
            printf("\r\n[check dnc_id's configration.] dnc_id was configured as dnc%02d.\r\n", dnc_id);
            return false;
        }
        src_addr = (uint64_t)strtoul(argv[1], NULL, 16);

        dst_addr = (uint64_t)strtoul(argv[2], NULL, 16);
        if(dst_addr > 0x400000){
            printf("\r\n[check dst_addr's configration.] dst_addr was configured as 0x%x.\r\n", dst_addr);
            return false;
        }

        trs_size = (uint32_t)strtoul(argv[3], NULL, 16);
        if(trs_size > 0x400000){
            printf("\r\n[check trs_size's configration.] trs_size was configured as 0x%x(%d).\r\n", trs_size, trs_size);
            return false;
        }
        printf("\r\n[dnc%02d] 0x%lx -> 0x%x(SP) 0x%x(%d)\r\n", dnc_id, src_addr, dst_addr, trs_size, trs_size);
	}

    tb = insert_or_find_tlb(dnc_id, (enum cmd_mode)LPuDMA, src_addr, trs_size);
    printf("tlb table set count is (%d)\r\n", tb);

    //generate task
    generate_udma_task(dnc_id, (enum cmd_mode)LPuDMA, src_addr, dst_addr, trs_size);

    dnc_done_accumulate_count(dnc_id, (enum cmd_mode)LPuDMA, 1 + tb);

    dnc_done_acc_count_all_clear(cur_cl_id);

	return true;
}

uint8_t studma_test(int argc, char *argv[])
{
    uint8_t dnc_id;
    uint32_t src_addr;
    uint64_t dst_addr;
    uint32_t trs_size;
    uint32_t tb = 0;

	if (argc < 4) {
		printf("%s\r\n", help_studma_test);
		return false;
	}else {
		dnc_id = atoi(argv[0]);
        if(dnc_id > HW_SPEC_DNC_COUNT){
            printf("\r\n[check dnc_id's configration.] dnc_id was configured as dnc%02d.\r\n", dnc_id);
            return false;
        }
        src_addr = (uint64_t)strtoul(argv[1], NULL, 16);
        if(src_addr > 0x400000){
            printf("\r\n[check src_addr's configration.] src_addr was configured as 0x%x.\r\n", src_addr);
            return false;
        }
        dst_addr = (uint64_t)strtoul(argv[2], NULL, 16);

        trs_size = (uint32_t)strtoul(argv[3], NULL, 16);
        if(trs_size > 0x400000){
            printf("\r\n[check trs_size's configration.] trs_size was configured as 0x%x(%d).\r\n", trs_size, trs_size);
            return false;
        }
        printf("\r\ndnc%02d 0x%x(SP) -> 0x%lx 0x%x(%d)\r\n", dnc_id, src_addr, dst_addr, trs_size, trs_size);
	}

	tb = insert_or_find_tlb(dnc_id, (enum cmd_mode)STuDMA, dst_addr, trs_size);
    printf("tlb table set count is (%d)\r\n", tb);

    //generate task
    generate_udma_task(dnc_id, (enum cmd_mode)STuDMA, src_addr, dst_addr, trs_size);

    dnc_done_accumulate_count(dnc_id, (enum cmd_mode)STuDMA, 1 + tb);

    dnc_done_acc_count_all_clear(cur_cl_id);

	return true;
}

uint8_t checksum_test(int argc, char *argv[])
{
    uint8_t dnc_id;
    uint32_t start_addr;
    uint32_t trs_size;
	volatile uint32_t *dump_ptr;
    
    if (argc < 3) {
		printf("%s\r\n", help_checksum_test);
		return false;
	}else {
		dnc_id = atoi(argv[0]);
        if(dnc_id > HW_SPEC_DNC_COUNT){
            printf("\r\n[check dnc_id's configration.] dnc_id was configured as dnc%02d.\r\n", dnc_id);
            return false;
        }
        start_addr = (uint64_t)strtoul(argv[1], NULL, 16);
        if(start_addr%128 != 0){
            printf("\r\n[check start_address.] the address must align 128byte (%x)\r\n", start_addr);
            return false;
        }

        trs_size = (uint64_t)strtoul(argv[2], NULL, 16);
        if(trs_size > 0x400000){
            printf("\r\n[check trs_size's configration.] trs_size was configured as 0x%x(%d).\r\n", trs_size, trs_size);
            return false;
        }
	}
    
    dnc_checksum(dnc_id, start_addr, trs_size);

    // result : 3ff80,  128bit
    dump_ptr = (volatile uint32_t *)(uintptr_t)(SP_SHM_PHYSICAL_START + SZ_4M - 128) + (uintptr_t)(dnc_id*SZ_4M);

    printf("\r\n[dnc%02d] checksum is ", dnc_id);
    for(int i=0;i<4;i++){
        printf("%08x ", *dump_ptr++);
    }
    printf("\r\n");

    return true;
}

uint8_t rbdma_test(int argc, char *argv[])
{
    uint64_t src_addr = 0;
    uint64_t dst_addr = 0;
    uint32_t trs_size = 0;
    uint32_t task_id = 0xDD3A1234;

    if(argc < 3){
        printf("%s\r\n", help_rbdma_test);
        return false;
    }else {
        src_addr = (uint64_t)strtoul(argv[0], NULL, 16);
        dst_addr = (uint64_t)strtoul(argv[1], NULL, 16);
        trs_size = (uint32_t)strtoul(argv[2], NULL, 16);
        if(trs_size == 0){
            printf("\r\n[check trs_size's configration.] trs_size was configured as 0x%x(%d).\r\n", trs_size, trs_size);
            return false;
        }
    }
    rbdma_set_max_perf_mode(0x0);

    generate_rbdma_task(task_id, src_addr, dst_addr, trs_size, 0);

    rbdma_done_acc_count(cur_cl_id, 1); // cl0 , count is 1
    rbdma_done_clear(cur_cl_id);    // cl0

    return true;
}

uint8_t rbdma_perf_test(int argc, char *argv[])
{
	uint64_t src_addr = 0;
	uint64_t dst_addr = 0;
	uint32_t trs_size = 0;
    uint8_t te_affinity = 0xff;
	uint32_t spl_grnl = 0;
	uint32_t iter = 0;
	uint32_t enable_compare = 0;
	uint32_t task_id;
	uint64_t start_cycle = 0ULL;
	uint64_t cpu_freq = 2000000000ULL;

	if (argc < 7) {
		printf("%s\r\n", help_rbdma_perf_test);
		return false;
	} else {
		src_addr = (uint64_t)strtoul(argv[0], NULL, 16);
		dst_addr = (uint64_t)strtoul(argv[1], NULL, 16);
		trs_size = (uint32_t)strtoul(argv[2], NULL, 16);
        te_affinity = (uint8_t)strtoul(argv[3], NULL, 16);
		spl_grnl = (uint32_t)strtoul(argv[4], NULL, 16);
		iter = (uint32_t)strtoul(argv[5], NULL, 16);
		enable_compare = (uint32_t)strtoul(argv[6], NULL, 16);
		if (trs_size == 0) {
			printf("\r\n[check trs_size's configuration.] 0x%x(%d).\r\n",
				trs_size, trs_size);
			return false;
		}
		if (enable_compare > 1) {
			printf("\r\n[check compare's configuration.] %d.\r\n", enable_compare);
			return false;
		}
	}

    rand_fill((void *)src_addr, trs_size);

    rbdma_set_max_perf_mode(0x0);
//	rbdma_logmgr_dump_start(0); // dram monitor

	start_cycle = bw_measure_start();
	for (int i = 0; i < iter; i++) {
		task_id = 0xDD3A0000 + i;
		generate_rbdma_perf_task(task_id, src_addr, dst_addr, trs_size, te_affinity, spl_grnl, 0);
	}
	rbdma_done_acc_count(cur_cl_id, iter);

	bw_measure_end_and_print(start_cycle, (uint64_t)trs_size * iter, cpu_freq, true);

//    hbm_activity_monitor(cur_cl_id, 0);

//	rbdma_logmgr_dump_detail();
//	rbdma_logmgr_exec_time(0);
	rbdma_done_clear(cur_cl_id);

	if (enable_compare)
		basic_test_compare(src_addr, dst_addr, trs_size);

	return true;
}

uint8_t rbdma_dram_2_shm_perf_test(int argc, char *argv[])
{
	uint64_t dram_addr = 0;
	uint64_t src_addr0 = 0;
	uint64_t dst_addr0 = 0;
	uint64_t src_addr1 = 0;
	uint64_t dst_addr1 = 0;
	uint32_t direction = 0;
	uint32_t trs_size = 0;
	uint64_t start_cycle;
	uint64_t cpu_freq = 2000000000ULL;

	if (argc < 3){
		printf("%s\r\n", help_rbdma_test);
		return false;
	} else {
		dram_addr = (uint64_t)strtoul(argv[0], NULL, 16);
		direction = (uint32_t)strtoul(argv[1], NULL, 16);
		trs_size  = (uint32_t)strtoul(argv[2], NULL, 16);
		if((trs_size == 0) || (trs_size > SZ_32M)){
			printf("\r\n[check trs_size's configration.] trs_size was configured as 0x%x(%d).\r\n", trs_size, trs_size);
			return false;
		}
	}

	if (direction == 0){
		src_addr0 = dram_addr;
		dst_addr0 = DCL0_SH_MEM_BASE_CL;
		src_addr1 = dram_addr + trs_size;
		dst_addr1 = DCL1_SH_MEM_BASE_CL;
	}
	else {
		src_addr0 = DCL0_SH_MEM_BASE_CL;
		dst_addr0 = dram_addr;
		src_addr1 = DCL1_SH_MEM_BASE_CL;
		dst_addr1 = dram_addr + trs_size;
	}

	rand_fill((void *)src_addr0, trs_size);
	rand_fill((void *)src_addr1, trs_size);

	rbdma_set_max_perf_mode(0x7);
	rbdma_logmgr_dump_start(0);
    
	generate_rbdma_task_tsync(0xDD3A0000, src_addr0, dst_addr0, trs_size, 0x7, 0, 0xf, 1);
	generate_rbdma_task_tsync(0xDD3A0001, src_addr1, dst_addr1, trs_size, 0x7, 0, 0xf0, 0);
	rbdma_tsync_by_cp();

	start_cycle = bw_measure_start();
	rbdma_done_acc_count(cur_cl_id, 2);

	bw_measure_end_and_print(start_cycle, (uint64_t)trs_size * 2, cpu_freq, true);

	rbdma_logmgr_dump_detail();
	rbdma_logmgr_exec_time(1);
	rbdma_done_clear(cur_cl_id);

	basic_test_compare(src_addr0, dst_addr0, trs_size);
	basic_test_compare(src_addr1, dst_addr1, trs_size);

	return true;
}

static uint8_t rbdma_cli_test_oto(int argc, char *argv[])
{
	const uint32_t task_id_base = 0xDD3A0000;
	uint64_t src;
	uint64_t dst;
	uint64_t block;
	uint32_t te_mask;
	uint32_t duration_sec = 1;
	uint32_t elapsed_cylces;
	bool compare;
	bool gpio_ctrl = false;
	int src_cl;
	int dst_cl;
	bool uses_shm;
	bool gpio_asserted = false;
	uint32_t queue_left;
	TickType_t test_time_tick = 0;
	TickType_t start_tick;
	uint32_t iteration = 0;
	uint32_t iter_cnt = 0;

	const uint32_t RBDMA_IDLE_ST_MASK = 0x7F;

	if (argc < 7) {
		printf("usage: test_oto {src_pa} {dst_pa} {block_size} "
			   "{te_mask} {duration_sec} {compare} {gpio_ctrl} "
			   "(optional: {iteration_cnt})\r\n");
		printf("All arguments except duration_sec and comp, gpio_ctrl should be hexa\r\n");
		return false;
	}

	src = (uint64_t)strtoll(argv[0], NULL, 16);
	dst = (uint64_t)strtoll(argv[1], NULL, 16);
	block = (uint64_t)strtoll(argv[2], NULL, 16);
	te_mask = (uint32_t)strtol(argv[3], NULL, 16);
	duration_sec = (uint32_t)strtol(argv[4], NULL, 10);
	compare = (bool)strtol(argv[5], NULL, 10);
	gpio_ctrl = (bool)strtol(argv[6], NULL, 10);

	if (argc > 7)
		iter_cnt = strtol(argv[7], NULL, 10);

	test_time_tick = pdMS_TO_TICKS(duration_sec * 1000);

	src_cl = get_chip_id_from_addr(src);
	if (src_cl == RL_ERROR) {
		printf("Wrong src addr %#lx\r\n", (unsigned long)src);
		return false;
	}

	dst_cl = get_chip_id_from_addr(dst);
	if (dst_cl == RL_ERROR) {
		printf("Wrong dst addr %#lx\r\n", (unsigned long)dst);
		return false;
	}

	if (te_mask > 0xFF) {
		printf("Invalid te_mask %#x\r\n", te_mask);
		return false;
	}

	uses_shm = is_shm_addr(src) || is_shm_addr(dst);
	if (uses_shm) {
		if (block > RL_SHM_SIZE) {
			printf("block size %#llx should be <= 64MB if src or dst is shm\r\n",
				   (unsigned long long)block);
			return false;
		}
	} else {
		if (block > DRAM_SIZE_PER_CL) {
			printf("block size %#llx should be <= 35GB if src and dst are dram\r\n",
				   (unsigned long long)block);
			return false;
		}
	}

	printf("* src fill random data\r\n");
	rand_fill((void *)src, block);
	cpu_clean_dcache_range((uintptr_t)src, (size_t)block);

	printf("\r\nsrc_cl %u -> dst_cl %u transfer start\r\n", src_cl, dst_cl);

	if (compare) {
		rand_fill((void *)src, block);
		cpu_clean_dcache_range((uintptr_t)dst, (size_t)block);
	}

	elapsed_cylces = get_current_count();
	if (gpio_ctrl) {
		rbdma_gpio_drive(src_cl, true);
		gpio_asserted = true;
	}

	queue_left = rbdma_global_normal_queue_status_cl(cur_cl_id);
	dsb();
	start_tick = xTaskGetTickCount();
	while (((xTaskGetTickCount() - start_tick) < test_time_tick) || iter_cnt) {
		if (queue_left == 0) {
			queue_left = rbdma_global_normal_queue_status_cl(cur_cl_id);
			dsb();
			continue;
		}
		generate_rbdma_perf_task(task_id_base + iteration, src, dst,
								 (uint32_t)block, te_mask, 0xF, 0);
		queue_left--;
		iteration++;

		if (iter_cnt && (iteration >= iter_cnt))
			break;
	}

	printf("Total %u rbdma tasks submitted\r\n", iteration);

	while ((rbdma_global_idle_status_cl(cur_cl_id) & RBDMA_IDLE_ST_MASK) != RBDMA_IDLE_ST_MASK)
		;
	rbdma_done_clear(cur_cl_id);

	printf("All rbdma tasks done\r\n");

	if (gpio_ctrl && gpio_asserted) {
		rbdma_gpio_drive(src_cl, false);
		gpio_asserted = false;
	}
	elapsed_cylces = get_current_count() - elapsed_cylces;

	if (compare && basic_test_compare(src, dst, (uint32_t)block)) {
		printf("src and dst mismatch\r\n");
		goto err;
	}

	if (gpio_ctrl)
		printf("PASSED. cpu cycles: %u, total transfer sz: %llu bytes, w/gpio ctrl\r\n",
			   elapsed_cylces, (unsigned long long)(block * iteration));
	else
		printf("PASSED. cpu cycles: %u, total transfer sz: %llu bytes\r\n",
			   elapsed_cylces, (unsigned long long)(block * iteration));

	return true;

err:
	if (gpio_ctrl && gpio_asserted)
		rbdma_gpio_drive(src_cl, false);

	printf("FAILED. rbdma task done polling failed\r\n");

	return true;
}

static uint8_t shm_exception_test(int argc, char *argv[])
{
    printf("\r\n\r\n generate sglue error interrupt.\r\n");
    printf("check the rbln log string.\r\n");
    printf("Reset System after this test\r\n");

    shm_exception_register(cur_cl_id);  // cl0

    return true;
}

static uint8_t mglue_interrupt_test(int argc, char *argv[])
{
	uint64_t src_addr   = 0;
	uint64_t dst_addr   = DCL0_SP_MEM_BASE;
	uint32_t trs_size   = SZ_4M;
	uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };

	printf("\r\n* generate mglue error interrupt.\r\n");
	printf("* check the rbln log string.\r\n");
	printf("* Reset System after this test.\r\n");

	rdsn_custom_config(cur_cl_id);
	mglue_interrupt_register(cur_cl_id);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		// RUN_TIME
		timeout_config(i, 0x1, 0xffffffff);
	}

	for (int i = 1; i < HW_SPEC_DNC_COUNT / 2; i++) {
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)STuDMA, dst_addr, trs_size);
		printf("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
		//generate task
		generate_udma_task(i, (enum cmd_mode)STuDMA, src_addr, dst_addr, trs_size);
	}

	for (int i = 8; i < HW_SPEC_DNC_COUNT; i++) {
		dst_addr = DCL1_SP_MEM_BASE;
		tb[i] = insert_or_find_tlb(i, (enum cmd_mode)STuDMA, dst_addr, trs_size);
		printf("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
		//generate task
		generate_udma_task(i, (enum cmd_mode)STuDMA, src_addr, dst_addr, trs_size);
	}

	return true;
}

static uint8_t rbdma_error_interrupt_test(int argc, char *argv[])
{
    printf("\r\n* generate rbdma error interrupt.\r\n");
    printf("* check the log string.\r\n");
    printf("* Reset System after this test.\r\n");

    generate_error_interrupt();

    return true;
}

int dnc_report_cdump(void)
{
    uint64_t src_addr   = DATA_MEM_BASE_ADDR;   // Dram input addr
    uint64_t dst_addr   = 0x0;                  // SP base
    uint32_t trs_size   = PAGE_SIZE_2MB;        // trs size is 2MB
    uint32_t tb[HW_SPEC_DNC_COUNT] = {0, };
    CdumpInfo_t      dump_info;
    volatile uint32_t *dump_ptr;
    uint64_t profile_addr = (DNC_PROFILE_BASE_ADDR_HIGH<<32) | DNC_PROFILE_BASE_ADDR_LOW;
//    int ret = false;

    printf("dnc_report_cdump\r\n");
    RLOG_INFO("dnc_report_cdump\r\n");

    rand_fill((void *)src_addr, trs_size);

    memset(&dump_info, 0x0, sizeof(CdumpInfo_t));
    dump_info.done_policy   = 1;
    dump_info.dcrn_size     = 20;   //24-4, ldudma acc0~5 x4
    dump_info.uan_size      = 252;  //256-4, nc tlb 64 x4
    dump_info.dest_addr     = profile_addr;	//0x710000000;
    dump_info.dcrn_offset_addr  = 0x4E0;    //ldudma acc0 ~
    dump_info.uan_offset_addr   = 0x500;    //nc tlb0 ~
    dump_info.stride    = 0;
    dump_info.cdump_component   = 1<<14 | 1<<15;    //NCLU, NCSU  
    dnc_cdump_mode(dump_info);

    printf("ldudma_dram_2_sp\r\n");
    RLOG_INFO("ldudma_dram_2_sp\r\n");

    for(int i=0;i<HW_SPEC_DNC_COUNT;i++){
        tb[i] = insert_or_find_tlb(i, (enum cmd_mode)LDuDMA, src_addr, trs_size);
        printf("[dnc%02d] tlb table set count is (%d)\r\n", i, tb[i]);
        //generate task
        generate_udma_task(i, (enum cmd_mode)LDuDMA, src_addr, dst_addr, trs_size);
        tb[i] += 1;
    }

    for(int i=0;i<HW_SPEC_DNC_COUNT;i++){
        dnc_done_accumulate_count(i, (enum cmd_mode)LDuDMA, tb[i]);
    }
    printf("task all done\r\n");

    if(dnc_cdump_flag == 1){
        // display cdump data
        for(int i=0;i<HW_SPEC_DNC_COUNT;i++){
            dump_ptr = (volatile uint32_t *)(uintptr_t)(0xC0000000 + i*0x1000 + 0x8);
            printf("dnc_local id : %02x \r\n", *dump_ptr & 0x7);
            printf("dcluster id : %02x \r\n", (*dump_ptr & 0x8)>>3);
            printf("chiplet id : %02x \r\n\r\n", (*dump_ptr & 0x30)>>4);
        }
    }

    dnc_done_acc_count_all_clear(cur_cl_id);
    printf("\r\n");

    return true;
}

static uint8_t dnc_report_dump_test(int argc, char *argv[])
{
    printf("\r\n* dnc_report_dump_test\r\n");

    dnc_report_cdump();

    return true;
}

CLI_REGISTER(ldudma_test, NULL, ldudma_test, help_ldudma_test);
CLI_REGISTER(lpudma_test, NULL, lpudma_test, help_lpudma_test);
CLI_REGISTER(studma_test, NULL, studma_test, help_studma_test);
CLI_REGISTER(checksum_test, NULL, checksum_test, help_checksum_test);
CLI_REGISTER(rbdma_test, NULL, rbdma_test, help_rbdma_test);
CLI_REGISTER(rbdma_perf_test, NULL, rbdma_perf_test, help_rbdma_perf_test);
CLI_REGISTER(rbdma_dram_2_shm_perf_test, NULL, rbdma_dram_2_shm_perf_test, help_rbdma_dram_2_shm_perf_test);
CLI_REGISTER(test_oto, NULL, rbdma_cli_test_oto, help_test_oto);
CLI_REGISTER(shm_exception_test, NULL, shm_exception_test, "[shm_exception_test]\r\n"
                                                "* generate sglue error interrupt.\r\n"
                                                "* Reset system after this test.\r\n\r\n");
CLI_REGISTER(mglue_interrupt_test, NULL, mglue_interrupt_test, "[mglue_interrupt_test]\r\n"
                                                "* generate mglue error interrrupt.\r\n"
                                                "* Reset system after this test.\r\n\r\n");
CLI_REGISTER(rbdma_error_interrupt_test, NULL, rbdma_error_interrupt_test, "[rbdma_error_interrupt_test]\r\n"
                                                "* generate mglue error interrrupt.\r\n"
                                                "* Reset system after this test.\r\n\r\n");
CLI_REGISTER(dnc_report_dump_test, NULL, dnc_report_dump_test, "[dnc_report_dump_test]\r\n"
                                                "* cdump area's start is 0xC0000000.\r\n"
                                                "* each offset has 0x1000.\r\n");
