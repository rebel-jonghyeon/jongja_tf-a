#!/usr/bin/env python3
#
# Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.
#
# cmrt-config-tool.py OUTFILE [OUTFILE]...
#
# To output build time configuration from fboot config:
# cmrt-config-tool.py board.mk
#
# To output json configuration from fboot and mw configs:
# cmrt-config-tool.py board.json
#
# To output kernel parameters from fboot and mw configs:
# cmrt-config-tool.py kernel.param
#
# Note that cmrt-config-tool.py must be run in the application directory,
# it will find all relevant configuration files from there.

import sys
import json
import os.path
from contextlib import redirect_stdout
from devicetree import edtlib

def parse_cmrt_config(filename, arg_vars=None):
    # Kconfig output is easy to parse machine generated flat file.
    config = {}
    for line in open(filename):
        line = line.strip()
        if line == '' or line[0] == '#': continue
        name, value = line.split('=', 1)
        if name and value:
            if value == 'y':
                config[name] = True
            elif value == 'n':
                config[name] = False
            else:
                try:
                    config[name] = int(value, 0)
                except ValueError:
                    config[name] = value.strip('"')
    if arg_vars is not None:
        config.update(arg_vars)
    return config


def calculate_otp_esw(dts, _config):
    # Return ESW area start offset based on config.
    otp_esw = 0x2ec # the standard value with OTP layout 1
    if dts.label2node['omc'].props['layout-version'].val >= 2:
        otp_esw += 0x4 # layout 2 adds key obliterate word
    if dts.label2node['omc'].props['layout-version'].val >= 3:
        otp_esw += 0x8 # layout 3 adds root valid and obliterate words
    # full OTP has 8 roots and 7 keysplits, take out what we don't have
    otp_esw -= (8 - dts.label2node['omc'].props['num-roots'].val) * 0x38
    otp_esw -= (7 - dts.label2node['omc'].props['num-keysplits'].val) * 0x20
    return otp_esw


def calculate_sboot_start(dts, config):
    # Return sboot start in SRAM based on config.
    ram_base = dts.label2node['sram'].regs[0].addr
    ram_size = dts.label2node['sram'].regs[0].size
    sboot_in_rom = config.get('CONFIG_CMRT_SBOOT_IN_ROM')
    supervisor_in_rom = config.get('CONFIG_CMRT_SUPERVISOR_IN_ROM')
    sboot_max_size = dts.label2node['otp'].regs[0].size
    if sboot_in_rom:
        if supervisor_in_rom:
            sboot_max_size = config['CONFIG_CMRT_MACHINE_ROM_SIZE']
        else: # only sboot in ROM
            sboot_max_size = dts.label2node['rom'].regs[0].size
    sboot_start = ram_base + ram_size - sboot_max_size
    return sboot_start

def calculate_os_start(dts, config):
    ram_base = dts.label2node['sram'].regs[0].addr
    pke_ram_size = dts.label2node['pkeram'].regs[0].size
    machine_ram_size = config['CONFIG_CMRT_MACHINE_RAM_SIZE']
    os_start = ram_base + pke_ram_size + machine_ram_size
    return os_start

def make_mk_config(dts_filenames, config_filenames, output_filename):
    config = parse_cmrt_config(config_filenames[0])
    dts = edtlib.EDT(dts_filenames[0], [dts_filenames[1]])
    otp_esw = calculate_otp_esw(dts, config)
    if config.get('CONFIG_CMRT_OMC_ESW_RSVD_FIRST', 0):
        # the returned offset points to the sboot start
        otp_esw += config.get('CONFIG_CMRT_OMC_ESW_RSVD_WORDS', 0) * 4
    sboot_start = calculate_sboot_start(dts, config)
    os_start = calculate_os_start(dts, config)
    otp_layout_version = dts.label2node['omc'].props['layout-version'].val
    sog_size = dts.label2node['sog'].regs[0].size

    with open(output_filename, 'w') as f, redirect_stdout(f):
        # Write only those variables we need in Makefiles.
        flash_m25p80 = 'y' if config.get('CONFIG_SOC_FLASH_M25P80') else 'n'
        print('FLASH_M25P80={}'.format(flash_m25p80))
        otp_size = dts.label2node['otp'].regs[0].size
        print('OTP_SIZE=0x{:x}'.format(otp_size))
        print('OTP_ESW=0x{:x}'.format(otp_esw))
        print('OTP_LAYOUT_VERSION={}'.format(otp_layout_version))
        keysplits_num = dts.label2node['omc'].props['num-keysplits'].val
        print('KEYSPLITS_NUM={}'.format(keysplits_num))
        print('SBOOT_START=0x{:x}'.format(sboot_start))
        sboot_in_rom = 'y' if config.get('CONFIG_CMRT_SBOOT_IN_ROM') else 'n'
        print('SBOOT_IN_ROM={}'.format(sboot_in_rom))
        try:
            ext_rom_size = dts.label2node['rom'].regs[0].size
        except KeyError:
            ext_rom_size = 0
        print('EXT_ROM_SIZE=0x{:x}'.format(ext_rom_size))
        machine_rom_size = config['CONFIG_CMRT_MACHINE_ROM_SIZE']
        print('MACHINE_ROM_SIZE=0x{:x}'.format(machine_rom_size))
        ext_mem_size = dts.label2node['extmem'].regs[0].size
        print('EXT_MEM_SIZE=0x{:x}'.format(ext_mem_size))
        ext_mem_fpga = config['CONFIG_FPGA_EXTMEM_SIZE']
        print('EXT_MEM_FPGA=0x{:x}'.format(ext_mem_fpga))
        fips_mode = 'y' if config.get('CONFIG_CMRT_FIPS_140_MODE') else 'n'
        print('FIPS_MODE={}'.format(fips_mode))
        asil_b_mode = 'y' if config.get('CONFIG_CMRT_ASIL_B_MODE') else 'n'
        print('ASIL_B_MODE={}'.format(asil_b_mode))
        encrypted_image = 'y' if config.get('CONFIG_CMRT_ENCRYPTED_IMAGE_SUPPORT') else 'n'
        print('ENCRYPTED_IMAGE={}'.format(encrypted_image))
        image_autoload = 'y' if config.get('CONFIG_CMRT_IMAGE_AUTOLOAD_SUPPORT') else 'n'
        print('IMAGE_AUTOLOAD={}'.format(image_autoload))
        supervisor_in_rom = 'y' if config.get('CONFIG_CMRT_SUPERVISOR_IN_ROM') else 'n'
        print('SUPERVISOR_IN_ROM={}'.format(supervisor_in_rom))
        cfi_enabled = 'y' if config.get('CONFIG_CMRT_CFI') else 'n'
        print('CFI_ENABLED={}'.format(cfi_enabled))
        print('OS_START=0x{:x}'.format(os_start))
        print('SOG_SIZE=0x{:x}'.format(sog_size))
    pass


