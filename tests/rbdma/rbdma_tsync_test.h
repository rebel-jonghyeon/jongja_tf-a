#ifndef __TSYNC_TEST_H__
#define __TSYNC_TEST_H__

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

//#define TEST_LOG
#ifdef TEST_LOG
#define LOG_INFO(format, ...) printf(format, ##__VA_ARGS__)
#else
#define LOG_INFO(format, ...) ((void)0)
#endif

#define ADDR_OFFSET_RBDMA_CDMA_GLOBAL	  0x00000000
#define ADDR_OFFSET_RBDMA_CDMA_TASK		  0x00000200
#define ADDR_OFFSET_RBDMA_CDMA_PT		  0x00000300
#define ADDR_OFFSET_RBDMA_CDMA_DPROFILE	  0x00000400
#define ADDR_OFFSET_RBDMA_CDMA_TSYNC	  0x00000800
#define ADDR_OFFSET_RBDMA_CDMA_DBG_UTLB	  0x00001000
#define ADDR_OFFSET_RBDMA_CDMA_DBG_TSYNC  0x00002000
#define ADDR_OFFSET_RBDMA_CDMA_AUTO_FETCH 0x00007000
#define ADDR_OFFSET_RBDMA_EDMA_GLOBAL	  0x00000000
#define ADDR_OFFSET_RBDMA_EDMA_SUBTASK	  0x00000200
#define ADDR_OFFSET_RBDMA_EDMA_DEBUG	  0x00000400
#define ADDR_OFFSET_RBDMA_EDMA_BUSPRF	  0x00000600

#define ADDR_OFFSET_RBDMA_TD_PTID_INIT				   0x0
#define ADDR_OFFSET_RBDMA_TD_SRCADDRESS_OR_CONST	   0x4
#define ADDR_OFFSET_RBDMA_TD_DESTADDRESS			   0x8
#define ADDR_OFFSET_RBDMA_TD_SIZEOF128BLOCK			   0xC
#define ADDR_OFFSET_RBDMA_TD_TSYNC_CONF_MASK		   0x10
#define ADDR_OFFSET_RBDMA_TD_SYNC_CONF_GIDX			   0x14
#define ADDR_OFFSET_RBDMA_TD_RUN_CONF0				   0x18
#define ADDR_OFFSET_RBDMA_TD_RUN_CONF1				   0x1C
#define ADDR_OFFSET_RBDMA_TDE_CHK_BASE_ADDR_MSB		   0x20
#define ADDR_OFFSET_RBDMA_TDE_CHK1_BASE_ADDR_OR_STRIDE 0x24
#define ADDR_OFFSET_RBDMA_TDE_CHK1_SIZE				   0x28
#define ADDR_OFFSET_RBDMA_TDE_CHK2_BASE_ADDR		   0x2C
#define ADDR_OFFSET_RBDMA_TDE_CHK2_SIZE				   0x30
#define ADDR_OFFSET_RBDMA_TDE_CHK3_BASE_ADDR		   0x34
#define ADDR_OFFSET_RBDMA_TDE_CHK3_SIZE				   0x38
#define ADDR_OFFSET_RBDMA_TDE_CHK4_BASE_ADDR		   0x3C
#define ADDR_OFFSET_RBDMA_TDE_CHK4_SIZE				   0x40
#define ADDR_OFFSET_RBDMA_TDE_CHK5_BASE_ADDR		   0x44
#define ADDR_OFFSET_RBDMA_TDE_CHK5_SIZE				   0x48
#define ADDR_OFFSET_RBDMA_TDE_CHK6_BASE_ADDR		   0x4C
#define ADDR_OFFSET_RBDMA_TDE_CHK6_SIZE				   0x50
#define ADDR_OFFSET_RBDMA_TDE_CHK7_BASE_ADDR		   0x54
#define ADDR_OFFSET_RBDMA_TDE_CHK7_SIZE				   0x58
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK1		   0x5C
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK2		   0x60
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK3		   0x64
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK4_RSV	   0x68
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK5_RSV	   0x6C
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK6_RSV	   0x70
#define ADDR_OFFSET_RBDMA_TDE_TSYNC_CONF_MASK7_RSV	   0x74
#define ADDR_OFFSET_RBDMA_TDE_RLSYNC_CONF_MASK		   0x78
#define ADDR_OFFSET_RBDMA_TDE_DONERPT_MST			   0x7C
#define ADDR_OFFSET_RBDMA_TD_RUN_CONF_EXT			   0x80

