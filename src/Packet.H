#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdint.h>
#include "NetBuf.H"
#include "Buffer.H"

class Packet {
    public:
        virtual uint8_t* header() = 0;
        virtual unsigned int headerSize() = 0;

        virtual uint8_t* payload() = 0;
        virtual unsigned int payloadSize() = 0;

        virtual uint16_t checksum() = 0;
};

#endif
