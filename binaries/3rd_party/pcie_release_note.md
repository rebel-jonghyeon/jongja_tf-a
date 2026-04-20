Copyright (c) 2026 Synopsys, Inc. 
This IP and the associated documentation are proprietary to Synopsys, Inc. 
This IP may only be used in accordance with the terms and conditions 
of a written license agreement with Synopsys, Inc. All other use, 
reproduction, or distribution of this IP is strictly prohibited.
--------------------------------------------------------------------------------
Synopsys Statement on Inclusivity and Diversity
Synopsys is committed to creating an inclusive environment where every employee,
customer, and partner feels welcomed. We are reviewing and removing exclusionary
language from our products and supporting customer-facing collateral. Our effort
also includes internal initiatives to remove biased language from our engineering
and working environment, including terms that are embedded in our software and IPs.
At the same time, we are working to ensure that our web content and software applications
are usable to people of varying abilities. You may still find examples of non-inclusive
language in our software or documentation as our IPs implement industry-standard
specifications that are currently under review to remove exclusionary language.
--------------------------------------------------------------------------------

E32 PCIe5 x4 PHY for SS 4LPP 1.2V
 
Release 2.04a_cust1_patch0a
January 15, 2026
 
Purpose of Release
*******************
- Release is to support case: 01943383 - Request latest FW.
- Release includes FW2.9_1, ATE and CM updates.

Changes compared to 2.04a_cust1 release:
****************************************

Soft-Macro view updates
-----------------------

ATE changes:
Must-have updates
- ATE parameter update due to CM update.
- Increase the ate_adpt_time to 5ms for pcie protocols in x4 config.
- Increase the delay from 10us to 50us after setting MAN_TUNE in TX DC level ALU and TX VCM ALU test to avoid the ADC measurement is not finished.
- ATE TB can reflect the timing sequence of refa<b>_clk_en and ref_repeat_clk_en in POR.
- Remove the register override for refa<b>_clk_en, mplla<b>_force_en and ref_repeat_clk_en_r.
- Removed the write operation of register E32_CR_RAWCMN_DIG_TOKEN_DLY to avoid potential holding issue when using cr access.
- Override to enable the mplla<b>_pmix_en when both IPNAME_ATE_MPLL_PMIX_EN and IPNAME_MPLL_PMIX_EN are defined.
- Remove RAWCMN_DIG_AON_PG_OVRD_IN from register writable test.

Enhancement
- Support ate_debug_regout test.
- Remove the extra vec_pause (2000) in normal mode during POR and adaptation.
- Updated tb_ate_jtag_driver.v to decouple VEC_TRACE and ATE_DISPLAY_MASK_BIT.
- Updated tb_ate_tasks.v to correct the value of dummy cycles in POR calibration.
- Replaced register E32_CR_SUP_DIG_MPLLA_DIV_CLK_OVRD_IN to E32_CR_SUP_DIG_MPLLA_OVRD_IN_1 in ate_run_simple_registers_test to avoid sim issue as ref_dig_clk_sel and ref_clk_sel setting wrong.
- Move "Override per lane resets to 1" and "Override tx_req, rx_req and rx_data_en to 0" before "Overriding sram_ext_ld_done to 1'b1".
- Support ana register test one by one in ate_register_test when the macro IPNAME_ENABLE_ANA_REGISTER is defined.
- Updated ate_register_test to replace absulute addr to relative addr of register name.
- Skip the step "Load ROM from firmware binary file" when the macro SRAM_EXT_LD is defined.
- Removed "Overriding sram_ext_ld_done to 1'b1" from task sram_external_load to avoid the data mismatch issue of register test when the macro SRAM_EXT_LD defined.
- Support wgl verification in cntx mode.
- Update leakage_current_test sequence to correct register override for RX_TERM_EN and RX_TERM_ACDC.
- Can support rx coarse adapt enable in fast sim mode.
- Remove the redundant ropll read check in bert test.
- Update register tests sequence to include the macro LANE_FSM_FREEZE by default.

IPXACT changes:
- IPXACT update due to firmware update.

Changes from FW2.5 to FW2.9_1
------------------------------
Must-have changes:
1.Updated firmware to correctly restore the TX DCC calibration code during the power-up and rate change sequence when TX DCC calibration is skipped. This update addresses the issue where the TX DCC calibration code was not restored correctly when TX DCC calibration was skipped.
2.Added a firmware workaround regarding issue where rxX_margin_error_clear remains asserted indefinitely.

