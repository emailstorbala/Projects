#ifndef __CONCURRENT_H__
#define __CONCURRENT_H__
#include <iostream>
#include <map>
#include <mutex>

class Concurrent {
    std::map <std::string, std::string> dnsDetails;
    std::mutex concMutex;


    public:
        Concurrent(void) {};
        bool UpdateDNSDetails(const std::string & dnsName, const std::string & ipAddress);
        void PrintDNSDetails(const std::string & dnsName);
};
#endif
