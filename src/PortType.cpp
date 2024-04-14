/**
 * @file PortType.cpp
 * @brief Port type
 * @version 0.1
 * @date 14/04/2024
 * @author Jakub Všetečka
 */

#include "PortType.h"

std::string toString(PortType t) {
    switch (t) {
    case PortType::SOURCE:
        return "Source";
    case PortType::DESTINATION:
        return "Destination";
    case PortType::ANY:
        return "Any";
    default:
        return "Unknown";
    }
}