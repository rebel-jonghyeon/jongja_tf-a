#!/usr/bin/env python3
#
# Copyright (c) 2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file.

import os
import sys
import errno
import argparse
import subprocess
import tempfile
import struct

def pack_ints(*ints):
    return b''.join(v.to_bytes(4, 'little') for v in ints)

def mw_command(args):
    # Set the command based on mw_protocol.h.
    commands = {'check': 0x01, 'load': 0x02, 'unload': 0x04, 'start': 0x08,
                'run': 0x0A, 'stop': 0x10, 'status': 0x20, 'query': 0x21,
                'logs': 0x40, 'reset': 0x41, 'ps': 0x50}
    command = commands.get(args.command)
    if command is None:
        sys.exit(f"Unknown command {args.command}")
    # Create temp file for MW header and possible contaimer image data.
    length = os.path.getsize(args.image) if args.image is not None else 0
    data = open(args.image, 'rb').read() if args.image is not None else b''
    hdr = pack_ints(command, args.containerid, 1, length)
    if args.norun:
        sys.stdout.buffer.writelines((hdr, data))
        return None
    f = tempfile.NamedTemporaryFile(delete=False)
    f.writelines((hdr, data))
    f.close()
    # Use cmtest data to send the command to MW.
    print('Sending request to CMRT MW...')
    cmd = ['cmtest', 'data', '-f0', f'-t{args.timeout}']
    if args.image is not None:
        # Use SAC for large data.
        cmd.append('-o0')
    cmd.append(f.name)
    if args.debug:
        print(' '.join(cmd))
    p = subprocess.run(cmd, capture_output=True, check=False)
    if args.debug:
        sys.stdout.buffer.write(p.stderr)
    else:
        os.unlink(f.name)
    # Check and print errors.
    if p.returncode == errno.ETIMEDOUT and command == 0x41:
        sys.exit(0) # reset timeout is not an error
    elif p.returncode != 0:
        sys.exit(f'Error {p.returncode}: {os.strerror(p.returncode)}')
    mwerror = struct.unpack_from('<I', p.stdout)[0]
    if mwerror != 0:
        sys.exit(f'...MW error {mwerror} ({os.strerror(mwerror)})')
    print('...MW status 0')
    # Return output data for the caller.
    return p.stdout

def main(args):
    # Run the command.
    out = mw_command(args)
    if args.norun:
        return
    # Parse the response for some commands base on mw_protocol.h.
    if args.command == 'status':
        _, status = struct.unpack_from('<II', out)
        statuses = ('idle', 'starting', 'running', 'exit requested', 'exiting', 'malfunction')
        status = statuses[status] if status < len(statuses) else 'unknown'
        print(f'...container state: {status}')
    elif args.command == 'query':
        # Print response here...
        pass
    elif args.command == 'logs':
        # Print response here...
        pass
    elif args.command == 'ps':
        _, _, size = struct.unpack_from('<III', out, offset=8)
        offset = 20
        for _ in range(size):
            flowid, priority, state = struct.unpack_from('<iii', out, offset=offset)
            print(f'FlowId: {flowid} - Status: {state} - Priority: {priority}')
            offset = offset + 12

DESCRIPTION = """
MW commands

check|load|run|logs|reset|unload|start|stop|ps
"""

def _parse_args():
    parser = argparse.ArgumentParser(description=DESCRIPTION,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('command', type=str, help='command to run')
    parser.add_argument('image', nargs='?', help='container image')
    parser.add_argument('-d', '--debug', action='store_true',
                        default=False, help='print debug info, keep temp file')
    parser.add_argument('-n', '--norun', action='store_true',
                        default=False, help='write to stdout only')
    parser.add_argument('-t', '--timeout', type=int, default=1000, help='timeout in ms')
    parser.add_argument('-c', '--containerid', type=int, default=100, help='container flow id')
    parser.add_argument('-p', '--priority', type=int, default=1, help='container priority')
    return parser.parse_args()

if __name__ == '__main__':
    main(_parse_args())