def has_boolean(config_name, machine_config, supervisor_config):
    if machine_config.get(config_name):
        return True
    if supervisor_config.get(config_name):
        return True
    return False


def read_int(config_name, machine_config, supervisor_config):
    if config_name in machine_config:
        return int(machine_config[config_name])
    return int(supervisor_config.get(config_name, 0))


def generate_pke_features(config):
    curves = []
    if config.get('CONFIG_CMRT_PKE_NIST_P192'):
        curves.append('nist-p192')
    if config.get('CONFIG_CMRT_PKE_NIST_P224'):
        curves.append('nist-p224')
    if config.get('CONFIG_CMRT_PKE_NIST_P256'):
        curves.append('nist-p256')
    if config.get('CONFIG_CMRT_PKE_SECP256K1'):
        curves.append('secp256k1')
    if config.get('CONFIG_CMRT_PKE_NIST_P384'):
        curves.append('nist-p384')
    if config.get('CONFIG_CMRT_PKE_NIST_P521'):
        curves.append('nist-p521')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P192R1'):
        curves.append('brainpool-p192r1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P224R1'):
        curves.append('brainpool-p224r1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P256R1'):
        curves.append('brainpool-p256r1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P320R1'):
        curves.append('brainpool-p320r1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P384R1'):
        curves.append('brainpool-p384r1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P512R1'):
        curves.append('brainpool-p512r1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P192T1'):
        curves.append('brainpool-p192t1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P224T1'):
        curves.append('brainpool-p224t1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P256T1'):
        curves.append('brainpool-p256t1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P320T1'):
        curves.append('brainpool-p320t1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P384T1'):
        curves.append('brainpool-p384t1')
    if config.get('CONFIG_CMRT_PKE_BRAINPOOL_P512T1'):
        curves.append('brainpool-p512t1')
    if config.get('CONFIG_CMRT_PKE_ED25519_CURVE'):
        curves.append('ed25519')
    if config.get('CONFIG_CMRT_PKE_X25519_CURVE'):
        curves.append('x25519')
    if config.get('CONFIG_CMRT_PKE_X448_CURVE'):
        curves.append('x448')
    if config.get('CONFIG_CMRT_PKE_ED448_CURVE'):
        curves.append('ed448')
    if config.get('CONFIG_CMRT_PKE_FRP256_CURVE'):
        curves.append('frp256')
    if config.get('CONFIG_CMRT_PKE_SM2_CURVE'):
        curves.append('sm2')
    if config.get('CONFIG_CMRT_FFDH'):
        curves.append('ffdh')
    if config.get('CONFIG_CMRT_PKE_SM2_CURVE'):
        curves.append('sm2')
    return curves


def generate_hc(node, pos):
    if node.label == 's2hc':
        if pos == 2:
            name = 's2hc2' ; description = 'SHA2 second hash core'
        else:
            name = 's2hc' ; description = 'SHA2 hash core'
    elif node.label == 's3hc':
        if pos == 2:
            name = 's3hc2' ; description = 'SHA3 second hash core'
        else:
            name = 's3hc' ; description = 'SHA3 hash core'
    else:
        raise SystemExit(f"Unknown hc label '{node.label}'")

    hc = {'type': name, 'description': description,
          'features': {'modes': []}}

    if node.props['has-sha-224'].val:
        hc['features']['modes'].append('sha-224')
    if node.props['has-sha-256'].val:
        hc['features']['modes'].append('sha-256')
    if node.props['has-sha-384'].val:
        hc['features']['modes'].append('sha-384')
    if node.props['has-sha-512'].val:
        hc['features']['modes'].append('sha-512')
    if node.props['has-sha-512-224'].val:
        hc['features']['modes'].append('sha-512/224')
    if node.props['has-sha-512-256'].val:
        hc['features']['modes'].append('sha-512/256')
    if node.props['has-hmac'].val:
        hc['features']['modes'].append('hmac')
    if node.props['has-sha3-224'].val:
        hc['features']['modes'].append('sha3-224')
    if node.props['has-sha3-256'].val:
        hc['features']['modes'].append('sha3-256')
    if node.props['has-sha3-384'].val:
        hc['features']['modes'].append('sha3-384')
    if node.props['has-sha3-512'].val:
        hc['features']['modes'].append('sha3-512')
    if node.props['has-shake128'].val:
        hc['features']['modes'].append('shake128')
    if node.props['has-shake256'].val:
        hc['features']['modes'].append('shake256')

    return hc


