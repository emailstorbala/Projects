#include "Concurrent.h"
#include <fmt/core.h>

using std::string;

void Concurrent::UpdateDNSDetails(const string & dnsName, const string & ipAddress) {
    std::lock_guard <std::mutex> lock(this->concMutex);

    if (!ipAddress.empty()) {
        this->dnsDetails[dnsName] = ipAddress;
        this->PrintDNSDetails(dnsName);
        this->successCnt++;
    } else {
        this->failedCnt++;
    }
}

void Concurrent::PrintDNSDetails(const string & dnsName) {
    fmt::print("IP Address for dnsName '{}' is {}\n", dnsName, this->dnsDetails[dnsName]);
}

void Concurrent::PrintSummary(void) {
    fmt::print("Total succeeded requests -> {}\n", this->successCnt);
    fmt::print("Total failed requests -> {}\n", this->failedCnt);
}
