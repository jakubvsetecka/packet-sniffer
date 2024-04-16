/**
 * @file PacketHandler.h
 * @brief Packet handler
 * @version 0.1
 * @date 16/04/2024
 * @author Jakub Všetečka
 */

#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include "PacketData.h"
#include "ThreadSafeQueue.h"

class PacketHandler {
  public:
    PacketHandler(ThreadSafeQueue<PacketData> *queueArg);
    ~PacketHandler();

    void run();
    void stop();

  private:
    ThreadSafeQueue<PacketData> *queue;
    std::thread worker;

    void processPacket(const PacketData &packet);
};

#endif // PACKET_HANDLER_H