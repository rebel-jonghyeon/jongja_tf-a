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

#ifndef _RL_ERROR_H
#define _RL_ERROR_H

#define RL_OK					0		/* Success */
#define RL_ERROR				-1		/* Error generic */
#define RL_BADARG				-2		/* Bad argument */
#define RL_BADLEN				-3		/* Bad length */
#define RL_BADADDR				-4		/* Bad address */
#define RL_DEV_DOWN				-5		/* Device down */
#define RL_BUSY					-6		/* Busy */
#define RL_NOTREADY				-7		/* Not ready */
#define RL_NORESOURCE			-8		/* Not enough resource */
#define RL_UNSUPPORTED			-9		/* Unsupported */
#define RL_NOMEM				-10		/* No memory */
#define RL_EPERM				-11		/* Not permitted */
#define RL_BUFTOOSHORT			-12		/* Buffer too short */
#define RL_BUFTOOLONG			-13		/* Buffer too long */
#define RL_RANGE				-14		/* Not in range */
#define RL_NOT_FOUND			-15		/* Not found */
#define RL_TIMEOUT				-16		/* Time out */
#define RL_ERR_VERSION			-17		/* Incorrect version */

#define RL_NO_IDLE_HDMA_CH		-128	/* All HDMA channels are busy */

#endif /* _RL_ERROR_H */
