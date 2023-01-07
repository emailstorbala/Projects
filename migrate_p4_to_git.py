#!/usr/bin/python3

"""
This program was written to migrate perforce (p4) data to git
using git-p4 tool (via shell commands). For efficient handling
and better readability, the program is written in Python
instead of Shell.

*** Program intended to be used as standalone. ***
"""

import os
import argparse
import logging
from subprocess import Popen, PIPE, STDOUT
from multiprocessing import Process
from typing import List

class GLOBALS:
    GIT_P4_BIN = '/usr/local/bin/git-p4.py'
    LOGGER_FILE = 'p4_git_migrate.log'

def parse_arguments() -> argparse.Namespace:
    """
    This function is used to parse the program arguments
    Returns the parsed program arguments
    """
    parser = argparse.ArgumentParser(prog='migrate_p4_to_git.py',
                                     description='Migrate p4 to git VCS')
    parser.add_argument('--mig_inp',
                        required=True,
                        help='Input p4-git path<->branch map CSV file')
    parser.add_argument('--gitlab_endpoint',
                        required=True,
                        help='Gitlab endpoint for migration target')
    parser.add_argument('--root_group',
                        default='velocix',
                        help='Gitlab Parent/ROOT group for documentation group.')
    parser.add_argument('--doc_grp',
                        required=True,
                        help='Gitlab documentation group name')
    args = parser.parse_args()
    return args

def validate_and_parse_file(inpfile:str) -> dict:
    p4_git_map:dict = {}
    inp_ctx:List[str] = []

    with open(inpfile) as fp:
        inp_ctx = [ line.strip() for line in fp.readlines() if not line.startswith('#') ]

    for curr_line in inp_ctx:
        p4_path, git_branch = curr_line.split(',')

        if not p4_path.startswith("//"):
            exception = "P4 path '{}' not starting with //".format(p4_path)
            raise Exception(exception)
        elif not p4_path.endswith("..."):
            exception = "P4 path '{}' not ending with ...".format(p4_path)
            raise Exception(exception)
        elif p4_path in p4_git_map.keys():
            exception = "P4 path '{}' duplicates in the input file".format(p4_path)
            raise Exception(exception)

        p4_git_map[p4_path] = git_branch

    return p4_git_map

def clone_from_p4(args, p4_path:str, git_branch:str):
    """
    Based on the p4-git path mapping provided
    in the input file, this function will
    git clone from the p4_path.
    """
    repo_name:str = p4_path.split('/')[-2]
    wrk_dir:str = os.path.dirname(os.path.abspath(__file__))
    clone_dir:str = "{}/{}_{}".format(wrk_dir, repo_name, git_branch)
    cmd_execpath_map:dict = {}
    
    # Frame commands for migrating the p4_path to git
    cmd = f"{GLOBALS.GIT_P4_BIN} clone --destination={clone_dir} {p4_path}@all"
    cmd_execpath_map[1] = (cmd, wrk_dir)

    if git_branch != "master":
        cmd = f"git checkout -b {git_branch}"
        cmd_execpath_map[2] = (cmd, clone_dir)
    
    cmd = f"git remote add origin {args.gitlab_endpoint}:{args.root_group}/{args.doc_grp}/{repo_name}.git"
    cmd = (
            "git remote add origin "
            f"{args.gitlab_endpoint}:{args.root_group}/${args.doc_grp}/{repo_name}.git"
          )
    cmd_execpath_map[3] = (cmd, clone_dir)

    cmd = f"git push origin {git_branch}"
    cmd_execpath_map[4] = (cmd, clone_dir)

    for (cmd, exec_path) in cmd_execpath_map.values():
        with Popen(cmd.split(), cwd=exec_path, stdout=PIPE, stderr=STDOUT, encoding='utf-8') as proc:
            while proc.stdout:
                data:str = proc.stdout.read(1024)
                if not data:
                    break

                logging.info("%s->%s => %s", repo_name, git_branch, data)

if __name__ == '__main__':
    logging.basicConfig(filename=GLOBALS.LOGGER_FILE, level=logging.DEBUG)

    args:argparse.Namespace = parse_arguments()
    p4_git_mapping:dict = validate_and_parse_file(args.mig_inp)
    procs:list = []

    for p4_path, git_branch in p4_git_mapping.items():
        proc = Process(target=clone_from_p4, args=(args, p4_path, git_branch))
        procs.append(proc)
        proc.start()

    for proc in procs:
        proc.join()
