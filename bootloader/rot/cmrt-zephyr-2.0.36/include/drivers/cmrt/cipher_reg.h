/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file cipher_reg.h
 *
 * @brief Common registers for cipher cores: AES and CCP
 */

#ifndef CMRT_CIPHER_REG_H
#define CMRT_CIPHER_REG_H

#define CIPHER_OP_ENCRYPT                0u
#define CIPHER_OP_DECRYPT                1u

/* Input and output status of core */
#define CIPHER_STATUS_IDLE_WITH_KEY        0x41UL
#define CIPHER_STATUS_ACCEPT               0x60UL       /* 0110 0000 */
#define CIPHER_STATUS_ACCEPT_LAST          0x64UL       /* 0110 0100 */
#define CIPHER_STATUS_ACCEPT_RELEASE       0x70UL       /* 0111 0000 */
#define CIPHER_STATUS_ACCEPT_LAST_RELEASE  0x74UL       /* 0111 0000 */
#define CIPHER_STATUS_RELEASE              0xf0UL       /* 1111 0000 */

#define CIPHER_LAST_BLOCK_IS_LAST          0x00010000UL

/* commands for input/output */
#define CIPHER_CMD_MASK               0x000000ffUL
#define CIPHER_CMD_INIT               0x00UL
#define CIPHER_CMD_LOAD_KEY           0x01UL
#define CIPHER_CMD_INVALIDATE_KEY     0x02UL
#define CIPHER_CMD_ENC_DEC            0x03UL
#define CIPHER_CMD_LOAD_IV            0x04UL
#define CIPHER_CMD_LOAD_AD            0x05UL
#define CIPHER_CMD_AUTH               0x06UL
#define CIPHER_CMD_FLUSH              0xffUL

#define CIPHER_ERR_NO_ERROR           0x00UL
#define CIPHER_ERR_UNEXPECTED_CTRL    0x01UL
#define CIPHER_ERR_CTRL_ENCODING      0x02UL
#define CIPHER_ERR_NO_KEY_LOADED      0x03UL
#define CIPHER_ERR_NO_IV_LOADED       0x04UL
#define CIPHER_ERR_AUTH_FAILED        0x05UL
#define CIPHER_ERR_INPUT_LAST_BYTE_EN 0x06UL
#define CIPHER_ERR_OVERFLOW           0x07UL
#define CIPHER_ERR_GLITCH             0x0cUL

#define CIPHER_OPERATION_SHIFT   8UL
#define CIPHER_OPERATION_MASK    (1UL << CIPHER_OPERATION_SHIFT)
#define CIPHER_OPERATION_ENCRYPT (CIPHER_OP_ENCRYPT << CIPHER_OPERATION_SHIFT)
#define CIPHER_OPERATION_DECRYPT (CIPHER_OP_DECRYPT << CIPHER_OPERATION_SHIFT)

#endif
