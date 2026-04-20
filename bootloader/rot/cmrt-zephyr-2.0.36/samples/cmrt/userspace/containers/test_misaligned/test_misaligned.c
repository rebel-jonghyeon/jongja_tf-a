#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <stdalign.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/util.h>

#define ERROR 1
#define NO_ERROR 0

#define MATCH(argp, argl, lstr)						\
	((argl == sizeof(lstr)-1) && (memcmp(argp, lstr, sizeof(lstr)-1) == 0))

/* SIC buffer */
#define BUFSZ 4096
alignas(4) uint8_t buffer[BUFSZ];

/* Dummy buffers for copying test. */
#define DBUFSZ 1024
alignas(4) static uint32_t dummy1[DBUFSZ];
alignas(4) static uint32_t dummy2[DBUFSZ];

/* 64 bits buffer for ASM operations. */
#define BUF64BSZ 8
alignas(4) static uint8_t buf64b[BUF64BSZ];

/* Assembly functions defined under lwsw.S*/
extern uint32_t lw(void *addr, uint32_t sign);
extern uint32_t lw_c(void *addr, uint32_t sign);
extern uint32_t lwsp(void *addr, uint32_t sign);
extern uint32_t lh(void *addr, uint32_t sign);
extern uint32_t lhu(void *addr, uint32_t sign);
extern void sw(void *addr, uint32_t data, uint32_t sign);
extern void sw_c(void *addr, uint32_t data, uint32_t sign);
extern void swsp(void *addr, uint32_t data, uint32_t sign);
/* NOTE TO SH: sh will return a complete word, but only half word will be valid.
 * This was done to simplify the functions related to storage in asm.
 */
extern void sh(void *addr, uint32_t data, uint32_t);

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

/**
 * @brief Copy 32bits
 *
 * Executes a simple word copy between two variables.
 *
 * @param[in] d Data destination.
 * @param[in] s Data source.
 *
 */
static void copy32(volatile uint32_t *d, volatile uint32_t *s, size_t n)
{
	for (unsigned int i = 0; i < n; i++) {
		d[i] = s[i];
	}
}

static void print_usage(void)
{
	LOG_INF("Usage:");
	LOG_INF("\tBUFFER:");
	LOG_INF("\t\tset [byte array 0 ... 7]");
	LOG_INF("\t\treset");
	LOG_INF("\tASM:");
	LOG_INF("\t\tAll assembly operations are performed on a 64 bits buffer.");
	LOG_INF("\t\tAll offset values are referred to the beginning of the buffer");
	LOG_INF("\t\t\tlw [offset 0 to 4] [offset sign 0 (-) to 1 (+)]= load word");
	LOG_INF("\t\t\tlw_c [offset 0 to 4] [offset sign 0 (-) to 1 (+)] = load word compressed ");
	LOG_INF("\t\t\tlwsp [offset 0 to 4] [offset sign 0 (-) to 1 (+)] = load word via sp ");
	LOG_INF("\t\t\tlh [offset 0 to 4] [offset sign 0 (-) to 1 (+)] = load half word");
	LOG_INF("\t\t\tlhu [offset 0 to 4] [offset sign 0 (-) to 1 (+)] = load unsigned half word ");
	LOG_INF("\t\t\tsw [offset 0 to 4] [offset sign 0 (-) to 1 (+)] [word to store] = store word");
	LOG_INF("\t\t\tsw_c [offset 0 to 4] [offset sign 0 (-) to 1 (+)] [word to store] = store word compressed");
	LOG_INF("\t\t\tswsp [offset 0 to 4] [offset sign 0 (-) to 1 (+)] [word to store] = store word via sp");
	LOG_INF("\t\t\tsh [offset 0 to 4] [offset sign 0 (-) to 1 (+)] [half word to store] = store half word");
	LOG_INF("\tMEM:");
	LOG_INF("\t\tcopy [offset 0 to 1] [offset 0 to 1] [loops 0 to 10000] = copy data between buffers");
}

/**
 * @brief Set buffer 64 bits
 *
 * Load word using assembly functions:
 *     Input expected:
 *	   8 bytes as content for buffer.
 *     Returns:
 *	   Buffer returns value loaded string format.
 *	   Bufferlen return length from buffer string.
 *
 * @param[in] argp Following arguments from cmd.
 * @param[in] argc Number of arguments from cmd.
 * @param[in]  _buflen Length of buffer.
 *
 * @return NO_ERROR or -ERROR
 */
