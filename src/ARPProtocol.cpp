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

    if (packet.size() < 42) { // Minimal ARP packet size with Ethernet header
        std::cerr << "ARP packet too short to process" << std::endl;
        return;
    }

    IPAddress srcIP, destIP;
    // Extracting sender IP address (at offset 28)
    std::memcpy(&srcIP.ipv4, &packet[28], 4); // Copy 4 bytes of IP

    // Extracting target IP address (at offset 38)
    std::memcpy(&destIP.ipv4, &packet[38], 4); // Copy 4 bytes of IP

    context->setSourceIP(srcIP);
    context->setDestinationIP(destIP);
}