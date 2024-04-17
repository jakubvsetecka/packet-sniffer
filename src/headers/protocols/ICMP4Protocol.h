/**
 * @file ICMP4Protocol.h
 * @brief ICMP4 protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef ICMP4_PROTOCOL_H
#define ICMP4_PROTOCOL_H

#include "Protocol.h"

class ICMP4Protocol : public Protocol {
  public:
    ICMP4Protocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~ICMP4Protocol() override = default;
    void process() override {
        // Implementation of the process method for IPv4
        std::cout << "Processing ICMPv4 packet" << std::endl;
        // Add actual processing logic here
    }
};

#endif // ICMP4_PROTOCOL_H