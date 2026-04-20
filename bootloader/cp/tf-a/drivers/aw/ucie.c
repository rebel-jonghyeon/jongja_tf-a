#include <drivers/aw/ucie.h>
#include <drivers/aw/reg/aw_ucie_reg.h>
#include <drivers/synopsys/qspi_bridge.h>
#include <common/debug.h>
#include <platform_def.h>

enum {
	TARGET_LINK_SPEED_4GT = 0,
	TARGET_LINK_SPEED_8GT,
	TARGET_LINK_SPEED_12GT,
	TARGET_LINK_SPEED_16GT,
	TARGET_LINK_SPEED_24GT,
	TARGET_LINK_SPEED_32GT,
};

#define AW_UCIE_PHY_CMN_CMNSOC_LS_MUX_SEL_REF_BUMP	(0x4)
#define CLOCK_CYCLE_1								(0x1)
#define ENABLE										(0x1)

/* reg_cmn_mcu_scratch_reg3*/
const uint32_t disable_fw_timeouts = 0x0; /* Set to 1 to disable all FW timeouts */
const uint32_t active_modules = 0x3; /* module per bit */
const uint32_t burst_mode = 0x0; /* continuous - 0 : burst - 1 */
const uint32_t sbdiv = 0x3; /* dividing sbclk 0x3 -100Mhz clock */
const uint32_t bitmode_override_val = 0x0; /* 0-16B mode, 1-8B mode only effective if BITMODE_OVERRIDE_EN is set */
const uint32_t bitmode_override_en = 0x0; /* Enables external override of 8B vs 16B mode selection */
#if EVT_VER == 0
	const uint32_t min_rate = 0x1; /*0-4GBs 1-8GBs 2-12GBs */
#else
	const uint32_t min_rate = 0x0;
#endif
/* reg_cmn_mcu_scratch_reg5*/
/* select which LTSM states to enable (final values will be enabled) */
#if EVT_VER == 0
	const uint32_t st_reset = 1;
	const uint32_t st_sbinit = 1;
	const uint32_t st_mbinit_param = 1;
	const uint32_t st_mbinit_cal = 0;
	const uint32_t st_mbinit_repairclk = 0;
	const uint32_t st_mbinit_repairval = 0;
	const uint32_t st_mbinit_reversalmb = 0;
	const uint32_t st_mbinit_repairmb = 0;
	const uint32_t st_mbtrain_valvref = 1;
	const uint32_t st_mbtrain_datavref =  1;
	const uint32_t st_mbtrain_speedidle = 1;
	const uint32_t st_mbtrain_txselfcal = 1;
	const uint32_t st_mbtrain_rxselfcal = 0;
	const uint32_t st_mbtrain_valtraincenter = 1;
	const uint32_t st_mbtrain_valtrainvref = 1;
	const uint32_t st_mbtrain_datatraincenter1 = 1;
	const uint32_t st_mbtrain_datatrainvref = 0;
	const uint32_t st_mbtrain_rxdeskew = 0;
	const uint32_t st_mbtrain_datatraincenter2 = 1;
	const uint32_t st_mbtrain_linkspeed = 1;
	const uint32_t st_mbtrain_repair = 0;
	const uint32_t st_phyretrain = 1;
	const uint32_t st_linkinit =  1;
	const uint32_t st_active = 1;
	const uint32_t st_trainerror = 1;
	const uint32_t st_l1_l2 = 0;
	const uint32_t st_max_states = 0;
