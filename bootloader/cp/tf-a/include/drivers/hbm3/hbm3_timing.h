/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#pragma once

/* KHBBC4B03C-MC1K */
/* SAMSUNG 24Gb 12H HBM3E_SE */

#ifndef RU
#define RU(x)										((int)((x) == (int)(x) ? (x) : (int)((x) + 1)))
#endif /* RU */

#ifndef MAX
#define MAX(x, y)									((x) > (y) ? (x) : (y))
#endif /* MAX */

#define NS_TO_CYCLES(ns, ck_freq)					(RU((ns) / (1000.0 / (ck_freq))))
#define CYCLE_TIME_NS(ck_freq)						(1000.0 / (ck_freq))
#define SAMSUNG_24G_12H_HBM3E_SE_tDQSS_MAX(ck_freq)	(CYCLE_TIME_NS(ck_freq) * 0.2)

#define CK_1200MHZ	(1200)
#define CK_1600MHZ	(1600)
#define CK_2000MHZ	(2000)
#define CK_2300MHZ	(2300)
#define CK_2400MHZ	(2400)

/* =============================================================================
 * SAMSUNG 24Gb 12H HBM3E (KHBBC4B03B-MC1J)
 * =============================================================================
 */

#define SAMSUNG_24G_12H_HBM3E_SE_BL							(8)
#define SAMSUNG_24G_12H_HBM3E_SE_tWDQS2DQ_O_MAX(ck_freq)	(2.5)
#define SAMSUNG_24G_12H_HBM3E_SE_tWDQS2DQ_I_MIN(ck_freq)	(0.45)
#define SAMSUNG_24G_12H_HBM3E_SE_tXPR(ck_freq)				(NS_TO_CYCLES(200, ck_freq))
#define SAMSUNG_24G_12H_HBM3E_SE_PL_MIN(ck_freq)			(1)
#define SAMSUNG_24G_12H_HBM3E_SE_PL_MAX(ck_freq)			(2)

/* Read Latency */
#define SAMSUNG_24G_12H_HBM3E_SE_READ_LATENCY(ck_freq)	((ck_freq) <= CK_1200MHZ ? 41 : \
														 (ck_freq) <= CK_1600MHZ ? 51 : \
														 (ck_freq) <= CK_2000MHZ ? 62 : \
														 (ck_freq) <= CK_2300MHZ ? 70 : 73)
/* Write Latency */
#define SAMSUNG_24G_12H_HBM3E_SE_WRITE_LATENCY(ck_freq)	((ck_freq) <= CK_1200MHZ ? 9 : \
														 (ck_freq) <= CK_1600MHZ ? 12 : \
														 (ck_freq) <= CK_2000MHZ ? 15 : 17)

/* Timing Parameters */
#define SAMSUNG_24G_12H_HBM3E_SE_tRC(ck_freq)			(MAX(NS_TO_CYCLES(52, ck_freq), 6))
#define SAMSUNG_24G_12H_HBM3E_SE_tRAS(ck_freq)			(MAX(NS_TO_CYCLES(34, ck_freq), 3))
#define SAMSUNG_24G_12H_HBM3E_SE_tRCDRD(ck_freq)		(MAX(NS_TO_CYCLES(18, ck_freq), 3))
#define SAMSUNG_24G_12H_HBM3E_SE_tRCDWR(ck_freq)		(MAX(NS_TO_CYCLES(12, ck_freq), 3))

#define SAMSUNG_24G_12H_HBM3E_SE_tRRDL(ck_freq)			(MAX(NS_TO_CYCLES(2.5, ck_freq), 2))
#define SAMSUNG_24G_12H_HBM3E_SE_tRRDS(ck_freq)			(MAX(NS_TO_CYCLES(2.5, ck_freq), 2))

#define SAMSUNG_24G_12H_HBM3E_SE_tFAW(ck_freq)			(SAMSUNG_24G_12H_HBM3E_SE_tRRDS(ck_freq) * 4)
#define SAMSUNG_24G_12H_HBM3E_SE_tRTP(ck_freq)			(5)
#define SAMSUNG_24G_12H_HBM3E_SE_tRP(ck_freq)			(MAX(NS_TO_CYCLES(18, ck_freq), 3))
#define SAMSUNG_24G_12H_HBM3E_SE_tWR(ck_freq)			((ck_freq) <= CK_1200MHZ ? 28 : \
														 (ck_freq) <= CK_1600MHZ ? 35 : \
														 (ck_freq) <= CK_2000MHZ ? 44 : \
														 (ck_freq) <= CK_2300MHZ ? 50 : 52)
