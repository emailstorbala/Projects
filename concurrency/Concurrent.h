#ifndef __CONCURRENT_H__
#define __CONCURRENT_H__
#include <iostream>
#include <map>
#include <mutex>

class Concurrent {
    std::map <std::string, long> fileLineDetails;
    std::string currentFile;
    long allFileLines = 0;
    std::mutex concMutex;

    void PrintFileDetails(const std::string & _file);

    public:
        Concurrent(void) {};
        bool UpdateFileDetails(const std::string &_file, const long &_loc);
};
#endif
