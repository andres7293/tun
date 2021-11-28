#ifndef __NETWORK_INTERFACE_H
#define __NETWORK_INTERFACE_H

#include <sys/types.h>

class NetworkInterface {
    public:
        virtual ~NetworkInterface() {}
        virtual ssize_t nread(uint8_t* buf, size_t len) = 0;
        virtual ssize_t nwrite(uint8_t* buf, size_t len) = 0;
};

#endif
