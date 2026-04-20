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

#ifndef _G_DNC_UAN_NC_COMMON_H_
#define _G_DNC_UAN_NC_COMMON_H_

#define ADDR_OFFSET_DNC_UAN_NC_UNIT_INFO 0x000
#define ADDR_OFFSET_DNC_UAN_NC_SPR_45	 0x008
#define ADDR_OFFSET_DNC_UAN_NC_SPR_67	 0x00C
#define ADDR_OFFSET_DNC_UAN_NC_IF_CTRL	 0x100
#define ADDR_OFFSET_DNC_UAN_NC_SE_CTRL	 0x104
#define ADDR_OFFSET_DNC_UAN_NC_AGU_CTRL	 0x108
#define ADDR_OFFSET_DNC_UAN_NC_LSU_CTRL	 0x110
#define ADDR_OFFSET_DNC_UAN_NC_PCFG_00	 0x200
#define ADDR_OFFSET_DNC_UAN_NC_PCFG_01	 0x204
#define ADDR_OFFSET_DNC_UAN_NC_PCFG_02	 0x208
#define ADDR_OFFSET_DNC_UAN_NC_PCFG_03	 0x20C
#define ADDR_OFFSET_DNC_UAN_NC_STAT_00	 0x210
#define ADDR_OFFSET_DNC_UAN_NC_STAT_01	 0x214
#define ADDR_OFFSET_DNC_UAN_NC_STAT_02	 0x218
#define ADDR_OFFSET_DNC_UAN_NC_STAT_03	 0x21C
#define ADDR_OFFSET_DNC_UAN_NC_USTAT_00	 0x220
#define ADDR_OFFSET_DNC_UAN_NC_USTAT_01	 0x224
#define ADDR_OFFSET_DNC_UAN_NC_USTAT_02	 0x228
#define ADDR_OFFSET_DNC_UAN_NC_USTAT_03	 0x22C
#define ADDR_OFFSET_DNC_UAN_NC_USTAT_04	 0x230
#define ADDR_OFFSET_DNC_UAN_NC_JCR_0	 0x300
#define ADDR_OFFSET_DNC_UAN_NC_JCR_1	 0x304
#define ADDR_OFFSET_DNC_UAN_NC_JCR_2	 0x308
#define ADDR_OFFSET_DNC_UAN_NC_JCR_3	 0x30C
#define ADDR_OFFSET_DNC_UAN_NC_JCR_4	 0x310
#define ADDR_OFFSET_DNC_UAN_NC_JCR_5	 0x314
#define ADDR_OFFSET_DNC_UAN_NC_JCR_6	 0x318
#define ADDR_OFFSET_DNC_UAN_NC_JCR_7	 0x31C
#define ADDR_OFFSET_DNC_UAN_NC_JCR_8	 0x320
#define ADDR_OFFSET_DNC_UAN_NC_JCR_9	 0x324
#define ADDR_OFFSET_DNC_UAN_NC_JCR_10	 0x328
#define ADDR_OFFSET_DNC_UAN_NC_JCR_11	 0x32C
#define ADDR_OFFSET_DNC_UAN_NC_JCR_12	 0x330
#define ADDR_OFFSET_DNC_UAN_NC_JCR_13	 0x334
#define ADDR_OFFSET_DNC_UAN_NC_JCR_14	 0x338
#define ADDR_OFFSET_DNC_UAN_NC_JCR_15	 0x33C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_0	 0x400
#define ADDR_OFFSET_DNC_UAN_NC_LRF_1	 0x404
#define ADDR_OFFSET_DNC_UAN_NC_LRF_2	 0x408
#define ADDR_OFFSET_DNC_UAN_NC_LRF_3	 0x40C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_4	 0x410
#define ADDR_OFFSET_DNC_UAN_NC_LRF_5	 0x414
#define ADDR_OFFSET_DNC_UAN_NC_LRF_6	 0x418
#define ADDR_OFFSET_DNC_UAN_NC_LRF_7	 0x41C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_8	 0x420
#define ADDR_OFFSET_DNC_UAN_NC_LRF_9	 0x424
#define ADDR_OFFSET_DNC_UAN_NC_LRF_10	 0x428
#define ADDR_OFFSET_DNC_UAN_NC_LRF_11	 0x42C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_12	 0x430
#define ADDR_OFFSET_DNC_UAN_NC_LRF_13	 0x434
#define ADDR_OFFSET_DNC_UAN_NC_LRF_14	 0x438
#define ADDR_OFFSET_DNC_UAN_NC_LRF_15	 0x43C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_16	 0x440
#define ADDR_OFFSET_DNC_UAN_NC_LRF_17	 0x444
#define ADDR_OFFSET_DNC_UAN_NC_LRF_18	 0x448
#define ADDR_OFFSET_DNC_UAN_NC_LRF_19	 0x44C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_20	 0x450
#define ADDR_OFFSET_DNC_UAN_NC_LRF_21	 0x454
#define ADDR_OFFSET_DNC_UAN_NC_LRF_22	 0x458
#define ADDR_OFFSET_DNC_UAN_NC_LRF_23	 0x45C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_24	 0x460
#define ADDR_OFFSET_DNC_UAN_NC_LRF_25	 0x464
#define ADDR_OFFSET_DNC_UAN_NC_LRF_26	 0x468
#define ADDR_OFFSET_DNC_UAN_NC_LRF_27	 0x46C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_28	 0x470
#define ADDR_OFFSET_DNC_UAN_NC_LRF_29	 0x474
#define ADDR_OFFSET_DNC_UAN_NC_LRF_30	 0x478
#define ADDR_OFFSET_DNC_UAN_NC_LRF_31	 0x47C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_32	 0x480
#define ADDR_OFFSET_DNC_UAN_NC_LRF_33	 0x484
#define ADDR_OFFSET_DNC_UAN_NC_LRF_34	 0x488
#define ADDR_OFFSET_DNC_UAN_NC_LRF_35	 0x48C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_36	 0x490
#define ADDR_OFFSET_DNC_UAN_NC_LRF_37	 0x494
#define ADDR_OFFSET_DNC_UAN_NC_LRF_38	 0x498
#define ADDR_OFFSET_DNC_UAN_NC_LRF_39	 0x49C
#define ADDR_OFFSET_DNC_UAN_NC_LRF_40	 0x4A0
#define ADDR_OFFSET_DNC_UAN_NC_LRF_41	 0x4A4
#define ADDR_OFFSET_DNC_UAN_NC_LRF_42	 0x4A8
#define ADDR_OFFSET_DNC_UAN_NC_LRF_43	 0x4AC
#define ADDR_OFFSET_DNC_UAN_NC_LRF_44	 0x4B0
#define ADDR_OFFSET_DNC_UAN_NC_LRF_45	 0x4B4
#define ADDR_OFFSET_DNC_UAN_NC_LRF_46	 0x4B8
#define ADDR_OFFSET_DNC_UAN_NC_LRF_47	 0x4BC
#define ADDR_OFFSET_DNC_UAN_NC_LRF_48	 0x4C0
#define ADDR_OFFSET_DNC_UAN_NC_LRF_49	 0x4C4
#define ADDR_OFFSET_DNC_UAN_NC_LRF_50	 0x4C8
#define ADDR_OFFSET_DNC_UAN_NC_LRF_51	 0x4CC
#define ADDR_OFFSET_DNC_UAN_NC_LRF_52	 0x4D0
#define ADDR_OFFSET_DNC_UAN_NC_LRF_53	 0x4D4
#define ADDR_OFFSET_DNC_UAN_NC_LRF_54	 0x4D8
#define ADDR_OFFSET_DNC_UAN_NC_LRF_55	 0x4DC
#define ADDR_OFFSET_DNC_UAN_NC_LRF_56	 0x4E0
#define ADDR_OFFSET_DNC_UAN_NC_LRF_57	 0x4E4
#define ADDR_OFFSET_DNC_UAN_NC_LRF_58	 0x4E8
#define ADDR_OFFSET_DNC_UAN_NC_LRF_59	 0x4EC
#define ADDR_OFFSET_DNC_UAN_NC_LRF_60	 0x4F0
#define ADDR_OFFSET_DNC_UAN_NC_LRF_61	 0x4F4
#define ADDR_OFFSET_DNC_UAN_NC_LRF_62	 0x4F8
#define ADDR_OFFSET_DNC_UAN_NC_LRF_63	 0x4FC
#define ADDR_OFFSET_DNC_UAN_NC_TLB_0	 0x500
#define ADDR_OFFSET_DNC_UAN_NC_TLB_1	 0x504
#define ADDR_OFFSET_DNC_UAN_NC_TLB_2	 0x508
#define ADDR_OFFSET_DNC_UAN_NC_TLB_3	 0x50C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_4	 0x510
#define ADDR_OFFSET_DNC_UAN_NC_TLB_5	 0x514
#define ADDR_OFFSET_DNC_UAN_NC_TLB_6	 0x518
#define ADDR_OFFSET_DNC_UAN_NC_TLB_7	 0x51C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_8	 0x520
#define ADDR_OFFSET_DNC_UAN_NC_TLB_9	 0x524
#define ADDR_OFFSET_DNC_UAN_NC_TLB_10	 0x528
#define ADDR_OFFSET_DNC_UAN_NC_TLB_11	 0x52C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_12	 0x530
#define ADDR_OFFSET_DNC_UAN_NC_TLB_13	 0x534
#define ADDR_OFFSET_DNC_UAN_NC_TLB_14	 0x538
#define ADDR_OFFSET_DNC_UAN_NC_TLB_15	 0x53C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_16	 0x540
#define ADDR_OFFSET_DNC_UAN_NC_TLB_17	 0x544
#define ADDR_OFFSET_DNC_UAN_NC_TLB_18	 0x548
#define ADDR_OFFSET_DNC_UAN_NC_TLB_19	 0x54C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_20	 0x550
#define ADDR_OFFSET_DNC_UAN_NC_TLB_21	 0x554
#define ADDR_OFFSET_DNC_UAN_NC_TLB_22	 0x558
#define ADDR_OFFSET_DNC_UAN_NC_TLB_23	 0x55C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_24	 0x560
#define ADDR_OFFSET_DNC_UAN_NC_TLB_25	 0x564
#define ADDR_OFFSET_DNC_UAN_NC_TLB_26	 0x568
#define ADDR_OFFSET_DNC_UAN_NC_TLB_27	 0x56C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_28	 0x570
#define ADDR_OFFSET_DNC_UAN_NC_TLB_29	 0x574
#define ADDR_OFFSET_DNC_UAN_NC_TLB_30	 0x578
#define ADDR_OFFSET_DNC_UAN_NC_TLB_31	 0x57C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_32	 0x580
#define ADDR_OFFSET_DNC_UAN_NC_TLB_33	 0x584
#define ADDR_OFFSET_DNC_UAN_NC_TLB_34	 0x588
#define ADDR_OFFSET_DNC_UAN_NC_TLB_35	 0x58C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_36	 0x590
#define ADDR_OFFSET_DNC_UAN_NC_TLB_37	 0x594
#define ADDR_OFFSET_DNC_UAN_NC_TLB_38	 0x598
#define ADDR_OFFSET_DNC_UAN_NC_TLB_39	 0x59C
#define ADDR_OFFSET_DNC_UAN_NC_TLB_40	 0x5A0
#define ADDR_OFFSET_DNC_UAN_NC_TLB_41	 0x5A4
#define ADDR_OFFSET_DNC_UAN_NC_TLB_42	 0x5A8
#define ADDR_OFFSET_DNC_UAN_NC_TLB_43	 0x5AC
#define ADDR_OFFSET_DNC_UAN_NC_TLB_44	 0x5B0
#define ADDR_OFFSET_DNC_UAN_NC_TLB_45	 0x5B4
#define ADDR_OFFSET_DNC_UAN_NC_TLB_46	 0x5B8
#define ADDR_OFFSET_DNC_UAN_NC_TLB_47	 0x5BC
#define ADDR_OFFSET_DNC_UAN_NC_TLB_48	 0x5C0
#define ADDR_OFFSET_DNC_UAN_NC_TLB_49	 0x5C4
#define ADDR_OFFSET_DNC_UAN_NC_TLB_50	 0x5C8
#define ADDR_OFFSET_DNC_UAN_NC_TLB_51	 0x5CC
#define ADDR_OFFSET_DNC_UAN_NC_TLB_52	 0x5D0
#define ADDR_OFFSET_DNC_UAN_NC_TLB_53	 0x5D4
#define ADDR_OFFSET_DNC_UAN_NC_TLB_54	 0x5D8
#define ADDR_OFFSET_DNC_UAN_NC_TLB_55	 0x5DC
#define ADDR_OFFSET_DNC_UAN_NC_TLB_56	 0x5E0
#define ADDR_OFFSET_DNC_UAN_NC_TLB_57	 0x5E4
#define ADDR_OFFSET_DNC_UAN_NC_TLB_58	 0x5E8
#define ADDR_OFFSET_DNC_UAN_NC_TLB_59	 0x5EC
#define ADDR_OFFSET_DNC_UAN_NC_TLB_60	 0x5F0
#define ADDR_OFFSET_DNC_UAN_NC_TLB_61	 0x5F4
#define ADDR_OFFSET_DNC_UAN_NC_TLB_62	 0x5F8
#define ADDR_OFFSET_DNC_UAN_NC_TLB_63	 0x5FC

