#ifndef ZEROS_H
#define ZEROS_H


#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * Count trailing zeros.  The implementation is a constant-time operation
 * return the count of trailing zeros for a non-zero value.
 * @param x input number != 0
 * @return number of trailing zeros (0 if lowest bit set)
 */
unsigned int ctz32(uint32_t x);


/*!
 * Count leading zeros.  The implementation is a constant-time operation
 * return the count of trailing zeros for a non-zero value.
 * @param x input number != 0
 * @return number of leading zeros
 */
unsigned int clz32(uint32_t x);


#ifdef __cplusplus
}
#endif


#endif
