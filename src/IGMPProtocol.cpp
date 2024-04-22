/**
 * @file IGMPProtocol.cpp
 * @brief IGMP protocol
 * @version 0.1
 * @date 22/04/2024
 * @author Jakub Všetečka
 */

#include "IGMPProtocol.h"

void IGMPProtocol::process() {
    context->setProtocol(ProtoType::IGMP);
}