static uint32_t process_buffer_set(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	(void)argc;
	argl_init(&argp);

	/* Load all 8 bytes into buf64b and return the content of buf64b */
	copy32((uint32_t *)buf64b, (uint32_t *)argp, BUF64BSZ);
	copy32((uint32_t *)buffer, (uint32_t *)buf64b, BUF64BSZ);
	buffer[BUF64BSZ] = '\0';
	*_buflen = BUF64BSZ;
	return NO_ERROR;
}

/**
 * @brief Resets buffer 64 bits
 *
 * Resets value buffer.
 *
 * @param[in] argp Following arguments from cmd.
 * @param[in] argc Number of arguments from cmd.
 * @param[in]  _buflen Length of buffer.
 *
 * @return NO_ERROR or -ERROR
 */
static uint32_t process_buffer_reset(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	(void)argp;
	(void)argc;

	/* Execution */
	memset(buf64b, 0, BUF64BSZ);

	/* Return */
	copy32((uint32_t *)buffer, (uint32_t *)buf64b, BUF64BSZ);
	buffer[BUF64BSZ] = '\0';
	*_buflen = BUF64BSZ;
	return NO_ERROR;
}

static int process_buffer(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	/* Expected format: set [byte0...byte7] */
	if ((argc != 1) && (argc != 2)) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		goto e_quit;
	}

	uint32_t argl = argl_init(&argp);
	uint8_t *argp_next = argp + ((argl + 3) & ~3);


	if (MATCH(argp, argl, "set")) {
		return process_buffer_set(argp_next, argc, _buflen);
	} else if (MATCH(argp, argl, "reset")) {
		return process_buffer_reset(argp_next, argc, _buflen);
	} else {
		argp[argl] = '\0';
		LOG_ERR("Invalid command ---> expected (set|reset) received (%s)", (char *) argp);
		*_buflen = 0;
		return -EINVAL;
	}

e_quit:
	LOG_ERR("Invalid command ---> %s", argp);
	*_buflen = 0;
	return -EINVAL;
}

/**
 * @brief Assembly Load Command Execution
 *
 * Load command using assembly functions:
 *     Input expected:
 *	   Parameter offset range 0 to 4.
 *     Returns:
 *	   Buffer returns value loaded string format.
 *	   Bufferlen return length from buffer string.
 *
 * @param[in] argp Following arguments from cmd.
 * @param[in] argc Number of arguments from cmd.
 * @param[in]  _buflen Length of buffer.
 *
 * @return NO_ERROR or -ERROR
 */
static uint32_t process_asm_load_command(uint8_t *argp, uint32_t argc, size_t *_buflen,
					 uint32_t (*fptr)(void *addr, uint32_t sign))
{
	(void)argc;

	/* Parameters collection */
	uint32_t parameter_size = argl_init(&argp);
	char *offset_str_param = (char *)argp;
	parameter_size = argl_next(&argp, parameter_size);
	char *sign_str_param = (char *)argp;

	uint32_t sign;
	char *next;
	uint32_t offset_parameter;

	/* Parameters conversion */
	offset_parameter = strtoul(offset_str_param, &next, 0);
	if (next == offset_str_param) {
		LOG_INF("Parsing error");
		goto e_quit;
	}

	sign = strtoul(sign_str_param, &next, 0);
	if (next == sign_str_param) {
		LOG_INF("Parsing error");
		goto e_quit;
	}

	/* Parameters verification */
	if (offset_parameter > 4) {
		LOG_INF("Parameter error");
		LOG_ERR("Invalid offset ---> expected [offset 0 to 4] received (%u)", (unsigned int) offset_parameter);
		goto e_quit;
	}

	if (sign > 1) {
		LOG_INF("Parameter error");
		LOG_ERR("Invalid sing ---> expected [sign 0(negative) to 1(positive)] received (%u)", (unsigned int) sign);
		goto e_quit;
	}

	void *p;
	int32_t ret;

	if (!sign) {
		p = &buf64b[offset_parameter] + 4;
	} else {
		p = &buf64b[offset_parameter] - 4;
	}

	/* Command acknowledgment */
	LOG_INF("ASM-LW @ offset: %s%d", sign == 0 ? "-" : "", (int) offset_parameter);

	/* Execution */
	ret = fptr(p, sign);

	/* Command result */
	LOG_INF("ASM-LW @ offset %p - returned: %08x", p, (unsigned int) ret);

	/* Return */
	*((int32_t *)buffer) = ret;
	*_buflen = sizeof(int32_t);
	return NO_ERROR;

e_quit:
	LOG_INF("Operation failed");
	*buffer = '\0';
	*_buflen = 0;
	return -ERROR;
}

