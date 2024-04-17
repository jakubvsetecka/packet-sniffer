/**
 * @file ProtocolFactory.h
 * @brief Protocol factory
 * @version 0.1
 * @date 17/04/2024
 * @author Jakub Všetečka
 */

#ifndef PROTOCOL_FACTORY_H
#define PROTOCOL_FACTORY_H

#include "ARPProtocol.h"
#include "ICMP4Protocol.h"
#include "ICMP6Protocol.h"
#include "IGMPProtocol.h"
#include "IPv4Protocol.h"
#include "IPv6Protocol.h"
#include "MLDProtocol.h"
#include "NDPProtocol.h"
#include "ParsingContext.h"
#include "Protocol.h"
#include "TCPProtocol.h"
#include "UDPProtocol.h"
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class ProtocolFactory {
  public:
    static std::shared_ptr<Protocol> createProtocol(uint16_t type, ParsingContext *context, const std::vector<u_char> &packet) {
        static std::map<int, std::function<std::shared_ptr<Protocol>(ParsingContext *, const std::vector<u_char> &)>> registry = {
            {ETHERTYPE_IP, [](ParsingContext *ctx, const std::vector<u_char> &pkt) { return std::make_shared<IPv4Protocol>(ctx, pkt); }},
            {ETHERTYPE_IPV6, [](ParsingContext *ctx, const std::vector<u_char> &pkt) { return std::make_shared<IPv6Protocol>(ctx, pkt); }},
            {ETHERTYPE_ARP, [](ParsingContext *ctx, const std::vector<u_char> &pkt) { return std::make_shared<ARPProtocol>(ctx, pkt); }},
            {IPPROTO_TCP, [](ParsingContext *ctx, const std::vector<u_char> &pkt) { return std::make_shared<TCPProtocol>(ctx, pkt); }},
            {IPPROTO_UDP, [](ParsingContext *ctx, const std::vector<u_char> &pkt) { return std::make_shared<UDPProtocol>(ctx, pkt); }},
            {IPPROTO_ICMP, [](ParsingContext *ctx, const std::vector<u_char> &pkt) { return std::make_shared<ICMP4Protocol>(ctx, pkt); }},
            {IPPROTO_ICMPV6, [](ParsingContext *ctx, const std::vector<u_char> &pkt) { return std::make_shared<ICMP6Protocol>(ctx, pkt); }},
            {IPPROTO_IGMP, [](ParsingContext *ctx, const std::vector<u_char> &pkt) { return std::make_shared<IGMPProtocol>(ctx, pkt); }}};

        auto it = registry.find(type);
        if (it != registry.end()) {
            return it->second(context, packet); // Create a new instance using the registered factory method
        }
        std::cerr << "No handler registered for type: 0x" << std::hex << type << std::endl;
        return nullptr;
    }
};

#endif // PROTOCOL_FACTORY_H
