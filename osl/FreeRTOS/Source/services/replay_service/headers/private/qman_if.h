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

#ifndef QMAN_IF_H
#define QMAN_IF_H

#ifndef __stringify
#ifndef	__stringify_1
#define __stringify_1(x...)	#x
#endif	/* __stringify_1 */
#define __stringify(x...)	__stringify_1(x)
#endif	/* __stringify */

#define QMAN_IF_MAJOR_VER	17
#define QMAN_IF_MINOR_VER	0
#define QMAN_IF_VER		__stringify(QMAN_IF_MAJOR_VER) "."\
				__stringify(QMAN_IF_MINOR_VER)

#include "qman_if_common.h"

#define MAX_SYNC_ID				0x7f
#define HALF_MAX_SYNC_ID			0x40

#define CP_SYNC_PACKET_SHIFT_HOST_SYNC		1
#define CP_SYNC_PACKET_SHIFT_PUT		0
#define CP_SYNC_PACKET_MASK_HOST_SYNC		((0x1) << CP_SYNC_PACKET_SHIFT_HOST_SYNC)
#define CP_SYNC_PACKET_MASK_PUT			((0x1) << CP_SYNC_PACKET_SHIFT_PUT)
#define CP_SYNC_PACKET_MASK_USER_SPECIFIED	(CP_SYNC_PACKET_MASK_HOST_SYNC | \
						 CP_SYNC_PACKET_MASK_PUT)
#define CP_SYNC_PACKET_GET_HOST_SYNC(h)		(((h) >> CP_SYNC_PACKET_SHIFT_HOST_SYNC) & 0x1)
#define CP_SYNC_PACKET_GET_PUT(h)		(((h) >> CP_SYNC_PACKET_SHIFT_PUT) & 0x1)

#define CP_BARRIER_PACKET_SHIFT_HOST_SYNC	CP_SYNC_PACKET_SHIFT_HOST_SYNC
#define CP_BARRIER_PACKET_SHIFT_PUT		CP_SYNC_PACKET_SHIFT_PUT
#define CP_BARRIER_PACKET_MASK_HOST_SYNC	CP_SYNC_PACKET_MASK_HOST_SYNC
#define CP_BARRIER_PACKET_MASK_PUT		CP_SYNC_PACKET_MASK_PUT
#define CP_BARRIER_PACKET_MASK_USER_SPECIFIED	CP_SYNC_PACKET_MASK_USER_SPECIFIED
#define CP_BARRIER_PACKET_GET_HOST_SYNC(h)	CP_SYNC_PACKET_GET_HOST_SYNC(h)
#define CP_BARRIER_PACKET_GET_PUT(h)		CP_SYNC_PACKET_GET_PUT(h)

#define CP_IB_PACKET_SHIFT_MAIN			0
#define CP_IB_PACKET_BITS_MAIN			0xFu
#define CP_IB_PACKET_MASK_MAIN			(CP_IB_PACKET_BITS_MAIN << CP_IB_PACKET_SHIFT_MAIN)
#define CP_IB_PACKET_MASK_USER_SPECIFIED	(CP_IB_PACKET_MASK_MAIN)
#define CP_IB_PACKET_GET_MAIN(h)		\
		(((h) >> CP_IB_PACKET_SHIFT_MAIN) & CP_IB_PACKET_BITS_MAIN)

enum packet_id_ext {
	GUARD_PACKET_IDX_EXT	= 0xf7,
	PACKET_CONST_BUF_DESC	= 0xf8,
	PACKET_QUERY_RESET	= 0xf9,
	PACKET_QUERY_END	= 0xfa,
	PACKET_QUERY_BEGIN	= 0xfb,
	PACKET_SYNC		= 0xfc,
	PACKET_BARRIER		= 0xfd,
	PACKET_INDIRECT_BUFFER	= 0xfe,
	MAX_PACKET_ID_EXT	= MAX_PACKET_ID,
	INVALID_PACKET_ID_EXT	= INVALID_PACKET_ID,
};

struct packet_indirect_buffer {
	__le32 header;
	__le32 size;
	__le64 addr;
};

/*
 * Sync-related functions
 */
struct packet_barrier {
	__le32 header;
	__le32 put_sync_id;

