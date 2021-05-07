#include "NetBuf.H"
#include <string.h>

NetBuf::NetBuf(uint16_t size) {
    this->ctor(size);
}

NetBuf::~NetBuf() {
    if (this->p != nullptr) {
        delete[] this->p;
    }
}

NetBuf::NetBuf(const NetBuf &n) {
    ctor(n.size);
    memcpy((uint8_t *)this->p, (uint8_t *) n.p, n.size);
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
