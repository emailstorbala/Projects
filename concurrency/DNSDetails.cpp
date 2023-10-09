#include <arpa/inet.h>
#include <netdb.h>
#include <stdexcept>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include <fmt/format.h>
#include "DNSDetails.h"

using std::string;

void DNSDetails::getDnsIP(void) {
    struct addrinfo          hints;
    struct addrinfo          *result, *rp;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int s = getaddrinfo(dnsName.c_str(), NULL, &hints, &result);
    if (s != 0) {
        string errMsg;
        fmt::format_to(std::back_inserter(errMsg), "{}: getaddrinfo: {}\n", dnsName, gai_strerror(s));
        throw std::runtime_error(errMsg);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
        char ipstr[INET6_ADDRSTRLEN];
        inet_ntop(rp->ai_family, (void *)(&ipv4->sin_addr), ipstr, sizeof ipstr);
        this->ipAddress = ipstr;

        if (!this->ipAddress.empty()) break;
    }
    freeaddrinfo(result);

    if (this->ipAddress.empty()) {
        string errMsg;
        fmt::format_to(std::back_inserter(errMsg), "Unknown issue. Unable to get the associated ip address for '{}'!", dnsName);
        throw std::runtime_error(errMsg);
    }
}

DNSDetails::DNSDetails(const string & dnsName) {
    this->dnsName = std::move(dnsName);
}

void DNSDetails::CalculateAndUpdateFileDetails(std::shared_ptr<Concurrent> cPtr) {
    try {
        this->getDnsIP();
        cPtr->UpdateDNSDetails(this->dnsName, this->ipAddress);
    } catch (std::runtime_error & err) {
        fmt::print("Exception occured: {}\n", err.what());
        cPtr->UpdateDNSDetails(this->dnsName);
    }
}
