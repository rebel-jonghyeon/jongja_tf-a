import os
import sys
import json
import binascii
import struct

output_file = './binaries/flash_gpt.hex'

def func_otp(fd, img, addr, size):
	global tid
	try:
		with open('scripts/otp.json', 'r') as f:
			data = json.load(f)

			for value in data.values():
				ch_list = [value[i:i+2] for i in range(0, len(value)-1, 2)]
				for ch in (ch_list):
					fd.write(ch + ' ')
					tid += 1
					if tid % 16 == 0:
						fd.write('\n')
	except Exception as e:
		print(f"Exception: {e}")
		raise RuntimeError("otp write error")

	try:
		with open(img, "rb") as file:
			binary_data = file.read()
			hex_text = binascii.hexlify(binary_data)

			ch_list = [hex_text[i:i+2] for i in range(0, len(hex_text), 2)]
			for i in range(0, len(ch_list), 4):
				sub_list = ch_list[i:i+4][::-1]

				for ch in sub_list:
					fd.write(ch.decode() + ' ')
					tid += 1

					if tid % 16 == 0:
						fd.write('\n')

			while tid < size:
				fd.write('00' + ' ')
				tid += 1

				if tid % 16 == 0:
					fd.write('\n')
	except Exception as e:
		print(f"Exception: {e}")
		raise RuntimeError("sboot write error")


def func_phy_fw(img, size, stride):
	global tid
	try:
		with open(img, "r") as file:
			lines = file.readlines()

			for line in lines:
				ch_list = [line[i:i+2] for i in range(0, len(line)-1, 2)]
				sub_list = ch_list[0:stride][::-1]

				for ch in sub_list:
					fd.write(ch + ' ')
					tid += 1

					if tid % 16 == 0:
						fd.write('\n')

			while tid < size:
				fd.write('00' + ' ')
				tid += 1

				if tid % 16 == 0:
					fd.write('\n')
	except Exception as e:
		print(f"Exception: {e}")
		raise RuntimeError("phy fw write error")


def func_sboot(fd, img, addr, size):
	global tid
	cid = tid
	with open(img, "rb") as file:
		binary_data = file.read()
		hex_text = binascii.hexlify(binary_data)

		ch_list = [hex_text[i:i+2] for i in range(0, len(hex_text)-1, 2)]
		for i in range(0, len(ch_list), 4):
			sub_list = ch_list[i:i+4][::-1]

			for ch in sub_list:
				fd.write(ch.decode() + ' ')
				tid += 1

				if tid % 16 == 0:
					fd.write('\n')

		while (tid - cid) < size:
			fd.write('00' + ' ')
			tid += 1

			if tid % 16 == 0:
				fd.write('\n')


def func_rsvd(fd, img, addr, size):
	global tid
	cid = tid

	while (tid - cid) < size:
		fd.write('00' + ' ')
		tid += 1

		if tid % 16 == 0:
			fd.write('\n')

from enum import Enum
class ActivePart(Enum):
	ACTIVE_PART_ONE = int(hex(0x006f6e65), base=16)
	ACTIVE_PART_TWO = int(hex(0x0074776f), base=16)

class RecoveryFlag(Enum):
	NORMAL = 0
	BOOT_FAIL = 1
	FW_UPDATE = 2

class RecoveryReason(Enum):
	NORMAL = 0
	BOOT_FAIL = 1
	FW_UPDATE = 2

class IsPciePhySramLoad(Enum):
	NOTLOAD = int(hex(0x0), base=16)
	LOAD = int(hex(0x29272523), base=16)

