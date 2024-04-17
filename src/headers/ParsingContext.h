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
#include <cstdint>
#include <netinet/in.h>

class ParsingContext {
  public:
    ParsingContext();
    ~ParsingContext();
    void print();

    void setSourceMAC(uint8_t sourceMAC[6]);
    void setDestinationMAC(uint8_t destinationMAC[6]);
    void setTimeStamp(timeval timeStamp);
    void setLength(size_t length);
    void setSourceIP(IPAddress sourceIP);
    void setDestinationIP(IPAddress destinationIP);
    void setSourcePort(uint16_t sourcePort);
    void setDestinationPort(uint16_t destinationPort);

  private:
    uint8_t sourceMAC[6];
    uint8_t destinationMAC[6];
    timeval timeStamp;
    size_t length;
    IPAddress sourceIP;
    IPAddress destinationIP;
    uint16_t sourcePort;
    uint16_t destinationPort;
};

#endif // PARSING_CONTEXT_H