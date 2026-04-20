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

#ifndef _G_RDSN_HEAD_COMMON_H_
#define _G_RDSN_HEAD_COMMON_H_

#define ADDR_OFFSET_RDSN_HEAD_INFO0		   0x000
#define ADDR_OFFSET_RDSN_HEAD_INFO1		   0x004
#define ADDR_OFFSET_RDSN_HEAD_INFO2		   0x008
#define ADDR_OFFSET_RDSN_HEAD_INFO3		   0x00C
#define ADDR_OFFSET_RDSN_HEAD_STATUS0	   0x010
#define ADDR_OFFSET_RDSN_HEAD_STATUS1	   0x014
#define ADDR_OFFSET_RDSN_HEAD_STATUS2	   0x018
#define ADDR_OFFSET_RDSN_HEAD_STATUS3	   0x01C
#define ADDR_OFFSET_RDSN_HEAD_STATUS4	   0x020
#define ADDR_OFFSET_RDSN_HEAD_STATUS5	   0x024
#define ADDR_OFFSET_RDSN_HEAD_EOR		   0x030
#define ADDR_OFFSET_RDSN_HEAD_INTR_VEC0	   0x040
#define ADDR_OFFSET_RDSN_HEAD_INTR_VEC1	   0x044
#define ADDR_OFFSET_RDSN_HEAD_INTR_VEC2	   0x048
#define ADDR_OFFSET_RDSN_HEAD_INTR_VEC3	   0x04C
#define ADDR_OFFSET_RDSN_HEAD_TE0_RPT0	   0x080
#define ADDR_OFFSET_RDSN_HEAD_TE0_RPT1	   0x084
#define ADDR_OFFSET_RDSN_HEAD_TE0_RPT2	   0x088
#define ADDR_OFFSET_RDSN_HEAD_TE0_RPT3	   0x08C
#define ADDR_OFFSET_RDSN_HEAD_TE3_RPT0	   0x090
#define ADDR_OFFSET_RDSN_HEAD_TE3_RPT1	   0x094
#define ADDR_OFFSET_RDSN_HEAD_TE3_RPT2	   0x098
#define ADDR_OFFSET_RDSN_HEAD_TE3_RPT3	   0x09C
#define ADDR_OFFSET_RDSN_HEAD_TE0_LAT_RPT0 0x0A0
#define ADDR_OFFSET_RDSN_HEAD_TE0_LAT_RPT1 0x0A4
#define ADDR_OFFSET_RDSN_HEAD_TE0_LAT_RPT2 0x0A8
#define ADDR_OFFSET_RDSN_HEAD_TE0_LAT_RPT3 0x0AC
#define ADDR_OFFSET_RDSN_HEAD_TE3_LAT_RPT0 0x0B0
#define ADDR_OFFSET_RDSN_HEAD_TE3_LAT_RPT1 0x0B4
#define ADDR_OFFSET_RDSN_HEAD_TE3_LAT_RPT2 0x0B8
#define ADDR_OFFSET_RDSN_HEAD_TE3_LAT_RPT3 0x0BC
#define ADDR_OFFSET_RDSN_HEAD_CMD_LOG0	   0x0E0
#define ADDR_OFFSET_RDSN_HEAD_CMD_LOG1	   0x0E4
#define ADDR_OFFSET_RDSN_HEAD_CMD_LOG2	   0x0E8
#define ADDR_OFFSET_RDSN_HEAD_CMD_LOG3	   0x0EC
#define ADDR_OFFSET_RDSN_HEAD_CMD_LOG4	   0x0F0
#define ADDR_OFFSET_RDSN_HEAD_CMD_LOG5	   0x0F4
#define ADDR_OFFSET_RDSN_HEAD_CMD_LOG6	   0x0F8
#define ADDR_OFFSET_RDSN_HEAD_CMD_LOG7	   0x0FC
#define ADDR_OFFSET_RDSN_HEAD_CTRL0		   0x100
#define ADDR_OFFSET_RDSN_HEAD_CTRL1		   0x104
#define ADDR_OFFSET_RDSN_HEAD_INTR_MASK0   0x140
#define ADDR_OFFSET_RDSN_HEAD_INTR_MASK1   0x144
#define ADDR_OFFSET_RDSN_HEAD_INTR_MASK2   0x148
#define ADDR_OFFSET_RDSN_HEAD_INTR_MASK3   0x14C
#define ADDR_OFFSET_RDSN_HEAD_QCH		   0x1E0
#define ADDR_OFFSET_RDSN_HEAD_TEST0		   0x1F0
#define ADDR_OFFSET_RDSN_HEAD_TEST1		   0x1F4
#define ADDR_OFFSET_RDSN_HEAD_TEST2		   0x1F8
#define ADDR_OFFSET_RDSN_HEAD_TEST3		   0x1FC
#define ADDR_OFFSET_RDSN_HEAD_CMD00		   0x200
#define ADDR_OFFSET_RDSN_HEAD_CMD01		   0x204
#define ADDR_OFFSET_RDSN_HEAD_CMD02		   0x208
#define ADDR_OFFSET_RDSN_HEAD_CMD03		   0x20C
#define ADDR_OFFSET_RDSN_HEAD_CMD04		   0x210
#define ADDR_OFFSET_RDSN_HEAD_CMD05		   0x214
#define ADDR_OFFSET_RDSN_HEAD_CMD06		   0x218
#define ADDR_OFFSET_RDSN_HEAD_CMD07		   0x21C
#define ADDR_OFFSET_RDSN_HEAD_CMD08		   0x220
#define ADDR_OFFSET_RDSN_HEAD_CMD09		   0x224
#define ADDR_OFFSET_RDSN_HEAD_CMD10		   0x228
#define ADDR_OFFSET_RDSN_HEAD_CMD11		   0x22C
#define ADDR_OFFSET_RDSN_HEAD_CMD12		   0x230
#define ADDR_OFFSET_RDSN_HEAD_CMD13		   0x234
#define ADDR_OFFSET_RDSN_HEAD_CMD14		   0x238
#define ADDR_OFFSET_RDSN_HEAD_CMD15		   0x23C
#define ADDR_OFFSET_RDSN_HEAD_RSP00		   0x300
#define ADDR_OFFSET_RDSN_HEAD_RSP01		   0x304
#define ADDR_OFFSET_RDSN_HEAD_RSP02		   0x308
#define ADDR_OFFSET_RDSN_HEAD_RSP03		   0x30C
#define ADDR_OFFSET_RDSN_HEAD_RSP04		   0x310
#define ADDR_OFFSET_RDSN_HEAD_RSP05		   0x314
#define ADDR_OFFSET_RDSN_HEAD_RSP06		   0x318
#define ADDR_OFFSET_RDSN_HEAD_RSP07		   0x31C
#define ADDR_OFFSET_RDSN_HEAD_RSP08		   0x320
#define ADDR_OFFSET_RDSN_HEAD_RSP09		   0x324
#define ADDR_OFFSET_RDSN_HEAD_RSP10		   0x328
#define ADDR_OFFSET_RDSN_HEAD_RSP11		   0x32C
#define ADDR_OFFSET_RDSN_HEAD_RSP12		   0x330
#define ADDR_OFFSET_RDSN_HEAD_RSP13		   0x334
#define ADDR_OFFSET_RDSN_HEAD_RSP14		   0x338
#define ADDR_OFFSET_RDSN_HEAD_RSP15		   0x33C

