#!/usr/bin/env python3
import sys

argument = sys.argv

f = open("otp.hex", 'w')

del argument[0]
with open(argument[0], mode='r', encoding='utf-8') as input_file:
    lines = input_file.readlines()
    for line in lines:
        line=line.replace("\n", "")
        lines = line.split(':')[1]
        line = lines.split(' ')
        for i in range(1,5):
            f.write(line[i])
            f.write('\n')

f.close()
