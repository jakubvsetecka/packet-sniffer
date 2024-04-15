#ifndef REAL_PCAP_WRAPPER_H
#define REAL_PCAP_WRAPPER_H

#include "IPCAPWrapper.h"

class RealPCAPWrapper : public IPCAPWrapper {
  public:
    pcap_t *open_live(const char *device, int snaplen, int promisc, int to_ms, char *errbuf) override;
    int compile(pcap_t *p, struct bpf_program *fp, const char *str, int optimize, bpf_u_int32 netmask) override;
    int setfilter(pcap_t *p, struct bpf_program *fp) override;
    int loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user) override;
    void close(pcap_t *p) override;
};

#endif // REAL_PCAP_WRAPPER_H
