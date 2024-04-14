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
#include "PacketSniffer.h"
#include "ThreadSafeQueue.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        ArgumentParser parser;
        parser.parse(argc, argv);
        parser.displayConfig();
        ThreadSafeQueue<PacketSniffer::PacketData> queue;
        PacketSniffer sniffer("eth0", &queue);
        sniffer.startCapture();
        std::cout << "Captured " << queue.size() << " packets" << std::endl;
        queue.print();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}