/**
 * @brief Assembly Store Command Execution
 *
 * Store command using assembly functions:
 *     Input expected:
 *	   Parameter offset range 0 to 4.
 *     Returns:
 *	   Buffer returns value loaded string format.
 *	   Bufferlen return length from buffer string.
 *
 * @param[in] argp Following arguments from cmd.
 * @param[in] argc Number of arguments from cmd.
 * @param[in]  _buflen Length of buffer.
 *
 * @return NO_ERROR or -ERROR
 */
static uint32_t process_asm_store_command(uint8_t *argp, uint32_t argc, size_t *_buflen,
					  void (*fptr)(void *addr, uint32_t data, uint32_t sign))
{
	(void)argc;

	/* Parameters collection */
	uint32_t parameter_size = argl_init(&argp);
	char *offset_str_param = (char *)argp;
	parameter_size = argl_next(&argp, parameter_size);
	char *sign_str_param = (char *)argp;
	parameter_size = argl_next(&argp, parameter_size);
	char *data_str_param = (char *)argp;


	/* Parameters conversion */
	uint32_t sign;
	char *next;
	uint32_t offset_parameter;
	uint32_t data_parameter;

	offset_parameter = strtoul(offset_str_param, &next, 0);
	if (next == offset_str_param) {
		LOG_INF("Parsing error");
		goto e_quit;
	}

	sign = strtoul(sign_str_param, &next, 0);
	if (next == sign_str_param) {
		LOG_INF("Parsing error");
		goto e_quit;
	}

	data_parameter = strtoul(data_str_param, &next, 0);
	if (next == data_str_param) {
		LOG_INF("Parsing error");
		goto e_quit;
	}

	/* Parameters verification */
	if (offset_parameter > 4) {
		LOG_INF("Parameter error");
		LOG_ERR("Invalid offset ---> expected [offset 0 to 4] received (%u)", (unsigned int)offset_parameter);
		goto e_quit;
	}

	if (sign > 1) {
		LOG_INF("Parameter error");
		LOG_ERR("Invalid sing ---> expected [offset sign 0 (-) to 1 (+)] received (%u)", (unsigned int) sign);
		goto e_quit;
	}

	void *p;

	if (!sign) {
		p = &buf64b[offset_parameter] + 4;
	} else {
		p = &buf64b[offset_parameter] - 4;
	}

	/* Command acknowledgment */
	LOG_INF("ASM-SW @ offset: %s%d with data: %08x", sign == 0 ? "-" : "",
		(unsigned int)offset_parameter, (unsigned int)data_parameter);

	/* Execution */
	fptr(p, data_parameter, sign);

	/* Command result */
	LOG_INF("ASM-SW @ offset %p - stored: %08x", p, *(unsigned int *) &buf64b[offset_parameter]);

	/* Return */
	*((int32_t *)buffer) = *(uint32_t *) &buf64b[offset_parameter];
	*_buflen = sizeof(int32_t);
	return NO_ERROR;

e_quit:
	LOG_INF("Operation failed");
	*buffer = '\0';
	*_buflen = 0;
	return -ERROR;
}

static int process_asm(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	uint32_t argl = argl_init(&argp);
	uint8_t *argp_next = argp + ((argl + 3) & ~3);

	if (argc > 4 || argc < 3) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		goto e_quit;
	}

	if (MATCH(argp, argl, "lw")) {
		return process_asm_load_command(argp_next, argc, _buflen, lw);
	} else if (MATCH(argp, argl, "lw_c")) {
		return process_asm_load_command(argp_next, argc, _buflen, lw_c);
	} else if (MATCH(argp, argl, "lwsp")) {
		return process_asm_load_command(argp_next, argc, _buflen, lwsp);
	} else if (MATCH(argp, argl, "lh")) {
		return process_asm_load_command(argp_next, argc, _buflen, lh);
	} else if (MATCH(argp, argl, "lhu")) {
		return process_asm_load_command(argp_next, argc, _buflen, lhu);
	} else if (MATCH(argp, argl, "sw")) {
		return process_asm_store_command(argp_next, argc, _buflen, sw);
	} else if (MATCH(argp, argl, "sw_c")) {
		return process_asm_store_command(argp_next, argc, _buflen, sw_c);
	} else if (MATCH(argp, argl, "swsp")) {
		return process_asm_store_command(argp_next, argc, _buflen, swsp);
	} else if (MATCH(argp, argl, "sh")) {
		return process_asm_store_command(argp_next, argc, _buflen, sh);
	} else {
		argp[argl] = '\0';
		*_buflen = 0;
		LOG_ERR("Invalid command ---> expected (lw|lw_c|lwsp|lh|lhu|sw|sw_c|sw_c|swsp|sh) received (%s)", (char *) argp);
		return -EINVAL;
	}

