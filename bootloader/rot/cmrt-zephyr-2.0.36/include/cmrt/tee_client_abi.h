/*
 * Copyright (c) 2019-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef TEE_CLIENT_ABI_H
#define TEE_CLIENT_ABI_H


#ifndef __packed
#ifdef __GNUC__
#define __packed  __attribute__ ((__packed__))
#else
#define __packed
#endif
#endif


#define CMRT_TEEC_ABI_MAJOR 1
#define CMRT_TEEC_ABI_MINOR 0

enum {
    CMRT_TEEC_MAGIC = 'c' | ('r' << 8)
};


/*!
 * Message types.  The values will be passed in
 * teec_abi_message_type_t in the header of the messages.
 */
enum {
    TEEC_ABI_MSG_INVALID = 0,
    TEEC_ABI_MSG_OPEN_SESSION,
    TEEC_ABI_MSG_CLOSE_SESSION,
    TEEC_ABI_MSG_INVOKE_COMMAND,
    TEEC_ABI_MSG_REQUEST_CANCELLATION
};

typedef uint32_t teec_abi_messagetype_t;

typedef struct __packed {
    uint32_t offset; /*!< from the beginning of SAC memory */
    uint32_t size;
} teec_abi_memref_t;

typedef struct __packed {
    uint32_t a;
    uint32_t b;
} teec_abi_value_t;

typedef union __packed {
    teec_abi_memref_t memref;
    teec_abi_value_t value;
} teec_abi_parameter_t;

/**
 * All messages have a common header. Note that there is no explicit response
 * message. A response will always have the same fields that the command had.
 * For example, when opening a session by sending \ref teec_abi_opensession_t
 * the response from CMRT will also be \ref teec_abi_opensession_t.
 */
typedef struct __packed {
    uint16_t magic;
    uint8_t version[2];
    teec_abi_messagetype_t type:16;
    uint16_t param_types;
    uint32_t session; /*!< session ID */
    uint32_t cmdres; /*!< command going into CMRT, result going out */
} teec_abi_header_t;

typedef struct __packed {
    teec_abi_header_t header;
    uint32_t connection_method;
    teec_abi_memref_t connection_data;
    teec_abi_parameter_t params[4];
} teec_abi_opensession_t;

typedef struct __packed {
    teec_abi_header_t header;
} teec_abi_closesession_t;

typedef struct __packed {
    teec_abi_header_t header;
    teec_abi_parameter_t params[4];
} teec_abi_invokecommand_t;

typedef struct __packed {
    teec_abi_header_t header;
} teec_abi_requestcancellation_t;

/**
 * A message will always fit to this space.
 */
typedef union __packed {
    teec_abi_opensession_t o;
    teec_abi_closesession_t c;
    teec_abi_invokecommand_t i;
    teec_abi_requestcancellation_t r;
} teec_abi_message_t;

#endif
