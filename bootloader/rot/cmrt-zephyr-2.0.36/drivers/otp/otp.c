/*
 * copyright (c) 2021, samsung foundry *
 * spdx-license-identifier: apache-2.0
 */
#define DT_DRV_COMPAT samsung_otp

#include <errno.h>
#include <device.h>
#include <soc.h>
#include <drivers/cmrt/sac.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/cmrt.h>
#include <rebel_h.h>
#include "otp.h"

#define LOG_DOMAIN dev_otp
#define LOG_LEVEL CONFIG_OTP_LOG_LEVEL

//#define SILICON_ONLY /*in case for silocon */

#define PVT_ROT_SFR	0x1FF026000C
#define PVT0_CTRL_DCL0_SFR	0x1FF212000C
#define PVT1_CTRL_DCL0_SFR	0x1FF213000C
#define PVT0_CTRL_DCL1_SFR	0x1FF292000C
#define PVT1_CTRL_DCL1_SFR	0x1FF293000C

#include <logging/log.h>
LOG_MODULE_REGISTER(LOG_DOMAIN);

/*******************************************************************************
 * Private Functions Code
 ******************************************************************************/
static bool check_null_pointer(uint32_t *addr)
{
	if (!addr)
		return false;
	else
		return true;
}

static void set_pvt_disable(uint32_t *pvt_control_reg)
{
	uint32_t reg;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT_ROT_SFR));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(PVT_ROT_SFR));
	pvt_control_reg[0] = reg;
	cmrt_sac_write32(0, GET_SAC_OFFSET(PVT_ROT_SFR));
#ifdef SILICON_ONLY
	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT0_CTRL_DCL0_SFR));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(PVT0_CTRL_DCL0_SFR));
	pvt_control_reg[1] = reg
	cmrt_sac_write32(0, GET_SAC_OFFSET(PVT0_CTRL_DCL0_SFR));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT1_CTRL_DCL0_SFR));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(PVT1_CTRL_DCL0_SFR));
	pvt_control_reg[2] = reg;
	cmrt_sac_write32(0, GET_SAC_OFFSET(PVT1_CTRL_DCL0_SFR));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT0_CTRL_DCL1_SFR));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(PVT0_CTRL_DCL1_SFR));
	pvt_control_reg[3] = reg;
	cmrt_sac_write32(0, GET_SAC_OFFSET(PVT0_CTRL_DCL1_SFR));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT1_CTRL_DCL1_SFR));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(PVT1_CTRL_DCL1_SFR));
	pvt_control_reg[4] = reg;
	cmrt_sac_write32(0, GET_SAC_OFFSET(PVT1_CTRL_DCL1_SFR));
#endif
}

static void set_pvt_restore(uint32_t *pvt_control_reg)
{

	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT_ROT_SFR));
	cmrt_sac_write32(pvt_control_reg[0], GET_SAC_OFFSET(PVT_ROT_SFR));
#ifdef SILICON_ONLY
	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT0_CTRL_DCL0_SFR));
	cmrt_sac_write32(pvt_control_reg[1], GET_SAC_OFFSET(PVT0_CTRL_DCL0_SFR));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT1_CTRL_DCL0_SFR));
	cmrt_sac_write32(pvt_control_reg[2], GET_SAC_OFFSET(PVT1_CTRL_DCL0_SFR));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT0_CTRL_DCL1_SFR));
	cmrt_sac_write32(pvt_control_reg[3], GET_SAC_OFFSET(PVT0_CTRL_DCL1_SFR));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(PVT1_CTRL_DCL1_SFR));
	cmrt_sac_write32(pvt_control_reg[4], GET_SAC_OFFSETi(PVT1_CTRL_DCL1_SFR));
#endif
}

