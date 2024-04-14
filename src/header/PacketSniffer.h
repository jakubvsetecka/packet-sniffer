/**
 * @file PacketSniffer.h
 * @brief Network sniffer
 * @version 0.1
 * @date 14/04/2024
 * @author Jakub Všetečka
 */

#ifndef PACKET_SNIFFER_H
#define PACKET_SNIFFER_H

#include "ThreadSafeQueue.h"
#include <pcap.h>
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
    PacketSniffer(const std::string &device, ThreadSafeQueue<PacketData> *queue);

    /**
     * @brief Destructor
     */
    ~PacketSniffer();

    /**
     * @brief Apply a filter
     *
     * @return void
     */
    void applyFilter(); // TODO

    /**
     * @brief Start capturing packets
     *
     * @return void
     */
    void startCapture();

  private:
    pcap_t *handle;
    ThreadSafeQueue<PacketData> *queue;

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
