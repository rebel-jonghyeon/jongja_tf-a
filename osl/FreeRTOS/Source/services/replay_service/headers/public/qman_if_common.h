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

#ifndef QMAN_IF_COMMON_H
#define QMAN_IF_COMMON_H

#ifndef __stringify
#ifndef	__stringify_1
#define __stringify_1(x...)	#x
#endif	/* __stringify_1 */
#define __stringify(x...)	__stringify_1(x)
#endif	/* __stringify */

#define QMAN_IF_COMMON_MAJOR_VER	7
#define QMAN_IF_COMMON_MINOR_VER	1
#define QMAN_IF_COMMON_VER		__stringify(QMAN_IF_COMMON_MAJOR_VER) "."\
					__stringify(QMAN_IF_COMMON_MINOR_VER)

#ifdef __REBEL_FW__
#include <stdint.h>
#include "rl_utils.h"

typedef uint16_t	__le16;
typedef uint32_t	__le32;
typedef uint64_t	__le64;

typedef uint8_t		__u8;
typedef int8_t		__s8;
#else
#include <linux/types.h>
#endif /* __REBEL_FW__ */

/*
 * PRIMARY QUEUE
 */

struct rbln_bd {
	__le32 header;
	__le32 size;
	__le64 addr;
	__le64 cb_jd_addr;
};

struct rbln_host_sync {
	__le64 d2h_sync_lo;
	__le64 d2h_sync_hi;
	__le32 cb_handle;
};

#define RBLN_MAX_HANDLE_CNT			1024

#define RBLN_BD_SIZE				sizeof(struct rbln_bd)

#define BD_FLAGS_DONE_SHIFT			31
#define BD_FLAGS_DONE_MASK			0x80000000
#define BD_FLAGS_IRQ_SHIFT			30
#define BD_FLAGS_IRQ_MASK			0x40000000
#define BD_FLAGS_CS_SHIFT			29		/* context submission */
#define BD_FLAGS_CS_MASK			0x20000000
#define BD_FLAGS_ACTIVE_SHIFT			28		/* binding new asid */
#define BD_FLAGS_ACTIVE_MASK			0x10000000
#define BD_FLAGS_REUSED_SHIFT			27		/* reuse command buffer */
#define BD_FLAGS_REUSED_MASK			0x08000000
#define BD_FLAGS_PTID_SHIFT			16
#define BD_FLAGS_PTID_MASK			0x00ff0000
#define BD_FLAGS_ERROR_SHIFT			16
#define BD_FLAGS_ERROR_MASK			0x00ff0000
#define BD_FLAGS_ASID_SHIFT			8
#define BD_FLAGS_ASID_MASK			0x0000ff00
#define BD_FLAGS_HTID_SHIFT			0
#define BD_FLAGS_HTID_MASK			0x000000ff

#define BD_HEADER_GET_IRQ(h)			(((h) & BD_FLAGS_IRQ_MASK) >> BD_FLAGS_IRQ_SHIFT)
#define BD_HEADER_GET_CS(h)			(((h) & BD_FLAGS_CS_MASK) >> BD_FLAGS_CS_SHIFT)
#define BD_HEADER_GET_ACTIVE(h)			\
	(((h) & BD_FLAGS_ACTIVE_MASK) >> BD_FLAGS_ACTIVE_SHIFT)
#define BD_HEADER_GET_REUSED(h)			\
	(((h) & BD_FLAGS_REUSED_MASK) >> BD_FLAGS_REUSED_SHIFT)
#define BD_HEADER_GET_PTID(h)			(((h) & BD_FLAGS_PTID_MASK) >> BD_FLAGS_PTID_SHIFT)
#define BD_HEADER_GET_ERROR(h)			(((h) & BD_FLAGS_ERROR_MASK) >> BD_FLAGS_ERROR_SHIFT)
#define BD_HEADER_GET_ASID(h)			(((h) & BD_FLAGS_ASID_MASK) >> BD_FLAGS_ASID_SHIFT)
#define BD_HEADER_GET_HTID(h)			(((h) & BD_FLAGS_HTID_MASK) >> BD_FLAGS_HTID_SHIFT)

#define BD_HEADER_SET_PTID(v)			(((v) << BD_FLAGS_PTID_SHIFT) & BD_FLAGS_PTID_MASK)