static uint32_t otp_cmd_init(uint64_t base_addr)
{
	uint32_t reg = 0;
	uint32_t cnt = 0;
	uint32_t err = NO_FAIL;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONTROL));
	cmrt_sac_write32(0x0, GET_SAC_OFFSET(base_addr + CON_CONTROL));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
	cmrt_sac_write32(reg, GET_SAC_OFFSET(base_addr + INT_STATUS));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONTROL));
	cmrt_sac_write32(MASK_INITCMD, GET_SAC_OFFSET(base_addr + CON_CONTROL));

	while (true) {

		cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
		if ((cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS)) &
							 MASK_INITDONE) == MASK_INITDONE) {
			break;
		}

		if (++cnt > TIMEOUT_REPEAT_MAX) {
			LOG_INF("[%s] time out fail", __func__);
			err = INIT_FAIL;
			break;
		}
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
	cmrt_sac_write32(reg | MASK_INITDONE,
					 GET_SAC_OFFSET(base_addr + INT_STATUS));
	return err;
}

static uint32_t otp_cmd_standby(uint64_t base_addr)
{
	uint32_t reg = 0;
	uint32_t cnt = 0;
	uint32_t err = NO_FAIL;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONTROL));
	cmrt_sac_write32(0x0, GET_SAC_OFFSET(base_addr + CON_CONTROL));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
	cmrt_sac_write32(reg, GET_SAC_OFFSET(base_addr + INT_STATUS));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONTROL));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + CON_CONTROL));
	cmrt_sac_write32((reg & ~MASK_STANDBYCMD) | MASK_STANDBYCMD,
					 GET_SAC_OFFSET(base_addr + CON_CONTROL));

	while (true) {
		cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
		if ((cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS))
			& MASK_STANDBYCMD) == MASK_STANDBYCMD) {
			break;
		}

		if (++cnt > TIMEOUT_REPEAT_MAX) {
			LOG_INF("[%s] time out fail", __func__);
			err = STANDBY_FAIL;
			break;
		}
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
	cmrt_sac_write32(reg | MASK_STANDBYCMD,
					 GET_SAC_OFFSET(base_addr + INT_STATUS));
	return err;
}

static uint32_t otp_cmd_pre_reading(uint64_t base_addr)
{
	uint32_t reg = 0;
	uint32_t cnt1 = 0;
	uint32_t cnt2 = 0;
	uint32_t err = NO_FAIL;

	while (true) {
		cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONFIG));
		reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + CON_CONFIG));
		cmrt_sac_write32((reg & ~MASK_SW_PREREADING) | MASK_SW_PREREADING,
						 GET_SAC_OFFSET(base_addr + CON_CONFIG));

		cnt1 = 0;
		while (true) {
			reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + CON_CONFIG));
			if ((reg & MASK_SW_PREREADING) != MASK_SW_PREREADING) {
				break;
			}

			if (++cnt1 > TIMEOUT_REPEAT_MAX) {
				LOG_INF("[%s] sw_prerdading time out fail", __func__);
				err = PRE_READING_FAIL;
				break;
			}
		}

		if (err)
			break;

		cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
		reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
		if ((reg & MASK_PREREADINGDONE) == MASK_PREREADINGDONE) {
			break;
		}

		if (++cnt2 > TIMEOUT_REPEAT_MAX) {
			LOG_INF("[%s] prereading done time out fail", __func__);
			err = PRE_READING_FAIL;
			break;
		}
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
	cmrt_sac_write32(reg | MASK_PREREADINGDONE,
					 GET_SAC_OFFSET(base_addr + INT_STATUS));
	return err;
}

