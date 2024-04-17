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

/**
 * @brief Packet handler
 */
class PacketHandler {
  public:
    /**
     * @brief Construct a new Packet Handler object
     *
     * @param queueArg
     */
    PacketHandler(ThreadSafeQueue<PacketData> *queueArg);

    /**
     * @brief Destroy the Packet Handler object
     */
    ~PacketHandler();

    /**
     * @brief Run the packet handler
     *
     * @return void
     */
    void run();

    /**
     * @brief Stop the packet handler
     *
     * @return void
     */
    void stop();

  private:
    ThreadSafeQueue<PacketData> *queue;
    std::thread worker;

    /**
     * @brief Process the packet
     *
     * @param packet
     * @return void
     */
    void processPacket(const PacketData &packet);
};

#endif // PACKET_HANDLER_H