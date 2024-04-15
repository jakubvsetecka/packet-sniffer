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
  public:
    /**
     * @brief Packet data
     *
     */
    struct PacketData {
        struct timeval ts;        // Timestamp for the packet
        std::vector<u_char> data; // Packet data
        size_t caplen;            // Captured length of the packet
        size_t len;               // Original length of the packet

        // Constructor that initializes the timestamp, captured length,
        // original length, and copies packet data
        PacketData(const struct pcap_pkthdr *header, const u_char *packet)
            : ts(header->ts), data(packet, packet + header->caplen),
              caplen(header->caplen), len(header->len) {}

        // To String
        std::string toString() const {
            std::string str;
            str += "Timestamp: " + std::to_string(ts.tv_sec) + "." + std::to_string(ts.tv_usec) + "\n";
            str += "Captured length: " + std::to_string(caplen) + "\n";
            str += "Original length: " + std::to_string(len) + "\n";
            return str;
        }

        // Friend declaration for the operator<<
        friend std::ostream &operator<<(std::ostream &os, const PacketData &pd);
    };

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

  private:
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
        {ProtoType::NDP, "ndp"},
        {ProtoType::IGMP, "igmp"},
        {ProtoType::MLD, "mld"}};

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
