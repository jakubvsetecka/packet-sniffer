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

int main(int argc, char *argv[]) {
    ArgumentParser parser;
    parser.parse(argc, argv);
    parser.displayConfig();
    return 0;
}