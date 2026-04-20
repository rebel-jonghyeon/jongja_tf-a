import sys
import struct

def main(argv):
    if len(sys.argv) != 2:
        print(f"\nUsage: {sys.argv[0]} input.img\n")
        return

    with open(argv[1], "rb") as f:
        data = f.read()
        size = len(data)

    if size % 4 == 0:
        return
    else:
        data += b"\x00" * (4 - size % 4)
        with open(argv[1], "wb") as f:
            f.write(data)
        return

if __name__ == "__main__":
    sys.exit(main(sys.argv))
