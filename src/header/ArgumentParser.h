/**
 * @file ArgumentParser.h
 * @brief Argument parser
 * @version 0.1
 * @date 13/04/2024
 * @author Jakub Všetečka
 */

#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include "PortType.h"
#include "ProtoType.h"
#include <string>
#include <unordered_map>

/**
 * @brief Argument parser
 *
 */
class ArgumentParser {
  public:
    ArgumentParser();

    /**
     * @brief Display the usage
     *
     * @return void
     */
    void usage() const;

    /**
     * @brief Parse the arguments
     *
     * @param argc
     * @param argv
     * @return void
     */
    void parse(int argc, char *argv[]);

    /**
     * @brief Display the configuration
     *
     * @return void
     */
    void displayConfig() const;

    /**
     * @brief Get the interface
     *
     * @return std::string
     */
    std::string getInterface() const { return interface; }

    /**
     * @brief Get the port
     *
     * @return int
     */
    int getPort() const { return port; }

    /**
     * @brief Get the port type
     *
     * @return PortType
     */
    PortType getPortType() const { return t_portType; }

    /**
     * @brief Get the protocols
     *
     * @return std::unordered_map<std::string, bool>
     */
    std::unordered_map<ProtoType, bool> getProtocols() const { return protocols; }

    /**
     * @brief Get the number of packets
     *
     * @return int
     */
    int getNumPackets() const { return numPackets; }

  private:
    std::string interface;

    int port;
    PortType t_portType;
    std::unordered_map<ProtoType, bool> protocols;
    int numPackets;

    /**
     * @brief Validate the arguments
     *
     * @return void
     */
    void validateArguments() const;

    /**
     * @brief Check if all protocols are disabled
     *
     * @return bool
     */
    bool areAllProtocolsDisabled() const;

    /**
     * @brief List the network interfaces
     *
     * @return void
     */
    void listNetworkInterfaces() const;
};

#endif // ARGUMENT_PARSER_H
