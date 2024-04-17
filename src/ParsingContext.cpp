/**
 * @file ParsingContext.cpp
 * @brief Parsing context
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#include "ParsingContext.h"
#include <chrono>  // For system_clock
#include <ctime>   // For localtime, strftime
#include <iomanip> // For setfill, setw
#include <iostream>
#include <vector>

void ParsingContext::print() const {
    std::cout << "Protocol: " << toString(protocol) << std::endl;

    // Convert timestamp to readable format
    std::time_t rawtime = timeStamp.tv_sec;
    struct tm *dt;
    char buffer[30]; // Buffer to hold the datetime string
    dt = localtime(&rawtime);
    // Format datetime in ISO 8601 style
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", dt);
    long milliseconds = timeStamp.tv_usec / 1000; // Convert microseconds to milliseconds

    std::cout << "Timestamp: " << buffer << "." << std::setfill('0') << std::setw(3) << milliseconds;
    int timezoneOffset = dt->tm_gmtoff / 3600; // Local timezone offset
    std::cout << (timezoneOffset >= 0 ? "+" : "") << timezoneOffset << ":00" << std::endl;

    std::cout << "MAC Source: " << macToString(sourceMAC) << std::endl;
    std::cout << "MAC Destination: " << macToString(destinationMAC) << std::endl;
    std::cout << "Length: " << std::dec << length << " bytes" << std::endl; // Print length in decimal
    std::cout << "IP Source: " << sourceIP.toString() << std::endl;
    std::cout << "IP Destination: " << destinationIP.toString() << std::endl;
    std::cout << "Port Source: " << std::dec << sourcePort << std::endl; // Print port in decimal
    std::cout << "Port Destination: " << std::dec << destinationPort << std::endl;

    std::cout << std::endl;
    for (auto byte : packet) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)byte << " "; // Ensure packet is printed in hex
    }
    std::cout << std::dec << std::endl; // Switch back to decimal output after hex

    std::cout << std::endl;
    std::cout << std::endl;
}

void ParsingContext::setProtocol(ProtoType protocol) {
    this->protocol = protocol;
}

void ParsingContext::setSourceMAC(const uint8_t sourceMAC[6]) {
    std::memcpy(this->sourceMAC, sourceMAC, 6);
}

void ParsingContext::setDestinationMAC(const uint8_t destinationMAC[6]) {
    std::memcpy(this->destinationMAC, destinationMAC, 6);
}

void ParsingContext::setTimeStamp(timeval timeStamp) {
    this->timeStamp = timeStamp;
}

void ParsingContext::setLength(size_t length) {
    this->length = length;
}

void ParsingContext::setSourceIP(IPAddress sourceIP) {
    this->sourceIP = sourceIP;
}

void ParsingContext::setDestinationIP(IPAddress destinationIP) {
    this->destinationIP = destinationIP;
}

void ParsingContext::setSourcePort(uint16_t sourcePort) {
    this->sourcePort = sourcePort;
}

void ParsingContext::setDestinationPort(uint16_t destinationPort) {
    this->destinationPort = destinationPort;
}

void ParsingContext::setPacket(std::vector<uint8_t> packet) {
    this->packet = packet;
}

std::string ParsingContext::macToString(const uint8_t *mac) const {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < 6; ++i) {
        ss << std::setw(2) << (unsigned int)mac[i];
        if (i < 5)
            ss << ":";
    }
    return ss.str();
}
