#include <cstdint>
#include <iostream>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "IP.H"
#include "Utils.H"
#include "TunIf.H"

using namespace std;

uint8_t buf[1024 * 1];

void print_header_host(IP_Header_t *h);

int main(void) {
    TunIf tunif("tun0");
    if (!tunif.alloc()) {
        cout << "Error opening /dev/tun" << endl;
        return -1;
    }
    while (1) {
        ssize_t bytesRead = tunif.tunread(buf, sizeof(buf));
        IP::ip_rcv(buf, (uint16_t) bytesRead);
    }
    tunif.dealloc();
    return 0;
}

void print_header_host(IP_Header_t *h) {
    cout   << "IP_Header{"
           << "version=0x"          << hex   << (int) IP_Header::getVersion(h)                << dec
           << ",headerLen=0x"       << hex   << (int) IP_Header::getHeaderLen(h)              << dec
           << ",tos=0x"             << hex   << (int) h->tos                                    << dec
           << ",total_len=0x"       << hex   << (int) utils::netToHostShort(h->total_len)       << dec
           << ",id=0x"              << hex   << (int) utils::netToHostShort(h->id)              << dec
           << ",flags=0x"           << hex   << (int) IP_Header::getFlags(h)                  << dec
           << ",fragmenOffset=0x"   << hex   << (int) IP_Header::getFragmentOffset(h)         << dec
           << ",ttl=0x"             << hex   << (int) h->ttl                                    << dec
           << ",protocol=0x"        << hex   << (int) h->protocol                               << dec
           << ",header_checksum=0x" << hex   << (int) utils::netToHostShort(h->header_checksum) << dec
           << ",src_addr=0x"        << hex   << (int) utils::netToHostLong(h->src_addr)         << dec
           << ",dst_addr=0x"        << hex   << (int) utils::netToHostLong(h->dst_addr)         << dec
           << "}"                   << endl;
}
