import argparse
import sys

def swap_file_endianness(input_path, output_path, chunk_size):
    """
    Swaps the endianness of a binary file in specified chunk sizes.

    Args:
        input_path (str): The path to the source binary file.
        output_path (str): The path for the destination binary file.
        chunk_size (int): The unit size in bytes for the swap (e.g., 2, 4, 8).
    """
    try:
        processed_bytes = 0
        with open(input_path, 'rb') as f_in, open(output_path, 'wb') as f_out:
            while True:
                # Read a chunk of the specified size from the file
                chunk = f_in.read(chunk_size)
                
                # If the chunk is empty, we've reached the end of the file
                if not chunk:
                    break
                
                # Reverse the byte order of the chunk
                swapped_chunk = chunk[::-1]
                
                # Write the swapped chunk to the output file
                f_out.write(swapped_chunk)
                processed_bytes += len(chunk)

        print("✅ Conversion successful!")
        print(f" - Source file: {input_path}")
        print(f" - Output file: {output_path}")
        print(f" - Chunk size: {chunk_size} bytes")
        print(f" - Total bytes processed: {processed_bytes} bytes")

    except FileNotFoundError:
        print(f"❌ Error: Input file not found at '{input_path}'", file=sys.stderr)
        return 1
    except Exception as e:
        print(f"❌ An error occurred: {e}", file=sys.stderr)
        return 1

    return 0

def main():
    """Parses command-line arguments and executes the main function."""
    parser = argparse.ArgumentParser(
        description="A script to swap the endianness of a binary file.",
        formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("input_file", help="The source binary file to convert.")
    parser.add_argument("output_file", help="The destination binary file to save.")
    parser.add_argument(
        "-s", "--size",
        type=int,
        default=4,
        choices=[2, 4, 8],
        help="The chunk size in bytes for the byte swap operation.\n"
             "  2: 16-bit (WORD)\n"
             "  4: 32-bit (DWORD) (default)\n"
             "  8: 64-bit (QWORD)"
    )
    
    args = parser.parse_args()
    
    # Warn the user if the file size is not a multiple of the chunk size
    try:
        from os.path import getsize
        file_size = getsize(args.input_file)
        if file_size % args.size != 0:
            print(f"⚠️ Warning: The file size ({file_size} bytes) is not a multiple of the chunk size ({args.size} bytes).")
            print("The remaining bytes at the end of the file will be processed as a smaller chunk.")
    except FileNotFoundError:
        # This error will be handled by the main logic, so we can pass here
        pass
        
    return swap_file_endianness(args.input_file, args.output_file, args.size)

if __name__ == "__main__":
    sys.exit(main())