def	func_info(fd, img, addr, size, pcie_phy_sram_load):
	global tid

	if pcie_phy_sram_load == 1:
		load_done = IsPciePhySramLoad.LOAD.value
	else:
		load_done = IsPciePhySramLoad.NOTLOAD.value
	header = binascii.hexlify(struct.pack("<L", int(hex(0x12345678), base=16)))
	header += binascii.hexlify(struct.pack("<L", ActivePart.ACTIVE_PART_ONE.value))
	header += binascii.hexlify(struct.pack("<L", int(hex(0x80000), base=16)))
	header += binascii.hexlify(struct.pack("<L", int(hex(0x880000), base=16)))
	header += binascii.hexlify(struct.pack("<L", RecoveryFlag.NORMAL.value))
	header += binascii.hexlify(struct.pack("<L", load_done))
	header += binascii.hexlify(struct.pack("<L", RecoveryReason.NORMAL.value))

	ch_list = [header[i:i+2] for i in range(0, len(header)-1, 2)]
	for i in range(0, len(ch_list), 4):
		sub_list = ch_list[i:i+4][::-1]

		for ch in sub_list:
			fd.write(ch.decode() + ' ')
			tid += 1

			if tid % 16 == 0:
				fd.write('\n')

	cid = tid
	while (tid - cid) < (size - 28):
		fd.write('00' + ' ')
		tid += 1

		if tid % 16 == 0:
			fd.write('\n')

	return


def func_size8(fd, img):
	global tid
	with open(img, "rb") as data:
		sz = len(data.read())
	header = binascii.hexlify(struct.pack("<ll", sz, ~sz))

	ch_list = [header[i:i+2] for i in range(0, len(header)-1, 2) ]
	for i in range(0, len(ch_list), 4):
		sub_list = ch_list[i:i+4][::-1]

		for ch in sub_list:
			fd.write(ch.decode() + ' ')
			tid += 1

			if tid % 16 == 0:
				fd.write('\n')


def func_dummy8(fd):
	global tid
	for i in range(0, 8):
		fd.write('00' + ' ')
		tid += 1

		if tid % 16 == 0:
			fd.write('\n')

