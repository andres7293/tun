#ifndef __TUNIF_H__
#define __TUNIF_H__

#include <stdint.h>
#include <sys/types.h>
#include <string>
#include <iostream>

#include "NetworkInterface.H"

using namespace std;

class TunIf: public NetworkInterface {
    public:
        TunIf(string tun_name);
        ~TunIf() {}
        bool alloc();
        int dealloc();
        bool isAllocated();
        int getErrno();
        int getFd();
        string& getTunName();

        virtual ssize_t nread(uint8_t *buf, size_t len);
        virtual ssize_t nwrite(uint8_t *buf, size_t len);
    private:
        string tun_name;
        int fd;

        fd_set readfds;
        fd_set writefds;
        fd_set exceptfds;
        struct timeval tv;

        int tun_alloc(char *dev);
};


#endif
