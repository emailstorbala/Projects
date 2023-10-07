#include <iostream>
#include <fstream>
#include "FileDetails.h"

using std::string;
using std::ifstream;

bool FileExists(const string & _file) {
    ifstream fileStream;
    if (fileStream.open((char *)_file.c_str(), std::ios::in); fileStream.is_open()) {
        fileStream.close();
        return true;
    }

    return false;
}

FileDetails::FileDetails(const string & _file) {
    if (!FileExists(_file)) {
        string err_msg = "File doesn't exists or permission denied for '" + string(_file) + "'";
        throw std::runtime_error(err_msg);
    }
    this->fileName = std::move(_file);
}

void FileDetails::CalculateAndUpdateFileDetails(std::shared_ptr<Concurrent> cPtr) {
    ifstream fileStream((const char *)fileName.c_str(), std::ios::in);

    if (fileStream.is_open()) {
        string line;
        long lineCount = 0;
        while (getline(fileStream, line)) {
            lineCount++;
        }
        fileStream.close();

        cPtr->UpdateFileDetails(fileName, lineCount);
    } else {
        throw std::runtime_error("Unable to open file for read!");
    }
}


