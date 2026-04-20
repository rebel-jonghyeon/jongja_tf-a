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

#ifndef _G_DNC_TASK_16B_COMMON_H_
#define _G_DNC_TASK_16B_COMMON_H_

#define ADDR_OFFSET_DNC_TASK16B_CMD	0x000
#define ADDR_OFFSET_DNC_TASK16B_COMMON	0x004
#define ADDR_OFFSET_DNC_TASK16B_ADDR0	0x008
#define ADDR_OFFSET_DNC_TASK16B_ADDR1	0x00C
#define ADDR_OFFSET_DNC_TASK16B_RSVD5	0x010
#define ADDR_OFFSET_DNC_TASK16B_RSVD6	0x014
#define ADDR_OFFSET_DNC_TASK16B_RSVD7	0x018
#define ADDR_OFFSET_DNC_TASK16B_RSVD8	0x01C
#define ADDR_OFFSET_DNC_TASK16B_EN	0x020
#define ADDR_OFFSET_DNC_TASK16B_TRIG	0x024
#define ADDR_OFFSET_DNC_TASK16B_RSVD11	0x028
#define ADDR_OFFSET_DNC_TASK16B_RSVD12	0x02C
#define ADDR_OFFSET_DNC_TASK16B_STATUS0	0x030
#define ADDR_OFFSET_DNC_TASK16B_STATUS1	0x034
#define ADDR_OFFSET_DNC_TASK16B_STATUS2	0x038
#define ADDR_OFFSET_DNC_TASK16B_STATUS3	0x03C
#define ADDR_OFFSET_DNC_TASK16B_RUN_TASK0	0x040
#define ADDR_OFFSET_DNC_TASK16B_RUN_TASK1	0x044
#define ADDR_OFFSET_DNC_TASK16B_RUN_TASK2	0x048
#define ADDR_OFFSET_DNC_TASK16B_RSVD20	0x04C
#define ADDR_OFFSET_DNC_TASK16B_DONE_CLEAR	0x050
#define ADDR_OFFSET_DNC_TASK16B_DONE_SETREG	0x054
#define ADDR_OFFSET_DNC_TASK16B_DONE_COMP0	0x058
#define ADDR_OFFSET_DNC_TASK16B_DONE_COMP1	0x05C
#define ADDR_OFFSET_DNC_TASK16B_DONE_LDUDMA0	0x060
#define ADDR_OFFSET_DNC_TASK16B_DONE_LDUDMA1	0x064
#define ADDR_OFFSET_DNC_TASK16B_DONE_LPUDMA0	0x068
#define ADDR_OFFSET_DNC_TASK16B_DONE_LPUDMA1	0x06C
#define ADDR_OFFSET_DNC_TASK16B_DONE_STUDMA0	0x070
#define ADDR_OFFSET_DNC_TASK16B_DONE_STUDMA1	0x074
#define ADDR_OFFSET_DNC_TASK16B_DONE_NWR	0x078
#define ADDR_OFFSET_DNC_TASK16B_DONE_PWR	0x07C
#define ADDR_OFFSET_DNC_TASK16B_DONE_CDUMP	0x080
#define ADDR_OFFSET_DNC_TASK16B_RSVD34	0x084
#define ADDR_OFFSET_DNC_TASK16B_RSVD35	0x088
#define ADDR_OFFSET_DNC_TASK16B_RSVD36	0x08C
#define ADDR_OFFSET_DNC_TASK16B_RSVD37	0x090
#define ADDR_OFFSET_DNC_TASK16B_RSVD38	0x094
#define ADDR_OFFSET_DNC_TASK16B_RSVD39	0x098
#define ADDR_OFFSET_DNC_TASK16B_RSVD40	0x09C
#define ADDR_OFFSET_DNC_TASK16B_TEST0	0x0A0
#define ADDR_OFFSET_DNC_TASK16B_TEST1	0x0A4
#define ADDR_OFFSET_DNC_TASK16B_TEST2	0x0A8
#define ADDR_OFFSET_DNC_TASK16B_TEST3	0x0AC
#define ADDR_OFFSET_DNC_TASK16B_TEST4	0x0B0
#define ADDR_OFFSET_DNC_TASK16B_TEST5	0x0B4
#define ADDR_OFFSET_DNC_TASK16B_TEST6	0x0B8
#define ADDR_OFFSET_DNC_TASK16B_TEST7	0x0BC
#define ADDR_OFFSET_DNC_TASK16B_RSVD49	0x0C0
#define ADDR_OFFSET_DNC_TASK16B_RSVD50	0x0C4
#define ADDR_OFFSET_DNC_TASK16B_RSVD51	0x0C8
#define ADDR_OFFSET_DNC_TASK16B_RSVD52	0x0CC
#define ADDR_OFFSET_DNC_TASK16B_RSVD53	0x0D0
#define ADDR_OFFSET_DNC_TASK16B_RSVD54	0x0D4
#define ADDR_OFFSET_DNC_TASK16B_RSVD55	0x0D8
#define ADDR_OFFSET_DNC_TASK16B_RSVD56	0x0DC
#define ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_00	0x0E0
#define ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_01	0x0E4
#define ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_02	0x0E8
#define ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_03	0x0EC
#define ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_04	0x0F0
#define ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_05	0x0F4
#define ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_06	0x0F8
#define ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_07	0x0FC

