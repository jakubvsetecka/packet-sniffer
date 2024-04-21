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
#include <sstream>

// Constructor Definition
PacketSniffer::PacketSniffer(IPCAPWrapper *pcapWrapperArg, const std::string &deviceArg, ThreadSafeQueue<PacketData> *queueArg,
                             const std::unordered_map<ProtoType, bool> &protocolsArg, int numPacketsArg,
                             int portArg, PortType t_portTypeArg)
    : pcapWrapper(pcapWrapperArg), device(deviceArg), queue(queueArg), protocols(protocolsArg),
      numPackets(numPacketsArg), port(portArg), t_portType(t_portTypeArg) {
    char errbuf[PCAP_ERRBUF_SIZE];

    // Open session
    handle = pcapWrapper->open_live(device.c_str(), 65535, 1, 1000, errbuf);
    if (handle == nullptr) {
        throw std::runtime_error("pcap_open_live failed: " + std::string(errbuf));
    }

    // Create Filter
    std::string filter = createFilter();
    struct bpf_program fp;

    // Compile Filter
    if (pcapWrapper->compile(handle, &fp, filter.c_str(), 0, PCAP_NETMASK_UNKNOWN) == -1) {
        throw std::runtime_error("pcap_compile failed: " + std::string(pcap_geterr(handle)));
    }

    // Set Filter
    if (pcapWrapper->setfilter(handle, &fp) == -1) {
        throw std::runtime_error("pcap_setfilter failed: " + std::string(pcap_geterr(handle)));
    }
}

PacketSniffer::~PacketSniffer() {
    // Close handle
    if (handle) {
        pcapWrapper->close(handle);
    }
}

std::string PacketSniffer::createFilter() {
    std::ostringstream filter;

    // Add port
    switch (t_portType) {
    case PortType::DESTINATION:
        filter << "dst port " << port;
        break;
    case PortType::SOURCE:
        filter << "src port " << port;
        break;
    case PortType::ANY:
        if (port != -1) {
            filter << "port " << port;
        }
        break;
    }

    // Add protocols
    bool first = true;
    for (const auto &kv : protocols) {
        if (kv.second) { // Ensure the protocol is set to true
            if (first) {
                if (port != -1) {
                    filter << " and (";
                }
                first = false;
            } else {
                filter << " or ";
            }
            filter << protoToFilter.at(kv.first); // This will throw an error if kv.first is not found
        }
    }

    if (!first && port != -1) { // This means the loop ran at least once and a protocol was added
        filter << ")";
    }

    std::string filterStr = filter.str();
    // std::cout << "Filter: " << filterStr << std::endl;
    return filterStr;
}

void PacketSniffer::startCapture() {
    pcapWrapper->loop(handle, numPackets, PacketSniffer::packetHandlerStatic, reinterpret_cast<u_char *>(this));
}

void PacketSniffer::packetHandlerStatic(u_char *userData, const struct pcap_pkthdr *header, const u_char *packet) {
    PacketSniffer *sniffer = reinterpret_cast<PacketSniffer *>(userData);
    sniffer->queue->push(PacketData(header, packet));
}