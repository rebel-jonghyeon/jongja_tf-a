/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2025 [Rebellions Inc.], All Rights Reserved.
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

#ifndef __TB_RBC_GLUE_REG_MODEL_
#define __TB_RBC_GLUE_REG_MODEL_

#ifndef UNBUFFERED_DECL
#define UNBUFFERED_DECL(DECL) DECL __attribute__((unused))
#endif

#ifndef UNBUFFERED_ATTR
#define UNBUFFERED_ATTR __attribute__((unused))
#endif

struct rbc_reg_ip_info0_t {
	union {
		uint32_t value;
		uint32_t release_date; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t release_date;
		})
		unbuffered;
	};
};

struct rbc_reg_ip_info1_t {
	union {
		uint32_t value;
		struct {
			uint32_t min_ver : 8; /* [7:0]   RO */
			uint32_t maj_ver : 8; /* [15:8]  RO */
			uint32_t ip_ver : 8; /* [23:16] RO */
			uint32_t ip_id : 8; /* [31:24] RO */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t min_ver : 8;
				uint32_t maj_ver : 8;
				uint32_t ip_ver : 8;
				uint32_t ip_id : 8;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_ip_info2_t {
	union {
		uint32_t value;
		struct {
			uint32_t global_nid0 : 8; /* [7:0]   RW */
			uint32_t global_nid1 : 8; /* [15:8]  RW */
			uint32_t global_nid2 : 8; /* [23:16] RW */
			uint32_t global_nid3 : 8; /* [31:24] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t global_nid0 : 8;
				uint32_t global_nid1 : 8;
				uint32_t global_nid2 : 8;
				uint32_t global_nid3 : 8;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_ip_info3_t {
	union {
		uint32_t value;
		struct {
			uint32_t local_nid0 : 8; /* [7:0]   RO */
			uint32_t local_nid1 : 8; /* [15:8]  RO */
			uint32_t rsvd_16 : 8;
			uint32_t local_ready : 8; /* [31:24] RO */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t local_nid0 : 8;
				uint32_t local_nid1 : 8;
				uint32_t rsvd_16 : 8;
				uint32_t local_ready : 8;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_design_info0_t {
	union {
		uint32_t value;
		uint32_t design_info0_0_31; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t design_info0_0_31;
		})
		unbuffered;
	};
};

struct rbc_reg_design_info1_t {
	union {
		uint32_t value;
		uint32_t design_info1_0_31; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t design_info1_0_31;
		})
		unbuffered;
	};
};

struct rbc_reg_common_rpt_t {
	union {
		uint32_t value;
		uint32_t common_rpt_0_31; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t common_rpt_0_31;
		})
		unbuffered;
	};
};

