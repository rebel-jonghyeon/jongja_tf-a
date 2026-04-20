/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_PKE4_REG_H
#define CMRT_PKE4_REG_H
#define CMRT_PKE_BASE             0x00030000UL
#define R_PKE_BASE                (CMRT_PKE_BASE + 0x200UL)

#define MCG_COMMAND_TYPE          (1 << 31)
#define MAU_COMMAND_TYPE          (1 << 30)

#define R_PKE_RESET_CTRL          0x00UL
#define R_MAU_IFC_ISR             0x18UL
#define R_MAU_IFC_ICR             0x1CUL
#define R_MAU_STATUS              0x20UL
#define R_PKE_SCRATCH             0x30UL
#define R_MAU_MIN_LEN             0x34UL
#define R_MAU_MAX_LEN             0x38UL
#define R_MAU_PKE_VERSION         0x3CUL
#define R_MAU_MCG_CMDS_ENABLED0   0x40UL
#define R_MAU_MCG_CMDS_ENABLED1   0x44UL
#define R_MAU_MCG_CMDS_ENABLED2   0x48UL
#define R_MAU_MCG_CMDS_ENABLED3   0x4CUL
#define R_MAU_MCG_PKE_PRNG_SEED_1 0x50UL
#define R_MAU_MCG_PKE_PRNG_SEED_2 0x54UL
#define R_MAU_MCG_PKE_PRNG_SEED_3 0x58UL
#define R_MAU_MCG_PKE_PRNG_SEED_4 0x5CUL
#define R_PKE_WORD_SIZE           0x60UL
#define R_PKE_SRAM_ADDR_MIN       0x70UL
#define R_PKE_SRAM_ADDR_MAX       0x74UL
#define R_MAU_MAU_COMMAND         0x80UL
#define R_MAU_MCG_COMMAND         0x88UL

#define R_MAU_ADDR_CONST_BASE     0x1000UL
#define R_MAU_ZERO                0x1000UL
#define R_MAU_ONE                 0x1002UL
#define R_MAU_TWO                 0x1004UL
#define R_MAU_HLV                 0x1010UL
#define R_MAU_ADDR_RAM_SLOTS      0x1020UL
#define R_MAU_ADDR_ROM_SLOTS      0x1040UL
#define R_MAU_ADDR_RNG_ODD        0x1060UL
#define R_MAU_ADDR_RNG            0x1061UL

#define MAU_TO_IDLE_IRQ           (1 << 0)
#define MAU_COMMAND_DONE_IRQ      (1 << 1)
#define FIFO_ERROR_IRQ            (1 << 2)
#define MAU_ERROR_IRQ             (1 << 4)
#define MCG_ERROR_IRQ             (1 << 6)
#define PKE_IRQ_MASK (MAU_TO_IDLE_IRQ | MAU_COMMAND_DONE_IRQ | FIFO_ERROR_IRQ | MAU_ERROR_IRQ | MCG_ERROR_IRQ)

#define PKE_CORE_IRQ              (1 << 0)

#define MAU_FIFO_OFFSET             0
#define MAU_CORE_OFFSET             4
#define MAU_MCG_OFFSET              8
#define MAU_MAU_ERROR_CAUSE_OFFSET 16
#define MAU_MCG_ERROR_CAUSE_OFFSET 24
#define MAU_COMPARE_OFFSET         30

#define MAU_FIFO_MASK             (0x0fUL << MAU_FIFO_OFFSET)
#define MAU_CORE_MASK             (0x0fUL << MAU_CORE_OFFSET)
#define MAU_MCG_MASK              (0x0fUL << MAU_MCG_OFFSET)
#define MAU_MAU_ERROR_CAUSE_MASK  (0x08UL << MAU_MAU_ERROR_CAUSE_OFFSET)
#define MAU_MCG_ERROR_CAUSE_MASK  (0x04UL << MAU_MCG_ERROR_CAUSE_OFFSET)

#define FIFO_STATUS_EMPTY         0x00
#define FIFO_STATUS_NOT_EMPTY     0x01
#define FIFO_STATUS_FULL          0x03
#define FIFO_STATUS_ERROR         0x04

#define PKE_MAU_STATUS_READY      (0x00 << MAU_CORE_OFFSET)
#define PKE_MAU_STATUS_BUSY       (0x01 << MAU_CORE_OFFSET)
#define PKE_MAU_STATUS_ERROR      (0x02 << MAU_CORE_OFFSET)
#define PKE_MAU_STATUS_PANIC      (0x08 << MAU_CORE_OFFSET)

