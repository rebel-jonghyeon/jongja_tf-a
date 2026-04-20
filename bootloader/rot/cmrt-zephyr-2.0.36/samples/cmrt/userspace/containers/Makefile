# List of container subdirectories
define container_subdirs
	echo
	caliptra_rt
	pmu
	teefs
	test_aes
	test_concurrent
	test_dma
	test_ecc test_ecies test_ffdh
	test_hash_hmac
	test_hkdf
	test_kdc
	test_ktc
	test_lms
	test_misaligned
	test_omc
	test_rsa
	test_teec
	test_tmc
	test_version
	test_xmss
	v1_sample/sample_aes_ccm
	v1_sample/sample_aes_cmac
	v1_sample/sample_aes_xts
	v1_sample/sample_dma
	v1_sample/sample_ecies
	v1_sample/sample_edwards_curve
	v1_sample/sample_enable_debug
	v1_sample/sample_ffdh
	v1_sample/sample_fmc
	v1_sample/sample_hmac_sha
	v1_sample/sample_irq
	v1_sample/sample_kdc
	v1_sample/sample_ktc
	v1_sample/sample_lifecycle
	v1_sample/sample_linger
	v1_sample/sample_otp_slot
	v1_sample/sample_otp_sub
	v1_sample/sample_root
	v1_sample/sample_tmc
	v1_sample/sample_version
endef

containers := $(strip $(container_subdirs))

# Targets for cleaning each container
cleantargets := $(addprefix clean-,$(containers))

.PHONY: all
all:	$(containers)

.PHONY: $(containers) $(cleantargets)

$(containers):
	$(MAKE) -C $@

$(cleantargets): clean-%:
	$(MAKE) -C $* clean

.PHONY: clean pristine
clean pristine:	$(cleantargets)

.SUFFIXES:
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
MAKEFLAGS += --warn-undefined-variables
unexport MAKEFLAGS
