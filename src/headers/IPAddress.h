/**
 * @file IPAdress.h
 * @brief IPAdress
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef IPADRESS_H
#define IPADRESS_H

#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <sys/time.h> // For struct timeval

enum IPType {
    IPv4 = 4,
    IPv6 = 6
};

union IPAddress {
    uint32_t ipv4;        // IPv4 address (4 bytes)
    struct in6_addr ipv6; // IPv6 address (16 bytes)

    IPAddress() { memset(this, 0, sizeof(*this)); } // Constructor to zero-initialize the union
};

#endif // IPADRESS_H