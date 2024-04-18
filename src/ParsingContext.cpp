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
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

// Helper function to convert MAC or other byte arrays to readable format
std::string ParsingContext::bytesToString(const std::vector<uint8_t> &bytes) const {
    std::ostringstream stream;
    for (size_t i = 0; i < bytes.size(); ++i) {
        stream << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(bytes[i]);
        if (i < bytes.size() - 1) stream << ":";
    }
    return stream.str();
}

template <typename... Args>
void ParsingContext::printField(const std::string &fieldName, Args... args) const {
    const uint totalWidth = 78;
    uint nameWidth = 18;
    if (fieldName.size() > nameWidth) nameWidth = fieldName.size();
    int valueWidth = totalWidth - nameWidth - 3;
    std::cout << std::left << std::setw(nameWidth) << fieldName;
    printValues(std::cout, valueWidth, args...);
    std::cout << std::endl;
}

template <typename T, typename... Args>
void ParsingContext::printValues(std::ostream &os, int valueWidth, T first, Args... args) const {
    if constexpr (sizeof...(args) == 0) {                  // Last or only one element
        os << std::left << std::setw(valueWidth) << first; // Print the last or only element with full width
    } else {
        os << first << " ";                   // Print current element and a space
        printValues(os, valueWidth, args...); // Recursive call
    }
}

void ParsingContext::printValues(std::ostream &os, int valueWidth) const {
    os << std::setw(valueWidth) << " "; // Fill the rest of the space
}

void ParsingContext::printPacketData() const {
    const int bytesPerLine = 16; // Standard number of bytes per line in packet data
    std::ostringstream hexStream;
    std::ostringstream asciiStream;

    for (size_t i = 0; i < packet.size(); i += bytesPerLine) {
        hexStream.str("");
        asciiStream.str("");
        hexStream << std::hex << "0x" << std::setw(4) << std::setfill('0') << i << ": ";

        for (size_t j = i; j < i + bytesPerLine; ++j) {
            if (j < packet.size()) {
                unsigned char byte = packet[j];
                hexStream << std::setw(2) << static_cast<int>(byte) << " ";
                asciiStream << (byte >= 32 && byte <= 126 ? static_cast<char>(byte) : '.');
            } else {
                hexStream << "   ";
            }

            if (j == i + 7) { // Extra space in the middle for readability
                hexStream << " ";
            }
        }

        printField(hexStream.str(), asciiStream.str());
    }
}

// Main print function that orchestrates the printing of all fields and packet data
void ParsingContext::print() const {

    if (protoSet) {
        printField("protocol: ", toString(protocol));
    }
    printField("timestamp:", formatTimestamp());
    if (sourceMACSet) {
        printField("source MAC: ", macToString(sourceMAC));
    }
    if (destinationMACSet) {
        printField("dst MAC: ", macToString(destinationMAC));
    }
    printField("frame length: ", std::to_string(length) + " bytes");
    if (sourceIPSet) {
        printField("src IP: ", sourceIP.toString());
    }
    if (destinationIPSet) {
        printField("dst IP: ", destinationIP.toString());
    }
    if (sourcePortSet) {
        printField("src port: ", std::to_string(sourcePort));
    }
    if (destinationPortSet) {
        printField("dst port: ", std::to_string(destinationPort));
    }

    std::cout << std::endl;

    printPacketData(); // Print the packet data aligned with the above fields

    std::cout << std::endl;
    std::cout << std::endl;
}

std::string ParsingContext::formatTimestamp() const {
    std::time_t rawtime = timeStamp.tv_sec;
    struct tm *dt;
    char buffer[30];
    dt = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", dt);
    long milliseconds = timeStamp.tv_usec / 1000; // Convert microseconds to milliseconds
    std::string tz = (dt->tm_gmtoff >= 0 ? "+" : "-") + std::to_string(abs(dt->tm_gmtoff / 3600)) + ":00";
    return std::string(buffer) + "." + std::to_string(milliseconds) + tz;
}

void ParsingContext::setProtocol(ProtoType protocol) {
    protoSet = true;
    this->protocol = protocol;
}

void ParsingContext::setSourceMAC(const uint8_t sourceMAC[6]) {
    sourceMACSet = true;
    std::memcpy(this->sourceMAC, sourceMAC, 6);
}

void ParsingContext::setDestinationMAC(const uint8_t destinationMAC[6]) {
    destinationMACSet = true;
    std::memcpy(this->destinationMAC, destinationMAC, 6);
}

void ParsingContext::setTimeStamp(timeval timeStamp) {
    timeStampSet = true;
    this->timeStamp = timeStamp;
}

void ParsingContext::setLength(size_t length) {
    lengthSet = true;
    this->length = length;
}

void ParsingContext::setSourceIP(IPAddress sourceIP) {
    sourceIPSet = true;
    this->sourceIP = sourceIP;
}

void ParsingContext::setDestinationIP(IPAddress destinationIP) {
    destinationIPSet = true;
    this->destinationIP = destinationIP;
}

void ParsingContext::setSourcePort(uint16_t sourcePort) {
    sourcePortSet = true;
    this->sourcePort = sourcePort;
}

void ParsingContext::setDestinationPort(uint16_t destinationPort) {
    destinationPortSet = true;
    this->destinationPort = destinationPort;
}

void ParsingContext::setPacket(std::vector<uint8_t> packet) {
    packetSet = true;
    this->packet = packet;
}

std::string ParsingContext::macToString(const uint8_t *mac) const {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < 6; ++i) {
        ss << std::setw(2) << static_cast<unsigned>(mac[i]);
        if (i < 5) ss << ":";
    }
    return ss.str();
}
