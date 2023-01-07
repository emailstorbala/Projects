#!/usr/bin/env python3

import sys
from subprocess import Popen, PIPE, STDOUT

def main():
    cmd:str = "find /home/balamurugan/Programs/Projects"
    exec_path:str = "."
    with Popen(cmd.split(), cwd=exec_path, stdout=PIPE, stderr=STDOUT, encoding='utf-8') as proc:
        while proc.stdout:
            data:str = proc.stdout.read(1024)
            print(f"data->{data}")
            if not data:
                break

if __name__ == '__main__':
    sys.exit(main())
