#ifndef __NETDEV_H__
#define __NETDEV_H__

#include <stdint.h>
#include <cstddef>

#include "NetworkInterface.H"

class NetDev {
    public:
        NetDev(NetworkInterface &net): net(net) {};
        virtual ~NetDev() {};
        virtual size_t nread(uint8_t *buf, uint16_t size);
        virtual size_t nwrite(uint8_t *buf, uint16_t size);
    private:
        NetworkInterface &net;
};

#endif
