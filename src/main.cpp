/**
 * @file main.cpp
 * @brief Main file
 * @version 0.2
 * @date 18/04/2024
 * @author Jakub Všetečka
 */

#include "ArgumentParser.h"
#include "PacketData.h"
#include "PacketHandler.h"
#include "PacketSniffer.h"
#include "RealIPCAPWrapper.h"
#include "SignalHandler.h"
#include "ThreadSafeQueue.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        ArgumentParser parser;
        parser.parse(argc, argv);
        if (parser.devices_listed) {
            return 0;
        }

        SignalHandler signalHandler;
        signalHandler.setSignalHandler();

        ThreadSafeQueue<PacketData> queue;

        PacketHandler handler(&queue);

        RealPCAPWrapper pcapWrapper;

        PacketSniffer sniffer(&pcapWrapper, parser.getInterface(), &queue, parser.getProtocols(), parser.getNumPackets(), parser.getPort(), parser.getPortType());
        sniffer.startCapture();

        handler.stop();

        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