tid = 0
def main(argv):
	global tid

	if len(argv) < 4:
		print(f"\nUsage: {sys.argv[0]} $SIGN(0/1) $USE_GPT(0/1) $PLATFORM(zebu/silicon)\n")
		return 1

	if argv[1] == '1':
		sign_img_file = "scripts/flash_gpt_map_sign.json"
	elif argv[1] == '0':
		sign_img_file = "scripts/flash_gpt_map.json"
	else:
		print("Invalid SIGN setting. Please specify either '0' (unsigned image) or '1' (signed image).")
		return 1

	if argv[2] == '0':	#preload image - gpt have only bl1
		gpt_bl1 = True
	elif argv[2] == '1':
		gpt_bl1 = False
	else:
		print("Invalid USE_GPT setting. Please specify either '0' (preload image) or '1' (normal gpt image).")
		return 1

	if argv[3] == 'zebu':
		plat_zebu = True
	elif argv[3] == 'silicon':
		plat_zebu = False
	else:
		print("Invalid platform. Please specify either 'zebu' or 'silicon'.")
		return 1

	fd = None
	try:
		fd = open(output_file, 'w')
		tid = 0

		is_phy_sram_load=0
		if len(sys.argv) == 5:
			is_phy_sram_load = argv[4]
			is_phy_sram_load = int(bool(is_phy_sram_load))

	# Reserved1 -- 512KB
		with open(sign_img_file, 'r') as f:
			data = json.load(f)

			if "reserved1" in data:
				for partition in data["reserved1"]:
					img = partition['image']
					addr = int(partition['address'], 16)
					size = int(partition['size']) * 1024
					print(f"Name: {partition['name']}, Image: {partition['image']}, addr: {hex(addr)}, size: {(size)}KiB")

					if partition['name'] == "otp":
						func_otp(fd, img, addr, size)
						continue
					# Header 16 Bytes
					# 4 Bytes: a size of sboot_n(tf-a.bl1)
					# 4 Bytes: mirro info of the the size
					# 8 Bytes: 0x0 dummy for DMA performance
					elif partition['name'] == "sboot_n":
						func_size8(fd, img)
						func_dummy8(fd)
						func_sboot(fd, img, addr, size - 16)

						if gpt_bl1 == True:
							raise StopAsyncIteration()
						else:
							continue
					elif partition['name'] == "reserved":
						func_rsvd(fd, img, addr, size)
						continue
					elif partition['name'] == "partition_info":
						func_info(fd, img, addr, size, is_phy_sram_load)
						continue

	# GPT1 -- address : 0x80000 , size : 7680KiB
			GPTfile = "./scripts/p1.part"
			if os.path.exists(GPTfile):
				print("GPT partition p1.part file exist, delete it")
				os.remove(GPTfile)

			ID = 0
			if "partition1" in data:
				for partition in data["partition1"]:
					name = partition['name']
					img = partition['image']
					sizeKB = int(partition['size'])

					if partition['name'] == "loc":
						addr = int(partition['address'], 16)
						size = int(partition['size']) * 1024
						print(f"partition1 address: {hex(addr)}, size : {(size)}KiB")

						cid = tid
						with open(img, "rb") as file:
							binary_data = file.read()
							hex_text = binascii.hexlify(binary_data)

							ch_list = [hex_text[i:i+2] for i in range(0, len(hex_text)-1, 2)]
							for i in range(0, len(ch_list), 4):
								sub_list = ch_list[i:i+4][::-1]

								for ch in sub_list:
									fd.write(ch.decode() + ' ')
									tid += 1

									if tid % 16 == 0:
										fd.write('\n')

							while (tid - cid) < size:
								fd.write('00' + ' ')
								tid += 1

								if tid % 16 == 0:
									fd.write('\n')

					elif partition['name'] == "pcie_phy" or partition['name'] == "ucie_phy":
						print(f"PHY FW : {name}, size : {sizeKB}KiB")

						bin_image = "binaries/" + name + ".bin"
						if partition['name'] == "ucie_phy":
							if plat_zebu == True:
								img = partition['image_for_zebu']

						with open(bin_image, "wb") as outfd:
							with open(img, "r") as infd:
								lines = infd.readlines()
								for line in lines:
									line = line.strip()
									if line:
										rline = line[6:8] + line[4:6] + line[2:4] + line[0:2]
										outfd.write(binascii.unhexlify(rline))

						ID = ID + 1
						print(f"ID : {ID}, Name: {partition['name']}, Image: {bin_image}, size: {(sizeKB)}KiB")
						os.system(f"./scripts/gen_gpt_partition.sh {ID} {name} {bin_image} {sizeKB}")

					else:
						ID = ID + 1
						print(f"ID : {ID}, Name: {partition['name']}, Image: {partition['image']}, size: {(sizeKB)}KiB")
						os.system(f"./scripts/gen_gpt_partition.sh {ID} {name} {img} {sizeKB}")

	# Reserved2 -- 512KB
			if "reserved2" in data:
				for partition in data["reserved2"]:
					img = partition['image']
					addr = int(partition['address'], 16)
					sizeKB = int(partition['size'])
					print(f"Name: {partition['name']}, Image: {partition['image']}, addr: {hex(addr)}, size: {(sizeKB)}KiB")

					if partition['name'] == "loc":
						addr = int(partition['address'], 16)
						size = int(partition['size']) * 1024

						cid = tid
						while (tid - cid) < size:
							fd.write('00' + ' ')
							tid += 1

							if tid % 16 == 0:
								fd.write('\n')

	# GPT2 -- address : 0x880000 , size : 7680KiB
			if not os.path.exists(GPTfile):
				print("GPT partition file not created : p1.part")
				return 1
			if "partition2" in data:
				for partition in data["partition2"]:
					img = partition['image']
					size = int(partition['size'])

					if partition['name'] == "loc":
						addr = int(partition['address'], 16)
						size = int(partition['size']) * 1024
						print(f"partition2 address: {hex(addr)}, size : {(size)}KiB")

						cid = tid
						with open(img, "rb") as file:
							binary_data = file.read()
							hex_text = binascii.hexlify(binary_data)

							ch_list = [hex_text[i:i+2] for i in range(0, len(hex_text)-1, 2)]
							for i in range(0, len(ch_list), 4):
								sub_list = ch_list[i:i+4][::-1]

								for ch in sub_list:
									fd.write(ch.decode() + ' ')
									tid += 1

									if tid % 16 == 0:
										fd.write('\n')

							while (tid - cid) < size:
								fd.write('00' + ' ')
								tid += 1

								if tid % 16 == 0:
									fd.write('\n')

	except StopAsyncIteration:
		print(f"Flash Done for Preload BL1")

	except Exception as e:
		print(f"Exception: {e}")
		return 1

	finally:
		if fd is not None:
			fd.close()

	return 0

if __name__ == "__main__":
    sys.exit(main(sys.argv))
