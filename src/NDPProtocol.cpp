/**
 * @file NDPProtocol.cpp
 * @brief NDP protocol
 * @version 0.1
 * @date 21/04/2024
 * @author Jakub Všetečka
 */

#include "NDPProtocol.h"

void NDPProtocol::process() {
    context->setProtocol(ProtoType::NDP);
}