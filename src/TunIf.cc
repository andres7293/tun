#include "TunIf.H"

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

TunIf::TunIf(string tun_name) {
    this->tun_name = tun_name;
    this->fd = -1;
}

bool TunIf::alloc() {
    this->fd = TunIf::tun_alloc((char *)this->tun_name.c_str());
    if (this->fd < 0)
        return false;
    return true;
}

int TunIf::dealloc() {
    return close(this->fd);
}

bool TunIf::isAllocated() {
    if (this->fd < 0)
        return false;
    return true;
}

int TunIf::getErrno() {
    return errno;
}

int TunIf::getFd() {
    return this->fd;
}

string& TunIf::getTunName() {
    return this->tun_name;
}

ssize_t TunIf::tunread(uint8_t *buf, size_t len) {
    this->tv.tv_sec = 5;
    this->tv.tv_usec = 0;
    FD_ZERO(&this->readfds);
    FD_ZERO(&this->writefds);
    FD_ZERO(&this->exceptfds);
    FD_SET(this->fd, &this->readfds);
    while (1) {
        int ret = select(this->fd + 1, &this->readfds, NULL, NULL, &tv);
        if (ret == -1) {
            cout << "Error select TunIf, errno=" << (int) this->getErrno() << endl;
            return -1;
        }
        else if (ret == 0) {
            //timeout
        }
        else if (FD_ISSET(this->fd, &this->readfds)) {
            return read(this->fd, buf, len);
        }
        FD_SET(this->fd, &this->readfds);
        this->tv.tv_sec = 5;
        this->tv.tv_usec = 0;
    }
}

ssize_t TunIf::tunwrite(uint8_t *buf, size_t len) {
    this->tv.tv_sec = 5;
    this->tv.tv_usec = 0;
    FD_ZERO(&this->readfds);
    FD_ZERO(&this->writefds);
    FD_ZERO(&this->exceptfds);
    FD_SET(this->fd, &this->writefds);
    while (1) {
        int ret = select(this->fd + 1, NULL, &this->writefds, NULL, &tv);
        if (ret == -1) {
            cout << "Error select TunIf, errno=" << (int) this->getErrno() << endl;
            return -1;
        }
        else if (ret == 0) {
            //timeout
        }
        else if (FD_ISSET(this->fd, &this->writefds)) {
            return write(this->fd, buf, len);
        }
        FD_SET(this->fd, &this->writefds);
        this->tv.tv_sec = 5;
        this->tv.tv_usec = 0;
    }
}

int TunIf::tun_alloc(char *dev) {
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
