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

#pragma once

#include "test_common.h"

typedef unsigned long ul;
typedef unsigned long long ull;
typedef unsigned long volatile ulv;
typedef unsigned long long volatile ullv;
typedef unsigned char volatile u8v;
typedef unsigned short volatile u16v;

#define rand32() ((unsigned int)rand() | ((unsigned int)rand() << 16))

#define ONE 0x00000001L

#define EXIT_FAIL_NONSTARTER    0xFF
#define EXIT_FAIL_ADDRESSLINES  0xFE

#define AARCH_64

#ifdef AARCH_32 //#if (ULONG_MAX == 4294967295UL)
#define rand_ul() rand32()
#define UL_ONEBITS 0xffffffff
#define UL_LEN 32
#define CHECKERBOARD1 0x55555555
#define CHECKERBOARD2 0xaaaaaaaa
#define UL_BYTE(x) (((x) | (x) << 8 | (x) << 16 | (x) << 24))
#endif

#ifdef AARCH_64 //#elif (ULONG_MAX == 18446744073709551615ULL)
#define rand64() (((ull)rand32()) << 32 | ((ull)rand32()))
#define rand_ul() rand64()
#define UL_ONEBITS 0xffffffffffffffffUL
#define UL_LEN 64
#define CHECKERBOARD1 0xaaaa5555aaaa5555UL
#define CHECKERBOARD2 0x5555aaaa5555aaaaUL
#define UL_BYTE(x) (((ull)(x) | (ull)(x) << 8 | (ull)(x) << 16 | (ull)(x) << 24 \
		| (ull)(x) << 32 | (ull)(x) << 40 | (ull)(x) << 48 | (ull)(x) << 56))
#endif

uint8_t test_memtest_main(int argc, char *argv[]);
