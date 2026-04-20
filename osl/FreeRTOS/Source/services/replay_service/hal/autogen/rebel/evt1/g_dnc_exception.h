/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2025 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _G_DNC_EXCEPTION_EVT1_H_
#define _G_DNC_EXCEPTION_EVT1_H_

#define ADDR_OFFSET_DNC_EXCEPTION_EXCEPTION1 0x004
#define ADDR_OFFSET_DNC_EXCEPTION_EXCEPTION3 0x00C

union dnc_exception_exception1 {
	struct __attribute__((packed)) {
		uint32_t ncore0_tu : 1;
		uint32_t ncore0_vu : 1;
		uint32_t ncore0_xvu : 1;
		uint32_t ncore0_ablu : 1;
		uint32_t ncore0_absu : 1;
		uint32_t ncore0_splu : 1;
		uint32_t ncore0_spsu : 1;
		uint32_t ncore0_rsvd : 1;
		uint32_t ncore1_tu : 1;
		uint32_t ncore1_vu : 1;
		uint32_t ncore1_xvu : 1;
		uint32_t ncore1_ablu : 1;
		uint32_t ncore1_absu : 1;
		uint32_t ncore1_splu : 1;
		uint32_t ncore1_spsu : 1;
		uint32_t ncore1_rsvd : 1;
		uint32_t nclu : 1;
		uint32_t ncsu : 1;
		uint32_t sp_ue : 1;
		uint32_t sp_perr : 1;
		uint32_t rsvd20 : 1;
		uint32_t rsvd21 : 1;
		uint32_t rsvd22 : 1;
		uint32_t rsvd23 : 1;
		uint32_t ext_dbus_ue : 1;
		uint32_t ext_cbus_ue : 1;
		uint32_t pwr_single_only_vio : 1;
		uint32_t rsvd27 : 1;
		uint32_t tsync_token_ovf : 1;
		uint32_t handle_dismiss : 1;
		uint32_t sync_path_in_pause : 1;
		uint32_t rsvd31 : 1;
	};
	uint32_t bits;
};

union dnc_exception_exception3 {
	struct __attribute__((packed)) {
		uint32_t sp_ce : 1;
		uint32_t dbus_ce : 1;
		uint32_t cbus_ce : 1;
		uint32_t rsvd3 : 1;
		uint32_t comp_vio_rsvd0 : 1;
		uint32_t comp_vio_rsvd1 : 1;
		uint32_t comp_credit_vio_desc : 1;
		uint32_t ldudma_vio_rsvd0 : 1;
		uint32_t ldudma_vio_rsvd1 : 1;
		uint32_t ldudma_credit_vio_desc : 1;
		uint32_t lpudma_vio_rsvd0 : 1;
		uint32_t lpudma_vio_rsvd1 : 1;
		uint32_t lpudma_credit_vio_desc : 1;
		uint32_t studma_vio_rsvd0 : 1;
		uint32_t studma_vio_rsvd1 : 1;
		uint32_t studma_credit_vio_desc : 1;
		uint32_t sp_test_done : 1;
		uint32_t rsvd17 : 1;
		uint32_t rsvd18 : 1;
		uint32_t rsvd19 : 1;
		uint32_t rsvd20 : 1;
		uint32_t rsvd21 : 1;
		uint32_t rsvd22 : 1;
		uint32_t rsvd23 : 1;
		uint32_t rsvd24 : 1;
		uint32_t rsvd25 : 1;
		uint32_t rsvd26 : 1;
		uint32_t rsvd27 : 1;
		uint32_t rsvd28 : 1;
		uint32_t rsvd29 : 1;
		uint32_t rsvd30 : 1;
		uint32_t abort_injec : 1;
	};
	uint32_t bits;
};

#endif /* _G_DNC_EXCEPTION_EVT1_H_*/
