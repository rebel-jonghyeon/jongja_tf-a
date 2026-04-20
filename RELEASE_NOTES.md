# rebel_hw_vdk - VDK 2.9.0/2.9.1
## Release Date: 251016
### git tag: vdk_v2.9.0_cds_release_251016
### Improvements
* Include vdk 3.0 test cases
    * ucie sanity test
    * ucie stress test
    * dcl stress test
* vdk 2.9.0
    * build with HBM 6.4 option
* vdk 2.9.1
    * build with HBM 8.0 option

### Test Condition
* **Build Options**
    * v2.9.0 T32: `./build.sh all -t -pl 0 -g 0 -p silicon --hbm 6.4`
    * v2.9.0 Flash: `./build.sh all -t -pl 0 -p silicon --cmrt 1 --hbm 6.4`
    * v2.9.1 T32: `./build.sh all -t -pl 0 -g 0 -p silicon --hbm 8.0`
    * v2.9.1 Flash: `./build.sh all -t -pl 0 -p silicon --cmrt 1 --hbm 8.0`

# rebel_hw_vdk - VDK 2.6.1
## Release Date: 250926
### git tag: vdk_v2.6.1_cds_release_250926
### Improvements
* Included Bootloader patch and other FDS commits (until 09.26)
# rebel_hw_vdk - VDK 2.6
## Release Date: 250925
### git tag: vdk_v2.6_cds_release_250925
### Improvements
* Included new HBM patch and other FDS commits (until 09.24)
# rebel_hw_vdk - VDK 2.5.1
## Release Date: 250923
### git tag: vdk_v2.5.1_cds_release_250923
### Improvements
* Minor update of VDK 2.5
### Bug Fixes
- Fixed test fail false alarm
# rebel_hw_vdk - VDK 2.5
## Release Date: 250915
### Test Conditions
* **Build Options**
    * T32 Fusing: `./build.sh all -t -pl 0 -g 0 -p silicon --hbm 6.4`
    * Flash: `./build.sh all -t -pl 0 -p silicon --cmrt 1 --hbm 6.4`
* **Frequency**
    * DNC: 1.8 GHz
    * BUS: 1.6 GHz
    * CP: 2.0 GHz
    * PCIe: 2.0 GHz (Gen5)
* **BW**
    * HBM: 6.4 Gbps
    * UCIe: 8.0 Gbps
* **Voltage**
    * VCC_DCL: 900 mV
    * VCC_MEM: 900 mV
    * VCC_TOPBUS: 850 mV

### Features
- Total 1301 test suites are included.
- 22 minutes are taken for 1 test round. 
- how to run
    - mv directory to `scripts`
    - run all test: `./run_all.sh`
    - run power vector 3001 for 10000 times: `./run_power_vector_3001.sh`
### Improvements
- Supports PCIe Gen5 
- add 1 test case at basic_test
- Stress Test is improved
- all tests are run with single script
- DRAM MMU property changed
    - Please refer to `osl/FreeRTOS/Source/portable/GCC/ARM_CA73/mmu_table.h`
    - DRAM property changed from `MT_NORMAL_NC` to `MT_NORMAL`
    - Reason of change: `MT_NORMAL_NC` causes major performance drop.

# rebel_hw_vdk - VDK 2.4
## Release Date: 250915

# rebel_hw_vdk - VDK 2.0.1
This release aims to run sorting vectors using PCIe and UCIe. PCIe host triggers the test by running the Python application. All 4 chiplets are tested simultaneously, results are gathered and reported back to the PCIe host. Approximately 20 minutes are required to sweep all tests.

## Release Date: 250901

### Test Conditions
* **Build Options** 
    * `./build.sh all -t -pl 0 -g 0 -p silicon -ps 4 -pn 16 --hbm 6.4`
* **Frequency**
    * DNC: 1.8 GHz
    * BUS: 1.6 GHz
    * CP: 2.0 GHz
    * PCIe: 2.0 GHz (Gen4)
* **BW**
    * HBM: 6.4 Gbps
    * UCIe: 8.0 Gbps
* **Voltage**
    * VCC_DCL: 900 mV
    * VCC_MEM: 900 mV
    * VCC_TOPBUS: 850 mV


### Features
FW
- Enhanced Unit Test functions
    - Execute 38 test cases for HW sanity check
- Enhanced Basic Test functions
    - Execute 1294 test cases including DCL primitive and  model zoo
    - Power vectors to estimate power consumption at DCL
- Added Stress Test
    - Internal SRAM(SHM/SP) test using TPG(Test Pattern Generator) for heavy traffic
    - Execute 2 AI Model Workload
- Host device driver/Application
    - No Updates
### Improvements
- Reduced Logs
- Refined Test Suite
