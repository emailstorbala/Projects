#!/usr/bin/python3

"""
This program downloads the pypi mirrors for the specified pypi packages
"""

from html.parser import HTMLParser
import argparse
import itertools
import os
import sys
import urllib.request
import wget

class MyHTMLParser(HTMLParser):
    """
    HTML parser to fetch the href urls
    """
    def reset(self):
        """
        Reset method
        """
        super().reset()
        self.links = iter([])

    def handle_starttag(self, tag, attrs):
        """
        Parsing the href tags
        """
        # Only parse the 'anchor' tag.
        if tag == "a":
           # Check the list of defined attributes.
            for (name, value) in attrs:
                # If href is defined, print it.
                if name == "href":
                    self.links = itertools.chain(self.links, [value])

def gen_links(stream, parser):
    """
    This function generates the href links in the URL
    """
    encoding = stream.headers.get_content_charset() or 'UTF-8'
    for line in stream:
        parser.feed(line.decode(encoding))
        yield from parser.links

def do_arg_parse():
    """
    Do program argument parsing
    """
    desc = "Downloading entire pip packages for the specified pakages"
    parser = argparse.ArgumentParser(description=desc)
    parser.add_argument("-p", "--pkg_list", required=True, help="Input package list")
    parser.add_argument("-r", "--pkg_repo", required=True, help="Output pip repository")

    return parser.parse_args()

def main():
    """
    Main entry routine of the program
    """
    args = do_arg_parse()

    if not os.path.exists(args.pkg_list):
        raise FileNotFoundError("Input file doesn't exists")
    elif os.path.isdir(args.pkg_list):
        raise OSError("Input file is a directory")

    with open(args.pkg_list) as f_hdl:
        lines = f_hdl.readlines()

    pkgs = []
    for line in lines:
        if not line.startswith("#"):
            pkgs.append(line.strip('\n'))

    pkg_url_map = {}

    for pkg in pkgs:
        try:
            url = "https://pypi.org/simple/{}/".format(pkg)
            parser = MyHTMLParser()
            with urllib.request.urlopen(url) as stream:
                pkg_url_map[pkg] = gen_links(stream, parser)
        except Exception:
            continue

    for pkg, urls in pkg_url_map.items():
        # skip if already in repo
        pkg_path = os.path.join(args.pkg_repo, pkg)

        if os.path.exists(pkg_path) and not os.path.isdir(pkg_path):
            print("Package path {} can't be created!".format(pkg_path))
        elif not os.path.exists(pkg_path):
            os.mkdir(pkg_path)

        for url in urls:
            wget.download(url, pkg_path)

if __name__ == '__main__':
    sys.exit(main())