#else
	const uint32_t st_reset = 1;
	const uint32_t st_sbinit = 1;
	const uint32_t st_mbinit_param = 1;
	const uint32_t st_mbinit_cal = 0;
	const uint32_t st_mbinit_repairclk = 0;
	const uint32_t st_mbinit_repairval = 1;
	const uint32_t st_mbinit_reversalmb = 1;
	const uint32_t st_mbinit_repairmb = 1;
	const uint32_t st_mbtrain_valvref = 1;
	const uint32_t st_mbtrain_datavref =  1;
	const uint32_t st_mbtrain_speedidle = 1;
	const uint32_t st_mbtrain_txselfcal = 1;
	const uint32_t st_mbtrain_rxselfcal = 0;
	const uint32_t st_mbtrain_valtraincenter = 1;
	const uint32_t st_mbtrain_valtrainvref = 1;
	const uint32_t st_mbtrain_datatraincenter1 = 1;
	const uint32_t st_mbtrain_datatrainvref = 0;
	const uint32_t st_mbtrain_rxdeskew = 0;
	const uint32_t st_mbtrain_datatraincenter2 = 1;
	const uint32_t st_mbtrain_linkspeed = 1;
	const uint32_t st_mbtrain_repair = 0;
	const uint32_t st_phyretrain = 1;
	const uint32_t st_linkinit =  1;
	const uint32_t st_active = 1;
	const uint32_t st_trainerror = 1;
	const uint32_t st_l1_l2 = 0;
	const uint32_t st_max_states = 0;
#endif

/* reg_cmn_mcu_scratch_reg6*/
/* 0 - pd, 1 - LTSM L0, 2 - LTSM L1 (Future), 3 - LTSM L2 (Future) */
const uint32_t cmn_pstate = 1; /* Set for CMN Glbl power state */
const uint32_t tx_pstate = 1; /* Set for TX power state */
const uint32_t rx_pstate = 1; /* Set for RX power state */
const uint32_t sticky_train_error = 0; /* Set to 1 to enable background NDE gathering */
const uint32_t no_degrade = 1; /* Set to 1 to enable ATEST gathering during NDE */
const uint32_t nde_bit_sel = 4; /* Select which bit to gather NDE data on */
const uint32_t skip_txlpbk_iq_cal = 1; /* Set to 1 to skip txlpbk iq cal */

