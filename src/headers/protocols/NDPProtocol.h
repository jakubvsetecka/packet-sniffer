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
    NDPProtocol();
    ~NDPProtocol() override;
    void process() override;
};

#endif // NDP_PROTOCOL_H