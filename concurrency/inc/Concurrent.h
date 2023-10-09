#ifndef __CONCURRENT_H__
#define __CONCURRENT_H__
#include <cstdint>
#include <iostream>
#include <map>
#include <mutex>

class Concurrent {
    std::map <std::string, std::string> dnsDetails;
    std::mutex concMutex;
    int64_t successCnt;
    int64_t failedCnt;

    public:
        Concurrent(void) {
            this->successCnt = 0;
            this->failedCnt = 0;
        };
        void UpdateDNSDetails(const std::string & dnsName, const std::string & ipAddress="");
        void PrintDNSDetails(const std::string & dnsName);
        void PrintSummary(void);
};
#endif
