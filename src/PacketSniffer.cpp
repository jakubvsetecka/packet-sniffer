/**
 * @file PacketSniffer.cpp
 * @brief Network sniffer
 * @version 0.1
 * @date 14/04/2024
 * @author Jakub Všetečka
 */

#include "PacketSniffer.h"
#include <cstring>
#include <iostream>
#include <pcap.h>

PacketSniffer::PacketSniffer(const std::string &device, ThreadSafeQueue<PacketData> *queue, const std::unordered_map<std::string, bool> &protocols, int numPackets, int port, PortType t_portType)
    : handle(nullptr), device(device), queue(queue), protocols(protocols), numPackets(numPackets), port(port), t_portType(t_portType) {
    char errbuf[PCAP_ERRBUF_SIZE];
    handle = pcap_open_live(device.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        throw std::runtime_error("pcap_open_live failed: " + std::string(errbuf));
    }
}

PacketSniffer::~PacketSniffer() {
    if (handle) {
        pcap_close(handle);
    }
}

void PacketSniffer::startCapture() {
    pcap_loop(handle, 5, PacketSniffer::packetHandlerStatic, reinterpret_cast<u_char *>(this));
}

void PacketSniffer::packetHandlerStatic(u_char *userData, const struct pcap_pkthdr *header, const u_char *packet) {
    PacketSniffer *sniffer = reinterpret_cast<PacketSniffer *>(userData);
    sniffer->queue->push(PacketData(header, packet));
}

std::ostream &operator<<(std::ostream &os, const PacketSniffer::PacketData &pd) {
    os << "Timestamp: " << pd.ts.tv_sec << "." << pd.ts.tv_usec
       << ", Captured Length: " << pd.caplen
       << ", Original Length: " << pd.len
       << ", Data Size: " << pd.data.size() << " bytes";
    return os;
}