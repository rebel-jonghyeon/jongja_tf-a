/* test_otp*/

#include <string.h>
#include <otp.h>
#include <drivers/cmrt/sac.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/cmrt.h>
#include "test_otp.h"
#include <drivers/watchdog.h>

uint32_t origin_table[32];
uint32_t target_table[32];
const struct device *wdt;

typedef struct {
	uint32_t omc_offset;
	uint32_t offset_byte_length;
	uint32_t bank;			/*Physical OTP Bank location for OMC_OFFSET*/
	uint32_t bit_offset;	/*Physical OTP bit location for OMC_OFFSET*/
	char *otp_label;
	char *omc_offset_name;
} cmrt_otp_offset_map;

//#define ESW_TEST_ENABLE

#define OMC_OFFSET_CNT (14)
cmrt_otp_offset_map cmrt_otp_offset[14] = {
	{OTP_LIFECYCLE_OFFSET, OTP_LIFECYCLE_SIZE, 0, 0, "OTP_TOP_S0", "lifecycle"},
	{OTP_TDV_OFFSET, OTP_TDV_SIZE, 0, 32, "OTP_TOP_S0", "test_and_debug_vector"},
	{OTP_STATUS_WORD_OFFSET, OTP_STATUS_WORD_SIZE, 0, 160, "OTP_TOP_S0",
	 "status_word"},
	{OTP_KEY_OBLITERATE_OFFSET, OTP_KEY_OBLITERATE_SIZE, 0, 192, "OTP_TOP_S0",
	 "obliterate_sutatus_word"},
	{OTP_DEVICE_ID_OFFSET, OTP_DEVICE_ID_SIZE, 0, 288, "OTP_TOP_S0",
	 "device_id"},
	{OTP_OEM_ID_OFFSET, OTP_OEM_ID_SIZE, 0, 384, "OTP_TOP_S0", "oem_id"},
	{OTP_ROOT_OFFSET(0), OTP_ROOT_SIZE, 2, 448, "OTP_TOP_S0", "root_0_id"},
	{OTP_ROOT_OFFSET(1), OTP_ROOT_SIZE, 2, 896, "OTP_TOP_S0", "root_1_id"},
	{OTP_ROOT_OFFSET(2), OTP_ROOT_SIZE, 3, 320, "OTP_TOP_S0", "root_2_id"},
	{OTP_ROOT_OFFSET(3), OTP_ROOT_SIZE, 3, 768, "OTP_TOP_S0", "root_3_id"},
	{OTP_ROOT_OFFSET(4), OTP_ROOT_SIZE, 4, 192, "OTP_TOP_S0", "root_4_id"},
	{OTP_ROOT_OFFSET(5), OTP_ROOT_SIZE, 4, 640, "OTP_TOP_S0", "root_5_id"},
	{OTP_ROOT_OFFSET(6), OTP_ROOT_SIZE, 5, 64, "OTP_TOP_S0", "root_6_id"},
	{OTP_ROOT_OFFSET(7), OTP_ROOT_SIZE, 5, 512, "OTP_TOP_S0", "root_7_id"},
};

LOG_MODULE_DECLARE(test_otp, CONFIG_CMRT_LOG_LEVEL);

/******************************************************************************
 *  Private Functions Code For Test
 ******************************************************************************/
void init_table(uint32_t *data, uint32_t cnt, uint32_t value)
{
	for (uint32_t i = 0 ; i < cnt; i++)
		data[i] = value;
}

void show_table(char *table_name, uint32_t *data, uint32_t cnt)
{
	LOG_INF(" - %s information", table_name);

	for (uint32_t i = 0 ; i < cnt; i++)
		LOG_INF(" -- data[%d]:0x%x", i, data[i]);

}

