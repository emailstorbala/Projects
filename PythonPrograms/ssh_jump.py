#!/usr/bin/env python3
from pathlib import Path
from jumpssh import SSHSession

user = "root"
jumpbox_pub_addr = '10.85.11.48'
target_addr = '10.25.123.10'
ssh_key_filename = "{}/.ssh/id_rsa".format(Path.home())

def main():
    print("Connecting sprout machine ...")
    with SSHSession(jumpbox_pub_addr, user, private_key_file=ssh_key_filename).open() as gateway_session:
        print("Connected sprout machine!")
        print("Connecting MN machine ...")
        with gateway_session.get_remote_session(target_addr) as remote_session:
            print("Connected MN machine!")
            stdout = remote_session.get_cmd_output("hostnamectl")
            print(stdout)

if __name__ == "__main__":
    main()
