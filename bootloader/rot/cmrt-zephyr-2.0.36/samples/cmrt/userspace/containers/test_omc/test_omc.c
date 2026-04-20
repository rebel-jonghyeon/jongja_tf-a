#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <stdalign.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/fboot.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/sic.h>

#define MATCH(argp, argl, lstr) \
        ((argl == sizeof(lstr)-1) && (memcmp(argp, lstr, sizeof(lstr)-1) == 0))

#define BUFSZ 4096
alignas(4) uint8_t buffer[BUFSZ];

static inline uint32_t argl_init(uint8_t **argpp)
{
        const uint32_t argl = **(uint32_t**)argpp;
        *argpp += sizeof(uint32_t);
        return argl;
}

static inline uint32_t argl_next(uint8_t **argpp, uint32_t argl)
{
        *argpp += ((argl + 3) & ~3);
        argl = **(uint32_t**)argpp;
        *argpp += sizeof(uint32_t);
        return argl;
}

static void print_usage(void)
{
        LOG_INF("Usage:");
        LOG_INF("\tREAD:");
        LOG_INF("\t\tOMC = OTP Memory Controller [offset] [size]");
        LOG_INF("\t\tMMR = Memory Map Region [address] [size]");
        LOG_INF("\tWRITE:");
        LOG_INF("\t\tOMC = OTP Memory Controller [offset] [value]");
        LOG_INF("\t\tMMR = Memory Map Region [address] [value]");
        LOG_INF("\tROOT:");
        LOG_INF("\t\tCREATE [index] [hash] [permissions]");
        LOG_INF("\t\tOBLITERATE [index]");
}

/* Converts a (decimal) string into a uint32_t. Returns the parsed number.
 * Processes exactly `sl` bytes from the string `s`.
 * On conversion error sets errno to -EINVAL and returns 0.
 *
 * Encountering a nullbyte is a a conversion error.
 * An empty string (`sl`== 0) is a conversion error.
 * No wrapparound checks on `sl`.
 *
 * Wrapparound on conversion is checked by ensuring that
 * acc*10 + v > acc.
 * */
static uint32_t conv_strl2u32(const char *s, size_t sl)
{
        uint32_t acc = 0;
        uint32_t pre_sum_acc = 0;

        const char *s_end = s + sl; /* no ovf check */
        for (; s < s_end; ++s) {
                char v = *s;
                if (v < '0' || v > '9') {
                        errno = EINVAL;
                        return 0;
                }
                v -= '0';
                pre_sum_acc = acc;
                acc *= 10;
                acc += v;
                if (acc < pre_sum_acc){ /* ovf check */
                        errno = EINVAL;
                        LOG_INF("Unsigned integer overflow!");
                        return 0;
                }
        }
        return acc;
}

static int process_create_root(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
    (void)argc;
    (void)*_buflen;

    uint32_t argl = argl_init(&argp);

    unsigned int index = (unsigned int)strtoul((char *) argp, NULL, 0);
    if (index > 99) {
        return -EINVAL;
    }

    struct cmrt_omc_root_t new_root;

    size_t hashlen = argl = argl_next(&argp, argl);

    if (sizeof(new_root.id.hash) != hashlen) {
        LOG_INF("Incorrect hash/id size %u, expecting %d",
            hashlen, sizeof(new_root.id.hash));
        return -EINVAL;
    }
    memcpy(new_root.id.hash, argp, sizeof(new_root.id.hash));

    size_t permlen = argl = argl_next(&argp, argl);
    if (sizeof(new_root.perm) != permlen) {
        LOG_INF("Incorrect permissions size %d, expecting %d",
            permlen, sizeof(new_root.perm));
        return -EINVAL;
    }
    memcpy(&new_root.perm, argp, sizeof(new_root.perm));

    LOG_INF("Creating root on index '%d'...", index);
    LOG_INF("Permissions:\n"
        "\tnew_root.perm.slot_perm = %lx", new_root.perm.slot_perm.val);
    LOG_INF("\tnew_root.perm.key_perm = %lx", new_root.perm.key_perm.val);
    LOG_INF("\tnew_root.perm.feature_perm = %lx", new_root.perm.feature_perm.val);
    LOG_INF("\tnew_root.perm.sw_otp_perm[0] = %lx", new_root.perm.sw_otp_perm[0].val);
    LOG_INF("\tnew_root.perm.sw_otp_perm[1] = %lx", new_root.perm.sw_otp_perm[1].val);
    LOG_INF("\tnew_root.perm.software_perm = %lx", new_root.perm.software_perm.val);

    int res = fboot_create_root(index, &new_root);
    return res;
}

