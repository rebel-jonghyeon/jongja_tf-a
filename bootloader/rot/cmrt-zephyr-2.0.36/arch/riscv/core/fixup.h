/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_FIXUP_H
#define CMRT_FIXUP_H

#define ZERO_EXT_8_32  1U
#define SIGN_EXT_8_32  2U
#define ZERO_EXT_16_32 3U
#define SIGN_EXT_16_32 4U
#define IS_WRITE       5U

#define SEXT32(x, signbit) (((x) & (1UL << (signbit))) ? ((x) | (0xFFFFFFFF ^ ((1UL << ((signbit) + 1)) - 1))) : (x))

#define BASE_REG_I(x)   (((x) & 0x000f8000) >> 15)
#define OFFSET_I(x)     SEXT32((((x) & 0xfff00000) >> 20), 11)
#define DATA_REG_I(x)   (((x) & 0x00000f80) >> 7)

#define BASE_REG_S(x)   (((x) & 0x000f8000) >> 15)
#define OFFSET_S(x)     SEXT32((((x) & 0xfe000000) >> 20 | ((x) & 0x00000f80) >> 7), 11)
#define DATA_REG_S(x)   (((x) & 0x01f00000) >> 20)

#define BASE_REG_CL(x)  ((((x) & 0x0380) >> 7) + 8)
#define OFFSET_CL(x)    (((x) & 0x40) >> 4 | ((x) & 0x20) << 1 | \
			 ((x) & 0x1c00) >> 7)
#define DATA_REG_CL(x)  ((((x) & 0x001c) >> 2) + 8)

#define BASE_REG_CS(x)  ((((x) & 0x0380) >> 7) + 8)
#define OFFSET_CS(x)    (((x) & 0x40) >> 4 | ((x) & 0x20) << 1 | \
			 ((x) & 0x1c00) >> 7)
#define DATA_REG_CS(x)  ((((x) & 0x001c) >> 2) + 8)

#define BASE_REG_CI(x)  2
#define OFFSET_CI(x)    ((((x) & 0x1000) >> 7) | (((x) & 0x70) >> 2) | \
			(((x) & 0xc) << 4))

#define DATA_REG_CI(x)  (((x) & 0xf80) >> 7)

#define BASE_REG_CSS(x) 2
#define OFFSET_CSS(x)   (((x) & 0x1e00) >> 7 | ((x) & 0x180) >> 1)
#define DATA_REG_CSS(x) (((x) & 0x7c) >> 2)


/* XXX use parse-opcodes */
#define MATCH_C_SW   0xc000UL
#define MASK_C_SW    0xe003UL
#define MATCH_SW     0x2023UL
#define MASK_SW      0x707fUL
#define MATCH_SH     0x1023UL
#define MASK_SH      0x707fUL
#define MATCH_C_SWSP 0xc002UL
#define MASK_C_SWSP  0xe003UL
#define MATCH_LHU    0x5003UL
#define MASK_LHU     0x707fUL
#define MATCH_LH     0x1003UL
#define MASK_LH      0x707fUL
#define MATCH_LW     0x2003UL
#define MASK_LW      0x707fUL
#define MATCH_C_LW   0x4000UL
#define MASK_C_LW    0xe003UL
#define MATCH_C_LWSP 0x4002UL
#define MASK_C_LWSP  0xe003UL
#define MATCH_LB     0x0003UL
#define MASK_LB      0x707fUL
#define MATCH_LBU    0x4003UL
#define MASK_LBU     0x707fUL
#define MATCH_SB     0x0023UL
#define MASK_SB      0x707fUL

#endif
