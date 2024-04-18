/**
 * @file TCPProtocol.cpp
 * @brief TCP protocol
 * @version 0.1
 * @date 18/04/2024
 * @author Jakub Všetečka
 */

#include "TCPProtocol.h"
#include <cstdint> // For uint16_t
#include <iostream>

void TCPProtocol::process() {
    // Setting the protocol type to TCP
    context->setProtocol(ProtoType::TCP);

    // Ensure packet is large enough to contain an IP header and the first part of the TCP header
    // For simplicity, we assume IPv4 and no IP options, so offset is 20 bytes for IP header
    // Adjust this offset if using IPv6 or IP options are present (IPv6 would be 40 bytes)
    size_t ip_header_len = 20; // or 40 for IPv6
    size_t tcp_header_offset = ip_header_len;
    size_t minimal_tcp_header_len = 20; // Minimal TCP header length, without options

    if (packet.size() < tcp_header_offset + minimal_tcp_header_len) {
        std::cerr << "Packet too short to contain valid TCP header" << std::endl;
        return;
    }

    // Reading source and destination ports
    uint16_t srcPort = static_cast<uint16_t>(packet[tcp_header_offset] << 8 | packet[tcp_header_offset + 1]);
    uint16_t destPort = static_cast<uint16_t>(packet[tcp_header_offset + 2] << 8 | packet[tcp_header_offset + 3]);

    // Setting source and destination ports in context
    context->setSourcePort(srcPort);
    context->setDestinationPort(destPort);
}