static int process_obliterate_root(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
        (void)argc;

        /* Expected format: [offset] */
        /* Obtaining parameters */
        uint32_t offset_length = argl_init(&argp);
        (void)offset_length;
        char *offset_str_param = (char *)argp;

        char *next;
        uint32_t offset_parameter = strtoul(offset_str_param, &next, 0);
        if (next == offset_str_param) {
                LOG_INF("Parsing error");
                return 0;
        }

        if (offset_parameter > 7) {
                LOG_INF("Index outside range 0 to 7.");
                return 0;
        }

        LOG_INF("Obliterate root at offset: %ld", offset_parameter);

        /* Operating with OTP */
        int ret = fboot_obliterate_root(offset_parameter);

        if (ret < 0) {
                LOG_INF("OTP operation failed.");
                *_buflen = 0;
        } else {
            *_buflen = offset_parameter;
        }

        return ret;
}

static int process_root(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
        /* Expected format: OMC|MMR [offset] [size] */
        if (argc < 2) {
                LOG_ERR("Error wrong number of parameters (%lu)", argc);
                return -1;
        }

        uint32_t argl = argl_init(&argp);
        uint8_t *argp_next = argp + ((argl + 3) & ~3);

        if (MATCH(argp, argl, "create")) {
                return process_create_root(argp_next, argc, _buflen);
        }
        if (MATCH(argp, argl, "obliterate")) {
                return process_obliterate_root(argp_next, argc, _buflen);
        }

        argp[argl] = '\0';
        LOG_ERR("%s: Invalid COMMAND", argp);
        return 0;
}


static int process_read_omc(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
        /* Expected format: [offset] [size] */
        //Check that the number of arguments is the correct one
        if (argc != 3) {
                LOG_ERR("Error wrong number of parameters (%lu)", argc);
                return -1;
        }

        //Initialize argument iterator (obtain first parameter length)
        uint32_t argl = argl_init(&argp);

        //Safely convert string (char *) to uint32_t (obtain offset value)
        uint32_t offset_parameter = conv_strl2u32((char *)argp, argl);
        if (offset_parameter == 0 && errno == EINVAL) {
                LOG_ERR("Invalid offset");
                return -1;
        }

        //Iterate to next argument
        argl = argl_next(&argp, argl);

        //Safely convert string (char *) to uint32_t (obtain size value)
        uint32_t size_parameter = conv_strl2u32((char *)argp, argl);
        if (size_parameter == 0 && errno == EINVAL) {
                LOG_ERR("Invalid size");
                return -1;
        }

        LOG_INF("Read OTP: offset: %ld, size: %ld", offset_parameter,
                size_parameter);

        /* Operating with OTP */
        cmrt_omc_t ctx = cmrt_omc_open(0);

        if (!cmrt_is_valid(ctx)) {
                LOG_INF("Cannot open OTP");
                return -1;
        }

        int ret = cmrt_omc_read(ctx, offset_parameter, buffer, size_parameter);
        cmrt_omc_close(ctx);

        if (ret < 0) {
                LOG_INF("OTP operation failed.");
                *_buflen = 0;
        } else {
            *_buflen = size_parameter;
        }
        LOG_INF("String value returned: %lx", *(uint32_t *) buffer);

        return ret;
}

