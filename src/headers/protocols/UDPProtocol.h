/**
 * @file UDPProtocol.h
 * @brief UDP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef UDP_PROTOCOL_H
#define UDP_PROTOCOL_H

#include "Protocol.h"

class UDPProtocol : public Protocol {
  public:
    UDPProtocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~UDPProtocol() override = default;
    void process() override{
        // Implementation of the process method for IPv4
        std::cout << "Processing UDP packet" << std::endl;
        // Add actual processing logic here
    }
};

#endif // UDP_PROTOCOL_H