union rdsn_head_info0 {
	struct __attribute__((packed)) {
		uint32_t release_date : 32;
	};
	uint32_t bits;
};

union rdsn_head_info1 {
	struct __attribute__((packed)) {
		uint32_t version : 32;
	};
	uint32_t bits;
};

union rdsn_head_info2 {
	struct __attribute__((packed)) {
		uint32_t revision : 32;
	};
	uint32_t bits;
};

union rdsn_head_info3 {
	struct __attribute__((packed)) {
		uint32_t num_col : 8;
		uint32_t reserved8 : 8;
		uint32_t depth_cse_req : 8;
		uint32_t depth_cse_rsp : 8;
	};
	uint32_t bits;
};

union rdsn_head_status0 {
	struct __attribute__((packed)) {
		uint32_t init0 : 1;
		uint32_t init1 : 1;
		uint32_t init2 : 1;
		uint32_t init3 : 1;
		uint32_t reserved4 : 12;
		uint32_t config0 : 1;
		uint32_t config1 : 1;
		uint32_t config2 : 1;
		uint32_t config3 : 1;
		uint32_t reserved20 : 12;
	};
	uint32_t bits;
};

union rdsn_head_status1 {
	struct __attribute__((packed)) {
		uint32_t idle0 : 1;
		uint32_t idle1 : 1;
		uint32_t idle2 : 1;
		uint32_t idle3 : 1;
		uint32_t reserved4 : 12;
		uint32_t except0 : 1;
		uint32_t except1 : 1;
		uint32_t except2 : 1;
		uint32_t except3 : 1;
		uint32_t reserved20 : 12;
	};
	uint32_t bits;
};