uint32_t compare_table(uint32_t *source_data, uint32_t *target_data,
					   uint32_t compare_size)
{
	uint32_t cnt;

	for (cnt = 0 ; cnt < compare_size / WORD_SIZE_4; cnt++) {

		if (source_data[cnt] != target_data[cnt]) {
			show_table("parity_data", source_data, compare_size / WORD_SIZE_4);
			show_table("otp_parity_data", target_data,
					   compare_size / WORD_SIZE_4);
			return 0xff;
		}
	}

	return 0;
}

uint32_t ecc_cal(uint32_t worddata)
{
	const uint32_t ecc_mask[] = {0x56AAAD5B, 0x9B33366D, 0xE3C3C78E, 0x03FC07F0,
								 0x03FFF800, 0xFC000000, 0xFFFFFFFF};
	uint32_t ecc_val = 0;
	uint32_t temp_p6 = 0;
	uint32_t i, j, tempdata, temp_ecc_val;

	for (j = 0; j < 7; j++) {
		tempdata = worddata & ecc_mask[j];
		temp_ecc_val = 0;

		for (i = 0; i < 32; i++) {
			temp_ecc_val += tempdata & 0x1;
			tempdata >>= 1;
		}

		temp_p6 += temp_ecc_val & 0x1;

		if (j < 6)
			ecc_val |= (temp_ecc_val & 0x1) << j;
		else
			ecc_val |= (temp_p6 & 0x1) << j;
	}

	return ecc_val;
}

void make_parity_table(uint32_t *input_data,
					   uint32_t *output_data, uint32_t data_length)
{
	uint32_t cnt, i;
	uint32_t val;
	uint32_t parity;

	for (cnt = 0; cnt < (data_length / 4); cnt++) {

		parity = 0;

		for (i = 0; i < 4; i++) {
			val = ecc_cal(input_data[cnt * 4 + i]);
			parity |= val << (8 * i);
		}

		output_data[cnt] = parity;
	}
}

uint32_t make_corrupt_data(uint32_t input_data,
						   uint32_t corrupt_bit_no, uint32_t *output_data)
{
	int i;
	int corrupt_bit_cnt = 0;
	int empty_bit;
	uint32_t target_data;
	uint32_t result = 0xff;

	target_data = input_data;
	for (i = 0; i < 32; i++) {
		empty_bit = (0x1 << i);
		if (~target_data & empty_bit) {
			target_data |= empty_bit;
			corrupt_bit_cnt++;
		}

		if (corrupt_bit_cnt >= corrupt_bit_no) {
			*output_data = target_data;
			result = 0;
			break;
		}
	}

	if (result)
		LOG_INF(" -- no corrupt data");

	return result;
}

uint32_t get_otp_mem_information(const char *label,
								 int *bank_num, int *aeessbile_bank_num)
{
	LOG_INF("%s", __func__);

	uint32_t result = 0xff;
	int tm_bank_cnt = 0;
	int type;
	const struct device *d = device_get_binding(label);
	otp_samsung_data *otp_data = d->data;

	for (int i = 0; i < otp_data->bank_num; i++) {
		type = otp_data->bank_type[i];
		if (type == SECURE_TYPE || type == NON_SECURE_TYPE) {
			tm_bank_cnt++;
		}
	}

	if (tm_bank_cnt == 0)
		result = 0xff;
	else
		result = 0;

	*aeessbile_bank_num = tm_bank_cnt;
	*bank_num = otp_data->bank_num;

	LOG_INF("OTP: %s", label);
	LOG_INF("OTP Total Bank num: %d", otp_data->bank_num);
	LOG_INF("OTP accessible bank num: %d", tm_bank_cnt);

	return result;
}

uint32_t get_bank_type(const char *label, int bank, uint32_t *type)
{
	uint32_t result = 0xff;
	const struct device *d = device_get_binding(label);
	otp_samsung_data *otp_data = d->data;

	if (bank < otp_data->bank_num) {
		*type = otp_data->bank_type[bank];
		result = 0;
	} else
		LOG_INF("the Bank[%d] is out of bank number[%d]  -----------------%s",
				bank, otp_data->bank_num, __func__);

	return result;
}

