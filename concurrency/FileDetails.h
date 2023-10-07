#ifndef __FILE_DETAILS_H__
#define __FILE_DETAILS_H__

#include <map>
#include <memory>
#include <string>
#include "Concurrent.h"

class FileDetails {
    std::string fileName;

    public:
    FileDetails(void) = delete;
    explicit FileDetails(const std::string & _file);
    void CalculateAndUpdateFileDetails(std::shared_ptr<Concurrent> cPtr);
};

#endif
