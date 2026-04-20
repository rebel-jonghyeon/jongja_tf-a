add_library(smmu OBJECT smmu.c smmu_pmu.c)

target_link_libraries(smmu
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(smmu
	PUBLIC
	${${DD_COMMON_INCLUDES}}
	${CMAKE_CURRENT_LIST_DIR}
)
