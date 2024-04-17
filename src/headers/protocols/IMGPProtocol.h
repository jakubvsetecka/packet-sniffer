/**
 * @file IMGPProtocol.h
 * @brief IMGP protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef IMGP_PROTOCOL_H
#define IMGP_PROTOCOL_H

#include "Protocol.h"

class IMGPProtocol : public Protocol {
  public:
    IMGPProtocol();
    ~IMGPProtocol() override;
    void process() override;
};

#endif // IMGP_PROTOCOL_H