static void _enable_local_ucie_core(const uint64_t base_addr)
{
	volatile struct aw_ucie * const target_ss = (struct aw_ucie * const)base_addr;

	target_ss->global_reg_cmn_mcu_scratch_reg3.val |= disable_fw_timeouts << 27;
	target_ss->global_reg_cmn_mcu_scratch_reg3.val |= active_modules << 16;
	target_ss->global_reg_cmn_mcu_scratch_reg3.val |= burst_mode << 30;
	target_ss->global_reg_cmn_mcu_scratch_reg3.val |= sbdiv << 11;
	target_ss->global_reg_cmn_mcu_scratch_reg3.val |= bitmode_override_val << 10;
	target_ss->global_reg_cmn_mcu_scratch_reg3.val |= bitmode_override_en << 9;
	target_ss->global_reg_cmn_mcu_scratch_reg3.val |= min_rate << 6;

	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_reset << 0;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_sbinit << 1;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbinit_param << 2;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbinit_cal << 3;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbinit_repairclk << 4;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbinit_repairval << 5;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbinit_reversalmb << 6;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbinit_repairmb << 7;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_valvref << 8;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_datavref << 9;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_speedidle << 10;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_txselfcal << 11;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_rxselfcal << 12;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_valtraincenter << 13;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_valtrainvref << 14;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_datatraincenter1 << 15;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_datatrainvref << 16;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_rxdeskew << 17;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_datatraincenter2 << 18;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_linkspeed << 19;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_mbtrain_repair << 20;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_phyretrain << 21;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_linkinit << 22;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_active << 23;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_trainerror << 24;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_l1_l2 << 25;
	target_ss->global_reg_cmn_mcu_scratch_reg5.val |= st_max_states << 26;

	target_ss->global_reg_cmn_mcu_scratch_reg6.val |= cmn_pstate << 5;
	target_ss->global_reg_cmn_mcu_scratch_reg6.val |= tx_pstate << 7;
	target_ss->global_reg_cmn_mcu_scratch_reg6.val |= rx_pstate << 9;
	target_ss->global_reg_cmn_mcu_scratch_reg6.val |= sticky_train_error << 14;
	target_ss->global_reg_cmn_mcu_scratch_reg6.val |= no_degrade << 15;
	target_ss->global_reg_cmn_mcu_scratch_reg6.val |= nde_bit_sel << 17;
	target_ss->global_reg_cmn_mcu_scratch_reg6.val |= skip_txlpbk_iq_cal << 26;


#if UCIE_DATA_RATE == 16000
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.lcap_max_link_speed = TARGET_LINK_SPEED_16GT;
#elif UCIE_DATA_RATE == 12000
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.lcap_max_link_speed = TARGET_LINK_SPEED_12GT;
#elif UCIE_DATA_RATE == 8000
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.lcap_max_link_speed = TARGET_LINK_SPEED_8GT;
#elif UCIE_DATA_RATE == 4000
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.lcap_max_link_speed = TARGET_LINK_SPEED_4GT;
#else
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.lcap_max_link_speed = TARGET_LINK_SPEED_12GT;
#endif
	target_ss->phy_cmn_reg_cmnsoc_reg1.ena_mux_sel_ovr_ena_a = ENABLE;
	target_ss->phy_cmn_reg_cmnsoc_reg1.ls_mux_sel_ovr_nt = AW_UCIE_PHY_CMN_CMNSOC_LS_MUX_SEL_REF_BUMP;

	const uint32_t mcu_ctrl_reset_value = 0x3ff6;

	target_ss->global_reg_cmn_mcu_ctrl.val = mcu_ctrl_reset_value;
	target_ss->dfx0_reg_lane_mcu_ctrl.val = mcu_ctrl_reset_value;
	target_ss->dfx1_reg_lane_mcu_ctrl.val = mcu_ctrl_reset_value;

	target_ss->global_reg_cmn_mcu_ctrl.fetch_en_a = ENABLE;
	target_ss->phy_cmn_reg_sram_cfg.rd_data_pipeline_stages_nt = CLOCK_CYCLE_1;

	target_ss->global_reg_cmn_mcu_ctrl.reset_n_a = ENABLE;
	target_ss->dfx0_reg_lane_mcu_ctrl.fetch_en_a = ENABLE;
	target_ss->dfx0_reg_lane_mcu_ctrl.reset_n_a = ENABLE;
	target_ss->dfx1_reg_lane_mcu_ctrl.fetch_en_a = ENABLE;
	target_ss->dfx1_reg_lane_mcu_ctrl.reset_n_a = ENABLE;
}

static void _enable_remote_ucie_core(const uint32_t chiplet_id, const uint64_t base_addr)
{
	volatile struct aw_ucie * const target_ss = (struct aw_ucie * const)base_addr;
	const uint32_t qspi_channel = 2;
	const uint32_t mcu_ctrl_reset_value = 0x3ff6;

	qspi_bridge_set_upper_addr(qspi_channel, (uint32_t)base_addr, chiplet_id);

	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->global_reg_cmn_mcu_scratch_reg3.val,
							disable_fw_timeouts << 27 | active_modules << 16 | burst_mode << 30 | sbdiv << 11
							| bitmode_override_val << 10 | bitmode_override_en << 9 | min_rate << 6, chiplet_id);

	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->global_reg_cmn_mcu_scratch_reg5.val,
							st_reset << 0 | st_sbinit << 1 | st_mbinit_param << 2 | st_mbinit_cal << 3
							| st_mbinit_repairclk << 4 | st_mbinit_repairval << 5 | st_mbinit_reversalmb << 6
							| st_mbinit_repairmb << 7 | st_mbtrain_valvref << 8 | st_mbtrain_datavref << 9
							| st_mbtrain_speedidle << 10 | st_mbtrain_txselfcal << 11 | st_mbtrain_rxselfcal << 12
							| st_mbtrain_valtraincenter << 13 | st_mbtrain_valtrainvref << 14
							| st_mbtrain_datatraincenter1 << 15 | st_mbtrain_datatrainvref << 16
							| st_mbtrain_rxdeskew << 17 | st_mbtrain_datatraincenter2 << 18
							| st_mbtrain_linkspeed << 19 | st_mbtrain_repair << 20 | st_phyretrain << 21
							| st_linkinit << 22 | st_active << 23 | st_trainerror << 24 | st_l1_l2 << 25
							| st_max_states << 26, chiplet_id);

	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->global_reg_cmn_mcu_scratch_reg6.val,
							rx_pstate << 9 | tx_pstate << 7 | cmn_pstate << 5 | sticky_train_error << 14
							| no_degrade << 15 | nde_bit_sel << 17 | skip_txlpbk_iq_cal << 26, chiplet_id);

