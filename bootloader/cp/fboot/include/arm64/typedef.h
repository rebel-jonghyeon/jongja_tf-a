#pragma once
#ifndef R_TYPEDEFS_H
#define R_TYPEDEFS_H

#ifndef     NULL
#define NULL			((void *)0)
#endif

#define     FALSE       (0)
#define     TRUE        (1)

#define     false       (0)
#define     true        (1)

typedef char                char_t;
typedef unsigned int        bool_t;
typedef int                 int_t;
typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef signed long long    int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;
typedef float               float32_t;
typedef double              float64_t;
typedef long double         float128_t;

typedef signed char         sint8_t;
typedef signed short        sint16_t;
typedef signed int          sint32_t;

typedef long unsigned int   uintptr_t;

typedef unsigned long long  size_t;

typedef unsigned int        bool;

typedef uint64_t            mem_addr_t;

#ifndef SIZE_MAX
#define SIZE_MAX    ( ( size_t ) -1 )
#endif

#endif
