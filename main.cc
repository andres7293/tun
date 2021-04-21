#include <cstdint>
#include <iostream>

#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

#include "IPv4.H"
#include "Utils.H"

using namespace std;

int tun_alloc(char *dev);

uint8_t buf[1024 * 1];

void print_header_host(IPv4_Header_t *h);

int main(void) {
    string dev = "tun0";
    int fd = tun_alloc((char *)dev.c_str());
    if (fd < 0) {
        cout << "Error opening /dev/tun" << endl;
    }

    struct timeval tv = {
        .tv_sec = 5,
        .tv_usec = 0
    };
    fd_set readfds;
    fd_set writefds;
    fd_set exceptfds;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&exceptfds);

    FD_SET(fd, &readfds);
    FD_SET(fd, &writefds);
    FD_SET(fd, &exceptfds);

    while (1) {
        int ret = select(fd + 1, &readfds, NULL, NULL, &tv);
        if (ret == -1) {
            cout << "Error select: errno = " << errno << endl;
        }
        else if (ret == 0) {
            //timeout
        }
        else {
            if (FD_ISSET(fd, &readfds)) {
                ssize_t bytesRead = read(fd, buf, sizeof(buf));
                if (bytesRead >= (int)sizeof(IPv4_Header_t)) {
                    IPv4_Header_t *header = (IPv4_Header_t *) buf;
                    if (header->protocol == 0x01) {
                        print_header_host(header);
                    }
                }
            }
            else if (FD_ISSET(fd, &writefds)) {
                cout << "write available" << endl;
            }
            else if (FD_ISSET(fd, &exceptfds)) {
                cout << "except available" << endl;
            }
        }
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        FD_SET(fd, &readfds);
        //FD_SET(fd, &writefds);
        //FD_SET(fd, &exceptfds);
    }
    close(fd);
    return 0;
}

int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd, err;

    if( (fd = open("/dev/net/tun", O_RDWR | O_NONBLOCK)) < 0 )
        return fd;

    memset(&ifr, 0, sizeof(ifr));

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers) 
     *        IFF_TAP   - TAP device  
     *
     *        IFF_NO_PI - Do not provide packet information  
     */ 
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    if( *dev )
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
        close(fd);
        return err;
    }
    strcpy(dev, ifr.ifr_name);
    return fd;
}

void print_header_host(IPv4_Header_t *h) {
    cout   << "IPv4_Header{"
           << "version=0x"          << hex   << (int) IPv4_Header::getVersion(h)                << dec
           << ",headerLen=0x"       << hex   << (int) IPv4_Header::getHeaderLen(h)              << dec
           << ",tos=0x"             << hex   << (int) h->tos                                    << dec
           << ",total_len=0x"       << hex   << (int) utils::netToHostShort(h->total_len)       << dec
           << ",id=0x"              << hex   << (int) utils::netToHostShort(h->id)              << dec
           << ",flags=0x"           << hex   << (int) IPv4_Header::getFlags(h)                  << dec
           << ",fragmenOffset=0x"   << hex   << (int) IPv4_Header::getFragmentOffset(h)         << dec
           << ",ttl=0x"             << hex   << (int) h->ttl                                    << dec
           << ",protocol=0x"        << hex   << (int) h->protocol                               << dec
           << ",header_checksum=0x" << hex   << (int) utils::netToHostShort(h->header_checksum) << dec
           << ",src_addr=0x"        << hex   << (int) utils::netToHostLong(h->src_addr)         << dec
           << ",dst_addr=0x"        << hex   << (int) utils::netToHostLong(h->dst_addr)         << dec
           << "}"                   << endl;
}