union rdsn_head_status2 {
	struct __attribute__((packed)) {
		uint32_t num_rsp : 8;
		uint32_t rsp_empty : 1;
		uint32_t rsp_full : 1;
		uint32_t reserved10 : 1;
		uint32_t reserved11 : 1;
		uint32_t req_empty : 1;
		uint32_t req_full : 1;
		uint32_t reserved14 : 1;
		uint32_t reserved15 : 1;
		uint32_t num_otf_cmd : 16;
	};
	uint32_t bits;
};

union rdsn_head_status3 {
	struct __attribute__((packed)) {
		uint32_t cmd_ovf : 1;
		uint32_t cmd_udf : 1;
		uint32_t cmd_ovf_p : 1;
		uint32_t cmd_udf_p : 1;
		uint32_t reserved4 : 4;
		uint32_t rsp_ovf : 1;
		uint32_t rsp_udf : 1;
		uint32_t rsp_perr : 1;
		uint32_t reserved11 : 5;
		uint32_t wr2ro : 1;
		uint32_t wr2rsp : 1;
		uint32_t rd2cmd : 1;
		uint32_t reserved19 : 5;
		uint32_t init_tout : 1;
		uint32_t auto_cfg_tout : 1;
		uint32_t reserved26 : 6;
	};
	uint32_t bits;
};

union rdsn_head_status4 {
	struct __attribute__((packed)) {
		uint32_t init_time : 32;
	};
	uint32_t bits;
};

union rdsn_head_status5 {
	struct __attribute__((packed)) {
		uint32_t auto_cfg_time : 32;
	};
	uint32_t bits;
};

union rdsn_head_eor {
	struct __attribute__((packed)) {
		uint32_t rtid0 : 8;
		uint32_t rtid1 : 8;
		uint32_t rtid2 : 8;
		uint32_t rtid3 : 8;
	};
	uint32_t bits;
};

union rdsn_head_intr_vec0 {
	struct __attribute__((packed)) {
		uint32_t row0 : 4;
		uint32_t row1 : 4;
		uint32_t row2 : 4;
		uint32_t row3 : 4;
		uint32_t row4 : 4;
		uint32_t row5 : 4;
		uint32_t row6 : 4;
		uint32_t row7 : 4;
	};
	uint32_t bits;
};

union rdsn_head_intr_vec1 {
	struct __attribute__((packed)) {
		uint32_t row0 : 4;
		uint32_t row1 : 4;
		uint32_t row2 : 4;
		uint32_t row3 : 4;
		uint32_t row4 : 4;
		uint32_t row5 : 4;
		uint32_t row6 : 4;
		uint32_t row7 : 4;
	};
	uint32_t bits;
};