/******************************************************************************
 *  OTP Driver Code for Application
 ******************************************************************************/

uint32_t otp_get_device_info(const char *label)
{
	const struct device *d = device_get_binding(label);
	struct otp_driver_api *otp_api = (struct otp_driver_api *)d->api;
	uint32_t err = 0xff;

	if (!otp_api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d,  __func__);
	} else {

		err = otp_api->device_info(d);

		if (err)
			LOG_INF("error!![%d] --------------%s", err, __func__);
	}

	return err;
}

int otp_get_product_id(const char *label)
{
	const struct device *d = device_get_binding(label);
	struct otp_driver_api *otp_api = (struct otp_driver_api *)d->api;
	uint32_t id;
	uint32_t err = 0xff;

	if (!otp_api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d,  __func__);
	} else {
		err = otp_api->product_id(d, &id);

		if (err)
			LOG_INF("error!!\n%s", __func__);
		else
			LOG_INF("id: 0x%x ------------ %s", id, __func__);
	}
	return err;
}

uint32_t otp_read_data(const char *label, uint32_t bank,
					   uint32_t bit_offset,
					   uint32_t *data_32,
					   uint32_t byte_length)
{
	const struct device *d = device_get_binding(label);
	struct otp_driver_api *otp_api = (struct otp_driver_api *)d->api;
	uint32_t otp_bit_addr;
	uint32_t otp_read_length;
	uint32_t err = 0xff;

	if (!otp_api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d, __func__);
		return err;
	}

	/* bit_addr, length must keep 4byte aline */
	otp_bit_addr = (bit_offset / READ_32) * READ_32;
	otp_bit_addr += bank * BANK_SIZE_1024;

	if (byte_length < WORD_SIZE_4)
		otp_read_length = WORD_SIZE_4;
	else
		otp_read_length = (byte_length / WORD_SIZE_4) *  WORD_SIZE_4;

	/* read data */
	err = (otp_api->read_32(d, otp_bit_addr, data_32, otp_read_length));

	if (err) {
		LOG_INF("error!!%d %s", err, __func__);
	}

	return err;

}

int otp_read_data_parity(const char *label, uint32_t bank,
						 uint32_t bit_offset, uint32_t *data_32,
						 uint32_t byte_length)
{
	const struct device *d = device_get_binding(label);
	struct otp_driver_api *otp_api = (struct otp_driver_api *)d->api;
	uint32_t otp_bit_addr;
	uint32_t otp_read_length;
	uint32_t err = 0xff;

	if (!otp_api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d, __func__);
		return err;
	}

	/* bit_addr, length must keep 4byte aline */
	otp_bit_addr = (bit_offset / READ_32) * READ_32;
	otp_bit_addr += bank * BANK_SIZE_1024;

	if (byte_length < WORD_SIZE_4)
		otp_read_length = WORD_SIZE_4;
	else
		otp_read_length = (byte_length / WORD_SIZE_4) *  WORD_SIZE_4;

	/* read data */
	err = otp_api->read_32_parity(d, otp_bit_addr,
								  data_32, otp_read_length);

	if (err)
		LOG_INF("error!!%d %s", err, __func__);

	return err;
}

uint32_t otp_read_data_ecc(const char *label,
						   uint32_t bank,
						   uint32_t bit_offset,
						   uint32_t *data_32_ecc,
						   uint32_t byte_length)
{
	const struct device *d = device_get_binding(label);
	struct otp_driver_api *otp_api = (struct otp_driver_api *)d->api;
	uint32_t otp_bit_addr;
	uint32_t otp_read_length;
	uint32_t err = 0xff;

	if (!otp_api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d, __func__);
		return err;
	}

	/* bit_addr, length must keep 4byte aline */
	otp_bit_addr = (bit_offset / READ_32) * READ_32;
	otp_bit_addr += bank * BANK_SIZE_1024;

	if (byte_length < WORD_SIZE_4)
		otp_read_length = WORD_SIZE_4;
	else
		otp_read_length = (byte_length / WORD_SIZE_4) *  WORD_SIZE_4;

	/* read data */
	err = otp_api->read_32_ecc(d, otp_bit_addr,
							   data_32_ecc, otp_read_length);

	if (err)
		LOG_INF("error!!%d %s", err, __func__);

	return err;
}