#define CP_PACKET_SHIFT_OPCODE			24
#define CP_PACKET_SHIFT_COUNT			20
#define CP_PACKET_SHIFT_VIRTUAL			19
#define CP_PACKET_SHIFT_EXTENSION		18
#define CP_PACKET_MASK_COUNT			((0xFu) << CP_PACKET_SHIFT_COUNT)
#define CP_PACKET_MASK_EXTENSION		((0x1u) << CP_PACKET_SHIFT_EXTENSION)
#define CP_PACKET_MASK_USER_SPECIFIED		(CP_PACKET_MASK_EXTENSION)
#define CP_PACKET_GET_OPCODE(h)			(((h) >> CP_PACKET_SHIFT_OPCODE) & 0xFFu)
#define CP_PACKET_GET_COUNT(h)			(((h) >> CP_PACKET_SHIFT_COUNT) & 0xFu)
#define CP_PACKET_GET_VIRTUAL(h)		(((h) >> CP_PACKET_SHIFT_VIRTUAL) & 0x1u)
#define CP_PACKET_GET_EXTENSION(h)		(((h) >> CP_PACKET_SHIFT_EXTENSION) & 0x1u)

#define PACKET(op, n, v, e)			((((op) & 0xFFu) << CP_PACKET_SHIFT_OPCODE) |	\
						 (((n) & 0xFu) << CP_PACKET_SHIFT_COUNT) |	\
						 ((v) ? 0x1u << CP_PACKET_SHIFT_VIRTUAL : 0) |	\
						 ((e) ? 0x1u << CP_PACKET_SHIFT_EXTENSION : 0))
#define PAYLOAD_SIZE_DWORD(pkt)			\
	((__u32)((sizeof(*(pkt)) - sizeof((pkt)->header)) >> 2))

#define CP_DMA_PACKET_SHIFT_SINGLE		4
#define CP_DMA_PACKET_SHIFT_DMA_DIR		2
#define CP_DMA_PACKET_SHIFT_CP_SYNC		1
#define CP_DMA_PACKET_SHIFT_EXCLUSIVE		0
#define CP_DMA_PACKET_MASK_SINGLE		((0x1u) << CP_DMA_PACKET_SHIFT_SINGLE)
#define CP_DMA_PACKET_MASK_DMA_DIR		((0x3u) << CP_DMA_PACKET_SHIFT_DMA_DIR)
#define CP_DMA_PACKET_MASK_CP_SYNC		((0x1u) << CP_DMA_PACKET_SHIFT_CP_SYNC)
#define CP_DMA_PACKET_MASK_EXCLUSIVE		((0x1u) << CP_DMA_PACKET_SHIFT_EXCLUSIVE)
#define CP_DMA_PACKET_MASK_USER_SPECIFIED	(CP_DMA_PACKET_MASK_SINGLE	| \
						 CP_DMA_PACKET_MASK_CP_SYNC	| \
						 CP_DMA_PACKET_MASK_EXCLUSIVE)
#define CP_DMA_PACKET_GET_SINGLE(h)	\
	(((h) >> CP_DMA_PACKET_SHIFT_SINGLE) & 0x1u)
#define CP_DMA_PACKET_GET_DMA_DIR(h)		(((h) >> CP_DMA_PACKET_SHIFT_DMA_DIR) & 0x3u)
#define CP_DMA_PACKET_GET_CP_SYNC(h)		(((h) >> CP_DMA_PACKET_SHIFT_CP_SYNC) & 0x1u)
#define CP_DMA_PACKET_GET_EXCLUSIVE(h)		(((h) >> CP_DMA_PACKET_SHIFT_EXCLUSIVE) & 0x1u)

enum packet_dma_direction {
	PACKET_DMA_DIR_UNKNOWN,
	PACKET_DMA_HOST_TO_DEVICE,
	PACKET_DMA_DEVICE_TO_HOST,
	PACKET_DMA_DEVICE_TO_DEVICE,
	PACKET_DMA_DIR_NUM,
	PACKET_DMA_DIR_INVALID = PACKET_DMA_DIR_NUM,
};

