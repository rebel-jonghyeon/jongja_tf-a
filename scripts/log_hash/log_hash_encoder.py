#!/usr/bin/env python3
"""
Log Hash Encoder
"""

import os
import shutil
import re
import csv
import time
import random
import subprocess
import argparse
import sys

class VersionInfo:
    """
    Get git describe --always --tags --dirty and user message for CSV header
    """
    def __init__(self, source_directory, custom_message=None):
        self.source_directory = source_directory
        self.custom_message = custom_message

    def get_git_info(self):
        """
        Extract git version and commit ID.
        """
        try:
            describe_result = subprocess.run(
                ['git', 'describe', '--always', '--tags'],
                capture_output=True,
                text=True,
                check=True,
                cwd=self.source_directory
            )
            version_info = describe_result.stdout.strip()

            log_result = subprocess.run(
                ['git', 'log', '-1', '--format=%cd', '--date=short'],
                capture_output=True,
                text=True,
                check=True,
                cwd=self.source_directory
            )
            date_info = log_result.stdout.strip()

            csv_info = f"{date_info} {version_info}".strip()
            return csv_info if csv_info else None
        except subprocess.CalledProcessError:
            print("ERROR: Failed to git info")
            return None

    def version_info(self):
        """
        write custom message to CSV header from --rel_msg option
        """
        header_lines = []

        git_info = self.get_git_info()
        if git_info:
            header_lines.append(f'# {git_info}')

        if self.custom_message:
            header_lines.append(f'# {self.custom_message}')

        return header_lines


class ConfigLoader:
    """
    Loads files for log macros and directories to exclude.
    """
    def __init__(self):
        self.default_excludes = {'.git', 'tools', 'cmake', 'doc', 'scripts'}

    @staticmethod
    def load_loglist(file_path) -> dict:
        """
        save dictionary as {function_name: level}
        0: RLOG_DBG
        """
        functions_level = {}
        try:
            with open(file_path, "r", encoding='utf-8') as file_handle:
                for line in file_handle:
                    line = line.strip()
                    if line and not line.startswith("#"):
                        line = line.split(":")
                        level = line[0]
                        func = line[1]
                        functions_level[func] = level
                return functions_level
        except FileNotFoundError:
            print(f"File not found: {file_path}")
            sys.exit(1)

    def load_excludes(self, script_dir=None, exclude_file='dirs_to_exclude.txt'):
        """
        Returns set of directory names to exclude.
        """
        if script_dir:
            exclude_file_path = os.path.join(script_dir, exclude_file)
        else:
            exclude_file_path = exclude_file

        try:
            with open(exclude_file_path, 'r', encoding='utf-8') as file_handle:
                exclude_dirs = set()
                for line in file_handle:
                    line = line.strip()
                    if line and not line.startswith('#'):
                        exclude_dirs.add(line)

                if exclude_dirs:
                    print(f"Loaded dirs_to_exclude.txt : {exclude_dirs}")
                    return exclude_dirs

                return self.default_excludes

        except FileNotFoundError:
            return self.default_excludes


def copy_directory(src_dir, dst_dir):
    """
    copy directory "rebel" to "rebel_hash"
    """
    try:
        if os.path.exists(dst_dir):
            shutil.rmtree(dst_dir)
        shutil.copytree(src_dir, dst_dir)
        print(f"Directory copied from {src_dir} to {dst_dir}")
        return True
    except (OSError, shutil.Error) as error:
        print(f"Directory copy failed: {error}")
        sys.exit(1)


def find_c_files(root_dir, exclude_dirs=None):
    """
    List C source files while checking exclusion directories.
    """
    if exclude_dirs is None:
        exclude_dirs = set()

    c_files = []
    for path, dirs, files in os.walk(root_dir):
        dirs[:] = [d for d in dirs if d not in exclude_dirs]

        for file in files:
            if file.endswith(".c"):
                c_file_path = os.path.join(path, file)
                c_files.append(c_file_path)
    return c_files


class EncodingFilter:
    """
    Before pattern parsing, identifies disable markers.
    """
    def __init__(self):
        self.disable_pattern = re.compile(r'DISABLE\s+LOGHASH')
        self.keep_function_pattern = re.compile(r'KEEP\s+THIS\s+FUNCTION')

    def check_disable_marker(self, file_content, match_start_pos):
        """Check DISABLE LOGHASH comment"""
        lines = file_content.split('\n')
        start_line_num = file_content[:match_start_pos].count('\n')

        if start_line_num > 0:
            prev_line = lines[start_line_num - 1].strip()
            if self.disable_pattern.search(prev_line):
                return True
        return False

    def get_keep_ranges(self, file_content):
        """Check and get ranges of KEEP THIS FUNCTION comment"""
        lines = file_content.split('\n')
        skip_ranges = set()

        for i, line in enumerate(lines):
            if self.keep_function_pattern.search(line):
                brace_count = 0
                function_started = False

                for j in range(i + 1, len(lines)):
                    current_line = lines[j]

                    if '{' in current_line and not function_started:
                        function_started = True
                        brace_count += current_line.count('{')
                        brace_count -= current_line.count('}')
                        skip_ranges.add(j)
                        continue

                    if function_started:
                        brace_count += current_line.count('{')
                        brace_count -= current_line.count('}')
                        skip_ranges.add(j)

                        if brace_count <= 0:
                            break

        return skip_ranges

    @staticmethod
    def check_keep_function_marker(file_content, match_start_pos, match_end_pos, keep_ranges):
        """Check if in skip ranges"""
        start_line_num = file_content[:match_start_pos].count('\n')
        end_line_num = file_content[:match_end_pos].count('\n')

        for line_num in range(start_line_num, end_line_num + 1):
            if line_num in keep_ranges:
                return True
        return False


