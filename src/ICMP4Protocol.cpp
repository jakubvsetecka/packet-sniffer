/**
 * @file ICMP4Protocol.cpp
 * @brief ICMP4 protocol
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#include "ICMP4Protocol.h"

void ICMP4Protocol::process() {
    context->setProtocol(ProtoType::ICMP4);
}