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

**fw_afe_fd4e3a15.hex:(23/12/2025)**
- AW will add this Fw into release notes document

**master_e1959c_evt1.hex:(21/01/2026)**
- AW will add this Fw into release notes document

**master_mbinit_db069.bin (27/01/2026) -> Latest Master**
- MBINIT 1) mbinit release done committed to dev_evt1 branch. new ltsm mask.
- A workaround to fix the repairval at 8G where a fixed offset of +16 is added to txpi cal. This is not required for 4G. If the link is to enabled at min datarate as 8G then skipping repairval would be adviced.
- scratch reg changes: Scratch_reg3 => 0x31800 ; Scratch_reg5 => 0x1ecefe7
- Changed reg3 to reflect min data rate from 0x31840.
- Reg5 is for all the states.

**fw_pls_shape_ovr_ab862.bin -> (26/03/2026) -> EVT1 Latest Master**
- Pulse shaper vfield added.
- Pulse shaper default changed from 127 to 15. Override needs to be discussed with AW if required.