#define MAU_MCG_IDLE              (0x00 << MAU_MCG_OFFSET)
#define MAU_MCG_BUSY              (0x01 << MAU_MCG_OFFSET)
#define MAU_MCG_ERROR             (0x04 << MAU_MCG_OFFSET)
#define MAU_MCG_PANIC             (0x08 << MAU_MCG_OFFSET)

#define MAU_COMPARE_MASK          (0x03 << MAU_COMPARE_OFFSET)

#define PKE_FLUSH_ERROR           (1 << 20)

#define PKE_SPEC_MOD_ENABLED      (1 << 7)
#define PKE_SPEC_MOD_DISABLED     (0 << 7)

enum eccRomSlot {
	eccRomSlot_b = 0,
	eccRomSlot_gx = 1,
	eccRomSlot_gy = 2,
	eccRomSlot_q = 3,
	eccRomSlot_p = 4,
	eccRomSlot_a = 5,
	eccMontRomSlot_gu = 0,
	eccMontRomSlot_q = 1,
};

enum eccKeyBlind {
	eccKeyBlind_s =  3,
	eccKeyBlind_q = 13,
	out_eccKeyBlind_s0 = 3,
	out_eccKeyBlind_s1 = 4
};

enum ecdsaVerf {
	ecdsaVerf_Px =  0,
	ecdsaVerf_Py =  1,
	ecdsaVerf_h =   2,
	ecdsaVerf_r =   3,
	ecdsaVerf_s = 4,
	ecdsaVerf_rnd = 5,
	ecdsaVerf_b =  10,
	ecdsaVerf_gx = 11,
	ecdsaVerf_gy = 12,
	ecdsaVerf_q =  13,
	ecdsaVerf_p =  14,
	ecdsaVerf_a =  15,
	out_ecdsaVerf_r = 5,
	out_ecdsaVerf_rnd = 7,
};

enum ecdsaSign {
	ecdsaSign_n0 =  0,
	ecdsaSign_n1 =  1,
	ecdsaSign_h =   2,
	ecdsaSign_s0 =  3,
	ecdsaSign_s1 =  4,
	ecdsaSign_b =  10,
	ecdsaSign_gx = 11,
	ecdsaSign_gy = 12,
	ecdsaSign_q =  13,
	ecdsaSign_p =  14,
	ecdsaSign_a =  15,
	ecdsaSign_rnd = 16,
	out_ecdsaSign_s0 = 3,
	out_ecdsaSign_s1 = 4,
	out_ecdsaSign_r = 11,
	out_ecdsaSign_s = 12,
	out_ecdsaSign_rnd = 0,
};

enum eccPrivKeyGen {
	eccPrivKeyGen_k =  0,
	eccPrivKeyGen_q =  1,
	eccPrivKeyGen_rnd = 2,
	eccPrivKeyGen_gx = 0,
	out_eccPrivKeyGen_k =  0,
	out_eccPrivKeyGen_gx = 0,
	out_eccPrivKeyGen_rnd = 2,
};

enum eccTests {
	eccTest_gx =  0,
	eccTest_p = 1,
	eccTest_rnd = 2,
	out_eccTest_gx = 0,
	out_eccTest_q = 0,
	out_eccTest_rnd = 2,
};

enum eccKeyGen {
	eccKeyGen_rnd = 0,
	eccKeyGen_s0 = 3,
	eccKeyGen_s1 =  4,
	eccKeyGen_b =  10,
	eccKeyGen_gx = 11,
	eccKeyGen_gy = 12,
	eccKeyGen_q =  13,
	eccKeyGen_p =  14,
	eccKeyGen_a =  15,
	out_eccKeyGen_s0 = 3,
	out_eccKeyGen_s1 = 4,
	out_eccKeyGen_px = 11,
	out_eccKeyGen_py = 12,
	out_eccKeyGen_rnd = 18,
};

enum ecdhShared {
	ecdhShared_s0 = 3,
	ecdhShared_s1 =  4,
	ecdhShared_b =  10,
	ecdhShared_px = 11,
	ecdhShared_q =  13,
	ecdhShared_p =  14,
	ecdhShared_a =  15,
	ecdhShared_rnd = 16,
	out_ecdhShared_s0 = 3,
	out_ecdhShared_s1 = 4,
	out_ecdhShared_sx = 11,
	out_ecdhShared_rnd = 0,
};

