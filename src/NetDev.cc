#include "NetDev.H"

size_t NetDev::write(uint8_t *buf, uint16_t size) {
    return this->tunif.tunwrite(buf, size);
}

size_t NetDev::read(uint8_t *buf, uint16_t size) {
    return this->tunif.tunread(buf, size);
}