#define SAMSUNG_24G_12H_HBM3E_SE_tDAL(ck_freq)			(SAMSUNG_24G_12H_HBM3E_SE_tWR(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_tRP(ck_freq))
#define SAMSUNG_24G_12H_HBM3E_SE_tPPD(ck_freq)			(2)
/* #define SAMSUNG_24G_12H_HBM3E_SE_tRRA(ck_freq)		(TBD) */

#define SAMSUNG_24G_12H_HBM3E_SE_tCCDL(ck_freq)			(MAX(NS_TO_CYCLES(2, ck_freq), 4))
#define SAMSUNG_24G_12H_HBM3E_SE_tCCDS(ck_freq)			(2)
#define SAMSUNG_24G_12H_HBM3E_SE_tCCDR(ck_freq)			((ck_freq) <= CK_2300MHZ ? \
														 (SAMSUNG_24G_12H_HBM3E_SE_tCCDS(ck_freq) + 1) : \
														 (SAMSUNG_24G_12H_HBM3E_SE_tCCDS(ck_freq) + 2))

#define SAMSUNG_24G_12H_HBM3E_SE_tWTRL(ck_freq)			(MAX(NS_TO_CYCLES(7.5, ck_freq), 4) + 1)
#define SAMSUNG_24G_12H_HBM3E_SE_tWTRS(ck_freq)			(MAX(NS_TO_CYCLES(4.3, ck_freq), 2) + 1)
#define SAMSUNG_24G_12H_HBM3E_SE_tRTW(ck_freq)			(RU(((SAMSUNG_24G_12H_HBM3E_SE_READ_LATENCY(ck_freq) + \
														 (SAMSUNG_24G_12H_HBM3E_SE_BL / 4) - \
														 SAMSUNG_24G_12H_HBM3E_SE_WRITE_LATENCY(ck_freq) + 0.5) * \
														 CYCLE_TIME_NS(ck_freq) + \
														 (SAMSUNG_24G_12H_HBM3E_SE_tWDQS2DQ_O_MAX(ck_freq) - \
														 SAMSUNG_24G_12H_HBM3E_SE_tWDQS2DQ_I_MIN(ck_freq))) / \
														 CYCLE_TIME_NS(ck_freq)))

#define SAMSUNG_24G_12H_HBM3E_SE_tCPDED(ck_freq)		(MAX(NS_TO_CYCLES(7.5, ck_freq), 10))
#define SAMSUNG_24G_12H_HBM3E_SE_tCKPDX(ck_freq)		(5)
#define SAMSUNG_24G_12H_HBM3E_SE_tCKPDE(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_tCPDED(ck_freq) + 1)

#define SAMSUNG_24G_12H_HBM3E_SE_tACTPDE(ck_freq)		(1)
#define SAMSUNG_24G_12H_HBM3E_SE_tPRPDER(ck_freq)		(1)
#define SAMSUNG_24G_12H_HBM3E_SE_tPRPDEF(ck_freq)		(RU(1.5))
#define SAMSUNG_24G_12H_HBM3E_SE_tREFPDE(ck_freq)		(1)
#define SAMSUNG_24G_12H_HBM3E_SE_tREFPBPDE(ck_freq)		(1)
#define SAMSUNG_24G_12H_HBM3E_SE_tREFPBPDE(ck_freq)		(1)
#define SAMSUNG_24G_12H_HBM3E_SE_tRDPDE(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_READ_LATENCY(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_PL_MIN(ck_freq) + 2 + \
														 RU((SAMSUNG_24G_12H_HBM3E_SE_tDQSS_MAX(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_tWDQS2DQ_O_MAX(ck_freq)) / \
														 CYCLE_TIME_NS(ck_freq)))

