/**
 * @file PacketSniffer.h
 * @brief Network sniffer
 * @version 0.1
 * @date 14/04/2024
 * @author Jakub Všetečka
 */

#ifndef PACKET_SNIFFER_H
#define PACKET_SNIFFER_H

#include "IPCAPWrapper.h"
#include "PacketData.h"
#include "PortType.h"
#include "ProtoType.h"
#include "ThreadSafeQueue.h"
#include <map>
#include <string>
#include <unordered_map>

/**
 * @brief Network sniffer
 *
 */
class PacketSniffer {
    friend class PacketSnifferTest; // Grant the test class access to private members
  public:
    /**
     * @brief Constructor
     */
    PacketSniffer(IPCAPWrapper *pcapWrapperArg, const std::string &deviceArg, ThreadSafeQueue<PacketData> *queueArg, const std::unordered_map<ProtoType, bool> &protocolsArg, int numPacketsArg, int portArg, PortType t_portTypeArg);

    /**
     * @brief Destructor
     */
    ~PacketSniffer();

    /**
     * @brief Start capturing packets
     *
     * @return void
     */
    void startCapture();

  protected:
    IPCAPWrapper *pcapWrapper;
    pcap_t *handle;
    std::string device;
    ThreadSafeQueue<PacketData> *queue;
    std::unordered_map<ProtoType, bool> protocols;
    int numPackets;
    int port;
    PortType t_portType;
    const std::map<ProtoType, std::string> protoToFilter = {
        {ProtoType::TCP, "tcp"},
        {ProtoType::UDP, "udp"},
        {ProtoType::ICMP4, "icmp"},
        {ProtoType::ICMP6, "icmp6"},
        {ProtoType::ARP, "arp"},
        {ProtoType::NDP, "(icmp6 && (ip6[40] == 133 || ip6[40] == 134 || ip6[40] == 135 || ip6[40] == 136 || ip6[40] == 137))"},
        {ProtoType::IGMP, "igmp"},
        {ProtoType::MLD, "(icmp6 && (ip6[40] == 130 || ip6[40] == 131 || ip6[40] == 132))"}};

    /**
     * @brief Create a filter
     *
     * @param filter    Filter string
     *
     * @return std::string
     */
    std::string createFilter();

    /**
     * @brief Packet handler
     *
     * @param userData  Pointer to the PacketSniffer object
     * @param pkthdr    Packet header
     * @param packet    Packet data
     *
     * @return void
     */
    static void packetHandlerStatic(unsigned char *userData, const struct pcap_pkthdr *pkthdr, const unsigned char *packet);
};

#endif // SNIFFER_H
