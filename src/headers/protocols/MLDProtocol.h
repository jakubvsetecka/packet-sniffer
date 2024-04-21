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
    MLDProtocol(ParsingContext *context, std::vector<u_char> packet)
        : Protocol(context, packet) {}
    ~MLDProtocol() override = default;
    void process() override;
};

#endif // MLD_PROTOCOL_H