static uint32_t otp_cmd_read(uint64_t base_addr, uint32_t bit_addr,
							 uint32_t bank_type, uint32_t *err)
{
	uint32_t reg = 0;
	uint32_t cnt = 0;
	uint32_t read_data = 0;

	if (check_null_pointer(err) == false) {
		return NULL_POINTER;
	}

	*err = NO_FAIL;
	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + IF));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + IF));
	reg = bit_addr & MASK_IF_ADDR;
	cmrt_sac_write32(reg, GET_SAC_OFFSET(base_addr + IF));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONTROL));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + CON_CONTROL));
	cmrt_sac_write32((reg & ~MASK_READCMD) | MASK_READCMD,
					 GET_SAC_OFFSET(base_addr + CON_CONTROL));

	while (true) {
		cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
		reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
		if ((reg & MASK_READDONE) == MASK_READDONE) {
			break;
		}

		if ((reg & MASK_SECUREFAIL) == MASK_SECUREFAIL) {
			*err = SECURE_FAIL;
			LOG_INF("[%s] read secure_fail 0x%x\n", __func__, reg);
			break;
		}

		if (++cnt > TIMEOUT_REPEAT_MAX) {
			*err = TIME_OUT;
			LOG_INF("[%s] time out fail %x\n", __func__, reg);
			break;
		}
	}

	if (*err == NO_FAIL) {
		reg = bit_addr >> SHIFT_BANK_SIZE_1024;
		switch (bank_type) {
		case NON_SECURE_TYPE:
			cmrt_sac_set_base(NULL,
							  GET_SAC_BASE(base_addr + NONSECURE_READ_DATA));
			read_data = cmrt_sac_read32(GET_SAC_OFFSET(base_addr +
										 NONSECURE_READ_DATA));
			break;
		case SECURE_TYPE:
			cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + SECURE_READ_DATA));
			read_data = cmrt_sac_read32(GET_SAC_OFFSET(base_addr +
										 SECURE_READ_DATA));
			break;
		case HARDWARE_TYPE:
		case OTPC_NOT_USED:
		default:
			LOG_INF("[%s] bank type %d\n", __func__, bank_type);
			*err = UNACCESSIBLE_REGION;
			break;
		}
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
	cmrt_sac_write32(reg | MASK_READDONE,
					 GET_SAC_OFFSET(base_addr + INT_STATUS));

	return read_data;
}

static uint32_t otp_cmd_program(uint64_t base_addr, uint32_t bit_addr,
								uint32_t data, uint32_t bank_type)
{
	uint32_t reg = 0;
	uint32_t cnt = 0;
	uint32_t err = NO_FAIL;
	uint32_t while_done = 0;

	switch (bank_type) {
	case NON_SECURE_TYPE:
	case SECURE_TYPE:
		break;
	case HARDWARE_TYPE:
	case OTPC_NOT_USED:
	default:
		LOG_INF("[%s] bank type %d\n", __func__, bank_type);
		return UNACCESSIBLE_REGION;
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONTROL));
	cmrt_sac_write32(0x0, GET_SAC_OFFSET(base_addr + CON_CONTROL));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
	cmrt_sac_write32(reg, GET_SAC_OFFSET(base_addr + INT_STATUS));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONFIG));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + CON_CONFIG));
	reg = (reg & ~MASK_RESPONSECON) | MASK_RESPONSECON_NONSEC;
	cmrt_sac_write32(reg, GET_SAC_OFFSET(base_addr + CON_CONFIG));

	reg = (bit_addr & MASK_IF_ADDR) | ((data & 0x1) << BIT_LOC_IF_PROGRAMDATA);
	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + IF));
	cmrt_sac_write32(reg, GET_SAC_OFFSET(base_addr + IF));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONTROL));
	cmrt_sac_write32(MASK_PROGRAMCMD, GET_SAC_OFFSET(base_addr + CON_CONTROL));

	while_done = 0;
	while (true) {

		cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + CON_CONTROL));
		reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));

		switch (reg & MASK_PROGRAM_STATUS)	{
		case MASK_PROGRAMDONE:
			while_done = 1;
			break;

		case MASK_PROGRAMFAIL:
			err = PROGRAM_FAIL;
			LOG_INF("[%s] fail %x\n", __func__, err);
			while_done = 1;
			break;

		case MASK_SECUREFAIL:
			err = SECURE_FAIL;
			LOG_INF("[%s] fail %x\n", __func__, err);
			while_done = 1;
			break;

		case MASK_PROGRAMLOCK:
			err = PROGRAM_LOCK;
			LOG_INF("[%s] fail %x\n", __func__, err);
			while_done = 1;
			break;
		default:
			break;
		}

		if (++cnt > TIMEOUT_REPEAT_MAX) {
			err = TIME_OUT;
			LOG_INF("[%s] fail %x\n", __func__, err);
			while_done = 1;
			break;
		}

		if (while_done)
			break;

	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base_addr + INT_STATUS));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(base_addr + INT_STATUS));
	cmrt_sac_write32(reg | (MASK_PROGRAMDONE | MASK_PROGRAMFAIL),
					 GET_SAC_OFFSET(base_addr + INT_STATUS));
	return err;
}

