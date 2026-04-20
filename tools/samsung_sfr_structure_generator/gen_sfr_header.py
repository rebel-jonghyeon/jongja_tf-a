# Copyright (c) 2024 SAMSUNG Electronics
# SPDX-License-Identifier: MIT

import sys

from queue import PriorityQueue
import re #for extract numbers from strings

pp_sfr = PriorityQueue() # priority queue for sorting accroding to SFR offset between SFRS
pp_bitfield = PriorityQueue() # priority queue for sorting accroding to bitfield offset within a SFR


license_string = \
'''/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */
'''

reserved_count = 0

def calculate_sfr_offset(cur_addr, next_addr):
    global reserved_count
    result = next_addr - cur_addr
    if result == 0 or result == 4:
        return 0

    if result % 4 != 0:
        print("there is error calculating the offset \n")
        exit(-1)

    result = int(result / 4) - 1

    if result != 0:
        reserved_count+=1

    return result   # return the times how many uint32_t needed.

def sort_sfr(sfr_desc_filename, ordered_sfr_list):
    sfr_num = 0 # number of SFR
    sfr_map = []
    with open(sfr_desc_filename, mode='r', encoding='utf-8') as input_file:
        sfr_name = ""
        offset = 0
        str_range = 0
        lines = input_file.readlines()
        for line in lines:
            if line == '\n':
                print("break")
                break

            line=line.replace("\t\t", "\t")
            line=line.replace("\n", "")
            splits = line.split('\t')

            if splits[0] == '': # in this case, splits var indicates bitfield
            #ex)
            # ['', 'BAR0_START', '[31:4]']
            # ['', 'BAR0_TYPE', '[2:1]']
            # extract 31, 2 with pattern below
                pattern = "([0-9]+)"
            #convert re.Match class to int class
                numbers = int(re.search(pattern, splits[2]).group())
            # ex [7:0] --> 7
                #python pq only supports minheap, which means the lower value it has, the higher priority it will has
                param = (numbers, splits)
                pp_bitfield.put(param)

            else: # in this case, splits var indicates SFR
                if pp_bitfield.qsize() != 0: # in this case, splits indicates SFR which is not the first one.
                                # handle the bitfields in pp_bitfield for previous SFR
                    sfr_map.append([])
                    sfr_map[sfr_num].append(sfr_name)
                    sfr_map[sfr_num].append(offset)
                    sfr_map[sfr_num].append(str_range)
                    sfr_map[sfr_num].append(pp_bitfield.qsize())

                    while not pp_bitfield.empty():
                        sfr_map[sfr_num].append(pp_bitfield.get()[1])
                    sfr_num = sfr_num + 1

                sfr_name = splits[0] # name of SFR
                offset = splits[1]
                pattern_range = "([0-9]+)"
                #convert re.Match class to int class
                str_range = int(re.search(pattern_range, splits[2]).group()) #range should be this order [bigger:smaller]


    if pp_bitfield.qsize() != 0: # in this case, splits indicates SFR which is not the first one.
        sfr_map.append([])
        sfr_map[sfr_num].append(sfr_name)
        sfr_map[sfr_num].append(offset)
        sfr_map[sfr_num].append(str_range)
        sfr_map[sfr_num].append(pp_bitfield.qsize())

        while not pp_bitfield.empty():
            sfr_map[sfr_num].append((pp_bitfield.get())[1])

    for sfr_info in sfr_map:
        pp_sfr.put(((int(sfr_info[1],16)), sfr_info))

    i = 0
    while not pp_sfr.empty():
        ordered_sfr_list.append([])
        ordered_sfr_list[i].append(pp_sfr.get()[1])
        ordered_sfr_list[i].append(sfr_desc_filename + "_" + ordered_sfr_list[i][0][0]) # sfr type name
        i+=1

    #print(ordered_sfr_list) # to debug ordered_sfr_list result

