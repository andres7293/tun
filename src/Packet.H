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

        void setNetworkLayerHeader(Buffer header) { this->networkLayerHeader_ = header; };
        void setNetworkLayer(Buffer payload) { this->networkLayer_ = payload; };

        void setTransportLayerHeader(Buffer header) { this->transportLayerHeader_ = header; };
        void setTransportLayer(Buffer transport) { this->transportLayer_ = transport; };
    private:
        Buffer packet_;

        Buffer networkLayerHeader_;
        Buffer networkLayer_;

        Buffer transportLayerHeader_;
        Buffer transportLayer_;
};

#endif
