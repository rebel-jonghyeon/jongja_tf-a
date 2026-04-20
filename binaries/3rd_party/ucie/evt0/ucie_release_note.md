**Initial release FW: (2 weeks prior to chipback)**
- Full Ltsm fw with hardcoded Skips and Inital Rate for running repair
- No postprocessing capability

**250724_ucie_ss :(25/04/2025)**
- Added User defined skips and User configurable initial rate.

**250725_fw_memcpy: (26/04/2025)**
- Preformed Memcpy Allowed for post processing of FW eyes from sram dump.
- Added minor changes to fix plotting

**fw_cfc31259.hex: (8/5/2025)**
- Fixed Front End Tx and RX calibrations to improve performance
- CMN configs related to regulators and retiming
- Aligned Most configs to use latest Samba (AW internal Samsung chip)

**fw_58192f8dc.hex:(8/6/2025)**
- Gammacore fix rebase including latest gammacore.
- Much newer silicon proven changes ported from internal testchip.
- Changes improved the linkup rate

**fw_c8baff4f_vref.hex:(26/9/2025)**
- Included fixes for pbd cal with datatraincenter2.
- Enabled Vref Calibration.
- Structures stored in sram all with 32 bit widths.
- New plotting capabilities with per io plot

**fw_afe_fd4e3a15.hex:(15/11/2025)**
- Optimized AFE setting: TIA nmos 18 -> 11, DQS: Res 3 -> 0 nmos/pmos 7->1
- Pattern changed Prbs7 pattern back to UCIE pattern as per spec.

**master_rt_9264e_out.hex:(27/01/2026) -> Latest Master**
- Removed AWTP Printing feature suspecting it was causing some hangs (still under investigation)
- Added Retrain flow from raichu_retrain branch. (Tested on available EVT1/0 100% passing with Sticky_Trainerror=0)
- Added optimized afe parameters into 16 and 24G tables from 12G. Initial data shows same optimal settings for tia @16G.