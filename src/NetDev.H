#ifndef __NETDEV_H__
#define __NETDEV_H__

#include <stdint.h>
#include <cstddef>

#include "TunIf.H"

class NetDev {
    public:
        NetDev(TunIf &tunif): tunif(tunif) {};
        size_t write(uint8_t *buf, uint16_t size);
        size_t read(uint8_t *buf, uint16_t size);
    private:
        TunIf &tunif;
};

#endif
