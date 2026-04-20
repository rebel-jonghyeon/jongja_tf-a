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
- Reason:  
leftovers of HDMA descriptor from previous test cause problem  
device triggers wrong HDMA(D2H) Channel
 * Solution:  
 change the logic to identify valid HDMA Channel  
 tc info is used instead of directly reading HDMA descriptor
  

# rebel_hw_vdk - VDK 2.5

## Release Date: 250915
### git tag: vdk_v2.5_cds_release_250915
### Test Condition
* **Build Options**
    * `./build.sh all -t -pl 0 -g 0 -p silicon --hbm 6.4`
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
run DTC, STC, basic test, Stress test, power vector test
- Total 1301 test suites are included.
- 22 minutes are taken for 1 test round. 

### Improvements
- Supports PCIe Gen5 
- add 1 test case at basic_test
    - ucie_sanity_test: checks UCIe data path and control path
- Stress Test is improved
    - Previously Stress Test iteration count is controlled from the Host PC. The interval between tests are excessively long.  
    - In VDK 2.4 the iteration count is controlled at the device side. This shortens the interval time, so the stress is induced effectively.
- run script improved
    - run all tests (DTC, STC, Basic Test, Stress Test) with single run script
    - total 1301 tests are run automatically.
- DRAM MMU property changed
    - Please refer to `osl/FreeRTOS/Source/portable/GCC/ARM_CA73/mmu_table.h`
    - DRAM property changed from `MT_NORMAL_NC` to `MT_NORMAL`
    - Reason of change: `MT_NORMAL_NC` causes major performance drop.

# rebel_hw_vdk - VDK 2.4
## Release Date: 250915
### git tag: vdk_v2.4_cds_release_250911
### git branch: dev_unified_test_bug_fix
Please refer to the branch `dev_unified_test_bug_fix`

# rebel_hw_vdk - VDK 2.0.1

## Release Date: 250901
### git tag: vdk_v2.0_cds_release_250901

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
This release aims to run sorting vectors using PCIe and UCIe. PCIe host triggers the test by running the Python application. All 4 chiplets are tested simultaneously, results are gathered and reported back to the PCIe host. Approximately 20 minutes are required to sweep all tests.

Below are the providing test suites for the VDK 2.0 250901:
- Basic Test (Unit Test)
Runs HW sanity check test. There are 38 test cases in this test. No input data are needed for this test. Device itself can produce the command and golden data. 
- Stress Test
These tests are the special case of basic test. Stress test are invented to generate heavy traffics to see the internal engines can endure in such circumstances. TPG(Test Pattern Generation) test for internal SRAMs such as SHM, SP and bus stress test for example RDSN config test are the representative stress tests.
- STC
run STC test. There are 1294 test cases including primitive, model zoo, power vector test. Test data are delivered through the PCIe. Once the test data arrives, each chiplet runs the test for 100 times repeatedly.
- Power Vectors
These tests are the special case of STC which requires more iteration times to see if the chip can draw heavy current. while heavy power comsumption. Test mechanism is same as the STC but iteration count is set to 10,000 times.
- DTC (Workload Test)
DTC is a workload test to see if the device can serve the actual LLM workload. DTC consists of complex combination of primitives. 2 types of DTC are served, each DTC workload runs 100 times individually .

### Improvements
- Reduced Logs
Being compared to previous release (VDK 2.0 250821) VDK 2.0 250901 significantly reduces logs for the debugging. This change can decrease test time and improves the visibility for tester by removing the unnecessary log string. So the tester only concerns about the "PASS" or "FAIL" string.
- Refined Test Suite
VDK 2.0 250901 provides 5 test cases (previously 4 test cases are served) to optimize the test iteration counts. It is obvious to assume that the stress test and the power vectors need more iteration count compared to the sanity tests, because longer stress testing period increases the probability that only high quality chips will survive.