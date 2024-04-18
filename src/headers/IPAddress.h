/**
 * @file IPAdress.h
 * @brief IPAdress
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef IPADRESS_H
#define IPADRESS_H

#include <arpa/inet.h> // For inet_ntop
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <string>
#include <sys/time.h> // For struct timeval

enum IPType {
    IPv4 = 4,
    IPv6 = 6
};

union IPAddress {
    uint32_t ipv4;        // IPv4 address (4 bytes)
    struct in6_addr ipv6; // IPv6 address (16 bytes)

    IPAddress() { memset(this, 0, sizeof(*this)); } // Constructor to zero-initialize the union

    std::string toString() const {
        char buffer[INET6_ADDRSTRLEN];       // Buffer to hold the IP address string
        memset(buffer, 0, INET6_ADDRSTRLEN); // Initialize the buffer to zero

        if (ipv4) {                                // Assuming ipv4 is non-zero for IPv4 addresses
            uint32_t net_order_ipv4 = htonl(ipv4); // Convert to network byte order
            inet_ntop(AF_INET, &net_order_ipv4, buffer, INET_ADDRSTRLEN);
        } else { // For IPv6 addresses
            inet_ntop(AF_INET6, &ipv6, buffer, INET6_ADDRSTRLEN);
        }
        return std::string(buffer);
    }
};

#endif // IPADRESS_H