/**
 * @file IPv6Protocol.h
 * @brief IPv6 protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef IPV6_PROTOCOL_H
#define IPV6_PROTOCOL_H

#include "Protocol.h"

class IPv6Protocol : public Protocol {
  public:
    IPv6Protocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~IPv6Protocol() override = default;
    void process() override;
};

#endif // IPV6_PROTOCOL_H