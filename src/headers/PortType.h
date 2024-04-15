/**
 * @file PortType.h
 * @brief Port type
 * @version 0.1
 * @date 14/04/2024
 * @author Jakub Všetečka
 */

#ifndef PORT_TYPE_H
#define PORT_TYPE_H

#include <string>

/**
 * @brief Port type
 *
 */
enum class PortType {
    SOURCE,      // Source port
    DESTINATION, // Destination port
    ANY          // Any port
};

/**
 * @brief Convert PortType to string
 * @param t PortType
 * @return std::string
 */
std::string toString(PortType t);

#endif // PORT_TYPE_H