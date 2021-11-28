#ifndef __TUNIFMOCK_H__
#define __TUNIFMOCK_H__

#include "TunIf.H"

class TunIfMock: public TunIf {
    public:
        TunIfMock(string tun_name): TunIf(tun_name) {}
        ~TunIfMock() {}
        ssize_t nread(uint8_t *buf, size_t len) { return len; }
        ssize_t nwrite(uint8_t *buf, size_t len) { return len; }
};

#endif