static uint32_t otp_program(uint64_t base_addr,
							uint32_t bit_start_addr,
							size_t bit_len,
							uint32_t *data,
							uint32_t *bank_type_data)
{
	uint32_t err = NO_FAIL;
	uint32_t idx = 0;
	uint32_t bit_idx = 0;
	uint32_t word_idx = 0;
	uint32_t bit_addr = 0;
	uint32_t bit_data = 0;
	uint32_t bank_sel = 0;
	uint32_t bank_type = 0;

	do {
		bit_idx = idx % WRITE_32;
		word_idx = idx / WRITE_32; /* same as bit_len >> SHIFT_BITLEN_5 */
		bit_addr = bit_start_addr + (word_idx * WRITE_32) + bit_idx;
		bit_data = (data[word_idx] >> bit_idx) & MASK_WRITE_1;
		bank_sel = bit_addr >> SHIFT_BANK_SIZE_1024;
		bank_type = bank_type_data[bank_sel];

		err = otp_cmd_program(base_addr,
							  bit_addr,
							  bit_data,
							  bank_type);
		if (err)
			break;

	} while (++idx < bit_len);

	return err;
}

static uint32_t otp_ecc_cal(uint32_t worddata)
{
	const uint32_t ecc_mask[] = {0x56AAAD5B, 0x9B33366D, 0xE3C3C78E, 0x03FC07F0,
								 0x03FFF800, 0xFC000000, 0xFFFFFFFF};

	uint32_t ecc_val;
	uint32_t i, j, tempdata, temp_ecc_val, temp_p6;

	ecc_val = 0;
	temp_p6 = 0;

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

static uint32_t otp_get_parity_addr(uint32_t bit_addr, uint32_t ecc_addr_offset,
									uint32_t *ecc_addr)
{
	if (ecc_addr_offset == 0xf) {
		return false;
	}

	*ecc_addr = (bit_addr >> 2) + (ecc_addr_offset * 0x4000);

	return true;

}

static void otp_ecc_enable(bool enable)
{
	uint32_t reg;
	uint64_t ecc_control_reg = OTP_ECC_CTRL;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(ecc_control_reg));
	reg = cmrt_sac_read32(GET_SAC_OFFSET(ecc_control_reg));

	if (enable)
		reg = reg & 0xfffffffe;
	else
		reg = reg | 0x1;

	cmrt_sac_write32(reg, GET_SAC_OFFSET(ecc_control_reg));
}

/*******************************************************************************
 * Public Functions Code
 ******************************************************************************/