def make_kdc_overrides():
    # Define overrides for QEMU values to be able to run FPGA builds in QEMU
    # This is the PNAK derived HMAC key from samples/cmrt/perso
    overrides = [{'derived':
                  '0x3697529bbea319d3c88843e5d939687a1ca366e76cbab62b6b45f05ae1970308',
                  'override':
                  '0x72fb89eb7414103c444028683d2dcda0b457b583568c8905a0174db1a2214246'},
                 {'derived':
                  '0x5708f3a9f4a775ae41495f398648e78c2cfe3a220ea7d71e9ea8f8e8ebe2b49b',
                  'override':
                  '0xFB9e7F6eefe352efc1c46dac26f27DCDedd61B747F95b0154775ed5a1042dc16'}
                 ]
    return overrides


def generate_hw_cores(dts, machine_config, supervisor_config):
    cores = []
    if has_boolean('CONFIG_CMRT_AES', machine_config, supervisor_config):
        aes = {'type': 'aes', 'description': 'AES crypto core',
               'features': {'modes': ['ecb', 'cbc', 'cfb', 'ctr', 'gcm'], 'keys': [128, 256]}}
        aes['features']['sw_entropy'] = False
        if dts.label2node['aes'].props['has-192'].val:
            aes['features']['keys'].append(192)
        if dts.label2node['aes'].props['has-cmac'].val:
            aes['features']['modes'].append('cmac')
        if dts.label2node['aes'].props['has-xts'].val:
            aes['features']['modes'].append('xts')
        if dts.label2node['aes'].props['has-ccm'].val:
            aes['features']['modes'].append('ccm')
        cores.append(aes)
        pass
    if has_boolean('CONFIG_CMRT_CC', machine_config, supervisor_config):
        cc = {'type': 'cc', 'description': 'Canary core'}
        cores.append(cc)
        pass
    if has_boolean('CONFIG_CMRT_CCP', machine_config, supervisor_config):
        cores.append({'type': 'ccp', 'description': 'ChaCha20/Poly core',
                      'features': {'modes': ['chacha', 'poly', 'chacha_poly_aead'],
                                   'keys': [128, 256]}})
        pass
    if has_boolean('CONFIG_CMRT_CSHC', machine_config, supervisor_config):
        cores.append({'type': 'cshc', 'description': 'Compact SHA hash core',
                      'features': {'modes': ['sha-224', 'sha-256', 'hmac']}})
        pass
    if has_boolean('CONFIG_CMRT_DMAC', machine_config, supervisor_config):
        cores.append({'type': 'dmac', 'description': 'DMA controller'})
        pass
    if has_boolean('CONFIG_CMRT_EAC', machine_config, supervisor_config):
        eac = {'type': 'eac', 'description': 'Error aggregator core',
               'features': { 'sw_halt': True }}
        cores.append(eac)
        pass
    if has_boolean('CONFIG_CMRT_EMC', machine_config, supervisor_config):
        cores.append({'type': 'emc', 'description': 'Entropy management core'})
        pass
    if has_boolean('CONFIG_SOC_FLASH_M25P80', machine_config, supervisor_config):
        cores.append({
            'type': 'm25p80',
            'description': 'm25p80 flash',
        })
        pass
    if has_boolean('CONFIG_CMRT_FMC', machine_config, supervisor_config):
        dts_fmc = dts.label2node['fmc']
        cores.append({'type': 'fmc', 'description': 'Feature management core',
                      'features': {'tdv_size': dts_fmc.props['tdv-size'].val,
                                   'feature_size': dts_fmc.props['feature-size'].val}})
        pass
    if has_boolean('CONFIG_CMRT_KDC', machine_config, supervisor_config):
        kdc = {'type': 'kdc', 'description': 'Key derivation core',
               'features': {'hw_state': hex(machine_config['CONFIG_CMRT_KDC_HW_STATE'])}}
        overrides = make_kdc_overrides()
        if overrides: kdc['overrides'] = overrides
        cores.append(kdc)
        pass
    if has_boolean('CONFIG_CMRT_KTC', machine_config, supervisor_config):
        cores.append({'type': 'ktc', 'description': 'Key transport core'})
        pass
    if has_boolean('CONFIG_CMRT_MPU', machine_config, supervisor_config):
        cores.append({'type': 'mpu', 'description': 'Memory protection unit'})
        pass
    if has_boolean('CONFIG_CMRT_OMC', machine_config, supervisor_config):
        omc = {'type': 'omc', 'description': 'OTP management core',
               'features': {'roots': dts.label2node['omc'].props['num-roots'].val,
                            'keysplits': dts.label2node['omc'].props['num-keysplits'].val,
                            'esw_rsvd_words': machine_config['CONFIG_CMRT_OMC_ESW_RSVD_WORDS'],
                            'esw_rsvd_first': has_boolean('CONFIG_CMRT_OMC_ESW_RSVD_FIRST',
                                                          machine_config, supervisor_config)}}
        omc['features']['emulated_otp'] = \
            has_boolean('CONFIG_CMRT_OMC_EMULATED_OTP', machine_config, supervisor_config)

        layout_version = dts.label2node['omc'].props['layout-version'].val
        omc['features']['layout_version'] = layout_version
        cores.append(omc)
        pass
    if has_boolean('CONFIG_CMRT_PKE', machine_config, supervisor_config):
        cores.append({'type': 'pke', 'description': 'Public key engine',
                      'features': {'version': hex(machine_config['CONFIG_CMRT_PKE_VERSION']),
                                   'ram_base': hex(dts.label2node['sram'].regs[0].addr),
                                   'ram_size': hex(dts.label2node['pkeram'].regs[0].size),
                                   'machine': generate_pke_features(machine_config),
                                   'supervisor': generate_pke_features(supervisor_config)}})
        pass
    if has_boolean('CONFIG_CMRT_PMU', machine_config, supervisor_config):
        cores.append({'type': 'pmu', 'description': 'Power management unit'})
        pass
    if has_boolean('CONFIG_CMRT_RSA', machine_config, supervisor_config):
        rsa = {'type': 'rsa', 'description': 'Virtual RSA core', 'features': {}}
        rsa['features']['crt'] = \
            has_boolean('CONFIG_CMRT_RSA_CRT', machine_config, supervisor_config)
        if has_boolean('CONFIG_CMRT_RSA_KEYGEN_DPA_RESIST', machine_config, supervisor_config):
            rsa['features']['keygen'] = 'dpa_resist'
        else:
            rsa['features']['keygen'] = 'fast'
        cores.append(rsa)
        pass
    if has_boolean('CONFIG_CMRT_SAC', machine_config, supervisor_config):
        sac = {'type': 'sac', 'description': 'System aperture core', 'features': {}}
        sac['features']['user_access'] = dts.label2node['sac'].props['user-access'].val
        cores.append(sac)
        pass
    if has_boolean('CONFIG_CMRT_SAC2', machine_config, supervisor_config):
        sac = {'type': 'sac2', 'description': '64bit system aperture core', 'features': {}}
        sac['features']['user_access'] = dts.label2node['sac'].props['user-access'].val
        cores.append(sac)
        pass
    if has_boolean('CONFIG_CMRT_SIC', machine_config, supervisor_config):
        sic = {'type': 'sic', 'description': 'System interface core', 'features': {}}
        sic['features']['has_root_table_status'] = True
        sic['features']['has_keys_perso_status'] = True
        sic['features']['soc_num_irqs'] = dts.label2node['sic'].props['num-irqs'].val
        sic['features']['sic_num_custom_regs'] = dts.label2node['sic'].props['num-custom'].val
        sic['features']['hlos2_tools'] = True
        cores.append(sic)
        pass
    if has_boolean('CONFIG_CMRT_SIC2', machine_config, supervisor_config):
        sic = {'type': 'sic2', 'description': 'System interface core', 'features': {}}
        sic['features']['has_root_table_status'] = True
        sic['features']['has_keys_perso_status'] = True
        sic['features']['has_boot_control'] = dts.label2node['sic'].props['has-boot-control'].val
        sic['features']['soc_num_irqs'] = dts.label2node['sic'].props['num-irqs'].val
        sic['features']['sic_num_custom_regs'] = dts.label2node['sic'].props['num-custom'].val
        sic['features']['sic_num_instances'] = dts.label2node['sic'].props['num-instances'].val
        sic['features']['hlos2_tools'] = True
        cores.append(sic)
        pass
    if has_boolean('CONFIG_CMRT_HC', machine_config, supervisor_config):
        hc = generate_hc(dts.label2node['hc0'], 1)
        cores.append(hc)
        pass
    if has_boolean('CONFIG_CMRT_HC2', machine_config, supervisor_config):
        hc = generate_hc(dts.label2node['hc3'], 2)
        cores.append(hc)
        pass
    if has_boolean('CONFIG_CMRT_SID', machine_config, supervisor_config):
        cores.append({'type': 'sid', 'description': 'Virtual SIC IRQ driver'})
        pass
    if has_boolean('CONFIG_CMRT_TMC', machine_config, supervisor_config):
        tmc = {'type': 'tmc', 'description': 'TRNG management core', 'features': {}}
        tmc['features']['eip76_trng'] = dts.label2node['tmc'].props['eip76-trng'].val
        tmc['features']['tmc_ext_entropy'] = dts.label2node['tmc'].props['tmc-ext-entropy'].val
        cores.append(tmc)
        pass
    if has_boolean('CONFIG_UART_SIFIVE', machine_config, supervisor_config):
        cores.append({'type': 'sifive', 'description': 'SiFive Freedom UART'})
        pass
    if has_boolean('CONFIG_UART_NS16550', machine_config, supervisor_config):
        cores.append({'type': 'ns16550', 'description': 'NS16550 UART'})
        pass
    if has_boolean('CONFIG_CMRT_UFC', machine_config, supervisor_config):
        cores.append({'type': 'ufc', 'description': 'Unbalanced feistel network core'})
        pass
    if has_boolean('CONFIG_CMRT_WHC', machine_config, supervisor_config):
        cores.append({'type': 'whc', 'description': 'Whirlpool hash core',
                      'features': {'modes': ['whirlpool']}})
        pass
    if has_boolean('CONFIG_CMRT_HSAES', machine_config, supervisor_config):
        cores.append({'type': 'hs_aes', 'description': 'Hight Speed AES core'})
        pass
    if has_boolean('CONFIG_CMRT_PDMA', machine_config, supervisor_config):
        cores.append({'type': 'pdma', 'description': 'PCIe DMA core'})
        pass
    # DCM exists by the virtue of PDMA
    if has_boolean('CONFIG_CMRT_PDMA', machine_config, supervisor_config):
        cores.append({'type': 'dcm', 'description': 'Data-flow Control Module'})
        pass
    if has_boolean('CONFIG_ETH_STELLARIS', machine_config, supervisor_config):
        cores.append({'type': 'eth_stellaris', 'description': 'Stellaris Ethernet'})
        pass
    if has_boolean('CONFIG_ETH_XAXIDMA', machine_config, supervisor_config):
        cores.append({'type': 'eth_xaxidma', 'description': 'Xilinx AXI Ethernet'})
        pass
    wdt_hw_start = dts.label2node['clint'].props['wdt-hw-start'].val
    cores.append({'type': 'timer', 'description': 'CMRT timer and watchdog',
                  'features': {'wdt_hw_start': wdt_hw_start}})

    return cores