class PatternParser:
    """
    Parses and matches logging function patterns in C source files.
    """
    def __init__(self, encoding_filter):
        self.encoding_filter = encoding_filter

    @staticmethod
    def extract_match_info(match, args_content):
        """
        parsing format specifics and multiline format
        """
        args_match = re.search(
            r'([\s\\]*"(?:\\.|[^"])*?"[\s\\]*)+', args_content.strip(), re.DOTALL)

        if not args_match:
            return None

        original_multiline_pattern = args_match.group(0)
        literals = re.findall(r'"([^"]*)"', original_multiline_pattern)
        original_string = "".join(literals)
        format_specs = re.findall(r'%[a-zA-Z0-9#]*[a-zA-Z]', original_string)

        return {
            'func_name': match.group(1),
            'original_string': original_string,  # CSV
            'original_multiline_pattern': original_multiline_pattern,  # replace
            'format_specs': format_specs
        }

    def parse_pattern(self, file_content, function_names):
        """
        1: RLOG_ERR("start %d %s again", v1,s1);
        2: parsing RLOG_ERR, "start %d %s again"
        3: "start %d %s again-> parsing %d, %s =>extract_match_info
        """
        func_pattern = "|".join(re.escape(func) for func in function_names)
        pattern = rf'\b({func_pattern})\s*\(\s*("(?:\\.|[^"])*?"(?:\s*"(?:\\.|[^"])*?")*)(.*?)\);'
        keep_ranges = self.encoding_filter.get_keep_ranges(file_content)

        matches = []
        for match in re.finditer(pattern, file_content, re.DOTALL | re.IGNORECASE):
            args_content = match.group(2)
            match_start = match.start()
            match_end = match.end()

            if self.encoding_filter.check_disable_marker(file_content, match_start):
                continue
            if EncodingFilter.check_keep_function_marker(
                    file_content, match_start, match_end, keep_ranges):
                continue

            match_info = PatternParser.extract_match_info(match, args_content)
            if match_info:
                matches.append(match_info)

        return matches


class HashEngine:
    """
    Generates hash values with collision detection.
    """
    def __init__(self):
        self.used_hashes = set()
        self.base_seed = None
        self.sequence_num = 0
        self.collision_count = 0

    def create_hash_24bit(self):
        """
        24bit hash with collision detection
        """
        if self.base_seed is None:
            self.base_seed = int(time.time())

        max_attempts = 1000
        collision_attempts = 0

        while collision_attempts < max_attempts:
            self.sequence_num += 1

            if self.sequence_num > 0xFFFFFF:
                print("ERROR: Exceeded maximum unique 24bit hashes")
                sys.exit(1)

            seed = self.base_seed + self.sequence_num << 10 + collision_attempts
            random.seed(seed)
            random_val = random.randint(0, 0xFFFFFF)
            hash_24bit = f"{random_val:06x}"

            if hash_24bit not in self.used_hashes:
                self.used_hashes.add(hash_24bit)
                return hash_24bit

            collision_attempts += 1
            self.collision_count += 1

        raise ValueError("Failed to generate unique 24bit hash after maximum attempts")

    def create_hash_32bit(self, log_level, module_id) -> str:
        """
        32bit hash combining level + module + 24bit hash
        """
        if not 1 <= log_level <= 6:
            log_level = 1

        hash_24bit = self.create_hash_24bit()
        hash_32bit = (log_level << 29) | (module_id << 24) | int(hash_24bit, 16)
        return f"0x{hash_32bit:08x}"

    @staticmethod
    def combine_new_format(hash_value, format_specs):
        """
        Combined format : printf("0x1234ABCD %d %s\n", v1, v2);
        """
        new_format = ' '.join(format_specs) if format_specs else ""
        result = f"{hash_value} {new_format}".strip()
        return result + '\\n'


def export_to_csv(results, csv_path, header_lines=None):
    """
    Export results to a CSV file
    """
    with open(csv_path, "w", newline='', encoding='utf-8') as csv_file:
        csv_writer = csv.writer(csv_file)

        if header_lines:
            for header_line in header_lines:
                csv_writer.writerow([header_line])

        csv_writer.writerow([
            'LogLevel', 'ModuleID', 'Hash32bit', 'Original', 'FuncType', 'FilePath'
        ])

        for result in results:
            csv_writer.writerow(result)


