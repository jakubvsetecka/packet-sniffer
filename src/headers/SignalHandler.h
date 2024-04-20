/**
 * @file SignalHandler.h
 * @brief Signal handler
 * @version 0.1
 * @date 20/04/2024
 * @author Jakub Všetečka
 */

#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <csignal>
#include <iostream>

class SignalHandler {
  public:
    SignalHandler() {}
    ~SignalHandler() = default;

    static void handleSignal(int signal) {
        switch (signal) {
        case SIGINT:
            exit(0);
            break;
        default:
            std::cerr << "Caught unknown signal" << std::endl;
            exit(signal);
        }
    }

    void setSignalHandler() {
        signal(SIGINT, (__sighandler_t)handleSignal);
    }
};

#endif // SIGNALHANDLER_H