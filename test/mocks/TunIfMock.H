#ifndef __TUNIFMOCK_H__
#define __TUNIFMOCK_H__

#include "../../src/TunIf.H"

class TunIfMock: public TunIf {
    public:
        TunIfMock(string tun_name): TunIf(tun_name) {}
};

#endif
