/**
 * @file ICMP6Protocol.cpp
 * @brief ICMP6 protocol
 * @version 0.1
 * @date 18/04/2024
 * @author Jakub Všetečka
*/

#include "ICMP6Protocol.h"

void ICMP6Protocol::process() {
    context->setProtocol(ProtoType::ICMP6);
}