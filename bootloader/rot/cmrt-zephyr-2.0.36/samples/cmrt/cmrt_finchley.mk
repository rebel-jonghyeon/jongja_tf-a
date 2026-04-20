
PERSOS = blank caliptra_setup tested provisioned
SUPERVISORS = dispatcher echo fips mw hkdf
OS_DIR = supervisors/mw

INSTALL_TBOOT ?= n

SIGN_KEY_supervisors/mw := $(ZEPHYR_BASE)/samples/cmrt/common/prikey_ecdsa_p384.pem
SIGN_KEY_userspace/containers/caliptra_rt := $(ZEPHYR_BASE)/samples/cmrt/common/prikey_ecdsa_p384_2.pem
