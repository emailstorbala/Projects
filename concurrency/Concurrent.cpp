#include "Concurrent.h"
#include <fmt/core.h>

using std::string;

bool  Concurrent::UpdateFileDetails(const string & _file, const long &_loc) {
    std::lock_guard <std::mutex> lock(this->concMutex); 

    bool retVal = true;

    try {
        this->fileLineDetails[_file] = _loc;
        this->allFileLines += _loc;

        this->PrintFileDetails(_file);
    } catch (std::runtime_error & excp) {
        fmt::print("Exception occurred in UpdateFileDetails : {}\n", excp.what());
        retVal = false;
    }

    return retVal;
}

void Concurrent::PrintFileDetails(const string & _file) {
    fmt::print("File '{}' has {} line(s)\n", _file, this->fileLineDetails[_file]);
    fmt::print("Total lines of all files: {}\n", this->allFileLines);
}
