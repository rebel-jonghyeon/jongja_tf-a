#define PCIE_HOST_TC_ADDR (0x1001000000ULL)
#define PCIE_HOST_TC_RESULT_ADDR (PCIE_HOST_TC_ADDR + 0x4)

#define PCIE_DOE_TEST_LENGTH (0x4)
#define PCIE_DOE_TEST_PAYLOAD_0 (0x12345678)
#define PCIE_DOE_TEST_PAYLOAD_1 (0x87654321)

#define PCIE_MSIX_TEST_HOST_ADDRESS (0x1000000000ULL)
#define PCIE_MSIX_TEST_MSG_DATA (0x10000000)

enum pcie_tc_id {
	TEST_ID_DOE = 1,
	TEST_ID_MSIX = 2,
};

enum pcie_tc_result {
	RESULT_PASS = 0x1,
	RESULT_FAIL = 0x2,
};

void run_test_case(uint64_t addr, uint32_t * data);
