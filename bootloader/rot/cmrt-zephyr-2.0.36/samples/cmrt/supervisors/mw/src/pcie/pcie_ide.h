/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

/* PCIE_IDE_AES Base Address */
#define PCIE_IDE_AES_TX_BASE (0x1ff0520000UL)
#define PCIE_IDE_AES_RX_BASE (0x1ff0520800UL)

/* PCIE_IDE_AES Register */
#define AES_CORE_VER_NUM (0x0)
#define AES_CORE_VER_TYPE (0x4)
#define AES_IRQ_EN (0x8)
#define AES_IRQ_STAT (0xc)
#define AES_CTRL	(0x14)
#define AES_STAT	(0x18)
#define AES_KEY_0	(0x20)
#define AES_KEY_1	(0x24)
#define AES_KEY_2	(0x28)
#define AES_KEY_3	(0x2C)
#define AES_KEY_4	(0x30)
#define AES_KEY_5	(0x34)
#define AES_KEY_6	(0x38)
#define AES_KEY_7	(0x3C)
#define AES_INITIAL_IV_LSW	(0x40)
#define AES_INITIAL_IV_MSW	(0x44)
#define AES_LINK_DISABLE_STREAM_KEYS	(0x1c0)
#define AES_SELECTIVE_DISABLE_STREAM_KEYS	(0x1c4)
#define AES_SELECTIVE_DISABLE_STREAM_KEYS_2	(0x1c8)

/* AES_CTRL Register */
#define AES_CTRL_CTX_IDX_MASK (0xFFFF)

/* KEY DW size */
#define KEY_DW_SIZE (0x8)
#define IFV_DW_SIZE (0x2)

/* PCIe Subctrl Register */
#define SFR_SMLH_LTSSM_STATE (0x1ff8180320ULL)
#define LTSSM_STATE_MASK (0x3F)
#define LTSSM_STATE_L0 (0x11)

/* AES Key Index */
#define INITIAL_SLS_PR_IDX (0)
#define INITIAL_SLS_NPR_IDX (1)
#define INITIAL_SLS_CPL_IDX (2)
#define INITIAL_LS_PR_IDX (3)
#define INITIAL_LS_NPR_IDX (4)
#define INITIAL_LS_CPL_IDX (5)
#define BACKUP_OFFSET_IDX (6)

/* IDE Data Object Defines */
#define OBJ_ID_FROM_DW(x) (((x) & 0xFF00) >> 8)

/* Stream ID : This value is for test */
#define STREAM_ID (1)

/* IDE Data Object */
#define PROTOCOL_ID_IDE (0x0)
#define RXTXB_TX (0x1)
#define RXTXB_RX (0x0)
#define KEY_SET_0 (0x0)
#define KEY_SET_1 (0x1)
#define SUB_STREAM_0 (0x0)
#define SUB_STREAM_1 (0x1)
#define SUB_STREAM_2 (0x2)

enum ide_obj_id {
	ID_QUERY = 0,
	ID_QUERY_RESP = 1,
	ID_KEY_PROG = 2,
	ID_KP_ACK = 3,
	ID_K_SET_GO = 4,
	ID_K_SET_STOP = 5,
	ID_K_GOSTOP_ACK = 6
};

#define KEY_PROG(sid, kset, dir, ss, port,							\
				 key7, key6, key5, key4, key3, key2, key1, key0,	\
				 ifv1, ifv0)										\
	{																\
		.header.object_id = ID_KEY_PROG,		\
		.header.protocol_id = PROTOCOL_ID_IDE,	\
		.header.portindex = port,				\
		.header.sub_stream = ss,				\
		.header.rxtx = dir,						\
		.header.key_set = kset,					\
		.header.stream_id = sid,				\
		.key_dw7 = key7,				\
		.key_dw6 = key6,				\
		.key_dw5 = key5,				\
		.key_dw4 = key4,				\
		.key_dw3 = key3,				\
		.key_dw2 = key2,				\
		.key_dw1 = key1,				\
		.key_dw0 = key0,				\
		.ifv_dw1 = ifv1,				\
		.ifv_dw0 = ifv0,				\
	}

struct ide_km_data_object {
	union {
		struct {
			uint32_t protocol_id:8; /* [7:0] */
			uint32_t object_id:8; /* [15:8] */
			uint32_t reserved_0:16; /* [31:16] */
		};
		uint32_t header0;
	};
	union {
		struct {
			uint32_t stream_id:8; /* [7:0] */
			uint32_t reserved_1:8; /* [15:8] */
			uint32_t key_set:1; /* [16:16] */
			uint32_t rxtx:1; /* [17:17] */
			uint32_t reserved_2:2; /* [19:18] */
			uint32_t sub_stream:4; /* [23:20] */
			uint32_t portindex:8; /* [24:31] */
		};
		uint32_t header1;
	};
};

struct key_prog_data_object {
	struct ide_km_data_object header;
	union {
		struct {
			uint32_t key_dw7;
			uint32_t key_dw6;
			uint32_t key_dw5;
			uint32_t key_dw4;
			uint32_t key_dw3;
			uint32_t key_dw2;
			uint32_t key_dw1;
			uint32_t key_dw0;
		};
		uint32_t key_dw[8];
	};
	union {
		struct {
			uint32_t ifv_dw1;
			uint32_t ifv_dw0;
		};
		uint32_t ifv_dw[2];
	};
};