#define SAMSUNG_24G_12H_HBM3E_SE_tPD(ck_freq)			(SAMSUNG_24G_12H_HBM3E_SE_tCPDED(ck_freq) + 6)
#define SAMSUNG_24G_12H_HBM3E_SE_tXP(ck_freq)			(MAX(NS_TO_CYCLES(7.5, ck_freq), 15))

#define SAMSUNG_24G_12H_HBM3E_SE_tWRPDE(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_WRITE_LATENCY(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_PL_MIN(ck_freq) + 3 + \
														 SAMSUNG_24G_12H_HBM3E_SE_tWR(ck_freq))
#define SAMSUNG_24G_12H_HBM3E_SE_tWRAPDE(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_WRITE_LATENCY(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_PL_MIN(ck_freq) + 3 + \
														 SAMSUNG_24G_12H_HBM3E_SE_tWR(ck_freq))

#define SAMSUNG_24G_12H_HBM3E_SE_tCKSR(ck_freq)			(SAMSUNG_24G_12H_HBM3E_SE_tCPDED(ck_freq) + 6)
#define SAMSUNG_24G_12H_HBM3E_SE_tCKSRE(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_tCPDED(ck_freq) + 1)
#define SAMSUNG_24G_12H_HBM3E_SE_tCKSRX(ck_freq)		(5)
#define SAMSUNG_24G_12H_HBM3E_SE_tRDSRE(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_READ_LATENCY(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_PL_MIN(ck_freq) + 3)

#define SAMSUNG_24G_12H_HBM3E_SE_tRFCab(ck_freq)		(NS_TO_CYCLES(450, ck_freq))
#define SAMSUNG_24G_12H_HBM3E_SE_tRFCpb(ck_freq)		(NS_TO_CYCLES(240, ck_freq))
#define SAMSUNG_24G_12H_HBM3E_SE_tREFI(ck_freq)			(NS_TO_CYCLES(3900, ck_freq))
#define SAMSUNG_24G_12H_HBM3E_SE_tREFIpb(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_tREFI(ck_freq) / 48)

#define SAMSUNG_24G_12H_HBM3E_SE_tXS(ck_freq)			(MAX(SAMSUNG_24G_12H_HBM3E_SE_tRFCab(ck_freq) + \
														 NS_TO_CYCLES(10, ck_freq), 10))
#define SAMSUNG_24G_12H_HBM3E_SE_tXSMRS(ck_freq)		(MAX(NS_TO_CYCLES(15, ck_freq), 10))
#define SAMSUNG_24G_12H_HBM3E_SE_tXSMRSF(ck_freq)		(MAX(SAMSUNG_24G_12H_HBM3E_SE_tRFCab(ck_freq) + \
														 NS_TO_CYCLES(10, ck_freq), 10))
#define SAMSUNG_24G_12H_HBM3E_SE_tRAASRF(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_READ_LATENCY(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_PL_MIN(ck_freq) + 2 + \
														 RU((SAMSUNG_24G_12H_HBM3E_SE_tDQSS_MAX(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_tWDQS2DQ_O_MAX(ck_freq)) / \
														 CYCLE_TIME_NS(ck_freq)))
#define SAMSUNG_24G_12H_HBM3E_SE_tRREFD(ck_freq)		(MAX(NS_TO_CYCLES(8, ck_freq), 3))

#define SAMSUNG_24G_12H_HBM3E_SE_tMOD(ck_freq)			(MAX(NS_TO_CYCLES(15, ck_freq), 12))
#define SAMSUNG_24G_12H_HBM3E_SE_tMRD(ck_freq)			(MAX(NS_TO_CYCLES(5, ck_freq), 8))
#define SAMSUNG_24G_12H_HBM3E_SE_tMRSPDE(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_tMOD(ck_freq))
#define SAMSUNG_24G_12H_HBM3E_SE_tRDMRS(ck_freq)		(SAMSUNG_24G_12H_HBM3E_SE_READ_LATENCY(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_PL_MIN(ck_freq) + 2 + \
														 RU((SAMSUNG_24G_12H_HBM3E_SE_tDQSS_MAX(ck_freq) + \
														 SAMSUNG_24G_12H_HBM3E_SE_tWDQS2DQ_O_MAX(ck_freq)) / \
														 CYCLE_TIME_NS(ck_freq)))
