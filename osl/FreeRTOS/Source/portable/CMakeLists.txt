# FreeRTOS internal cmake file. Do not use it in user top-level project
add_compile_options(-DCHIPLET_COUNT=${CHIPLET_COUNT})

add_library(freertos_kernel_port STATIC
    # CA73
    $<$<STREQUAL:${FREERTOS_PORT},GCC_ARM_CA73>:
        GCC/ARM_CA73/port.c
        GCC/ARM_CA73/portASM.S>
    # CM7
    $<$<STREQUAL:${FREERTOS_PORT},GCC_ARM_CM7>:
        GCC/ARM_CM7/r1p2/start.S
        GCC/ARM_CM7/r1p2/system_rebelh_cm7.c
        GCC/ARM_CM7/r1p2/port.c
        GCC/ARM_CM7/r1p2/fpu.S>
)

target_include_directories(freertos_kernel_port
    PUBLIC
    ${FREERTOS_CONFIG_FILE_DIRECTORY}
    ${FREERTOS_COMMON_INCLUDES}
)

if(${FREERTOS_PORT} STREQUAL "GCC_ARM_CA73")
	add_library(freertos_arch
		STATIC
		GCC/ARM_CA73/startup.S
		GCC/ARM_CA73/vector.S
		GCC/ARM_CA73/prep_c.c
	)

	target_include_directories(freertos_arch
		PUBLIC
		${FREERTOS_CONFIG_FILE_DIRECTORY}
		${FREERTOS_COMMON_INCLUDES}
	)

	add_library(smp
		STATIC
		GCC/ARM_CA73/smp.c
		GCC/ARM_CA73/smp.S
	)

	target_link_libraries(smp
		PUBLIC
		intc
		psci
	)

	target_include_directories(smp
		PUBLIC
		${FREERTOS_CONFIG_FILE_DIRECTORY}
		${FREERTOS_COMMON_INCLUDES}
	)

	add_library(mmu
		STATIC
		GCC/ARM_CA73/mmu.c
	)

	target_link_libraries(mmu
		PUBLIC
		freertos_arch
		intc
	)

	add_library(smccc
		STATIC
		GCC/ARM_CA73/smccc.S
	)

	target_link_libraries(freertos_kernel_port
		PUBLIC
		freertos_arch
		smp
		smccc
		mmu
	)
elseif(${FREERTOS_PORT} STREQUAL "GCC_ARM_CM7")
	target_link_libraries(freertos_kernel_port
		PUBLIC
		bat
	)
endif()
