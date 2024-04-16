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
#include "PacketData.h"
#include "PacketHandler.h"
#include "PacketSniffer.h"
#include "RealIPCAPWrapper.h"
#include "ThreadSafeQueue.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        ArgumentParser parser;
        parser.parse(argc, argv);
        parser.displayConfig();

        ThreadSafeQueue<PacketData> queue;

        PacketHandler handler(&queue);

        RealPCAPWrapper pcapWrapper;

        PacketSniffer sniffer(&pcapWrapper, "eth0", &queue, parser.getProtocols(), parser.getNumPackets(), parser.getPort(), parser.getPortType());
        sniffer.startCapture();
        std::cout << "Captured " << queue.size() << " packets" << std::endl;

        handler.stop();

        queue.print();

        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}