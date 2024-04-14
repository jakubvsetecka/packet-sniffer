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
    enum class portType { SOURCE,
                          DESTINATION,
                          ANY };

    std::string toString(portType t) const;

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
    portType t_portType;
    std::unordered_map<std::string, bool> protocols;
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
     * @param protocols
     * @return bool
     */
    bool areAllProtocolsDisabled(const std::unordered_map<std::string, bool> &protocols) const;

    /**
     * @brief List the network interfaces
     *
     * @return void
     */
    void listNetworkInterfaces() const;
};

#endif // ARGUMENT_PARSER_H
