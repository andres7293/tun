#include "NetDev.H"

size_t NetDev::nwrite(uint8_t *buf, uint16_t size) {
    return this->net.nwrite(buf, size);
}

size_t NetDev::nread(uint8_t *buf, uint16_t size) {
    return this->net.nread(buf, size);
}
