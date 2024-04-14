/**
 * @file ProtoType.cpp
 * @brief Protocol type
 * @version 0.1
 * @date 14/04/2024
 * @author Jakub Všetečka
 */

#include "ProtoType.h"

std::string toString(ProtoType t) {
    switch (t) {
    case ProtoType::TCP:
        return "TCP";
    case ProtoType::UDP:
        return "UDP";
    case ProtoType::ICMP4:
        return "ICMP4";
    case ProtoType::ICMP6:
        return "ICMP6";
    case ProtoType::ARP:
        return "ARP";
    case ProtoType::NDP:
        return "NDP";
    case ProtoType::IGMP:
        return "IGMP";
    case ProtoType::MLD:
        return "MLD";
    default:
        return "Unknown";
    }
}