enum packet_id {
	PACKET_NOP = 0x0,
	PACKET_WRITE_DATA = 0x1,
	PACKET_CTX_DMA = 0x2,
	PACKET_LINKED_DMA = 0x3,
	PACKET_FLUSH = 0x4,
	NUM_PACKET_ID,
	MAX_PACKET_ID = 0xfe,
	INVALID_PACKET_ID,
};

struct packet_write_data {
	__le32 header;
	__le32 value;
	__le64 addr;
};

struct packet_ctx_dma {
	__le32 header;
	__le32 size;
	__le32 src_ctx;
	__le32 src_task;
	__le64 src_addr;
	__le32 dst_ctx;
	__le32 dst_task;
	__le64 dst_addr;
};

struct packet_linked_dma {
	__le32 header;
	__le32 size;
	__le64 addr;
};

struct packet_flush {
	__le32 header;
	__le32 size;
	__le64 addr;
};

#ifndef	BIT
#define __QMAN_STR_CONCAT(X, Y)	(X##Y)
#define __QMAN_UL(v)		(__QMAN_STR_CONCAT(v, UL))
#define BIT(nr)			(__QMAN_UL(1) << (nr))
#endif	/* BIT */

enum dw_hdma_control {
	DW_HDMA_V0_CB		= BIT(0),
	DW_HDMA_V0_TCB		= BIT(1),
	DW_HDMA_V0_LLP		= BIT(2),
	DW_HDMA_V0_LIE		= BIT(3),
	DW_HDMA_V0_RIE		= BIT(4),
	DW_HDMA_V0_CCS		= BIT(8),
	DW_HDMA_V0_LLE		= BIT(9),
};

#ifdef __KERNEL__
#define __QMAN_PAKCED	__packed
#else	/* ifndef __KERNEL__ */
#define __QMAN_PAKCED	__attribute__((packed))
#endif	/* __KERNEL__ */

struct dw_hdma_v0_lli {
	__le32 control;
	__le32 transfer_size;
	union {
		__le64 reg;
		struct {
			__le32 lsb;
			__le32 msb;
		};
	} sar;
	union {
		__le64 reg;
		struct {
			__le32 lsb;
			__le32 msb;
		};
	} dar;
} __QMAN_PAKCED;

struct dw_hdma_v0_llp {
	__le32 control;
	__le32 reserved;
	union {
		__le64 reg;
		struct {
			__le32 lsb;
			__le32 msb;
		};
	} llp;
} __QMAN_PAKCED;

#undef __QMAN_PAKCED

#ifndef GENMASK
#ifndef RBLN_GENMASK
#ifndef RBLN_BITS_PER_LONG
#define RBLN_BITS_PER_LONG			32
#endif	/* RBLN_BITS_PER_LONG */
#define RBLN_GENMASK(h, l)			\
	((0xFFFFFFFF << (l)) & (0xFFFFFFFF >> (RBLN_BITS_PER_LONG - 1 - (h))))
#endif	/* RBLN_GENMASK */
#define GENMASK(h, l)				RBLN_GENMASK(h, l)
#endif	/* GENMASK */

#ifndef GENMASK_ULL
#ifndef RBLN_GENMASK64
#ifndef RBLN_BITS_PER_LONG_LONG
#define RBLN_BITS_PER_LONG_LONG			64
#endif	/* RBLN_BITS_PER_LONG_LONG */
#define RBLN_GENMASK64(h, l)			\
	((0xFFFFFFFFFFFFFFFFull << (l)) &	\
	 (0xFFFFFFFFFFFFFFFFull >> (RBLN_BITS_PER_LONG_LONG - 1 - (h))))
#endif	/* RBLN_GENMASK64 */
#define GENMASK_ULL(h, l)			RBLN_GENMASK64(h, l)
#endif	/* GENMASK_ULL */

/* message ring */
#define RBLN_MSG_HDR_RC_SHIFT			28
#define RBLN_MSG_HDR_RC_MASK			GENMASK(31, 28)
#define RBLN_MSG_HDR_RC_GET(h)			\
	(((h) & RBLN_MSG_HDR_RC_MASK) >> RBLN_MSG_HDR_RC_SHIFT)
#define RBLN_MSG_HDR_RC_SET(rc)			\
	(((rc) << RBLN_MSG_HDR_RC_SHIFT) & RBLN_MSG_HDR_RC_MASK)

