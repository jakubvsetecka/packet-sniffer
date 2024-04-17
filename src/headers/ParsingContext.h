/**
 * @file ParsingContext.h
 * @brief Parsing context
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef PARSING_CONTEXT_H
#define PARSING_CONTEXT_H

#include "IPAddress.h"
#include "ProtoType.h"
#include <cstdint>
#include <netinet/in.h>
#include <vector>

class ParsingContext {
  public:
    ParsingContext() = default;
    ~ParsingContext() = default;
    void print() const;

    void setProtocol(ProtoType protocol);
    void setSourceMAC(const uint8_t sourceMAC[6]);
    void setDestinationMAC(const uint8_t destinationMAC[6]);
    void setTimeStamp(timeval timeStamp);
    void setLength(size_t length);
    void setSourceIP(IPAddress sourceIP);
    void setDestinationIP(IPAddress destinationIP);
    void setSourcePort(uint16_t sourcePort);
    void setDestinationPort(uint16_t destinationPort);
    void setPacket(std::vector<uint8_t> packet);

  private:
    ProtoType protocol;
    uint8_t sourceMAC[6];
    uint8_t destinationMAC[6];
    timeval timeStamp;
    size_t length;
    IPAddress sourceIP;
    IPAddress destinationIP;
    uint16_t sourcePort;
    uint16_t destinationPort;
    std::vector<uint8_t> packet;

    std::string macToString(const uint8_t mac[6]) const;
};

#endif // PARSING_CONTEXT_H