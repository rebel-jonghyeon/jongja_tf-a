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

#ifndef _G_DNC_CONFIG_COMMON_H_
#define _G_DNC_CONFIG_COMMON_H_

#define ADDR_OFFSET_DNC_CONFIG_IP_INFO0				  0x000
#define ADDR_OFFSET_DNC_CONFIG_IP_INFO1				  0x004
#define ADDR_OFFSET_DNC_CONFIG_IP_INFO2				  0x008
#define ADDR_OFFSET_DNC_CONFIG_IP_INFO3				  0x00C
#define ADDR_OFFSET_DNC_CONFIG_DESIGN_INFO0			  0x010
#define ADDR_OFFSET_DNC_CONFIG_DESIGN_INFO1			  0x014
#define ADDR_OFFSET_DNC_CONFIG_AUTO_CONFIG			  0x018
#define ADDR_OFFSET_DNC_CONFIG_COMMON_REG			  0x01C
#define ADDR_OFFSET_DNC_CONFIG_DUMMY_JIC0			  0x028
#define ADDR_OFFSET_DNC_CONFIG_DUMMY_JIC1			  0x02C
#define ADDR_OFFSET_DNC_CONFIG_DO0					  0x030
#define ADDR_OFFSET_DNC_CONFIG_TRIG0				  0x040
#define ADDR_OFFSET_DNC_CONFIG_ID_CFG				  0x050
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_CFG			  0x080
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_TGV0			  0x084
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_TGV1			  0x088
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_SOFF_TGV0		  0x08C
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_SOFF_TGV1		  0x090
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ABORT_SOFF_TGV0 0x094
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ABORT_SOFF_TGV1 0x098
#define ADDR_OFFSET_DNC_CONFIG_COMP_TLB0			  0x100
#define ADDR_OFFSET_DNC_CONFIG_COMP_TLB1			  0x104
#define ADDR_OFFSET_DNC_CONFIG_COMP_TLB2			  0x108
#define ADDR_OFFSET_DNC_CONFIG_COMP_TLB3			  0x10C
#define ADDR_OFFSET_DNC_CONFIG_LDUDMA_TLB0			  0x110
#define ADDR_OFFSET_DNC_CONFIG_LDUDMA_TLB1			  0x114
#define ADDR_OFFSET_DNC_CONFIG_LDUDMA_TLB2			  0x118
#define ADDR_OFFSET_DNC_CONFIG_LDUDMA_TLB3			  0x11C
#define ADDR_OFFSET_DNC_CONFIG_LPUDMA_TLB0			  0x120
#define ADDR_OFFSET_DNC_CONFIG_LPUDMA_TLB1			  0x124
#define ADDR_OFFSET_DNC_CONFIG_LPUDMA_TLB2			  0x128
#define ADDR_OFFSET_DNC_CONFIG_LPUDMA_TLB3			  0x12C
#define ADDR_OFFSET_DNC_CONFIG_STUDMA_TLB0			  0x130
#define ADDR_OFFSET_DNC_CONFIG_STUDMA_TLB1			  0x134
#define ADDR_OFFSET_DNC_CONFIG_STUDMA_TLB2			  0x138
#define ADDR_OFFSET_DNC_CONFIG_STUDMA_TLB3			  0x13C
#define ADDR_OFFSET_DNC_CONFIG_SP_EN				  0x200
#define ADDR_OFFSET_DNC_CONFIG_SP_CFG0				  0x204
#define ADDR_OFFSET_DNC_CONFIG_SP_CFG1				  0x208
#define ADDR_OFFSET_DNC_CONFIG_SP_CFG2				  0x20C
#define ADDR_OFFSET_DNC_CONFIG_SP_CFG3				  0x210
#define ADDR_OFFSET_DNC_CONFIG_SRAM_CFG0			  0x214
#define ADDR_OFFSET_DNC_CONFIG_SRAM_CFG4			  0x224
#define ADDR_OFFSET_DNC_CONFIG_SP_TEST				  0x240
#define ADDR_OFFSET_DNC_CONFIG_SP_PINIT				  0x248
#define ADDR_OFFSET_DNC_CONFIG_SP_PINIT_CFG			  0x24C
#define ADDR_OFFSET_DNC_CONFIG_SP_DMAP0				  0x250
#define ADDR_OFFSET_DNC_CONFIG_SP_DMAP1				  0x254
#define ADDR_OFFSET_DNC_CONFIG_SP_DMAP2				  0x258