static int process_read_mmr(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
        /* Expected format: [address] [size] */
        //Check that the number of arguments is the correct one
        if (argc != 3) {
                LOG_ERR("Error wrong number of parameters (%lu)", argc);
                return -1;
        }

        //Initialize argument iterator (obtain first parameter length)
        uint32_t argl = argl_init(&argp);

        //Safely convert string (char *) to uint32_t (obtain address value)
        uint32_t address_parameter = conv_strl2u32((char *)argp, argl);
        if (address_parameter == 0 && errno == EINVAL) {
                LOG_ERR("Invalid address");
                return -1;
        }

        //Iterate to next argument
        argl = argl_next(&argp, argl);

        //Safely convert string (char *) to uint32_t (obtain size value)
        uint32_t size_parameter = conv_strl2u32((char *)argp, argl);
        if (size_parameter == 0 && errno == EINVAL) {
                LOG_ERR("Invalid size");
                return -1;
        }

        LOG_INF("Read MMR: address: %ld, size: %ld", address_parameter,
                size_parameter);

        char *next = (char *)address_parameter;
        memcpy(buffer, next, size_parameter);
        *_buflen = size_parameter;

        return *_buflen;
}

static int process_read(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
        /* Expected format: OMC|MMR [offset] [size] */
        if (argc != 3) {
                LOG_ERR("Error wrong number of parameters (%lu)", argc);
                return -1;
        }

        uint32_t argl = argl_init(&argp);
        uint8_t *argp_next = argp + ((argl + 3) & ~3);

        if (MATCH(argp, argl, "omc")) {
                return process_read_omc(argp_next, argc, _buflen);
        }
        if (MATCH(argp, argl, "mmr")) {
                return process_read_mmr(argp_next, argc, _buflen);
        }

        argp[argl] = '\0';
        LOG_ERR("%s: Invalid COMMAND", argp);
        return -1;
}

static int process_write_omc(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
        /* Expected format: [offset] [value] */
        /* Obtaining parameters */

        //Check that the number of arguments is the correct one
        if (argc != 3) {
                LOG_ERR("Error wrong number of parameters (%lu)", argc);
                return -1;
        }

        //Initialize argument iterator and obtain first parameter length
        uint32_t argl = argl_init(&argp);

        //Safely convert string (char *) to uint32_t (obtain offset value)
        uint32_t offset_parameter = conv_strl2u32((char *)argp, argl);
        if (offset_parameter == 0 && errno == EINVAL) {
                LOG_ERR("Invalid offset");
                return -1;
        }

        //Iterate to next argument and obtain second parameter length
        uint32_t value_length = argl_next(&argp, argl);
        uint8_t *value_str_param = argp;

        LOG_INF("Write OTP: offset: %ld, value: %s", offset_parameter,
                value_str_param);

        /* Operating with OTP */
        cmrt_omc_t ctx = cmrt_omc_open(0);

        if (!cmrt_is_valid(ctx)) {
                LOG_INF("Cannot open OTP");
                return -1;
        } else {
            LOG_INF("OMC context opened.");
        }

        int ret = cmrt_omc_write(ctx, offset_parameter, value_str_param,
                value_length);

        cmrt_omc_close(ctx);
        LOG_INF("OMC context closed.");

        if (ret < 0) {
                LOG_INF("OTP operation failed.");
                *_buflen = 0;
                ret = -1;
                buffer[0] = '\0';
        } else {
                sprintf((char *) buffer, "%ld", value_length);
                *_buflen =  strlen((char *)buffer);
        }
        return ret;
}

static int process_write_mmr(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
        /* Expected format: [address] [value] */
        //Check that the number of arguments is the correct one
        if (argc != 3) {
                LOG_ERR("Error wrong number of parameters (%lu)", argc);
                return -1;
        }

        //Initialize argument iterator (obtain first parameter length)
        uint32_t argl = argl_init(&argp);

        //Safely convert string (char *) to uint32_t (obtain address value)
        uint32_t address_parameter = conv_strl2u32((char *)argp, argl);
        if (address_parameter == 0 && errno == EINVAL) {
                LOG_ERR("Invalid address");
                return -1;
        }

        //Iterate to next argument
        uint32_t value_length = argl_next(&argp, argl);
        uint8_t *value_str_param = argp;

        LOG_INF("Write MMR: address: %ld, value: %s", address_parameter,
                value_str_param);

        char *next = (char *) address_parameter;
        memcpy(next, value_str_param, value_length);

        sprintf((char *) buffer, "%ld", value_length);
        *_buflen =  strlen((char *)buffer);

        return *_buflen;
}

