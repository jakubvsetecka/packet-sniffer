/**
 * @file ARPProtocol.cpp
 * @brief ARP protocol
 * @version 0.1
 * @date 18/04/2024
 * @author Jakub Všetečka
 */

#include "ARPProtocol.h"
#include <cstring> // For memcpy if needed
#include <iostream>

void ARPProtocol::process() {
    context->setProtocol(ProtoType::ARP);

    if (packet.size() < 28) {
        std::cerr << "ARP packet too short to process" << std::endl;
        return;
    }

    IPAddress srcIP, destIP;

    std::memcpy(&srcIP.ipv4, &packet[14], 4); // Copy 4 bytes of sender IP

    std::memcpy(&destIP.ipv4, &packet[24], 4); // Copy 4 bytes of target IP

    context->setSourceIP(srcIP);
    context->setDestinationIP(destIP);
}