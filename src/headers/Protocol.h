/**
 * @file Protocol.h
 * @brief Protocol
 * @version 0.1
 * @date 16/04/2024
 * @author Jakub Všetečka
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "PacketData.h"
#include <netinet/if_ether.h>

class Protocol {
  public:
    Protocol(ParsingContext *context, std::vector<u_char> packet)
        : context(context), packet(packet) {}
    virtual ~Protocol();
    virtual void process();

  protected:
    ParsingContext *context;
    std::vector<u_char> packet;
};

#endif // PROTOCOL_H