Enhancements:
1.Updated DFE tap1 overflow conditions in IQ v2 adaptation to address inferior results
2.Support scaling capability for DFE eye width
	a.The DFE eye width value undergoes scaling with its corresponding register during the calculation of Figure of Merit(FOM).
	b.RAWLANEAON_DIG_ADPT_CTL_15_ADDR[14:13] = fom_dfe_scale (Default : 0)
		i.  fom_dfe_scale = 0 : not scaled
		ii. fom_dfe_scale = 1 : DFE eye width * 1/2
		iii.fom_dfe_scale = 2 : DFE eye width * 1/4
		iv. fom_dfe_scale = 3 : DFE eye width * 1/8
	c.The RAWLANE_DIG_RX_CTL_FOM_CTL_ADDR[7:0](FOM_STARTUP_EXTEND=dfe_eyew) value itself remains in unscaled. (same usage as FOM_AFE_EYEH scale)
	d.FOM value including scaled 'dfe_eyew' and scaled 'afe_eyeh' is stored in the RAWLANE_DIG_PCS_XF_RX_ADAPT_FOM_ADDR
3.Updated the AFE peaking algorithm for enhanced receiver performance
	a.Added the capability to collect additional statistics to tighten repeatability.
		i.  RAWLANEAON_DIG_ADPT_CTL_4_ADDR[2:0] = The exponent number of averaging loop iterations (default : 0)
		ii. Example
			1.RAWLANEAON_DIG_ADPT_CTL_4_ADDR[2:0] = 0 -> 1-iteration for averaging (no additional statistics collection)
			2.RAWLANEAON_DIG_ADPT_CTL_4_ADDR[2:0] = 1 -> 2-iteration for averaging
			3.RAWLANEAON_DIG_ADPT_CTL_4_ADDR[2:0] = 2 -> 4-iteration for averaging
		iii.Note that increased statistics collection also increases the overall adaptation time (hence this feature is disabled by default)
	b.Introduced a boost threshold to bypass the algorithm for debug exceptionally short channels. This adjustment prevents excessive    over-equalization of the AFE output and ensures accurate pattern matching.
		i. RAWLANEAON_DIG_ADPT_CTL_4_ADDR[3] = icc_boost_thresh_en (default : 0)
			1.1'b0 : Firmware do not bypass the algorithm to update icc_code (legacy behavior)
			2.1'b1 : Firmware bypass the algorithm and checks ctle_boost value is less than icc_boost_thresh 
		ii.RAWLANEAON_DIG_ADPT_CTL_4_ADDR[7:4] : icc_boost_thresh (default : 8)
	c.Expanded the bit width of adapt_icc_thresh1/2_int from 3 bits to 5 bits to enhance threshold resolution thereby improve the margin    between ICC levels. 
		i. adapt_icc_thresh1_int : RAWLANEAON_DIG_ADPT_CTL_9_ADDR[6:4] -> RAWLANEAON_DIG_ADPT_CTL_8_ADDR[10:6]
		ii.adapt_icc_thresh2_int : RAWLANEAON_DIG_ADPT_CTL_9_ADDR[9:7] -> RAWLANEAON_DIG_ADPT_CTL_8_ADDR[15:11]
	d.Increased the loop iteration in AFE peaking adaptation algorithm to expand the icc range selection
		i.  Number of ICC iteration loops = RAWLANEAON_DIG_ADPT_CTL_11_ADDR[14:12]
		ii. Example)
			1.RAWLANEAON_DIG_ADPT_CTL_11_ADDR[14:12] = 4
		iii.ICC iteration loop == 4 (ICC code can change 4 times)
	e.Added a debug feature for monitoring internal measurement results in AFE peaking adaptation algorithm
		i. RAWLANEAON_DIG_ADPT_CTL_18_ADDR : ref_ee_int_code_sum
		ii.RAWLANEAON_DIG_ADPT_CTL_19_ADDR : dfe_tap1_int_code_sum
4.Non-destructive margining updated to improve the centering of eye measurement both horizontally and vertically 
	a.RAWLANEAON_DIG_ADPT_CTL_4_ADDR[15] is used to enable/disable this feature
		i. 0 : Enable the option for improve unbalanced margin value (default)
		ii.1 : Disable the option for improve unbalanced margin value
5.Added functionality to disable lane staggering feature during Power-On Reset(POR) and Power-Gating(PG) sequence
	a.RAWLANEAON_DIG_ADPT_CTL_8_ADDR[3] = 0 : Enable lane staggering (default)
	b.RAWLANEAON_DIG_ADPT_CTL_8_ADDR[3] = 1 : Disable lane staggering
6.Added a feature to retry CDR reset if IQ steps to right is less than 2 during IQ adaptation for extra robustness.  
	a.RAWLANEAON_DIG_ADPT_CTL_15_ADDR[12] used to enable or disable the IQ retry feature
		i. 0 : Disable (default)
		ii.1 : Enable
	b.RAWLANEAON_DIG_ADPT_CTL_8_ADDR[2:1] stores the iteration counts of CDR reset retries (cleared at the start of IQ adaptation)
