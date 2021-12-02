#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdint.h>
#include "NetBuf.H"
#include "Buffer.H"

class Packet {
    public:
        Packet() {}
        Packet(Buffer packet): packet{packet} {}
        virtual ~Packet() {}

        Buffer packet;
        Buffer networkLayer;
        Buffer transportLayer;
};

#endif