union dnc_config_ip_info0 {
	struct __attribute__((packed)) {
		uint32_t release_date : 32;
	};
	uint32_t bits;
};

union dnc_config_ip_info1 {
	struct __attribute__((packed)) {
		uint32_t min_ver : 8;
		uint32_t maj_ver : 8;
		uint32_t ip_ver : 8;
		uint32_t ip_id : 8;
	};
	uint32_t bits;
};

union dnc_config_ip_info2 {
	struct __attribute__((packed)) {
		uint32_t dnc_unit_id : 8;
		uint32_t rdsn_rtid0 : 8;
		uint32_t rdsn_rtid1 : 8;
		uint32_t rdsn_ready0 : 1;
		uint32_t rdsn_ready1 : 1;
		uint32_t rsvd26 : 6;
	};
	uint32_t bits;
};

union dnc_config_ip_info3 {
	struct __attribute__((packed)) {
		uint32_t regmap_min_ver : 8;
		uint32_t regmap_maj_ver : 8;
		uint32_t rsvd16 : 16;
	};
	uint32_t bits;
};

union dnc_config_design_info0 {
	struct __attribute__((packed)) {
		uint32_t credit_comp : 8;
		uint32_t credit_ldudma : 8;
		uint32_t credit_lpudma : 8;
		uint32_t credit_studma : 8;
	};
	uint32_t bits;
};

union dnc_config_design_info1 {
	struct __attribute__((packed)) {
		uint32_t marker : 32;
	};
	uint32_t bits;
};

union dnc_config_auto_config {
	struct __attribute__((packed)) {
		uint32_t dar : 1;
		uint32_t dac : 1;
		uint32_t rsvd2 : 30;
	};
	uint32_t bits;
};

union dnc_config_common_reg {
	struct __attribute__((packed)) {
		uint32_t rsvd : 32;
	};
	uint32_t bits;
};

union dnc_config_dummy_jic0 {
	struct __attribute__((packed)) {
		uint32_t config : 32;
	};
	uint32_t bits;
};

union dnc_config_dummy_jic1 {
	struct __attribute__((packed)) {
		uint32_t status : 32;
	};
	uint32_t bits;
};

union dnc_config_do0 {
	struct __attribute__((packed)) {
		uint32_t clear_keep_all : 1;
		uint32_t clear_keep_core : 1;
		uint32_t rsvd2 : 6;
		uint32_t insist_ncspwr0 : 1;
		uint32_t insist_ncspwr1 : 1;
		uint32_t insist_ncsprd0 : 1;
		uint32_t insist_ncsprd1 : 1;
		uint32_t rsvd12 : 20;
	};
	uint32_t bits;
};

union dnc_config_trig0 {
	struct __attribute__((packed)) {
		uint32_t clear_all : 1;
		uint32_t clear_core : 1;
		uint32_t clear_dm : 1;
		uint32_t clear_sp : 1;
		uint32_t clear_nclsu : 1;
		uint32_t rsvd5 : 11;
		uint32_t init_cfg : 1;
		uint32_t rsvd17 : 15;
	};
	uint32_t bits;
};

union dnc_config_id_cfg {
	struct __attribute__((packed)) {
		uint32_t fid_max : 1;
		uint32_t rsvd1 : 31;
	};
	uint32_t bits;
};