union dnc_uan_nc_unit_info {
	struct __attribute__((packed)) {
		uint32_t core_id : 4;
		uint32_t unit_id : 4;
		uint32_t sub_unit_id : 4;
		uint32_t op : 4;
		uint32_t reserved : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_spr_45 {
	struct __attribute__((packed)) {
		uint32_t machine_exc_en_mask : 16;
		uint32_t machine_exc_type : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_spr_67 {
	struct __attribute__((packed)) {
		uint32_t fp_exc_report_en : 1;
		uint32_t fp_exc_slice : 3;
		uint32_t fp_exc_mask : 8;
		uint32_t reserved : 12;
		uint32_t exc_pc : 8;
	};
	uint32_t bits;
};

union dnc_uan_nc_if_ctrl {
	struct __attribute__((packed)) {
		uint32_t if_cfg : 3;
		uint32_t reserved0 : 1;
		uint32_t reserved1 : 28;
	};
	uint32_t bits;
};

union dnc_uan_nc_se_ctrl {
	struct __attribute__((packed)) {
		uint32_t chiplet_id : 2;
		uint32_t reserved0 : 2;
		uint32_t fuse : 1;
		uint32_t reserved2 : 24;
	};
	uint32_t bits;
};

union dnc_uan_nc_agu_ctrl {
	struct __attribute__((packed)) {
		uint32_t max_bl : 2;
		uint32_t reserved0 : 2;
		uint32_t qos : 2;
		uint32_t reserved1 : 2;
		uint32_t reserved2 : 24;
	};
	uint32_t bits;
};

union dnc_uan_nc_lsu_ctrl {
	struct __attribute__((packed)) {
		uint32_t switch_mode : 3;
		uint32_t reserved0 : 1;
		uint32_t mo_mode : 1;
		uint32_t default_bl : 2;
		uint32_t mo_main : 8;
		uint32_t mo_sub_p0 : 8;
		uint32_t mo_sub_p1 : 8;
	};
	uint32_t bits;
};

union dnc_uan_nc_pcfg_00 {
	struct __attribute__((packed)) {
		uint32_t profile_mode : 2;
		uint32_t profile_cnt_src : 1;
		uint32_t reserved : 29;
	};
	uint32_t bits;
};

union dnc_uan_nc_pcfg_01 {
	struct __attribute__((packed)) {
		uint32_t profile_start : 32;
	};
	uint32_t bits;
};

union dnc_uan_nc_pcfg_02 {
	struct __attribute__((packed)) {
		uint32_t profile_window : 32;
	};
	uint32_t bits;
};

union dnc_uan_nc_pcfg_03 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union dnc_uan_nc_stat_00 {
	struct __attribute__((packed)) {
		uint32_t count_cycle : 32;
	};
	uint32_t bits;
};

union dnc_uan_nc_stat_01 {
	struct __attribute__((packed)) {
		uint32_t count_fetch : 32;
	};
	uint32_t bits;
};

union dnc_uan_nc_stat_02 {
	struct __attribute__((packed)) {
		uint32_t prog_status : 2;
		uint32_t prog_pc : 8;
		uint32_t prog_lnlc : 5;
		uint32_t prog_lccr : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_stat_03 {
	struct __attribute__((packed)) {
		uint32_t reserved : 32;
	};
	uint32_t bits;
};

union dnc_uan_nc_ustat_00 {
	struct __attribute__((packed)) {
		uint32_t unit_stat0 : 16;
		uint32_t unit_stat1 : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_ustat_01 {
	struct __attribute__((packed)) {
		uint32_t unit_stat2 : 16;
		uint32_t unit_stat3 : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_ustat_02 {
	struct __attribute__((packed)) {
		uint32_t unit_stat4 : 16;
		uint32_t unit_stat5 : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_ustat_03 {
	struct __attribute__((packed)) {
		uint32_t unit_stat6 : 16;
		uint32_t unit_stat7 : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_ustat_04 {
	struct __attribute__((packed)) {
		uint32_t unit_stat8 : 16;
		uint32_t unit_stat9 : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_0 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_1 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_2 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_3 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_4 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_5 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_6 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_7 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_8 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_9 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_10 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_11 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_12 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_13 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_14 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_jcr_15 {
	struct __attribute__((packed)) {
		uint32_t data : 16;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_0 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_1 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_2 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_3 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_4 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_5 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_6 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_7 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_8 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_9 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_10 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_11 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_12 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_13 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_14 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_15 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_16 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_17 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_18 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_19 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_20 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_21 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_22 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_23 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_24 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_25 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_26 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_27 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_28 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_29 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_30 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_31 {
	struct __attribute__((packed)) {
		uint32_t data : 15;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_32 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_33 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_34 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_35 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_36 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_37 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_38 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_39 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_40 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_41 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_42 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_43 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_44 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_45 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_46 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_47 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_48 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_49 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_50 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_51 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_52 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_53 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_54 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_55 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_56 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_57 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_58 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_59 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_60 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_61 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_62 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_lrf_63 {
	struct __attribute__((packed)) {
		uint32_t data : 21;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_0 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_1 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_2 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_3 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_4 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_5 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_6 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_7 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_8 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_9 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_10 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_11 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_12 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_13 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_14 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_15 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_16 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_17 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_18 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_19 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_20 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_21 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_22 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_23 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_24 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_25 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_26 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_27 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_28 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_29 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_30 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_31 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_32 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_33 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_34 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_35 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_36 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_37 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_38 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_39 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_40 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_41 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_42 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_43 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_44 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_45 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_46 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_47 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_48 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_49 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_50 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_51 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_52 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_53 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_54 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_55 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_56 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_57 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_58 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_59 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_60 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_61 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_62 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

union dnc_uan_nc_tlb_63 {
	struct __attribute__((packed)) {
		uint32_t ppn : 19;
		uint32_t reserved : 7;
		uint32_t attribute : 6;
	};
	uint32_t bits;
};

enum dnc_uan_nc_pcfg_00_profile_cnt_src {
	DNC_UAN_NC_PCFG_00_PROFILE_CNT_SRC_CLK_CYCLE,
	DNC_UAN_NC_PCFG_00_PROFILE_CNT_SRC_FETCH_CNT,
};

#endif /* _G_DNC_UAN_NC_COMMON_H_*/
