#!/usr/bin/env python3

import os
import sys

file_path = sys.argv[1]
os.system('xxd -e ' + file_path + ' > temp.img')
os.system('tboot_formatter.py temp.img') # otp.hex will be generated

if file_path == "os.img":
    f = open("flash_os1.hex" , 'w')
elif file_path == "os.img2":
    f = open("flash_os2.hex" , 'w')

# 0x10000 is the offset from the base (0x1f_8000_0000)
# the offset could be changed
for i in range(0, 0x10000):
    f.write('00\n')
with open('os_temp.hex', mode='r', encoding='utf-8') as input_file:
    lines = input_file.readlines()
    for line in lines:
        ch_list_in_line = [line[i:i+2] for i in range(0, len(line)-1, 2)]
# result = [line[i:i+3] for i in range(0, len(line), 3)]   if want
        for ch in ch_list_in_line:
            f.write(ch)
            f.write('\n')

f.close()

os.system('rm temp.img')
os.system('rm os_temp.hex')