static uint32_t samsung_otp_device_info(const struct device *dev)
{
	uint64_t sfr_base_addr;
	uint64_t sfr_parity_base_addr;
	uint64_t ecc_base_addr;
	uint32_t parity_addr_offset;
	uint32_t bank_num;
	uint32_t *bank_type;
	uint32_t *parity_bank_type;

	const otp_samsung_device_config *otp_device = dev->config;
	otp_samsung_data *otp_data = dev->data;

	if (check_null_pointer((uint32_t *)dev) == false) {
		return NULL_POINTER;
	}

	sfr_base_addr = otp_device->base;
	sfr_parity_base_addr = otp_device->ecc_parity_base;
	ecc_base_addr = otp_device->ecc_base;

	parity_addr_offset = otp_data->ecc_parity_addr_offset;
	bank_num = otp_data->bank_num;
	bank_type = otp_data->bank_type;
	parity_bank_type = otp_data->parity_bank_type;

	LOG_INF("function: %s", __func__);
	LOG_INF("otp sfr base address: 0x%llx", sfr_base_addr);
	LOG_INF("parity otp sfr base address: 0x%llx ", sfr_parity_base_addr);
	LOG_INF("data base address: 0x%llx ", ecc_base_addr);
	LOG_INF("parity otp rom address offset: 0x%x ", parity_addr_offset);
	LOG_INF("total bank number: 0x%x ", bank_num);

	for (int i = 0 ; i < bank_num; i++)
		LOG_INF("bank type[%d]: %d ", i, bank_type[i]);

	return NO_FAIL;
}

static uint32_t samsung_otp_product_id(const struct device *dev, uint32_t *id)
{
	uint64_t sfr_base_addr;
	const otp_samsung_device_config *otp_device = dev->config;

	if (check_null_pointer((uint32_t *)dev) == false) {
		return NULL_POINTER;
	}

	sfr_base_addr = otp_device->base;
	cmrt_sac_set_base(NULL, GET_SAC_BASE(sfr_base_addr + PRODUCT_ID));
	*id = cmrt_sac_read32(GET_SAC_OFFSET(sfr_base_addr + PRODUCT_ID));

	return NO_FAIL;
}

static uint32_t samsung_otp_read_32(const struct device *dev,
									uint32_t bit_addr,
									uint32_t *data_32,
									size_t byte_len)
{
	uint64_t sfr_base_addr;
	uint32_t cnt;
	uint32_t bank_sel;
	uint32_t err = NO_FAIL;
	const otp_samsung_device_config *otp_device = dev->config;
	otp_samsung_data *otp_data = dev->data;

	if (check_null_pointer((uint32_t *)dev) == false) {
		return NULL_POINTER;
	}
	if (check_null_pointer(data_32) == false) {
		return NULL_POINTER;
	}

	sfr_base_addr = otp_device->base;
	bit_addr = bit_addr & ~(0x1f);
	bank_sel = bit_addr >> SHIFT_BANK_SIZE_1024;

	err = otp_cmd_init(sfr_base_addr);

	if (err == NO_FAIL) {

		for (cnt = 0; cnt < (byte_len >> SHIFT_BYTE_LEN); cnt++) {

			data_32[cnt] =  otp_cmd_read(sfr_base_addr,
										 bit_addr + (cnt * READ_32),
										 otp_data->bank_type[bank_sel],
										 &err);

			if (err != NO_FAIL)
				break;
		}

		if (err == NO_FAIL)
			err = otp_cmd_standby(sfr_base_addr);
	}

	return err;
}

static uint32_t samsung_otp_read_32_parity(const struct device *dev,
										   uint32_t bit_addr,
										   uint32_t *data_32,
										   size_t byte_len)
{
	uint64_t sfr_parity_base_addr = 0;
	uint32_t ecc_parity_addr = 0;
	uint32_t cnt = 0;
	uint32_t bank_sel = 0;
	uint32_t err = NO_FAIL;
	const otp_samsung_device_config *otp_device = dev->config;
	otp_samsung_data *otp_data = dev->data;

	if (check_null_pointer((uint32_t *)dev) == false) {
		return NULL_POINTER;
	}
	if (check_null_pointer(data_32) == false) {
		return NULL_POINTER;
	}

	sfr_parity_base_addr = otp_device->ecc_parity_base;

	if (sfr_parity_base_addr) {
		if (otp_get_parity_addr(bit_addr, otp_data->ecc_parity_addr_offset,
								&ecc_parity_addr) == false) {
			return INVALID_ADDR;
		}

		bank_sel = ecc_parity_addr >> SHIFT_BANK_SIZE_1024;
		ecc_parity_addr = (ecc_parity_addr / READ_32) * READ_32;
		err = otp_cmd_init(sfr_parity_base_addr);

		if (err == NO_FAIL) {

			for (cnt = 0; cnt < (byte_len >> SHIFT_BYTE_LEN); cnt++) {

				data_32[cnt] = otp_cmd_read(sfr_parity_base_addr,
											ecc_parity_addr + (cnt * READ_32),
											otp_data->parity_bank_type[bank_sel],
											&err);

				if (err != NO_FAIL)
					break;
			}

			if (err == NO_FAIL)
				err = otp_cmd_standby(sfr_parity_base_addr);
		}

	} else {
		err = NO_ADDRESS;
	}

	return err;
}