e_quit:
	LOG_ERR("Invalid command ---> %s", argp);
	*_buflen = 0;
	return -EINVAL;
}

/**
 * @brief Memory Copy Performance Measurement
 *
 * Load word using assembly functions:
 *     Input expected:
 *	   Offsets for source and destination buffers.
 *     Returns:
 *	   Buffer returns cycles measured for operation.
 *	   Bufferlen return length from buffer string.
 *
 * @param[in] argp Following arguments from cmd.
 * @param[in] argc Number of arguments from cmd.
 * @param[in]  _buflen Length of buffer.
 *
 * @return NO_ERROR or -ERROR
 */
static uint32_t process_mem_copy(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	(void)argc;

	/* Parameters collection */
	uint32_t parameter_size = argl_init(&argp);
	char *str_offset_source = (char *)argp;

	/* Next parameter */
	parameter_size = argl_next(&argp, parameter_size);
	char *str_offset_destination = (char *)argp;

	/* Nest parameter */
	parameter_size = argl_next(&argp, parameter_size);
	char *str_loops = (char *)argp;

	/* Parameters conversion */
	char *next;
	uint32_t offset_source = strtoul(str_offset_source, &next, 0);
	if (next == str_offset_source) {
		LOG_INF("Parsing error");
		goto e_quit;
	}

	uint32_t offset_destination = strtoul(str_offset_destination, &next, 0);
	if (next == str_offset_destination) {
		LOG_INF("Parsing error");
		goto e_quit;
	}

	uint32_t loops = strtoul(str_loops, &next, 0);
	if (next == str_loops) {
		LOG_INF("Parsing error");
		goto e_quit;
	}

	if ((offset_source > 1) || (offset_destination > 1) || (loops > 10000)) {
		LOG_INF("Parameter value error");
		goto e_quit;
	}

	/* Execute command */
	uint64_t measured_cycles = cmrt_perf_ref();
	for(uint32_t i = 0; i < loops; i++) {
		copy32((volatile uint32_t *)((volatile uint8_t *)dummy1 + offset_source),
		       (volatile uint32_t *)((volatile uint8_t *)dummy2 + offset_destination),
		       DBUFSZ - 1);
	}
	measured_cycles = cmrt_perf_cycles(measured_cycles);

	/* Return values */
	*(uint64_t *)buffer = measured_cycles;
	*_buflen = sizeof(uint64_t);
	return NO_ERROR;

e_quit:
	LOG_INF("Operation failed");
	*buffer = '\0';
	*_buflen = 0;
	return -ERROR;
}

static int process_mem(uint8_t *argp, uint32_t argc, size_t *_buflen)
{
	if (argc != 4) {
		LOG_ERR("Error wrong number of parameters (%lu)", argc);
		goto e_quit;
	}

	uint32_t argl = argl_init(&argp);
	uint8_t *argp_next = argp + ((argl + 3) & ~3);

	if (MATCH(argp, argl, "copy")) {
		return process_mem_copy(argp_next, argc, _buflen);
	} else {
		argp[argl] = '\0';
		LOG_ERR("Invalid command ---> expected (copy) received (%s)", (char *) argp);
		*_buflen = 0;
		return -EINVAL;
	}

e_quit:
	LOG_ERR("Invalid command ---> %s", argp);
	*_buflen = 0;
	return -EINVAL;
}

static int process_message(uint8_t *buffer, size_t *_buflen)
{
	if (*_buflen < 3) {
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

	/* Select operations */
	if (MATCH(argp, argl, "buffer")) {
		return process_buffer(argp_next, argc, _buflen);
	} else if (MATCH(argp, argl, "asm")) {
		return process_asm(argp_next, argc, _buflen);
	} else if (MATCH(argp, argl, "mem")) {
		return process_mem(argp_next, argc, _buflen);
	} else {
		argp[argl] = '\0';
		LOG_ERR("Invalid command ---> expected (buffer|asm|mem) received (%s)", (char *) argp);
		return -EINVAL;
	}
}

static int main_loop(uint32_t flowid)
{
	/* Globals initialization */
	memset(buf64b, 0, BUF64BSZ);
	memset(dummy1, 0, DBUFSZ);
	memset(dummy2, 0, DBUFSZ);
	memset(buffer, 0, BUFSZ);

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
