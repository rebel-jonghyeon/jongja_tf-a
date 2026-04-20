import os
import sys
import json
import binascii
import struct

output_file = 'binaries/flash.hex'

def func_otp(fd, img, size):
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


def func_phy_fw(fd, img, size, stride):
	global tid
	try:
		# header = binascii.hexlify(struct.pack("<ll", size, ~size))

		# ch_list = [header[i:i+2] for i in range(0, len(header)-1, 2) ]
		# for i in range(0, len(ch_list), 4):
		# 	sub_list = ch_list[i:i+4][::-1]

		# 	for ch in sub_list:
		# 		fd.write(ch.decode() + ' ')
		# 		tid += 1

		# 		if tid % 16 == 0:
		# 			fd.write('\n')

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
	if len(sys.argv) != 2:
		print(f"\nUsage: {sys.argv[0]} $SIGN(0/1)\n")
		return

	try:
		fd = open(output_file, 'w')
		tid = 0

		if argv[1] == '1':
			sign_img_file = "scripts/flash_map_sign.json"
		elif argv[1] == '0':
			sign_img_file = "scripts/flash_map.json"
		else:
			return

		with open(sign_img_file, 'r') as f:
			data = json.load(f)

			for partition in data["partition1"]:
				img = partition['image']
				addr = int(partition['address'], 16)
				size = int(partition['size']) * 1024
				print(f"Image: {partition['image']}, addr: {hex(addr)}, size: {hex(size)}")

				if partition['name'] == "otp":
					func_otp(fd, img, size)
					continue

				while tid < addr:
					fd.write('00' + ' ')
					tid += 1

					if tid % 16 == 0:
						fd.write('\n')

				if partition['name'] == "ucie phy":
					func_phy_fw(fd, img, size, 4)
					continue
				# Header 16 Bytes
				# 4 Bytes: a size of sboot_n(tf-a.bl1)
				# 4 Bytes: mirro info of the the size
				# 8 Bytes: 0x0 dummy for DMA performance
				# elif partition['name'] == "sboot_n":
				# 	func_size8(fd, img)
				# 	func_dummy8(fd)
				# 	size = size - 16	# header 16B
				# elif partition['name'] == "tboot_s":
				# 	size = size			# tboot_s has header already
				# else:
				# 	func_size8(fd, img)
				# 	size = size - 8		# header 8B

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

	except Exception as e:
		print(f"Exception: {e}")

	finally:
		fd.close()

if __name__ == "__main__":
    sys.exit(main(sys.argv))
