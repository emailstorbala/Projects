#ifndef __DNS_DETAILS_H__
#define __DNS_DETAILS_H__

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "Concurrent.h"

class DNSDetails {
    std::string dnsName;
    std::string ipAddress;

    public:
    DNSDetails(void) = delete;
    void getDnsIP(void);
    explicit DNSDetails(const std::string & dnsName);
    void CalculateAndUpdateFileDetails(std::shared_ptr<Concurrent> cPtr);
};

#endif
