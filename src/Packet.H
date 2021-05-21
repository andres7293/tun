#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdint.h>
#include "NetBuf.H"
#include "Buffer.H"

class IPacket {
    public:
        virtual uint8_t* data() = 0;
        virtual uint16_t size() = 0;
        virtual INetBuf& getNetBuf() = 0;
        virtual Buffer getHeader() = 0;
        virtual Buffer getPayload() = 0;
        virtual int boundCheck() = 0;
};

class Packet: public IPacket {
    public:
        Packet(INetBuf& nbuf, uint16_t packetSize, Buffer header, Buffer payload):
            nbuf(nbuf),
            _psize(packetSize),
            header(header),
            payload(payload) {}

        uint8_t* data() { return this->nbuf.data(); }
        uint16_t size() { return this->_psize; }
        INetBuf& getNetBuf() { return this->nbuf; }
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
