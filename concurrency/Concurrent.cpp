#include "Concurrent.h"

using std::string;
using std::cout;
using std::endl;

bool  Concurrent::UpdateFileDetails(const string & _file, const long &_loc) {
    std::lock_guard <std::mutex> lock(this->concMutex); 

    bool retVal = true;

    try {
        this->fileLineDetails[_file] = _loc;
        this->allFileLines += _loc;
    } catch (std::runtime_error & excp) {
        cout << "Exception occurred in UpdateFileDetails : " << excp.what() << endl;
        retVal = false;
    }

    return retVal;
}

void Concurrent::PrintFileDetails(const string & _file) {
    cout << "File '" << _file << "' has " << this->fileLineDetails[_file] << " line(s)" << endl;
    cout << "Total lines of all files : " << this->allFileLines << endl;
}