union rdsn_head_intr_vec2 {
	struct __attribute__((packed)) {
		uint32_t row0 : 4;
		uint32_t row1 : 4;
		uint32_t row2 : 4;
		uint32_t row3 : 4;
		uint32_t row4 : 4;
		uint32_t row5 : 4;
		uint32_t row6 : 4;
		uint32_t row7 : 4;
	};
	uint32_t bits;
};

union rdsn_head_intr_vec3 {
	struct __attribute__((packed)) {
		uint32_t row0 : 4;
		uint32_t row1 : 4;
		uint32_t row2 : 4;
		uint32_t row3 : 4;
		uint32_t row4 : 4;
		uint32_t row5 : 4;
		uint32_t row6 : 4;
		uint32_t row7 : 4;
	};
	uint32_t bits;
};

union rdsn_head_te0_rpt0 {
	struct __attribute__((packed)) {
		uint32_t timeout : 1;
		uint32_t valid : 1;
		uint32_t pass : 1;
		uint32_t reserved3 : 29;
	};
	uint32_t bits;
};

union rdsn_head_te0_rpt1 {
	struct __attribute__((packed)) {
		uint32_t pass_map_d : 32;
	};
	uint32_t bits;
};

union rdsn_head_te0_rpt2 {
	struct __attribute__((packed)) {
		uint32_t pass_map_r : 32;
	};
	uint32_t bits;
};

union rdsn_head_te0_rpt3 {
	struct __attribute__((packed)) {
		uint32_t pass_map_c : 32;
	};
	uint32_t bits;
};

union rdsn_head_te3_rpt0 {
	struct __attribute__((packed)) {
		uint32_t timeout : 1;
		uint32_t valid : 1;
		uint32_t pass : 1;
		uint32_t reserved3 : 29;
	};
	uint32_t bits;
};

union rdsn_head_te3_rpt1 {
	struct __attribute__((packed)) {
		uint32_t pass_map_d : 32;
	};
	uint32_t bits;
};

union rdsn_head_te3_rpt2 {
	struct __attribute__((packed)) {
		uint32_t pass_map_r : 32;
	};
	uint32_t bits;
};

union rdsn_head_te3_rpt3 {
	struct __attribute__((packed)) {
		uint32_t pass_map_c : 32;
	};
	uint32_t bits;
};

union rdsn_head_te0_lat_rpt0 {
	struct __attribute__((packed)) {
		uint32_t lat0 : 8;
		uint32_t lat1 : 8;
		uint32_t lat2 : 8;
		uint32_t reserved24 : 8;
	};
	uint32_t bits;
};

union rdsn_head_te0_lat_rpt1 {
	struct __attribute__((packed)) {
		uint32_t lat0 : 8;
		uint32_t lat1 : 8;
		uint32_t lat2 : 8;
		uint32_t reserved24 : 8;
	};
	uint32_t bits;
};

union rdsn_head_te0_lat_rpt2 {
	struct __attribute__((packed)) {
		uint32_t lat0 : 8;
		uint32_t lat1 : 8;
		uint32_t lat2 : 8;
		uint32_t reserved24 : 8;
	};
	uint32_t bits;
};

union rdsn_head_te0_lat_rpt3 {
	struct __attribute__((packed)) {
		uint32_t lat0 : 8;
		uint32_t lat1 : 8;
		uint32_t lat2 : 8;
		uint32_t reserved24 : 8;
	};
	uint32_t bits;
};

union rdsn_head_te3_lat_rpt0 {
	struct __attribute__((packed)) {
		uint32_t lat0 : 8;
		uint32_t lat1 : 8;
		uint32_t lat2 : 8;
		uint32_t reserved24 : 8;
	};
	uint32_t bits;
};

