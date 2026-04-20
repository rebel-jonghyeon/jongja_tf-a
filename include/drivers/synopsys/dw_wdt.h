/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
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

#ifndef DW_WDT_H
#define DW_WDT_H

typedef struct dw_wdt_params {
	uintptr_t	reg_base;
	uint32_t	clk_rate;
	uint32_t	timeout;
} dw_wdt_params_t;

void dw_wdt_init(dw_wdt_params_t *params);
void dw_wdt_kick(dw_wdt_params_t *params);

#endif /* DW_WDT_H */
