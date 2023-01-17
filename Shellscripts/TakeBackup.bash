#!/usr/bin/env bash
: "
Author : br
File Name : TakeBackup.bash
Description : This script takes snapshott bacup of file(s) & dir(s) provided as input
Creation Date : 27-05-2016
"

: "
Set Global variables for this function
"
SetGlobalVariables() {
    GLOBAL_BACKUP_DIRECTORY="$HOME/BackupArchivePath"
    INP_FILE_AND_DIR_LIST=
    DATE_TIME_STAMP=$(date +%d-%b-%Y_%H-%M-%S)
    TARGET_FILE_NAME=

    mkdir -p "${GLOBAL_BACKUP_DIRECTORY}" || return $?
    echo "Global variables initialised."
}

: "
Define usage of this script
"
Usage() {
    echo "$0 <file1>/<dir1> ... <filen>/<dirn>"
}

: "
This function parses the arguments of the script and validates the inputs.
"
ParseAndValidate() {
    local args="$*"
    local argc=$#

    for arg in ${args}
    do
        if [ ! -f "${arg}" ] && [ ! -d "${arg}" ]
        then
            echo
            echo "Invalid Usage! Arguments must be file(s) or dir(s)"
            Usage
            return 10
        fi
    done

    curr_dir=$(basename "${PWD}")
    if [ ${argc} -ne 0 ]
    then
        INP_FILE_AND_DIR_LIST=${args}
    else
        INP_FILE_AND_DIR_LIST=.
    fi

    TARGET_FILE_NAME="${GLOBAL_BACKUP_DIRECTORY}/${curr_dir}_${DATE_TIME_STAMP}.tar.gz"
    echo "Parsing and validation completed."
}

: "
Actual backup functionality for the given input file(s) and dir(s)
"
DoBackup() {
    tar -czf "${TARGET_FILE_NAME}" "${INP_FILE_AND_DIR_LIST}" || return $?
}

: "
Main function that does the work flow
"
main() {
    SetGlobalVariables || return $?
    ParseAndValidate "$@" || return $?
    DoBackup || return $?

    echo -e "\033[32mBackup snapshot archived as ${TARGET_FILE_NAME} successfully!"
    echo -e "\033[0m"
}

main "$@"
