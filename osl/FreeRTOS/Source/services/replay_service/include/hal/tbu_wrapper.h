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

#ifndef _TBU_WRAPPER_H_
#define _TBU_WRAPPER_H_

#define EBUS_D_SYSREG_SMMU_ETC_OFF              0x520
#define     EBUS_D_ERR_IRPT_EN_BIT              (1 << 1)
#define     EBUS_D_TBU_IF_EN_BIT                (1 << 0)

#define EBUS_R_SYSREG_SMMU_ETC_OFF              0x518
#define     EBUS_R_ERR_IRPT_EN_CL1_BIT          (1 << 3)
#define     EBUS_R_TBU_IF_EN_CL1_BIT            (1 << 2)
#define     EBUS_R_ERR_IRPT_EN_CL0_BIT          (1 << 1)
#define     EBUS_R_TBU_IF_EN_CL0_BIT            (1 << 0)

#define EBUS_U_SYSREG_SMMU_ETC_OFF              0x520
#define     EBUS_U_ERR_IRPT_EN_BIT              (1 << 1)
#define     EBUS_U_TBU_IF_EN_BIT                (1 << 0)

#define NBUS_D_SYSREG_SMMU_ETC_OFF              0x51C
#define     NBUS_D_ERR_IRPT_EN_RBDMA_7_BIT      (1 << 11)
#define     NBUS_D_ERR_IRPT_EN_RBDMA_6_BIT      (1 << 10)
#define     NBUS_D_ERR_IRPT_EN_RBDMA_5_BIT      (1 << 9)
#define     NBUS_D_ERR_IRPT_EN_RBDMA_4_BIT      (1 << 8)
#define     NBUS_D_TBU_IF_EN_RBDMA_7_BIT        (1 << 3)
#define     NBUS_D_TBU_IF_EN_RBDMA_6_BIT        (1 << 2)
#define     NBUS_D_TBU_IF_EN_RBDMA_5_BIT        (1 << 1)
#define     NBUS_D_TBU_IF_EN_RBDMA_4_BIT        (1 << 0)

#define NBUS_L_SYSREG_SMMU_ETC_OFF              0x51C
#define     NBUS_L_ERR_IRPT_EN_RBDMA_3_BIT      (1 << 11)
#define     NBUS_L_ERR_IRPT_EN_RBDMA_2_BIT      (1 << 10)
#define     NBUS_L_ERR_IRPT_EN_RBDMA_1_BIT      (1 << 9)
#define     NBUS_L_ERR_IRPT_EN_RBDMA_0_BIT      (1 << 8)
#define     NBUS_L_TBU_IF_EN_RBDMA_3_BIT        (1 << 3)
#define     NBUS_L_TBU_IF_EN_RBDMA_2_BIT        (1 << 2)
#define     NBUS_L_TBU_IF_EN_RBDMA_1_BIT        (1 << 1)
#define     NBUS_L_TBU_IF_EN_RBDMA_0_BIT        (1 << 0)

#define WBUS_D_TBU_IF_EN_OFF                    0x508
#define     WBUS_D_TBU_I_TBU_IF_EN_BIT          (3 << 0)
#define WBUS_D_TBU_ERR_IRPT_EN_OFF              0x50C
#define     WBUS_D_TBU_I_ERR_IRPT_EN_BIT        (3 << 0)

#define WBUS_U_TBU_IF_EN_OFF                    0x510
#define     WBUS_U_TBU_I_TBU_IF_EN_BIT          (3 << 0)
#define WBUS_U_TBU_ERR_IRPT_EN_OFF              0x514
#define     WBUS_U_TBU_I_ERR_IRPT_EN_BIT        (3 << 0)

int tbu_wrapper_deinit(uint32_t cl_id);
int tbu_wrapper_init(uint32_t cl_id);

#endif /* _TBU_WRAPPER_H_ */
