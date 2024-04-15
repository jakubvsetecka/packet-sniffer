/**
 * @file PacketSniffer_tests.cpp
 * @brief Tests for the PacketSniffer class
 * @version 0.1
 * @date 15/04/2024
 * @author Jakub Všetečka
 */

#include "MockIPCAPWrapper.h"
#include "PacketSnifferTestWrapper.h"
#include "ThreadSafeQueue.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

using namespace testing;

/**
 * @brief PacketSnifferTest
 *
 * Test fixture for PacketSniffer
 */
class PacketSnifferTest : public Test {
  protected:
    MockIPCAPWrapper *mockWrapper;
    ThreadSafeQueue<PacketSniffer::PacketData> *packetQueue;
    std::unordered_map<ProtoType, bool> protocols;
    std::string device;
    PacketSnifferTestWrapper *sniffer;
    int numPackets;
    int port;
    PortType portType;

    /**
     * @brief SetUp
     */
    void SetUp() override {
        mockWrapper = new MockIPCAPWrapper();
        packetQueue = new ThreadSafeQueue<PacketSniffer::PacketData>();
        protocols[ProtoType::TCP] = true;
        numPackets = 100;
        port = 8080;
        portType = PortType::SOURCE;
    }

    /**
     * @brief TearDown
     */
    void TearDown() override {
        delete sniffer;
        delete packetQueue;
        delete mockWrapper;
    }
};

/**
 * @brief ConstructorFailureOpenLive
 *
 * Test case for the constructor when open_live fails
 */
TEST_F(PacketSnifferTest, ConstructorFailureOpenLive) {
    EXPECT_CALL(*mockWrapper, open_live(_, _, _, _, _))
        .WillOnce(Return(nullptr)); // Ensure open_live fails for this test
    EXPECT_CALL(*mockWrapper, close(_))
        .Times(0); // Ensure close is called once

    EXPECT_THROW({
        sniffer = new PacketSnifferTestWrapper(mockWrapper, device, packetQueue, protocols, numPackets, port, portType);
    },
                 std::runtime_error);
}

/**
 * @brief ConstructorSuccess
 *
 * Test case for the constructor when everything succeeds
 */
TEST_F(PacketSnifferTest, ConstructorSuccess) {
    // Adjust expectations for success scenario
    EXPECT_CALL(*mockWrapper, open_live(_, _, _, _, _))
        .WillOnce(Return(reinterpret_cast<pcap_t *>(0x123456))); // Return a dummy handle
    EXPECT_CALL(*mockWrapper, close(_))
        .Times(1); // Ensure close is called once

    EXPECT_NO_THROW({
        sniffer = new PacketSnifferTestWrapper(mockWrapper, device, packetQueue, protocols, numPackets, port, portType);
    });
}

/**
 * @brief CreateFilterCorrectness
 *
 * Test case for the createFilter method
 */
TEST_F(PacketSnifferTest, CreateFilterCorrectness) {
    // Setup for a successful creation
    pcap_t *dummyHandle = reinterpret_cast<pcap_t *>(0x123456);
    EXPECT_CALL(*mockWrapper, open_live(_, _, _, _, _))
        .WillOnce(Return(dummyHandle)); // Return a dummy handle
    EXPECT_CALL(*mockWrapper, close(_))
        .Times(1); // Ensure close is called once

    sniffer = new PacketSnifferTestWrapper(mockWrapper, device, packetQueue, protocols, numPackets, port, portType);
    std::string expectedFilter = "src port 8080 and (tcp)";
    ASSERT_EQ(sniffer->testCreateFilter(), expectedFilter);
}

/**
 * @brief StartCaptureProcess
 *
 * Test case for the startCapture method
 */
TEST_F(PacketSnifferTest, StartCaptureProcess) {
    pcap_t *dummyHandle = reinterpret_cast<pcap_t *>(0x123456);
    EXPECT_CALL(*mockWrapper, open_live(_, _, _, _, _))
        .WillOnce(Return(dummyHandle)); // Ensure open_live succeeds for this test
    EXPECT_CALL(*mockWrapper, close(_))
        .Times(1); // Ensure close is called once

    sniffer = new PacketSnifferTestWrapper(mockWrapper, device, packetQueue, protocols, numPackets, port, portType);

    EXPECT_CALL(*mockWrapper, loop(dummyHandle, numPackets, _, _))
        .Times(1); // Verify that loop is called correctly

    EXPECT_NO_THROW({
        sniffer->startCapture();
    });
}