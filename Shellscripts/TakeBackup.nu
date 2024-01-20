#!/usr/bin/env nu
# Author : br
# File Name : TakeBackup.nu
# Description : This script takes snapshot backup of file(s) & dir(s) provided as input
# Creation Date : 20-Jan-2024

# Actual backup functionality for the given input file(s) and dir(s)
def do_backup [target_file_name: string, inp_list] {
    run-external "tar" "-czf" $target_file_name ...$inp_list
}

def validate [inp_list] {
    if ($inp_list | length) == 0 {
        let span = (metadata $inp_list).span;
        error make {msg: $"No input files/directories provided!", label: {text: "Error here", span: $span } }
    }

    for item in $inp_list {
        if not ($item | path exists) {
            let span = (metadata $inp_list).span;
            error make {msg: $"Path '($item)' doesn't exists!", label: {text: "Error here", span: $span } }
        }
    }
}

# Main function that does the work flow
def main [...inp_list: string] {
    validate $inp_list

    let backup_directory = ($env.HOME) + "/BackupArchivePath"
    let date_time_stamp = (date now | format date "%d-%b-%Y_%H-%M-%S")
    let target_file_name = $"($backup_directory)/($env.PWD | path basename)_($date_time_stamp).tar.gz"
    mkdir $backup_directory
    do_backup $target_file_name $inp_list

    echo $"Backup snapshot archived as ($target_file_name) successfully!"
    echo
}