def generate_machine_options(_dts, config):
    machine = {
        'fboot_has_aes': True, # AES is always in fboot now
        'fboot_has_ecdsa_full': bool(config.get('CONFIG_CMRT_FBOOT_HAS_ECDSA_FULL')),
        'fboot_has_ecdsa_p521': bool(config.get('CONFIG_CMRT_FBOOT_HAS_ECDSA_P521')),
        'fboot_has_ecdsa_p384': bool(config.get('CONFIG_CMRT_FBOOT_HAS_ECDSA_P384')),
        'fboot_has_rsa_verify': bool(config.get('CONFIG_CMRT_FBOOT_HAS_RSA_VERIFY')),
        'fboot_has_lms_verify': bool(config.get('CONFIG_CMRT_FBOOT_HAS_LMS_VERIFY')),
        'fboot_has_lms_hss_verify': bool(config.get('CONFIG_CMRT_FBOOT_HAS_LMS_HSS_VERIFY')),
        'fboot_has_xmss_verify': bool(config.get('CONFIG_CMRT_FBOOT_HAS_XMSS_VERIFY')),
        'fboot_has_xmss_mt_verify': bool(config.get('CONFIG_CMRT_FBOOT_HAS_XMSS_MT_VERIFY')),
        'sboot_in_rom': bool(config.get('CONFIG_CMRT_SBOOT_IN_ROM')),
        'rom_size': hex(config['CONFIG_CMRT_MACHINE_ROM_SIZE']),
        'sboot_has_pkhash': False,
        'supervisor_in_rom': bool(config.get('CONFIG_CMRT_SUPERVISOR_IN_ROM')),
        'fips_mode': bool(config.get('CONFIG_CMRT_FIPS_140_MODE')),
        'asil_b_mode': bool(config.get('CONFIG_CMRT_ASIL_B_MODE')),
        'has_ram_console': bool(config.get('CONFIG_RAM_CONSOLE')),
        'sac_ram_console': bool(config.get('CONFIG_CMRT_SAC_CONSOLE')),
        'ram_console_size': int(config.get('CONFIG_RAM_CONSOLE_BUFFER_SIZE', 0)),
        'ab_location_support': bool(config.get('CONFIG_CMRT_AB_LOCATION_SUPPORT')),
        'ab_image_support': bool(config.get('CONFIG_CMRT_AB_IMAGE_SUPPORT')),
        'encrypted_image_support': bool(config.get('CONFIG_CMRT_ENCRYPTED_IMAGE_SUPPORT')),
        'image_autoload_support': bool(config.get('CONFIG_CMRT_IMAGE_AUTOLOAD_SUPPORT')),
        'sys_clock_hw_cycles_per_sec': config['CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC'],
        'debug_build': bool(config.get('CONFIG_DEBUG')),
        'wait_before_boot': bool(config.get('CONFIG_WAIT_BEFORE_BOOT')),
        'machine_ram_size': int(config.get('CONFIG_CMRT_MACHINE_RAM_SIZE', 0)),
        'caliptra_support': bool(config.get('CONFIG_CMRT_CALIPTRA_SUPPORT')),
    }
    return machine


