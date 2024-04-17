/**
 * @file Protocol.h
 * @brief Protocol
 * @version 0.1
 * @date 16/04/2024
 * @author Jakub Všetečka
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

class Protocol {
  public:
    Protocol();
    virtual ~Protocol();
    virtual void proccess();
};

#endif // PROTOCOL_H