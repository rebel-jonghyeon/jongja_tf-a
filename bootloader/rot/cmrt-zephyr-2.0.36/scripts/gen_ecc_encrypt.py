#!/usr/bin/env python3

### 32 bit message & 7 bit parity
### OTP ECC
### 32-bit message {D31, ..., D1, D0}
### 7bit parity {P6, ..., P1, P0}
### P0 = D0 + D1 + D3 + D4 + D6 + D8 + D10 + D11 + D13 + D15 + D17 + D19 + D21 + D23 + D25 + D26 + D28 + D30
### P1 = D0 + D2 + D3 + D5 + D6 + D9 + D10 + D12 + D13 + D16 + D17 + D20 + D21 + D24 + D25 + D27 + D28 + D31
### P2 = D1 + D2 + D3 + D7 + D8 + D9 + D10 + D14 + D15 + D16 + D17 + D22 + D23 + D24 + D25 + D29 + D30 + D31
### P3 = D4 + D5 + D6 + D7 + D8 + D9 + D10 + D18 + D19 + D20 + D21 + D22 + D23 + D24 + D25
### P4 = D11 + D12 + D13 + D14 + D15 + D16 + D17 + D18 + D19 + D20 + D21 + D22 + D23 + D24 + D25
### P5 = D26 + D27 + D28 + D29 + D30 + D31
### P6 = D0 + D1 + D2 + D3 + D4 + D5 + D6 + D7 + D8 + D9 + D10 + D11 + D12 + D13 + D14 + D15 + D16 + D17 + D18 + D19 + D20 + D21 + D22 + D23 + D24 + D25 + D26 + D27 + D28 + D29 + D30 + D31 + P0 + P1 + P2 + P3 + P4 + P5

import sys
import os

#for line in lines:
#    line = line.strip()
#    print(line)

#P0 = [ 0, 1, 3, 4, 6, 8, 10, 11, 13, 15, 17, 19, 21, 23, 25, 26, 28, 30 ]
#P1 = [ 0, 2, 3, 5, 6, 9, 10, 12, 13, 16, 17, 20, 21, 24, 25, 27, 28, 31 ]
#P2 = [ 1, 2, 3, 7, 8, 9, 10, 14, 15, 16, 17, 22, 23, 24, 25, 29, 30, 31 ]
#P3 = [ 4, 5, 6, 7, 8, 9, 10, 18, 19, 20, 21, 22, 23, 24, 25 ]
#P4 = [ 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 ]
#P5 = [ 26, 27, 28, 29, 30, 31 ]
#P6 = [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, P0, P1, P2, P3, P4, P5 ]

parity_encoding = [
    [ 0, 1, 3, 4, 6, 8, 10, 11, 13, 15, 17, 19, 21, 23, 25, 26, 28, 30 ], # P0
    [ 0, 2, 3, 5, 6, 9, 10, 12, 13, 16, 17, 20, 21, 24, 25, 27, 28, 31 ], # P1
    [ 1, 2, 3, 7, 8, 9, 10, 14, 15, 16, 17, 22, 23, 24, 25, 29, 30, 31 ], # P2
    [ 4, 5, 6, 7, 8, 9, 10, 18, 19, 20, 21, 22, 23, 24, 25 ],               #P3
    [ 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 ],         #P4
    [ 26, 27, 28, 29, 30, 31 ], #P5
    [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31] #P6,  should be added with P0 + P1 + P2 + P3 + P4 + P5 at the end
]

if __name__ == "__main__":
    argument = sys.argv
    del argument[0]
    argument[0] = argument[0].lower()

    f = open("otp_ecc_temp.hex", 'w')

    result = []
    output_str = ""
    newline_needed = 0
    with open(argument[0], mode='r', encoding='utf-8') as input_file:
        lines = input_file.readlines()
        for line in lines:
            newline_needed +=1
            line = line.strip()
            data = bin(int(line,16))
            data = data.split('0b')[1]
            while len(data) < 32:
                data = '0' + data

            for li in parity_encoding:
                parity_result = 0
                for element in li:
                    parity_result += int(data[31-element])

                parity_result = parity_result % 2
                result.append(parity_result)

            result[6] += (result[0] + result[1] + result[2] + result[3] + result[4] + result[5] )
            result[6] = result[6] % 2
            # note that P0 -> result[0]
            # P6 -> result[6]

            output_str = "".join(map(str, result))[::-1]
            output_str = (hex(int(output_str, 2)))
            output_str = output_str.split('x')[1]
            if len(output_str) < 2:
                output_str = '0' + output_str

            if newline_needed % 4 == 0:
                f.write(output_str + '\n')
            else:
                f.write(output_str)
            result = []

    f.close()
    f = open("otp_ecc.hex", 'w')
    with open("otp_ecc_temp.hex", mode='r', encoding='utf-8') as input_file:
        lines = input_file.readlines()
        newline_needed = 0
        for line in lines:
            while len(line) < 8:
                line = '0' + line
            temp1 = line[0:2]
            temp2 = line[2:4]
            temp3 = line[4:6]
            temp4 = line[6:8]
            line = temp4 + temp3 + temp2 + temp1

            f.write(line + '\n')
    f.close()
    os.remove('./otp_ecc_temp.hex')
