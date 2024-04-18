/**
 * @file TCPProtocol.h
 * @brief TCP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef TCP_PROTOCOL_H
#define TCP_PROTOCOL_H

#include "Protocol.h"

class TCPProtocol : public Protocol {
  public:
    TCPProtocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~TCPProtocol() override = default;
    void process() override;
};

#endif // TCP_PROTOCOL_H