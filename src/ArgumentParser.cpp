/**
 * @file ArgumentParser.cpp
 * @brief Argument parser
 * @version 0.1
 * @date 13/04/2024
 * @author Jakub Všetečka
 */

#include "ArgumentParser.h"
#include "ProtoType.h"
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <pcap.h>

ArgumentParser::ArgumentParser()
    : port(-1), t_portType(PortType::ANY), numPackets(1) {
    protocols = {{ProtoType::TCP, false},
                 {ProtoType::UDP, false},
                 {ProtoType::ARP, false},
                 {ProtoType::NDP, false},
                 {ProtoType::ICMP4, false},
                 {ProtoType::ICMP6, false},
                 {ProtoType::IGMP, false},
                 {ProtoType::MLD, false}};
}

void ArgumentParser::usage() const {
    std::cout << "Usage: ./program [options]\n"
              << "Options:\n"
              << "  -i, --interface <interface>  Network interface\n"
              << "  -p, --port <port>            Port number\n"
              << "  -t, --tcp                    TCP protocol\n"
              << "  -u, --udp                    UDP protocol\n"
              << "  --arp                        ARP protocol\n"
              << "  --ndp                        NDP protocol\n"
              << "  --icmp4                      ICMPv4 protocol\n"
              << "  --icmp6                      ICMPv6 protocol\n"
              << "  --igmp                       IGMP protocol\n"
              << "  --mld                        MLD protocol\n"
              << "  -n <number>                  Number of packets\n"
              << "  -h, --help                   Display this help message\n";
}

void ArgumentParser::parse(int argc, char *argv[]) {
    const char *const short_opts = ":i:p:tun:h";
    const option long_opts[] = {
        {"interface", required_argument, nullptr, 'i'},
        {"port-source", required_argument, nullptr, '1'},
        {"port-destination", required_argument, nullptr, '2'},
        {"tcp", no_argument, nullptr, 't'},
        {"udp", no_argument, nullptr, 'u'},
        {"arp", no_argument, nullptr, 'a'},
        {"ndp", no_argument, nullptr, 'd'},
        {"icmp4", no_argument, nullptr, '4'},
        {"icmp6", no_argument, nullptr, '6'},
        {"igmp", no_argument, nullptr, 'g'},
        {"mld", no_argument, nullptr, 'm'},
        {"n", required_argument, nullptr, 'n'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}};

    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt) {
        case 'i':
            interface = optarg;
            break;
        case 'p':
            port = std::stoi(optarg);
            break;
        case '1':
            port = std::stoi(optarg);
            t_portType = PortType::SOURCE;
            break;
        case '2':
            port = std::stoi(optarg);
            t_portType = PortType::DESTINATION;
            break;
        case 't':
            protocols[ProtoType::TCP] = true;
            break;
        case 'u':
            protocols[ProtoType::UDP] = true;
            break;
        case 'a':
            protocols[ProtoType::ARP] = true;
            break;
        case 'd':
            protocols[ProtoType::NDP] = true;
            break;
        case '4':
            protocols[ProtoType::ICMP4] = true;
            break;
        case '6':
            protocols[ProtoType::ICMP6] = true;
            break;
        case 'g':
            protocols[ProtoType::IGMP] = true;
            break;
        case 'm':
            protocols[ProtoType::MLD] = true;
            break;
        case 'n':
            numPackets = std::stoi(optarg);
            break;
        case 'h': // -h or --help
            usage();
            exit(EXIT_SUCCESS);
        case ':': // Missing argument
            if (optopt == 'i') {
                interface = "";
            } else {
                throw std::invalid_argument("Missing argument");
            }
            break;
        case '?': // Unrecognized option
        default:
            usage();
            throw std::invalid_argument("Unrecognized option");
        }
    }

    validateArguments();
}

void ArgumentParser::validateArguments() const {
    if (interface.empty() && port == 0 && areAllProtocolsDisabled() && numPackets == 1) {
        listNetworkInterfaces();
    } else if (interface.empty()) {
        usage();
        throw std::invalid_argument("Interface is required");
    }
}

bool ArgumentParser::areAllProtocolsDisabled() const {
    for (const auto &pair : protocols) {
        if (pair.second) { // Check if any protocol is enabled
            return false;
        }
    }
    return true;
}

void ArgumentParser::listNetworkInterfaces() const {
    pcap_if_t *alldevs;
    pcap_if_t *device;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Fetch the list of devices
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
        return;
    }

    // Iterate over the list of devices and print them
    std::cout << "Available Network Interfaces:" << std::endl;
    for (device = alldevs; device != NULL; device = device->next) {
        std::cout << device->name;
        if (device->description)
            std::cout << " (" << device->description << ")";
        std::cout << std::endl;
    }

    // Free the device list
    pcap_freealldevs(alldevs);
}

void ArgumentParser::displayConfig() const {
    std::cout << "Interface: " << (interface.empty() ? "Any" : interface) << std::endl;
    std::cout << "Port: " << (port ? std::to_string(port) : "Any") << std::endl;
    std::cout << "PortType: " << toString(t_portType) << std::endl;
    std::cout << "Protocols: ";
    for (const auto &pair : protocols) {
        if (pair.second) {
            std::cout << toString(pair.first) << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Number of Packets: " << numPackets << std::endl;
}
