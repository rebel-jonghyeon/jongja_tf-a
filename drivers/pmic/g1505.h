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

#define	PAGE			0x0
#define	OPERATION		0x1
#define ON_OFF_CONFIG	0x2
#define CLEAR_FAULT		0x3
#define VOUT_MODE		0x20
#define VOUT_COMMAND	0x21
#define STATUS_WORD		0x79
#define STATUS_VOUT		0x7A
#define STATUS_IOUT		0x7B

int g1505_set_page(uint16_t target_address, uint8_t value);
int g1505_get_page(uint16_t target_address);
int g1505_set_operation(uint16_t target_address, uint8_t value);
int g1505_set_on_off_config(uint16_t target_address, uint8_t value);
int g1505_get_on_off_config(uint16_t target_address);
int g1505_clear_fault(uint16_t target_address);
int g1505_set_vout_command(uint16_t target_address, uint32_t vout);
int g1505_get_vout_command(uint16_t target_address);
int g1505_get_status_word(uint16_t target_address);
int g1505_get_status_vout(uint16_t target_address);
int g1505_get_status_iout(uint16_t target_address);
