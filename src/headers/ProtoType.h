/**
 * @file ProtoType.h
 * @brief Protocol type
 * @version 0.1
 * @date 14/04/2024
 * @author Jakub Všetečka
 */

#ifndef PROTOTYPE_H // Include guard starts
#define PROTOTYPE_H

#include <string>
#include <unordered_map>

/**
 * @brief Protocol type
 *
 */
enum class ProtoType {
    TCP,
    UDP,
    ICMP4,
    ICMP6,
    ARP,
    NDP,
    IGMP,
    MLD,
    IPv4,
    IPv6,
    UNKNOWN
};

/**
 * @brief Convert ProtoType to string
 * @param t ProtoType
 * @return std::string
 */
std::string toString(ProtoType t);

#endif // PROTOTYPE_H