def generate_supervisor_options(_dts, config):
    supervisor = {
        'name': config.get('sv_name', 'unknown'),
        'in_rom': bool(config.get('CONFIG_CMRT_SUPERVISOR_IN_ROM')),
        'user_containers': bool(config.get('CONFIG_USERSPACE')),
        'has_ram_console': bool(config.get('CONFIG_RAM_CONSOLE')),
        'sac_ram_console': bool(config.get('CONFIG_CMRT_SAC_CONSOLE')),
        'ram_console_size': int(config.get('CONFIG_RAM_CONSOLE_BUFFER_SIZE', 0)),
        'ecies': bool(config.get('CONFIG_CMRT_ECIES')),
        'lms': bool(config.get('CONFIG_CMRT_SHSIG_LMS')),
        'lms_hss': bool(config.get('CONFIG_CMRT_SHSIG_LMS_HSS')),
        'xmss': bool(config.get('CONFIG_CMRT_SHSIG_XMSS')),
        'xmss_mt': bool(config.get('CONFIG_CMRT_SHSIG_XMSS_MT')),
        'xmss_all_modes': bool(config.get('CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES')),
        'with_tboot': config.get('with_tboot') == 'y',
        'sv_perf_meas': bool(config.get('CONFIG_SV_PERF_MEAS'))
    }
    if config.get('CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC'):
        supervisor['sys_clock_hw_cycles_per_sec'] = config['CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC']
    supervisor['debug_build'] = bool(config.get('CONFIG_DEBUG'))
    return supervisor


