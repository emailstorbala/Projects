#!/usr/bin/env python3
""" Program to prettify the input json file """

import argparse
import json
import os
import sys

def parse_args():
    """ Function to parse the program arguments """
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--infile", required=True,
                        help="Input file in json format")
    parser.add_argument("-o", "--outfile", default="out.json",
                        help="Write pretty output to outfile")
    parser.add_argument("-s", "--stdout", action="store_true",
                        help="Flag to decide stdout/outfile for output")
    return parser.parse_args()

def prettify_json(args):
    """ Function to prettify the input json """
    with open(file=args.infile, encoding='utf-8') as json_file:
        json_obj = json.load(json_file)
        if args.stdout:
            json_str = json.dumps(obj=json_obj, indent=4)
            print(json_str)
        else:
            with open(file=args.outfile, mode='w', encoding='utf-8') as out_file:
                json.dump(obj=json_obj, fp=out_file, indent=4)

def main():
    """ Main entrypoint function """
    args = parse_args()
    if not os.path.exists(args.infile):
        raise FileNotFoundError(f"Input file '{args.infile}' doesn't exist!")

    prettify_json(args)


if __name__ == '__main__':
    sys.exit(main())
