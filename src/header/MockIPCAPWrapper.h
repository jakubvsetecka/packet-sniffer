#ifndef MOCK_PCAP_WRAPPER_H
#define MOCK_PCAP_WRAPPER_H

#include "IPCAPWrapper.h"
#include "gmock/gmock.h"

class MockPCAPWrapper : public IPCAPWrapper {
  public:
    MOCK_METHOD(pcap_t *, open_live, (const char *device, int snaplen, int promisc, int to_ms, char *errbuf), (override));
    MOCK_METHOD(int, compile, (pcap_t * p, struct bpf_program *fp, const char *str, int optimize, bpf_u_int32 netmask), (override));
    // Include other MOCK_METHODs
};

#endif // MOCK_PCAP_WRAPPER_H