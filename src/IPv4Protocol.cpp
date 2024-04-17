/**
 * @file IPv4Protocol.cpp
 * @brief IPv4 protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#include "IPv4Protocol.h"
#include <iostream>
#include <netinet/ip.h>

void IPv4Protocol::process() {
    if (packet.size() < sizeof(struct ip)) {
        std::cerr << "Packet too short to process" << std::endl;
        return;
    }

    const struct ip *ip_header = reinterpret_cast<const struct ip *>(packet.data());

    IPAddress srcIP, destIP;
    srcIP.ipv4 = ip_header->ip_src.s_addr; // Assuming network byte order is handled if needed
    destIP.ipv4 = ip_header->ip_dst.s_addr;

    context->setProtocol(ProtoType::IPv4);
    context->setSourceIP(srcIP);
    context->setDestinationIP(destIP);
}