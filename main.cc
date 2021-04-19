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

using namespace std;

int tun_alloc(char *dev);

uint8_t buf[1024 * 1];

int main(void) {
    uint8_t raw_frame[] = {0x45, 0x00, 0x00, 0x54, 0x2f, 0x87, 0x40, 0x00, 0x40, 0x01, 0xf7, 0x1f, 0x0a, 0x00, 0x00, 0x01, 0x0a, 0x00, 0x00, 0x02, 0x08, 0x00, 0x2d, 0x25, 0x57, 0xb6, 0x00, 0x01, 0x48, 0x72, 0x7d, 0x60, 0x00, 0x00, 0x00, 0x00, 0xe2, 0x7d, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};

    IPv4_Header_t *raw_header = (IPv4_Header_t *) raw_frame;
    cout << *raw_header << endl;
    IPv4 ipv4(raw_frame);

    return 0;
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
            cout << "timeout" << endl;
        }
        else {
            if (FD_ISSET(fd, &readfds)) {
                //ssize_t bytesRead = read(fd, buf, sizeof(buf));
                read(fd, buf, sizeof(buf));
                IPv4 ipv4(buf);
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

