import sys

def process_hex_file(input_path, output_path):
    with open(input_path, 'r') as f:
        hex_str = f.read()

    bytes_list = hex_str.strip().replace('\n', ' ').split()
    result = []
    for i in range(0, len(bytes_list), 4):
        chunk = bytes_list[i:i+4]
        if len(chunk) < 4:
            chunk += ['00'] * (4 - len(chunk))  # padding 0 for empty high bits
        normal_chunk = ''.join(chunk)
        result.append(normal_chunk)

    with open(output_path, 'w') as f_out:
        for line in result:
            f_out.write('0x' + line + '\n')

    return 0

if __name__ == "__main__":
    input_file = './binaries/flash_gpt.hex'
    output_file = 't32_flash_gpt.hex'
    ret = process_hex_file(input_file, output_file)
    print(f"'{output_file}' has been generated for flash write with t32")
    sys.exit(ret)