static uint32_t samsung_otp_read_32_ecc(const struct device *dev,
										uint32_t bit_addr,
										uint32_t *data_32,
										size_t byte_len)
{
	uint64_t ecc_base_addr;
	uint32_t addr_offset;
	uint32_t cnt;
	uint32_t err = NO_FAIL;
	const otp_samsung_device_config *otp_device = dev->config;

	if (check_null_pointer((uint32_t *)dev) == false) {
		return NULL_POINTER;
	}
	if (check_null_pointer(data_32) == false) {
		return NULL_POINTER;
	}

	ecc_base_addr = otp_device->ecc_base;

	if (ecc_base_addr) {
		addr_offset = bit_addr / 8;

		for (cnt = 0; cnt < (byte_len >> SHIFT_BYTE_LEN); cnt++) {
			cmrt_sac_set_base(NULL, GET_SAC_BASE(ecc_base_addr +
												 addr_offset +
												 (cnt * WORD_SIZE_4)));
			data_32[cnt] =  cmrt_sac_read32(GET_SAC_OFFSET(ecc_base_addr +
											addr_offset + (cnt * WORD_SIZE_4)));
		}

	} else {
		err = NO_ADDRESS;
	}

	return err;
}

static uint32_t samsung_otp_read_32_omc(const struct device *dev,
										uint32_t offset,
										uint32_t *data_32,
										size_t byte_len)
{
	int res;
	uint32_t err = NO_FAIL;
	cmrt_omc_t omc;

	if (check_null_pointer((uint32_t *)dev) == false) {
		return NULL_POINTER;
	}

	if (check_null_pointer(data_32) == false) {
		return NULL_POINTER;
	}

	omc = cmrt_omc_open(CMRT_O_SYNC);

	if (!cmrt_is_valid(omc)) {
		LOG_INF("[%s] cannot open OMC", __func__);
		cmrt_omc_close(omc);
		return OMC_OPEN_FAIL;
	}

	res = cmrt_omc_read(omc, offset, data_32, byte_len);
	if (res == -EIO) {
		LOG_INF("[%s] ECC error", __func__);
		err = OMC_EIO_FAIL;
	} else if (res != 0) {
		LOG_INF("[%s] Fail to read/ res:0x%x", __func__, res);
		err = OMC_READ_FAIL;
	}

	cmrt_omc_close(omc);

	return err;
}

