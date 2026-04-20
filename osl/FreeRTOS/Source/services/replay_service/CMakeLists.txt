file(GLOB COMMON_SOURCES "common/*.c")
file(GLOB_RECURSE HAL_SOURCES "hal/*.c")

# EVT_VER: single source for replay HAL (0=evt0, 1=evt1). build.sh -evt 0|1 -> -DEVT_VER via
# scripts/build_cp0.sh / build_cm.sh. Manual cmake: -DEVT_VER=0 or -DEVT_VER=1 (default 0).
if(NOT DEFINED EVT_VER)
	set(EVT_VER "0" CACHE STRING "Replay HAL: 0=evt0, 1=evt1")
endif()

# Exclude evt0/evt1 HAL sources based on EVT_VER (must match target_compile_definitions below)
if(EVT_VER STREQUAL "1")
	list(FILTER HAL_SOURCES EXCLUDE REGEX ".*/evt0/.*")
else()
	list(FILTER HAL_SOURCES EXCLUDE REGEX ".*/evt1/.*")
endif()

if(FREERTOS_PORT STREQUAL "GCC_ARM_CA73")
    file(GLOB RBLN_SOURCES "rbln/arm64/*.c" "rbln/arm64/*.S" "rbln/*.c")
else()
    file(GLOB RBLN_SOURCES "rbln/arm/*.c" "rbln/*.c")
endif()

execute_process(
    COMMAND git describe --always --dirty --tags
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VER
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (NOT GIT_VER)
    set(GIT_VERSION "can't get version")
else()
    set(GIT_VERSION "${GIT_VER}")
endif()

if (DEFINED BUILD_NOTE)
    set(CUSTOM_MSG "${BUILD_NOTE}")
else()
    set(CUSTOM_MSG "")
endif()

add_definitions(-DCUSTOM_MSG="${CUSTOM_MSG}")
add_definitions(-DGIT_VERSION="${GIT_VERSION}")

set(RUSH_CLI_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/rush_cli")
add_subdirectory(external)
add_subdirectory(rush_cli)

add_library(replay_service
	STATIC	#OBJECT
	${HAL_SOURCES}
	${COMMON_SOURCES}
	${RBLN_SOURCES}
	$<TARGET_OBJECTS:backtrace>
	$<TARGET_OBJECTS:argparse>
	$<TARGET_OBJECTS:rush_cli>
	replay.c
	sub_function.c
)

target_link_libraries(replay_service
	PUBLIC
	freertos_kernel # it need event_group.o of freertos_kernel lib
	chiplet
	terminal_service
)

set(HAL_PRIVATE_INCLUDES
	hal/autogen/rebel
	hal/dnc/rebel
	hal/rbdma/rebel
	hal/shm/rebel
	hal/cmgr/rebel
)


# Add evt0/evt1 specific include paths (must match EVT_VER)
# Common headers: hal/autogen/rebel, hal/dnc/rebel; per-evt headers in evt0/evt1 subdirs
if(EVT_VER STREQUAL "1")
	list(APPEND HAL_PRIVATE_INCLUDES
		hal/autogen/rebel/evt1
		hal/dnc/rebel/evt1
	)
else()
	list(APPEND HAL_PRIVATE_INCLUDES
		hal/autogen/rebel/evt0
		hal/dnc/rebel/evt0
	)
endif()

if(FREERTOS_PORT STREQUAL "GCC_ARM_CA73")
    set(RBLN_ARCH_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/rbln/include/arm64")
else()
    set(RBLN_ARCH_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/rbln/include/arm")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__REBEL_FW__ -DENABLE_BACKTRACE -DLOG_LEVEL_DEFAULT=2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRDSN_ENABLED")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSHM_ENABLED")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDNC_ENABLED")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRBDMA_ENABLED")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DIPA_DISABLED")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DMMU_V2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSMMU_FORCE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSORT_MODE")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DINDICATOR_DEBUG_MODE")

# C/C++: use #if EVT_VER == 1 (evt1) / #if EVT_VER == 0 (evt0); must match HAL globs above
target_compile_definitions(replay_service PRIVATE "EVT_VER=${EVT_VER}")

target_include_directories(replay_service
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/autogen
	${CMAKE_CURRENT_SOURCE_DIR}/include/rbln/abort
	${CMAKE_CURRENT_SOURCE_DIR}/common/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/common
	${CMAKE_CURRENT_SOURCE_DIR}/rbln/include
	${CMAKE_CURRENT_SOURCE_DIR}/gloss
	${CMAKE_CURRENT_SOURCE_DIR}/headers/private
	${CMAKE_CURRENT_SOURCE_DIR}/headers/public
	${CMAKE_CURRENT_SOURCE_DIR}/rush_cli
	${HAL_PRIVATE_INCLUDES}
	${FREERTOS_COMMON_INCLUDES}
	${SVC_COMMON_INCLUDES}
	${DD_COMMON_INCLUDES}
	${RBLN_ARCH_INCLUDE}
	${CMAKE_ROOT_DIR}/drivers/mailbox
	${CMAKE_ROOT_DIR}/drivers/gpio
	${CMAKE_ROOT_DIR}/drivers/hbm3
	${CMAKE_ROOT_DIR}/drivers/smmu
)

if(FREERTOS_PORT STREQUAL "GCC_ARM_CA73")

execute_process(COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/replay.c)

add_custom_command(
    TARGET replay_service
    POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_ROOT_DIR}/binaries/Replay_Lib/
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_ROOT_DIR}/binaries/Replay_Lib/
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:replay_service> ${CMAKE_ROOT_DIR}/binaries/Replay_Lib/
)
endif()