#define RBLN_MSG_HDR_COUNT_SHIFT		15
#define RBLN_MSG_HDR_COUNT_MASK			GENMASK(27, 15)
#define RBLN_MSG_HDR_COUNT_GET(h)		(((h) & RBLN_MSG_HDR_COUNT_MASK) >> \
						 RBLN_MSG_HDR_COUNT_SHIFT)
#define RBLN_MSG_HDR_COUNT_SET(c)		(((c) << RBLN_MSG_HDR_COUNT_SHIFT) & \
						 RBLN_MSG_HDR_COUNT_MASK)

#define RBLN_MSG_HDR_IB_SHIFT			14
#define RBLN_MSG_HDR_IB_SET()			(1 << RBLN_MSG_HDR_IB_SHIFT)
#define RBLN_MSG_HDR_IB_CHK(h)			((h) & (1 << RBLN_MSG_HDR_IB_SHIFT))

#define RBLN_MSG_HDR_OPCODE_SHIFT		0
#define RBLN_MSG_HDR_OPCODE_MASK		GENMASK(9, 0)
#define RBLN_MSG_HDR_OPCODE_GET(h)		(((h) & RBLN_MSG_HDR_OPCODE_MASK) >> \
						 RBLN_MSG_HDR_OPCODE_SHIFT)
#define RBLN_MSG_HDR_OPCODE_SET(c)		(((c) << RBLN_MSG_HDR_OPCODE_SHIFT) & \
						 RBLN_MSG_HDR_OPCODE_MASK)

#define RBLN_MSG_HDR(op, c)			(RBLN_MSG_HDR_OPCODE_SET(op) | \
						 RBLN_MSG_HDR_COUNT_SET(c))

#define RBLN_MSG_PAYLOAD_OFF_DW			1

enum rbln_msg_packet_rc {
	RBLN_MSG_RC_SUCCESS = 1,
	RBLN_MSG_RC_ERROR,
	RBLN_MSG_RC_FULL,
	RBLN_MSG_RC_NOT_SUPPORT,
	RBLN_MSG_RC_INVALID,
	RBLN_MSG_RC_VERSION_MISMATCH,
	RBLN_MSG_RC_TIMEOUT,
	RBLN_MSG_RC_NOT_FOUND,
	RBLN_MSG_RC_PAGE_FAULT,
};

#define RBLN_MSG_OP_RESERVED_NUM	20
enum rbln_msg_packet_op {
	RBLN_MSG_OP_NOP = 0,
	RBLN_MSG_OP_SEND_TDR,
	RBLN_MSG_OP_RESERVED_2,
	RBLN_MSG_OP_RESERVED_3,
	RBLN_MSG_OP_TEST_IB,		/* indirect buffer is used */
	RBLN_MSG_OP_DRV_VER,		/* Not supported */
	RBLN_MSG_OP_LOAD_IMAGE,		/* load image is used */
	RBLN_MSG_OP_HOST_SYNC,          /* host sync is used */
	RBLN_MSG_OP_LOAD_MCU_IMAGE_2,	/* load_image for smc fw */

	/*
	 * IMPORTANT
	 * : The ID of last opcode should be less than RBLN_MSG_OP_RESERVED_NUM. If the ID of a new
	 *   opcode needs to equal to or greater than RBLN_MSG_OP_RESERVED_NUM, a new mechanism is
	 *   needed to add the new opcode.
	 */
	RBLN_MSG_OP_NUM = RBLN_MSG_OP_RESERVED_NUM,
	RBLN_MSG_OP_INVALID = RBLN_MSG_OP_NUM
};

struct rbln_msg_packet_ib {
	__le32 header;
	__le32 ib_cnt;
	__le64 ib_addr;
};

struct rbln_msg_packet_drv_ver {
	__le32 header;
	__le32 major;
	__le32 minor;
	__le32 patchlevel;
	__le32 git_sha;
};

struct rbln_msg_packet_load_image {
	__le32 header;
	__le32 timeout_us;
	__le32 size;
	__le64 addr;
};

struct rbln_msg_packet_host_sync {
	__le32 header;
	__le32 ptid;
	__le32 cb_handle;
	__le32 sync_id;
	__le64 cb_jd_addr;
};

#endif /* QMAN_IF_COMMON_H */
