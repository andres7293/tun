#ifndef __NETDEVMOCK_H__
#define __NETDEVMOCK_H__

#include <stdint.h>
#include "../../src/TunIf.H"

class NetDevMock: public NetDev {
    public:
        NetDevMock(TunIf &tunif): NetDev(tunif) {}
        size_t write(uint8_t *buf, uint16_t size) { return size; }
        size_t read(uint8_t *buf, uint16_t size) { return size; }
};

#endif
