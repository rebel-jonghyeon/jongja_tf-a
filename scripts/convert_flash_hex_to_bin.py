import sys

def decode_ascii_hex(ascii_hex_line):
    """Converts ASCII hex dump (like '3030 2030') to binary"""
    parts = ascii_hex_line.strip().split()
    binary_data = bytearray()
    for part in parts:
        for i in range(0, len(part), 2):
            byte_str = part[i:i+2]
            if len(byte_str) == 2:
                binary_data.append(int(byte_str, 16))
    return binary_data

def parse_hex_file(filename):
    result = bytearray()
    with open(filename, 'r') as f:
        for line in f:
            result += decode_ascii_hex(line)
    return result

def swap_4byte_endian(data):
    swapped = bytearray()
    for i in range(0, len(data), 4):
        chunk = data[i:i+4]
        if len(chunk) == 4:
            swapped += chunk[::-1]
        else:
            swapped += chunk
    return swapped

def main():
    if len(sys.argv) != 3:
        print(f"Usage: python3 {sys.argv[0]} <input.hex> <output.bin>")
        return 1

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    decoded = parse_hex_file(input_file)
    swapped = swap_4byte_endian(decoded)

    with open(output_file, "wb") as f:
        f.write(swapped)

    print(f"✅ Converted ASCII hex dump '{input_file}' → '{output_file}' with 4-byte endian swap.")

    return 0

if __name__ == "__main__":
    sys.exit(main())
