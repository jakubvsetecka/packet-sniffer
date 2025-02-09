/**
 * @file NDPProtocol.h
 * @brief NDP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef NDP_PROTOCOL_H
#define NDP_PROTOCOL_H

#include "Protocol.h"

class NDPProtocol : public Protocol {
  public:
    NDPProtocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~NDPProtocol() override = default;
    void process() override;
};

#endif // NDP_PROTOCOL_H