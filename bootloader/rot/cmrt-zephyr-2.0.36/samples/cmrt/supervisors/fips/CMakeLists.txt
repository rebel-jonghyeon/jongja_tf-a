# Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(supervisor)

zephyr_cc_option(-Os -Wno-pointer-arith)
add_definitions(-DSUPERVISOR_VERSION_NUMBER=${SUPERVISOR_VERSION_NUMBER} -DSUPERVISOR_VERSION_INFO="${SUPERVISOR_VERSION_INFO}")

target_sources(app PRIVATE src/cri_utils.c)
target_sources(app PRIVATE src/fips_aes.c)
target_sources(app PRIVATE src/fips_asset.c)
target_sources(app PRIVATE src/fips.c)
target_sources(app PRIVATE src/fips_drbg.c)
target_sources(app PRIVATE src/fips_ecc.c)
target_sources(app PRIVATE src/fips_ecdh.c)
target_sources(app PRIVATE src/fips_ecdsa.c)
target_sources(app PRIVATE src/fips_kat.c)
target_sources(app PRIVATE src/fips_kdf.c)
target_sources(app PRIVATE src/fips_key_importexport.c)
target_sources(app PRIVATE src/fips_ktc.c)
target_sources(app PRIVATE src/fips_log.c)
target_sources(app PRIVATE src/fips_pk_test.c)
target_sources(app PRIVATE src/fips_rsa_keygen.c)
target_sources(app PRIVATE src/fips_rsa_pss.c)
target_sources(app PRIVATE src/fips_service.c)
target_sources(app PRIVATE src/fips_sha.c)
target_sources(app PRIVATE src/fips_status.c)
target_sources(app PRIVATE src/fips_sym.c)
target_sources(app PRIVATE src/fips_tmc.c)
target_sources(app PRIVATE src/fips_user.c)
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/pke_kat.c)
target_sources(app PRIVATE src/sw_kdf_kat.c)
target_sources(app PRIVATE src/teec_cmvp.c)
target_sources(app PRIVATE src/teefs_cmvp.c)


target_sources_ifdef(CONFIG_CMRT_SHSIG_LMS app PRIVATE src/fips_lms_hss.c)
target_sources_ifdef(CONFIG_CMRT_SHSIG_XMSS app PRIVATE src/fips_xmss.c)

target_link_libraries(app PUBLIC "-Wl,-e__reset")
