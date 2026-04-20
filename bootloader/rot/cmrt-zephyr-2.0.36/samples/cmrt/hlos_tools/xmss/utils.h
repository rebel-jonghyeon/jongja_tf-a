#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

void hexdump(const void *data, size_t len);
void worddump(const void *data, size_t words);
void checksum(const void *data, size_t len);
int store_file(const void *data, size_t bytes, const char *fname);
size_t load_file(void **pdata, const char *fname);
void prng_reseed(uint32_t s);
uint32_t prng(void);
void randombytes(void *buf, uint32_t size);


#endif
