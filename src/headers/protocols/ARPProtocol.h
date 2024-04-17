/**
 * @file ARPProtocol.h
 * @brief ARP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef ARP_PROTOCOL_H
#define ARP_PROTOCOL_H

#include "Protocol.h"

class ARPProtocol : public Protocol {
  public:
    ARPProtocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~ARPProtocol() override = default;
    void process() override {
        // Implementation of the process method for IPv4
        std::cout << "Processing ARP packet" << std::endl;
        // Add actual processing logic here
    }
};

#endif // ARP_PROTOCOL_H