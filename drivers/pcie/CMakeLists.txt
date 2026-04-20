# Generate variables by CMake
if(NOT PCIE_TARGET_SPEED)
	set(PCIE_TARGET_SPEED 5)
endif()

if(NOT PCIE_TARGET_NUM_LANES)
	set(PCIE_TARGET_NUM_LANES 16)
endif()

if (NOT PCIE_IATU_NUM_REGION)
	set(PCIE_IATU_NUM_REGION 64)
endif()

if (PCIE_TARGET_SPEED GREATER 5)
	message(FATAL_ERROR "PCIE_TARGET_SPEED must be lower than 5")
endif()

if (PCIE_TARGET_NUM_LANES GREATER 16)
	message(FATAL_ERROR "PCIE_TARGET_NUM_LANES must be lower than 16")
endif()

if (PCIE_IATU_NUM_REGION GREATER 64)
	message(FATAL_ERROR "PCIE_IATU_NUM_REGION must be lower than 64")
endif()

configure_file(pcie_generated_config.h.in ${CMAKE_CURRENT_LIST_DIR}/pcie_generated_config.h)

add_library(pcie
	OBJECT
	pcie_ep.c
	pcie_dw.c
	pcie_snps_phy.c
	pcie_dw_hdma.c
	pcie_irq.c
	pcie_dw_iatu.c
	pcie_dw_bar.c
	pcie_dw_msix.c
	pcie_subctrl.c
	pcie_doe.c
	pcie_dw_ide.c
	pcie_sysreg.c
)

target_link_libraries(pcie
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(pcie
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/../pmu
)