uint32_t otp_read_data_omc(const char *label,
						   uint32_t byte_offset,
						   uint32_t *data_32_omc,
						   uint32_t byte_length)
{
	const struct device *d = device_get_binding(label);
	struct otp_driver_api *otp_api = (struct otp_driver_api *)d->api;
	uint32_t otp_read_length;
	uint32_t err = 0xff;

	if (!otp_api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d, __func__);
		return err;
	}

	if (byte_length < WORD_SIZE_4)
		otp_read_length = WORD_SIZE_4;
	else
		otp_read_length = (byte_length / WORD_SIZE_4) *  WORD_SIZE_4;

	/* read data */
	err = otp_api->read_32_omc(d, byte_offset,
							   data_32_omc, otp_read_length);

	if (err)
		LOG_INF("error!!%d %s", err, __func__);

	return err;
}

uint32_t otp_write_data_word(const char *label, uint32_t bank,
							 uint32_t bit_offset, uint32_t data)
{
	const struct device *d = device_get_binding(label);
	struct otp_driver_api *otp_api = (struct otp_driver_api *)d->api;
	uint32_t bit_addr;
	uint32_t ecc_enable = 1;
	uint32_t err = 0xff;

	if (!otp_api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d, __func__);
		return err;
	}

	/* bit_addr must keep 4 byte aline*/
	bit_addr = (bit_offset / WRITE_32) * WRITE_32;
	bit_addr += bank * BANK_SIZE_1024;

	/* write data */
	err = otp_api->write(d, bit_addr, &data, ecc_enable, WORD_SIZE_4 * BIT_8);

	if (err) {
		LOG_INF("bit_address[0x%x] ------------ %s\n", bit_addr, __func__);
		LOG_INF("error!!%d\n%s", err, __func__);
	}

	return err;
}

uint32_t otp_write_data_word_no_ecc(const char *label, uint32_t bank,
									uint32_t bit_offset, uint32_t data)
{
	const struct device *d = device_get_binding(label);
	struct otp_driver_api *otp_api = (struct otp_driver_api *)d->api;
	uint32_t bit_addr;
	uint32_t err = 0xff;
	uint32_t ecc_enable = 0;

	if (!otp_api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d, __func__);
		return err;
	}

	/* bit_addr must keep 4 byte aline*/
	bit_addr = (bit_offset / WRITE_32) * WRITE_32;
	bit_addr += bank * BANK_SIZE_1024;

	/* write data */
	err = otp_api->write(d, bit_addr, &data, ecc_enable, WORD_SIZE_4 * BIT_8);

	if (err) {
		LOG_INF("bit_address[0x%x] ------------ %s\n", bit_addr, __func__);
		LOG_INF("error!!%d\n%s", err, __func__);
	}

	return err;
}

/******************************************************************************
 *  OTP Test Code
 ******************************************************************************/
uint32_t test_otp_device_info(void)
{
	uint32_t result = 0;

	result |= otp_get_device_info("OTP_SOC");
	result |= otp_get_device_info("OTP_CPU");
	result |= otp_get_device_info("OTP_TOP_S0");
	result |= otp_get_device_info("OTP_TOP_S1");
	result |= otp_get_device_info("OTP_TOP_S2");

	return result;
}