#define ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC0 0x004
#define ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0	  0x084

#define ADDR_OFFSET_RBDMA_CLOG_CLEAR			   0x000

union rbdma_td_ptid_init {
	struct __attribute__((packed)) {
		uint32_t func_id : 4;
		uint32_t ctx_id : 8;
		uint32_t thread_id : 4;
		uint32_t cmd_id : 16;
	};
	uint32_t bits;
};

union rbdma_td_srcaddress_or_const {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_td_destaddress {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_td_sizeof128block {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_td_tsync_conf_mask {
	struct __attribute__((packed)) {
		uint32_t get_dnc_mask : 16;
		uint32_t put_dnc_mask : 16;
	};
	uint32_t bits;
};

union rbdma_td_sync_conf_gidx {
	struct __attribute__((packed)) {
		uint32_t get_tsync_gidx : 7;
		uint32_t get_tsync_en : 1;
		uint32_t put_tsync_gidx : 7;
		uint32_t put_tsync_en : 1;
		uint32_t get_lsync_gidx : 6;
		uint32_t get_lsync_en : 1;
		uint32_t get_rlsync_en : 1;
		uint32_t put_lsync_gidx : 6;
		uint32_t put_lsync_en : 1;
		uint32_t put_rlsync_en : 1;
	};
	uint32_t bits;
};

union rbdma_td_run_conf0 {
	struct __attribute__((packed)) {
		uint32_t task_type : 4;
		uint32_t split_granule_l2 : 4;
		uint32_t ext_num_of_chunk : 12;
		uint32_t src_addr_msb : 2;
		uint32_t dst_addr_msb : 2;
		uint32_t tsync_dnc_code : 4;
		uint32_t ext_dnc_mask : 3;
		uint32_t fid_max : 1;
	};
	uint32_t bits;
};

union rbdma_td_run_conf1 {
	struct __attribute__((packed)) {
		uint32_t intr_disable : 1;
		uint32_t en_donerpt_mst : 1;
		uint32_t en_invalid_pt : 1;
		uint32_t no_tlb : 1;
		uint32_t map_lvl : 2;
		uint32_t iv_lvl : 2;
		uint32_t ptnum_or_v2pnum : 8;
		uint32_t read_bl : 2;
		uint32_t write_bl : 2;
		uint32_t te_mask : 8;
		uint32_t read_qos : 1;
		uint32_t write_qos : 1;
		uint32_t td_mst : 1;
		uint32_t queue_type : 1;
	};
	uint32_t bits;
};

union rbdma_global_config_cdma_opmode0 {
	struct __attribute__((packed)) {
		uint32_t en_cmgr_evt0 : 1;
		uint32_t en_cmgr_evt1 : 1;
		uint32_t en_cmgr_evt2 : 1;
		uint32_t lvl_op : 1;
		uint32_t sp_parallel : 1;
		uint32_t force_mst_mode : 1;
		uint32_t en_auto_fetch : 1;
		uint32_t max_perf : 1;
		uint32_t split_granule : 6;
		uint32_t read_bl : 2;
		uint32_t write_bl : 2;
		uint32_t overwrite : 1;
		uint32_t mp_mode : 1;
		uint32_t mp_hash_pos0 : 4;
		uint32_t mp_hash_pos1 : 4;
		uint32_t mp_hash_pos2 : 4;
	};
	uint32_t bits;
};

union rbdma_clog_num_nrm_tdone_tstc0 {
	struct __attribute__((packed)) {
		uint32_t na : 32;
	};
	uint32_t bits;
};

union rbdma_clog_clear {
	struct __attribute__((packed)) {
		uint32_t clear : 1;
		uint32_t reserved : 31;
	};
	uint32_t bits;
};

int rbdma_test_dram_2_shm(void);
int rbdma_test_shm_2_dram(void);
int rbdma_test_dram_2_dram(void);

#endif /* __TSYNC_TEST_H__ */