enum eddsaKeyGen {
	eddsaKeyGen_magic =  2,
	eddsaKeyGen_s0 =     3,
	eddsaKeyGen_s1 =     4,
	eddsaKeyGen_gu =    12,
	eddsaKeyGen_q =     13,
	eddsaKeyGen_p =     14,
	eddsaKeyGen_a24 =   15,
	out_eddsaKeyGen_s0 =   3,
	out_eddsaKeyGen_s1 =   4,
	out_eddsaKeyGen_pyc = 11,
	out_eddsaKeyGen_pxc = 12,
};

enum eddsaVerf {
	eddsaVerf_pyc = 0,
	eddsaVerf_c0 =  2,
	eddsaVerf_r =   3,
	eddsaVerf_s =   4,
	eddsaVerf_c1 =  5,
	eddsaVerf_c2 =  6,
	eddsaVerf_rxs = 7,
	eddsaVerf_i =  10,
	eddsaVerf_gy = 11,
	eddsaVerf_gx = 12,
	eddsaVerf_q = 13,
	eddsaVerf_p = 14,
	eddsaVerf_d = 15,
	eddsaVerf_rnd = 18,
	out_eddsaVerf_r = 11,
	out_eddsaVerf_rnd = 18,
};

enum eddsaSign1 {
	eddsaSign1_n0 =    0,
	eddsaSign1_n1 =    1,
	eddsaSign1_magic = 2,
	eddsaSign1_s0 =    3,
	eddsaSign1_s1 =    4,
	eddsaSign1_n2 =    5,
	eddsaSign1_gu =   12,
	eddsaSign1_q =    13,
	eddsaSign1_p =    14,
	eddsaSign1_a24 = 15,
	eddsaSign1_rnd = 18,
	out_eddsaSign1_n0 = 0,
	out_eddsaSign1_n1 = 1,
	out_eddsaSign1_s0 = 3,
	out_eddsaSign1_s1 = 4,
	out_eddsaSign1_r = 11,
	out_eddsaSign1_rvs = 12,
	out_eddsaSign1_rnd = 0,
};

enum eddsaSign2 {
	eddsaSign2_n0 = 0,
	eddsaSign2_n1 = 1,
	eddsaSign2_c0 = 2,
	eddsaSign2_s0 = 3,
	eddsaSign2_s1 = 4,
	eddsaSign2_c1 = 5,
	eddsaSign2_c2 = 6,
	eddsaSign2_blank = 7,
	eddsaSign2_q = 13,
	eddsaSign2_rnd = 18,
	out_eddsaSign2_s0 = 3,
	out_eddsaSign2_s1 = 4,
	out_eddsaSign2_s_448 = 5,
	out_eddsaSign2_s_25519 = 12,
	out_eddsaSign2_rnd = 18,
};

enum eccOnCurve {
	eccOnCurve_rnd = 0,
	eccOnCurve_temp = 5,
	eccOnCurve_b =  10,
	eccOnCurve_px = 11,
	eccOnCurve_py = 12,
	eccOnCurve_p =  14,
	eccOnCurve_a =  15,
};

enum eccDecompress {
	eccDecompress_px = 0,
	eccDecompress_sy = 1,
	eccDecompress_rnd = 3,
	out_eccDecompress_py = 1,
	out_eccDecompress_rnd = 3,
};

enum ecdhMont {
	ecdhMont_s0 =  3,
	ecdhMont_s1 =  4,
	ecdhMont_gx = 12,
	ecdhMont_p =  14,
	ecdhMont_a24 = 15,
	out_ecdhMont_px = 12,
};
enum modexp_mont {
	modexp_mont_x =  0,
	modexp_mont_n =  2,
	modexp_mont_d0 = 4,
	modexp_mont_d1 = 5,
	out_modexp_mont_xd = 0,
};

enum modexp {
	modexp_x =  0,
	modexp_n =  2,
	modexp_d0 = 4,
	modexp_d1 = 5,
	out_modexp_xd = 0,
};