uint32_t test_otp_write_word(const char *label, int bank,
							 int offset, uint32_t write_data)
{
	uint32_t read_data = 0;
	uint32_t result = 0xff;

	/* write a pattern data to otp memory*/
	if (otp_write_data_word(label, bank, offset, write_data))
		return result;
/* compare a pattern data with otp memory*/
	if (otp_read_data(label, bank, offset, &read_data, WORD_SIZE_4))
		return result;

	if (read_data != write_data) {
		LOG_INF("--- [0x%x][0x%x](Fail)",
				write_data, read_data);
	} else {
		LOG_INF("--- [0x%x][0x%x](Pass))",
				write_data, read_data);
		result = 0;
	}

	return result;
}

// - Read all banks of nonsecure OTP memory in 4-byte units and if it is empty,
//   write the pre-set write pattern to the OTP memory and read it again
//   to compare with the pattern
uint32_t test_otp_rw_nonsecure_memory(const char *label)
{
	int bank;
	uint32_t type;
	uint32_t bit_offset;
	uint32_t read_data;
	uint32_t write_data;
	uint32_t write_pattern[2] = {0xAA55AA55, 0x55AA55AA};
	int error;
	int pass_cnt;
	int bank_num;
	int accessible_bank_cnt;
	int otp_rw_test_cnt;
	uint32_t result = 0xff;

	LOG_INF("OTP R/W NON_SECURE M TEST(START)");

	if (otp_get_product_id(label) == 0) {

		get_otp_mem_information(label, &bank_num, &accessible_bank_cnt);
		pass_cnt = 0;
		error = 0;
		read_data = 0;
		write_data = 0;
		otp_rw_test_cnt = 0;

		for (bank = 0; bank < bank_num; bank++) {

			LOG_INF("Bank[%d]", bank);
			if (get_bank_type(label, bank, &type))
				break;

			if (type == HARDWARE_TYPE || type == OTPC_NOT_USED) {
				LOG_INF("Bank[%d]: N/A", bank);
				continue;
			}
			/* 4byte(32bit) unit  read/write test */
			for (int offset = 0; offset < 32; offset++) {

				(void)wdt_feed(wdt, 0);

				bit_offset = offset * READ_32;
				/* read 4byte of bank */
				if (otp_read_data(label, bank, bit_offset,
								  &read_data, WORD_SIZE_4)) {
					result = 0xff;
					break;
				} else {
					/* check 32byte of otp memory is empty*/
					if (read_data == 0) {
						/* set a pattern data*/
						write_data = write_pattern[offset % 2];

						LOG_INF("-- offset[%d]", offset);
						/* write a pattern data to otp memory*/
						if (test_otp_write_word(label, bank,
												bit_offset, write_data)) {
							result = 0xff;
							error++;
							break;
						} else {
							otp_rw_test_cnt++;
							result = 0;
						}

					} else
						LOG_INF("-- offset[%d](N/A):", offset);
				}
			}

			if (result)
				break;
		}

		LOG_INF("OTP R/W NO_SECURE M TEST(END)");
		if (result)
			LOG_INF("---- [FAIL]");
		else {
			if (otp_rw_test_cnt == 0)
				LOG_INF("---- [NO TEST OPERATION]");
			else
				LOG_INF("---- [PASS]");
		}
	}

	return result;
}

uint32_t test_otp_r_secure_memory(char *label)
{
	uint32_t bank;
	uint32_t read_data[32];
	uint32_t read_parity_data[8];
	uint32_t parity_data[8];

	int bank_num;
	int accessible_bank_cnt;
	uint32_t result = 0xff;

	LOG_INF("OTP READ SECURE TEST (S) ");

	if (otp_get_product_id(label) == 0) {

		get_otp_mem_information(label, &bank_num, &accessible_bank_cnt);

		for (bank = 0; bank < bank_num; bank++) {

			(void)wdt_feed(wdt, 0);

			init_table(&read_data[0], 32, 0);

			LOG_INF("Bank[%d]", bank);

			if (otp_read_data(label, bank, 0, &read_data[0], 128))
				break;

			if (otp_read_data_parity(label, bank,
									 0, &read_parity_data[0], 32))
				break;

			make_parity_table(read_data, &parity_data[0], 32);

			if (compare_table(parity_data, read_parity_data, 32))
				break;
		}

		LOG_INF("OTP READ SECURE TEST (E) ");

		if (bank == bank_num) {
			LOG_INF("---- PASS");
			result = 0;
		} else {
			LOG_INF("---- FAIL");
			result = 0xff;
		}
	}

	return result;

}

