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
    ICMP6Protocol();
    ~ICMP6Protocol() override;
    void process() override;
};

#endif // ICMP6_PROTOCOL_H