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

/* IDE Data Object Defines */
#define PROTO_ID_FROM_DW(x) ((x) & 0xFF)
#define OBJ_ID_FROM_DW(x) (((x) & 0xFF00) >> 8)
#define PROTOCOL_ID_IDE (0x0)

/* IDE Object ID */
enum ide_obj_id {
	ID_QUERY = 0,
	ID_QUERY_RESP = 1,
	ID_KEY_PROG = 2,
	ID_KP_ACK = 3,
	ID_K_SET_GO = 4,
	ID_K_SET_STOP = 5,
	ID_K_GOSTOP_ACK = 6
};

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