// This is a test to check if normal data can be read
// even if the data is damaged by 1 bit at a time in units of 4 bytes
// in the secure OTP memory area.
uint32_t test_otp_write_1bit_ecc(uint32_t omc_offset, uint32_t omc_byte_length,
								 uint32_t bank, uint32_t offset, char *label)
{
	uint32_t temp_data = 0xAA55AA00;
	uint32_t original_data;
	uint32_t otp_raw_data;
	uint32_t corrupt_data;
	uint32_t otp_omc_data[50];
	uint32_t pass_cnt = 0;
	uint32_t all_pass_cnt = 0;
	uint32_t bit_offset;
	uint32_t original_raw_data[50];
	uint32_t original_omc_data[50];
	uint32_t result = 0xff;

	init_table(&original_raw_data[0], 50, 0xaaaaaaaa);
	init_table(&original_omc_data[0], 50, 0xaaaaaaaa);

	if (otp_read_data(label, bank, offset,
					  &original_raw_data[0],
					  omc_byte_length))
		return result;

	if (otp_read_data_omc(label, omc_offset,
						  &original_omc_data[0],
						  omc_byte_length))
		return result;

	all_pass_cnt = omc_byte_length / 4;

	for (uint32_t cnt = 0 ; cnt < omc_byte_length / WORD_SIZE_4; cnt++) {
		original_data = original_raw_data[cnt];
		bit_offset = offset + (cnt * WORD_SIZE_4 * BIT_8);

		LOG_INF("****) test of otp_data[%d]", cnt);
		//OTP ECC write test, write data at OTP S0 or S1 and wrie perity to OTP S2
		//if otp memory is empty, write pattern(0xAA55AA55)and its parity to otp memory
		if (original_data == 0) {
			original_data = temp_data;
			/* write data and parity to otp memory */
			if (otp_write_data_word(label, bank,
									bit_offset, original_data))
				break;

			/* read omc data */
			init_table(&otp_omc_data[0], 50, 0xaaaaaaaa);

			if (otp_read_data_omc(label, omc_offset,
								  original_omc_data,
								  omc_byte_length))
				break;

		}
		/* OTP 1bit error corection test */
		if (make_corrupt_data(original_data, 1, &corrupt_data)) {
			pass_cnt++;
		} else {

			(void)wdt_feed(wdt, 0);
			/* write target data with on parity*/
			if (otp_write_data_word_no_ecc(label, bank,
										   bit_offset, corrupt_data))
				break;
			/* read raw data */
			if (otp_read_data(label, bank, bit_offset,
							  &otp_raw_data, WORD_SIZE_4))
				break;

			/* read omc data */
			init_table(&otp_omc_data[0], 50, 0xaaaaaaaa);

			if (otp_read_data_omc(label, omc_offset,
								  &otp_omc_data[0],
								  omc_byte_length))
				break;

			LOG_INF("****) [test result]");
			LOG_INF("****) original omc data: 0x%x", original_omc_data[cnt]);
			LOG_INF("****) data by omc_con: 0x%x", otp_omc_data[cnt]);
			LOG_INF("****) --- must be same");
			LOG_INF("****) corrupt data: 0x%x(0x%x)", corrupt_data,
					original_raw_data[cnt]);
			LOG_INF("****) data by otp_con: 0x%x", otp_raw_data);
			LOG_INF("****) --- must be same");
			/* compare raw data with target data*/
			if (otp_raw_data != corrupt_data ||
				otp_omc_data[cnt] != original_omc_data[cnt]) {
				LOG_INF("****) Test Fail!!!");
			} else {
				LOG_INF("****) Test pass!!!");
				pass_cnt++;
			}
		}
	}

	if (all_pass_cnt == pass_cnt)
		result = 0;

	return result;
}

