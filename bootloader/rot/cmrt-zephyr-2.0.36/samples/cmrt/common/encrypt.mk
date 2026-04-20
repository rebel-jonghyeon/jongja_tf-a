ifeq ($(BOARD),cmrt_systest)
# Define static data store encryption key.
ENCRYPT_KEY = 000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f
ENCRYPT_KEYID = ds
ENCRYPT_DIVERSIFY = 00000000
endif

# Define encryption key using OTP keysplit and KDC.
ifndef ENCRYPT_KEY
# This is the first OTP keysplit provisioned in tested perso.
ENCRYPT_IKM = 2ed4d081a511ffdea63ecb58c050202332920a72e30f9e804ce3afd8db61aff2
ENCRYPT_KEYID = 1

# $(SIGN_KEY) is the public key that signs the image, it makes the derive path.
ENCRYPT_DERIVE = $(shell cmrt-image-footer.py --show-pubkey-hash $(SIGN_KEY))

# ENCRYPT_DIVERSIFY is a randomly generated bitstring, 4 bytes.
# This is followed by 11 bytes of 00, and a single 00 or 01 byte.

# ENCRYPT_KEY used once, executed when used. '"caveats".*0' matches NONE caveat
ENCRYPT_KEY = $(shell \
        grep -q '"caveats".*0' footer.json && s= d=00 || s=-s d=01 ;\
        cmrt-derive.py $$s -H 0 -k $(ENCRYPT_IKM) $(ENCRYPT_DERIVE) aes $(ENCRYPT_DIVERSIFY)0000000000000000000000$$d )

# Recursively expand ENCRYPT_DIVERSIFY on first use (same value used twice).
ENCRYPT_DIVERSIFY = $(eval ENCRYPT_DIVERSIFY := $(shell od -An -N4 -tx4 /dev/urandom))$(ENCRYPT_DIVERSIFY)
endif