def create_sfr_union(sfr_desc_filename, ordered_sfr_list):
    header_file = sfr_desc_filename + ".h"
    f = open(header_file, 'w')

    i = 0
    var_type = ""
    current_offset = 0
    target_offset = 0

    f.write(license_string)
    f.write('\n')

    f.write('#pragma once\n\n')

    for sfr in ordered_sfr_list:
        target_offset = int(sfr[0][1], 16)

        #[i][0][0] : sfr name
        #[i][0][1] : offset
        # ...
        #[i][1] : sfr type name (will be used as union type)
        f.write("union " + ordered_sfr_list[i][1].lower() + " {") # sfr tpye name (ip + sfr name)

        f.write("\n\tstruct {")

        current_bit = 0
        target_s_bit = 0
        target_e_bit = 0
        range_bit = 0
        reserved_bit = 0
        reserved_bit_count = 0
        accumulated_bit = 0
        for bitfield in range(0, sfr[0][3]):
            bit_range_pattern = "([0-9]+)"
            range_list = re.findall(bit_range_pattern, sfr[0][4 + bitfield][2])
            target_s_bit = int(range_list[1])
            target_e_bit = int(range_list[0])
            range_bit = target_e_bit - target_s_bit + 1

            bit_offset = target_s_bit - current_bit
            if ordered_sfr_list[i][0][2] == 31:
                var_type = "uint32_t"
            elif ordered_sfr_list[i][0][2] == 63:
                var_type = "uint64_t"
            if bit_offset != 0:
                f.write("\n\t\t" + var_type + " " + "reserved_bit_" + str(reserved_bit_count) + ":" + str(bit_offset) + ";")
                reserved_bit_count+=1


            if range_bit == 32 or range_bit == 64:
                f.write("\n\t\t" + var_type + " " + sfr[0][4 + bitfield][1].lower() + ";")
            else:
                f.write("\n\t\t" + var_type + " " + sfr[0][4 + bitfield][1].lower() + ":" + str(range_bit) + ";")

            f.write(" /* " + sfr[0][4 + bitfield][2] + " */")
            current_bit = target_e_bit + 1

        f.write("\n\t};")

        f.write("\n\t" + var_type + " val;");

        f.write("\n};\n\n")

        #f.write("\n\t\t
        current_offset = target_offset
        i+=1

    f.close()




def create_sfr_header(sfr_desc_filename, ordered_sfr_list):
    header_file = sfr_desc_filename + ".h"
    f = open(header_file, 'a')

    f.write("struct " + sfr_desc_filename + " {")
    ##################################
    #   struct arguemnt_name {
    ##################################
    #f.write("\n\tstruct {")
    i = 0
    var_type = ""
    current_offset = 0
    target_offset = 0

    for sfr in ordered_sfr_list:
        reserved_num = 0
        target_offset = int(sfr[0][1], 16)
        if ordered_sfr_list[i][0][2] == 31:
            var_type = "uint32_t"
        elif ordered_sfr_list[i][0][2] == 63:
            var_type = "uint64_t"

        if i == 0:
            if target_offset != 0x0:
                reserved_num = calculate_sfr_offset(-4, target_offset)
        else:
            reserved_num = calculate_sfr_offset(current_offset, target_offset)

        if reserved_num != 0:
            if reserved_num == 1:
                f.write("\n\tuint32_t " + "reserved_" + str(reserved_count) + ";")
            else:
                f.write("\n\tuint32_t " + "reserved_" + str(reserved_count) + "[" + str(reserved_num) + "];")

        f.write("\n\tunion " + ordered_sfr_list[i][1].lower() + " " + ordered_sfr_list[i][0][0].lower() + ";")
        f.write(" /* offset : " + sfr[0][1] + " */")

        current_offset = target_offset
        i+=1

    f.write("\n};")

    f.close()
    print("####\tdone with generating \t%s\t IP's SFR header\t####\n" % sfr_desc_filename)
    print("####\tplease refer to \t%s.h file\t####" % sfr_desc_filename)


if __name__ == "__main__":
    argument = sys.argv
    del argument[0] # first arugment will be the name of this script. so remove it.
    print("####\tgenerating \t%s\t IP's SFR header\t####\n" % argument[0])
	# sfr_desc_filename it should be the name of the file that has info of SFR

    ordered_sfr_list = []
    argument[0] = argument[0].lower()

    sort_sfr(argument[0], ordered_sfr_list)
    create_sfr_union(argument[0], ordered_sfr_list)
    create_sfr_header(argument[0], ordered_sfr_list)
