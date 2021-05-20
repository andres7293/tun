#include "Packet.H"

int Packet::boundCheck() {
    uint16_t maxBufSize = this->nbuf.size();
    uint16_t psize = this->getPacketSize();
    if (psize > maxBufSize)
        return -1;
    if (this->header.size() > maxBufSize)
        return -2;
    if (this->payload.size() > maxBufSize)
        return -3;
    return 0;
}