struct rbc_reg_common_reg_t {
	union {
		uint32_t value;
		uint32_t common_reg_0_31; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t common_reg_0_31;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_info_t {
	union {
		uint32_t value;
		struct {
			uint32_t rsvd_0 : 3;
			uint32_t id_rbc_direction : 2; /* [4:3]   RW */
			uint32_t id_rbc_number : 3; /* [7:5]   RW */
			uint32_t rsvd_8 : 24;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t rsvd_0 : 3;
				uint32_t id_rbc_direction : 2;
				uint32_t id_rbc_number : 3;
				uint32_t rsvd_8 : 24;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_ctl_t {
	union {
		uint32_t value;
		struct {
			uint32_t sw_reset : 1; /* [0:0]   RW */
			uint32_t rsvd_1 : 31;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t sw_reset : 1;
				uint32_t rsvd_1 : 31;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_config_t {
	union {
		uint32_t value;
		struct {
			uint32_t rbc_en : 1; /* [0:0]   RW */
			uint32_t transaction_mode : 1; /* [1:1]   RW */
			uint32_t secded_en : 1; /* [2:2]   RW */
			uint32_t rsvd_3 : 1;
			uint32_t ttreg_en : 1; /* [4:4]   RW */
			uint32_t rsvd_5 : 1;
			uint32_t lb_usr_en : 1; /* [6:6]   RW */
			uint32_t trl : 1; /* [7:7]   RW */
			uint32_t bp : 1; /* [8:8]   RW */
			uint32_t rtbl_en : 1; /* [9:9]   RW */
			uint32_t intr_clr_mode : 1; /* [10:10] RW */
			uint32_t intr_oper_mode : 1; /* [11:11] RW */
			uint32_t ttreg_err_blen : 1; /* [12:12] RW */
			uint32_t ttreg_err_bseq : 1; /* [13:13] RW */
			uint32_t ttreg_err_req : 1; /* [14:14] RW */
			uint32_t ttreg_err_rsp : 1; /* [15:15] RW */
			uint32_t rsvd_16 : 16;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t rbc_en : 1;
				uint32_t transaction_mode : 1;
				uint32_t secded_en : 1;
				uint32_t rsvd_3 : 1;
				uint32_t ttreg_en : 1;
				uint32_t rsvd_5 : 1;
				uint32_t lb_usr_en : 1;
				uint32_t trl : 1;
				uint32_t bp : 1;
				uint32_t rtbl_en : 1;
				uint32_t intr_clr_mode : 1;
				uint32_t intr_oper_mode : 1;
				uint32_t ttreg_err_blen : 1;
				uint32_t ttreg_err_bseq : 1;
				uint32_t ttreg_err_req : 1;
				uint32_t ttreg_err_rsp : 1;
				uint32_t rsvd_16 : 16;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_port_config_t {
	union {
		uint32_t value;
		struct {
			uint32_t Port_0 : 1; /* [0:0]   RW */
			uint32_t Port_1 : 1; /* [1:1]   RW */
			uint32_t Port_2 : 1; /* [2:2]   RW */
			uint32_t rsvd_3 : 29;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t Port_0 : 1;
				uint32_t Port_1 : 1;
				uint32_t Port_2 : 1;
				uint32_t rsvd_3 : 29;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_intr_status_t {
	union {
		uint32_t value;
		struct {
			uint32_t rsvd_0 : 1;
			uint32_t port_err : 1; /* [1:1]   RO */
			uint32_t rsvd_2 : 2;
			uint32_t timeout : 1; /* [4:4]   RO */
			uint32_t cbus_error : 1; /* [5:5]   RO */
			uint32_t utg_error : 1; /* [6:6]   RO */
			uint32_t ttreg : 1; /* [7:7]   RO */
			uint32_t utg_done : 6; /* [13:8]  RO */
			uint32_t rsvd_14 : 18;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t rsvd_0 : 1;
				uint32_t port_err : 1;
				uint32_t rsvd_2 : 2;
				uint32_t timeout : 1;
				uint32_t cbus_error : 1;
				uint32_t utg_error : 1;
				uint32_t ttreg : 1;
				uint32_t utg_done : 6;
				uint32_t rsvd_14 : 18;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_intr_mask_t {
	union {
		uint32_t value;
		struct {
			uint32_t rsvd_0 : 1;
			uint32_t port_err : 1; /* [1:1]   RO */
			uint32_t rsvd_2 : 2;
			uint32_t timeout : 1; /* [4:4]   RO */
			uint32_t cbus_error : 1; /* [5:5]   RO */
			uint32_t utg_error : 1; /* [6:6]   RO */
			uint32_t ttreg : 1; /* [7:7]   RO */
			uint32_t utg_done : 6; /* [13:8]  RO */
			uint32_t rsvd_14 : 18;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t rsvd_0 : 1;
				uint32_t port_err : 1;
				uint32_t rsvd_2 : 2;
				uint32_t timeout : 1;
				uint32_t cbus_error : 1;
				uint32_t utg_error : 1;
				uint32_t ttreg : 1;
				uint32_t utg_done : 6;
				uint32_t rsvd_14 : 18;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_intr_clr_t {
	union {
		uint32_t value;
		struct {
			uint32_t rsvd_0 : 1;
			uint32_t port_err : 1; /* [1:1]   RW */
			uint32_t rsvd_2 : 2;
			uint32_t timeout : 1; /* [4:4]   RW */
			uint32_t cbus_err : 1; /* [5:5]   RW */
			uint32_t utg_error : 1; /* [6:6]   RW */
			uint32_t ttreg : 1; /* [7:7]   RW */
			uint32_t utg_done : 6; /* [13:8]  RW */
			uint32_t rsvd_14 : 18;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t rsvd_0 : 1;
				uint32_t port_err : 1;
				uint32_t rsvd_2 : 2;
				uint32_t timeout : 1;
				uint32_t cbus_err : 1;
				uint32_t utg_error : 1;
				uint32_t ttreg : 1;
				uint32_t utg_done : 6;
				uint32_t rsvd_14 : 18;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_rtbl_in_0_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_rtbl_in_1_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_rtbl_out_0_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_rtbl_out_1_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_window_config0_t {
	union {
		uint32_t value;
		struct {
			uint32_t tick : 16; /* [15:0]  RW */
			uint32_t window : 16; /* [31:16] RW */
		} __packed;

		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t tick : 16;
				uint32_t window : 16;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_port_err_intr_status_t {
	union {
		uint32_t value;
		uint32_t status; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t status;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_err_intr_status_t {
	union {
		uint32_t value;
		uint32_t status; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t status;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_intr_status_t {
	union {
		uint32_t value;
		uint32_t stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t stat;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_0_t {
	union {
		uint32_t value;
		uint32_t s0_w; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t s0_w;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_1_t {
	union {
		uint32_t value;
		uint32_t s0_r; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t s0_r;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_2_t {
	union {
		uint32_t value;
		uint32_t m0_w; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t m0_w;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_3_t {
	union {
		uint32_t value;
		uint32_t m0_r; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t m0_r;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_4_t {
	union {
		uint32_t value;
		uint32_t s1_w; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t s1_w;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_5_t {
	union {
		uint32_t value;
		uint32_t s1_r; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t s1_r;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_6_t {
	union {
		uint32_t value;
		uint32_t m1_w; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t m1_w;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_7_t {
	union {
		uint32_t value;
		uint32_t m1_r; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t m1_r;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_8_t {
	union {
		uint32_t value;
		uint32_t s2_w; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t s2_w;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_9_t {
	union {
		uint32_t value;
		uint32_t s2_r; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t s2_r;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_10_t {
	union {
		uint32_t value;
		uint32_t m2_w; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t m2_w;
		})
		unbuffered;
	};
};

struct rbc_reg_timeout_status_11_t {
	union {
		uint32_t value;
		uint32_t m2_r; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t m2_r;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_sel_t {
	union {
		uint32_t value;
		uint32_t sel; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t sel;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_acc_t {
	union {
		uint32_t value;
		struct {
			uint32_t id : 20; /* [19:0]  RW */
			uint32_t id_type : 1; /* [20:20] RW */
			uint32_t rsvd_21 : 10;
			uint32_t acc_req : 1; /* [31:31] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t id : 20;
				uint32_t id_type : 1;
				uint32_t rsvd_21 : 10;
				uint32_t acc_req : 1;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_acc_chk_t {
	union {
		uint32_t value;
		uint32_t acc_chk; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t acc_chk;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_ret_0_t {
	union {
		uint32_t value;
		struct {
			uint32_t acc_done : 1;
			uint32_t unmatched : 1;
			uint32_t detect_single_error : 1;
			uint32_t detect_double_error : 1;
			uint32_t valid : 1;
			uint32_t request_valid : 1;
			uint32_t response_valid : 1;
			uint32_t request_timeout : 1;
			uint32_t response_timeout : 1;
			uint32_t output_request_valid : 1;
			uint32_t output_response_valid : 1;
			uint32_t ttreg_error : 1;
			uint32_t axid : 7;
			uint32_t mstr_id : 6;
			uint32_t chiplet_id : 3;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_ret;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_ret_1_t {
	union {
		uint32_t value;
		struct {
			uint32_t port_id : 3;
			uint32_t module_id : 3;
			uint32_t nsew_id : 2;
			uint32_t ttreg_addr : 24;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_ret;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_ret_2_t {
	union {
		uint32_t value;
		struct {
			uint32_t ttreg_addr : 16;
			uint32_t ttreg_ttst : 16;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_ret;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_ret_3_t {
	union {
		uint32_t value;
		struct {
			uint32_t ttreg_ttet : 16;
			uint32_t axi_id : 8;
			uint32_t port_id : 8;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_ret;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_ve_0_t {
	union {
		uint32_t value;
		struct {
			uint32_t s0_w : 8; /* [7:0]   RO */
			uint32_t s0_r : 8; /* [15:8]  RO */
			uint32_t m0_w : 8; /* [23:16] RO */
			uint32_t m0_r : 8; /* [31:24] RO */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t s0_w : 8;
				uint32_t s0_r : 8;
				uint32_t m0_w : 8;
				uint32_t m0_r : 8;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_ve_1_t {
	union {
		uint32_t value;
		struct {
			uint32_t s1_w : 8; /* [7:0]   RO */
			uint32_t s1_r : 8; /* [15:8]  RO */
			uint32_t m1_w : 8; /* [23:16] RO */
			uint32_t m1_r : 8; /* [31:24] RO */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t s1_w : 8;
				uint32_t s1_r : 8;
				uint32_t m1_w : 8;
				uint32_t m1_r : 8;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_ve_2_t {
	union {
		uint32_t value;
		struct {
			uint32_t s2_r : 8; /* [7:0]   RO */
			uint32_t s2_w : 8; /* [15:8]  RO */
			uint32_t m2_r : 8; /* [23:16] RO */
			uint32_t m2_w : 8; /* [31:24] RO */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t s2_r : 8;
				uint32_t s2_w : 8;
				uint32_t m2_r : 8;
				uint32_t m2_w : 8;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_lb_ctl_t {
	union {
		uint32_t value;
		struct {
			uint32_t ilb : 6; /* [5:0]   RW */
			uint32_t rsvd_6 : 2;
			uint32_t olb : 6; /* [13:8]  RW */
			uint32_t rsvd_14 : 2;
			uint32_t lb_usr : 6; /* [21:16] RW */
			uint32_t rsvd_22 : 2;
			uint32_t lb_port : 3; /* [26:24] RW */
			uint32_t rsvd_27 : 5;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t ilb : 6;
				uint32_t rsvd_6 : 2;
				uint32_t olb : 6;
				uint32_t rsvd_14 : 2;
				uint32_t lb_usr : 6;
				uint32_t rsvd_22 : 2;
				uint32_t lb_port : 3;
				uint32_t rsvd_27 : 5;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_ctl_t {
	union {
		uint32_t value;
		struct {
			uint32_t str_s0_w : 1; /* [0:0]   RW */
			uint32_t str_s0_r : 1; /* [1:1]   RW */
			uint32_t str_s1_w : 1; /* [2:2]   RW */
			uint32_t str_s1_r : 1; /* [3:3]   RW */
			uint32_t str_s2_w : 1; /* [4:4]   RW */
			uint32_t str_s2_r : 1; /* [5:5]   RW */
			uint32_t rsvd_6 : 26;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t str_s0_w : 1;
				uint32_t str_s0_r : 1;
				uint32_t str_s1_w : 1;
				uint32_t str_s1_r : 1;
				uint32_t str_s2_w : 1;
				uint32_t str_s2_r : 1;
				uint32_t rsvd_6 : 26;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_status_t {
	union {
		uint32_t value;
		uint32_t status; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t status;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p0_w_config0_t {
	union {
		uint32_t value;
		struct {
			uint32_t id : 7; /* [6:0]   RW */
			uint32_t rsvd_7 : 1;
			uint32_t size : 3; /* [10:8]  RW */
			uint32_t rsvd_11 : 1;
			uint32_t burst : 2; /* [13:12] RW */
			uint32_t rsvd_14 : 2;
			uint32_t cache : 4; /* [19:16] RW */
			uint32_t lock : 1; /* [20:20] RW */
			uint32_t prot : 3; /* [23:21] RW */
			uint32_t blen : 4; /* [27:24] RW */
			uint32_t qos : 4; /* [31:28] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t id : 7;
				uint32_t rsvd_7 : 1;
				uint32_t size : 3;
				uint32_t rsvd_11 : 1;
				uint32_t burst : 2;
				uint32_t rsvd_14 : 2;
				uint32_t cache : 4;
				uint32_t lock : 1;
				uint32_t prot : 3;
				uint32_t blen : 4;
				uint32_t qos : 4;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p0_w_config1_t {
	union {
		uint32_t value;
		uint32_t addr_l; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t addr_l;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p0_w_config2_t {
	union {
		uint32_t value;
		struct {
			uint32_t addr_h : 8; /* [7:0]   RW */
			uint32_t user : 24; /* [31:8]  RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t addr_h : 8;
				uint32_t user : 24;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p0_w_config3_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p0_r_config0_t {
	union {
		uint32_t value;
		struct {
			uint32_t id : 7; /* [6:0]   RW */
			uint32_t rsvd_7 : 1;
			uint32_t size : 3; /* [10:8]  RW */
			uint32_t rsvd_11 : 1;
			uint32_t burst : 2; /* [13:12] RW */
			uint32_t rsvd_14 : 2;
			uint32_t cache : 4; /* [19:16] RW */
			uint32_t lock : 1; /* [20:20] RW */
			uint32_t prot : 3; /* [23:21] RW */
			uint32_t blen : 4; /* [27:24] RW */
			uint32_t qos : 4; /* [31:28] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t id : 7;
				uint32_t rsvd_7 : 1;
				uint32_t size : 3;
				uint32_t rsvd_11 : 1;
				uint32_t burst : 2;
				uint32_t rsvd_14 : 2;
				uint32_t cache : 4;
				uint32_t lock : 1;
				uint32_t prot : 3;
				uint32_t blen : 4;
				uint32_t qos : 4;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p0_r_config1_t {
	union {
		uint32_t value;
		uint32_t addr_l; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t addr_l;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p0_r_config2_t {
	union {
		uint32_t value;
		struct {
			uint32_t addr_h : 8; /* [7:0]   RW */
			uint32_t user : 24; /* [31:8]  RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t addr_h : 8;
				uint32_t user : 24;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p0_r_config3_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p1_w_config0_t {
	union {
		uint32_t value;
		struct {
			uint32_t id : 7; /* [6:0]   RW */
			uint32_t rsvd_7 : 1;
			uint32_t size : 3; /* [10:8]  RW */
			uint32_t rsvd_11 : 1;
			uint32_t burst : 2; /* [13:12] RW */
			uint32_t rsvd_14 : 2;
			uint32_t cache : 4; /* [19:16] RW */
			uint32_t lock : 1; /* [20:20] RW */
			uint32_t prot : 3; /* [23:21] RW */
			uint32_t blen : 4; /* [27:24] RW */
			uint32_t qos : 4; /* [31:28] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t id : 7;
				uint32_t rsvd_7 : 1;
				uint32_t size : 3;
				uint32_t rsvd_11 : 1;
				uint32_t burst : 2;
				uint32_t rsvd_14 : 2;
				uint32_t cache : 4;
				uint32_t lock : 1;
				uint32_t prot : 3;
				uint32_t blen : 4;
				uint32_t qos : 4;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p1_w_config1_t {
	union {
		uint32_t value;
		uint32_t addr_l; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t addr_l;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p1_w_config2_t {
	union {
		uint32_t value;
		struct {
			uint32_t addr_h : 8; /* [7:0]   RW */
			uint32_t user : 24; /* [31:8]  RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t addr_h : 8;
				uint32_t user : 24;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p1_w_config3_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p1_r_config0_t {
	union {
		uint32_t value;
		struct {
			uint32_t id : 7; /* [6:0]   RW */
			uint32_t rsvd_7 : 1;
			uint32_t size : 3; /* [10:8]  RW */
			uint32_t rsvd_11 : 1;
			uint32_t burst : 2; /* [13:12] RW */
			uint32_t rsvd_14 : 2;
			uint32_t cache : 4; /* [19:16] RW */
			uint32_t lock : 1; /* [20:20] RW */
			uint32_t prot : 3; /* [23:21] RW */
			uint32_t blen : 4; /* [27:24] RW */
			uint32_t qos : 4; /* [31:28] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t id : 7;
				uint32_t rsvd_7 : 1;
				uint32_t size : 3;
				uint32_t rsvd_11 : 1;
				uint32_t burst : 2;
				uint32_t rsvd_14 : 2;
				uint32_t cache : 4;
				uint32_t lock : 1;
				uint32_t prot : 3;
				uint32_t blen : 4;
				uint32_t qos : 4;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p1_r_config1_t {
	union {
		uint32_t value;
		uint32_t addr_l; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t addr_l;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p1_r_config2_t {
	union {
		uint32_t value;
		struct {
			uint32_t addr_h : 8; /* [7:0]   RW */
			uint32_t user : 24; /* [31:8]  RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t addr_h : 8;
				uint32_t user : 24;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p1_r_config3_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p2_w_config0_t {
	union {
		uint32_t value;
		struct {
			uint32_t id : 7; /* [6:0]   RW */
			uint32_t rsvd_7 : 1;
			uint32_t size : 3; /* [10:8]  RW */
			uint32_t rsvd_11 : 1;
			uint32_t burst : 2; /* [13:12] RW */
			uint32_t rsvd_14 : 2;
			uint32_t cache : 4; /* [19:16] RW */
			uint32_t lock : 1; /* [20:20] RW */
			uint32_t prot : 3; /* [23:21] RW */
			uint32_t blen : 4; /* [27:24] RW */
			uint32_t qos : 4; /* [31:28] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t id : 7;
				uint32_t rsvd_7 : 1;
				uint32_t size : 3;
				uint32_t rsvd_11 : 1;
				uint32_t burst : 2;
				uint32_t rsvd_14 : 2;
				uint32_t cache : 4;
				uint32_t lock : 1;
				uint32_t prot : 3;
				uint32_t blen : 4;
				uint32_t qos : 4;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p2_w_config1_t {
	union {
		uint32_t value;
		uint32_t addr_l; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t addr_l;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p2_w_config2_t {
	union {
		uint32_t value;
		struct {
			uint32_t addr_h : 8; /* [7:0]   RW */
			uint32_t user : 24; /* [31:8]  RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t addr_h : 8;
				uint32_t user : 24;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p2_w_config3_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p2_r_config0_t {
	union {
		uint32_t value;
		struct {
			uint32_t id : 7; /* [6:0]   RW */
			uint32_t rsvd_7 : 1;
			uint32_t size : 3; /* [10:8]  RW */
			uint32_t rsvd_11 : 1;
			uint32_t burst : 2; /* [13:12] RW */
			uint32_t rsvd_14 : 2;
			uint32_t cache : 4; /* [19:16] RW */
			uint32_t lock : 1; /* [20:20] RW */
			uint32_t prot : 3; /* [23:21] RW */
			uint32_t blen : 4; /* [27:24] RW */
			uint32_t qos : 4; /* [31:28] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t id : 7;
				uint32_t rsvd_7 : 1;
				uint32_t size : 3;
				uint32_t rsvd_11 : 1;
				uint32_t burst : 2;
				uint32_t rsvd_14 : 2;
				uint32_t cache : 4;
				uint32_t lock : 1;
				uint32_t prot : 3;
				uint32_t blen : 4;
				uint32_t qos : 4;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p2_r_config1_t {
	union {
		uint32_t value;
		uint32_t addr_l; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t addr_l;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p2_r_config2_t {
	union {
		uint32_t value;
		struct {
			uint32_t addr_h : 8; /* [7:0]   RW */
			uint32_t user : 24; /* [31:8]  RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t addr_h : 8;
				uint32_t user : 24;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_user_transaction_p2_r_config3_t {
	union {
		uint32_t value;
		uint32_t config; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t config;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_glue_ctl_0_t {
	union {
		uint32_t value;
		struct {
			uint32_t s0_w_0 : 1; /* [0:0]   RW */
			uint32_t s0_w_1 : 1; /* [1:1]   RW */
			uint32_t s0_w_2 : 1; /* [2:2]   RW */
			uint32_t s0_w_3 : 1; /* [3:3]   RW */
			uint32_t s0_w_4 : 1; /* [4:4]   RW */
			uint32_t s0_w_5 : 1; /* [5:5]   RW */
			uint32_t s0_w_6 : 1; /* [6:6]   RW */
			uint32_t s0_w_7 : 1; /* [7:7]   RW */
			uint32_t s0_r_0 : 1; /* [8:8]   RW */
			uint32_t s0_r_1 : 1; /* [9:9]   RW */
			uint32_t s0_r_2 : 1; /* [10:10] RW */
			uint32_t s0_r_3 : 1; /* [11:11] RW */
			uint32_t s0_r_4 : 1; /* [12:12] RW */
			uint32_t s0_r_5 : 1; /* [13:13] RW */
			uint32_t s0_r_6 : 1; /* [14:14] RW */
			uint32_t s0_r_7 : 1; /* [15:15] RW */
			uint32_t m0_w_0 : 1; /* [16:16] RW */
			uint32_t m0_w_1 : 1; /* [17:17] RW */
			uint32_t m0_w_2 : 1; /* [18:18] RW */
			uint32_t m0_w_3 : 1; /* [19:19] RW */
			uint32_t m0_w_4 : 1; /* [20:20] RW */
			uint32_t m0_w_5 : 1; /* [21:21] RW */
			uint32_t m0_w_6 : 1; /* [22:22] RW */
			uint32_t m0_w_7 : 1; /* [23:23] RW */
			uint32_t m0_r_0 : 1; /* [24:24] RW */
			uint32_t m0_r_1 : 1; /* [25:25] RW */
			uint32_t m0_r_2 : 1; /* [26:26] RW */
			uint32_t m0_r_3 : 1; /* [27:27] RW */
			uint32_t m0_r_4 : 1; /* [28:28] RW */
			uint32_t m0_r_5 : 1; /* [29:29] RW */
			uint32_t m0_r_6 : 1; /* [30:30] RW */
			uint32_t m0_r_7 : 1; /* [31:31] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t s0_w_0 : 1;
				uint32_t s0_w_1 : 1;
				uint32_t s0_w_2 : 1;
				uint32_t s0_w_3 : 1;
				uint32_t s0_w_4 : 1;
				uint32_t s0_w_5 : 1;
				uint32_t s0_w_6 : 1;
				uint32_t s0_w_7 : 1;
				uint32_t s0_r_0 : 1;
				uint32_t s0_r_1 : 1;
				uint32_t s0_r_2 : 1;
				uint32_t s0_r_3 : 1;
				uint32_t s0_r_4 : 1;
				uint32_t s0_r_5 : 1;
				uint32_t s0_r_6 : 1;
				uint32_t s0_r_7 : 1;
				uint32_t m0_w_0 : 1;
				uint32_t m0_w_1 : 1;
				uint32_t m0_w_2 : 1;
				uint32_t m0_w_3 : 1;
				uint32_t m0_w_4 : 1;
				uint32_t m0_w_5 : 1;
				uint32_t m0_w_6 : 1;
				uint32_t m0_w_7 : 1;
				uint32_t m0_r_0 : 1;
				uint32_t m0_r_1 : 1;
				uint32_t m0_r_2 : 1;
				uint32_t m0_r_3 : 1;
				uint32_t m0_r_4 : 1;
				uint32_t m0_r_5 : 1;
				uint32_t m0_r_6 : 1;
				uint32_t m0_r_7 : 1;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_glue_ctl_1_t {
	union {
		uint32_t value;
		struct {
			uint32_t s1_w_0 : 1; /* [0:0]   RW */
			uint32_t s1_w_1 : 1; /* [1:1]   RW */
			uint32_t s1_w_2 : 1; /* [2:2]   RW */
			uint32_t s1_w_3 : 1; /* [3:3]   RW */
			uint32_t s1_w_4 : 1; /* [4:4]   RW */
			uint32_t s1_w_5 : 1; /* [5:5]   RW */
			uint32_t s1_w_6 : 1; /* [6:6]   RW */
			uint32_t s1_w_7 : 1; /* [7:7]   RW */
			uint32_t s1_r_0 : 1; /* [8:8]   RW */
			uint32_t s1_r_1 : 1; /* [9:9]   RW */
			uint32_t s1_r_2 : 1; /* [10:10] RW */
			uint32_t s1_r_3 : 1; /* [11:11] RW */
			uint32_t s1_r_4 : 1; /* [12:12] RW */
			uint32_t s1_r_5 : 1; /* [13:13] RW */
			uint32_t s1_r_6 : 1; /* [14:14] RW */
			uint32_t s1_r_7 : 1; /* [15:15] RW */
			uint32_t m1_w_0 : 1; /* [16:16] RW */
			uint32_t m1_w_1 : 1; /* [17:17] RW */
			uint32_t m1_w_2 : 1; /* [18:18] RW */
			uint32_t m1_w_3 : 1; /* [19:19] RW */
			uint32_t m1_w_4 : 1; /* [20:20] RW */
			uint32_t m1_w_5 : 1; /* [21:21] RW */
			uint32_t m1_w_6 : 1; /* [22:22] RW */
			uint32_t m1_w_7 : 1; /* [23:23] RW */
			uint32_t m1_r_0 : 1; /* [24:24] RW */
			uint32_t m1_r_1 : 1; /* [25:25] RW */
			uint32_t m1_r_2 : 1; /* [26:26] RW */
			uint32_t m1_r_3 : 1; /* [27:27] RW */
			uint32_t m1_r_4 : 1; /* [28:28] RW */
			uint32_t m1_r_5 : 1; /* [29:29] RW */
			uint32_t m1_r_6 : 1; /* [30:30] RW */
			uint32_t m1_r_7 : 1; /* [31:31] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t s1_w_0 : 1;
				uint32_t s1_w_1 : 1;
				uint32_t s1_w_2 : 1;
				uint32_t s1_w_3 : 1;
				uint32_t s1_w_4 : 1;
				uint32_t s1_w_5 : 1;
				uint32_t s1_w_6 : 1;
				uint32_t s1_w_7 : 1;
				uint32_t s1_r_0 : 1;
				uint32_t s1_r_1 : 1;
				uint32_t s1_r_2 : 1;
				uint32_t s1_r_3 : 1;
				uint32_t s1_r_4 : 1;
				uint32_t s1_r_5 : 1;
				uint32_t s1_r_6 : 1;
				uint32_t s1_r_7 : 1;
				uint32_t m1_w_0 : 1;
				uint32_t m1_w_1 : 1;
				uint32_t m1_w_2 : 1;
				uint32_t m1_w_3 : 1;
				uint32_t m1_w_4 : 1;
				uint32_t m1_w_5 : 1;
				uint32_t m1_w_6 : 1;
				uint32_t m1_w_7 : 1;
				uint32_t m1_r_0 : 1;
				uint32_t m1_r_1 : 1;
				uint32_t m1_r_2 : 1;
				uint32_t m1_r_3 : 1;
				uint32_t m1_r_4 : 1;
				uint32_t m1_r_5 : 1;
				uint32_t m1_r_6 : 1;
				uint32_t m1_r_7 : 1;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_rbc_glue_ctl_2_t {
	union {
		uint32_t value;
		struct {
			uint32_t s2_w_0 : 1; /* [0:0]   RW */
			uint32_t s2_w_1 : 1; /* [1:1]   RW */
			uint32_t s2_w_2 : 1; /* [2:2]   RW */
			uint32_t s2_w_3 : 1; /* [3:3]   RW */
			uint32_t s2_w_4 : 1; /* [4:4]   RW */
			uint32_t s2_w_5 : 1; /* [5:5]   RW */
			uint32_t s2_w_6 : 1; /* [6:6]   RW */
			uint32_t s2_w_7 : 1; /* [7:7]   RW */
			uint32_t s2_r_0 : 1; /* [8:8]   RW */
			uint32_t s2_r_1 : 1; /* [9:9]   RW */
			uint32_t s2_r_2 : 1; /* [10:10] RW */
			uint32_t s2_r_3 : 1; /* [11:11] RW */
			uint32_t s2_r_4 : 1; /* [12:12] RW */
			uint32_t s2_r_5 : 1; /* [13:13] RW */
			uint32_t s2_r_6 : 1; /* [14:14] RW */
			uint32_t s2_r_7 : 1; /* [15:15] RW */
			uint32_t m2_w_0 : 1; /* [16:16] RW */
			uint32_t m2_w_1 : 1; /* [17:17] RW */
			uint32_t m2_w_2 : 1; /* [18:18] RW */
			uint32_t m2_w_3 : 1; /* [19:19] RW */
			uint32_t m2_w_4 : 1; /* [20:20] RW */
			uint32_t m2_w_5 : 1; /* [21:21] RW */
			uint32_t m2_w_6 : 1; /* [22:22] RW */
			uint32_t m2_w_7 : 1; /* [23:23] RW */
			uint32_t m2_r_0 : 1; /* [24:24] RW */
			uint32_t m2_r_1 : 1; /* [25:25] RW */
			uint32_t m2_r_2 : 1; /* [26:26] RW */
			uint32_t m2_r_3 : 1; /* [27:27] RW */
			uint32_t m2_r_4 : 1; /* [28:28] RW */
			uint32_t m2_r_5 : 1; /* [29:29] RW */
			uint32_t m2_r_6 : 1; /* [30:30] RW */
			uint32_t m2_r_7 : 1; /* [31:31] RW */
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t s2_w_0 : 1;
				uint32_t s2_w_1 : 1;
				uint32_t s2_w_2 : 1;
				uint32_t s2_w_3 : 1;
				uint32_t s2_w_4 : 1;
				uint32_t s2_w_5 : 1;
				uint32_t s2_w_6 : 1;
				uint32_t s2_w_7 : 1;
				uint32_t s2_r_0 : 1;
				uint32_t s2_r_1 : 1;
				uint32_t s2_r_2 : 1;
				uint32_t s2_r_3 : 1;
				uint32_t s2_r_4 : 1;
				uint32_t s2_r_5 : 1;
				uint32_t s2_r_6 : 1;
				uint32_t s2_r_7 : 1;
				uint32_t m2_w_0 : 1;
				uint32_t m2_w_1 : 1;
				uint32_t m2_w_2 : 1;
				uint32_t m2_w_3 : 1;
				uint32_t m2_w_4 : 1;
				uint32_t m2_w_5 : 1;
				uint32_t m2_w_6 : 1;
				uint32_t m2_w_7 : 1;
				uint32_t m2_r_0 : 1;
				uint32_t m2_r_1 : 1;
				uint32_t m2_r_2 : 1;
				uint32_t m2_r_3 : 1;
				uint32_t m2_r_4 : 1;
				uint32_t m2_r_5 : 1;
				uint32_t m2_r_6 : 1;
				uint32_t m2_r_7 : 1;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_bp_sel_t {
	union {
		uint32_t value;
		struct {
			uint32_t p0 : 4; /* [3:0]   RW */
			uint32_t p1 : 4; /* [7:4]   RW */
			uint32_t p2 : 4; /* [11:8]  RW */
			uint32_t rsvd_12 : 20;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t p0 : 4;
				uint32_t p1 : 4;
				uint32_t p2 : 4;
				uint32_t rsvd_12 : 20;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_trl_sel_t {
	union {
		uint32_t value;
		struct {
			uint32_t sel : 4; /* [3:0]   RW */
			uint32_t rsvd_4 : 28;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t sel : 4;
				uint32_t rsvd_4 : 28;
			} __packed;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_0_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_1_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_2_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_3_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_4_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_5_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_6_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_7_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_8_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_9_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_10_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_11_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_12_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_13_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_14_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_15_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_16_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_17_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_18_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_19_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_20_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_21_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_22_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_23_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_24_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_25_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_26_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_27_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_28_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_29_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_30_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rbc_reg_ttreg_status_31_t {
	union {
		uint32_t value;
		uint32_t ttreg_stat; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t ttreg_stat;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_ip_info0_t {
	union {
		uint32_t value;
		uint32_t rel_date; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t rel_date;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_ip_info1_t {
	union {
		uint32_t value;
		struct {
			uint32_t min_ver : 8; /* [7:0]   RO */
			uint32_t maj_ver : 8; /* [15:8]  RO */
			uint32_t busprofiler_ver : 8; /* [23:16] RO */
			uint32_t rsvd_24 : 8;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t min_ver : 8;
				uint32_t maj_ver : 8;
				uint32_t busprofiler_ver : 8;
				uint32_t rsvd_24 : 8;
			} __packed;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_ip_info2_t {
	union {
		uint32_t value;
		uint32_t target_num; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t target_num;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_ip_info3_t {
	union {
		uint32_t value;
		uint32_t min_conf_time; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t min_conf_time;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_ip_info4_t {
	union {
		uint32_t value;
		uint32_t rsvd_0;

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t rsvd_0;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_ip_info5_t {
	union {
		uint32_t value;
		uint32_t rsvd_0;

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t rsvd_0;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_ip_info6_t {
	union {
		uint32_t value;
		uint32_t rsvd_0;

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t rsvd_0;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_ip_info7_t {
	union {
		uint32_t value;
		uint32_t rsvd_0;

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t rsvd_0;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_configure_en_t {
	union {
		uint32_t value;
		struct {
			uint32_t read_mon_en : 1; /* [0:0]   RW */
			uint32_t write_mon_en : 1; /* [1:1]   RW */
			uint32_t target0_en : 1; /* [2:2]   RW */
			uint32_t target1_en : 1; /* [3:3]   RW */
			uint32_t target2_en : 1; /* [4:4]   RW */
			uint32_t target3_en : 1; /* [5:5]   RW */
			uint32_t rsvd_6 : 26;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t read_mon_en : 1;
				uint32_t write_mon_en : 1;
				uint32_t target0_en : 1;
				uint32_t target1_en : 1;
				uint32_t target2_en : 1;
				uint32_t target3_en : 1;
				uint32_t rsvd_6 : 26;
			} __packed;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_clear_set_t {
	union {
		uint32_t value;
		struct {
			uint32_t requeue : 1; /* [0:0]   RW */
			uint32_t profile_reg : 1; /* [1:1]   RW */
			uint32_t profile_fifo : 1; /* [2:2]   RW */
			uint32_t status : 1; /* [3:3]   RW */
			uint32_t sequence_idx : 1; /* [4:4]   RW */
			uint32_t rsvd_5 : 27;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t requeue : 1;
				uint32_t profile_reg : 1;
				uint32_t profile_fifo : 1;
				uint32_t status : 1;
				uint32_t sequence_idx : 1;
				uint32_t rsvd_5 : 27;
			} __packed;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_configure_period_t {
	union {
		uint32_t value;
		uint32_t sampling_period; /* [31:0]   RW */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t sampling_period;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_configure_flush_t {
	union {
		uint32_t value;
		struct {
			uint32_t start : 1; /* [0:0]   RW */
			uint32_t rsvd_1 : 31;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t start : 1;
				uint32_t rsvd_1 : 31;
			} __packed;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_configure_trgt01_t {
	union {
		uint32_t value;
		struct {
			uint32_t trgt0_offset_exp : 4; /* [3:0]   RW */
			uint32_t trgt0_intv_exp : 4; /* [7:4]   RW */
			uint32_t trgt0_cntup_exp : 3; /* [10:8]  RW */
			uint32_t rsvd_11 : 5;
			uint32_t trgt1_offset_exp : 4; /* [19:16] RW */
			uint32_t trgt1_intv_exp : 4; /* [23:20] RW */
			uint32_t trgt1_cntup_exp : 3; /* [26:24] RW */
			uint32_t rsvd_27 : 5;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t trgt0_offset_exp : 4;
				uint32_t trgt0_intv_exp : 4;
				uint32_t trgt0_cntup_exp : 3;
				uint32_t rsvd_11 : 5;
				uint32_t trgt1_offset_exp : 4;
				uint32_t trgt1_intv_exp : 4;
				uint32_t trgt1_cntup_exp : 3;
				uint32_t rsvd_27 : 5;
			} __packed;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_configure_trgt23_t {
	union {
		uint32_t value;
		struct {
			uint32_t trgt2_offset_exp : 4; /* [3:0]   RW */
			uint32_t trgt2_intv_exp : 4; /* [7:4]   RW */
			uint32_t trgt2_cntup_exp : 3; /* [10:8]  RW */
			uint32_t rsvd_11 : 5;
			uint32_t trgt3_offset_exp : 4; /* [19:16] RW */
			uint32_t trgt3_intv_exp : 4; /* [23:20] RW */
			uint32_t trgt3_cntup_exp : 3; /* [26:24] RW */
			uint32_t rsvd_27 : 5;
		} __packed;
		UNBUFFERED_DECL(union {
			uint32_t value;
			struct {
				uint32_t trgt2_offset_exp : 4;
				uint32_t trgt2_intv_exp : 4;
				uint32_t trgt2_cntup_exp : 3;
				uint32_t rsvd_11 : 5;
				uint32_t trgt3_offset_exp : 4;
				uint32_t trgt3_intv_exp : 4;
				uint32_t trgt3_cntup_exp : 3;
				uint32_t rsvd_27 : 5;
			} __packed;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_reserved_15_t {
	union {
		uint32_t value;
		uint32_t rsvd_0;

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t rsvd_0;
		})
		unbuffered;
	};
};

struct rebel_perfmon_bp_mon_status_t {
	union {
		uint32_t value;
		uint32_t status; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t status;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg0_t {
	union {
		uint32_t value;
		uint32_t header_0; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t header_0;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg1_t {
	union {
		uint32_t value;
		uint32_t header_1; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t header_1;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg2_t {
	union {
		uint32_t value;
		uint32_t data_0; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_0;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg3_t {
	union {
		uint32_t value;
		uint32_t data_1; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_1;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg4_t {
	union {
		uint32_t value;
		uint32_t data_2; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_2;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg5_t {
	union {
		uint32_t value;
		uint32_t data_3; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_3;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg6_t {
	union {
		uint32_t value;
		uint32_t data_4; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_4;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg7_t {
	union {
		uint32_t value;
		uint32_t data_5; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_5;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg8_t {
	union {
		uint32_t value;
		uint32_t data_6; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_6;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg9_t {
	union {
		uint32_t value;
		uint32_t data_7; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_7;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg10_t {
	union {
		uint32_t value;
		uint32_t data_8; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_8;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg11_t {
	union {
		uint32_t value;
		uint32_t data_9; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_9;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg12_t {
	union {
		uint32_t value;
		uint32_t data_10; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_10;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg13_t {
	union {
		uint32_t value;
		uint32_t data_11; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_11;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg14_t {
	union {
		uint32_t value;
		uint32_t data_12; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_12;
		})
		unbuffered;
	};
};

struct rebel_perfmon_profile_pkg15_t {
	union {
		uint32_t value;
		uint32_t data_13; /* [31:0]   RO */

		UNBUFFERED_DECL(union {
			uint32_t value;
			uint32_t data_13;
		})
		unbuffered;
	};
};

struct rbc_reg {
	struct rbc_reg_ip_info0_t ip_info0; /* 0x00000000 */
	struct rbc_reg_ip_info1_t ip_info1; /* 0x00000004 */
	struct rbc_reg_ip_info2_t ip_info2; /* 0x00000008 */
	struct rbc_reg_ip_info3_t ip_info3; /* 0x0000000c */
	struct rbc_reg_design_info0_t design_info0; /* 0x00000010 */
	struct rbc_reg_design_info1_t design_info1; /* 0x00000014 */
	struct rbc_reg_common_rpt_t common_rpt; /* 0x00000018 */
	struct rbc_reg_common_reg_t common_reg; /* 0x0000001c */
	struct rbc_reg_rbc_info_t rbc_info; /* 0x00000020 */
	struct rbc_reg_rbc_ctl_t rbc_ctl; /* 0x00000024 */
	uint8_t reserved_40[8];
	struct rbc_reg_rbc_config_t rbc_config; /* 0x00000030 */
	struct rbc_reg_port_config_t port_config; /* 0x00000034 */
	struct rbc_reg_rbc_intr_status_t rbc_intr_status; /* 0x00000038 */
	struct rbc_reg_rbc_intr_mask_t rbc_intr_mask; /* 0x0000003c */
	struct rbc_reg_rbc_intr_clr_t rbc_intr_clr; /* 0x00000040 */
	uint8_t reserved_68[172];
	struct rbc_reg_rbc_rtbl_in_0_t rbc_rtbl_in_0; /* 0x000000f0 */
	struct rbc_reg_rbc_rtbl_in_1_t rbc_rtbl_in_1; /* 0x000000f4 */
	struct rbc_reg_rbc_rtbl_out_0_t rbc_rtbl_out_0; /* 0x000000f8 */
	struct rbc_reg_rbc_rtbl_out_1_t rbc_rtbl_out_1; /* 0x000000fc */
	struct rbc_reg_timeout_window_config0_t
		Timeout_window_config0; /* 0x00000100 */
	struct rbc_reg_port_err_intr_status_t
		port_err_intr_status; /* 0x00000104 */
	struct rbc_reg_ttreg_err_intr_status_t
		ttreg_err_intr_status; /* 0x00000108 */
	struct rbc_reg_timeout_intr_status_t Timeout_intr_status; /* 0x0000010c */
	struct rbc_reg_timeout_status_0_t Timeout_status_0; /* 0x00000110 */
	struct rbc_reg_timeout_status_1_t Timeout_status_1; /* 0x00000114 */
	struct rbc_reg_timeout_status_2_t Timeout_status_2; /* 0x00000118 */
	struct rbc_reg_timeout_status_3_t Timeout_status_3; /* 0x0000011c */
	struct rbc_reg_timeout_status_4_t Timeout_status_4; /* 0x00000120 */
	struct rbc_reg_timeout_status_5_t Timeout_status_5; /* 0x00000124 */
	struct rbc_reg_timeout_status_6_t Timeout_status_6; /* 0x00000128 */
	struct rbc_reg_timeout_status_7_t Timeout_status_7; /* 0x0000012c */
	struct rbc_reg_timeout_status_8_t Timeout_status_8; /* 0x00000130 */
	struct rbc_reg_timeout_status_9_t Timeout_status_9; /* 0x00000134 */
	struct rbc_reg_timeout_status_10_t Timeout_status_10; /* 0x00000138 */
	struct rbc_reg_timeout_status_11_t Timeout_status_11; /* 0x0000013c */
	struct rbc_reg_ttreg_sel_t TTReg_sel; /* 0x00000140 */
	struct rbc_reg_ttreg_acc_t TTReg_acc; /* 0x00000144 */
	struct rbc_reg_ttreg_acc_chk_t TTReg_acc_chk; /* 0x00000148 */
	uint8_t reserved_332[4];
	struct rbc_reg_ttreg_ret_0_t TTReg_ret_0; /* 0x00000150 */
	struct rbc_reg_ttreg_ret_1_t TTReg_ret_1; /* 0x00000154 */
	struct rbc_reg_ttreg_ret_2_t TTReg_ret_2; /* 0x00000158 */
	struct rbc_reg_ttreg_ret_3_t TTReg_ret_3; /* 0x0000015c */
	struct rbc_reg_ttreg_ve_0_t TTReg_ve_0; /* 0x00000160 */
	struct rbc_reg_ttreg_ve_1_t TTReg_ve_1; /* 0x00000164 */
	struct rbc_reg_ttreg_ve_2_t TTReg_ve_2; /* 0x00000168 */
	struct rbc_reg_lb_ctl_t lb_ctl; /* 0x0000016c */
	struct rbc_reg_user_transaction_ctl_t
		user_transaction_ctl; /* 0x00000170 */
	struct rbc_reg_user_transaction_status_t
		user_transaction_status; /* 0x00000174 */
	uint8_t reserved_376[8];
	struct rbc_reg_user_transaction_p0_w_config0_t
		user_transaction_p0_w_config0; /* 0x00000180 */
	struct rbc_reg_user_transaction_p0_w_config1_t
		user_transaction_p0_w_config1; /* 0x00000184 */
	struct rbc_reg_user_transaction_p0_w_config2_t
		user_transaction_p0_w_config2; /* 0x00000188 */
	struct rbc_reg_user_transaction_p0_w_config3_t
		user_transaction_p0_w_config3; /* 0x0000018c */
	struct rbc_reg_user_transaction_p0_r_config0_t
		user_transaction_p0_r_config0; /* 0x00000190 */
	struct rbc_reg_user_transaction_p0_r_config1_t
		user_transaction_p0_r_config1; /* 0x00000194 */
	struct rbc_reg_user_transaction_p0_r_config2_t
		user_transaction_p0_r_config2; /* 0x00000198 */
	struct rbc_reg_user_transaction_p0_r_config3_t
		user_transaction_p0_r_config3; /* 0x0000019c */
	struct rbc_reg_user_transaction_p1_w_config0_t
		user_transaction_p1_w_config0; /* 0x000001a0 */
	struct rbc_reg_user_transaction_p1_w_config1_t
		user_transaction_p1_w_config1; /* 0x000001a4 */
	struct rbc_reg_user_transaction_p1_w_config2_t
		user_transaction_p1_w_config2; /* 0x000001a8 */
	struct rbc_reg_user_transaction_p1_w_config3_t
		user_transaction_p1_w_config3; /* 0x000001ac */
	struct rbc_reg_user_transaction_p1_r_config0_t
		user_transaction_p1_r_config0; /* 0x000001b0 */
	struct rbc_reg_user_transaction_p1_r_config1_t
		user_transaction_p1_r_config1; /* 0x000001b4 */
	struct rbc_reg_user_transaction_p1_r_config2_t
		user_transaction_p1_r_config2; /* 0x000001b8 */
	struct rbc_reg_user_transaction_p1_r_config3_t
		user_transaction_p1_r_config3; /* 0x000001bc */
	struct rbc_reg_user_transaction_p2_w_config0_t
		user_transaction_p2_w_config0; /* 0x000001c0 */
	struct rbc_reg_user_transaction_p2_w_config1_t
		user_transaction_p2_w_config1; /* 0x000001c4 */
	struct rbc_reg_user_transaction_p2_w_config2_t
		user_transaction_p2_w_config2; /* 0x000001c8 */
	struct rbc_reg_user_transaction_p2_w_config3_t
		user_transaction_p2_w_config3; /* 0x000001cc */
	struct rbc_reg_user_transaction_p2_r_config0_t
		user_transaction_p2_r_config0; /* 0x000001d0 */
	struct rbc_reg_user_transaction_p2_r_config1_t
		user_transaction_p2_r_config1; /* 0x000001d4 */
	struct rbc_reg_user_transaction_p2_r_config2_t
		user_transaction_p2_r_config2; /* 0x000001d8 */
	struct rbc_reg_user_transaction_p2_r_config3_t
		user_transaction_p2_r_config3; /* 0x000001dc */
	struct rbc_reg_rbc_glue_ctl_0_t rbc_glue_ctl_0; /* 0x000001e0 */
	struct rbc_reg_rbc_glue_ctl_1_t rbc_glue_ctl_1; /* 0x000001e4 */
	struct rbc_reg_rbc_glue_ctl_2_t rbc_glue_ctl_2; /* 0x000001e8 */
	uint8_t reserved_492[4];
	struct rbc_reg_bp_sel_t bp_sel; /* 0x000001f0 */
	struct rbc_reg_trl_sel_t trl_sel; /* 0x000001f4 */
	uint8_t reserved_504[8];
	struct rbc_reg_ttreg_status_0_t TTReg_status_0; /* 0x00000200 */
	struct rbc_reg_ttreg_status_1_t TTReg_status_1; /* 0x00000204 */
	struct rbc_reg_ttreg_status_2_t TTReg_status_2; /* 0x00000208 */
	struct rbc_reg_ttreg_status_3_t TTReg_status_3; /* 0x0000020c */
	struct rbc_reg_ttreg_status_4_t TTReg_status_4; /* 0x00000210 */
	struct rbc_reg_ttreg_status_5_t TTReg_status_5; /* 0x00000214 */
	struct rbc_reg_ttreg_status_6_t TTReg_status_6; /* 0x00000218 */
	struct rbc_reg_ttreg_status_7_t TTReg_status_7; /* 0x0000021c */
	struct rbc_reg_ttreg_status_8_t TTReg_status_8; /* 0x00000220 */
	struct rbc_reg_ttreg_status_9_t TTReg_status_9; /* 0x00000224 */
	struct rbc_reg_ttreg_status_10_t TTReg_status_10; /* 0x00000228 */
	struct rbc_reg_ttreg_status_11_t TTReg_status_11; /* 0x0000022c */
	struct rbc_reg_ttreg_status_12_t TTReg_status_12; /* 0x00000230 */
	struct rbc_reg_ttreg_status_13_t TTReg_status_13; /* 0x00000234 */
	struct rbc_reg_ttreg_status_14_t TTReg_status_14; /* 0x00000238 */
	struct rbc_reg_ttreg_status_15_t TTReg_status_15; /* 0x0000023c */
	struct rbc_reg_ttreg_status_16_t TTReg_status_16; /* 0x00000240 */
	struct rbc_reg_ttreg_status_17_t TTReg_status_17; /* 0x00000244 */
	struct rbc_reg_ttreg_status_18_t TTReg_status_18; /* 0x00000248 */
	struct rbc_reg_ttreg_status_19_t TTReg_status_19; /* 0x0000024c */
	struct rbc_reg_ttreg_status_20_t TTReg_status_20; /* 0x00000250 */
	struct rbc_reg_ttreg_status_21_t TTReg_status_21; /* 0x00000254 */
	struct rbc_reg_ttreg_status_22_t TTReg_status_22; /* 0x00000258 */
	struct rbc_reg_ttreg_status_23_t TTReg_status_23; /* 0x0000025c */
	struct rbc_reg_ttreg_status_24_t TTReg_status_24; /* 0x00000260 */
	struct rbc_reg_ttreg_status_25_t TTReg_status_25; /* 0x00000264 */
	struct rbc_reg_ttreg_status_26_t TTReg_status_26; /* 0x00000268 */
	struct rbc_reg_ttreg_status_27_t TTReg_status_27; /* 0x0000026c */
	struct rbc_reg_ttreg_status_28_t TTReg_status_28; /* 0x00000270 */
	struct rbc_reg_ttreg_status_29_t TTReg_status_29; /* 0x00000274 */
	struct rbc_reg_ttreg_status_30_t TTReg_status_30; /* 0x00000278 */
	struct rbc_reg_ttreg_status_31_t TTReg_status_31; /* 0x0000027c */
};

struct rbc_reg_user_transaction_config0 {
	union {
		uint32_t value;
		struct {
			uint32_t id : 7; // [6:0]   RW
			uint32_t rsvd_7 : 1;
			uint32_t size : 3; // [10:8]  RW
			uint32_t rsvd_11 : 1;
			uint32_t burst : 2; // [13:12] RW
			uint32_t rsvd_14 : 2;
			uint32_t cache : 4; // [19:16] RW
			uint32_t lock : 1; // [20:20] RW
			uint32_t prot : 3; // [23:21] RW
			uint32_t blen : 4; // [27:24] RW
			uint32_t qos : 4; // [31:28] RW
		} __packed;
	};
};

struct rbc_reg_user_transaction_config1 {
	union {
		uint32_t value;
		uint32_t addr_l; // [31:0]   RW
	};
};

struct rbc_reg_user_transaction_config2 {
	union {
		uint32_t value;
		struct {
			uint32_t addr_h : 8; // [7:0]   RW
			uint32_t user : 24; // [31:8]  RW
		} __packed;
	};
};

struct rbc_reg_user_transaction_config3 {
	union {
		uint32_t value;
		uint32_t config; // [31:0]   RW
	};
};

/* Define a generic structure for user transaction configuration registers */
struct user_transaction_config {
	struct rbc_reg_user_transaction_config0 config0;
	struct rbc_reg_user_transaction_config1 config1;
	struct rbc_reg_user_transaction_config2 config2;
	struct rbc_reg_user_transaction_config3 config3;
};

struct timeout_status_reg_t {
	union {
		uint32_t value;
		struct {
			uint32_t axid : 7;
			uint32_t srcid : 16;
			uint32_t reserved_23 : 1;
			uint32_t to_flag : 1;
			uint32_t to_entry_number : 3;
			uint32_t detect_single_error : 1;
			uint32_t detect_double_error : 1;
			uint32_t reserved_30 : 1;
			uint32_t access_done : 1;
		} __packed;
	};
};

#endif /* __TB_RBC_GLUE_REG_MODEL_ */
