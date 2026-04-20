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

#include "rl_utils.h"

/* CRC16/XMODEM */
int crc16(unsigned char *ptr, int count)
{
	int i;
	int crc = 0;

	while (--count >= 0) {
		crc = crc ^ (int)*ptr++ << 8;
		for (i = 0; i < 8; ++i) {
			if ((crc & 0x8000) != 0) {
				crc = crc << 1 ^ 0x1021;
			} else {
				crc = crc << 1;
			}
		}
	}
	return crc & 0xffff;
}

uint32_t hex2u32(const char *num_array)
{
	uint32_t value = 0U;
	uint32_t idx = 0U;

	if (num_array == NULL)
		return 0;

	while(num_array[idx] != '\0') {
		char digit = num_array[idx];

		if(ISDIGIT(digit))
			digit -= '0';
		else if(ISHEXDIGITU(digit))
			digit -= ('A' - 10);
		else if(ISHEXDIGITL(digit))
			digit -= ('a' - 10);
		else
			break;

		value <<= 4U;
		value += digit;

		idx++;
	}
	return value;
}
