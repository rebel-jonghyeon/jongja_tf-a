/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 * PROPRIETARY/CONFIDENTIAL
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it
 * only in accordance with the terms of the license agreement you entered
 * into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NON-INFRINGEMENT.
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT
 * OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include <stdint.h>

void pvt_cli_disable_dfs(uint32_t chiplet_id, uint32_t instance_id);
void pvt_cli_disable_trip(uint32_t chiplet_id, uint32_t instance_id);
void pvt_cli_disable_process(uint32_t chiplet_id, uint32_t instance_id);
void pvt_cli_disable_voltage(uint32_t chiplet_id, uint32_t instance_id);
void pvt_cli_disable_temperature(uint32_t chiplet_id, uint32_t instance_id);
