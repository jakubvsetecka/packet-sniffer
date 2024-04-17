/**
 * @file ICMP6Protocol.h
 * @brief ICMP6 protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef ICMP6_PROTOCOL_H
#define ICMP6_PROTOCOL_H

#include "Protocol.h"

class ICMP6Protocol : public Protocol {
  public:
    ICMP6Protocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~ICMP6Protocol() override = default;
    void process() override;
};

#endif // ICMP6_PROTOCOL_H