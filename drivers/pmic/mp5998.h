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

#define MOSFET_ENABLE			(BIT(7))
#define MOSFET_DISABLE			(0 << 7)
#define OPERATION				0x1
#define CLEAR_FAULT				0x3
#define STORE_ALL				0x15
#define RESTORE_ALL				0x16
#define VIN_ON					0x35
#define VIN_OFF					0x36
#define POWER_GOOD_ON			0x5E
#define POWER_GOOD_OFF			0x5F
#define TON_DELAY				0x60
#define TOFF_DELAY				0x64
#define STATUS_BYTE				0x78
#define STATUS_WORD				0x79
#define STATUS_CML				0x7E
#define READ_VOUT				0x8B
#define READ_IOUT				0x8C

int mp5998_set_enable(uint16_t target_address);
int mp5998_set_disable(uint16_t target_address);
int mp5998_clear_fault(uint16_t target_address);
int mp5998_store_all(uint16_t target_address);
int mp5998_restore_all(uint16_t target_address);
int mp5998_set_vin_on(uint16_t target_address, float vin);
int mp5998_set_vin_off(uint16_t target_address, float vin);
int mp5998_set_power_good_on(uint16_t target_address, float pg_v);
int mp5998_set_power_good_off(uint16_t target_address, float pg_v);
int mp5998_set_ton_delay(uint16_t target_address, float delay);
int mp5998_set_toff_delay(uint16_t target_address, float delay);
int mp5998_read_status_byte(uint16_t target_address);
int mp5998_read_status_word(uint16_t target_address);
float mp5998_read_vout(uint16_t target_address);
float mp5998_read_iout(uint16_t target_address);
