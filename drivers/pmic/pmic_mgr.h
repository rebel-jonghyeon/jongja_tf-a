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

#pragma once

int i2c_write_int_o_d(uint32_t id, uint16_t device, uint32_t offset, uint8_t *data, uint8_t len);
int i2c_read_int_o_d(uint32_t id, uint16_t device, uint32_t offset, uint8_t *data, uint8_t len);
int i2c_write_polling_o_d(uint32_t id, uint16_t device, uint32_t offset, uint8_t *data,
						  uint8_t len);
int i2c_read_polling_o_d(uint32_t id, uint16_t device, uint32_t offset, uint8_t *data, uint8_t len);
int i2c_write_polling_d(uint32_t id, uint16_t device, uint8_t *data, uint8_t len);
int i2c_read_polling_d(uint32_t id, uint16_t device, uint8_t *data, uint8_t len);
