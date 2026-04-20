#!/usr/bin/env python3
"""
Log Hash Decoder
"""

import csv
import re
import os
import sys
import argparse
from typing import Dict, List, Tuple, Optional

class TxtDecoder:
    """
    Decodes hashed log messages in .txt file back to their original string format.
    """
    def __init__(self):
        # dict: {hash_id: original_format_string}
        self.hash_map: Dict[str, str] = {}
        self.log_pattern = re.compile(r'(0x[0-9A-Fa-f]{8})(?:\s+(.*))?')

    def load_hash_map(self, csv_file_path: str) -> bool:
        """
        Load hash mappings from hash_map.csv.
        """
        if not os.path.exists(csv_file_path):
            print(f"Error: CSV file not found: {csv_file_path}")
            return False

        print(f"Loading hash map from: {csv_file_path}")

        try:
            with open(csv_file_path, 'r', encoding='utf-8') as file_handle:
                csv_lines = [line for line in file_handle if not line.strip().startswith('#')]

            csv_reader = csv.DictReader(csv_lines)
            loaded_count = 0

            for row in csv_reader:
                hash_32bit = row.get('Hash32bit', '').strip()
                original = row.get('Original', '').strip()

                if original.startswith('"') and original.endswith('"'):
                    original = original[1:-1] #remove ""

                if hash_32bit and original:
                    self.hash_map[hash_32bit] = original
                    loaded_count += 1

            print(f"Loaded {loaded_count} hash mappings")
            return loaded_count > 0

        except (OSError, csv.Error, UnicodeDecodeError) as error:
            print(f"Error loading CSV {csv_file_path}: {error}")
            return False

    def parse_txt_line(self, raw_line: str) -> Tuple[Optional[str], List[str]]:
        """
        Parse a log line to extract hash ID and runtime data.
        Tuple (0x1234ABCD, data1 data2)
        """
        raw_line = raw_line.strip()

        match = self.log_pattern.search(raw_line)
        if not match:
            return None, []

        hash_id = match.group(1)
        args_str = match.group(2).strip() if match.group(2) else ''
        runtime_data = args_str.split() if args_str else []

        return hash_id, runtime_data

    def decode_txt_line(self, raw_line: str) -> str:
        """
        Decode a single log line by replacing hash with original string.
        0x1234ABCD data1 data2  -> Original format with data1, data2
        """
        hash_id, runtime_data = self.parse_txt_line(raw_line)

        if not hash_id or hash_id not in self.hash_map:
            return raw_line

        original_format = self.hash_map[hash_id]

        try:
            if runtime_data:
                pattern = r'%[#\-+ 0]*(?:\*|\d+)?(?:\.(?:\*|\d+))?[hlL]*[diouxXeEfFgGaAcspn%]'
                format_specifiers = re.findall(pattern, original_format)
                if len(format_specifiers) == 1:
                    combined_arg = ' '.join(runtime_data)
                    decoded_message = re.sub(pattern, combined_arg, original_format, count=1)
                else:
                    for arg in runtime_data:
                        original_format = re.sub(pattern, arg, original_format, count=1)
                    # re.sub = search + replace
                    decoded_message = original_format
            else:
                decoded_message = original_format

            decoded_message = decoded_message.replace('\\r\\n', '\r\n')
            decoded_message = decoded_message.replace('\\n', '\n')
            return decoded_message
        except (ValueError, TypeError, IndexError) as error:
            print(f"Format error for hash {hash_id}: {error}")
            return raw_line

    def decode_txt_file(self, input_file: str) -> bool:
        """
        decode_txt_file -> decode_txt_line -> parse_txt_line
        """
        base_name = os.path.splitext(input_file)[0]
        output_file = f"{base_name}_decoded.txt"

        try:
            print(f"Decoding text file: {input_file} -> {output_file}")

            decoded_lines = []
            total_lines = 0
            decoded_count = 0

            with open(input_file, 'r', encoding='utf-8') as file_input:
                for line in file_input:
                    total_lines += 1
                    original_line = line.rstrip()
                    decoded_line = self.decode_txt_line(line)

                    if decoded_line != original_line:
                        decoded_count += 1

                    decoded_lines.append(decoded_line)

            with open(output_file, 'w', encoding='utf-8') as file_output:
                for line in decoded_lines:
                    file_output.write(line)

            print(f"Decoded {decoded_count}/{total_lines} lines")
            print(f"Output saved to: {output_file}")
            return True

        except (OSError, UnicodeDecodeError) as error:
            print(f"Error decoding file {input_file}: {error}")
            return False