	/*
	 * If get_sync_bits is zero, a barrier packet waits all previous packets in the command
	 * buffer.
	 * If get_sync_bits is not zero, a barrier packet waits the sync ids specified in it.
	 */
	__le64 get_sync_bits_lo;
	__le64 get_sync_bits_hi;
};

struct packet_sync {
	__le32 header;
	__le32 put_sync_id;

	/*
	 * If get_sync_bits is zero, a sync packet doesn't wait anything.
	 * If get_sync_bits is not zero, a sync packet waits the sync ids specified in it.
	 */
	__le64 get_sync_bits_lo;
	__le64 get_sync_bits_hi;
};

/*
 * Query-related functions
 */
#define QUERY_DESC_SHIFT_COUNT	0u
#define QUERY_DESC_BITS_COUNT	0xFFu
#define QUERY_DESC_MASK_COUNT	((QUERY_DESC_BITS_COUNT) << QUERY_DESC_SHIFT_COUNT)
#define QUERY_DESC_GET_COUNT(h)	(((h) & QUERY_DESC_MASK_COUNT) >> QUERY_DESC_SHIFT_COUNT)
#define QUERY_DESC_HEADER(n)	(((n) & QUERY_DESC_BITS_COUNT) << QUERY_DESC_SHIFT_COUNT)