union dnc_config_pthrot_cfg {
	struct __attribute__((packed)) {
		uint32_t en : 1;
		uint32_t reset : 1;
		uint32_t rsvd2 : 6;
		uint32_t period : 8;
		uint32_t rsvd16 : 16;
	};
	uint32_t bits;
};

union dnc_config_pthrot_tgv0 {
	struct __attribute__((packed)) {
		uint32_t ncore0 : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_tgv1 {
	struct __attribute__((packed)) {
		uint32_t ncore1 : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_soff_tgv0 {
	struct __attribute__((packed)) {
		uint32_t ncore0 : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_soff_tgv1 {
	struct __attribute__((packed)) {
		uint32_t ncore1 : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_abort_soff_tgv0 {
	struct __attribute__((packed)) {
		uint32_t ncore0 : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_abort_soff_tgv1 {
	struct __attribute__((packed)) {
		uint32_t ncore1 : 32;
	};
	uint32_t bits;
};

union dnc_config_comp_tlb0 {
	struct __attribute__((packed)) {
		uint32_t uan_info : 16;
		uint32_t clr_addr : 16;
	};
	uint32_t bits;
};

union dnc_config_comp_tlb1 {
	struct __attribute__((packed)) {
		uint32_t clr_data_type1 : 32;
	};
	uint32_t bits;
};

union dnc_config_comp_tlb2 {
	struct __attribute__((packed)) {
		uint32_t clr_data_type2 : 32;
	};
	uint32_t bits;
};

union dnc_config_comp_tlb3 {
	struct __attribute__((packed)) {
		uint32_t vaddr_base : 16;
		uint32_t paddr_base : 16;
	};
	uint32_t bits;
};

union dnc_config_ldudma_tlb0 {
	struct __attribute__((packed)) {
		uint32_t uan_info : 16;
		uint32_t clr_addr : 16;
	};
	uint32_t bits;
};

union dnc_config_ldudma_tlb1 {
	struct __attribute__((packed)) {
		uint32_t clr_data_type1 : 32;
	};
	uint32_t bits;
};

union dnc_config_ldudma_tlb2 {
	struct __attribute__((packed)) {
		uint32_t clr_data_type2 : 32;
	};
	uint32_t bits;
};

union dnc_config_ldudma_tlb3 {
	struct __attribute__((packed)) {
		uint32_t vaddr_base : 16;
		uint32_t paddr_base : 16;
	};
	uint32_t bits;
};

union dnc_config_lpudma_tlb0 {
	struct __attribute__((packed)) {
		uint32_t uan_info : 16;
		uint32_t clr_addr : 16;
	};
	uint32_t bits;
};

union dnc_config_lpudma_tlb1 {
	struct __attribute__((packed)) {
		uint32_t clr_data_type1 : 32;
	};
	uint32_t bits;
};

union dnc_config_lpudma_tlb2 {
	struct __attribute__((packed)) {
		uint32_t clr_data_type2 : 32;
	};
	uint32_t bits;
};

union dnc_config_lpudma_tlb3 {
	struct __attribute__((packed)) {
		uint32_t vaddr_base : 16;
		uint32_t paddr_base : 16;
	};
	uint32_t bits;
};

union dnc_config_studma_tlb0 {
	struct __attribute__((packed)) {
		uint32_t uan_info : 16;
		uint32_t clr_addr : 16;
	};
	uint32_t bits;
};

union dnc_config_studma_tlb1 {
	struct __attribute__((packed)) {
		uint32_t clr_data_type1 : 32;
	};
	uint32_t bits;
};

union dnc_config_studma_tlb2 {
	struct __attribute__((packed)) {
		uint32_t clr_data_type2 : 32;
	};
	uint32_t bits;
};

union dnc_config_studma_tlb3 {
	struct __attribute__((packed)) {
		uint32_t vaddr_base : 16;
		uint32_t paddr_base : 16;
	};
	uint32_t bits;
};

union dnc_config_sp_en {
	struct __attribute__((packed)) {
		uint32_t cfg_sp : 1;
		uint32_t cfg_dmap : 1;
		uint32_t rsvd2 : 30;
	};
	uint32_t bits;
};

union dnc_config_sp_cfg0 {
	struct __attribute__((packed)) {
		uint32_t ba0_mcyc : 2;
		uint32_t ba0_rwpv : 6;
		uint32_t ba1_mcyc : 2;
		uint32_t ba1_rwpv : 6;
		uint32_t ba2_mcyc : 2;
		uint32_t ba2_rwpv : 6;
		uint32_t ba3_mcyc : 2;
		uint32_t ba3_rwpv : 6;
	} sp_cfg0;
	uint32_t bits;
};

union dnc_config_sp_cfg1 {
	struct __attribute__((packed)) {
		uint32_t ba4_mcyc : 2;
		uint32_t ba4_rwpv : 6;
		uint32_t ba5_mcyc : 2;
		uint32_t ba5_rwpv : 6;
		uint32_t ba6_mcyc : 2;
		uint32_t ba6_rwpv : 6;
		uint32_t ba7_mcyc : 2;
		uint32_t ba7_rwpv : 6;
	} sp_cfg1;
	uint32_t bits;
};

union dnc_config_sp_cfg2 {
	struct __attribute__((packed)) {
		uint32_t ecc_on : 1;
		uint32_t rsvd1 : 3;
		uint32_t sad_on : 1;
		uint32_t rsvd2 : 3;
		uint32_t einjec : 8;
		uint32_t addr_mode : 2;
		uint32_t dummy_screen : 2;
		uint32_t mo_cfg0 : 4;
		uint32_t mo_cfg1 : 4;
		uint32_t mo_cfg2 : 4;
	} sp_cfg2;
	uint32_t bits;
};

union dnc_config_sp_cfg3 {
	struct __attribute__((packed)) {
		uint32_t pssm_wreq : 1;
		uint32_t pssm_rreq : 1;
		uint32_t pssm_wrsp : 1;
		uint32_t pssm_rrsp : 1;
		uint32_t rsvd4 : 4;
		uint32_t sinsist_wr : 3;
		uint32_t rsvd11 : 5;
		uint32_t sinsist_rd : 5;
		uint32_t rsvd21 : 11;
	} sp_cfg3;
	uint32_t bits;
};

union dnc_config_sram_cfg0 {
	uint32_t bits;
};

union dnc_config_sram_cfg4 {
	struct __attribute__((packed)) {
		uint32_t macro : 32;
	};
	uint32_t bits;
};

union dnc_config_sp_test {
	struct __attribute__((packed)) {
		uint32_t trig : 1;
		uint32_t rsvd1 : 3;
		uint32_t pattern : 4;
		uint32_t log_mode : 4;
		uint32_t rsvd12 : 20;
	};
	uint32_t bits;
};

union dnc_config_sp_pinit {
	struct __attribute__((packed)) {
		uint32_t trig : 1;
		uint32_t done : 1;
		uint32_t rsvd1 : 2;
		uint32_t addr : 16;
		uint32_t size : 12;
	};
	uint32_t bits;
};

union dnc_config_sp_pinit_cfg {
	struct __attribute__((packed)) {
		uint32_t bcnt : 8;
		uint32_t dcnt : 8;
		uint32_t skew : 8;
		uint32_t rsvd24 : 8;
	};
	uint32_t bits;
};

union dnc_config_sp_dmap0 {
	struct __attribute__((packed)) {
		uint32_t sval : 32;
	};
	uint32_t bits;
};

union dnc_config_sp_dmap1 {
	struct __attribute__((packed)) {
		uint32_t arbc0 : 32;
	};
	uint32_t bits;
};

union dnc_config_sp_dmap2 {
	struct __attribute__((packed)) {
		uint32_t arbc1 : 32;
	};
	uint32_t bits;
};

#endif /* _G_DNC_CONFIG_COMMON_H_*/