uint32_t test_otp_write_2bit_ecc(uint32_t omc_offset, uint32_t omc_byte_length,
								 uint32_t bank, uint32_t offset, char *label)
{
	uint32_t original_data;
	uint32_t corrupt_data;
	uint32_t otp_omc_data[50];
	uint32_t pass_cnt = 0;
	uint32_t all_pass_cnt = 0;
	uint32_t bit_offset;
	uint32_t original_raw_data[50];
	uint32_t result = 0xff;

	init_table(&original_raw_data[0], 50, 0xaaaaaaaa);

	if (otp_read_data(label, bank, offset,
					  &original_raw_data[0], omc_byte_length))
		return result;

	all_pass_cnt = omc_byte_length / 4;

	for (uint32_t cnt = 0 ; cnt < omc_byte_length / WORD_SIZE_4; cnt++) {
		original_data = original_raw_data[cnt];
		bit_offset = offset + (cnt * WORD_SIZE_4 * BIT_8);

		LOG_INF("****) test of otp_data[%d]", cnt);

		if (make_corrupt_data(original_data, 1, &corrupt_data)) {
			pass_cnt++;
		} else {

			(void)wdt_feed(wdt, 0);
			/* write target data */
			if (otp_write_data_word_no_ecc(label, bank,
										   bit_offset, corrupt_data))
				break;

			/* read omc data */
			init_table(&otp_omc_data[0], 50, 0xaaaaaaaa);
			if (otp_read_data_omc(label, omc_offset,
								  &otp_omc_data[0],
								  omc_byte_length)) {
				LOG_INF("****) Test pass!!!");
				pass_cnt++;
			} else {
				LOG_INF("****) Test fail!!!");

			}
		}
	}

	if (all_pass_cnt == pass_cnt)
		result = 0;

	return result;
}

uint32_t test_otp_rw_secure_mem_1bit_corruption(void)
{
	int offset_cnt;
	int32_t omc_offset;
	uint32_t omc_byte_length;
	uint32_t bank;
	uint32_t bit_offset;
	uint32_t fail_cnt = 0;
	char *label;
	char *offset_name;
	uint32_t result = 0xff;

	LOG_INF("OTP R/W SECURE M TEST(START)");
	LOG_INF("1 BIT CORRUPTION TEST");

	for (offset_cnt = 0; offset_cnt < OMC_OFFSET_CNT; offset_cnt++) {
		/* store variable */
		omc_offset = cmrt_otp_offset[offset_cnt].omc_offset;
		omc_byte_length = cmrt_otp_offset[offset_cnt].offset_byte_length;
		bank = cmrt_otp_offset[offset_cnt].bank;
		bit_offset = cmrt_otp_offset[offset_cnt].bit_offset;
		label = cmrt_otp_offset[offset_cnt].otp_label;
		offset_name = cmrt_otp_offset[offset_cnt].omc_offset_name;

		LOG_INF("WRITE ECC TEST [%s]", offset_name);

		if (!(test_otp_write_1bit_ecc(omc_offset, omc_byte_length,
									  bank, bit_offset, label))) {
			LOG_INF("WRITE ECC TEST [%s] -- PASS", offset_name);
		} else {
			LOG_INF("WRITE ECC TEST [%s] -- FAIL", offset_name);
			fail_cnt++;
		}
		LOG_INF("");
	}

#ifdef ESW_TEST_ENABLE
	uint32_t esw_length = (16383 - OTP_ESW_OFFSET) / 4;

	for (offset_cnt = 0; offset_cnt < esw_length; offset_cnt++) {
		omc_offset = OTP_ESW_OFFSET + (offset_cnt * 4);
		omc_byte_length = 4;
		bank = omc_offset / 128;
		label = "OTP_TOP_S0";

		if (bank > 63) {
			bank = bank - 63;
			label = "OTP_TOP_S1";
		}
		bit_offset = (omc_offset - (bank * 128)) * 8;
		offset_name = "ESW";

		LOG_INF("WRITE ECC TEST [%s]", offset_name);

		if (!(test_otp_write_1bit_ecc(omc_offset, omc_byte_length,
									  bank, bit_offset, label))) {
			LOG_INF("WRITE ECC TEST [%s][0x%x] -- PASS", offset_name, omc_offset);
		} else {
			LOG_INF("WRITE ECC TEST [%s][0x%x] -- FAIL", offset_name, omc_offset);
			fail_cnt++;
		}
		LOG_INF("");
	}
#endif

	if (fail_cnt) {
		LOG_INF("OTP R/W SECURE M TEST(END) ---- [FAIL]");
	} else {
		result = 0;
		LOG_INF("OTP R/W SECURE M TEST(END) ---- [PASS]");
	}
	LOG_INF("");

	return result;
}

