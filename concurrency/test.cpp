#include <arpa/inet.h>
#include <cstdlib>
#include <netdb.h>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <iostream>

using std::string;

string getDnsIP(string dnsName) {
    string ipAddress;
    int sfd, s;
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    s = getaddrinfo(dnsName.c_str(), NULL, &hints, &result);
    if (s != 0) {
        string errMsg;
        fmt::format_to(std::back_inserter(errMsg),
                       "Invalid hostname '{}' provided!", dnsName);
        throw std::runtime_error(errMsg);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
        char ipstr[INET6_ADDRSTRLEN];
        inet_ntop(rp->ai_family, (void *)(&ipv4->sin_addr), ipstr,
                  sizeof ipstr);
        ipAddress = ipstr;
        fmt::print("IP address is {}\n", ipAddress);
    }
    freeaddrinfo(result);

    if (ipAddress.empty()) {
        string errMsg;
        fmt::format_to(
            std::back_inserter(errMsg),
            "Unknown issue. Unable to get the associate ip address for '{}'!",
            dnsName);
        throw std::runtime_error(errMsg);
    }

    return ipAddress;
}

int main() {
    string dnsName = "testcontroller.eng.velocix.com";
    string ipAddress = getDnsIP(dnsName);
    fmt::print("ipaddress of '{}' is {}\n", dnsName, ipAddress);

    return EXIT_SUCCESS;
}