/* [7:4] 0h: 4GT/s, 1h: 8GT/s,2h: 12GT/s, 3h: 16GT/s */
#if UCIE_DATA_RATE == 16000
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.val,
							0x30, chiplet_id);
#elif UCIE_DATA_RATE == 12000
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.val,
							0x20, chiplet_id);
#elif UCIE_DATA_RATE == 8000
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.val,
							0x10, chiplet_id);
#elif UCIE_DATA_RATE == 4000
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.val,
							0x0, chiplet_id);
#else
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.val,
							0x20, chiplet_id);
#endif

	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->phy_cmn_reg_cmnsoc_reg1.val, 0x101,
							chiplet_id);

	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->global_reg_cmn_mcu_ctrl.val,
							mcu_ctrl_reset_value, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dfx0_reg_lane_mcu_ctrl.val,
							mcu_ctrl_reset_value, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dfx1_reg_lane_mcu_ctrl.val,
							mcu_ctrl_reset_value, chiplet_id);

	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->global_reg_cmn_mcu_ctrl.val,
							mcu_ctrl_reset_value | 0x4, chiplet_id);

	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->phy_cmn_reg_sram_cfg.val, 0x1, chiplet_id);

	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->global_reg_cmn_mcu_ctrl.val,
							mcu_ctrl_reset_value | 0x5, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dfx0_reg_lane_mcu_ctrl.val,
							mcu_ctrl_reset_value | 0x4, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dfx0_reg_lane_mcu_ctrl.val,
							mcu_ctrl_reset_value | 0x5, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dfx1_reg_lane_mcu_ctrl.val,
							mcu_ctrl_reset_value | 0x4, chiplet_id);
	qspi_bridge_write_1word(qspi_channel, (uint64_t)&target_ss->dfx1_reg_lane_mcu_ctrl.val,
							mcu_ctrl_reset_value | 0x5, chiplet_id);
}

void enable_ucie_core(const uint32_t chiplet_id, const uint64_t base_addr)
{
	VERBOSE("chip %d, enable 0x%lx\n", chiplet_id, base_addr);

	if (chiplet_id == CHIPLET_ID) {
		_enable_local_ucie_core(base_addr);
	} else {
		_enable_remote_ucie_core(chiplet_id, base_addr);
	}
}

bool check_link_up(const uint32_t chiplet_id, const uint64_t base_addr)
{
	volatile struct aw_ucie * const target_ss = (struct aw_ucie * const)base_addr;

#if ZEBU /* for AW Emulation FW */
	if (chiplet_id == CHIPLET_ID)
		return target_ss->global_reg_cmn_mcu_scratch_reg1.cmn_mcu_scratch1_reg == 0xffffffff;

	const uint32_t qspi_channel = 2;

	qspi_bridge_set_upper_addr(qspi_channel, (uint32_t)base_addr, chiplet_id);
	uint32_t rdata = qspi_bridge_read_1word(qspi_channel,
											(uint64_t)&target_ss->global_reg_cmn_mcu_scratch_reg1.val, chiplet_id);

	return rdata == 0xffffffff;
#else /* ZEBU */
	const uint32_t qspi_channel = 2;

	if (chiplet_id == CHIPLET_ID)
		return target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_link_status;

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_status;

	qspi_bridge_set_upper_addr(qspi_channel, base_addr, chiplet_id);
	link_status.val = qspi_bridge_read_1word(qspi_channel,
											 (uint64_t)&target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val,
											 chiplet_id);

	return link_status.lstatus_link_status;
#endif /* not ZEBU */
}
