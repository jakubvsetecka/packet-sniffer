/**
 * @file IGMPProtocol.h
 * @brief IGMP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef IGMP_PROTOCOL_H
#define IGMP_PROTOCOL_H

#include "Protocol.h"

class IGMPProtocol : public Protocol {
  public:
    IGMPProtocol();
    ~IGMPProtocol() override;
    void process() override;
};

#endif // IGMP_PROTOCOL_H