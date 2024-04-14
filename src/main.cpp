/**
 * @file main.cpp
 * @brief Main file
 * @version 0.1
 * @date 13/04/2024
 * @author Jakub Všetečka
 *
 * @note THIS IS A TEST
 */

#include "ArgumentParser.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        ArgumentParser parser;
        parser.parse(argc, argv);
        parser.displayConfig();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}