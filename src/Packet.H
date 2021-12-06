#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdint.h>
#include "NetBuf.H"
#include "Buffer.H"

class Packet {
    public:
        Packet() {}
        Packet(Buffer packet): packet_{packet} {}
        virtual ~Packet() {}

        uint8_t* data() { return static_cast<uint8_t*>(this->packet_.data()); }
        Buffer get() { return this->packet_; }
        unsigned int size() { return this->packet_.size(); }

        void setNetworkLayerHeader(uint8_t* h, unsigned int len)
        {
            this->networkLayerHeader_ = Buffer{h, len};
        }
        void setNetworkLayer(uint8_t* p, unsigned int len)
        {
            this->networkLayer_ = Buffer{p, len};
        }

        void setTransportLayerHeader(uint8_t* h, unsigned int len)
        {
            this->transportLayerHeader_ = Buffer{h, len};
        }
        void setTransportLayer(uint8_t* p, unsigned int len)
        {
            this->transportLayer_ = Buffer{p, len};
        }
    private:
        Buffer packet_;

        Buffer networkLayerHeader_;
        Buffer networkLayer_;

        Buffer transportLayerHeader_;
        Buffer transportLayer_;
};

#endif