#define HW_COUNTER_DESC_SHIFT_COUNT	0u
#define HW_COUNTER_DESC_BITS_COUNT	0xFFu
#define HW_COUNTER_DESC_MASK(name)	\
		((HW_COUNTER_DESC_BITS_ ## name) << HW_COUNTER_DESC_SHIFT_ ## name)
#define HW_COUNTER_DESC_GET(name, h)	\
		(((h) & HW_COUNTER_DESC_MASK(name)) >> HW_COUNTER_DESC_SHIFT_ ## name)
#define HW_COUNTER_DESC_SET(name, t)	\
		(((t) & HW_COUNTER_DESC_BITS_ ## name) << HW_COUNTER_DESC_SHIFT_ ## name)
#define HW_COUNTER_DESC_HEADER(n)	HW_COUNTER_DESC_SET(COUNT, n)

#define CS_HW_COUNTER_SIZE_DNC_RUNNING_CYCLE		sizeof(__le32)
#define CS_HW_COUNTER_SIZE_DONE_IRQ_TICK		sizeof(__le64)
#define CS_HW_COUNTER_SIZE_DDMA_RUNNING_CYCLE		sizeof(__le32)
#define CS_HW_COUNTER_SIZE_SYNC_RUNNING_CYCLE		sizeof(__le32)
#define CS_HW_COUNTER_SIZE_DEVICE_HDMA_RUNNING_CYCLE	sizeof(__le32)

#define HDMA_COUNTER_SIZE_RUNNING_CYCLE		sizeof(__le32)
#define HDMA_COUNTER_SIZE_DONE_TICK		sizeof(__le64)

#define HW_INFO_SHIFT_COUNT	0u
#define HW_INFO_BITS_COUNT	0xFFu
#define HW_INFO_MASK_COUNT	((HW_INFO_BITS_COUNT) << HW_INFO_SHIFT_COUNT)
#define HW_INFO_GET_COUNT(h)	(((h) & HW_INFO_MASK_COUNT) >> HW_INFO_SHIFT_COUNT)
#define HW_INFO_HEADER(n)	(((n) & HW_INFO_BITS_COUNT) << HW_INFO_SHIFT_COUNT)

/**
 * enum query_type - enumeration of query type
 *
 * It should be sams as the `enum rblnthunk_query_type` in "rblnthunk.h"
 */
enum query_type {
	QUERY_TYPE_CS_HW_COUNTER,
	QUERY_TYPE_HW_INFO,
	QUERY_TYPE_HDMA_COUNTER,
	QUERY_TYPE_NUM,
	QUERY_TYPE_INVALID = QUERY_TYPE_NUM,
};

/**
 * enum cs_hw_counter_type - enumeration of hardware counter type in command stream
 */
enum cs_hw_counter_type {
	CS_HW_COUNTER_DNC_RUNNING_CYCLE,
	CS_HW_COUNTER_DONE_IRQ_TICK,
	CS_HW_COUNTER_DDMA_RUNNING_CYCLE,
	CS_HW_COUNTER_SYNC_RUNNING_CYCLE,
	CS_HW_COUNTER_DEVICE_HDMA_RUNNING_CYCLE,
	CS_HW_COUNTER_NUM,
	CS_HW_COUNTER_INVALID			= CS_HW_COUNTER_NUM,
};

/**
 * enum hdma_counter_type - enumeration of HDMA counter
 */
enum hdma_counter_type {
	HDMA_COUNTER_RUNNING_CYCLE,
	HDMA_COUNTER_DONE_TICK,
	HDMA_COUNTER_TYPE_NUM,
	HDMA_COUNTER_INVALID		= HDMA_COUNTER_TYPE_NUM,
};

/**
 * struct query_counter_desc - descriptor of query counter extension
 * @header: information of this structure
 * @array_len: length of counter type structure list
 * @desc_array_ptr: device virtual address of counter type structure list
 *
 * This structure describes hardware counter list. The `header` variable has the size of payload of
 * this structure, and it can be used to verify whether the descriptor written by user is able to
 * be used in the FW.
 * Currently, the `desc_array_ptr` variable is pointing the device virtual address just behind the
 * device virtual address of this structure. So, the memory layout is like below.
 *
 *   |--------------------------------|
 *   |   struct query_counter_desc    |
 *   |--------------------------------| ---------
 *   |        desc structure #1       |     |
 *   |--------------------------------|     |
 *   |        desc structure #2       | array_len * sizeof(desc structure)
 *   |--------------------------------|     |
 *   |              ...               |     |
 *   |--------------------------------| ---------
 */
struct query_counter_desc {
	__le32 header;
	__le32 array_len;
	__le64 desc_array_ptr;
};

struct cs_hw_counter_type_1 {
	union {
		struct {
			__le32 DNC_running_cycle		: 1;
			__le32 done_irq_tick			: 1;
			__le32 ddma_running_cycle		: 1;
			__le32 sync_running_cycle		: 1;
			__le32 device_hdma_running_cycle	: 1;
			__le32 reserved				: 27;
		};
		__le32 u32All;
	};
};

struct hdma_counter_type_1 {
	union {
		struct {
			__le32 runninc_cycle	: 1;
			__le32 done_tick	: 1;
			__le32 reserved		: 30;
		};
		__le32 u32All;
	};
};

/**
 * struct query_hw_info - query type structure of hardware information
 * @cp_freq: CP frequency at the time of query
 * @dcluster0_freq: frequency of DNC cluster 0 at the time of query
 *
 * This structure provides a hardware configuration, e.g., Dcluster0 frequency, CP frequency.
 * This structure should be same as `struct rblnthunk_query_hw_info` in rblnthunk.h
 */
struct query_hw_info {
	__le32 cp_freq;
	__le32 dcluster0_freq;
	__le32 bus_freq;
};

/**
 * struct query_desc - descriptor of query
 * @header: information of this structure
 * @type: value of `enum query_type`
 * @ext_desc: extension descriptor address info (e.g., query_counter_desc)
 * @dva: start device virtual address of query pool memory
 * @size: size of query pool memory
 * @stride: stride value for each query (== query size of each query
 *                                       == total size of hardware counter data of each query)
 *          : Use this for verifying size of hw counters between UMD and FW
 * @query_cnt: the number of query
 *
 * The `header` variable has the size of payload of this structure, and it can be used to verify
 * whether the descriptor written by user is able to be used in the FW.
 */
struct query_desc {
	__le32 header;
	__le32 type;
	__le64 ext_desc;
	__le64 dva;
	__le64 size;
	__le64 stride;
	__le32 query_cnt;
};

/**
 * struct packet_query_reset - packet to reset query results memory
 * @header: payload value is used for verifying structure size between UMD and FW
 * @desc_addr: device virtual address of struct query_desc
 * @query_idx: start query index to be reset
 * @query_cnt: number of queries to be reset
 */
struct packet_query_reset {
	__le32 header;
	__le64 desc_addr;
	__le32 query_idx;
	__le32 query_cnt;
};

/**
 * struct packet_query_begin - packet for beginning query
 * @header: payload value is used for verifying structure size between UMD and FW
 * @desc_addr: device virtual address of struct query_desc
 * @query_idx: use it when multiple begin/end pairs for single query pool
 */
struct packet_query_begin {
	__le32 header;
	__le64 desc_addr;
	__le32 query_idx;
};

/**
 * struct packet_query_end - packet for finishing query
 * @header: payload value is used for verifying structure size between UMD and FW
 * @desc_addr: device virtual address of struct query_desc
 * @query_idx: use it when multiple begin/end pairs for single query pool
 */
struct packet_query_end {
	__le32 header;
	__le64 desc_addr;
	__le32 query_idx;
};

/*
 * Constant Buffer-related
 */
/**
 * < Memory Layout Information >
 * |--------------------------|
 * |  constant buffr pool HDR |		// constant buffer count
 * |--------------------------|
 * |    buffer #0's header    |		// constant buffer size
 * |     buffer #0's addr     | -|
 * |--------------------------|  |
 * |    buffer #1's header    |  |
 * |     buffer #1's addr     | -|-|
 * |--------------------------|  | |
 * |           ...            |  | |
 * |--------------------------|  | |
 * |                          |  | |
 * |            ~             |  | |
 * |                          |  | |
 * |--------------------------|  | |
 * |  Data_Group_0 - Data_0   |<-| |	// size of single data is aligned to 4B
 * |--------------------------|    |
 * |  Data_Group_0 - Data_..  |    |
 * |--------------------------|    |
 * |  Data_Group_0 - Data_N   |    |
 * |--------------------------|    |
 * |  Data_Group_1 - Data_0   |    |
 * |--------------------------|    |
 * |  Data_Group_1 - Data_..  |    |
 * |--------------------------|    |
 * |  Data_Group_1 - Data_N   |    |
 * |--------------------------|    |
 * |           ...            |    |
 * |--------------------------|    |
 * |                          |    |
 * |            ~             |    |
 * |                          |    |
 * |--------------------------|    |
 * |  Data_Group_0 - Data_0   |<---|
 * |--------------------------|
 * |           ...            |
 * |--------------------------|
 */

#define CONST_BUF_POOL_DESC_SHIFT_BUF_CNT	0
#define CONST_BUF_POOL_DESC_BITS_BUF_CNT	0xFFu
#define CONST_BUF_POOL_DESC_MAX_BUF_CNT		((CONST_BUF_POOL_DESC_BITS_BUF_CNT) + 1)
#define CONST_BUF_POOL_DESC_MASK_BUF_CNT	\
	((CONST_BUF_POOL_DESC_BITS_BUF_CNT) << (CONST_BUF_POOL_DESC_SHIFT_BUF_CNT))
#define CONST_BUF_POOL_DESC_GET_BUF_CNT(h)	\
	((((h) & CONST_BUF_POOL_DESC_MASK_BUF_CNT) >> CONST_BUF_POOL_DESC_SHIFT_BUF_CNT) ?	\
	 : (CONST_BUF_POOL_DESC_MAX_BUF_CNT))

/**
 * struct const_buf_pool_desc - descriptor of constant buffer pool
 * @header: information of constant buffer pool (e.g., total buffer count, etc)
 *
 * "header" can be interpreted using above defines
 */
struct const_buf_pool_desc {
	__le64 header;
};

#define CONST_BUF_DESC_SHIFT_GROUP_NUM	24
#define CONST_BUF_DESC_SHIFT_DATA_NUM	16
#define CONST_BUF_DESC_SHIFT_ELEM_NUM	8
#define CONST_BUF_DESC_SHIFT_ELEM_SIZE	4
#define CONST_BUF_DESC_SHIFT_BUF_TYPE	0
#define CONST_BUF_DESC_BITS_GROUP_NUM	0xFFu
#define CONST_BUF_DESC_BITS_DATA_NUM	0x3Fu
#define CONST_BUF_DESC_BITS_ELEM_NUM	0xFu
#define CONST_BUF_DESC_BITS_ELEM_SIZE	0xFu
#define CONST_BUF_DESC_BITS_BUF_TYPE	0xFu
#define CONST_BUF_DESC_MASK_GROUP_NUM	\
	((CONST_BUF_DESC_BITS_GROUP_NUM) << (CONST_BUF_DESC_SHIFT_GROUP_NUM))
#define CONST_BUF_DESC_MASK_DATA_NUM	\
	((CONST_BUF_DESC_BITS_DATA_NUM) << (CONST_BUF_DESC_SHIFT_DATA_NUM))
#define CONST_BUF_DESC_MASK_ELEM_NUM	\
	((CONST_BUF_DESC_BITS_ELEM_NUM) << (CONST_BUF_DESC_SHIFT_ELEM_NUM))
#define CONST_BUF_DESC_MASK_ELEM_SIZE	\
	((CONST_BUF_DESC_BITS_ELEM_SIZE) << (CONST_BUF_DESC_SHIFT_ELEM_SIZE))
#define CONST_BUF_DESC_MASK_BUF_TYPE	\
	((CONST_BUF_DESC_BITS_BUF_TYPE) << (CONST_BUF_DESC_SHIFT_BUF_TYPE))
#define CONST_BUF_DESC_GET_GROUP_NUM(h)	\
	((((h) & CONST_BUF_DESC_MASK_GROUP_NUM) >> CONST_BUF_DESC_SHIFT_GROUP_NUM) ?	\
	 : (CONST_BUF_DESC_BITS_GROUP_NUM + 1))
#define CONST_BUF_DESC_GET_DATA_NUM(h)	\
	((((h) & CONST_BUF_DESC_MASK_DATA_NUM) >> CONST_BUF_DESC_SHIFT_DATA_NUM) ?	\
	 : (CONST_BUF_DESC_BITS_DATA_NUM + 1))
#define CONST_BUF_DESC_GET_ELEM_NUM(h)	\
	((((h) & CONST_BUF_DESC_MASK_ELEM_NUM) >> CONST_BUF_DESC_SHIFT_ELEM_NUM) ?	\
	 : (CONST_BUF_DESC_BITS_ELEM_NUM + 1))
#define CONST_BUF_DESC_GET_ELEM_SIZE(h)	\
	(((h) & CONST_BUF_DESC_MASK_ELEM_SIZE) >> CONST_BUF_DESC_SHIFT_ELEM_SIZE)
#define CONST_BUF_DESC_GET_BUF_TYPE(h)	\
	(((h) & CONST_BUF_DESC_MASK_BUF_TYPE) >> CONST_BUF_DESC_SHIFT_BUF_TYPE)

#define CONST_BUF_DATA_SIZE_ALIGNMENT	sizeof(__le32)
#define CONST_BUF_GET_ALIGNED_DATA_SIZE(elem_num, elem_size)					\
	((((0x1UL << (elem_size)) * (elem_num)) + (CONST_BUF_DATA_SIZE_ALIGNMENT) - 1) &	\
	(~((CONST_BUF_DATA_SIZE_ALIGNMENT) - 1)))

/**
 * struct const_buf_desc - descriptor of constant buffer
 * @header: information of constant buffer (e.g., number of data and data group, etc)
 * @dva: device virtual address of the memory where the data resides
 *
 * "header" can be interpreted using above defines
 */
struct const_buf_desc {
	__le64 header;
	__le64 dva;
};

/**
 * struct packet_const_buf_desc - packet to point to pool descriptor memory
 * @header: information of packet (e.g., payload size, etc)
 * @addr: device virtual address of the memory where pool descriptor resides
 * @size: size of pool descriptor
 *
 * "header" can be interpreted using above defines
 */
struct packet_const_buf_desc {
	__le32 header;
	__le64 addr;
};

/*
 * Message queue-related functions
 */
enum rbln_msg_packet_op_ext {
	RBLN_MSG_OP_FW_VER = RBLN_MSG_OP_NUM,
	RBLN_MSG_OP_CHIP_INFO,
	RBLN_MSG_OP_TEMP,
	RBLN_MSG_OP_PMIC,
	RBLN_MSG_OP_CDB,
	RBLN_MSG_OP_CDB_MODE_SET,
	RBLN_MSG_OP_CDB_MODE_GET,
	RBLN_MSG_OP_CDB_BREAK_SET,
	RBLN_MSG_OP_CDB_BREAK_GET,
	RBLN_MSG_OP_CDB_DELETE_ALL,
	RBLN_MSG_OP_CDB_DELETE,
	RBLN_MSG_OP_CDB_GO,
	RBLN_MSG_OP_CDB_GO_CMD,
	RBLN_MSG_OP_CDB_STEP,
	RBLN_MSG_OP_CDB_CUR_CMD_GET,
	RBLN_MSG_OP_CDB_DONE_CMD_GET,
	RBLN_MSG_OP_CDB_QUIT,
	RBLN_MSG_OP_SP_DUMP,
	RBLN_MSG_OP_SHM_DUMP,
	RBLN_MSG_OP_LOG_CTRL,
	RBLN_MSG_OP_CDB_PROC_INFO_GET,
	RBLN_MSG_OP_PROC_CNT_GET,
	RBLN_MSG_OP_TRANSLATE_VA2PA,
	RBLN_MSG_OP_ABORT_EVENT,
	RBLN_MSG_OP_ABORT_GUILTY_CTX,
	RBLN_MSG_OP_DRV_VER_GET,		/* Not supported */
	RBLN_MSG_OP_LOAD_MCU_IMAGE,
	RBLN_MSG_OP_PWR,
	RBLN_MSG_OP_CLK,
	RBLN_MSG_OP_SMC_CTRL,
	RBLN_MSG_OP_PCIE_STAT_HISTO,
	RBLN_MSG_OP_POWER_MEASURE,
	/*
	 * Change HW_INFO to GDDR_INFO
	 * changelist from 10.0 -> 17.0
	 */
	RBLN_MSG_OP_GDDR_INFO,
	RBLN_MSG_OP_NVMEM_HW_CFG,
	RBLN_MSG_OP_BINNING_RESULT,
	RBLN_MSG_OP_CDB_ENABLE,
	RBLN_MSG_OP_PRODUCT_INFO,

	RBLN_MSG_OP_EXT_NUM,
	RBLN_MSG_OP_EXT_INVALID = RBLN_MSG_OP_EXT_NUM,
};
struct rbln_msg_packet_set {
	__le32 header;
	__le32 payload_in;
};

struct rbln_msg_packet_ib_ext {
	__le32 header;
	__le32 ib_cnt;
	__le64 ib_addr;
	__le64 data;
};

struct rbln_dump_info {
	__le64 size;
	__le64 addr;
};

/* Temperature */
enum temperature_device_t {
	TEMPERATURE_DEVICE_MIN,
	TEMPERATURE_DEVICE_CA53 = TEMPERATURE_DEVICE_MIN,
	TEMPERATURE_DEVICE_DNC0,
	TEMPERATURE_DEVICE_DNC1,
	TEMPERATURE_DEVICE_DNC2,
	TEMPERATURE_DEVICE_DNC3,
	TEMPERATURE_DEVICE_DNC4,
	TEMPERATURE_DEVICE_DNC5,
	TEMPERATURE_DEVICE_DNC6,
	TEMPERATURE_DEVICE_DNC7,
	TEMPERATURE_DEVICE_DRAM,
	TEMPERATURE_DEVICE_PCIE,
	TEMPERATURE_DEVICE_PVT,
	TEMPERATURE_DEVICE_SHM,

	TEMPERATURE_DEVICE_VIRTUAL_START,

	// The maximum value of all devices
	TEMPERATURE_DEVICE_PEAK = TEMPERATURE_DEVICE_VIRTUAL_START,
	// The average value of all devices
	TEMPERATURE_DEVICE_AVERAGE,
	// The average value x 10 of DNCs
	// 10 times an average value for the decimalization of temperature
	TEMPERATURE_DEVICE_DNC_AVERAGE_X10,
	// The average value x 10 of CA53, DRAM, PCIe and SHM
	TEMPERATURE_DEVICE_ETC_AVERAGE_X10,
	TEMPERATURE_DEVICE_MAX
};

struct rbln_pvt_temp_data {
	__le32 val[TEMPERATURE_DEVICE_MAX];
	__le32 raw[TEMPERATURE_DEVICE_MAX];
};

/*
 * PMIC
 */
enum rbln_pmic_ctrl_dev {
	RBLN_PMIC_GDR_VDDQ,
	RBLN_PMIC_GDR_CORE,
	RBLN_PMIC_GDRM_VDD,
	RBLN_PMIC_GDRM_CORE,
	RBLN_PMIC_GDR_PLL,
	RBLN_PMIC_DNC_CORE,
	RBLN_PMIC_DNC_MEM,
	RBLN_PMIC_DNC_PLL,
	RBLN_PMIC_CP_CORE,
	RBLN_PMIC_CP_MEM,
	RBLN_PMIC_CP_PLL,
	RBLN_PMIC_BUS_CORE,
	RBLN_PMIC_BUS_MEM,
	RBLN_PMIC_BUS_PLL,
	RBLN_PMIC_PCIEA,
	RBLN_PMIC_PCIE_CORE,
	RBLN_PMIC_GDR_VDDQ2,	/* Only available for TGB3 */
	RBLN_PMIC_DEV_MAX,

	RBLN_PMIC_DEV_ALL = RBLN_PMIC_DEV_MAX	/* for set/get all */
};

struct rbln_pmic_voltage_data {
	__le32 target;		/* use __le32 instead of enum rbln_pmic_ctrl_dev due to
				 * cross platform/compiler issue
				 */
	__le32 voltage;		/* unit: micro volage */
	__le32 current;		/* unit: mili Ampere current */
	__le32 power;		/* unit: mili Watt power */
};

struct rbln_pmic_read_data {
	__u8 val[2];
};

enum rbln_pmic_cmd {
	RBLN_PMIC_CMD_READ,
	RBLN_PMIC_CMD_GET,
	RBLN_PMIC_CMD_SET,
};

struct rbln_msg_packet_pmic {
	__le32 header;
	__le32 size;
	__le64 addr;
	__le32 cmd;			/* use __le32 instead of enum rbln_pmic_cmd */
	union {
		/* Get/Set */
		struct {
			__le32 target;	/* use __le32 instead of enum rbln_pmic_ctrbln_dev */
			__le32 voltage;
			__le32 current;	/* Get Only */
			__le32 power;	/* Get Only */
		};
		/* Read */
		struct {
			__le32 pmic_num;
			__le32 page;
			__le32 pmic_addr;
			__le32 bytes;
		};
	};
};

struct rbln_pwr_data {
	__le32 voltage;
	__le32 power;
	__le16 rail_data[6];
};

struct rbln_msg_packet_smc {
	__le32 header;
	__le32 size;
	__le64 addr;	/* address for data read from ATOM */
	__le32 cmd_type;
	__le32 param[3];
};

struct rbln_smc_read_data {
	__le32 data[8];
};

struct rbln_clk_data {
	__le32 cp;
	__le32 dcluster0;
	__le32 dcluster1;
	__le32 mainbus;
	__le32 shm;
};

/* PCIe Stat Histogram */
struct rbln_msg_packet_pcie_stat_histo {
	__le32 header;
	__le32 size;
	__le32 enable;
	__le32 max_histo_num;
	__le32 interval;
	__le32 ecnt_mask;
};

#define PCIE_STAT_HISTO_MAGIC_CODE  0x0C0FFEE0

/**
 * struct pcie_stat_ecnt_data_chunk
 *  @header
 *   [31:12]: Reserved
 *   [11:4]: Data size
 *   [3:0]: ECNT group number
 */
#define PCIE_STAT_HISTO_ITEM_HDR_SIZE           RL_GENMASK(11, 4)
#define PCIE_STAT_HISTO_ITEM_HDR_ECNT_GROUP     RL_GENMASK(3, 0)
struct pcie_stat_ecnt_data_chunk {
	__le32 header;
	__le32 data[];				/* ECNT data */
};

enum pcie_stat_temp {
	TEMP_PCIE,
	TEMP_CPU,
	TEMP_BUS,
	TEMP_DRAM,
	TEMP_DNC_AVG_X10,	/* DNCs' average temperature x 10 for precision */
	TEMP_PEAK,
	TEMP_AVG,
	TEMP_MAX_NUM
};

struct pcie_stat_histo_item {
	__le32 idx;
	__le32 timestamp;			/* From system counter 32Mhz */
	__le32 temp[TEMP_MAX_NUM];	/* Temperature */

	__s8 chunk[];				/* Data chunk */
};

struct pcie_stat_histo {
	__le32 magic;				/* Magic Key */
	__le32 size;				/* Total buf Size */
	__le32 used_size;			/* Used size of total buf size, 4 bytes align */

	__le32 max_histo_num;		/* Max number of PCIe stat histogram */
	__le32 item_size;			/* Size of each PCIe stat histogram item */
	__le32 cur_idx;				/* Current idx */
	__s8 buf[];					/* Buf for PCIe stat Histogram items */
};

#define PCIE_DTLOG_LTSSM_HISTO_MAGIC_CODE	0x0C0FFEE0
struct pcie_dtlog_ltssm_histo_item {
	__le32 timestamp;
	__le32 pcie_width;
	__le32 pcie_speed;
	__le32 dtlog_cnt;
	__le64 dtlog[];
};

struct pcie_dtlog_ltssm_histo_hdr {
	__le32 magic;
	__le32 chip_ver;
	__le32 max_item_num;
	__le32 item_cnt;
	__le32 data[];
};

enum rbln_nvmem_hw_cfg_cmd {
	NVMEM_HW_CFG_CMD_READ_CURR,		/* Current HW CFG configuration */
	NVMEM_HW_CFG_CMD_READ_FLASH,	/* Read raw HW CFG data from Flash */
	NVMEM_HW_CFG_CMD_WRITE_FLASH,	/* Write HW CFG to Flash*/
	NVMEM_HW_CFG_CMD_UPDATE_FLASH,	/* Update HW CFG to Flash */
	NVMEM_HW_CFG_CMD_ERASE_FLASH,	/* Erase HW CFG region at Flash */
};

#define NVMEM_HW_CFG_LPM_DISABLE_DCLUSTER		0x01
#define NVMEM_HW_CFG_LPM_DISABLE_PCIE_SPEED		0x02
#define NVMEM_HW_CFG_LPM_DISABLE_GDDR			0x04

#define NVMEM_HW_CFG_LPM_DISABLE_ALL	\
		(NVMEM_HW_CFG_LPM_DISABLE_DCLUSTER | \
		 NVMEM_HW_CFG_LPM_DISABLE_PCIE_SPEED | \
		 NVMEM_HW_CFG_LPM_DISABLE_GDDR)

#define NVMEM_HW_CFG_DISABLE_DEF	0xff

/**
 * struct rbln_msg_hw_cfg_data - for nvmem hw_cfg
 *
 * Do not change member variable position.
 * Add new member variable after the last member variable.
 */
struct rbln_msg_hw_cfg_data {
	__le32 magic_code;

	__le32 board_type;
	__le32 form_factor;
	__le32 overclk;
	__le32 pcie_width;
	__le32 pcie_speed;
	__le32 gddr6_data_rate;
	__le32 dnc_core_voltage;

	__le32 hc_disable;
	__le32 hc_disable_pcie_mnt;
	__le32 hc_temp_threshold;

	__le32 dcluster_clk;
	__le32 lpm_disable_mask;
};

struct rbln_msg_packet_nvmem_hw_cfg {
	__le32 header;
	__le32 size;
	__le64 addr;
	__le32 cmd;
	__s8 buf[];
};

/**
 * struct rbln_gddr_info - for GDDR information
 */

#ifndef HW_SPEC_GDDR_COUNT
#define HW_SPEC_GDDR_COUNT 4
#endif /* HW_SPEC_GDDR_COUNT */

struct rbln_gddr_info {
	/* because of alignment, have to check union size as even number*/
	union {
		__le32 dw[32];	/* 128-Byte */
		struct {
			__le32 gddr6_build_mem_type;
			__le32 gddr6_device_mem_type;
			__le32 gddr6_build_data_rate;
			__le32 gddr6_device_data_rate;
			__le32 gddr6_lp_mode;
			__le32 gddr6_lp_valid[HW_SPEC_GDDR_COUNT];
			__le32 gddr6_lp_state[HW_SPEC_GDDR_COUNT];
			__le32 gddr6_max_crc_count[HW_SPEC_GDDR_COUNT];
			__le32 reserved[15];
		};
	};
};

struct __attribute__ ((__packed__)) product_info_tx_data_v1_t {
	struct __attribute__ ((__packed__)) {
		__le32 magic_code;
		__le16 tx_data_version;
		__le16 total_index_cnt;
		__le16 valid_uuid_cnt;
		__u8 product_name[9];
		__u8 reserved_0[3];
	} index_0;	/* 22 bytes */
	struct __attribute__ ((__packed__)) {
		__u8 card_serial_num[8];
		__u8 board_type[2];
		__u8 reserved_1[2];
		__u8 board_revision[2];
		__u8 reserved_2[8];
	} index_1;	/* 22 bytes */
	struct __attribute__ ((__packed__)) {
		__u8 pcb_lot_num[22];
	} index_2;	/* 22 bytes */
	struct __attribute__ ((__packed__)) {
		__u8 smt_lot_num[22];
	} index_3;	/* 22 bytes */
	struct __attribute__ ((__packed__)) {
		__u8 card_part_num[18];
		__u8 prefix_header[4];
	} index_4;	/* 22 bytes */
};

#endif /* QMAN_IF_H */
