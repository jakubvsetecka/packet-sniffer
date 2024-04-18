/**
 * @file IPv4Protocol.cpp
 * @brief IPv4 protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#include "IPv4Protocol.h"
#include "ProtocolFactory.h"
#include <arpa/inet.h> // For ntohl
#include <iostream>
#include <netinet/ip.h>

void IPv4Protocol::process() {
    if (packet.size() < sizeof(struct ip)) {
        std::cerr << "Packet too short to process" << std::endl;
        return;
    }

    const struct ip *ip_header = reinterpret_cast<const struct ip *>(packet.data());

    // Assuming IPAddress.ipv4 is a uint32_t type
    IPAddress srcIP, destIP;

    // Use ntohl to convert from network byte order to host byte order
    srcIP.ipv4 = ntohl(ip_header->ip_src.s_addr);
    destIP.ipv4 = ntohl(ip_header->ip_dst.s_addr);

    context->setProtocol(ProtoType::IPv4);
    context->setSourceIP(srcIP);
    context->setDestinationIP(destIP);

    uint8_t type = ip_header->ip_p;

    // You may need to update ProtocolFactory::createProtocol to pass the right parameters
    auto protocol = ProtocolFactory::createProtocol(type, context, packet);
    if (protocol != nullptr) {
        protocol->process();
    }
}
