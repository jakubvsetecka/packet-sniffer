/**
 * @file TCPProtocol.h
 * @brief TCP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef TCP_PROTOCOL_H
#define TCP_PROTOCOL_H

#include "Protocol.h"

class TCPProtocol : public Protocol {
  public:
    TCPProtocol();
    ~TCPProtocol() override;
    void process() override;
};

#endif // TCP_PROTOCOL_H