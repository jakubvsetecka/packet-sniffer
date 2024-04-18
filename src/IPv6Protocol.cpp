/**
 * @file IPv6Protocol.cpp
 * @brief IPv6 protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#include "IPv6Protocol.h"
#include "ProtocolFactory.h"
#include <iostream>
#include <netinet/ip6.h> // Correct header for IPv6

void IPv6Protocol::process() {
    // Check if the received packet is at least the size of an IPv6 header
    if (packet.size() < sizeof(struct ip6_hdr)) {
        std::cerr << "Packet too short to process" << std::endl;
        return;
    }

    // Cast the packet data to an IPv6 header structure
    const struct ip6_hdr *ip6_header = reinterpret_cast<const struct ip6_hdr *>(packet.data());

    IPAddress srcIP, destIP;
    // Directly copying IPv6 address, assuming network byte order
    std::memcpy(&srcIP.ipv6, &ip6_header->ip6_src, sizeof(struct in6_addr));
    std::memcpy(&destIP.ipv6, &ip6_header->ip6_dst, sizeof(struct in6_addr));

    context->setProtocol(ProtoType::IPv6);
    context->setSourceIP(srcIP);
    context->setDestinationIP(destIP);

    uint8_t type = ip6_header->ip6_nxt; // Next header type field in IPv6

    // Create the appropriate protocol processor based on the next header type
    auto protocol = ProtocolFactory::createProtocol(type, context, packet);
    if (protocol != nullptr) {
        protocol->process();
    }
}
