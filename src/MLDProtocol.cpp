/**
 * @file MLDProtocol.cpp
 * @brief MLD protocol
 * @version 0.1
 * @date 21/04/2024
 * @author Jakub Všetečka
*/

#include "MLDProtocol.h"

void MLDProtocol::process() {
    context->setProtocol(ProtoType::MLD);
}