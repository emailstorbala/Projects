#!/usr/bin/env python

from __future__ import print_function
import os
import sys
import wget
import urllib2
import hashlib
import argparse
from HTMLParser import HTMLParser
from xml.etree import ElementTree

class MyHTMLParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        if tag != 'a':
            return
        attr = dict(attrs)
        self.links.append(attr)

def extract(url):
    try:
        f = urllib2.urlopen(url)
        html = f.read()
        f.close()
    except urllib2.HTTPError as e:
        print(e, 'while fetching', url)
        return
 
    parser = MyHTMLParser()
    parser.links = []
    parser.feed(html)

    return parser.links

def do_arg_parse():
    parser = argparse.ArgumentParser(description='Downloading entire pip packages for the specified pakages')
    parser.add_argument("-p", "--pkg_list", required=True, help="Input package list")
    parser.add_argument("-r", "--pkg_repo", required=True, help="Output pip repository")

    args = parser.parse_args()

    return args


if __name__ == '__main__':
    args = do_arg_parse()
    
    if not os.path.exists(args.pkg_list):
        raise Exception("Input file doesn't exists")
    elif os.path.isdir(args.pkg_list):
        raise Exception("Input file is a directory")

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
            pkg_links = extract(url)
            pkg_urls = []
            for pkg_link in pkg_links:
                tmp_url = pkg_link.get('href')
                pkg_urls.append(tmp_url)

            pkg_url_map[pkg] = pkg_urls
        except Exception as ex:
            print("Exception -> {}".format(ex))
            continue

    for pkg, urls in pkg_url_map.items():
        # skip if already in repo
        pkg_path = os.path.join(args.pkg_repo, pkg)

        if os.path.exists(pkg_path) and not os.path.isdir(pkg_path):
            print("Package path {} can't be created!".format(pkg_path))

        if not os.path.exists(pkg_path):
            os.mkdir(pkg_path)

        for url in urls:
            wget.download(url, pkg_path)
