#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdint.h>
#include "NetBuf.H"
#include "RawPointer.H"

class Packet {
    public:
        Packet(INetBuf& nbuf, uint16_t packetSize, RawPointer header, RawPointer payload):
            nbuf(nbuf),
            _psize(packetSize),
            header(header),
            payload(payload) {}

        INetBuf& getNetBuf() { return this->nbuf; }
        uint16_t getPacketSize() { return this->_psize; }
        RawPointer getHeader() { return this->header; }
        RawPointer getPayload() { return this->payload; }
        int boundCheck();
        uint8_t operator [] (int index);
    private:
        INetBuf &nbuf;
        uint16_t _psize;
        RawPointer header;
        RawPointer payload;

};

#endif