7.The RTRIM override has been moved from before VGEN calibration to after VGEN calibration
8.Added skip option to AFE Peaking in PCIE GEN3
	a.RAWLANE_DIG_FSM_FW_SCRATCH_15_ADDR[13] = 0 : skip AFE Peaking in GEN3 (By default)
	b.RAWLANE_DIG_FSM_FW_SCRATCH_15_ADDR[13] = 1 : do not skip AFE Peaking in GEN3
9.Added option to increase CDR wait time in REF tracking mode before coarse adaptation/latching of golden DPLL FREQ to ADPT_CTL_0 which can take care of VCO leakage issue.
	a.RAWLANEAON_DIG_ADPT_CTL_9_ADDR[7:6] can be programmed to vary the wait time.
	b.RAWLANEAON_DIG_ADPT_CTL_9_ADDR[7:6] = 00 -> expected wait time > 35us (By default)
	c.RAWLANEAON_DIG_ADPT_CTL_9_ADDR[7:6] = 01 -> expected wait time > 70us
	d.RAWLANEAON_DIG_ADPT_CTL_9_ADDR[7:6] = 10 -> expected wait time > 105us
	e.RAWLANEAON_DIG_ADPT_CTL_9_ADDR[7:6] = 11 -> expected wait time > 140us
10.Added offset to the reference level during the adaptation reset at the beginning of the startup adaptation only for the Gen5.
	a.RAWLANEAON_DIG_ADPT_CTL_6_ADDR[11] : cal_ref_ofst_ovrd_en
		i. 1'b0 : Disable adding offset for Gen5
		ii.1'b1 : Enable adding offset for Gen5
	b.RAWLANEAON_DIG_ADPT_CTL_6_ADDR[15:12] : cal_ref_ofst_ovrd
		i.The number of additional offset for Gen5
11.Added workaround to prevent rxX_valid asserted during the adaptation sequence which can causes the bit error on the controller side.
	a.RAWLANEAON_DIG_ADPT_CTL_6_ADDR[8]
		i. 1'b0 : Disable WA (By default)
		ii.1'b1 : Enable WA
12.Added workaround for preventing the additional txX/rxX_reset input while FW is doing tx/rx_reset sub-routine, which can cause the PHY to get stuck.
	a.RAWLANEAON_DIG_ADPT_CTL_6_ADDR[9] : tx_reset workaround enable
		i. 1'b0 : Disable WA for tx_reset (By default)
		ii.1'b1 : Enable WA for tx_reset
	b.RAWLANEAON_DIG_ADPT_CTL_6_ADDR[10] : rx_reset workaround enable
		i. 1'b0 : Disable WA for rx_reset (By default)
		ii.1'b1 : Enable WA for rx_reset
13.Added slicer non-linearity enhancement algorithm
	a.RAWLANEAON_DIG_ADPT_CTL_10_ADDR[12] : Slicer Non-Linearity enhancement feature enable
		i.1'b0 : (By default) Disable slicer non-linearity enhancement feature
		ii.1'b1 : Enable slicer non-linearity enhancement feature
	b.RAWLANEAON_DIG_ADPT_CTL_20_ADDR[1] : Enable to check for negative side of slicer non-linearity if RAWLANEAON_DIG_ADPT_CTL_10_ADDR[12] = 1
		i.1'b0 : Check slicer non-linearity only on positive side
		ii.1'b1 : (By default) Enable to check both positive and negative side of slicer non-linearity
	c.RAWLANEAON_DIG_ADPT_CTL_10_ADDR[10] : Control bit to detect slicer non-linearity based on short channel detection only for positive side.
		i.1'b0 : Slicer non-linearity detection do not depened on short channel detection
		ii.1'b1 : (By default) When short channel detected, assuming slicer non-linearity exists on positvie side.
			Set RAWLANEAON_DIG_ADPT_CTL_11_ADDR[3](Short channel detect) = 0
			Set RAWLANEAON_DIG_ADPT_CTL_10_ADDR[13](Slicer NL detect on positive side) = 1
		iii.Note : To use this feature, RAWLANEAON_DIG_ADPT_CTL_20_ADDR[1] should be 0.
	d.RAWLANEAON_DIG_ADPT_CTL_10_ADDR[13] : Slicer non-linearity detection flag on positive side
		1.1'b0 : Slicer non-linearity NOT detected on the positive side
		ii.1'b1 : Slicer non-linearity detected on the positive side
	e.The threshold value to detect slicer non-linearity adjusted by CREGs as follows. Thresholds can be changed through rate restore.
		i.RAWLANEAON_DIG_ADPT_CTL_20_ADDR[7:2] : th_sNL_dac_ofst_low
			6'd29 : (By default)
		ii.RAWLANEAON_DIG_ADPT_CTL_23_ADDR[15:10] : th_sNL_dac_ofst 
			6'd35 : (By default)
		iii.RAWLANEAON_DIG_ADPT_CTL_23_ADDR[9:5] : th_sNL_cal_ref_2
			5'd11 : (By default)
		iv.RAWLANEAON_DIG_ADPT_CTL_23_ADDR[4:0] : th_sNL_cal_ref
			5'd16 : (By default)
		v.RAWLANEAON_DIG_ADPT_CTL_21_ADDR[14:9] : th_sNL_dac_ofst_2
			6'd32 : (By default)
		vi.Note: Please keep default values to use the slicer non-linearity function if there are no intended values.
	f.To monitor the REF_CAL value of individual reference calibration level for slicer non-linearity debug
		i.RAWLANEAON_DIG_ADPT_CTL_13_ADDR[15] : Log individual slicer reference calibration values instead of average
			1'b0 : (By default) Disable logging individual slicer reference calibration values
			1'b1 : Enable logging individual slicer reference calibration values
		ii.Reference calibration value can be monitored
			RAWLANEAON_DIG_RX_CAL_REF_EE_VDAC_OFST_ADDR
			RAWLANEAON_DIG_RX_CAL_REF_EO_VDAC_OFST_ADDR
	g.Added slicer non-linearity debug feature which is skipping "DFE Fixed Tap Fine Adaptation"
		i.RAWLANEAON_DIG_ADPT_CTL_20_ADDR[0]
			1'b0 : (By default) Not skipping "DFE Fixed Tap Fine Adaptation"
			1'b1 : Skip "DFE Fixed Tap Fine Adaptation"
