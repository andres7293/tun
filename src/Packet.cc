#include "Packet.H"

int Packet::boundCheck() {
    uint16_t maxBufSize = this->nbuf.size();
    uint16_t psize = this->getPacketSize();
    if (psize > maxBufSize)
        return -1;
    if (psize > maxBufSize)
        return -2;
    if (psize > maxBufSize)
        return -3;
    return 0;
}
