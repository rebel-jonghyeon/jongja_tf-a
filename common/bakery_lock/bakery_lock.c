/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include "bakery_lock.h"

void rebel_bakery_lock_acquire(uint32_t cpu_id)
{
	int max_ticket = 0;

	if (cpu_id >= BAKERY_ID_MAX)
		return;

	/* Try to get a ticket */
	BAKERY_ENTERING[cpu_id] = 1;
	dmb();

	/* Find the maximum ticket */
	for (int i = 0; i < BAKERY_ID_MAX; ++i) {
		int ticket = BAKERY_TICKET[i];

		if (ticket > max_ticket)
			max_ticket = ticket;
	}

	/* Take a ticket higher than _max_ticket */
	BAKERY_TICKET[cpu_id] = max_ticket + 1;
	dmb();

	/* End of choosing the ticket */
	BAKERY_ENTERING[cpu_id] = 0;
	dmb();

	/* Wait for all other cpus to either:
	 *	1) finish choosing their ticket, or
	 *	2) hold a lower ticket
	 */
	for (int i = 0; i < BAKERY_ID_MAX; ++i) {
		if (i == cpu_id)
			continue;

		/* Wait until i-th cpu finished choosing its ticket	*/
		while (BAKERY_ENTERING[i])
			;
		/* Wait until i-th cpu either leaves or has lower priority	*/
		while (BAKERY_TICKET[i] != 0 &&
			   (BAKERY_TICKET[i] < BAKERY_TICKET[cpu_id] ||
				(BAKERY_TICKET[i] == BAKERY_TICKET[cpu_id] && i < cpu_id)))
			;
	}
	dmb();
}

void rebel_bakery_lock_release(uint32_t cpu_id)
{
	if (cpu_id >= BAKERY_ID_MAX)
		return;

	dmb();
	BAKERY_TICKET[cpu_id] = 0;
	dmb();
}

void rebel_bakery_lock_init(void)
{
	for (int i = 0; i < BAKERY_ID_MAX; ++i) {
		BAKERY_ENTERING[i]	= 0;
		BAKERY_TICKET[i]	= 0;
	}
}