def make_json_config(dts_filenames, config_filenames, arg_vars, output_filename):
    machine_config = parse_cmrt_config(config_filenames[0])
    supervisor_config = parse_cmrt_config(config_filenames[1], arg_vars) \
        if len(config_filenames) > 1 else {}
    dts = edtlib.EDT(dts_filenames[0], [dts_filenames[1]])

    board = machine_config['CONFIG_BOARD']
    has_ethernet = bool(supervisor_config.get('CONFIG_NET_L2_ETHERNET'))
    cores = generate_hw_cores(dts, machine_config, supervisor_config)
    machine = generate_machine_options(dts, machine_config)
    supervisor = generate_supervisor_options(dts, supervisor_config)

    sog_base = dts.label2node['sog'].regs[0].addr
    sog_size = dts.label2node['sog'].regs[0].size
    try:
        rom_base = dts.label2node['rom'].regs[0].addr
        rom_size = dts.label2node['rom'].regs[0].size
    except KeyError:
        rom_base = 0x880000
        rom_size = 0
    sram_base = dts.label2node['sram'].regs[0].addr
    sram_size = dts.label2node['sram'].regs[0].size
    sram_fpga = machine_config['CONFIG_FPGA_SRAM_SIZE']
    otp_base = dts.label2node['otp'].regs[0].addr
    otp_size = dts.label2node['otp'].regs[0].size
    otp_esw = calculate_otp_esw(dts, machine_config)
    sboot_start = calculate_sboot_start(dts, machine_config)
    extmem_base = dts.label2node['extmem'].regs[0].addr
    extmem_size = dts.label2node['extmem'].regs[0].size
    extmem_fpga = machine_config['CONFIG_FPGA_EXTMEM_SIZE']
    try:
        extdev_base = dts.label2node['extdev'].regs[0].addr
        extdev_size = dts.label2node['extdev'].regs[0].size
    except KeyError:
        extdev_base = 0x100000
        extdev_size = 0
    cfi_enabled = bool(machine_config.get('CONFIG_CMRT_CFI'))

    board_config = {
        'board': board,
        'config_version': 3,
        'has_ethernet': has_ethernet,
        'cores': cores,
        'machine': machine,
        'supervisor': supervisor,
        'rom_base': hex(sog_base),
        'rom_size': hex(sog_size),
        'sram_base': hex(sram_base),
        'sram_size': hex(sram_size),
        'sram_fpga': hex(sram_fpga),
        'ext_rom_base': hex(rom_base),
        'ext_rom_size': hex(rom_size),
        'ext_mem_base': hex(extmem_base),
        'ext_mem_size': hex(extmem_size),
        'ext_mem_fpga': hex(extmem_fpga),
        'otp_base': hex(otp_base),
        'otp_size': hex(otp_size),
        'otp_esw': hex(otp_esw),
        'sboot_start': hex(sboot_start),
        'ext_dev_base': hex(extdev_base),
        'ext_dev_size': hex(extdev_size),
        'cfi_enabled': cfi_enabled,
    }
    with open(output_filename, 'w') as f:
        print(json.dumps(board_config, indent=4,
                         sort_keys=(sys.version_info < (3,6))), file=f)
    pass


