/**
 * @file ARPProtocol.h
 * @brief ARP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef ARP_PROTOCOL_H
#define ARP_PROTOCOL_H

#include "Protocol.h"

class ARPProtocol : public Protocol {
  public:
    ARPProtocol();
    ~ARPProtocol() override;
    void process() override;
};

#endif // ARP_PROTOCOL_H