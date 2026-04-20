#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>

#include "utils.h"

void hexdump(const void *data, size_t len)
{
    int bytes = (int)len;
    const unsigned char *p = data;
    while (bytes > 0) {
        printf("%08x: ", (int)len - bytes);
        for (int i = 0; i < 16; ++i) {
            if (bytes > 0) printf("%02x ", *p);
            else fputs("   ", stdout);
            ++p;
            --bytes;
            if (i == 7) fputc(' ', stdout);
        }
        bytes += 16;
        p = data;
        fputs(" |", stdout);
        for (int i = 0; i < 16 && bytes > 0; ++i) {
            fputc(isprint(*p) ? *p : '.', stdout);
            ++p;
            --bytes;
        }
        fputs("|\n", stdout);
        data = p;
    }
}

void worddump(const void *data, size_t words)
{
    const uint32_t *p = data;

    for (size_t i = 0; i < words; ++i) {
        if (i % 8 == 0 && i != 0) {
            printf("\n");
        }
        printf("0x%08x, ", p[i]);
    }
    printf("\n");
}

int store_file(const void *data, size_t bytes, const char *fname)
{
    FILE *fp = fopen(fname, "wb");
    int ret = -1;

    if (fp) {
        if (fwrite(data, bytes, 1, fp) > 0) {
            ret = 0;
        }
        fclose(fp);
    }
    return ret;
}

size_t load_file(void **pdata, const char *fname)
{
    FILE *fp = fopen(fname, "rb");
    size_t bytes = 0;
    char *data = NULL;

    if (fp) {
        fseek(fp, 0L, SEEK_END);
        bytes = ftell(fp);
        if (bytes > 0) {
            data = malloc(bytes);
            rewind(fp);
            if (fread(data, bytes, 1, fp) == 0) {
                free(data);
                bytes = 0;
            }
        }
        fclose(fp);
        if (bytes > 0) {
            if (*pdata) {
                memcpy(*pdata, data, bytes);
                free(data);
            } else {
                *pdata = data;
            }
        }
    }
    return bytes;
}

void checksum(const void *data, size_t len)
{
    uint8_t h[32];
    SHA256(data, len, h);
    hexdump(h, 32);
}

static uint32_t g_prng_seed = 0xdeadbeef;

void prng_reseed(uint32_t s)
{
    g_prng_seed = s;
}

uint32_t prng(void)
{

    uint32_t x = g_prng_seed;

    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    g_prng_seed = x;

    return x;
}

void randombytes(void *buf, uint32_t size)
{
    uint8_t *p = buf;

    while (size > 0) {
        uint32_t x = prng();
        if (size >= 4) {
            memcpy(p, &x, 4);
            size -= 4;
            p += 4;
        } else {
            memcpy(p, &x, size);
            size = 0;
        }
    }
}