#if 0
struct RegData reg_dnc_task_16b[] = {/*{{{*/
{"ADDR_OFFSET_DNC_TASK16B_CMD", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_COMMON", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ADDR0", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ADDR1", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD5", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD6", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD7", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD8", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_EN", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_TRIG", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD11", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD12", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_STATUS0", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_STATUS1", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_STATUS2", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_STATUS3", 0xffffffff},
{"ADDR_OFFSET_DNC_TASK16B_RUN_TASK0", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RUN_TASK1", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RUN_TASK2", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD20", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_CLEAR", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_SETREG", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_COMP0", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_COMP1", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_LDUDMA0", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_LDUDMA1", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_LPUDMA0", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_LPUDMA1", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_STUDMA0", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_STUDMA1", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_NWR", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_PWR", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_DONE_CDUMP", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD34", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD35", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD36", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD37", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD38", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD39", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD40", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_TEST0", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_TEST1", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_TEST2", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_TEST3", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_TEST4", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_TEST5", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_TEST6", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_TEST7", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD49", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD50", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD51", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD52", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD53", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD54", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD55", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_RSVD56", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_00", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_01", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_02", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_03", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_04", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_05", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_06", 0x0},
{"ADDR_OFFSET_DNC_TASK16B_ETIME_COMP_07", 0x0}
};/*}}}*/
#endif

union dnc_task16b_cmd {
	struct __attribute__ ((packed)) {
		uint32_t type	: 4;
		uint32_t blocking	: 4;
		uint32_t wait	: 1;
		uint32_t intr	: 1;
		uint32_t rsvd10	: 6;
		uint32_t tid	: 8;
		uint32_t delay	: 8;
	};
	uint32_t bits;
};

union dnc_task16b_common {
	struct __attribute__ ((packed)) {
		uint32_t content	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_addr0 {
	struct __attribute__ ((packed)) {
		uint32_t ext	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_addr1 {
	struct __attribute__ ((packed)) {
		uint32_t ext	: 8;
		uint32_t sp	: 16;
		uint32_t ctrl	: 4;
		uint32_t rsvd28	: 3;
		uint32_t itdone	: 1;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd5 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd6 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd7 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd8 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_en {
	struct __attribute__ ((packed)) {
		uint32_t task16b	: 1;
		uint32_t task16b_rpt	: 1;
		uint32_t rsvd2	: 30;
	};
	uint32_t bits;
};

union dnc_task16b_trig {
	struct __attribute__ ((packed)) {
		uint32_t erun	: 1;
		uint32_t clear_intr	: 1;
		uint32_t clear_intr_all	: 1;
		uint32_t rsvd3	: 29;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd11 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd12 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_status0 {
	struct __attribute__ ((packed)) {
		uint32_t run_clear	: 1;
		uint32_t run_setreg	: 1;
		uint32_t run_comp	: 1;
		uint32_t run_ldudma	: 1;
		uint32_t run_lpudma	: 1;
		uint32_t run_studma	: 1;
		uint32_t run_nwr	: 1;
		uint32_t run_pwr	: 1;
		uint32_t run_cdump	: 1;
		uint32_t rsvd9	: 7;
		uint32_t wait	: 1;
		uint32_t tout_setreg	: 1;
		uint32_t tout_comp	: 1;
		uint32_t tout_ldudma	: 1;
		uint32_t tout_lpudma	: 1;
		uint32_t tout_studma	: 1;
		uint32_t tout_nwr	: 1;
		uint32_t tout_pwr	: 1;
		uint32_t tout_cdump	: 1;
		uint32_t rsvd25	: 7;
	};
	uint32_t bits;
};

union dnc_task16b_status1 {
	struct __attribute__ ((packed)) {
		uint32_t q_depth	: 8;
		uint32_t intr_cnt	: 4;
		uint32_t rsvd12	: 20;
	};
	uint32_t bits;
};

union dnc_task16b_status2 {
	struct __attribute__ ((packed)) {
		uint32_t dnc_exception	: 16;
		uint32_t ncore0_exception	: 8;
		uint32_t ncore1_exception	: 8;
	};
	uint32_t bits;
};

union dnc_task16b_status3 {
	struct __attribute__ ((packed)) {
		uint32_t dnc_idle	: 16;
		uint32_t ncore0_quiesce	: 8;
		uint32_t ncore1_quiesce	: 8;
	};
	uint32_t bits;
};

union dnc_task16b_run_task0 {
	struct __attribute__ ((packed)) {
		uint32_t clear	: 8;
		uint32_t regset	: 8;
		uint32_t comp	: 8;
		uint32_t ldudma	: 8;
	};
	uint32_t bits;
};

union dnc_task16b_run_task1 {
	struct __attribute__ ((packed)) {
		uint32_t lpudma	: 8;
		uint32_t studma	: 8;
		uint32_t nwr	: 8;
		uint32_t pwr	: 8;
	};
	uint32_t bits;
};

union dnc_task16b_run_task2 {
	struct __attribute__ ((packed)) {
		uint32_t cdump	: 8;
		uint32_t rsvd8	: 8;
		uint32_t rsvd16	: 8;
		uint32_t rsvd24	: 8;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd20 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_done_clear {
	struct __attribute__ ((packed)) {
		uint32_t vcnt	: 8;
		uint32_t tid	: 8;
		uint32_t rsvd16	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_done_setreg {
	struct __attribute__ ((packed)) {
		uint32_t vcnt	: 8;
		uint32_t tid	: 8;
		uint32_t exec_time	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_done_comp0 {
	struct __attribute__ ((packed)) {
		uint32_t vcnt	: 8;
		uint32_t tid	: 8;
		uint32_t exec_time	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_done_comp1 {
	struct __attribute__ ((packed)) {
		uint32_t exec_time	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_done_ldudma0 {
	struct __attribute__ ((packed)) {
		uint32_t vcnt	: 8;
		uint32_t tid	: 8;
		uint32_t exec_time	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_done_ldudma1 {
	struct __attribute__ ((packed)) {
		uint32_t exec_time	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_done_lpudma0 {
	struct __attribute__ ((packed)) {
		uint32_t vcnt	: 8;
		uint32_t tid	: 8;
		uint32_t exec_time	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_done_lpudma1 {
	struct __attribute__ ((packed)) {
		uint32_t exec_time	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_done_studma0 {
	struct __attribute__ ((packed)) {
		uint32_t vcnt	: 8;
		uint32_t tid	: 8;
		uint32_t exec_time	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_done_studma1 {
	struct __attribute__ ((packed)) {
		uint32_t exec_time	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_done_nwr {
	struct __attribute__ ((packed)) {
		uint32_t vcnt	: 8;
		uint32_t tid	: 8;
		uint32_t exec_time	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_done_pwr {
	struct __attribute__ ((packed)) {
		uint32_t vcnt	: 8;
		uint32_t tid	: 8;
		uint32_t exec_time	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_done_cdump {
	struct __attribute__ ((packed)) {
		uint32_t vcnt	: 8;
		uint32_t tid	: 8;
		uint32_t exec_time	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd34 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd35 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd36 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd37 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd38 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd39 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd40 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_test0 {
	struct __attribute__ ((packed)) {
		uint32_t access	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_test1 {
	struct __attribute__ ((packed)) {
		uint32_t access	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_test2 {
	struct __attribute__ ((packed)) {
		uint32_t access	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_test3 {
	struct __attribute__ ((packed)) {
		uint32_t access	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_test4 {
	struct __attribute__ ((packed)) {
		uint32_t access	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_test5 {
	struct __attribute__ ((packed)) {
		uint32_t access	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_test6 {
	struct __attribute__ ((packed)) {
		uint32_t access	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_test7 {
	struct __attribute__ ((packed)) {
		uint32_t access	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd49 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd50 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd51 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd52 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd53 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd54 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd55 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_rsvd56 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_etime_comp_00 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd0	: 16;
		uint32_t measure	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_etime_comp_01 {
	struct __attribute__ ((packed)) {
		uint32_t measure	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_etime_comp_02 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd0	: 16;
		uint32_t measure	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_etime_comp_03 {
	struct __attribute__ ((packed)) {
		uint32_t measure	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_etime_comp_04 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd0	: 16;
		uint32_t measure	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_etime_comp_05 {
	struct __attribute__ ((packed)) {
		uint32_t measure	: 32;
	};
	uint32_t bits;
};

union dnc_task16b_etime_comp_06 {
	struct __attribute__ ((packed)) {
		uint32_t rsvd0	: 16;
		uint32_t measure	: 16;
	};
	uint32_t bits;
};

union dnc_task16b_etime_comp_07 {
	struct __attribute__ ((packed)) {
		uint32_t measure	: 32;
	};
	uint32_t bits;
};

#endif /* _G_DNC_TASK_16B_COMMON_H_*/
