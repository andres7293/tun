#include "NetBuf.H"
#include <string.h>

NetBuf::NetBuf(std::vector<uint8_t> v) {
    this->ctor(v.size());
    memcpy((uint8_t *) this->p, (uint8_t *) v.data(), this->size);
}

NetBuf::NetBuf(uint8_t *data, uint16_t size) {
    this->ctor(size);
    memcpy((uint8_t *) this->p, (uint8_t *) data, this->size);
}

NetBuf::NetBuf(uint16_t size) {
    this->ctor(size);
}

NetBuf::~NetBuf() {
    if (this->p != nullptr) {
        delete[] this->p;
    }
}

uint8_t* NetBuf::getBuf() {
    return this->p;
}

uint16_t NetBuf::getSize() {
    return this->size;
}

void NetBuf::ctor(uint16_t size) {
    this->size = size;
    this->p = new uint8_t[size];
}