enum primegen {
	primegen_pdiff = 0,
	primegen_redp = 0,
	primegen_redphi = 0,
	primegen_pk = 2,
	primegen_qdiff = 1,
	primegen_maxdiff = 2,
	primegen_tmp = 6,
	primegen_tmp_low = 6,
	primegen_qm1 = 6,
	primegen_tmp_high = 7,
	primegen_pm1 = 7,
	primegen_mr = 8,
	primegen_d = 8,
	primegen_d_low = 8,
	primegen_d_high = 9,
	primegen_n = 10,
	primegen_n_low = 10,
	primegen_n_high = 11,
	primegen_phi = 12,
	primegen_phi_low = 12,
	primegen_phi_high = 13,
	primegen_p = 14,
	primegen_q = 15,
};

enum primegen_qr {
	primegen_setup_qr_acc = 0,
	primegen_setup_qr_b = 1,
	primegen_setup_qr_pr = 2,
	primegen_setup_qr_u = 3,
	primegen_setup_qr_m = 4,
	primegen_setup_qr_tmp = 1,
	primegen_qr_m = 0,
	primegen_qr_mr = 1,
	primegen_qr_u = 2,
	primegen_qr_sr = 3,
	primegen_qr_r = 4,
	primegen_qr_c = 6,
	primegen_qr_cu = 7,
	primegen_qr_x = 8,
	primegen_qr_xr = 9,
	primegen_qr_mb = 10,
	primegen_qr_ub = 11,
	primegen_qr_xb = 12,
};

enum keygen {
	keygen_r = 0,
	keygen_redphi = 0,
	keygen_pk = 1,
	keygen_d = 4,
	keygen_n = 5,
	keygen_phi = 6,
};

enum rsa_public {
	rsa_public_m = 0,
	rsa_public_n = 2,
	rsa_public_e = 3,
	rsa_public_rnd = 7,
	out_rsa_public_c = 0,
	out_rsa_public_rnd = 7,
};

enum rsa_sign {
	rsa_sign_c = 0,
	rsa_sign_n =  2,
	rsa_sign_e =  3,
	rsa_sign_d0 = 4,
	rsa_sign_d1 = 5,
	rsa_sign_rnd = 7,
	rsa_sign_tmp = 7,
	out_rsa_sign_m = 0,
	out_rsa_sign_rnd = 1,
};

enum rsa_crt_blind {
	rsa_blind_p = 0,
	rsa_blind_q = 1,
	rsa_blind_dp = 2,
	rsa_blind_dq = 3,
	rsa_blind_iq = 4,
	rsa_blind_new_mask = 5,
	rsa_blind_old_mask = 6,
	rsa_blind_iq_mask = 7,
	rsa_blind_tmp = 8,
	rsa_blind_tmp2 = 9,
	rsa_blind_rnd = 15,
};

enum rsa_crt_sign {
	rsa_crt_rnd = 0,
	rsa_crt_c = 1,
	rsa_crt_p = 2,
	rsa_crt_m = 3,
	rsa_crt_dp = 4,
	rsa_crt_iq = 5,
	rsa_crt_sec_rnd = 14,
	out_rsa_crt_sign_m = 0,
	out_rsa_crt_sign_rnd = 1
};

#ifdef CONFIG_CMRT_FFDH
enum ffdh_verify {
	ffdh_verify_g = 0,
	ffdh_verify_mod_p = 2,
	ffdh_verify_exp_q = 4,
	ffdh_verify_p = 14,
	ffdh_verify_q = 15,
	ffdh_verify_rnd = 0,
};

enum ffdh_keygen {
	ffdh_keygen_q = 0,
	ffdh_keygen_k = 1,
	ffdh_keygen_rnd = 2,
	out_ffdh_keygen_k = 0,
};

enum ffdh {
	ffdh_in = 0,
	ffdh_mod = 2,
	ffdh_exp = 4,
	ffdh_p = 6,
	ffdh_q = 7,
	ffdh_g = 8,
	ffdh_pri = 9,
	ffdh_peer = 10,
	ffdh_tmp = 11,
	out_ffdh_pub = 0,
	out_ffdh_sh = 0,
};

enum ffdh_parmgen {
	ffdh_parmgen_g = 0,
	ffdh_parmgen_rnd = 0,
	ffdh_parmgen_p = 12,
	ffdh_parmgen_inv_q = 13,
	ffdh_parmgen_q = 14,
	ffdh_parmgen_dh = 15,
};

enum binary_xgcd {
	binary_xgcd_x = 0,
	binary_xgcd_y = 1,
	binary_xgcd_u = 2,
	binary_xgcd_v = 3,
	binary_xgcd_s = 4,
	binary_xgcd_t = 5,
};
#endif
#endif
