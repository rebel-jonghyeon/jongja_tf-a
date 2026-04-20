#!/usr/bin/env python3
"""
Log Hash Directory Decoder
"""
import csv
import re
import os
from typing import Dict

class HashDecoder:
    """
    Decode target : decoded "_hash" directory
    """
    def __init__(self, target_directory=None):
        # dict: {hash_id: original_format}
        self.hash_map: Dict[str, str] = {}
        self.target_directory = target_directory or os.getcwd()
        self.target_file_paths = set()
        self.log_functions_from_csv = set()

    def load_hash_map(self, csv_file_path: str) -> bool:
        """Load hash map from hash_map.csv"""
        if not os.path.exists(csv_file_path):
            print(f"Error: CSV file not found: {csv_file_path}")
            return False
        print(f"Loading hash map from: {csv_file_path}")

        try:
            with open(csv_file_path, 'r', encoding='utf-8') as csv_file:
                csv_lines = [line for line in csv_file if not line.strip().startswith('#')]
            csv_reader = csv.DictReader(csv_lines)
            loaded_count = 0

            for row in csv_reader:
                try:
                    hash_32bit = row['Hash32bit'].strip()
                    original = row['Original']  # Don't strip Original to preserve whitespace
                    function_type = row['FuncType'].strip()
                    file_path = row['FilePath'].strip()
                except KeyError as error:
                    print(f"Error: Missing required column {error} in CSV row: {row}")
                    return False

                if not hash_32bit or not function_type or not file_path:
                    print(f"Error: Empty required field in CSV row: {row}")
                    return False

                if original.startswith('"') and original.endswith('"'):
                    original = original[1:-1]

                self.hash_map[hash_32bit] = original
                loaded_count += 1

                self.target_file_paths.add(file_path)
                self.log_functions_from_csv.add(function_type)

            print(f"Loaded {loaded_count} hash mappings")
            return loaded_count > 0

        except (IOError, OSError) as error:
            print(f"Error loading CSV {csv_file_path}: {error}")
            return False

    def get_target_files(self):
        """Get C file paths from hash_map.csv"""
        existing_files = []
        missing_files = []

        print(f"Processing {len(self.target_file_paths)} file paths from CSV...")

        for rel_path in self.target_file_paths:
            absolute_path = os.path.join(self.target_directory, rel_path)

            if os.path.exists(absolute_path):
                existing_files.append(absolute_path)
                print(f"  Found: {rel_path}")
            else:
                missing_files.append(absolute_path)
                print(f"  Missing: {rel_path}")

        if missing_files:
            print(f"Warning: {len(missing_files)} files from CSV not found")

        print(f"Found {len(existing_files)} existing files from CSV")
        return existing_files

    def decode_dir_line(self, match, content):
        """Decode a single line match and return updated content"""
        func_type = match.group(1)  # RLOG_ERR
        full_args = match.group(2)  # "0x1A2B3C4D %s", user_id

        hash_match = re.search(r'"(0x[0-9a-fA-F]{8}[^"]*)"', full_args)
        if not hash_match:
            return content

        hash_id = hash_match.group(1)[:10]  # '0x1A2B3C4D'

        if hash_id not in self.hash_map:
            return content

        original_format = self.hash_map[hash_id]
        # hash_match.group(0) : '"0x1A2B3C4D %s"'
        new_full_args = full_args.replace(
            hash_match.group(0),
            f'"{original_format}"',
            1
        )

        start, end = match.span()  # indexes of pattern in file
        return (
            content[:start]
            + f'{func_type}({new_full_args});'
            + content[end:]
        )

    def decode_dir_file(self, file_path):
        """Decode a single file"""
        try:
            with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
                content = file.read()
        except (IOError, OSError) as error:
            print(f"Error reading {file_path}: {error}")
            return False

        original_content = content

        if not self.log_functions_from_csv:
            print("No log functions found in CSV using printf")
            log_functions = ['printf']
        else:
            log_functions = list(self.log_functions_from_csv)

        # Quick check
        if '0x' not in content:
            print(f"  No changes needed for {file_path}")
            return True

        log_pattern = '|'.join(log_functions)
        full_pattern = rf'({log_pattern})\s*\((.*?)\);'
        matches = list(re.finditer(full_pattern, content, re.DOTALL))

        for match in reversed(matches):  # Process in reverse order
            content = self.decode_dir_line(match, content)

        try:
            with open(file_path, 'w', encoding='utf-8') as file:
                file.write(content)
            return True
        except (IOError, OSError) as error:
            print(f"Error writing {file_path}: {error}")
            # Restore original content
            with open(file_path, 'w', encoding='utf-8') as file:
                file.write(original_content)
            return False

    def decode_directory(self):
        """Decode all target files in the directory"""
        print("="*60)
        print("HASH DECODER - DIRECTORY")
        print("="*60)
        print(f"Target directory: {self.target_directory}")
        print("-"*60)

        if not self.hash_map:
            print("Error: No hash mappings loaded!")
            return False

        target_files = self.get_target_files()

        if not target_files:
            print("No files found to decode")
            return False

        success_count = 0

        for file_path in target_files:
            if self.decode_dir_file(file_path):
                success_count += 1

        print("-"*60)
        print(f"Processed {len(target_files)} files")

        if success_count == len(target_files):
            print(f"{success_count} files processed successfully!")
        else:
            print("Some files failed to decode.")

        return success_count == len(target_files)
