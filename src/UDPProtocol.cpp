/**
 * @file UDPProtocol.cpp
 * @brief UDP protocol
 * @version 0.1
 * @date 18/04/2024
 * @author Jakub Všetečka
 */

#include "UDPProtocol.h"
#include <cstdint> // For uint16_t
#include <iostream>

void UDPProtocol::process() {
    // Setting the protocol type to UDP
    context->setProtocol(ProtoType::UDP);

    // Ensure packet is large enough to contain an IP header and UDP header
    // For simplicity, we assume IPv4 and no IP options, so offset is 20 bytes for IP header
    // Adjust this offset if using IPv6 or IP options are present (IPv6 would be 40 bytes)
    size_t ip_header_len = 20; // or 40 for IPv6
    size_t udp_header_offset = ip_header_len;
    size_t udp_header_len = 8;

    if (packet.size() < udp_header_offset + udp_header_len) {
        std::cerr << "Packet too short to contain valid UDP header" << std::endl;
        return;
    }

    // Reading source and destination ports
    uint16_t srcPort = static_cast<uint16_t>(packet[udp_header_offset] << 8 | packet[udp_header_offset + 1]);
    uint16_t destPort = static_cast<uint16_t>(packet[udp_header_offset + 2] << 8 | packet[udp_header_offset + 3]);

    // Setting source and destination ports in context
    context->setSourcePort(srcPort);
    context->setDestinationPort(destPort);
}