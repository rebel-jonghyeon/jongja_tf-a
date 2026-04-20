/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2024 [Rebellions Inc.], All Rights Reserved.
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

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

//TODO: Uncomment after porting terminal task
//#include "terminal_task.h"
#include "external/backtrace/backtrace.h"
#include "rbln/abort.h"
#include "rbln/rebel.h"

void __assert_func(const char *file, int line, const char *func, const char *expr)
{
	//const char *last_slash;
	//const char *last_path;

	//if (file) {
	//	last_slash = strrchr(file, '/');
	//	last_path = (last_slash != NULL) ? (last_slash + 1) : file;
	//}

	func = func ? func : "";
	//LOG_ASSERT("\r\nASSERT: '%s' at %s (line %d in %s)\r\n",
	//	expr ? expr : "", func, line, file ? last_path : "");
	backtrace(func);

	rl_abort_event(ERR_UNKNOWN);
	rl_shutdown(-1);
}
