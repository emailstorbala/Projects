#ifndef __FILE_DETAILS_H__
#define __FILE_DETAILS_H__

#include <map>
#include <memory>
#include "Concurrent.h"

class FileDetails {
    std::string fileName;

    public:
    FileDetails(void) = delete;
    explicit FileDetails(const char * _file);
    void CalculateAndUpdateFileDetails(std::shared_ptr<Concurrent> cPtr);
};

#endif
