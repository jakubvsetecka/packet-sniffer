/**
 * @file PacketData.h
 * @brief Packet data
 * @version 0.1
 * @date 16/04/2024
 * @author Jakub Všetečka
 */

#ifndef PACKET_DATA_H
#define PACKET_DATA_H

#include <cstring>
#include <iostream>
#include <pcap.h>
#include <vector>

class PacketData {
  public:
    bool stop = false;

    // Default constructor for stop packet
    PacketData()
        : stop(true), packet(), header() {}

    // Standard constructor for normal packets
    PacketData(const pcap_pkthdr *headerArg, const u_char *packetArg)
        : stop(false), packet(packetArg, packetArg + headerArg->caplen), header(*headerArg) {}

    size_t getLength() const {
        return header.len;
    }

    size_t getCapturedLength() const {
        return header.caplen;
    }

    timeval getTimeStamp() const {
        return header.ts;
    }

    const u_char *getData() const {
        return packet.data();
    }

    const std::vector<u_char> &getPacket() const {
        return packet;
    }

    friend std::ostream &operator<<(std::ostream &os, const PacketData &pd);

  private:
    std::vector<u_char> packet;
    pcap_pkthdr header;
};

inline std::ostream &operator<<(std::ostream &os, const PacketData &pd) {
    if (pd.stop) {
        os << "Stop Packet" << std::endl;
    } else {
        os << "Timestamp: " << pd.getTimeStamp().tv_sec << "." << pd.getTimeStamp().tv_usec << "\n"
           << "Captured length: " << pd.getCapturedLength() << "\n"
           << "Original length: " << pd.getLength() << "\n";
    }
    return os;
}

#endif // PACKET_DATA_H