def main():
    """
    there are two modes:
    1. Text File Decoding
    2. Directory Restoration
    """
    parser = argparse.ArgumentParser(
        description='Log Hash Decoder - Unified decoder for text files and directories',
        epilog='''Usage examples:
  %(prog)s                                   # Decode entire _hash directory (auto mode)
  %(prog)s hash_map.csv log.txt              # Decode specific text file
        ''',
        formatter_class=argparse.RawDescriptionHelpFormatter
    )

    parser.add_argument('csv_file', nargs='?',
                       help='Path to hash_map.csv file (for text mode)')

    parser.add_argument('txt_file', nargs='?',
                       help='Text file path to decode (for text mode)')

    args = parser.parse_args()

    if not args.csv_file and not args.txt_file:
        print("=== Directory Restoration Mode ===")
        process_hash_directory()

    elif args.csv_file and args.txt_file:
        print("=== Text File Decoding Mode ===")
        process_text_file(args.csv_file, args.txt_file)

    else:
        print("Error: Invalid arguments")
        print()
        print("Usage:")
        print("  log_hash_decoder.py                        # Directory restoration mode")
        print("  log_hash_decoder.py <csv_file> <txt_file>  # Text file decoding mode")
        print()
        print("Run 'log_hash_decoder.py --help' for more information")
        sys.exit(1)


def process_text_file(csv_file_arg, txt_file_arg):
    """main process for text file decoding"""
    csv_file_path = os.path.abspath(csv_file_arg)
    txt_file_path = os.path.abspath(txt_file_arg)

    if not os.path.exists(csv_file_path):
        print(f"Error: CSV file not found: {csv_file_path}")
        sys.exit(1)

    if not os.path.exists(txt_file_path):
        print(f"Error: Text file not found: {txt_file_path}")
        sys.exit(1)

    print(f"CSV file: {csv_file_path}")
    print(f"Text file: {txt_file_path}")

    decoder = TxtDecoder()
    if not decoder.load_hash_map(csv_file_path):
        print("Failed to load hash mappings!")
        sys.exit(1)

    if decoder.decode_txt_file(txt_file_path):
        print("Text file decoding completed successfully!")
    else:
        print("Text file decoding failed!")
        sys.exit(1)


def process_hash_directory():
    """Decode Directory by importing dir decoder"""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_dir = os.path.dirname(os.path.dirname(script_dir))
    hash_dir = f"{project_dir}"
    csv_file = os.path.join(hash_dir, "scripts", "log_hash", "hashmap.csv")

    print("Directory Decode Mode")
    print(f"Script directory: {script_dir}")
    print(f"Hash directory: {hash_dir}")
    print(f"CSV file: {csv_file}")


    if not os.path.exists(hash_dir):
        print(f"Error: Hash directory not found: {hash_dir}")
        print("Please run the encoder first or provide CSV and text file paths explicitly")
        sys.exit(1)

    if not os.path.exists(csv_file):
        print(f"Error: Hash map CSV not found: {csv_file}")
        print("Expected location: {project_name}_hash/scripts/log_hash/hashmap.csv")
        sys.exit(1)

    # Import log_hash_directory_decoder only when needed for directory decoding
    try:
        from log_hash_directory_decoder import HashDecoder # pylint: disable=C0415
    except ImportError:
        print("Error: log_hash_directory_decoder.py is required for directory decoding mode")
        sys.exit(1)

    try:
        decoder = HashDecoder(hash_dir)

        if not decoder.load_hash_map(csv_file):
            print("Failed to load hash mappings!")
            sys.exit(1)

        if decoder.decode_directory():
            print("Directory restoration completed successfully!")
            return True
        print("Directory restoration failed!")
        sys.exit(1)

    except (OSError, ImportError, AttributeError) as error:
        print(f"Error during directory restoration: {error}")
        sys.exit(1)

if __name__ == "__main__":
    main()
