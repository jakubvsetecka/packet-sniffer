#ifndef MOCK_PCAP_WRAPPER_H
#define MOCK_PCAP_WRAPPER_H

#include "IPCAPWrapper.h"
#include "gmock/gmock.h"

class MockIPCAPWrapper : public IPCAPWrapper {
  public:
    MOCK_METHOD(pcap_t *, open_live, (const char *device, int snaplen, int promisc, int to_ms, char *errbuf), (override));
    MOCK_METHOD(int, compile, (pcap_t * p, struct bpf_program *fp, const char *str, int optimize, bpf_u_int32 netmask), (override));
    MOCK_METHOD(int, setfilter, (pcap_t * p, struct bpf_program *fp), (override));
    MOCK_METHOD(void, close, (pcap_t * p), (override));
    MOCK_METHOD(int, loop, (pcap_t * p, int cnt, pcap_handler callback, u_char *user), (override));
};

#endif // MOCK_PCAP_WRAPPER_H