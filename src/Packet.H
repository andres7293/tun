#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdint.h>
#include "NetBuf.H"
#include "Buffer.H"

class Packet {
    public:
        Packet() {}
        Packet(Buffer packet): packet_{packet} {}
        Packet(uint8_t* p, unsigned int size):
            packet_{Buffer{p, size}} {}
        virtual ~Packet() {}

        uint8_t* data() { return static_cast<uint8_t*>(this->packet_.data()); }
        unsigned int size() { return this->packet_.size(); }
        Buffer get() { return this->packet_; }

        Buffer getNetworkLayer() { return this->networkLayer_; }
        Buffer getTransportLayer() { return this->transportLayer_; }

        void setNetworkLayer(uint8_t* p, unsigned int len)
        {
            this->networkLayer_ = Buffer{p, len};
        }

        void setTransportLayer(uint8_t* p, unsigned int len)
        {
            this->transportLayer_ = Buffer{p, len};
        }
    private:
        Buffer packet_;

        Buffer networkLayer_;
        Buffer transportLayer_;
};

#endif
