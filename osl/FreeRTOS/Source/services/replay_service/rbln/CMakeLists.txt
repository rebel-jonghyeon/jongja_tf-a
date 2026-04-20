file(GLOB RBLN_SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/abort.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/log.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/mem_cmds.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/assert.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/core.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/rand.c"
)

if("${UTEST}" STREQUAL "all")
	if(FREERTOS_PORT STREQUAL "GCC_ARM_CA73")
		set(RBLN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/arm64")
	else()
		set(RBLN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/arm")
	endif()

	if(FREERTOS_PORT STREQUAL "GCC_ARM_CA73")
		file(GLOB ARCH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/arm64/*.c"
			"${CMAKE_CURRENT_SOURCE_DIR}/arm64/*.S")
		set(ARCH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/arm64")
	else()
		file(GLOB ARCH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/arm/*.c")
		set(ARCH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/arm")
	endif()

	add_library(rbln
		STATIC
		${RBLN_SRCS}
		${ARCH_SRCS}
	)

	target_include_directories(rbln
		PRIVATE
		${CMAKE_ROOT_DIR}/unit_test/unity/src
	)

#	target_include_directories(rbln
#		PUBLIC
#		${CMAKE_ROOT_DIR}/osl/FreeRTOS/Source/include/rbln/abort
#		${CMAKE_CURRENT_SOURCE_DIR}/include
#		${CMAKE_CURRENT_SOURCE_DIR}/include/rbln
#	)
else()
	if(FREERTOS_PORT STREQUAL "GCC_ARM_CA73")
		set(RBLN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/arm64")
	else()
		set(RBLN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/arm")
	endif()

	if(FREERTOS_PORT STREQUAL "GCC_ARM_CA73")
		file(GLOB ARCH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/arm64/*.c"
			"${CMAKE_CURRENT_SOURCE_DIR}/arm64/*.S")
		set(ARCH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/arm64")
	else()
		file(GLOB ARCH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/arm/*.c")
		set(ARCH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/arm")
	endif()

	add_library(rbln
		STATIC
		${RBLN_SRCS}
		${ARCH_SRCS}
	)

#	target_include_directories(rbln
#		PUBLIC
#		${CMAKE_ROOT_DIR}/osl/FreeRTOS/Source/include/rbln/abort
#		${CMAKE_CURRENT_SOURCE_DIR}/include
#		${CMAKE_CURRENT_SOURCE_DIR}/include/rbln
#	)
endif()

target_include_directories(rbln
	PUBLIC
	${FREERTOS_COMMON_INCLUDES}
	${ARCH_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include       # rbln/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/rbln
	${CMAKE_ROOT_DIR}/drivers/intc
	${CMAKE_ROOT_DIR}/common/headers/private
	${CMAKE_ROOT_DIR}/common/headers/public
	${CMAKE_ROOT_DIR}/lib/include
	${CMAKE_ROOT_DIR}/osl/FreeRTOS/Source/rbln/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../services/replay_service/include/autogen
)

#if(${FREERTOS_PORT} STREQUAL "GCC_ARM_CA73")
#	target_link_libraries(rbln
#		PUBLIC
#		arch_arm64
#	)
#else()
#	target_link_libraries(rbln
#		PUBLIC
#		arch_arm
#	)
#endif()
