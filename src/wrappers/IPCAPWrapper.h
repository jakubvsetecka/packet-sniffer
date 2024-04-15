#ifndef IPCAP_WRAPPER_H
#define IPCAP_WRAPPER_H

#include <pcap.h>

class IPCAPWrapper {
  public:
    virtual ~IPCAPWrapper() = default;
    virtual pcap_t *open_live(const char *device, int snaplen, int promisc, int to_ms, char *errbuf) = 0;
    virtual int compile(pcap_t *p, struct bpf_program *fp, const char *str, int optimize, bpf_u_int32 netmask) = 0;
    virtual int setfilter(pcap_t *p, struct bpf_program *fp) = 0;
    virtual int loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user) = 0;
    virtual void close(pcap_t *p) = 0;
};

#endif // IPCAP_WRAPPER_H