static int process_write(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
        /* Expected format: OMC|MMR [offset] [size] */
        if (argc != 3) {
                LOG_ERR("Error wrong number of parameters (%lu)", argc);
                return -1;
        }

        uint32_t argl = argl_init(&argp);
        uint8_t *argp_next = argp + ((argl + 3) & ~3);

        if (MATCH(argp, argl, "omc")) {
                return process_write_omc(argp_next, argc, _buflen);
        }
        if (MATCH(argp, argl, "mmr")) {
                return process_write_mmr(argp_next, argc, _buflen);
        }

        argp[argl] = '\0';
        LOG_ERR("%s: Invalid COMMAND", argp);
        return -1;
}

static int process_message(uint8_t *buffer, size_t *_buflen)
{
        if (*_buflen < 8) {
                LOG_ERR("Short message!");
                return -EINVAL;
        }
        uint8_t *argp = buffer;
        uint32_t argc = argl_init(&argp);
        /*
         * Check argument array length matches message length, then
         * commands can trust the lengths of inputs given to them.
         */
        const uint8_t *ap2 = argp;
        for (size_t i = 0; i < argc; i++) {
                const int alen = *(uint32_t*)ap2;
                const uint8_t *const nap = ap2 + ((alen + 7) & ~3);
                if (nap < ap2 || (size_t)(nap - buffer) > *_buflen) {
                        LOG_ERR("Message format error: args length mismatch");
                        return -EINVAL;
                }
                ap2 = nap;
        }
        *_buflen = 0;
        uint32_t argl = argl_init(&argp);
        uint8_t *argp_next = argp + ((argl + 3) & ~3); /* revisit how to do .*/
        argc--;

        /* dispatch OPERATION */
        if (MATCH(argp, argl, "read")) {
                return process_read(argp_next, argc, _buflen);
        }
        if (MATCH(argp, argl, "write")) {
                return process_write(argp_next, argc, _buflen);
        }
        if (MATCH(argp, argl, "root")) {
                return process_root(argp_next, argc, _buflen);
        }

        /* else */
        argp[argl] = '\0';
        LOG_ERR("%s: Invalid COMMAND", argp);
        return -1;
}

static int main_loop(uint32_t flowid)
{
        cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, flowid);
        if (!cmrt_is_valid(sic)) {
                LOG_INF("Cannot open SIC");
                return -ENODEV;
        }
        LOG_INF("Waiting for SIC input on flow 0x%x...", (unsigned int)flowid);

        int res = 0;
        while (true) {
                uint32_t peerid;
                size_t buflen = sizeof(buffer) - 4;

                res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
                if (res < 0) {
                        LOG_INF("Failed to read from HLOS: %d!", res);
                        break;
                }

                LOG_INF("Got request from HLOS of %zu bytes", buflen);
                if (buflen)
                        LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Request from HLOS:");

                /* Processing failure is a fatal error. */
                res = process_message(buffer, &buflen);
                if (res < 0) {
                        LOG_INF("Failed to process the message: %d!", res);
                        break;
                }

                /* The same buffer holds the response to HLOS. */
                LOG_INF("Sending response to HLOS of %zu bytes", buflen);
                if (buflen)
                        LOG_HEXDUMP_DBG(buffer, MIN(64, buflen), "Response to HLOS:");

                if (!buflen) continue;
                res = cmrt_sic_write(sic, buffer, buflen, peerid);
                if (res < 0) {
                        LOG_INF("Failed to write to HLOS: %d!", res);
                        break;
                }
        }
        cmrt_sic_close(sic);
        return res;
}

void container(void *p1, void *p2, void *p3)
{
        (void)p2;
        (void)p3;
        print_usage();
        int res = main_loop((uint32_t)p1);
        LOG_ERR("Container main_loop exited with %d!", res);
}