class Encoder:
    """
    Main encoding Executor.
    """
    def __init__(self, functions_level, exclude_dirs, custom_message=None):
        self.functions_level = functions_level
        self.exclude_dirs = exclude_dirs
        self.custom_message = custom_message

        # Create components internally
        encoding_filter = EncodingFilter()
        self.pattern_parser = PatternParser(encoding_filter)
        self.hash_engine = HashEngine()

        self.results = []

    @staticmethod
    def get_directories():
        """Get source and destination directories"""
        src_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), "../.."))
        dst_dir = f"{src_dir}_hash"
        return src_dir, dst_dir

    def process_match(self, match, relative_path):
        """Process a single match and update results"""
        func_name = match['func_name']
        original_string = match['original_string']
        original_multiline_pattern = match['original_multiline_pattern']
        format_specs = match['format_specs']

        log_level = self.functions_level.get(func_name, 1)
        module_id = 0  # Currently using 0 for all modules

        hash_32bit = self.hash_engine.create_hash_32bit(int(log_level), module_id)
        new_format = HashEngine.combine_new_format(hash_32bit, format_specs)

        new_pattern = f'"{new_format}"'

        if original_string:
            self.results.append((
                int(log_level), module_id, hash_32bit, original_string,
                func_name, relative_path
            ))

        return original_multiline_pattern, new_pattern

    def process_file(self, c_file_path, dst_dir):
        """
        Process a single C source file, replacing log strings with hash values.
        """
        with open(c_file_path, "r", encoding='utf-8') as file_handle:
            file_content = file_handle.read()

        original_content = file_content
        matches = self.pattern_parser.parse_pattern(
            file_content, self.functions_level.keys()
        )
        relative_path = os.path.relpath(c_file_path, dst_dir)

        for match in matches:
            original_pattern, new_pattern = self.process_match(match, relative_path)
            file_content = file_content.replace(original_pattern, new_pattern)

        if file_content != original_content:
            with open(c_file_path, "w", encoding='utf-8') as file_handle:
                file_handle.write(file_content)

    def run(self):
        """
        Execute the complete encoding process.
        """
        try:
            src_dir, dst_dir = Encoder.get_directories()

            if not copy_directory(src_dir, dst_dir):
                print("ERROR: Failed to copy source directory", file=sys.stderr)
                return False

            c_files = find_c_files(dst_dir, self.exclude_dirs)
            if not c_files:
                print("WARNING: No C files found to process")
                return True

            print(f"Found {len(c_files)} C files")

            for c_file_path in c_files:
                try:
                    self.process_file(c_file_path, dst_dir)
                except (OSError, ValueError) as error:
                    print(f"ERROR: Failed to process file {c_file_path}: {error}", file=sys.stderr)
                    return False

            version_collector = VersionInfo(src_dir, self.custom_message)
            header_version = version_collector.version_info()

            scripts_log_hash_dir = os.path.join(dst_dir, "scripts", "log_hash")
            os.makedirs(scripts_log_hash_dir, exist_ok=True)

            csv_path = os.path.join(scripts_log_hash_dir, "hashmap.csv")
            export_to_csv(
                self.results, csv_path, header_version
            )

            print(f"Total patterns encoded: {len(self.results)}")
            print(f"Hash collisions resolved: {self.hash_engine.collision_count}")
            return True

        except (OSError, ValueError) as error:
            print(f"ERROR: Unexpected error from run(): {error}", file=sys.stderr)
            sys.exit(1)

def main():
    """
    Main process
    """
    try:
        parser = argparse.ArgumentParser(description='Log Hash Encoder')
        parser.add_argument(
            '--rel_msg', type=str,
            help='Custom message to add to hash map CSV header'
        )
        args = parser.parse_args()

        script_dir = os.path.dirname(os.path.abspath(__file__))
        loglist_path = os.path.join(script_dir, "macros_to_hash.txt")

        config_loader = ConfigLoader()
        functions_level = ConfigLoader.load_loglist(loglist_path)
        exclude_dirs = config_loader.load_excludes(script_dir)

        if functions_level is None:
            print("ERROR: Failed to load log functions configuration", file=sys.stderr)
            sys.exit(1)

        encoder = Encoder(
            functions_level, exclude_dirs,
            custom_message=args.rel_msg
        )

        success = encoder.run()
        if not success:
            print("ERROR: Log hash encoding failed", file=sys.stderr)
            sys.exit(1)

        print("SUCCESS: Log hash encoding completed successfully")

    except KeyboardInterrupt:
        print("\nERROR: Keyboard interrupt", file=sys.stderr)
        sys.exit(1)
    except (OSError, ImportError, TypeError, AttributeError) as error:
        print(f"ERROR: Unexpected error from main(): {error}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