uint32_t test_otp_rw_secure_mem_2bit_corruption(void)
{
	int offset_cnt;
	int32_t omc_offset;
	uint32_t omc_byte_length;
	uint32_t bank;
	uint32_t bit_offset;
	uint32_t fail_cnt = 0;
	char *label;
	char *offset_name;
	uint32_t result = 0xff;

	LOG_INF("OTP R/W SECURE M TEST(START)");
	LOG_INF("2 BIT CORRUTION TEST");

	for (offset_cnt = 0; offset_cnt < OMC_OFFSET_CNT; offset_cnt++) {
		/* store variable */
		omc_offset = cmrt_otp_offset[offset_cnt].omc_offset;
		omc_byte_length = cmrt_otp_offset[offset_cnt].offset_byte_length;
		bank = cmrt_otp_offset[offset_cnt].bank;
		bit_offset = cmrt_otp_offset[offset_cnt].bit_offset;
		label = cmrt_otp_offset[offset_cnt].otp_label;
		offset_name = cmrt_otp_offset[offset_cnt].omc_offset_name;

		LOG_INF("WRITE ECC TEST [%s]", offset_name);

		if (!(test_otp_write_2bit_ecc(omc_offset, omc_byte_length,
									  bank, bit_offset, label))) {
			LOG_INF("WRITE ECC TEST [%s] -- PASS", offset_name);
		} else {
			LOG_INF("WRITE ECC TEST [%s] -- FAIL", offset_name);
			fail_cnt++;
		}
		LOG_INF("");
	}

	if (fail_cnt) {
		LOG_INF("OTP R/W SECURE M TEST(END) ---- [FAIL]");
	} else {
		result = 0;
		LOG_INF("OTP R/W SECURE M TEST(END) ---- [PASS]");
	}
	LOG_INF("");

	return result;
}

uint32_t test_otp_main(void)
{
	uint32_t result = 0;

	wdt = device_get_binding(DT_LABEL(DT_ALIAS(watchdog0)));
	if (!wdt)
		return 1;

	LOG_INF("OTP ALL TEST START");

	/* nonsecure otp memory read / write test */
	result |= test_otp_rw_nonsecure_memory("OTP_SOC");
	result |= test_otp_rw_nonsecure_memory("OTP_CPU");

	/* secure otp memory read / write test */
	result |= test_otp_rw_secure_mem_1bit_corruption();
	result |= test_otp_rw_secure_mem_2bit_corruption();

	if (result)
		LOG_INF("OTP ALL TEST END ----------[FAIL]");
	else
		LOG_INF("OTP ALL TEST END ----------[PASS]");

	LOG_INF("OTP ALL TEST DONE !!!!");

	return result;
}