union rdsn_head_te3_lat_rpt1 {
	struct __attribute__((packed)) {
		uint32_t lat0 : 8;
		uint32_t lat1 : 8;
		uint32_t lat2 : 8;
		uint32_t reserved24 : 8;
	};
	uint32_t bits;
};

union rdsn_head_te3_lat_rpt2 {
	struct __attribute__((packed)) {
		uint32_t lat0 : 8;
		uint32_t lat1 : 8;
		uint32_t lat2 : 8;
		uint32_t reserved24 : 8;
	};
	uint32_t bits;
};

union rdsn_head_te3_lat_rpt3 {
	struct __attribute__((packed)) {
		uint32_t lat0 : 8;
		uint32_t lat1 : 8;
		uint32_t lat2 : 8;
		uint32_t reserved24 : 8;
	};
	uint32_t bits;
};

union rdsn_head_cmd_log0 {
	struct __attribute__((packed)) {
		uint32_t last_cmd0 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd_log1 {
	struct __attribute__((packed)) {
		uint32_t last_cmd1 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd_log2 {
	struct __attribute__((packed)) {
		uint32_t last_cmd2 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd_log3 {
	struct __attribute__((packed)) {
		uint32_t last_cmd3 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd_log4 {
	struct __attribute__((packed)) {
		uint32_t last_cmd4 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd_log5 {
	struct __attribute__((packed)) {
		uint32_t last_cmd5 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd_log6 {
	struct __attribute__((packed)) {
		uint32_t last_cmd6 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd_log7 {
	struct __attribute__((packed)) {
		uint32_t last_cmd7 : 32;
	};
	uint32_t bits;
};

union rdsn_head_ctrl0 {
	struct __attribute__((packed)) {
		uint32_t clear_rdsn : 1;
		uint32_t clear_head : 1;
		uint32_t reserved2 : 6;
		uint32_t cfg_chiplet_id_trig : 1;
		uint32_t reserved9 : 7;
		uint32_t trig_dtest0 : 1;
		uint32_t trig_dtest3 : 1;
		uint32_t reserved18 : 14;
	};
	uint32_t bits;
};

union rdsn_head_ctrl1 {
	struct __attribute__((packed)) {
		uint32_t custom_config : 1;
		uint32_t cmd_log : 1;
		uint32_t reserved2 : 2;
		uint32_t dclst_id : 1;
		uint32_t reserved5 : 3;
		uint32_t chiplet_id : 2;
		uint32_t reserved10 : 6;
		uint32_t dtest_pat_even : 4;
		uint32_t dtest_pat_odd : 4;
		uint32_t dtest_short : 1;
		uint32_t reserved25 : 7;
	};
	uint32_t bits;
};

union rdsn_head_intr_mask0 {
	struct __attribute__((packed)) {
		uint32_t row0 : 4;
		uint32_t row1 : 4;
		uint32_t row2 : 4;
		uint32_t row3 : 4;
		uint32_t row4 : 4;
		uint32_t row5 : 4;
		uint32_t row6 : 4;
		uint32_t row7 : 4;
	};
	uint32_t bits;
};

union rdsn_head_intr_mask1 {
	struct __attribute__((packed)) {
		uint32_t row0 : 4;
		uint32_t row1 : 4;
		uint32_t row2 : 4;
		uint32_t row3 : 4;
		uint32_t row4 : 4;
		uint32_t row5 : 4;
		uint32_t row6 : 4;
		uint32_t row7 : 4;
	};
	uint32_t bits;
};

union rdsn_head_intr_mask2 {
	struct __attribute__((packed)) {
		uint32_t row0 : 4;
		uint32_t row1 : 4;
		uint32_t row2 : 4;
		uint32_t row3 : 4;
		uint32_t row4 : 4;
		uint32_t row5 : 4;
		uint32_t row6 : 4;
		uint32_t row7 : 4;
	};
	uint32_t bits;
};

union rdsn_head_intr_mask3 {
	struct __attribute__((packed)) {
		uint32_t row0 : 4;
		uint32_t row1 : 4;
		uint32_t row2 : 4;
		uint32_t row3 : 4;
		uint32_t row4 : 4;
		uint32_t row5 : 4;
		uint32_t row6 : 4;
		uint32_t row7 : 4;
	};
	uint32_t bits;
};

union rdsn_head_qch {
	struct __attribute__((packed)) {
		uint32_t qreqn : 1;
		uint32_t qacceptn : 1;
		uint32_t qdeny : 1;
		uint32_t qactive : 1;
		uint32_t reserved4 : 28;
	};
	uint32_t bits;
};

union rdsn_head_test0 {
	struct __attribute__((packed)) {
		uint32_t space : 32;
	};
	uint32_t bits;
};

union rdsn_head_test1 {
	struct __attribute__((packed)) {
		uint32_t space : 32;
	};
	uint32_t bits;
};

union rdsn_head_test2 {
	struct __attribute__((packed)) {
		uint32_t space : 32;
	};
	uint32_t bits;
};

union rdsn_head_test3 {
	struct __attribute__((packed)) {
		uint32_t space : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd00 {
	struct __attribute__((packed)) {
		uint32_t passage00 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd01 {
	struct __attribute__((packed)) {
		uint32_t passage01 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd02 {
	struct __attribute__((packed)) {
		uint32_t passage02 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd03 {
	struct __attribute__((packed)) {
		uint32_t passage03 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd04 {
	struct __attribute__((packed)) {
		uint32_t passage04 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd05 {
	struct __attribute__((packed)) {
		uint32_t passage05 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd06 {
	struct __attribute__((packed)) {
		uint32_t passage06 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd07 {
	struct __attribute__((packed)) {
		uint32_t passage07 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd08 {
	struct __attribute__((packed)) {
		uint32_t passage08 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd09 {
	struct __attribute__((packed)) {
		uint32_t passage09 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd10 {
	struct __attribute__((packed)) {
		uint32_t passage10 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd11 {
	struct __attribute__((packed)) {
		uint32_t passage11 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd12 {
	struct __attribute__((packed)) {
		uint32_t passage12 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd13 {
	struct __attribute__((packed)) {
		uint32_t passage13 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd14 {
	struct __attribute__((packed)) {
		uint32_t passage14 : 32;
	};
	uint32_t bits;
};

union rdsn_head_cmd15 {
	struct __attribute__((packed)) {
		uint32_t passage15 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp00 {
	struct __attribute__((packed)) {
		uint32_t passage00 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp01 {
	struct __attribute__((packed)) {
		uint32_t passage01 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp02 {
	struct __attribute__((packed)) {
		uint32_t passage02 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp03 {
	struct __attribute__((packed)) {
		uint32_t passage03 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp04 {
	struct __attribute__((packed)) {
		uint32_t passage04 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp05 {
	struct __attribute__((packed)) {
		uint32_t passage05 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp06 {
	struct __attribute__((packed)) {
		uint32_t passage06 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp07 {
	struct __attribute__((packed)) {
		uint32_t passage07 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp08 {
	struct __attribute__((packed)) {
		uint32_t passage08 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp09 {
	struct __attribute__((packed)) {
		uint32_t passage09 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp10 {
	struct __attribute__((packed)) {
		uint32_t passage10 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp11 {
	struct __attribute__((packed)) {
		uint32_t passage11 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp12 {
	struct __attribute__((packed)) {
		uint32_t passage12 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp13 {
	struct __attribute__((packed)) {
		uint32_t passage13 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp14 {
	struct __attribute__((packed)) {
		uint32_t passage14 : 32;
	};
	uint32_t bits;
};

union rdsn_head_rsp15 {
	struct __attribute__((packed)) {
		uint32_t passage15 : 32;
	};
	uint32_t bits;
};

#endif /* _G_RDSN_HEAD_COMMON_H_*/
