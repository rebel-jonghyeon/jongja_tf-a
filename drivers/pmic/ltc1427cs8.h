/*
 * Copyright 2025 Samsung Electronics Co, Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */

#include <stdint.h>

#define SHDN_BIT			(BIT(7))
#define VREF_FLOAT			800.0f
#define DAC_MAX_FLOAT		1023.0f
#define IOUT_MAX			50.0f
#define IOUT_MIN			0.0f
#define DAC_LOW_MASK		0xFF
#define DAC_HIGH_MASK		0x3
#define DAC_SHIFT_HIGH		8

struct ltc_config {
	uint8_t mux_channel;
	uint8_t ltc_addr;
	float r1_ohm;
	float r2_ohm;
	uint8_t last_cmd_value;
	uint8_t last_data_value;
};

int ltc1427_set_vout(uint32_t index, uint32_t target_vout);
int ltc1427_enable(uint32_t index);
int ltc1427_disable(uint32_t index);
