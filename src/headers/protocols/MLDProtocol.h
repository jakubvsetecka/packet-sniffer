/**
 * @file MLDProtocol.h
 * @brief MLD protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef MLD_PROTOCOL_H
#define MLD_PROTOCOL_H

#include "Protocol.h"

class MLDProtocol : public Protocol {
  public:
    MLDProtocol();
    ~MLDProtocol() override;
    void process() override;
};

#endif // MLD_PROTOCOL_H