14.The RTRIM threshold override logic has been updated. Gen1-4 and Gen5 can be controlled separately. This feature should be used with rate restore.
	a.For Gen1-4 
		i.  RAWLANEAON_DIG_ADPT_CTL_15_ADDR[15] : RTRIM threshold override enable for Gen1-4.
			1.1'b0 : (By default) Disable overriding
			2.1'b1 : Enable overriding
		ii. RAWLANEAON_DIG_ADPT_CTL_15_ADDR[7:0] : Threshold value between RTRIM value 0 and 1
			1.8'h0 : (By default)
		iii.RAWLANEAON_DIG_ADPT_CTL_14_ADDR[7:0] : Threshold value between RTRIM value 1 and 2
			1.8'h0 : (By default)
		iv. RAWLANEAON_DIG_ADPT_CTL_14_ADDR[15:8] : Threshold value between RTRIM value 2 and 3
			1.8'h0 : (By default)
	b.For Gen5
		i.  RAWLANEAON_DIG_ADPT_CTL_21_ADDR[15] : RTRIM threshold override enable for Gen5
			1.1'b0 : (By default) Disable overriding
			2.1'b1 : Enable overriding
		ii. RAWLANEAON_DIG_ADPT_CTL_20_ADDR[15:8] : Threshold value between RTRIM value 0 and 1
			1.8'h0 : (By default)
		iii.RAWLANEAON_DIG_ADPT_CTL_22_ADDR[15:8] : Threshold value between RTRIM value 1 and 2
			1.8'h0 : (By default)
		iv. RAWLANEAON_DIG_ADPT_CTL_22_ADDR[7:0] : Threshold value between RTRIM value 2 and 3
			1.8'h0 : (By default)
15.Added code for clearing tx_req_disable_r  in rx2tx_loopback IRQ so that FW issued pma tx_req can be accepted by tx_pwr_ctl FSM.
16.Updated to skip term code update by firmware to prevent conflicts between hardware and firmware. 
	a.rx/tx term code updated executed by
		i. Hardware & Firmware (PMA >= 2.9)
		ii.Firmware (PMA < 2.9)
	b.RAWLANEAON_DIG_ADPT_CTL_15_ADDR[8]
		i. 1'b0 : (By default) Not skip the tx/rx term code update
		ii.1'b1 : Skip tx/rx term code update
		
Package contents
----------------
doc
 
phy
  include      - Verilog include files
  ipxact       - IP-XACT description
  sim          - Simulation scripts
  testbench    - Behavioral model simulation test environment
 
upcs
  sim          - Simulation scripts
  testbench    - Behavioral model simulation test environment
  
  
Labels used in this release:
----------------------------
PMA Label:		e32_pma_2.9aq1_2	
RAW PCS Label:		e32_raw_1.18	
RAW PCS Cust_TB Label:	e32_raw_1.18_cust_1.11	
IPXACT Label:		e32_pma_2.9aq1_2_raw_1.18_fw_2.9_1
UPCS Label:		exx_upcs_1.58 [CM 1.332]	
UPCS_Cust_TB Label:	exx_upcs_1.58_cust_1.0	
ATE cust Label:		e32_ate_cust_te_1.44_6
Config Master:		v1.453

