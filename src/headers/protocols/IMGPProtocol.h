/**
 * @file IMGPProtocol.h
 * @brief IMGP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef IMGP_PROTOCOL_H
#define IMGP_PROTOCOL_H

#include "Protocol.h"

class IMGPProtocol : public Protocol {
  public:
    IMGPProtocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~IMGPProtocol() override = default;
    void process() override{
        // Implementation of the process method for IPv4
        std::cout << "Processing IMGP packet" << std::endl;
        // Add actual processing logic here
    }
};

#endif // IMGP_PROTOCOL_H