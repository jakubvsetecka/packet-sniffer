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

#include "IPv4Protocol.h"
#include <arpa/inet.h>
#include <cstring>
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

    if (packetData.getPacket().size() < sizeof(struct ether_header)) {
        std::cerr << "Packet too short to process" << std::endl;
        return; // Ensure the packet is large enough to contain an Ethernet header
    }

    // Properly accessing the packet data
    const struct ether_header *eth_header = reinterpret_cast<const struct ether_header *>(packetData.getData());
    u_int16_t type = ntohs(eth_header->ether_type); // Network to host short conversion

    ParsingContext context;
    context.setSourceMAC(eth_header->ether_shost);
    context.setDestinationMAC(eth_header->ether_dhost);
    context.setPacket(packetData.getPacket());
    context.setLength(packetData.getLength());
    context.setTimeStamp(packetData.getTimeStamp());

    auto protocol = ProtocolFactory::createProtocol(type, &context, packetData.getPacket());
    if (protocol != nullptr) {
        protocol->process();
    }

    context.print();
}