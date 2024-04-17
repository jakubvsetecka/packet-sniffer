/**
 * @file PacketHandler.cpp
 * @brief Packet handler
 * @version 0.1
 * @date 16/04/2024
 * @author Jakub Všetečka
 */

#include "PacketHandler.h"
#include <netinet/ether.h>

#include <iomanip>

#include <arpa/inet.h>
#include <cstring>
#include <iomanip> // For std::setw and std::setfill
#include <iostream>
#include <netinet/if_ether.h>
#include <vector>

PacketHandler::PacketHandler(ThreadSafeQueue<PacketData> *queueArg)
    : queue(queueArg), worker(&PacketHandler::run, this) {}

PacketHandler::~PacketHandler() {
    if (worker.joinable()) {
        worker.join();
    }
}

void PacketHandler::run() {
    while (true) {
        PacketData packet = queue->pop();

        if (packet.stop) {
            break;
        }

        processPacket(packet);
    }
}

void PacketHandler::stop() {
    PacketData stopPacket;
    queue->push(stopPacket);
}

void PacketHandler::processPacket(const PacketData &packetData) {
    std::cout << "Processing packet: " << std::endl;
    std::cout << packetData << std::endl;

    if (packetData.getPacket().size() < sizeof(struct ether_header)) {
        std::cerr << "Packet too short to process" << std::endl;
        return; // Ensure the packet is large enough to contain an Ethernet header
    }

    // Properly accessing the packet data
    const struct ether_header *eth_header = reinterpret_cast<const struct ether_header *>(packetData.getData());
    u_int16_t type = ntohs(eth_header->ether_type); // Network to host short conversion

    // Print source and destination MAC addresses
    std::cout << "Destination MAC: ";
    for (int i = 0; i < 6; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(eth_header->ether_dhost[i]);
        if (i < 5) std::cout << ":";
    }
    std::cout << "\nSource MAC: ";
    for (int i = 0; i < 6; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(eth_header->ether_dhost[i]);
        if (i < 5) std::cout << ":";
    }
    std::cout << std::endl;

    switch (type) {
    case ETHERTYPE_IP:
        std::cout << "IPv4 Packet" << std::endl;
        break;
    case ETHERTYPE_ARP:
        std::cout << "ARP Packet" << std::endl;
        break;
    case ETHERTYPE_IPV6:
        std::cout << "IPv6 Packet" << std::endl;
        break;
    default:
        std::cout << "Other Type: 0x" << std::hex << type << std::endl;
        break;
    }
}