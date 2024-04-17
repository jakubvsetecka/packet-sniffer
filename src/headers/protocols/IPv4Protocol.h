/**
 * @file IPv4Protocol.h
 * @brief IPv4 protocol
 * @version 0.1
 * @date 16/04/2024
 * @author Jakub Všetečka
 */

#ifndef IPV4_PROTOCOL_H
#define IPV4_PROTOCOL_H

#include "Protocol.h"

class IPv4Protocol : public Protocol {
  public:
    IPv4Protocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~IPv4Protocol() override = default;
    void process() override;
};

#endif // IPV4_PROTOCOL_H