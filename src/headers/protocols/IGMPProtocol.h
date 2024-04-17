/**
 * @file IGMPProtocol.h
 * @brief IGMP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef IGMP_PROTOCOL_H
#define IGMP_PROTOCOL_H

#include "Protocol.h"

class IGMPProtocol : public Protocol {
  public:
    IGMPProtocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~IGMPProtocol() override = default;
    void process() override {
        // Implementation of the process method for IPv4
        std::cout << "Processing IGMP packet" << std::endl;
        // Add actual processing logic here
    }
};

#endif // IGMP_PROTOCOL_H