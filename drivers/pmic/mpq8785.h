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

#define PAGE_OPERATE_MODE			(0 << PAGE)
#define PAGE_TEST_MODE				(BIT(PAGE))

#define OP_MARGIN_FAULT_RESPONSE	2
#define OP_MARGIN_FAULT_IGNORE		(BIT(OP_MARGIN_FAULT_RESPONSE))
#define OP_MARGIN_FAULT_TRIGGER		(2 << OP_MARGIN_FAULT_RESPONSE)
#define OP_VOLT_CMD_SOURCE			4
#define OP_VOUT_CMD_DATA		(0 << OP_VOLT_CMD_SOURCE)
#define OP_VOUT_MARGIN_LOW_DATA		(BIT(OP_VOLT_CMD_SOURCE))
#define OP_VOUT_MARGIN_HIGH_DATA	(2 << OP_VOLT_CMD_SOURCE)
#define OP_NOT_SUPPORTED			(3 << OP_VOLT_CMD_SOURCE)
#define OP_TURN_OFF_BEHAVIOR		6
#define OP_HIGH_IMPEDANCE_OFF		(0 << OP_TURN_OFF_BEHAVIOR)
#define OP_SOFT_SHUTDOWN			(BIT(OP_TURN_OFF_BEHAVIOR))
#define OP_ON_OFF_STATE				7
#define OP_OUTPUT_OFF				(0 << OP_ON_OFF_STATE)
#define OP_OUTPUT_ON				(BIT(OP_ON_OFF_STATE))

#define CONF_CTRL_OFF_ACTION		0
#define CONF_TURN_OFF_CONFIGURED	(0 << CONF_CTRL_OFF_ACTION)
#define CONF_TURN_OFF_QUICKLY		(BIT(CONF_CTRL_OFF_ACTION))
#define CONF_CTRL_POLARITY			1
#define CONF_CTRL_ACTIVE_LOW		(0 << CONF_CTRL_POLARITY)
#define CONF_CTRL_ACTIVE_HIGH		(BIT(CONF_CTRL_POLARITY))
#define CONF_BEHAVIOR				2
#define CONF_TURN_ON_BIAS_POWER		(BIT(CONF_BEHAVIOR)
#define CONF_TURN_ON_BUS			(4 << CONF_BEHAVIOR)
#define CONF_TURN_ON_PIN			(5 << CONF_BEHAVIOR)
#define CONF_TURN_ON_BUS_PIN		(7 << CONF_BEHAVIOR)

#define VOUT_MODE_PARA				0
#define VOUT_MODE_PARA_VID_DIR		(0 << VOUT_MODE_PARA)
#define VOUT_MODE_PARA_LINEAR		(0x17 << VOUT_MODE_PARA)
#define VOUT_MODE_SEL				5
#define VOUT_MODE_SEL_LINEAR		(0 << VOUT_MODE_SEL)
#define VOUT_MODE_SEL_VID			(BIT(VOUT_MODE_SEL))
#define VOUT_MODE_SEL_DIRECT		(2 << VOUT_MODE_SEL)
#define VOUT_MODE_SEL_MASK			(3 << VOUT_MODE_SEL)

#define PAGE					0x0
#define OPERATION				0x1
#define ON_OFF_CONFIG			0x2
#define CLEAR_FAULT				0x3
#define STORE_ALL				0x15
#define RESTORE_ALL				0x16
#define VOUT_MODE				0x20
#define VOUT_COMMAND			0x21
#define VIN_ON					0x35
#define VIN_OFF					0x36
#define STATUS_WORD				0x79
#define STATUS_VOUT				0x7A
#define READ_VOUT				0x8B

int mpq8785_set_page(uint16_t target_address, uint8_t value);
int mpq8785_set_operation(uint16_t target_address, uint8_t value);
int mpq8785_set_on_off_config(uint16_t target_address, uint8_t value);
int mpq8785_clear_fault(uint16_t target_address);
int mpq8785_store_all(uint16_t target_address);
int mpq8785_restore_all(uint16_t target_address);
int mpq8785_set_vout_mode(uint16_t target_address, uint8_t value);
int mpq8785_read_vout_mode(uint16_t target_address);
int mpq8785_read_vout(uint16_t target_address);
int mpq8785_set_vout_command(uint16_t target_address, uint32_t vout);
int mpq8785_set_vin_on(uint16_t target_address, uint8_t vin);
int mpq8785_set_vin_off(uint16_t target_address, uint8_t vin);
int mpq8785_read_word(uint16_t target_address);
int mpq8785_read_status_vout(uint16_t target_address);
int mpq8785_enable(uint16_t target_address, uint32_t vout);
int mpq8785_disable(uint16_t target_address);
int mpq8785_set_vout(uint16_t target_address, uint32_t vout);
int mpq8785_get_vout(uint16_t target_address);
