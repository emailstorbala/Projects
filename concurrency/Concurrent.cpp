#include "Concurrent.h"
#include <fmt/core.h>

using std::string;

bool Concurrent::UpdateDNSDetails(const string & dnsName, const string & ipAddress) {
    std::lock_guard <std::mutex> lock(this->concMutex); 

    bool retVal = true;

    try {
        this->dnsDetails[dnsName] = ipAddress;
        this->PrintDNSDetails(dnsName);
    } catch (std::runtime_error & excp) {
        fmt::print("Exception occurred in UpdateDNSDetails: {}\n", excp.what());
        retVal = false;
    }

    return retVal;
}

void Concurrent::PrintDNSDetails(const string & dnsName) {
    fmt::print("IP Address for dnsName '{}' is {}\n", dnsName, this->dnsDetails[dnsName]);
}
