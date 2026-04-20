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

#define PAGE0_REG				0x0
#define PAGE1_REG				0x1
#define PAGE2_REG				0x2
#define PAGE3_REG				0x3
#define PAGE4_REG				0x4

#define OP_HIGH_Z_OFF			0
#define OP_SOFT_OFF				(BIT(6))
#define OP_NORMAL_ON			(BIT(7))
#define OP_MARGIN_LOW			(BIT(7)) | (BIT(4))
#define OP_MARGIN_HIGH			(BIT(7)) | (BIT(5))
#define OP_AVSBUS_MODE			(BIT(7)) | (BIT(4)) | (BIT(5))
#define OP_UNUSED				(BIT(7)) | (BIT(6))

#define CONF_TURN_OFF_MODE		0
#define CONF_NO_DELAY			(BIT(CONF_TURN_OFF_MODE))
#define CONF_HAVE_DELAY			(0 << CONF_TURN_OFF_MODE)
#define CONF_EN_POLARITY		1
#define CONF_ACTIVE_HIGH		(BIT(CONF_EN_POLARITY))
#define CONF_ACTIVE_LOW			(0 << CONF_EN_POLARITY)
#define CONF_PIN_ON_EN			2
#define CONF_IGNORE_CTRL_PIN	(0 << CONF_PIN_ON_EN)
#define CONF_REQUIRE_CTRL_PIN	(BIT(CONF_PIN_ON_EN))
#define CONF_CMD_ON_EN			3
#define CONF_IGNORE_CMD			(0 << CONF_CMD_ON_EN)
#define CONF_REQUIRE_CMD		(BIT(CONF_CMD_ON_EN))
#define CONF_DEBUG_ON_EN		4
#define CONF_DEBUG_USE			(0 << CONF_DEBUG_ON_EN)
#define CONF_DEBUG_NOT_USE		(BIT(CONF_DEBUG_ON_EN))

#define PHASE_NUM				0
#define PHASE_NUM_16			(0xF << PHASE_NUM)
#define PHASE_NUM_2				(BIT(PHASE_NUM))
#define PHASE_FORCE_NUM			8
#define PHASE_FORCE_16			(0x10 << PHASE_FORCE_NUM)
#define PHASE_FORCE_2			(0x2 << PHASE_FORCE_NUM)

#define VOUT_MODE_DIRECT		0x40
#define VOUT_MODE_VID			0x20

#define MFR_VID_RES				10
#define MFR_VID_LSB_1MV			(0x4 << MFR_VID_RES)

#define PAGE					0x0
#define OPERATION				0x1
#define ON_OFF_CONFIG			0x2
#define CLEAR_FAULTS			0x3
#define PHASE					0x4
#define STORE_USER_ALL			0x15
#define RESTORE_USER_ALL		0x16
#define STORE_USER_CODE			0x17
#define RESTORE_USER_CODE		0x18
#define VOUT_MODE				0x20
#define VOUT_COMMAND			0x21
#define MFR_VOUT_SCALE_LOOP		0x29
#define STATUS_BYTE				0x78
#define STATUS_WORD				0x79
#define READ_VOUT_PMBUS			0x8B
#define MP29816A_VID			5

int mp29816a_set_page(uint16_t target_address, uint8_t value);
int mp29816a_get_page(uint16_t target_address);
int mp29816a_set_operation_page(uint16_t target_address, uint8_t value);
int mp29816a_set_on_off_config_page(uint16_t target_address, uint8_t value);
int mp29816a_clear_fault(uint16_t target_address);
int mp29816a_set_phase(uint16_t target_address, uint32_t value);
int mp29816a_store_user_all(uint16_t target_address);
int mp29816a_restore_user_all(uint16_t target_address);
int mp29816a_store_user_code(uint16_t target_address);
int mp29816a_restore_user_code(uint16_t target_address);
int mp29816a_set_vout_mode(uint16_t target_address, uint8_t value);
int mp29816a_set_vout_command(uint16_t target_address, uint32_t value);
int mp29816a_mfr_vout_droop(uint16_t target_address, uint32_t value);
int mp29816a_read_byte_page(uint16_t target_address);
int mp29816a_read_word_page(uint16_t target_address);
int mp29816a_read_vout_pmbus(uint16_t target_address);

int mp29816a_enable_rail1(uint16_t target_address, uint32_t vout);
int mp29816a_disable_rail1(uint16_t target_address);
int mp29816a_enable_rail1_rail2(uint16_t target_address, uint32_t vout);
int mp29816a_disable_rail1_rail2(uint16_t target_address);

int mp29816a_set_vout(uint16_t target_address, uint32_t vout);
int mp29816a_get_vout(uint16_t target_address);

