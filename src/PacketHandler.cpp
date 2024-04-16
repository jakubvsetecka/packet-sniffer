/**
 * @file PacketHandler.cpp
 * @brief Packet handler
 * @version 0.1
 * @date 16/04/2024
 * @author Jakub Všetečka
 */

#include "PacketHandler.h"

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

void PacketHandler::processPacket(const PacketData &packet) {
    std::cout << packet << std::endl;
}