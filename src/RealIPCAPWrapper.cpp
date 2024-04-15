/**
 * @file RealIPCAPWrapper.cpp
 * @brief RealIPCAPWrapper class implementation
 * @date 15/04/2024
 * @version 1.0
 * @author Jakub Všetečka
 */

#include "RealIPCAPWrapper.h"

pcap_t *RealPCAPWrapper::open_live(const char *device, int snaplen, int promisc, int to_ms, char *errbuf) {
    return pcap_open_live(device, snaplen, promisc, to_ms, errbuf);
}

int RealPCAPWrapper::compile(pcap_t *p, struct bpf_program *fp, const char *str, int optimize, bpf_u_int32 netmask) {
    return pcap_compile(p, fp, str, optimize, netmask);
}

int RealPCAPWrapper::setfilter(pcap_t *p, struct bpf_program *fp) {
    return pcap_setfilter(p, fp);
}

int RealPCAPWrapper::loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user) {
    return pcap_loop(p, cnt, callback, user);
}

void RealPCAPWrapper::close(pcap_t *p) {
    pcap_close(p);
}