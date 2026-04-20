import struct
import argparse

def swap_endian(input_filename, output_filename, data_type='int', to_endian='le'):
    with open(input_filename, 'rb') as input_file:
        with open(output_filename, 'wb') as output_file:
            while True:
                chunk = input_file.read(4)
                if len(chunk) != 4:
                    output_file.write(chunk)  # 남은 데이터는 그대로 출력
                    break
                if data_type == 'int':
                    if to_endian == 'le':
                        # 빅 엔디안 -> 리틀 엔디안
                        swapped_chunk = struct.pack('<I', struct.unpack('>I', chunk)[0])
                    else:
                        # 리틀 엔디안 -> 빅 엔디안
                        swapped_chunk = struct.pack('>I', struct.unpack('<I', chunk)[0])
                elif data_type == 'float':
                    if to_endian == 'le':
                        # 빅 엔디안 -> 리틀 엔디안
                        swapped_chunk = struct.pack('<f', struct.unpack('>f', chunk)[0])
                    else:
                        # 리틀 엔디안 -> 빅 엔디안
                        swapped_chunk = struct.pack('>f', struct.unpack('<f', chunk)[0])
                else:
                    raise ValueError("Unsupported data type. Use 'int' or 'float'.")
                output_file.write(swapped_chunk)

def main():
    parser = argparse.ArgumentParser(description='Swap endianness of a binary file.')
    parser.add_argument('input_file', help='Input binary file.')
    parser.add_argument('output_file', help='Output binary file.')
    parser.add_argument('--data_type', choices=['int', 'float'], default='int', help='Data type (int or float).')
    parser.add_argument('--to_endian', choices=['le', 'be'], required=True, help='Target endianness (le: little-endian, be: big-endian).')
    args = parser.parse_args()
    swap_endian(args.input_file, args.output_file, args.data_type, args.to_endian)
    print(f"Endianness swapped and saved to {args.output_file}")

if __name__ == "__main__":
    main()

