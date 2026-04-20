import sys

name = sys.argv[1]
input_file = name + ".memh"
output_file = name + ".h"


# Read input file
with open(input_file, 'r') as file:
    lines = file.readlines()

# Process the lines
converted_data = []
for line in lines:
    line = line.strip()
    if line:
        converted_data.append('0x' + line)

# Generate the output C header file
with open(output_file, 'w') as file:
    file.write('unsigned long '+ name +'_bin[] = {\n\t')
    file.write(',\n\t'.join(converted_data))
    file.write('\n};\n\n')
    file.write('unsigned int '+ name + '_bin_len = {};\n'.format(len(converted_data)))