static uint32_t samsung_otp_write(const struct device *dev,
								  uint32_t bit_addr,
								  uint32_t *data,
								  uint32_t ecc_enable,
								  size_t bit_len)
{
	uint64_t sfr_base_addr;
	uint64_t sfr_parity_base_addr;
	uint32_t ecc_parity_addr;
	uint32_t parity_data;
	uint32_t pvt_control_reg[5];
	uint32_t err = NO_FAIL;
	const otp_samsung_device_config *otp_device = dev->config;
	otp_samsung_data *otp_data = dev->data;

	if (check_null_pointer((uint32_t *)dev) == false) {
		return NULL_POINTER;
	}

	set_pvt_disable(pvt_control_reg);

	sfr_base_addr = otp_device->base;
	sfr_parity_base_addr = otp_device->ecc_parity_base;

	/* write length of an ecc write case must be 4 bytes long */
	if (ecc_enable && sfr_parity_base_addr &&
		(bit_len != (WORD_SIZE_4 * BIT_8)) &&
		!(bit_addr % (WORD_SIZE_4 * BIT_8))) {

		set_pvt_restore(pvt_control_reg);
		return PROGRAM_FAIL;
	}

	err = otp_cmd_init(sfr_base_addr);

	if (err == NO_FAIL) {
		err = otp_program(sfr_base_addr,
						  bit_addr,
						  bit_len,
						  data,
						  otp_data->bank_type);

	}

	err |= otp_cmd_standby(sfr_base_addr);
	err |= otp_cmd_pre_reading(sfr_base_addr);

	k_sleep(K_MSEC(WAIT_MSEC_10));

	if (err != NO_FAIL) {
		set_pvt_restore(pvt_control_reg);
		return err;
	}

	if (ecc_enable && sfr_parity_base_addr) {
		if (otp_get_parity_addr(bit_addr, otp_data->ecc_parity_addr_offset,
								&ecc_parity_addr) == false) {

			set_pvt_restore(pvt_control_reg);
			return INVALID_ADDR;
		}
		parity_data = otp_ecc_cal(data[0]);

		err = otp_cmd_init(sfr_parity_base_addr);

		if (err == NO_FAIL) {

			err = otp_program(sfr_parity_base_addr,
							  ecc_parity_addr,
							  BIT_8,
							  &parity_data,
							  otp_data->parity_bank_type);

		}
		err |= otp_cmd_standby(sfr_parity_base_addr);
		err |= otp_cmd_pre_reading(sfr_parity_base_addr);
	}

	k_sleep(K_MSEC(WAIT_MSEC_10));

	set_pvt_restore(pvt_control_reg);

	return err;
}

static const struct otp_driver_api otp_samsung_driver_api = {
	.device_info = samsung_otp_device_info,
	.product_id = samsung_otp_product_id,
	.read_32 = samsung_otp_read_32,
	.read_32_parity = samsung_otp_read_32_parity,
	.read_32_ecc = samsung_otp_read_32_ecc,
	.read_32_omc = samsung_otp_read_32_omc,
	.write = samsung_otp_write,
};

static int otp_samsung_init(const struct device *dev)
{
	otp_ecc_enable(true);
	return 0;
}

#define SAMSUNG_OTP_DEVICE_INIT(inst_num)										\
	static void otp_samsung_irq_config_func_##inst_num(void);					\
	static const otp_samsung_device_config otp_samsung_cfg_##inst_num = {       \
		.base = DT_INST_REG_ADDR_BY_NAME(inst_num, base),						\
		.ecc_parity_base = DT_INST_REG_ADDR_BY_NAME(inst_num, ecc_parity_base),	\
		.ecc_base = DT_INST_REG_ADDR_BY_NAME(inst_num, ecc_base),				\
		.irq_config_func = otp_samsung_irq_config_func_##inst_num,			    \
	};																			\
																				\
	static otp_samsung_data otp_samsung_data_##inst_num = {						\
		.ecc_parity_addr_offset = DT_INST_PROP(inst_num, ecc_parity_addr_offset),		\
		.bank_num = DT_INST_PROP(inst_num, bank_num),							\
		.bank_type = DT_INST_PROP(inst_num, bank_type),							\
		.parity_bank_type = DT_INST_PROP(inst_num, parity_bank_type),			\
	};																			\
																				\
	DEVICE_DT_INST_DEFINE(														\
		inst_num,																\
		&otp_samsung_init,																	\
		NULL,																	\
		&otp_samsung_data_##inst_num,											\
		&otp_samsung_cfg_##inst_num,											\
		PRE_KERNEL_1,															\
		CONFIG_KERNEL_INIT_PRIORITY_DEVICE,										\
		&otp_samsung_driver_api);												\
																				\
	static void otp_samsung_irq_config_func_##inst_num(void)					\
	{																			\
	}																			\

DT_INST_FOREACH_STATUS_OKAY(SAMSUNG_OTP_DEVICE_INIT)