def make_kernel_config(dts_filenames, config_filenames, output_filename):
    config = parse_cmrt_config(config_filenames[0])
    dts = edtlib.EDT(dts_filenames[0], [dts_filenames[1]])
    with open(output_filename, 'w') as f, redirect_stdout(f):
        # Write config for cmrt2.ko
        params = []

        if bool(config.get('CONFIG_FPGA_TYPE_VMK180')):
            devcfg_phys = 0x00000000 # vmk180 value
            sysctl_phys = 0xA4000000 # vmk180 value
            sic_phys = 0xA4800000 # vmk180 value
            dm_phys = 0xA5000000 # vmk180 value
        else:
            devcfg_phys = 0xF8007000 # zynq706 value
            sysctl_phys = 0x40000000 # zynq706 value
            sic_phys = 0x40800000 # zynq706 value
            dm_phys = 0x41200000 # zynq706 value
        params.append('devcfg_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(0x00000000, 0x0, devcfg_phys, 0x1000))
        params.append('sysctl_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(0x00000000, 0x1000, sysctl_phys, 0x1000))
        params.append('sic_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(0x00001000, 0x1000, sic_phys, 0x1000))
        params.append('dm_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(0x000FF000, 0x1000, dm_phys, 0x1000))

        sog_base = dts.label2node['sog'].regs[0].addr
        sog_size = dts.label2node['sog'].regs[0].size
        if bool(config.get('CONFIG_FPGA_TYPE_VMK180')):
            sog_phys = 0xA4100000 # vmk180 value
        else:
            sog_phys = 0x40100000 # zynq706 value
        sog_fpga = sog_size
        params.append('sog_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(sog_base, sog_size, sog_phys, sog_fpga))

        cfi_base = sog_base + sog_size
        cfi_size = sog_size
        if bool(config.get('CONFIG_CMRT_CFI')):
            if bool(config.get('CONFIG_FPGA_TYPE_VMK180')):
                cfi_phys = 0xA4180000 # vmk180 value
            else:
                cfi_phys = 0x40180000 # zynq706 value
            cfi_fpga = sog_size
        else:
            cfi_phys = 0x00000000
            cfi_fpga = 0x0
        params.append('cfi_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(cfi_base, cfi_size, cfi_phys, cfi_fpga))

        try:
            rom_base = dts.label2node['rom'].regs[0].addr
            rom_size = dts.label2node['rom'].regs[0].size
        except KeyError:
            rom_base = 0x880000
            rom_size = 0
        if bool(config.get('CONFIG_FPGA_TYPE_VMK180')):
            rom_phys = 0xA4200000 # vmk180 value
        else:
            rom_phys = 0x40200000 # zynq706 value
        rom_fpga = rom_size
        params.append('rom_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(rom_base, rom_size, rom_phys, rom_fpga))

        sram_base = dts.label2node['sram'].regs[0].addr
        sram_size = dts.label2node['sram'].regs[0].size
        if bool(config.get('CONFIG_FPGA_TYPE_VMK180')):
            sram_phys = 0xA4400000 # vmk180 value
        else:
            sram_phys = 0x40400000 # zynq706 value
        sram_fpga = config['CONFIG_FPGA_SRAM_SIZE']
        params.append('sram_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(sram_base, sram_size, sram_phys, sram_fpga))

        otp_base = dts.label2node['otp'].regs[0].addr
        otp_size = dts.label2node['otp'].regs[0].size
        if bool(config.get('CONFIG_FPGA_TYPE_VMK180')):
            otp_phys = 0xA4300000 # vmk180 value
        else:
            otp_phys = 0x40300000 # zynq706 value
        otp_fpga = otp_size
        params.append('otp_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(otp_base, otp_size, otp_phys, otp_fpga))

        extmem_base = dts.label2node['extmem'].regs[0].addr
        extmem_size = dts.label2node['extmem'].regs[0].size
        if bool(config.get('CONFIG_FPGA_TYPE_VMK180')):
            extmem_phys = 0xA6000000 # vmk180 value
        else:
            extmem_phys = 0x41500000 # zynq706 value
        extmem_fpga = config['CONFIG_FPGA_EXTMEM_SIZE']
        params.append('sac_conf=0x{:08x},0x{:08x},0x{:08x},0x{:08x},0,0'
                      .format(extmem_base, extmem_size, extmem_phys, extmem_fpga))

        print(' '.join(params))
    pass


def make_asciidoctor_config(dts_filenames, config_filenames, output_filename):
    machine_config = parse_cmrt_config(config_filenames[0])
    supervisor_config = parse_cmrt_config(config_filenames[1]) \
        if len(config_filenames) > 1 else {}
    _dts = edtlib.EDT(dts_filenames[0], [dts_filenames[1]])
    with open(output_filename, 'w') as f, redirect_stdout(f):
        # Write config for doc/cmrt/Makefile
        params = [ '-a', machine_config['CONFIG_BOARD'] ]
        if has_boolean('CONFIG_CMRT_SIC2', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_SIC2')
        else:
            params.append('-a CONFIG_CMRT_SIC')
            pass
        if has_boolean('CONFIG_USERSPACE', machine_config, supervisor_config):
            params.append('-a CONFIG_USERSPACE')
            pass
        if has_boolean('CONFIG_CMRT_PMU', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_PMU')
            pass
        if has_boolean('CONFIG_CMRT_SBOOT_IN_ROM', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_SBOOT_IN_ROM')
            pass
        if has_boolean('CONFIG_CMRT_SUPERVISOR_IN_ROM', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_SUPERVISOR_IN_ROM')
            pass
        if has_boolean('CONFIG_CMRT_CALIPTRA_SUPPORT', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_CALIPTRA_SUPPORT')
            pass
        if has_boolean('CONFIG_CMRT_CCP', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_CCP')
            pass
        if has_boolean('CONFIG_CMRT_FFDH', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_FFDH')
            pass
        if has_boolean('CONFIG_CMRT_ECIES', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_ECIES')
            pass
        if has_boolean('CONFIG_CMRT_OMC_EMULATED_OTP', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_OMC_EMULATED_OTP')
            pass
        if has_boolean('CONFIG_CMRT_SHSIG_LIBRARY', machine_config, supervisor_config):
            params.append('-a CONFIG_CMRT_SHSIG_LIBRARY')
            pass
        print(' '.join(params))
    pass


def make_usermode_config(dts_filenames, config_filenames, output_filename):
    machine_config = parse_cmrt_config(config_filenames[0])
    supervisor_config = parse_cmrt_config(config_filenames[1]) \
        if len(config_filenames) > 1 else {}
    dts = edtlib.EDT(dts_filenames[0], [dts_filenames[1]])
    with open(output_filename, 'w') as f, redirect_stdout(f):
        ram_base = dts.label2node['sram'].regs[0].addr
        print('#define CONFIG_RISCV_RAM_BASE_ADDR 0x{:x}'.format(ram_base))
        ram_size = dts.label2node['sram'].regs[0].size
        print('#define CONFIG_RISCV_RAM_SIZE_KB {}'.format(int(ram_size / 1024)))
        if dts.label2node['aes'].props['has-192'].val:
            print('#define CMRT_AES_HAS_192 1')
        if dts.label2node['aes'].props['has-cmac'].val:
            print('#define CMRT_AES_HAS_CMAC 1')
        if dts.label2node['aes'].props['has-xts'].val:
            print('#define CMRT_AES_HAS_XTS 1')
        if dts.label2node['aes'].props['has-ccm'].val:
            print('#define CMRT_AES_HAS_CCM 1')
        tdv_size = dts.label2node['fmc'].props['tdv-size'].val
        print('#define CMRT_FMC_TDV_SIZE {}'.format(tdv_size))
        feature_size = dts.label2node['fmc'].props['feature-size'].val
        print('#define CMRT_FMC_FEATURE_SIZE {}'.format(feature_size))
        if (dts.label2node['hc0'].props['has-shake128'].val or
            dts.label2node['hc3'].props['has-shake128'].val):
            print('#define CMRT_HC_HAS_SHAKE128 1')
        if (dts.label2node['hc0'].props['has-shake256'].val or
            dts.label2node['hc3'].props['has-shake256'].val):
            print('#define CMRT_HC_HAS_SHAKE256 1')
        otp_base = dts.label2node['otp'].regs[0].addr
        print('#define CONFIG_RISCV_OTP_BASE_ADDR 0x{:x}'.format(otp_base))
        print('#define CMRT_OTP_BASE 0x{:x}'.format(otp_base))
        otp_size = dts.label2node['otp'].regs[0].size
        print('#define CMRT_OTP_SIZE 0x{:x}'.format(otp_size))
        otp_layout_version = dts.label2node['omc'].props['layout-version'].val
        print('#define CONFIG_CRI_OMC_LAYOUT_VERSION {}'.format(otp_layout_version))
        keysplits_num = dts.label2node['omc'].props['num-keysplits'].val
        print('#define CONFIG_CRI_OMC_KEYSPLITS_NUM {}'.format(keysplits_num))
        roots_num = dts.label2node['omc'].props['num-roots'].val
        print('#define CONFIG_CRI_OMC_ROOTS_NUM {}'.format(roots_num))
        if has_boolean('CONFIG_CMRT_OMC_EMULATED_OTP', machine_config, supervisor_config):
            print('#define CONFIG_CMRT_OMC_EMULATED_OTP')
        rsvd_words = read_int('CONFIG_CMRT_OMC_ESW_RSVD_WORDS', machine_config, supervisor_config)
        print('#define CONFIG_CMRT_OMC_ESW_RSVD_WORDS {}'.format(rsvd_words))
        if has_boolean('CONFIG_CMRT_OMC_ESW_RSVD_FIRST', machine_config, supervisor_config):
            print('#define CONFIG_CMRT_OMC_ESW_RSVD_FIRST')
        print('#define CONFIG_CRI_AES_NAME "{}"'.format(dts.label2node['aes'].label))
        print('#define CONFIG_CRI_CC_NAME "{}"'.format(dts.label2node['cc'].label))
        print('#define CONFIG_CRI_CCP_NAME "{}"'.format(dts.label2node['ccp'].label))
        print('#define CONFIG_CRI_CSHC_NAME "{}"'.format(dts.label2node['hc2'].label))
        print('#define CONFIG_CRI_DMAC_NAME "{}"'.format(dts.label2node['dmac'].label))
        print('#define CONFIG_CRI_FMC_NAME "{}"'.format(dts.label2node['fmc'].label))
        print('#define CONFIG_CRI_HC_NAME "{}"'.format(dts.label2node['hc0'].label))
        print('#define CONFIG_CRI_HC2_NAME "{}"'.format(dts.label2node['hc3'].label))
        print('#define CONFIG_CRI_KDC_NAME "{}"'.format(dts.label2node['kdc'].label))
        print('#define CONFIG_CRI_KTC_NAME "{}"'.format(dts.label2node['ktc'].label))
        print('#define CONFIG_CRI_OMC_NAME "{}"'.format(dts.label2node['omc'].label))
        print('#define CONFIG_CRI_PKE_NAME "{}"'.format(dts.label2node['pke'].label))
        print('#define CONFIG_CRI_TMC_NAME "{}"'.format(dts.label2node['tmc'].label))
        print('#define CONFIG_CRI_SIC_NAME "{}"'.format(dts.label2node['sic'].label))
        print('#define CONFIG_CRI_WHC_NAME "{}"'.format(dts.label2node['hc1'].label))
        if supervisor_config.get('CONFIG_CMRT_SHSIG_LMS'):
            print('#define CONFIG_CMRT_SHSIG_LMS')
            pass
        if supervisor_config.get('CONFIG_CMRT_SHSIG_LMS_HSS'):
            print('#define CONFIG_CMRT_SHSIG_LMS_HSS')
            pass
        if supervisor_config.get('CONFIG_CMRT_SHSIG_XMSS'):
            print('#define CONFIG_CMRT_SHSIG_XMSS')
            pass
        if supervisor_config.get('CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES'):
            print('#define CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES')
            pass
        if supervisor_config.get('CONFIG_CMRT_SHSIG_XMSS_MT'):
            print('#define CONFIG_CMRT_SHSIG_XMSS_MT')
            pass
    pass

def main():
    if len(sys.argv) < 2:
        raise SystemExit(f"\nUsage: {sys.argv[0]} [var=val ...]"
                         "board.mk|board.json|kernel.param|config.asciidoctor|userconfig.h\n")
    config_files = []
    dts_files = []
    output_mk = None
    output_json = None
    output_param = None
    output_asciidoctor = None
    output_h = None
    arg_vars = {}
    for arg in sys.argv[1:]:
        l = arg.split('=', 1)
        if len(l) == 2: arg_vars[l[0]] = l[1]; continue
        if arg.endswith('.mk'): output_mk = arg; continue
        if arg.endswith('.json'): output_json = arg; continue
        if arg.endswith('.param'): output_param = arg; continue
        if arg.endswith('.asciidoctor'): output_asciidoctor = arg; continue
        if arg.endswith('.h'): output_h = arg; continue
        raise SystemExit(f"Cannot determine output format for '{arg}'")

    zephyr_base = os.getenv('ZEPHYR_BASE')
    builddir = os.getenv('BUILDDIR', 'build')
    build = '' if os.path.basename(os.getcwd()) == builddir else builddir + '/'

    app_dts = build + 'zephyr/zephyr.dts'
    dts_files.append(app_dts)
    app_bindings = zephyr_base + '/dts/bindings'
    dts_files.append(app_bindings)

    fboot_config = zephyr_base + '/samples/cmrt/fboot/' + builddir + '/zephyr/.config'
    if os.path.exists(fboot_config):
        config_files.append(fboot_config)
    app_config = build + 'zephyr/.config'
    config_files.append(app_config)

    if output_mk: make_mk_config(dts_files, config_files, output_mk)
    if output_json: make_json_config(dts_files, config_files, arg_vars, output_json)
    if output_param: make_kernel_config(dts_files, config_files, output_param)
    if output_asciidoctor: make_asciidoctor_config(dts_files, config_files, output_asciidoctor)
    if output_h: make_usermode_config(dts_files, config_files, output_h)
    pass


if __name__ == '__main__':
    main()
    pass
