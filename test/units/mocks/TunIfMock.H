#ifndef __TUNIFMOCK_H__
#define __TUNIFMOCK_H__

#include "TunIf.H"

class TunIfMock: public TunIf {
    public:
        TunIfMock(string tun_name): TunIf(tun_name) {}
};

#endif
