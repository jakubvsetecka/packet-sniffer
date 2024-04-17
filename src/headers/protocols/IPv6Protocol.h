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
    IPv6Protocol();
    ~IPv6Protocol() override;
    void process() override;
};

#endif // IPV6_PROTOCOL_H