#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdint.h>
#include "NetBuf.H"
#include "Buffer.H"

class Packet {
    public:
        Packet(INetBuf& nbuf, uint16_t packetSize, Buffer header, Buffer payload):
            nbuf(nbuf),
            _psize(packetSize),
            header(header),
            payload(payload) {}

        INetBuf& getNetBuf() { return this->nbuf; }
        uint16_t getPacketSize() { return this->_psize; }
        Buffer getHeader() { return this->header; }
        Buffer getPayload() { return this->payload; }
        int boundCheck();
        uint8_t operator [] (int index);
    private:
        INetBuf &nbuf;
        uint16_t _psize;
        Buffer header;
        Buffer payload;

};

#endif
