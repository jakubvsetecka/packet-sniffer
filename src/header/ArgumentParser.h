/**
 * @file ArgumentParser.h
 * @brief Argument parser
 * @version 0.1
 * @date 13/04/2024
 * @author Jakub Všetečka
 */

#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

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

  private:
    std::string interface;
    int port;
    bool tcp, udp, ndp, arp, icmp4, icmp6, igmp, mld;
    int numPackets;

    /**
     * @brief Validate the arguments
     *
     * @return void
     */
    void validateArguments() const;

    /**
     * @brief List the network interfaces
     *
     * @return void
     */
    void listNetworkInterfaces() const;
};

#endif // ARGUMENT_PARSER_H
